#!/usr/bin/env python3
"""pdbq: look up names, types, locals and source lines in a server PDB.

Usage: tools/pdbq.py <Server> <command> <pattern> [...]

  data  <regex>   static and global data (S_LDATA32, S_GDATA32, S_CONSTANT): name, type, address, module
  fn    <regex>   functions: name, address, size, module, type, parameters and locals
  type  <regex>   classes, structs, unions, enums: members with offsets, enumerators
  enumv <regex>   enumerator name -> enum type and value
  udt   <regex>   typedef names (S_UDT)
  line  <hex rva> source file and line of an address (rva = address - image base)
  src   <regex>   source files of a module (use it to find the file of a module)

The tool reads text dumps from llvm-pdbutil. It keeps them in ~/.cache/bns-lift/pdbq/.
The PDB path is ../ida/lift/<Server>/<Server>.pdb (or $LIFT_IDA_DIR/<Server>/<Server>.pdb).
A regex matches the full name unless it contains a regex character.
"""
import os
import re
import struct
import subprocess
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
CACHE = os.path.expanduser("~/.cache/bns-lift/pdbq")


def ida_dir():
    d = os.environ.get("LIFT_IDA_DIR")
    if d:
        return d
    p = HERE
    for _ in range(5):
        p = os.path.dirname(p)
        c = os.path.join(p, "ida", "lift")
        if os.path.isdir(c):
            return c
    sys.exit("ida/lift not found; set LIFT_IDA_DIR")


def dump(server, kind):
    os.makedirs(CACHE, exist_ok=True)
    pdb = os.path.join(ida_dir(), server, server + ".pdb")
    out = os.path.join(CACHE, "%s.%s.txt" % (server, kind))
    if not os.path.exists(out) or os.path.getmtime(out) < os.path.getmtime(pdb):
        flag = {"types": "-types", "syms": "-symbols", "globals": "-globals", "lines": "-l"}[kind]
        with open(out + ".tmp", "w") as f:
            subprocess.run(["llvm-pdbutil", "dump", flag, pdb], stdout=f, stderr=subprocess.DEVNULL, check=True)
        os.rename(out + ".tmp", out)
    with open(out, errors="replace") as f:
        return f.read().split("\n")


def sections(server):
    """Section virtual addresses of the exe (index 1..n)."""
    exe = os.path.join(ida_dir(), server, server + ".exe")
    with open(exe, "rb") as f:
        d = f.read(0x1000)
    pe = struct.unpack_from("<I", d, 0x3C)[0]
    n = struct.unpack_from("<H", d, pe + 6)[0]
    opt = struct.unpack_from("<H", d, pe + 20)[0]
    base = pe + 24 + opt
    return [0] + [struct.unpack_from("<I", d, base + 40 * i + 12)[0] for i in range(n)]


_IMG = {}


def image(server):
    """(data, [(va, vsize, raw offset, raw size)], image base) of the exe."""
    if server not in _IMG:
        with open(os.path.join(ida_dir(), server, server + ".exe"), "rb") as f:
            d = f.read()
        pe = struct.unpack_from("<I", d, 0x3C)[0]
        n = struct.unpack_from("<H", d, pe + 6)[0]
        opt = struct.unpack_from("<H", d, pe + 20)[0]
        base = struct.unpack_from("<Q", d, pe + 24 + 24)[0]
        t = pe + 24 + opt
        secs = [struct.unpack_from("<IIII", d, t + 40 * i + 8) for i in range(n)]
        _IMG[server] = (d, [(va, vs, ro, rs) for vs, va, rs, ro in secs], base)
    return _IMG[server]


def read(server, rva, size):
    d, secs, _b = image(server)
    for va, vs, ro, rs in secs:
        if va <= rva < va + max(vs, rs):
            o = rva - va
            return d[ro + o:ro + o + size] if o < rs else b"\0" * size
    return b""


def value(server, rva, ty):
    """Text of the initial value of a datum, for simple types."""
    _d, _s, base = image(server)

    def text(a, wide):
        raw = read(server, a - base, 400)
        if wide:
            e = next((i for i in range(0, len(raw) - 1, 2) if raw[i:i + 2] == b"\0\0"), len(raw))
            return 'L"%s"' % raw[:e].decode("utf-16-le", "replace")
        return '"%s"' % raw.split(b"\0")[0].decode("latin-1")
    try:
        if "wchar_t*" in ty or "char*" in ty:
            a = struct.unpack("<Q", read(server, rva, 8))[0]
            return "= " + (text(a, "wchar_t" in ty) if a else "nullptr")
        if re.search(r"\((const )?(unsigned )?(int|long|short)\)", ty):
            return "= %d" % struct.unpack("<i", read(server, rva, 4))[0]
        if re.search(r"\((const )?(unsigned )?__int64\)", ty):
            return "= %d" % struct.unpack("<q", read(server, rva, 8))[0]
        if re.search(r"\((const )?bool\)", ty):
            return "= %d" % read(server, rva, 1)[0]
    except (struct.error, IndexError):
        pass
    return ""


