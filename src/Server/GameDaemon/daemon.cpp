// daemon.cpp: daemon.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "daemon_gd.h"
#include "../BloodLib/include/Daemon.h"
#include "LiftStub.h"

// 0x68c390
::Console * __cdecl makeConsole(void)
{
    LIFT_STUB(0x68c390);
}

// 0x68cb60 Daemon::Start: LIFT: no body in wave 0 (shared class Daemon has another form or the change needs codegen (W1, pattern 35)).

// 0x68cd40 Daemon::Reload: LIFT: no body in wave 0 (shared class Daemon has another form or the change needs codegen (W1, pattern 35)).

// 0x68ce60 Daemon::Cooldown: LIFT: no body in wave 0 (shared class Daemon has another form or the change needs codegen (W1, pattern 35)).

// 0x68cf50
bool __cdecl Daemon::AddDelayedRelease(void (__cdecl *)(::RefCntObject *, ::RefCntObject *, ::RefCntObject *), ::RefCntObject *, ::RefCntObject *, ::RefCntObject *)
{
    LIFT_STUB(0x68cf50);
}

// 0x68d9e0
void __cdecl Daemon::SetPublicAddressWithSetting(unsigned long)
{
    LIFT_STUB(0x68d9e0);
}

// 0x68dba0
static bool parseCIDRAddress(const wchar_t*, _cidraddress&)
{
    LIFT_STUB(0x68dba0);
}

// 0x68dcc0
bool __cdecl Daemon::setInternalAddressRange(wchar_t const *)
{
    LIFT_STUB(0x68dcc0);
}

// 0x68dd50
bool __cdecl Daemon::setPublicAddressRange(wchar_t const *)
{
    LIFT_STUB(0x68dd50);
}

// 0x68dde0
bool __cdecl Daemon::allocateZstdDictionary(int)
{
    LIFT_STUB(0x68dde0);
}
