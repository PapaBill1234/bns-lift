# Handoff: lift-gamedaemon-gap-019-e19 (card lift-gamedaemon-e19)

Exe: GameDaemon (2019 + PDB). Round 1. The driver does the build, the gate and the MATCH comparison.

## Lifted (12)

| RVA | Function |
| --- | --- |
| 0x18c880 | `PcPublicRaidState::CheckAddScoreCoolTime` |
| 0x1d190 | `Action::SetSlotId` |
| 0x1d1a0 | `Action::GetSlotId` |
| 0x1d1b0 | `Action::cancelAction` (4 arguments; it calls the 3-argument virtual) |
| 0x453520 | `ActionQueue::~ActionQueue` |
| 0x453530 | `ActionQueue::generateInstanceId` |
| 0x453580 | `PcActionQueue::GetOperation` |
| 0x453590 | `DuelBotActionQueue::GetOperation` |
| 0x51fa50 | `RepairWithCampfireAction::availableCancel` |
| 0x52c230 | `PickupAction::availableCancel` |
| 0x52e720 | `PickupDeadBodyAction::availableCancel` |
| 0x52ed00 | `PutdownFieldItemAction::availableCancel` |

## Layout changes

- `Action` now derives from `ZoneSerializedObject`. It has the PDB data members (+0x80 to +0x95, size 0x98).
  The virtual functions have the PDB slot order (slots 8 to 24). A slot with no lifted body is a pure placeholder.
  Slot 8 (`ZoneSerializedObject::ProcessUnexpired`) is the placeholder `lift_slot8_ProcessUnexpired` in `Action`.
- `ActionQueue` has the PDB vftable (slots 0 to 13), `MAX_INSTANCE_ID` (100), `SIMULTANEOUS_MASK` (0x80) and `instanceId` (+8).
- `PcActionQueue` and `DuelBotActionQueue` now derive from `ActionQueue` and have their PDB data members.
- `CancelActionReason` in `GameDaemonFwd.h` has the PDB enumerators.
- Each lifted function has an `/INCLUDE` dead-strip pragma with a `// LIFT:` note. The decorated names are hand-made from the source declarations. If the link fails on one name, fix that name.

## Not done (27)

| RVA | Function | Reason |
| --- | --- | --- |
| 0xd6520 | `LineIterator::X_TO_UX` | It reads `Zone::GeoZoneData` (+0x3F60) and the GeoZone terrain boundary. The `Zone` and `GeoZone` source layouts do not declare these members yet. |
| 0xd6570 | `LineIterator::Y_TO_UY` | Same as `X_TO_UX`. |
| 0x18c800 | `PcPublicRaidState::CheckResetCombatModeCoolTime` | It reads `Pc::zone`, the GeoZone data and the data table at loader slot 165. These layouts are not declared yet. |
| 0x96ed0 | `Action::GetCaster` | It reads `RelationalRefCntObject::_childRole` (+0x20). `ZoneSerializedObject` keeps this member in its `LiftBytes` base. |
| 0x4535b0 | `DuelBotSummonedActionQueue::getPriority` | It makes virtual calls on its own class and reads a word at +146. The class has no PDB base or members in the source. |
| 0x47c7a0 | `AirDashAction::intervalAction` | It calls the virtual `finishAction`. `AirDashAction` has no PDB base chain (`MoveAction`, `Action`) in the source. |
| 0x51bc40 | `UnlockMasteryLevelAction::failAction` | It calls a virtual function of the caster (file, line, 4). The class has no `Action` base and the caster vftable is not declared. |
| 0x51d330 | `EquipAction::failAction` | Same cause as 0x51bc40. |
| 0x51dba0 | `UnequipAction::failAction` | Same cause as 0x51bc40. |
| 0x51e660 | `RepairWithCampfireAction::failAction` | Same cause as 0x51bc40. |
| 0x51fb60 | `SealItemAction::failAction` | Same cause as 0x51bc40. |
| 0x51fc70 | `IdentifyItemAction::failAction` | Same cause as 0x51bc40. |
| 0x51fd20 | `UnsealItemAction::failAction` | It calls a virtual send function of `_pc`. The class members and the `Pc` vftable are not declared. |
| 0x52c640 | `PickupAction::failAction` | Same cause as 0x51bc40. |
| 0x52d0e0 | `LootAction::failAction` | Same cause as 0x51bc40. |
| 0x52d340 | `GatherAction::failAction` | Same cause as 0x51bc40. |
| 0x52e170 | `UseSkillSkinAcquirementItemAction::failAction` | Same cause as 0x51bc40. |
| 0x52e6a0 | `PickupFieldItemAction::failAction` | Same cause as 0x51bc40. |
| 0x52ec80 | `PutdownFieldItemAction::failAction` | Same cause as 0x51bc40. |
| 0x52f1c0 | `PickupDeadBodyAction::failAction` | Same cause as 0x51bc40. |
| 0x52f720 | `ExpandInventoryAction::failAction` | Same cause as 0x51bc40. |
| 0x48da60 | `SkillAction::GetKey` | It reads `SkillAction::_data3._record` and skill record fields. `SkillAction` (size 0x2050) has no source layout yet. |
| 0x48da80 | `SkillAction::GetDataId` | Same as `GetKey`. |
| 0x48daa0 | `SkillAction::GetSkillVariationId` | Same as `GetKey`. |
| 0x48dac0 | `SkillAction::GetFlowType` | Same as `GetKey`. |
| 0x48dae0 | `SkillAction::IsSimultaneous` | Same as `GetKey`. |
| 0x49c530 | `SkillAction::stateDestroy` | It calls the virtual `finishAction`. `SkillAction` has no PDB base and vftable order in the source. |

The failAction bodies of 0x51bc40 to 0x52f720 do not read the PDB members of the action (they read the bytes of the
`Action` base). They need `Action::GetCaster` (or the `ChildRole` parent) and the caster vftable slot first.

## Files changed

- `src/Server/GameDaemon/action.h`
- `src/Server/GameDaemon/action_h.cpp`
- `src/Server/GameDaemon/pcattractionstate_cpp.cpp`
- `src/Server/GameDaemon/inventoryaction_cpp_2.cpp`
- `src/Server/GameDaemon/GameDaemonFwd.h`
- `Docs/Plan/handoffs/lift-gamedaemon-gap-019-e19.md`

## Lead repair

| Function | Reject | Repair (VS2010 scratch compile: same bytes) |
| --- | --- | --- |
| `PutdownFieldItemAction::availableCancel` | P2_cc (je vs js) | `switch` with cases 0, 1 |
| `RepairWithCampfireAction::availableCancel` | P2_cc (je vs js) | `switch` with cases 0, 1, 3 |
| `PcPublicRaidState::CheckAddScoreCoolTime` | P2_cc (setge vs setle) | `duration <= elapsed ? true : false` |
