// brainraidboss_cpp.cpp: brainraidboss.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "brainraidboss.h"
#include "creature.h"
#include "npc.h"
#include "LiftStub.h"

// 0x634f0
__cdecl BrainRaidBoss::BrainRaidBoss(::Npc &)
{
    LIFT_STUB(0x634f0);
}

// 0x63700
void __cdecl BrainRaidBoss::InitSpecialState(void)
{
    LIFT_STUB(0x63700);
}

// 0x63730
void __cdecl BrainRaidBoss::GatherSpecialTargets(char, char, bool, bool, char, bool, char)
{
    LIFT_STUB(0x63730);
}

// 0x63ac0
void __cdecl BrainRaidBoss::getNearSpecialTargets(::Creature **const, char, char)
{
    LIFT_STUB(0x63ac0);
}

// 0x63c80
void __cdecl BrainRaidBoss::getFarSpecialTargets(::Creature **const, char, char)
{
    LIFT_STUB(0x63c80);
}

// 0x63e40
void __cdecl BrainRaidBoss::getMinHateSpecialTargets(::Creature **const, char, char)
{
    LIFT_STUB(0x63e40);
}
