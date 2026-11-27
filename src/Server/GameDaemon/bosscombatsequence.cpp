// bosscombatsequence.cpp: bosscombatsequence.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "bosscombatsequence.h"
#include "action.h"
#include "bossnpc.h"
#include "brainbase.h"
#include "combatsequence.h"
#include "creature.h"
#include "npc.h"
#include "LiftStub.h"

// 0x77bc0
::Action * __cdecl BossCombatSequence::NextCombatAction(::BrainBase &, ::Creature *, int, ::NpcActionQueue::ActionExpiredReason, bool &)
{
    LIFT_STUB(0x77bc0);
}

// 0x77d70
bool __cdecl BossCombatSequence::ReserveTransitBerserk(unsigned __int64)
{
    LIFT_STUB(0x77d70);
}

// 0x77d90
void __cdecl BossCombatSequence::transitBerserk(::BossNpc &, unsigned __int64)
{
    LIFT_STUB(0x77d90);
}

// 0x77e60
bool __cdecl BossCombatSequence::resetData(::Npc &)
{
    LIFT_STUB(0x77e60);
}

// 0x77ea0
::Action * __cdecl BossCombatSequence::createAction(::BrainBase &, ::Creature *, ::Data::CombatSequenceAction const &, ::CombatSequence::CombatDecisionFactors const &, ::ScriptEvent &, char &, char &)
{
    LIFT_STUB(0x77ea0);
}

// 0x78100
::Action * __cdecl BossCombatSequence::createRushAttack(::BrainBase &, ::Creature *, ::Data::CombatSequenceActionBossRushAttack const &, ::CombatSequence::CombatDecisionFactors const &, ::ScriptEvent &, char &)
{
    LIFT_STUB(0x78100);
}

// 0x784e0
::Action * __cdecl BossCombatSequence::createRepeaterAttack(::BrainBase &, ::Creature *, ::Data::CombatSequenceActionBossRepeaterAttack const &, ::CombatSequence::CombatDecisionFactors const &, ::ScriptEvent &, char &)
{
    LIFT_STUB(0x784e0);
}

// 0x785f0
::Action * __cdecl BossCombatSequence::createMultigroundAttack(::BrainBase &, ::Creature *, ::Data::CombatSequenceActionBossMultigroundAttack const &, ::CombatSequence::CombatDecisionFactors const &, ::ScriptEvent &, char &)
{
    LIFT_STUB(0x785f0);
}

// 0x78830
::Action * __cdecl BossCombatSequence::createSpSelectAttack(::BrainBase &, ::Creature *, ::Data::CombatSequenceActionBossSpSelectAttack const &, ::CombatSequence::CombatDecisionFactors const &, ::ScriptEvent &, char &)
{
    LIFT_STUB(0x78830);
}

// 0x78970
::Action * __cdecl BossCombatSequence::createGpSelectAttack(::BrainBase &, ::Creature *, ::Data::CombatSequenceActionBossGpSelectAttack const &, ::CombatSequence::CombatDecisionFactors const &, ::ScriptEvent &, char &)
{
    LIFT_STUB(0x78970);
}

// 0x78ab0
::Action * __cdecl BossCombatSequence::createSimultaneousGroundAttack(::BrainBase &, ::Creature *, ::Data::CombatSequenceActionBossSimultaneousGroundAttack const &, ::CombatSequence::CombatDecisionFactors const &, ::ScriptEvent &, char &)
{
    LIFT_STUB(0x78ab0);
}

// 0x78bc0
::Action * __cdecl BossCombatSequence::createSimultaneousCasterAttack(::BrainBase &, ::Creature *, ::Data::CombatSequenceActionBossSimultaneousCasterAttack const &, ::CombatSequence::CombatDecisionFactors const &, ::ScriptEvent &, char &)
{
    LIFT_STUB(0x78bc0);
}

// 0x78cd0
::Action * __cdecl BossCombatSequence::createRisingAttack(::BrainBase &, ::Creature *)
{
    LIFT_STUB(0x78cd0);
}

// 0x794b0
::Action * __cdecl BossCombatSequence::createWakeupAttack(::BrainBase &, ::Creature *)
{
    LIFT_STUB(0x794b0);
}
