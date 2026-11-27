// extracreatureproperty.h: extracreatureproperty.cpp, extracreatureproperty.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"
#include "propertysync.h"

class ExtraCreatureProperty
{
public:
    virtual __cdecl ~ExtraCreatureProperty(void);  // 0x19940
    virtual int const __cdecl TypeId(void) const;  // 0x19950
    virtual wchar_t const * __cdecl Name(void) const;  // 0x19960
protected:
    virtual int __cdecl FieldMax(void) const;  // 0x19970
    virtual ::Field::Def const * __cdecl FieldDefine(void) const;  // 0x19980
    virtual int __cdecl SyncMax(void) const;  // 0x19990
    virtual ::SyncBuffer::Def const * __cdecl SyncDefine(void) const;  // 0x199a0
    // LIFT: PDB data members (protected static), see creatureproperty.h. ❓
    static int fieldMax;
    static ::Field::Def const * fieldDefine;
    static int syncMax;
    static ::SyncBuffer::Def const * syncDefine;
public:
    __cdecl ExtraCreatureProperty(void);  // 0x199e0
};

