# lift-gamedaemon-73: DataManager: datamanager_cpp_1 part 7/10

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
| Depends on | `lift-gamedaemon-e26`, `lift-gamedaemon-72` |
| Pattern | none |
| Plan | `Docs/Plan/gamedaemon-lift.md` sections 1, 3, 5 |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Grep `Docs/Parity/lessons.md` for A2 (block order), A6 (per-exe path literals), A12 (PDB member types), A18 (destructors), A21 (PDB facts) and A22 (per-exe source form). Do not read it in full.
- Pattern: none. Read the functions that `lift-gamedaemon-72` lifted in the same file first. Use their form.

## Scope

17 functions, about 2,376 pseudocode lines (about 19,008 tokens). Stems: `datamanager_cpp_1`.

The easy functions of this stem are in `lift-gamedaemon-e26`. Do not change them unless a fix needs it.

This card is part 7/10 of stem `datamanager_cpp_1`. The other parts are in other cards of this wave. They run one after the other (column "Depends on"). Edit only the functions in this table.

| n | Exe | RVA | PDB name | Stem | Lines |
| ---: | --- | --- | --- | --- | ---: |
| 1 | GD | `0x6284a0` | `Data::DataManager::loadHiddenFieldFromEffect` | datamanager_cpp_1 | 398 |
| 2 | GD | `0x628b10` | `Data::DataManager::loadHiddenFieldFromGuildBankItem` | datamanager_cpp_1 | 86 |
| 3 | GD | `0x628c90` | `Data::DataManager::loadHiddenFieldFromGuildUniformParamTypeCategory` | datamanager_cpp_1 | 130 |
| 4 | GD | `0x628ec0` | `Data::DataManager::loadHiddenFieldFromAccountPostCharge` | datamanager_cpp_1 | 48 |
| 5 | GD | `0x628f90` | `Data::DataManager::loadHiddenFieldFromSkill` | datamanager_cpp_1 | 171 |
| 6 | GD | `0x629330` | `Data::DataManager::loadHiddenFieldFromEnv` | datamanager_cpp_1 | 356 |
| 7 | GD | `0x629a50` | `Data::DataManager::loadExpTableFromLevel` | datamanager_cpp_1 | 109 |
| 8 | GD | `0x629cd0` | `Data::DataManager::loadAccountExpTableFromAccountLevel` | datamanager_cpp_1 | 95 |
| 9 | GD | `0x629e80` | `Data::DataManager::loadQuotaTableFromContentQuota` | datamanager_cpp_1 | 73 |
| 10 | GD | `0x629fe0` | `Data::DataManager::loadArenaDungeonZoneFromInterDungeonList` | datamanager_cpp_1 | 139 |
| 11 | GD | `0x62a2b0` | `Data::DataManager::loadArenaDuelZoneFromDuel` | datamanager_cpp_1 | 36 |
| 12 | GD | `0x62a390` | `Data::DataManager::loadGradeBenefits` | datamanager_cpp_1 | 335 |
| 13 | GD | `0x62aa50` | `Data::DataManager::loadItemTransformRecipe` | datamanager_cpp_1 | 42 |
| 14 | GD | `0x62ab50` | `Data::DataManager::loadZoneNpcSpawn` | datamanager_cpp_1 | 185 |
| 15 | GD | `0x62aed0` | `Data::DataManager::addToArenaDungeonZoneIdList` | datamanager_cpp_1 | 42 |
| 16 | GD | `0x62afc0` | `Data::DataManager::addToArenaDuelZoneIdList` | datamanager_cpp_1 | 41 |
| 17 | GD | `0x62b0b0` | `Data::DataManager::checkQuestReward` | datamanager_cpp_1 | 90 |

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

Write `Docs/Plan/handoffs/lift-gamedaemon-73.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
