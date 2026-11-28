// achievementchannel_cpp.cpp: achievementchannel.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "achievementchannel.h"
#include "LiftStub.h"

// LIFT: per-exe path literal (lessons A6).
#define ACHIEVEMENTCHANNEL_FILE L"e:\\dailybuild02\\gamedaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\gamedaemon\\AchievementChannel.cpp"

// 0x32da0
__cdecl AchievementDaemonChannel::~AchievementDaemonChannel(void)
{
    LIFT_STUB(0x32da0);
}

// 0x32db0
bool __cdecl AchievementDaemonChannel::InitSession(void)
{
    LIFT_STUB(0x32db0);
}

// 0x32f00
bool __cdecl AchievementDaemonChannel::PacketHandler(::Session const *, ::Packet const *) const
{
    LIFT_STUB(0x32f00);
}

// 0x32f90
#pragma comment(linker, "/INCLUDE:?onConnect@AchievementDaemonChannel@@MEAA_NPEBVSession@@_N@Z")  // LIFT: dead-strip keep (no live caller yet)
bool __cdecl AchievementDaemonChannel::onConnect(::Session const *session, bool firstConnected)
{
    if (firstConnected)
        Log::Write(Log::LT_DEBUG, ACHIEVEMENTCHANNEL_FILE, 110, L"[achievement-channel], connected, session-id:0x%I64x", session->_id);
    else
        Log::Write(Log::LT_DEBUG, ACHIEVEMENTCHANNEL_FILE, 114, L"[achievement-channel], reconnected, session-id:0x%I64x", session->_id);
    _pingSent = 0;
    _pingReceived = 0;
    // LIFT: hello packet. Command 1, values 10 and 33 are literals in the original (no PDB enum names found).
    session->Send("hiih", 1, 10, 33, _clusterId);
    return true;
}

// 0x33020
void __cdecl AchievementDaemonChannel::onClose(::Session const *, bool, bool)
{
    LIFT_STUB(0x33020);
}

// 0x33110
bool __cdecl AchievementDaemonChannel::IsConnected(void)
{
    LIFT_STUB(0x33110);
}

// 0x33190
void __cdecl AchievementDaemonChannel::SendLoginAllPc(void)
{
    LIFT_STUB(0x33190);
}

// 0x33340
bool __cdecl AchievementDaemonChannel::SendPing(void)
{
    LIFT_STUB(0x33340);
}

// 0x33400
void __cdecl AchievementDaemonChannel::CheckPing(void)
{
    LIFT_STUB(0x33400);
}

// 0x334c0
bool __cdecl HandleAchievementGameGameHelloOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x334c0);
}

// 0x33520
#pragma comment(linker, "/INCLUDE:?HandleAchievementGameGameHelloFail@@YA_NPEBVSession@@PEBVPacket@@@Z")  // LIFT: dead-strip keep (no live caller yet)
bool __cdecl HandleAchievementGameGameHelloFail(::Session const *session, ::Packet const *packet)
{
    short cmd = 0;
    short reason = 0;
    packet->Decompose("hh", &cmd, &reason);
    Log::Write(Log::LT_ERROR, ACHIEVEMENTCHANNEL_FILE, 258, L"[achievement-channel], hello failed, session-id:0x%I64x, reason:%d",
               session->_id, static_cast<int>(reason));
    return true;
}

// 0x33590
bool __cdecl HandleAchievementGameGameUpdateDataNotify(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x33590);
}

// 0x33ae0
bool __cdecl HandleAchievementGameGameCompleteTakeRewardOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x33ae0);
}

// 0x33d90
bool __cdecl HandleAchievementGameGameCompleteTakeRewardFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x33d90);
}

// 0x34030
bool __cdecl HandleAchievementGameGamePingOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x34030);
}

// 0x340e0
bool __cdecl HandleAchievementGameGameLogAchievementStepCompleteNotify(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x340e0);
}

// 0x34440
bool __cdecl HandleAchievementGameGameLogAchievementRegisterResetNotify(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x34440);
}

// 0xa7870
void __cdecl AchievementDaemonChannel::Destroy(void)
{
    LIFT_STUB(0xa7870);
}
