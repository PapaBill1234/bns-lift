// contentquotaproperty.h: contentquotaproperty.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"
#include "propertysync.h"

class ContentQuotaProperty
{
public:
    virtual wchar_t const * __cdecl Name(void) const;  // 0x19620
protected:
    virtual int __cdecl FieldMax(void) const;  // 0x19630
    virtual ::Field::Def const * __cdecl FieldDefine(void) const;  // 0x19640
    virtual int __cdecl SyncMax(void) const;  // 0x19650
    virtual ::SyncBuffer::Def const * __cdecl SyncDefine(void) const;  // 0x19660
};

