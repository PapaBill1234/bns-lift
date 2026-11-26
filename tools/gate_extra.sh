#!/usr/bin/env bash
# Extra gate steps. tools/gate.sh calls this file. The gate fails when this file is missing or not executable.
set -euo pipefail
cd "$(dirname "$0")/.."
tools/run_selftest.sh
# Lift class members must have the PDB names and offsets (needs resymc, see tools/pdb_layout.py).
# It writes the summary <build>/pdb_layout.json. Exit 2 = a server PDB is missing.
tools/pdb_layout.py "${LIFT_BUILD_DIR:-build}"
