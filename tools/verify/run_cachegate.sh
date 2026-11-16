#!/usr/bin/env bash
# Run one CacheGate exe under wine64 for a fixed time. Save the daemon log,
# the listen ports, (with --peer) the bytes that the exe sends to CacheD, and (with --pktlog) the
# pktlog records.
#
# Usage: tools/verify/run_cachegate.sh lifted|original [SECONDS] [--pktlog] [--peer] [--client]
#   lifted   = build/CacheGate.exe (CMake target CacheGate)
#   original = Service_348_8349/Service/CacheGate/bin/CacheGate.exe (2019 + PDB; not CacheGate2019.exe)
#   --pktlog = patch the copy with patch_import.py (pktlog.dll writes D:\Logs\pktlog\*.pkl)
#   --peer   = set the CacheD address in cached-list.config.xml to 127.0.0.1 and run
#              replay.py as the CacheD peer on the economy port (records what the exe sends)
#   --client = near the end, connect to public-port as a client, send CG_CLIENT_STREAM, record replies
# Env: CG_SRC_BIN   folder with the original exe and config (default: see below)
#      CG_ARGS      extra arguments for the exe (default: none)
#      CG_PKTLOG    folder with pktlog.dll and patch_import.py (default: bns-wine/pktlog)
#      CG_PEER_STREAM  bytes that the CacheD peer sends (default "-" = nothing)
#      CG_CLIENT_STREAM bytes that the client sends (default "-" = nothing)
#      CG_DISPLAY   X display for the console window (default :77, a hidden Xvfb)
#      CG_LIFTED_EXE   exe for "lifted" (default: build/CacheGate.exe; self test: the original exe)
#      LIFT_BUILD_DIR build folder (default: build)
# Output: build/verify/<kind>/ with log.txt, ports.txt, exit.txt, peer.txt, client.txt, pktlog/*.pkl.
# The console text is the same as log.txt (pktlog also records it as CONSOLE lines).
#
# Facts (found 2026-11-16 with the original exe):
# - The exe must have a console window (GetConsoleWindow). Without it, it starts in service mode and
#   crashes (page fault). So the script runs it in wineconsole on a hidden Xvfb display.
# - wineconsole must get the full Windows path of the exe. A relative name does not start it.
# - The config uses E:\Service\CacheGate\{bin,config} and E:\log\CacheGate\. E: points to the run
#   folder. The exe stops at start if config\cached-list.config.xml is missing.
# - The script uses its own Wine prefix (build/verify/wineprefix). It does not change your prefix.
set -euo pipefail
cd "$(dirname "$0")/../.."
ROOT="$PWD"

KIND="${1:?usage: run_cachegate.sh lifted|original [SECONDS] [--pktlog] [--peer]}"
SECS="${2:-20}"
PKTLOG=0; PEER=0; CLIENT=0
for a in "$@"; do
  [ "$a" = "--pktlog" ] && PKTLOG=1
  [ "$a" = "--peer" ] && PEER=1
  [ "$a" = "--client" ] && CLIENT=1
done

B="${LIFT_BUILD_DIR:-build}"
CODEX="${CODEX_DIR:-$(cd ../.. && pwd)}"   # worktree is <Codex>/bns-wt/<slice>
SRC_SVC="${CG_SRC_SVC:-$CODEX/private-project/Service_348_8349/Service/CacheGate}"
SRC_BIN="${CG_SRC_BIN:-$SRC_SVC/bin}"
SRC_CFG="${CG_SRC_CFG:-$SRC_SVC/config}"
PKT="${CG_PKTLOG:-$CODEX/bns-wine/pktlog}"

case "$KIND" in
  lifted)   EXE_SRC="${CG_LIFTED_EXE:-$B/CacheGate.exe}" ;;
  original) EXE_SRC="$SRC_BIN/CacheGate.exe" ;;
  *) echo "unknown kind: $KIND" >&2; exit 2 ;;
esac
if [ ! -f "$EXE_SRC" ]; then
  echo "missing exe: $EXE_SRC" >&2
  [ "$KIND" = lifted ] && echo "build it first: cmake --build $B --target CacheGate" >&2
  exit 3
fi

OUT="$ROOT/$B/verify/$KIND"
DRIVE_E="$OUT/drive_e"
DRIVE_D="$OUT/drive_d"
RUN="$DRIVE_E/Service/CacheGate/bin"   # pktlog.dll takes the server name from <name>\bin\.
rm -rf "$OUT"
mkdir -p "$RUN" "$DRIVE_E/Service/CacheGate/config" "$DRIVE_E/log/CacheGate" "$DRIVE_D/Logs/pktlog"

