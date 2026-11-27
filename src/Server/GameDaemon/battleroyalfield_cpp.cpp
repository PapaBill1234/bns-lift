// battleroyalfield_cpp.cpp: battleroyalfield.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "battleroyalfield.h"
#include "controlledcreature.h"
#include "creature.h"
#include "gameobject.h"
#include "pc.h"
#include "zone.h"
#include "LiftStub.h"

// 0x51440
__cdecl BattleRoyalField::BattleRoyalField(void)
{
    LIFT_STUB(0x51440);
}

// 0x515d0
__cdecl BattleRoyalField::~BattleRoyalField(void)
{
    LIFT_STUB(0x515d0);
}

// 0x51650
__cdecl BattleRoyalFieldPlayerManager::BattleRoyalFieldPlayerManager(void)
{
    LIFT_STUB(0x51650);
}

// 0x51700
bool __cdecl BattleRoyalField::CanJoinState(::Pc *, ::Zone *)
{
    LIFT_STUB(0x51700);
}

// 0x517c0
int __cdecl BattleRoyalField::GetMaxPcCount(void)
{
    LIFT_STUB(0x517c0);
}

// 0x51890
bool __cdecl BattleRoyalField::Init(::Zone *, bool)
{
    LIFT_STUB(0x51890);
}

// 0x51e70
void __cdecl BattleRoyalField::OnEntered(::Zone *, ::Creature *, ::EnterReason)
{
    LIFT_STUB(0x51e70);
}

// 0x52480
bool __cdecl BattleRoyalField::isWinnerPc(::Zone *, ::Pc *)
{
    LIFT_STUB(0x52480);
}

// 0x52600
void __cdecl BattleRoyalField::OnLeaved(::Zone *, ::Creature *, ::LeaveReason)
{
    LIFT_STUB(0x52600);
}

// 0x52e50
void __cdecl BattleRoyalField::OnKill(::Zone *, ::GameObject *, ::Creature *)
{
    LIFT_STUB(0x52e50);
}

// 0x53060
void __cdecl BattleRoyalField::SetBattleRoyalFieldStateForDebug(::Zone *, char)
{
    LIFT_STUB(0x53060);
}

// 0x531a0
void __cdecl BattleRoyalField::OnZoneAttractionTimer(::Zone *)
{
    LIFT_STUB(0x531a0);
}

// 0x53240
bool __cdecl BattleRoyalField::checkStandBy(::Zone *)
{
    LIFT_STUB(0x53240);
}

// 0x53410
bool __cdecl BattleRoyalField::standBy(::Zone *)
{
    LIFT_STUB(0x53410);
}

// 0x53630
bool __cdecl BattleRoyalField::onStandBy(::Zone *)
{
    LIFT_STUB(0x53630);
}

// 0x537b0
bool __cdecl BattleRoyalField::start(::Zone *)
{
    LIFT_STUB(0x537b0);
}

// 0x53980
void __cdecl BattleRoyalField::setEventAreaInfo(void)
{
    LIFT_STUB(0x53980);
}

// 0x53aa0
bool __cdecl BattleRoyalField::onStart(::Zone *)
{
    LIFT_STUB(0x53aa0);
}

// 0x53d70
void __cdecl BattleRoyalField::setBattleRoyalFieldStartTime(__int64)
{
    LIFT_STUB(0x53d70);
}

// 0x53e10
void __cdecl BattleRoyalField::setCombatStartTime(::Zone *, __int64)
{
    LIFT_STUB(0x53e10);
}

// 0x53ec0
bool __cdecl BattleRoyalField::inProgress(::Zone *)
{
    LIFT_STUB(0x53ec0);
}

// 0x54090
bool __cdecl BattleRoyalField::onInProgress(::Zone *)
{
    LIFT_STUB(0x54090);
}

// 0x541a0
bool __cdecl BattleRoyalField::finish(::Zone *)
{
    LIFT_STUB(0x541a0);
}

