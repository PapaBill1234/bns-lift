#!/usr/bin/env bash
# Build one time and print a short error list. Then run the gate.
# Use this in a card session in place of tools/gate.sh: one run gives all errors, each one time.
#   full build log: .scratch/build.log     full gate log: .scratch/gate.log
# Usage: tools/gate_errors.sh [max errors, default 25]
set -uo pipefail
cd "$(dirname "$0")/.."
MAX="${1:-25}"
mkdir -p .scratch
if [ -f CMakeLists.txt ]; then
  B="${LIFT_BUILD_DIR:-build}"
  if ! cmake -S . -B "$B" -G Ninja -DCMAKE_TOOLCHAIN_FILE=cmake/clangcl-wine.cmake -DCMAKE_BUILD_TYPE=Release > .scratch/build.log 2>&1; then
    echo "configure FAILED"; tail -n 20 .scratch/build.log; exit 1
  fi
  # -k 0: do not stop at the first file with an error. One run shows the errors of all files.
  if ! cmake --build "$B" -- -k 0 >> .scratch/build.log 2>&1; then
    python3 - "$MAX" "$PWD/" <<'PY'
import re, sys
mx, root = int(sys.argv[1]), sys.argv[2]
seen, out, total = set(), [], 0
for line in open(".scratch/build.log", errors="replace"):
    line = line.rstrip().replace(root, "")
    if not re.search(r"\berror\b[ :]|undefined symbol|duplicate symbol|fatal error", line) or line.startswith("ninja:") or " generated." in line:
        continue
    total += 1
    key = re.sub(r"\(\d+,\d+\)|:\d+:\d+", "", line)   # the same error in a header shows one time
    if key in seen:
        continue
    seen.add(key)
    out.append(line[:300])
print(f"build FAILED: {total} error lines, {len(out)} different. Full log: .scratch/build.log")
print("\n".join(out[:mx]))
if len(out) > mx:
    print(f"... {len(out) - mx} more: grep -n 'error' .scratch/build.log")
if not out:
    print("".join(open(".scratch/build.log", errors="replace").readlines()[-15:]))
PY
    exit 1
  fi
fi
if tools/gate.sh > .scratch/gate.log 2>&1; then
  echo "gate ok"
else
  echo "gate FAILED (build ok). Full log: .scratch/gate.log"; tail -n 25 .scratch/gate.log; exit 1
fi
