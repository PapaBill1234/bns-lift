// seasoncontentscombatrecord.h: seasoncontentscombatrecord.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"
#include "propertysync.h"

class SeasonContentsCombatRecord
{
public:
    virtual int const __cdecl TypeId(void) const;  // 0x19fc0
    virtual wchar_t const * __cdecl Name(void) const;  // 0x19fd0
protected:
    virtual int __cdecl FieldMax(void) const;  // 0x19fe0
    virtual ::Field::Def const * __cdecl FieldDefine(void) const;  // 0x19ff0
    virtual int __cdecl SyncMax(void) const;  // 0x1a000
    virtual ::SyncBuffer::Def const * __cdecl SyncDefine(void) const;  // 0x1a010
    // LIFT: PDB data members (protected static). Set at start-up by Property::initInstance. Plain pointers, as in the pilot. ❓
    static int fieldMax;
    static ::Field::Def const * fieldDefine;
    static int syncMax;
    static ::SyncBuffer::Def const * syncDefine;
};

