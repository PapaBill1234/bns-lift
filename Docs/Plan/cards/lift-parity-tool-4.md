# lift-parity-tool-4

## Goal

Compare each virtual table reference with all its public PDB names.

## Check

1. Use the PDB to find tables that have more than one name at one address.
2. Pair table references only when they share a name. Use each
   reference one time.
3. Record the address and PDB proof in `Docs/Parity/noise.md`.
4. Check all four VS2010 binaries before and after the change. Check
   that all previous matches hold.
