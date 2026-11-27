// questjournal.h: questjournal.cpp, questjournal.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"
#include "inventory.h"
#include "questlist.h"

class OpenQuest
{
public:
    __cdecl OpenQuest(void);  // 0x454cb0
private:
    long __cdecl getDaemonUpTimeSec(void);  // 0x454d30
public:
    bool __cdecl Initialize(::Pc *, ::Quest const *, int, char, char);  // 0x55bab0
    bool __cdecl GetRegister(int, __int64 *) const;  // 0x55bd80
    bool __cdecl SetRegister(int, __int64);  // 0x55be30
    bool __cdecl AttachQuestEffect(::Pc *);  // 0x55c030
    bool __cdecl DetachQuestEffect(::Pc *);  // 0x55c280
    short __cdecl FetchAll(char *, short) const;  // 0x55c350
    short __cdecl FetchDb(char *, short) const;  // 0x55c3e0
    char __cdecl GetCurrentMissionStep(void) const;  // 0x55c460
    bool __cdecl SetCurrentMissionStep(::Pc *, char);  // 0x55c490
    char __cdecl GetCurrentMissionVariation(void) const;  // 0x55c5c0
    char __cdecl GetRewardMultiplicationFactor(void) const;  // 0x55c5f0
    bool __cdecl IsCompleteMission(char) const;  // 0x55c620
    bool __cdecl CompleteMission(char);  // 0x55c6a0
    bool __cdecl CanBeCompletedMissionStep(char) const;  // 0x55c720
    bool __cdecl RollbackMissionStep(::Pc *, ::Data::QuestMission *);  // 0x55c840
    void __cdecl LogProp(::Log::Type, unsigned __int64, wchar_t const *, int, wchar_t const *, ...) const;  // 0x55c8f0
    void __cdecl LogCurrentProp(unsigned __int64) const;  // 0x55caf0
    bool __cdecl CheckValidMissionStepTimeLimit(void);  // 0x55cdc0
    bool __cdecl IsTimeLimitMissionStep(void);  // 0x55ce80
private:
    unsigned short __cdecl getMissionCompletionFieldId(char) const;  // 0x55cf10
    unsigned short __cdecl getMissionValueFieldId(char) const;  // 0x55d090
};

