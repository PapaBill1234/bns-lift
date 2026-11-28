// questjournal_cpp_2.cpp: questjournal.cpp part 2 (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "questjournal.h"
#include "inventory.h"
#include "questlist.h"
#include "LiftStub.h"
#include "Log.h"

#pragma comment(linker, "/INCLUDE:?validateQuestId@QuestJournal@@CA_NG@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?isScriptableCase@QuestJournal@@AEAA_NF@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?RemoveLeaveZoneRollbackQuestIndex@QuestJournal@@QEAA_NH@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?removeAttrationQuest@QuestJournal@@AEAA_NH@Z")  // LIFT: dead-strip keep (no live caller yet)

#define QUESTJOURNAL_FILE L"e:\\dailybuild02\\gamedaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\gamedaemon\\QuestJournal.cpp"

// 0x572fa0
bool __cdecl QuestJournal::IsRewardRestrictedCase(::QuestCase const &)
{
    LIFT_STUB(0x572fa0);
}

// 0x573010
bool __cdecl QuestJournal::validateQuestId(unsigned short questId)
{
    if ((questId >= 1 && questId <= 2000)
        || (questId >= 20000 && questId <= 23000)
        || (questId >= 25000 && questId <= 25300)
        || (questId >= 28000 && questId <= 29999))
    {
        return true;
    }

    Log::Write(Log::LT_ERROR, QUESTJOURNAL_FILE, 10096, L"[quest], invalid quest id, quest:%d", questId);
    return false;
}

// 0x5730a0
bool __cdecl QuestJournal::isScriptableCase(short caseType)
{
    switch (caseType)
    {
    case 0:
    case 3:
    case 4:
    case 5:
    case 6:
    case 8:
    case 10:
    case 11:
    case 17:
    case 18:
        return true;
    default:
        return false;
    }
}

// 0x5730f0
bool __cdecl QuestJournal::ProcessRollbackCase(::ScriptEvent const &, unsigned short, char, char)
{
    LIFT_STUB(0x5730f0);
}

// 0x5734b0
bool __cdecl QuestJournal::ProcessMissionStepTimeLimitFail(unsigned short, char, bool)
{
    LIFT_STUB(0x5734b0);
}

// 0x573720
bool __cdecl QuestJournal::processMissionStepFail(::OpenQuest *, int, bool, bool, ::MissionStepFail const *)
{
    LIFT_STUB(0x573720);
}

// 0x573f60
bool __cdecl QuestJournal::rollbackMissionStep(::OpenQuest *, char)
{
    LIFT_STUB(0x573f60);
}

// 0x574160
bool __cdecl QuestJournal::completeOpenQuest(::QuestJournal::QuestRequestInfo const &, int, ::QuestJournal::RequestFromType)
{
    LIFT_STUB(0x574160);
}

// 0x574220
bool __cdecl QuestJournal::completeQuest(::QuestJournal::QuestRequestInfo const &, ::Quest const *, ::QuestJournal::RequestFromType)
{
    LIFT_STUB(0x574220);
}

// 0x574fb0
bool __cdecl QuestJournal::acquireNextQuest(::Quest const *)
{
    LIFT_STUB(0x574fb0);
}

// 0x5750b0
bool __cdecl QuestJournal::setQuestCompletionBit(unsigned short)
{
    LIFT_STUB(0x5750b0);
}

// 0x575260
::GameFailReason __cdecl QuestJournal::completeMission(::QuestJournal::QuestContext const &, ::QuestJournal::QuestRequestInfo const &, bool &, ::QuestJournal::RequestFromType)
{
    LIFT_STUB(0x575260);
}

// 0x575de0
void __cdecl QuestJournal::notifyAcquire(unsigned short, char, char, char)
{
    LIFT_STUB(0x575de0);
}

// 0x575e70
void __cdecl QuestJournal::notifyChange(::QuestJournal::QuestRequestInfo const &, ::OpenQuest const *)
{
    LIFT_STUB(0x575e70);
}

