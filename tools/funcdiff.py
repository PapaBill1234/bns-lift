#!/usr/bin/env python3
"""funcdiff: compare each function of the original 2019 exe with the same function of our exe.

Usage: tools/funcdiff.py <Server> [--build build-pdb] [--show <regex>] [--json out.json] [--diff base.json]

Each exe needs its own PDB. The original pair is ../ida/lift/<Server>/<Server>.{exe,pdb}.
Our pair is <build>/<Server>.{exe,pdb}. Make it with a /Z7 + /debug build (see Docs/Plan/plan.md).

reccmp does the same for x86 only. This tool is the x64 glue. It does not compare instructions,
because clang-cl and VS2010 give different code. It compares 3 signals that do not depend on the compiler:

  calls   callee names in call order (imports by name). A call in our exe to a function that the
          original never calls from this function is expanded to the callee's calls (the original
          inlined it; we build with /Ob0). Folded (ICF) names count as one name.
  refs    strings and named data (vftables, globals) that the function reads by address
  consts  immediate values (not stack frame sizes)

Status: MATCH = all 3 equal. Score = mean similarity of the 3 lists (0..100).
Needs: capstone, pefile (for example: uv pip install capstone pefile).
"""
import argparse
import bisect
import collections
import difflib
import json
import os
import re
import subprocess
import sys

try:
    import capstone
    import pefile
except ImportError:
    sys.exit("funcdiff needs capstone and pefile (uv pip install capstone pefile)")

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
# Worktree (bns-wt/<id>): ida/lift is not in a parent dir. Use the main project dir (same rule as hr_export.py).
_PP_IDA = os.path.expanduser("~/Documents/Codex/private-project/ida/lift")
if not os.environ.get("LIFT_IDA_DIR") and os.path.isdir(_PP_IDA) \
        and not os.path.isdir(os.path.join(os.path.dirname(os.path.dirname(HERE)), "ida", "lift")):
    os.environ["LIFT_IDA_DIR"] = _PP_IDA
import pdbq  # noqa: E402

CACHE = os.path.expanduser("~/.cache/bns-lift/funcdiff")
REC = re.compile(r"^\s*\d+ \| (S_\w+) \[size = \d+\] `(.*)`\s*$")
ADDR = re.compile(r"addr = (\d+):(\d+)(?:, code size = (\d+))?")
SKIP_NAME = re.compile(r"^(`|__|_RTC|_CRT|\$|std::|\?\?)|`")
# /GS and CRT helpers: the compiler adds them, the source does not.
NOISE = {"__security_check_cookie", "__security_cookie", "__GSHandlerCheck", "_RTC_CheckStackVars",
         "__chkstk", "_alloca_probe", "__std_terminate"}


def pdb_dump(pdb, flag):
    os.makedirs(CACHE, exist_ok=True)
    out = os.path.join(CACHE, "%s.%d%s.txt" % (os.path.basename(pdb), int(os.path.getmtime(pdb)), flag))
    if not os.path.exists(out):
        with open(out + ".tmp", "w") as f:
            subprocess.run(["llvm-pdbutil", "dump", flag, pdb], stdout=f, stderr=subprocess.DEVNULL, check=True)
        os.rename(out + ".tmp", out)
    with open(out, errors="replace") as f:
        return f.read().split("\n")


