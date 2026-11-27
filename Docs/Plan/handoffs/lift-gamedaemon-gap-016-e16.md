# Handoff: lift-gamedaemon-gap-016-e16 (round 1)

Card: `lift-gamedaemon-e16`. Exe: GameDaemon (2019 + PDB).

## Lifted (5 functions)

The bodies come from the Hex-Rays cache. The names come from the PDB.

| RVA | Function |
| --- | --- |
| 0x454250 | `GetEconomyCommonItemCategory` (static, `switch` on `ItemClass`) |
| 0x4542d0 | `WeaponItem::SetCount` (crash log, `Item.h` line 1447) |
| 0x454630 | `CostumeItem::SetCount` (crash log, line 1586) |
| 0x4548f0 | `GemItem::SetCount` (crash log, line 1765) |
| 0x454ad0 | `AccessoryItem::SetCount` (crash log, line 1886) |

- The `SetCount` bodies call `Log::Write` and `AlertSender::Write` of BloodLib (`lift_common_gd`). `item_h_1.cpp` includes `AlertSender.h` and `Log.h` after the GameDaemon headers. Thus the Windows macros cannot rename a GameDaemon declaration.
- The path literal is the GameDaemon `Item.h` path of the original binary (lesson A6).
- Each `SetCount` has no live caller yet. `item_h_1.cpp` has a `/INCLUDE` pragma with a `// LIFT: dead-strip keep` note for each one.
- `GetEconomyCommonItemCategory` is static in the PDB. It has no public name, so it has no pragma. The compiler drops it until a lifted caller uses it.
- `GameDaemonFwd.h` now has the PDB enumerators of `EconomyItemCategory` and `ItemClass`.

## Not done (35 functions)

The reason for each function: the source class has no members and no bases yet (Wave 0). The body reads a member at a PDB offset or calls a virtual function of another class. A later W2 card must add the layout first. The needed member is in the table.

| RVA | Function | Needed layout |
| --- | --- | --- |
| 0x454290 | `Item::~Item` | `Item` vftable and `GameObjectCounter::Instance._itemCount` (the source `GameObjectCounter` has no members) |
| 0x454330 | `AccessoryItem::GetExp` | `prop.Default.exp` (ICF fold of a getter of other item classes) |
| 0x454340 | `WeaponItem::GetMaxDurability` | `data._record` (weapon record) |
| 0x454350 | `WeaponItem::GetDurability` | `prop.Default.durability` |
| 0x454360 | `AccessoryItem::GetUsed` | `prop.Default._flags1`. The skeleton names this address `ItemBase<GroceryTrait>::GetSequestration` (ICF); it has no stub body. |
| 0x4543e0 | `WeaponItem::GetAppearanceItemDataId` | `prop.Default.appearance_item_data_id` |
| 0x454420 | `WeaponItem::GetAppearanceItemLevel` | `prop.Default.appearance_item_level` |
| 0x454460 | `WeaponItem::IsAppearanceApplied` | the vftable slots of the 2 getters |
| 0x4544d0 | `WeaponItem::R_GetEnchantConsecutiveTrial` | `prop.Remaster.enchant_consecutive_trial` |
| 0x454540 | `WeaponItem::R_GetEnchantCrack` | `prop.Remaster.enchant_crack` |
| 0x4545b0 | `WeaponItem::R_GetEnchantRestore` | `prop.Remaster.enchant_restore` |
| 0x4545f0 | `WeaponItem::GetTransformFailureExp` | `prop.Default.transform_failure_exp` |
| 0x454690 | `CostumeItem::R_GetEnchantPoint` | `prop.Remaster.enchant_point` |
| 0x4547c0 | `GroceryItem::HandleExp` | `data._record`, `prop.Default.data_id` and `Data::DataManager::Instance->_loaderDefs[114]` |
| 0x454810 | `GroceryItem::GetCount` | `prop.Default.count` |
| 0x4548b0 | `GroceryItem::R_GetEnchantPoint` | `prop.Remaster.enchant_point` |
| 0x454950 | `AccessoryItem::Locked` | `prop.Default._flags1` |
| 0x454960 | `AccessoryItem::GetLockExpirationTime` | `prop.Default.lock_expiration_time` |
| 0x454970 | `GemItem::R_GetEnchantPoint` | `prop.Remaster.enchant_point` |
| 0x4549b0 | `GemItem::R_GetEnchantConsecutiveTrial` | `prop.Remaster.enchant_consecutive_trial` |
| 0x454a20 | `GemItem::R_GetEnchantCrack` | `prop.Remaster.enchant_crack` |
| 0x454a90 | `GemItem::R_GetEnchantRestore` | `prop.Remaster.enchant_restore` |
| 0x454b30 | `AccessoryItem::GetLevel` | `prop.Default.level` |
| 0x454b80 | `AccessoryItem::GetTimeLimitType` | `prop.Default.time_limit_type` |
| 0x454b90 | `AccessoryItem::GetTimeLimitExpirationTime` | `prop.Default.time_limit_expiration_time` |
| 0x454bd0 | `AccessoryItem::GetTransformFailureExp` | `prop.Default.transform_failure_exp` |
| 0x454be0 | `AccessoryItem::R_GetEnchantPoint` | `prop.Remaster.enchant_point` |
| 0x454bf0 | `AccessoryItem::R_GetEnchantConsecutiveTrial` | `prop.Remaster.enchant_consecutive_trial` |
| 0x454c30 | `AccessoryItem::R_GetEnchantCrack` | `prop.Remaster.enchant_crack` |
| 0x454c70 | `AccessoryItem::R_GetEnchantRestore` | `prop.Remaster.enchant_restore` |
| 0x6832d0 | `ZoneTriggerEvent::NextBranch` | the `GetData` vftable slot and the `ZoneTriggerEventCond` record |
| 0x6836d0 | `ZoneTriggerNpcKilledEvent::ResetContext` | `_targetNpcCount` and `_killedCount[]` |
| 0x683780 | `ZoneTriggerNpcKilledEvent2::ResetContext` | `_killedCount` |
| 0x683bf0 | `ZoneTriggerBossChallengeTimeoutEvent::PostExecute` | `Zone::_attractionState` and the `AttractionState::PostExecute` vftable slot |
| 0x683dd0 | `ZoneTriggerBossChallengeRoundScoreEvent::PostExecute` | same as 0x683bf0 |

Nothing changed in `zonetriggerevent_cpp.cpp`.

## Gate and MATCH

The author did not run the gate or funcdiff. The driver runs them after this session.

## Changed files

- `src/Server/GameDaemon/item_h_1.cpp`
- `src/Server/GameDaemon/GameDaemonFwd.h`
- `Docs/Plan/handoffs/lift-gamedaemon-gap-016-e16.md`
