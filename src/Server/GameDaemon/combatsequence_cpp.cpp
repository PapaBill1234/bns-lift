// combatsequence_cpp.cpp: combatsequence.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "combatsequence.h"
#include "action.h"
#include "bosscombatsequence.h"
#include "brainbase.h"
#include "creature.h"
#include "npc.h"
#include "zone.h"
#include "LiftStub.h"

// 0x630d0
__cdecl BossCombatSequence::~BossCombatSequence(void)
{
    LIFT_STUB(0x630d0);
}

// 0x4053d0
bool __cdecl CombatSequence::CheckLOS(::Zone *, ::vector16, ::vector16, int)
{
    LIFT_STUB(0x4053d0);
}

// 0x4059c0
static bool isSufficentHpCondition(Creature*, const char)
{
    LIFT_STUB(0x4059c0);
}

// 0x405a20
bool __cdecl CombatSequence::Set(::Npc &, unsigned __int64, char, char)
{
    LIFT_STUB(0x405a20);
}

// 0x405a90
bool __cdecl CombatSequence::resetData(::Npc &)
{
    LIFT_STUB(0x405a90);
}

// 0x405c70
bool __cdecl CombatSequence::IsInAttackRange(::Npc &, short, __int64, short, bool &)
{
    LIFT_STUB(0x405c70);
}

// 0x405e30
bool __cdecl CombatSequence::Transit(::Npc &, int)
{
    LIFT_STUB(0x405e30);
}

// 0x405f20
bool __cdecl CombatSequence::CheckCondition(::Creature *, char)
{
    LIFT_STUB(0x405f20);
}

// 0x4060c0
bool __cdecl CombatSequence::GetCloseInPosition(::Npc &, ::vector16, ::Creature &, short, ::vector16 &, bool)
{
    LIFT_STUB(0x4060c0);
}

// 0x406310
bool __cdecl CombatSequence::isTransitable(::Npc &, char, int, char)
{
    LIFT_STUB(0x406310);
}

// 0x406470
int __cdecl CombatSequence::checkTransitableCondIndex(::Npc &, int)
{
    LIFT_STUB(0x406470);
}

// 0x406530
::Action * __cdecl CombatSequence::NextCombatAction(::BrainBase &, ::Creature *, int, ::NpcActionQueue::ActionExpiredReason, bool &)
{
    LIFT_STUB(0x406530);
}

// 0x4069c0
bool __cdecl CombatSequence::applyLastActionResult(::Npc &, ::Creature *, ::NpcActionQueue::ActionExpiredReason, __int64, bool &, bool &)
{
    LIFT_STUB(0x4069c0);
}

// 0x406e90
::Action * __cdecl CombatSequence::checkFallAction(::Npc &, ::Zone *)
{
    LIFT_STUB(0x406e90);
}

// 0x407010
::Action * __cdecl CombatSequence::createTransitAction(::Npc &, ::Creature *)
{
    LIFT_STUB(0x407010);
}

// 0x4071b0
::Action * __cdecl CombatSequence::createSequenceStartAction(::Npc &, ::Creature *)
{
    LIFT_STUB(0x4071b0);
}

// 0x4072e0
bool __cdecl CombatSequence::setCombatDecisionFactors(::Npc &, ::Creature *, ::CombatSequence::CombatDecisionFactors &)
{
    LIFT_STUB(0x4072e0);
}

// 0x4075b0
void __cdecl CombatSequence::setSpecialSequenceCombatDecisionFactors(::Npc &, short, ::CombatSequence::CombatDecisionFactors &)
{
    LIFT_STUB(0x4075b0);
}

// 0x407660
::Action * __cdecl CombatSequence::createSequenceAction(::BrainBase &, ::Creature *, __int64, ::CombatSequence::CombatDecisionFactors &)
{
    LIFT_STUB(0x407660);
}

// 0x407740
bool __cdecl CombatSequence::fireSpecial(::BrainBase &, ::Creature *)
{
    LIFT_STUB(0x407740);
}

// 0x407c80
char __cdecl CombatSequence::checkSpecialFired(::Npc &, char, __int64, ::ScriptEvent &)
{
    LIFT_STUB(0x407c80);
}

// 0x407d40
bool __cdecl CombatSequence::checkSpecialCondition(::Npc &, char const *, ::DrScriptObj const *, unsigned __int64, ::ScriptEvent &)
{
    LIFT_STUB(0x407d40);
}

// 0x408030
bool __cdecl CombatSequence::FireSpecial(::Npc &, char, unsigned __int64, long, __int64)
{
    LIFT_STUB(0x408030);
}

// 0x4080b0
void __cdecl CombatSequence::finishSpecial(::Npc &)
{
    LIFT_STUB(0x4080b0);
}

// 0x408130
::Action * __cdecl CombatSequence::createSpecialAction(::BrainBase &, ::Creature *, ::CombatSequence::CombatDecisionFactors const &)
{
    LIFT_STUB(0x408130);
}

// 0x408520
::Action * __cdecl CombatSequence::createNormalAction(::BrainBase &, ::Creature *, ::CombatSequence::CombatDecisionFactors const &)
{
    LIFT_STUB(0x408520);
}

// 0x4087d0
::Action * __cdecl CombatSequence::createSkillCooldown(::Npc &, ::Creature *, __int64, ::CombatSequence::CombatDecisionFactors const &)
{
    LIFT_STUB(0x4087d0);
}

// 0x408970
::Action * __cdecl CombatSequence::registerLastAction(::Action *, ::Data::CombatSequenceAction const &)
{
    LIFT_STUB(0x408970);
}

// 0x4089c0
::Action * __cdecl CombatSequence::createAction(::BrainBase &, ::Creature *, ::Data::CombatSequenceAction const &, ::CombatSequence::CombatDecisionFactors const &, ::ScriptEvent &, char &, char &)
{
    LIFT_STUB(0x4089c0);
}

// 0x409840
::Action * __cdecl CombatSequence::createSkillAction(::BrainBase &, ::Creature *, ::CombatSequence::CombatDecisionFactors const &, ::ScriptEvent &, ::DrScriptObj, unsigned __int64, char, int, bool, bool, char &, char, ::DrScriptObj const *const, unsigned __int64 const *const)
{
    LIFT_STUB(0x409840);
}

// 0x409ea0
::Action * __cdecl CombatSequence::createGroundSkillAction(::BrainBase &, ::vector16 const &, ::CombatSequence::CombatDecisionFactors const &, ::ScriptEvent &, unsigned __int64, char, int, char &)
{
    LIFT_STUB(0x409ea0);
}

// 0x40a020
::Action * __cdecl CombatSequence::createStayAction(::Npc &, ::ScriptEvent &, ::DrScriptObj, long, int)
{
    LIFT_STUB(0x40a020);
}

// 0x40a180
::Action * __cdecl CombatSequence::createMoveToTicket(::Npc &, ::Creature &, int, ::Data::CombatSequenceSetupDirType)
{
    LIFT_STUB(0x40a180);
}

// 0x40a280
int __cdecl CombatSequence::assignTargetTicket(::Zone *, ::vector16 const &, ::Creature &, int, ::vector16 &)
{
    LIFT_STUB(0x40a280);
}

// 0x40a320
void __cdecl CombatSequence::clearTargetTicket(::Zone *, ::Creature *)
{
    LIFT_STUB(0x40a320);
}
