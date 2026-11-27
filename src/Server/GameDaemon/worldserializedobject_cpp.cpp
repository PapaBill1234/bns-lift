// worldserializedobject_cpp.cpp: worldserializedobject.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "worldserializedobject.h"
#include "pc.h"
#include "Log.h"
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:?writeError@GuildCraftWSO@@IEAAXPEA_W@Z")  // LIFT: dead-strip keep (no live caller yet)

namespace
{
// LIFT: view of GuildCraftWSO. The skeleton class has no members yet. Offsets are from the PDB.
struct GuildCraftWSOView
{
    char lift_pad_0[0x70];
    int _guildCraftOp;                  // +112 (0x70). LIFT: PDB type GuildCraftWSO::GuildCraftOp
    unsigned __int64 _guildId;          // +120 (0x78)
    unsigned __int64 _guildCraftId;     // +128 (0x80)
    unsigned __int64 _requestorId;      // +136 (0x88)
};
}  // namespace

// 0x676270
__cdecl WorldSerializedObject::WorldSerializedObject(unsigned short)
{
    LIFT_STUB(0x676270);
}

// 0x676310
__cdecl WorldSerializedObject::~WorldSerializedObject(void)
{
    LIFT_STUB(0x676310);
}

// 0x6763a0
bool __cdecl MessageWSO::Initialize(::Pc *, ::MessageRange, int, wchar_t const *, wchar_t const *)
{
    LIFT_STUB(0x6763a0);
}

// 0x676470
void __cdecl MessageWSO::TimerExpired(long)
{
    LIFT_STUB(0x676470);
}

// 0x6765a0
bool __cdecl MessageWSO::SendMessageInParty(::Pc *, unsigned __int64, short, wchar_t const *, int, wchar_t const *, wchar_t const *)
{
    LIFT_STUB(0x6765a0);
}

// 0x6767d0
bool __cdecl MessageWSO::SendMessageInChannel(::Pc *, int, wchar_t const *, wchar_t const *)
{
    LIFT_STUB(0x6767d0);
}

// 0x676890
void __cdecl ChattingChannelOperationWSO::TimerExpired(long)
{
    LIFT_STUB(0x676890);
}

// 0x676b20
// LIFT: feature off (owner scope)
void __cdecl EnableGameGuard::TimerExpired(long)
{
}

// 0x676b70
void __cdecl ChattingServerHeartBeat::TimerExpired(long)
{
    LIFT_STUB(0x676b70);
}

// 0x676c10
__cdecl ChattingServerAuthenticateUser::ChattingServerAuthenticateUser(void)
{
    LIFT_STUB(0x676c10);
}

// 0x676cc0
void __cdecl ChattingServerAuthenticateUser::TimerExpired(long)
{
    LIFT_STUB(0x676cc0);
}

// 0x677040
void __cdecl GameRestrictLevelNotifyWSO::TimerExpired(long)
{
    LIFT_STUB(0x677040);
}

// 0x677680
__cdecl SetGameRestrictLevelForHealthySystemWSO::SetGameRestrictLevelForHealthySystemWSO(unsigned __int64, unsigned __int64, int, int)
{
    LIFT_STUB(0x677680);
}

// 0x677770
void __cdecl SetGameRestrictLevelForHealthySystemWSO::TimerExpired(long)
{
    LIFT_STUB(0x677770);
}

// 0x677db0
void __cdecl WorldPerfMonitor::TimerExpired(long)
{
    LIFT_STUB(0x677db0);
}

// 0x677e20
bool __cdecl WorldPerfMonitor::initialize(void)
{
    LIFT_STUB(0x677e20);
}

// 0x677f80
void __cdecl WorldPerfMonitor::check(void)
{
    LIFT_STUB(0x677f80);
}

// 0x678b10
__cdecl GuildOperationWSO::GuildOperationWSO(void)
{
    LIFT_STUB(0x678b10);
}

// 0x678c80
void __cdecl GuildOperationWSO::TimerExpired(long)
{
    LIFT_STUB(0x678c80);
}

// 0x679e50
void __cdecl GuildOperationWSO::sendInvalidGuildIdError(void)
{
    LIFT_STUB(0x679e50);
}

// 0x679fa0
__cdecl GuildJoinWSO::GuildJoinWSO(void)
{
    LIFT_STUB(0x679fa0);
}

