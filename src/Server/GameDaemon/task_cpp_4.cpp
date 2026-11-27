// task_cpp_4.cpp: task.cpp part 4 (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "task.h"
#include "creature.h"
#include "inventory.h"
#include "pc.h"
#include "propertytran.h"
#include "seasonscore.h"
#include "zone.h"
#include "LiftStub.h"

// 0x2c24d0
void __cdecl DuelBotTrainingRoomResultTask::TimerExpired(unsigned int, long)
{
    LIFT_STUB(0x2c24d0);
}

// 0x2c2510
void __cdecl DuelBotTrainingRoomResultTask::start(void)
{
    LIFT_STUB(0x2c2510);
}

// 0x2c2630
__cdecl DuelBotTrainingRoomRewardHandlerTask::DuelBotTrainingRoomRewardHandlerTask(void)
{
    LIFT_STUB(0x2c2630);
}

// 0x2c26a0
bool __cdecl DuelBotTrainingRoomRewardHandlerTask::Initialize(::Zone *, ::Pc *, char, char, char)
{
    LIFT_STUB(0x2c26a0);
}

// 0x2c2760
void __cdecl DuelBotTrainingRoomRewardHandlerTask::TimerExpired(unsigned int, long)
{
    LIFT_STUB(0x2c2760);
}

// 0x2c27a0
void __cdecl DuelBotTrainingRoomRewardHandlerTask::start(void)
{
    LIFT_STUB(0x2c27a0);
}

// 0x2c2e40
bool __cdecl DuelBotChallengeCombatTask::Initialize(::Zone *, ::Creature *, unsigned __int64)
{
    LIFT_STUB(0x2c2e40);
}

// 0x2c2f00
void __cdecl DuelBotChallengeCombatTask::start(void)
{
    LIFT_STUB(0x2c2f00);
}

// 0x2c3430
bool __cdecl DuelBotChallengeStrategicToolTask::Initialize(::Zone *, ::Creature *, ::DuelBotChallengeStrategicToolTask::DuelBotChallengeStrategicToolAction, unsigned __int64, char)
{
    LIFT_STUB(0x2c3430);
}

// 0x2c3510
void __cdecl DuelBotChallengeStrategicToolTask::start(void)
{
    LIFT_STUB(0x2c3510);
}

// 0x2c3590
void __cdecl TakeAttractionRewardTask::start(void)
{
    LIFT_STUB(0x2c3590);
}

// 0x2c35e0
void __cdecl ReviveByAttractionRuleTask::start(void)
{
    LIFT_STUB(0x2c35e0);
}

// 0x2c3630
bool __cdecl EnterAttractionZoneTask::Initialize(::Zone *, ::Creature *, char, char, short, ::Inventory::DisposeOrderWithPos *const)
{
    LIFT_STUB(0x2c3630);
}

// 0x2c37d0
void __cdecl EnterAttractionZoneTask::start(void)
{
    LIFT_STUB(0x2c37d0);
}

// 0x2c3f20
::GameFailReason __cdecl EnterAttractionZoneTask::checkChallengePartyAttraction(unsigned __int64 &, short &, ::Inventory::DisposeOrderWithPos *const)
{
    LIFT_STUB(0x2c3f20);
}

// 0x2c4450
bool __cdecl EnterAttractionZoneTask::chkeckConsumeItems(int, unsigned __int64 const *const, short const *const, short &, ::Inventory::DisposeOrderWithPos *const)
{
    LIFT_STUB(0x2c4450);
}

// 0x2c4a40
bool __cdecl LeaveAttractionZoneTask::Initialize(::Zone *, ::Creature *)
{
    LIFT_STUB(0x2c4a40);
}

// 0x2c4af0
void __cdecl LeaveAttractionZoneTask::start(void)
{
    LIFT_STUB(0x2c4af0);
}

// 0x2c4c60
__cdecl DuelResultTask::DuelResultTask(void)
{
    LIFT_STUB(0x2c4c60);
}

// 0x2c4d20
__cdecl DuelResultTask::~DuelResultTask(void)
{
    LIFT_STUB(0x2c4d20);
}

