# lift-gamedaemon-gap-022-e22 handoff (round 1)

## Lifted

- `BoardGachaRetrieveSeasonInfoWSO::SendFail` (0xd9e0)
- `BoardGachaSessionCloseWSO::SendFail` (0xde40)
- `BoardGachaBoardInfoReqWSO::SendFail` (0xdff0)
- `BoardGachaRetrieveParticipationInfoAllWSO::SendFail` (0xe200)
- `FactionContribution` and `GuildContribution` leaves (0x98dd0, 0x98e00, 0x98e40, 0x994e0, 0x99500, 0x99520)
- `BrainBoss`, `BrainMonster`, `BrainFollower`: `GetLastTargetId`, `GetState`
- `OpenQuest::getDaemonUpTimeSec` (0x454d30), `QuestJournal::findQuestIndex` (0x454d70)
- `tryProbability` (0xd5840), `tryProbability10000` (0xd58d0)
- `EnterZoneTask::TimerExpired` (0x294050)
- `DeathMatchDuelManager::verifyDuelType` (0x4c180), `TagMatchDuelManager::verifyDuelType` (0x4c390). Both read `Data::DuelRecord::duel_type` (+32) through `_data` (+8) with raw offsets.
- `GameLocale::IsWupperNotApplied` (0xd50d0), `GameLocale::GetVietToneMarkType` (0xd5450). The PDB enumerators are now in `gamelocale.h`.
- `OccupationWarManager::OnCanceledEnvManipulation` (0x171500)
- `ContentQuotaManager::ContentQuotaManager` (0x86390), `ContentQuotaPriorityQueue::Top` (0x3fb920). Raw offsets. The tree head node uses the GameDaemon `StlMemory.h` path literal.
- `TagMatchDuelMember::ResetRound` (0x1d0560), `TagMatchDuelTeam::ResetRound` (0x1d0ae0), `TagMatchDuelManager::getOppositeFightMember` (0x1d46d0), `TagMatchDuelManager::resetRound` (0x1d5570). Raw offsets. The classes have no member layout yet.

Each `BoardGacha*::SendFail` body sends `Send("hE", opcode, 2)`. The `failReason` argument is unused in the original. Keep pragmas are in the `.cpp` files.

## Not done

- `BoardGacha::SendSeasonInfoPacket` (0xbb50): the Log::Write call uses 3 string literals in the data section. The pseudocode shows only data offsets, not the text.
- `BoardGacha::SendBoardInfo` (0xc3b0): same reason.
- `DeathMatchDuelManager::instantiateDuelRule` (0x4c190) and `TagMatchDuelManager::instantiateDuelRule` (0x4c3a0): the body builds `DeathMatchDuleRule` and `TagMatchDuelRule` objects. Their headers have no base class and no members yet. The vtable store needs the real class layouts first.
- `OccupationWarManager::getRatingRevise` (0x1719a0): needs the `Data::DataManager::Instance->_loaderDefs[6]` table layout and a virtual call on `DrTable`. No lifted code shows this form yet.
- `Task::getParentZone` (0x291b50), `RequestActionCancel::start` (0x293fd0), `RequestSkillTrigger::start` (0x294000): the pseudocode reads `RelationalRefCntObject` parent fields at unknown offsets (`MEMORY[0x8B8]`, `parent[56]` vtable call). Needs more than 5 look-ups.

## Repair (round 3)

`useRandomValue2()` in `gamemath_cpp.cpp` read the private `GameDaemon::config` member. It now reads the member at its PDB offset (+0xAA8), then `_userandomValue2` at +0x30C. No other body changed.

## Not checked

The author session ran no build and no formtest. The driver build must confirm each lifted body.

## Files changed

- `src/Server/GameDaemon/boardgacha.cpp`
- `src/Server/GameDaemon/brainboss_h.cpp`
- `src/Server/GameDaemon/brainfollower_h.cpp`
- `src/Server/GameDaemon/brainmonster_h.cpp`
- `src/Server/GameDaemon/contribution_cpp.cpp`
- `src/Server/GameDaemon/questjournal_h.cpp`
- `src/Server/GameDaemon/gamemath_cpp.cpp`
- `src/Server/GameDaemon/task_cpp_1.cpp`
- `src/Server/GameDaemon/deathmatchduelmanager_h.cpp`
- `src/Server/GameDaemon/tagmatchduelmanager_h.cpp`
- `src/Server/GameDaemon/gamelocale.cpp`
- `src/Server/GameDaemon/gamelocale.h`
- `src/Server/GameDaemon/occupationwarmanager.cpp`
- `src/Server/GameDaemon/contentquota.cpp`
- `src/Server/GameDaemon/tagmatchduelmanager_cpp.cpp`
- `Docs/Plan/handoffs/lift-gamedaemon-gap-022-e22.md`
