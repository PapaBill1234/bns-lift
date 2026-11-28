# lift-gamedaemon-gap-022-e22 handoff (round 5)

## Lifted

- `BoardGachaRetrieveSeasonInfoWSO::SendFail` (0xd9e0)
- `BoardGachaSessionCloseWSO::SendFail` (0xde40)
- `BoardGachaBoardInfoReqWSO::SendFail` (0xdff0)
- `BoardGachaRetrieveParticipationInfoAllWSO::SendFail` (0xe200)
- `FactionContribution::TopContributionGroupId` (0x98dd0), `GuildContribution::Reset` (0x99520)
- `BrainBoss`, `BrainMonster`, `BrainFollower`: `GetLastTargetId`, `GetState`
- `OpenQuest::getDaemonUpTimeSec` (0x454d30)
- `DeathMatchDuelManager::verifyDuelType` (0x4c180), `TagMatchDuelManager::verifyDuelType` (0x4c390)
- `GameLocale::IsWupperNotApplied` (0xd50d0), `GameLocale::GetVietToneMarkType` (0xd5450)
- `OccupationWarManager::OnCanceledEnvManipulation` (0x171500)
- `TagMatchDuelTeam::ResetRound` (0x1d0ae0), `TagMatchDuelManager::getOppositeFightMember` (0x1d46d0), `TagMatchDuelManager::resetRound` (0x1d5570)

Each `BoardGacha*::SendFail` body sends `Send("hE", opcode, 2)`. The `failReason` argument is unused in the original. Keep pragmas are in the `.cpp` files.

## Not done

Repair round 4 put these 11 functions back to `LIFT_STUB`. Their `/INCLUDE` pragmas are removed. Each one is for a later card.

- `ContentQuotaManager::ContentQuotaManager` (0x86390): review found node and member offsets that differ (the original stores at node +0x28/+0x29 and a qword at this+0x20).
- `ContentQuotaPriorityQueue::Top` (0x3fb920): review found field offsets that differ (the original reads `[rcx+0x0]` and compares with `[rcx+0x8]`).
- `EnterZoneTask::TimerExpired` (0x294050): P1_calls (build `ind[+0x8]`, original `ind[+0x48]`).
- `FactionContribution::Reset` (0x98e40): review found store widths and immediates that differ.
- `FactionContribution::TotalDamage` (0x98e00): P1_calls (build `ind[+0x10]`, original `ind[+0x18]`).
- `GuildContribution::TopContributionGroupId` (0x994e0): P2_cc (build `jle`, original `jg`).
- `GuildContribution::TotalDamage` (0x99500): P2_cc (build `jle`, original `jg`).
- `QuestJournal::findQuestIndex` (0x454d70): review found a 16-bit index sign extension (the original uses `movsx`).
- `TagMatchDuelMember::ResetRound` (0x1d0560): the original reloads the rule pointer `[0xab0]` after the store to `[rcx+0x38]`.
- `tryProbability` (0xd5840): P2_cc (build `jne`, original `je`) and P3_imm.
- `tryProbability10000` (0xd58d0): P2_cc (build `jne`, original `je`) and P3_imm.

Earlier Not done functions, unchanged:

- `BoardGacha::SendSeasonInfoPacket` (0xbb50) and `BoardGacha::SendBoardInfo` (0xc3b0): the Log::Write call uses string literals in the data section. The pseudocode shows only data offsets, not the text.
- `DeathMatchDuelManager::instantiateDuelRule` (0x4c190) and `TagMatchDuelManager::instantiateDuelRule` (0x4c3a0): the rule classes have no base class and no members yet.
- `OccupationWarManager::getRatingRevise` (0x1719a0): needs the `Data::DataManager::Instance->_loaderDefs[6]` table layout and a virtual call on `DrTable`.
- `Task::getParentZone` (0x291b50), `RequestActionCancel::start` (0x293fd0), `RequestSkillTrigger::start` (0x294000): unknown parent field offsets. Needs more than 5 look-ups.

## Not checked

The author session ran no build and no formtest. The driver build must confirm each lifted body.

## Files changed

- `src/Server/GameDaemon/contentquota.cpp`
- `src/Server/GameDaemon/contribution_cpp.cpp`
- `src/Server/GameDaemon/gamemath_cpp.cpp`
- `src/Server/GameDaemon/questjournal_h.cpp`
- `src/Server/GameDaemon/task_cpp_1.cpp`
- `src/Server/GameDaemon/tagmatchduelmanager_cpp.cpp`
- `Docs/Plan/handoffs/lift-gamedaemon-gap-022-e22.md`
