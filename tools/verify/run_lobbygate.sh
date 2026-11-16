#!/usr/bin/env bash
# Run one LobbyGate exe under wine64 for a fixed time. Save the log, the console output, the listen
# ports, (with --peer) the bytes that the exe sends to the LobbyDaemon peer, (with --client) the replies
# to clients, and (with --pktlog) the pktlog records.
#
# Usage: tools/verify/run_lobbygate.sh lifted|original [SECONDS] [--pktlog] [--peer] [--client]
#   lifted   = build/LobbyGate.exe (CMake target LobbyGate)
#   original = Service_348_8349/Service/LobbyGate/bin/LobbyGate.exe (the exe of the IDA copy;
#              not LobbyGate2019.exe, other PDB GUID)
#   --pktlog = patch the copy with patch_import.py (pktlog.dll writes D:\Logs\pktlog\*.pkl)
#   --peer   = set lobby-daemon-addr to 127.0.0.1 and run replay.py as the LobbyDaemon peer
#              (lobby-daemon-port). Records what the exe sends to the LobbyDaemon.
#   --client = near the end, connect to client-port and to internal-port, send LG_CLIENT_STREAM /
#              LG_INTERNAL_STREAM, record the replies
# Env: LG_SRC_SVC      service folder of the original (default: see below)
#      LG_ARGS         extra arguments for the exe (default: none)
#      LG_PKTLOG       folder with pktlog.dll and patch_import.py (default: bns-wine/pktlog)
#      LG_LOBBYD_STREAM bytes that the LobbyDaemon peer sends (default "-" = nothing)
#      LG_CLIENT_STREAM, LG_INTERNAL_STREAM bytes that the clients send (default "-" = nothing)
#      LG_CLIENT_AT    seconds after start for the --client connects (default SECONDS-6)
#      LG_DISPLAY      X display for the console window (default :77, a hidden Xvfb)
#      LG_LIFTED_EXE   exe for "lifted" (default: build/LobbyGate.exe; self test: the original)
#      LG_CERT         none | placeholder (default) | <file>: E:\Service\cert\Lobbygate.cfg
#                      initialize (0x12E70) only checks that fread gives > 0 bytes. It does not use the text.
#      LIFT_BUILD_DIR  build folder (default: build)
# Output: build/verify/lg-<kind>/ with log.txt, console.txt, ports.txt, exit.txt, peer-lobbyd.txt,
#         client-client.txt, client-internal.txt, pktlog/*.pkl.
# Facts: see Docs/Verify/LobbyGate.md. Same console and drive setup as run_smartcoupondaemon.sh.
set -euo pipefail
cd "$(dirname "$0")/../.."
ROOT="$PWD"

KIND="${1:?usage: run_lobbygate.sh lifted|original [SECONDS] [--pktlog] [--peer] [--client]}"
SECS="${2:-20}"
PKTLOG=0; PEER=0; CLIENT=0
for a in "$@"; do
  [ "$a" = "--pktlog" ] && PKTLOG=1
  [ "$a" = "--peer" ] && PEER=1
  [ "$a" = "--client" ] && CLIENT=1
done

B="${LIFT_BUILD_DIR:-build}"
CODEX="${CODEX_DIR:-$(cd ../.. && pwd)}"   # worktree is <Codex>/bns-wt/<slice>
SRC_SVC="${LG_SRC_SVC:-$CODEX/private-project/Service_348_8349/Service/LobbyGate}"
SRC_BIN="$SRC_SVC/bin"
PKT="${LG_PKTLOG:-$CODEX/bns-wine/pktlog}"
NAME=LobbyGate

case "$KIND" in
  lifted)   EXE_SRC="${LG_LIFTED_EXE:-$B/$NAME.exe}" ;;
  original) EXE_SRC="$SRC_BIN/$NAME.exe" ;;
  *) echo "unknown kind: $KIND" >&2; exit 2 ;;
esac
if [ ! -f "$EXE_SRC" ]; then
  echo "missing exe: $EXE_SRC" >&2
  [ "$KIND" = lifted ] && echo "build it first: cmake --build $B --target $NAME" >&2
  exit 3
fi

OUT="$ROOT/$B/verify/lg-$KIND"
DRIVE_E="$OUT/drive_e"
DRIVE_D="$OUT/drive_d"
RUN="$DRIVE_E/Service/$NAME/bin"   # pktlog.dll takes the server name from <name>\bin\.
CFG="$DRIVE_E/Service/$NAME/config"
rm -rf "$OUT"
mkdir -p "$RUN" "$CFG" "$DRIVE_E/Service/cert" "$DRIVE_E/log/$NAME" "$DRIVE_D/Logs/pktlog"

