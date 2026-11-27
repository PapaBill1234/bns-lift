#!/usr/bin/env python3
"""pdb_layout: compare the member names and offsets of each lift class with the server PDB.

Usage: tools/pdb_layout.py [build-dir] [--nopdb]

Exit codes: 0 pass, 1 layout errors (or a clang or resymc failure), 2 setup error (a server PDB that a target
needs is missing, or no compile_commands.json).
Summary: <build-dir>/pdb_layout.json (build output, never commit it). It holds the classes and members checked,
the holes (classes and targets that the script does not check), the PDB hashes, the errors and the result.

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
  - Each target maps to the server PDBs of the exes that link it (TARGET_PDB). lift_common goes into 5 exes:
    each of its classes must match each of these PDBs that has a member list for the class.
  - A target that is not in TARGET_PDB is checked against all PDBs (the closest one wins). The summary lists it
    in holes.unmapped_targets. Add each new library target to TARGET_PDB.
  - If a server PDB that a target needs is not in the IDA dir, the script stops with exit 2.
"""
import collections
import glob
import hashlib
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
SERVERS = ("CacheGate", "LobbyGate", "SmartCouponDaemon", "PostOfficeDaemon", "LobbyDaemon", "MarketDealerDaemon",
           "GameDaemon")
# CMake target -> the server PDBs of the exes that link it (CMakeLists.txt target_link_libraries).
# A class of a target with more than one server must match each of these PDBs that has the class.
TARGET_PDB = {
    "CacheGate": ("CacheGate",), "lift_common_cg": ("CacheGate",),
    "LobbyGate": ("LobbyGate",), "lift_lobbygate": ("LobbyGate",), "lift_common_lg": ("LobbyGate",),
    "SmartCouponDaemon": ("SmartCouponDaemon",), "lift_smartcoupondaemon": ("SmartCouponDaemon",),
    "lift_common_scd": ("SmartCouponDaemon",),
    "PostOfficeDaemon": ("PostOfficeDaemon",), "lift_postofficedaemon": ("PostOfficeDaemon",),
    "lift_common_pod": ("PostOfficeDaemon",),
    "LobbyDaemon": ("LobbyDaemon",), "lift_lobbydaemon": ("LobbyDaemon",), "lift_common_ld": ("LobbyDaemon",),
    "lift_marketdealerdaemon": ("MarketDealerDaemon",),
    # GameDaemon is opt-in (cmake -DLIFT_GAMEDAEMON=ON). lift_common_gd goes into GameDaemon only.
    "GameDaemon": ("GameDaemon",), "lift_gamedaemon": ("GameDaemon",), "lift_common_gd": ("GameDaemon",),
    # LG, SCD, POD and LobbyDaemon link lift_common; lift_marketdealerdaemon links it too. CacheGate does not.
    "lift_common": ("LobbyGate", "SmartCouponDaemon", "PostOfficeDaemon", "LobbyDaemon", "MarketDealerDaemon"),
}
SKIP_TARGETS = {"lift_selftest", "lift_zstd"}
SUMMARY = "pdb_layout.json"


# ---------------------------------------------------------------- PDB side (resymc)
def pdb_path(server):
    return os.path.join(pdbq.ida_dir(), server, server + ".pdb")


def resym_dump(server):
    pdb = pdb_path(server)
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


# ---------------------------------------------------------------- summary
def file_sha256(path):
    h = hashlib.sha256()
    with open(path, "rb") as f:
        for b in iter(lambda: f.read(1 << 20), b""):
            h.update(b)
    return h.hexdigest()


def git_rev():
    r = subprocess.run(["git", "-C", ROOT, "rev-parse", "HEAD"], capture_output=True, text=True)
    return r.stdout.strip() if r.returncode == 0 else None


def write_summary(build, summary):
    """Write <build>/pdb_layout.json (a build output). The gate and the parity engine can read it."""
    if not os.path.isdir(build):
        return
    summary = dict(kind="bns-lift pdb_layout v1", rev=git_rev(), script_sha256=file_sha256(os.path.abspath(__file__)),
                   **summary)
    out = os.path.join(build, SUMMARY)
    with open(out + ".tmp", "w") as f:
        json.dump(summary, f, indent=1, sort_keys=True)
        f.write("\n")
    os.replace(out + ".tmp", out)


def fail_setup(build, why, **extra):
    """Exit 2: the check cannot run. The summary says why."""
    print("pdb_layout: " + why)
    write_summary(build, dict(result="error", rc=2, why=why, **extra))
    return 2


