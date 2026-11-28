// rankingchannel.cpp: rankingchannel.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "rankingchannel.h"
#include "gamedaemon.h"
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:?onConnect@RankingChannel@@MEAA_NPEBVSession@@_N@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?HandleRankingGame_HelloFail@@YA_NPEBVSession@@PEBVPacket@@@Z")  // LIFT: dead-strip keep (no live caller yet)

// LIFT: per-exe path literal (lessons A6).
#define RANKINGCHANNEL_FILE L"e:\\dailybuild02\\gamedaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\gamedaemon\\RankingChannel.cpp"

// 0x1aef40
__cdecl RankingChannel::~RankingChannel(void)
{
    LIFT_STUB(0x1aef40);
}

// 0x1aef50
void __cdecl RankingChannel::Initialize(void)
{
    LIFT_STUB(0x1aef50);
}

// 0x1aefb0
bool __cdecl RankingChannel::InitSession(void)
{
    LIFT_STUB(0x1aefb0);
}

// 0x1af0f0
bool __cdecl RankingChannel::PacketHandler(::Session const *, ::Packet const *) const
{
    LIFT_STUB(0x1af0f0);
}

// 0x1af180
bool __cdecl RankingChannel::onConnect(::Session const *session, bool firstConnected)
{
    if (firstConnected)
        Log::Write(Log::LT_DEBUG, RANKINGCHANNEL_FILE, 174, L"[ranking-channel], connected, session-id:0x%I64x", session->_id);
    else
        Log::Write(Log::LT_DEBUG, RANKINGCHANNEL_FILE, 178, L"[ranking-channel], reconnected, session-id:0x%I64x", session->_id);
    _pingSent = 0;
    _pingReceived = 0;
    // LIFT: hello packet. Command 1 and value 10 are literals in the original (no PDB enum names found).
    session->Send("hhh", 1, 10, _clusterId);
    return true;
}

// 0x1af210
void __cdecl RankingChannel::onClose(::Session const *, bool, bool)
{
    LIFT_STUB(0x1af210);
}

// 0x1af300
bool __cdecl RankingChannel::SendRetrievePlayerRankingInfo(unsigned __int64, char, unsigned __int64, char, int)
{
    LIFT_STUB(0x1af300);
}

// 0x1af370
bool __cdecl RankingChannel::InsertPlayerRankingScore(__int64, __int64, short, char, int, char, __int64, char, int, wchar_t *, __int64, char, __int64, wchar_t const *, wchar_t const *)
{
    LIFT_STUB(0x1af370);
}

// 0x1af4b0
bool __cdecl RankingChannel::InsertRankingScore(__int64, __int64, short, char, __int64, __int64, __int64, char, int, wchar_t *, char, __int64, wchar_t const *, wchar_t const *)
{
    LIFT_STUB(0x1af4b0);
}

// 0x1af5c0
void __cdecl RankingChannel::SendLoadGuildRankingResultList(void)
{
    LIFT_STUB(0x1af5c0);
}

// 0x1af660
bool __cdecl RankingChannel::SendLoadPlayerSeasonResultByPlayerTypeList(short, __int64)
{
    LIFT_STUB(0x1af660);
}

// 0x1af710
bool __cdecl HandleRankingGame_HelloOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x1af710);
}

// 0x1af940
bool __cdecl HandleRankingGame_HelloFail(::Session const *session, ::Packet const *packet)
{
    short cmd = 0;
    short reason = 0;
    packet->Decompose("hh", &cmd, &reason);
    Log::Write(Log::LT_ERROR, RANKINGCHANNEL_FILE, 432, L"[ranking-channel], hello failed, session-id:0x%I64x, reason:%d",
               session->_id, static_cast<int>(reason));
    // LIFT: LTCG inlines GameDaemon::SetEventReplyCacheHello (0x180e10) here; the original ignores the result.
    GameDaemon::SetEventReplyCacheHello();
    return true;
}

// 0x1af9d0
bool __cdecl HandleRankingGame_PingOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x1af9d0);
}

// 0x1afa80
bool __cdecl HandleRankingGame_RetrievePlayerRankingInfoOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x1afa80);
}

// 0x1b0020
bool __cdecl HandleRankingGame_RetrievePlayerRankingInfoFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x1b0020);
}

// 0x1b0240
bool __cdecl HandleRankingGame_RetrievePcRankingResultListOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x1b0240);
}

// 0x1b09e0
bool __cdecl HandleRankingGame_RetrievePcRankingResultListFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x1b09e0);
}

// 0x1b0ba0
bool __cdecl HandleRankingGame_LoadGuildRankingResultListOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x1b0ba0);
}

// 0x1b0d20
bool __cdecl HandleRankingGame_LoadGuildRankingResultListFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x1b0d20);
}

// 0x1b0e30
bool __cdecl HandleRankingGame_LoadPlayerSeasonResultByPlayerTypeListOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x1b0e30);
}

// 0x1b1240
bool __cdecl HandleRankingGame_LoadPlayerSeasonResultByPlayerTypeListFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x1b1240);
}

// 0x1b1350
bool __cdecl HandleRankingGame_InsertPlayerRatingScoreOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x1b1350);
}

// 0x1b1850
bool __cdecl HandleRankingGame_InsertPlayerRatingScoreFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x1b1850);
}

// 0x1b1c50
bool __cdecl HandleRankingGame_InsertRankingScoreOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x1b1c50);
}

// 0x1b1f30
bool __cdecl HandleRankingGame_InsertRankingScoreFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x1b1f30);
}
