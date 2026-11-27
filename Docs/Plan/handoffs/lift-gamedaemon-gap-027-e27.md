# Handoff: lift-gamedaemon-gap-027-e27 (card lift-gamedaemon-e27)

Round 1. The work has two sessions. The driver split the round at the context limit. It committed the first session at `e0e06fd`.

## Lifted

| RVA | PDB name | File |
| --- | --- | --- |
| 0x41a220 | `Npc::GetCombatSequence` | `npc_cpp.cpp` |
| 0x41ba20 | `Npc::calculateAdditionalExpBonusByTestServer` | `npc_cpp.cpp` |
| 0x5a2ec0 | `Effect::~Effect` | `effect_cpp_1.cpp` |
| 0x5a2f30 | `Effect::GetDataSubType` | `effect_cpp_1.cpp` |
| 0x5a3fd0 | `Effect::checkImmuneDebuff` | `effect_cpp_1.cpp` |
| 0x5a62a0 | `PassiveEffect::GetRemainDuration` | `effect_cpp_1.cpp` |
| 0x2749f0 | `Creature::GetActivatedBadgeEquipSlot` | `creature_cpp_2.cpp` |
| 0x274a10 | `Creature::IsActivatedBadgeEquipSlot` | `creature_cpp_2.cpp` |
| 0x5c8620 | `EmbersExplosionTimerEffect::checkApply` | `effectcontent_cpp_2.cpp` |
| 0x5caf40 | `DashEffect::checkApply` | `effectcontent_cpp_2.cpp` |
| 0x5cbea0 | `DebuffGuildBattleFieldEffect::checkApply` | `effectcontent_cpp_2.cpp` |
| 0x5cc380 | `OceanicEffect::checkApply` | `effectcontent_cpp_2.cpp` |
| 0x5cc5f0 | `FallDeathEffect::checkApply` | `effectcontent_cpp_2.cpp` |
| 0x5cf7c0 | `MasteryStatEquipEffect::FindBlankModifyAbility` | `effectcontent_cpp_2.cpp` |
| 0x5d10a0 | `SecondGaugePointEffect::checkApply` | `effectcontent_cpp_2.cpp` |
| 0x5d13a0 | `IntervalSecondGaugePointEffect::checkApply` | `effectcontent_cpp_2.cpp` |
| 0x5d1d00 | `AccumulatedDamageEffect::checkApply` | `effectcontent_cpp_2.cpp` |
| 0x5535f0 | `WeaponItem::R_GetRandomEffectId` | `item_cpp_1.cpp` |
| 0x5536a0 | `WeaponItem::R_GetRandomEffectGroupId` | `item_cpp_1.cpp` |

Session 2 decisions:

- `item.h` has a new view `WeaponItemPropertyView`. It declares the PDB group `WeaponProperty::__remaster__` at +0xB8. `WeaponItem` has a pad (+8 to +0x2F) and the member `prop` at +0x30. The pad is the Item members and `ItemBase::data`. The base `ItemBase<WeaponTrait>` is not declared yet.
- The two `WeaponItem` getters have a `/INCLUDE` keep pragma. No lifted caller keeps them.

## Not done

| RVA | PDB name | Reason |
| --- | --- | --- |
| 0x54f780 | `Item::GetSetItemCount` | Needs the virtual `Item::GetData` (slot 14) and the `Data::ItemRecord` layout. `Item` declares only `~Item` as a virtual. `Data::ItemRecordPtr` is an empty class. |
| 0x54fa40 | `Item::CheckRuleDispose` | Same cause: `Item` vtable (GetData, GetDepot, GetSequestration) and `Data::ItemRecord` layout are not declared. |
| 0x54faa0 | `Item::CheckSell` | Same cause. |
| 0x54fb10 | `Item::CheckOldItemSell` | Same cause. |
| 0x54fbb0 | `Item::CheckMaxDurability` | Needs `Item` virtual slots 29 and 30 (GetMaxDurability, GetDurability). The `Item` vtable is not in PDB order. |
| 0x54fbf0 | `Item::CheckWardrobeStoreable` | Same cause as 0x54fa40. Also needs `RuleConfig::_enablePutGroceryIntoWardrobe`. |
| 0x54fc90 | `Item::CheckWarehouseStoreable` | Same cause as 0x54fa40. |
| 0x54fce0 | `Item::CheckBadgeDepositoryStoreable` | Same cause as 0x54fa40. |
| 0x54fed0 | `Item::checkEquipLevel` | Needs `Item::GetData`, the `Data::ItemRecord` layout and `Pc::Prop.State.level`. |
| 0x5501f0 | `Item::CheckTimeLimitItem` | Same cause as 0x54f780. |
| 0x550230 | `Item::IsExpired` | Needs `Item` virtual slots 45 and 47. The `Item` vtable is not in PDB order. |
| 0x550280 | `Item::CalculateRemainingTime` | Needs the `Item` vtable and the `Data::ItemRecord` layout. The pseudocode is not clear (❓ field at vtable offset). |
| 0x5502d0 | `Item::CheckStackable` | Same cause as 0x54fa40. Also needs `Data::ItemRecordGroceryPtr` layout. |
| 0x5503c0 | `Item::IsEquipJobNone` | Same cause as 0x54f780. |
| 0x550430 | `Item::CheckDepositInGuildBank` | Same cause as 0x54fa40. Also needs `RuleConfig::_itemLockEnable`. |
| 0x551380 | `Item::GetUsedGuildIdForGameLog` | Needs `Item::GetClass` (slot 13) and the derived item member at +0x90. |
| 0x5ccd90 | `DuelFighterChangeEffect::DuelFighterChangeEffect` | Needs the `Effect` and `InstantEffect` base layouts as a base chain and `GameObjectCounter::Instance._instantEffectCount`. `DuelFighterChangeEffect` has no base in `effectcontent.h`. |
| 0x4131c0 | `Npc::SetDespawnSocial` | Needs the `Data::DataManager` table look-up (loader 215). No lifted file declares `Data::DataManager`. `Npc` has no data members. |
| 0x41aa60 | `Npc::IsExpiredCombatTimer` | Needs `Zone` tick members, `Npc::_combatStartTime` and the brain record layout. `Npc` has no data members. |
| 0x26fad0 | `Creature::IsJoinedFaction` | Needs the `Data::DataManager` table look-up (loader 83). No lifted file declares it. |
| 0x2712e0 | `Creature::CheckToLockMasteryLevel` | Needs the `Data::DataManager` table look-up (loader 143). No lifted file declares it. |

The `Item` items need one structural card: declare the `Item` vtable in PDB order (84 slots), make `ItemBase<Trait>` and `WeaponItem` derive in the PDB chain, and declare `Data::ItemRecord`.

## Gate and MATCH

The driver builds and runs the gate and funcdiff after this session. This session did not run them.

## Files changed

- `src/Server/GameDaemon/npc_cpp.cpp`
- `src/Server/GameDaemon/effect_cpp_1.cpp`
- `src/Server/GameDaemon/creature_cpp_2.cpp`
- `src/Server/GameDaemon/effectcontent_cpp_2.cpp`
- `src/Server/GameDaemon/contentsruleconfigdefinition.cpp`
- `src/Server/GameDaemon/contentsruleconfigdefinition_gd.h`
- `src/Server/GameDaemon/item_cpp_1.cpp`
- `src/Server/GameDaemon/item.h`
- `Docs/Plan/handoffs/lift-gamedaemon-gap-027-e27.md`