// 0x2c4d90
bool __cdecl DuelResultTask::Initialize(::Zone *, ::Pc *, char, bool, ::SeasonContentsCombatRecordContainer::SeasonContentsCombatRecordValue const *, bool, ::DuelResultTranResultNotifyInfo const *)
{
    LIFT_STUB(0x2c4d90);
}

// 0x2c5030
void __cdecl DuelResultTask::TimerExpired(unsigned int, long)
{
    LIFT_STUB(0x2c5030);
}

// 0x2c5070
void __cdecl DuelResultTask::start(void)
{
    LIFT_STUB(0x2c5070);
}

// 0x2c5450
__cdecl PartyBattleResultTask::PartyBattleResultTask(void)
{
    LIFT_STUB(0x2c5450);
}

// 0x2c5510
__cdecl PartyBattleResultTask::~PartyBattleResultTask(void)
{
    LIFT_STUB(0x2c5510);
}

// 0x2c5580
bool __cdecl PartyBattleResultTask::Initialize(::Zone *, ::Pc *, char, bool, ::SeasonContentsCombatRecordContainer::SeasonContentsCombatRecordValue const *, bool, ::PartyBattleResultTranResultNotifyInfo const *)
{
    LIFT_STUB(0x2c5580);
}

// 0x2c5800
void __cdecl PartyBattleResultTask::TimerExpired(unsigned int, long)
{
    LIFT_STUB(0x2c5800);
}

// 0x2c5840
void __cdecl PartyBattleResultTask::start(void)
{
    LIFT_STUB(0x2c5840);
}

// 0x2c5ac0
__cdecl TimeAttackRecordResultTask::TimeAttackRecordResultTask(void)
{
    LIFT_STUB(0x2c5ac0);
}

// 0x2c5b70
__cdecl TimeAttackRecordResultTask::~TimeAttackRecordResultTask(void)
{
    LIFT_STUB(0x2c5b70);
}

// 0x2c5be0
bool __cdecl TimeAttackRecordResultTask::Initialize(::Zone *, ::Pc *, char, bool, ::SeasonContentsTimeAttackRecordContainer::SeasonContentsTimeAttackRecordValue const *, bool, ::TimeAttackRecordResultTranResultNotifyInfo const *)
{
    LIFT_STUB(0x2c5be0);
}

// 0x2c5e40
void __cdecl TimeAttackRecordResultTask::TimerExpired(unsigned int, long)
{
    LIFT_STUB(0x2c5e40);
}

// 0x2c5e80
void __cdecl TimeAttackRecordResultTask::start(void)
{
    LIFT_STUB(0x2c5e80);
}

// 0x2c6020
__cdecl InitailizeSeasonContentsInfoTask::InitailizeSeasonContentsInfoTask(void)
{
    LIFT_STUB(0x2c6020);
}

// 0x2c60f0
bool __cdecl InitailizeSeasonContentsInfoTask::InitializeReq(::Zone *, ::Pc *, char, char const *const)
{
    LIFT_STUB(0x2c60f0);
}

// 0x2c61c0
bool __cdecl InitailizeSeasonContentsInfoTask::InitializeOk(::Zone *, ::Pc *, short, ::InitCombatResultList *const, short, ::InitTimeAttackResultList *const)
{
    LIFT_STUB(0x2c61c0);
}

// 0x2c62f0
void __cdecl InitailizeSeasonContentsInfoTask::start(void)
{
    LIFT_STUB(0x2c62f0);
}

// 0x2c6360
void __cdecl InitailizeSeasonContentsInfoTask::ok(void)
{
    LIFT_STUB(0x2c6360);
}

// 0x2c6440
void __cdecl InitailizeSeasonContentsInfoTask::TimerExpired(unsigned int, long)
{
    LIFT_STUB(0x2c6440);
}

// 0x2c6480
void __cdecl SeasonContentsInfoTask::start(void)
{
    LIFT_STUB(0x2c6480);
}

// 0x2c6790
void __cdecl AddBotScoreStateTask::start(void)
{
    LIFT_STUB(0x2c6790);
}

// 0x2c6860
void __cdecl RefreshSimpleQuestPackTask::start(void)
{
    LIFT_STUB(0x2c6860);
}

