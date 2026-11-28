#!/usr/bin/env python3
"""Check the text encoding of string literals for the VS2010 build. tools/gate_extra.sh runs it.

VS2010 cl reads a source file that has no UTF-8 BOM in the ANSI code page of the host.
Under Wine that code page is 1252. So UTF-8 Korean text in a wide literal becomes mojibake:
"투사" became "íˆ¬ì‚¬" in our LobbyDaemon.exe (found 2026-11-28). The original exe has correct UTF-16.
With a BOM, cl reads the file as UTF-8 and writes correct UTF-16. clang-cl reads UTF-8 with or without a BOM.

Rules (exit 1 when a rule fails):
  1. A wide literal (L"", u"", U"") that has non-ASCII text needs a UTF-8 BOM in its file.
  2. A narrow literal ("" or u8"") must not have non-ASCII text: its bytes change with the host code page.
     Write the bytes of the original exe as \\x escapes.
Usage: tools/check_literals.py [--fix] [FILE...]
  No FILE: check each C/C++ source that git tracks.
  --fix: add the BOM to each file that fails rule 1. It does not change rule 2 failures.
"""
import subprocess
import sys

BOM = b"\xef\xbb\xbf"
SUFFIXES = (".c", ".cc", ".cpp", ".cxx", ".h", ".hh", ".hpp", ".inl")
WIDE = ("L", "u", "U", "LR", "uR", "UR")
PREFIXES = WIDE + ("u8", "R", "u8R")


def literals(text):
    """Yield (line, prefix, body) for each string literal. Comments and char literals are skipped."""
    i, n, line = 0, len(text), 1
    while i < n:
        c = text[i]
        if c == "\n":
            line += 1
            i += 1
        elif text.startswith("//", i):
            j = text.find("\n", i)
            i = n if j < 0 else j
        elif text.startswith("/*", i):
            j = text.find("*/", i + 2)
            j = n if j < 0 else j + 2
            line += text.count("\n", i, j)
            i = j
        elif c == "'":
            j = i + 1
            while j < n and text[j] not in "'\n":
                j += 2 if text[j] == "\\" else 1
            i = j + 1
        elif c == '"':
            k = i
            while k > 0 and (text[k - 1].isalnum() or text[k - 1] == "_"):
                k -= 1
            prefix = text[k:i] if text[k:i] in PREFIXES else ""
            if prefix.endswith("R"):
                m = text.find("(", i)
                delim = text[i + 1:m]
                end = text.find(")" + delim + '"', m)
                end = n if end < 0 else end
                body, j = text[m + 1:end], end + len(delim) + 2
            else:
                j = i + 1
                while j < n and text[j] not in '"\n':
                    j += 2 if text[j] == "\\" else 1
                body, j = text[i + 1:j], j + 1
            yield line, prefix, body
            line += body.count("\n")
            i = j
        else:
            i += 1


def check(path):
    """Return (wide lines without BOM, narrow lines) for one file."""
    raw = open(path, "rb").read()
    has_bom = raw.startswith(BOM)
    text = raw[len(BOM):].decode("utf-8", "surrogateescape") if has_bom else raw.decode("utf-8", "surrogateescape")
    wide, narrow = [], []
    for line, prefix, body in literals(text):
        if all(ord(ch) < 128 for ch in body):
            continue
        if prefix in WIDE:
            if not has_bom:
                wide.append(line)
        else:
            narrow.append(line)
    return wide, narrow


def main(argv):
    fix = "--fix" in argv
    files = [a for a in argv if a != "--fix"]
    if not files:
        out = subprocess.run(["git", "ls-files", "-z"], capture_output=True, check=True).stdout.decode()
        files = [f for f in out.split("\0") if f.endswith(SUFFIXES) and not f.startswith("tools/LegacyBin/")]
    bad = 0
    for path in files:
        wide, narrow = check(path)
        if wide and fix:
            data = open(path, "rb").read()
            with open(path, "wb") as f:
                f.write(BOM + data)
            print("%s: added a UTF-8 BOM (%d wide literals with non-ASCII text)" % (path, len(wide)))
            wide = []
        if wide:
            bad += 1
            print("%s:%d: %d wide literals have non-ASCII text, but the file has no UTF-8 BOM. VS2010 reads the file "
                  "as code page 1252 and writes mojibake. Fix: tools/check_literals.py --fix %s" % (path, wide[0], len(wide), path))
        if narrow:
            bad += 1
            print("%s:%d: %d narrow literals have non-ASCII text. The bytes change with the host code page. "
                  "Write the bytes of the original exe as \\x escapes." % (path, narrow[0], len(narrow)))
    if bad:
        print("check_literals: %d problems" % bad)
        return 1
    print("check_literals ok (%d files)" % len(files))
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