// 0x576060
bool __cdecl QuestJournal::checkAcquisitionFilter(::Acquisition const *, ::QuestCase const *, ::ScriptEvent const &) const
{
    LIFT_STUB(0x576060);
}

// 0x5766b0
bool __cdecl QuestJournal::checkFilterSetArray(::QuestFilterSet const *, int, ::ScriptEvent const &) const
{
    LIFT_STUB(0x5766b0);
}

// 0x576830
::GameFailReason __cdecl QuestJournal::checkNormalCaseCondition(::Data::QuestCase const *, ::Data::QuestQuest const *, bool)
{
    LIFT_STUB(0x576830);
}

// 0x576950
bool __cdecl QuestJournal::checkZone(::QuestCase const *)
{
    LIFT_STUB(0x576950);
}

// 0x576a10
bool __cdecl QuestJournal::checkGadget(::Data::QuestCase const *)
{
    LIFT_STUB(0x576a10);
}

// 0x576a70
bool __cdecl QuestJournal::checkGrocery(unsigned __int64, short, short, unsigned __int64, short, bool, bool &, ::Inventory::DisposeOrderWithPos &, ::QuestJournal::QuestRequestInfo const &)
{
    LIFT_STUB(0x576a70);
}

// 0x576c40
bool __cdecl QuestJournal::checkRequiredItems(::QuestRequiredItems const *, ::QuestCase const &, ::QuestJournal::RequiredItemLoss &, ::QuestJournal::QuestRequestInfo const &)
{
    LIFT_STUB(0x576c40);
}

// 0x5778a0
bool __cdecl QuestJournal::checkRequiredBrandItems(::QuestRequiredItems const *, char, int, unsigned __int64 const *const, ::QuestJournal::QuestRequestInfo const &)
{
    LIFT_STUB(0x5778a0);
}

// 0x577e10
bool __cdecl QuestJournal::checkRequiredEquipGems(::QuestRequiredItems const *, unsigned __int64, ::QuestJournal::QuestRequestInfo const &)
{
    LIFT_STUB(0x577e10);
}

// 0x578260
bool __cdecl QuestJournal::checkRequiredJumpingCharacterState(char, ::QuestJournal::QuestRequestInfo const &)
{
    LIFT_STUB(0x578260);
}

// 0x578380
::GameFailReason __cdecl QuestJournal::checkLossAndReward(::QuestJournal::QuestContext const &, ::QuestCase const *, char, bool, ::QuestJournal::LossList &, ::QuestJournal::RewardList &, ::MentorRewardPostParam *, ::QuestJournal::RequiredItemLoss const *)
{
    LIFT_STUB(0x578380);
}

// 0x578710
void __cdecl QuestJournal::giveLossAndReward(::QuestJournal::LossList &, ::QuestJournal::RewardList &, ::MentorRewardPostParam *, ::QuestJournal::RequiredItemLoss const *)
{
    LIFT_STUB(0x578710);
}

// 0x578960
::GameFailReason __cdecl QuestJournal::checkCompletionLoss(unsigned short, ::Mission const *, ::QuestJournal::LossList &, ::QuestJournal::RequiredItemLoss const *)
{
    LIFT_STUB(0x578960);
}

// 0x578c80
void __cdecl QuestJournal::takeCompletionLoss(::QuestJournal::LossList &, ::QuestJournal::RequiredItemLoss const *)
{
    LIFT_STUB(0x578c80);
}

// 0x578f00
::GameFailReason __cdecl QuestJournal::checkAcquisitionLoss(unsigned short, ::Acquisition const *, ::QuestJournal::LossList &, ::QuestJournal::RequiredItemLoss const *)
{
    LIFT_STUB(0x578f00);
}

// 0x5791a0
void __cdecl QuestJournal::takeAcquisitionLoss(::QuestJournal::LossList &, ::QuestJournal::RequiredItemLoss const *)
{
    LIFT_STUB(0x5791a0);
}

// 0x579420
void __cdecl QuestJournal::takeGiveupLoss(::Quest const *)
{
    LIFT_STUB(0x579420);
}

