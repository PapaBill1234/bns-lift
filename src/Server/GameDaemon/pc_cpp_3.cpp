// pc_cpp_3.cpp: pc.cpp part 3 (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "pc.h"
#include "creature.h"
#include "npcdeadbody.h"
#include "raiddungeon.h"
#include "task.h"
#include "transactionexpirechecker.h"
#include "zone.h"
#include "zoneserializedobject.h"
#include "LiftStub.h"

// 0x5f70b0
void __cdecl Pc::ActivateGradeBenefit(int)
{
    LIFT_STUB(0x5f70b0);
}

// 0x5f7390
void __cdecl Pc::ActivateGradeEffectBenefits(void)
{
    LIFT_STUB(0x5f7390);
}

// 0x5f7580
void __cdecl Pc::DeactivateAllGradeBenefits(bool)
{
    LIFT_STUB(0x5f7580);
}

// 0x5f7610
void __cdecl Pc::DeactivateGradeBenefit(int, bool &)
{
    LIFT_STUB(0x5f7610);
}

// 0x5f7860
void __cdecl Pc::onGradeTimerExpired(void)
{
    LIFT_STUB(0x5f7860);
}

// 0x5f7a90
bool __cdecl Pc::IsAvailableGradeAchievement(short, short)
{
    LIFT_STUB(0x5f7a90);
}

// 0x5f7b90
bool __cdecl Pc::IsAllowedContent(char)
{
    LIFT_STUB(0x5f7b90);
}

// 0x5f7d50
bool __cdecl Pc::isActivatedGrade(int) const
{
    LIFT_STUB(0x5f7d50);
}

// 0x5f7d90
void __cdecl Pc::invokeGradeEffect(int)
{
    LIFT_STUB(0x5f7d90);
}

// 0x5f7f00
void __cdecl Pc::deactivateGradeVitalityBonus(void)
{
    LIFT_STUB(0x5f7f00);
}

// 0x5f8180
void __cdecl Pc::checkAndDeactivateGradeAchievementBenefit(void)
{
    LIFT_STUB(0x5f8180);
}

// 0x5f8350
void __cdecl Pc::IncreaseContribution(unsigned __int64, __int64, char, __int64)
{
    LIFT_STUB(0x5f8350);
}

// 0x5f8400
void __cdecl Pc::insertContribution(unsigned __int64, __int64, char, __int64)
{
    LIFT_STUB(0x5f8400);
}

// 0x5f8590
__int64 __cdecl Pc::GetRewardContribution(unsigned __int64, __int64)
{
    LIFT_STUB(0x5f8590);
}

// 0x5f85e0
__int64 __cdecl Pc::RegisterContributionPouch(::NpcDeadBody &, __int64, __int64, __int64)
{
    LIFT_STUB(0x5f85e0);
}

// 0x5f8800
void __cdecl Pc::insertContributionPouch(::NpcDeadBody &, __int64, __int64)
{
    LIFT_STUB(0x5f8800);
}

// 0x5f8bc0
::GameFailReason __cdecl Pc::TakeContributionReward(::NpcDeadBody &)
{
    LIFT_STUB(0x5f8bc0);
}

// 0x5f8e60
int __cdecl Pc::TakeContributionFactionScore(::NpcDeadBody &, int, __int64)
{
    LIFT_STUB(0x5f8e60);
}

// 0x5f8f50
bool __cdecl Pc::SetExceptLootCaseBitMap(unsigned __int64, int, char)
{
    LIFT_STUB(0x5f8f50);
}

// 0x5f8fb0
void __cdecl Pc::sendContributionPouchList(unsigned __int64)
{
    LIFT_STUB(0x5f8fb0);
}

// 0x5f9220
void __cdecl Pc::ResetAllGroupContribution(void)
{
    LIFT_STUB(0x5f9220);
}

// 0x5f9360
void __cdecl Pc::ResetContribution(char, __int64)
{
    LIFT_STUB(0x5f9360);
}

// 0x5f95b0
void __cdecl Pc::SetMaxLevel(void)
{
    LIFT_STUB(0x5f95b0);
}

// 0x5f9860
bool __cdecl Pc::CheckRechargeVitality(void)
{
    LIFT_STUB(0x5f9860);
}

// 0x5f99a0
bool __cdecl Pc::RechargeVitality(::ChangedProperty *)
{
    LIFT_STUB(0x5f99a0);
}

// 0x5f9e00
void __cdecl Pc::CutOffVitality(::ChangedProperty *)
{
    LIFT_STUB(0x5f9e00);
}

// 0x5fa120
void __cdecl Pc::SendEnterPortalFail(::GameFailReason)
{
    LIFT_STUB(0x5fa120);
}

