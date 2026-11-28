// duelmanager.h: duelmanager.cpp, duelmanager.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"
#include <stddef.h>

// LIFT: view of the PDB record Data::DuelRecord (base DrEl, size 0x440).
// Only the fields that the lifted bodies read are declared.
struct DuelRecordView
{
    char lift_pad_0[0x3D8];  // ❓ no PDB name: fields +0 to +0x3D7 are not declared yet
    bool is_unrated_match;  // +984 (0x3D8)
};

// LIFT: partial view of the PDB class DuelManager (size 0xD4B0). The bodies read it with reinterpret_cast.
// Only the fields that the lifted bodies read are declared.
struct DuelManagerView
{
    void *lift_vfptr;  // +0 (0x0) vfptr
    ::DuelRecordView *_data;  // +8 (0x8) PDB type Data::DuelRecordPtr (one pointer _record)
    char lift_pad_10[0x39];  // PDB fields +0x10 to +0x48 (_zone to _teamEnd)
    bool _calcRatingScore;  // +73 (0x49)
};
static_assert(offsetof(DuelManagerView, _calcRatingScore) == 0x49, "DuelManager::_calcRatingScore");

class DuelManager
{
public:
    enum DuelScoreResult {};
private:
    bool __cdecl isSaveGameResult(void) const;  // 0x97070
public:
    __cdecl DuelManager(void);  // 0xb1d00
    virtual __cdecl ~DuelManager(void);  // 0xb1e00
    bool __cdecl Initialize(::Zone *const, ::Data::DuelRecordPtr const &);  // 0xb1ed0
    void __cdecl FetchMembers(::FragmentPacket &);  // 0xb2250
    void __cdecl SetRoomInfo(::ArenaLobbyRoomInfo const &);  // 0xb2430
    ::DuelMember *const __cdecl GetDuelMember(::Pc const *const);  // 0xb2590
    ::DuelMember const *const __cdecl GetDuelMember(::Pc const *const) const;  // 0xb2620
    ::DuelMember *const __cdecl GetDuelMember(unsigned __int64);  // 0xb26b0
    bool __cdecl IsDuelMember(::Pc const *const) const;  // 0xb2770
    bool __cdecl Enter(::Pc *const);  // 0xb2810
    bool __cdecl Leave(::Pc *const);  // 0xb3310
    void __cdecl EnterByRevive(::ControlledCreature *const);  // 0xb3bd0
    bool __cdecl Ready(unsigned __int64, short &);  // 0xb3f40
    bool __cdecl ReadyAll(short &);  // 0xb4230
    void __cdecl NotifyDuelDeath(unsigned __int64, ::Pc const *const);  // 0xb4560
    void __cdecl OnTimer(void);  // 0xb4660
    void __cdecl OnDead(::Pc *const);  // 0xb48a0
    bool __cdecl OnDamaged(::Pc *const, ::ControlledCreature *const, __int64);  // 0xb4a80
    void __cdecl OnSkillChanged(::Pc *const);  // 0xb4b70
protected:
    void __cdecl clearDuelMemberState(::Pc *const, bool);  // 0xb4c50
    void __cdecl spawnDuelMember(::Pc *const, ::Data::ZonePcSpawnRecordPtr, bool);  // 0xb4e40
public:
    int const __cdecl GetDuelTypeCodeForLog(void) const;  // 0xb5020
private:
    virtual bool __cdecl verifyRoomInfo(void) const;  // 0xb5080
    void __cdecl addDuelTimer(long);  // 0xb5170
    bool __cdecl isAllRoundEntrance(void) const;  // 0xb52d0
    bool __cdecl setTeamRatingScore(void);  // 0xb5350
    void __cdecl startCountdown(void);  // 0xb56d0
    void __cdecl startGame(void);  // 0xb57c0
    void __cdecl prepareRound(void);  // 0xb6ec0
    void __cdecl checkRound(void);  // 0xb6fb0
protected:
    virtual void __cdecl startRound(void);  // 0xb7130
private:
    void __cdecl finishRound(void);  // 0xb7aa0
    void __cdecl finishGame(void);  // 0xb7c40
    void __cdecl finishGame(::DuelGameResult);  // 0xb7ca0
    void __cdecl standbyNextRound(void);  // 0xb8260
    virtual void __cdecl enterToArena(void);  // 0xb8360
    virtual void __cdecl leaveFromArena(void);  // 0xb8400
protected:
    virtual void __cdecl resetRound(void);  // 0xb84d0
private:
    virtual ::Data::ZonePcSpawnRecordPtr const __cdecl getRoundStartPcSpawn(int, int) const;  // 0xb84e0
    void __cdecl recordGameResult(::Pc *const, int, ::DuelManager::DuelScoreResult);  // 0xb8560
    void __cdecl recordGameResult(::DuelGameResult);  // 0xb8660
    void __cdecl calcDuelRating(::Pc *const, ::DuelManager::DuelScoreResult, int, int, int, int);  // 0xb92a0
    int const __cdecl calcRateDiffByELO(::DuelManager::DuelScoreResult, int, int, int, int) const;  // 0xb9a10
    int const __cdecl calcRateDiffByELORenewal(::DuelManager::DuelScoreResult, int, int, int, int, int) const;  // 0xb9c00
    virtual void __cdecl calcBaseExpPoint(::Pc *const, char, ::DuelManager::DuelScoreResult, ::ResultReward &) const;  // 0xb9d70
    virtual void __cdecl calcBonusExpPoint(::Pc *const, ::DuelManager::DuelScoreResult, int, ::ResultReward &, int &) const;  // 0xb9f50
    bool const __cdecl isBeginner(::Pc *const, char, int &) const;  // 0xba6d0
protected:
    bool __cdecl startDuelResultTran(::Pc *, ::DuelManager::DuelScoreResult, int, ::DuelResultTranResultNotifyInfo const &);  // 0xba850
};

