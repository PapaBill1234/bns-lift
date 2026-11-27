# lift-gamedaemon-82: DataManager: datamanager_cpp_2 part 6/10

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
| Depends on | `lift-gamedaemon-67`, `lift-gamedaemon-81` |
| Pattern | none |
| Plan | `Docs/Plan/gamedaemon-lift.md` sections 1, 3, 5 |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Grep `Docs/Parity/lessons.md` for A2 (block order), A6 (per-exe path literals), A12 (PDB member types), A18 (destructors), A21 (PDB facts) and A22 (per-exe source form). Do not read it in full.
- Pattern: none. Read the functions that `lift-gamedaemon-81` lifted in the same file first. Use their form.

## Scope

19 functions, about 2,437 pseudocode lines (about 19,496 tokens). Stems: `datamanager_cpp_2`.

This card is part 6/10 of stem `datamanager_cpp_2`. The other parts are in other cards of this wave. They run one after the other (column "Depends on"). Edit only the functions in this table.

| n | Exe | RVA | PDB name | Stem | Lines |
| ---: | --- | --- | --- | --- | ---: |
| 1 | GD | `0x63d740` | `Data::loadHiddenStopNextSkill` | datamanager_cpp_2 | 150 |
| 2 | GD | `0x63d9c0` | `Data::DataManager::loadHiddenFieldFromSkill3` | datamanager_cpp_2 | 259 |
| 3 | GD | `0x63df10` | `Data::DataManager::loadHiddenFieldFromFishingPaste` | datamanager_cpp_2 | 215 |
| 4 | GD | `0x63e270` | `Data::DataManager::loadHiddenFieldFromPc` | datamanager_cpp_2 | 102 |
| 5 | GD | `0x63e470` | `Data::DataManager::loadHiddenFieldFromBadgeSetItem` | datamanager_cpp_2 | 81 |
| 6 | GD | `0x63e5d0` | `Data::DataManager::loadHiddenFieldFromBadgeSynthesisCost` | datamanager_cpp_2 | 110 |
| 7 | GD | `0x63e720` | `Data::DataManager::loadHiddenFieldFromBadgeSynthesisRecipe` | datamanager_cpp_2 | 295 |
| 8 | GD | `0x63eb40` | `Data::DataManager::makeBadgeSynthesisResultDataPacket` | datamanager_cpp_2 | 150 |
| 9 | GD | `0x63ef30` | `Data::DataManager::loadHiddenFieldFromJumpingCharacter2` | datamanager_cpp_2 | 208 |
| 10 | GD | `0x63f3c0` | `Data::DataManager::loadHiddenFieldFromJumpingQuest2` | datamanager_cpp_2 | 116 |
| 11 | GD | `0x63f5f0` | `Data::DataManager::loadHiddenFieldFromJumpingTeleport2` | datamanager_cpp_2 | 70 |
| 12 | GD | `0x63f770` | `Data::DataManager::loadHiddenFieldFromNpc` | datamanager_cpp_2 | 44 |
| 13 | GD | `0x63f8b0` | `Data::DataManager::loadHiddenFieldFromChallengeList` | datamanager_cpp_2 | 57 |
| 14 | GD | `0x63f9b0` | `Data::DataManager::loadHiddenFieldFromItemFusion` | datamanager_cpp_2 | 151 |
| 15 | GD | `0x63fc00` | `Data::validateZoneAttraction` | datamanager_cpp_2 | 106 |
| 16 | GD | `0x63fdb0` | `Data::validateArenaPortal` | datamanager_cpp_2 | 103 |
| 17 | GD | `0x63ff90` | `Data::validateCave` | datamanager_cpp_2 | 77 |
| 18 | GD | `0x640140` | `Data::validateFieldZone` | datamanager_cpp_2 | 77 |
| 19 | GD | `0x6402e0` | `Data::validateJackpotBossZone` | datamanager_cpp_2 | 66 |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/datamanager_cpp_2.cpp`
- `src/Server/GameDaemon/datamanager_cpp_2.h`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-82.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
