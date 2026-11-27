# lift-gamedaemon-e19: Easy leaves (GameDaemon): skillaction_cpp_1, action_h, inventoryaction_cpp_1, inventoryaction_cpp_2, ...

| Item | Value |
| --- | --- |
| Exe | GD |
| Source build | GameDaemon 2019 + PDB (VS2010 SP1) |
| Exe file | `<work-root>/ida/lift/GameDaemon/GameDaemon.exe` |
| PDB | `<work-root>/ida/lift/GameDaemon/GameDaemon.pdb` |
| Pseudocode | `~/.cache/bns-lift/hr/GameDaemon/<stem>.c` |
| Pseudocode index | `~/.cache/bns-lift/hr/GameDaemon/index.tsv` (stem, rva, name, first, last, status, source file, part) |
| Wave | E |
| Model | opus |
| Depends on | `lift-gamedaemon-0e` |
| Pattern | none |
| Plan | `Docs/Plan/gamedaemon-lift.md` sections 1, 3, 5 |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Grep `Docs/Parity/lessons.md` for A2 (block order), A6 (per-exe path literals), A12 (PDB member types), A18 (destructors), A21 (PDB facts) and A22 (per-exe source form). Do not read it in full.
- Pattern: none. No lifted file has the same role.

## Scope

39 functions, about 546 pseudocode lines (about 4,368 tokens). Stems: `skillaction_cpp_1`, `action_h`, `inventoryaction_cpp_1`, `inventoryaction_cpp_2`, `geomovechecker`, `pcattractionstate_cpp`.

Wave E (owner order 2026-11-27: the easiest work first). Each function in this card is a leaf: its body calls no other counted function that needs a lift. Thus a `LIFT_STUB` callee cannot keep it DIFF. Each function has at most 30 pseudocode lines. Ease key: 14.0 cost per function (rule in `Docs/Plan/gamedaemon-lift.md` section 3).

Lift only the functions in the table. The other functions of these stems are in later W cards. Those cards depend on this card.

