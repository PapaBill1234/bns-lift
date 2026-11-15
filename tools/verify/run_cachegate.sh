#!/usr/bin/env bash
# Run one CacheGate exe under wine64 for a fixed time. Save the console output, the
# listen ports and (with --pktlog) the pktlog records.
#
# Usage: tools/verify/run_cachegate.sh lifted|original [SECONDS] [--pktlog]
#   lifted   = build/CacheGate.exe (CMake target CacheGate)
#   original = Service_348_8349/Service/CacheGate/bin/CacheGate.exe (2019 + PDB; not CacheGate2019.exe)
# Env: CG_SRC_BIN   folder with the original exe and config (default: see below)
#      CG_ARGS      extra arguments for the exe (default: none)
#      CG_PKTLOG    folder with pktlog.dll and patch_import.py (default: bns-wine/pktlog)
#      LIFT_BUILD_DIR build folder (default: build)
# Output: build/verify/<kind>/ with console.txt, ports.txt, pktlog/*.pkl, exit.txt.
# The script uses its own Wine prefix (build/verify/wineprefix). It does not change your prefix.
set -euo pipefail
cd "$(dirname "$0")/../.."

KIND="${1:?usage: run_cachegate.sh lifted|original [SECONDS] [--pktlog]}"
SECS="${2:-20}"
PKTLOG=0
for a in "$@"; do [ "$a" = "--pktlog" ] && PKTLOG=1; done

B="${LIFT_BUILD_DIR:-build}"
CODEX="${CODEX_DIR:-$(cd ../.. && pwd)}"   # worktree is <Codex>/bns-wt/<slice>
SRC_BIN="${CG_SRC_BIN:-$CODEX/private-project/Service_348_8349/Service/CacheGate/bin}"
PKT="${CG_PKTLOG:-$CODEX/bns-wine/pktlog}"

case "$KIND" in
  lifted)   EXE_SRC="$B/CacheGate.exe" ;;
  original) EXE_SRC="$SRC_BIN/CacheGate.exe" ;;
  *) echo "unknown kind: $KIND" >&2; exit 2 ;;
esac
if [ ! -f "$EXE_SRC" ]; then
  echo "missing exe: $EXE_SRC" >&2
  [ "$KIND" = lifted ] && echo "build it first: cmake --build $B --target CacheGate" >&2
  exit 3
fi

OUT="$B/verify/$KIND"
RUN="$OUT/Server/CacheGate/bin"     # pktlog.dll takes the server name from <name>\bin\.
DRIVE_D="$OUT/drive_d"
rm -rf "$OUT"
mkdir -p "$RUN" "$DRIVE_D"

# Exe, original config, DLLs and data. No .pdb (not needed to run).
cp "$EXE_SRC" "$RUN/CacheGate.exe"
for f in "$SRC_BIN"/*.xml "$SRC_BIN"/*.dll "$SRC_BIN"/*.cfg; do [ -f "$f" ] && cp "$f" "$RUN/"; done
[ -d "$SRC_BIN/dict" ] && cp -r "$SRC_BIN/dict" "$RUN/"

if [ "$PKTLOG" = 1 ]; then
  cp "$PKT/pktlog.dll" "$RUN/"
  python3 -I "$PKT/patch_import.py" "$RUN/CacheGate.exe"
  rm -f "$RUN/CacheGate.exe.orig"
fi

# Own Wine prefix. Drive D: points to this run, so pktlog writes to $DRIVE_D/Logs/pktlog.
export WINEPREFIX="$PWD/$B/verify/wineprefix"
export WINEDEBUG="${WINEDEBUG:--all}"
WINE="$(command -v wine64 || command -v wine64-stable || command -v wine)"
if [ ! -d "$WINEPREFIX/dosdevices" ]; then
  "$WINE" wineboot -i >/dev/null 2>&1 || true
  "${WINE%/*}/wineserver" -w 2>/dev/null || wineserver -w || true
fi
ln -sfn "$PWD/$DRIVE_D" "$WINEPREFIX/dosdevices/d:"

ss -ltnH 2>/dev/null | awk '{print $4}' | sort -u > "$OUT/ports_before.txt" || true

# Run from the bin folder: the exe reads its config from the current folder.
set +e
( cd "$RUN" && timeout -s INT -k 5 "$SECS" "$WINE" CacheGate.exe ${CG_ARGS:-} ) \
  > "$OUT/console.raw" 2>&1 &
PID=$!
sleep $(( SECS > 4 ? SECS - 3 : 1 ))
ss -ltnH 2>/dev/null | awk '{print $4}' | sort -u > "$OUT/ports_during.txt" || true
wait "$PID"; echo "$?" > "$OUT/exit.txt"
set -e
WINESERVER="$(command -v wineserver || true)"
[ -n "$WINESERVER" ] && "$WINESERVER" -k 2>/dev/null || true

tr -d '\r' < "$OUT/console.raw" > "$OUT/console.txt"
comm -13 "$OUT/ports_before.txt" "$OUT/ports_during.txt" | sed 's/.*://' | sort -n -u > "$OUT/ports.txt"

if [ -d "$DRIVE_D/Logs/pktlog" ]; then
  mkdir -p "$OUT/pktlog"
  cp "$DRIVE_D"/Logs/pktlog/* "$OUT/pktlog/" 2>/dev/null || true
fi

echo "kind=$KIND exit=$(cat "$OUT/exit.txt") ports=$(tr '\n' ' ' < "$OUT/ports.txt")"
echo "console: $OUT/console.txt ($(wc -l < "$OUT/console.txt") lines)"