// 0x542e0
bool __cdecl BattleRoyalField::onFinish(::Zone *)
{
    LIFT_STUB(0x542e0);
}

// 0x544e0
bool __cdecl BattleRoyalField::IsPartyMode(void)
{
    LIFT_STUB(0x544e0);
}

// 0x54520
bool __cdecl BattleRoyalField::IsArenaMathcing(void)
{
    LIFT_STUB(0x54520);
}

// 0x54530
void __cdecl BattleRoyalField::onIncrementReservePcCountAttractionRule(::Zone *, int)
{
    LIFT_STUB(0x54530);
}

// 0x54660
void __cdecl BattleRoyalField::doEnvOperation(::Zone *)
{
    LIFT_STUB(0x54660);
}

// 0x547d0
bool __cdecl BattleRoyalField::executeBattleRoyalFieldEvent(::Zone *)
{
    LIFT_STUB(0x547d0);
}

// 0x54fe0
bool __cdecl BattleRoyalField::invokeEventEffect(::Zone *, int)
{
    LIFT_STUB(0x54fe0);
}

// 0x555e0
bool __cdecl BattleRoyalField::invokeEffect(::Zone *, unsigned __int64, unsigned __int64, unsigned __int64)
{
    LIFT_STUB(0x555e0);
}

// 0x556d0
bool __cdecl BattleRoyalField::startEvent(::Zone *)
{
    LIFT_STUB(0x556d0);
}

// 0x557e0
bool __cdecl BattleRoyalField::stopEvent(::Zone *)
{
    LIFT_STUB(0x557e0);
}

// 0x55a60
bool __cdecl BattleRoyalField::setNextEventIndex(::Zone *)
{
    LIFT_STUB(0x55a60);
}

// 0x55b70
bool __cdecl BattleRoyalField::calculateEventCenterPos(void)
{
    LIFT_STUB(0x55b70);
}

// 0x55e20
void __cdecl BattleRoyalField::OnDead(::Zone *, unsigned __int64, ::Creature *)
{
    LIFT_STUB(0x55e20);
}

// 0x56440
bool __cdecl BattleRoyalField::CheckToFinishGame(void)
{
    LIFT_STUB(0x56440);
}

// 0x56550
void __cdecl BattleRoyalField::OnDamagedEvent(::Zone *, ::ControlledCreature *const, ::Creature *, __int64)
{
    LIFT_STUB(0x56550);
}

// 0x567f0
bool __cdecl BattleRoyalField::GetFinishRespawnArea(::Pc *, unsigned int &, unsigned __int64 &)
{
    LIFT_STUB(0x567f0);
}

// 0x568e0
bool __cdecl BattleRoyalField::CanResurrect(::ControlledCreature const *)
{
    LIFT_STUB(0x568e0);
}

// 0x56ab0
wchar_t * __cdecl BattleRoyalField::GetStateName(char)
{
    LIFT_STUB(0x56ab0);
}

// 0x56b00
wchar_t * __cdecl BattleRoyalField::GetPartyStateName(char)
{
    LIFT_STUB(0x56b00);
}

// 0x56b40
wchar_t * __cdecl BattleRoyalField::GetPcCombatSideName(char)
{
    LIFT_STUB(0x56b40);
}

// 0x56bb0
void __cdecl BattleRoyalField::TakeAttractionReward(::Pc *)
{
    LIFT_STUB(0x56bb0);
}

// 0x56bd0
void __cdecl BattleRoyalField::processBattleRoyalResultTran(::Pc *, char)
{
    LIFT_STUB(0x56bd0);
}

// 0x571c0
bool __cdecl BattleRoyalField::startBattleRoyalResultTran(::Pc *, char, ::DuelResultTranResultNotifyInfo const &)
{
    LIFT_STUB(0x571c0);
}

// 0x57720
bool __cdecl BattleRoyalField::EnableInfiniteHyperEnergy(void) const
{
    LIFT_STUB(0x57720);
}

