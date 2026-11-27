// systemaction.h: systemaction.cpp, systemaction.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"
#include "action.h"

class DieAction
{
private:
    virtual void __cdecl startAction(void);  // 0x4bb5e0
    virtual void __cdecl finishAction(void);  // 0x4bb700
    virtual void __cdecl cancelAction(::Action::CancelReason, wchar_t const *, int);  // 0x4bb8b0
    void __cdecl spawnAdditionalNpc(::BossNpc *);  // 0x4bb950
    void __cdecl getAuthorizedMember(::BossNpc *, ::NpcSpawnParam &);  // 0x4bbc60
};

class HelpRestorationAction
{
private:
    virtual void __cdecl startAction(void);  // 0x4bde20
    virtual void __cdecl failAction(::Action::FailReason);  // 0x4be310
    virtual void __cdecl finishAction(void);  // 0x4be370
    virtual void __cdecl cancelAction(::Action::CancelReason, wchar_t const *, int);  // 0x4be460
};

class LeaveAction
{
public:
    struct PhaseZone {};
private:
    virtual ::ActionPriorityClass __cdecl getPriority(void) const;  // 0x4b7930
public:
    __cdecl LeaveAction(void);  // 0x4b7970
private:
    void __cdecl applyLeaveCost(void);  // 0x4b7b10
    bool __cdecl initialize(::Zone *, ::Creature *, ::LeaveType, unsigned int, short, unsigned __int64, short, ::LeaveReason, unsigned __int64, unsigned __int64, unsigned __int64, unsigned __int64, ::LeaveAction::PhaseZone *, unsigned __int64, unsigned __int64);  // 0x4b8310
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, ::LeaveType, unsigned int, ::LeaveReason, unsigned __int64, unsigned __int64, unsigned __int64, unsigned __int64, unsigned __int64);  // 0x4b87d0
    bool __cdecl InitializeWithPcSpawn(::Zone *, ::Creature *, ::LeaveType, unsigned int, short, ::LeaveReason, unsigned __int64, unsigned __int64, unsigned __int64, unsigned __int64, ::LeaveAction::PhaseZone *, unsigned __int64);  // 0x4b8850
    bool __cdecl InitializeWithArea(::Zone *, ::Creature *, ::LeaveType, unsigned int, unsigned __int64, ::LeaveReason, unsigned __int64, unsigned __int64, unsigned __int64, unsigned __int64, ::LeaveAction::PhaseZone *);  // 0x4b88e0
    bool __cdecl Initialize(::Zone *, ::Creature *, unsigned int, short);  // 0x4b8970
    bool __cdecl Initialize(::Zone *, ::Creature *, short);  // 0x4b8a90
    bool __cdecl InitializeWithEnterArenaLobby(::Zone *, ::Creature *, ::ArenaLobbyRoomInfo &);  // 0x4b8b00
    bool __cdecl InitializeWithReturnToArenaDungeon(::Zone *, ::Creature *, ::ArenaLobbyRoomInfo &);  // 0x4b8be0
    bool __cdecl InitializeWithReturnToArenaLobby(::Zone *, ::Pc *, unsigned __int64);  // 0x4b8cc0
    bool __cdecl Initialize(::Zone *, ::Creature *, ::LeaveType, unsigned int, short, ::vector16 &, ::LeaveReason, unsigned __int64, unsigned __int64, unsigned __int64, unsigned __int64);  // 0x4b8df0
    bool __cdecl Initialize(::Zone *, ::Creature *, ::LeaveType, unsigned int, ::vector16, ::LeaveReason);  // 0x4b8e90
    bool __cdecl Initialize(::Zone *, ::Creature *, ::LeaveType, unsigned int, unsigned __int64, ::LeaveReason);  // 0x4b8f20
    virtual __cdecl ~LeaveAction(void);  // 0x4b8f90
    void __cdecl AddNext(::LeaveAction *);  // 0x4b90d0
    ::LeaveAction * __cdecl RemoveNext(void);  // 0x4b9170
    void __cdecl Post(void);  // 0x4b91c0
