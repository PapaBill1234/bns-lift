# lift-lobbydaemon-4: Character, GradeService, and schedule

| Item | Value |
| --- | --- |
| Source build | LobbyDaemon 2019 + PDB (VS2010 SP1) |
| Exe | `/home/ubuntu/Documents/Codex/private-project/ida/lift/LobbyDaemon/LobbyDaemon.exe` |
| PDB | `/home/ubuntu/Documents/Codex/private-project/ida/lift/LobbyDaemon/LobbyDaemon.pdb` |
| Pseudocode | `~/.cache/bns-lift/hr/LobbyDaemon/<Module>.c` |
| Pseudocode index | `~/.cache/bns-lift/hr/LobbyDaemon/index.tsv` |
| Wave | 1 |
| Model | opus |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Read sections A2 (block order), A12 (PDB member types), and A21 (PDB facts) in `Docs/Parity/lessons.md`.
- No pattern file is available.

## Modules

49 functions, about 3,229 pseudocode lines.

The ranges give inclusive function start RVAs. Use the module name and the RVA together.
Do not lift compiler-generated deleting destructors as separate functions.

| Module | Scope | RVA range | Functions | Pseudocode lines |
| --- | --- | --- | ---: | ---: |
| `Character` | Whole module | `0x30e90` to `0x328f0` | 21 | 1,217 |
| `GradeService` | Whole module | `0x53370` to `0x547b0` | 16 | 1,344 |
| `GameTimeSchedule` | Whole module | `0x4b8e0` to `0x4c6a0` | 12 | 668 |

## Tasks

1. Use the listed exe and PDB only. Do not use `LobbyDaemon2019.exe` or a 381 file.
2. Use the index to select the functions in this card. Read their pseudocode. Use IDA only if the cached output is not sufficient. Close the database when you finish.
3. Use PDB types and names. Restore STL calls in place of inlined STL code.
4. Replace the stub bodies in `Character`, `GradeService`, and `GameTimeSchedule`.
5. Keep each source file in the LobbyDaemon target. Change `CMakeLists.txt` only if the target needs a source entry. Do not add a second entry.
6. Run `tools/gate.sh` after each module.
7. Compare `tools/funcdiff.py` results with the pre-card baseline. Use the same build settings for both runs. Check function identities as well as counts for the four earlier servers.

## Files

- `src/Server/LobbyDaemon/Character.cpp`
- `src/Server/LobbyDaemon/GradeService.cpp`
- `src/Server/LobbyDaemon/GameTimeSchedule.cpp`
- `CMakeLists.txt`

## Handoff

Write `Docs/Plan/handoffs/lift-lobbydaemon-4.md`.
List the modules and functions that you lifted. List each remaining function under "Not done" with its RVA and the reason.
Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, and PostOfficeDaemon lose no MATCH functions.
- The LobbyDaemon MATCH count does not decrease.
