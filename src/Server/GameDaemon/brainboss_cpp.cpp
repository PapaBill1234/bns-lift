// brainboss_cpp.cpp: brainboss.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "brainboss.h"
#include "creature.h"
#include "npc.h"
#include "LiftStub.h"

// 0x7c740
__cdecl BrainBoss::BrainBoss(::Npc &)
{
    LIFT_STUB(0x7c740);
}

// 0x7c9e0
bool __cdecl BrainBoss::Stop(void)
{
    LIFT_STUB(0x7c9e0);
}

// 0x7c9f0
void __cdecl BrainBoss::InitSpecialState(void)
{
    LIFT_STUB(0x7c9f0);
}

// 0x7ca30
void __cdecl BrainBoss::GatherSpecialTargets(char, char, bool, bool, char, bool, char)
{
    LIFT_STUB(0x7ca30);
}

// 0x7cdc0
void __cdecl BrainBoss::getNearSpecialTargets(::Creature **const, char, char)
{
    LIFT_STUB(0x7cdc0);
}

// 0x7cf80
void __cdecl BrainBoss::getFarSpecialTargets(::Creature **const, char, char)
{
    LIFT_STUB(0x7cf80);
}

// 0x7d140
void __cdecl BrainBoss::getMinHateSpecialTargets(::Creature **const, char, char)
{
    LIFT_STUB(0x7d140);
}

// 0x7d2e0
bool __cdecl BrainBoss::checkPCHateListEmptied(void)
{
    LIFT_STUB(0x7d2e0);
}

// 0x7d350
void __cdecl BrainBoss::fireEventHateListEmptied(void)
{
    LIFT_STUB(0x7d350);
}

// 0x7d4c0
bool __cdecl BrainBoss::ResetHateByTargetId(unsigned __int64, wchar_t const *)
{
    LIFT_STUB(0x7d4c0);
}

// 0x7d530
bool __cdecl BrainBoss::ResetHateByIndex(int, wchar_t const *)
{
    LIFT_STUB(0x7d530);
}

// 0x7d570
bool __cdecl BrainBoss::checkSpecialTargetCond(::Creature *, bool, bool, char, bool, char)
{
    LIFT_STUB(0x7d570);
}