private:
    virtual bool __cdecl prepareAction(void);  // 0x4b92e0
    virtual void __cdecl startAction(void);  // 0x4b9710
    bool __cdecl selectTransitZone(short, unsigned __int64 *, unsigned int *, unsigned __int64 *, unsigned __int64 *, unsigned __int64 *, unsigned __int64 *, short *, char);  // 0x4ba1a0
    virtual void __cdecl intervalAction(long);  // 0x4ba3f0
    virtual void __cdecl finishAction(void);  // 0x4ba420
    virtual void __cdecl cancelAction(::Action::CancelReason, wchar_t const *, int);  // 0x4baef0
    virtual void __cdecl failAction(::Action::FailReason);  // 0x4baf90
    bool __cdecl translatePosition(void);  // 0x4bb000
    void __cdecl sendFailPacket(::GameFailReason);  // 0x4bb530
    void __cdecl clearChannelChangeCooltime(void);  // 0x4bb5a0
};

class PcSpawnAction
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, short, short, short, short, short, unsigned __int64, ::EnterReason, unsigned __int64, bool, bool, unsigned int);  // 0x4b47e0
    void __cdecl AddNext(::PcSpawnAction *);  // 0x4b4a60
private:
    virtual void __cdecl startAction(void);  // 0x4b4b00
    virtual void __cdecl intervalAction(long);  // 0x4b4db0
    void __cdecl prepareSpawn(void);  // 0x4b4e50
    bool __cdecl spawn(::ControlledCreature *, ::vector16, ::GeoCell, short, unsigned __int64, bool);  // 0x4b5160
public:
    void __cdecl SpawnCreature(::vector16, short);  // 0x4b5500
private:
    virtual void __cdecl finishAction(void);  // 0x4b5ab0
    virtual void __cdecl cancelAction(::Action::CancelReason, wchar_t const *, int);  // 0x4b6dd0
    virtual void __cdecl failAction(::Action::FailReason);  // 0x4b6e50
    void __cdecl revive(void);  // 0x4b6ea0
    bool __cdecl checkSpawnPosition(void);  // 0x4b7630
};

class RestorationAction
{
private:
    virtual void __cdecl cancelAction(::Action::CancelReason, wchar_t const *, int);  // 0x456530
    bool __cdecl calcHelperTime(void);  // 0x4bc260
    bool __cdecl updateRemainTime(void);  // 0x4bc340
    void __cdecl finishHelperAction(void);  // 0x4bc4a0
public:
    bool __cdecl LeaveHelper(::ControlledCreature *);  // 0x4bc560
private:
    virtual bool __cdecl prepareAction(void);  // 0x4bc600
    virtual void __cdecl startAction(void);  // 0x4bc6a0
    void __cdecl revive(void);  // 0x4bcad0
    void __cdecl die(unsigned __int64);  // 0x4bd330
    virtual void __cdecl failAction(::Action::FailReason);  // 0x4bd3d0
    virtual void __cdecl finishAction(void);  // 0x4bd400
    virtual void __cdecl cancelAction(::Action::CancelReason, wchar_t const *, int, unsigned __int64);  // 0x4bdd20
    virtual bool __cdecl availableCancel(::CancelActionReason);  // 0x4bde10
};

class ReviveAction
{
private:
    virtual void __cdecl startAction(void);  // 0x4bbed0
    virtual void __cdecl finishAction(void);  // 0x4bc0e0
    virtual void __cdecl cancelAction(::Action::CancelReason, wchar_t const *, int);  // 0x4bc160
    virtual void __cdecl failAction(::Action::FailReason);  // 0x4bc1f0
};

wchar_t const * __cdecl GetEnterReasonString(::EnterReason);  // 0x4b4600
wchar_t const * __cdecl GetLeaveReasonString(::LeaveReason);  // 0x4b46a0