// 0x67a010
void __cdecl GuildJoinWSO::TimerExpired(long)
{
    LIFT_STUB(0x67a010);
}

// 0x67a500
void __cdecl GuildJoinWSO::sendInvalidGuildIdError(void)
{
    LIFT_STUB(0x67a500);
}

// 0x67a620
__cdecl GuildCraftWSO::GuildCraftWSO(void)
{
    LIFT_STUB(0x67a620);
}

// 0x67a690
void __cdecl GuildCraftWSO::TimerExpired(long)
{
    LIFT_STUB(0x67a690);
}

// 0x67a7e0
void __cdecl GuildCraftWSO::writeError(wchar_t *desc)
{
    GuildCraftWSOView const *self = reinterpret_cast<GuildCraftWSOView const *>(this);
    Log::Write(Log::LT_ERROR,
               L"e:\\dailybuild02\\gamedaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\gamedaemon\\WorldSerializedObject.cpp",
               2309, L"[guild craft wso], %s, guildId:0x%I64X, op:%d, guildCraftId:0x%I64X, requestorId:0x%I64X", desc,
               self->_guildId, self->_guildCraftOp, self->_guildCraftId, self->_requestorId);
}

// 0x67a840
void __cdecl GuildCraftWSO::sendInvalidGuildIdError(void)
{
    LIFT_STUB(0x67a840);
}

// 0x67a980
void __cdecl RemoveTimeoutArenaPendings::TimerExpired(long)
{
    LIFT_STUB(0x67a980);
}

// 0x67aa80
void __cdecl ArenaDisconnectedSessionTimer::TimerExpired(long)
{
    LIFT_STUB(0x67aa80);
}

// 0x67abc0
void __cdecl SendNCGServerMessageWSO::TimerExpired(long)
{
    LIFT_STUB(0x67abc0);
}

// 0x67ae30
void __cdecl WriteNCGEventLogWSO::TimerExpired(long)
{
    LIFT_STUB(0x67ae30);
}

// 0x67ca60
// LIFT: feature off (owner scope)
void __cdecl SendXIGNCode3MessageWSO::TimerExpired(long)
{
}

// 0x67ccd0
// LIFT: feature off (owner scope)
void __cdecl KickByXignCode3WSO::TimerExpired(long)
{
}

// 0x67cd20
void __cdecl CloseTrialPlayExpireChecker::TimerExpired(long)
{
    LIFT_STUB(0x67cd20);
}

// 0x67cdd0
void __cdecl RemoveTimeoutBotTestQuery::TimerExpired(long)
{
    LIFT_STUB(0x67cdd0);
}

// 0x67ce80
void __cdecl DestroyZoneWSO::TimerExpired(long)
{
    LIFT_STUB(0x67ce80);
}

// 0x67cf30
void __cdecl MaxPacketCheckWSO::TimerExpired(long)
{
    LIFT_STUB(0x67cf30);
}

// 0x67d030
void __cdecl MaxPacketCheckWSO::sendPacketCheck(::Pc **, int)
{
    LIFT_STUB(0x67d030);
}

// 0x67d6b0
void __cdecl MaxPacketCheckWSO::recvPacketCheck(::Pc **, int)
{
    LIFT_STUB(0x67d6b0);
}

// 0x67df60
void __cdecl ServerPingWSO::TimerExpired(long)
{
    LIFT_STUB(0x67df60);
}

// 0x67e290
void __cdecl ServerPingWSO::disconnectPc(::Pc *, wchar_t const *, ::ServerPing, ::ServerPing, short)
{
    LIFT_STUB(0x67e290);
}

// 0x67e910
void __cdecl ClientSideDaemonPingWSO::TimerExpired(long)
{
    LIFT_STUB(0x67e910);
}

// 0x67ea70
void __cdecl ServerSideDaemonPingWSO::TimerExpired(long)
{
    LIFT_STUB(0x67ea70);
}

// 0x67eb60
void __cdecl GuildBattleFieldWSO::TimerExpired(long)
{
    LIFT_STUB(0x67eb60);
}

// 0x67eef0
bool __cdecl GuildBattleFieldWSO::closeZone(unsigned __int64, unsigned __int64)
{
    LIFT_STUB(0x67eef0);
}

