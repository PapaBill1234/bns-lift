# Handoff: lift-gamedaemon-gap-018-e18 (card lift-gamedaemon-e18)

Round 1 and round 2. In round 1, two sessions did the work. The driver split the first session at the context limit.

## Lifted

- `attractionstate_h`: all 6 functions (0x35ea0, 0x35ec0, 0x35ed0, 0x35ee0, 0x35ef0, 0x35f00).
- `attractionstate_cpp`: 27 of 28 functions. These include `TendencyFieldAttractionState::DrainTendencyScores` (0x4dd80).
- `systemaction_h`: `RestorationAction::cancelAction` (0x456530).
- `skillaction_h`: `TargetSelectorForDamageTransferNpcSquad::~TargetSelectorForDamageTransferNpcSquad` (0x27560), `SkillAction::getDashAngle` (0x27600).
- `transactionexpirechecker`: `GameTranExpireToken::Set` (0x225ae0).

Each lifted function with no live caller has a `/INCLUDE` dead-strip keep pragma with a `// LIFT:` note.

## Decisions

- `TendencyFieldAttractionState` now declares `_tendencyScoreLock` (+0x8) and `_tendencyScore[4]` (+0x10) from the PDB.
- Round 2: the gate failed with 4 `pdb_layout` errors. The cause: `lift_pad_*` members in PDB classes (`TendencyFieldAttractionState` two times, `SkillAction`, `GameTranExpireToken`). The layout check accepts only PDB member names in a PDB class. The fix moves the pads and the later fields to view structs: `TendencyFieldAttractionStateView` (in `attractionstate.h`), `SkillActionView` (in `skillaction_h.cpp`) and `GameTranExpireTokenView` (in `transactionexpirechecker.cpp`). The view names are not in the PDB, so the check skips them. The bodies read the fields through a cast of `this`. The offsets do not change.
- `DrainTendencyScores` uses a plain index loop. The compiler makes the pointer-delta loop of the pseudocode from it.
- Error code 1189 in `AttractionState::CanChangeChannel` has no PDB enum name. It has a `// ❓` mark.

## Not done

- `DuelBotMoveAction::IsAvailableAction` (0xa2aa0): the skeleton class has no base. The body reads the owner creature through `_childRole->_parent` (an `Action` base field) and two owner fields. The `Action` base layout and the owner fields need more than 5 look-ups. The `LIFT_STUB` stays.
- `DuelBotMoveAction::finishAction` (0xa2e60): the body is a thunk to the base `finishAction`. The skeleton class has no base class. Adding the base changes the vtable and layout of the class. A later card must add the base. The `LIFT_STUB` stays.
- `TendencyFieldAttractionState::GetAdditionalBonus` (0x4fd30): the body reads two fields of `Data::TendencyFieldRecord` and `Pc::Prop.State.activated_faction`. The record layout and the `Pc` property offsets are not declared. The look-ups need more than 5 reads. The `LIFT_STUB` stays.

## Gate and MATCH

The driver builds REF and NOREF and records the gate result and the MATCH comparison. This session did not run a build or a gate.

## Changed files

- `src/Server/GameDaemon/attractionstate.h`
- `src/Server/GameDaemon/attractionstate_cpp.cpp`
- `src/Server/GameDaemon/attractionstate_h.cpp`
- `src/Server/GameDaemon/skillaction.h`
- `src/Server/GameDaemon/skillaction_h.cpp`
- `src/Server/GameDaemon/systemaction_h.cpp`
- `src/Server/GameDaemon/transactionexpirechecker.cpp`
- `src/Server/GameDaemon/transactionexpirechecker.h`
- `Docs/Plan/handoffs/lift-gamedaemon-gap-018-e18.md`

## Lead repair

| Function | Reject | Repair |
| --- | --- | --- |
| `GameTranExpireToken::Set` | store order; its `Log::Write` call makes the GD log functions live (they are rejected until engine issue E16 is fixed) | Back to `LIFT_STUB`. The `/INCLUDE` pragma and the view structs are removed. |
| `AttractionState::CanChangeChannel` | P2_cc (je vs jne) | `0 == channel` early-return form (VS2010 scratch compile: same bytes) |
| `DuelAttractionState::GetGameType` | P2_cc (je vs jne) | null check first, call last (VS2010 scratch compile: same bytes) |

## Lead repair 2

| Function | Reject | Repair |
| --- | --- | --- |
| `RestorationAction::cancelAction` (3 arguments) | P1_calls: the 4-argument overload is at vtable +0xb0; the skeleton class has another virtual order | Back to `LIFT_STUB`; pragma removed |
| `TendencyFieldAttractionState::IsPcSpawnWithSummoned` | P1_calls: `GetGameType` is PDB slot 3 (+0x18); the skeleton class has another virtual order | Back to `LIFT_STUB`; pragma removed. Lifted body for later: `return GetGameType() == 6 (GAMETYPE_TENDENCY_FIELD_BUYUDO) && reason == 2 (ENTERREASON_REVIVE) && job == 6;` |
| `TendencyFieldAttractionState::EnableInfiniteHyperEnergy` | P2_cc (je vs jne) | `_targetType == 0` early-return form |

A later card must put the virtuals of the attraction-state and action classes in PDB slot order (`tools/pdbcls.py`).
