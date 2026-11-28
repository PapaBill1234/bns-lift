// creature_h.cpp: creature.h (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "creature.h"
#include "LiftStub.h"

// 0x1d240
#pragma comment(linker, "/INCLUDE:?AddChangedPropertyId@Creature@@UEAAXG@Z")  // LIFT: dead-strip keep (no live caller yet)
void __cdecl Creature::AddChangedPropertyId(unsigned short fieldId)
{
    reinterpret_cast< ::CreatureMemberView *>(this)->_changedPropertyIdListSet.insert(fieldId);
}

// 0x1d280
#pragma comment(linker, "/INCLUDE:?AddChangedExtraPropertyId@Creature@@UEAAXG@Z")  // LIFT: dead-strip keep (no live caller yet)
void __cdecl Creature::AddChangedExtraPropertyId(unsigned short fieldId)
{
    reinterpret_cast< ::CreatureMemberView *>(this)->_changedExtraPropertyIdListSet.insert(fieldId);
}

// 0x1edbb0
bool __cdecl Creature::IsCreatureInDuelCombat(void) const
{
    LIFT_STUB(0x1edbb0);
}

// 0x1edbf0
__cdecl CreatureStateKeeper::~CreatureStateKeeper(void)
{
    LIFT_STUB(0x1edbf0);
}

// 0x1edc40
void __cdecl CreatureStateKeeper::SnapshotCreatureState(void)
{
    LIFT_STUB(0x1edc40);
}

// 0x453650
long const __cdecl ApplySkillModifyInfo::CalcRecycleDuration(long const) const
{
    LIFT_STUB(0x453650);
}

// 0x4536f0
short const __cdecl ApplySkillModifyInfo::CalcSpConsume(short const) const
{
    LIFT_STUB(0x4536f0);
}

// 0x453740
int const __cdecl ApplySkillModifyInfo::CalcDamagePowerPercent(int const) const
{
    LIFT_STUB(0x453740);
}

// 0x4537e0
short const __cdecl ApplySkillModifyInfo::CalcHealPercent(short const) const
{
    LIFT_STUB(0x4537e0);
}

// 0x453880
short const __cdecl ApplySkillModifyInfo::CalcHpDrainPercent(short const) const
{
    LIFT_STUB(0x453880);
}
