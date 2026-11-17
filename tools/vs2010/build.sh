#!/usr/bin/env bash
# Build the lifted exes with the VS2010 SP1 x64 tools (cl 16.00.40219.1, link 10.0) under Wine.
# The original 2019 servers used this toolchain with /GL and /LTCG.
#
# Needs:
#   - ~/toolchains/vs2010 (see Docs/Plan/plan.md, "VS2010 SP1 compiler"). Never commit it.
#   - The clang build dir (default: build). The script takes the object list of each exe and the .res files from it.
# Usage: tools/vs2010/build.sh [EXE...]   (default: CacheGate LobbyGate SmartCouponDaemon PostOfficeDaemon)
# Env: LIFT_BUILD_DIR (clang build dir), VS2010_OUT (default: build-vs2010), JOBS (default: nproc)
# Output: $VS2010_OUT/<EXE>.exe and <EXE>.pdb.
set -euo pipefail
cd "$(dirname "$0")/../.."
R="$PWD"
B="${LIFT_BUILD_DIR:-build}"
O="${VS2010_OUT:-build-vs2010}"
JOBS="${JOBS:-$(nproc)}"
EXES=("$@"); [ ${#EXES[@]} -gt 0 ] || EXES=(CacheGate LobbyGate SmartCouponDaemon PostOfficeDaemon)
# shellcheck source=/dev/null
source "$HOME/toolchains/vs2010/bin/vs2010-env.sh"
[ -f "$B/build.ninja" ] || { echo "no $B/build.ninja: run tools/gate.sh first" >&2; exit 2; }
mkdir -p "$O/obj"

# The clang build gives these with crt0 and the Wine import libs. The VS2010 build uses the real CRT (msvcrt.lib, /MD).
skip_src() { case "$1" in src/crt/*) return 0;; esac; return 1; }

# Objects of one ninja target, with the objects of the static libs that it links (one level per call).
objs_of() {
  ninja -C "$B" -t query "$1" | sed -n '/^  input:/,/^  outputs:/p' | sed -E 's/^ +(\|\|? )?//' |
    grep -v -e '^input:' -e '^outputs:' -e '^CXX_' -e '^C_' -e '^/usr/' | sort -u
}
declare -A SEEN=()
collect() {
  local t f
  for f in $(objs_of "$1"); do
    [ -n "${SEEN[$f]:-}" ] && continue
    SEEN[$f]=1
    case "$f" in
      *.lib) [ "$f" = msvcp100.lib ] || collect "$f";;
      *.obj|*.res) echo "$f";;
    esac
  done
}

INC=""
for d in include $(sed -n '/set(LIFT_SRC_INCLUDE/,/^)/p' CMakeLists.txt | grep -o 'src/[^ )]*') \
         vendor/zstd/src/lib vendor/zstd/src/lib/common; do
  [ -d "$d" ] && INC="$INC /I$(winepath -w "$R/$d")"
done
export INC R O

# Compile one source to $O/obj/<path>.obj. Skip it when the object is newer than the source.
compile_one() {
  local src="$1" obj="$O/obj/$1.obj" log="$O/obj/$1.log" lang=""
  mkdir -p "$(dirname "$obj")"
  [ "$obj" -nt "$src" ] && return 0
  case "$src" in *.c) lang="/TC";; esac
  # /Z7: /Zi starts mspdbsrv.exe, which hangs under Wine. /FIwinsock2.h: the headers include windows.h first.
  if ! wine "$VS2010_BIN/cl.exe" /nologo /c /O2 /GL /EHsc /MD /Z7 /GR- /W3 /D_WIN64 /DNDEBUG /DWIN32_LEAN_AND_MEAN \
        /FIwinsock2.h $lang $INC /Fo"$(winepath -w "$R/$obj")" "$(winepath -w "$R/$src")" > "$log" 2>&1; then
    echo "FAIL $src (see $log)"; rm -f "$obj"; return 1
  fi
}
export -f compile_one

RC=0
for exe in "${EXES[@]}"; do
  SEEN=()
  mapfile -t items < <(collect "$exe.exe")
  srcs=(); res=()
  for it in "${items[@]}"; do
    if [[ "$it" == *.res ]]; then res+=("$B/$it"); continue; fi
    s="$(sed -E 's#^CMakeFiles/[^/]+\.dir/##; s#\.obj$##' <<< "$it")"
    # vendor/zstd objects have an absolute path in ninja.
    [[ "$s" == "$R"/* ]] && s="${s#"$R"/}"
    skip_src "$s" && continue
    [ -f "$s" ] || { echo "$exe: no source for $it" >&2; RC=1; continue; }
    srcs+=("$s")
  done
  echo "$exe: ${#srcs[@]} sources"
  printf '%s\n' "${srcs[@]}" | xargs -P "$JOBS" -I{} bash -c 'compile_one "$@"' _ {} || { RC=1; continue; }

  w=(); for s in "${srcs[@]}"; do w+=("$(winepath -w "$R/$O/obj/$s.obj")"); done
  for r in "${res[@]}"; do w+=("$(winepath -w "$R/$r")"); done
  rsp="$O/$exe.rsp"
  printf '"%s"\n' "${w[@]}" > "$rsp"
  if ! wine "$VS2010_BIN/link.exe" /nologo /LTCG /DEBUG /OPT:REF /OPT:ICF /SUBSYSTEM:CONSOLE /MACHINE:X64 \
       /OUT:"$(winepath -w "$R/$O/$exe.exe")" /PDB:"$(winepath -w "$R/$O/$exe.pdb")" @"$(winepath -w "$R/$rsp")" \
       msvcrt.lib msvcprt.lib kernel32.lib odbc32.lib ws2_32.lib iphlpapi.lib ole32.lib advapi32.lib shell32.lib \
       version.lib user32.lib shlwapi.lib > "$O/$exe.link.log" 2>&1; then
    echo "$exe: link FAIL (see $O/$exe.link.log)"; RC=1; continue
  fi
  echo "$exe: ok"
done
exit $RC