# ---------------------------------------------------------------- compare
def main():
    argv = [a for a in sys.argv[1:] if not a.startswith("--")]
    build = argv[0] if argv else os.environ.get("LIFT_BUILD_DIR", os.path.join(ROOT, "build"))
    cc_path = os.path.join(build, "compile_commands.json")
    if not os.path.exists(cc_path):
        return fail_setup(build, "%s not found. Configure with -DCMAKE_EXPORT_COMPILE_COMMANDS=ON." % cc_path)
    with open(cc_path) as f:
        entries = [e for e in json.load(f) if e["file"].endswith(".cpp")]

    def target(e):
        m = re.search(r"/FoCMakeFiles/([^/]+)\.dir", e["command"])
        return m.group(1) if m else None

    tus = collections.Counter(target(e) for e in entries)
    skipped = sorted(t for t in tus if t in SKIP_TARGETS)
    unmapped = sorted(str(t) for t in tus if t not in SKIP_TARGETS and t not in TARGET_PDB)
    entries = [e for e in entries if target(e) not in SKIP_TARGETS]
    # The server PDBs that the targets of this build need. An unmapped target can match any PDB.
    need = set(SERVERS) if unmapped else {s for t in tus if t in TARGET_PDB for s in TARGET_PDB[t]}
    missing = sorted(pdb_path(s) for s in need if not os.path.exists(pdb_path(s)))
    if missing:
        return fail_setup(build, "server PDB not found: %s. Mount or copy each server PDB (LIFT_IDA_DIR)."
                          % ", ".join(missing), missing_pdbs=missing)
    if unmapped:
        print("pdb_layout: target(s) %s are not in TARGET_PDB; their classes match the closest of all PDBs"
              % ", ".join(unmapped))
    servers = sorted(need)
    with ThreadPoolExecutor(os.cpu_count() or 4) as ex:
        dumps = list(ex.map(clang_dump, entries))

    own = own_names()
    pdb = {s: pdb_types(s) for s in servers}

    def pdb_variants(srvs, name):
        out = [(s, v) for s in srvs for v in pdb[s].get(name, [])]
        if not out:  # The PDB name can have an outer class or namespace that the lift does not use.
            out = [(s, v) for s in srvs for n, vs in pdb[s].items() if n.endswith("::" + name) for v in vs]
        return out

    seen, errors, nopdb, vbases, n_rec, n_mem = set(), [], set(), set(), 0, 0
    per_target = collections.defaultdict(lambda: {"classes": 0, "members": 0})
    for e, text in zip(entries, dumps):
        tgt = target(e)
        for name, members, vbase in lift_records(text):
            base = name.split("::")[-1].split("<")[0]
            if base not in own or "anonymous" in name or "(lambda" in name or name.startswith("std::"):
                continue
            if (tgt, name) in seen:
                continue
            seen.add((tgt, name))
            if vbase:
                vbases.add(name)
                continue
            # Mapped target: one group for each server (each must match). Unmapped: one group, all servers.
            groups = [[s] for s in TARGET_PDB[tgt]] if tgt in TARGET_PDB else [servers]
            found = [v for v in (pdb_variants(g, name) for g in groups) if v]
            if not found:
                nopdb.add(name)
                continue
            n_rec += 1
            n_mem += len(members)
            per_target[str(tgt)]["classes"] += 1
            per_target[str(tgt)]["members"] += len(members)
            for variants in found:
                best = min(([(k, o) for k, o in members.items() if v.get(k) != o], s, v) for s, v in variants)
                for k, o in best[0]:
                    v = best[2]
                    at = [n for n, x in v.items() if x == o]
                    why = ("PDB has %s at %d" % (at[0], o) if at else
                           "PDB offset %d" % v[k] if k in v else "no PDB member with this name")
                    errors.append("%s: %s::%s at %d: %s (%s)" % (tgt, name, k, o, why, best[1]))
    errors = sorted(set(errors))
    for line in errors:
        print("pdb_layout: " + line)
    print("pdb_layout: %d classes, %d members checked; %d classes have no PDB member list; %d errors"
          % (n_rec, n_mem, len(nopdb), len(errors)))
    if "--nopdb" in sys.argv:
        for n in sorted(nopdb):
            print("  no PDB member list: " + n)
    rc = 1 if errors else 0
    write_summary(build, dict(
        result="fail" if rc else "pass", rc=rc,
        classes=n_rec, members=n_mem, errors=len(errors), error_lines=errors,
        tus_total=sum(tus.values()), tus_checked=len(entries), targets=dict(sorted((str(t), n) for t, n in tus.items())),
        per_target=dict(sorted(per_target.items())),
        target_pdb={t: list(TARGET_PDB[t]) for t in sorted(str(t) for t in tus) if t in TARGET_PDB},
        pdb_sha256={s: file_sha256(pdb_path(s)) for s in servers},
        holes=dict(skipped_targets=skipped, unmapped_targets=unmapped, missing_pdbs=[],
                   nopdb_classes=len(nopdb), vbase_classes=sorted(vbases))))
    return rc


if __name__ == "__main__":
    sys.exit(main())
