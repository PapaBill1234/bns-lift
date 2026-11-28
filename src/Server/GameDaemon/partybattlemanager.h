// partybattlemanager.h: partybattlemanager.cpp, partybattlemanager.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include <stddef.h>
#include "GameDaemonFwd.h"

class PartyBattleGameLog
{
public:
    static void __cdecl WritePartyBattleTeamStart(::Zone *, ::PartyBattleManager *, char, int, ::PartyBattleSideMember *const, short);  // 0x188d20
private:
    static void __cdecl getTimeStr(wchar_t *, unsigned __int64, __int64);  // 0x1890f0
public:
    static void __cdecl WritePartyBattleTeamEnd(::Zone *, ::PartyBattleManager *, char, int, ::PartyBattleSideMember *const, short, __int64, ::PartyBattleResult, short, short);  // 0x189190
    static void __cdecl WritePartyBattlePcStart(::Zone *, ::PartyBattleManager *, unsigned __int64, char, int);  // 0x1895b0
    static void __cdecl WritePartyBattleResult(::Zone *, ::PartyBattleManager *, ::Pc *, char, int, int, int, __int64, ::PartyBattleResult, int, __int64, __int64, char);  // 0x1898b0
    static void __cdecl WritePartyBattleDisconnected(::PartyBattleManager *, ::Pc *, char);  // 0x189be0
    static void __cdecl WritePartyBattleRejoin(::PartyBattleManager *, ::Pc *);  // 0x189e60
    static void __cdecl WritePartyBattleMvpVote(::PartyBattleManager *, ::Pc *, unsigned __int64);  // 0x18a0b0
    static void __cdecl WriteOccupyControlPoint(::Zone *, ::PartyBattleManager *, ::Pc *, unsigned __int64, wchar_t *, short, char, char);  // 0x18a4d0
    static void __cdecl WriteCreateBall(::Npc *, char);  // 0x18a840
    static void __cdecl WriteGoalIn(::Zone *, ::PartyBattleManager *, unsigned __int64, __int64, __int64, __int64, __int64);  // 0x18a9b0
private:
    static ::Pc * __cdecl getFirstPartyMember(::Zone *, ::PartyBattleManager *, ::PartyBattleSideMember *const, short);  // 0x18ac30
    static char __cdecl getLogResultCode(::PartyBattleResult, unsigned __int64, char);  // 0x18ace0
};

