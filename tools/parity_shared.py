#!/usr/bin/env python3
"""Shared library parity across the 4 parity exes.
A shared function = a function name that funcdiff pairs in 2 or more exes
(BloodLib, Shared, Packet, CRT and other common code).
A shared function is MATCH only if it is MATCH in each exe that has it.
Usage: tools/parity_shared.py [DIR]   DIR = funcdiff json dir (default Docs/Parity/baseline)
       --list   print the shared functions that are not MATCH, with the exes where they differ.
The goal for shared functions is 99 % (Docs/Parity/README.md, Goal)."""
import collections, json, sys
EXES = ["CacheGate", "LobbyGate", "SmartCouponDaemon", "PostOfficeDaemon"]
args = [a for a in sys.argv[1:] if not a.startswith("--")]
src = args[0] if args else "Docs/Parity/baseline"
suffix = ".json" if src.rstrip("/").endswith("baseline") else ".funcdiff.json"
d = {e: json.load(open(f"{src}/{e}{suffix}")) for e in EXES}
count = collections.Counter(k for e in EXES for k in d[e])
shared = sorted(k for k, n in count.items() if n >= 2)
bad = {k: [e for e in EXES if k in d[e] and d[e][k]["status"] != "MATCH"] for k in shared}
bad = {k: v for k, v in bad.items() if v}
m = len(shared) - len(bad)
print(f"shared library: MATCH {m}/{len(shared)} = {100*m/max(len(shared),1):.1f} % parity (goal 99 %)")
if "--list" in sys.argv:
    for k, v in bad.items():
        print(f"  DIFF  {k}  in {','.join(v)}")
