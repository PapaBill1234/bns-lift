// user.h: user.cpp, user.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class CloseWaitManager
{
public:
    bool __cdecl Add(::Session const *);  // 0x3ebca0
    void __cdecl Expire(void);  // 0x3ebdf0
};

class GameGuardAuth
{
public:
    __cdecl ~GameGuardAuth(void);  // 0x3e3c30
    void __cdecl Init(unsigned __int64);  // 0x3e3d00
    bool __cdecl AvailableCheck(void);  // 0x3e3e90
    unsigned int __cdecl CheckValueFromClient(unsigned char const *, unsigned int);  // 0x3e40e0
};

class TimeBasedPlayInfoList
{
public:
    __cdecl TimeBasedPlayInfoList(void);  // 0x3e1fc0
    __cdecl ~TimeBasedPlayInfoList(void);  // 0x3e2040
    bool __cdecl RenewDailyPlayInfo(__int64, __int64);  // 0x3e2080
    void __cdecl SetLastCheckTimeUTC(__int64);  // 0x3e2260
    __int64 const __cdecl GetValidCheckTimeUTC(char);  // 0x3e22b0
    void __cdecl SetData(::TimeBasedPlayInfoList const &);  // 0x3e2370
    void __cdecl SetRewardInfo(::TimeBasedPlayInfoList const &);  // 0x3e2400
    bool __cdecl SetDurationForDebug(char, int);  // 0x3e24a0
    bool __cdecl CheckSchedule(__int64, bool &);  // 0x3e2530
private:
    bool __cdecl firstSyncSchedule(__int64);  // 0x3e2770
public:
    bool __cdecl CheckRemainRewards(__int64);  // 0x3e29c0
    short __cdecl CheckRewards(char, __int64, int &, int &);  // 0x3e2aa0
    bool __cdecl GetPlayTimeDurationSec(__int64, bool, int &, int &, int &, int &);  // 0x3e2c30
    int __cdecl GetPlayTimeDurationSec(char, __int64, bool);  // 0x3e2de0
    bool __cdecl ComposeToClient(::FragmentPacket &);  // 0x3e2f10
    bool __cdecl ComposeToClient(::RepeatPacketComposer &, ::Packet &);  // 0x3e3170
    bool __cdecl Decompose(::FragmentPacketConcatenater *);  // 0x3e3380
    bool __cdecl Compose(::RepeatPacketComposer &, ::Packet &, bool, __int64);  // 0x3e3520
    bool __cdecl Decompose(::RepeatPacketDecomposer &, ::Packet const *);  // 0x3e3740
    void __cdecl Dump(__int64, wchar_t *, int);  // 0x3e38e0
};