class Image:
    def __init__(self, exe, pdb):
        self.pe = pefile.PE(exe, fast_load=True)
        self.pe.parse_data_directories(directories=[pefile.DIRECTORY_ENTRY["IMAGE_DIRECTORY_ENTRY_IMPORT"]])
        self.base = self.pe.OPTIONAL_HEADER.ImageBase
        self.secs = [0] + [s.VirtualAddress for s in self.pe.sections]
        self.mem = self.pe.get_memory_mapped_image()
        self.size = self.pe.OPTIONAL_HEADER.SizeOfImage
        self.imports = {}
        for e in getattr(self.pe, "DIRECTORY_ENTRY_IMPORT", []):
            for i in e.imports:
                name = i.name.decode() if i.name else "%s#%d" % (e.dll.decode(), i.ordinal)
                self.imports[i.address - self.base] = name
        self.funcs = {}            # rva -> (name, size)
        self.names = collections.defaultdict(set)   # rva -> names (functions and data)
        for flag in ("-symbols", "-globals", "-publics"):
            lines = pdb_dump(pdb, flag)
            for n, l in enumerate(lines):
                m = REC.match(l)
                if not m or n + 1 >= len(lines):
                    continue
                kind, name = m.groups()
                a = ADDR.search(lines[n + 1])
                if not a or not 0 < int(a.group(1)) < len(self.secs):
                    continue
                rva = self.secs[int(a.group(1))] + int(a.group(2))
                if kind in ("S_GPROC32", "S_LPROC32"):
                    self.funcs.setdefault(rva, (name, int(a.group(3) or 0)))
                if kind in ("S_GPROC32", "S_LPROC32", "S_GDATA32", "S_LDATA32", "S_PUB32"):
                    self.names[rva].add(name)
        # Mangled public name of each function: it tells overloads and destructor kinds apart.
        self.mangled = {}
        for rva in self.funcs:
            ms = sorted(n for n in self.names[rva] if n.startswith("?") and not n.startswith("??_C"))
            if ms:
                self.mangled[rva] = ms[0]

    def data_below(self, t, span=0x40):
        """The nearest named symbol below t in a writable section, at most span bytes away."""
        sec = next((s for s in self.pe.sections
                    if s.VirtualAddress <= t < s.VirtualAddress + s.Misc_VirtualSize), None)
        if sec is None or not sec.Characteristics & 0x80000000:      # IMAGE_SCN_MEM_WRITE
            return None
        if not hasattr(self, "_named"):
            self._named = sorted(self.names)
        i = bisect.bisect_right(self._named, t) - 1
        b = self._named[i] if i >= 0 else None
        return b if b is not None and t - b <= span else None

    def const_ptr(self, t):
        """The RVA that a pointer in a read-only section holds, else None."""
        sec = next((s for s in self.pe.sections
                    if s.VirtualAddress <= t < s.VirtualAddress + s.Misc_VirtualSize), None)
        if sec is None or sec.Characteristics & 0x80000000 or t + 8 > len(self.mem):
            return None
        v = int.from_bytes(self.mem[t:t + 8], "little") - self.base
        return v if 0 < v < self.size else None

    def code(self, rva, size):
        return self.mem[rva:rva + size]

    def string_at(self, rva):
        b = self.mem[rva:rva + 256]
        if len(b) >= 4 and b[1] == 0 and b[3] == 0 and 32 <= b[0] < 127:
            e = next((i for i in range(0, len(b) - 1, 2) if b[i:i + 2] == b"\0\0"), None)
            s = b[:e].decode("utf-16-le", "replace") if e else None
            if s and all(32 <= ord(c) < 127 or c in "\t\r\n" for c in s):
                return 'L"%s"' % s
        e = b.find(b"\0")
        if e >= 2:
            s = b[:e]
            if all(32 <= c < 127 or c in (9, 10, 13) for c in s):
                return '"%s"' % s.decode()
        return None


def canon_names(orig):
    """Map each name of a folded (ICF) group to one name, from the original PDB."""
    alias = {}
    for rva, (name, _s) in orig.funcs.items():
        group = sorted(n for n in orig.names[rva] if not n.startswith("?"))
        for n in group:
            alias[n] = group[0]
    return alias


MD = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_64)
MD.detail = True
X86 = capstone.x86


