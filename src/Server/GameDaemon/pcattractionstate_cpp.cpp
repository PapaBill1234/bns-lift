// pcattractionstate_cpp.cpp: pcattractionstate.cpp (GameDaemon PDB, 2019 + PDB).
#include "pcattractionstate.h"
#include "pc.h"
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:?CheckAddScoreCoolTime@PcPublicRaidState@@UEBA_NPEAVPc@@_JJ@Z")  // LIFT: dead-strip keep (no live caller yet)

// 0x18c800
// LIFT: stub kept. The body reads Pc::zone, the Zone/GeoZone layout and the data table at loader slot 165.
// These layouts are not declared yet.
bool __cdecl PcPublicRaidState::CheckResetCombatModeCoolTime(::Pc *, __int64) const
{
    LIFT_STUB(0x18c800);
}

// 0x18c880
bool __cdecl PcPublicRaidState::CheckAddScoreCoolTime(::Pc *pc, __int64 now, long addScoreRecycleDuration) const
{
    if (pc == nullptr)
        return false;

    return static_cast<long>(now - _lastAddScoreTime) >= addScoreRecycleDuration;
}
