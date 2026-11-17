#!/usr/bin/env bash
# Run one PostOfficeDaemon exe under wine64 for a fixed time. Save the daemon log, the listen ports,
# (with --peer) the bytes that the exe sends to the CacheGate peer, (with --client) the bytes that the
# exe sends to the agent, world and manage clients, and (with --pktlog) the pktlog records.
#
# Usage: tools/verify/run_postofficedaemon.sh lifted|original [SECONDS] [--pktlog] [--peer] [--client]
#   lifted   = build/PostOfficeDaemon.exe (CMake target PostOfficeDaemon)
#   original = Service_348_8349/Service/PostOfficeDaemon/bin/PostOfficeDaemon.exe
#              (the exe of the IDA copy; not PostOfficeDaemon2019.exe)
#   --pktlog = patch the copy with patch_import.py (pktlog.dll writes D:\Logs\pktlog\*.pkl)
#   --peer   = set cachegate-ip-address and the gamed ip-address to 127.0.0.1, and run replay.py
#              as the CacheGate peer (cachegate_listen-port). Records what the exe sends.
#   --client = near the end, connect to agent-listen-port, world-listen-port and manage-port as a
#              client, send POD_AGENT_STREAM / POD_WORLD_STREAM / POD_MANAGE_STREAM, record the replies
# Env: POD_SRC_SVC  service folder of the original (default: see below)
#      POD_ARGS     extra arguments for the exe (default: none)
#      POD_PKTLOG   folder with pktlog.dll and patch_import.py (default: bns-wine/pktlog)
#      POD_CACHEGATE_STREAM  bytes that the CacheGate peer sends (default "-" = nothing)
#      POD_AGENT_STREAM, POD_WORLD_STREAM, POD_MANAGE_STREAM  bytes that the clients send (default "-")
#      POD_CLIENT_AT  seconds after start for the --client connects (default SECONDS-8)
#      POD_DISPLAY  X display for the console window (default :77, a hidden Xvfb)
#      POD_LIFTED_EXE exe for "lifted" (default: build/PostOfficeDaemon.exe; self test: the original)
#      POD_CERT     none | placeholder (default) | sql | <file>: E:\Service\cert\Postofficed.cfg
#                   sql = real PostOfficeDB in Docker bns-mssql; installs ODBC Driver 17 in the prefix
#      POD_ODBC_MSI ODBC driver installer for POD_CERT=sql (default: bns-wine/dl/msodbcsql17_x64.msi)
#      LIFT_BUILD_DIR build folder (default: build)
# Output: build/verify/pod-<kind>/ with log.txt, console.txt, ports.txt, exit.txt,
#         peer-cachegate.txt, client-agent.txt, client-world.txt, client-manage.txt, pktlog/*.pkl.
# Facts: see Docs/Verify/PostOfficeDaemon.md. The run setup is the same as run_smartcoupondaemon.sh
# (console window in wineconsole on Xvfb, E: and D: in the run folder, own Wine prefix).
set -euo pipefail
cd "$(dirname "$0")/../.."
ROOT="$PWD"

KIND="${1:?usage: run_postofficedaemon.sh lifted|original [SECONDS] [--pktlog] [--peer] [--client]}"
SECS="${2:-20}"
PKTLOG=0; PEER=0; CLIENT=0
for a in "$@"; do
  [ "$a" = "--pktlog" ] && PKTLOG=1
  [ "$a" = "--peer" ] && PEER=1
  [ "$a" = "--client" ] && CLIENT=1
done

B="${LIFT_BUILD_DIR:-build}"
CODEX="${CODEX_DIR:-$(cd ../.. && pwd)}"   # worktree is <Codex>/bns-wt/<slice>
SRC_SVC="${POD_SRC_SVC:-$CODEX/private-project/Service_348_8349/Service/PostOfficeDaemon}"
SRC_BIN="$SRC_SVC/bin"
SRC_CFG="$SRC_SVC/config"
PKT="${POD_PKTLOG:-$CODEX/bns-wine/pktlog}"
NAME=PostOfficeDaemon
XML=postofficed.config.xml

