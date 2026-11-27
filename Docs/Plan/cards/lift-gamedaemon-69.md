# lift-gamedaemon-69: DataManager: datamanager_cpp_1 part 3/10

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
| Depends on | `lift-gamedaemon-68` |
| Pattern | none |
| Plan | `Docs/Plan/gamedaemon-lift.md` sections 1, 3, 5 |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Grep `Docs/Parity/lessons.md` for A2 (block order), A6 (per-exe path literals), A12 (PDB member types), A18 (destructors), A21 (PDB facts) and A22 (per-exe source form). Do not read it in full.
- Pattern: none. Read the functions that `lift-gamedaemon-68` lifted in the same file first. Use their form.

## Scope

18 functions, about 2,189 pseudocode lines (about 17,512 tokens). Stems: `datamanager_cpp_1`.

This card is part 3/10 of stem `datamanager_cpp_1`. The other parts are in other cards of this wave. They run one after the other (column "Depends on"). Edit only the functions in this table.

| n | Exe | RVA | PDB name | Stem | Lines |
| ---: | --- | --- | --- | --- | ---: |
| 1 | GD | `0x61e640` | `Data::DataManager::~DataManager` | datamanager_cpp_1 | 633 |
| 2 | GD | `0x61f330` | `Data::DataManager::CloseLog` | datamanager_cpp_1 | 75 |
| 3 | GD | `0x61f4c0` | `Data::DataManager::FlushLog` | datamanager_cpp_1 | 18 |
| 4 | GD | `0x61f560` | `Data::DataManager::Load` | datamanager_cpp_1 | 187 |
| 5 | GD | `0x61f8f0` | `Data::DataManager::loadData` | datamanager_cpp_1 | 143 |
| 6 | GD | `0x61fc80` | `Data::DataManager::loadGeoData` | datamanager_cpp_1 | 108 |
| 7 | GD | `0x61fe40` | `Data::DataManager::onConstructData` | datamanager_cpp_1 | 23 |
| 8 | GD | `0x61ff00` | `Data::DataManager::checkToExistKeyFromAllTable` | datamanager_cpp_1 | 170 |
| 9 | GD | `0x620270` | `Data::DataManager::constructData` | datamanager_cpp_1 | 565 |
| 10 | GD | `0x620b20` | `Data::insertQuestErrorLog` | datamanager_cpp_1 | 64 |
| 11 | GD | `0x620c40` | `Data::insertQuest` | datamanager_cpp_1 | 3 |
| 12 | GD | `0x620d30` | `Data::insertQuestConvoy` | datamanager_cpp_1 | 3 |
| 13 | GD | `0x620de0` | `Data::insertQuestFactionPcKill` | datamanager_cpp_1 | 3 |
| 14 | GD | `0x620ec0` | `Data::insertQuestAttraction` | datamanager_cpp_1 | 47 |
| 15 | GD | `0x620f50` | `Data::setDungeonInQuest` | datamanager_cpp_1 | 96 |
| 16 | GD | `0x621120` | `Data::getNpcScriptId` | datamanager_cpp_1 | 23 |
| 17 | GD | `0x621180` | `Data::getEnvScriptId` | datamanager_cpp_1 | 14 |
| 18 | GD | `0x6211c0` | `Data::getZoneScriptId` | datamanager_cpp_1 | 14 |

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

Write `Docs/Plan/handoffs/lift-gamedaemon-69.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
