#!/usr/bin/env bash
# Parity gate for the lift-parity cards.
# 1. Build the 5 exes with VS2010 /GL /LTCG (tools/vs2010/build.sh). Needs build/ from tools/gate.sh.
# 2. Compare each exe with the original (tools/funcdiff.py).
# 3. Compare the result with Docs/Parity/baseline/<EXE>.json.
# Fail when the MATCH count of an exe goes down, or a MATCH function becomes DIFF.
# A MATCH -> DIFF change is allowed only if Docs/Parity/allow-worse.txt has "<EXE> <function> | <reason>".
# Usage: tools/parity.sh [--update|--accept] [EXE...]
#   --update: build, compare, then write the new results as the baseline.
#   --accept: no build. Copy the results of the last run to the baseline (the runner does this after a pass).
# Cards never change Docs/Parity/baseline/. The runner checks against the committed baseline and then accepts.
# Parity % = MATCH / (paired + only in original). The goal is 90 %.
# Excluded symbols (Docs/Parity/excluded.tsv, tools/parity_excluded.py) never count as MATCH. --accept and --update
# write them into the baseline with status EXCLUDED. The gate ignores them: an excluded symbol that turns DIFF is
# not a loss. progress.tsv and the README show MATCH without them and a separate excluded count.
set -euo pipefail
cd "$(dirname "$0")/.."
UPDATE=0
[ "${1:-}" = "--update" ] && { UPDATE=1; shift; }
ACCEPT=0
[ "${1:-}" = "--accept" ] && { ACCEPT=1; shift; }
EXES=("$@"); [ ${#EXES[@]} -gt 0 ] || EXES=(CacheGate LobbyGate SmartCouponDaemon PostOfficeDaemon LobbyDaemon)
O="${VS2010_OUT:-build-vs2010}"
# Copy one funcdiff result to the baseline. Excluded MATCH symbols get status EXCLUDED.
# With no excluded symbol for the exe, the file is a byte copy (same as before excluded.tsv).
write_baseline() {
  python3 - "$O/$1.funcdiff.json" "Docs/Parity/baseline/$1.json" "$1" <<'PY'
import json, shutil, sys
sys.path.insert(0, "tools")
import parity_excluded as px
src, dst, exe = sys.argv[1:]
sym = px.load().get(exe, {})
if not sym:
    shutil.copyfile(src, dst)
    sys.exit(0)
with open(dst, "w") as f:
    json.dump(px.mark(json.load(open(src)), sym), f, indent=0, sort_keys=True)
PY
}
if [ "$ACCEPT" = 1 ]; then
  python3 tools/parity_excluded.py >/dev/null || { python3 tools/parity_excluded.py; exit 1; }
  for e in "${EXES[@]}"; do write_baseline "$e"; done
  # One row per accepted card in Docs/Parity/progress.tsv: date, card, then MATCH/total per exe.
  # MATCH does not hold excluded symbols. A cell gets " excluded N" when N > 0.
  python3 - "$O" "${PARITY_CARD:-manual}" "${EXES[@]}" <<'PY'
import datetime, json, os, re, sys
sys.path.insert(0, "tools")
import parity_excluded as px
o, card, exes = sys.argv[1], sys.argv[2], sys.argv[3:]
f = "Docs/Parity/progress.tsv"
excl = px.load()
cells = []
for e in exes:
    new = json.load(open(f"{o}/{e}.funcdiff.json"))
    only = int(re.search(r"(\d+) only in original", open(f"{o}/{e}.funcdiff.txt").readline()).group(1))
    m, x, _ = px.count(new, excl.get(e, {}))
    t = len(new) + only
    cells.append(f"{e} {m}/{t} {100*m/max(t,1):.1f}%" + (f" excluded {x}" if x else ""))
new_file = not os.path.exists(f)
with open(f, "a") as fh:
    if new_file:
        fh.write("date\tcard\tparity (MATCH/total per exe)\n")
    fh.write(f"{datetime.date.today()}\t{card}\t" + "; ".join(cells) + "\n")
PY
  python3 tools/parity_readme.py || echo "README parity table not updated"
  echo "baseline accepted"; exit 0
fi
UV="$(command -v uv || echo "$HOME/.local/bin/uv")"
tools/vs2010/build.sh "${EXES[@]}" | tail -20
rc=0
for e in "${EXES[@]}"; do
  "$UV" run -q --no-project --with capstone --with pefile python tools/funcdiff.py "$e" --build "$O" \
      --json "$O/$e.funcdiff.json" --worst 0 > "$O/$e.funcdiff.txt"
  python3 - "$e" "$O/$e.funcdiff.json" "Docs/Parity/baseline/$e.json" "$O/$e.funcdiff.txt" <<'PY' || rc=1
import json, os, re, sys
sys.path.insert(0, "tools")
import parity_excluded as px
exe, new_f, base_f, txt = sys.argv[1:]
try:
    excl = px.load().get(exe, {})
except px.BadRow as exc:
    print(f"{exe}: excluded.tsv: {exc}")
    sys.exit(1)
new = json.load(open(new_f))
head = open(txt).read().splitlines()[0]
only = int(re.search(r"(\d+) only in original", head).group(1))
m, x, _ = px.count(new, excl)
total = len(new) + only
mean = sum(r["score"] for r in new.values()) / max(len(new), 1)
print(f"{exe}: MATCH {m}/{total} = {100*m/max(total,1):.1f} % parity, paired {len(new)}, only in original {only}, mean {mean:.1f}, excluded {x}")
if not os.path.exists(base_f):
    print(f"  no baseline {base_f}: run tools/parity.sh --update")
    sys.exit(0)
base = json.load(open(base_f))
bm, bx, _ = px.count(base, excl)
allow = set()
if os.path.exists("Docs/Parity/allow-worse.txt"):
    for line in open("Docs/Parity/allow-worse.txt"):
        p = line.split("|")[0].split(None, 1)
        if len(p) == 2 and p[0] == exe:
            allow.add(p[1].strip())
# Excluded symbols are not MATCH on either side: they are never lost, gone or gained.
lost = [k for k, r in base.items() if px.is_match(k, r, excl) and k in new and new[k]["status"] != "MATCH" and k not in allow]
gone = [k for k, r in base.items() if px.is_match(k, r, excl) and k not in new]
gained = [k for k, r in new.items() if px.is_match(k, r, excl) and not px.is_match(k, base.get(k, {}), excl)]
print(f"  baseline MATCH {bm} -> {m} ({m-bm:+d}); new MATCH {len(gained)}; MATCH -> DIFF {len(lost)}; MATCH name gone {len(gone)}; excluded {bx} -> {x}")
for k in lost:
    print(f"  LOST  {k}  {new[k]}")
for k in gone:
    print(f"  GONE  {k}")
sys.exit(1 if (m < bm or lost) else 0)
PY
  if [ "$UPDATE" = 1 ]; then write_baseline "$e"; fi
done
[ "$UPDATE" = 1 ] && echo "baseline updated" && exit 0
[ "$rc" = 0 ] && echo "parity ok" || echo "parity FAIL"
exit "$rc"
