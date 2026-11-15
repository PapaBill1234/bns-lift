#!/usr/bin/env bash
# Run the original and the lifted CacheGate with the same config and compare:
#   1. startup console output (time stamps, pids and addresses removed)
#   2. listen ports
#   3. packet logs (pkldump.py --summary and the packet list), only with --pktlog
# Usage: tools/verify/compare_cachegate.sh [SECONDS] [--pktlog]
# Output: build/verify/compare/*.diff. Exit 0 = no difference.
set -uo pipefail
cd "$(dirname "$0")/../.."
SECS="${1:-20}"
EXTRA=()
for a in "$@"; do [ "$a" = "--pktlog" ] && EXTRA+=(--pktlog); done
B="${LIFT_BUILD_DIR:-build}"
CODEX="${CODEX_DIR:-$(cd ../.. && pwd)}"
PKT="${CG_PKTLOG:-$CODEX/bns-wine/pktlog}"
CMP="$B/verify/compare"

tools/verify/run_cachegate.sh original "$SECS" "${EXTRA[@]}" || exit $?
tools/verify/run_cachegate.sh lifted   "$SECS" "${EXTRA[@]}" || exit $?
mkdir -p "$CMP"

# Remove values that change from run to run.
norm() {
  sed -E \
    -e 's/[0-9]{4}[-/.][0-9]{2}[-/.][0-9]{2}[ T][0-9:.]+/<TIME>/g' \
    -e 's/[0-9]{2}:[0-9]{2}:[0-9]{2}([.:][0-9]+)?/<TIME>/g' \
    -e 's/0x[0-9A-Fa-f]{6,16}/<ADDR>/g' \
    -e 's/(pid|PID|tid|TID)[=: ]*[0-9]+/\1=<N>/g' \
    "$1"
}
norm "$B/verify/original/console.txt" > "$CMP/console.original.txt"
norm "$B/verify/lifted/console.txt"   > "$CMP/console.lifted.txt"

RC=0
diff -u "$CMP/console.original.txt" "$CMP/console.lifted.txt" > "$CMP/console.diff" || RC=1
diff -u "$B/verify/original/ports.txt" "$B/verify/lifted/ports.txt" > "$CMP/ports.diff" || RC=1

if [ "${#EXTRA[@]}" -gt 0 ]; then
  for k in original lifted; do
    P="$B/verify/$k/pktlog"
    if ls "$P"/*.pkl >/dev/null 2>&1; then
      python3 -I "$PKT/pkldump.py" "$P" --summary --bytes 0 > "$CMP/pkl-summary.$k.txt" 2>&1
      # Packet list without time, peer port and pid: kind, dir, name(id), size.
      python3 -I "$PKT/pkldump.py" "$P" --bytes -1 --no-fold --kind pkt,crypt,sock 2>&1 \
        | sed -E -e 's/^[^ ]+ +//' -e 's/:[0-9]{4,5}\b/:<PORT>/g' > "$CMP/pkl.$k.txt"
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