def rx(p):
    if re.search(r"[.*+?\[\]()|^$\\]", p):
        return re.compile(p)
    return re.compile("^(.*::)?" + re.escape(p) + "$")


REC = re.compile(r"^\s*(\d+) \| (S_\w+) \[size = \d+\] `(.*)`\s*$")
MOD = re.compile(r"^\s*Mod (\d+) \| `(.*)`:")
ADDR = re.compile(r"addr = (\d+):(\d+)")


def sym_records(server):
    """Yield (module, kind, name, [detail lines])."""
    mod, cur = "", None
    for l in dump(server, "syms"):
        m = MOD.match(l)
        if m:
            if cur:
                yield cur
                cur = None
            mod = m.group(2).rsplit("\\", 1)[-1]
            continue
        m = REC.match(l)
        if m:
            if cur:
                yield cur
            cur = (mod, m.group(2), m.group(3), [])
        elif cur and l.strip():
            cur[3].append(l.strip())
    if cur:
        yield cur


def rva_of(secs, text):
    m = ADDR.search(text)
    if not m:
        return None
    s, o = int(m.group(1)), int(m.group(2))
    return secs[s] + o if 0 < s < len(secs) else None


def cmd_data(server, pat):
    r, secs, seen = rx(pat), sections(server), set()
    for mod, kind, name, det in sym_records(server):
        if kind in ("S_LDATA32", "S_GDATA32", "S_CONSTANT", "S_LTHREAD32") and r.search(name):
            d = " ".join(det)
            a = rva_of(secs, d)
            d = re.sub(r", addr = [\d:]+", "", d)
            row = "%s  %s  %s %s  [%s]" % (name, d, "rva 0x%X" % a if a is not None else "",
                                           value(server, a, d) if a is not None else "", mod)
            if row not in seen:
                seen.add(row)
                print(row)
    # constants and globals that are only in the global stream
    for i, l in enumerate(g := dump(server, "globals")):
        m = REC.match(l)
        if m and m.group(2) in ("S_CONSTANT", "S_GDATA32", "S_LDATA32") and r.search(m.group(3)):
            d = g[i + 1].strip()
            a = rva_of(secs, d)
            row = "%s  %s  %s  [globals]" % (m.group(3), re.sub(r", addr = [\d:]+", "", d),
                                             "rva 0x%X" % a if a is not None else "")
            key = row.rsplit("[", 1)[0]
            if not any(s.startswith(key) for s in seen):
                seen.add(row)
                print(row)


def cmd_fn(server, pat):
    r, secs = rx(pat), sections(server)
    show = False
    depth = 0
    for mod, kind, name, det in sym_records(server):
        if kind in ("S_GPROC32", "S_LPROC32"):
            show = bool(r.search(name))
            if show:
                d = " ".join(det)
                a = rva_of(secs, d)
                size = re.search(r"code size = (\d+)", d)
                ty = re.search(r"type = `([^`]*)`", d) or re.search(r"type = (\S+ \([^)]*\)|\S+)", d)
                print("%s  rva 0x%X  size %s  [%s]%s\n    type %s" % (
                    name, a or 0, size.group(1) if size else "?", mod,
                    " static" if kind == "S_LPROC32" else "", ty.group(1) if ty else "?"))
        elif show and kind in ("S_REGREL32", "S_LOCAL", "S_BPREL32", "S_REGISTER", "S_LDATA32", "S_CONSTANT", "S_UDT"):
            d = " ".join(det)
            a = rva_of(secs, d) if kind == "S_LDATA32" else None
            print("    %-10s %s  %s%s" % (kind[2:].lower(), name, re.sub(r", addr = [\d:]+", "", d),
                                          "  rva 0x%X %s" % (a, value(server, a, d)) if a is not None else ""))


TREC = re.compile(r"^\s*(0x[0-9A-F]+) \| (LF_\w+) \[size = \d+\](?: `(.*)`)?\s*$")


def type_records(server):
    recs, cur = {}, None
    for l in dump(server, "types"):
        m = TREC.match(l)
        if m:
            cur = [m.group(2), m.group(3) or "", []]
            recs[int(m.group(1), 16)] = cur
        elif cur is not None and l.strip():
            cur[2].append(l.strip())
    return recs


