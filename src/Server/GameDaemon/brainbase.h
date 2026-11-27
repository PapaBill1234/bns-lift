// brainbase.h: brainbase.cpp, brainbase.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"
#include "action.h"
#include "brainconst.h"

class BrainBase
{
public:
    struct TransitionTable {};
public:
    bool __cdecl IsPeace(void) const;  // 0x34f040
protected:
    __cdecl BrainBase(::Npc &, ::BrainBase::TransitionTable &, ::Data::NpcBrainType, char);  // 0x3feee0
    virtual __cdecl ~BrainBase(void);  // 0x3fefc0
public:
    virtual bool __cdecl Start(::BrainConst::State);  // 0x3fefd0
    virtual bool __cdecl Stop(void);  // 0x3ff0f0
protected:
    void __cdecl actionFinished(::Action *, ::NpcActionQueue::ActionExpiredReason);  // 0x3ff1a0
public:
    bool __cdecl EventOccured(::BrainConst::Event, bool);  // 0x3ff320
    bool __cdecl isValidTargetBySquadRule(::Creature *, ::vector16 const &);  // 0x3ff790
    int __cdecl getTargetBySquadTargetRule(::Pointer2< ::Creature> *, ::vector16 const &);  // 0x3ff890
    int __cdecl GetTarget(::Pointer2< ::Creature> *, int &, bool);  // 0x3ffd80
    static bool __cdecl IsValidTarget(::Npc &, ::Creature &);  // 0x400080
    void __cdecl GetTargetIds(unsigned __int64 *, unsigned __int64 *, int *);  // 0x400110
    void __cdecl GetTargetIdsExceptCond(unsigned __int64 *, unsigned __int64 *, char, int *);  // 0x400220
    int __cdecl AddHate(::Creature *, __int64, bool);  // 0x4003f0
    int __cdecl AddHate(unsigned __int64, __int64, bool);  // 0x400560
    bool __cdecl UpdateHateTime(unsigned __int64);  // 0x4005f0
    virtual bool __cdecl ResetHateByTargetId(unsigned __int64, wchar_t const *);  // 0x400660
    virtual bool __cdecl ResetHateByIndex(int, wchar_t const *);  // 0x4006b0
    void __cdecl ResetAllHates(wchar_t const *);  // 0x400d10
    void __cdecl SetProvocativeTarget(unsigned __int64);  // 0x400d80
    void __cdecl SetMinHate(unsigned __int64);  // 0x401000
    void __cdecl SetMaxHate(unsigned __int64);  // 0x4011d0
    __int64 __cdecl GetHateById(unsigned __int64) const;  // 0x401390
    __int64 __cdecl GetHateByIndex(int) const;  // 0x401410
    int __cdecl getTargetByHateRule(::Pointer2< ::Creature> *, int &);  // 0x401480
protected:
    ::Creature * __cdecl isValidHate(int, int &);  // 0x401750
private:
    void __cdecl changeTargetProp(unsigned __int64);  // 0x401a20
    int __cdecl findHateful(unsigned __int64, bool, __int64);  // 0x401aa0
    ::BrainBase * __cdecl getReferenceHateBrain(void) const;  // 0x401cc0
public:
    void __cdecl CopyHateList(::BrainBase *);  // 0x401da0
    void __cdecl SetReferenceHateTargetId(unsigned __int64);  // 0x401fa0
    unsigned __int64 __cdecl GetTopHateTargetId(bool);  // 0x402040
    unsigned __int64 __cdecl GetMinHateTargetId(bool);  // 0x402160
    void __cdecl SetForcedCombatMode(bool, unsigned __int64);  // 0x402280
    int __cdecl GetLastTarget(::Pointer2< ::Creature> *);  // 0x402320
    unsigned __int64 __cdecl GetNearestTargetId(bool);  // 0x402420
    unsigned __int64 __cdecl GetNearestTargetPcInDetectRange(void);  // 0x4025a0
    unsigned __int64 __cdecl GetFarthestTargetId(bool);  // 0x402710
protected:
    void __cdecl traceHate(wchar_t *, ...);  // 0x402880
private:
    void __cdecl pushState(::BrainConst::State);  // 0x402910
    ::BrainConst::State __cdecl popState(::BrainConst::State);  // 0x4029a0
public:
    bool __cdecl CancelActionByCombatSeqTransit(void);  // 0x402a20
};

