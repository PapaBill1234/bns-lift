// leaveworldtran_h.cpp: leaveworldtran.h (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "leaveworldtran.h"
#include "user.h"
#include "LiftStub.h"

// 0x35fe0
::GameTranDef const * __cdecl LeaveWorldTran::GetDefinition(void) const
{
    LIFT_STUB(0x35fe0);
}

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
    LIFT_STUB(0x360f0);
}

// 0x1397e0
::GameTranDef const * __cdecl ReturnToArenaLobbyTran::GetDefinition(void) const
{
    LIFT_STUB(0x1397e0);
}
