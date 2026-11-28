// pc_cpp_1.cpp: pc.cpp part 1 (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "pc.h"
#include "creature.h"
#include "item.h"
#include "gamedaemon.h"
#include "ruleconfig.h"
#include "LiftStub.h"

// 0x5d4bf0
__cdecl CraftInfo::CraftInfo(void)
{
    LIFT_STUB(0x5d4bf0);
}

// 0x5d4cc0
__cdecl CraftInfo::~CraftInfo(void)
{
    LIFT_STUB(0x5d4cc0);
}

// 0x5d4d30
bool __cdecl CraftInfo::TryToRegister(int, unsigned __int64, char, ::CraftOutput *, char, ::SyncContext *)
{
    LIFT_STUB(0x5d4d30);
}

// 0x5d4e00
bool __cdecl CraftInfo::TryToTake(::SyncContext &)
{
    LIFT_STUB(0x5d4e00);
}

// 0x5d4f80
void __cdecl CraftInfo::CancelToTake(void)
{
    LIFT_STUB(0x5d4f80);
}

// 0x5d50b0
void __cdecl SeasonContentsTimeAttackRecordContext::Init(::Pc *, char, __int64, short)
{
    LIFT_STUB(0x5d50b0);
}

// 0x5d5210
bool __cdecl SeasonContentsTimeAttackRecordContext::Start(short, __int64)
{
    LIFT_STUB(0x5d5210);
}

// 0x5d53e0
bool __cdecl SeasonContentsTimeAttackRecordContext::Progress(short, __int64)
{
    LIFT_STUB(0x5d53e0);
}

// 0x5d5680
bool __cdecl SeasonContentsTimeAttackRecordContext::End(void)
{
    LIFT_STUB(0x5d5680);
}

// 0x5d58a0
bool __cdecl SeasonContentsTimeAttackRecordContext::startTran(short, int)
{
    LIFT_STUB(0x5d58a0);
}

// 0x5d5de0
::GameLogExpReasonCode __cdecl Pc::GetGameLogExpReasonCode(::Pc::ExpReason)
{
    LIFT_STUB(0x5d5de0);
}

// 0x5d5ea0
__cdecl Pc::Pc(void)
{
    LIFT_STUB(0x5d5ea0);
}

// 0x5d6b60
__cdecl Pc::~Pc(void)
{
    LIFT_STUB(0x5d6b60);
}

// 0x5d7180
#pragma comment(linker, "/INCLUDE:?IsTryingInstantPayment@Pc@@QEAA_NXZ")  // LIFT: dead-strip keep (no live caller yet)
bool __cdecl Pc::IsTryingInstantPayment(void)
{
    AcquireSRWLockShared(&_tryingInstantPaymentLock);
    bool isTrying = _isTryingInstantPayment;
    ReleaseSRWLockShared(&_tryingInstantPaymentLock);
    return isTrying;
}

// 0x5d71c0
void __cdecl Pc::clearRankingRewardList(void)
{
    LIFT_STUB(0x5d71c0);
}

// 0x5d7310
bool __cdecl Pc::AddRankingRewardList(char, int, char, short, int, __int64, __int64)
{
    LIFT_STUB(0x5d7310);
}

// 0x5d7690
bool __cdecl Pc::FetchRankingRewardListToCache(::RepeatPacketComposer *, ::Packet *)
{
    LIFT_STUB(0x5d7690);
}

// 0x5d7930
bool __cdecl Pc::UpdateRankingRewardList(::RepeatPacketDecomposer *, ::Packet const *)
{
    LIFT_STUB(0x5d7930);
}

// 0x5d7d70
bool __cdecl Pc::GetRankingRewardInfo(char, int, char, ::RankingRewardInfo &)
{
    LIFT_STUB(0x5d7d70);
}

// 0x5d7e80
short __cdecl Pc::TakeRankingRewardOkFromCache(char, int, char)
{
    LIFT_STUB(0x5d7e80);
}

// 0x5d7f30
bool __cdecl Pc::SendRetrieveRankingRewardListOk(void)
{
    LIFT_STUB(0x5d7f30);
}

// 0x5d8320
void __cdecl Pc::SendRetrieveRankingRewardListFail(short)
{
    LIFT_STUB(0x5d8320);
}

