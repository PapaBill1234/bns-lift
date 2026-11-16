#!/usr/bin/env bash
# Run the original and the lifted CacheGate with the same config and the same input, then compare:
#   1. daemon log (time stamps, pointers, socket handles, local ports and worker ids removed; any order)
#   2. listen ports
#   3. bytes that the exe sends to the CacheD peer (replay.py listen) and to the client (replay.py connect)
#   4. packet logs (pkldump.py), only with --pktlog
# Usage: tools/verify/compare_cachegate.sh [SECONDS] [--pktlog]
# Env: CG_PEER_STREAM, CG_CLIENT_STREAM (see run_cachegate.sh)
# Output: build/verify/compare/*.diff. Exit 0 = no difference. Exit 3 = no lifted exe.
set -uo pipefail
cd "$(dirname "$0")/../.."
SECS="${1:-20}"
EXTRA=(--peer --client)
for a in "$@"; do [ "$a" = "--pktlog" ] && EXTRA+=(--pktlog); done
B="${LIFT_BUILD_DIR:-build}"
CODEX="${CODEX_DIR:-$(cd ../.. && pwd)}"
PKT="${CG_PKTLOG:-$CODEX/bns-wine/pktlog}"
CMP="$B/verify/compare"

bash tools/verify/run_cachegate.sh original "$SECS" "${EXTRA[@]}" || exit $?
bash tools/verify/run_cachegate.sh lifted   "$SECS" "${EXTRA[@]}" || exit $?
rm -rf "$CMP"; mkdir -p "$CMP"

# Remove values that change from run to run.
norm() {
  sed -E \
    -e 's/^[0-9]{4}\/[0-9]{2}\/[0-9]{2}-[0-9:.]+,/<TIME>,/' \
    -e 's/[0-9A-F]{16}/<PTR>/g' \
    -e 's/(port|socket|loading time):[ ]?[0-9]+/\1:<N>/g' \
    -e 's/loading time: [0-9]+/loading time: <N>/' \
    -e 's/addr:\(127\.0\.0\.1:[0-9]+\)/addr:(127.0.0.1:<N>)/' \
    -e 's/(hostname|public|internal): [^,]*/\1: <HOST>/g' \
    -e 's/(\[worker\].*id: )[0-9]+/\1<N>/' \
    "$1"
}
# replay.py lines are "<ms> <len> <id> <hex>": drop the time.
nots() { [ -f "$1" ] && cut -d' ' -f2- "$1" || echo "no file $1"; }

RC=0
for k in original lifted; do
  norm "$B/verify/$k/log.txt" > "$CMP/log.$k.txt"
  nots "$B/verify/$k/peer.txt"   > "$CMP/peer.$k.txt"
  nots "$B/verify/$k/client.txt" > "$CMP/client.$k.txt"
done
# Threads change the line order from run to run: the diff ignores the order (log.*.txt keep it).
diff -u <(sort "$CMP/log.original.txt") <(sort "$CMP/log.lifted.txt") > "$CMP/log.diff" || RC=1
diff -u "$B/verify/original/ports.txt" "$B/verify/lifted/ports.txt" > "$CMP/ports.diff" || RC=1
diff -u "$CMP/peer.original.txt"   "$CMP/peer.lifted.txt"   > "$CMP/peer.diff"   || RC=1
diff -u "$CMP/client.original.txt" "$CMP/client.lifted.txt" > "$CMP/client.diff" || RC=1

if [[ " ${EXTRA[*]} " == *" --pktlog "* ]]; then
  for k in original lifted; do
    P="$B/verify/$k/pktlog"
    if ls "$P"/*.pkl >/dev/null 2>&1; then
      python3 -I "$PKT/pkldump.py" "$P"/*.pkl --summary --bytes 0 > "$CMP/pkl-summary.$k.txt" 2>&1
      # Packet and socket records without time, local ports and pids.
      python3 -I "$PKT/pkldump.py" "$P"/*.pkl --bytes -1 --no-fold --kind pkt,crypt,sock 2>&1 \
        | sed -E -e 's/^[0-9:.]+ +//' -e 's/:[0-9]{4,5}\b/:<PORT>/g' -e 's/CacheGate:[0-9]+/CacheGate:<PID>/g' \
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
echo "original ports: $(tr '\n' ' ' < "$B/verify/original/ports.txt")"
echo "lifted ports:   $(tr '\n' ' ' < "$B/verify/lifted/ports.txt")"
exit $RC
