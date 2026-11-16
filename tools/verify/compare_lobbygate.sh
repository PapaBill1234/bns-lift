#!/usr/bin/env bash
# Run the original and the lifted LobbyGate with the same config and the same input, then compare:
#   1. log (time stamps, pointers, local ports removed; any order)
#   2. listen ports (polled every 0.1 s)
#   3. bytes that the exe sends to the LobbyDaemon peer (replay.py listen)
#   4. bytes that the exe sends to clients on client-port and internal-port (replay.py connect)
#   5. packet logs (pkldump.py), only with --pktlog
# Usage: tools/verify/compare_lobbygate.sh [SECONDS] [--pktlog]
# Env: see run_lobbygate.sh (LG_*_STREAM, LG_CERT, LG_CLIENT_AT, LG_LIFTED_EXE).
#      LG_LOBBYD_STREAM default: build/verify/lg-lobbyd.bin (LobbyDaemon cmd 2 + cmd 4 from the 381
#      capture, made with pkl_stream.py if it is missing). Set it to "-" for no reply.
#      Self test: LG_LIFTED_EXE=<original exe> tools/verify/compare_lobbygate.sh 20 --pktlog
# Output: build/verify/lg-compare/*.diff. Exit 0 = no difference. Exit 3 = no lifted exe.
set -uo pipefail
cd "$(dirname "$0")/../.."
SECS="${1:-20}"
EXTRA=(--peer --client)
for a in "$@"; do [ "$a" = "--pktlog" ] && EXTRA+=(--pktlog); done
B="${LIFT_BUILD_DIR:-build}"
CODEX="${CODEX_DIR:-$(cd ../.. && pwd)}"
PKT="${LG_PKTLOG:-$CODEX/bns-wine/pktlog}"
CMP="$B/verify/lg-compare"
RUNNER=tools/verify/run_lobbygate.sh

LIFTED="${LG_LIFTED_EXE:-$B/LobbyGate.exe}"
[ -f "$LIFTED" ] || { echo "missing lifted exe: $LIFTED (CMake target LobbyGate)" >&2; exit 3; }

if [ -z "${LG_LOBBYD_STREAM:-}" ]; then
  LG_LOBBYD_STREAM="$PWD/$B/verify/lg-lobbyd.bin"
  if [ ! -f "$LG_LOBBYD_STREAM" ]; then
    CAP="${LG_LOBBYD_PKL:-$CODEX/bns-wine/Logs/pktlog/LobbyGate-2272-20261112-234739.pkl}"
    python3 -I tools/verify/pkl_stream.py "$CAP" 21801 "$LG_LOBBYD_STREAM" --count 2 || exit $?
  fi
fi
export LG_LOBBYD_STREAM

bash "$RUNNER" original "$SECS" "${EXTRA[@]}" || exit $?
bash "$RUNNER" lifted   "$SECS" "${EXTRA[@]}" || exit $?
rm -rf "$CMP"; mkdir -p "$CMP"

# Remove values that change from run to run.
norm() {
  sed -E \
    -e 's/^[0-9]{4}\/[0-9]{2}\/[0-9]{2}-[0-9:.]+,/<TIME>,/' \
    -e 's/[0-9A-F]{16}/<PTR>/g' \
    -e 's/addr:\(127\.0\.0\.1:[0-9]+\)/addr:(127.0.0.1:<N>)/' \
    -e 's/(hostname|public|internal): [^,]*/\1: <HOST>/g' \
    -e 's/(ip:127\.0\.0\.1, port:)[0-9]{5}(, socket:)/\1<PORT>\2/' \
    -e 's/(event object handle failed, id: )[0-9]+/\1<N>/' \
    -e 's/(loading time: )[0-9]+/\1<N>/' \
    "$1"
}
# replay.py lines are "<ms> <len> <id> <hex>": drop the time.
nots() {
  [ -f "$1" ] || { echo "no file (no connect or no data)"; return; }
  cut -d' ' -f2- "$1"
}

RC=0
FILES="peer-lobbyd client-client client-internal"
for k in original lifted; do
  norm "$B/verify/lg-$k/log.txt" > "$CMP/log.$k.txt"
  for f in $FILES; do nots "$B/verify/lg-$k/$f.txt" > "$CMP/$f.$k.txt"; done
done
diff -u <(sort "$CMP/log.original.txt") <(sort "$CMP/log.lifted.txt") > "$CMP/log.diff" || RC=1
diff -u "$B/verify/lg-original/ports.txt" "$B/verify/lg-lifted/ports.txt" > "$CMP/ports.diff" || RC=1
for f in $FILES; do
  diff -u "$CMP/$f.original.txt" "$CMP/$f.lifted.txt" > "$CMP/$f.diff" || RC=1
done

if [[ " ${EXTRA[*]} " == *" --pktlog "* ]]; then
  for k in original lifted; do
    P="$B/verify/lg-$k/pktlog"
    if ls "$P"/*.pkl >/dev/null 2>&1; then
      python3 -I "$PKT/pkldump.py" "$P"/*.pkl --summary --bytes 0 > "$CMP/pkl-summary.$k.txt" 2>&1
      python3 -I "$PKT/pkldump.py" "$P"/*.pkl --bytes -1 --no-fold --kind pkt,sts,raw,sock 2>&1 \
        | sed -E -e 's/^[0-9:.]+ +//' -e 's/:(327[6-9][0-9]|32[89][0-9]{2}|3[3-9][0-9]{3}|[4-6][0-9]{4})\b/:<PORT>/g' \
                 -e 's/LobbyGate:[0-9a-fA-F]+/LobbyGate:<PID>/g' -e 's/listen=[0-9a-fA-F]+/listen=<SOCK>/' \
        > "$CMP/pkl.$k.txt"
    else
      echo "no .pkl in $P" > "$CMP/pkl.$k.txt"
    fi
  done
  diff -u "$CMP/pkl.original.txt" "$CMP/pkl.lifted.txt" > "$CMP/pkl.diff" || RC=1
fi

for f in "$CMP"/*.diff; do
  n=$(grep -c '^[-+][^-+]' "$f" || true)
  echo "$(basename "$f"): $n changed lines"
done
echo "original ports: $(tr '\n' ' ' < "$B/verify/lg-original/ports.txt")"
echo "lifted ports:   $(tr '\n' ' ' < "$B/verify/lg-lifted/ports.txt")"
exit $RC