// 0x2c6a30
bool __cdecl SkillTrainingRoomCombatStartTask::Initialize(::Zone *, ::Creature *, unsigned __int64, char)
{
    LIFT_STUB(0x2c6a30);
}

// 0x2c6b10
void __cdecl SkillTrainingRoomCombatStartTask::start(void)
{
    LIFT_STUB(0x2c6b10);
}

// 0x2c6be0
bool __cdecl SkillTrainingRoomCombatStopTask::Initialize(::Zone *, ::Creature *, char)
{
    LIFT_STUB(0x2c6be0);
}

// 0x2c6cb0
void __cdecl SkillTrainingRoomCombatStopTask::start(void)
{
    LIFT_STUB(0x2c6cb0);
}

// 0x2c6d80
void __cdecl SkillTrainingRoomCombatRestartTask::start(void)
{
    LIFT_STUB(0x2c6d80);
}

// 0x2c6e40
void __cdecl SkillTrainingRoomInitCreatureStateTask::start(void)
{
    LIFT_STUB(0x2c6e40);
}

// 0x2c6f00
void __cdecl EnterSkillTrainingRoomTask::start(void)
{
    LIFT_STUB(0x2c6f00);
}

// 0x2c75d0
__cdecl TakeAchievementRewardTask::TakeAchievementRewardTask(void)
{
    LIFT_STUB(0x2c75d0);
}

// 0x2c76e0
void __cdecl TakeAchievementRewardTask::TimerExpired(unsigned int, long)
{
    LIFT_STUB(0x2c76e0);
}

// 0x2c7720
void __cdecl TakeAchievementRewardTask::start(void)
{
    LIFT_STUB(0x2c7720);
}

// 0x2c7760
bool __cdecl TakeAchievementRewardTask::Initialize(::Zone *, ::Creature *, __int64, short, short)
{
    LIFT_STUB(0x2c7760);
}

// 0x2c7830
void __cdecl TakeAchievementRewardTask::processTry(void)
{
    LIFT_STUB(0x2c7830);
}

// 0x2c7f30
bool __cdecl TakeAchievementRewardTask::InitializeForOk(::Zone *, ::Creature *, ::TakeAchievementRewardTranOkParam *)
{
    LIFT_STUB(0x2c7f30);
}

// 0x2c8090
void __cdecl TakeAchievementRewardTask::processOk(void)
{
    LIFT_STUB(0x2c8090);
}

// 0x2c8980
bool __cdecl TakeAchievementRewardTask::InitializeForFail(::Zone *, ::Creature *, short, ::TakeAchievementRewardTranFailParam *)
{
    LIFT_STUB(0x2c8980);
}

// 0x2c8ae0
void __cdecl TakeAchievementRewardTask::processFail(void)
{
    LIFT_STUB(0x2c8ae0);
}

// 0x2c8f40
void __cdecl FinishTakeAchievementRewardTask::TimerExpired(unsigned int, long)
{
    LIFT_STUB(0x2c8f40);
}

// 0x2c8f80
void __cdecl FinishTakeAchievementRewardTask::start(void)
{
    LIFT_STUB(0x2c8f80);
}

// 0x2c9350
void __cdecl SpecialSkillGaugeTask::TimerExpired(unsigned int, long)
{
    LIFT_STUB(0x2c9350);
}

// 0x2c9390
void __cdecl SpecialSkillGaugeTask::start(void)
{
    LIFT_STUB(0x2c9390);
}

// 0x2c9550
__cdecl RegisterCraftTask::RegisterCraftTask(void)
{
    LIFT_STUB(0x2c9550);
}

// 0x2c9650
bool __cdecl RegisterCraftTask::InitializeForTry(::Zone *, ::Creature *, ::Packet const *)
{
    LIFT_STUB(0x2c9650);
}

// 0x2c99e0
bool __cdecl RegisterCraftTask::InitializeForOk(::Zone *, ::Creature *, ::RegisterCraftOkParam &)
{
    LIFT_STUB(0x2c99e0);
}

