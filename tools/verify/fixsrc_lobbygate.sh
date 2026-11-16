#!/usr/bin/env bash
# Make a test copy of the source in build/verify/lg-fixsrc/, apply Docs/Verify/LobbyGate-fixes.patch
# (Network::Initialize 0x200D0 calls CryptoKey::Initialize 0x526E0), and build LobbyGate.exe there.
# The worktree src/ does not change.
#
# Usage: tools/verify/fixsrc_lobbygate.sh
# Output: build/verify/lg-fixsrc/build/LobbyGate.exe
# Then:   LG_LIFTED_EXE=$PWD/build/verify/lg-fixsrc/build/LobbyGate.exe \
#           tools/verify/run_lobbygate.sh lifted 20 --peer --client --pktlog
set -euo pipefail
cd "$(dirname "$0")/../.."
B="${LIFT_BUILD_DIR:-build}"
FIX="$B/verify/lg-fixsrc"
rm -rf "$FIX"
mkdir -p "$FIX"
cp -r CMakeLists.txt cmake include src "$FIX/"
[ -d vendor ] && cp -r vendor "$FIX/"
git apply --directory="$FIX" Docs/Verify/LobbyGate-fixes.patch
cmake -S "$FIX" -B "$FIX/build" -G Ninja -DCMAKE_TOOLCHAIN_FILE=cmake/clangcl-wine.cmake \
  -DCMAKE_BUILD_TYPE=Release >/dev/null
cmake --build "$FIX/build" --target LobbyGate 2>&1 | tail -5
ls -la "$FIX/build/LobbyGate.exe"
