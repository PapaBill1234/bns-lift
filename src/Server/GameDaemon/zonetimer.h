// zonetimer.h: zonetimer.cpp, zonetimer.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class ZoneSerializer
{
public:
    bool __cdecl PostCloseEvent(long);  // 0x2283e0
    bool __cdecl Initialize(::Zone *, long, long);  // 0x25fd00
    bool __cdecl Clear(void);  // 0x25fdf0
private:
    void __cdecl executeLast(long, unsigned int *);  // 0x25fe70
public:
    virtual void __cdecl preExecute(long);  // 0x260170
    virtual void __cdecl postExecute(long, unsigned int, unsigned int);  // 0x2601c0
};

