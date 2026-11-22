#!/usr/bin/env python3
"""Write the parity table into README.md (between the parity markers).
Sources (all in git): Docs/Parity/baseline/<EXE>.json (per-function results),
Docs/Parity/progress.tsv (total per exe = paired + only in original; start and last card).
tools/parity.sh --accept runs this after each accepted lift-parity card. Manual run: tools/parity_readme.py"""
import collections, json, re
# CORE: the first 4 exes (summary row and shared library). LobbyDaemon is in the lift; it gets its own row.
CORE = ["CacheGate", "LobbyGate", "SmartCouponDaemon", "PostOfficeDaemon"]
EXES = CORE + ["LobbyDaemon"]
START, END = "<!-- parity:start -->", "<!-- parity:end -->"

rows = [l.rstrip("\n").split("\t") for l in open("Docs/Parity/progress.tsv")][1:]
def cells(row):
    return {m[0]: (int(m[1]), int(m[2])) for m in re.findall(r"(\w+) (\d+)/(\d+)", row[2])}
last = cells(rows[-1])
first = {}
for row in rows:  # start = first card that measured the exe
    for e, v in cells(row).items():
        first.setdefault(e, v)
EXES = [e for e in EXES if e in last]
d = {e: json.load(open(f"Docs/Parity/baseline/{e}.json")) for e in EXES}

def pct(m, t):
    return 100 * m / max(t, 1)

def level(p):
    return "99 % ✅" if p >= 99 else "95 % ✅" if p >= 95 else "90 % ✅" if p >= 90 else "below 90 %"

out = [f"Last update: card `{rows[-1][1]}` ({rows[-1][0]}). Tool: `tools/parity.sh` (VS2010 /GL /LTCG build vs original, funcdiff).", "",
       "| Exe | Parity | MATCH | DIFF | Only in original | Total | Mean score | Start | Change | Level |",
       "| --- | ---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: | --- |"]
sm = st = 0
for e in EXES:
    r = d[e]
    m = sum(x["status"] == "MATCH" for x in r.values())
    diff = len(r) - m
    t = last.get(e, (0, len(r)))[1]
    only = t - len(r)
    mean = sum(x["score"] for x in r.values()) / max(len(r), 1)
    p0 = pct(*first[e]) if e in first else 0
    p = pct(m, t)
    if e in CORE:
        sm += m; st += t
    out.append(f"| {e} | **{p:.1f} %** | {m} | {diff} | {only} | {t} | {mean:.1f} | {p0:.1f} % | {p - p0:+.1f} | {level(p)} |")
p = pct(sm, st)
p0 = pct(sum(first[e][0] for e in CORE), sum(first[e][1] for e in CORE))
out.append(f"| **First 4** | **{p:.1f} %** | {sm} | | | {st} | | {p0:.1f} % | {p - p0:+.1f} | {level(p)} |")

count = collections.Counter(k for e in CORE for k in d[e])
shared = [k for k, n in count.items() if n >= 2]
sbad = [k for k in shared if any(k in d[e] and d[e][k]["status"] != "MATCH" for e in CORE)]
sp = pct(len(shared) - len(sbad), len(shared))
out += ["", "| Shared library (functions in 2+ exes) | Parity | MATCH in each exe | DIFF in 1+ exe | Total | Goal |",
        "| --- | ---: | ---: | ---: | ---: | --- |",
        f"| BloodLib, Shared, Packet, CRT | **{sp:.1f} %** | {len(shared) - len(sbad)} | {len(sbad)} | {len(shared)} | 99 % |"]
out += ["", "First 4 and shared library: CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon. LobbyDaemon: lift in progress; most functions are still stubs (only in original). Goal: 95 % per exe, 99 % preferred. Shared library: 99 % preferred. Rules: [Docs/Parity/README.md](Docs/Parity/README.md). History: [Docs/Parity/progress.tsv](Docs/Parity/progress.tsv).",
        "", "| Card | " + " | ".join(EXES) + " |", "| --- |" + " ---: |" * len(EXES)]
for row in rows:
    c = cells(row)
    out.append(f"| `{row[1]}` | " + " | ".join(f"{pct(*c[e]):.1f} %" if e in c else "" for e in EXES) + " |")

body = "\n".join(out)
s = open("README.md").read()
if START in s:
    a, b = s.index(START) + len(START), s.index(END)
    s = s[:a] + "\n" + body + "\n" + s[b:]
else:
    s = s.rstrip("\n") + f"\n\n## Parity\n\n{START}\n{body}\n{END}\n"
open("README.md", "w").write(s)
print(f"README parity table: first 4 {p:.1f} %, shared {sp:.1f} %")
