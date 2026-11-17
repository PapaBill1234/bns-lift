# bns-lift

PRIVATE repo. C++ lift of the 2019 + PDB BnS servers. Plan: `Docs/Plan/plan.md`.

- Write all text in ASD-STE100.
- Never write keys, passwords or certificates. Write `keyhere`.
- Never commit binaries. Never push to a public repo.
- Use PDB names only. Mark a name that is not in the PDB with `// ❓`.
- `tools/pdb_layout.py` (in the gate) compares class members with the PDB. It uses clang and resymc.
- Phase 1 keeps the original logic. Mark bugs with `// BUG:`.
- Build and check: `tools/gate.sh`.
- Commit author: `Claude <noreply@anthropic.com>`.
