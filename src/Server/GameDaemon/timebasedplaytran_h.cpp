// timebasedplaytran_h.cpp: timebasedplaytran.h (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "timebasedplaytran.h"
#include "LiftStub.h"

// 0x224250
::GameTranDef const * __cdecl TakeTimeBasedPlayRewardTran::GetDefinition(void) const
{
    return &TakeTimeBasedPlayRewardTran::_def;
}
#pragma comment(linker, "/INCLUDE:?GetDefinition@TakeTimeBasedPlayRewardTran@@UEBAPEBUGameTranDef@@XZ")  // LIFT: dead-strip keep (no live caller yet)
// LIFT: placeholder. The real _def needs the state tables of the class (a later card).
::GameTranDef TakeTimeBasedPlayRewardTran::_def;
