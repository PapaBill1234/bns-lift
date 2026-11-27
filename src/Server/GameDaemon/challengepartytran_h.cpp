// challengepartytran_h.cpp: challengepartytran.h (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "challengepartytran.h"
#include "LiftStub.h"

// 0x65da0
::GameTranDef const * __cdecl CreateChallengePartyTran::GetDefinition(void) const
{
    return &CreateChallengePartyTran::_def;
}
#pragma comment(linker, "/INCLUDE:?GetDefinition@CreateChallengePartyTran@@UEBAPEBUGameTranDef@@XZ")  // LIFT: dead-strip keep (no live caller yet)
// LIFT: placeholder. The real _def needs the state tables of the class (a later card).
::GameTranDef CreateChallengePartyTran::_def;

// 0x65db0
::GameTranDef const * __cdecl ConfirmInvitationChallengePartyTran::GetDefinition(void) const
{
    return &ConfirmInvitationChallengePartyTran::_def;
}
#pragma comment(linker, "/INCLUDE:?GetDefinition@ConfirmInvitationChallengePartyTran@@UEBAPEBUGameTranDef@@XZ")  // LIFT: dead-strip keep (no live caller yet)
// LIFT: placeholder. The real _def needs the state tables of the class (a later card).
::GameTranDef ConfirmInvitationChallengePartyTran::_def;

// 0x65dc0
::GameTranDef const * __cdecl LeaveChallengePartyTran::GetDefinition(void) const
{
    return &LeaveChallengePartyTran::_def;
}
#pragma comment(linker, "/INCLUDE:?GetDefinition@LeaveChallengePartyTran@@UEBAPEBUGameTranDef@@XZ")  // LIFT: dead-strip keep (no live caller yet)
// LIFT: placeholder. The real _def needs the state tables of the class (a later card).
::GameTranDef LeaveChallengePartyTran::_def;
