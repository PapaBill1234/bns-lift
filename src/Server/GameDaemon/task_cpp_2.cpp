// task_cpp_2.cpp: task.cpp part 2 (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "task.h"
#include "achievementdata.h"
#include "creature.h"
#include "instantpaymenttran.h"
#include "inventory.h"
#include "item.h"
#include "pc.h"
#include "tendencymanager.h"
#include "zone.h"
#include "LiftStub.h"

// 0x2a0730
void __cdecl ArenaEventReturnToArenaLobbyAllPcTask::start(void)
{
    LIFT_STUB(0x2a0730);
}

// 0x2a0b10
bool __cdecl ArenaEventRetreivePcAssetTask::Initialize(::Zone *, ::Pc *, ::Pc *)
{
    LIFT_STUB(0x2a0b10);
}

// 0x2a0bc0
void __cdecl ArenaEventRetreivePcAssetTask::start(void)
{
    LIFT_STUB(0x2a0bc0);
}

// 0x2a0da0
bool __cdecl ArenaEventWarpToDuelRoundStartPcSpawnTask::Initialize(::Zone *, ::Pc *, char)
{
    LIFT_STUB(0x2a0da0);
}

// 0x2a0e40
void __cdecl ArenaEventWarpToDuelRoundStartPcSpawnTask::start(void)
{
    LIFT_STUB(0x2a0e40);
}

// 0x2a1050
bool __cdecl ArenaEventInZonePcLocTask::Initialize(::Zone *, ::Pc *)
{
    LIFT_STUB(0x2a1050);
}

// 0x2a10d0
void __cdecl ArenaEventInZonePcLocTask::start(void)
{
    LIFT_STUB(0x2a10d0);
}

// 0x2a12b0
bool __cdecl ArenaEventBattleRoyalScoreTask::Initialize(::Zone *, ::Pc *)
{
    LIFT_STUB(0x2a12b0);
}

// 0x2a1340
void __cdecl ArenaEventBattleRoyalScoreTask::start(void)
{
    LIFT_STUB(0x2a1340);
}

// 0x2a1540
bool __cdecl SkillScoreNotifyTask::Initialize(::Zone *, ::Creature *)
{
    LIFT_STUB(0x2a1540);
}

// 0x2a15d0
void __cdecl SkillScoreNotifyTask::start(void)
{
    LIFT_STUB(0x2a15d0);
}

// 0x2a15f0
bool __cdecl KillSummonedTask::Initialize(::Zone *, ::Creature *)
{
    LIFT_STUB(0x2a15f0);
}

// 0x2a1680
void __cdecl KillSummonedTask::start(void)
{
    LIFT_STUB(0x2a1680);
}

// 0x2a1750
bool __cdecl AutoLogoutCheckTask::Initialize(::Zone *, ::Creature *)
{
    LIFT_STUB(0x2a1750);
}

// 0x2a17e0
void __cdecl AutoLogoutCheckTask::start(void)
{
    LIFT_STUB(0x2a17e0);
}

// 0x2a1b10
void __cdecl RechargeVitalityTask::start(void)
{
    LIFT_STUB(0x2a1b10);
}

// 0x2a1c30
bool __cdecl ChangeGradeTask::Initialize(::Zone *, ::Pc *, int, ::GradeInfo &, char)
{
    LIFT_STUB(0x2a1c30);
}

// 0x2a1d20
void __cdecl ChangeGradeTask::TimerExpired(unsigned int, long)
{
    LIFT_STUB(0x2a1d20);
}

// 0x2a1d60
void __cdecl ChangeGradeTask::start(void)
{
    LIFT_STUB(0x2a1d60);
}

// 0x2a2130
bool __cdecl ChangeGradeLevelTask::Initialize(::Zone *, ::Pc *, int, ::GradeLevelInfo &)
{
    LIFT_STUB(0x2a2130);
}

// 0x2a2210
void __cdecl ChangeGradeLevelTask::TimerExpired(unsigned int, long)
{
    LIFT_STUB(0x2a2210);
}

// 0x2a2250
void __cdecl ChangeGradeLevelTask::start(void)
{
    LIFT_STUB(0x2a2250);
}