case "$KIND" in
  lifted)   EXE_SRC="${POD_LIFTED_EXE:-$B/$NAME.exe}" ;;
  original) EXE_SRC="$SRC_BIN/$NAME.exe" ;;
  *) echo "unknown kind: $KIND" >&2; exit 2 ;;
esac
if [ ! -f "$EXE_SRC" ]; then
  echo "missing exe: $EXE_SRC" >&2
  [ "$KIND" = lifted ] && echo "build it first: cmake --build $B --target $NAME" >&2
  exit 3
fi

OUT="$ROOT/$B/verify/pod-$KIND"
DRIVE_E="$OUT/drive_e"
DRIVE_D="$OUT/drive_d"
RUN="$DRIVE_E/Service/$NAME/bin"   # pktlog.dll takes the server name from <name>\bin\.
CFG="$DRIVE_E/Service/$NAME/config"
rm -rf "$OUT"
mkdir -p "$RUN" "$CFG" "$DRIVE_E/Service/cert" "$DRIVE_E/log/$NAME" "$DRIVE_D/Logs/pktlog"

# Exe, original config, DLLs and data. No .pdb, no 2019 exe.
cp "$EXE_SRC" "$RUN/$NAME.exe"
for f in "$SRC_BIN"/*.xml "$SRC_BIN"/*.dll "$SRC_BIN"/*.cfg; do [ -f "$f" ] && cp "$f" "$RUN/"; done
[ -e "$SRC_BIN/dict" ] && cp -r "$SRC_BIN/dict" "$RUN/"
for f in "$SRC_CFG"/*.xml; do [ -f "$f" ] && cp "$f" "$CFG/"; done
# PostOfficeDaemon::initialize (0x132b0) reads the cert file with fread (max 1000 B) and uses the
# text as the ODBC connection string (same as SmartCouponDaemon).
CERT="$DRIVE_E/Service/cert/Postofficed.cfg"
case "${POD_CERT:-placeholder}" in
  none) ;;
  placeholder) printf 'DSN=PostOfficeDB;UID=keyhere;PWD=keyhere;' > "$CERT" ;;
  # The script reads the sa password from the container env into the file. It never prints it.
  sql)
    docker exec bns-mssql true 2>/dev/null || { echo "start the container first: docker start bns-mssql" >&2; exit 4; }
    { printf 'Driver={ODBC Driver 17 for SQL Server};Server=127.0.0.1,14333;Database=PostOfficeDB;UID=sa;PWD='
      docker exec bns-mssql bash -c 'printf %s "${MSSQL_SA_PASSWORD:-$SA_PASSWORD}"'
      printf ';' ; } > "$CERT" ;;
  *) cp "$POD_CERT" "$CERT" ;;
esac

opt() { grep -oE "name='$1' value='[^']*'" "$RUN/$XML" | head -1 | sed -E "s/.*value='([^']*)'/\1/"; }
AGENT_PORT="$(opt agent-listen-port)"
WORLD_PORT="$(opt world-listen-port)"
MANAGE_PORT="$(opt manage-port)"
CG_PORT="$(opt cachegate_listen-port)"

if [ "$PEER" = 1 ]; then
  sed -i -E "s/(name='cachegate-ip-address' value=')[^']*'/\1127.0.0.1'/" "$RUN/$XML"
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
export DISPLAY="${POD_DISPLAY:-:77}"
if [ "$DISPLAY" = ":77" ] && [ ! -e /tmp/.X11-unix/X77 ]; then
  nohup Xvfb :77 -screen 0 1024x768x16 >/dev/null 2>&1 &
  sleep 1
fi
if [ ! -d "$WINEPREFIX/dosdevices" ]; then
  "$WINE" wineboot -i >/dev/null 2>&1 || true
  "$WINESERVER" -w || true
fi
if [ "${POD_CERT:-}" = sql ] && [ ! -f "$WINEPREFIX/drive_c/windows/system32/msodbcsql17.dll" ]; then
  MSI="${POD_ODBC_MSI:-$CODEX/bns-wine/dl/msodbcsql17_x64.msi}"
  "$WINE" msiexec /i "$MSI" /qn IACCEPTMSODBCSQLLICENSETERMS=YES >/dev/null 2>&1 || true
  "$WINESERVER" -w || true
  [ -f "$WINEPREFIX/drive_c/windows/system32/msodbcsql17.dll" ] || { echo "ODBC Driver 17 install failed: $MSI" >&2; exit 4; }
fi
"$WINESERVER" -k 2>/dev/null || true
ln -sfn "$DRIVE_D" "$WINEPREFIX/dosdevices/d:"
ln -sfn "$DRIVE_E" "$WINEPREFIX/dosdevices/e:"

ss -ltnH 2>/dev/null | awk '{print $4}' | sort -u > "$OUT/ports_before.txt" || true

PEER_PIDS=()
if [ "$PEER" = 1 ]; then
  python3 -I "$ROOT/tools/verify/replay.py" listen "$CG_PORT" "${POD_CACHEGATE_STREAM:--}" "$OUT/peer-cachegate.txt" \
    --hdr 0 --wait "$SECS" --accept-timeout "$SECS" > "$OUT/peer-cachegate.log" 2>&1 &
  PEER_PIDS+=($!)
fi

WEXE="E:\\Service\\$NAME\\bin\\$NAME.exe"
set +e
( cd "$RUN" && timeout -s INT -k 5 "$SECS" "$WINE" wineconsole "$WEXE" ${POD_ARGS:-} ) \
  > "$OUT/wine.txt" 2>&1 &
PID=$!
( while kill -0 "$PID" 2>/dev/null; do ss -ltnH 2>/dev/null | awk '{print $4}'; sleep 0.1; done ) \
  | sort -u > "$OUT/ports_during.txt" &
POLL_PID=$!
sleep "${POD_CLIENT_AT:-$(( SECS > 10 ? SECS - 8 : 2 ))}"
if [ "$CLIENT" = 1 ]; then
  for c in agent:$AGENT_PORT:${POD_AGENT_STREAM:--} world:$WORLD_PORT:${POD_WORLD_STREAM:--} \
           manage:$MANAGE_PORT:${POD_MANAGE_STREAM:--}; do
    IFS=: read -r cn cp cs <<< "$c"
    python3 -I "$ROOT/tools/verify/replay.py" connect "127.0.0.1:$cp" "$cs" \
      "$OUT/client-$cn.txt" --hdr 0 --wait 2 > "$OUT/client-$cn.log" 2>&1 || true
  done
fi
wait "$PID"; echo "$?" > "$OUT/exit.txt"
wait "$POLL_PID" 2>/dev/null
set -e
"$WINESERVER" -k 2>/dev/null || true
for p in "${PEER_PIDS[@]}"; do kill "$p" 2>/dev/null || true; wait "$p" 2>/dev/null || true; done

cat "$DRIVE_E"/log/$NAME/*.log 2>/dev/null | tr -d '\r' > "$OUT/log.txt" || : > "$OUT/log.txt"
[ -s "$OUT/log.txt" ] || find "$DRIVE_E/log" -type f -exec cat {} + 2>/dev/null | tr -d '\r' > "$OUT/log.txt" || true
cp "$OUT/log.txt" "$OUT/console.txt"
comm -13 "$OUT/ports_before.txt" "$OUT/ports_during.txt" | sed 's/.*://' | sort -n -u > "$OUT/ports.txt"
[ "$PEER" = 1 ] && sed -i -e "/^${CG_PORT}\$/d" "$OUT/ports.txt"   # replay.py port

mkdir -p "$OUT/pktlog"
cp "$DRIVE_D"/Logs/pktlog/* "$OUT/pktlog/" 2>/dev/null || true

echo "kind=$KIND exit=$(cat "$OUT/exit.txt") ports=$(tr '\n' ' ' < "$OUT/ports.txt")"
echo "log: $OUT/log.txt ($(wc -l < "$OUT/log.txt") lines)"
[ "$PEER" = 1 ] && echo "peer cachegate: $(tr '\n' ' ' < "$OUT/peer-cachegate.log")"
if [ "$CLIENT" = 1 ]; then
  for cn in agent world manage; do echo "client $cn: $(tr '\n' ' ' < "$OUT/client-$cn.log")"; done
fi
exit 0
