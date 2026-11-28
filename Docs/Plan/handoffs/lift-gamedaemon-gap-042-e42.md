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

## Not done

- `0x42e430` `Data::QuestDecision::QuestDecision`. The code is folded with a std::vector constructor (identical code folding). The body stays without a lift.
- `0x131560` `GuildUniform::fetchUniformInfo`. The GameDaemon sources do not declare `FragmentPacket` (packet, composer and the variadic `Compose`). A later card must add it.
- `0x2c3590` `TakeAttractionRewardTask::start`. `AttractionState` has no virtual declarations. The task class has no `_childRole` member. `ZoneInstance::_attractionState` is only a view type.
- `0x2c35e0` `ReviveByAttractionRuleTask::start`. Same reason as `0x2c3590`. It also reads a field of `RelationalRefCntObject` that is not declared.
- `0x403d60` `ActSeqState::leave`. It needs the `Npc` layout (`_brainParams`, `_detectType`, `Prop.State.effect_flag`), the brain params record field and the `ActSequence::_backupState` layout. These are not declared.

## Changed files

- `src/Server/GameDaemon/warfieldmanager.cpp`, `warfieldmanager.h`
- `src/Server/GameDaemon/guilduniform.cpp`, `guilduniform.h`
- `src/Server/GameDaemon/scripttable.cpp`, `scripttable.h`
- `src/Server/GameDaemon/duelmanager_h.cpp`, `duelmanager.h`
- `src/Server/GameDaemon/brainmonstertalkable_h.cpp`, `brainmonstertalkable.h`

## Gate and MATCH

The driver builds and runs the gate and the MATCH comparison after this session.
