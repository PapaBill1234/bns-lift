# Handoff: lift-gamedaemon-gap-033-e33 (round 1)

Card: `lift-gamedaemon-e33`. Exe: GameDaemon (2019 + PDB).
Two sessions did this round. The driver split the work at the context limit.
The driver does the build, the gate and the MATCH comparison. This file does not record them.

## Lifted

| RVA | PDB name |
| --- | --- |
| `0x557fe0` | `AccessoryItem::R_GetRandomEffectId` |
| `0x558090` | `AccessoryItem::R_GetRandomEffectGroupId` |
| `0x558b50` | `GemItem::R_GetRandomEffectId` |
| `0x558ba0` | `GemItem::R_GetRandomEffectGroupId` |
| `0x428bc0` | `NpcParty::~NpcParty` |
| `0x428cd0` | `NpcParty::Remove` |
| `0x42d0a0` | `NpcSquad::EventOccured` |
| `0x5d7180` | `Pc::IsTryingInstantPayment` |
| `0x5e2dc0` | `Pc::SetCombatModeByTargeted` |
| `0x5e5510` | `Pc::DeactivateSkillScore` |
| `0x5e51b0` | `Pc::CalculateStyleScoreBonus` |
| `0x261e60` | `Creature::initMoveCtx` |
| `0x263a40` | `Creature::CanJoinFaction` |
| `0x264050` | `Creature::CheckCombatSideEnabled` |
| `0x265160` | `Creature::GetAbnormalState` |

Each lifted body has a dead-strip `/INCLUDE` keep pragma with a `// LIFT:` note.

## Decisions

- `NpcSquad` now derives from `NpcParty`, as in the PDB. The `NpcParty` data members are now `protected`, so that `NpcSquad` can read them. The `NpcSquad` members `_squad` and `_npc[20]` are not declared yet.
- `NpcSquad::EventOccured` uses a local `ScriptEventView` (size 0x98, PDB layout). The skeleton `ScriptEvent` has no members yet.
- `Pc::CalculateStyleScoreBonus` reads `Prop.State.style_score` through `CreatureMemberView`, because the skeleton `Pc` has no `Creature` base yet. `RuleConfig` has the four `_styleScoreExp*` members now (+540 to +552). `Pc` is a friend of `RuleConfig`, because no PDB accessor was found.
- Round 2 fix (pdb_layout): `Pc::_takingAchievementRewardLock` is now an `_RTL_SRWLOCK` at +0x4F40. The gap after it starts at +0x4F48 and has the PDB name `_isTakingAchievementReward`. The two `RuleConfig` gap arrays now have the PDB names of their first members (`_usePcContentsTypeDungeonEnable` at +0, `_useReserveFactionReputation` at +84).

## Not done

| RVA | PDB name | Reason |
| --- | --- | --- |
| `0x558a40` | `GemItem::BroadcastEquip` | The skeleton `Pc` covers `_equipGearScore` with a padding array. The gem record field at record +0x78 is not modeled. |
| `0x558a70` | `GemItem::BroadcastUnequip` | Same reason as `GemItem::BroadcastEquip`. |
| `0x558aa0` | `GemItem::R_CheckEnchantTargetItem` | log path (E16) |
| `0x428c70` | `NpcParty::Add` | The skeleton `Npc` does not declare `_spawnInfo._spawnData`. |
| `0x428d10` | `NpcParty::SetVar` | log path (E16) |
| `0x42db10` | `NpcSquad::CheckLeaderlessParty` | It uses a DataManager loader table lookup (`_loaderDefs[254]`) and `NpcSquad::_squad`. The skeleton models neither of them. |
| `0x261650` | `Creature::GetExtraBroadcastOnChangePropertySize` | log path (E16) |
| `0x2621b0` | `Creature::IsAttackable` | log path (E16) |
| `0x264350` | `Creature::IsHostileFaction` | It uses a DataManager loader table lookup (`_loaderDefs[83]`). No lifted pattern for that lookup exists yet. |
| `0x2672f0` | `Creature::CalcHeal` | log path (E16) |
| `0x5d4cc0` | `CraftInfo::~CraftInfo` | The skeleton has no `CraftInfo` / `Petition` / `RefCntObject` layout. The body also needs the `Memory::_Manager` free path. |
| `0x5d8320` | `Pc::SendRetrieveRankingRewardListFail` | log path (E16) |
| `0x5d8390` | `Pc::SendRetrieveGuildRankingInfoFail` | log path (E16) |
| `0x5d8400` | `Pc::SendRetrieveChallengePartyRankingInfoFail` | log path (E16) |
| `0x5d8490` | `Pc::SendTakeRankingRewardFail` | log path (E16) |
| `0x5d8500` | `Pc::SendRegisterCraftFail` | log path (E16) |
| `0x5d8590` | `Pc::SendTakeCraftFail` | log path (E16) |
| `0x5d8620` | `Pc::SendAbortCraftFail` | log path (E16) |
| `0x5d86a0` | `Pc::SendJoinCraftUnionFail` | log path (E16) |
| `0x5d8730` | `Pc::SendLeaveCraftUnionFail` | log path (E16) |
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