// 0x5d8390
void __cdecl Pc::SendRetrieveGuildRankingInfoFail(short)
{
    LIFT_STUB(0x5d8390);
}

// 0x5d8400
void __cdecl Pc::SendRetrieveChallengePartyRankingInfoFail(short)
{
    LIFT_STUB(0x5d8400);
}

// 0x5d8490
void __cdecl Pc::SendTakeRankingRewardFail(short)
{
    LIFT_STUB(0x5d8490);
}

// 0x5d8500
void __cdecl Pc::SendRegisterCraftFail(int, short)
{
    LIFT_STUB(0x5d8500);
}

// 0x5d8590
void __cdecl Pc::SendTakeCraftFail(unsigned __int64, short)
{
    LIFT_STUB(0x5d8590);
}

// 0x5d8620
void __cdecl Pc::SendAbortCraftFail(unsigned __int64, short)
{
    LIFT_STUB(0x5d8620);
}

// 0x5d86a0
void __cdecl Pc::SendJoinCraftUnionFail(char, short)
{
    LIFT_STUB(0x5d86a0);
}

// 0x5d8730
void __cdecl Pc::SendLeaveCraftUnionFail(char, short)
{
    LIFT_STUB(0x5d8730);
}

// 0x5d87c0
void __cdecl Pc::InitailizeJoinedGuildInfo(unsigned __int64)
{
    LIFT_STUB(0x5d87c0);
}

// 0x5d8bc0
bool __cdecl Pc::updateRankingRewardInfo(unsigned __int64, __int64)
{
    LIFT_STUB(0x5d8bc0);
}

// 0x5d8cc0
bool __cdecl Pc::Initialize(unsigned __int64, char)
{
    LIFT_STUB(0x5d8cc0);
}

// 0x5d8ef0
void __cdecl Pc::EnterZone(::EnterReason, bool, unsigned int)
{
    LIFT_STUB(0x5d8ef0);
}

// 0x5da450
void __cdecl Pc::LeaveZone(::LeaveReason)
{
    LIFT_STUB(0x5da450);
}

// 0x5dafc0
void __cdecl Pc::WriteGameLogFactionScoreDisappear(int, int, int)
{
    LIFT_STUB(0x5dafc0);
}

// 0x5db450
bool __cdecl Pc::IsInTeamPartyZone(void)
{
    LIFT_STUB(0x5db450);
}

// 0x5db4a0
bool __cdecl Pc::IsInPartyBattleFieldZone(void)
{
    LIFT_STUB(0x5db4a0);
}

// 0x5db4e0
bool __cdecl Pc::IsInPartyZone(void)
{
    LIFT_STUB(0x5db4e0);
}

// 0x5db520
bool __cdecl Pc::SetDead(bool, ::ChangedProperty *, unsigned __int64, unsigned __int64, unsigned __int64, bool, bool)
{
    LIFT_STUB(0x5db520);
}

// 0x5de2f0
bool __cdecl Pc::SetAllDbData(unsigned __int64, ::FragmentPacketConcatenater *, ::std::vector< ::Item *, ::StlAllocator< ::Item *, 2> > &)
{
    LIFT_STUB(0x5de2f0);
}

// 0x5debc0
int __cdecl Pc::SetExtraDbData(unsigned __int64, char const *, int)
{
    LIFT_STUB(0x5debc0);
}

// 0x5dec60
int __cdecl Pc::SetDbEffectData(short, char const *, int)
{
    LIFT_STUB(0x5dec60);
}

// 0x5ded20
bool __cdecl Pc::SetDbSeasonContentsCombatRecordData(::FragmentPacketConcatenater *)
{
    LIFT_STUB(0x5ded20);
}

// 0x5def40
bool __cdecl Pc::SetDbSeasonContentsTimeAttackRecordData(::FragmentPacketConcatenater *)
{
    LIFT_STUB(0x5def40);
}

// 0x5df130
bool __cdecl Pc::SetDbDuelBotTrainingRoomScoreData(::FragmentPacketConcatenater *)
{
    LIFT_STUB(0x5df130);
}

// 0x5df350
bool __cdecl Pc::SetDbCompletedAchievementRewardData(::FragmentPacketConcatenater *)
{
    LIFT_STUB(0x5df350);
}