class PartyBattleManager
{
public:
    enum PartyBattleScoreResult {};
public:
    __cdecl PartyBattleManager(void);  // 0x111af0
    virtual bool __cdecl Init(::Zone *, unsigned __int64);  // 0x1832b0
    void __cdecl SetRoomInfo(::Zone *, ::ArenaLobbyRoomInfo const &, bool);  // 0x183430
    virtual bool __cdecl EnterByRevive(::Pc *);  // 0x183630
    virtual bool __cdecl Enter(::Pc *);  // 0x183830
    virtual bool __cdecl Leave(::Pc *);  // 0x1839d0
    virtual bool __cdecl Ready(::Pc *);  // 0x183b90
    virtual bool __cdecl Start(::Pc *, bool);  // 0x183c40
    virtual void __cdecl Vote(bool, bool, ::PartyBattleResult, char);  // 0x183e40
    virtual void __cdecl Finish(void);  // 0x184220
    virtual bool __cdecl CheckToFinishGame(void);  // 0x184310
    virtual bool __cdecl CanResurrect(::Pc *);  // 0x184370
    virtual bool __cdecl CanTakeAchievementReward(void);  // 0x1843d0
    virtual bool __cdecl GetNearRespawnArea(::Pc *, unsigned int &, unsigned __int64 &);  // 0x1843e0
    virtual void __cdecl DisposeFieldItem(::Pc *, ::FieldItem *);  // 0x1844f0
    virtual void __cdecl OnDamaged(unsigned __int64, ::Creature *, __int64);  // 0x184510
    virtual void __cdecl IncreaseKillCount(::Pc *);  // 0x1845f0
    virtual void __cdecl IncreaseDeathCount(::Pc *);  // 0x1846a0
    virtual void __cdecl IncreaseOccupationCount(::Pc *);  // 0x1846f0
    virtual void __cdecl IncreaseManipulationCount(::Pc *);  // 0x184740
    virtual void __cdecl AddAttackDamage(::Pc *, __int64);  // 0x184790
    virtual void __cdecl AddReceivedDamage(::Pc *, __int64);  // 0x184830
    virtual void __cdecl SetMemberScore(::Pc *, ::PartyBattleResult, int, int, __int64, ::PartyBattleSideMember const &);  // 0x1848d0
    void __cdecl FetchMembers(::FragmentPacket &);  // 0x184980
    void __cdecl SendMemberRecord(::Pc *);  // 0x184b30
    ::PartyBattleSide * __cdecl GetPartyBattleSideByPcDbId(unsigned __int64);  // 0x184d50
    static ::PartyBattleManager * __cdecl CreatePartyBattleManager(::Zone *, unsigned __int64);  // 0x184df0
private:
    virtual ::PartyBattleResult __cdecl getResult(bool);  // 0x184f90
    bool __cdecl enterMember(::Pc *);  // 0x185110
public:
    static void __cdecl ResetPcState(::Pc *);  // 0x185240
    void __cdecl SetVoteMember(void);  // 0x1852d0
    bool __cdecl VoteEnable(::Pc *, unsigned __int64);  // 0x185360
    char __cdecl VoteCast(::Pc *, unsigned __int64, unsigned __int64);  // 0x1853f0
protected:
    void __cdecl initEnv(void);  // 0x185590
    bool __cdecl doEnvOperation(void);  // 0x1856c0
    ::Pc * __cdecl getAttackerPc(::GameObject *);  // 0x1858d0
    bool const __cdecl isBeginner(::Pc *const) const;  // 0x185910
    virtual char __cdecl getIndividualScoreResult(char, ::PartyBattleResult);  // 0x185ad0
    virtual bool __cdecl isSaveGameResult(void);  // 0x185b70
public:
    virtual void __cdecl RecordGameResult(::Pc *, ::PartyBattleResult, int, int, __int64, ::PartyBattleSideMember const &);  // 0x185b90
protected:
    virtual void __cdecl getTeamRatingScore(char, int &, int &, int &) const;  // 0x185ce0
    virtual void __cdecl setTeamRatingScore(void);  // 0x185d90
    bool __cdecl checkFinishByRule(::PartyBattleStep);  // 0x186110
    bool __cdecl startPartyBattleResultTran(::Pc *, ::PartyBattleManager::PartyBattleScoreResult, int, ::PartyBattleResultTranResultNotifyInfo const &);  // 0x1862a0
public:
    bool __cdecl RestoreDisconnectPartyBattleResultTran(::Pc *, int, int);  // 0x1867f0
    void __cdecl DelegateNewEmcee(void);  // 0x186d30
protected:
    virtual int __cdecl calcGuildRatingScore(char, __int64, ::PartyBattleManager::PartyBattleScoreResult, int, int);  // 0x186dc0
    virtual int __cdecl calcRatingScore(::Pc *const, char, ::PartyBattleResult, ::PartyBattleManager::PartyBattleScoreResult, int, int, int, int, int, int, __int64, ::PartyBattleSideMember const &);  // 0x186f60
    virtual int __cdecl calcGuildRatingScoreDiffByELO(::PartyBattleManager::PartyBattleScoreResult, int, int) const;  // 0x1879c0
    virtual int __cdecl calcRatingScoreDiffByELO(::PartyBattleManager::PartyBattleScoreResult, int, int, int, int) const;  // 0x187bb0
    virtual int __cdecl calcRatingScoreDiffByELORenewal(::PartyBattleManager::PartyBattleScoreResult, int, int, int, int, int) const;  // 0x187df0
    virtual void __cdecl calcBaseExpPoint(::Pc *const, char, char, ::PartyBattleManager::PartyBattleScoreResult, int, int, int, int, ::ResultReward &);  // 0x187f60
    virtual void __cdecl calcBonusExpPoint(::Pc *const, char, ::PartyBattleManager::PartyBattleScoreResult, int, ::ResultReward &);  // 0x1884c0
    virtual short __cdecl calcBonusZoneScore(char, short, short);  // 0x188b20
    virtual void __cdecl addZoneScoreOnDead(char, char);  // 0x188c10
};

