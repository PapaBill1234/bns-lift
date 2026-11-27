// npcaction.h: npcaction.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"
#include "action.h"

class NpcChangeWeaponAndStanceAction
{
private:
    virtual void __cdecl startAction(void);  // 0x420f60
    virtual void __cdecl cancelAction(::Action::CancelReason, wchar_t const *, int);  // 0x421190
    virtual void __cdecl failAction(::Action::FailReason);  // 0x421210
};

class NpcPathFindMoveAction
{
public:
    enum NpcMoveSpeed {};
public:
    __cdecl NpcPathFindMoveAction(::ActionClass);  // 0x41e510
    bool __cdecl Initialize(::Npc &, ::vector16 const &, ::MoveType, ::NpcPathFindMoveAction::NpcMoveSpeed, short, unsigned __int64, bool *const);  // 0x41e580
    static bool __cdecl IsStraightWalkable(::Zone *, ::vector16 const &, ::vector16 const &);  // 0x41e670
private:
    bool __cdecl isSameCell(::vector16 const &, ::vector16 const &);  // 0x41e730
    bool __cdecl needResearch(void) const;  // 0x41e8d0
protected:
    bool __cdecl searchPath(::vector16 const &, long);  // 0x41e9d0
    virtual void __cdecl startAction(void);  // 0x41ed70
    virtual void __cdecl intervalAction(long);  // 0x41ee80
private:
    bool __cdecl pathfindMove(::vector16 const &, long);  // 0x41ef80
protected:
    virtual bool __cdecl arrived(::vector16 const &, ::vector16 const &);  // 0x41f370
private:
    bool __cdecl move(::vector16 const &, long);  // 0x41f390
    short __cdecl getSpeed(::NpcPathFindMoveAction::NpcMoveSpeed) const;  // 0x41f800
};

class NpcChaseMoveAction
{
public:
    enum DistanceCheckResult {};
public:
    bool __cdecl Initialize(::Npc &, ::Creature &, short, ::MoveType, ::NpcPathFindMoveAction::NpcMoveSpeed, ::vector16 const &, bool, bool *const);  // 0x41f8b0
protected:
    ::vector16 __cdecl getDestinationPos(::Creature *, ::Creature *, bool *const);  // 0x41f980
    virtual bool __cdecl updateDestination(::vector16 &, long);  // 0x4201a0
public:
    static ::NpcChaseMoveAction::DistanceCheckResult __cdecl CheckTargetDistance(::vector16 const &, ::vector16 const &, ::vector16 const &, ::Data::NpcRecordPtr);  // 0x420520
protected:
    virtual bool __cdecl arrived(::vector16 const &, ::vector16 const &);  // 0x420620
};

class NpcDetectCreatureAction
{
public:
    bool __cdecl Initialize(::Zone *, ::Npc *, short, short);  // 0x4217a0
private:
    virtual void __cdecl startAction(void);  // 0x4218b0
    virtual void __cdecl failAction(::Action::FailReason);  // 0x421cb0
};

class NpcFallAction
{
public:
    bool __cdecl Initialize(::Zone *, ::Npc *, ::GeoCell *);  // 0x41db30
    virtual bool __cdecl IsAvailableAction(void);  // 0x41dc30
private:
    virtual void __cdecl startAction(void);  // 0x41dc60
    virtual void __cdecl intervalAction(long);  // 0x41de00
    virtual void __cdecl finishAction(void);  // 0x41e370
    virtual void __cdecl cancelAction(::Action::CancelReason, wchar_t const *, int);  // 0x41e420
};

class NpcFollowMoveAction
{
protected:
    virtual bool __cdecl updateDestination(::vector16 &, long);  // 0x420e20
    virtual bool __cdecl arrived(::vector16 const &, ::vector16 const &);  // 0x420f40
};

class NpcGroupMoveSyncAction
{
public:
    bool __cdecl Initialize(::Zone *, ::Npc *, short);  // 0x41bee0
private:
    virtual void __cdecl startAction(void);  // 0x41bfe0
    virtual void __cdecl intervalAction(long);  // 0x41c0a0
};

class NpcHideAction
{
private:
    bool __cdecl Initialize(::Zone *, ::Npc *, bool, unsigned __int64);  // 0x41c4f0
    virtual void __cdecl startAction(void);  // 0x41c600
    virtual void __cdecl intervalAction(long);  // 0x41c810
    virtual void __cdecl cancelAction(::Action::CancelReason, wchar_t const *, int);  // 0x41c840
};

class NpcIdleAction
{
public:
    enum IdleType {};
public:
    bool __cdecl Initialize(::Zone *, ::Npc *, ::NpcIdleAction::IdleType, long, unsigned char);  // 0x41bc20
    virtual bool __cdecl IsAvailableAction(void);  // 0x41bd70
private:
    virtual void __cdecl startAction(void);  // 0x41bdd0
    virtual void __cdecl intervalAction(long);  // 0x41be30
};

class NpcKnockBackAction
{
private:
    bool __cdecl Initialize(::Zone *, ::Npc *, __int64);  // 0x41c8d0
    virtual void __cdecl startAction(void);  // 0x41c9d0
    virtual void __cdecl finishAction(void);  // 0x41ca20
    virtual void __cdecl cancelAction(::Action::CancelReason, wchar_t const *, int);  // 0x41ca40
};

class NpcPredefinedMoveAction
{
public:
    enum NpcMoveSpeed {};
    enum NpcMoveType {};
public:
    static wchar_t * __cdecl NpcMoveTypeName(::NpcPredefinedMoveAction::NpcMoveType);  // 0x41ca80
    bool __cdecl SetDestination(::vector16 const *, int, ::NpcPredefinedMoveAction::NpcMoveSpeed, bool, short);  // 0x41cac0
    virtual bool __cdecl IsAvailableAction(void);  // 0x41cc00
private:
    virtual void __cdecl startAction(void);  // 0x41cc40
    virtual void __cdecl intervalAction(long);  // 0x41cd90
    bool __cdecl move(::vector16 const &, long, bool);  // 0x41d150
    bool __cdecl createPath(void);  // 0x41d450
    short __cdecl getSpeed(::NpcPredefinedMoveAction::NpcMoveSpeed) const;  // 0x41d730
    short __cdecl getYaw(::vector16 const &, ::vector16 const &) const;  // 0x41d7e0
    ::MoveType __cdecl getMoveType(::NpcPredefinedMoveAction::NpcMoveSpeed) const;  // 0x41d850
    long __cdecl getTimerDuration(void) const;  // 0x41d8f0
};

class NpcSocialAction
{
public:
    bool __cdecl Initialize(::Zone *, ::Npc *, unsigned int, short, long);  // 0x41c130
private:
    virtual void __cdecl startAction(void);  // 0x41c270
    virtual void __cdecl intervalAction(long);  // 0x41c3b0
    virtual void __cdecl cancelAction(::Action::CancelReason, wchar_t const *, int);  // 0x41c460
};

class NpcWarpAction
{
private:
    virtual void __cdecl startAction(void);  // 0x4212a0
};

