// creatureproperty.h: creatureproperty.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"
#include "propertysync.h"

class CreatureProperty
{
public:
    virtual __cdecl ~CreatureProperty(void);  // 0x19340
    virtual int __cdecl Version(void) const;  // 0x19350
    virtual wchar_t const * __cdecl Name(void) const;  // 0x19360
protected:
    virtual int __cdecl FieldMax(void) const;  // 0x19370
    virtual ::Field::Def const * __cdecl FieldDefine(void) const;  // 0x19380
    virtual int __cdecl SyncMax(void) const;  // 0x19390
    virtual ::SyncBuffer::Def const * __cdecl SyncDefine(void) const;  // 0x193a0
};