// 0x2c9c70
bool __cdecl RegisterCraftTask::InitializeForFail(::Zone *, ::Creature *, ::FragmentPacketConcatenater *)
{
    LIFT_STUB(0x2c9c70);
}

// 0x2c9f30
void __cdecl RegisterCraftTask::TimerExpired(unsigned int, long)
{
    LIFT_STUB(0x2c9f30);
}

// 0x2c9f70
bool __cdecl RegisterCraftTask::makeConsumptionParam(::PropertyTransactionSyncFetchEx &, int, short, ::CraftOutput *const)
{
    LIFT_STUB(0x2c9f70);
}

// 0x2ca720
void __cdecl RegisterCraftTask::RegisterCraftReq(void)
{
    LIFT_STUB(0x2ca720);
}

// 0x2caa20
void __cdecl RegisterCraftTask::RegisterCraftOk(void)
{
    LIFT_STUB(0x2caa20);
}

// 0x2cac60
void __cdecl RegisterCraftTask::RegisterCraftFail(void)
{
    LIFT_STUB(0x2cac60);
}

// 0x2cb1b0
void __cdecl RegisterCraftTask::start(void)
{
    LIFT_STUB(0x2cb1b0);
}

// 0x2cb230
short __cdecl RegisterCraftTask::checkRecipe(void)
{
    LIFT_STUB(0x2cb230);
}

// 0x2cb4b0
short __cdecl RegisterCraftTask::checkMaterial(void)
{
    LIFT_STUB(0x2cb4b0);
}

// 0x2cb600
short __cdecl RegisterCraftTask::checkMaterialItem(::Data::ItemRecordPtr &, short, short &)
{
    LIFT_STUB(0x2cb600);
}

// 0x2cb950
short __cdecl RegisterCraftTask::checkMaterialItemBrand(::Data::ItemBrandRecordPtr &, char, short &)
{
    LIFT_STUB(0x2cb950);
}

// 0x2cbc80
bool __cdecl RegisterCraftTask::simulation(short &, ::CraftOutput *const)
{
    LIFT_STUB(0x2cbc80);
}

// 0x2cbe80
__cdecl TakeCraftTask::TakeCraftTask(void)
{
    LIFT_STUB(0x2cbe80);
}

// 0x2cbf20
bool __cdecl TakeCraftTask::InitializeForTry(::Zone *, ::Creature *, unsigned __int64)
{
    LIFT_STUB(0x2cbf20);
}

// 0x2cc040
bool __cdecl TakeCraftTask::InitializeForOk(::Zone *, ::Creature *, ::TakeCraftOkParam &)
{
    LIFT_STUB(0x2cc040);
}

// 0x2cc200
bool __cdecl TakeCraftTask::InitializeForFail(::Zone *, ::Creature *, ::TakeCraftFailParam &)
{
    LIFT_STUB(0x2cc200);
}

// 0x2cc300
void __cdecl TakeCraftTask::TimerExpired(unsigned int, long)
{
    LIFT_STUB(0x2cc300);
}

// 0x2cc340
void __cdecl TakeCraftTask::start(void)
{
    LIFT_STUB(0x2cc340);
}

// 0x2cc3c0
void __cdecl TakeCraftTask::TakeCraftReq(void)
{
    LIFT_STUB(0x2cc3c0);
}

// 0x2cc900
void __cdecl TakeCraftTask::TakeCraftOk(void)
{
    LIFT_STUB(0x2cc900);
}

// 0x2ccc90
void __cdecl TakeCraftTask::TakeCraftFail(void)
{
    LIFT_STUB(0x2ccc90);
}

// 0x2cd0f0
__cdecl JoinCraftUnionTask::JoinCraftUnionTask(void)
{
    LIFT_STUB(0x2cd0f0);
}

// 0x2cd160
bool __cdecl JoinCraftUnionTask::InitializeForTry(::Zone *, ::Creature *, char, __int64)
{
    LIFT_STUB(0x2cd160);
}

// 0x2cd2d0
bool __cdecl JoinCraftUnionTask::InitializeForOk(::Zone *, ::Creature *, char)
{
    LIFT_STUB(0x2cd2d0);
}

