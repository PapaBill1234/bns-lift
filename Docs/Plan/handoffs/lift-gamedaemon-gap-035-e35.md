# lift-gamedaemon-gap-035-e35 handoff

Card: `lift-gamedaemon-e35` (easy leaves, GameDaemon).

## Lifted

### skillaction_cpp_2

- 0x4a6550 `SkillAction::getConsumePoint`. The enumerator names of `Data::SkillPointTypeType` are not in the skeleton, so the cases use the values 0 to 5 (marked ❓).
- 0x4acc40 `TargetSkillAction::SucceedTargetInfo`.
- 0x4af2f0 `ChainSkillAction::SucceedTargetInfo`.
- 0x4b09e0 `NoneTargetSkillAction::SucceedTargetInfo`.

### manipulateaction_cpp

- 0x4791d0 `FishManipulateAction::convertFailReason`. The fail reason values have no names in the skeleton (marked ❓).

Each body has an `/INCLUDE` keep pragma (no live caller yet).
`skillaction.h` now gives `TargetSkillAction`, `ChainSkillAction` and `NoneTargetSkillAction` a partial PDB layout:
a `LiftBytes` base for base `SkillAction` (+8 to +0xB7), `_targetId` (+0xB8), a ❓ gap to +0x2050, and the PDB members that the bodies use.

## Not done

### moveaction_cpp

| RVA | Function | Reason |
| --- | --- | --- |
| 0x47c010 | `WarpAction::adjustZ` | log path (E16) |
| 0x4839a0 | `MoveAction::intervalAction` | log path (E16) |
| 0x4839c0 | `MoveAction::finishAction` | log path (E16) |
| 0x489e40 | `SummonMoveAction::intervalAction` | log path (E16) |
| 0x489e60 | `SummonMoveAction::finishAction` | log path (E16) |
| 0x47cc20 | `WarpToGuildMemberAction::failAction` | Blocked. The body inlines `Action::GetCaster` (`_childRole` +0x20 has no name in the skeleton) and calls the variadic `ControlledCreature::Send(char const *, ...)` (vtable slot 75). The skeleton `ControlledCreature` has no members. The `types.h` form shows the varargs as `void *`. The format string literal is not known. |
| 0x47e140 | `CallGuildMemberAction::failAction` | Same cause as 0x47cc20. |
| 0x47f290 | `WarpToGuildMeetingPlaceAction::failAction` | Same cause as 0x47cc20. |
| 0x480c90 | `TeleportAction::failAction` | Same cause as 0x47cc20 (format `"hEq"`, packet 1179). |
| 0x48cbc0 | `EscapeFromCaveAction::failAction` | Same cause as 0x47cc20. |
| 0x47f4b0 | `RecallSummonAction::prepareAction` | Same cause as 0x47cc20. It also calls an unnamed virtual (slot 10) on a creature member at +0x8C0. |

### skillaction_cpp_2

| RVA | Function | Reason |
| --- | --- | --- |
| 0x4a7f80 | `SkillAction::getTargetAngle` | The body reads fields of the `_data3` skill record. The skeleton has no `SkillAction` members and no record layout. |
| 0x4aa1c0 | `SkillAction::calculateRange` | The body reads `GameObject` type (+0x2E), a creature field (+0x908) and calls a `GameObject` virtual (slot 20). The skeleton `GameObject` has no members. |
| 0x4abf30 | `SkillAction::addGatherTarget` | The body reads `_gatherRangeData` record fields and `_flowStep`. The skeleton `SkillAction` has no members. |
| 0x4ac080 | `SkillAction::getSkillInstanceIdForGameLog` | The body reads `_zoneInstance` and `Zone::_skillInstanceIdForGameLog`. The skeleton classes have no members. |
| 0x4ac100 | `CasterSkillAction::SucceedTargetInfo` | The body inlines `Action::GetCaster`, which is a stub (`_childRole` has no name yet). |
| 0x4adc20 | `GroundRadiusSkillAction::SucceedTargetInfo` | The body copies `_targetPosition` (`vector16`). The skeleton `vector16` is an empty struct, so the copy cannot match. |
| 0x4b09d0 | `NoneTargetSkillAction::isExecutable` | The body is a virtual call to `isFlyable(0)`. The skeleton vtable order is not the PDB order, so the slot does not match. |