class QuestJournal
{
public:
    struct LossList {};
    struct QuestContext {};
    struct QuestRequestInfo {};
    enum RequestFromType {};
    struct RequiredItemLoss {};
    struct RewardList;
    struct StDayOfWeekFixedReward {};
    struct StFixedReward {};
    struct StOptioanlReward {};
private:
    int __cdecl findQuestIndex(unsigned short) const;  // 0x454d70
public:
    __cdecl QuestJournal(void);  // 0x55d210
    __cdecl ~QuestJournal(void);  // 0x55d330
    static bool __cdecl InitializeCaseMapping(void);  // 0x55d3d0
    bool __cdecl IsComplete(unsigned short) const;  // 0x55d640
    ::OpenQuest * __cdecl GetOpenQuest(unsigned short) const;  // 0x55d800
private:
    ::GameFailReason __cdecl checkExistEmptySlot(unsigned short, ::QuestJournal::RequestFromType);  // 0x55d880
    ::GameFailReason __cdecl acquire(::QuestJournal::QuestRequestInfo const &, ::ScriptEvent const *, ::QuestJournal::RequestFromType, ::QuestRequiredItems const *, bool, bool);  // 0x55db10
public:
    bool __cdecl ConfirmAcquire(__int64, unsigned __int64);  // 0x561f30
    bool __cdecl AcquireByDebugCommand(unsigned short);  // 0x562240
    bool __cdecl AcquireByBuilderCommand(unsigned short);  // 0x5622d0
    bool __cdecl AcquireByMentoring(void);  // 0x562360
    ::GameFailReason __cdecl AcquireByContentsReset(unsigned short);  // 0x5626e0
    int __cdecl Complete(unsigned short, ::QuestJournal::RequestFromType);  // 0x5627a0
private:
    ::GameFailReason __cdecl dispose(unsigned short, ::QuestJournal::RequestFromType);  // 0x562970
public:
    ::GameFailReason __cdecl RefreshSimpleQuestPack(bool, __int64 &);  // 0x562a40
    ::GameFailReason __cdecl FinishTendencyQuestPack(wchar_t const *, int);  // 0x562ee0
    ::GameFailReason __cdecl DisposeSimpleQuestPack(char, wchar_t const *, int);  // 0x562f50
    ::GameFailReason __cdecl DisposeTendencyQuestPack(char, wchar_t const *, int);  // 0x562fe0
private:
    bool __cdecl addSimpleAndTendencyQuest(bool, int);  // 0x563060
    bool __cdecl disposeSimpleQuestPack(unsigned __int64, char);  // 0x563220
    bool __cdecl isCompleteSimpleQuestPack(void);  // 0x563470
    bool __cdecl completeSimpleQuestPack(int &, short *const);  // 0x563690
    bool __cdecl acquireSimpleQuestPack(unsigned __int64, bool, short, int, short const *const);  // 0x5639c0
    ::GameFailReason __cdecl acquireTendencyQuestPack(unsigned __int64, char);  // 0x564010
    bool __cdecl disposeTendencyQuestPack(char, ::QuestJournal::RequestFromType);  // 0x564550
    void __cdecl enterTendencyField(unsigned __int64);  // 0x5648a0
    ::GameFailReason __cdecl enterTendencyFieldSimpleQuest(unsigned __int64);  // 0x5648e0
    ::GameFailReason __cdecl enterTendencyFieldTendencyQuest(unsigned __int64, wchar_t const *, int);  // 0x5649a0
public:
    bool __cdecl SaveLogoutQuest(void);  // 0x564bd0
private:
    ::GameFailReason __cdecl disposeWithOpenQuestIndex(int, ::QuestJournal::RequestFromType, short);  // 0x564d20
    void __cdecl addQuest(::OpenQuest *, int);  // 0x565ba0
    void __cdecl removeQuest(int);  // 0x565d20
public:
    bool __cdecl SetRegister(unsigned short, char, __int64, ::QuestJournal::RequestFromType);  // 0x565fb0
    bool __cdecl DiffRegister(unsigned short, char, __int64, ::QuestJournal::RequestFromType);  // 0x566050
    void __cdecl EnterZone(::EnterReason, unsigned int);  // 0x566120
    void __cdecl LeaveZone(void);  // 0x5662f0
private:
    bool __cdecl canMemberBroadcast(::Pc *, ::Pc *);  // 0x5663b0
    ::GameFailReason __cdecl missionStepFailByPartyBroadcast(unsigned short, char, ::MissionStepFail const *);  // 0x566460
public:
    int __cdecl SetDbList(short, char const *, int);  // 0x566560
    short __cdecl FetchList(short *, char *, short);  // 0x566860
    short __cdecl FetchCompleteList(char *, short);  // 0x566970
    void __cdecl FetchQuestInfoForBuilder(::FragmentPacket &);  // 0x566a00
    ::GameFailReason __cdecl GetQuestCase(::Data::QuestForwardingTypeType const &, ::QuestJournal::QuestRequestInfo const &, ::QuestCase *&);  // 0x566b60
    unsigned char __cdecl GetCompletionCount(unsigned short) const;  // 0x5670b0
    bool __cdecl HasSimpleTendencyAndFactionQuest(void) const;  // 0x567200
private:
    ::GameFailReason __cdecl findQuestContext(unsigned short, unsigned short, ::QuestJournal::QuestContext &, bool, ::QuestJournal::RequestFromType);  // 0x567350
    ::GameFailReason __cdecl checkAdvanceMissionStep(::QuestJournal::QuestContext &, char, bool, bool);  // 0x567560
public:
    ::GameFailReason __cdecl ProcessCase(::ScriptEvent const &, char, ::QuestJournal::QuestRequestInfo const &, ::QuestCase::Category, short, ::QuestJournal::RequestFromType, ::QuestRequiredItems const *, bool);  // 0x5679e0
    bool __cdecl ProcessCaseWithForwarding(::ScriptEvent const &, short, ::Data::QuestForwarding const &, ::QuestJournal::RequestFromType, bool);  // 0x568080
private:
    bool __cdecl processCaseWithForwardingToMembersInternal(::ScriptEvent const &, char, unsigned __int64, char, char, short, ::QuestJournal::RequestFromType, bool);  // 0x568190
public:
    bool __cdecl ProcessCaseWithForwardingToMembers(::ScriptEvent const &, short, ::Data::QuestForwarding const &, ::QuestJournal::RequestFromType, bool);  // 0x568430
    bool __cdecl ProcessCaseWithFactionKilledFowardingToMembers(::ScriptEvent const &);  // 0x5686e0
    bool __cdecl ProcessCaseWithDuel(::ScriptEvent const &);  // 0x568a70
private:
    ::GameFailReason __cdecl checkDistance(::QuestJournal::QuestRequestInfo const &, ::GameObject *, ::GameObject *, int, ::QuestJournal::RequestFromType, bool);  // 0x568cd0
    ::GameFailReason __cdecl progressMissionByTalked(::QuestJournal::QuestContext const &, ::QuestJournal::QuestRequestInfo const &, ::QuestCase const &, ::ScriptEvent const &, ::QuestJournal::RequestFromType, ::QuestRequiredItems const *);  // 0x568f50
    ::GameFailReason __cdecl progressMissionByApproached(::QuestJournal::QuestContext const &, ::QuestJournal::QuestRequestInfo const &, ::QuestCase const &, ::ScriptEvent const &, ::QuestJournal::RequestFromType, ::QuestRequiredItems const *);  // 0x5695f0
    ::GameFailReason __cdecl progressMissionByTalkToItem(::QuestJournal::QuestContext const &, ::QuestJournal::QuestRequestInfo const &, ::QuestCase const &, ::ScriptEvent const &, ::QuestJournal::RequestFromType, ::QuestRequiredItems const *);  // 0x569a70
    ::GameFailReason __cdecl progressMissionByTalkToSelf(::QuestJournal::QuestContext const &, ::QuestJournal::QuestRequestInfo const &, ::QuestCase const &, ::ScriptEvent const &, ::QuestJournal::RequestFromType, ::QuestRequiredItems const *);  // 0x569e90
    ::GameFailReason __cdecl progressMissionByManipulated(::QuestJournal::QuestContext const &, ::QuestJournal::QuestRequestInfo const &, ::QuestCase const &, ::ScriptEvent const &, ::QuestJournal::RequestFromType, ::QuestRequiredItems const *);  // 0x569fe0
    ::GameFailReason __cdecl progressMissionByNpcManipulate(::QuestJournal::QuestContext const &, ::QuestJournal::QuestRequestInfo const &, ::QuestCase const &, ::ScriptEvent const &, ::QuestJournal::RequestFromType, ::QuestRequiredItems const *);  // 0x56a820
    ::GameFailReason __cdecl progressMissionBySkillUsed(::QuestJournal::QuestContext const &, ::QuestJournal::QuestRequestInfo const &, ::QuestCase const &, ::ScriptEvent const &, ::QuestJournal::RequestFromType, ::QuestRequiredItems const *);  // 0x56ae40
    ::GameFailReason __cdecl progressMissionByLoot(::QuestJournal::QuestContext const &, ::QuestJournal::QuestRequestInfo const &, ::QuestCase const &, ::ScriptEvent const &, ::QuestJournal::RequestFromType, ::QuestRequiredItems const *);  // 0x56b160
    bool __cdecl getVictimInfoFromCase(::Data::QuestCaseKilled const *, ::GameObject *, ::dr_tref &);  // 0x56b550
    ::GameFailReason __cdecl progressMissionByKilled(::QuestJournal::QuestContext const &, ::QuestJournal::QuestRequestInfo const &, ::QuestCase const &, ::ScriptEvent const &, ::QuestJournal::RequestFromType, ::QuestRequiredItems const *);  // 0x56b680
    ::GameFailReason __cdecl progressMissionByFinishBlow(::QuestJournal::QuestContext const &, ::QuestJournal::QuestRequestInfo const &, ::QuestCase const &, ::ScriptEvent const &, ::QuestJournal::RequestFromType, ::QuestRequiredItems const *);  // 0x56bfa0
    ::GameFailReason __cdecl progressMissionByEnvEntered(::QuestJournal::QuestContext const &, ::QuestJournal::QuestRequestInfo const &, ::QuestCase const &, ::ScriptEvent const &, ::QuestJournal::RequestFromType, ::QuestRequiredItems const *);  // 0x56c190
    ::GameFailReason __cdecl progressMissionByEnterZone(::QuestJournal::QuestContext const &, ::QuestJournal::QuestRequestInfo const &, ::QuestCase const &, ::ScriptEvent const &, ::QuestJournal::RequestFromType, ::QuestRequiredItems const *);  // 0x56c300
    ::GameFailReason __cdecl progressMissionByNpcBleedingOccured(::QuestJournal::QuestContext const &, ::QuestJournal::QuestRequestInfo const &, ::QuestCase const &, ::ScriptEvent const &, ::QuestJournal::RequestFromType, ::QuestRequiredItems const *);  // 0x56c400
    ::GameFailReason __cdecl progressMissionByEnterPortal(::QuestJournal::QuestContext const &, ::QuestJournal::QuestRequestInfo const &, ::QuestCase const &, ::ScriptEvent const &, ::QuestJournal::RequestFromType, ::QuestRequiredItems const *);  // 0x56c590
    ::GameFailReason __cdecl progressMissionByAcquireSummoned(::QuestJournal::QuestContext const &, ::QuestJournal::QuestRequestInfo const &, ::QuestCase const &, ::ScriptEvent const &, ::QuestJournal::RequestFromType, ::QuestRequiredItems const *);  // 0x56ca00
    ::GameFailReason __cdecl progressMissionByPcSocial(::QuestJournal::QuestContext const &, ::QuestJournal::QuestRequestInfo const &, ::QuestCase const &, ::ScriptEvent const &, ::QuestJournal::RequestFromType, ::QuestRequiredItems const *);  // 0x56cc10
    ::GameFailReason __cdecl progressMissionByJoinFaction(::QuestJournal::QuestContext const &, ::QuestJournal::QuestRequestInfo const &, ::QuestCase const &, ::ScriptEvent const &, ::QuestJournal::RequestFromType, ::QuestRequiredItems const *);  // 0x56ce80
    ::GameFailReason __cdecl progressMissionByDuelFinish(::QuestJournal::QuestContext const &, ::QuestJournal::QuestRequestInfo const &, ::QuestCase const &, ::ScriptEvent const &, ::QuestJournal::RequestFromType, ::QuestRequiredItems const *);  // 0x56d680
    ::GameFailReason __cdecl progressMissionByPartyBattle(::QuestJournal::QuestContext const &, ::QuestJournal::QuestRequestInfo const &, ::QuestCase const &, ::ScriptEvent const &, ::QuestJournal::RequestFromType, ::QuestRequiredItems const *);  // 0x56d960
    ::GameFailReason __cdecl progressMissionByPartyBattleAction(::QuestJournal::QuestContext const &, ::QuestJournal::QuestRequestInfo const &, ::QuestCase const &, ::ScriptEvent const &, ::QuestJournal::RequestFromType, ::QuestRequiredItems const *);  // 0x56db30
    ::GameFailReason __cdecl progressMissionByCompleteQuest(::QuestJournal::QuestContext const &, ::QuestJournal::QuestRequestInfo const &, ::QuestCase const &, ::ScriptEvent const &, ::QuestJournal::RequestFromType, ::QuestRequiredItems const *);  // 0x56dc00
    ::GameFailReason __cdecl progressMissionByBattleRoyal(::QuestJournal::QuestContext const &, ::QuestJournal::QuestRequestInfo const &, ::QuestCase const &, ::ScriptEvent const &, ::QuestJournal::RequestFromType, ::QuestRequiredItems const *);  // 0x56dd40
    ::GameFailReason __cdecl progressMissionByConvoyArrived(::QuestJournal::QuestContext const &, ::QuestJournal::QuestRequestInfo const &, ::QuestCase const &, ::ScriptEvent const &, ::QuestJournal::RequestFromType, ::QuestRequiredItems const *);  // 0x56ddf0
    ::GameFailReason __cdecl checkProgressConvoy(::QuestJournal::QuestContext const &, ::QuestCase const &, ::Convoy **, ::Npc **const);  // 0x56dec0
    ::GameFailReason __cdecl progressMission(::QuestJournal::QuestContext const &, ::QuestJournal::QuestRequestInfo const &, ::QuestCase const &, char, ::QuestJournal::RequestFromType, bool, ::QuestJournal::RequiredItemLoss const *);  // 0x56e080
    ::GameFailReason __cdecl progressMissionInternal(::QuestJournal::QuestContext const &, ::QuestJournal::QuestRequestInfo const &, ::QuestCase const &, char, ::QuestJournal::RequestFromType, bool, ::QuestJournal::RequiredItemLoss const *);  // 0x56e870
    ::GameFailReason __cdecl progressMissionByTutorialCase(::QuestJournal::QuestContext const &, ::QuestJournal::QuestRequestInfo const &, ::QuestCase const &, ::ScriptEvent const &, ::QuestJournal::RequestFromType, ::QuestRequiredItems const *);  // 0x5710d0
public:
    bool __cdecl CanManipulateEnv(::Data::QuestForwarding const &, int, ::ScriptEvent &, ::QuestRequiredItems const *);  // 0x5711c0
    bool __cdecl CanManipulateNpc(::Data::NpcRecordPtr, int, ::ScriptEvent &, ::QuestRequiredItems const *);  // 0x5718f0
    bool __cdecl CanUseSkill(unsigned __int64, char, char, ::GameObject *, ::ScriptEvent const &);  // 0x571f90
private:
    bool __cdecl checkValidZonePhase(char, ::Data::ZoneRecordPtr, unsigned short, char, char);  // 0x572280
public:
    int __cdecl SelectTransitDestination(unsigned __int64 const *const, char const *const, int, int, ::Data::ZoneRecordPtr);  // 0x572310
    int __cdecl SelectTransitDestinationForDungeon(unsigned __int64 const *const, char const *const, int, int, unsigned short, char);  // 0x5726d0
    char __cdecl GetDungeonQuestCurrentMissionStep(unsigned __int64);  // 0x572a60
    bool __cdecl ProgressMissionByPartyDungeonStep(short, char);  // 0x572b30
    static bool __cdecl IsRewardRestrictedCase(::QuestCase const &);  // 0x572fa0
private:
    static bool __cdecl validateQuestId(unsigned short);  // 0x573010
    bool __cdecl isScriptableCase(short);  // 0x5730a0
public:
    bool __cdecl ProcessRollbackCase(::ScriptEvent const &, unsigned short, char, char);  // 0x5730f0
    bool __cdecl ProcessMissionStepTimeLimitFail(unsigned short, char, bool);  // 0x5734b0
private:
    bool __cdecl processMissionStepFail(::OpenQuest *, int, bool, bool, ::MissionStepFail const *);  // 0x573720
    bool __cdecl rollbackMissionStep(::OpenQuest *, char);  // 0x573f60
    bool __cdecl completeOpenQuest(::QuestJournal::QuestRequestInfo const &, int, ::QuestJournal::RequestFromType);  // 0x574160
    bool __cdecl completeQuest(::QuestJournal::QuestRequestInfo const &, ::Quest const *, ::QuestJournal::RequestFromType);  // 0x574220
    bool __cdecl acquireNextQuest(::Quest const *);  // 0x574fb0
    bool __cdecl setQuestCompletionBit(unsigned short);  // 0x5750b0
    ::GameFailReason __cdecl completeMission(::QuestJournal::QuestContext const &, ::QuestJournal::QuestRequestInfo const &, bool &, ::QuestJournal::RequestFromType);  // 0x575260
    void __cdecl notifyAcquire(unsigned short, char, char, char);  // 0x575de0
    void __cdecl notifyChange(::QuestJournal::QuestRequestInfo const &, ::OpenQuest const *);  // 0x575e70
    bool __cdecl checkAcquisitionFilter(::Acquisition const *, ::QuestCase const *, ::ScriptEvent const &) const;  // 0x576060
    bool __cdecl checkFilterSetArray(::QuestFilterSet const *, int, ::ScriptEvent const &) const;  // 0x5766b0
    ::GameFailReason __cdecl checkNormalCaseCondition(::Data::QuestCase const *, ::Data::QuestQuest const *, bool);  // 0x576830
    bool __cdecl checkZone(::QuestCase const *);  // 0x576950
    bool __cdecl checkGadget(::Data::QuestCase const *);  // 0x576a10
    bool __cdecl checkGrocery(unsigned __int64, short, short, unsigned __int64, short, bool, bool &, ::Inventory::DisposeOrderWithPos &, ::QuestJournal::QuestRequestInfo const &);  // 0x576a70
    bool __cdecl checkRequiredItems(::QuestRequiredItems const *, ::QuestCase const &, ::QuestJournal::RequiredItemLoss &, ::QuestJournal::QuestRequestInfo const &);  // 0x576c40
    bool __cdecl checkRequiredBrandItems(::QuestRequiredItems const *, char, int, unsigned __int64 const *const, ::QuestJournal::QuestRequestInfo const &);  // 0x5778a0
    bool __cdecl checkRequiredEquipGems(::QuestRequiredItems const *, unsigned __int64, ::QuestJournal::QuestRequestInfo const &);  // 0x577e10
    bool __cdecl checkRequiredJumpingCharacterState(char, ::QuestJournal::QuestRequestInfo const &);  // 0x578260
    ::GameFailReason __cdecl checkLossAndReward(::QuestJournal::QuestContext const &, ::QuestCase const *, char, bool, ::QuestJournal::LossList &, ::QuestJournal::RewardList &, ::MentorRewardPostParam *, ::QuestJournal::RequiredItemLoss const *);  // 0x578380
    void __cdecl giveLossAndReward(::QuestJournal::LossList &, ::QuestJournal::RewardList &, ::MentorRewardPostParam *, ::QuestJournal::RequiredItemLoss const *);  // 0x578710
    ::GameFailReason __cdecl checkCompletionLoss(unsigned short, ::Mission const *, ::QuestJournal::LossList &, ::QuestJournal::RequiredItemLoss const *);  // 0x578960
    void __cdecl takeCompletionLoss(::QuestJournal::LossList &, ::QuestJournal::RequiredItemLoss const *);  // 0x578c80
    ::GameFailReason __cdecl checkAcquisitionLoss(unsigned short, ::Acquisition const *, ::QuestJournal::LossList &, ::QuestJournal::RequiredItemLoss const *);  // 0x578f00
    void __cdecl takeAcquisitionLoss(::QuestJournal::LossList &, ::QuestJournal::RequiredItemLoss const *);  // 0x5791a0
    void __cdecl takeGiveupLoss(::Quest const *);  // 0x579420
    ::GameFailReason __cdecl checkCaseLoss(::QuestJournal::RequiredItemLoss const *);  // 0x579e70
    void __cdecl takeCaseLoss(::QuestJournal::RequiredItemLoss const *);  // 0x579f20
    int __cdecl calcQuestRewardExpBonus(unsigned short, int);  // 0x57a090
    int __cdecl calcQuestRewardExpBonusTestServer(int);  // 0x57a110
    int __cdecl calcQuestRewardExpBonusGradeBenefit(unsigned short, int);  // 0x57a170
    ::GameFailReason __cdecl checkReward(::QuestNewbieState, bool, bool, bool, unsigned short, ::QuestReward const *, unsigned __int64 *&, int, char, ::QuestJournal::RewardList &, char, ::MentorRewardPostParam *);  // 0x57a200
    void __cdecl giveReward(::QuestJournal::RewardList &, ::MentorRewardPostParam *);  // 0x57bda0
    ::GameFailReason __cdecl getFixedReward(unsigned short, ::Data::QuestFixedReward *, ::Inventory::AcquireOrder *const, int &);  // 0x57d2a0
    ::GameFailReason __cdecl getDisjoinedFixedReward(unsigned short, ::QuestJournal::StFixedReward &, ::Inventory::AcquireOrder *const, int &);  // 0x57d3e0
    ::GameFailReason __cdecl getRewardSlot(unsigned short, ::dr_tref *, char, ::Inventory::AcquireOrder *const, int &);  // 0x57d540
    bool __cdecl getDayOfWeeklFixedReward(unsigned short, ::QuestJournal::StDayOfWeekFixedReward &, ::Inventory::AcquireOrder *const, int &);  // 0x57d640
    bool __cdecl getNewbieReward(unsigned short, ::Data::QuestRewardRecordPtr, ::Inventory::AcquireOrder *const, char *const, int &);  // 0x57d730
    bool __cdecl getOldbieReward(unsigned short, ::Data::QuestRewardRecordPtr, ::Inventory::AcquireOrder *const, char *const, int &);  // 0x57d880
    bool __cdecl getAdditionalRewardItem(unsigned short, int, unsigned __int64 *const, short *const, ::Inventory::AcquireOrder *const, int &, bool &);  // 0x57d9d0
    bool __cdecl checkPcCondition(int, unsigned __int64 const *const, int, char const *const, int, char const *const, int, char const *const) const;  // 0x57daf0
    bool __cdecl checkPcDifficultyType(char);  // 0x57dc70
    unsigned char __cdecl diffCompletionCount(unsigned short, char, char);  // 0x57dcb0
    ::GameFailReason __cdecl setRegister(::QuestJournal::QuestContext &, __int64, ::QuestJournal::RequestFromType);  // 0x57dff0
    bool __cdecl completeMissionManage(::QuestJournal::RequestFromType, unsigned short, char, char);  // 0x57e450
    int __cdecl resetQuestManage(::QuestJournal::RequestFromType, unsigned short);  // 0x57e8d0
    bool __cdecl resetQuestAllManage(::QuestJournal::RequestFromType);  // 0x57eb40
    int __cdecl rollbackMissionStepManage(::QuestJournal::RequestFromType, unsigned short, char);  // 0x57ee00
    bool __cdecl setQuestCompletionTime(unsigned short, __int64);  // 0x57eef0
    bool __cdecl checkCompletionTime(::Quest const *);  // 0x57efa0
public:
    bool __cdecl CheckTimeForResetByAcquireTime(::Quest const *);  // 0x57f000
private:
    bool __cdecl getCompletionTypeInfo(::Data::QuestQuest const *, ::QuestList::CompletionTimeTypeSequence &, int &);  // 0x57f060
    bool __cdecl setQuestCompletionDay(::Data::QuestQuest const *, __int64);  // 0x57f330
    bool __cdecl setQuestCompletionDayInternal(unsigned short, ::QuestList::CompletionTimeTypeSequence, int, __int64);  // 0x57f3f0
    bool __cdecl deleteCompletionDay(::Data::QuestQuest const *);  // 0x57f8d0
    int __cdecl getQuestCompletionDay(::Data::QuestQuest const *);  // 0x57fcd0
    int __cdecl getQuestCompletionDayInternal(unsigned short, ::QuestList::CompletionTimeTypeSequence);  // 0x57fd90
    bool __cdecl checkCompletionDay(::Data::QuestQuest const *);  // 0x57ffd0
    unsigned short __cdecl getCompletionDayByResetHourFromTime(__int64, char, char);  // 0x580270
    bool __cdecl isDeleteTimeForCompletionTime(char, char);  // 0x580340
    bool __cdecl checkAndDeleteCompletionTimeGarbage(::Data::QuestQuest const *);  // 0x580440
    bool __cdecl deleteCompletionTimeGarbage(void);  // 0x580490
    int __cdecl getCompletedQuestCountByResetType(char);  // 0x5809f0
public:
    bool __cdecl SetChallengeListRewardCompleted(__int64, char);  // 0x580d10
    bool __cdecl HasFactionQuest(char);  // 0x580f00
private:
    void __cdecl sendUpdateQuestToCacheChannel(::OpenQuest const *);  // 0x580f50
public:
    bool __cdecl AddLeaveZoneRollbackQuestIndex(int);  // 0x580fc0
    bool __cdecl RemoveLeaveZoneRollbackQuestIndex(int);  // 0x581080
private:
    void __cdecl processLeaveZoneRollback(void);  // 0x5810f0
public:
    void __cdecl RollbackByRemoveFielditem(unsigned int);  // 0x581260
private:
    bool __cdecl resetBindDungeonQuest(int);  // 0x5813d0
    bool __cdecl updatePartyDungeonStep(unsigned short, char);  // 0x5814b0
    void __cdecl disposeUnbindDungeonQuest(void);  // 0x581620
public:
    static bool __cdecl GetQuestFixedRewardByIndex(int, ::Data::QuestRewardRecordPtr, ::QuestJournal::StFixedReward &);  // 0x581800
    static bool __cdecl GetQuestOptionalRewardByIndex(int, ::Data::QuestRewardRecordPtr, ::QuestJournal::StOptioanlReward &);  // 0x581da0
    static bool __cdecl GetQuestDayOfWeekFixedReward(int, ::Data::QuestRewardRecordPtr, ::QuestJournal::StDayOfWeekFixedReward &);  // 0x582340
private:
    __int64 __cdecl calcCaseFee(void);  // 0x582500
public:
    ::GameFailReason __cdecl DungeonProgressToStepN(short, unsigned short, char, __int64, int, ::Inventory::DisposeOrderWithPos const *const);  // 0x582570
    unsigned short __cdecl GetValidDungeonQuestId(::Data::DungeonRecordPtr);  // 0x583850
private:
    bool __cdecl isValidBroadcastCategoryForProgress(unsigned short);  // 0x583970
    bool __cdecl addDuelQuestIdx(int, ::Quest const *);  // 0x583ac0
    bool __cdecl removeDuelQuestIdx(int, ::Quest const *);  // 0x583ba0
    bool __cdecl checkDuelCurrentStraightWin(char, char, int, ::QuestJournal::QuestRequestInfo const &);  // 0x583c70
    bool __cdecl removeAttrationQuest(int);  // 0x583ce0
public:
    void __cdecl LeaveEnterAttraction(::dr_tref, ::dr_tref);  // 0x583d40
    ::GameFailReason __cdecl ResetQuestCompletionTime(unsigned short, int, ::Inventory::DisposeOrderWithPos const *const);  // 0x5843b0
    bool __cdecl CheckToExistFaction2NextEpic(char, char, unsigned short &);  // 0x585820
    bool __cdecl TransferFaction2Epic(char, unsigned short);  // 0x585b50
private:
    ::GameFailReason __cdecl disposeWithOpenQuestIndexForce(int);  // 0x585d00
    bool __cdecl checkPcConditionWithParam(int, unsigned __int64 const *const, int, char const *const, int, char const *const, int, char const *const, char, char, char, char, char) const;  // 0x5860d0
    ::GameFailReason __cdecl checkQuestValidDateTime(::Data::QuestQuest const *, bool);  // 0x5861b0
public:
    ::GameFailReason __cdecl ProgressRetiredMissionStep(unsigned short, char);  // 0x586490
    static ::Data::QuestMissionStep const * __cdecl GetNextMissionstepRecord(char, ::Quest const *);  // 0x586d50
private:
    void __cdecl gameLogCompleteMissionStep(::Data::QuestQuest const *, char, ::QuestJournal::QuestRequestInfo const &);  // 0x586da0
public:
    ::GameFailReason __cdecl ChangeToReplayEpic(unsigned short);  // 0x5871b0
private:
    bool __cdecl warpToZonePcspawn(unsigned __int64, unsigned __int64, unsigned __int64, unsigned __int64, unsigned __int64);  // 0x587bd0
public:
    static __int64 __cdecl ConvertCategoryToGameLogCategory(char);  // 0x587d20
private:
    bool __cdecl checkContentQuota(char, unsigned short);  // 0x587da0
    void __cdecl consumeContentQuota(char);  // 0x587e20
public:
    bool __cdecl AcqurireLastJumpingQuest(void);  // 0x587ef0
    bool __cdecl CompleteJumpingQuest(unsigned short, __int64 &, bool &);  // 0x588000
    void __cdecl SetInfoForJumpingCharacterGameLog(short &, char &);  // 0x5882d0
private:
    bool __cdecl completeJumpingQuest(::QuestJournal::QuestRequestInfo const &, ::Quest const *, ::QuestJournal::RewardList &, ::QuestJournal::RequestFromType);  // 0x588330
    void __cdecl checkRewardForJumpingCharacter(unsigned short, unsigned __int64 *const, int, ::QuestJournal::RewardList &);  // 0x5885e0
    void __cdecl giveSkillForJumpingCharacter(::QuestJournal::RewardList &);  // 0x588760
};

struct QuestJournal::RewardList
{
public:
    __cdecl RewardList(void);  // 0x57e350
};

