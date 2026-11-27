// bossnpc.cpp: bossnpc.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "bossnpc.h"
#include "creature.h"
#include "gameobject.h"
#include "npcspawn.h"
#include "zone.h"
#include "LiftStub.h"

// 0x79cb0
__cdecl BossNpc::BossNpc(::Zone *, ::Data::NpcRecordPtr, ::NpcSpawnInfo, ::Data::BossNpcRecordPtr)
{
    LIFT_STUB(0x79cb0);
}

// 0x79e60
bool __cdecl BossNpc::Initialize(unsigned __int64, ::NpcSpawnParam const &)
{
    LIFT_STUB(0x79e60);
}

// 0x79f30
void __cdecl BossNpc::EnterZone(::EnterReason, bool, unsigned int)
{
    LIFT_STUB(0x79f30);
}

// 0x79f90
void __cdecl BossNpc::OnDamaged(::Zone *, ::GameObject *, unsigned int, __int64, __int64)
{
    LIFT_STUB(0x79f90);
}

// 0x7a180
void __cdecl BossNpc::setSecondGaugeSection(short)
{
    LIFT_STUB(0x7a180);
}

// 0x7a480
void __cdecl BossNpc::OnCombatStart(::Creature *, bool)
{
    LIFT_STUB(0x7a480);
}

// 0x7b320
void __cdecl BossNpc::OnCombatEnd(void)
{
    LIFT_STUB(0x7b320);
}

// 0x7bc80
void __cdecl BossNpc::OnSpawn(void)
{
    LIFT_STUB(0x7bc80);
}

// 0x7bec0
void __cdecl BossNpc::OnDespawn(void)
{
    LIFT_STUB(0x7bec0);
}

// 0x7c060
void __cdecl BossNpc::OnHandleEffectFlag(short, bool)
{
    LIFT_STUB(0x7c060);
}

// 0x7c0f0
void __cdecl BossNpc::OnSecondGaugeChanged(short, short, wchar_t const *)
{
    LIFT_STUB(0x7c0f0);
}

// 0x7c420
__int64 __cdecl BossNpc::GetBerserkSequenceInvokeTime(void)
{
    LIFT_STUB(0x7c420);
}

// 0x7c560
void __cdecl BossNpc::TakeFactionScore(::GameObject *)
{
    LIFT_STUB(0x7c560);
}
