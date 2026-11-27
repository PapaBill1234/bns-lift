// leaveworldtran_h.cpp: leaveworldtran.h (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "leaveworldtran.h"
#include "user.h"
#include "LiftStub.h"

// 0x35fe0
::GameTranDef const * __cdecl LeaveWorldTran::GetDefinition(void) const
{
    return &LeaveWorldTran::_def;
}
#pragma comment(linker, "/INCLUDE:?GetDefinition@LeaveWorldTran@@UEBAPEBUGameTranDef@@XZ")  // LIFT: dead-strip keep (no live caller yet)
// LIFT: placeholder. The real _def (0xE7FA70) needs the state tables of the class (a later card).
::GameTranDef LeaveWorldTran::_def;

// 0x35ff0
__cdecl LogoutTran::LogoutTran(::User *)
{
    LIFT_STUB(0x35ff0);
}

// 0x36080
__cdecl LogoutArenaTran::LogoutArenaTran(::User *)
{
    LIFT_STUB(0x36080);
}

// 0x360f0
::GameTranDef const * __cdecl LogoutArenaTran::GetDefinition(void) const
{
    return &LogoutArenaTran::_def;
}
#pragma comment(linker, "/INCLUDE:?GetDefinition@LogoutArenaTran@@UEBAPEBUGameTranDef@@XZ")  // LIFT: dead-strip keep (no live caller yet)
// LIFT: placeholder. The real _def needs the state tables of the class (a later card).
::GameTranDef LogoutArenaTran::_def;

// 0x1397e0
::GameTranDef const * __cdecl ReturnToArenaLobbyTran::GetDefinition(void) const
{
    return &ReturnToArenaLobbyTran::_def;
}
#pragma comment(linker, "/INCLUDE:?GetDefinition@ReturnToArenaLobbyTran@@UEBAPEBUGameTranDef@@XZ")  // LIFT: dead-strip keep (no live caller yet)
// LIFT: placeholder. The real _def needs the state tables of the class (a later card).
::GameTranDef ReturnToArenaLobbyTran::_def;
