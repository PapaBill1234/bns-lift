// pcattractionstate.h: pcattractionstate.cpp, pcattractionstate.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class PcPublicRaidState
{
public:
    virtual __int64 __cdecl GetResetCombatModeCoolTime(void) const;  // 0x180ba0
    virtual void __cdecl SetAddScoreCoolTime(__int64);  // 0x180bb0
    virtual bool __cdecl IsEventAttendee(void) const;  // 0x180bc0
    virtual void __cdecl SetEventAttendee(void);  // 0x180bd0
    virtual void __cdecl ResetEventAttendee(void);  // 0x180be0
    virtual short __cdecl GetAddScoreCount(void) const;  // 0x180bf0
    virtual void __cdecl IncrementAddScoreCount(void);  // 0x180c00
    virtual bool __cdecl CheckResetCombatModeCoolTime(::Pc *, __int64) const;  // 0x18c800
    virtual bool __cdecl CheckAddScoreCoolTime(::Pc *, __int64, long) const;  // 0x18c880
    virtual __int64 __cdecl GetAddScroeCoolTime(void) const;  // 0x4535a0
    virtual void __cdecl SetResetCombatModeCoolTime(__int64);  // 0x6fd280
private:
    // LIFT: PDB members of PcPublicRaidState (base PcAttractionState not declared yet; vptr is at +0).
    __int64 _lastResetCombatModeTime;  // +8
    __int64 _lastAddScoreTime;  // +16
    bool _isEventAttendee;  // +24
    short _addScoreCount;  // +26
};