class PartyBattleSide
{
public:
    __cdecl PartyBattleSide(void);  // 0x181370
    __cdecl ~PartyBattleSide(void);  // 0x1813a0
    bool __cdecl OnEntered(::PartyBattleManager *, ::Pc *);  // 0x1813e0
    bool __cdecl OnLeaved(::PartyBattleManager *, ::Pc *, char);  // 0x181740
    void __cdecl OnFinished(::Zone *, ::PartyBattleManager *);  // 0x1819d0
    void __cdecl IncreaseDeathCount(unsigned __int64);  // 0x181aa0
    void __cdecl IncreaseOccupationCount(unsigned __int64);  // 0x181b20
    void __cdecl IncreaseManipulationCount(unsigned __int64);  // 0x181b80
    void __cdecl InvokeEffectToAllMember(::Zone *, unsigned __int64 *const, char);  // 0x181be0
    void __cdecl SendGoalInAchievement(::Zone *, ::PartyBattleManager *);  // 0x181de0
    void __cdecl SendGoalInCountInfoAllMember(::Zone *, short, short, short, short);  // 0x181f10
    bool __cdecl SetMembers(char, ::ArenaLobbyTeamMemberInfo *const, short, bool);  // 0x182060
    unsigned __int64 __cdecl GetFirstMemberId(void);  // 0x182200
    void __cdecl SetMemberScore(::Zone *, ::PartyBattleManager *);  // 0x182250
    void __cdecl SendMemberRecord(::Zone *, ::PartyBattleManager *);  // 0x1824d0
    bool __cdecl ReturnToArenaLobbyRequest(::Zone *, ::Pc *, bool, unsigned __int64, char, char);  // 0x182670
private:
    void __cdecl spawnAllMember(::Zone *, ::Data::ZonePcSpawnRecordPtr const &);  // 0x182d30
    void __cdecl spawnMember(::Pc *, ::Data::ZonePcSpawnRecordPtr const &);  // 0x182e30
    bool __cdecl invokeEffect(::Zone *, unsigned __int64, ::Data::EffectRecordPtr const &);  // 0x183120
    void __cdecl resetAllMemberSpecialSkillGauge(::Zone *);  // 0x1831d0
private:
    // PDB layout (size 0x30).
    char _combatSide;                   // +0 (0x0)
    short _worldId;                     // +2 (0x2)
    short _memberCapacity;              // +4 (0x4)
    ::PartyBattleSideMember *_member;   // +8 (0x8)
    short _memberCount;                 // +16 (0x10)
    int _ratingScore;                   // +20 (0x14)
    int _totalRatingScore;              // +24 (0x18)
    int _maxRatingScore;                // +28 (0x1C)
    unsigned __int64 _guildId;          // +32 (0x20)
    short _goalInCount;                 // +40 (0x28)
    short _consecutiveGoalInCount;      // +42 (0x2A)
};
static_assert(sizeof(PartyBattleSide) == 0x30, "sizeof PartyBattleSide");

// LIFT: local view of the PDB struct PartyBattleSideMember (size 0x1F0). The name differs on purpose: the view is partial.
struct PartyBattleSideMemberView
{
    char lift_pad_0[0x18];              // ❓ pcInfo (ArenaLobbyTeamMemberInfo) +0 to +0x17 are not declared here
    unsigned __int64 _pcId;             // +24 (0x18) (PDB: pcInfo._pcId)
    char lift_pad_1[0x1A0];             // ❓ pcInfo +0x20 to +0x1BF
    char side;                          // +448 (0x1C0)
    char state;                         // +449 (0x1C1)
    short killCount;                    // +450 (0x1C2)
    short straightKillCount;            // +452 (0x1C4)
    short deathCount;                   // +454 (0x1C6)
    short occupationCount;              // +456 (0x1C8)
    short manipulationCount;            // +458 (0x1CA)
    char lift_pad_2[0x24];              // ❓ attackDamage ... disconnectPrevWinningStreak (+0x1CC to +0x1EF)
};
static_assert(sizeof(PartyBattleSideMemberView) == 0x1F0, "sizeof PartyBattleSideMemberView");

// LIFT: local view of the PDB record Data::PartyBattleFieldZoneRecord (size 0x140). Only goal_score is declared.
struct PartyBattleFieldZoneRecordView
{
    char lift_head[0x102];              // ❓ DrEl, key, alias ... kill_score are not declared here
    short goal_score;                   // +258 (0x102)
};

// LIFT: local view of the PDB class PartyBattleManager (size 0xD5F0). Only the members that the lifted bodies read are declared.
struct PartyBattleManagerView
{
    void *lift_vfptr;                           // +0 (0x0)
    ::PartyBattleFieldZoneRecordView *_data;    // +8 (0x8) (PDB: Data::PartyBattleFieldZoneRecordPtr::_record)
    ::Zone *_zone;                              // +16 (0x10)
    char _step;                                 // +24 (0x18)
    char lift_pad_0[0x35];                      // ❓ _stepStartTime ... _envOperated (+0x19 to +0x4D)
    bool _isGiveReward;                         // +78 (0x4E)
    char lift_pad_1[0x29];                      // ❓ _roomInfo +0x0 to +0x27 (+0x4F to +0x77)
    int _detailRule;                            // +120 (0x78) (PDB: _roomInfo._detailRule, Data::ArenaMatchingRuleDetailType)
};
static_assert(offsetof(PartyBattleManagerView, _isGiveReward) == 0x4E, "PartyBattleManager::_isGiveReward");
static_assert(offsetof(PartyBattleManagerView, _detailRule) == 0x78, "PartyBattleManager::_roomInfo._detailRule");