// 0x2a2660
bool __cdecl ActivateAllGradeTask::Initialize(::Zone *, ::Pc *, int, ::GradeLevelInfo &, ::GradeInfo *const, short)
{
    LIFT_STUB(0x2a2660);
}

// 0x2a27a0
void __cdecl ActivateAllGradeTask::TimerExpired(unsigned int, long)
{
    LIFT_STUB(0x2a27a0);
}

// 0x2a27e0
void __cdecl ActivateAllGradeTask::start(void)
{
    LIFT_STUB(0x2a27e0);
}

// 0x2a2c00
void __cdecl AchievementPcRelogin::TimerExpired(unsigned int, long)
{
    LIFT_STUB(0x2a2c00);
}

// 0x2a2c40
void __cdecl AchievementPcRelogin::start(void)
{
    LIFT_STUB(0x2a2c40);
}

// 0x2a2f90
__cdecl UpdateAchievementListTask::~UpdateAchievementListTask(void)
{
    LIFT_STUB(0x2a2f90);
}

// 0x2a3010
bool __cdecl UpdateAchievementListTask::Initialize(::Zone *, ::Pc *, ::AchievementData *)
{
    LIFT_STUB(0x2a3010);
}

// 0x2a30e0
void __cdecl UpdateAchievementListTask::TimerExpired(unsigned int, long)
{
    LIFT_STUB(0x2a30e0);
}

// 0x2a3120
void __cdecl UpdateAchievementListTask::start(void)
{
    LIFT_STUB(0x2a3120);
}

// 0x2a31f0
void __cdecl AchievementTitleInstallTask::start(void)
{
    LIFT_STUB(0x2a31f0);
}

// 0x2a33c0
void __cdecl AchievementAbilityInstallTask::start(void)
{
    LIFT_STUB(0x2a33c0);
}

// 0x2a3730
bool __cdecl BindRaidDungeonTask::Initialize(::Zone *, ::Creature *, unsigned __int64, unsigned __int64, char)
{
    LIFT_STUB(0x2a3730);
}

// 0x2a3810
void __cdecl BindRaidDungeonTask::TimerExpired(unsigned int, long)
{
    LIFT_STUB(0x2a3810);
}

// 0x2a3860
void __cdecl BindRaidDungeonTask::start(void)
{
    LIFT_STUB(0x2a3860);
}

// 0x2a3c80
__cdecl UnbindRaidDungeonTask::UnbindRaidDungeonTask(void)
{
    LIFT_STUB(0x2a3c80);
}

// 0x2a3d30
bool __cdecl UnbindRaidDungeonTask::Initialize(::Zone *, ::Creature *, unsigned __int64, int, ::Inventory::DisposeOrderWithPos *const)
{
    LIFT_STUB(0x2a3d30);
}

// 0x2a3e20
void __cdecl UnbindRaidDungeonTask::start(void)
{
    LIFT_STUB(0x2a3e20);
}

// 0x2a5630
bool __cdecl RetrieveBoundRaidDungeonInfoTask::Initialize(::Zone *, ::Creature *, unsigned __int64)
{
    LIFT_STUB(0x2a5630);
}

// 0x2a5700
void __cdecl RetrieveBoundRaidDungeonInfoTask::start(void)
{
    LIFT_STUB(0x2a5700);
}

// 0x2a5c30
bool __cdecl InitializeRaidDungeonInfoTask::Initialize(::Zone *, ::Creature *, bool)
{
    LIFT_STUB(0x2a5c30);
}

// 0x2a5d00
void __cdecl InitializeRaidDungeonInfoTask::start(void)
{
    LIFT_STUB(0x2a5d00);
}

// 0x2a5dc0
bool __cdecl GuildBattleFieldZoneCloseTask::Initialize(::Zone *)
{
    LIFT_STUB(0x2a5dc0);
}

// 0x2a5e50
void __cdecl GuildBattleFieldZoneCloseTask::TimerExpired(unsigned int, long)
{
    LIFT_STUB(0x2a5e50);
}

// 0x2a5ed0
__cdecl TendencyEventTask::TendencyEventTask(void)
{
    LIFT_STUB(0x2a5ed0);
}

// 0x2a5f70
bool __cdecl TendencyEventTask::Initialize(::Zone *, ::TendencyField::EventData const &)
{
    LIFT_STUB(0x2a5f70);
}

