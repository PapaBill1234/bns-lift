#!/usr/bin/env python3
"""Make a replay.py STREAM file from a pktlog capture.

Usage:
  pkl_stream.py PKL PEER_PORT OUT [--dir IN|OUT] [--count N]
      Take the "pkt" records of one direction (default IN = peer -> exe) to or from PEER_PORT
      in PKL, in capture order, and write their bytes as one binary file OUT.
      --count N: take only the first N packets (default all).

It reads the text output of pkldump.py (--kind pkt --bytes -1 --no-fold).
Env: LG_PKTLOG = folder of pkldump.py (default ../../bns-wine/pktlog from the repo root).
"""
import argparse, os, re, subprocess, sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("pkl")
    ap.add_argument("port", type=int)
    ap.add_argument("out")
    ap.add_argument("--dir", default="IN", choices=["IN", "OUT"])
    ap.add_argument("--count", type=int, default=0)
    a = ap.parse_args()
    pkt = os.environ.get("LG_PKTLOG", os.path.join(ROOT, "..", "..", "bns-wine", "pktlog"))
    txt = subprocess.run([sys.executable, "-I", os.path.join(pkt, "pkldump.py"), a.pkl, "--kind", "pkt",
                          "--bytes", "-1", "--no-fold"], capture_output=True, text=True, check=True).stdout
    head = re.compile(r"^\S+\s+\S+\s+(IN|OUT)\s+\S+\s+[\d.]+:(\d+)\s+pkt\b")
    row = re.compile(r"^\s+[0-9a-f]{4}\s+((?:[0-9a-f]{2} )+)")
    packets, cur = [], None
    for line in txt.splitlines():
        m = head.match(line)
        if m:
            cur = None
            if m.group(1) == a.dir and int(m.group(2)) == a.port:
                cur = bytearray()
                packets.append(cur)
            continue
        m = row.match(line)
        if m and cur is not None:
            cur += bytes.fromhex(m.group(1).replace(" ", ""))
    if a.count:
        packets = packets[:a.count]
    with open(a.out, "wb") as f:
        for p in packets:
            f.write(p)
    print(f"{a.out}: {len(packets)} packets, {sum(map(len, packets))} bytes")


if __name__ == "__main__":
    main()
