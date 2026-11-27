// ncguard.h: ncguard.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class NCGuard
{
public:
    __cdecl ~NCGuard(void);  // 0x16e080
    bool __cdecl Initialize(void);  // 0x16e110
    bool __cdecl Start(void);  // 0x16e320
    void __cdecl AddClientSession(unsigned __int64);  // 0x16e380
    void __cdecl RemoveClientSession(unsigned __int64);  // 0x16e3c0
};

int __cdecl NCGSendPacketHandler(unsigned __int64, void *, unsigned long);  // 0x16ddf0
int __cdecl OnNCGEvent(unsigned __int64, ::_NCG_EVENT_TYPE, void *, unsigned long, unsigned long);  // 0x16df30
