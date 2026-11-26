#!/usr/bin/env bash
# Build lift_selftest and run it under wine64. Exit 0 = pass.
set -euo pipefail
cd "$(dirname "$0")/.."
B="${LIFT_BUILD_DIR:-build}"
if [ ! -f "$B/build.ninja" ]; then
  cmake -S . -B "$B" -G Ninja -DCMAKE_TOOLCHAIN_FILE=cmake/clangcl-wine.cmake -DCMAKE_BUILD_TYPE=Release >/dev/null
fi
cmake --build "$B" --target lift_selftest >/dev/null

WINE="$(command -v wine64 || command -v wine64-stable || command -v wine)"
OUT="$(WINEDEBUG=-all "$WINE" "$B/lift_selftest.exe" | tr -d '\r')"
echo "$OUT"
EXPECT=$'lift ok 2 32\nlift exit'
if [ "$OUT" != "$EXPECT" ]; then
  echo "selftest FAIL: expected:"
  echo "$EXPECT"
  exit 1
fi
echo "selftest ok"