// 0x2a6010
bool __cdecl TendencyEventTask::Initialize(::Zone *, int, unsigned __int64, int, __int64, __int64, char)
{
    LIFT_STUB(0x2a6010);
}

// 0x2a6110
void __cdecl TendencyEventTask::TimerExpired(unsigned int, long)
{
    LIFT_STUB(0x2a6110);
}

// 0x2a62c0
void __cdecl RandomStoreInfoTask::start(void)
{
    LIFT_STUB(0x2a62c0);
}

// 0x2a62f0
__cdecl RandomStoreDrawTask::~RandomStoreDrawTask(void)
{
    LIFT_STUB(0x2a62f0);
}

// 0x2a6350
bool __cdecl RandomStoreDrawTask::Initialize(::Zone *const, ::Pc *const, char, char, char, int, ::RandomStoreDrawTask::ConsumeOrder const *const)
{
    LIFT_STUB(0x2a6350);
}

// 0x2a6620
bool __cdecl RandomStoreDrawTask::Initialize(::Zone *const, ::Pc *const, char, char, char, ::RandomStoreDrawTask::Operation, ::InstantPaymentTran *const, __int64)
{
    LIFT_STUB(0x2a6620);
}

// 0x2a6830
void __cdecl RandomStoreDrawTask::ProcessUnexpired(int)
{
    LIFT_STUB(0x2a6830);
}

// 0x2a68b0
void __cdecl RandomStoreDrawTask::TimerExpired(unsigned int, long)
{
    LIFT_STUB(0x2a68b0);
}

// 0x2a68f0
void __cdecl RandomStoreDrawTask::start(void)
{
    LIFT_STUB(0x2a68f0);
}

// 0x2a6920
short const __cdecl RandomStoreDrawTask::checkInstantPaymentCondition(void)
{
    LIFT_STUB(0x2a6920);
}

// 0x2a6b80
short const __cdecl RandomStoreDrawTask::checkApplyCondition(void)
{
    LIFT_STUB(0x2a6b80);
}

// 0x2a7460
void __cdecl RandomStoreDrawTask::tryInstantPayment(void)
{
    LIFT_STUB(0x2a7460);
}

// 0x2a75f0
void __cdecl RandomStoreDrawTask::apply(void)
{
    LIFT_STUB(0x2a75f0);
}

// 0x2a87d0
bool __cdecl ExpandRandomStoreSlotTask::Initialize(::Zone *const, ::Pc *const, char, char, char, int, ::ExpandRandomStoreSlotTask::DisposeOrder const *const)
{
    LIFT_STUB(0x2a87d0);
}

// 0x2a8a20
bool __cdecl ExpandRandomStoreSlotTask::Initialize(::Zone *const, ::Pc *const, char, char, char, ::ExpandRandomStoreSlotTask::Operation, ::InstantPaymentTran *const, __int64)
{
    LIFT_STUB(0x2a8a20);
}

// 0x2a8c60
void __cdecl ExpandRandomStoreSlotTask::ProcessUnexpired(int)
{
    LIFT_STUB(0x2a8c60);
}

// 0x2a8cf0
void __cdecl ExpandRandomStoreSlotTask::TimerExpired(unsigned int, long)
{
    LIFT_STUB(0x2a8cf0);
}

// 0x2a8d30
void __cdecl ExpandRandomStoreSlotTask::start(void)
{
    LIFT_STUB(0x2a8d30);
}

// 0x2a8d60
short const __cdecl ExpandRandomStoreSlotTask::checkInstantPaymentCondition(void)
{
    LIFT_STUB(0x2a8d60);
}

// 0x2a9350
short const __cdecl ExpandRandomStoreSlotTask::checkApplyCondition(void)
{
    LIFT_STUB(0x2a9350);
}

// 0x2a9510
void __cdecl ExpandRandomStoreSlotTask::tryInstantPayment(void)
{
    LIFT_STUB(0x2a9510);
}

// 0x2a96b0
void __cdecl ExpandRandomStoreSlotTask::apply(void)
{
    LIFT_STUB(0x2a96b0);
}

