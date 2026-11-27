# lift-gamedaemon-e13: Easy leaves (Property headers and DataManager): skillpage, skillskinproperty, summonedproperty, weaponproperty, ...

| Item | Value |
| --- | --- |
| Exe | GD |
| Source build | GameDaemon 2019 + PDB (VS2010 SP1) |
| Exe file | `<work-root>/ida/lift/GameDaemon/GameDaemon.exe` |
| PDB | `<work-root>/ida/lift/GameDaemon/GameDaemon.pdb` |
| Pseudocode | `~/.cache/bns-lift/hr/GameDaemon/<stem>.c` |
| Pseudocode index | `~/.cache/bns-lift/hr/GameDaemon/index.tsv` (stem, rva, name, first, last, status, source file, part) |
| Wave | E |
| Model | opus |
| Depends on | `lift-gamedaemon-0e` |
| Pattern | none |
| Plan | `Docs/Plan/gamedaemon-lift.md` sections 1, 3, 5 |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Grep `Docs/Parity/lessons.md` for A2 (block order), A6 (per-exe path literals), A12 (PDB member types), A18 (destructors), A21 (PDB facts) and A22 (per-exe source form). Do not read it in full.
- Pattern: none. No lifted file has the same role.

## Scope

28 functions, about 287 pseudocode lines (about 2,296 tokens). Stems: `skillpage`, `skillskinproperty`, `summonedproperty`, `weaponproperty`, `datamanager_cpp_3`.

Wave E (owner order 2026-11-27: the easiest work first). Each function in this card is a leaf: its body calls no other counted function that needs a lift. Thus a `LIFT_STUB` callee cannot keep it DIFF. Each function has at most 30 pseudocode lines. Ease key: 10.2 cost per function (rule in `Docs/Plan/gamedaemon-lift.md` section 3).

Lift only the functions in the table. The other functions of these stems are in later W cards. Those cards depend on this card.

| n | Exe | RVA | PDB name | Stem | Lines | Form |
| ---: | --- | --- | --- | --- | ---: | --- |
| 1 | GD | `0x1a0f0` | `SkillPage::TypeId` | skillpage | 7 | getter |
| 2 | GD | `0x1a100` | `SkillPage::Name` | skillpage | 7 | getter |
| 3 | GD | `0x1a110` | `SkillPage::FieldMax` | skillpage | 7 | getter |
| 4 | GD | `0x1a120` | `SkillPage::FieldDefine` | skillpage | 7 | getter |
| 5 | GD | `0x1a130` | `SkillPage::SyncMax` | skillpage | 7 | getter |
| 6 | GD | `0x1a140` | `SkillPage::SyncDefine` | skillpage | 7 | getter |
| 7 | GD | `0x1a190` | `SkillSkinProperty::TypeId` | skillskinproperty | 7 | getter |
| 8 | GD | `0x1a1a0` | `SkillSkinProperty::Name` | skillskinproperty | 7 | getter |
| 9 | GD | `0x1a1b0` | `SkillSkinProperty::FieldMax` | skillskinproperty | 7 | getter |
| 10 | GD | `0x1a1c0` | `SkillSkinProperty::FieldDefine` | skillskinproperty | 7 | getter |
| 11 | GD | `0x1a1d0` | `SkillSkinProperty::SyncMax` | skillskinproperty | 7 | getter |
| 12 | GD | `0x1a1e0` | `SkillSkinProperty::SyncDefine` | skillskinproperty | 7 | getter |
| 13 | GD | `0x1a240` | `SummonedProperty::Name` | summonedproperty | 7 | getter |
| 14 | GD | `0x1a250` | `SummonedProperty::FieldMax` | summonedproperty | 7 | getter |
| 15 | GD | `0x1a260` | `SummonedProperty::FieldDefine` | summonedproperty | 7 | getter |
| 16 | GD | `0x1a270` | `SummonedProperty::SyncMax` | summonedproperty | 7 | getter |
| 17 | GD | `0x1a280` | `SummonedProperty::SyncDefine` | summonedproperty | 7 | getter |
| 18 | GD | `0x1a2d0` | `WeaponProperty::Name` | weaponproperty | 7 | getter |
| 19 | GD | `0x1a2e0` | `WeaponProperty::FieldMax` | weaponproperty | 7 | getter |
| 20 | GD | `0x1a2f0` | `WeaponProperty::FieldDefine` | weaponproperty | 7 | getter |
| 21 | GD | `0x1a300` | `WeaponProperty::SyncMax` | weaponproperty | 7 | getter |
| 22 | GD | `0x1a310` | `WeaponProperty::SyncDefine` | weaponproperty | 7 | getter |
| 23 | GD | `0x65b3e0` | `Data::validateSecretTreasure` | datamanager_cpp_3 | 25 | leaf |
| 24 | GD | `0x65d0b0` | `Data::validateBadgeSetItem` | datamanager_cpp_3 | 25 | leaf |
| 25 | GD | `0x65d150` | `Data::validateBadgeSynthesisCost` | datamanager_cpp_3 | 25 | leaf |
| 26 | GD | `0x6621b0` | `Data::DataManager::GetDifficultyTypeDataIndex` | datamanager_cpp_3 | 23 | leaf |
| 27 | GD | `0x662910` | `Data::DataManager::GetChallengeTypeDay` | datamanager_cpp_3 | 21 | leaf |
| 28 | GD | `0x662990` | `Data::DataManager::GetChallengeTypeWeek` | datamanager_cpp_3 | 14 | leaf |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/skillpage.cpp`
- `src/Server/GameDaemon/skillpage.h`
- `src/Server/GameDaemon/skillskinproperty.cpp`
- `src/Server/GameDaemon/skillskinproperty.h`
- `src/Server/GameDaemon/summonedproperty.cpp`
- `src/Server/GameDaemon/summonedproperty.h`
- `src/Server/GameDaemon/weaponproperty.cpp`
- `src/Server/GameDaemon/weaponproperty.h`
- `src/Server/GameDaemon/datamanager_cpp_3.cpp`
- `src/Server/GameDaemon/datamanager_cpp_3.h`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-e13.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