// 0x57730
bool __cdecl BattleRoyalField::EnableArenaEventReturnToArenaLobbyAllPc(void)
{
    LIFT_STUB(0x57730);
}

// 0x57740
void __cdecl BattleRoyalField::FetchBattleRoyalScore(::Packet &, ::RepeatPacketComposer &)
{
    LIFT_STUB(0x57740);
}

// 0x57840
bool __cdecl BattleRoyalFieldPlayerManager::PlayerEnter(::Zone *, ::Pc *)
{
    LIFT_STUB(0x57840);
}

// 0x57980
void __cdecl BattleRoyalFieldPlayerManager::PlayerLeave(::Zone *, ::Pc *)
{
    LIFT_STUB(0x57980);
}

// 0x57b00
bool __cdecl BattleRoyalFieldPlayerManager::partyEnter(::Zone *, ::Pc *)
{
    LIFT_STUB(0x57b00);
}

// 0x57c50
void __cdecl BattleRoyalFieldPlayerManager::partyLeave(::Zone *, ::Pc *)
{
    LIFT_STUB(0x57c50);
}

// 0x57d70
bool __cdecl BattleRoyalFieldPlayerManager::AllPlayerStartGame(::Zone *, unsigned __int64, wchar_t *)
{
    LIFT_STUB(0x57d70);
}

// 0x581f0
bool __cdecl BattleRoyalFieldPlayerManager::allPartyStartGame(::Zone *)
{
    LIFT_STUB(0x581f0);
}

// 0x58370
bool __cdecl BattleRoyalFieldPlayerManager::AllPlayerFinishGame(::Zone *)
{
    LIFT_STUB(0x58370);
}

// 0x58890
bool __cdecl BattleRoyalFieldPlayerManager::PlayerFinishGame(::Zone *, ::Pc *, bool)
{
    LIFT_STUB(0x58890);
}

// 0x58cc0
void __cdecl BattleRoyalFieldPlayerManager::partyFinishGame(::Zone *, ::Pc *)
{
    LIFT_STUB(0x58cc0);
}

// 0x58e30
::BattleRoyalFieldPlayer __cdecl BattleRoyalFieldPlayerManager::GetPlayerRecord(::Zone *, unsigned __int64)
{
    LIFT_STUB(0x58e30);
}

// 0x58fd0
char __cdecl BattleRoyalFieldPlayerManager::GetPlayerState(::Zone *, unsigned __int64)
{
    LIFT_STUB(0x58fd0);
}

// 0x59110
char __cdecl BattleRoyalFieldPlayerManager::GetPlayerKillCount(unsigned __int64)
{
    LIFT_STUB(0x59110);
}

// 0x59160
void __cdecl BattleRoyalFieldPlayerManager::IncreaseKillPcCount(::Zone *, ::Pc *)
{
    LIFT_STUB(0x59160);
}

// 0x59270
int __cdecl BattleRoyalFieldPlayerManager::GetPlayerAttackDamage(unsigned __int64)
{
    LIFT_STUB(0x59270);
}

// 0x592c0
void __cdecl BattleRoyalFieldPlayerManager::AddAttackDamage(::Zone *, ::Pc *, int)
{
    LIFT_STUB(0x592c0);
}

// 0x594f0
char __cdecl BattleRoyalFieldPlayerManager::GetPlayerRanking(unsigned __int64)
{
    LIFT_STUB(0x594f0);
}

// 0x59530
bool __cdecl BattleRoyalFieldPlayerManager::SetAllPlayerCombatSide(::Zone *, char)
{
    LIFT_STUB(0x59530);
}

// 0x59800
bool __cdecl BattleRoyalFieldPlayerManager::insertPlayerRecord(::Zone *, ::Pc *)
{
    LIFT_STUB(0x59800);
}

// 0x59b60
void __cdecl BattleRoyalFieldPlayerManager::resetPlayerRecord(::Zone *, unsigned __int64)
{
    LIFT_STUB(0x59b60);
}

