// acquiredskill1.h: acquiredskill1.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"
#include "propertysync.h"

class AcquiredSkill1
{
public:
    virtual __cdecl ~AcquiredSkill1(void);  // 0x19270
    virtual int __cdecl TypeId(void) const;  // 0x19280
    virtual wchar_t const * __cdecl Name(void) const;  // 0x19290
protected:
    virtual int __cdecl FieldMax(void) const;  // 0x192a0
    virtual ::Field::Def const * __cdecl FieldDefine(void) const;  // 0x192b0
    virtual int __cdecl SyncMax(void) const;  // 0x192c0
    virtual ::SyncBuffer::Def const * __cdecl SyncDefine(void) const;  // 0x192d0
    // LIFT: PDB data members (protected static), same form as CreatureProperty.
    static int fieldMax;
    static ::Field::Def const * fieldDefine;
    static int syncMax;
    static ::SyncBuffer::Def const * syncDefine;
};

