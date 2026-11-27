// task_cpp_3.cpp: task.cpp part 3 (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "task.h"
#include "creature.h"
#include "duelbottrainingroomscorecontainer.h"
#include "duelbottrainingroomtran.h"
#include "item.h"
#include "pc.h"
#include "team.h"
#include "user.h"
#include "zone.h"
#include "LiftStub.h"

// 0x2b3120
bool __cdecl InvitePcToPartyTask::checkZoneRule(::Pointer2< ::Pc>, ::Pointer2< ::Pc>)
{
    LIFT_STUB(0x2b3120);
}

// 0x2b33c0
void __cdecl InvitePcToPartyTask::start(void)
{
    LIFT_STUB(0x2b33c0);
}

// 0x2b4790
bool __cdecl RejectTeamInvitationTask::Initialize(::Zone *, ::Creature *, ::TeamInvitationType, unsigned __int64, char, char)
{
    LIFT_STUB(0x2b4790);
}

// 0x2b4870
void __cdecl RejectTeamInvitationTask::start(void)
{
    LIFT_STUB(0x2b4870);
}

// 0x2b4f90
bool __cdecl LeaveTeamMemberTask::Initialize(::Zone *, ::Creature *, unsigned __int64, ::LeavePartyReason)
{
    LIFT_STUB(0x2b4f90);
}

// 0x2b5060
void __cdecl LeaveTeamMemberTask::TimerExpired(unsigned int, long)
{
    LIFT_STUB(0x2b5060);
}

// 0x2b50a0
void __cdecl LeaveTeamMemberTask::start(void)
{
    LIFT_STUB(0x2b50a0);
}

// 0x2b51b0
bool __cdecl LeaveTeamPartyTask::Initialize(::Zone *, ::Creature *, unsigned __int64, ::LeavePartyReason)
{
    LIFT_STUB(0x2b51b0);
}

// 0x2b5270
void __cdecl LeaveTeamPartyTask::TimerExpired(unsigned int, long)
{
    LIFT_STUB(0x2b5270);
}

// 0x2b52b0
void __cdecl LeaveTeamPartyTask::start(void)
{
    LIFT_STUB(0x2b52b0);
}

// 0x2b5420
bool __cdecl BanishFromTeamTask::Initialize(::Zone *, ::Creature *, short, char)
{
    LIFT_STUB(0x2b5420);
}

// 0x2b54f0
void __cdecl BanishFromTeamTask::start(void)
{
    LIFT_STUB(0x2b54f0);
}

// 0x2b55d0
bool __cdecl TeamMemberPartyChangeTask::Initialize(::Zone *, ::Creature *, short, char, __int64, short, char, __int64)
{
    LIFT_STUB(0x2b55d0);
}

// 0x2b56d0
void __cdecl TeamMemberPartyChangeTask::start(void)
{
    LIFT_STUB(0x2b56d0);
}

// 0x2b5830
bool __cdecl DelegateTeamLeaderTask::Initialize(::Zone *, ::Creature *, unsigned __int64)
{
    LIFT_STUB(0x2b5830);
}

// 0x2b5900
void __cdecl DelegateTeamLeaderTask::start(void)
{
    LIFT_STUB(0x2b5900);
}

// 0x2b5a50
bool __cdecl NominatePartyLeaderTask::Initialize(::Zone *, ::Creature *, unsigned __int64)
{
    LIFT_STUB(0x2b5a50);
}

// 0x2b5b20
void __cdecl NominatePartyLeaderTask::start(void)
{
    LIFT_STUB(0x2b5b20);
}

// 0x2b5c70
bool __cdecl ChangeTeamInviteAuthTask::Initialize(::Zone *, ::Creature *, char)
{
    LIFT_STUB(0x2b5c70);
}

// 0x2b5d40
void __cdecl ChangeTeamInviteAuthTask::start(void)
{
    LIFT_STUB(0x2b5d40);
}

// 0x2b5e00
bool __cdecl ChangeTeamPartyDifficultyTypeTask::Initialize(::Zone *, ::Creature *, char, char)
{
    LIFT_STUB(0x2b5e00);
}

// 0x2b5ed0
void __cdecl ChangeTeamPartyDifficultyTypeTask::start(void)
{
    LIFT_STUB(0x2b5ed0);
}

// 0x2b5f80
bool __cdecl CheckToJoinPartyTask::Initialize(::Zone *, ::Creature *, unsigned __int64, unsigned int, char)
{
    LIFT_STUB(0x2b5f80);
}