// 0x579e70
::GameFailReason __cdecl QuestJournal::checkCaseLoss(::QuestJournal::RequiredItemLoss const *)
{
    LIFT_STUB(0x579e70);
}

// 0x579f20
void __cdecl QuestJournal::takeCaseLoss(::QuestJournal::RequiredItemLoss const *)
{
    LIFT_STUB(0x579f20);
}

// 0x57a090
int __cdecl QuestJournal::calcQuestRewardExpBonus(unsigned short, int)
{
    LIFT_STUB(0x57a090);
}

// 0x57a110
int __cdecl QuestJournal::calcQuestRewardExpBonusTestServer(int)
{
    LIFT_STUB(0x57a110);
}

// 0x57a170
int __cdecl QuestJournal::calcQuestRewardExpBonusGradeBenefit(unsigned short, int)
{
    LIFT_STUB(0x57a170);
}

// 0x57a200
::GameFailReason __cdecl QuestJournal::checkReward(::QuestNewbieState, bool, bool, bool, unsigned short, ::QuestReward const *, unsigned __int64 *&, int, char, ::QuestJournal::RewardList &, char, ::MentorRewardPostParam *)
{
    LIFT_STUB(0x57a200);
}

// 0x57bda0
void __cdecl QuestJournal::giveReward(::QuestJournal::RewardList &, ::MentorRewardPostParam *)
{
    LIFT_STUB(0x57bda0);
}

// 0x57d2a0
::GameFailReason __cdecl QuestJournal::getFixedReward(unsigned short, ::Data::QuestFixedReward *, ::Inventory::AcquireOrder *const, int &)
{
    LIFT_STUB(0x57d2a0);
}

// 0x57d3e0
::GameFailReason __cdecl QuestJournal::getDisjoinedFixedReward(unsigned short, ::QuestJournal::StFixedReward &, ::Inventory::AcquireOrder *const, int &)
{
    LIFT_STUB(0x57d3e0);
}

// 0x57d540
::GameFailReason __cdecl QuestJournal::getRewardSlot(unsigned short, ::dr_tref *, char, ::Inventory::AcquireOrder *const, int &)
{
    LIFT_STUB(0x57d540);
}

// 0x57d640
bool __cdecl QuestJournal::getDayOfWeeklFixedReward(unsigned short, ::QuestJournal::StDayOfWeekFixedReward &, ::Inventory::AcquireOrder *const, int &)
{
    LIFT_STUB(0x57d640);
}

// 0x57d730
bool __cdecl QuestJournal::getNewbieReward(unsigned short, ::Data::QuestRewardRecordPtr, ::Inventory::AcquireOrder *const, char *const, int &)
{
    LIFT_STUB(0x57d730);
}

// 0x57d880
bool __cdecl QuestJournal::getOldbieReward(unsigned short, ::Data::QuestRewardRecordPtr, ::Inventory::AcquireOrder *const, char *const, int &)
{
    LIFT_STUB(0x57d880);
}

// 0x57d9d0
bool __cdecl QuestJournal::getAdditionalRewardItem(unsigned short, int, unsigned __int64 *const, short *const, ::Inventory::AcquireOrder *const, int &, bool &)
{
    LIFT_STUB(0x57d9d0);
}

// 0x57daf0
bool __cdecl QuestJournal::checkPcCondition(int, unsigned __int64 const *const, int, char const *const, int, char const *const, int, char const *const) const
{
    LIFT_STUB(0x57daf0);
}

// 0x57dc70
bool __cdecl QuestJournal::checkPcDifficultyType(char)
{
    LIFT_STUB(0x57dc70);
}

// 0x57dcb0
unsigned char __cdecl QuestJournal::diffCompletionCount(unsigned short, char, char)
{
    LIFT_STUB(0x57dcb0);
}

// 0x57dff0
::GameFailReason __cdecl QuestJournal::setRegister(::QuestJournal::QuestContext &, __int64, ::QuestJournal::RequestFromType)
{
    LIFT_STUB(0x57dff0);
}