// 0x5fa2a0
bool __cdecl Pc::AvailableTurnBack(void)
{
    LIFT_STUB(0x5fa2a0);
}

// 0x5fa360
bool __cdecl Pc::executeZSO(::Zone *)
{
    LIFT_STUB(0x5fa360);
}

// 0x5fa5b0
void __cdecl Pc::destroyZSO(::Pc::ExpireReason, wchar_t const *)
{
    LIFT_STUB(0x5fa5b0);
}

// 0x5fa710
bool __cdecl Pc::postZSO(::ZoneSerializedObject *, ::Pc::ZSOType, bool)
{
    LIFT_STUB(0x5fa710);
}

// 0x5fa8b0
bool __cdecl Pc::HandleChallengePartyId(__int64, ::ChangedProperty *)
{
    LIFT_STUB(0x5fa8b0);
}

// 0x5fa9b0
bool __cdecl Pc::HandleChallengePartyOutTime(__int64, ::ChangedProperty *)
{
    LIFT_STUB(0x5fa9b0);
}

// 0x5faab0
__int64 __cdecl Pc::GetGuildRegistrationTime(void)
{
    LIFT_STUB(0x5faab0);
}

// 0x5fab60
void __cdecl Pc::UpdateGeoZoneToGuild(::EnterReason)
{
    LIFT_STUB(0x5fab60);
}

// 0x5faca0
bool __cdecl Pc::PostSetGuildIdTask(unsigned __int64, wchar_t const *)
{
    LIFT_STUB(0x5faca0);
}

// 0x5fb150
bool __cdecl Pc::PostCompleteChallengeList(unsigned __int64, char, char, char, char, wchar_t const *)
{
    LIFT_STUB(0x5fb150);
}

// 0x5fb1f0
void __cdecl Pc::SendGetGradeListFailToArena(short)
{
    LIFT_STUB(0x5fb1f0);
}

// 0x5fb3a0
void __cdecl Pc::SendGradeList(void)
{
    LIFT_STUB(0x5fb3a0);
}

// 0x5fb630
void __cdecl Pc::SendGradeListToArena(int, ::GradeLevelInfo &, ::GradeInfo *const, short)
{
    LIFT_STUB(0x5fb630);
}

// 0x5fb940
void __cdecl Pc::SendGradeToArena(int, ::GradeInfo &, char)
{
    LIFT_STUB(0x5fb940);
}

// 0x5fbb50
void __cdecl Pc::SendGradeLevelToArena(int, ::GradeLevelInfo &)
{
    LIFT_STUB(0x5fbb50);
}

// 0x5fbd40
void __cdecl Pc::SendGuildInfoToArena(::Session const *)
{
    LIFT_STUB(0x5fbd40);
}

// 0x5fc020
void __cdecl Pc::SendGamePlayRestrictLevelToArena(::Session const *)
{
    LIFT_STUB(0x5fc020);
}

// 0x5fc1a0
void __cdecl Pc::SendGamePlayRestrictLevelForHealthySystemToArena(::Session const *)
{
    LIFT_STUB(0x5fc1a0);
}

// 0x5fc300
void __cdecl Pc::SendChangedGuildBuff(::SeasonContentsResultInfoOfGuild const *)
{
    LIFT_STUB(0x5fc300);
}

// 0x5fc650
short __cdecl Pc::CheckArenaPortalUsable(::Data::ArenaPortalRecordPtr)
{
    LIFT_STUB(0x5fc650);
}

// 0x5fc9f0
bool __cdecl Pc::BeginArenaLobbyReservation(unsigned __int64, char)
{
    LIFT_STUB(0x5fc9f0);
}

// 0x5fca90
void __cdecl Pc::RollbackArenaLobbyReservation(void)
{
    LIFT_STUB(0x5fca90);
}

// 0x5fcae0
bool __cdecl Pc::CreateArenaLobbyRoomNotify(::ArenaLobbyEnterParam const &, bool, char)
{
    LIFT_STUB(0x5fcae0);
}

// 0x5fcc00
void __cdecl Pc::SendReserveArenaLobbyFail(short)
{
    LIFT_STUB(0x5fcc00);
}

// 0x5fcd70
void __cdecl Pc::SendFriendNotiLocation(::Pc::FriendNotiLocationType)
{
    LIFT_STUB(0x5fcd70);
}

// 0x5fcfe0
short __cdecl Pc::SendEnterArenaLobby(char const *, short)
{
    LIFT_STUB(0x5fcfe0);
}

// 0x5fd820
void __cdecl Pc::SendLeaveArenaLobbyByDisconnect(void)
{
    LIFT_STUB(0x5fd820);
}

