#!/usr/bin/env bash
# Run one SmartCouponDaemon exe under wine64 for a fixed time. Save the daemon log, the console
# output, the listen ports, (with --peer) the bytes that the exe sends to its peers, and (with
# --pktlog) the pktlog records.
#
# Usage: tools/verify/run_smartcoupondaemon.sh lifted|original [SECONDS] [--pktlog] [--peer] [--client]
#   lifted   = build/SmartCouponDaemon.exe (CMake target SmartCouponDaemon)
#   original = Service_348_8349/Service/SmartCouponDaemon/bin/SmartCouponDaemon.exe
#              (the exe of the IDA copy; not SmartCouponDaemon2019.exe)
#   --pktlog = patch the copy with patch_import.py (pktlog.dll writes D:\Logs\pktlog\*.pkl)
#   --peer   = set np-address and the gamed ip-address to 127.0.0.1, and run replay.py as the
#              NP peer (np-port) and as the GameDaemon peer (internal-port). Records what the exe sends.
#   --client = near the end, connect to manage-listen-port and to daemon-listen-port as a client,
#              send SCD_MANAGER_STREAM / SCD_DAEMON_STREAM, record the replies
# Env: SCD_SRC_SVC  service folder of the original (default: see below)
#      SCD_ARGS     extra arguments for the exe (default: none)
#      SCD_PKTLOG   folder with pktlog.dll and patch_import.py (default: bns-wine/pktlog)
#      SCD_NP_STREAM, SCD_GAMED_STREAM     bytes that the peers send (default "-" = nothing)
#      SCD_MANAGER_STREAM, SCD_DAEMON_STREAM bytes that the clients send (default "-" = nothing)
#      SCD_CLIENT_AT  seconds after start for the --client connects (default SECONDS-6)
#      SCD_DISPLAY  X display for the console window (default :77, a hidden Xvfb)
#      SCD_LIFTED_EXE exe for "lifted" (default: build/SmartCouponDaemon.exe; self test: the original)
#      SCD_CERT     none | placeholder (default) | <file>: E:\Service\cert\smartcoupond.cfg (see below)
#      LIFT_BUILD_DIR build folder (default: build)
# Output: build/verify/scd-<kind>/ with log.txt, console.txt, ports.txt, exit.txt,
#         peer-np.txt, peer-gamed.txt, client-manager.txt, client-daemon.txt, pktlog/*.pkl.
#
# Facts (found 2026-11-16 with the original exe): see Docs/Verify/SmartCouponDaemon.md.
# - The exe must have a console window (same as CacheGate). The script runs it in wineconsole on a
#   hidden Xvfb display, with the full Windows path of the exe.
# - The config uses E:\Service\SmartCouponDaemon\{bin,config}, E:\log\SmartCouponDaemon and
#   E:\Service\cert\smartcoupond.cfg. E: points to the run folder.
# - The script uses its own Wine prefix (build/verify/wineprefix). It does not change your prefix.
set -euo pipefail
cd "$(dirname "$0")/../.."
ROOT="$PWD"

KIND="${1:?usage: run_smartcoupondaemon.sh lifted|original [SECONDS] [--pktlog] [--peer] [--client]}"
SECS="${2:-20}"
PKTLOG=0; PEER=0; CLIENT=0
for a in "$@"; do
  [ "$a" = "--pktlog" ] && PKTLOG=1
  [ "$a" = "--peer" ] && PEER=1
  [ "$a" = "--client" ] && CLIENT=1
done

B="${LIFT_BUILD_DIR:-build}"
CODEX="${CODEX_DIR:-$(cd ../.. && pwd)}"   # worktree is <Codex>/bns-wt/<slice>
SRC_SVC="${SCD_SRC_SVC:-$CODEX/private-project/Service_348_8349/Service/SmartCouponDaemon}"
SRC_BIN="$SRC_SVC/bin"
SRC_CFG="$SRC_SVC/config"
PKT="${SCD_PKTLOG:-$CODEX/bns-wine/pktlog}"
NAME=SmartCouponDaemon

case "$KIND" in
  lifted)   EXE_SRC="${SCD_LIFTED_EXE:-$B/$NAME.exe}" ;;
  original) EXE_SRC="$SRC_BIN/$NAME.exe" ;;
  *) echo "unknown kind: $KIND" >&2; exit 2 ;;
esac
if [ ! -f "$EXE_SRC" ]; then
  echo "missing exe: $EXE_SRC" >&2
  [ "$KIND" = lifted ] && echo "build it first: cmake --build $B --target $NAME" >&2
  exit 3
fi

OUT="$ROOT/$B/verify/scd-$KIND"
DRIVE_E="$OUT/drive_e"
DRIVE_D="$OUT/drive_d"
RUN="$DRIVE_E/Service/$NAME/bin"   # pktlog.dll takes the server name from <name>\bin\.
CFG="$DRIVE_E/Service/$NAME/config"
rm -rf "$OUT"
mkdir -p "$RUN" "$CFG" "$DRIVE_E/Service/cert" "$DRIVE_E/log/$NAME" "$DRIVE_D/Logs/pktlog"

