// slateproperty.h: slateproperty.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"
#include "propertysync.h"

class SlateProperty
{
public:
    virtual int const __cdecl TypeId(void) const;  // 0x9750
    virtual wchar_t const * __cdecl Name(void) const;  // 0x9760
protected:
    virtual int __cdecl FieldMax(void) const;  // 0x9770
    virtual ::Field::Def const * __cdecl FieldDefine(void) const;  // 0x9780
    virtual int __cdecl SyncMax(void) const;  // 0x9790
    virtual ::SyncBuffer::Def const * __cdecl SyncDefine(void) const;  // 0x97a0
    // LIFT: PDB data members (protected static), same form as CreatureProperty.
    static int fieldMax;
    static ::Field::Def const * fieldDefine;
    static int syncMax;
    static ::SyncBuffer::Def const * syncDefine;
};

