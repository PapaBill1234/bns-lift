# lift-gamedaemon-e35: Easy leaves (GameDaemon): moveaction_cpp, skillaction_cpp_2, manipulateaction_cpp, reaction, ...

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

38 functions, about 779 pseudocode lines (about 6,232 tokens). Stems: `moveaction_cpp`, `skillaction_cpp_2`, `manipulateaction_cpp`, `reaction`, `duelbotchallengeattractionstate_cpp`, `challengepartyattractionstate_cpp`.

Wave E (owner order 2026-11-27: the easiest work first). Each function in this card is a leaf: its body calls no other counted function that needs a lift. Thus a `LIFT_STUB` callee cannot keep it DIFF. Each function has at most 30 pseudocode lines. Ease key: 20.5 cost per function (rule in `Docs/Plan/gamedaemon-lift.md` section 3).

Lift only the functions in the table. The other functions of these stems are in later W cards. Those cards depend on this card.

| n | Exe | RVA | PDB name | Stem | Lines | Form |
| ---: | --- | --- | --- | --- | ---: | --- |
| 1 | GD | `0x47c010` | `WarpAction::adjustZ` | moveaction_cpp | 30 | leaf |
| 2 | GD | `0x47cc20` | `WarpToGuildMemberAction::failAction` | moveaction_cpp | 16 | leaf |
| 3 | GD | `0x47e140` | `CallGuildMemberAction::failAction` | moveaction_cpp | 16 | leaf |
| 4 | GD | `0x47f290` | `WarpToGuildMeetingPlaceAction::failAction` | moveaction_cpp | 18 | leaf |
| 5 | GD | `0x47f4b0` | `RecallSummonAction::prepareAction` | moveaction_cpp | 21 | leaf |
| 6 | GD | `0x480c90` | `TeleportAction::failAction` | moveaction_cpp | 17 | leaf |
| 7 | GD | `0x4839a0` | `MoveAction::intervalAction` | moveaction_cpp | 11 | leaf |
| 8 | GD | `0x4839c0` | `MoveAction::finishAction` | moveaction_cpp | 29 | leaf |
| 9 | GD | `0x489e40` | `SummonMoveAction::intervalAction` | moveaction_cpp | 11 | leaf |
| 10 | GD | `0x489e60` | `SummonMoveAction::finishAction` | moveaction_cpp | 29 | leaf |
| 11 | GD | `0x48cbc0` | `EscapeFromCaveAction::failAction` | moveaction_cpp | 16 | leaf |
| 12 | GD | `0x4a6550` | `SkillAction::getConsumePoint` | skillaction_cpp_2 | 28 | leaf |
| 13 | GD | `0x4a7f80` | `SkillAction::getTargetAngle` | skillaction_cpp_2 | 21 | leaf |
| 14 | GD | `0x4aa1c0` | `SkillAction::calculateRange` | skillaction_cpp_2 | 25 | leaf |
| 15 | GD | `0x4abf30` | `SkillAction::addGatherTarget` | skillaction_cpp_2 | 25 | leaf |
| 16 | GD | `0x4ac080` | `SkillAction::getSkillInstanceIdForGameLog` | skillaction_cpp_2 | 20 | leaf |
| 17 | GD | `0x4ac100` | `CasterSkillAction::SucceedTargetInfo` | skillaction_cpp_2 | 22 | leaf |
| 18 | GD | `0x4acc40` | `TargetSkillAction::SucceedTargetInfo` | skillaction_cpp_2 | 17 | leaf |
| 19 | GD | `0x4adc20` | `GroundRadiusSkillAction::SucceedTargetInfo` | skillaction_cpp_2 | 18 | leaf |
| 20 | GD | `0x4af2f0` | `ChainSkillAction::SucceedTargetInfo` | skillaction_cpp_2 | 17 | leaf |
| 21 | GD | `0x4b09d0` | `NoneTargetSkillAction::isExecutable` | skillaction_cpp_2 | 7 | leaf |
| 22 | GD | `0x4b09e0` | `NoneTargetSkillAction::SucceedTargetInfo` | skillaction_cpp_2 | 16 | leaf |
| 23 | GD | `0x475440` | `ManipulateAction::failAction` | manipulateaction_cpp | 20 | leaf |
| 24 | GD | `0x476800` | `NpcManipulateAction::failAction` | manipulateaction_cpp | 16 | leaf |
| 25 | GD | `0x476d60` | `GiveFactionScoreToRefinerAction::failAction` | manipulateaction_cpp | 18 | leaf |
| 26 | GD | `0x4791d0` | `FishManipulateAction::convertFailReason` | manipulateaction_cpp | 25 | leaf |
| 27 | GD | `0x479230` | `ManipulateActionGameLog::GetFishingFieldId` | manipulateaction_cpp | 21 | leaf |
| 28 | GD | `0x479280` | `ManipulateActionGameLog::GetFishingPasteId` | manipulateaction_cpp | 23 | leaf |
| 29 | GD | `0x4629d0` | `PatternStartReaction::Do` | reaction | 17 | leaf |
| 30 | GD | `0x462a00` | `PatternSuccessReaction::Do` | reaction | 21 | leaf |
| 31 | GD | `0x462d80` | `ReactionFactory::clear` | reaction | 24 | leaf |
| 32 | GD | `0xa51e0` | `DuelBotChallengeAttractionState::getStartFloor` | duelbotchallengeattractionstate_cpp | 25 | leaf |
| 33 | GD | `0xa7610` | `DuelBotChallengeGameLog::getEffectKey` | duelbotchallengeattractionstate_cpp | 30 | leaf |
| 34 | GD | `0xae770` | `DuelBotChallengeGameLog::getPcAttackPower` | duelbotchallengeattractionstate_cpp | 11 | leaf |
| 35 | GD | `0x6c300` | `ChallengePartyAttractionState::OnDamagedEvent` | challengepartyattractionstate_cpp | 24 | leaf |
| 36 | GD | `0x6ee50` | `ChallengePartyAttractionState::initPatternScore` | challengepartyattractionstate_cpp | 28 | leaf |
| 37 | GD | `0x6f370` | `ChallengePartyAttractionState::~ChallengePartyAttractionState` | challengepartyattractionstate_cpp | 27 | leaf |
| 38 | GD | `0x6f3e0` | `ChallengePartyAttractionState::CanTeamAttractionWithTarget` | challengepartyattractionstate_cpp | 19 | leaf |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/moveaction_cpp.cpp`
- `src/Server/GameDaemon/moveaction_cpp.h`
- `src/Server/GameDaemon/skillaction_cpp_2.cpp`
- `src/Server/GameDaemon/skillaction_cpp_2.h`
- `src/Server/GameDaemon/manipulateaction_cpp.cpp`
- `src/Server/GameDaemon/manipulateaction_cpp.h`
- `src/Server/GameDaemon/reaction.cpp`
- `src/Server/GameDaemon/reaction.h`
- `src/Server/GameDaemon/duelbotchallengeattractionstate_cpp.cpp`
- `src/Server/GameDaemon/duelbotchallengeattractionstate_cpp.h`
- `src/Server/GameDaemon/challengepartyattractionstate_cpp.cpp`
- `src/Server/GameDaemon/challengepartyattractionstate_cpp.h`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-e35.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
