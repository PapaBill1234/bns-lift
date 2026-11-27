// ncguard.cpp: ncguard.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "ncguard.h"
#include "LiftStub.h"

// 0x16ddf0
// LIFT: feature off (owner scope)
int __cdecl NCGSendPacketHandler(unsigned __int64, void *, unsigned long)
{
    return 0;
}

// 0x16df30
// LIFT: feature off (owner scope)
int __cdecl OnNCGEvent(unsigned __int64, ::_NCG_EVENT_TYPE, void *, unsigned long, unsigned long)
{
    return 0;
}

// 0x16e080
// LIFT: feature off (owner scope)
__cdecl NCGuard::~NCGuard(void)
{
}

// 0x16e110
// LIFT: feature off (owner scope)
bool __cdecl NCGuard::Initialize(void)
{
    return false;
}

// 0x16e320
// LIFT: feature off (owner scope)
bool __cdecl NCGuard::Start(void)
{
    return false;
}

// 0x16e380
// LIFT: feature off (owner scope)
void __cdecl NCGuard::AddClientSession(unsigned __int64)
{
}

// 0x16e3c0
// LIFT: feature off (owner scope)
void __cdecl NCGuard::RemoveClientSession(unsigned __int64)
{
}
