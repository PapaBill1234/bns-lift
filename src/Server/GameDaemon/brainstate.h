// brainstate.h: brainstate.cpp, brainstate.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"
#include "action.h"

class ActSeqState
{
public:
    virtual __cdecl ~ActSeqState(void);  // 0x633b0
protected:
    virtual ::Action * __cdecl enter(::BrainBase &);  // 0x4039a0
    virtual ::Action * __cdecl process(::BrainBase &, ::NpcActionQueue::ActionExpiredReason);  // 0x403c60
    virtual void __cdecl leave(::BrainBase &);  // 0x403d60
};

class CombatSeqState
{
protected:
    virtual ::Action * __cdecl enter(::BrainBase &);  // 0x4044b0
    virtual ::Action * __cdecl process(::BrainBase &, ::NpcActionQueue::ActionExpiredReason);  // 0x4044e0
    virtual void __cdecl leave(::BrainBase &);  // 0x404920
};

class FollowState
{
public:
    void __cdecl SetMaster(::Npc &, unsigned __int64, ::Data::ActSequenceDetectType, int, int);  // 0x403dc0
    void __cdecl ChangeMaster(::Npc &, unsigned __int64);  // 0x403e70
protected:
    virtual ::Action * __cdecl enter(::BrainBase &);  // 0x403f10
    virtual ::Action * __cdecl process(::BrainBase &, ::NpcActionQueue::ActionExpiredReason);  // 0x403f30
public:
    bool __cdecl GetNextPosition(::Npc &, ::vector16 &, ::Creature *);  // 0x404200
    void __cdecl ClearTicket(::Zone *, ::Creature *);  // 0x404390
protected:
    virtual void __cdecl leave(::BrainBase &);  // 0x404430
};

class ReturnState
{
protected:
    virtual ::Action * __cdecl enter(::BrainBase &);  // 0x404e40
    virtual ::Action * __cdecl process(::BrainBase &, ::NpcActionQueue::ActionExpiredReason);  // 0x405020
    virtual void __cdecl leave(::BrainBase &);  // 0x4050b0
    ::Action * __cdecl createReturnLongWarp(::Npc &);  // 0x405220
    void __cdecl removeDebuff(::Npc &);  // 0x4052e0
};

class SpawnState
{
protected:
    ::Action * __cdecl createSpawnSkill(::Npc &);  // 0x4034c0
    ::Action * __cdecl createSpawnIdle(::Npc &);  // 0x403590
    virtual ::Action * __cdecl enter(::BrainBase &);  // 0x403630
    virtual ::Action * __cdecl process(::BrainBase &, ::NpcActionQueue::ActionExpiredReason);  // 0x4037e0
    virtual void __cdecl leave(::BrainBase &);  // 0x403850
};

class TalkState
{
protected:
    bool __cdecl resizePcList(void);  // 0x404a00
    virtual ::Action * __cdecl enter(::BrainBase &);  // 0x404ab0
    virtual ::Action * __cdecl process(::BrainBase &, ::NpcActionQueue::ActionExpiredReason);  // 0x404bd0
    virtual void __cdecl leave(::BrainBase &);  // 0x404c20
    void __cdecl ClearPcList(wchar_t const *);  // 0x404d30
};

