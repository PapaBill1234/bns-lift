// duelmanager_cpp.cpp: duelmanager.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "duelmanager.h"
#include "controlledcreature.h"
#include "pc.h"
#include "zone.h"
#include "LiftStub.h"

// 0xb1750
bool __cdecl DuelMember::ReadyRound(short &)
{
    LIFT_STUB(0xb1750);
}

// 0xb17c0
void __cdecl DuelMember::ResetRound(void)
{
    LIFT_STUB(0xb17c0);
}

// 0xb17e0
bool __cdecl DuelTeam::IsTeamMember(::Pc const *const) const
{
    LIFT_STUB(0xb17e0);
}

// 0xb1860
bool __cdecl DuelTeam::IsTeamMemberAllDead(void) const
{
    LIFT_STUB(0xb1860);
}

// 0xb1890
::DuelMember *const __cdecl DuelTeam::GetDuelMember(::Pc const *const)
{
    LIFT_STUB(0xb1890);
}

// 0xb1920
bool __cdecl DuelTeam::Join(int, ::Pc *const)
{
    LIFT_STUB(0xb1920);
}

// 0xb1b20
bool __cdecl DuelTeam::Leave(::Pc *const)
{
    LIFT_STUB(0xb1b20);
}

// 0xb1cf0
void __cdecl DuelTeam::ResetRound(void)
{
    LIFT_STUB(0xb1cf0);
}

// 0xb1d00
__cdecl DuelManager::DuelManager(void)
{
    LIFT_STUB(0xb1d00);
}

// 0xb1e00
__cdecl DuelManager::~DuelManager(void)
{
    LIFT_STUB(0xb1e00);
}

// 0xb1ed0
bool __cdecl DuelManager::Initialize(::Zone *const, ::Data::DuelRecordPtr const &)
{
    LIFT_STUB(0xb1ed0);
}

// 0xb2250
void __cdecl DuelManager::FetchMembers(::FragmentPacket &)
{
    LIFT_STUB(0xb2250);
}

// 0xb2430
void __cdecl DuelManager::SetRoomInfo(::ArenaLobbyRoomInfo const &)
{
    LIFT_STUB(0xb2430);
}

// 0xb2590
::DuelMember *const __cdecl DuelManager::GetDuelMember(::Pc const *const)
{
    LIFT_STUB(0xb2590);
}

// 0xb2620
::DuelMember const *const __cdecl DuelManager::GetDuelMember(::Pc const *const) const
{
    LIFT_STUB(0xb2620);
}

// 0xb26b0
::DuelMember *const __cdecl DuelManager::GetDuelMember(unsigned __int64)
{
    LIFT_STUB(0xb26b0);
}

// 0xb2770
bool __cdecl DuelManager::IsDuelMember(::Pc const *const) const
{
    LIFT_STUB(0xb2770);
}

// 0xb2810
bool __cdecl DuelManager::Enter(::Pc *const)
{
    LIFT_STUB(0xb2810);
}

// 0xb3310
bool __cdecl DuelManager::Leave(::Pc *const)
{
    LIFT_STUB(0xb3310);
}

// 0xb3bd0
void __cdecl DuelManager::EnterByRevive(::ControlledCreature *const)
{
    LIFT_STUB(0xb3bd0);
}

// 0xb3f40
bool __cdecl DuelManager::Ready(unsigned __int64, short &)
{
    LIFT_STUB(0xb3f40);
}

// 0xb4230
bool __cdecl DuelManager::ReadyAll(short &)
{
    LIFT_STUB(0xb4230);
}

// 0xb4560
void __cdecl DuelManager::NotifyDuelDeath(unsigned __int64, ::Pc const *const)
{
    LIFT_STUB(0xb4560);
}

// 0xb4660
void __cdecl DuelManager::OnTimer(void)
{
    LIFT_STUB(0xb4660);
}

// 0xb48a0
void __cdecl DuelManager::OnDead(::Pc *const)
{
    LIFT_STUB(0xb48a0);
}

// 0xb4a80
bool __cdecl DuelManager::OnDamaged(::Pc *const, ::ControlledCreature *const, __int64)
{
    LIFT_STUB(0xb4a80);
}

// 0xb4b70
void __cdecl DuelManager::OnSkillChanged(::Pc *const)
{
    LIFT_STUB(0xb4b70);
}

// 0xb4c50
void __cdecl DuelManager::clearDuelMemberState(::Pc *const, bool)
{
    LIFT_STUB(0xb4c50);
}

// 0xb4e40
void __cdecl DuelManager::spawnDuelMember(::Pc *const, ::Data::ZonePcSpawnRecordPtr, bool)
{
    LIFT_STUB(0xb4e40);
}

