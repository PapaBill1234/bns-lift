# Handoff: lift-gamedaemon-gap-033-e33 (round 4)

Card: `lift-gamedaemon-e33`. Exe: GameDaemon (2019 + PDB).
The driver does the build, the gate and the MATCH comparison. This file does not record them.

## Lifted

| RVA | PDB name | Round |
| --- | --- | --- |
| `0x557fe0` | `AccessoryItem::R_GetRandomEffectId` | 1 |
| `0x558090` | `AccessoryItem::R_GetRandomEffectGroupId` | 1 |
| `0x558b50` | `GemItem::R_GetRandomEffectId` | 1 |
| `0x558ba0` | `GemItem::R_GetRandomEffectGroupId` | 1 |
| `0x428bc0` | `NpcParty::~NpcParty` | 1 |
| `0x428cd0` | `NpcParty::Remove` | 1 |
| `0x42d0a0` | `NpcSquad::EventOccured` | 1 |
| `0x5d7180` | `Pc::IsTryingInstantPayment` | 1 |
| `0x5e2dc0` | `Pc::SetCombatModeByTargeted` | 1 |
| `0x5e5510` | `Pc::DeactivateSkillScore` | 1 |
| `0x261e60` | `Creature::initMoveCtx` | 1 |
| `0x263a40` | `Creature::CanJoinFaction` | 1 |
| `0x264050` | `Creature::CheckCombatSideEnabled` | 1 |
| `0x265160` | `Creature::GetAbnormalState` | 1 |
| `0x428d10` | `NpcParty::SetVar` | 4 |
| `0x5e51b0` | `Pc::CalculateStyleScoreBonus` | 4 (repair) |
| `0x5d8320` | `Pc::SendRetrieveRankingRewardListFail` | 4 |
| `0x5d8390` | `Pc::SendRetrieveGuildRankingInfoFail` | 4 |
| `0x5d8400` | `Pc::SendRetrieveChallengePartyRankingInfoFail` | 4 |
| `0x5d8490` | `Pc::SendTakeRankingRewardFail` | 4 |
| `0x5d8500` | `Pc::SendRegisterCraftFail` | 4 |
| `0x5d8590` | `Pc::SendTakeCraftFail` | 4 |
| `0x5d8620` | `Pc::SendAbortCraftFail` | 4 |
| `0x5d86a0` | `Pc::SendJoinCraftUnionFail` | 4 |
| `0x5d8730` | `Pc::SendLeaveCraftUnionFail` | 4 |

Each lifted body has a dead-strip `/INCLUDE` keep pragma with a `// LIFT:` note.

## Round 4 repair

- `Pc::CalculateStyleScoreBonus` (P2_cc, build `jle`, original `jl`): the first test is now `if (0 >= style_score) return 0;`. The return variable is set to 0 before the test, and the bonus rate starts at 0. Formtest gives FORM (only the names are different). The form `style_score <= 0` gives `test`/`jle`.
- `RefCntHistory::add` (P2_cc, build `je`, original `jne`): this card does not change it. The rebase on main brings the E129 GD form (`#if defined(LIFT_EXE_GD)`). Formtest of that GD form against GD `0x693d00` gives SAME. The reject came from the earlier build before the rebase. If the reject stays, check that the GD build defines `LIFT_EXE_GD` for the BloodLib sources.

## Decisions

- `NpcSquad` now derives from `NpcParty`, as in the PDB. The `NpcParty` data members are `protected`, so that `NpcSquad` can read them.
- `NpcSquad::EventOccured` uses a local `ScriptEventView` (size 0x98, PDB layout).
- `RuleConfig` has the four `_styleScoreExp*` members (+540 to +552). `Pc` is a friend of `RuleConfig`, because no PDB accessor was found.
- `Pc` is `LiftBytes` up to +0x4E30. The `Pc::Send*Fail` bodies read `GameObject::Id` (+0x28) and `Pc::_pcDbId` (+0x4E10) through the macros `PC1_ID` and `PC1_DBID` in `pc_cpp_1.cpp`. `gamepackethandler_2.cpp` uses the same method.
- `Pc::SendAbortCraftFail` logs and sends the constant 3, not `failReason`. This is the original behavior. The source name of the constant is not known (marked `// ❓`).
- `NpcParty::SetVar` tests the index as `unsigned int`, as the original does (one compare for both bounds).
- Round 2 fix (pdb_layout): `Pc::_takingAchievementRewardLock` is an `_RTL_SRWLOCK` at +0x4F40. The `RuleConfig` gap arrays have the PDB names of their first members.