// 0x57e350
__cdecl QuestJournal::RewardList::RewardList(void)
{
    LIFT_STUB(0x57e350);
}

// 0x57e450
bool __cdecl QuestJournal::completeMissionManage(::QuestJournal::RequestFromType, unsigned short, char, char)
{
    LIFT_STUB(0x57e450);
}

// 0x57e8d0
int __cdecl QuestJournal::resetQuestManage(::QuestJournal::RequestFromType, unsigned short)
{
    LIFT_STUB(0x57e8d0);
}

// 0x57eb40
bool __cdecl QuestJournal::resetQuestAllManage(::QuestJournal::RequestFromType)
{
    LIFT_STUB(0x57eb40);
}

// 0x57ee00
int __cdecl QuestJournal::rollbackMissionStepManage(::QuestJournal::RequestFromType, unsigned short, char)
{
    LIFT_STUB(0x57ee00);
}

// 0x57eef0
bool __cdecl QuestJournal::setQuestCompletionTime(unsigned short, __int64)
{
    LIFT_STUB(0x57eef0);
}

// 0x57efa0
bool __cdecl QuestJournal::checkCompletionTime(::Quest const *)
{
    LIFT_STUB(0x57efa0);
}

// 0x57f000
bool __cdecl QuestJournal::CheckTimeForResetByAcquireTime(::Quest const *)
{
    LIFT_STUB(0x57f000);
}

// 0x57f060
bool __cdecl QuestJournal::getCompletionTypeInfo(::Data::QuestQuest const *, ::QuestList::CompletionTimeTypeSequence &, int &)
{
    LIFT_STUB(0x57f060);
}

// 0x57f330
bool __cdecl QuestJournal::setQuestCompletionDay(::Data::QuestQuest const *, __int64)
{
    LIFT_STUB(0x57f330);
}

// 0x57f3f0
bool __cdecl QuestJournal::setQuestCompletionDayInternal(unsigned short, ::QuestList::CompletionTimeTypeSequence, int, __int64)
{
    LIFT_STUB(0x57f3f0);
}

// 0x57f8d0
bool __cdecl QuestJournal::deleteCompletionDay(::Data::QuestQuest const *)
{
    LIFT_STUB(0x57f8d0);
}

// 0x57fcd0
int __cdecl QuestJournal::getQuestCompletionDay(::Data::QuestQuest const *)
{
    LIFT_STUB(0x57fcd0);
}

// 0x57fd90
int __cdecl QuestJournal::getQuestCompletionDayInternal(unsigned short, ::QuestList::CompletionTimeTypeSequence)
{
    LIFT_STUB(0x57fd90);
}

// 0x57ffd0
bool __cdecl QuestJournal::checkCompletionDay(::Data::QuestQuest const *)
{
    LIFT_STUB(0x57ffd0);
}

// 0x580270
unsigned short __cdecl QuestJournal::getCompletionDayByResetHourFromTime(__int64, char, char)
{
    LIFT_STUB(0x580270);
}

// 0x580340
bool __cdecl QuestJournal::isDeleteTimeForCompletionTime(char, char)
{
    LIFT_STUB(0x580340);
}

// 0x580440
bool __cdecl QuestJournal::checkAndDeleteCompletionTimeGarbage(::Data::QuestQuest const *)
{
    LIFT_STUB(0x580440);
}

// 0x580490
bool __cdecl QuestJournal::deleteCompletionTimeGarbage(void)
{
    LIFT_STUB(0x580490);
}

// 0x5809f0
int __cdecl QuestJournal::getCompletedQuestCountByResetType(char)
{
    LIFT_STUB(0x5809f0);
}

// 0x580d10
bool __cdecl QuestJournal::SetChallengeListRewardCompleted(__int64, char)
{
    LIFT_STUB(0x580d10);
}

// 0x580f00
bool __cdecl QuestJournal::HasFactionQuest(char)
{
    LIFT_STUB(0x580f00);
}

// 0x580f50
void __cdecl QuestJournal::sendUpdateQuestToCacheChannel(::OpenQuest const *)
{
    LIFT_STUB(0x580f50);
}

