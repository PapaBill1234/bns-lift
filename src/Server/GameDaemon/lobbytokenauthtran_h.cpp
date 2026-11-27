// lobbytokenauthtran_h.cpp: lobbytokenauthtran.h (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "lobbytokenauthtran.h"
#include "LiftStub.h"

// 0x13e020
__cdecl EnterWorldOkParam::EnterWorldOkParam(void)
{
    LIFT_STUB(0x13e020);
}

// 0x13e270
::GameTranDef const * __cdecl LobbyTokenAuthTran::GetDefinition(void) const
{
    return &LobbyTokenAuthTran::_def;
}
#pragma comment(linker, "/INCLUDE:?GetDefinition@LobbyTokenAuthTran@@UEBAPEBUGameTranDef@@XZ")  // LIFT: dead-strip keep (no live caller yet)
// LIFT: placeholder. The real _def needs the state tables of the class (a later card).
::GameTranDef LobbyTokenAuthTran::_def;
