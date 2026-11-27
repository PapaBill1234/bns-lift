// raiddungeonunbindproperty.h: raiddungeonunbindproperty.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"
#include "propertysync.h"

class RaidDungeonUnbindProperty
{
public:
    virtual int const __cdecl TypeId(void) const;  // 0x19e00
    virtual wchar_t const * __cdecl Name(void) const;  // 0x19e10
protected:
    virtual int __cdecl FieldMax(void) const;  // 0x19e20
    virtual ::Field::Def const * __cdecl FieldDefine(void) const;  // 0x19e30
    virtual int __cdecl SyncMax(void) const;  // 0x19e40
    virtual ::SyncBuffer::Def const * __cdecl SyncDefine(void) const;  // 0x19e50
};

