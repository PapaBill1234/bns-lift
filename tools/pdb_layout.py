#!/usr/bin/env python3
"""pdb_layout: compare the member names and offsets of each lift class with the server PDB.

Usage: tools/pdb_layout.py [build-dir] [--nopdb]

The script only joins the output of 2 existing tools:
  - lift side: clang `-fdump-record-layouts-complete` for each .cpp in <build-dir>/compile_commands.json;
  - PDB side:  resymc `dump-all` (https://github.com/ergrelet/resym) for each server PDB.

Install resymc (the C flag is necessary for the oniguruma build with a new gcc):
  CFLAGS=-std=gnu17 cargo install --locked --git https://github.com/ergrelet/resym --rev 5be09381 resymc
Set $RESYMC if resymc is not on PATH. The PDB dumps go to ~/.cache/bns-lift/resym/.

Rules:
  - The script checks the classes that src/ declares. It skips SDK, STL and vendor types.
  - If the PDB has a member list for the class, each lift member must have a PDB member
    with the same name at the same offset. Each other member is an error (exit 1).
  - If the PDB has no member list for the class, the script does not check it.
    --nopdb prints these classes. Their invented names must have `// ❓`.
  - Bit fields and members of classes with virtual bases are not checked.
"""
import collections
import glob
import json
import os
import re
import shlex
import shutil
import subprocess
import sys
from concurrent.futures import ThreadPoolExecutor

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)
sys.path.insert(0, HERE)
import pdbq  # noqa: E402

CACHE = os.path.expanduser("~/.cache/bns-lift/resym")
# CMake target -> server PDB. A target that is not here (lift_common) can match any of these PDBs.
TARGET_PDB = {
    "CacheGate": "CacheGate", "lift_cachegate": "CacheGate",
    "LobbyGate": "LobbyGate", "lift_lobbygate": "LobbyGate",
    "PostOfficeDaemon": "PostOfficeDaemon", "lift_postofficedaemon": "PostOfficeDaemon",
    "SmartCouponDaemon": "SmartCouponDaemon", "lift_smartcoupondaemon": "SmartCouponDaemon",
    "LobbyDaemon": "LobbyDaemon", "lift_lobbydaemon": "LobbyDaemon",
}
SKIP_TARGETS = {"lift_selftest", "lift_zstd"}


# ---------------------------------------------------------------- PDB side (resymc)
def resym_dump(server):
    pdb = os.path.join(pdbq.ida_dir(), server, server + ".pdb")
    out = os.path.join(CACHE, server + ".h")
    if os.path.exists(out) and os.path.getmtime(out) >= os.path.getmtime(pdb):
        return out
    exe = os.environ.get("RESYMC") or shutil.which("resymc")
    if not exe:
        sys.exit("pdb_layout: resymc not found. See the install line in tools/pdb_layout.py.")
    os.makedirs(CACHE, exist_ok=True)
    subprocess.run([exe, "dump-all", "-s", pdb, out + ".tmp"], check=True, stdout=subprocess.DEVNULL)
    os.replace(out + ".tmp", out)
    return out


TOP = re.compile(r"^(?:class|struct|union) (.+?)(?: : .*)? \{ /\* Size=")
MEMBER = re.compile(r"^\s*/\* 0x([0-9a-f]+) \*/ (.*);(?: /\* BitPos=\d+ \*/)?$")


def member_name(decl):
    """Name of a member from a resym declaration (without offset and `;`). None for a bit field."""
    if re.search(r" : \d+$", decl):
        return None
    m = re.search(r"\(\*+\s*(\w+)\)\s*\(", decl)  # function pointer
    if m:
        return m.group(1)
    m = re.search(r"(\w+)(?:\[[^\]]*\])*$", decl)
    return m.group(1) if m else None


def pdb_types(server):
    """name -> list of {member: offset} (one entry for each different definition)."""
    types = collections.defaultdict(list)
    name, fields = None, None
    with open(resym_dump(server), errors="replace") as f:
        for line in f:
            line = line.rstrip("\n")
            if name is None:
                m = TOP.match(line)
                if m:
                    name, fields = m.group(1), {}
                continue
            if line == "};":
                if fields not in types[name]:
                    types[name].append(fields)
                name = None
                continue
            m = MEMBER.match(line)
            if m:
                n = member_name(m.group(2))
                if n:
                    fields[n] = int(m.group(1), 16)
    return types


# ---------------------------------------------------------------- lift side (clang)
def own_names():
    """Class names that src/ declares."""
    names = set()
    decl = re.compile(r"^\s*(?:class|struct|union)\s+(\w+)\s*(?:final\s*)?(?::[^;{]*)?(?:\{.*|//.*)?$")
    for path in glob.glob(os.path.join(ROOT, "src", "**", "*.*"), recursive=True):
        if not path.endswith((".h", ".cpp")):
            continue
        with open(path, errors="replace") as f:
            for line in f:
                m = decl.match(line)
                if m:
                    names.add(m.group(1))
    return names


