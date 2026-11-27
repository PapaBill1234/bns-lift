// recycletimeproperty.h: recycletimeproperty.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"
#include "propertysync.h"

class RecycleTimeProperty
{
public:
    virtual __cdecl ~RecycleTimeProperty(void);  // 0x19f30
    virtual wchar_t const * __cdecl Name(void) const;  // 0x19f40
protected:
    virtual int __cdecl FieldMax(void) const;  // 0x19f50
    virtual ::Field::Def const * __cdecl FieldDefine(void) const;  // 0x19f60
    virtual int __cdecl SyncMax(void) const;  // 0x19f70
    virtual ::SyncBuffer::Def const * __cdecl SyncDefine(void) const;  // 0x19f80
    // LIFT: PDB data members (protected static). Set at start-up by Property::initInstance. Plain pointers, as in the pilot. ❓
    static int fieldMax;
    static ::Field::Def const * fieldDefine;
    static int syncMax;
    static ::SyncBuffer::Def const * syncDefine;
};

