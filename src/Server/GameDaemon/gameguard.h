// gameguard.h: gameguard.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class GameGuard
{
public:
    bool __cdecl Initialize(void);  // 0x36b730
    bool __cdecl SendCheckAuthData(::User *);  // 0x36b800
    bool __cdecl RecvCheckAuthData(::Pc *, ::User *, unsigned char const *, short);  // 0x36bf30
};

