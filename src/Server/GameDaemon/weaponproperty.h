// weaponproperty.h: weaponproperty.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"
#include "propertysync.h"

class WeaponProperty
{
public:
    virtual __cdecl ~WeaponProperty(void);  // 0x1a2c0
    virtual wchar_t const * __cdecl Name(void) const;  // 0x1a2d0
protected:
    virtual int __cdecl FieldMax(void) const;  // 0x1a2e0
    virtual ::Field::Def const * __cdecl FieldDefine(void) const;  // 0x1a2f0
    virtual int __cdecl SyncMax(void) const;  // 0x1a300
    virtual ::SyncBuffer::Def const * __cdecl SyncDefine(void) const;  // 0x1a310
};

