#!/usr/bin/env python3
"""Compare the functions of an original 2019 + PDB exe with the functions of the lift.

Usage: tools/coverage.py <Server> [--build <dir>] [--missing] [--module <regex>]
  <dir>      = a build made with /Ob0 (no inlining). Default: build-cov.
               Make it: cmake -S . -B build-cov ... -DCMAKE_CXX_FLAGS_RELEASE="/O2 /Ob0 /DNDEBUG"
               then: cmake --build build-cov --target <Server>
  --missing  = print each missing function (name, RVA, size)
  --module   = only PDB modules whose .obj name matches

PDB side: S_GPROC32 and S_LPROC32 of all modules except the CRT, DLL imports and zstd (vendor).
The script skips compiler-made names, std:: internals and CRT template helpers (SKIP_NAME).
Lift side: defined code symbols in the .obj files of the build (llvm-nm), demangled with llvm-undname.
Match key: the qualified name without parameters. Overloads count as one name.
"""
import argparse, collections, pathlib, re, subprocess, sys

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
import pdbq  # noqa: E402

SKIP_MOD = re.compile(r"^f:\\dd\\|\.dll$|^\* |\\crt\\|\.lib$", re.I)
# Compiler-made code and STL internals. The lift uses the STL subset in include/vs2010, so std:: internals are not lift work.
SKIP_NAME = re.compile(r"`|\$|^std::|^operator (new|delete)|^_|^swprintf_s<|^wcscpy_s<|^sprintf_s<|^strcpy_s<|^_?vsnwprintf")
VENDOR = re.compile(r"zstd|fse_|huf_|entropy_common|xxhash|error_private", re.I)


def pdb_functions(server):
    lines = pdbq.dump(server, "syms")
    mod = None
    out = []
    for i, line in enumerate(lines):
        m = re.match(r"\s*Mod \d+ \| `(.*)`:", line)
        if m:
            mod = m.group(1)
            continue
        m = re.search(r"S_[GL]PROC32 \[size = \d+\] `(.*)`$", line)
        if not m or mod is None or SKIP_MOD.search(mod):
            continue
        name = m.group(1)
        obj = re.split(r"[\\/]", mod)[-1]
        if SKIP_NAME.search(name) or VENDOR.search(obj):
            continue
        a = re.search(r"addr = (\w+):(\w+), code size = (\d+)", lines[i + 1])
        out.append((obj, name, a.group(2) if a else "?", int(a.group(3)) if a else 0))
    return out


def key(name):
    """Qualified name without parameters, return type and calling convention."""
    name = name.replace("__ptr64", "")
    return re.sub(r"\s+", "", name)


def lift_functions(build):
    objs = [str(p) for p in pathlib.Path(build).rglob("*.obj")]
    if not objs:
        sys.exit(f"no .obj files in {build}")
    names = set()
    nm = subprocess.run(["llvm-nm", "--defined-only", "--format=just-symbols", *objs],
                        capture_output=True, text=True).stdout.split()
    mangled = sorted({s for s in nm if s.startswith("?")})
    plain = {s for s in nm if not s.startswith("?") and not s.endswith(":")}
    names |= plain
    dem = subprocess.run(["llvm-undname", "--no-calling-convention", "--no-return-type",
                          "--no-access-specifier", "--no-member-type"],
                         input="\n".join(mangled) + "\n", capture_output=True, text=True).stdout
    for line in dem.splitlines():
        line = line.strip()
        if not line or line.startswith("?"):
            continue
        # Cut the parameter list: the last top-level "(".
        depth, cut = 0, None
        for i, c in enumerate(line):
            if c in "<":
                depth += 1
            elif c in ">":
                depth -= 1
            elif c == "(" and depth == 0:
                cut = i
                break
        if cut is not None:
            line = line[:cut]
        names.add(key(line))
    return names


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("server")
    ap.add_argument("--build", default="build-cov")
    ap.add_argument("--missing", action="store_true")
    ap.add_argument("--module")
    a = ap.parse_args()
    pdb = pdb_functions(a.server)
    if a.module:
        pdb = [f for f in pdb if re.search(a.module, f[0])]
    lift = lift_functions(a.build)
    per = collections.OrderedDict()
    for obj, name, rva, size in pdb:
        per.setdefault(obj, [0, 0, 0, 0, []])
        r = per[obj]
        hit = key(name) in lift
        r[0] += 1
        r[1] += hit
        r[2] += size
        r[3] += size if hit else 0
        if not hit:
            r[4].append((name, rva, size))
    tf = sum(r[0] for r in per.values())
    th = sum(r[1] for r in per.values())
    tb = sum(r[2] for r in per.values())
    tbh = sum(r[3] for r in per.values())
    print(f"{a.server}: {th}/{tf} functions ({100 * th / max(tf, 1):.1f} %), "
          f"{tbh}/{tb} code bytes ({100 * tbh / max(tb, 1):.1f} %)")
    print("| Module | Functions | Missing | Missing bytes |")
    print("| --- | --- | --- | --- |")
    for obj, r in sorted(per.items(), key=lambda kv: -(kv[1][2] - kv[1][3])):
        if r[0] - r[1]:
            print(f"| {obj} | {r[0]} | {r[0] - r[1]} | {r[2] - r[3]} |")
    if a.missing:
        for obj, r in per.items():
            for name, rva, size in r[4]:
                print(f"{obj}\t{rva}\t{size}\t{name}")


if __name__ == "__main__":
    main()