def signals(img, rva, size, alias):
    calls, refs, consts = [], [], []
    end = rva + size

    def target_name(t):
        if t in img.imports:
            return "import:" + img.imports[t]
        if t in img.funcs:
            n = img.funcs[t][0]
            return alias.get(n, n)
        ns = sorted(img.names.get(t, ()), key=lambda n: (n.startswith("?"), n))
        return alias.get(ns[0], ns[0]) if ns else None

    def field_name(t):
        """A slot inside a named global (for example Aes128::_Delegator+0x10). Noise fix 3."""
        p = img.const_ptr(t)                       # a slot of a vtable in .rdata: call its function
        if p is not None and p in img.funcs:
            return target_name(p)
        base = img.data_below(t)
        if base is None:
            return None
        n = target_name(base)
        return "%s+0x%x" % (n, t - base) if n else None

    loaded = {}                                    # register -> import loaded into it

    # Noise fix 2: a jump table at the end of the function is data, not code. The table is read
    # with [base + index*4 + disp] where disp is an RVA inside the function. Stop before it.
    for ins in MD.disasm(img.code(rva, size), rva):
        for op in ins.operands:
            if (op.type == X86.X86_OP_MEM and op.mem.index != 0 and op.mem.scale in (1, 4)
                    and op.mem.base not in (0, X86.X86_REG_RIP) and ins.address < op.mem.disp < end):
                end = op.mem.disp
        if ins.address >= end:
            break
    size = end - rva

    chk = None                                     # const of the last instruction if it is mov eax, imm
    for ins in MD.disasm(img.code(rva, size), rva):
        op0 = ins.operands[0] if ins.operands else None
        chk, prev = None, chk
        if ins.group(X86.X86_GRP_JUMP) and ins.mnemonic != "jmp" or ins.mnemonic.startswith("loop"):
            continue                               # noise fix 1: a branch target is not a constant
        if ins.group(X86.X86_GRP_CALL) or (ins.group(X86.X86_GRP_JUMP) and ins.mnemonic == "jmp"):
            t = None
            if op0 is not None and op0.type == X86.X86_OP_IMM:
                t = op0.imm
                if rva <= t < end:
                    continue                       # jump inside the function
            elif op0 is not None and op0.type == X86.X86_OP_MEM and op0.mem.base == X86.X86_REG_RIP:
                t = ins.address + ins.size + op0.mem.disp
            if t is not None and target_name(t) in ("__chkstk", "_alloca_probe") and prev is not None:
                consts.remove(prev)                 # noise fix 4: frame size for the stack probe
            if t is not None:
                n = target_name(t) or (field_name(t) or "?%x" % t if ins.mnemonic == "call" else None)
                if n and n not in NOISE:
                    calls.append(n)
            elif ins.mnemonic == "call":
                r = op0.reg if op0 is not None and op0.type == X86.X86_OP_REG else None
                calls.append(loaded.get(r, "<indirect>"))
            continue
        if ins.mnemonic == "mov" and len(ins.operands) == 2 and ins.operands[0].type == X86.X86_OP_REG:
            src = ins.operands[1]
            r = ins.operands[0].reg
            loaded.pop(r, None)
            if src.type == X86.X86_OP_MEM and src.mem.base == X86.X86_REG_RIP:
                t = ins.address + ins.size + src.mem.disp
                if t in img.imports:
                    loaded[r] = "import:" + img.imports[t]
                    continue
        for op in ins.operands:
            if op.type == X86.X86_OP_MEM and op.mem.base == X86.X86_REG_RIP:
                t = ins.address + ins.size + op.mem.disp
                n = img.string_at(t) or target_name(t) or "<data>"
                if n not in NOISE:
                    refs.append(n)
            elif op.type == X86.X86_OP_IMM:
                regs = [o.reg for o in ins.operands if o.type == X86.X86_OP_REG]
                if X86.X86_REG_RSP in regs or X86.X86_REG_RBP in regs:
                    continue
                v = op.imm & 0xFFFFFFFFFFFFFFFF
                if v in (0, 1) or ins.mnemonic.startswith(("sh", "sa", "ro")):
                    continue                       # flags and shifts: compiler noise
                if 0x10000 <= v < img.size:
                    continue                       # an RVA (try tables, image-base addressing)
                consts.append(v)
                if ins.mnemonic == "mov" and ins.operands[0].type == X86.X86_OP_REG \
                        and ins.operands[0].reg == X86.X86_REG_EAX:
                    chk = v
    return calls, refs, sorted(set(consts))


def expand(orig, calls, table, rounds=3):
    """Replace a call that the original does not make with the callee's own calls (the original
    inlined it; we build with /Ob0). Keep a replacement only when it makes the lists more similar."""
    keep = set(orig)
    best = sim(orig, calls)
    for _ in range(rounds):
        changed = False
        i = 0
        while i < len(calls):
            c = calls[i]
            if c not in keep and c in table:
                cand = calls[:i] + table[c] + calls[i + 1:]
                s = sim(orig, cand)
                if s > best:
                    calls, best, changed = cand, s, True
                    continue
            i += 1
        if not changed:
            break
    return calls