// 0x2b6060
void __cdecl CheckToJoinPartyTask::TimerExpired(unsigned int, long)
{
    LIFT_STUB(0x2b6060);
}

// 0x2b60a0
void __cdecl CheckToJoinPartyTask::start(void)
{
    LIFT_STUB(0x2b60a0);
}

// 0x2b6b20
bool __cdecl ReservePartyMemberTask::Initialize(::Zone *, ::Creature *, unsigned __int64, unsigned __int64, unsigned int, char)
{
    LIFT_STUB(0x2b6b20);
}

// 0x2b6c00
void __cdecl ReservePartyMemberTask::TimerExpired(unsigned int, long)
{
    LIFT_STUB(0x2b6c00);
}

// 0x2b6c40
void __cdecl ReservePartyMemberTask::start(void)
{
    LIFT_STUB(0x2b6c40);
}

// 0x2b7040
bool __cdecl ConfirmPartyMemberTask::Initialize(::Zone *, ::Creature *, unsigned int, char, char)
{
    LIFT_STUB(0x2b7040);
}

// 0x2b7120
void __cdecl ConfirmPartyMemberTask::ProcessUnexpired(int)
{
    LIFT_STUB(0x2b7120);
}

// 0x2b71b0
void __cdecl ConfirmPartyMemberTask::TimerExpired(unsigned int, long)
{
    LIFT_STUB(0x2b71b0);
}

// 0x2b71f0
void __cdecl ConfirmPartyMemberTask::start(void)
{
    LIFT_STUB(0x2b71f0);
}

// 0x2b7380
bool __cdecl DismissPartyIfSoloTask::Initialize(::Zone *, ::Creature *)
{
    LIFT_STUB(0x2b7380);
}

// 0x2b7430
void __cdecl DismissPartyIfSoloTask::TimerExpired(unsigned int, long)
{
    LIFT_STUB(0x2b7430);
}

// 0x2b7470
void __cdecl DismissPartyIfSoloTask::start(void)
{
    LIFT_STUB(0x2b7470);
}

// 0x2b75b0
bool __cdecl SuggestPartyTask::Initialize(::Zone *, ::Creature *, unsigned __int64, char, char, char, char, char, char)
{
    LIFT_STUB(0x2b75b0);
}

// 0x2b76c0
void __cdecl SuggestPartyTask::start(void)
{
    LIFT_STUB(0x2b76c0);
}

// 0x2b7920
bool __cdecl CreatePartyTask::Initialize(::Zone *, ::Creature *, char, bool)
{
    LIFT_STUB(0x2b7920);
}

// 0x2b79f0
void __cdecl CreatePartyTask::start(void)
{
    LIFT_STUB(0x2b79f0);
}

// 0x2b7af0
bool __cdecl DelegatePartyLeaderTask::Initialize(::Zone *, ::Creature *, unsigned __int64)
{
    LIFT_STUB(0x2b7af0);
}

// 0x2b7bc0
void __cdecl DelegatePartyLeaderTask::start(void)
{
    LIFT_STUB(0x2b7bc0);
}

// 0x2b7d30
bool __cdecl BanishFromPartyTask::Initialize(::Zone *, ::Creature *, char)
{
    LIFT_STUB(0x2b7d30);
}

// 0x2b7e00
void __cdecl BanishFromPartyTask::start(void)
{
    LIFT_STUB(0x2b7e00);
}

// 0x2b7ee0
bool __cdecl ClearLogoutPartyMemberTask::Initialize(::Zone *, ::Creature *)
{
    LIFT_STUB(0x2b7ee0);
}

// 0x2b7f90
void __cdecl ClearLogoutPartyMemberTask::start(void)
{
    LIFT_STUB(0x2b7f90);
}

// 0x2b8050
bool __cdecl ChangePartyOptionTask::Initialize(::Zone *, ::Creature *, ::PartyPickupRule, unsigned __int64, char, __int64)
{
    LIFT_STUB(0x2b8050);
}

// 0x2b8140
void __cdecl ChangePartyOptionTask::start(void)
{
    LIFT_STUB(0x2b8140);
}

// 0x2b8220
bool __cdecl ChangePartyInviteAuthTask::Initialize(::Zone *, ::Creature *, ::PartyInviteAuth)
{
    LIFT_STUB(0x2b8220);
}

