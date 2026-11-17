#!/usr/bin/env python3
"""Find wide string literals in the lift that are not in the original 2019 + PDB exe.

Usage: tools/verify/strings_check.py <Server> [--build <dir>] [--exe <path>] [--common]
  <dir>    = build dir with compile_commands.json. Default: build.
  <path>   = original exe. Default: ../ida/lift/<Server>/<Server>.exe.
  --common = also read lift_common (BloodLib). Code that is not linked gives noise.

The script reads the sources of the targets <Server> and lift_<server> from compile_commands.json.
It joins adjacent literals (also across lines). It skips a run with a macro or a name before or after it.
It prints each literal that is not a wide string in the exe, with file and line.
A literal that is only a part of an exe string is "PARTIAL". The script prints it apart.
Literals with escapes other than \\n, \\t, \\\\ and \\" are skipped. Literals with a new line are skipped.
"""
import argparse, json, pathlib, re, subprocess, sys

ROOT = pathlib.Path(__file__).resolve().parents[2]
STR = r'L?"(?:[^"\\\n]|\\.)*"'
RUN = re.compile(STR + r'(?:\s*' + STR + r')*')
PART = re.compile(r'L?"((?:[^"\\\n]|\\.)*)"')
PREV = re.compile(r'\w\s*$')
NEXT = re.compile(r'\s*\w')


def exe_strings(exe):
    out = subprocess.run(["strings", "-n1", "-el", str(exe)], capture_output=True, text=True).stdout
    return set(out.split("\n"))


def sources(build, server, common):
    targets = [server, "lift_" + server.lower()] + (["lift_common"] if common else [])
    d = json.load(open(pathlib.Path(build) / "compile_commands.json"))
    files = set()
    for e in d:
        out = e.get("output", "")
        if any(f"CMakeFiles/{t}.dir/" in out for t in targets):
            files.add(pathlib.Path(e["directory"], e["file"]).resolve())
    if not files:
        sys.exit(f"no sources for target {server} in {build}/compile_commands.json")
    return sorted(files)


def unescape(s):
    if re.search(r'\\[^nt\\"]', s):
        return None
    return s.replace("\\n", "\n").replace("\\t", "\t").replace('\\"', '"').replace("\\\\", "\\")


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("server")
    ap.add_argument("--build", default=str(ROOT / "build"))
    ap.add_argument("--exe")
    ap.add_argument("--common", action="store_true")
    a = ap.parse_args()
    exe = a.exe or ROOT.parent / "ida" / "lift" / a.server / f"{a.server}.exe"
    have = exe_strings(exe)
    data = pathlib.Path(exe).read_bytes()  # strings -el reads only ASCII. Non-ASCII literals need a byte search.
    blob = "\n".join(have)
    missing, partial, total = [], [], 0
    for f in sources(a.build, a.server, a.common):
        text = f.read_text(errors="replace")
        for m in RUN.finditer(text):
            run = m.group(0)
            if not run.startswith("L") or PREV.search(text, 0, m.start()) or NEXT.match(text, m.end()):
                continue
            # A '//' before the run on the same line: the run is in a comment.
            if "//" in text[text.rfind("\n", 0, m.start()) + 1:m.start()]:
                continue
            parts = [unescape(p) for p in PART.findall(run)]
            if None in parts:
                continue
            s = "".join(parts)
            if s == "" or "\n" in s:
                continue
            total += 1
            w = s.encode("utf-16-le")
            if s in have or (not s.isascii() and b"\0\0" + w + b"\0\0" in data):
                continue
            n = text.count("\n", 0, m.start()) + 1
            rel = f.relative_to(ROOT) if f.is_relative_to(ROOT) else f
            (partial if s in blob or (not s.isascii() and w in data) else missing).append(f"{rel}:{n}\t{s}")
    print(f"{a.server}: {total} literals, {len(missing)} not in exe, {len(partial)} partial")
    for x in missing:
        print("MISSING\t" + x)
    for x in partial:
        print("PARTIAL\t" + x)


if __name__ == "__main__":
    main()
