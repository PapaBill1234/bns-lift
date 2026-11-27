// mileagedeposittran_h.cpp: mileagedeposittran.h (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "mileagedeposittran.h"
#include "LiftStub.h"

// 0x1107e0
::GameTranDef const * __cdecl MileageDepositTran::GetDefinition(void) const
{
    return &MileageDepositTran::_def;
}
#pragma comment(linker, "/INCLUDE:?GetDefinition@MileageDepositTran@@UEBAPEBUGameTranDef@@XZ")  // LIFT: dead-strip keep (no live caller yet)
// LIFT: placeholder. The real _def needs the state tables of the class (a later card).
::GameTranDef MileageDepositTran::_def;