// 0x2b82f0
void __cdecl ChangePartyInviteAuthTask::start(void)
{
    LIFT_STUB(0x2b82f0);
}

// 0x2b83b0
bool __cdecl StopCinematicTask::Initialize(::Zone *, ::Creature *, unsigned int)
{
    LIFT_STUB(0x2b83b0);
}

// 0x2b8480
void __cdecl StopCinematicTask::start(void)
{
    LIFT_STUB(0x2b8480);
}

// 0x2b8680
bool __cdecl ChangePartyDifficultyTypeTask::Initialize(::Zone *, ::Creature *, char)
{
    LIFT_STUB(0x2b8680);
}

// 0x2b8750
void __cdecl ChangePartyDifficultyTypeTask::start(void)
{
    LIFT_STUB(0x2b8750);
}

// 0x2b8810
bool __cdecl UpdatePcTeamInfoTask::Initialize(::Zone *, ::Creature *, unsigned __int64, unsigned __int64)
{
    LIFT_STUB(0x2b8810);
}

// 0x2b88e0
void __cdecl UpdatePcTeamInfoTask::TimerExpired(unsigned int, long)
{
    LIFT_STUB(0x2b88e0);
}

// 0x2b8920
void __cdecl UpdatePcTeamInfoTask::start(void)
{
    LIFT_STUB(0x2b8920);
}

// 0x2b8b50
bool __cdecl PartyVoteCastTask::Initialize(::Zone *, ::Creature *, char, char)
{
    LIFT_STUB(0x2b8b50);
}

// 0x2b8c20
void __cdecl PartyVoteCastTask::start(void)
{
    LIFT_STUB(0x2b8c20);
}

// 0x2b8ee0
void __cdecl TeamPsoTask::TimerExpired(unsigned int, long)
{
    LIFT_STUB(0x2b8ee0);
}

// 0x2b8f20
bool __cdecl InviteTeamTask::Initialize(::Zone *, ::Creature *, char, unsigned __int64, unsigned __int64, char, char, char, char, char, unsigned __int64)
{
    LIFT_STUB(0x2b8f20);
}

// 0x2b9050
void __cdecl InviteTeamTask::start(void)
{
    LIFT_STUB(0x2b9050);
}

// 0x2baba0
bool __cdecl CheckToJoinTeamTask::Initialize(::Zone *, ::Creature *, char, unsigned __int64, unsigned __int64)
{
    LIFT_STUB(0x2baba0);
}

// 0x2bac80
void __cdecl CheckToJoinTeamTask::start(void)
{
    LIFT_STUB(0x2bac80);
}

// 0x2bbba0
bool __cdecl ReserveTeamMemberTask::Initialize(::Zone *, ::Creature *, char, unsigned __int64, unsigned __int64)
{
    LIFT_STUB(0x2bbba0);
}

// 0x2bbc80
void __cdecl ReserveTeamMemberTask::start(void)
{
    LIFT_STUB(0x2bbc80);
}

// 0x2bbf80
bool __cdecl ConfirmTeamMemberTask::Initialize(::Zone *, ::Creature *, ::TeamInvitationType, char)
{
    LIFT_STUB(0x2bbf80);
}

// 0x2bc060
void __cdecl ConfirmTeamMemberTask::ProcessUnexpired(int)
{
    LIFT_STUB(0x2bc060);
}

// 0x2bc0f0
void __cdecl ConfirmTeamMemberTask::start(void)
{
    LIFT_STUB(0x2bc0f0);
}

// 0x2bc2f0
bool __cdecl ConfirmTeamMemberPartyChangeTask::Initialize(::Zone *, ::Creature *, unsigned int, char, char, ::LeavePartyMemberResult *)
{
    LIFT_STUB(0x2bc2f0);
}

// 0x2bc3f0
void __cdecl ConfirmTeamMemberPartyChangeTask::ProcessUnexpired(int)
{
    LIFT_STUB(0x2bc3f0);
}

// 0x2bc480
void __cdecl ConfirmTeamMemberPartyChangeTask::start(void)
{
    LIFT_STUB(0x2bc480);
}

// 0x2bc550
bool __cdecl DuelChooseDuelOrderTask::Initialize(::Zone *const, ::Pc *const, char)
{
    LIFT_STUB(0x2bc550);
}

// 0x2bc600
void __cdecl DuelChooseDuelOrderTask::start(void)
{
    LIFT_STUB(0x2bc600);
}

