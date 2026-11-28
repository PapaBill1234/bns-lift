# lift-gamedaemon-gap-034-e34 handoff

Card: `lift-gamedaemon-e34` (easy leaves, GameDaemon). Round 1.

## Lifted

Each body has a dead-strip keep pragma with a `// LIFT:` note, because no live caller keeps it yet.

| Function | RVA | File | Note |
| --- | --- | --- | --- |
| `NpcPredefinedMoveAction::NpcMoveTypeName` | 0x41ca80 | `npcaction.cpp` | The PDB enumerators of `NpcMoveType` are now in `npcaction.h`. |
| `RestorationAction::availableCancel` | 0x4bde10 | `systemaction_cpp.cpp` | |
| `Action::availableCancel` | 0x468190 | `action_cpp.cpp` | Switch form. Formtest gave SAME. |
| `DuelBotActionQueue::RequestActionCancel` | 0x469f00 | `action_cpp.cpp` | The linker folds this body with `PcActionQueue::RequestActionCancel` (same member offset 0x18). |
| `DuelBotActionQueue::IntervalAction` | 0x46d330 | `action_cpp.cpp` | The linker folds this body with the other queue `IntervalAction` bodies. |

## Not done

| Function | RVA | Reason |
| --- | --- | --- |
| `RevealItemAbilityAction::failAction` | 0x52f8a0 | The body calls `ControlledCreature::Send` (slot 75) with a format string literal and variadic arguments. The PDB type is `Send(char const *, void *)`. The literal text is not in the Hex-Rays cache. |
| `AttachEquipGemPieceAction::failAction` | 0x52fa10 | Same cause as 0x52f8a0. |
| `RegisterSaleAction::OnRegisterSaleOk` | 0x53f190 | log path (E16). |
| `RegisterSaleAction::failAction` | 0x541120 | Same cause as 0x52f8a0. |
| `GetBlockState` | 0x41bbe0 | The function is file-static and has no public symbol. It has no live caller, so no `/INCLUDE` pragma can keep it. Lift it with its first caller. |
| `NpcIdleAction::IsAvailableAction` | 0x41bd70 | The repo class has no PDB base and no members (`_cancelFlag`, `_blocks`). The body also needs the `Npc` layout of the caster. |
| `NpcKnockBackAction::finishAction` | 0x41ca20 | The repo class has no PDB base (`KnockBackAction`, `WarpAction`). The body needs `Npc::_knockBackEndTime`. |
| `NpcPredefinedMoveAction::IsAvailableAction` | 0x41cc00 | The repo class has no PDB base. The body needs the `Npc` layout (`_flags`, block counts). |
| `NpcFallAction::IsAvailableAction` | 0x41dc30 | Same cause as 0x41cc00. |
| `NpcFallAction::finishAction` | 0x41e370 | log path (E16). |
| `NpcPathFindMoveAction::arrived` | 0x41f370 | The repo class has no members (`_pathOffset`, `_pathCount`). |
| `NpcFollowMoveAction::arrived` | 0x420f40 | `vector16` is an empty struct in `GameDaemonFwd.h`. A change of that shared type is out of scope for a leaf card. |
| `NpcChangeWeaponAndStanceAction::failAction` | 0x421210 | log path (E16). |
| `NpcDetectCreatureAction::failAction` | 0x421cb0 | log path (E16). |
| `PcSpawnAction::failAction` | 0x4b6e50 | log path (E16). |
| `LeaveAction::getPriority` | 0x4b7930 | The repo class `LeaveAction` has no PDB base and no members (`_reason`). The body also needs the `GameDaemon` config layout. |
| `LeaveAction::RemoveNext` | 0x4b9170 | The repo class has no members (`_prev`, `_next`). |
| `LeaveAction::intervalAction` | 0x4ba3f0 | log path (E16). |
| `LeaveAction::failAction` | 0x4baf90 | log path (E16). |
| `LeaveAction::clearChannelChangeCooltime` | 0x4bb5a0 | The repo class has no members (`_reason`). The body needs a `Pc` member at a fixed offset. |
| `ReviveAction::finishAction` | 0x4bc0e0 | log path (E16). |
| `ReviveAction::failAction` | 0x4bc1f0 | log path (E16). |
| `RestorationAction::failAction` | 0x4bd3d0 | Same cause as 0x52f8a0. |
| `HelpRestorationAction::failAction` | 0x4be310 | The body calls two caster virtuals and `Send` with the format `"hEc"`. The repo `ControlledCreature` header does not give these slots. |
| `Action::startAction` | 0x468070 | The body calls `ActionQueue::ActionStarted` through the caster member at offset 0x8C0. The repo `Creature` class has no such member yet. |
| `Action::changePriority` | 0x4680a0 | Same cause as 0x468070 (`ActionChangedPriority`). |
| `NoAction::intervalAction` | 0x468350 | log path (E16). |
| `NoOpAction::intervalAction` | 0x468390 | log path (E16). |
| `NoMoveAction::intervalAction` | 0x4683d0 | log path (E16). |
| `ActionFactory::~ActionFactory` | 0x468410 | The repo class has no members (`nullAction`, `noopAction`, `nomvAction`). |
| `PcActionQueue::getSimOpSlotId` | 0x46abd0 | The body reads the private `Action::_actionClass`. The enum `ActionClass` has no enumerators in the repo. |
| `PcActionQueue::getPriority` | 0x46ac60 | The body needs `ACTION_CATEGORIES` and `PcActionQueue::OPERATION_PRIORITIES`. The pseudocode of the index form is not clear. |
| `NpcActionQueue::RequestActionCancel` | 0x46b210 | The repo class has no PDB base and no members (`_currentAction`). |
| `SummonedActionQueue::~SummonedActionQueue` | 0x46b970 | The repo class has no PDB base and no members (`_currentAction`, `_simOperation`). |
| `DuelBotSummonedActionQueue::~DuelBotSummonedActionQueue` | 0x46d110 | Same cause as 0x46b970. |

## Gate and MATCH

The driver builds the code and runs the gate and parity checks after this session. This session did not record a gate result or MATCH counts.

## Changed files

- `src/Server/GameDaemon/npcaction.h`
- `src/Server/GameDaemon/npcaction.cpp`
- `src/Server/GameDaemon/systemaction_cpp.cpp`
- `src/Server/GameDaemon/action_cpp.cpp`
- `Docs/Plan/handoffs/lift-gamedaemon-gap-034-e34.md`
