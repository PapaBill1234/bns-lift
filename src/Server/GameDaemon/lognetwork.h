// lognetwork.h: lognetwork.cpp, lognetwork.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class LogNetwork
{
public:
    static ::LogNetwork * __cdecl Instance(void);  // 0x6a07c0
    static void __cdecl Stop(void);  // 0x6a0870
    static bool __cdecl AddSession(::Session const *);  // 0x6a09d0
    static void __cdecl RemoveSession(::Session const *);  // 0x6a0c90
private:
    virtual void __cdecl write(::LogBuffer const *);  // 0x6a0e30
};

