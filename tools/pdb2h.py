#!/usr/bin/env python3
"""pdb2h: write include/pdb/<Server>/types.h from a server PDB.

Usage: tools/pdb2h.py <file.pdb> <Server> [--out include/pdb]

The script reads the PDB file directly (MSF 7.00, TPI stream, DBI global symbols).
It does not need llvm-pdbutil. Leaf and symbol numbers come from cvinfo.h.

Output:
  - forward declarations of all emitted types;
  - enums, structs, classes and unions in dependency order;
  - base classes, data members, virtual methods in vtable order;
  - static_assert(sizeof) and static_assert(offsetof) for each type and member;
  - extern declarations of global data (S_GDATA32).
Nested types go inside their outer class. Members of anonymous structs and unions
(the PDB lists them flat) go back into anonymous unions and structs.
A Windows SDK or CRT struct that a member uses by value comes from the PDB too,
with its PDB name (_GUID, _RTL_CRITICAL_SECTION). The header includes no SDK header.
Skipped: CRT and STL internals, templates that are not mapped.
A member that has a type which the script cannot write becomes a
byte array with the same offset and size (comment: original type name).
std:: types map to include/vs2010/ (string, vector, list, map, set, deque, queue, pair).
"""
import argparse
import os
import re
import struct
import sys

# ---------------------------------------------------------------------------
# PDB reader
# ---------------------------------------------------------------------------
MSF_MAGIC = b"Microsoft C/C++ MSF 7.00\r\n\x1aDS\x00\x00\x00"

LF_VTSHAPE = 0x000A
LF_MODIFIER = 0x1001
LF_POINTER = 0x1002
LF_PROCEDURE = 0x1008
LF_MFUNCTION = 0x1009
LF_ARGLIST = 0x1201
LF_FIELDLIST = 0x1203
LF_BITFIELD = 0x1205
LF_METHODLIST = 0x1206
LF_BCLASS = 0x1400
LF_VBCLASS = 0x1401
LF_IVBCLASS = 0x1402
LF_INDEX = 0x1404
LF_VFUNCTAB = 0x1409
LF_ENUMERATE = 0x1502
LF_ARRAY = 0x1503
LF_CLASS = 0x1504
LF_STRUCTURE = 0x1505
LF_UNION = 0x1506
LF_ENUM = 0x1507
LF_MEMBER = 0x150D
LF_STMEMBER = 0x150E
LF_METHOD = 0x150F
LF_NESTTYPE = 0x1510
LF_ONEMETHOD = 0x1511
LF_NESTTYPEEX = 0x1512
LF_INTERFACE = 0x1519

S_CONSTANT = 0x1107
S_UDT = 0x1108
S_LDATA32 = 0x110C
S_GDATA32 = 0x110D
S_LTHREAD32 = 0x1112
S_GTHREAD32 = 0x1113

PROP_ISNESTED = 0x08
PROP_FWDREF = 0x80
PROP_HASUNIQUENAME = 0x200

MP_VANILLA, MP_VIRTUAL, MP_STATIC, MP_FRIEND, MP_INTRO, MP_PUREVIRT, MP_PUREINTRO = range(7)

UDT_LEAVES = (LF_CLASS, LF_STRUCTURE, LF_INTERFACE, LF_UNION)


class Msf:
    def __init__(self, path):
        with open(path, "rb") as f:
            self.data = f.read()
        if not self.data.startswith(MSF_MAGIC):
            raise ValueError("not a PDB 7.00 file: %s" % path)
        (self.block_size, _fpm, self.num_blocks, dir_bytes, _u,
         block_map_addr) = struct.unpack_from("<6I", self.data, 32)
        nb = (dir_bytes + self.block_size - 1) // self.block_size
        dir_blocks = struct.unpack_from("<%dI" % nb, self.data, block_map_addr * self.block_size)
        d = b"".join(self._block(b) for b in dir_blocks)[:dir_bytes]
        n = struct.unpack_from("<I", d, 0)[0]
        sizes = struct.unpack_from("<%dI" % n, d, 4)
        pos = 4 + 4 * n
        self.streams = []
        for s in sizes:
            if s == 0xFFFFFFFF:
                self.streams.append(None)
                continue
            cnt = (s + self.block_size - 1) // self.block_size
            blocks = struct.unpack_from("<%dI" % cnt, d, pos)
            pos += 4 * cnt
            self.streams.append((s, blocks))

    def _block(self, i):
        return self.data[i * self.block_size:(i + 1) * self.block_size]

    def stream(self, i):
        if i >= len(self.streams) or self.streams[i] is None:
            return b""
        size, blocks = self.streams[i]
        return b"".join(self._block(b) for b in blocks)[:size]


def numeric(buf, pos):
    """Read a CodeView numeric leaf. Return (value, new pos)."""
    v = struct.unpack_from("<H", buf, pos)[0]
    pos += 2
    if v < 0x8000:
        return v, pos
    fmt = {0x8000: "<b", 0x8001: "<h", 0x8002: "<H", 0x8003: "<i", 0x8004: "<I",
           0x8009: "<q", 0x800A: "<Q"}.get(v)
    if fmt is None:
        raise ValueError("numeric leaf 0x%x" % v)
    r = struct.unpack_from(fmt, buf, pos)[0]
    return r, pos + struct.calcsize(fmt)


def cstr(buf, pos):
    e = buf.index(b"\x00", pos)
    return buf[pos:e].decode("utf-8", "replace"), e + 1


class Rec(dict):
    """One type record. Keys depend on the leaf. 'leaf' is always set."""
    __getattr__ = dict.get

    def __setattr__(self, k, v):
        self[k] = v


