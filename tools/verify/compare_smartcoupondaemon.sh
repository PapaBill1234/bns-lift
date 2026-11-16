#!/usr/bin/env bash
# Run the original and the lifted SmartCouponDaemon with the same config and the same input, then compare:
#   1. daemon log (time stamps, pointers, thread ids, local ports removed; any order)
#   2. listen ports (polled every 0.1 s)
#   3. bytes that the exe sends to the NP peer and to the GameDaemon peer (replay.py listen)
#   4. bytes that the exe sends to clients on the manage and daemon ports (replay.py connect)
#   5. packet logs (pkldump.py), only with --pktlog
# Usage: tools/verify/compare_smartcoupondaemon.sh [SECONDS] [--pktlog]
# Env: see run_smartcoupondaemon.sh (SCD_*_STREAM, SCD_CERT, SCD_CLIENT_AT, SCD_LIFTED_EXE).
#      Self test: SCD_LIFTED_EXE=<original exe> tools/verify/compare_smartcoupondaemon.sh 15 --pktlog
# Output: build/verify/scd-compare/*.diff. Exit 0 = no difference. Exit 3 = no lifted exe.
set -uo pipefail
cd "$(dirname "$0")/../.."
SECS="${1:-15}"
EXTRA=(--peer --client)
for a in "$@"; do [ "$a" = "--pktlog" ] && EXTRA+=(--pktlog); done
B="${LIFT_BUILD_DIR:-build}"
CODEX="${CODEX_DIR:-$(cd ../.. && pwd)}"
PKT="${SCD_PKTLOG:-$CODEX/bns-wine/pktlog}"
CMP="$B/verify/scd-compare"
RUNNER=tools/verify/run_smartcoupondaemon.sh

# Stop early if there is no lifted exe (do not spend a run on the original).
LIFTED="${SCD_LIFTED_EXE:-$B/SmartCouponDaemon.exe}"
[ -f "$LIFTED" ] || { echo "missing lifted exe: $LIFTED (CMake target SmartCouponDaemon)" >&2; exit 3; }

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
    -e 's/(worker run, id:)[0-9]+\([0-9]+\)/\1<N>/' \
    -e 's/(event object handle failed, id: )[0-9]+/\1<N>/' \
    -e 's/(loading time: )[0-9]+/\1<N>/' \
    -e 's/(ip:127\.0\.0\.1, port:)[0-9]{5}(, socket:)/\1<PORT>\2/' \
    "$1"
}
# replay.py lines are "<ms> <len> <id> <hex>": drop the time. In the STS Connect body, Epoch
# (tick count) and Process (pid) change from run to run: <Epoch>, <Process>.
nots() {
  [ -f "$1" ] || { echo "no file (no connect or no data)"; return; }
  cut -d' ' -f2- "$1" | python3 -I -c '
import sys, re
for l in sys.stdin:
    p = l.split()
    if len(p) == 3:
        b = bytes.fromhex(p[2])
        b = re.sub(rb"<(Epoch|Process)>[0-9]+<", rb"<\1>N<", b)
        p[2] = b.hex()
    print(" ".join(p))'
}

RC=0
for k in original lifted; do
  norm "$B/verify/scd-$k/log.txt" > "$CMP/log.$k.txt"
  for f in peer-np peer-gamed client-manager client-daemon; do
    nots "$B/verify/scd-$k/$f.txt" > "$CMP/$f.$k.txt"
  done
done
# Threads change the line order from run to run: the diff ignores the order (log.*.txt keep it).
# Race in the original: the NP I/O thread writes "np channel connected" and "[np-session-handler],
# connected" only in some runs, because onStart fails (no DB) at the same time. The log diff ignores
# these 2 lines. pkl.diff and peer-np.diff still check the NP traffic.
RACE='np channel connected|\[np-session-handler\], connected'
diff -u <(grep -vE "$RACE" "$CMP/log.original.txt" | sort) <(grep -vE "$RACE" "$CMP/log.lifted.txt" | sort) \
  > "$CMP/log.diff" || RC=1
diff -u "$B/verify/scd-original/ports.txt" "$B/verify/scd-lifted/ports.txt" > "$CMP/ports.diff" || RC=1
for f in peer-np peer-gamed client-manager client-daemon; do
  diff -u "$CMP/$f.original.txt" "$CMP/$f.lifted.txt" > "$CMP/$f.diff" || RC=1
done

if [[ " ${EXTRA[*]} " == *" --pktlog "* ]]; then
  for k in original lifted; do
    P="$B/verify/scd-$k/pktlog"
    if ls "$P"/*.pkl >/dev/null 2>&1; then
      python3 -I "$PKT/pkldump.py" "$P"/*.pkl --summary --bytes 0 > "$CMP/pkl-summary.$k.txt" 2>&1
      # Packet, STS and socket records without time, local (ephemeral) ports, pids, Epoch and Process.
      python3 -I "$PKT/pkldump.py" "$P"/*.pkl --bytes -1 --no-fold --kind pkt,sts,raw,sock 2>&1 \
        | sed -E -e 's/^[0-9:.]+ +//' -e 's/:(327[6-9][0-9]|32[89][0-9]{2}|3[3-9][0-9]{3}|[4-6][0-9]{4})\b/:<PORT>/g' \
                 -e 's/SmartCouponDaemon:[0-9]+/SmartCouponDaemon:<PID>/g' \
                 -e 's/<(Epoch|Process)>[0-9]+</<\1>N</g' \
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
echo "original ports: $(tr '\n' ' ' < "$B/verify/scd-original/ports.txt")"
echo "lifted ports:   $(tr '\n' ' ' < "$B/verify/scd-lifted/ports.txt")"
exit $RC
