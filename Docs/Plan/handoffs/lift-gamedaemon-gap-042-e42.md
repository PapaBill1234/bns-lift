# lift-gamedaemon-gap-042-e42 handoff

Card: Easy leaves (GameDaemon), wave E. Round 1.

## Lifted

- `0x226d70` `WarFieldGroup::getDataKey`
- `0x131db0` `GuildUniform::EnableRegisterGuildUniform`
- `0x1324a0` `GuildUniformManager::GetRegisteredUniformCount`
- `0x467060` `Data::FilterSet::FilterSet`
- `0x467080` `Data::FilterSet::~FilterSet`
- `0x4670f0` `Data::ReactionSet::ReactionSet`
- `0x467110` `Data::ReactionSet::~ReactionSet`
- `0x467380` `Data::ObjectScript::GetDecisionSequence`
- `0x97070` `DuelManager::isSaveGameResult`
- `0x630e0` `BrainMonsterTalkable::GetState`. The state members are byte views at their PDB offsets. The base BrainBase and the state classes are not declared yet.
- `0x27bb0` `DuelTeam::DuelTeam`
- `0x36c580` `GameObject::Think`
- `0x36c5c0` `GameObject::OnTimer`
- `0x1909e0` `PetitionPacketBufferHandler::Destroy`
- `0x190a90` `PetitionPacketBufferHandler::ToBuffer`
- `0x190c10` `PetitionPacketBufferHandler::Decompose`
- `0x1a8360` `RaidDungeon::GetOccupyingObjectId`
- `0x1a94a0` `RaidDungeon::IsBound`
- `0x1aa220` `RaidDungeonManager::RaidDungeonManager`
- `0x1aa2d0` `RaidDungeonManager::~RaidDungeonManager`
- `0x1ab2e0` `RaidDungeonPropertyContainer::RaidDungeonPropertyContainer`
- `0x202980` `TeamManager::unlock`. `TeamManager::TeamMgrLockCount` is a thread-local static member. The body decrements it after it leaves the lock.
- `0x2062f0` `Team::GetPartyDifficultyType`
- `0x206320` `Team::GetPartyMemberCount`
- `0x207970` `Team::GetPartyDungeonStep`. The inlined `TeamParty::GetDungeonStep` is written in place.
- `0x2079e0` `Team::GetPartyChallengePartyAttractionId`
- `0x207a40` `Team::PartyIsInChallengePartyAttraction`
- `0x207cb0` `Team::IsPublishedRecruitArenaDungeonPartyMember`
- `0x20e710` `Team::findEmptyPartyIndex`
- `0x20f150` `Team::setVisible`. The 2019 body does not read the parameter. It logs 1 and stores true. This is marked `// ❓`.
- The Team bodies read the members through byte views (`TeamView`, `TeamPartyView`, `TeamManagerView` in `team.h`), because these classes have no PDB members in the sources yet. The `/INCLUDE` names are hand-mangled. If the link fails, check them with `pdbpub.py`.

## Round 3 repair

- The build failed on `#include <list>` in `duelmanager.h`. The lift build has no STL headers. `DuelTeam::DuelMembers` is now a layout struct of the PDB `std::list` (`lift_alval` +0, `_Myhead` +8, `_Mysize` +0x10, with a `Node` type).
- `DuelTeam::DuelTeam` (0x27bb0) now writes the inlined list constructor by hand. It sets `_Mysize` to 0 and takes the 24-byte head node from `Memory::_Manager[2]`. It links the node to itself.
- `GuildUniform::fetchUniformInfo` (0x131560) stays Not done. See below.

## Not done

- `0x42e430` `Data::QuestDecision::QuestDecision`. The code is folded with a std::vector constructor (identical code folding). The body stays without a lift.
- `0x131560` `GuildUniform::fetchUniformInfo`. The GameDaemon sources do not declare `FragmentPacket` (packet, composer and the variadic `Compose`). A later card must add it.
- `0x2c3590` `TakeAttractionRewardTask::start`. `AttractionState` has no virtual declarations. The task class has no `_childRole` member. `ZoneInstance::_attractionState` is only a view type.
- `0x2c35e0` `ReviveByAttractionRuleTask::start`. Same reason as `0x2c3590`. It also reads a field of `RelationalRefCntObject` that is not declared.
- `0x27d60` `DuelTeam::instantiateDuelMember`. The first session stopped at the context split before this body. It keeps its `LIFT_STUB`.
- `0x36d500` `GameObjectTimer::TimerExpired`. The first session stopped at the context split before this body. It keeps its `LIFT_STUB`.
- `0x190990` `PetitionPacketBufferHandler::Clone`. The first session stopped at the context split before this body. It keeps its `LIFT_STUB`.
- `0x1a71c0` `RaidDungeon::GetMaxUnbindCount`. The first session stopped at the context split before this body. It keeps its `LIFT_STUB`.
- `0x1aaf70` `RaidDungeonManager::GetRaidDungeonPtrById`. The first session stopped at the context split before this body. It keeps its `LIFT_STUB`.
- `0x403d60` `ActSeqState::leave`. It needs the `Npc` layout (`_brainParams`, `_detectType`, `Prop.State.effect_flag`), the brain params record field and the `ActSequence::_backupState` layout. These are not declared.

## Changed files

- `src/Server/GameDaemon/warfieldmanager.cpp`, `warfieldmanager.h`
- `src/Server/GameDaemon/guilduniform.cpp`, `guilduniform.h`
- `src/Server/GameDaemon/scripttable.cpp`, `scripttable.h`
- `src/Server/GameDaemon/duelmanager_h.cpp`, `duelmanager.h`
- `src/Server/GameDaemon/brainmonstertalkable_h.cpp`, `brainmonstertalkable.h`
- `src/Server/GameDaemon/gameobject_cpp.cpp`
- `src/Server/GameDaemon/petitionpacketbufferhandler.cpp`
- `src/Server/GameDaemon/raiddungeon.cpp`, `raiddungeon.h`
- `src/Server/GameDaemon/team_cpp_2.cpp`, `team.h`

## Gate and MATCH

The driver builds and runs the gate and the MATCH comparison after this session.
