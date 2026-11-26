#!/usr/bin/env bash
# Extra gate steps. tools/gate.sh calls this file if it is executable.
set -euo pipefail
cd "$(dirname "$0")/.."
tools/run_selftest.sh
# Lift class members must have the PDB names and offsets (needs resymc, see tools/pdb_layout.py).
tools/pdb_layout.py "${LIFT_BUILD_DIR:-build}"
