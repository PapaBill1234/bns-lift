# lift-gamedaemon-e18: Easy leaves (GameDaemon): attractionstate_h, duelbotaction, attractionstate_cpp, systemaction_h, ...

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

40 functions, about 439 pseudocode lines (about 3,512 tokens). Stems: `attractionstate_h`, `duelbotaction`, `attractionstate_cpp`, `systemaction_h`, `skillaction_h`, `transactionexpirechecker`.

Wave E (owner order 2026-11-27: the easiest work first). Each function in this card is a leaf: its body calls no other counted function that needs a lift. Thus a `LIFT_STUB` callee cannot keep it DIFF. Each function has at most 30 pseudocode lines. Ease key: 11.0 cost per function (rule in `Docs/Plan/gamedaemon-lift.md` section 3).

Lift only the functions in the table. The other functions of these stems are in later W cards. Those cards depend on this card.

| n | Exe | RVA | PDB name | Stem | Lines | Form |
| ---: | --- | --- | --- | --- | ---: | --- |
| 1 | GD | `0x35ea0` | `AttractionState::CanChangeChannel` | attractionstate_h | 10 | leaf |
| 2 | GD | `0x35ec0` | `BossChallengeAttractionState::GetTypeName` | attractionstate_h | 7 | getter |
| 3 | GD | `0x35ed0` | `TendencyFieldAttractionState::GetTypeName` | attractionstate_h | 7 | getter |
| 4 | GD | `0x35ee0` | `TendencyFieldAttractionState::GetGameType` | attractionstate_h | 7 | getter |
| 5 | GD | `0x35ef0` | `DuelAttractionState::GetTypeName` | attractionstate_h | 7 | getter |
| 6 | GD | `0x35f00` | `PartyBattleFieldAttractionState::GetTypeName` | attractionstate_h | 7 | getter |
| 7 | GD | `0xa2aa0` | `DuelBotMoveAction::IsAvailableAction` | duelbotaction | 12 | leaf |
| 8 | GD | `0xa2e60` | `DuelBotMoveAction::finishAction` | duelbotaction | 8 | leaf |
| 9 | GD | `0x4d840` | `BossChallengeAttractionState::AvailableNextStep` | attractionstate_cpp | 23 | leaf |
| 10 | GD | `0x4dbd0` | `BossChallengeAttractionState::EnableInfiniteHyperEnergy` | attractionstate_cpp | 7 | getter |
| 11 | GD | `0x4dd80` | `TendencyFieldAttractionState::DrainTendencyScores` | attractionstate_cpp | 25 | leaf |
| 12 | GD | `0x4fa50` | `TendencyFieldAttractionState::IsPcSpawnWithSummoned` | attractionstate_cpp | 10 | getter |
| 13 | GD | `0x4fd30` | `TendencyFieldAttractionState::GetAdditionalBonus` | attractionstate_cpp | 26 | leaf |
| 14 | GD | `0x50120` | `TendencyFieldAttractionState::EnableInfiniteHyperEnergy` | attractionstate_cpp | 10 | leaf |
| 15 | GD | `0x501f0` | `TendencyFieldAttractionState::DisableMoveToArena` | attractionstate_cpp | 7 | leaf |
| 16 | GD | `0x50200` | `TendencyFieldAttractionState::DisableMoveToSkillTrainingRoom` | attractionstate_cpp | 7 | leaf |
| 17 | GD | `0x50210` | `TendencyFieldAttractionState::EnableChangeFactionCostume` | attractionstate_cpp | 7 | leaf |
| 18 | GD | `0x50220` | `TendencyFieldAttractionState::EnableSetGuildMeetingPlace` | attractionstate_cpp | 7 | getter |
| 19 | GD | `0x50230` | `TendencyFieldAttractionState::EnableWarpToGuildMember` | attractionstate_cpp | 7 | leaf |
| 20 | GD | `0x50a70` | `DuelAttractionState::GetGameType` | attractionstate_cpp | 10 | leaf |
| 21 | GD | `0x50dd0` | `DuelAttractionState::OnZoneAttractionEventTimer` | attractionstate_cpp | 7 | leaf |
| 22 | GD | `0x50de0` | `DuelAttractionState::CanResurrect` | attractionstate_cpp | 9 | leaf |
| 23 | GD | `0x50e10` | `DuelAttractionState::CanTakeAchievementReward` | attractionstate_cpp | 7 | getter |
| 24 | GD | `0x51260` | `PartyBattleFieldAttractionState::CanResurrect` | attractionstate_cpp | 11 | leaf |
| 25 | GD | `0x51280` | `PartyBattleFieldAttractionState::CanTakeAchievementReward` | attractionstate_cpp | 7 | leaf |
| 26 | GD | `0x51290` | `PartyBattleFieldAttractionState::CanProgressQuest` | attractionstate_cpp | 9 | leaf |
| 27 | GD | `0x512b0` | `PartyBattleFieldAttractionState::OnDead` | attractionstate_cpp | 12 | leaf |
| 28 | GD | `0x512e0` | `PartyBattleFieldAttractionState::OnDamagedEvent` | attractionstate_cpp | 13 | leaf |
| 29 | GD | `0x51320` | `PartyBattleFieldAttractionState::OnEnvManipulated` | attractionstate_cpp | 13 | leaf |
| 30 | GD | `0x51350` | `PartyBattleFieldAttractionState::OnCanceledEnvManipulation` | attractionstate_cpp | 12 | leaf |
| 31 | GD | `0x51380` | `PartyBattleFieldAttractionState::DisposeFieldItem` | attractionstate_cpp | 11 | leaf |
| 32 | GD | `0x513f0` | `PartyBattleFieldAttractionState::Leave` | attractionstate_cpp | 7 | leaf |
| 33 | GD | `0x51400` | `PartyBattleFieldAttractionState::EnableInfiniteHyperEnergy` | attractionstate_cpp | 7 | leaf |
| 34 | GD | `0x51410` | `PartyBattleFieldAttractionState::CheckToManipulateEnv` | attractionstate_cpp | 11 | leaf |
| 35 | GD | `0x51420` | `PartyBattleFieldAttractionState::TryToManipulateEnv` | attractionstate_cpp | 11 | leaf |
| 36 | GD | `0x51430` | `PartyBattleFieldAttractionState::OnEnterFootSwitch` | attractionstate_cpp | 11 | leaf |
| 37 | GD | `0x456530` | `RestorationAction::cancelAction` | systemaction_h | 11 | leaf |
| 38 | GD | `0x27560` | `TargetSelectorForDamageTransferNpcSquad::~TargetSelectorForDamageTransferNpcSquad` | skillaction_h | 23 | leaf |
| 39 | GD | `0x27600` | `SkillAction::getDashAngle` | skillaction_h | 7 | getter |
| 40 | GD | `0x225ae0` | `GameTranExpireToken::Set` | transactionexpirechecker | 29 | leaf |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/attractionstate_h.cpp`
- `src/Server/GameDaemon/attractionstate_h.h`
- `src/Server/GameDaemon/duelbotaction.cpp`
- `src/Server/GameDaemon/duelbotaction.h`
- `src/Server/GameDaemon/attractionstate_cpp.cpp`
- `src/Server/GameDaemon/attractionstate_cpp.h`
- `src/Server/GameDaemon/systemaction_h.cpp`
- `src/Server/GameDaemon/systemaction_h.h`
- `src/Server/GameDaemon/skillaction_h.cpp`
- `src/Server/GameDaemon/skillaction_h.h`
- `src/Server/GameDaemon/transactionexpirechecker.cpp`
- `src/Server/GameDaemon/transactionexpirechecker.h`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-e18.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