// 0x2bc850
bool __cdecl DuelTask::Initialize(::Zone *const, ::Pc *const, ::DuelTask::DuelTaskType)
{
    LIFT_STUB(0x2bc850);
}

// 0x2bc8f0
void __cdecl DuelTask::start(void)
{
    LIFT_STUB(0x2bc8f0);
}

// 0x2bcc70
bool __cdecl PartyBattleRatingScoreTask::Initialize(::Zone *, ::Pc *, ::PartyBattleResult, int, int, __int64, ::PartyBattleSideMember const &)
{
    LIFT_STUB(0x2bcc70);
}

// 0x2bcda0
void __cdecl PartyBattleRatingScoreTask::start(void)
{
    LIFT_STUB(0x2bcda0);
}

// 0x2bce30
void __cdecl PartyBattleRatingScoreTask::TimerExpired(unsigned int, long)
{
    LIFT_STUB(0x2bce30);
}

// 0x2bce70
__cdecl PartyBattleRatingScoreTask::~PartyBattleRatingScoreTask(void)
{
    LIFT_STUB(0x2bce70);
}

// 0x2bcee0
bool __cdecl PartyBattleTask::Initialize(::Zone *, ::Creature *, ::PartyBattleTask::PartyBattleTaskType)
{
    LIFT_STUB(0x2bcee0);
}

// 0x2bcfb0
void __cdecl PartyBattleTask::start(void)
{
    LIFT_STUB(0x2bcfb0);
}

// 0x2bd1b0
bool __cdecl PartyBattleVoteCastTask::Initialize(::Zone *, ::Creature *, unsigned __int64)
{
    LIFT_STUB(0x2bd1b0);
}

// 0x2bd280
void __cdecl PartyBattleVoteCastTask::start(void)
{
    LIFT_STUB(0x2bd280);
}

// 0x2bd3f0
__cdecl ChangeWeaponAppearanceTask::ChangeWeaponAppearanceTask(void)
{
    LIFT_STUB(0x2bd3f0);
}

// 0x2bd490
__cdecl ChangeWeaponAppearanceTask::~ChangeWeaponAppearanceTask(void)
{
    LIFT_STUB(0x2bd490);
}

// 0x2bd560
bool __cdecl ChangeWeaponAppearanceTask::InitializeForTry(::Zone *, ::Pc *, ::ChangeWeaponAppearanceTaskTryParam const *)
{
    LIFT_STUB(0x2bd560);
}

// 0x2bd6c0
bool __cdecl ChangeWeaponAppearanceTask::InitializeForOk(::Zone *, ::Pc *, ::ChangeWeaponAppearanceTaskOkParam const *)
{
    LIFT_STUB(0x2bd6c0);
}

// 0x2bd860
bool __cdecl ChangeWeaponAppearanceTask::InitializeForFail(::Zone *, ::Pc *, ::ChangeWeaponAppearanceTaskFailParam const *)
{
    LIFT_STUB(0x2bd860);
}

// 0x2bda30
void __cdecl ChangeWeaponAppearanceTask::TimerExpired(unsigned int, long)
{
    LIFT_STUB(0x2bda30);
}

// 0x2bda70
void __cdecl ChangeWeaponAppearanceTask::start(void)
{
    LIFT_STUB(0x2bda70);
}

// 0x2bdc40
bool __cdecl ChangeWeaponAppearanceTask::checkTryParam(::Pc *, ::ChangeWeaponAppearanceTaskTryParam const *)
{
    LIFT_STUB(0x2bdc40);
}

// 0x2be0f0
short __cdecl ChangeWeaponAppearanceTask::processChangeWeaponAppearanceTry(::Pc *, ::User *)
{
    LIFT_STUB(0x2be0f0);
}

// 0x2be660
void __cdecl ChangeWeaponAppearanceTask::processChangeWeaponAppearanceOk(::Pc *)
{
    LIFT_STUB(0x2be660);
}

// 0x2be8b0
void __cdecl ChangeWeaponAppearanceTask::processChangeWeaponAppearanceFail(::Pc *)
{
    LIFT_STUB(0x2be8b0);
}

// 0x2bebb0
bool __cdecl ChangeWeaponAppearanceTask::checkTargetWeapon(::Pc *, unsigned __int64 &, int &, char &, ::Data::ItemRecordWeaponPtr &, ::Data::WeaponAppearanceChangeCostRecordPtr &, ::ChangeWeaponAppearanceTranLogInfo &)
{
    LIFT_STUB(0x2bebb0);
}