// 0x580fc0
bool __cdecl QuestJournal::AddLeaveZoneRollbackQuestIndex(int)
{
    LIFT_STUB(0x580fc0);
}

// 0x581080
bool __cdecl QuestJournal::RemoveLeaveZoneRollbackQuestIndex(int questIndex)
{
    for (int i = 0; i < _leaveZoneRollbackCount; ++i)
    {
        if (_leaveZoneRollbackQuestIdxs[i] == questIndex)
        {
            if (i < _leaveZoneRollbackCount - 1)
                _leaveZoneRollbackQuestIdxs[i] = _leaveZoneRollbackQuestIdxs[_leaveZoneRollbackCount - 1];
            --_leaveZoneRollbackCount;
            break;
        }
    }
    return true;
}

// 0x5810f0
void __cdecl QuestJournal::processLeaveZoneRollback(void)
{
    LIFT_STUB(0x5810f0);
}

// 0x581260
void __cdecl QuestJournal::RollbackByRemoveFielditem(unsigned int)
{
    LIFT_STUB(0x581260);
}

// 0x5813d0
bool __cdecl QuestJournal::resetBindDungeonQuest(int)
{
    LIFT_STUB(0x5813d0);
}

// 0x5814b0
bool __cdecl QuestJournal::updatePartyDungeonStep(unsigned short, char)
{
    LIFT_STUB(0x5814b0);
}

// 0x581620
void __cdecl QuestJournal::disposeUnbindDungeonQuest(void)
{
    LIFT_STUB(0x581620);
}

// 0x581800
bool __cdecl QuestJournal::GetQuestFixedRewardByIndex(int, ::Data::QuestRewardRecordPtr, ::QuestJournal::StFixedReward &)
{
    LIFT_STUB(0x581800);
}

// 0x581da0
bool __cdecl QuestJournal::GetQuestOptionalRewardByIndex(int, ::Data::QuestRewardRecordPtr, ::QuestJournal::StOptioanlReward &)
{
    LIFT_STUB(0x581da0);
}

// 0x582340
bool __cdecl QuestJournal::GetQuestDayOfWeekFixedReward(int, ::Data::QuestRewardRecordPtr, ::QuestJournal::StDayOfWeekFixedReward &)
{
    LIFT_STUB(0x582340);
}

// 0x582500
__int64 __cdecl QuestJournal::calcCaseFee(void)
{
    LIFT_STUB(0x582500);
}

// 0x582570
::GameFailReason __cdecl QuestJournal::DungeonProgressToStepN(short, unsigned short, char, __int64, int, ::Inventory::DisposeOrderWithPos const *const)
{
    LIFT_STUB(0x582570);
}

// 0x583850
unsigned short __cdecl QuestJournal::GetValidDungeonQuestId(::Data::DungeonRecordPtr)
{
    LIFT_STUB(0x583850);
}

// 0x583970
bool __cdecl QuestJournal::isValidBroadcastCategoryForProgress(unsigned short)
{
    LIFT_STUB(0x583970);
}

// 0x583ac0
bool __cdecl QuestJournal::addDuelQuestIdx(int, ::Quest const *)
{
    LIFT_STUB(0x583ac0);
}

// 0x583ba0
bool __cdecl QuestJournal::removeDuelQuestIdx(int, ::Quest const *)
{
    LIFT_STUB(0x583ba0);
}

// 0x583c70
bool __cdecl QuestJournal::checkDuelCurrentStraightWin(char, char, int, ::QuestJournal::QuestRequestInfo const &)
{
    LIFT_STUB(0x583c70);
}

// 0x583ce0
bool __cdecl QuestJournal::removeAttrationQuest(int questIndex)
{
    int last = _attractionQuestCount - 1;
    for (int i = last; i >= 0; --i)
    {
        if (_attractionQuestIdxs[i] == questIndex)
        {
            if (i < last)
                _attractionQuestIdxs[i] = _attractionQuestIdxs[last];
            --_attractionQuestCount;
            break;
        }
    }
    return true;
}