def _parse_fieldlist(buf):
    out = []
    pos = 0
    n = len(buf)
    while pos < n:
        b = buf[pos]
        if b >= 0xF0:
            pos += b & 0x0F
            continue
        leaf = struct.unpack_from("<H", buf, pos)[0]
        pos += 2
        r = Rec(leaf=leaf)
        if leaf == LF_BCLASS:
            r.attr, r.type = struct.unpack_from("<HI", buf, pos)
            r.offset, pos = numeric(buf, pos + 6)
        elif leaf in (LF_VBCLASS, LF_IVBCLASS):
            r.attr, r.type, r.vbptr = struct.unpack_from("<HII", buf, pos)
            r.vbpoff, pos = numeric(buf, pos + 10)
            r.vboff, pos = numeric(buf, pos)
        elif leaf == LF_MEMBER:
            r.attr, r.type = struct.unpack_from("<HI", buf, pos)
            r.offset, pos = numeric(buf, pos + 6)
            r.name, pos = cstr(buf, pos)
        elif leaf == LF_STMEMBER:
            r.attr, r.type = struct.unpack_from("<HI", buf, pos)
            r.name, pos = cstr(buf, pos + 6)
        elif leaf == LF_METHOD:
            r.count, r.mlist = struct.unpack_from("<HI", buf, pos)
            r.name, pos = cstr(buf, pos + 6)
        elif leaf == LF_ONEMETHOD:
            r.attr, r.type = struct.unpack_from("<HI", buf, pos)
            pos += 6
            mp = (r.attr >> 2) & 7
            r.vbaseoff = None
            if mp in (MP_INTRO, MP_PUREINTRO):
                r.vbaseoff = struct.unpack_from("<I", buf, pos)[0]
                pos += 4
            r.name, pos = cstr(buf, pos)
        elif leaf == LF_ENUMERATE:
            r.attr = struct.unpack_from("<H", buf, pos)[0]
            r.value, pos = numeric(buf, pos + 2)
            r.name, pos = cstr(buf, pos)
        elif leaf in (LF_NESTTYPE, LF_NESTTYPEEX):
            r.attr, r.type = struct.unpack_from("<HI", buf, pos)
            r.name, pos = cstr(buf, pos + 6)
        elif leaf in (LF_VFUNCTAB, LF_INDEX):
            r.type = struct.unpack_from("<I", buf, pos + 2)[0]
            pos += 6
        else:
            raise ValueError("field leaf 0x%x" % leaf)
        out.append(r)
    return out


def _parse_type(leaf, buf):
    r = Rec(leaf=leaf)
    if leaf in (LF_CLASS, LF_STRUCTURE, LF_INTERFACE):
        r.count, r.prop, r.field, r.derived, r.vshape = struct.unpack_from("<HHIII", buf, 0)
        r.size, pos = numeric(buf, 16)
        r.name, pos = cstr(buf, pos)
        if r.prop & PROP_HASUNIQUENAME and pos < len(buf):
            r.uname, pos = cstr(buf, pos)
    elif leaf == LF_UNION:
        r.count, r.prop, r.field = struct.unpack_from("<HHI", buf, 0)
        r.size, pos = numeric(buf, 8)
        r.name, pos = cstr(buf, pos)
        if r.prop & PROP_HASUNIQUENAME and pos < len(buf):
            r.uname, pos = cstr(buf, pos)
    elif leaf == LF_ENUM:
        r.count, r.prop, r.utype, r.field = struct.unpack_from("<HHII", buf, 0)
        r.name, pos = cstr(buf, 12)
        if r.prop & PROP_HASUNIQUENAME and pos < len(buf):
            r.uname, pos = cstr(buf, pos)
    elif leaf == LF_POINTER:
        r.utype, r.attr = struct.unpack_from("<II", buf, 0)
        r.mode = (r.attr >> 5) & 7
        r.const = bool(r.attr & 0x400)
        r.volatile = bool(r.attr & 0x200)
        if r.mode in (2, 3):
            r.cls, r.pmtype = struct.unpack_from("<IH", buf, 8)
    elif leaf == LF_MODIFIER:
        r.utype, r.mod = struct.unpack_from("<IH", buf, 0)
    elif leaf == LF_ARRAY:
        r.etype, r.itype = struct.unpack_from("<II", buf, 0)
        r.size, pos = numeric(buf, 8)
    elif leaf == LF_BITFIELD:
        r.utype, r.length, r.position = struct.unpack_from("<IBB", buf, 0)
    elif leaf == LF_PROCEDURE:
        r.rvtype, r.cc, r.fattr, r.nparm, r.arglist = struct.unpack_from("<IBBHI", buf, 0)
    elif leaf == LF_MFUNCTION:
        (r.rvtype, r.cls, r.this, r.cc, r.fattr, r.nparm, r.arglist,
         r.thisadjust) = struct.unpack_from("<IIIBBHIi", buf, 0)
    elif leaf == LF_ARGLIST:
        n = struct.unpack_from("<I", buf, 0)[0]
        r.args = list(struct.unpack_from("<%dI" % n, buf, 4))
    elif leaf == LF_FIELDLIST:
        r.fields = _parse_fieldlist(buf)
    elif leaf == LF_METHODLIST:
        ms = []
        pos = 0
        while pos + 8 <= len(buf):
            attr, _pad, t = struct.unpack_from("<HHI", buf, pos)
            pos += 8
            vb = None
            if ((attr >> 2) & 7) in (MP_INTRO, MP_PUREINTRO):
                vb = struct.unpack_from("<I", buf, pos)[0]
                pos += 4
            ms.append(Rec(attr=attr, type=t, vbaseoff=vb))
        r.methods = ms
    elif leaf == LF_VTSHAPE:
        r.count = struct.unpack_from("<H", buf, 0)[0]
    return r


class Tpi:
    def __init__(self, msf, stream_index=2):
        s = msf.stream(stream_index)
        (self.version, hdr_size, self.ti_begin, self.ti_end,
         rec_bytes) = struct.unpack_from("<IIIII", s, 0)
        self.recs = {}
        pos = hdr_size
        end = hdr_size + rec_bytes
        ti = self.ti_begin
        while pos < end:
            ln, leaf = struct.unpack_from("<HH", s, pos)
            body = s[pos + 4:pos + 2 + ln]
            try:
                self.recs[ti] = _parse_type(leaf, body)
            except (ValueError, struct.error) as e:
                self.recs[ti] = Rec(leaf=leaf, error=str(e))
            pos += 2 + ln
            ti += 1

    def get(self, ti):
        return self.recs.get(ti)


class Dbi:
    def __init__(self, msf):
        s = msf.stream(3)
        (_sig, _ver, _age, self.gsi, _bld, self.psi, _dllv, self.symrec,
         _rbld) = struct.unpack_from("<iIIHHHHHH", s, 0)
        self.msf = msf

    def symbols(self):
        s = self.msf.stream(self.symrec)
        pos = 0
        while pos + 4 <= len(s):
            ln, kind = struct.unpack_from("<HH", s, pos)
            if ln < 2:
                break
            yield kind, s[pos + 4:pos + 2 + ln]
            pos += 2 + ln

    def data_symbols(self):
        for kind, b in self.symbols():
            if kind in (S_GDATA32, S_LDATA32, S_GTHREAD32, S_LTHREAD32):
                t, off, seg = struct.unpack_from("<IIH", b, 0)
                name, _ = cstr(b, 10)
                yield dict(kind=kind, type=t, offset=off, seg=seg, name=name)


