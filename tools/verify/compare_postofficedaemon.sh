#!/usr/bin/env bash
# Run the original and the lifted PostOfficeDaemon with the same config and the same input, then compare:
#   1. daemon log (time stamps, pointers, session pointers, local ports removed; any order)
#   2. listen ports (polled every 0.1 s)
#   3. bytes that the exe sends to the CacheGate peer (replay.py listen)
#   4. bytes that the exe sends to clients on the agent, world and manage ports (replay.py connect)
#   5. packet logs (pkldump.py), only with --pktlog
# Usage: tools/verify/compare_postofficedaemon.sh [SECONDS] [--pktlog]
# Env: see run_postofficedaemon.sh (POD_*_STREAM, POD_CERT, POD_CLIENT_AT, POD_LIFTED_EXE).
#      Self test: POD_LIFTED_EXE=<original exe> tools/verify/compare_postofficedaemon.sh 25 --pktlog
#      Fixed source: POD_LIFTED_EXE=build/verify/pod-fixsrc/src-copy/build/PostOfficeDaemon.exe
# Output: build/verify/pod-compare/*.diff. Exit 0 = no difference. Exit 3 = no lifted exe.
set -uo pipefail
cd "$(dirname "$0")/../.."
SECS="${1:-25}"
EXTRA=(--peer --client)
for a in "$@"; do [ "$a" = "--pktlog" ] && EXTRA+=(--pktlog); done
B="${LIFT_BUILD_DIR:-build}"
CODEX="${CODEX_DIR:-$(cd ../.. && pwd)}"
PKT="${POD_PKTLOG:-$CODEX/bns-wine/pktlog}"
CMP="$B/verify/pod-compare"
RUNNER=tools/verify/run_postofficedaemon.sh
FILES=(peer-cachegate client-agent client-world client-manage)

LIFTED="${POD_LIFTED_EXE:-$B/PostOfficeDaemon.exe}"
[ -f "$LIFTED" ] || { echo "missing lifted exe: $LIFTED (CMake target PostOfficeDaemon)" >&2; exit 3; }

bash "$RUNNER" original "$SECS" "${EXTRA[@]}" || exit $?
bash "$RUNNER" lifted   "$SECS" "${EXTRA[@]}" || exit $?
rm -rf "$CMP"; mkdir -p "$CMP"

# Remove values that change from run to run.
norm() {
  sed -E \
    -e 's/^[0-9]{4}\/[0-9]{2}\/[0-9]{2}-[0-9:.]+,/<TIME>,/' \
    -e 's/[0-9A-F]{16}/<PTR>/g' \
    -e 's/(session|this):[0-9a-fA-Fx]+/\1:<PTR>/g' \
    -e 's/addr:\(127\.0\.0\.1:[0-9]+\)/addr:(127.0.0.1:<N>)/' \
    -e 's/127\.0\.0\.1:[0-9]{5}/127.0.0.1:<PORT>/g' \
    -e 's/(hostname|public|internal): [^,]*/\1: <HOST>/g' \
    -e 's/(worker run, id:)[0-9]+\([0-9]+\)/\1<N>/' \
    -e 's/(event object handle failed, id: )[0-9]+/\1<N>/' \
    -e 's/(loading time: )[0-9]+/\1<N>/' \
    -e 's/(ip:127\.0\.0\.1, port:)[0-9]{5}(, socket:)/\1<PORT>\2/' \
    "$1"
}
# replay.py lines are "<ms> <len> <id> <hex>": drop the time.
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
  norm "$B/verify/pod-$k/log.txt" > "$CMP/log.$k.txt"
  for f in "${FILES[@]}"; do nots "$B/verify/pod-$k/$f.txt" > "$CMP/$f.$k.txt"; done
done
# Threads change the line order from run to run: the diff ignores the order (log.*.txt keep it).
diff -u <(sort "$CMP/log.original.txt") <(sort "$CMP/log.lifted.txt") > "$CMP/log.diff" || RC=1
diff -u "$B/verify/pod-original/ports.txt" "$B/verify/pod-lifted/ports.txt" > "$CMP/ports.diff" || RC=1
for f in "${FILES[@]}"; do
  diff -u "$CMP/$f.original.txt" "$CMP/$f.lifted.txt" > "$CMP/$f.diff" || RC=1
done

if [[ " ${EXTRA[*]} " == *" --pktlog "* ]]; then
  for k in original lifted; do
    P="$B/verify/pod-$k/pktlog"
    if ls "$P"/*.pkl >/dev/null 2>&1; then
      python3 -I "$PKT/pkldump.py" "$P"/*.pkl --summary --bytes 0 > "$CMP/pkl-summary.$k.txt" 2>&1
      python3 -I "$PKT/pkldump.py" "$P"/*.pkl --bytes -1 --no-fold --kind pkt,sts,raw,sock 2>&1 \
        | sed -E -e 's/^[0-9:.]+ +//' -e 's/:(327[6-9][0-9]|32[89][0-9]{2}|3[3-9][0-9]{3}|[4-6][0-9]{4})\b/:<PORT>/g' \
                 -e 's/PostOfficeDaemon:[0-9a-f]+/PostOfficeDaemon:<SOCK>/g' \
                 -e 's/listen=[0-9a-f]+/listen=<SOCK>/g' \
                 -e 's/<(Epoch|Process)>[0-9]+</<\1>N</g' \
        > "$CMP/pkl.$k.txt"
    else
      echo "no .pkl in $P" > "$CMP/pkl.$k.txt"
    fi
  done
  # The accept order of the 3 listen ports changes from run to run (self test): compare sorted lines.
  # The byte order of each stream is checked by peer-*.diff and client-*.diff.
  diff -u <(sort "$CMP/pkl.original.txt") <(sort "$CMP/pkl.lifted.txt") > "$CMP/pkl.diff" || RC=1
fi

for f in "$CMP"/*.diff; do
  n=$(grep -c '^[-+][^-+]' "$f" || true)
  echo "$(basename "$f"): $n changed lines"
done
echo "original ports: $(tr '\n' ' ' < "$B/verify/pod-original/ports.txt")"
echo "lifted ports:   $(tr '\n' ' ' < "$B/verify/pod-lifted/ports.txt")"
exit $RC
