# lift-parity-tool-3

## Goal

Use TLS variable names when the compiler sets an address offset before a
loop or adds an offset to the TLS block pointer.

## Procedure

1. Measure all four executables with the current tool.
2. Trace each offset that the code uses to access the TLS block. Keep an
   immediate value as a constant if the code also uses it for another purpose.
3. Identify the narrow IP address buffer from its use in
   `Network::GetAddressStringW` and the PDB entry for the wide buffer.
4. Give the disassembly and PDB evidence in `Docs/Parity/noise.md`.
5. Measure the same executable files again. Check that each previous
   match holds. Run the gate and the parity check.

This is a tooling card. It changes the comparison and its documentation.