# Exe, original config, DLLs and data. No .pdb (not needed to run).
cp "$EXE_SRC" "$RUN/CacheGate.exe"
for f in "$SRC_BIN"/*.xml "$SRC_BIN"/*.dll "$SRC_BIN"/*.cfg; do [ -f "$f" ] && cp "$f" "$RUN/"; done
[ -d "$SRC_BIN/dict" ] && cp -r "$SRC_BIN/dict" "$RUN/"
cp "$SRC_CFG/cached-list.config.xml" "$DRIVE_E/Service/CacheGate/config/"

if [ "$PEER" = 1 ]; then
  sed -i -E "s/ip-address='[^']*'/ip-address='127.0.0.1'/" "$DRIVE_E/Service/CacheGate/config/cached-list.config.xml"
  ECON_PORT="$(grep -oE "economy-port='[0-9]+'" "$DRIVE_E/Service/CacheGate/config/cached-list.config.xml" | head -1 | grep -oE '[0-9]+')"
fi

PUB_PORT="$(grep -oE "name='public-port' value='[0-9]+'" "$RUN/cachegate.config.xml" | grep -oE '[0-9]+' | tail -1)"

if [ "$PKTLOG" = 1 ]; then
  cp "$PKT/pktlog.dll" "$RUN/"
  python3 -I "$PKT/patch_import.py" "$RUN/CacheGate.exe"
  rm -f "$RUN/CacheGate.exe.orig"
fi

WINE="$(command -v wine64 || command -v wine)"
WINESERVER="$(command -v wineserver || echo /usr/lib/x86_64-linux-gnu/wine/wineserver)"
export WINEPREFIX="$ROOT/$B/verify/wineprefix"
export WINEDEBUG="${WINEDEBUG:--all}"
export WINEDLLOVERRIDES="mscoree,mshtml="
export DISPLAY="${CG_DISPLAY:-:77}"
if [ "$DISPLAY" = ":77" ] && [ ! -e /tmp/.X11-unix/X77 ]; then
  nohup Xvfb :77 -screen 0 1024x768x16 >/dev/null 2>&1 &
  sleep 1
fi
if [ ! -d "$WINEPREFIX/dosdevices" ]; then
  "$WINE" wineboot -i >/dev/null 2>&1 || true
  "$WINESERVER" -w || true
fi
"$WINESERVER" -k 2>/dev/null || true
ln -sfn "$DRIVE_D" "$WINEPREFIX/dosdevices/d:"
ln -sfn "$DRIVE_E" "$WINEPREFIX/dosdevices/e:"

ss -ltnH 2>/dev/null | awk '{print $4}' | sort -u > "$OUT/ports_before.txt" || true

PEER_PID=""
if [ "$PEER" = 1 ]; then
  python3 -I "$ROOT/tools/verify/replay.py" listen "$ECON_PORT" "${CG_PEER_STREAM:--}" "$OUT/peer.txt" \
    --hdr 0 --wait "$SECS" --accept-timeout "$SECS" > "$OUT/peer.log" 2>&1 &
  PEER_PID=$!
fi

WEXE="E:\\Service\\CacheGate\\bin\\CacheGate.exe"
set +e
( cd "$RUN" && timeout -s INT -k 5 "$SECS" "$WINE" wineconsole "$WEXE" ${CG_ARGS:-} ) \
  > "$OUT/wine.txt" 2>&1 &
PID=$!
sleep $(( SECS > 8 ? SECS - 6 : 2 ))
ss -ltnH 2>/dev/null | awk '{print $4}' | sort -u > "$OUT/ports_during.txt" || true
if [ "$CLIENT" = 1 ]; then
  # Client on the public port (as a game server). Send CG_CLIENT_STREAM, record the replies.
  python3 -I "$ROOT/tools/verify/replay.py" connect "127.0.0.1:$PUB_PORT" "${CG_CLIENT_STREAM:--}" \
    "$OUT/client.txt" --hdr 0 --wait 2 > "$OUT/client.log" 2>&1 || true
fi
wait "$PID"; echo "$?" > "$OUT/exit.txt"
set -e
"$WINESERVER" -k 2>/dev/null || true
[ -n "$PEER_PID" ] && { kill "$PEER_PID" 2>/dev/null || true; wait "$PEER_PID" 2>/dev/null || true; }

cat "$DRIVE_E"/log/CacheGate/*.log 2>/dev/null | tr -d '\r' > "$OUT/log.txt" || : > "$OUT/log.txt"
comm -13 "$OUT/ports_before.txt" "$OUT/ports_during.txt" | sed 's/.*://' | sort -n -u > "$OUT/ports.txt"
[ "$PEER" = 1 ] && [ -n "${ECON_PORT:-}" ] && sed -i "/^${ECON_PORT}\$/d" "$OUT/ports.txt"   # replay.py port

mkdir -p "$OUT/pktlog"
cp "$DRIVE_D"/Logs/pktlog/* "$OUT/pktlog/" 2>/dev/null || true

echo "kind=$KIND exit=$(cat "$OUT/exit.txt") ports=$(tr '\n' ' ' < "$OUT/ports.txt")"
echo "log: $OUT/log.txt ($(wc -l < "$OUT/log.txt") lines)"
[ "$PEER" = 1 ] && echo "peer: $(tr '\n' ' ' < "$OUT/peer.log")"
[ "$CLIENT" = 1 ] && echo "client: $(tr '\n' ' ' < "$OUT/client.log")"
exit 0
