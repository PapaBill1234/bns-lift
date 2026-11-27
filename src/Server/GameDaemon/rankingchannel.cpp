// rankingchannel.cpp: rankingchannel.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "rankingchannel.h"
#include "LiftStub.h"

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
bool __cdecl RankingChannel::onConnect(::Session const *, bool)
{
    LIFT_STUB(0x1af180);
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
bool __cdecl HandleRankingGame_HelloFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x1af940);
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
