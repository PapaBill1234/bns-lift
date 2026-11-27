# lift-gamedaemon-75: DataManager: datamanager_cpp_1 part 9/10

| Item | Value |
| --- | --- |
| Exe | GD |
| Source build | GameDaemon 2019 + PDB (VS2010 SP1) |
| Exe file | `<work-root>/ida/lift/GameDaemon/GameDaemon.exe` |
| PDB | `<work-root>/ida/lift/GameDaemon/GameDaemon.pdb` |
| Pseudocode | `~/.cache/bns-lift/hr/GameDaemon/<stem>.c` |
| Pseudocode index | `~/.cache/bns-lift/hr/GameDaemon/index.tsv` (stem, rva, name, first, last, status, source file, part) |
| Wave | W2 |
| Model | opus |
| Depends on | `lift-gamedaemon-74` |
| Pattern | none |
| Plan | `Docs/Plan/gamedaemon-lift.md` sections 1, 3, 5 |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Grep `Docs/Parity/lessons.md` for A2 (block order), A6 (per-exe path literals), A12 (PDB member types), A18 (destructors), A21 (PDB facts) and A22 (per-exe source form). Do not read it in full.
- Pattern: none. Read the functions that `lift-gamedaemon-74` lifted in the same file first. Use their form.

## Scope

11 functions, about 1,610 pseudocode lines (about 12,880 tokens). Stems: `datamanager_cpp_1`.

This card is part 9/10 of stem `datamanager_cpp_1`. The other parts are in other cards of this wave. They run one after the other (column "Depends on"). Edit only the functions in this table.

| n | Exe | RVA | PDB name | Stem | Lines |
| ---: | --- | --- | --- | --- | ---: |
| 1 | GD | `0x62dba0` | `Data::postprocExpandInventoryData` | datamanager_cpp_1 | 31 |
| 2 | GD | `0x62dc10` | `Data::postprocDuelBotEquippedItem` | datamanager_cpp_1 | 15 |
| 3 | GD | `0x62dc50` | `Data::postprocGrade` | datamanager_cpp_1 | 111 |
| 4 | GD | `0x62ddf0` | `Data::postprocNpcConvoy` | datamanager_cpp_1 | 32 |
| 5 | GD | `0x62de60` | `Data::postprocRandomStore` | datamanager_cpp_1 | 225 |
| 6 | GD | `0x62e260` | `Data::postprocRandomStoreItem` | datamanager_cpp_1 | 179 |
| 7 | GD | `0x62e4e0` | `Data::postprocRandomStoreItemGroup` | datamanager_cpp_1 | 95 |
| 8 | GD | `0x62e6f0` | `Data::postprocRandomStoreProbGroup` | datamanager_cpp_1 | 522 |
| 9 | GD | `0x62ef50` | `Data::postprocRankingPvEStage` | datamanager_cpp_1 | 127 |
| 10 | GD | `0x62f140` | `Data::postprocExpandRandomStore` | datamanager_cpp_1 | 88 |
| 11 | GD | `0x62f2b0` | `Data::postprocZoneTriggerEventStage` | datamanager_cpp_1 | 185 |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/datamanager_cpp_1.cpp`
- `src/Server/GameDaemon/datamanager_cpp_1.h`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-75.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
