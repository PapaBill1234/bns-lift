// bossnpc.h: bossnpc.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class BossNpc
{
public:
    __cdecl BossNpc(::Zone *, ::Data::NpcRecordPtr, ::NpcSpawnInfo, ::Data::BossNpcRecordPtr);  // 0x79cb0
    virtual bool __cdecl Initialize(unsigned __int64, ::NpcSpawnParam const &);  // 0x79e60
    virtual void __cdecl EnterZone(::EnterReason, bool, unsigned int);  // 0x79f30
    virtual void __cdecl OnDamaged(::Zone *, ::GameObject *, unsigned int, __int64, __int64);  // 0x79f90
private:
    void __cdecl setSecondGaugeSection(short);  // 0x7a180
public:
    virtual void __cdecl OnCombatStart(::Creature *, bool);  // 0x7a480
    virtual void __cdecl OnCombatEnd(void);  // 0x7b320
    virtual void __cdecl OnSpawn(void);  // 0x7bc80
    virtual void __cdecl OnDespawn(void);  // 0x7bec0
    void __cdecl OnHandleEffectFlag(short, bool);  // 0x7c060
    void __cdecl OnSecondGaugeChanged(short, short, wchar_t const *);  // 0x7c0f0
    __int64 __cdecl GetBerserkSequenceInvokeTime(void);  // 0x7c420
    virtual void __cdecl TakeFactionScore(::GameObject *);  // 0x7c560
};