// 0x2aa240
bool __cdecl BuyRandomStoreItemTask::Initialize(::Zone *const, ::Pc *const, char, char, char, int, ::BuyRandomStoreItemTask::DisposeOrder const *const)
{
    LIFT_STUB(0x2aa240);
}

// 0x2aa470
void __cdecl BuyRandomStoreItemTask::start(void)
{
    LIFT_STUB(0x2aa470);
}

// 0x2ab9a0
bool __cdecl BuyRandomStoreItemTask::checkItemPrice(int, short)
{
    LIFT_STUB(0x2ab9a0);
}

// 0x2abd80
bool __cdecl TakeRandomStoreDrawRewardTask::Initialize(::Zone *const, ::Pc *const, char, char)
{
    LIFT_STUB(0x2abd80);
}

// 0x2abed0
void __cdecl TakeRandomStoreDrawRewardTask::start(void)
{
    LIFT_STUB(0x2abed0);
}

// 0x2ac870
void __cdecl TakeRandomStoreDrawRewardTask::writeGameLogGetRandomStoreDrawReward(::Pc *const, int, ::Data::RandomStoreDrawRewardRecordPtr, char, ::Inventory::AcquireOrder const *const)
{
    LIFT_STUB(0x2ac870);
}

// 0x2acaa0
void __cdecl ChangeToReplayQuestTask::start(void)
{
    LIFT_STUB(0x2acaa0);
}

// 0x2acb60
__cdecl PutItemIntoClosetTask::PutItemIntoClosetTask(void)
{
    LIFT_STUB(0x2acb60);
}

// 0x2acbf0
bool __cdecl PutItemIntoClosetTask::InitializeForTry(::Zone *, ::Creature *, short)
{
    LIFT_STUB(0x2acbf0);
}

// 0x2accf0
bool __cdecl PutItemIntoClosetTask::InitializeForOk(::Zone *, ::Creature *, int, char, short)
{
    LIFT_STUB(0x2accf0);
}

// 0x2acdd0
bool __cdecl PutItemIntoClosetTask::InitializeForFail(::Zone *, ::Creature *, short, unsigned __int64, char, int)
{
    LIFT_STUB(0x2acdd0);
}

// 0x2aceb0
bool __cdecl PutItemIntoClosetTask::rollbackItem(char)
{
    LIFT_STUB(0x2aceb0);
}

// 0x2acef0
void __cdecl PutItemIntoClosetTask::TimerExpired(unsigned int, long)
{
    LIFT_STUB(0x2acef0);
}

// 0x2acf30
void __cdecl PutItemIntoClosetTask::start(void)
{
    LIFT_STUB(0x2acf30);
}

// 0x2ad2f0
bool __cdecl PutItemIntoClosetTask::checkItem(void)
{
    LIFT_STUB(0x2ad2f0);
}

// 0x2ad8d0
bool __cdecl PutItemIntoClosetTask::makeTransaction(::Pc *)
{
    LIFT_STUB(0x2ad8d0);
}

// 0x2ae100
__cdecl TakeItemFromClosetTask::TakeItemFromClosetTask(void)
{
    LIFT_STUB(0x2ae100);
}

// 0x2ae1b0
bool __cdecl TakeItemFromClosetTask::InitializeForReqRetrieve(::Zone *, ::Creature *, int, short)
{
    LIFT_STUB(0x2ae1b0);
}

// 0x2ae2f0
bool __cdecl TakeItemFromClosetTask::InitializeForFailRetrieve(::Zone *, ::Creature *, int, short)
{
    LIFT_STUB(0x2ae2f0);
}

// 0x2ae400
bool __cdecl TakeItemFromClosetTask::InitializeForTry(::Zone *, ::Creature *, int, short, unsigned __int64, unsigned int, bool, bool, __int64, char, __int64, char *const)
{
    LIFT_STUB(0x2ae400);
}

// 0x2ae540
bool __cdecl TakeItemFromClosetTask::InitializeForOk(::Zone *, ::Creature *, int, short, unsigned __int64)
{
    LIFT_STUB(0x2ae540);
}

// 0x2ae620
bool __cdecl TakeItemFromClosetTask::InitializeForFail(::Zone *, ::Creature *, int, short, unsigned __int64, char)
{
    LIFT_STUB(0x2ae620);
}

