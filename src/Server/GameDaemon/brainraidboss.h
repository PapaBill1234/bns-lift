// brainraidboss.h: brainraidboss.cpp, brainraidboss.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"
#include "brainconst.h"

// LIFT: view of the PDB class CombatSeqState (base BrainState, size 0x18). Only the fields that the lifted bodies read are declared.
struct BrainRaidBossCombatSeqStateView
{
    void *lift_vfptr;  // +0 (0x0): vfptr of BrainState
    ::CombatSequence *_combatSeq;  // +8 (0x8) (PDB: CombatSequence &)
    unsigned __int64 _lastTargetId;  // +16 (0x10)
};

class BrainRaidBoss : private ::LiftBytes<0xC08 - 8>  // LIFT: PDB base BrainBase, _actSeq, _bossCombatSeq and _hateList (+8 to +0xC07) are not declared yet
{
protected:
    virtual unsigned __int64 __cdecl GetLastTargetId(void) const;  // 0x634a0
    virtual ::BrainState * __cdecl GetState(::BrainConst::State);  // 0x634b0
    __cdecl BrainRaidBoss(::Npc &);  // 0x634f0
public:
    virtual void __cdecl InitSpecialState(void);  // 0x63700
    void __cdecl GatherSpecialTargets(char, char, bool, bool, char, bool, char);  // 0x63730
private:
    void __cdecl getNearSpecialTargets(::Creature **const, char, char);  // 0x63ac0
    void __cdecl getFarSpecialTargets(::Creature **const, char, char);  // 0x63c80
    void __cdecl getMinHateSpecialTargets(::Creature **const, char, char);  // 0x63e40
private:
    // PDB layout (size 0xCB8). The vfptr is at +0.
    unsigned __int64 _spawn[1];  // +3080 (0xC08) (PDB: SpawnState, size 0x8)
    unsigned __int64 _act[2];  // +3088 (0xC10) (PDB: ActSeqState, size 0x10)
    ::BrainRaidBossCombatSeqStateView _combat;  // +3104 (0xC20) (PDB: CombatSeqState)
    unsigned __int64 _return[3];  // +3128 (0xC38) (PDB: ReturnState, size 0x18)
    unsigned __int64 _specialTargets[12];  // +3152 (0xC50)
    char _specialRotateCount;  // +3248 (0xCB0)
};