def sim(a, b):
    if not a and not b:
        return 1.0
    return difflib.SequenceMatcher(None, a, b, autojunk=False).ratio()


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("server")
    ap.add_argument("--build", default="build-pdb")
    ap.add_argument("--show", help="print the signals of functions that match this regex")
    ap.add_argument("--json", help="write per-function results")
    ap.add_argument("--diff", help="compare with an earlier --json file")
    ap.add_argument("--worst", type=int, default=25)
    ap.add_argument("--only", action="store_true",
                    help="print the functions that are only in the original and only in ours (name, rva, size)")
    a = ap.parse_args()

    od = os.path.join(pdbq.ida_dir(), a.server)
    orig = Image(os.path.join(od, a.server + ".exe"), os.path.join(od, a.server + ".pdb"))
    ours = Image(os.path.join(a.build, a.server + ".exe"), os.path.join(a.build, a.server + ".pdb"))
    alias = canon_names(orig)

    def table(img):
        """key -> signals. Key = mangled name, else the PDB name."""
        t, plain = {}, collections.defaultdict(list)
        where = {}
        for rva, (name, size) in img.funcs.items():
            if SKIP_NAME.search(name) or not size:
                continue
            k = img.mangled.get(rva, name)
            if k not in t:
                t[k] = (alias.get(name, name), signals(img, rva, size, alias))
                plain[alias.get(name, name)].append(k)
                where[k] = (rva, size)
        img.where = where
        return t, plain

    (to, po), (tl, pl) = table(orig), table(ours)
    pairs = {k: k for k in set(to) & set(tl)}
    # Pair the rest by PDB name when the name is unique on both sides (signature changed).
    for name, ks in po.items():
        ko = [k for k in ks if k not in pairs]
        kl = [k for k in pl.get(name, ()) if k not in tl or k not in to]
        if len(ks) == 1 and len(pl.get(name, ())) == 1 and ko and kl:
            pairs[ko[0]] = kl[0]
    # Inline expansion uses PDB names; overloads share one list (the first). It also uses our
    # helpers that table() skips (anonymous namespace, templates): the original has them inlined.
    ours_calls = {}
    for k, (name, sig) in tl.items():
        ours_calls.setdefault(name, sig[0])
    for rva, (name, size) in ours.funcs.items():
        if size and alias.get(name, name) not in ours_calls:
            ours_calls[alias.get(name, name)] = signals(ours, rva, size, alias)[0]
    res = {}
    for ko in sorted(pairs, key=lambda k: to[k][0]):
        k = to[ko][0] if len(po[to[ko][0]]) == 1 else "%s [%s]" % (to[ko][0], ko)
        oc, orf, ok = to[ko][1]
        lc, lrf, lk = tl[pairs[ko]][1]
        lc = expand(oc, lc, ours_calls)
        s = (sim(oc, lc), sim(sorted(orf), sorted(lrf)), sim(ok, lk))
        status = "MATCH" if s == (1.0, 1.0, 1.0) else "DIFF"
        res[k] = {"status": status, "score": round(100 * sum(s) / 3, 1),
                  "calls": round(100 * s[0]), "refs": round(100 * s[1]), "consts": round(100 * s[2])}
        if a.show and re.search(a.show, k):
            print("== %s  %s" % (k, res[k]))
            for label, x, y in (("calls", oc, lc), ("refs", sorted(orf), sorted(lrf)),
                                ("consts", [hex(v) for v in ok], [hex(v) for v in lk])):
                if x != y:
                    print("  %s:" % label)
                    for d in difflib.unified_diff([str(v) for v in x], [str(v) for v in y], "orig", "ours", n=1, lineterm=""):
                        print("    " + d)
    n = len(res)
    m = sum(1 for r in res.values() if r["status"] == "MATCH")
    avg = sum(r["score"] for r in res.values()) / max(n, 1)
    only_o = len(to) - len(pairs)
    print("%s: %d paired functions, %d MATCH (%.1f %%), mean score %.1f, %d only in original"
          % (a.server, n, m, 100.0 * m / max(n, 1), avg, only_o))
    if a.only:
        lo = set(pairs.values())
        for label, tab, img, ks in (("ORIG", to, orig, [k for k in to if k not in pairs]),
                                    ("OURS", tl, ours, [k for k in tl if k not in lo])):
            for k in sorted(ks, key=lambda k: tab[k][0]):
                rva, size = img.where[k]
                print("  ONLY-%s  0x%06x %5d  %s%s" % (label, rva, size, tab[k][0],
                                                     "" if k == tab[k][0] else "  [%s]" % k))
    if not a.show and not a.only:
        worst = sorted(res.items(), key=lambda kv: kv[1]["score"])[:a.worst]
        for k, r in worst:
            print("  %5.1f  calls %3d  refs %3d  consts %3d  %s" % (r["score"], r["calls"], r["refs"], r["consts"], k))
    if a.diff:
        with open(a.diff) as f:
            base = json.load(f)
        for k, r in sorted(res.items()):
            if k in base and r["score"] < base[k]["score"]:
                print("  WORSE %5.1f -> %5.1f  %s" % (base[k]["score"], r["score"], k))
    if a.json:
        with open(a.json, "w") as f:
            json.dump(res, f, indent=0, sort_keys=True)


if __name__ == "__main__":
    main()
