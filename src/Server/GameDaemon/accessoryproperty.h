// accessoryproperty.h: accessoryproperty.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"
#include "propertysync.h"

class AccessoryProperty
{
public:
    virtual int const __cdecl TypeId(void) const;  // 0x191d0
    virtual wchar_t const * __cdecl Name(void) const;  // 0x191f0
protected:
    virtual int __cdecl FieldMax(void) const;  // 0x19200
    virtual ::Field::Def const * __cdecl FieldDefine(void) const;  // 0x19210
    virtual int __cdecl SyncMax(void) const;  // 0x19220
    virtual ::SyncBuffer::Def const * __cdecl SyncDefine(void) const;  // 0x19230
};

