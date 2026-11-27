// publicraid_cpp.cpp: publicraid.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "publicraid.h"
#include "creature.h"
#include "pc.h"
#include "summoned.h"
#include "zone.h"
#include "LiftStub.h"

// 0x1a0cf0
void __cdecl EnterPublicRaidAttractionState::SetRoomInfo(::Zone *, ::ArenaLobbyRoomInfo const &, bool)
{
    LIFT_STUB(0x1a0cf0);
}

// 0x1a0d70
bool __cdecl EnterPublicRaidAttractionState::setMaxReservePcCountTouched(::Zone *, bool)
{
    LIFT_STUB(0x1a0d70);
}

// 0x1a0dd0
bool __cdecl EnterPublicRaidAttractionState::IncrementReservePcCount(::Zone *, int)
{
    LIFT_STUB(0x1a0dd0);
}

// 0x1a0ed0
bool __cdecl EnterPublicRaidAttractionState::decrementReservePcCount(::Pc *, ::Zone *, int)
{
    LIFT_STUB(0x1a0ed0);
}

// 0x1a10b0
bool __cdecl EnterPublicRaidAttractionState::checkReservePcCount(::Pc *, ::Zone *, int, int)
{
    LIFT_STUB(0x1a10b0);
}

// 0x1a1120
__cdecl PublicRaid::~PublicRaid(void)
{
    LIFT_STUB(0x1a1120);
}

// 0x1a11a0
bool __cdecl PublicRaid::Init(::Zone *, bool)
{
    LIFT_STUB(0x1a11a0);
}

// 0x1a13e0
void __cdecl PublicRaid::OnEntered(::Zone *, ::Creature *, ::EnterReason)
{
    LIFT_STUB(0x1a13e0);
}

// 0x1a1500
void __cdecl PublicRaid::OnLeaved(::Zone *, ::Creature *, ::LeaveReason)
{
    LIFT_STUB(0x1a1500);
}

// 0x1a1660
void __cdecl PublicRaid::OnBossCombatEnd(::Zone *, ::Creature *)
{
    LIFT_STUB(0x1a1660);
}

// 0x1a16a0
void __cdecl PublicRaid::SetContentQuota(::Pc *)
{
    LIFT_STUB(0x1a16a0);
}

// 0x1a17c0
bool __cdecl PublicRaid::CanJoinState(::Pc *, ::Zone *)
{
    LIFT_STUB(0x1a17c0);
}

// 0x1a1840
bool __cdecl PublicRaid::CanPreserveSessionState(::Pc *)
{
    LIFT_STUB(0x1a1840);
}

// 0x1a1910
void __cdecl PublicRaid::OnZoneAttractionTimer(::Zone *)
{
    LIFT_STUB(0x1a1910);
}

// 0x1a19e0
bool __cdecl PublicRaid::onTimeCheck(::Zone *)
{
    LIFT_STUB(0x1a19e0);
}

// 0x1a1a70
bool __cdecl PublicRaid::onStandBy(::Zone *)
{
    LIFT_STUB(0x1a1a70);
}

// 0x1a1ba0
bool __cdecl PublicRaid::onStart(::Zone *)
{
    LIFT_STUB(0x1a1ba0);
}

// 0x1a1ec0
bool __cdecl PublicRaid::onFinish(::Zone *)
{
    LIFT_STUB(0x1a1ec0);
}

// 0x1a1f60
bool __cdecl PublicRaid::SetPublicRaidEvent(::Zone *, unsigned __int64)
{
    LIFT_STUB(0x1a1f60);
}

// 0x1a2120
bool __cdecl PublicRaid::executePublicRaidEvent(void)
{
    LIFT_STUB(0x1a2120);
}

// 0x1a2220
bool __cdecl PublicRaid::AddScore(::Zone *, ::Pc *)
{
    LIFT_STUB(0x1a2220);
}

// 0x1a2410
void __cdecl PublicRaid::ReduceScore(::Zone *)
{
    LIFT_STUB(0x1a2410);
}

// 0x1a24c0
void __cdecl PublicRaid::stopPublicRaidEvent(bool)
{
    LIFT_STUB(0x1a24c0);
}

// 0x1a2840
bool __cdecl PublicRaid::setEventAttendee(void)
{
    LIFT_STUB(0x1a2840);
}

// 0x1a2ac0
char __cdecl PublicRaid::setEffectTargetInfoAtEventFinish(unsigned __int64 *const, unsigned __int64 *const, unsigned __int64 *const, unsigned __int64 *const)
{
    LIFT_STUB(0x1a2ac0);
}

// 0x1a2e70
void __cdecl PublicRaid::invokeNpcEffectAtEventFinish(unsigned __int64 const *const, int, unsigned __int64 const *const, int)
{
    LIFT_STUB(0x1a2e70);
}

// 0x1a3000
void __cdecl PublicRaid::invokePcEffectAtEventFinish(unsigned __int64 const *const, int, unsigned __int64 const *const, int)
{
    LIFT_STUB(0x1a3000);
}

// 0x1a32e0
void __cdecl PublicRaid::invokeSummonedEffectAtEventFinish(::Summoned *, unsigned __int64 const *const, int)
{
    LIFT_STUB(0x1a32e0);
}

// 0x1a33b0
bool __cdecl PublicRaid::invokeEffect(unsigned __int64, unsigned __int64, unsigned __int64)
{
    LIFT_STUB(0x1a33b0);
}

// 0x1a3460
void __cdecl PublicRaid::broadcastPublicRaidEventStart(unsigned __int64)
{
    LIFT_STUB(0x1a3460);
}

// 0x1a3630
void __cdecl PublicRaid::broadcastPublicRaidEventScore(short)
{
    LIFT_STUB(0x1a3630);
}

// 0x1a3800
void __cdecl PublicRaid::broadcastPublicRaidEventStop(short)
{
    LIFT_STUB(0x1a3800);
}

// 0x1a39f0
void __cdecl PublicRaid::doEnvOperation(void)
{
    LIFT_STUB(0x1a39f0);
}

// 0x1a3b40
bool __cdecl PublicRaid::getEventCylinder(::cylinder16 &)
{
    LIFT_STUB(0x1a3b40);
}

// 0x1a3cc0
void __cdecl PublicRaidGameLog::WritePublicRaidDisconnected(::Pc *, unsigned __int64, char)
{
    LIFT_STUB(0x1a3cc0);
}

// 0x1a3e50
void __cdecl PublicRaidGameLog::WritePublicRaidFinishTeam(::Zone *, unsigned __int64)
{
    LIFT_STUB(0x1a3e50);
}

// 0x1a4030
void __cdecl PublicRaidGameLog::WritePublicRaidStartPc(::Pc *, unsigned __int64)
{
    LIFT_STUB(0x1a4030);
}

// 0x1a41c0
void __cdecl PublicRaidGameLog::WritePublicRaidFinishPc(::Pc *, unsigned __int64)
{
    LIFT_STUB(0x1a41c0);
}