class User
{
public:
    struct BotScoreInfo;
    enum ChargeApplyType {};
public:
    virtual unsigned __int64 __cdecl GetId(void);  // 0x3502e0
    __cdecl User(void);  // 0x3e41a0
    virtual __cdecl ~User(void);  // 0x3e4530
    virtual void __cdecl SetSession(::Session const *);  // 0x3e4610
    void __cdecl SetPcCafeDebugCode(wchar_t *, char);  // 0x3e4650
    bool __cdecl Initialize(short, unsigned __int64, ::id128 const &, wchar_t const *, wchar_t const *, unsigned __int64, int, int, int, int, int, ::User::ChargeApplyType, wchar_t const *const, int, char, wchar_t const *, __int64, int, int, __int64, int, int, int, __int64, __int64, ::LobbyCharacterSlot *, short, ::ContentsBan const *, int, int);  // 0x3e46d0
    bool __cdecl SetCharacterInfo(unsigned __int64, __int64, ::id128 const &, wchar_t const *, wchar_t const *, int, int, int, int, bool, int, int, ::User::ChargeApplyType, wchar_t const *, ::LobbyCharacterSlot *, short, ::ContentsBan const *, __int64);  // 0x3e4d60
    bool __cdecl SetChargeInfo(wchar_t const *const, int, char);  // 0x3e5330
    void __cdecl SetPc(::Pc *);  // 0x3e54e0
    void __cdecl ResetPc(bool);  // 0x3e55c0
private:
    static void __cdecl resetPc(::RefCntObject *, ::RefCntObject *, ::RefCntObject *);  // 0x3e56f0
    void __cdecl resetPc(void);  // 0x3e5700
    void __cdecl logCutOffAccessDelayEnterZoneTask(wchar_t const *);  // 0x3e5770
public:
    ::Pointer2< ::Pc> __cdecl GetPcPtr(void);  // 0x3e5d40
    void __cdecl SetContentsBanDebugCode(int, __int64, __int64);  // 0x3e5da0
private:
    void __cdecl setExistContentsBan(void);  // 0x3e5e60
public:
    bool __cdecl IsBannedContents(char) const;  // 0x3e5eb0
    bool __cdecl IsExistBannedContentsForReward(void) const;  // 0x3e5f50
    void __cdecl CheckBotMovePacketReceived(::Pc *);  // 0x3e5fe0
    void __cdecl CheckBotSummonedMovePacketReceived(::Pc *);  // 0x3e60c0
    void __cdecl CheckBotEnterZone(wchar_t const *, int);  // 0x3e6190
    void __cdecl checkBotPartyRecvCount(void);  // 0x3e6320
    void __cdecl SetExternalInfo(short, char const *, short, char const *, short, char const *, short, char const *);  // 0x3e69c0
    void __cdecl TouchEnterWorld(void);  // 0x3e6cf0
    void __cdecl OnTimeBasedPlayTimeExpired(bool, bool, bool);  // 0x3e6f50
    void __cdecl SendToClientTimeBasedPlayInfoOk(void);  // 0x3e70a0
    bool __cdecl CalcTimeBasedPlay(bool, bool &);  // 0x3e7270
    bool __cdecl AutoTakeTimeBasedReward(__int64, bool, bool, bool);  // 0x3e7420
    void __cdecl UpdateBotScoreLevel(void);  // 0x3e78e0
    void __cdecl DumpBotState(wchar_t *, int);  // 0x3e7b80
    bool __cdecl UpdateAccountExpInfo(::AccountExpInfo const &);  // 0x3e7ea0
    bool __cdecl SendUpdateAccountExpToLobby(::AccountExpInfo const &);  // 0x3e8030
    bool __cdecl SendUpdateAccountContentQuotaToLobby(::AccountContentQuota const &);  // 0x3e8170
    bool __cdecl SendUpdateAccountRecycleTimeToLobby(::AccountRecycleTime const &);  // 0x3e8280
    void __cdecl AddBotState(::Data::BotScoringConditionConditionTypeType, __int64, wchar_t const *, int);  // 0x3e8390
    void __cdecl ClearBotState(wchar_t const *, int);  // 0x3e8440
private:
    void __cdecl addBotScore(int);  // 0x3e84d0
public:
    void __cdecl UpdateCombatForBotScore(bool, bool);  // 0x3e8520
    void __cdecl StartCombatForBotScore(__int64, bool);  // 0x3e8620
    void __cdecl FinishCombatForBotScore(__int64, bool, bool);  // 0x3e86f0
    void __cdecl InitBotScore(bool, int);  // 0x3e87b0
    bool __cdecl UpdateDeductionScore(bool, __int64);  // 0x3e8900
    void __cdecl UpdateBotScore(bool);  // 0x3e8bc0
    unsigned __int64 __cdecl GetGameGuardAuthCount(void);  // 0x3e9340
};

class UserManager
{
public:
    __cdecl UserManager(void);  // 0x3e9390
    __cdecl ~UserManager(void);  // 0x3e9440
private:
    bool __cdecl add(::User *);  // 0x3e9530
public:
    ::Pointer2< ::User> __cdecl GetUserPtr(unsigned __int64);  // 0x3e9790
    ::User * __cdecl RemoveWaitingUser(unsigned __int64);  // 0x3e9870
    ::Pointer2< ::User> __cdecl GetWaitingUserPtr(unsigned __int64);  // 0x3e9930
    ::User * __cdecl CreateArenaReservedUser(short, __int64, unsigned __int64, ::Pc *, ::id128 const &, wchar_t const *, wchar_t const *, unsigned __int64, int, int, int, int, int, ::User::ChargeApplyType, wchar_t const *const, int, char, wchar_t const *, __int64, int, int, __int64, int, int, int, __int64, __int64, ::LobbyCharacterSlot *, short, ::ContentsBan const *, unsigned __int64 *, int, int);  // 0x3e9a20
    ::User * __cdecl ConfirmArenaReservedUser(unsigned __int64, short, __int64);  // 0x3ea130
    void __cdecl RemoveTimeoutReservedUser(__int64, __int64);  // 0x3ea2c0
    void __cdecl Kick(unsigned __int64, short);  // 0x3ea430
    bool __cdecl CreateWaitingUser(short, unsigned __int64, ::Session *);  // 0x3ea7e0
    ::User * __cdecl ConfirmUser(bool &, ::Pc *, unsigned __int64);  // 0x3ea960
    ::User * __cdecl RemoveUser(unsigned __int64, unsigned __int64, __int64);  // 0x3eac50
    bool __cdecl LogoutUser(::User *, bool);  // 0x3eae90
    ::Pointer2< ::User> __cdecl LogoutArenaUser(unsigned __int64);  // 0x3eb0e0
    void __cdecl LogoutArenaUsers(short);  // 0x3eb360
private:
    void __cdecl removeReservedUser(::User *, wchar_t const *);  // 0x3ebb80
};

struct User::BotScoreInfo
{
public:
    __cdecl BotScoreInfo(void);  // 0x3e7850
};

