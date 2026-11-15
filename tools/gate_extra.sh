#!/usr/bin/env bash
# Extra gate steps. tools/gate.sh calls this file if it is executable.
set -euo pipefail
cd "$(dirname "$0")/.."
tools/run_selftest.sh
