# lift-lobbydaemon-44: DeleteCharacterJob 1, scheduler

| Item | Value |
| --- | --- |
| Source build | LobbyDaemon 2019 + PDB (VS2010 SP1) |
| Exe | `<work-root>/ida/lift/LobbyDaemon/LobbyDaemon.exe` |
| PDB | `<work-root>/ida/lift/LobbyDaemon/LobbyDaemon.pdb` |
| Pseudocode index | `~/.cache/bns-lift/hr/LobbyDaemon/index.tsv` |
| Pseudocode: DeleteCharacterJob | `~/.cache/bns-lift/hr/LobbyDaemon/DeleteCharacterJob.c` |
| Pseudocode: GetChargeInfoJob | `~/.cache/bns-lift/hr/LobbyDaemon/GetChargeInfoJob.c` |
| Pseudocode: CliSessionJob | `~/.cache/bns-lift/hr/LobbyDaemon/CliSessionJob.c` |
| Pseudocode: LobbyCharacterDeletionScheduler | `~/.cache/bns-lift/hr/LobbyDaemon/LobbyCharacterDeletionScheduler.c` |
| Wave | 8 |
| Model | sol |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Read A2, A8, A17, A21, and C4 in `Docs/Parity/lessons.md`. This is the current path for `lessons.md`.
- Read the pattern for the jobs once: `src/Server/SmartCouponDaemon/CouponJob.cpp`.
- `LobbyCharacterDeletionScheduler` has no pattern file.

## Modules

Use the module name and the function entry RVA together. Both ends of each range are in scope. Counts exclude EH funclets and scalar deleting destructors.

| Module | Scope | RVA range | Functions | Pseudocode lines |
| --- | --- | --- | ---: | ---: |
| `DeleteCharacterJob` | Part 1 | `0x45040` to `0x47560` | 13 | 2,155 |
| `GetChargeInfoJob` | Whole module | `0x50550` to `0x11ed00` | 11 | 947 |
| `CliSessionJob` | Whole module | `0x3bef0` to `0x3c010` | 3 | 60 |
| `LobbyCharacterDeletionScheduler` | Whole module | `0x56780` to `0x56ce0` | 4 | 308 |
| Total | | | 31 | 3,470 |

## Tasks

1. Use only the exe and PDB in the table. Do not use `LobbyDaemon2019.exe` or a 381 file.
2. Run `tools/gate.sh` before the edits. Then run `tools/parity.sh CacheGate LobbyGate SmartCouponDaemon PostOfficeDaemon LobbyDaemon`. Save the MATCH counts and function results outside the tracked files.
3. Use `index.tsv` to select the functions and line spans in scope. Read only those spans. Use IDA only if the cache does not give enough data. Close the database when you finish.
4. Replace only the stub bodies in scope. Use names and types from the 2019 PDB. Check for an existing body before you lift a function. Do not reproduce security bugs.
5. Leave the stubs for the other parts of `DeleteCharacterJob` unchanged.
6. Change `CMakeLists.txt` only if the LobbyDaemon target needs it. Do not add a source file twice.
7. Run `tools/gate.sh` after each module. Run the same parity check after the last edit. Compare the results with the saved results. Do not update the parity baselines.

## Files

- `src/Server/LobbyDaemon/DeleteCharacterJob.cpp`
- `src/Server/LobbyDaemon/GetChargeInfoJob.cpp`
- `src/Server/LobbyDaemon/CliSessionJob.cpp`
- `src/Server/LobbyDaemon/LobbyCharacterDeletionScheduler.cpp`
- `CMakeLists.txt`

## Handoff

Write `Docs/Plan/handoffs/lift-lobbydaemon-44.md`. List the functions you lifted. List each function that remains as **Not done**. Give its PDB name, RVA, and reason. Record the gate result and the MATCH counts for each exe before and after the edits. Keep binaries, PDBs, IDA databases, keys, and abuse notes out of git.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in scope is lifted or listed as **Not done** with its RVA in the handoff.
- No function that was a MATCH loses that status in CacheGate, LobbyGate, SmartCouponDaemon, or PostOfficeDaemon.
- The LobbyDaemon MATCH count does not go down.
