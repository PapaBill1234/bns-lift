# lift-gamedaemon-e34: Easy leaves (GameDaemon): inventoryaction_cpp_3, npcaction, action_cpp, systemaction_cpp, ...

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
- Dead-strip: `wmain` and most callers are still `LIFT_STUB` bodies. `/OPT:REF` removes a lifted function that has no live caller, and funcdiff then cannot pair it. For each function in scope with no live caller, add `#pragma comment(linker, "/INCLUDE:<public name>")` in its `.cpp` (public names: `llvm-pdbutil dump -publics`; grep `/INCLUDE` in `Docs/Parity/lessons.md`). Do not add a pragma for a function that a lifted caller keeps.

## Scope

40 functions, about 711 pseudocode lines (about 5,688 tokens). Stems: `inventoryaction_cpp_3`, `npcaction`, `action_cpp`, `systemaction_cpp`, `inventoryaction_cpp_4`.

Wave E (owner order 2026-11-27: the easiest work first). Each function in this card is a leaf: its body calls no other counted function that needs a lift. Thus a `LIFT_STUB` callee cannot keep it DIFF. Each function has at most 30 pseudocode lines. Ease key: 17.8 cost per function (rule in `Docs/Plan/gamedaemon-lift.md` section 3).

Lift only the functions in the table. The other functions of these stems are in later W cards. Those cards depend on this card.

| n | Exe | RVA | PDB name | Stem | Lines | Form |
| ---: | --- | --- | --- | --- | ---: | --- |
| 1 | GD | `0x52f8a0` | `RevealItemAbilityAction::failAction` | inventoryaction_cpp_3 | 16 | leaf |
| 2 | GD | `0x52fa10` | `AttachEquipGemPieceAction::failAction` | inventoryaction_cpp_3 | 16 | leaf |
| 3 | GD | `0x41bbe0` | `GetBlockState` | npcaction | 16 | leaf |
| 4 | GD | `0x41bd70` | `NpcIdleAction::IsAvailableAction` | npcaction | 22 | leaf |
| 5 | GD | `0x41ca20` | `NpcKnockBackAction::finishAction` | npcaction | 13 | leaf |
| 6 | GD | `0x41ca80` | `NpcPredefinedMoveAction::NpcMoveTypeName` | npcaction | 19 | leaf |
| 7 | GD | `0x41cc00` | `NpcPredefinedMoveAction::IsAvailableAction` | npcaction | 14 | leaf |
| 8 | GD | `0x41dc30` | `NpcFallAction::IsAvailableAction` | npcaction | 12 | leaf |
| 9 | GD | `0x41e370` | `NpcFallAction::finishAction` | npcaction | 27 | leaf |
| 10 | GD | `0x41f370` | `NpcPathFindMoveAction::arrived` | npcaction | 10 | getter |
| 11 | GD | `0x420f40` | `NpcFollowMoveAction::arrived` | npcaction | 7 | getter |
| 12 | GD | `0x421210` | `NpcChangeWeaponAndStanceAction::failAction` | npcaction | 20 | leaf |
| 13 | GD | `0x421cb0` | `NpcDetectCreatureAction::failAction` | npcaction | 18 | leaf |
| 14 | GD | `0x468070` | `Action::startAction` | action_cpp | 15 | leaf |
| 15 | GD | `0x4680a0` | `Action::changePriority` | action_cpp | 15 | leaf |
| 16 | GD | `0x468190` | `Action::availableCancel` | action_cpp | 7 | getter |
| 17 | GD | `0x468350` | `NoAction::intervalAction` | action_cpp | 15 | leaf |
| 18 | GD | `0x468390` | `NoOpAction::intervalAction` | action_cpp | 15 | leaf |
| 19 | GD | `0x4683d0` | `NoMoveAction::intervalAction` | action_cpp | 15 | leaf |
| 20 | GD | `0x468410` | `ActionFactory::~ActionFactory` | action_cpp | 28 | leaf |
| 21 | GD | `0x469f00` | `DuelBotActionQueue::RequestActionCancel` | action_cpp | 7 | leaf |
| 22 | GD | `0x46abd0` | `PcActionQueue::getSimOpSlotId` | action_cpp | 29 | leaf |
| 23 | GD | `0x46ac60` | `PcActionQueue::getPriority` | action_cpp | 29 | leaf |
| 24 | GD | `0x46b210` | `NpcActionQueue::RequestActionCancel` | action_cpp | 7 | leaf |
| 25 | GD | `0x46b970` | `SummonedActionQueue::~SummonedActionQueue` | action_cpp | 30 | leaf |
| 26 | GD | `0x46d110` | `DuelBotSummonedActionQueue::~DuelBotSummonedActionQueue` | action_cpp | 30 | leaf |
| 27 | GD | `0x46d330` | `DuelBotActionQueue::IntervalAction` | action_cpp | 7 | leaf |
| 28 | GD | `0x4b6e50` | `PcSpawnAction::failAction` | systemaction_cpp | 18 | leaf |
| 29 | GD | `0x4b7930` | `LeaveAction::getPriority` | systemaction_cpp | 19 | leaf |
| 30 | GD | `0x4b9170` | `LeaveAction::RemoveNext` | systemaction_cpp | 18 | leaf |
| 31 | GD | `0x4ba3f0` | `LeaveAction::intervalAction` | systemaction_cpp | 12 | leaf |
| 32 | GD | `0x4baf90` | `LeaveAction::failAction` | systemaction_cpp | 24 | leaf |
| 33 | GD | `0x4bb5a0` | `LeaveAction::clearChannelChangeCooltime` | systemaction_cpp | 19 | leaf |
| 34 | GD | `0x4bc0e0` | `ReviveAction::finishAction` | systemaction_cpp | 25 | leaf |
| 35 | GD | `0x4bc1f0` | `ReviveAction::failAction` | systemaction_cpp | 23 | leaf |
| 36 | GD | `0x4bd3d0` | `RestorationAction::failAction` | systemaction_cpp | 16 | leaf |
| 37 | GD | `0x4bde10` | `RestorationAction::availableCancel` | systemaction_cpp | 7 | getter |
| 38 | GD | `0x4be310` | `HelpRestorationAction::failAction` | systemaction_cpp | 26 | leaf |
| 39 | GD | `0x53f190` | `RegisterSaleAction::OnRegisterSaleOk` | inventoryaction_cpp_4 | 29 | leaf |
| 40 | GD | `0x541120` | `RegisterSaleAction::failAction` | inventoryaction_cpp_4 | 16 | leaf |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/inventoryaction_cpp_3.cpp`
- `src/Server/GameDaemon/inventoryaction_cpp_3.h`
- `src/Server/GameDaemon/npcaction.cpp`
- `src/Server/GameDaemon/npcaction.h`
- `src/Server/GameDaemon/action_cpp.cpp`
- `src/Server/GameDaemon/action_cpp.h`
- `src/Server/GameDaemon/systemaction_cpp.cpp`
- `src/Server/GameDaemon/systemaction_cpp.h`
- `src/Server/GameDaemon/inventoryaction_cpp_4.cpp`
- `src/Server/GameDaemon/inventoryaction_cpp_4.h`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-e34.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
