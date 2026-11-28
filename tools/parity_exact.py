#!/usr/bin/env python3
"""MATCH-B (exact) for the parity totals.

funcdiff MATCH is the progress signal: equal calls, data refs and constant set. It does not see register,
order or branch-sense changes. MATCH-B is a MATCH function whose code is also equal to the original as an
ordered instruction stream: the "full" level of the parity engine strict compare (registers, immediates and
memory forms stay; relocation targets become names; a branch inside the function becomes an instruction
distance). There is only one definition of MATCH-B: the strict "full" level. This file only reads it.

Baseline state. When the runner gives a strict directory (env PARITY_STRICT, one <EXE>.json per exe from the
same build), tools/parity.sh --accept writes "exact": true or false into each MATCH row of
Docs/Parity/baseline/<EXE>.json. A row without "exact" is not measured. progress.tsv gets " exact N" in the cell
of the exe, and the README table gets the column Exact. When one counted MATCH row of an exe has no "exact",
the exe has no exact count.

The gate does not change. The parity engine refuses a card that makes a baseline MATCH lose a strict level
(proof rule R4). It gives automatic credit only with strict full and cfg; other new MATCH go to review.

Usage (manual): tools/parity_exact.py                MATCH and MATCH-B per exe from the committed baselines
                tools/parity_exact.py --mark DIR     write "exact" into the committed baselines from strict DIR
                                                     (DIR must be the strict output of the build of these baselines)"""
import json
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import parity_excluded as px  # noqa: E402

EXES = ["CacheGate", "LobbyGate", "SmartCouponDaemon", "PostOfficeDaemon", "LobbyDaemon", "GameDaemon"]
MIN_OVERLAP = 0.99   # share of baseline rows that must have a strict row; less = strict data of another build


def load_strict(d, exe):
    """{funcdiff key: strict row} from <d>/<exe>.json, or None when d is empty or the file is missing."""
    if not d:
        return None
    p = os.path.join(d, exe + ".json")
    if not os.path.isfile(p):
        return None
    with open(p, encoding="utf-8") as f:
        s = json.load(f)
    rows = s.get("rows", s) if isinstance(s, dict) else None
    if not isinstance(rows, dict):
        raise ValueError(f"{p}: not a strict result (no row map)")
    return rows


def mark(rows, strict):
    """Set "exact" on each MATCH row from the strict full level. Remove it from all other rows.
    Raise ValueError when the strict rows do not cover the baseline (strict data of another build)."""
    hit = sum(1 for k in rows if k in strict)
    if rows and hit < MIN_OVERLAP * len(rows):
        raise ValueError(f"strict data covers {hit} of {len(rows)} rows; it is not from this build")
    for k, r in rows.items():
        s = strict.get(k)
        if r.get("status") == "MATCH" and isinstance(s, dict) and "full" in s:
            r["exact"] = bool(s["full"])
        else:
            r.pop("exact", None)
    return rows


def count(rows, excl):
    """MATCH-B count of one exe: counted MATCH rows (no excluded symbol) with exact true.
    None when one counted MATCH row has no "exact" (not measured)."""
    n = 0
    for k, r in rows.items():
        if not px.is_match(k, r, excl):
            continue
        if "exact" not in r:
            return None
        n += r["exact"] is True
    return n


def baseline(exe):
    return f"Docs/Parity/baseline/{exe}.json"


def report():
    excl = px.load()
    print("| Exe | MATCH | MATCH-B (exact) | Exact share | MATCH, not exact |")
    print("| --- | ---: | ---: | ---: | ---: |")
    for e in EXES:
        if not os.path.exists(baseline(e)):
            continue
        rows = json.load(open(baseline(e), encoding="utf-8"))
        m = px.count(rows, excl.get(e, {}))[0]
        n = count(rows, excl.get(e, {}))
        if n is None:
            print(f"| {e} | {m} | not measured | | |")
        else:
            print(f"| {e} | {m} | {n} | {100 * n / max(m, 1):.1f} % | {m - n} |")


def mark_committed(d):
    for e in EXES:
        strict = load_strict(d, e)
        if strict is None or not os.path.exists(baseline(e)):
            print(f"{e}: no strict data or no baseline; skipped")
            continue
        rows = mark(json.load(open(baseline(e), encoding="utf-8")), strict)
        with open(baseline(e), "w") as f:
            json.dump(rows, f, indent=0, sort_keys=True)
        print(f"{e}: marked")


def main(argv):
    os.chdir(os.path.join(os.path.dirname(os.path.abspath(__file__)), ".."))
    if argv[:1] == ["--mark"] and len(argv) == 2:
        mark_committed(argv[1])
    elif argv:
        print(__doc__)
        return 2
    report()
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
