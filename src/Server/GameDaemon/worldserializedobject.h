// worldserializedobject.h: worldserializedobject.cpp, worldserializedobject.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class AddTendencyFieldZoneWSO
{
protected:
    virtual void __cdecl TimerExpired(long);  // 0x67f960
};

class ArenaDisconnectedSessionTimer
{
protected:
    virtual void __cdecl TimerExpired(long);  // 0x67aa80
};

class ChangeSeasonContentsScheduleWSO
{
private:
    virtual void __cdecl TimerExpired(long);  // 0x681e70
};

class ChattingChannelOperationWSO
{
protected:
    virtual void __cdecl TimerExpired(long);  // 0x676890
};

class ChattingServerAuthenticateUser
{
public:
    __cdecl ChattingServerAuthenticateUser(void);  // 0x676c10
protected:
    virtual void __cdecl TimerExpired(long);  // 0x676cc0
};

class ChattingServerHeartBeat
{
protected:
    virtual void __cdecl TimerExpired(long);  // 0x676b70
};

class ClientSideDaemonPingWSO
{
private:
    virtual void __cdecl TimerExpired(long);  // 0x67e910
};

class CloseTrialPlayExpireChecker
{
private:
    virtual void __cdecl TimerExpired(long);  // 0x67cd20
};

class DestroyZoneWSO
{
private:
    virtual void __cdecl TimerExpired(long);  // 0x67ce80
};

class EnableGameGuard
{
protected:
    virtual void __cdecl TimerExpired(long);  // 0x676b20
};

class FinishGuildCraftWSO
{
private:
    virtual void __cdecl TimerExpired(long);  // 0x67f270
};

class FinishMakeGuildUniformWSO
{
private:
    virtual void __cdecl TimerExpired(long);  // 0x67f370
};

class GameRestrictLevelNotifyWSO
{
protected:
    virtual void __cdecl TimerExpired(long);  // 0x677040
};

class GuildBattleFieldWSO
{
private:
    virtual void __cdecl TimerExpired(long);  // 0x67eb60
    bool __cdecl closeZone(unsigned __int64, unsigned __int64);  // 0x67eef0
};

class GuildCraftWSO
{
public:
    __cdecl GuildCraftWSO(void);  // 0x67a620
protected:
    virtual void __cdecl TimerExpired(long);  // 0x67a690
    void __cdecl writeError(wchar_t *);  // 0x67a7e0
    void __cdecl sendInvalidGuildIdError(void);  // 0x67a840
};

class GuildExpiredJobCheckWSO
{
private:
    virtual void __cdecl TimerExpired(long);  // 0x67f1f0
};

class GuildJoinWSO
{
public:
    __cdecl GuildJoinWSO(void);  // 0x679fa0
protected:
    virtual void __cdecl TimerExpired(long);  // 0x67a010
    void __cdecl sendInvalidGuildIdError(void);  // 0x67a500
};

class GuildOperationWSO
{
public:
    __cdecl GuildOperationWSO(void);  // 0x678b10
protected:
    virtual void __cdecl TimerExpired(long);  // 0x678c80
    void __cdecl sendInvalidGuildIdError(void);  // 0x679e50
};

class KickByXignCode3WSO
{
private:
    virtual void __cdecl TimerExpired(long);  // 0x67ccd0
};

class MaxPacketCheckWSO
{
private:
    virtual void __cdecl TimerExpired(long);  // 0x67cf30
    void __cdecl sendPacketCheck(::Pc **, int);  // 0x67d030
    void __cdecl recvPacketCheck(::Pc **, int);  // 0x67d6b0
};

class MessageWSO
{
public:
    bool __cdecl Initialize(::Pc *, ::MessageRange, int, wchar_t const *, wchar_t const *);  // 0x6763a0
protected:
    virtual void __cdecl TimerExpired(long);  // 0x676470
public:
    bool __cdecl SendMessageInParty(::Pc *, unsigned __int64, short, wchar_t const *, int, wchar_t const *, wchar_t const *);  // 0x6765a0
    bool __cdecl SendMessageInChannel(::Pc *, int, wchar_t const *, wchar_t const *);  // 0x6767d0
};

class NcGuardStart
{
protected:
    virtual void __cdecl TimerExpired(long);  // 0x67f590
};

class NcGuardStop
{
protected:
    virtual void __cdecl TimerExpired(long);  // 0x67f790
};

