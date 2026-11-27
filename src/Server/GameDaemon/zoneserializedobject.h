// zoneserializedobject.h: zoneserializedobject.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class ZoneSerializedObject
{
public:
    __cdecl ZoneSerializedObject(void);  // 0x25fa00
    virtual __cdecl ~ZoneSerializedObject(void);  // 0x25fab0
    void __cdecl SetZone(::Zone *);  // 0x25fb40
protected:
    virtual void __cdecl TimerExpired(unsigned int, long) = 0;  // PDB slot 7, pure
    virtual void __cdecl TimerExpired(long);  // 0x25fbf0
public:
    void __cdecl DetachParent(void);  // 0x25fc00
};