// 0x5df500
bool __cdecl Pc::SetDbJoinCraftUnionData(::FragmentPacketConcatenater *)
{
    LIFT_STUB(0x5df500);
}

// 0x5df630
bool __cdecl Pc::SetDbCraftData(::FragmentPacketConcatenater *)
{
    LIFT_STUB(0x5df630);
}

// 0x5dfc40
bool __cdecl Pc::LoadData(void)
{
    LIFT_STUB(0x5dfc40);
}

// 0x5dfd20
bool __cdecl Pc::ApplyAbility(::ChangedProperty *const, char, char)
{
    LIFT_STUB(0x5dfd20);
}

// 0x5e01e0
bool __cdecl Pc::RemasterApplyAbility(::ChangedProperty *const, char, char)
{
    LIFT_STUB(0x5e01e0);
}

// 0x5e07f0
bool __cdecl Pc::ReturnToRespawn(bool)
{
    LIFT_STUB(0x5e07f0);
}

// 0x5e0bb0
bool __cdecl Pc::LevelUp(::ChangedProperty *, int, int, int, int, short)
{
    LIFT_STUB(0x5e0bb0);
}

// 0x5e14d0
bool __cdecl Pc::OpenMasteryLevel(::ChangedProperty *const)
{
    LIFT_STUB(0x5e14d0);
}

// 0x5e1650
::Data::PcContentsTypeType __cdecl Pc::GetPcContentsType(::Pc *)
{
    LIFT_STUB(0x5e1650);
}

// 0x5e16c0
void __cdecl Pc::FullRecovery(::Pc *)
{
    LIFT_STUB(0x5e16c0);
}

// 0x5e1a00
bool __cdecl Pc::HandleJobStyle(::ChangedProperty *)
{
    LIFT_STUB(0x5e1a00);
}

// 0x5e1ad0
bool __cdecl Pc::HandleStance(char, unsigned __int64 const *, int, ::ChangedProperty *)
{
    LIFT_STUB(0x5e1ad0);
}

// 0x5e1bc0
void __cdecl Pc::RefreshSkillList(void)
{
    LIFT_STUB(0x5e1bc0);
}

// 0x5e1d70
bool __cdecl Pc::AcquireSkillFromLevel(char, bool)
{
    LIFT_STUB(0x5e1d70);
}

// 0x5e1fa0
bool __cdecl Pc::InvokeMasteryStatBonusAbility(void)
{
    LIFT_STUB(0x5e1fa0);
}

// 0x5e2030
::Data::ItemRecordCostumePtr const __cdecl Pc::GetCostume(void) const
{
    LIFT_STUB(0x5e2030);
}

// 0x5e20e0
bool __cdecl Pc::CheckUsableWeapon(void) const
{
    LIFT_STUB(0x5e20e0);
}

// 0x5e21b0
bool __cdecl Pc::CheckToEquipMainFactionItem(void) const
{
    LIFT_STUB(0x5e21b0);
}

// 0x5e22e0
bool __cdecl Pc::CheckResurrectPosition(void) const
{
    LIFT_STUB(0x5e22e0);
}

// 0x5e2430
bool __cdecl Pc::CheckSkillSkinCondition(short) const
{
    LIFT_STUB(0x5e2430);
}

// 0x5e27f0
void __cdecl Pc::ResetUnacquiredSkillSkin(bool)
{
    LIFT_STUB(0x5e27f0);
}

// 0x5e28f0
::GameFailReason __cdecl Pc::CheckUsableGrocery(::Data::ItemRecordGroceryPtr)
{
    LIFT_STUB(0x5e28f0);
}

// 0x5e2ba0
void __cdecl Pc::SetCombatModeByAttack(bool, ::SourceLocation const &)
{
    LIFT_STUB(0x5e2ba0);
}

// 0x5e2cd0
void __cdecl Pc::SetCombatModeByAttacked(::SourceLocation const &)
{
    LIFT_STUB(0x5e2cd0);
}

