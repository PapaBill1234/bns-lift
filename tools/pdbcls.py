#!/usr/bin/env python3
"""pdbcls: print classes, typedefs and function types of a server PDB as C++ text.

Usage: tools/pdbcls.py <Server> <name or regex> [...]

  A name without a regex character matches the full type name or typedef name.
  The output gives bases, members (offset, type), methods (access, static, virtual, slot) and enumerators.
The tool reads the TPI stream with the parser of pdb2h.py. It caches the parsed records.
"""
import os
import pickle
import re
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
import pdb2h as P  # noqa: E402
import pdbq  # noqa: E402

ACCESS = {1: "private", 2: "protected", 3: "public"}
MPROP = {0: "", 1: "virtual", 2: "static", 3: "friend", 4: "virtual", 5: "virtual =0", 6: "virtual =0"}


class Db:
    def __init__(self, server):
        cache = os.path.join(pdbq.CACHE, server + ".tpi.pkl")
        pdb = os.path.join(pdbq.ida_dir(), server, server + ".pdb")
        if os.path.exists(cache) and os.path.getmtime(cache) > os.path.getmtime(pdb):
            self.recs = pickle.load(open(cache, "rb"))
        else:
            self.recs = {k: dict(v) for k, v in P.Tpi(P.Msf(pdb)).recs.items()}
            for r in self.recs.values():
                for key in ("fields", "methods"):
                    if r.get(key):
                        r[key] = [dict(x) for x in r[key]]
            pickle.dump(self.recs, open(cache, "wb"))
        self.defs = {}
        for ti, r in self.recs.items():
            if r["leaf"] in P.UDT_LEAVES + (P.LF_ENUM,) and not r.get("prop", 0) & P.PROP_FWDREF:
                self.defs[r["name"]] = ti

    def ty(self, ti, name=""):
        """C++ text of type ti. 'name' is the declared name (for arrays and function pointers)."""
        if ti < 0x1000:
            kind, mode = ti & 0xFF, (ti >> 8) & 0xF
            p = P.PRIM.get(kind)
            t = (p[0] if p else "prim_0x%x" % kind) + (" *" if mode else "")
            return (t + " " + name).strip()
        r = self.recs.get(ti)
        if r is None:
            return ("?0x%x " % ti + name).strip()
        leaf = r["leaf"]
        if leaf in P.UDT_LEAVES + (P.LF_ENUM,):
            return (r["name"] + " " + name).strip()
        if leaf == P.LF_MODIFIER:
            m = ("const " if r["mod"] & 1 else "") + ("volatile " if r["mod"] & 2 else "")
            return (self.ty(r["utype"]) + " " + m + name).strip()
        if leaf == P.LF_POINTER:
            sym = {0: "*", 1: "&", 2: "::*", 3: "::*", 4: "&&"}.get(r["mode"], "*")
            q = sym + (" const" if r.get("const") else "")
            u = self.recs.get(r["utype"]) if r["utype"] >= 0x1000 else None
            if u and u["leaf"] in (P.LF_PROCEDURE, P.LF_MFUNCTION):
                cls = self.ty(u["cls"]) + "::" if u["leaf"] == P.LF_MFUNCTION else ""
                return "%s (%s%s %s)(%s)" % (self.ty(u["rvtype"]), cls, q, name, self.args(u["arglist"]))
            if u and u["leaf"] == P.LF_ARRAY:
                return self.ty(r["utype"], "(%s %s)" % (q, name))
            return ("%s %s %s" % (self.ty(r["utype"]), q, name)).strip()
        if leaf == P.LF_ARRAY:
            e = self.recs.get(r["etype"]) if r["etype"] >= 0x1000 else None
            es = self.size(r["etype"])
            n = r["size"] // es if es else 0
            return self.ty(r["etype"], "%s[%d]" % (name, n))
        if leaf == P.LF_PROCEDURE:
            return "%s %s(%s)" % (self.ty(r["rvtype"]), name, self.args(r["arglist"]))
        if leaf == P.LF_MFUNCTION:
            th = self.recs.get(r["this"]) if r["this"] >= 0x1000 else None
            c = ""
            if th and th["leaf"] == P.LF_POINTER and th["utype"] >= 0x1000:
                u = self.recs.get(th["utype"])
                if u and u["leaf"] == P.LF_MODIFIER and u["mod"] & 1:
                    c = " const"
            return "%s %s(%s)%s" % (self.ty(r["rvtype"]), name, self.args(r["arglist"]), c)
        if leaf == P.LF_BITFIELD:
            return "%s %s : %d /* bit %d */" % (self.ty(r["utype"]), name, r["length"], r["position"])
        return ("leaf_0x%x " % leaf + name).strip()

    def args(self, ti):
        al = self.recs.get(ti)
        a = al.get("args") if al else None
        if not a or a == [3]:
            return ""
        return ", ".join("..." if x == 0 else self.ty(x) for x in a)

    def size(self, ti):
        if ti < 0x1000:
            if (ti >> 8) & 0xF:
                return 8
            p = P.PRIM.get(ti & 0xFF)
            return p[1] if p else 0
        r = self.recs.get(ti)
        if r is None:
            return 0
        leaf = r["leaf"]
        if leaf in P.UDT_LEAVES:
            if r.get("prop", 0) & P.PROP_FWDREF:
                d = self.defs.get(r["name"])
                return self.recs[d]["size"] if d else 0
            return r["size"]
        if leaf == P.LF_ENUM:
            return self.size(r["utype"])
        if leaf == P.LF_MODIFIER:
            return self.size(r["utype"])
        if leaf == P.LF_POINTER:
            return 8
        if leaf == P.LF_ARRAY:
            return r["size"]
        return 0

    def fields(self, fl):
        r = self.recs.get(fl)
        for f in (r.get("fields") or []) if r else []:
            if f["leaf"] == P.LF_INDEX:
                yield from self.fields(f["type"])
            else:
                yield f

    def method_line(self, name, attr, mti, vb):
        acc = ACCESS.get(attr & 3, "")
        mp = MPROP.get((attr >> 2) & 7, "")
        pure = mp.endswith("=0")
        pre = mp.replace(" =0", "")
        s = "%s: %s%s%s" % (acc, pre + " " if pre else "", self.ty(mti, name), " = 0" if pure else "")
        if vb is not None:
            s += "  // slot %d" % (vb // 8)
        if attr & 0x100:
            s += "  // compiler-generated"
        return s

    def show(self, ti):
        r = self.recs[ti]
        leaf = r["leaf"]
        if leaf == P.LF_ENUM:
            print("enum %s : %s  // 0x%X" % (r["name"], self.ty(r["utype"]), ti))
            for f in self.fields(r["field"]):
                print("    %s = %d" % (f["name"], f["value"]))
            return
        kw = {P.LF_CLASS: "class", P.LF_STRUCTURE: "struct", P.LF_UNION: "union"}.get(leaf, "struct")
        print("%s %s  // 0x%X, size 0x%X" % (kw, r["name"], ti, r["size"]))
        for f in self.fields(r["field"]):
            lf = f["leaf"]
            if lf == P.LF_BCLASS:
                print("    base %s %s  // +%d" % (ACCESS.get(f["attr"] & 3, ""), self.ty(f["type"]), f["offset"]))
            elif lf in (P.LF_VBCLASS, P.LF_IVBCLASS):
                print("    virtual base %s" % self.ty(f["type"]))
            elif lf == P.LF_VFUNCTAB:
                print("    vfptr")
            elif lf == P.LF_MEMBER:
                print("    %s: %s;  // +%d (0x%X)" % (ACCESS.get(f["attr"] & 3, ""), self.ty(f["type"], f["name"]),
                                                    f["offset"], f["offset"]))
            elif lf == P.LF_STMEMBER:
                print("    %s: static %s;" % (ACCESS.get(f["attr"] & 3, ""), self.ty(f["type"], f["name"])))
            elif lf == P.LF_ONEMETHOD:
                print("    " + self.method_line(f["name"], f["attr"], f["type"], f.get("vbaseoff")))
            elif lf == P.LF_METHOD:
                ml = self.recs.get(f["mlist"])
                for m in (ml.get("methods") or []) if ml else []:
                    print("    " + self.method_line(f["name"], m["attr"], m["type"], m.get("vbaseoff")))
            elif lf in (P.LF_NESTTYPE, P.LF_NESTTYPEEX):
                print("    nested %s = %s" % (f["name"], self.ty(f["type"])))


def main():
    if len(sys.argv) < 3:
        sys.exit(__doc__)
    server = sys.argv[1]
    db = Db(server)
    udts = None
    for pat in sys.argv[2:]:
        rx = pdbq.rx(pat)
        hit = False
        for name, ti in sorted(db.defs.items()):
            if rx.search(name):
                db.show(ti)
                hit = True
        if udts is None:
            udts = {}
            for kind in ("globals", "syms"):
                lines = pdbq.dump(server, kind)
                for i, l in enumerate(lines):
                    m = pdbq.REC.match(l)
                    if m and m.group(2) == "S_UDT":
                        t = re.search(r"original type = (0x[0-9A-F]+)", lines[i + 1])
                        if t:
                            udts[m.group(3)] = int(t.group(1), 16)
        for name, ti in sorted(udts.items()):
            if rx.search(name) and name not in db.defs:
                print("typedef %s;  // 0x%X" % (db.ty(ti, name), ti))
                hit = True
        if not hit:
            print("%s: not in the %s PDB types" % (pat, server))


if __name__ == "__main__":
    main()
