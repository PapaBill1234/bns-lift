// activatedteleport.h: activatedteleport.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"
#include "propertysync.h"

class ActivatedTeleport
{
public:
    virtual __cdecl ~ActivatedTeleport(void);  // 0x193e0
    virtual int const __cdecl TypeId(void) const;  // 0x193f0
    virtual wchar_t const * __cdecl Name(void) const;  // 0x19400
protected:
    virtual int __cdecl FieldMax(void) const;  // 0x19410
    virtual ::Field::Def const * __cdecl FieldDefine(void) const;  // 0x19420
    virtual int __cdecl SyncMax(void) const;  // 0x19430
    virtual ::SyncBuffer::Def const * __cdecl SyncDefine(void) const;  // 0x19440
    // LIFT: PDB data members (protected static). Pilot of card lift-gamedaemon-0d. The values are set at start-up
    // by Property::initInstance (a later wave lifts the caller). The PDB mangles the 2 pointers as const (a const object that start-up code writes). A const definition with a constant value folds the getter, so the pilot uses a plain pointer. ❓
    static int fieldMax;
    static ::Field::Def const * fieldDefine;
    static int syncMax;
    static ::SyncBuffer::Def const * syncDefine;
};