// 0x5e2dc0
#pragma comment(linker, "/INCLUDE:?SetCombatModeByTargeted@Pc@@UEAAXAEBVSourceLocation@@@Z")  // LIFT: dead-strip keep (no live caller yet)
void __cdecl Pc::SetCombatModeByTargeted(::SourceLocation const &)
{
    ++_targetedCountByNpc;
}

// 0x5e2dd0
void __cdecl Pc::SetCombatModeByLink(::SourceLocation const &)
{
    LIFT_STUB(0x5e2dd0);
}

// 0x5e2e50
void __cdecl Pc::ResetCombatModeByLink(::SourceLocation const &)
{
    LIFT_STUB(0x5e2e50);
}

// 0x5e2ef0
void __cdecl Pc::ResetCombatModeByTargeted(::SourceLocation const &)
{
    LIFT_STUB(0x5e2ef0);
}

// 0x5e2fa0
void __cdecl Pc::ResetCombatModeByKill(::SourceLocation const &)
{
    LIFT_STUB(0x5e2fa0);
}

// 0x5e3030
void __cdecl Pc::StartRestoration(void)
{
    LIFT_STUB(0x5e3030);
}

// 0x5e30b0
__int64 __cdecl Pc::GetGradeBenefitValue(int)
{
    LIFT_STUB(0x5e30b0);
}

// 0x5e3190
__int64 const __cdecl Pc::GetGradeBenefitRandomStoreProbGroup(int, char) const
{
    LIFT_STUB(0x5e3190);
}

// 0x5e3280
unsigned __int64 const * __cdecl Pc::GetGradeBenefitAchievementRef(int, char &) const
{
    LIFT_STUB(0x5e3280);
}

// 0x5e3360
void __cdecl Pc::ResetCombatMode(bool, ::SourceLocation const &)
{
    LIFT_STUB(0x5e3360);
}

// 0x5e3610
bool __cdecl Pc::SetCombatSide(char, ::ChangedProperty *const)
{
    LIFT_STUB(0x5e3610);
}

// 0x5e3750
void __cdecl Pc::InvokeReviveExceptionRuleEffect(void)
{
    LIFT_STUB(0x5e3750);
}

// 0x5e3820
void __cdecl Pc::InvokeRevivalEffect(void)
{
    LIFT_STUB(0x5e3820);
}

// 0x5e3930
void __cdecl Pc::setCombatMode(::Pc::CombatModeType, long, ::SourceLocation const &)
{
    LIFT_STUB(0x5e3930);
}

// 0x5e3a00
bool __cdecl Pc::banishFromInstantPartyZone(void)
{
    LIFT_STUB(0x5e3a00);
}

// 0x5e3b80
bool __cdecl Pc::CheckPcCafe(void)
{
    LIFT_STUB(0x5e3b80);
}

// 0x5e3c00
bool __cdecl Pc::UseHeartCount(unsigned __int64, unsigned int)
{
    LIFT_STUB(0x5e3c00);
}

// 0x5e40a0
bool __cdecl Pc::CheckEnableHeartCount(void)
{
    LIFT_STUB(0x5e40a0);
}

// 0x5e41d0
char __cdecl Pc::getPcCafePublisherCode(void)
{
    LIFT_STUB(0x5e41d0);
}

// 0x5e42e0
unsigned __int64 __cdecl Pc::getPcCafeEffect(void)
{
    LIFT_STUB(0x5e42e0);
}

// 0x5e43e0
int __cdecl Pc::GetPcCafePointBonusPercent(int)
{
    LIFT_STUB(0x5e43e0);
}

// 0x5e4510
int __cdecl Pc::GetPcCafeExpBonusPercent(int)
{
    LIFT_STUB(0x5e4510);
}

// 0x5e4630
int __cdecl Pc::getPcCafeNpcLootingMoneyRewardPercent(void)
{
    LIFT_STUB(0x5e4630);
}

// 0x5e46d0
bool __cdecl Pc::UsablePcCafeUnlocatedWareHouse(void)
{
    LIFT_STUB(0x5e46d0);
}

// 0x5e4770
bool __cdecl Pc::UsablePcCafeQuestReward(void)
{
    LIFT_STUB(0x5e4770);
}

// 0x5e4810
::Data::PcCafeBenefitsRecordPtr const __cdecl Pc::GetPcCafeBenefitsData(void)
{
    LIFT_STUB(0x5e4810);
}

