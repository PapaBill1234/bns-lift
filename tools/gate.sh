#!/usr/bin/env bash
# Gate for bns-lift cards. Exit 0 = pass.
# 1. No binaries in the tree that git tracks or would add.
# 2. If CMakeLists.txt exists: configure and build all targets with the clang-cl toolchain.
set -euo pipefail
cd "$(dirname "$0")/.."
BAD="$(git ls-files -co --exclude-standard | grep -iE '\.(exe|dll|pdb|i64|idb|lib|a|obj|o|bin|dat|pem|key)$' || true)"
[ -z "$BAD" ] || { echo "binary or key files: $BAD"; exit 1; }
if [ -f CMakeLists.txt ]; then
  B="${LIFT_BUILD_DIR:-build}"
  cmake -S . -B "$B" -G Ninja -DCMAKE_TOOLCHAIN_FILE=cmake/clangcl-wine.cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON >/dev/null
  cmake --build "$B" 2>&1 | tail -40   # pipefail: a build error stops the script here
fi
[ -x tools/gate_extra.sh ] && tools/gate_extra.sh
echo "gate ok"