# Exe, original config and DLLs. No .pdb, no .7z, no 2019 exe. The service folder has no config\
# folder: the xml files go to bin\ and to config\ (config-path).
cp "$EXE_SRC" "$RUN/$NAME.exe"
for f in "$SRC_BIN"/*.xml "$SRC_BIN"/*.dll "$SRC_BIN"/*.cfg; do [ -f "$f" ] && cp "$f" "$RUN/"; done
[ -e "$SRC_BIN/dict" ] && cp -r "$SRC_BIN/dict" "$RUN/"
for f in "$SRC_BIN"/*.xml; do cp "$f" "$CFG/"; done
case "${LG_CERT:-placeholder}" in
  none) ;;
  placeholder) printf 'keyhere' > "$DRIVE_E/Service/cert/Lobbygate.cfg" ;;
  *) cp "$LG_CERT" "$DRIVE_E/Service/cert/Lobbygate.cfg" ;;
esac

opt() { grep -oE "name='$1' value='[^']*'" "$RUN/lobbygate.config.xml" | head -1 | sed -E "s/.*value='([^']*)'/\1/"; }
CLI_PORT="$(opt client-port)"
INT_PORT="$(opt internal-port)"
LD_PORT="$(opt lobby-daemon-port)"

if [ "$PEER" = 1 ]; then
  for x in "$RUN" "$CFG"; do
    sed -i -E "s/(name='lobby-daemon-addr' value=')[^']*'/\1127.0.0.1'/" "$x/lobbygate.config.xml"
  done
fi

if [ "$PKTLOG" = 1 ]; then
  cp "$PKT/pktlog.dll" "$RUN/"
  python3 -I "$PKT/patch_import.py" "$RUN/$NAME.exe"
  rm -f "$RUN/$NAME.exe.orig"
fi

WINE="$(command -v wine64 || command -v wine)"
WINESERVER="$(command -v wineserver || echo /usr/lib/x86_64-linux-gnu/wine/wineserver)"
export WINEPREFIX="$ROOT/$B/verify/wineprefix"
export WINEDEBUG="${WINEDEBUG:--all}"
export WINEDLLOVERRIDES="mscoree,mshtml="
export DISPLAY="${LG_DISPLAY:-:77}"
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

PEER_PIDS=()
if [ "$PEER" = 1 ]; then
  python3 -I "$ROOT/tools/verify/replay.py" listen "$LD_PORT" "${LG_LOBBYD_STREAM:--}" "$OUT/peer-lobbyd.txt" \
    --hdr 0 --wait "$SECS" --accept-timeout "$SECS" > "$OUT/peer-lobbyd.log" 2>&1 &
  PEER_PIDS+=($!)
fi

WEXE="E:\\Service\\$NAME\\bin\\$NAME.exe"
set +e
( cd "$RUN" && timeout -s INT -k 5 "$SECS" "$WINE" wineconsole "$WEXE" ${LG_ARGS:-} ) \
  > "$OUT/wine.txt" 2>&1 &
PID=$!
( while kill -0 "$PID" 2>/dev/null; do ss -ltnH 2>/dev/null | awk '{print $4}'; sleep 0.1; done ) \
  | sort -u > "$OUT/ports_during.txt" &
POLL_PID=$!
sleep "${LG_CLIENT_AT:-$(( SECS > 8 ? SECS - 6 : 2 ))}"
if [ "$CLIENT" = 1 ]; then
  python3 -I "$ROOT/tools/verify/replay.py" connect "127.0.0.1:$CLI_PORT" "${LG_CLIENT_STREAM:--}" \
    "$OUT/client-client.txt" --hdr 0 --wait 2 > "$OUT/client-client.log" 2>&1 || true
  python3 -I "$ROOT/tools/verify/replay.py" connect "127.0.0.1:$INT_PORT" "${LG_INTERNAL_STREAM:--}" \
    "$OUT/client-internal.txt" --hdr 0 --wait 2 > "$OUT/client-internal.log" 2>&1 || true
fi
wait "$PID"; echo "$?" > "$OUT/exit.txt"
wait "$POLL_PID" 2>/dev/null
set -e
"$WINESERVER" -k 2>/dev/null || true
for p in "${PEER_PIDS[@]}"; do kill "$p" 2>/dev/null || true; wait "$p" 2>/dev/null || true; done

cat "$DRIVE_E"/log/$NAME/*.log 2>/dev/null | tr -d '\r' > "$OUT/log.txt" || : > "$OUT/log.txt"
cp "$OUT/log.txt" "$OUT/console.txt"
comm -13 "$OUT/ports_before.txt" "$OUT/ports_during.txt" | sed 's/.*://' | sort -n -u > "$OUT/ports.txt"
[ "$PEER" = 1 ] && sed -i -e "/^${LD_PORT}\$/d" "$OUT/ports.txt"   # replay.py port

mkdir -p "$OUT/pktlog"
cp "$DRIVE_D"/Logs/pktlog/* "$OUT/pktlog/" 2>/dev/null || true

echo "kind=$KIND exit=$(cat "$OUT/exit.txt") ports=$(tr '\n' ' ' < "$OUT/ports.txt")"
echo "log: $OUT/log.txt ($(wc -l < "$OUT/log.txt") lines)"
[ "$PEER" = 1 ] && echo "peer lobbyd: $(tr '\n' ' ' < "$OUT/peer-lobbyd.log")"
if [ "$CLIENT" = 1 ]; then
  echo "client client: $(tr '\n' ' ' < "$OUT/client-client.log")"
  echo "client internal: $(tr '\n' ' ' < "$OUT/client-internal.log")"
fi
exit 0
