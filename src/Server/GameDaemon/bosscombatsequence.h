// bosscombatsequence.h: bosscombatsequence.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"
#include "action.h"
#include "combatsequence.h"

class BossCombatSequence : private ::LiftBytes<0x188 - 8>  // LIFT: PDB base CombatSequence (+8 to +0x187) is not declared yet
{
public:
    virtual __cdecl ~BossCombatSequence(void);  // 0x630d0
    virtual ::Action * __cdecl NextCombatAction(::BrainBase &, ::Creature *, int, ::NpcActionQueue::ActionExpiredReason, bool &);  // 0x77bc0
    virtual bool __cdecl ReserveTransitBerserk(unsigned __int64);  // 0x77d70
protected:
    void __cdecl transitBerserk(::BossNpc &, unsigned __int64);  // 0x77d90
    virtual bool __cdecl resetData(::Npc &);  // 0x77e60
    virtual ::Action * __cdecl createAction(::BrainBase &, ::Creature *, ::Data::CombatSequenceAction const &, ::CombatSequence::CombatDecisionFactors const &, ::ScriptEvent &, char &, char &);  // 0x77ea0
private:
    ::Action * __cdecl createRushAttack(::BrainBase &, ::Creature *, ::Data::CombatSequenceActionBossRushAttack const &, ::CombatSequence::CombatDecisionFactors const &, ::ScriptEvent &, char &);  // 0x78100
    ::Action * __cdecl createRepeaterAttack(::BrainBase &, ::Creature *, ::Data::CombatSequenceActionBossRepeaterAttack const &, ::CombatSequence::CombatDecisionFactors const &, ::ScriptEvent &, char &);  // 0x784e0
    ::Action * __cdecl createMultigroundAttack(::BrainBase &, ::Creature *, ::Data::CombatSequenceActionBossMultigroundAttack const &, ::CombatSequence::CombatDecisionFactors const &, ::ScriptEvent &, char &);  // 0x785f0
    ::Action * __cdecl createSpSelectAttack(::BrainBase &, ::Creature *, ::Data::CombatSequenceActionBossSpSelectAttack const &, ::CombatSequence::CombatDecisionFactors const &, ::ScriptEvent &, char &);  // 0x78830
    ::Action * __cdecl createGpSelectAttack(::BrainBase &, ::Creature *, ::Data::CombatSequenceActionBossGpSelectAttack const &, ::CombatSequence::CombatDecisionFactors const &, ::ScriptEvent &, char &);  // 0x78970
    ::Action * __cdecl createSimultaneousGroundAttack(::BrainBase &, ::Creature *, ::Data::CombatSequenceActionBossSimultaneousGroundAttack const &, ::CombatSequence::CombatDecisionFactors const &, ::ScriptEvent &, char &);  // 0x78ab0
    ::Action * __cdecl createSimultaneousCasterAttack(::BrainBase &, ::Creature *, ::Data::CombatSequenceActionBossSimultaneousCasterAttack const &, ::CombatSequence::CombatDecisionFactors const &, ::ScriptEvent &, char &);  // 0x78bc0
    ::Action * __cdecl createRisingAttack(::BrainBase &, ::Creature *);  // 0x78cd0
    ::Action * __cdecl createWakeupAttack(::BrainBase &, ::Creature *);  // 0x794b0
private:
    // PDB layout (size 0x198). The vfptr is at +0.
    bool _isInBerserkSeq;  // +392 (0x188)
    unsigned __int64 _reservedBerserkSeqId;  // +400 (0x190)
};

