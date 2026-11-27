// achievementchannel_cpp.cpp: achievementchannel.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "achievementchannel.h"
#include "LiftStub.h"

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
bool __cdecl AchievementDaemonChannel::onConnect(::Session const *, bool)
{
    LIFT_STUB(0x32f90);
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
bool __cdecl HandleAchievementGameGameHelloFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x33520);
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
