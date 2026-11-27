// skillpage.h: skillpage.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"
#include "propertysync.h"

class SkillPage
{
public:
    virtual __cdecl ~SkillPage(void);  // 0x1a0e0
    virtual int const __cdecl TypeId(void) const;  // 0x1a0f0
    virtual wchar_t const * __cdecl Name(void) const;  // 0x1a100
protected:
    virtual int __cdecl FieldMax(void) const;  // 0x1a110
    virtual ::Field::Def const * __cdecl FieldDefine(void) const;  // 0x1a120
    virtual int __cdecl SyncMax(void) const;  // 0x1a130
    virtual ::SyncBuffer::Def const * __cdecl SyncDefine(void) const;  // 0x1a140
};

