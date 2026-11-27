#!/usr/bin/env bash
# Gate for bns-lift cards. Exit 0 = pass.
# 1. No binaries in the tree that git tracks or would add.
# Exception: tools/LegacyBin/ holds unchanged upstream DLLs (DotNetZip, MaterialSkin). The user allowed them on 2026-11-22.
# 2. If CMakeLists.txt exists: configure and build all targets with the clang-cl toolchain.
# 3. tools/gate_extra.sh must pass (see below).
set -euo pipefail
cd "$(dirname "$0")/.."
BAD="$(git ls-files -co --exclude-standard | grep -v '^tools/LegacyBin/' | grep -iE '\.(exe|dll|pdb|i64|idb|lib|a|obj|o|bin|dat|pem|key)$' || true)"
[ -z "$BAD" ] || { echo "binary or key files: $BAD"; exit 1; }
if [ -f CMakeLists.txt ]; then
  B="${LIFT_BUILD_DIR:-build}"
  cmake -S . -B "$B" -G Ninja -DCMAKE_TOOLCHAIN_FILE=cmake/clangcl-wine.cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DLIFT_GAMEDAEMON=ON >/dev/null
  cmake --build "$B" 2>&1 | tail -40   # pipefail: a build error stops the script here
fi
# 3. tools/gate_extra.sh (selftest and the PDB layout check). It must be there and executable (git mode 100755).
#    Before 2026-11-26 a missing or mode 644 file skipped the check with no sign (Dr. Zero D05).
if [ ! -x tools/gate_extra.sh ]; then
  echo "gate: tools/gate_extra.sh is missing or not executable; the selftest and the PDB layout check cannot run." >&2
  echo "gate: fix it with 'git update-index --chmod=+x tools/gate_extra.sh' (git mode 100755)." >&2
  exit 1
fi
tools/gate_extra.sh
echo "gate ok"
