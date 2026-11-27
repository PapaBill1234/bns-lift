# Handoff: lift-gamedaemon-gap-013-e13 (round 1)

Card: `lift-gamedaemon-e13`. Exe: GameDaemon (2019 + PDB).

## Lifted (22 functions)

The bodies come from the Hex-Rays cache. The names come from the PDB.

| RVA | Function |
| --- | --- |
| 0x1a0f0 | `SkillPage::TypeId` (returns 26) |
| 0x1a100 | `SkillPage::Name` |
| 0x1a110 | `SkillPage::FieldMax` |
| 0x1a120 | `SkillPage::FieldDefine` |
| 0x1a130 | `SkillPage::SyncMax` |
| 0x1a140 | `SkillPage::SyncDefine` |
| 0x1a190 | `SkillSkinProperty::TypeId` (returns 34) |
| 0x1a1a0 | `SkillSkinProperty::Name` |
| 0x1a1b0 | `SkillSkinProperty::FieldMax` |
| 0x1a1c0 | `SkillSkinProperty::FieldDefine` |
| 0x1a1d0 | `SkillSkinProperty::SyncMax` |
| 0x1a1e0 | `SkillSkinProperty::SyncDefine` |
| 0x1a240 | `SummonedProperty::Name` |
| 0x1a250 | `SummonedProperty::FieldMax` |
| 0x1a260 | `SummonedProperty::FieldDefine` |
| 0x1a270 | `SummonedProperty::SyncMax` |
| 0x1a280 | `SummonedProperty::SyncDefine` |
| 0x1a2d0 | `WeaponProperty::Name` |
| 0x1a2e0 | `WeaponProperty::FieldMax` |
| 0x1a2f0 | `WeaponProperty::FieldDefine` |
| 0x1a300 | `WeaponProperty::SyncMax` |
| 0x1a310 | `WeaponProperty::SyncDefine` |

The four classes now declare the PDB static data members `fieldMax`, `fieldDefine`, `syncMax` and `syncDefine`. The `.cpp` files define them. The form follows `contentquotaproperty.cpp`.

Each lifted virtual function has no live caller yet. Each `.cpp` file has a `/INCLUDE` pragma with a `// LIFT: dead-strip keep` note for each lifted function.

The destructors (0x1a0e0, 0x1a180, 0x1a220, 0x1a2c0) are not in this card. They stay `LIFT_STUB`.

## Not done (6 functions)

| RVA | Function | Reason |
| --- | --- | --- |
| 0x65b3e0 | `Data::validateSecretTreasure` | The source `Data::DataManager` class has no members yet (Wave 0 stub). The body needs `Instance`, `_loaderDefs[185]` and the `DrTable` iterator vtable. A later card must add the DataManager layout first. |
| 0x65d0b0 | `Data::validateBadgeSetItem` | Same reason (`_loaderDefs[10]`). |
| 0x65d150 | `Data::validateBadgeSynthesisCost` | Same reason (`_loaderDefs[11]`). |
| 0x6621b0 | `Data::DataManager::GetDifficultyTypeDataIndex` | Needs the DataManager member `_defaultDifficultyTypeDataIdx` (offset 0x85DC). It also needs the `Log::Write` declaration. The source class has no members yet. |
| 0x662910 | `Data::DataManager::GetChallengeTypeDay` | Needs `GameDaemon::GamedInstance->ruleConfig->_questDailyResetTime`. The source `GameDaemon` and `RuleConfig` classes have no layout yet. |
| 0x662990 | `Data::DataManager::GetChallengeTypeWeek` | Needs `Instance`, `_challengeListWeekStartDateTime` and `_challengeListWeekCount`. The source class has no members yet. |

## Gate and MATCH

The author did not run the gate or funcdiff. The driver runs them after this session.

## Changed files

- `src/Server/GameDaemon/skillpage.cpp`
- `src/Server/GameDaemon/skillpage.h`
- `src/Server/GameDaemon/skillskinproperty.cpp`
- `src/Server/GameDaemon/skillskinproperty.h`
- `src/Server/GameDaemon/summonedproperty.cpp`
- `src/Server/GameDaemon/summonedproperty.h`
- `src/Server/GameDaemon/weaponproperty.cpp`
- `src/Server/GameDaemon/weaponproperty.h`
- `Docs/Plan/handoffs/lift-gamedaemon-gap-013-e13.md`
