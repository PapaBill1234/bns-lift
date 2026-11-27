// session.cpp: session.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "session_gd.h"
#include "../BloodLib/include/Session.h"
#include "LiftStub.h"

// 0x699170
bool __cdecl Session::IsConnected(void) const
{
    LIFT_STUB(0x699170);
}

// 0x6992c0
void __cdecl Session::SendText(char const *, ...) const
{
    LIFT_STUB(0x6992c0);
}

// 0x6994a0
void __cdecl Session::SendTextV(char const *, char *) const
{
    LIFT_STUB(0x6994a0);
}

// 0x699b30 Session::SetHandshakeParameter: LIFT: no body in wave 0 (shared class Session has another form or the change needs codegen (W1, pattern 35)).

// 0x699dd0
bool __cdecl ReconnectTimer::HandleEvent(::EventContext *, unsigned long)
{
    LIFT_STUB(0x699dd0);
}
