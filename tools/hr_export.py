#!/usr/bin/env python3
"""Export Hex-Rays pseudocode of all PDB functions of one server, one file per PDB module.

    tools/hr_export.py <Server> [--force]

Input:  private-project/ida/lift/<Server>/<Server>.exe.i64 and <Server>.pdb
Output: ~/.cache/bns-lift/hr/<Server>/<Module>.c and index.tsv (module, rva, name, first line, last line, status)

IDA runs headless (idat -A) on a copy of the .i64. The original database is not changed.
A lift session reads these files and does not need to decompile in IDA.
"""
import fcntl, os, re, shutil, subprocess, sys, tempfile
from pathlib import Path

PP = Path(__file__).resolve().parents[1].parent
if not (PP / "ida/lift").is_dir():  # worktree: bns-wt/<id>
    PP = Path.home() / "Documents/Codex/private-project"
IDAT = Path.home() / "ida-pro-9.5/idat"
OUT_ROOT = Path.home() / ".cache/bns-lift/hr"
IDA_SCRIPT = Path(__file__).with_name("hr_export_ida.py")

MOD = re.compile(r"^\s*Mod (\d+) \| `(.+)`:\s*$")
PROC = re.compile(r"S_[GL]PROC32\S* \[size = \d+\] `(.+)`$")
ADDR = re.compile(r"addr = (\d{4}):(\d+), code size = (\d+)")


def sections(pdb):
    out = subprocess.run(["llvm-pdbutil", "dump", "-section-headers", str(pdb)], capture_output=True, text=True, check=True).stdout
    va, n = {}, None
    for line in out.splitlines():
        m = re.match(r"\s*SECTION HEADER #(\d+)", line)
        if m:
            n = int(m.group(1))
        m = re.match(r"\s*([0-9A-Fa-f]+) virtual address", line)
        if m and n:
            va[n] = int(m.group(1), 16)
    return va


def functions(pdb):
    """Return [(rva, module, name, size)], one row per address."""
    va = sections(pdb)
    out = subprocess.run(["llvm-pdbutil", "dump", "-modules", "-symbols", str(pdb)], capture_output=True, text=True, check=True).stdout
    lines = out.splitlines()
    mod, name, rows, paths = None, None, {}, {}
    for line in lines:
        m = MOD.match(line)
        if m:
            path = m.group(2).replace("\\", "/")
            mod = path if path.lower().endswith(".obj") else None
            continue
        m = PROC.search(line)
        if m:
            name = m.group(1)
            continue
        m = ADDR.search(line)
        if m and name and mod:
            sec, off, size = int(m.group(1)), int(m.group(2)), int(m.group(3))
            if sec in va and "$" not in name:
                rva = va[sec] + off
                rows.setdefault(rva, (rva, mod, name, size))
        name = None if m else name
    # Module key: .obj stem. On a name clash, add the parent folder.
    stems = {}
    for _, path, _, _ in rows.values():
        stems.setdefault(Path(path).stem, set()).add(path)
    def key(path):
        p = Path(path)
        return p.stem if len(stems[p.stem]) == 1 else f"{p.parent.name}_{p.stem}"
    return sorted((r, key(p), n, s) for r, p, n, s in rows.values())


def export(server, force=False):
    OUT_ROOT.mkdir(parents=True, exist_ok=True)
    with open(OUT_ROOT / f".{server}.lock", "w") as lk:
        fcntl.flock(lk, fcntl.LOCK_EX)  # one export per server at a time; a waiter then finds .done
        return _export(server, force)


def _export(server, force):
    d = PP / "ida/lift" / server
    i64, pdb = d / f"{server}.exe.i64", d / f"{server}.pdb"
    out = OUT_ROOT / server
    if (out / ".done").exists() and not force:
        return out
    if not i64.exists() or not pdb.exists():
        raise SystemExit(f"missing {i64} or {pdb}")
    if out.exists():
        shutil.rmtree(out)
    out.mkdir(parents=True)
    funcs = functions(pdb)
    with open(out / "funcs.tsv", "w") as f:
        for r, m, n, s in funcs:
            f.write(f"{r:x}\t{m}\t{n}\t{s}\n")
    with tempfile.TemporaryDirectory(prefix=f"hr-{server}-") as tmp:
        db = Path(tmp) / i64.name
        shutil.copy2(i64, db)
        log = out / "idat.log"
        env = dict(os.environ, HR_FUNCS=str(out / "funcs.tsv"), HR_OUT=str(out), TVHEADLESS="1")
        p = subprocess.run([str(IDAT), "-A", f"-S{IDA_SCRIPT}", f"-L{log}", str(db)], env=env, timeout=12 * 3600,
                           stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    if not (out / "index.tsv").exists():
        raise SystemExit(f"idat failed (exit {p.returncode}); see {log}")
    (out / ".done").touch()
    return out


if __name__ == "__main__":
    if len(sys.argv) < 2:
        raise SystemExit(__doc__)
    o = export(sys.argv[1], "--force" in sys.argv)
    idx = (o / "index.tsv").read_text().splitlines()
    bad = sum(1 for l in idx if not l.endswith("\tok"))
    print(f"{o}: {len(idx)} functions, {bad} failed, {len(list(o.glob('*.c')))} modules")