### manipulateaction_cpp

| RVA | Function | Reason |
| --- | --- | --- |
| 0x475440 | `ManipulateAction::failAction` | Same cause as 0x47cc20: caster access (`_childRole`) and the variadic `Send` on a skeleton class. |
| 0x476800 | `NpcManipulateAction::failAction` | Same cause as 0x475440. |
| 0x476d60 | `GiveFactionScoreToRefinerAction::failAction` | Same cause as 0x475440. |
| 0x479230 | `ManipulateActionGameLog::GetFishingFieldId` | The body reads `Env::_env2` record fields and calls a `DataManager` loader table virtual (loader 90). The skeleton has no `Env` record layout and no `DataManager` table accessor. |
| 0x479280 | `ManipulateActionGameLog::GetFishingPasteId` | The body calls the `Item::GetData` virtual and a `DataManager` loader table virtual (loader 91). The skeleton has no layout for these. |

### reaction

| RVA | Function | Reason |
| --- | --- | --- |
| 0x4629d0 | `PatternStartReaction::Do` | The body reads `ScriptEvent::zone`, `Zone::_attractionState` and calls the `AttractionState::PatternStart` virtual. The skeleton classes have no members and no PDB vtable order. |
| 0x462a00 | `PatternSuccessReaction::Do` | Same cause as 0x4629d0 (`AttractionState::PatternFinish`). |
| 0x462d80 | `ReactionFactory::clear` | The body needs `ReactionFactory::Reactions[78]`, the `Reaction` destructor slot and the `Memory::_Manager` free form. The skeleton has no layout for these. |

### duelbotchallengeattractionstate_cpp

| RVA | Function | Reason |
| --- | --- | --- |
| 0xa51e0 | `DuelBotChallengeAttractionState::getStartFloor` | log path (E16) |
| 0xa7610 | `DuelBotChallengeGameLog::getEffectKey` | The body returns addresses of `DuelBotChallenge` record fields. The skeleton has no record layout. |
| 0xae770 | `DuelBotChallengeGameLog::getPcAttackPower` | The body reads `Pc::Prop.Ability` fields. The partial `Pc` layout does not declare `Prop`. |

### challengepartyattractionstate_cpp

| RVA | Function | Reason |
| --- | --- | --- |
| 0x6c300 | `ChallengePartyAttractionState::OnDamagedEvent` | The body reads `_state`, `_challengePartyId`, `_receivedDamage`, creature `Id` and `Prop.State.challenge_party_id`. The skeleton classes have no members. |
| 0x6ee50 | `ChallengePartyAttractionState::initPatternScore` | The body writes the `_pattern*` members and the `ZoneScore` members of `Zone::_score`. The skeleton classes have no members. |
| 0x6f370 | `ChallengePartyAttractionState::~ChallengePartyAttractionState` | The body releases `_challengeParty` (`Pointer2<ChallengeParty>`) and restores the base `AttractionState` vtable. The skeleton class has no members and no base. |
| 0x6f3e0 | `ChallengePartyAttractionState::CanTeamAttractionWithTarget` | log path (E16) |

## Files changed

- `src/Server/GameDaemon/skillaction.h`
- `src/Server/GameDaemon/skillaction_cpp_2.cpp`
- `src/Server/GameDaemon/manipulateaction_cpp.cpp`
- `Docs/Plan/handoffs/lift-gamedaemon-gap-035-e35.md`

## Gate and MATCH

The driver builds and runs the gate and the parity check after this session. This session did not build.
