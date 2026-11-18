# bns-lift

Public repo. C++ lift of the 2019 + PDB BnS servers. Plan: `Docs/Plan/plan.md`.

- Write all text in ASD-STE100.
- Never write keys, passwords or certificates. Write `keyhere`.
- Never commit binaries, PDBs, IDA databases or abuse notes. The repo is public.
- Use PDB names only.
- Mark an open question with `// ❓`. Remove the mark when the PDB or IDA settles it.
- Mark a name that can have no PDB name (inlined code, folded code, lift helper) with `// LIFT:`. Give the reason and the address.
- `tools/pdb_layout.py` (in the gate) compares class members with the PDB. It uses clang and resymc.
- Phase 1 keeps the original logic. Mark bugs with `// BUG:`.
- Build and check: `tools/gate.sh`.
- Commit author: `Claude <noreply@anthropic.com>`.