## Not done

| RVA | PDB name | Reason |
| --- | --- | --- |
| `0x558a40` | `GemItem::BroadcastEquip` | The skeleton `Pc` covers `_equipGearScore` with a padding array. The gem record field at record +0x78 is not modeled. |
| `0x558a70` | `GemItem::BroadcastUnequip` | Same reason as `GemItem::BroadcastEquip`. |
| `0x558aa0` | `GemItem::R_CheckEnchantTargetItem` | The log path is open, but the skeleton `GemItem` does not derive from `ItemBase<GemTrait>`. Its virtual slot order is not the PDB order. The calls to `GetData`, `GetPos` and `GetDepot` cannot use the original vtable slots. |
| `0x428c70` | `NpcParty::Add` | The skeleton `Npc` does not declare `_spawnInfo._spawnData`. |
| `0x42db10` | `NpcSquad::CheckLeaderlessParty` | It uses a DataManager loader table lookup (`_loaderDefs[254]`) and `NpcSquad::_squad`. The skeleton models neither of them. |
| `0x261650` | `Creature::GetExtraBroadcastOnChangePropertySize` | The log path is open, but the skeleton does not declare `GameDaemon::publisherCode` or `Creature::_extraProp`. |
| `0x2621b0` | `Creature::IsAttackable` | The log path is open, but `CreatureMemberView` does not declare `Prop.State.dead`. One PDB look-up did not give its offset. |
| `0x264350` | `Creature::IsHostileFaction` | It uses a DataManager loader table lookup (`_loaderDefs[83]`). No lifted pattern for that lookup exists yet. |
| `0x2672f0` | `Creature::CalcHeal` | The log path is open, but the skeleton does not declare the `Prop.Ability` members (`max_hp`, `max_hp_equip`, `heal_power_*`), and the `Creature` vtable does not have the PDB slot of `GetHealPowerModify`. |
| `0x5d4cc0` | `CraftInfo::~CraftInfo` | The skeleton has no `CraftInfo` / `Petition` / `RefCntObject` layout. The body also needs the `Memory::_Manager` free path. |
| `0x5db450` | `Pc::IsInTeamPartyZone` | The skeleton does not declare `GameObject::zone`, `Zone::GeoZoneData` or the `GeoZone::zoneData` record layout. |
| `0x5db4a0` | `Pc::IsInPartyBattleFieldZone` | Same reason as `Pc::IsInTeamPartyZone`. |
| `0x5db4e0` | `Pc::IsInPartyZone` | Same reason as `Pc::IsInTeamPartyZone`. |
| `0x5e1650` | `Pc::GetPcContentsType` | The skeleton does not declare `GamedConfig` arena members, `GameDaemon::arenaAttraction`, `Pc::_arenaRoom` or `Pc::_enterArenaParam`. |

## Changed files

- `src/Server/GameDaemon/creature.h`
- `src/Server/GameDaemon/creature_cpp_1.cpp`
- `src/Server/GameDaemon/gamedaemon.h`
- `src/Server/GameDaemon/item.h`
- `src/Server/GameDaemon/item_cpp_2.cpp`
- `src/Server/GameDaemon/npcparty.h`
- `src/Server/GameDaemon/npcparty_cpp.cpp`
- `src/Server/GameDaemon/npcsquad.h`
- `src/Server/GameDaemon/npcsquad.cpp`
- `src/Server/GameDaemon/pc.h`
- `src/Server/GameDaemon/pc_cpp_1.cpp`
- `src/Server/GameDaemon/ruleconfig.h`
- `Docs/Plan/handoffs/lift-gamedaemon-gap-033-e33.md`
