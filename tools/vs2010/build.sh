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
# Header changes: the .dep file of each object lists its repo headers. A newer header rebuilds the object.
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

# Compile one source to $O/obj/<path>.obj. Skip it when the object is newer than the source
# and newer than each repo header that it included. /showIncludes gives the headers: they are
# written to $O/obj/<path>.dep (one Linux path per line). An object with no .dep file is stale.
# $2 = exe define tag (CG, LG, SCD, POD) for a source with a per-exe form: object in $O/obj/<tag>/<src>.obj, /DLIFT_EXE_<tag>.
compile_one() {
  local src="$1" tag="${2:-}" d="" lang="" h stale=0 pre="$O/obj"
  [ -n "$tag" ] && { pre="$O/obj/$tag"; d="/DLIFT_EXE_$tag"; }
  local obj="$pre/$1.obj" log="$pre/$1.log" dep="$pre/$1.dep"
  mkdir -p "$(dirname "$obj")"
  if [ -f "$obj" ] && [ -f "$dep" ] && [ "$obj" -nt "$src" ]; then
    while IFS= read -r h; do
      if [ ! -e "$h" ] || [ "$h" -nt "$obj" ]; then stale=1; break; fi
    done < "$dep"
    [ "$stale" = 0 ] && return 0
  fi
  case "$src" in *.c) lang="/TC";; esac
  # /Z7: /Zi starts mspdbsrv.exe, which hangs under Wine. /FIwinsock2.h: the headers include windows.h first.
  if ! wine "$VS2010_BIN/cl.exe" /nologo /c /O2 /GL /EHsc /MD /Z7 /GR- /W3 /D_WIN64 /DNDEBUG /DWIN32_LEAN_AND_MEAN \
        /showIncludes /FIwinsock2.h $d $lang $INC /Fo"$(winepath -w "$R/$obj")" "$(winepath -w "$R/$src")" > "$log" 2>&1; then
    echo "FAIL $src (see $log)"; rm -f "$obj" "$dep"; return 1
  fi
  # "Note: including file:   Z:\home\...\X.h" -> "/home/.../X.h". Keep only the files of the repo.
  tr -d '\r' < "$log" | sed -n 's/^Note: including file: *//p' | sed -E 's#^[Zz]:##; s#\\#/#g' |
    grep -F "$R/" | sort -u > "$dep" || true
}
export -f compile_one

RC=0
# LIFT: python filter, in this file so that the script has no extra file. stdin = sources; prints those that use the token LIFT_EXE_.
PEREXE_PY=$(cat <<'PYEOF'
"""Print the sources (stdin, one per line) that include a repo header or file with the token LIFT_EXE_.
These sources get one object per exe in tools/vs2010/build.sh (define -DLIFT_EXE_<X>)."""
import os, re, sys

ROOT = os.getcwd()
INC = ["include"] + sys.argv[1:]
INC_RE = re.compile(r'^\s*#\s*include\s+"([^"]+)"', re.M)
cache = {}


def resolve(name, cur):
    for d in [os.path.dirname(cur)] + INC:
        p = os.path.normpath(os.path.join(d, name))
        if os.path.isfile(p):
            return p
    return None


def uses(path, seen):
    if path in cache:
        return cache[path]
    if path in seen:
        return False
    seen.add(path)
    try:
        txt = open(path, encoding="utf-8", errors="replace").read()
    except OSError:
        return False
    r = "LIFT_EXE_" in txt
    if not r:
        for m in INC_RE.finditer(txt):
            p = resolve(m.group(1), path)
            if p and uses(p, seen):
                r = True
                break
    cache[path] = r
    return r


for line in sys.stdin:
    s = line.strip()
    if s and uses(os.path.normpath(s), set()):
        print(s)
PYEOF
)

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
  # LIFT: a source that has the token LIFT_EXE_ (itself or in a repo header) gets one object per exe.
  case "$exe" in CacheGate) tag=CG;; LobbyGate) tag=LG;; SmartCouponDaemon) tag=SCD;; PostOfficeDaemon) tag=POD;; *) tag="";; esac
  declare -A PE=()
  if [ -n "$tag" ]; then
    while IFS= read -r s; do PE[$s]=1; done < <(printf '%s\n' "${srcs[@]}" | python3 -c "$PEREXE_PY" $(sed -n '/set(LIFT_SRC_INCLUDE/,/^)/p' CMakeLists.txt | grep -o 'src/[^ )]*'))
  fi
  echo "$exe: ${#srcs[@]} sources, ${#PE[@]} per-exe"
  for s in "${srcs[@]}"; do echo "$s${PE[$s]:+ $tag}"; done |
    xargs -P "$JOBS" -L1 bash -c 'compile_one "$@"' _ || { RC=1; continue; }

  w=(); for s in "${srcs[@]}"; do
    if [ -n "${PE[$s]:-}" ]; then w+=("$(winepath -w "$R/$O/obj/$tag/$s.obj")"); else w+=("$(winepath -w "$R/$O/obj/$s.obj")"); fi
  done
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
