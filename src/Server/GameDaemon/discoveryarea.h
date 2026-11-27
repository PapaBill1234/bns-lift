// discoveryarea.h: discoveryarea.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"
#include "propertysync.h"

class DiscoveryArea
{
public:
    virtual __cdecl ~DiscoveryArea(void);  // 0x19740
    virtual int const __cdecl TypeId(void) const;  // 0x19750
    virtual wchar_t const * __cdecl Name(void) const;  // 0x19760
protected:
    virtual int __cdecl FieldMax(void) const;  // 0x19770
    virtual ::Field::Def const * __cdecl FieldDefine(void) const;  // 0x19780
    virtual int __cdecl SyncMax(void) const;  // 0x19790
    virtual ::SyncBuffer::Def const * __cdecl SyncDefine(void) const;  // 0x197a0
    static int fieldMax;
    static ::Field::Def const * fieldDefine;
    static int syncMax;
    static ::SyncBuffer::Def const * syncDefine;
};

