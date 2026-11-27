// combatsequence.h: combatsequence.cpp, combatsequence.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"
#include "action.h"

class CombatSequence
{
public:
    struct CombatDecisionFactors {};
public:
    void __cdecl ClearTicket(::Zone *);  // 0x3fee50
    static bool __cdecl CheckLOS(::Zone *, ::vector16, ::vector16, int);  // 0x4053d0
    bool __cdecl Set(::Npc &, unsigned __int64, char, char);  // 0x405a20
protected:
    virtual bool __cdecl resetData(::Npc &);  // 0x405a90
public:
    bool __cdecl IsInAttackRange(::Npc &, short, __int64, short, bool &);  // 0x405c70
    bool __cdecl Transit(::Npc &, int);  // 0x405e30
    bool __cdecl CheckCondition(::Creature *, char);  // 0x405f20
    bool __cdecl GetCloseInPosition(::Npc &, ::vector16, ::Creature &, short, ::vector16 &, bool);  // 0x4060c0
private:
    bool __cdecl isTransitable(::Npc &, char, int, char);  // 0x406310
    int __cdecl checkTransitableCondIndex(::Npc &, int);  // 0x406470
public:
    virtual ::Action * __cdecl NextCombatAction(::BrainBase &, ::Creature *, int, ::NpcActionQueue::ActionExpiredReason, bool &);  // 0x406530
private:
    bool __cdecl applyLastActionResult(::Npc &, ::Creature *, ::NpcActionQueue::ActionExpiredReason, __int64, bool &, bool &);  // 0x4069c0
    ::Action * __cdecl checkFallAction(::Npc &, ::Zone *);  // 0x406e90
    ::Action * __cdecl createTransitAction(::Npc &, ::Creature *);  // 0x407010
    ::Action * __cdecl createSequenceStartAction(::Npc &, ::Creature *);  // 0x4071b0
    bool __cdecl setCombatDecisionFactors(::Npc &, ::Creature *, ::CombatSequence::CombatDecisionFactors &);  // 0x4072e0
    void __cdecl setSpecialSequenceCombatDecisionFactors(::Npc &, short, ::CombatSequence::CombatDecisionFactors &);  // 0x4075b0
    ::Action * __cdecl createSequenceAction(::BrainBase &, ::Creature *, __int64, ::CombatSequence::CombatDecisionFactors &);  // 0x407660
    bool __cdecl fireSpecial(::BrainBase &, ::Creature *);  // 0x407740
    char __cdecl checkSpecialFired(::Npc &, char, __int64, ::ScriptEvent &);  // 0x407c80
    bool __cdecl checkSpecialCondition(::Npc &, char const *, ::DrScriptObj const *, unsigned __int64, ::ScriptEvent &);  // 0x407d40
public:
    bool __cdecl FireSpecial(::Npc &, char, unsigned __int64, long, __int64);  // 0x408030
private:
    void __cdecl finishSpecial(::Npc &);  // 0x4080b0
    ::Action * __cdecl createSpecialAction(::BrainBase &, ::Creature *, ::CombatSequence::CombatDecisionFactors const &);  // 0x408130
    ::Action * __cdecl createNormalAction(::BrainBase &, ::Creature *, ::CombatSequence::CombatDecisionFactors const &);  // 0x408520
    ::Action * __cdecl createSkillCooldown(::Npc &, ::Creature *, __int64, ::CombatSequence::CombatDecisionFactors const &);  // 0x4087d0
    ::Action * __cdecl registerLastAction(::Action *, ::Data::CombatSequenceAction const &);  // 0x408970
protected:
    virtual ::Action * __cdecl createAction(::BrainBase &, ::Creature *, ::Data::CombatSequenceAction const &, ::CombatSequence::CombatDecisionFactors const &, ::ScriptEvent &, char &, char &);  // 0x4089c0
    ::Action * __cdecl createSkillAction(::BrainBase &, ::Creature *, ::CombatSequence::CombatDecisionFactors const &, ::ScriptEvent &, ::DrScriptObj, unsigned __int64, char, int, bool, bool, char &, char, ::DrScriptObj const *const, unsigned __int64 const *const);  // 0x409840
    ::Action * __cdecl createGroundSkillAction(::BrainBase &, ::vector16 const &, ::CombatSequence::CombatDecisionFactors const &, ::ScriptEvent &, unsigned __int64, char, int, char &);  // 0x409ea0
private:
    ::Action * __cdecl createStayAction(::Npc &, ::ScriptEvent &, ::DrScriptObj, long, int);  // 0x40a020
    ::Action * __cdecl createMoveToTicket(::Npc &, ::Creature &, int, ::Data::CombatSequenceSetupDirType);  // 0x40a180
    int __cdecl assignTargetTicket(::Zone *, ::vector16 const &, ::Creature &, int, ::vector16 &);  // 0x40a280
    void __cdecl clearTargetTicket(::Zone *, ::Creature *);  // 0x40a320
};