// 0x583d40
void __cdecl QuestJournal::LeaveEnterAttraction(::dr_tref, ::dr_tref)
{
    LIFT_STUB(0x583d40);
}

// 0x5843b0
::GameFailReason __cdecl QuestJournal::ResetQuestCompletionTime(unsigned short, int, ::Inventory::DisposeOrderWithPos const *const)
{
    LIFT_STUB(0x5843b0);
}

// 0x585820
bool __cdecl QuestJournal::CheckToExistFaction2NextEpic(char, char, unsigned short &)
{
    LIFT_STUB(0x585820);
}

// 0x585b50
bool __cdecl QuestJournal::TransferFaction2Epic(char, unsigned short)
{
    LIFT_STUB(0x585b50);
}

// 0x585d00
::GameFailReason __cdecl QuestJournal::disposeWithOpenQuestIndexForce(int)
{
    LIFT_STUB(0x585d00);
}

// 0x5860d0
bool __cdecl QuestJournal::checkPcConditionWithParam(int, unsigned __int64 const *const, int, char const *const, int, char const *const, int, char const *const, char, char, char, char, char) const
{
    LIFT_STUB(0x5860d0);
}

// 0x5861b0
::GameFailReason __cdecl QuestJournal::checkQuestValidDateTime(::Data::QuestQuest const *, bool)
{
    LIFT_STUB(0x5861b0);
}

// 0x586490
::GameFailReason __cdecl QuestJournal::ProgressRetiredMissionStep(unsigned short, char)
{
    LIFT_STUB(0x586490);
}

// 0x586d50
::Data::QuestMissionStep const * __cdecl QuestJournal::GetNextMissionstepRecord(char, ::Quest const *)
{
    LIFT_STUB(0x586d50);
}

// 0x586da0
void __cdecl QuestJournal::gameLogCompleteMissionStep(::Data::QuestQuest const *, char, ::QuestJournal::QuestRequestInfo const &)
{
    LIFT_STUB(0x586da0);
}

// 0x5871b0
::GameFailReason __cdecl QuestJournal::ChangeToReplayEpic(unsigned short)
{
    LIFT_STUB(0x5871b0);
}

// 0x587bd0
bool __cdecl QuestJournal::warpToZonePcspawn(unsigned __int64, unsigned __int64, unsigned __int64, unsigned __int64, unsigned __int64)
{
    LIFT_STUB(0x587bd0);
}

// 0x587d20
__int64 __cdecl QuestJournal::ConvertCategoryToGameLogCategory(char)
{
    LIFT_STUB(0x587d20);
}

// 0x587da0
bool __cdecl QuestJournal::checkContentQuota(char, unsigned short)
{
    LIFT_STUB(0x587da0);
}

// 0x587e20
void __cdecl QuestJournal::consumeContentQuota(char)
{
    LIFT_STUB(0x587e20);
}

// 0x587ef0
bool __cdecl QuestJournal::AcqurireLastJumpingQuest(void)
{
    LIFT_STUB(0x587ef0);
}

// 0x588000
bool __cdecl QuestJournal::CompleteJumpingQuest(unsigned short, __int64 &, bool &)
{
    LIFT_STUB(0x588000);
}

// 0x5882d0
void __cdecl QuestJournal::SetInfoForJumpingCharacterGameLog(short &, char &)
{
    LIFT_STUB(0x5882d0);
}

// 0x588330
bool __cdecl QuestJournal::completeJumpingQuest(::QuestJournal::QuestRequestInfo const &, ::Quest const *, ::QuestJournal::RewardList &, ::QuestJournal::RequestFromType)
{
    LIFT_STUB(0x588330);
}

// 0x5885e0
void __cdecl QuestJournal::checkRewardForJumpingCharacter(unsigned short, unsigned __int64 *const, int, ::QuestJournal::RewardList &)
{
    LIFT_STUB(0x5885e0);
}

// 0x588760
void __cdecl QuestJournal::giveSkillForJumpingCharacter(::QuestJournal::RewardList &)
{
    LIFT_STUB(0x588760);
}
