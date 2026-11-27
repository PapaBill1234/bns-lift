# lift-gamedaemon-e44: Easy leaves (GameDaemon): questjournal_cpp_2, filter_cpp, teamparty, publicraid_cpp, ...

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

40 functions, about 974 pseudocode lines (about 7,792 tokens). Stems: `questjournal_cpp_2`, `filter_cpp`, `teamparty`, `publicraid_cpp`, `fishingcontainer_cpp`, `mentoring`, `postbox`, `task_cpp_5`, `rankingseason_cpp`.

Wave E (owner order 2026-11-27: the easiest work first). Each function in this card is a leaf: its body calls no other counted function that needs a lift. Thus a `LIFT_STUB` callee cannot keep it DIFF. Each function has at most 30 pseudocode lines. Ease key: 24.4 cost per function (rule in `Docs/Plan/gamedaemon-lift.md` section 3).

Lift only the functions in the table. The other functions of these stems are in later W cards. Those cards depend on this card.

| n | Exe | RVA | PDB name | Stem | Lines | Form |
| ---: | --- | --- | --- | --- | ---: | --- |
| 1 | GD | `0x572fa0` | `QuestJournal::IsRewardRestrictedCase` | questjournal_cpp_2 | 22 | leaf |
| 2 | GD | `0x573010` | `QuestJournal::validateQuestId` | questjournal_cpp_2 | 23 | leaf |
| 3 | GD | `0x5730a0` | `QuestJournal::isScriptableCase` | questjournal_cpp_2 | 27 | leaf |
| 4 | GD | `0x57a090` | `QuestJournal::calcQuestRewardExpBonus` | questjournal_cpp_2 | 17 | leaf |
| 5 | GD | `0x57a110` | `QuestJournal::calcQuestRewardExpBonusTestServer` | questjournal_cpp_2 | 14 | leaf |
| 6 | GD | `0x57dc70` | `QuestJournal::checkPcDifficultyType` | questjournal_cpp_2 | 16 | leaf |
| 7 | GD | `0x580f00` | `QuestJournal::HasFactionQuest` | questjournal_cpp_2 | 29 | leaf |
| 8 | GD | `0x581080` | `QuestJournal::RemoveLeaveZoneRollbackQuestIndex` | questjournal_cpp_2 | 25 | leaf |
| 9 | GD | `0x582500` | `QuestJournal::calcCaseFee` | questjournal_cpp_2 | 28 | leaf |
| 10 | GD | `0x583ce0` | `QuestJournal::removeAttrationQuest` | questjournal_cpp_2 | 27 | leaf |
| 11 | GD | `0x277f50` | `PcFilter::Check` | filter_cpp | 22 | leaf |
| 12 | GD | `0x278540` | `NpcFilter::Check` | filter_cpp | 26 | leaf |
| 13 | GD | `0x2785b0` | `NotNpcFilter::Check` | filter_cpp | 26 | leaf |
| 14 | GD | `0x278bf0` | `EventBroadcastedFilter::Check` | filter_cpp | 15 | leaf |
| 15 | GD | `0x278c10` | `EnvFilter::Check` | filter_cpp | 26 | leaf |
| 16 | GD | `0x2791f0` | `SummonedFilter::Check` | filter_cpp | 29 | leaf |
| 17 | GD | `0x279270` | `NotSummonedFilter::Check` | filter_cpp | 29 | leaf |
| 18 | GD | `0x2792f0` | `LinkLaserTerminateReasonFilter::Check` | filter_cpp | 21 | leaf |
| 19 | GD | `0x2796e0` | `FilterFactory::clear` | filter_cpp | 24 | leaf |
| 20 | GD | `0x346ca0` | `DataKeyFilter<Data::FilterRecordActSequence>::Check` | filter_cpp | 21 | leaf |
| 21 | GD | `0x346d10` | `DataIdFilter<Data::FilterRecordSkill3Id,Data::Skill3Record>::Check` | filter_cpp | 21 | leaf |
| 22 | GD | `0x211170` | `TeamParty::GetMaxMemberCountByPartyType` | teamparty | 19 | leaf |
| 23 | GD | `0x2113c0` | `TeamParty::~TeamParty` | teamparty | 28 | leaf |
| 24 | GD | `0x213250` | `TeamParty::AddAuction` | teamparty | 24 | leaf |
| 25 | GD | `0x2147a0` | `TeamParty::IsEnteredMemberByAttraction` | teamparty | 27 | leaf |
| 26 | GD | `0x21b970` | `TeamParty::addMember` | teamparty | 19 | leaf |
| 27 | GD | `0x21bd80` | `TeamParty::buildAppearance` | teamparty | 28 | leaf |
| 28 | GD | `0x21c1c0` | `TeamParty::isFull` | teamparty | 21 | leaf |
| 29 | GD | `0x1a0cf0` | `EnterPublicRaidAttractionState::SetRoomInfo` | publicraid_cpp | 25 | leaf |
| 30 | GD | `0x1a0d70` | `EnterPublicRaidAttractionState::setMaxReservePcCountTouched` | publicraid_cpp | 25 | leaf |
| 31 | GD | `0x1a10b0` | `EnterPublicRaidAttractionState::checkReservePcCount` | publicraid_cpp | 26 | leaf |
| 32 | GD | `0xbae40` | `FishingEntry::Initialize` | fishingcontainer_cpp | 27 | leaf |
| 33 | GD | `0x169a10` | `MentoringManager::Initialize` | mentoring | 27 | leaf |
| 34 | GD | `0x1922c0` | `PostBox::~PostBox` | postbox | 25 | leaf |
| 35 | GD | `0x195620` | `RetreivePostBriefListTask::AddPost` | postbox | 29 | leaf |
| 36 | GD | `0x2d2010` | `ConfirmInvitationChallengePartyFailFromCacheTask::start` | task_cpp_5 | 28 | leaf |
| 37 | GD | `0x2d52a0` | `ConfirmInvitationMentoringOkFromCacheTask::start` | task_cpp_5 | 26 | leaf |
| 38 | GD | `0x2d5430` | `ConfirmInvitationMentoringFailFromCacheTask::start` | task_cpp_5 | 27 | leaf |
| 39 | GD | `0x1b39e0` | `RankingSeasonManager::RankingSeasonManager` | rankingseason_cpp | 26 | leaf |
| 40 | GD | `0x1b5e40` | `RankingSeasonManager::GetSeasonContentsSchedule` | rankingseason_cpp | 29 | leaf |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/questjournal_cpp_2.cpp`
- `src/Server/GameDaemon/questjournal_cpp_2.h`
- `src/Server/GameDaemon/filter_cpp.cpp`
- `src/Server/GameDaemon/filter_cpp.h`
- `src/Server/GameDaemon/teamparty.cpp`
- `src/Server/GameDaemon/teamparty.h`
- `src/Server/GameDaemon/publicraid_cpp.cpp`
- `src/Server/GameDaemon/publicraid_cpp.h`
- `src/Server/GameDaemon/fishingcontainer_cpp.cpp`
- `src/Server/GameDaemon/fishingcontainer_cpp.h`
- `src/Server/GameDaemon/mentoring.cpp`
- `src/Server/GameDaemon/mentoring.h`
- `src/Server/GameDaemon/postbox.cpp`
- `src/Server/GameDaemon/postbox.h`
- `src/Server/GameDaemon/task_cpp_5.cpp`
- `src/Server/GameDaemon/task_cpp_5.h`
- `src/Server/GameDaemon/rankingseason_cpp.cpp`
- `src/Server/GameDaemon/rankingseason_cpp.h`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-e44.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