def cmd_type(server, pat):
    r, recs = rx(pat), type_records(server)
    for ti in sorted(recs):
        leaf, name, det = recs[ti]
        if leaf not in ("LF_CLASS", "LF_STRUCTURE", "LF_UNION", "LF_ENUM") or not r.search(name):
            continue
        d = " ".join(det)
        if "forward ref" in d:
            continue
        size = re.search(r"sizeof (\d+)", d)
        print("%s %s  (0x%X)%s" % (leaf[3:].lower(), name, ti, "  size 0x%X" % int(size.group(1)) if size else ""))
        fl = re.search(r"field list: (0x[0-9A-F]+)", d)
        if not fl:
            continue
        todo = [int(fl.group(1), 16)]
        while todo:
            f = recs.get(todo.pop())
            if not f:
                continue
            lines = f[2]
            for i, x in enumerate(lines):
                if x.startswith("- LF_INDEX"):
                    m = re.search(r"0x[0-9A-F]+", x)
                    if m:
                        todo.append(int(m.group(0), 16))
                elif x.startswith("- LF_ENUMERATE"):
                    print("    " + x[16:-1])
                elif x.startswith(("- LF_MEMBER", "- LF_BCLASS", "- LF_STMEMBER", "- LF_NESTTYPE", "- LF_VFUNCTAB",
                                   "- LF_ONEMETHOD", "- LF_METHOD")):
                    extra = lines[i + 1] if i + 1 < len(lines) and not lines[i + 1].startswith("- ") else ""
                    print("    %s  %s" % (x[5:], extra))


def cmd_enumv(server, pat):
    r, recs = rx(pat), type_records(server)
    owner = {}
    for ti, (leaf, name, det) in recs.items():
        if leaf == "LF_ENUM":
            m = re.search(r"field list: (0x[0-9A-F]+)", " ".join(det))
            if m:
                owner.setdefault(int(m.group(1), 16), name)
    for ti in sorted(recs):
        leaf, name, det = recs[ti]
        if leaf != "LF_FIELDLIST":
            continue
        for x in det:
            if x.startswith("- LF_ENUMERATE"):
                m = re.match(r"- LF_ENUMERATE \[(\S+) = (.*)\]", x)
                if m and r.search(m.group(1)):
                    print("%s = %s  in enum %s" % (m.group(1), m.group(2), owner.get(ti, "?")))


def cmd_udt(server, pat):
    r, seen = rx(pat), set()
    for src in ("globals", "syms"):
        g = dump(server, src)
        for i, l in enumerate(g):
            m = REC.match(l)
            if m and m.group(2) == "S_UDT" and r.search(m.group(3)):
                row = "%s  %s" % (m.group(3), g[i + 1].strip())
                if row not in seen:
                    seen.add(row)
                    print(row)


def cmd_line(server, pat):
    rva, secs = int(pat, 16), sections(server)
    mod = fil = None
    best = None
    seg = base = 0
    for l in dump(server, "lines"):
        m = MOD.match(l)
        if m:
            mod = m.group(2).rsplit("\\", 1)[-1]
            continue
        m = re.match(r"^(\S.*) \(MD5: ", l)
        if m:
            fil = m.group(1)
            continue
        m = re.match(r"^\s+(\d+):([0-9A-F]+)-([0-9A-F]+), line/addr", l)
        if m:
            seg, base = int(m.group(1)), int(m.group(2), 16)
            continue
        if seg and seg < len(secs):
            for ln, off in re.findall(r"(\d+) ([0-9A-F]{8})", l):
                a = secs[seg] + int(off, 16)
                if a <= rva and (best is None or a > best[0] or (a == best[0])):
                    if best is None or a >= best[0]:
                        best = (a, fil, int(ln), mod)
    if best:
        print("0x%X: %s:%d  [%s]  (entry at 0x%X)" % (rva, best[1], best[2], best[3], best[0]))


def cmd_src(server, pat):
    r = re.compile(pat, re.I)
    mod = None
    for l in dump(server, "lines"):
        m = MOD.match(l)
        if m:
            mod = m.group(2).rsplit("\\", 1)[-1]
            continue
        m = re.match(r"^(\S.*) \(MD5: ", l)
        if m and (r.search(mod or "") or r.search(m.group(1))):
            print("%s  %s" % (mod, m.group(1)))


def main():
    if len(sys.argv) < 4:
        sys.exit(__doc__)
    server, cmd = sys.argv[1], sys.argv[2]
    f = globals().get("cmd_" + cmd)
    if f is None:
        sys.exit(__doc__)
    for p in sys.argv[3:]:
        f(server, p)


if __name__ == "__main__":
    main()