// 0x5fd930
short __cdecl Pc::SendLeaveArenaLobbyByUserRequest(void)
{
    LIFT_STUB(0x5fd930);
}

// 0x5fda50
bool __cdecl Pc::SendLeaveArenaLobbyByAASFatiqueRule(void)
{
    LIFT_STUB(0x5fda50);
}

// 0x5fdb60
bool __cdecl Pc::EnterArenaLobbyOk(char)
{
    LIFT_STUB(0x5fdb60);
}

// 0x5fdc40
bool __cdecl Pc::LeaveArenaLobbyOk(void)
{
    LIFT_STUB(0x5fdc40);
}

// 0x5fdcc0
short __cdecl Pc::SendExitFromArenaLobbyRoom(void)
{
    LIFT_STUB(0x5fdcc0);
}

// 0x5fddc0
short __cdecl Pc::SendSetArenaLobbyRoomMatchOption(char, char, char, char, short, short const *const)
{
    LIFT_STUB(0x5fddc0);
}

// 0x5fe780
short __cdecl Pc::SendDelegateArenaLobbyRoomLeader(short, unsigned __int64)
{
    LIFT_STUB(0x5fe780);
}

// 0x5fe880
short __cdecl Pc::SendSetArenaLobbyRoomPassword(short)
{
    LIFT_STUB(0x5fe880);
}

// 0x5fe970
short __cdecl Pc::SendJoinArenaLobbyRoom(__int64, wchar_t const *, short, char, char)
{
    LIFT_STUB(0x5fe970);
}

// 0x5fead0
short __cdecl Pc::SendBanishFromArenaLobby(short, unsigned __int64)
{
    LIFT_STUB(0x5fead0);
}

// 0x5febd0
bool __cdecl Pc::ReturnToGame(void)
{
    LIFT_STUB(0x5febd0);
}

// 0x5fec90
short __cdecl Pc::SendReadyToMatchArenaLobbyRoom(void)
{
    LIFT_STUB(0x5fec90);
}

// 0x5fed90
short __cdecl Pc::SendUnReadyToMatchArenaLobbyRoom(void)
{
    LIFT_STUB(0x5fed90);
}

// 0x5fee70
short __cdecl Pc::SendArenaLobbyMatchReq(char)
{
    LIFT_STUB(0x5fee70);
}

// 0x5ff000
short __cdecl Pc::SendSkipArenaLobbyMatchReq(void)
{
    LIFT_STUB(0x5ff000);
}

// 0x5ff0e0
short __cdecl Pc::SendCancelArenaLobbyMatchingReq(char)
{
    LIFT_STUB(0x5ff0e0);
}

// 0x5ff1d0
short __cdecl Pc::SendCancelArenaLobbyMatchReq(void)
{
    LIFT_STUB(0x5ff1d0);
}

// 0x5ff2b0
short __cdecl Pc::SendDecideToGoToArena(::Data::ArenaMatchingRuleDetailType)
{
    LIFT_STUB(0x5ff2b0);
}

// 0x5ff3a0
bool __cdecl Pc::ReserveArena(::ReserveArenaParam const &)
{
    LIFT_STUB(0x5ff3a0);
}

// 0x5ff580
void __cdecl Pc::RetrieveArenaLobbyWaitingNumber(void)
{
    LIFT_STUB(0x5ff580);
}

// 0x5ff6f0
void __cdecl Pc::RetrieveArenaLobbyWaitingNumberComplete(unsigned __int64, int)
{
    LIFT_STUB(0x5ff6f0);
}

// 0x5ff7f0
short __cdecl Pc::CancelArenaLobbyWaiting(void)
{
    LIFT_STUB(0x5ff7f0);
}

// 0x5ff8e0
void __cdecl Pc::CancelArenaLobbyWaitingComplete(unsigned __int64)
{
    LIFT_STUB(0x5ff8e0);
}

// 0x5ff990
bool __cdecl Pc::SendEnterArena(char const *, int)
{
    LIFT_STUB(0x5ff990);
}

// 0x6004f0
void __cdecl Pc::InitArenaGradeParam(void)
{
    LIFT_STUB(0x6004f0);
}

// 0x6006f0
bool __cdecl Pc::SetArenaGradeParam(::ArenaGradeParam &)
{
    LIFT_STUB(0x6006f0);
}

// 0x600850
bool __cdecl Pc::GetArenaGradeParam(::ArenaGradeParam &)
{
    LIFT_STUB(0x600850);
}

// 0x6009b0
bool __cdecl Pc::SendLogoutReqToArena(::TransactionExpireChecker::ExpireToken *, short)
{
    LIFT_STUB(0x6009b0);
}

