#!/usr/bin/env python3
"""Print the interface of the lifted C++ headers: classes, method signatures and fields. No bodies.
Usage: tools/cpp_api.py [-C <repo root>] [-i] [dir or header ...] [-n <Name> ...]
  no paths   = src/common
  -n Name    = only the classes and free functions whose name has this text (more names: more -n)
  -i         = index only: one line per header with its class names
One call gives the signatures that many grep and sed calls give."""
import pathlib, re, sys

HEAD = re.compile(r"^(?:template\s*<[^{;]*>\s*)?(class|struct|union|enum(?:\s+class)?|namespace)\b\s*([\w:]*)([^;{]*)$", re.S)
ACCESS = re.compile(r"^(?:(?:public|private|protected)\s*:\s*)+")


def strip(text):
    text = re.sub(r"/\*.*?\*/", " ", text, flags=re.S)
    text = re.sub(r"//[^\n]*", "", text)
    text = re.sub(r"^[ \t]*#(?:[^\n]*\\\n)*[^\n]*", "", text, flags=re.M)
    return re.sub(r'"(?:\\.|[^"\\])*"', '""', text)


def close(text, i):
    """Index after the brace that closes the one at text[i]."""
    depth = 0
    while i < len(text):
        depth += text[i] == "{"
        depth -= text[i] == "}"
        i += 1
        if depth == 0:
            break
    return i


def one(s):
    return re.sub(r"\s+", " ", ACCESS.sub("", s.strip())).strip()


def scope(text, i, name, out):
    """Read one scope from text[i]. out gets (class name or '', kind, text) rows. Returns the index after the scope."""
    stmt = ""
    while i < len(text):
        c = text[i]
        if c == "}":
            return i + 1
        if c == ";":
            s = one(stmt)
            stmt = ""
            i += 1
            if not s or s.startswith(("static_assert", "friend ", "using ", "typedef ", "extern \"\"")) or HEAD.match(s):
                continue
            out.append((name, "fn" if "(" in s.split("=")[0] else "field", s))
            continue
        if c == "{":
            s = one(stmt)
            stmt = ""
            m = HEAD.match(s)
            if m and m.group(1).startswith("enum"):
                out.append((name, "type", f"enum {m.group(2)}"))
                i = close(text, i)
            elif m and m.group(1) == "namespace":
                i = scope(text, i + 1, name, out)
            elif m and "(" not in s:
                sub = (name + "::" if name else "") + (m.group(2) or "<anonymous>")
                out.append((sub, "class", one(f"{m.group(1)} {m.group(2)}{m.group(3)}")))
                i = scope(text, i + 1, sub, out)
            elif "(" in s:
                out.append((name, "fn", re.sub(r"\)\s*:\s*[A-Za-z_].*$", ")", s)))
                i = close(text, i)
            else:
                i = close(text, i)  # initializer list of a table
            continue
        stmt += c
        i += 1
    return i


def main(argv):
    root, names, paths, index = pathlib.Path("."), [], [], False
    it = iter(argv)
    for a in it:
        if a == "-C":
            root = pathlib.Path(next(it))
        elif a == "-n":
            names.append(next(it))
        elif a == "-i":
            index = True
        else:
            paths.append(a)
    files = []
    for p in paths or ["src/common"]:
        p = root / p
        files += sorted(p.glob("*.h")) if p.is_dir() else [p]
    for f in files:
        rows = []
        scope(strip(f.read_text(errors="replace")), 0, "", rows)
        rel = f.relative_to(root) if f.is_relative_to(root) else f
        classes = [r[0] for r in rows if r[1] == "class"]
        if index:
            free = sum(1 for r in rows if not r[0] and r[1] == "fn")
            print(f"{rel}: {', '.join(classes) or '-'}" + (f" (+{free} free functions)" if free else ""))
            continue
        if names:
            rows = [r for r in rows if any(n in (r[0] or r[2]) for n in names)]
        if not rows:
            continue
        print(f"## {rel}")
        cur = None
        for name, kind, s in rows:
            if kind == "class":
                cur = name
                print(s)
                continue
            if name != cur:
                cur = name
                if name:
                    print(f"class {name} (cont.)")
            print(("  " if name else "") + s)


if __name__ == "__main__":
    main(sys.argv[1:])
