// gameguard.cpp: gameguard.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "gameguard.h"
#include "pc.h"
#include "user.h"
#include "LiftStub.h"

// 0x36b730
// LIFT: feature off (owner scope)
bool __cdecl GameGuard::Initialize(void)
{
    return false;
}

// 0x36b800
// LIFT: feature off (owner scope)
bool __cdecl GameGuard::SendCheckAuthData(::User *)
{
    return false;
}

// 0x36bf30
// LIFT: feature off (owner scope)
bool __cdecl GameGuard::RecvCheckAuthData(::Pc *, ::User *, unsigned char const *, short)
{
    return false;
}
