# lift-gamedaemon-e22: Easy leaves (GameDaemon): boardgacha, contribution_cpp, brainboss_h, brainmonster_h, ...

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

40 functions, about 549 pseudocode lines (about 4,392 tokens). Stems: `boardgacha`, `contribution_cpp`, `brainboss_h`, `brainmonster_h`, `brainfollower_h`, `questjournal_h`, `gamemath_cpp`, `task_cpp_1`, `deathmatchduelmanager_h`, `tagmatchduelmanager_cpp`, `tagmatchduelmanager_h`, `gamelocale`, `occupationwarmanager`, `contentquota`.

Wave E (owner order 2026-11-27: the easiest work first). Each function in this card is a leaf: its body calls no other counted function that needs a lift. Thus a `LIFT_STUB` callee cannot keep it DIFF. Each function has at most 30 pseudocode lines. Ease key: 13.7 cost per function (rule in `Docs/Plan/gamedaemon-lift.md` section 3).

Lift only the functions in the table. The other functions of these stems are in later W cards. Those cards depend on this card.

| n | Exe | RVA | PDB name | Stem | Lines | Form |
| ---: | --- | --- | --- | --- | ---: | --- |
| 1 | GD | `0xbb50` | `BoardGacha::SendSeasonInfoPacket` | boardgacha | 20 | leaf |
| 2 | GD | `0xc3b0` | `BoardGacha::SendBoardInfo` | boardgacha | 23 | leaf |
| 3 | GD | `0xd9e0` | `BoardGachaRetrieveSeasonInfoWSO::SendFail` | boardgacha | 8 | leaf |
| 4 | GD | `0xde40` | `BoardGachaSessionCloseWSO::SendFail` | boardgacha | 8 | leaf |
| 5 | GD | `0xdff0` | `BoardGachaBoardInfoReqWSO::SendFail` | boardgacha | 8 | leaf |
| 6 | GD | `0xe200` | `BoardGachaRetrieveParticipationInfoAllWSO::SendFail` | boardgacha | 8 | leaf |
| 7 | GD | `0x98dd0` | `FactionContribution::TopContributionGroupId` | contribution_cpp | 20 | leaf |
| 8 | GD | `0x98e00` | `FactionContribution::TotalDamage` | contribution_cpp | 14 | leaf |
| 9 | GD | `0x98e40` | `FactionContribution::Reset` | contribution_cpp | 12 | leaf |
| 10 | GD | `0x994e0` | `GuildContribution::TopContributionGroupId` | contribution_cpp | 10 | leaf |
| 11 | GD | `0x99500` | `GuildContribution::TotalDamage` | contribution_cpp | 10 | leaf |
| 12 | GD | `0x99520` | `GuildContribution::Reset` | contribution_cpp | 10 | leaf |
| 13 | GD | `0x79c60` | `BrainBoss::GetLastTargetId` | brainboss_h | 7 | getter |
| 14 | GD | `0x79c70` | `BrainBoss::GetState` | brainboss_h | 19 | leaf |
| 15 | GD | `0x402d60` | `BrainMonster::GetLastTargetId` | brainmonster_h | 7 | getter |
| 16 | GD | `0x402d70` | `BrainMonster::GetState` | brainmonster_h | 19 | leaf |
| 17 | GD | `0x402db0` | `BrainFollower::GetLastTargetId` | brainfollower_h | 7 | getter |
| 18 | GD | `0x402dc0` | `BrainFollower::GetState` | brainfollower_h | 19 | leaf |
| 19 | GD | `0x454d30` | `OpenQuest::getDaemonUpTimeSec` | questjournal_h | 7 | leaf |
| 20 | GD | `0x454d70` | `QuestJournal::findQuestIndex` | questjournal_h | 19 | leaf |
| 21 | GD | `0xd5840` | `tryProbability` | gamemath_cpp | 14 | leaf |
| 22 | GD | `0xd58d0` | `tryProbability10000` | gamemath_cpp | 14 | leaf |
| 23 | GD | `0x291b50` | `Task::getParentZone` | task_cpp_1 | 13 | leaf |
| 24 | GD | `0x293fd0` | `RequestActionCancel::start` | task_cpp_1 | 18 | leaf |
| 25 | GD | `0x294000` | `RequestSkillTrigger::start` | task_cpp_1 | 18 | leaf |
| 26 | GD | `0x294050` | `EnterZoneTask::TimerExpired` | task_cpp_1 | 7 | leaf |
| 27 | GD | `0x4c180` | `DeathMatchDuelManager::verifyDuelType` | deathmatchduelmanager_h | 7 | leaf |
| 28 | GD | `0x4c190` | `DeathMatchDuelManager::instantiateDuelRule` | deathmatchduelmanager_h | 22 | leaf |
| 29 | GD | `0x1d0560` | `TagMatchDuelMember::ResetRound` | tagmatchduelmanager_cpp | 19 | leaf |
| 30 | GD | `0x1d0ae0` | `TagMatchDuelTeam::ResetRound` | tagmatchduelmanager_cpp | 10 | leaf |
| 31 | GD | `0x1d46d0` | `TagMatchDuelManager::getOppositeFightMember` | tagmatchduelmanager_cpp | 22 | leaf |
| 32 | GD | `0x1d5570` | `TagMatchDuelManager::resetRound` | tagmatchduelmanager_cpp | 8 | leaf |
| 33 | GD | `0x4c390` | `TagMatchDuelManager::verifyDuelType` | tagmatchduelmanager_h | 7 | leaf |
| 34 | GD | `0x4c3a0` | `TagMatchDuelManager::instantiateDuelRule` | tagmatchduelmanager_h | 23 | leaf |
| 35 | GD | `0xd50d0` | `GameLocale::IsWupperNotApplied` | gamelocale | 9 | leaf |
| 36 | GD | `0xd5450` | `GameLocale::GetVietToneMarkType` | gamelocale | 21 | leaf |
| 37 | GD | `0x171500` | `OccupationWarManager::OnCanceledEnvManipulation` | occupationwarmanager | 13 | leaf |
| 38 | GD | `0x1719a0` | `OccupationWarManager::getRatingRevise` | occupationwarmanager | 17 | leaf |
| 39 | GD | `0x86390` | `ContentQuotaManager::ContentQuotaManager` | contentquota | 22 | leaf |
| 40 | GD | `0x3fb920` | `ContentQuotaPriorityQueue::Top` | contentquota | 10 | leaf |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/boardgacha.cpp`
- `src/Server/GameDaemon/boardgacha.h`
- `src/Server/GameDaemon/contribution_cpp.cpp`
- `src/Server/GameDaemon/contribution_cpp.h`
- `src/Server/GameDaemon/brainboss_h.cpp`
- `src/Server/GameDaemon/brainboss_h.h`
- `src/Server/GameDaemon/brainmonster_h.cpp`
- `src/Server/GameDaemon/brainmonster_h.h`
- `src/Server/GameDaemon/brainfollower_h.cpp`
- `src/Server/GameDaemon/brainfollower_h.h`
- `src/Server/GameDaemon/questjournal_h.cpp`
- `src/Server/GameDaemon/questjournal_h.h`
- `src/Server/GameDaemon/gamemath_cpp.cpp`
- `src/Server/GameDaemon/gamemath_cpp.h`
- `src/Server/GameDaemon/task_cpp_1.cpp`
- `src/Server/GameDaemon/task_cpp_1.h`
- `src/Server/GameDaemon/deathmatchduelmanager_h.cpp`
- `src/Server/GameDaemon/deathmatchduelmanager_h.h`
- `src/Server/GameDaemon/tagmatchduelmanager_cpp.cpp`
- `src/Server/GameDaemon/tagmatchduelmanager_cpp.h`
- `src/Server/GameDaemon/tagmatchduelmanager_h.cpp`
- `src/Server/GameDaemon/tagmatchduelmanager_h.h`
- `src/Server/GameDaemon/gamelocale.cpp`
- `src/Server/GameDaemon/gamelocale.h`
- `src/Server/GameDaemon/occupationwarmanager.cpp`
- `src/Server/GameDaemon/occupationwarmanager.h`
- `src/Server/GameDaemon/contentquota.cpp`
- `src/Server/GameDaemon/contentquota.h`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-e22.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
