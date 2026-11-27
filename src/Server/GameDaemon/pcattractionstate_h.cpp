// pcattractionstate_h.cpp: pcattractionstate.h (GameDaemon PDB, 2019 + PDB).
#include "pcattractionstate.h"
#include "LiftStub.h"

// 0x180ba0 (shared body with NpcContribution::TotalDamage)
__int64 __cdecl PcPublicRaidState::GetResetCombatModeCoolTime(void) const
{
    return _lastResetCombatModeTime;
}

// 0x180bb0
void __cdecl PcPublicRaidState::SetAddScoreCoolTime(__int64 now)
{
    _lastAddScoreTime = now;
}

// 0x180bc0
bool __cdecl PcPublicRaidState::IsEventAttendee(void) const
{
    return _isEventAttendee;
}

// 0x180bd0
void __cdecl PcPublicRaidState::SetEventAttendee(void)
{
    _isEventAttendee = true;
}

// 0x180be0
void __cdecl PcPublicRaidState::ResetEventAttendee(void)
{
    _isEventAttendee = false;
}

// 0x180bf0
short __cdecl PcPublicRaidState::GetAddScoreCount(void) const
{
    return _addScoreCount;
}

// 0x180c00
void __cdecl PcPublicRaidState::IncrementAddScoreCount(void)
{
    ++_addScoreCount;
}

// 0x4535a0 (shared body with DuelBotActionQueue::GetMovement)
__int64 __cdecl PcPublicRaidState::GetAddScroeCoolTime(void) const
{
    return _lastAddScoreTime;
}

// 0x6fd280 (shared body with DrDataTableImpl::Setup)
void __cdecl PcPublicRaidState::SetResetCombatModeCoolTime(__int64 now)
{
    _lastResetCombatModeTime = now;
}
