#!/usr/bin/env bash
# Make a test copy of the source in build/verify/pod-fixsrc/src-copy/, apply
# Docs/Verify/PostOfficeDaemon-fixes.patch, and build PostOfficeDaemon.exe there.
# The worktree src/ does not change.
#
# Usage: tools/verify/fixsrc_postofficedaemon.sh
# Output: build/verify/pod-fixsrc/src-copy/build/PostOfficeDaemon.exe
# Then:   POD_LIFTED_EXE=$PWD/build/verify/pod-fixsrc/src-copy/build/PostOfficeDaemon.exe POD_CERT=sql \
#           tools/verify/compare_postofficedaemon.sh 25 --pktlog
set -euo pipefail
cd "$(dirname "$0")/../.."
B="${LIFT_BUILD_DIR:-build}"
FIX="$B/verify/pod-fixsrc/src-copy"
rm -rf "$FIX"
mkdir -p "$FIX"
cp -r CMakeLists.txt cmake include src "$FIX/"
[ -d vendor ] && cp -r vendor "$FIX/"
git apply --directory="$FIX" Docs/Verify/PostOfficeDaemon-fixes.patch
cmake -S "$FIX" -B "$FIX/build" -G Ninja -DCMAKE_TOOLCHAIN_FILE=cmake/clangcl-wine.cmake \
  -DCMAKE_BUILD_TYPE=Release >/dev/null
cmake --build "$FIX/build" --target PostOfficeDaemon 2>&1 | tail -5
ls -la "$FIX/build/PostOfficeDaemon.exe"