// 0xb5020
int const __cdecl DuelManager::GetDuelTypeCodeForLog(void) const
{
    LIFT_STUB(0xb5020);
}

// 0xb5080
bool __cdecl DuelManager::verifyRoomInfo(void) const
{
    LIFT_STUB(0xb5080);
}

// 0xb5170
void __cdecl DuelManager::addDuelTimer(long)
{
    LIFT_STUB(0xb5170);
}

// 0xb52d0
bool __cdecl DuelManager::isAllRoundEntrance(void) const
{
    LIFT_STUB(0xb52d0);
}

// 0xb5350
bool __cdecl DuelManager::setTeamRatingScore(void)
{
    LIFT_STUB(0xb5350);
}

// 0xb56d0
void __cdecl DuelManager::startCountdown(void)
{
    LIFT_STUB(0xb56d0);
}

// 0xb57c0
void __cdecl DuelManager::startGame(void)
{
    LIFT_STUB(0xb57c0);
}

// 0xb6ec0
void __cdecl DuelManager::prepareRound(void)
{
    LIFT_STUB(0xb6ec0);
}

// 0xb6fb0
void __cdecl DuelManager::checkRound(void)
{
    LIFT_STUB(0xb6fb0);
}

// 0xb7130
void __cdecl DuelManager::startRound(void)
{
    LIFT_STUB(0xb7130);
}

// 0xb7aa0
void __cdecl DuelManager::finishRound(void)
{
    LIFT_STUB(0xb7aa0);
}

// 0xb7c40
void __cdecl DuelManager::finishGame(void)
{
    LIFT_STUB(0xb7c40);
}

// 0xb7ca0
void __cdecl DuelManager::finishGame(::DuelGameResult)
{
    LIFT_STUB(0xb7ca0);
}

// 0xb8260
void __cdecl DuelManager::standbyNextRound(void)
{
    LIFT_STUB(0xb8260);
}

// 0xb8360
void __cdecl DuelManager::enterToArena(void)
{
    LIFT_STUB(0xb8360);
}

// 0xb8400
void __cdecl DuelManager::leaveFromArena(void)
{
    LIFT_STUB(0xb8400);
}

// 0xb84d0
void __cdecl DuelManager::resetRound(void)
{
    LIFT_STUB(0xb84d0);
}

// 0xb84e0
::Data::ZonePcSpawnRecordPtr const __cdecl DuelManager::getRoundStartPcSpawn(int, int) const
{
    LIFT_STUB(0xb84e0);
}

// 0xb8560
void __cdecl DuelManager::recordGameResult(::Pc *const, int, ::DuelManager::DuelScoreResult)
{
    LIFT_STUB(0xb8560);
}

// 0xb8660
void __cdecl DuelManager::recordGameResult(::DuelGameResult)
{
    LIFT_STUB(0xb8660);
}

// 0xb92a0
void __cdecl DuelManager::calcDuelRating(::Pc *const, ::DuelManager::DuelScoreResult, int, int, int, int)
{
    LIFT_STUB(0xb92a0);
}

// 0xb9a10
int const __cdecl DuelManager::calcRateDiffByELO(::DuelManager::DuelScoreResult, int, int, int, int) const
{
    LIFT_STUB(0xb9a10);
}

// 0xb9c00
int const __cdecl DuelManager::calcRateDiffByELORenewal(::DuelManager::DuelScoreResult, int, int, int, int, int) const
{
    LIFT_STUB(0xb9c00);
}

// 0xb9d70
void __cdecl DuelManager::calcBaseExpPoint(::Pc *const, char, ::DuelManager::DuelScoreResult, ::ResultReward &) const
{
    LIFT_STUB(0xb9d70);
}

// 0xb9f50
void __cdecl DuelManager::calcBonusExpPoint(::Pc *const, ::DuelManager::DuelScoreResult, int, ::ResultReward &, int &) const
{
    LIFT_STUB(0xb9f50);
}

// 0xba6d0
bool const __cdecl DuelManager::isBeginner(::Pc *const, char, int &) const
{
    LIFT_STUB(0xba6d0);
}

// 0xba850
bool __cdecl DuelManager::startDuelResultTran(::Pc *, ::DuelManager::DuelScoreResult, int, ::DuelResultTranResultNotifyInfo const &)
{
    LIFT_STUB(0xba850);
}

// 0xbad50
bool __cdecl DuelRule::IsGameDone(void) const
{
    LIFT_STUB(0xbad50);
}

// 0xbada0
::DuelGameResult const __cdecl DuelRule::CalcGameResult(void) const
{
    LIFT_STUB(0xbada0);
}

// 0xbae10
bool __cdecl DuelRule::CanResurrect(::Pc const *const) const
{
    LIFT_STUB(0xbae10);
}
