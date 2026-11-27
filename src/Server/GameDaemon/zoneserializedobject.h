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
    // LIFT: slots 1-5 come from RefCntObject and RelationalRefCntObject (not lifted yet). Pure placeholders keep the PDB slot order.
    virtual void __cdecl lift_slot1_deallocate_object(void) = 0;
    virtual void __cdecl lift_slot2_deallocate_me(void) = 0;
    virtual void __cdecl lift_slot3_DumpRefCntHistory(void) = 0;
    virtual void __cdecl lift_slot4_parentRoleAllocator(void) = 0;
    virtual void __cdecl lift_slot5_childRoleAllocator(void) = 0;
    // MSVC orders same-name virtual overloads in reverse declaration order.
    virtual void __cdecl TimerExpired(unsigned int, long) = 0;  // PDB slot 7 (+0x38), pure
    virtual void __cdecl TimerExpired(long);  // 0x25fbf0, PDB slot 6 (override of SerializedObject)
public:
    void __cdecl DetachParent(void);  // 0x25fc00
};

