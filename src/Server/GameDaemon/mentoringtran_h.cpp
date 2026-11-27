// mentoringtran_h.cpp: mentoringtran.h (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "mentoringtran.h"
#include "LiftStub.h"

// 0x16a300
::GameTranDef const * __cdecl ConfirmInvitationMentoringTran::GetDefinition(void) const
{
    return &ConfirmInvitationMentoringTran::_def;
}
#pragma comment(linker, "/INCLUDE:?GetDefinition@ConfirmInvitationMentoringTran@@UEBAPEBUGameTranDef@@XZ")  // LIFT: dead-strip keep (no live caller yet)
// LIFT: placeholder. The real _def needs the state tables of the class (a later card).
::GameTranDef ConfirmInvitationMentoringTran::_def;

// 0x16a310
::GameTranDef const * __cdecl LeaveMentoringTran::GetDefinition(void) const
{
    return &LeaveMentoringTran::_def;
}
#pragma comment(linker, "/INCLUDE:?GetDefinition@LeaveMentoringTran@@UEBAPEBUGameTranDef@@XZ")  // LIFT: dead-strip keep (no live caller yet)
// LIFT: placeholder. The real _def needs the state tables of the class (a later card).
::GameTranDef LeaveMentoringTran::_def;