# ---------------------------------------------------------------------------
# Header writer
# ---------------------------------------------------------------------------
# Primitive types (ti < 0x1000): low byte = kind, bits 8..11 = pointer mode.
PRIM = {
    0x03: ("void", 0), 0x08: ("long", 4),
    0x10: ("char", 1), 0x20: ("unsigned char", 1), 0x68: ("signed char", 1),
    0x69: ("unsigned char", 1), 0x70: ("char", 1), 0x71: ("wchar_t", 2),
    0x7A: ("char16_t", 2), 0x7B: ("char32_t", 4),
    0x11: ("short", 2), 0x21: ("unsigned short", 2), 0x72: ("short", 2),
    0x73: ("unsigned short", 2),
    0x12: ("long", 4), 0x22: ("unsigned long", 4), 0x74: ("int", 4), 0x75: ("unsigned int", 4),
    0x13: ("long long", 8), 0x23: ("unsigned long long", 8), 0x76: ("long long", 8),
    0x77: ("unsigned long long", 8),
    0x40: ("float", 4), 0x41: ("double", 8), 0x42: ("long double", 8),
    0x30: ("bool", 1), 0x31: ("bool", 2), 0x32: ("bool", 4), 0x33: ("bool", 8),
}

# Type names in PDB strings (template arguments).
NAME_PRIM = {
    "void": "void", "bool": "bool", "char": "char", "signed char": "signed char",
    "unsigned char": "unsigned char", "wchar_t": "wchar_t", "short": "short",
    "unsigned short": "unsigned short", "int": "int", "unsigned int": "unsigned int",
    "long": "long", "unsigned long": "unsigned long", "__int64": "long long",
    "unsigned __int64": "unsigned long long", "float": "float", "double": "double",
    "long double": "long double", "__int8": "signed char", "unsigned __int8": "unsigned char",
    "__int16": "short", "unsigned __int16": "unsigned short", "__int32": "int",
    "unsigned __int32": "unsigned int",
}

IDENT = re.compile(r"^[A-Za-z_][A-Za-z0-9_]*$")
SKIP_PREFIX = ("std::", "stdext::", "_", "<", "$", "`", "type_info", "ATL::", "Concurrency::",
               "details::", "vc_attributes::", "__vc_attributes", "_s__", "tag")
# Windows SDK structs. The lift takes them from the SDK headers, not from the PDB.
SKIP_NAMES = set("""
GUID IID CLSID LARGE_INTEGER ULARGE_INTEGER OVERLAPPED SYSTEMTIME FILETIME
CRITICAL_SECTION RTL_CRITICAL_SECTION RTL_CRITICAL_SECTION_DEBUG LIST_ENTRY
SECURITY_ATTRIBUTES WSAData WSADATA sockaddr sockaddr_in in_addr in6_addr
sockaddr_in6 sockaddr_storage WSABUF timeval fd_set hostent linger
lconv tm localeinfo_struct threadlocaleinfostruct threadmbcinfostruct
EXCEPTION_RECORD EXCEPTION_POINTERS CONTEXT M128A XSAVE_FORMAT
_GUID PROCESS_INFORMATION STARTUPINFOA STARTUPINFOW
""".split())
STL_MAP = {"std::basic_string": None, "std::vector": None, "std::map": None,
           "std::multimap": None, "std::set": None, "std::multiset": None,
           "std::deque": None, "std::list": None, "std::queue": None, "std::priority_queue": None,
           "std::pair": None}
VTBL_SKIP = ("__vecDelDtor", "__delDtor", "__local_vftable_ctor_closure")


def valid_name(n):
    return all(IDENT.match(p) for p in n.split("::"))


def split_args(s):
    """Split 'A,B<C,D>,E' at top-level commas."""
    out, depth, cur = [], 0, ""
    for ch in s:
        if ch == "<":
            depth += 1
        elif ch == ">":
            depth -= 1
        if ch == "," and depth == 0:
            out.append(cur.strip())
            cur = ""
        else:
            cur += ch
    if cur.strip():
        out.append(cur.strip())
    return out


def parse_tmpl(s):
    s = s.strip()
    i = s.find("<")
    if i < 0 or not s.endswith(">"):
        return s, None
    return s[:i].strip(), split_args(s[i + 1:-1])


class GenFail(Exception):
    pass