// 0x5e4880
bool __cdecl Pc::SetPcCafeDebugCode(wchar_t *, char)
{
    LIFT_STUB(0x5e4880);
}

// 0x5e4960
bool __cdecl Pc::invokePcCafeEffect(void)
{
    LIFT_STUB(0x5e4960);
}

// 0x5e4a10
int __cdecl Pc::CalcNpcLootingMoney(__int64, int, bool)
{
    LIFT_STUB(0x5e4a10);
}

// 0x5e4c40
bool __cdecl Pc::AcquireFactionScore(int)
{
    LIFT_STUB(0x5e4c40);
}

// 0x5e4d40
char __cdecl Pc::GetActivatedMainFactionId(void)
{
    LIFT_STUB(0x5e4d40);
}

// 0x5e4dd0
void __cdecl Pc::ClearFactionKilledCount(void)
{
    LIFT_STUB(0x5e4dd0);
}

// 0x5e4e50
void __cdecl Pc::RestoreActivatedFaction(void)
{
    LIFT_STUB(0x5e4e50);
}

// 0x5e5030
void __cdecl Pc::AcquireStyleScore(short, short, long)
{
    LIFT_STUB(0x5e5030);
}

// 0x5e5130
void __cdecl Pc::ClearStyleScore(void)
{
    LIFT_STUB(0x5e5130);
}

// 0x5e51b0
#pragma comment(linker, "/INCLUDE:?CalculateStyleScoreBonus@Pc@@QEAA_J_J@Z")  // LIFT: dead-strip keep (no live caller yet)
__int64 __cdecl Pc::CalculateStyleScoreBonus(__int64 exp)
{
    // LIFT: Pc derives from Creature in the PDB. The skeleton Pc has no Creature base yet.
    short styleScore = reinterpret_cast<const ::CreatureMemberView *>(this)->style_score;
    if (styleScore <= 0)
        return 0;
    ::RuleConfig *ruleConfig = GameDaemon::GamedInstance->GetRuleConfig();
    int bonus = 0;
    if (styleScore >= ruleConfig->_styleScoreExpStep2)
        bonus = ruleConfig->_styleScoreExpBonus2;
    else if (styleScore >= ruleConfig->_styleScoreExpStep1)
        bonus = ruleConfig->_styleScoreExpBonus1;
    if (bonus <= 0)
        return 0;
    return exp * bonus / 1000;
}

// 0x5e5220
void __cdecl Pc::SendSkillScoreNotify(void)
{
    LIFT_STUB(0x5e5220);
}

// 0x5e5380
void __cdecl Pc::ActivateSkillScore(__int64)
{
    LIFT_STUB(0x5e5380);
}

// 0x5e5510
#pragma comment(linker, "/INCLUDE:?DeactivateSkillScore@Pc@@QEAAXXZ")  // LIFT: dead-strip keep (no live caller yet)
void __cdecl Pc::DeactivateSkillScore(void)
{
    _activatedSkillScore = false;
    _bonusSkillScoreRate = 0;
    _skillScoreUseHeartCount = 0;
    _skillScoreUseItemPoint = 0;
    _skillScoreBossNpcKillCount = 0;
    _skillScoreStartTime = 0;
    _skillScoreMaxComboCount = 0;
    if (_skillScoreComboCount > 0)
        _skillScoreMaxComboCount = _skillScoreComboCount;
    _skillScoreRate = 0;
    _skillScoreComboCount = 0;
    _skillScoreKillCount = 0;
    _baseSkillScore = 0;
    _lastSkillScoreLimitTime = 0;
}

// 0x5e5560
void __cdecl Pc::AcquireSkillScore(int)
{
    LIFT_STUB(0x5e5560);
}

// 0x5e56d0
void __cdecl Pc::AcquireSkillScoreRate(::Pc::SkillScoreRateReason, int)
{
    LIFT_STUB(0x5e56d0);
}

// 0x5e57c0
void __cdecl Pc::IncreaseSkillScoreCombo(bool)
{
    LIFT_STUB(0x5e57c0);
}

// 0x5e5890
void __cdecl Pc::FinishedSkillScoreCombo(void)
{
    LIFT_STUB(0x5e5890);
}