class DuelMember
{
public:
    virtual bool __cdecl ReadyRound(short &);  // 0xb1750
    virtual void __cdecl ResetRound(void);  // 0xb17c0
};

class DuelRule
{
public:
    virtual bool __cdecl IsGameDone(void) const;  // 0xbad50
    virtual ::DuelGameResult const __cdecl CalcGameResult(void) const;  // 0xbada0
    virtual bool __cdecl CanResurrect(::Pc const *const) const;  // 0xbae10
};

class DuelTeam
{
public:
    // LIFT: PDB nested type DuelTeam::DuelMembers (std::list, size 0x18). The lift build has no STL headers.
    // Layout view of the list header: the bodies walk the nodes by hand.
    struct DuelMembers
    {
        struct Node
        {
            Node *_Next;
            Node *_Prev;
            ::DuelMember *_Myval;
        };
        void *lift_alval;  // +0 (0x0) ❓ no PDB name: allocator proxy slot
        Node *_Myhead;  // +8 (0x8)
        unsigned long long _Mysize;  // +16 (0x10)
    };

    __cdecl DuelTeam(int const, int const);  // 0x27bb0
    virtual __cdecl ~DuelTeam(void);  // 0x27c30 (slot 0)
    // LIFT: the virtual functions follow the PDB slot order (ResetRound slot 1, instantiateDuelMember slot 2).
    // ❓ slot 3 onLeave has no body in the sources yet and is not declared.
    virtual void __cdecl ResetRound(void);  // 0xb1cf0
private:
    virtual ::DuelMember *const __cdecl instantiateDuelMember(int, int, ::Pc *const);  // 0x27d60
public:
    bool __cdecl IsTeamMember(::Pc const *const) const;  // 0xb17e0
    bool __cdecl IsTeamMemberAllDead(void) const;  // 0xb1860
    ::DuelMember *const __cdecl GetDuelMember(::Pc const *const);  // 0xb1890
    bool __cdecl Join(int, ::Pc *const);  // 0xb1920
    bool __cdecl Leave(::Pc *const);  // 0xb1b20
private:
    int const _teamIndex;  // +8 (0x8)
protected:
    DuelMembers _members;  // +16 (0x10)
    __int64 _reserveKey;  // +40 (0x28)
private:
    int _maxMemberCount;  // +48 (0x30)
    int _ratingScore;  // +52 (0x34)
    int _maxRatingScore;  // +56 (0x38)
    int _totalRatingScore;  // +60 (0x3C)
    __int64 _teamAttackDamage;  // +64 (0x40)
    __cdecl DuelTeam(DuelTeam const &);  // PDB: private, no body
    DuelTeam &operator=(DuelTeam const &);  // PDB: private, no body
};
static_assert(sizeof(DuelTeam) == 0x48, "DuelTeam size");

