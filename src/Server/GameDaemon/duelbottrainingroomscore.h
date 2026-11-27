// duelbottrainingroomscore.h: duelbottrainingroomscore.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"
#include "propertysync.h"

class DuelBotTrainingRoomScore
{
public:
    virtual wchar_t const * __cdecl Name(void) const;  // 0x197e0
protected:
    virtual int __cdecl FieldMax(void) const;  // 0x197f0
    virtual ::Field::Def const * __cdecl FieldDefine(void) const;  // 0x19800
    virtual int __cdecl SyncMax(void) const;  // 0x19810
    virtual ::SyncBuffer::Def const * __cdecl SyncDefine(void) const;  // 0x19820
    // LIFT: PDB data members (protected static), see creatureproperty.h. ❓
    static int fieldMax;
    static ::Field::Def const * fieldDefine;
    static int syncMax;
    static ::SyncBuffer::Def const * syncDefine;
public:
    virtual int const __cdecl TypeId(void) const;  // 0x1a050
};

