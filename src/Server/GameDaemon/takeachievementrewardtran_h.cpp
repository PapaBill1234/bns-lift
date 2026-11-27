// takeachievementrewardtran_h.cpp: takeachievementrewardtran.h (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "takeachievementrewardtran.h"
#include "LiftStub.h"

// 0x1d77b0
::GameTranDef const * __cdecl TakeAchievementRewardTran::GetDefinition(void) const
{
    return &TakeAchievementRewardTran::_def;
}
#pragma comment(linker, "/INCLUDE:?GetDefinition@TakeAchievementRewardTran@@UEBAPEBUGameTranDef@@XZ")  // LIFT: dead-strip keep (no live caller yet)
// LIFT: placeholder. The real _def needs the state tables of the class (a later card).
::GameTranDef TakeAchievementRewardTran::_def;
