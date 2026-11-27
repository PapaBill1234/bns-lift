// gathersource.h: gathersource.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class GatherSource
{
public:
    bool __cdecl Initialize(unsigned __int64, ::Zone *, unsigned int, ::vector16);  // 0x5a2bc0
    virtual void __cdecl OnTimer(::Zone *, unsigned short);  // 0x5a2d40
    static ::GatherSource * __cdecl Create(int, ::Zone *, unsigned int, ::vector16);  // 0x5a2d80
};