| n | Exe | RVA | PDB name | Stem | Lines | Form |
| ---: | --- | --- | --- | --- | ---: | --- |
| 1 | GD | `0x48da60` | `SkillAction::GetKey` | skillaction_cpp_1 | 12 | leaf |
| 2 | GD | `0x48da80` | `SkillAction::GetDataId` | skillaction_cpp_1 | 12 | leaf |
| 3 | GD | `0x48daa0` | `SkillAction::GetSkillVariationId` | skillaction_cpp_1 | 13 | leaf |
| 4 | GD | `0x48dac0` | `SkillAction::GetFlowType` | skillaction_cpp_1 | 12 | leaf |
| 5 | GD | `0x48dae0` | `SkillAction::IsSimultaneous` | skillaction_cpp_1 | 11 | leaf |
| 6 | GD | `0x49c530` | `SkillAction::stateDestroy` | skillaction_cpp_1 | 7 | leaf |
| 7 | GD | `0x1d190` | `Action::SetSlotId` | action_h | 7 | setter |
| 8 | GD | `0x1d1a0` | `Action::GetSlotId` | action_h | 7 | getter |
| 9 | GD | `0x1d1b0` | `Action::cancelAction` | action_h | 12 | leaf |
| 10 | GD | `0x96ed0` | `Action::GetCaster` | action_h | 12 | leaf |
| 11 | GD | `0x453520` | `ActionQueue::~ActionQueue` | action_h | 7 | xtor |
| 12 | GD | `0x453530` | `ActionQueue::generateInstanceId` | action_h | 13 | leaf |
| 13 | GD | `0x453580` | `PcActionQueue::GetOperation` | action_h | 10 | leaf |
| 14 | GD | `0x453590` | `DuelBotActionQueue::GetOperation` | action_h | 10 | leaf |
| 15 | GD | `0x4535b0` | `DuelBotSummonedActionQueue::getPriority` | action_h | 23 | leaf |
| 16 | GD | `0x47c7a0` | `AirDashAction::intervalAction` | inventoryaction_cpp_1 | 7 | leaf |
| 17 | GD | `0x51bc40` | `UnlockMasteryLevelAction::failAction` | inventoryaction_cpp_1 | 20 | leaf |
| 18 | GD | `0x51d330` | `EquipAction::failAction` | inventoryaction_cpp_1 | 16 | leaf |
| 19 | GD | `0x51dba0` | `UnequipAction::failAction` | inventoryaction_cpp_1 | 16 | leaf |
| 20 | GD | `0x51e660` | `RepairWithCampfireAction::failAction` | inventoryaction_cpp_2 | 16 | leaf |
| 21 | GD | `0x51fa50` | `RepairWithCampfireAction::availableCancel` | inventoryaction_cpp_2 | 7 | leaf |
| 22 | GD | `0x51fb60` | `SealItemAction::failAction` | inventoryaction_cpp_2 | 16 | leaf |
| 23 | GD | `0x51fc70` | `IdentifyItemAction::failAction` | inventoryaction_cpp_2 | 16 | leaf |
| 24 | GD | `0x51fd20` | `UnsealItemAction::failAction` | inventoryaction_cpp_2 | 7 | leaf |
| 25 | GD | `0x52c230` | `PickupAction::availableCancel` | inventoryaction_cpp_2 | 7 | getter |
| 26 | GD | `0x52c640` | `PickupAction::failAction` | inventoryaction_cpp_2 | 25 | leaf |
| 27 | GD | `0x52d0e0` | `LootAction::failAction` | inventoryaction_cpp_2 | 16 | leaf |
| 28 | GD | `0x52d340` | `GatherAction::failAction` | inventoryaction_cpp_2 | 16 | leaf |
| 29 | GD | `0x52e170` | `UseSkillSkinAcquirementItemAction::failAction` | inventoryaction_cpp_2 | 27 | leaf |
| 30 | GD | `0x52e6a0` | `PickupFieldItemAction::failAction` | inventoryaction_cpp_2 | 24 | leaf |
| 31 | GD | `0x52e720` | `PickupDeadBodyAction::availableCancel` | inventoryaction_cpp_2 | 7 | getter |
| 32 | GD | `0x52ec80` | `PutdownFieldItemAction::failAction` | inventoryaction_cpp_2 | 24 | leaf |
| 33 | GD | `0x52ed00` | `PutdownFieldItemAction::availableCancel` | inventoryaction_cpp_2 | 7 | getter |
| 34 | GD | `0x52f1c0` | `PickupDeadBodyAction::failAction` | inventoryaction_cpp_2 | 24 | leaf |
| 35 | GD | `0x52f720` | `ExpandInventoryAction::failAction` | inventoryaction_cpp_2 | 16 | leaf |
| 36 | GD | `0xd6520` | `LineIterator::X_TO_UX` | geomovechecker | 16 | leaf |
| 37 | GD | `0xd6570` | `LineIterator::Y_TO_UY` | geomovechecker | 16 | leaf |
| 38 | GD | `0x18c800` | `PcPublicRaidState::CheckResetCombatModeCoolTime` | pcattractionstate_cpp | 21 | leaf |
| 39 | GD | `0x18c880` | `PcPublicRaidState::CheckAddScoreCoolTime` | pcattractionstate_cpp | 11 | leaf |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/skillaction_cpp_1.cpp`
- `src/Server/GameDaemon/skillaction_cpp_1.h`
- `src/Server/GameDaemon/action_h.cpp`
- `src/Server/GameDaemon/action_h.h`
- `src/Server/GameDaemon/inventoryaction_cpp_1.cpp`
- `src/Server/GameDaemon/inventoryaction_cpp_1.h`
- `src/Server/GameDaemon/inventoryaction_cpp_2.cpp`
- `src/Server/GameDaemon/inventoryaction_cpp_2.h`
- `src/Server/GameDaemon/geomovechecker.cpp`
- `src/Server/GameDaemon/geomovechecker.h`
- `src/Server/GameDaemon/pcattractionstate_cpp.cpp`
- `src/Server/GameDaemon/pcattractionstate_cpp.h`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-e19.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
