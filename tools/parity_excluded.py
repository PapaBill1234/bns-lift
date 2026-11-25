#!/usr/bin/env python3
"""Excluded symbols for the parity totals (Docs/Parity/excluded.tsv).

An excluded symbol is a function that funcdiff calls MATCH, but that a review rejected and the operator excluded
(no honest source fix, for example an LTCG layout effect). It gets no credit. It is not a MATCH in any total.

excluded.tsv: one header line, then one row per symbol. Tab-separated columns:
  exe           exe name (CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon, LobbyDaemon)
  symbol        funcdiff key of the function
  reason        why there is no honest fix (10 characters or more)
  card          card that excluded it
  proof_digest  sha256 of the proof that the exclude receipt binds (64 hex characters)
Lines that start with '#' and empty lines are ignored.

Baseline state. tools/parity.sh --accept writes an excluded MATCH function into Docs/Parity/baseline/<EXE>.json
with status "EXCLUDED" (and "raw_status": "MATCH"). An old baseline (written before this file) can still hold
"MATCH" for an excluded symbol. count() reads both forms: a listed symbol is never counted as MATCH.

Usage (manual check): tools/parity_excluded.py [--check]   prints the rows per exe; exit 1 on a bad row."""
import json
import os
import re
import sys

PATH = "Docs/Parity/excluded.tsv"
COLUMNS = ["exe", "symbol", "reason", "card", "proof_digest"]
EXES = ["CacheGate", "LobbyGate", "SmartCouponDaemon", "PostOfficeDaemon", "LobbyDaemon"]
EXCLUDED = "EXCLUDED"
DIGEST = re.compile(r"^[0-9a-f]{64}$")


class BadRow(ValueError):
    pass


def load(path=PATH):
    """Return {exe: {symbol: row dict}}. A missing file gives {}. A bad row raises BadRow."""
    out = {}
    if not os.path.exists(path):
        return out
    with open(path, encoding="utf-8") as f:
        lines = f.read().splitlines()
    header_seen = False
    for n, line in enumerate(lines, 1):
        if not line.strip() or line.startswith("#"):
            continue
        cells = line.split("\t")
        if not header_seen:
            header_seen = True
            if cells != COLUMNS:
                raise BadRow(f"{path}:{n}: header must be {' '.join(COLUMNS)} (tab-separated)")
            continue
        if len(cells) != len(COLUMNS):
            raise BadRow(f"{path}:{n}: {len(cells)} columns, need {len(COLUMNS)}")
        row = dict(zip(COLUMNS, (c.strip() for c in cells)))
        if row["exe"] not in EXES:
            raise BadRow(f"{path}:{n}: unknown exe {row['exe']!r}")
        if not row["symbol"]:
            raise BadRow(f"{path}:{n}: empty symbol")
        if len(row["reason"]) < 10:
            raise BadRow(f"{path}:{n}: reason needs 10 characters or more")
        if not row["card"]:
            raise BadRow(f"{path}:{n}: empty card")
        if not DIGEST.match(row["proof_digest"]):
            raise BadRow(f"{path}:{n}: proof_digest must be 64 lowercase hex characters")
        if row["symbol"] in out.get(row["exe"], {}):
            raise BadRow(f"{path}:{n}: duplicate row for {row['exe']} {row['symbol']}")
        out.setdefault(row["exe"], {})[row["symbol"]] = row
    return out


def mark(results, symbols):
    """Return a copy of funcdiff results with each MATCH in `symbols` set to EXCLUDED. Other states stay."""
    out = {}
    for k, r in results.items():
        if k in symbols and r.get("status") in ("MATCH", EXCLUDED):
            r = dict(r, status=EXCLUDED, raw_status="MATCH")
        out[k] = r
    return out


def is_match(key, r, symbols):
    return r.get("status") == "MATCH" and key not in symbols


def count(results, symbols):
    """(match, excluded, other) for funcdiff results or a baseline (old or new form)."""
    m = x = 0
    for k, r in results.items():
        if r.get("status") == EXCLUDED or (r.get("status") == "MATCH" and k in symbols):
            x += 1
        elif r.get("status") == "MATCH":
            m += 1
    return m, x, len(results) - m - x


def main(argv):
    try:
        rows = load()
    except BadRow as exc:
        print(f"excluded.tsv: {exc}")
        return 1
    for e in EXES:
        for s, r in sorted(rows.get(e, {}).items()):
            print(f"{e}\t{s}\t{r['card']}\t{r['proof_digest'][:12]}\t{r['reason']}")
    print(f"excluded symbols: {sum(len(v) for v in rows.values())}")
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
