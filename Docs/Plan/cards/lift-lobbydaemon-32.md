# lift-lobbydaemon-32: AddSlotJob 1, ActivateGradeJob

| Item | Value |
| --- | --- |
| Source build | LobbyDaemon 2019 + PDB (VS2010 SP1) |
| Exe | `<work-root>/ida/lift/LobbyDaemon/LobbyDaemon.exe` |
| PDB | `<work-root>/ida/lift/LobbyDaemon/LobbyDaemon.pdb` |
| Pseudocode: AddSlotJob | `~/.cache/bns-lift/hr/LobbyDaemon/AddSlotJob.c` |
| Pseudocode: ActivateGradeJob | `~/.cache/bns-lift/hr/LobbyDaemon/ActivateGradeJob.c` |
| Wave | 6 |
| Model | sol |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Read A2, A17, A18, A19, A21 and C4 in `Docs/Parity/lessons.md`.
- Use `~/.cache/bns-lift/hr/LobbyDaemon/index.tsv` for the function list and pseudocode line spans.
- Read the pattern once: `src/Server/SmartCouponDaemon/CouponJob.cpp`.

## Modules

Addresses are function entry RVAs. Both ends of each range are in scope. Counts exclude EH funclets and scalar deleting destructors. Use only the index rows for the module in each range.

| Module | Scope | RVA range | Functions | Pseudocode lines |
| --- | --- | --- | ---: | ---: |
| `AddSlotJob` | Part 1 | `0xd1e0` to `0xeec0` | 15 | 1,905 |
| `ActivateGradeJob` | Whole module | `0xb9e0` to `0x11e800` | 15 | 1,416 |
| Total | | | 30 | 3,321 |

## Tasks

1. Use only the exe and PDB in the table. Do not use `LobbyDaemon2019.exe` or a 381 file.
2. Run `tools/gate.sh` before edits. Record the results of `tools/parity.sh CacheGate LobbyGate SmartCouponDaemon PostOfficeDaemon LobbyDaemon` outside the tracked files.
3. Read only the function spans in scope. Use IDA only if the cache does not give enough data. Close the database when you finish.
4. Check for an existing body before you lift a function. Replace only the stub bodies in scope. Use PDB types and names. Do not change the bodies or stubs in the other parts of `AddSlotJob.cpp`. Do not reproduce security bugs.
5. Change `CMakeLists.txt` only if the LobbyDaemon target needs it. Do not add a source file twice.
6. Run `tools/gate.sh` after each module. Run the same parity check after the last edit. Compare the MATCH results with the results from before the edits. Do not update the parity baselines.

## Files

- `src/Server/LobbyDaemon/AddSlotJob.cpp`
- `src/Server/LobbyDaemon/ActivateGradeJob.cpp`
- `CMakeLists.txt`

## Handoff

Write `Docs/Plan/handoffs/lift-lobbydaemon-32.md`. List the functions you lifted. List each function in scope that remains as **Not done**. Give its name, RVA and reason. Record the gate result and the before and after MATCH counts for each exe. Do not put binaries, PDBs, IDA databases, keys or abuse notes in the public repo.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in scope is lifted or is listed as **Not done** in the handoff with its RVA.
- No function that was a MATCH loses that status in CacheGate, LobbyGate, SmartCouponDaemon or PostOfficeDaemon.
- The LobbyDaemon MATCH count does not go down.