// 0x600a80
bool __cdecl Pc::SendLogoutReqToArena(unsigned __int64, short)
{
    LIFT_STUB(0x600a80);
}

// 0x600b30
void __cdecl Pc::LogoutOkFromArena(void)
{
    LIFT_STUB(0x600b30);
}

// 0x600b90
void __cdecl Pc::UpdateReturnPos(::Pc::UpdateReturnPosType)
{
    LIFT_STUB(0x600b90);
}

// 0x600ce0
void __cdecl Pc::ArenaLobbyClosed(short)
{
    LIFT_STUB(0x600ce0);
}

// 0x600e20
void __cdecl Pc::ReturnToGameByEnterFail(void)
{
    LIFT_STUB(0x600e20);
}

// 0x600eb0
short __cdecl Pc::SendMoveToArena(int, bool, char)
{
    LIFT_STUB(0x600eb0);
}

// 0x600fe0
::Pc::ArenaSession __cdecl Pc::GetArenaSessionState(void) const
{
    LIFT_STUB(0x600fe0);
}

// 0x601020
bool __cdecl Pc::IsInArenaOrArenaLobby(void) const
{
    LIFT_STUB(0x601020);
}

// 0x601080
char __cdecl Pc::GetArenaLobbySessionForClient(void)
{
    LIFT_STUB(0x601080);
}

// 0x601100
wchar_t const * __cdecl Pc::GetArenaSessionString(void) const
{
    LIFT_STUB(0x601100);
}

// 0x601200
bool __cdecl Pc::FetchShowcaseData(::FsdShowcaseRecord *)
{
    LIFT_STUB(0x601200);
}

// 0x601600
void __cdecl Pc::resetExhaustionTimer(bool)
{
    LIFT_STUB(0x601600);
}

// 0x601b00
void __cdecl Pc::exhaustionExceptRule(bool)
{
    LIFT_STUB(0x601b00);
}

// 0x601c00
void __cdecl Pc::onExhaustionTimer(void)
{
    LIFT_STUB(0x601c00);
}

// 0x601da0
void __cdecl Pc::onAutoRespawnTimer(void)
{
    LIFT_STUB(0x601da0);
}

// 0x601e50
bool __cdecl Pc::UseHyperEnergy(int)
{
    LIFT_STUB(0x601e50);
}

// 0x601f10
int __cdecl Pc::getMaxHyperEnergyPoint(void)
{
    LIFT_STUB(0x601f10);
}

// 0x602090
void __cdecl Pc::calcHyperEnergyPoint(void)
{
    LIFT_STUB(0x602090);
}

// 0x602150
bool __cdecl Pc::changeMoveState(::CreatureMoveState, short, wchar_t *)
{
    LIFT_STUB(0x602150);
}

// 0x602810
void __cdecl Pc::StopTrialPlay(void)
{
    LIFT_STUB(0x602810);
}

// 0x602910
bool __cdecl Pc::IsBoundRaidDungeon(unsigned __int64)
{
    LIFT_STUB(0x602910);
}

// 0x602990
int __cdecl Pc::GetAllBoundRaidDungeon(::Pointer2< ::RaidDungeon> *const)
{
    LIFT_STUB(0x602990);
}

// 0x602b80
void __cdecl Pc::LogoutBoundRaidDungeon(void)
{
    LIFT_STUB(0x602b80);
}

// 0x602c50
bool __cdecl Pc::SetOccupyingRaidDungeon(unsigned __int64)
{
    LIFT_STUB(0x602c50);
}

// 0x602e30
bool __cdecl Pc::InitializeRaidDungeonInfo(bool)
{
    LIFT_STUB(0x602e30);
}

// 0x603290
::GameFailReason __cdecl Pc::isEnterableRaidDungeon(short, unsigned __int64 &, char)
{
    LIFT_STUB(0x603290);
}

// 0x604020
void __cdecl Pc::writeLogMoveHacking(void)
{
    LIFT_STUB(0x604020);
}

// 0x6041c0
void __cdecl Pc::checkToEnterZoneCount(void)
{
    LIFT_STUB(0x6041c0);
}

// 0x6042c0
void __cdecl Pc::CheckToInvalidPartyPacket(void)
{
    LIFT_STUB(0x6042c0);
}

// 0x604350
bool __cdecl Pc::checkTeamFactionBattleFieldWithTarget(::Creature *)
{
    LIFT_STUB(0x604350);
}

// 0x604430
bool __cdecl Pc::checkTeamGuildBattleFieldWithTarget(::Creature *)
{
    LIFT_STUB(0x604430);
}

// 0x6044d0
char __cdecl Pc::CheckTeamAttractionCondition(unsigned int)
{
    LIFT_STUB(0x6044d0);
}