class Gen:
    def __init__(self, pdb_path, server):
        msf = Msf(pdb_path)
        self.tpi = Tpi(msf)
        self.dbi = Dbi(msf)
        self.server = server
        self.defs = {}       # name -> ti of the full definition
        self.kinds = {}      # name -> leaf
        self.emit = {}       # name -> ti, types that the header writes
        self.fwd_extra = set()  # class names that only get a forward declaration
        self.notes = []
        self.children = {}   # outer class name -> nested type names
        self.nested_ok = set()  # nested types that the header writes inside the outer class
        self.extra = set()   # "_" names that a member uses by value
        self.extra_failed = set()
        self.nested_failed = {}
        self.changed = False
        self._index()

    # -- index ------------------------------------------------------------
    def _index(self):
        for ti in sorted(self.tpi.recs):
            r = self.tpi.recs[ti]
            if r.leaf not in UDT_LEAVES + (LF_ENUM,) or r.error:
                continue
            if r.prop & PROP_FWDREF:
                continue
            n = r.name
            old = self.defs.get(n)
            if old is None or (self.tpi.get(old).size == 0 and r.size):
                self.defs[n] = ti
                self.kinds[n] = r.leaf
        for n, ti in self.defs.items():
            r = self.tpi.get(ti)
            if self._want(n, r):
                self.emit[n] = ti
        for n, ti in self.defs.items():
            if "::" not in n or n.startswith(SKIP_PREFIX) or not valid_name(n):
                continue
            outer = n.rsplit("::", 1)[0]
            r = self.tpi.get(ti)
            if outer in self.defs and self.kinds.get(outer) != LF_ENUM and (r.leaf == LF_ENUM or r.size):
                self.children.setdefault(outer, []).append(n)
                self.nested_ok.add(n)

    def top_of(self, n):
        """Top-level class that holds the nested type n, or None."""
        while n in self.nested_ok:
            n = n.rsplit("::", 1)[0]
        return n if n in self.emit else None

    def _want(self, n, r):
        if n.startswith(SKIP_PREFIX) or n in SKIP_NAMES or not valid_name(n):
            return False
        if r.prop & PROP_ISNESTED:
            return False
        if "::" in n:
            outer = n.rsplit("::", 1)[0]
            if outer in self.defs:      # nested type without the nested flag
                return False
        if r.leaf != LF_ENUM and r.size == 0:
            return False
        return True

    def resolve(self, ti):
        """Return the full definition ti for a forward reference ti."""
        r = self.tpi.get(ti)
        if r and r.leaf in UDT_LEAVES + (LF_ENUM,) and r.prop & PROP_FWDREF:
            return self.defs.get(r.name, ti)
        return ti

    # -- type names ---------------------------------------------------------
    def prim(self, ti):
        kind = ti & 0xFF
        mode = (ti >> 8) & 0xF
        p = PRIM.get(kind)
        if p is None:
            return None
        if mode == 0:
            return p[0]
        return p[0] + " *"   # near/64-bit pointer to a primitive

    def tname(self, ti, hard, soft):
        """C++ type for a type index, or None. hard/soft collect dependencies."""
        if ti < 0x1000:
            return self.prim(ti)
        ti = self.resolve(ti)
        r = self.tpi.get(ti)
        if r is None or r.error:
            return None
        if r.leaf == LF_MODIFIER:
            t = self.tname(r.utype, hard, soft)
            if t is None:
                return None
            if r.mod & 1:
                t = t + " const"
            if r.mod & 2:
                t = t + " volatile"
            return t
        if r.leaf == LF_POINTER:
            if r.mode in (2, 3):
                return None          # pointer to member
            u = self.tpi.get(self.resolve(r.utype)) if r.utype >= 0x1000 else None
            if u is not None and u.leaf in (LF_PROCEDURE, LF_MFUNCTION):
                t = "void *"         # function pointer: the lift writes the real type
            elif u is not None and u.leaf in UDT_LEAVES:
                t = self.ptr_target(u.name, soft, hard) or "void"
                t = t + (" &" if r.mode in (1, 4) else " *")
            else:
                t = self.tname(r.utype, set(), soft) if r.utype >= 0x1000 else self.prim(r.utype)
                if t is None:
                    t = "void"
                t = t + (" &" if r.mode in (1, 4) else " *")
            if t.startswith("void") and t.endswith("&"):
                # reference to a type that pdb2h does not write: a pointer has the same ABI
                t = t[:-1] + "*"
            if r.const:
                t += " const"
            return t
        if r.leaf in UDT_LEAVES + (LF_ENUM,):
            n = r.name
            if n in self.emit:
                hard.add(n)
                return n
            if n in self.nested_ok and self.top_of(n):
                hard.add(self.top_of(n))
                hard.add(n)
                return n
            if n.startswith("std::"):
                return self.std_name(n, hard, soft)
            if r.leaf == LF_ENUM:
                return self.tname(r.utype, hard, soft)
            if ((n.startswith("_") or n in SKIP_NAMES) and IDENT.match(n) and r.size
                    and n in self.defs and n not in self.extra and n not in self.extra_failed):
                self.extra.add(n)      # a Windows SDK or CRT struct by value: the next pass writes it
            return None
        return None

    def ptr_target(self, n, soft, hard=None):
        """Name of a class that is used only through a pointer."""
        if n in self.emit:
            soft.add(n)
            return n
        if n in self.nested_ok and self.top_of(n):
            # a nested class has no forward declaration outside its outer class
            if hard is not None:
                hard.add(self.top_of(n))
                hard.add(n)
            else:
                soft.add(self.top_of(n))
            return n
        if n.startswith("std::"):
            return self.std_name(n, set(), soft)
        if (valid_name(n) and not n.startswith(SKIP_PREFIX) and "::" not in n
                and n not in SKIP_NAMES and self.kinds.get(n, LF_STRUCTURE) != LF_ENUM):
            self.fwd_extra.add(n)
            return n
        return None

    def sname(self, s, hard, soft):
        """C++ type for a type name string from a template argument list."""
        s = s.strip()
        if s.endswith("*") or s.endswith("&"):
            inner = s[:-1].strip()
            const = ""
            if inner.endswith(" const"):
                inner, const = inner[:-6].strip(), " const"
            if inner in NAME_PRIM:
                t = NAME_PRIM[inner]
            elif inner.startswith("std::") or "<" not in inner:
                t = self.ptr_target(inner, soft, hard)
            else:
                t = None
            if t is None:
                return None
            return t + const + " " + s[-1]
        if s.endswith(" const"):
            t = self.sname(s[:-6], hard, soft)
            return None if t is None else t + " const"
        if s in NAME_PRIM:
            return NAME_PRIM[s]
        if s.startswith("enum "):
            s = s[5:]
        if s.startswith("std::"):
            return self.std_name(s, hard, soft)
        if s in self.emit:
            hard.add(s)
            return s
        if s in self.nested_ok and self.top_of(s):
            hard.add(self.top_of(s))
            hard.add(s)
            return s
        ti = self.defs.get(s)
        if ti is not None and self.tpi.get(ti).leaf == LF_ENUM:
            return self.tname(self.tpi.get(ti).utype, hard, soft)
        return None

    def std_name(self, n, hard, soft):
        base, args = parse_tmpl(n)
        if args is None:
            return None
        a = args
        if base == "std::basic_string" and len(a) == 3:
            if a[0] == "char":
                return "std::string"
            if a[0] == "wchar_t":
                return "std::wstring"
            return None
        if base == "std::pair" and len(a) == 2:
            x, y = self.sname(a[0], hard, soft), self.sname(a[1], hard, soft)
            return None if None in (x, y) else "std::pair<%s, %s>" % (x, y)
        if base in ("std::vector", "std::deque", "std::list") and len(a) == 2:
            x = self.sname(a[0], hard, soft)
            return None if x is None else "%s<%s>" % (base, x)
        if base in ("std::set", "std::multiset") and len(a) == 3:
            if a[1] != "std::less<%s >" % a[0] and a[1] != "std::less<%s>" % a[0]:
                return None
            x = self.sname(a[0], hard, soft)
            return None if x is None else "%s<%s>" % (base, x)
        if base in ("std::map", "std::multimap") and len(a) == 4:
            if a[2] != "std::less<%s >" % a[0] and a[2] != "std::less<%s>" % a[0]:
                return None
            x, y = self.sname(a[0], hard, soft), self.sname(a[1], hard, soft)
            return None if None in (x, y) else "%s<%s, %s>" % (base, x, y)
        if base == "std::queue" and len(a) == 2:
            cb, ca = parse_tmpl(a[1])
            if cb != "std::deque" or not ca or ca[0] != a[0]:
                return None
            x = self.sname(a[0], hard, soft)
            return None if x is None else "std::queue<%s>" % x
        if base == "std::priority_queue" and len(a) == 3:
            cb, ca = parse_tmpl(a[1])
            if cb != "std::vector" or not ca or ca[0] != a[0]:
                return None
            x = self.sname(a[0], hard, soft)
            if x is None:
                return None
            if a[2] not in ("std::less<%s >" % a[0], "std::less<%s>" % a[0]):
                c = self.sname(a[2], hard, soft)
                return None if c is None else "std::priority_queue<%s, std::vector<%s>, %s>" % (x, x, c)
            return "std::priority_queue<%s>" % x
        return None

    # -- size and alignment -------------------------------------------------
    def size_align(self, ti):
        if ti < 0x1000:
            if (ti >> 8) & 0xF:
                return 8, 8
            p = PRIM.get(ti & 0xFF)
            s = p[1] if p else 1
            return s, max(s, 1)
        ti = self.resolve(ti)
        r = self.tpi.get(ti)
        if r is None:
            return 1, 1
        if r.leaf == LF_MODIFIER:
            return self.size_align(r.utype)
        if r.leaf == LF_POINTER:
            return 8, 8
        if r.leaf == LF_ARRAY:
            _s, a = self.size_align(r.etype)
            return r.size, a
        if r.leaf == LF_ENUM:
            return self.size_align(r.utype)
        if r.leaf == LF_BITFIELD:
            return self.size_align(r.utype)
        if r.leaf in UDT_LEAVES:
            return r.size, self.udt_align(ti)
        return 1, 1

    def udt_align(self, ti, _seen=None):
        r = self.tpi.get(ti)
        if r.name.startswith("std::") and r.size >= 8:
            return 8
        fl = self.tpi.get(r.field)
        a = 1
        if fl is None or not fl.fields:
            return a
        for f in fl.fields:
            if f.leaf in (LF_VFUNCTAB, LF_VBCLASS, LF_IVBCLASS):
                a = max(a, 8)
            elif f.leaf in (LF_MEMBER, LF_BCLASS):
                a = max(a, self.size_align(f.type)[1])
        return min(a, 8)

    # -- array members --------------------------------------------------------
    def decl(self, ti, name, hard, soft):
        """Declaration 'T name[..]' or None."""
        dims = []
        while ti >= 0x1000:
            r = self.tpi.get(self.resolve(ti))
            if r is None or r.leaf != LF_ARRAY:
                break
            es, _a = self.size_align(r.etype)
            if es == 0:
                return None
            dims.append(r.size // es if es else 0)
            ti = r.etype
        t = self.tname(ti, hard, soft)
        if t is None:
            return None
        # each LF_ARRAY size is in bytes; size // element size is the extent of that level
        return "%s %s%s" % (t, name, "".join("[%d]" % e for e in dims))

    def is_bf(self, ti):
        r = self.tpi.get(ti) if ti >= 0x1000 else None
        return r is not None and r.leaf == LF_BITFIELD

    # -- methods --------------------------------------------------------------
    def methods(self, fl):
        """Yield (name, attr, mfunc ti, vbaseoff) for each method in a field list."""
        for f in fl.fields:
            if f.leaf == LF_ONEMETHOD:
                yield f.name, f.attr, f.type, f.vbaseoff
            elif f.leaf == LF_METHOD:
                ml = self.tpi.get(f.mlist)
                for m in (ml.methods if ml and ml.methods else []):
                    yield f.name, m.attr, m.type, m.vbaseoff

    def sig(self, cls, name, mti, hard, soft):
        m = self.tpi.get(mti)
        if m is None or m.leaf != LF_MFUNCTION:
            return None
        short = cls.rsplit("::", 1)[-1]
        args = []
        sh = set()
        al = self.tpi.get(m.arglist)
        for i, a in enumerate(al.args if al and al.args else []):
            if a == 0x0003 and len(al.args) == 1:
                break
            t = self.tname(a, sh, soft)
            if t is None:
                t = "void *"     # ❓ type not written by pdb2h
            args.append(t)
        if name.startswith("~"):
            return "~%s()" % short
        rv = self.tname(m.rvtype, sh, soft) or "void *"
        # a nested type in a signature needs the full outer class; other classes need only a declaration
        for h in sh:
            if h in self.nested_ok:
                hard.add(self.top_of(h))
            elif self.kinds.get(h) == LF_ENUM:
                hard.add(h)
            else:
                soft.add(h)
        if name == short:
            return None
        if not IDENT.match(name):
            return None       # operators: the lift writes them
        return "%s %s(%s)%s" % (rv, name, ", ".join(args),
                                " const" if self.this_const(m) else "")

    def this_const(self, m):
        """True if the 'this' pointer of LF_MFUNCTION m points to a const class."""
        if not m.this or m.this < 0x1000:
            return False
        p = self.tpi.get(m.this)
        if p is None or p.leaf != LF_POINTER or p.utype < 0x1000:
            return False
        u = self.tpi.get(p.utype)
        return u is not None and u.leaf == LF_MODIFIER and bool(u.mod & 1)

    # -- one type ---------------------------------------------------------------
    def body_enum(self, n, r):
        hard, soft = set(), set()
        ut = self.tname(r.utype, hard, soft) or "int"
        fl = self.tpi.get(r.field)
        items = [f for f in (fl.fields if fl and fl.fields else []) if f.leaf == LF_ENUMERATE]
        ns, short = self.split_ns(n)
        clash = any(f.name in self.enum_names.get(ns, set()) for f in items)
        kw = "enum class" if clash else "enum"
        lines = ["%s %s : %s {%s" % (kw, short, ut, "  // ❓ enum class: an enumerator name clashes" if clash else "")]
        usize, _a = self.size_align(r.utype)
        signed = not ut.startswith("unsigned") and ut not in ("bool", "wchar_t")
        for f in items:
            v = f.value
            if signed and usize in (1, 2, 4, 8) and v >= 1 << (8 * usize - 1):
                v -= 1 << (8 * usize)
            lines.append("    %s = %s," % (f.name, ("0x%X" % v) if v >= 0 else str(v)))
            self.enum_names.setdefault(ns, set()).add(f.name)
        lines.append("};")
        return lines

    def body_udt(self, n, r, hard, soft):
        fl = self.tpi.get(r.field)
        fields = fl.fields if fl and fl.fields else []
        ns, short = self.split_ns(n)
        kw = {LF_CLASS: "class", LF_STRUCTURE: "struct", LF_INTERFACE: "struct",
              LF_UNION: "union"}[r.leaf]
        bases = []
        for f in fields:
            if f.leaf == LF_BCLASS:
                b = self.tpi.get(self.resolve(f.type))
                if (b is not None and b.name not in self.emit and (b.name.startswith("_") or b.name in SKIP_NAMES)
                        and IDENT.match(b.name) and b.name in self.defs and b.name not in self.extra_failed):
                    self.extra.add(b.name)
                if b is None or b.name not in self.emit:
                    return None, "base %s" % (b.name if b else "?")
                hard.add(b.name)
                bases.append("public " + b.name)
            elif f.leaf in (LF_VBCLASS, LF_IVBCLASS):
                if f.leaf == LF_VBCLASS:
                    b = self.tpi.get(self.resolve(f.type))
                    if b is None or b.name not in self.emit:
                        return None, "virtual base"
                    hard.add(b.name)
                    bases.append("virtual public " + b.name)
        head = "%s %s%s {" % (kw, short, (" : " + ", ".join(bases)) if bases else "")
        out = [head, "public:"]
        nested_asserts = []
        kids = [c for c in sorted(self.children.get(n, ())) if c in self.nested_ok]
        if kids:
            kkw = {LF_CLASS: "class", LF_STRUCTURE: "struct", LF_INTERFACE: "struct", LF_UNION: "union"}
            kb, kd = {}, {}
            for c in kids:
                cr = self.tpi.get(self.defs[c])
                if cr.leaf == LF_ENUM:
                    kb[c], kd[c] = (self.body_enum(c, cr), []), set()
                    continue
                ch, cs = set(), set()
                cl, ca = self.body_udt(c, cr, ch, cs)
                if cl is None:
                    self.nested_ok.discard(c)
                    self.nested_failed[c] = ca
                    self.changed = True
                    continue
                kb[c], kd[c] = (cl, ca), ch
                hard |= {h for h in ch if h != c}
                soft |= cs
            for c in kb:
                if self.kinds.get(c) != LF_ENUM:
                    out.append("    %s %s;" % (kkw[self.kinds[c]], c.rsplit("::", 1)[1]))
            done = []

            def put(c, stack):
                if c in done or c in stack:
                    return
                for d in sorted(kd[c]):
                    if d in kb and d != c:
                        put(d, stack + [c])
                done.append(c)
                out.extend("    " + l for l in kb[c][0])
                nested_asserts.extend(kb[c][1])
            for c in sorted(kb, key=lambda c: (self.kinds.get(c) != LF_ENUM, c)):
                put(c, [])

        # virtual methods, vtable order
        vt = []
        has_dtor_slot = None
        own_dtor = False
        for mname, attr, mti, vb in self.methods_safe(fields):
            mp = (attr >> 2) & 7
            if mp not in (MP_VIRTUAL, MP_INTRO, MP_PUREVIRT, MP_PUREINTRO):
                continue
            if mname in VTBL_SKIP:
                if vb is not None:
                    has_dtor_slot = vb
                continue
            s = self.sig(n, mname, mti, hard, soft)
            if s is None:
                if vb is None:
                    continue
                # keep the slot: the lift writes the real declaration
                vt.append((vb, "    virtual void _pdb_slot%d();  // ❓ PDB name: %s" % (vb // 8, mname)))
                continue
            if mname.startswith("~"):
                own_dtor = True
            pure = mp in (MP_PUREVIRT, MP_PUREINTRO)
            order = vb if vb is not None else 1 << 30
            vt.append((order, "    virtual %s%s;%s" % (s, " = 0" if pure else "",
                                                       "  // slot %d" % (vb // 8) if vb is not None else "")))
        if has_dtor_slot is not None and not own_dtor:
            vt.append((has_dtor_slot, "    virtual ~%s();  // slot %d" % (short, has_dtor_slot // 8)))
        vt.sort(key=lambda x: x[0])
        if not vt and any(f.leaf == LF_VFUNCTAB for f in fields) and not bases:
            vt.append((0, "    virtual void _pdb_slot0();  // ❓ vfptr without a named virtual"))
        out += [line for _o, line in vt]

        # data members
        members = [f for f in fields if f.leaf == LF_MEMBER]
        asserts = []
        start = 0
        if any(f.leaf == LF_VFUNCTAB for f in fields):
            start = 8             # this class adds the vfptr (also with a base that has no vfptr)
        for f in fields:
            if f.leaf == LF_BCLASS:
                b = self.tpi.get(self.resolve(f.type))
                if not self.is_empty(b):   # an empty base takes no space
                    start = max(start, f.offset + b.size)
        if any(f.leaf in (LF_VBCLASS, LF_IVBCLASS) for f in fields):
            start = None          # vbptr position: no padding check
        is_union = r.leaf == LF_UNION
        self._npad = 0
        try:
            lines, cur, _top = self.render(n, self.group(members, is_union), start, is_union, hard, soft, asserts)
        except GenFail as e:
            return None, str(e)
        out += ["    " + l for l in lines]
        # tail padding
        if cur is not None and not is_union:
            al = self.udt_align(self.defs[n])
            nat = (cur + al - 1) // al * al
            if self.is_empty(r):
                pass                  # an empty class has size 1 and no member
            elif nat < r.size:
                out.append("    char _pdb_tail[0x%X];" % (r.size - cur))
            elif nat > r.size:
                return None, "size 0x%x < natural 0x%x" % (r.size, nat)
        out.append("};")
        asserts.insert(0, "static_assert(sizeof(%s) == 0x%X, \"sizeof %s\");" % (n, r.size, n))
        return out, asserts + nested_asserts

    def anon_decl(self, ti, name, hard, soft):
        """Lines 'struct { ... } name;' for a member that has an unnamed struct or union type."""
        r = self.tpi.get(self.resolve(ti)) if ti >= 0x1000 else None
        if r is None or r.leaf not in UDT_LEAVES or "<unnamed" not in r.name or not r.size:
            return None
        self._anon = getattr(self, "_anon", 0) + 1
        fake = "_pdb_anon%d" % self._anon
        self.defs[fake] = self.resolve(ti)
        npad = self._npad
        try:
            lines, _asserts = self.body_udt(fake, r, hard, soft)
        finally:
            del self.defs[fake]
            self._npad = npad
        if lines is None or any(l.lstrip().startswith("virtual ") for l in lines):
            return None
        kw = "union" if r.leaf == LF_UNION else "struct"
        body = [l for l in lines[1:-1] if l != "public:"]
        return [kw + " {"] + body + ["} %s;" % name]

    # -- data members: the PDB lists the members of anonymous structs and unions flat -----
    def m_end(self, f):
        if self.is_bf(f.type):
            return f.offset + self.size_align(self.tpi.get(f.type).utype)[0]
        return f.offset + self.size_align(f.type)[0]

    def m_align(self, f):
        if self.is_bf(f.type):
            return self.size_align(self.tpi.get(f.type).utype)[1]
        return self.size_align(f.type)[1]

    def group(self, members, is_union):
        """Put flat members back into anonymous unions and structs.
        Node: ("m", member) | ("u", [alternative, ...]); an alternative is a list of nodes."""
        def both_bf(k):
            return self.is_bf(members[k].type) and self.is_bf(members[k - 1].type)

        def alts(i, splits, e):
            b = [i] + splits + [e]
            return ("u", [self.group(members[b[j]:b[j + 1]], False) for j in range(len(b) - 1)])

        n = len(members)
        if is_union:
            if not members:
                return []
            base = members[0].offset
            splits = [k for k in range(1, n) if members[k].offset == base and not both_bf(k)]
            return [alts(0, splits, n)]
        nodes, i = [], 0
        while i < n:
            base = members[i].offset
            splits = [k for k in range(i + 1, n) if members[k].offset == base and not both_bf(k)]
            if not splits:
                nodes.append(("m", members[i]))
                i += 1
                continue
            uend = max(self.m_end(m) for m in members[i:splits[-1] + 1])
            e = splits[-1] + 1
            while e < n and base < members[e].offset < uend:
                e += 1
            nodes.append(alts(i, splits, e))
            i = e
        return nodes

    def node_members(self, node):
        if node[0] == "m":
            return [node[1]]
        return [m for alt in node[1] for nd in alt for m in self.node_members(nd)]

    def render(self, n, nodes, cur, is_union, hard, soft, asserts):
        """Lines for the nodes. Return (lines, cur, largest end offset). cur None = no padding check."""
        out = []
        top = 0
        for node in nodes:
            ms = self.node_members(node)
            off = min(m.offset for m in ms)
            al = max(self.m_align(m) for m in ms)
            if cur is not None and not is_union:
                if off < cur:
                    if not (node[0] == "m" and self.is_bf(node[1].type)):
                        raise GenFail("member %s overlaps (0x%x < 0x%x)" % (ms[0].name, off, cur))
                else:
                    nat = (cur + al - 1) // al * al
                    if nat != off:
                        if off > cur and off % al == 0:
                            out.append("char _pdb_pad%d[0x%X];" % (self._npad, off - cur))
                            self._npad += 1
                        else:
                            raise GenFail("member %s needs pack (0x%x)" % (ms[0].name, off))
            end = off
            if node[0] == "m":
                g = node[1]
                if not IDENT.match(g.name):
                    raise GenFail("member name %s" % g.name)
                if self.is_bf(g.type):
                    t = self.tpi.get(g.type)
                    bt = self.tname(t.utype, hard, soft) or "unsigned int"
                    out.append("%s %s : %d;" % (bt, g.name, t.length))
                    end = self.m_end(g)     # bitfields share one storage unit
                else:
                    d = self.decl(g.type, g.name, hard, soft)
                    gs, ga = self.size_align(g.type)
                    anon = self.anon_decl(g.type, g.name, hard, soft) if d is None else None
                    if anon is not None:
                        out += anon
                    elif d is None:
                        if gs == 0:
                            raise GenFail("member %s has size 0" % g.name)
                        # keep the alignment of the original type (a byte array has alignment 1)
                        out.append("%sunsigned char %s[0x%X];  // ❓ PDB type 0x%X: %s" % (
                            "alignas(%d) " % ga if ga > 1 else "",
                            g.name, gs, g.type, self.type_label(g.type)))
                    else:
                        out.append(d + ";")
                    end = g.offset + gs
                    if n is not None:
                        asserts.append("static_assert(offsetof(%s, %s) == 0x%X, \"%s::%s\");"
                                       % (n, g.name, g.offset, n, g.name))
            else:
                inner = []
                for alt in node[1]:
                    if len(alt) == 1 and alt[0][0] == "m":
                        l2, _c, e2 = self.render(n, alt, None, True, hard, soft, asserts)
                        inner += l2
                    else:
                        l2, _c, e2 = self.render(n, alt, off, False, hard, soft, asserts)
                        inner += ["struct {"] + ["    " + x for x in l2] + ["};"]
                    end = max(end, e2)
                if is_union:
                    out += inner            # the type itself is the union
                else:
                    out += ["union {"] + ["    " + x for x in inner] + ["};"]
            top = max(top, end)
            if cur is not None:
                cur = max(cur, end)
        return out, cur, top

    def is_empty(self, r):
        """True for a class that has no data member, no vfptr and only empty bases."""
        if r is None or r.size > 1:
            return False
        fl = self.tpi.get(r.field)
        for f in (fl.fields if fl and fl.fields else []):
            if f.leaf in (LF_MEMBER, LF_VFUNCTAB, LF_VBCLASS, LF_IVBCLASS):
                return False
            if f.leaf == LF_BCLASS and not self.is_empty(self.tpi.get(self.resolve(f.type))):
                return False
        return True

    def methods_safe(self, fields):
        class _F:
            pass
        fl = _F()
        fl.fields = fields
        return list(self.methods(fl))

    def type_label(self, ti):
        r = self.tpi.get(self.resolve(ti)) if ti >= 0x1000 else None
        if r is None:
            return "primitive" if ti < 0x1000 else "?"
        if r.name:
            return r.name
        return "leaf 0x%X" % r.leaf

    @staticmethod
    def split_ns(n):
        if "::" in n:
            ns, short = n.rsplit("::", 1)
            return ns, short
        return "", n

    # -- whole header -------------------------------------------------------------
    def build(self):
        self.enum_names = {}
        bodies = {}     # name -> (lines, asserts)
        deps = {}
        dropped = {}
        # repeat: a type that fails drops out, then types that need it fail too
        changed = True
        while changed:
            changed = False
            self.changed = False
            bodies.clear()
            deps.clear()
            self.enum_names = {}
            self.fwd_extra = set()
            for n in sorted(self.extra):
                if n not in self.emit and n not in self.extra_failed:
                    self.emit[n] = self.defs[n]
            for n in sorted(self.emit):
                r = self.tpi.get(self.emit[n])
                if r.leaf == LF_ENUM:
                    bodies[n] = (self.body_enum(n, r), [])
                    deps[n] = set()
                    continue
                hard, soft = set(), set()
                lines, extra = self.body_udt(n, r, hard, soft)
                if lines is None:
                    dropped[n] = extra
                    changed = True
                    continue
                bodies[n] = (lines, extra)
                deps[n] = hard - {n}
            pending = [n for n in self.extra if n not in self.emit and n not in self.extra_failed]
            for n in list(dropped):
                if n in self.extra:
                    self.extra_failed.add(n)
                    self.emit.pop(n, None)
                elif pending and dropped[n].startswith("base "):
                    del dropped[n]            # the base comes in the next pass
                else:
                    self.emit.pop(n, None)
            if self.changed or pending:
                changed = True
        for n, why in self.nested_failed.items():
            dropped.setdefault(n, why)
        order = self.topo(deps)
        return order, bodies, dropped

    def topo(self, deps):
        order, state = [], {}

        def visit(n, stack):
            st = state.get(n)
            if st == 2:
                return
            if st == 1:
                self.notes.append("dependency cycle: " + " -> ".join(stack + [n]))
                return
            state[n] = 1
            for d in sorted(deps.get(n, ())):
                if d in deps:
                    visit(d, stack + [n])
            state[n] = 2
            order.append(n)

        for n in sorted(deps):
            visit(n, [])
        return order

    def globals(self):
        out = []
        seen = set()
        for g in self.dbi.data_symbols():
            if g["kind"] != S_GDATA32:
                continue
            n = g["name"]
            if (n in seen or not IDENT.match(n) or n.startswith("_") or n in self.emit
                    or n in self.enum_names.get("", set())):
                continue
            seen.add(n)
            hard, soft = set(), set()
            if g["type"] >= 0x1000:
                r = self.tpi.get(self.resolve(g["type"]))
                if r and r.leaf in UDT_LEAVES and r.name not in self.emit and not r.name.startswith("std::"):
                    continue
            d = self.decl(g["type"], n, hard, soft)
            if d is None or any(h not in self.emit and h not in self.nested_ok for h in hard):
                continue
            out.append("extern %s;" % d)
        return out

    def write(self, out_root):
        order, bodies, dropped = self.build()
        glob = self.globals()
        path = os.path.join(out_root, self.server, "types.h")
        os.makedirs(os.path.dirname(path), exist_ok=True)
        L = ["// Generated by tools/pdb2h.py from %s.pdb. Do not edit." % self.server,
             "// Skipped types (reason): see the end of this file.",
             "#pragma once",
             "#include <stddef.h>",
             "#include <string>",
             "#include <vector>",
             "#include <map>",
             "#include <set>",
             "#include <deque>",
             "#include <list>",
             "#include <queue>",
             "#include <utility>",
             "",
             "#pragma clang diagnostic push",
             "#pragma clang diagnostic ignored \"-Winvalid-offsetof\"",
             "#pragma clang diagnostic ignored \"-Wmismatched-tags\"",
             "#pragma clang diagnostic ignored \"-Wmicrosoft-enum-forward-reference\"",
             "",
             "// Forward declarations"]
        kw = {LF_CLASS: "class", LF_STRUCTURE: "struct", LF_INTERFACE: "struct", LF_UNION: "union"}
        for n in sorted(set(bodies) | self.fwd_extra):
            leaf = self.kinds.get(n, LF_STRUCTURE)
            if leaf == LF_ENUM:
                continue
            L += self.wrap(n, ["%s %s;" % (kw.get(leaf, "struct"), self.split_ns(n)[1])])
        L.append("")
        # enums first: virtual method declarations can use them by value
        order = ([n for n in order if self.kinds.get(n) == LF_ENUM]
                 + [n for n in order if self.kinds.get(n) != LF_ENUM])
        for n in order:
            lines, asserts = bodies[n]
            L += self.wrap(n, lines)
            L += self.local_asserts(n, asserts)
            L.append("")
        if glob:
            L.append("// Global data (S_GDATA32)")
            L += glob
            L.append("")
        L.append("#pragma clang diagnostic pop")
        L.append("")
        L.append("// Skipped types:")
        for n in sorted(dropped):
            L.append("//   %s: %s" % (n, dropped[n]))
        for note in self.notes:
            L.append("//   " + note)
        with open(path, "w", newline="\n") as f:
            f.write("\n".join(L) + "\n")
        return path, len(order), len(dropped), len(glob)

    def local_asserts(self, n, asserts):
        """The asserts of a type that is local to a member function must use the pdb_local:: name."""
        ns, _s = self.split_ns(n)
        if not ns or ns.split("::")[0] not in self.defs:
            return asserts
        return [a.replace("sizeof(%s" % n, "sizeof(pdb_local::%s" % n)
                 .replace("offsetof(%s" % n, "offsetof(pdb_local::%s" % n) for a in asserts]

    def wrap(self, n, lines):
        ns, _s = self.split_ns(n)
        if not ns:
            return lines
        if ns.split("::")[0] in self.defs:
            # a type that is local to a member function: C++ cannot name it from outside
            ns = "pdb_local::" + ns
        return ["namespace %s {" % ns] + lines + ["}  // namespace %s" % ns]


def main():
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("pdb")
    ap.add_argument("server")
    ap.add_argument("--out", default=os.path.join(os.path.dirname(os.path.abspath(__file__)),
                                                  "..", "include", "pdb"))
    a = ap.parse_args()
    g = Gen(a.pdb, a.server)
    path, nt, nd, ng = g.write(a.out)
    print("%s: %d types, %d skipped, %d globals" % (os.path.normpath(path), nt, nd, ng))
    return 0


if __name__ == "__main__":
    sys.exit(main())