class PublisherLibsKickWSO
{
private:
    virtual void __cdecl TimerExpired(long);  // 0x67f180
};

class RemoveTimeoutArenaPendings
{
protected:
    virtual void __cdecl TimerExpired(long);  // 0x67a980
};

class RemoveTimeoutBotTestQuery
{
private:
    virtual void __cdecl TimerExpired(long);  // 0x67cdd0
};

class RetryMileageDepositWSO
{
private:
    virtual void __cdecl TimerExpired(long);  // 0x67f4c0
};

class RetryUncompletedChallengePartyRankingScoreWSO
{
public:
    virtual __cdecl ~RetryUncompletedChallengePartyRankingScoreWSO(void);  // 0x67fea0
protected:
    virtual void __cdecl TimerExpired(long);  // 0x67ff10
};

class RetryUncompletedGuildRankingScoreWSO
{
protected:
    virtual void __cdecl TimerExpired(long);  // 0x67fda0
};

class SendNCGServerMessageWSO
{
private:
    virtual void __cdecl TimerExpired(long);  // 0x67abc0
};

class SendXIGNCode3MessageWSO
{
private:
    virtual void __cdecl TimerExpired(long);  // 0x67ca60
};

class ServerPingWSO
{
private:
    virtual void __cdecl TimerExpired(long);  // 0x67df60
    void __cdecl disconnectPc(::Pc *, wchar_t const *, ::ServerPing, ::ServerPing, short);  // 0x67e290
};

class ServerSideDaemonPingWSO
{
private:
    virtual void __cdecl TimerExpired(long);  // 0x67ea70
};

class SetGameRestrictLevelForHealthySystemWSO
{
public:
    __cdecl SetGameRestrictLevelForHealthySystemWSO(unsigned __int64, unsigned __int64, int, int);  // 0x677680
protected:
    virtual void __cdecl TimerExpired(long);  // 0x677770
};

class SetTendencyPlayValueDebugWSO
{
protected:
    virtual void __cdecl TimerExpired(long);  // 0x67fbc0
};

class SetTendencyScoreDebugWSO
{
protected:
    virtual void __cdecl TimerExpired(long);  // 0x67fb60
};

class TakeRankingRewardWSO
{
protected:
    virtual void __cdecl TimerExpired(long);  // 0x67fc30
};

class TencentHealthySystemJudgeTimingTSO
{
public:
    enum FactType {};
public:
    __cdecl TencentHealthySystemJudgeTimingTSO(::std::basic_string<wchar_t, ::std::char_traits<wchar_t>, ::StlAllocator<wchar_t, 2> > const &, unsigned __int64, unsigned __int64, ::TencentHealthySystemJudgeTimingTSO::FactType);  // 0x67fff0
    virtual __cdecl ~TencentHealthySystemJudgeTimingTSO(void);  // 0x680200
protected:
    virtual void __cdecl TimerExpired(long);  // 0x680340
};

class TencentHealthySystemReportExecuteTSO
{
public:
    __cdecl TencentHealthySystemReportExecuteTSO(unsigned __int64, ::std::basic_string<wchar_t, ::std::char_traits<wchar_t>, ::StlAllocator<wchar_t, 2> > const &, ::std::basic_string<char, ::std::char_traits<char>, ::StlAllocator<char, 2> >, ::std::basic_string<char, ::std::char_traits<char>, ::StlAllocator<char, 2> >);  // 0x6811c0
    virtual __cdecl ~TencentHealthySystemReportExecuteTSO(void);  // 0x6814b0
protected:
    virtual void __cdecl TimerExpired(long);  // 0x6816c0
};

class TendencyCheckWSO
{
protected:
    virtual void __cdecl TimerExpired(long);  // 0x67f990
};

class WarFieldCheckWSO
{
protected:
    virtual void __cdecl TimerExpired(long);  // 0x67fa60
};

class WorldPerfMonitor
{
protected:
    virtual void __cdecl TimerExpired(long);  // 0x677db0
    bool __cdecl initialize(void);  // 0x677e20
    void __cdecl check(void);  // 0x677f80
};

class WorldSerializedObject
{
protected:
    bool __cdecl SetTimer(long);  // 0x8c240
public:
    __cdecl WorldSerializedObject(unsigned short);  // 0x676270
    virtual __cdecl ~WorldSerializedObject(void);  // 0x676310
};

class WriteNCGEventLogWSO
{
private:
    virtual void __cdecl TimerExpired(long);  // 0x67ae30
};

