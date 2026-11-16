#!/usr/bin/env bash
# Make a test copy of the source in build/verify/scd-fixsrc/, apply the src/common part of
# Docs/Verify/CacheGate-fixes.patch (not the CacheGate.cpp part), and build SmartCouponDaemon.exe there.
# The worktree src/ does not change.
#
# Usage: tools/verify/fixsrc_smartcoupondaemon.sh
# Output: build/verify/scd-fixsrc/build/SmartCouponDaemon.exe
# Then:   SCD_LIFTED_EXE=$PWD/build/verify/scd-fixsrc/build/SmartCouponDaemon.exe \
#           tools/verify/compare_smartcoupondaemon.sh 15 --pktlog
set -euo pipefail
cd "$(dirname "$0")/../.."
B="${LIFT_BUILD_DIR:-build}"
FIX="$B/verify/scd-fixsrc"
rm -rf "$FIX"
mkdir -p "$FIX"
cp -r CMakeLists.txt cmake include src "$FIX/"
[ -d vendor ] && cp -r vendor "$FIX/"
git apply --directory="$FIX" --exclude='src/CacheGate/*' Docs/Verify/CacheGate-fixes.patch
cmake -S "$FIX" -B "$FIX/build" -G Ninja -DCMAKE_TOOLCHAIN_FILE=cmake/clangcl-wine.cmake \
  -DCMAKE_BUILD_TYPE=Release >/dev/null
cmake --build "$FIX/build" --target SmartCouponDaemon 2>&1 | tail -5
ls -la "$FIX/build/SmartCouponDaemon.exe"