// 0x2cd3d0
void __cdecl JoinCraftUnionTask::TimerExpired(unsigned int, long)
{
    LIFT_STUB(0x2cd3d0);
}

// 0x2cd410
void __cdecl JoinCraftUnionTask::start(void)
{
    LIFT_STUB(0x2cd410);
}

// 0x2cd480
void __cdecl JoinCraftUnionTask::JoinCraftUnionReq(void)
{
    LIFT_STUB(0x2cd480);
}

// 0x2cde70
void __cdecl JoinCraftUnionTask::JoinCraftUnionOk(void)
{
    LIFT_STUB(0x2cde70);
}

// 0x2cdfe0
__cdecl LeaveCraftUnionTask::LeaveCraftUnionTask(void)
{
    LIFT_STUB(0x2cdfe0);
}

// 0x2ce050
bool __cdecl LeaveCraftUnionTask::InitializeForTry(::Zone *, ::Creature *, char)
{
    LIFT_STUB(0x2ce050);
}

// 0x2ce160
bool __cdecl LeaveCraftUnionTask::InitializeForOk(::Zone *, ::Creature *, char)
{
    LIFT_STUB(0x2ce160);
}

// 0x2ce260
void __cdecl LeaveCraftUnionTask::TimerExpired(unsigned int, long)
{
    LIFT_STUB(0x2ce260);
}

// 0x2ce2a0
void __cdecl LeaveCraftUnionTask::start(void)
{
    LIFT_STUB(0x2ce2a0);
}

// 0x2ce310
void __cdecl LeaveCraftUnionTask::LeaveCraftUnionReq(void)
{
    LIFT_STUB(0x2ce310);
}

// 0x2ceb60
void __cdecl LeaveCraftUnionTask::LeaveCraftUnionOk(void)
{
    LIFT_STUB(0x2ceb60);
}

// 0x2cecd0
bool __cdecl UseEquippedTask::Initialize(::Zone *, ::Creature *, short, short, short, short, short)
{
    LIFT_STUB(0x2cecd0);
}

// 0x2ced70
void __cdecl UseEquippedTask::start(void)
{
    LIFT_STUB(0x2ced70);
}

// 0x2cf180
void __cdecl ResetCombatModeTask::start(void)
{
    LIFT_STUB(0x2cf180);
}

// 0x2cf5a0
void __cdecl PublicRaidEventAddScoreTask::start(void)
{
    LIFT_STUB(0x2cf5a0);
}

// 0x2cf8e0
void __cdecl SkillSkinAcquiredListTask::start(void)
{
    LIFT_STUB(0x2cf8e0);
}

// 0x2cfaa0
bool __cdecl ApplySkillSkinTask::Initialize(::Zone *, ::Creature *, short)
{
    LIFT_STUB(0x2cfaa0);
}

// 0x2cfb40
void __cdecl ApplySkillSkinTask::start(void)
{
    LIFT_STUB(0x2cfb40);
}

// 0x2cfd20
void __cdecl ChangeWarFieldStepTask::start(void)
{
    LIFT_STUB(0x2cfd20);
}

// 0x2cfe90
void __cdecl IPsoTranTask::TimerExpired(unsigned int, long)
{
    LIFT_STUB(0x2cfe90);
}

// 0x2cfed0
bool __cdecl CreateChallengePartyStartTask::Initialize(::Zone *, ::Creature *, void *)
{
    LIFT_STUB(0x2cfed0);
}

// 0x2cfff0
void __cdecl CreateChallengePartyStartTask::start(void)
{
    LIFT_STUB(0x2cfff0);
}

// 0x2d02d0
bool __cdecl CreateChallengePartyOkFromCacheTask::Initialize(::Zone *, ::Creature *, void *)
{
    LIFT_STUB(0x2d02d0);
}

// 0x2d03e0
void __cdecl CreateChallengePartyOkFromCacheTask::start(void)
{
    LIFT_STUB(0x2d03e0);
}

// 0x2d05d0
bool __cdecl CreateChallengePartyFailFromCacheTask::Initialize(::Zone *, ::Creature *, void *)
{
    LIFT_STUB(0x2d05d0);
}