// 0x2bf040
bool __cdecl ChangeWeaponAppearanceTask::checkApplyingWeapon(::Pc *, int, char, ::Data::ItemRecordWeaponPtr, int &, char &, ::ChangeWeaponAppearanceTranLogInfo &)
{
    LIFT_STUB(0x2bf040);
}

// 0x2bf4f0
bool __cdecl ChangeWeaponAppearanceTask::checkCostItem(::Pc *, ::Data::WeaponAppearanceChangeCostRecordPtr, ::ChangeWeaponAppearanceTranLogInfo &)
{
    LIFT_STUB(0x2bf4f0);
}

// 0x2bf730
bool __cdecl ChangeWeaponAppearanceTask::checkCostMoney(::Pc *, ::Data::WeaponAppearanceChangeCostRecordPtr, int &, ::ChangeWeaponAppearanceTranLogInfo &)
{
    LIFT_STUB(0x2bf730);
}

// 0x2bf9a0
bool __cdecl ChangeWeaponAppearanceTask::startTransaction(::Pc *, ::User *, unsigned __int64, int, char, int, ::ChangeWeaponAppearanceTranLogInfo *, ::Item *, unsigned __int64)
{
    LIFT_STUB(0x2bf9a0);
}

// 0x2c0300
bool __cdecl FeedPetFoodTask::Initialize(::Zone *, ::Creature *, unsigned char, unsigned short, unsigned short, unsigned char)
{
    LIFT_STUB(0x2c0300);
}

// 0x2c03f0
void __cdecl FeedPetFoodTask::TimerExpired(unsigned int, long)
{
    LIFT_STUB(0x2c03f0);
}

// 0x2c0430
void __cdecl FeedPetFoodTask::start(void)
{
    LIFT_STUB(0x2c0430);
}

// 0x2c05a0
bool __cdecl DuelBotTrainingRoomPickDuelBotTask::Initialize(::Zone *, ::Creature *, int, char)
{
    LIFT_STUB(0x2c05a0);
}

// 0x2c06e0
void __cdecl DuelBotTrainingRoomPickDuelBotTask::start(void)
{
    LIFT_STUB(0x2c06e0);
}

// 0x2c08e0
void __cdecl DuelBotTrainingRoomCombatTask::start(void)
{
    LIFT_STUB(0x2c08e0);
}

// 0x2c0e60
__cdecl DuelBotTrainingRoomRewardTask::DuelBotTrainingRoomRewardTask(void)
{
    LIFT_STUB(0x2c0e60);
}

// 0x2c0f40
__cdecl DuelBotTrainingRoomRewardTask::~DuelBotTrainingRoomRewardTask(void)
{
    LIFT_STUB(0x2c0f40);
}

// 0x2c0fa0
bool __cdecl DuelBotTrainingRoomRewardTask::InitializeForTry(::Zone *, ::Creature *, ::DuelBotTrainingRoomRewardTran *)
{
    LIFT_STUB(0x2c0fa0);
}

// 0x2c1280
bool __cdecl DuelBotTrainingRoomRewardTask::InitializeForOk(::Zone *, ::Creature *, short, char, char, int, short, unsigned __int64 *const, unsigned __int64 *const, ::DuelBotTrainingRoomRewardTran *)
{
    LIFT_STUB(0x2c1280);
}

// 0x2c1470
bool __cdecl DuelBotTrainingRoomRewardTask::InitializeForFail(::Zone *, ::Creature *, short, char, char, int, ::PropertyTransactionFailParam *, ::DuelBotTrainingRoomRewardTran *)
{
    LIFT_STUB(0x2c1470);
}

// 0x2c1690
void __cdecl DuelBotTrainingRoomRewardTask::TimerExpired(unsigned int, long)
{
    LIFT_STUB(0x2c1690);
}

// 0x2c16d0
void __cdecl DuelBotTrainingRoomRewardTask::start(void)
{
    LIFT_STUB(0x2c16d0);
}

// 0x2c23b0
__cdecl DuelBotTrainingRoomResultTask::DuelBotTrainingRoomResultTask(void)
{
    LIFT_STUB(0x2c23b0);
}

// 0x2c2430
bool __cdecl DuelBotTrainingRoomResultTask::Initialize(::Zone *, ::Pc *, bool, short, ::DuelBotTrainingRoomScoreContainer::DuelBotTrainingRoomScoreValue const *)
{
    LIFT_STUB(0x2c2430);
}