def clang_dump(entry):
    args = shlex.split(entry["command"])
    args = [a for a in args if not a.startswith(("/Fo", "/Fd"))]
    args[args.index("-c")] = "/Zs"
    args[1:1] = ["-Xclang", "-fdump-record-layouts-complete"]
    r = subprocess.run(args, cwd=entry["directory"], capture_output=True, text=True)
    if r.returncode:
        sys.exit("pdb_layout: clang failed on %s\n%s" % (entry["file"], r.stderr[:2000]))
    return r.stdout


LAYOUT_LINE = re.compile(r"^ *(\d+)(?::\d+-\d+)? \| (.*)$")
BASE = re.compile(r"\((?:primary |virtual )?base\)")


def lift_records(text):
    """Yield (class name, {member: offset}, has virtual base) for each layout in a clang dump."""
    lines = text.split("\n")
    i = 0
    while i < len(lines):
        if not lines[i].startswith("*** Dumping AST Record Layout"):
            i += 1
            continue
        top = LAYOUT_LINE.match(lines[i + 1]).group(2)
        name = re.sub(r"^(?:class|struct|union) ", "", top)
        members, vbase, anon_depth, j = {}, False, None, i + 2
        while j < len(lines) and "[sizeof=" not in lines[j]:
            m = LAYOUT_LINE.match(lines[j])
            j += 1
            if not m:
                continue
            bitfield = re.match(r"^ *\d+:\d+-\d+ \|", lines[j - 1]) is not None
            body = m.group(2)
            depth = (len(body) - len(body.lstrip(" "))) // 2
            t = body.strip()
            if "(virtual base)" in t:
                vbase = True
            if depth == 1:
                anon_depth = 1 if "(anonymous" in t else None
            own = depth == 1 or (anon_depth is not None and depth >= 2 and "(anonymous" not in t)
            if (own and not bitfield and not BASE.search(t) and "(anonymous" not in t
                    and "vftable pointer" not in t and "vbtable pointer" not in t):
                members[t.split()[-1]] = int(m.group(1))
        yield name, members, vbase
        i = j


# ---------------------------------------------------------------- compare
def main():
    argv = [a for a in sys.argv[1:] if not a.startswith("--")]
    build = argv[0] if argv else os.environ.get("LIFT_BUILD_DIR", os.path.join(ROOT, "build"))
    cc_path = os.path.join(build, "compile_commands.json")
    if not os.path.exists(cc_path):
        sys.exit("pdb_layout: %s not found. Configure with -DCMAKE_EXPORT_COMPILE_COMMANDS=ON." % cc_path)
    with open(cc_path) as f:
        entries = [e for e in json.load(f) if e["file"].endswith(".cpp")]

    def target(e):
        m = re.search(r"/FoCMakeFiles/([^/]+)\.dir", e["command"])
        return m.group(1) if m else None

    entries = [e for e in entries if target(e) not in SKIP_TARGETS]
    with ThreadPoolExecutor(os.cpu_count() or 4) as ex:
        dumps = list(ex.map(clang_dump, entries))

    own = own_names()
    servers = sorted(set(TARGET_PDB.values()))
    pdb = {s: pdb_types(s) for s in servers}

    def pdb_variants(srvs, name):
        out = [(s, v) for s in srvs for v in pdb[s].get(name, [])]
        if not out:  # The PDB name can have an outer class or namespace that the lift does not use.
            out = [(s, v) for s in srvs for n, vs in pdb[s].items() if n.endswith("::" + name) for v in vs]
        return out

    seen, errors, nopdb, n_rec, n_mem = set(), [], set(), 0, 0
    for e, text in zip(entries, dumps):
        tgt = target(e)
        for name, members, vbase in lift_records(text):
            base = name.split("::")[-1].split("<")[0]
            if base not in own or "anonymous" in name or "(lambda" in name or name.startswith("std::"):
                continue
            if (tgt, name) in seen or vbase:
                continue
            seen.add((tgt, name))
            variants = pdb_variants([TARGET_PDB[tgt]] if tgt in TARGET_PDB else servers, name)
            if not variants:
                nopdb.add(name)
                continue
            n_rec += 1
            n_mem += len(members)
            best = min(([(k, o) for k, o in members.items() if v.get(k) != o], s, v) for s, v in variants)
            for k, o in best[0]:
                v = best[2]
                at = [n for n, x in v.items() if x == o]
                why = ("PDB has %s at %d" % (at[0], o) if at else
                       "PDB offset %d" % v[k] if k in v else "no PDB member with this name")
                errors.append("%s: %s::%s at %d: %s (%s)" % (tgt, name, k, o, why, best[1]))
    for line in sorted(set(errors)):
        print("pdb_layout: " + line)
    print("pdb_layout: %d classes, %d members checked; %d classes have no PDB member list; %d errors"
          % (n_rec, n_mem, len(nopdb), len(set(errors))))
    if "--nopdb" in sys.argv:
        for n in sorted(nopdb):
            print("  no PDB member list: " + n)
    return 1 if errors else 0


if __name__ == "__main__":
    sys.exit(main())
