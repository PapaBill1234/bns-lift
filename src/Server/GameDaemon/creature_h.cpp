// creature_h.cpp: creature.h (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "creature.h"
#include "LiftStub.h"

// 0x1d240
void __cdecl Creature::AddChangedPropertyId(unsigned short)
{
    LIFT_STUB(0x1d240);
}

// 0x1d280
void __cdecl Creature::AddChangedExtraPropertyId(unsigned short)
{
    LIFT_STUB(0x1d280);
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
long const __cdecl ApplySkillModifyInfo::CalcRecycleDuration(long) const
{
    LIFT_STUB(0x453650);
}

// 0x4536f0
short const __cdecl ApplySkillModifyInfo::CalcSpConsume(short) const
{
    LIFT_STUB(0x4536f0);
}

// 0x453740
int const __cdecl ApplySkillModifyInfo::CalcDamagePowerPercent(int) const
{
    LIFT_STUB(0x453740);
}

// 0x4537e0
short const __cdecl ApplySkillModifyInfo::CalcHealPercent(short) const
{
    LIFT_STUB(0x4537e0);
}

// 0x453880
short const __cdecl ApplySkillModifyInfo::CalcHpDrainPercent(short) const
{
    LIFT_STUB(0x453880);
}