// 0x67f180
void __cdecl PublisherLibsKickWSO::TimerExpired(long)
{
    LIFT_STUB(0x67f180);
}

// 0x67f1f0
void __cdecl GuildExpiredJobCheckWSO::TimerExpired(long)
{
    LIFT_STUB(0x67f1f0);
}

// 0x67f270
void __cdecl FinishGuildCraftWSO::TimerExpired(long)
{
    LIFT_STUB(0x67f270);
}

// 0x67f370
void __cdecl FinishMakeGuildUniformWSO::TimerExpired(long)
{
    LIFT_STUB(0x67f370);
}

// 0x67f4c0
void __cdecl RetryMileageDepositWSO::TimerExpired(long)
{
    LIFT_STUB(0x67f4c0);
}

// 0x67f590
// LIFT: feature off (owner scope)
void __cdecl NcGuardStart::TimerExpired(long)
{
}

// 0x67f790
// LIFT: feature off (owner scope)
void __cdecl NcGuardStop::TimerExpired(long)
{
}

// 0x67f960
void __cdecl AddTendencyFieldZoneWSO::TimerExpired(long)
{
    LIFT_STUB(0x67f960);
}

// 0x67f990
void __cdecl TendencyCheckWSO::TimerExpired(long)
{
    LIFT_STUB(0x67f990);
}

// 0x67fa60
void __cdecl WarFieldCheckWSO::TimerExpired(long)
{
    LIFT_STUB(0x67fa60);
}

// 0x67fb60
void __cdecl SetTendencyScoreDebugWSO::TimerExpired(long)
{
    LIFT_STUB(0x67fb60);
}

// 0x67fbc0
void __cdecl SetTendencyPlayValueDebugWSO::TimerExpired(long)
{
    LIFT_STUB(0x67fbc0);
}

// 0x67fc30
void __cdecl TakeRankingRewardWSO::TimerExpired(long)
{
    LIFT_STUB(0x67fc30);
}

// 0x67fda0
void __cdecl RetryUncompletedGuildRankingScoreWSO::TimerExpired(long)
{
    LIFT_STUB(0x67fda0);
}

// 0x67fea0
__cdecl RetryUncompletedChallengePartyRankingScoreWSO::~RetryUncompletedChallengePartyRankingScoreWSO(void)
{
    LIFT_STUB(0x67fea0);
}

// 0x67ff10
void __cdecl RetryUncompletedChallengePartyRankingScoreWSO::TimerExpired(long)
{
    LIFT_STUB(0x67ff10);
}

// 0x67fff0
__cdecl TencentHealthySystemJudgeTimingTSO::TencentHealthySystemJudgeTimingTSO(::std::basic_string<wchar_t, ::std::char_traits<wchar_t>, ::StlAllocator<wchar_t, 2> > const &, unsigned __int64, unsigned __int64, ::TencentHealthySystemJudgeTimingTSO::FactType)
{
    LIFT_STUB(0x67fff0);
}

// 0x680200
__cdecl TencentHealthySystemJudgeTimingTSO::~TencentHealthySystemJudgeTimingTSO(void)
{
    LIFT_STUB(0x680200);
}

// 0x680340
void __cdecl TencentHealthySystemJudgeTimingTSO::TimerExpired(long)
{
    LIFT_STUB(0x680340);
}

// 0x6811c0
__cdecl TencentHealthySystemReportExecuteTSO::TencentHealthySystemReportExecuteTSO(unsigned __int64, ::std::basic_string<wchar_t, ::std::char_traits<wchar_t>, ::StlAllocator<wchar_t, 2> > const &, ::std::basic_string<char, ::std::char_traits<char>, ::StlAllocator<char, 2> >, ::std::basic_string<char, ::std::char_traits<char>, ::StlAllocator<char, 2> >)
{
    LIFT_STUB(0x6811c0);
}

// 0x6814b0
__cdecl TencentHealthySystemReportExecuteTSO::~TencentHealthySystemReportExecuteTSO(void)
{
    LIFT_STUB(0x6814b0);
}

// 0x6816c0
void __cdecl TencentHealthySystemReportExecuteTSO::TimerExpired(long)
{
    LIFT_STUB(0x6816c0);
}

// 0x681e70
void __cdecl ChangeSeasonContentsScheduleWSO::TimerExpired(long)
{
    LIFT_STUB(0x681e70);
}