# Exe, original config, DLLs and data. No .pdb, no .7z, no 2019 exe.
cp "$EXE_SRC" "$RUN/$NAME.exe"
for f in "$SRC_BIN"/*.xml "$SRC_BIN"/*.dll "$SRC_BIN"/*.cfg; do [ -f "$f" ] && cp "$f" "$RUN/"; done
[ -e "$SRC_BIN/dict" ] && cp -r "$SRC_BIN/dict" "$RUN/"
for f in "$SRC_CFG"/*.xml; do [ -f "$f" ] && cp "$f" "$CFG/"; done
# The cert file holds the plain ODBC connection string (initialize reads it with fread, max 1000 B).
# Default "placeholder": a fake DSN with no secret, so that the exe gets past the cert check
# (error 3) and stops at the DB step. "none" = no file. Else: the path of a file to copy.
case "${SCD_CERT:-placeholder}" in
  none) ;;
  placeholder) printf 'DSN=SmartCouponDB;UID=keyhere;PWD=keyhere;' > "$DRIVE_E/Service/cert/smartcoupond.cfg" ;;
  *) cp "$SCD_CERT" "$DRIVE_E/Service/cert/smartcoupond.cfg" ;;
esac

opt() { grep -oE "name='$1' value='[^']*'" "$RUN/smartcoupond.config.xml" | head -1 | sed -E "s/.*value='([^']*)'/\1/"; }
MAN_PORT="$(opt manage-listen-port)"
DMN_PORT="$(opt daemon-listen-port)"
NP_PORT="$(opt np-port)"
GAMED_PORT="$(grep -oE "^[[:space:]]*<gamed [^>]*internal-port='[0-9]+'" "$CFG/gamed-list.config.xml" | head -1 | grep -oE "internal-port='[0-9]+'" | grep -oE '[0-9]+')"

if [ "$PEER" = 1 ]; then
  sed -i -E "s/(name='np-address' value=')[^']*'/\1127.0.0.1'/" "$RUN/smartcoupond.config.xml"
  sed -i -E "s/ip-address='[^']*'/ip-address='127.0.0.1'/" "$CFG/gamed-list.config.xml"
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
export DISPLAY="${SCD_DISPLAY:-:77}"
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
  python3 -I "$ROOT/tools/verify/replay.py" listen "$NP_PORT" "${SCD_NP_STREAM:--}" "$OUT/peer-np.txt" \
    --hdr 0 --wait "$SECS" --accept-timeout "$SECS" > "$OUT/peer-np.log" 2>&1 &
  PEER_PIDS+=($!)
  python3 -I "$ROOT/tools/verify/replay.py" listen "$GAMED_PORT" "${SCD_GAMED_STREAM:--}" "$OUT/peer-gamed.txt" \
    --hdr 0 --wait "$SECS" --accept-timeout "$SECS" > "$OUT/peer-gamed.log" 2>&1 &
  PEER_PIDS+=($!)
fi

# wineconsole writes the console text into its window, not to stdout. wine.txt keeps what Wine
# itself writes. The daemon log file has the same lines as the console.
WEXE="E:\\Service\\$NAME\\bin\\$NAME.exe"
set +e
( cd "$RUN" && timeout -s INT -k 5 "$SECS" "$WINE" wineconsole "$WEXE" ${SCD_ARGS:-} ) \
  > "$OUT/wine.txt" 2>&1 &
PID=$!
# The original opens its listen ports for about 0.1 s only when onStart fails (no DB). So poll
# the ports every 0.1 s for the full run, not once.
( while kill -0 "$PID" 2>/dev/null; do ss -ltnH 2>/dev/null | awk '{print $4}'; sleep 0.1; done ) \
  | sort -u > "$OUT/ports_during.txt" &
POLL_PID=$!
sleep "${SCD_CLIENT_AT:-$(( SECS > 8 ? SECS - 6 : 2 ))}"
if [ "$CLIENT" = 1 ]; then
  python3 -I "$ROOT/tools/verify/replay.py" connect "127.0.0.1:$MAN_PORT" "${SCD_MANAGER_STREAM:--}" \
    "$OUT/client-manager.txt" --hdr 0 --wait 2 > "$OUT/client-manager.log" 2>&1 || true
  python3 -I "$ROOT/tools/verify/replay.py" connect "127.0.0.1:$DMN_PORT" "${SCD_DAEMON_STREAM:--}" \
    "$OUT/client-daemon.txt" --hdr 0 --wait 2 > "$OUT/client-daemon.log" 2>&1 || true
fi
wait "$PID"; echo "$?" > "$OUT/exit.txt"
wait "$POLL_PID" 2>/dev/null
set -e
"$WINESERVER" -k 2>/dev/null || true
for p in "${PEER_PIDS[@]}"; do kill "$p" 2>/dev/null || true; wait "$p" 2>/dev/null || true; done

cat "$DRIVE_E"/log/$NAME/*.log 2>/dev/null | tr -d '\r' > "$OUT/log.txt" || : > "$OUT/log.txt"
# Console copy: pktlog CONSOLE lines if there are any, else the log file.
cp "$OUT/log.txt" "$OUT/console.txt"
comm -13 "$OUT/ports_before.txt" "$OUT/ports_during.txt" | sed 's/.*://' | sort -n -u > "$OUT/ports.txt"
if [ "$PEER" = 1 ]; then
  sed -i -e "/^${NP_PORT}\$/d" -e "/^${GAMED_PORT}\$/d" "$OUT/ports.txt"   # replay.py ports
fi

mkdir -p "$OUT/pktlog"
cp "$DRIVE_D"/Logs/pktlog/* "$OUT/pktlog/" 2>/dev/null || true

echo "kind=$KIND exit=$(cat "$OUT/exit.txt") ports=$(tr '\n' ' ' < "$OUT/ports.txt")"
echo "log: $OUT/log.txt ($(wc -l < "$OUT/log.txt") lines)"
if [ "$PEER" = 1 ]; then
  echo "peer np: $(tr '\n' ' ' < "$OUT/peer-np.log")"
  echo "peer gamed: $(tr '\n' ' ' < "$OUT/peer-gamed.log")"
fi
if [ "$CLIENT" = 1 ]; then
  echo "client manager: $(tr '\n' ' ' < "$OUT/client-manager.log")"
  echo "client daemon: $(tr '\n' ' ' < "$OUT/client-daemon.log")"
fi
exit 0
