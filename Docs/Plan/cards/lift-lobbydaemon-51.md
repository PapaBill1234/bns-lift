# lift-lobbydaemon-51: TryEnterGameWorldJob 2, mileage

| Item | Value |
| --- | --- |
| Source build | LobbyDaemon 2019 + PDB (VS2010 SP1) |
| Exe | `<work-root>/ida/lift/LobbyDaemon/LobbyDaemon.exe` |
| PDB | `<work-root>/ida/lift/LobbyDaemon/LobbyDaemon.pdb` |
| Pseudocode: TryEnterGameWorldJob | `~/.cache/bns-lift/hr/LobbyDaemon/TryEnterGameWorldJob.c` |
| Pseudocode: DepositMileageJob | `~/.cache/bns-lift/hr/LobbyDaemon/DepositMileageJob.c` |
| Pseudocode: SecondPasswordGetStatusJob | `~/.cache/bns-lift/hr/LobbyDaemon/SecondPasswordGetStatusJob.c` |
| Wave | 9 |
| Model | sol |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Read A2, A17, A18, A21 and C4 in `Docs/Parity/lessons.md`.
- Read the job pattern once: `src/Server/SmartCouponDaemon/CouponJob.cpp`.
- Use `~/.cache/bns-lift/hr/LobbyDaemon/index.tsv` for function names, RVAs and pseudocode line spans.

## Modules

The ranges show function entry RVAs. Both ends are in scope.
Function counts exclude EH funclets and scalar deleting destructors.
Pseudocode line counts include all index entries in each range.

| Module | Scope | RVA range | Functions | Pseudocode lines |
| --- | --- | --- | ---: | ---: |
| `TryEnterGameWorldJob` | Part 2 | `0x7e0f0` to `0x11f180` | 11 | 1,955 |
| `DepositMileageJob` | Whole module | `0x49b40` to `0x11ec80` | 11 | 864 |
| `SecondPasswordGetStatusJob` | Whole module | `0x71550` to `0x11ef80` | 10 | 664 |
| Total | | | 32 | 3,483 |

## Tasks

1. Use only the exe and PDB in the source table. Do not use `LobbyDaemon2019.exe` or a 381 file.
2. Run `tools/gate.sh` before edits. Run `tools/parity.sh CacheGate LobbyGate SmartCouponDaemon PostOfficeDaemon LobbyDaemon` before edits. Save the function-level results outside the tracked files.
3. Read only the function spans in scope.
   Do not change TryEnterGameWorldJob functions outside the range in the table. Leave their stubs as they are.
   Use IDA only if the cache does not give enough data. Close the database when you finish.
4. Replace the stub bodies in the listed `.cpp` files. Check for an existing body first. Use PDB names and types. Do not reproduce security bugs.
5. Change `CMakeLists.txt` only if the LobbyDaemon target needs it. Do not add a source file twice.
6. Run `tools/gate.sh` after each module. Repeat the parity check after the last edit. Compare the MATCH results by function with the results from before the edits. Do not change the parity baselines.

## Files

- `src/Server/LobbyDaemon/TryEnterGameWorldJob.cpp`
- `src/Server/LobbyDaemon/DepositMileageJob.cpp`
- `src/Server/LobbyDaemon/SecondPasswordGetStatusJob.cpp`
- `CMakeLists.txt`

## Handoff

Write `Docs/Plan/handoffs/lift-lobbydaemon-51.md`. List the functions you lifted.
List each remaining in-scope function as **Not done**. Give its name, RVA and reason.
Record the gate result and the MATCH counts for each exe before and after the edits.
Do not commit binaries, PDBs, IDA databases, keys or abuse notes.

## Done when

- `tools/gate.sh` prints `gate ok`.
- You lift each function in scope or list it as **Not done** in the handoff with its RVA.
- All functions that were a MATCH in CacheGate, LobbyGate, SmartCouponDaemon or PostOfficeDaemon are still a MATCH.
- The LobbyDaemon MATCH count does not go down.
