// duelbotdaemonchannel.cpp: duelbotdaemonchannel.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "duelbotdaemonchannel.h"
#include "duelbot.h"
#include "LiftStub.h"

// 0xa76a0
__cdecl DuelBotDaemonChannel::~DuelBotDaemonChannel(void)
{
    LIFT_STUB(0xa76a0);
}

// 0xa76b0
void __cdecl DuelBotDaemonChannel::Initialize(void)
{
    LIFT_STUB(0xa76b0);
}

// 0xa7730
bool __cdecl DuelBotDaemonChannel::InitSession(void)
{
    LIFT_STUB(0xa7730);
}

// 0xa7900
bool __cdecl DuelBotDaemonChannel::PacketHandler(::Session const *, ::Packet const *) const
{
    LIFT_STUB(0xa7900);
}

// 0xa7990
bool __cdecl DuelBotDaemonChannel::onConnect(::Session const *, bool)
{
    LIFT_STUB(0xa7990);
}

// 0xa7a40
void __cdecl DuelBotDaemonChannel::onClose(::Session const *, bool, bool)
{
    LIFT_STUB(0xa7a40);
}

// 0xa7b50
bool __cdecl DuelBotDaemonChannel::SendPing(void)
{
    LIFT_STUB(0xa7b50);
}

// 0xa7c10
void __cdecl DuelBotDaemonChannel::CheckPing(void)
{
    LIFT_STUB(0xa7c10);
}

// 0xa7cd0
bool __cdecl DuelBotDaemonChannel::IsConnected(void)
{
    LIFT_STUB(0xa7cd0);
}

// 0xa7d50
bool __cdecl DuelBotDaemonChannel::SendCreateDuelBotBrain(__int64, int)
{
    LIFT_STUB(0xa7d50);
}

// 0xa7e00
bool __cdecl DuelBotDaemonChannel::SendUseSkillFail(::DuelBotCreature *, short, __int64, unsigned int, char)
{
    LIFT_STUB(0xa7e00);
}

// 0xa7ee0
bool __cdecl HandleDuelBotGameGameHelloOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xa7ee0);
}

// 0xa7f70
bool __cdecl HandleDuelBotGameGameHelloFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xa7f70);
}

// 0xa7fe0
bool __cdecl HandleDuelBotGameGamePingOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xa7fe0);
}

// 0xa8090
bool __cdecl HandleDuelBotGameGameCreateDuelBotBrainOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xa8090);
}

// 0xa8340
bool __cdecl HandleDuelBotGameGameCreateDuelBotBrainFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xa8340);
}

// 0xa8630
bool __cdecl HandleDuelBotGameGameUseSkillReq(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xa8630);
}

// 0xa9020
bool __cdecl HandleDuelBotGameGameUseSkillToGroundReq(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xa9020);
}

// 0xa9a20
bool __cdecl HandleDuelBotGameGameMoveReq(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xa9a20);
}

// 0xa9e70
bool __cdecl HandleDuelBotGameGameCancelSkillActionReq(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xa9e70);
}

// 0xaa1d0
bool __cdecl HandleDuelBotGameGameCreatureInfoForMonitoringNotify(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xaa1d0);
}
