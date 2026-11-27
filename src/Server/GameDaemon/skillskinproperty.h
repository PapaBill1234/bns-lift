// skillskinproperty.h: skillskinproperty.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"
#include "propertysync.h"

class SkillSkinProperty
{
public:
    virtual __cdecl ~SkillSkinProperty(void);  // 0x1a180
    virtual int const __cdecl TypeId(void) const;  // 0x1a190
    virtual wchar_t const * __cdecl Name(void) const;  // 0x1a1a0
protected:
    virtual int __cdecl FieldMax(void) const;  // 0x1a1b0
    virtual ::Field::Def const * __cdecl FieldDefine(void) const;  // 0x1a1c0
    virtual int __cdecl SyncMax(void) const;  // 0x1a1d0
    virtual ::SyncBuffer::Def const * __cdecl SyncDefine(void) const;  // 0x1a1e0
    static int fieldMax;
    static ::Field::Def const * fieldDefine;
    static int syncMax;
    static ::SyncBuffer::Def const * syncDefine;
};

