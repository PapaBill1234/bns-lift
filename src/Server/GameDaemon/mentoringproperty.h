// mentoringproperty.h: mentoringproperty.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"
#include "propertysync.h"

class MentoringProperty
{
public:
    virtual __cdecl ~MentoringProperty(void);  // 0x19bd0
    virtual wchar_t const * __cdecl Name(void) const;  // 0x19be0
protected:
    virtual int __cdecl FieldMax(void) const;  // 0x19bf0
    virtual ::Field::Def const * __cdecl FieldDefine(void) const;  // 0x19c00
    virtual int __cdecl SyncMax(void) const;  // 0x19c10
    virtual ::SyncBuffer::Def const * __cdecl SyncDefine(void) const;  // 0x19c20
};