// 0x2ae700
void __cdecl TakeItemFromClosetTask::TimerExpired(unsigned int, long)
{
    LIFT_STUB(0x2ae700);
}

// 0x2ae740
void __cdecl TakeItemFromClosetTask::start(void)
{
    LIFT_STUB(0x2ae740);
}

// 0x2aef70
bool __cdecl TakeItemFromClosetTask::makeTransaction(::Pc *, ::Item *)
{
    LIFT_STUB(0x2aef70);
}

// 0x2af430
__cdecl TakeRankingRewardTask::TakeRankingRewardTask(void)
{
    LIFT_STUB(0x2af430);
}

// 0x2af520
bool __cdecl TakeRankingRewardTask::InitializeForTry(::Zone *, ::Creature *, char, int, char, short, int, bool, int, int, bool)
{
    LIFT_STUB(0x2af520);
}

// 0x2af7f0
bool __cdecl TakeRankingRewardTask::InitializeForOk(::Zone *, ::Creature *, char, int, char, char, int, int, int, int, short, unsigned __int64 *const, unsigned __int64 *const)
{
    LIFT_STUB(0x2af7f0);
}

// 0x2afb20
bool __cdecl TakeRankingRewardTask::InitializeForFail(::Zone *, ::Creature *, char, int, char, char, int, int, int, int, ::PropertyTransactionFailParam *)
{
    LIFT_STUB(0x2afb20);
}

// 0x2afcc0
void __cdecl TakeRankingRewardTask::TimerExpired(unsigned int, long)
{
    LIFT_STUB(0x2afcc0);
}

// 0x2afd00
void __cdecl TakeRankingRewardTask::start(void)
{
    LIFT_STUB(0x2afd00);
}

// 0x2b10d0
__cdecl DepositMileageTask::DepositMileageTask(void)
{
    LIFT_STUB(0x2b10d0);
}

// 0x2b1170
__cdecl DepositMileageTask::~DepositMileageTask(void)
{
    LIFT_STUB(0x2b1170);
}

// 0x2b1240
bool __cdecl DepositMileageTask::InitializeForTry(::Zone *, ::Creature *, ::DepositMileageTaskTryParam const *)
{
    LIFT_STUB(0x2b1240);
}

// 0x2b1530
bool __cdecl DepositMileageTask::InitializeForOk(::Zone *, ::Creature *, ::DepositMileageTaskOkParam const *)
{
    LIFT_STUB(0x2b1530);
}

// 0x2b1760
bool __cdecl DepositMileageTask::InitializeForFail(::Zone *, ::Creature *, ::DepositMileageTaskFailParam const *)
{
    LIFT_STUB(0x2b1760);
}

// 0x2b19c0
void __cdecl DepositMileageTask::TimerExpired(unsigned int, long)
{
    LIFT_STUB(0x2b19c0);
}

// 0x2b1a00
bool __cdecl DepositMileageTask::checkTryParam(::Pc const *, ::DepositMileageTaskTryParam const *)
{
    LIFT_STUB(0x2b1a00);
}

// 0x2b1e00
short __cdecl DepositMileageTask::processDepositMileageTry(::Pc *)
{
    LIFT_STUB(0x2b1e00);
}

// 0x2b2980
void __cdecl DepositMileageTask::processDepositMileageOk(::Pc *)
{
    LIFT_STUB(0x2b2980);
}

// 0x2b2a80
void __cdecl DepositMileageTask::processDepositMileageFail(::Pc *)
{
    LIFT_STUB(0x2b2a80);
}

// 0x2b2bb0
void __cdecl DepositMileageTask::start(void)
{
    LIFT_STUB(0x2b2bb0);
}

// 0x2b2ce0
void __cdecl RetrieveMysteriousStoreTask::start(void)
{
    LIFT_STUB(0x2b2ce0);
}

// 0x2b2fb0
bool __cdecl InvitePcToPartyTask::Initialize(::Zone *, ::Creature *, unsigned __int64, unsigned __int64, unsigned int, char, char, char, char, char, char)
{
    LIFT_STUB(0x2b2fb0);
}

// 0x2b30e0
void __cdecl InvitePcToPartyTask::TimerExpired(unsigned int, long)
{
    LIFT_STUB(0x2b30e0);
}
