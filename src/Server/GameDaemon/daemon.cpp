// daemon.cpp: daemon.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "daemon_gd.h"
#include "../BloodLib/include/Daemon.h"
#include "LiftStub.h"
#include "../BloodLib/include/DelayedRelease.h"
#include "../BloodLib/include/Network.h"
#include <stdlib.h>
#include <wchar.h>

#pragma comment(linker, "/INCLUDE:?SetPublicAddressWithSetting@Daemon@@SAXK@Z")  // LIFT: dead-strip keep (no live caller yet)

// 0x68c390
::Console * __cdecl makeConsole(void)
{
    LIFT_STUB(0x68c390);
}

// 0x68cb60 Daemon::Start: LIFT: no body in wave 0 (shared class Daemon has another form or the change needs codegen (W1, pattern 35)).

// 0x68cd40 Daemon::Reload: LIFT: no body in wave 0 (shared class Daemon has another form or the change needs codegen (W1, pattern 35)).

// 0x68ce60 Daemon::Cooldown: LIFT: no body in wave 0 (shared class Daemon has another form or the change needs codegen (W1, pattern 35)).

// 0x68cf50
bool __cdecl Daemon::AddDelayedRelease(void (__cdecl *callback)(::RefCntObject *, ::RefCntObject *, ::RefCntObject *), ::RefCntObject *ref1, ::RefCntObject *ref2, ::RefCntObject *ref3)
{
    return Daemon::Instance->GlobalDelayedRelease->Add(GetTickCount64() - Daemon::Instance->StartSystemTick64,
                                                       callback, ref1, ref2, ref3);
}

// 0x68d9e0
void __cdecl Daemon::SetPublicAddressWithSetting(unsigned long address)
{
    Daemon::Instance->publicAddress = address;
    // ❓ HR shows the count 4 (0x68d9e0). publicAddrString has 20 characters. The source form of the count is not known.
    wcsncpy(Daemon::Instance->publicAddrString, Network::GetAddressStringW(address), 4);
}

// 0x68dba0
static bool parseCIDRAddress(const wchar_t* string, _cidraddress& result)
{
    wchar_t* context = nullptr;
    wchar_t wbuf[128];
    wcsncpy(wbuf, string, 128);
    wchar_t* address = wcstok_s(wbuf, L"/", &context);
    wchar_t* netmask = wcstok_s(nullptr, L"/", &context);
    if (address == nullptr || netmask == nullptr)
        return false;

    char abuf[128];
    // LIFT: inline copy of String::UnicodeToMultibyte with count 128 (0x68dba0). Same form as Network.cpp.
    *reinterpret_cast<wchar_t*>(&abuf[126]) = 0;
    WideCharToMultiByte(CP_ACP, 0, address, -1, abuf, 127, nullptr, nullptr);
    result.address = inet_addr(abuf);
    result.netmask = ~(0xFFFFFFFFu << _wtoi(netmask));
    return true;
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
