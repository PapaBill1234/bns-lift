// costumeproperty.h: costumeproperty.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"
#include "propertysync.h"

class CostumeProperty
{
public:
    virtual __cdecl ~CostumeProperty(void);  // 0x196a0
    virtual wchar_t const * __cdecl Name(void) const;  // 0x196c0
protected:
    virtual int __cdecl FieldMax(void) const;  // 0x196d0
    virtual ::Field::Def const * __cdecl FieldDefine(void) const;  // 0x196e0
    virtual int __cdecl SyncMax(void) const;  // 0x196f0
    virtual ::SyncBuffer::Def const * __cdecl SyncDefine(void) const;  // 0x19700
};