// 0x59cf0
bool __cdecl BattleRoyalFieldPlayerManager::insertPartyRecord(::Zone *, ::Pc *)
{
    LIFT_STUB(0x59cf0);
}

// 0x59df0
void __cdecl BattleRoyalFieldPlayerManager::resetPartyRecord(::Zone *, unsigned __int64)
{
    LIFT_STUB(0x59df0);
}

// 0x59ec0
void __cdecl BattleRoyalFieldPlayerManager::increasePlayingPartyMemberCount(::Zone *, ::Pc *)
{
    LIFT_STUB(0x59ec0);
}

// 0x5a010
void __cdecl BattleRoyalFieldPlayerManager::decreasePlayingPartyMemberCount(::Zone *, ::Pc *)
{
    LIFT_STUB(0x5a010);
}

// 0x5a160
bool __cdecl BattleRoyalFieldPlayerManager::isMemberCountZero(::Zone *, ::Pc *)
{
    LIFT_STUB(0x5a160);
}

// 0x5a290
bool __cdecl BattleRoyalFieldPlayerManager::setPartyState(::Zone *, unsigned __int64, char)
{
    LIFT_STUB(0x5a290);
}

// 0x5a420
bool __cdecl BattleRoyalFieldPlayerManager::setPlayerRanking(::Zone *, ::Pc *, bool)
{
    LIFT_STUB(0x5a420);
}

// 0x5a6c0
bool __cdecl BattleRoyalFieldPlayerManager::setPlayerCombatSide(::Zone *, ::Pc *, char)
{
    LIFT_STUB(0x5a6c0);
}

// 0x5a8c0
void __cdecl BattleRoyalFieldPlayerManager::initAllPlayer(::Zone *)
{
    LIFT_STUB(0x5a8c0);
}

// 0x5ad70
void __cdecl BattleRoyalFieldPlayerManager::increasePlayingPcCount(::Zone *, unsigned __int64)
{
    LIFT_STUB(0x5ad70);
}

// 0x5b010
void __cdecl BattleRoyalFieldPlayerManager::decreasePlayingPcCount(::Zone *, unsigned __int64)
{
    LIFT_STUB(0x5b010);
}

// 0x5b2b0
void __cdecl BattleRoyalFieldPlayerManager::increasePlayingPartyCount(::Zone *, ::Pc *)
{
    LIFT_STUB(0x5b2b0);
}

// 0x5b3d0
void __cdecl BattleRoyalFieldPlayerManager::decreasePlayingPartyCount(::Zone *, ::Pc *)
{
    LIFT_STUB(0x5b3d0);
}

// 0x5b4f0
void __cdecl BattleRoyalFieldPlayerManager::WriteBattleRoyalFieldStartPcLog(::Zone *, unsigned __int64, wchar_t *)
{
    LIFT_STUB(0x5b4f0);
}

// 0x5b630
void __cdecl BattleRoyalFieldGameLog::WriteBattleRoyalFieldEnd(::Zone *, unsigned __int64, wchar_t *, char)
{
    LIFT_STUB(0x5b630);
}

// 0x5b700
void __cdecl BattleRoyalFieldGameLog::WriteBattleRoyalFieldStartPc(::Pc *, unsigned __int64, wchar_t *)
{
    LIFT_STUB(0x5b700);
}

// 0x5b900
void __cdecl BattleRoyalFieldGameLog::WriteBattleRoyalFieldEndPc(::Pc *, unsigned __int64, wchar_t *, char, char, char)
{
    LIFT_STUB(0x5b900);
}

// 0x5bb50
void __cdecl BattleRoyalFieldGameLog::WriteLootBattleRoyalFieldDroppedItem(::Pc *, unsigned __int64, unsigned __int64, __int64)
{
    LIFT_STUB(0x5bb50);
}

// 0x5bd40
void __cdecl BattleRoyalFieldGameLog::WriteBattleRoyalFieldRewardItem(::Pc *, unsigned __int64, __int64, __int64)
{
    LIFT_STUB(0x5bd40);
}
