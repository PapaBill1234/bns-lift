// summonedproperty.h: summonedproperty.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"
#include "propertysync.h"

class SummonedProperty
{
public:
    virtual __cdecl ~SummonedProperty(void);  // 0x1a220
    virtual wchar_t const * __cdecl Name(void) const;  // 0x1a240
protected:
    virtual int __cdecl FieldMax(void) const;  // 0x1a250
    virtual ::Field::Def const * __cdecl FieldDefine(void) const;  // 0x1a260
    virtual int __cdecl SyncMax(void) const;  // 0x1a270
    virtual ::SyncBuffer::Def const * __cdecl SyncDefine(void) const;  // 0x1a280
    static int fieldMax;
    static ::Field::Def const * fieldDefine;
    static int syncMax;
    static ::SyncBuffer::Def const * syncDefine;
};

