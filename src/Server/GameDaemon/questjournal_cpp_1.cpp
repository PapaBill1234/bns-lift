// questjournal_cpp_1.cpp: questjournal.cpp part 1 (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "questjournal.h"
#include "convoy.h"
#include "gameobject.h"
#include "npc.h"
#include "pc.h"
#include "LiftStub.h"

// 0x55bab0
bool __cdecl OpenQuest::Initialize(::Pc *, ::Quest const *, int, char, char)
{
    LIFT_STUB(0x55bab0);
}

// 0x55bd80
bool __cdecl OpenQuest::GetRegister(int, __int64 *) const
{
    LIFT_STUB(0x55bd80);
}

// 0x55be30
bool __cdecl OpenQuest::SetRegister(int, __int64)
{
    LIFT_STUB(0x55be30);
}

// 0x55c030
bool __cdecl OpenQuest::AttachQuestEffect(::Pc *)
{
    LIFT_STUB(0x55c030);
}

// 0x55c280
bool __cdecl OpenQuest::DetachQuestEffect(::Pc *)
{
    LIFT_STUB(0x55c280);
}

// 0x55c350
short __cdecl OpenQuest::FetchAll(char *, short) const
{
    LIFT_STUB(0x55c350);
}

// 0x55c3e0
short __cdecl OpenQuest::FetchDb(char *, short) const
{
    LIFT_STUB(0x55c3e0);
}

// 0x55c460
char __cdecl OpenQuest::GetCurrentMissionStep(void) const
{
    LIFT_STUB(0x55c460);
}

// 0x55c490
bool __cdecl OpenQuest::SetCurrentMissionStep(::Pc *, char)
{
    LIFT_STUB(0x55c490);
}

// 0x55c5c0
char __cdecl OpenQuest::GetCurrentMissionVariation(void) const
{
    LIFT_STUB(0x55c5c0);
}

// 0x55c5f0
char __cdecl OpenQuest::GetRewardMultiplicationFactor(void) const
{
    LIFT_STUB(0x55c5f0);
}

// 0x55c620
bool __cdecl OpenQuest::IsCompleteMission(char) const
{
    LIFT_STUB(0x55c620);
}

// 0x55c6a0
bool __cdecl OpenQuest::CompleteMission(char)
{
    LIFT_STUB(0x55c6a0);
}

// 0x55c720
bool __cdecl OpenQuest::CanBeCompletedMissionStep(char) const
{
    LIFT_STUB(0x55c720);
}

// 0x55c840
bool __cdecl OpenQuest::RollbackMissionStep(::Pc *, ::Data::QuestMission *)
{
    LIFT_STUB(0x55c840);
}

// 0x55c8f0
void __cdecl OpenQuest::LogProp(::Log::Type, unsigned __int64, wchar_t const *, int, wchar_t const *, ...) const
{
    LIFT_STUB(0x55c8f0);
}

// 0x55caf0
void __cdecl OpenQuest::LogCurrentProp(unsigned __int64) const
{
    LIFT_STUB(0x55caf0);
}

// 0x55cdc0
bool __cdecl OpenQuest::CheckValidMissionStepTimeLimit(void)
{
    LIFT_STUB(0x55cdc0);
}

// 0x55ce80
bool __cdecl OpenQuest::IsTimeLimitMissionStep(void)
{
    LIFT_STUB(0x55ce80);
}

// 0x55cf10
unsigned short __cdecl OpenQuest::getMissionCompletionFieldId(char) const
{
    LIFT_STUB(0x55cf10);
}

// 0x55d090
unsigned short __cdecl OpenQuest::getMissionValueFieldId(char) const
{
    LIFT_STUB(0x55d090);
}

// 0x55d210
__cdecl QuestJournal::QuestJournal(void)
{
    LIFT_STUB(0x55d210);
}

// 0x55d330
__cdecl QuestJournal::~QuestJournal(void)
{
    LIFT_STUB(0x55d330);
}

// 0x55d3d0
bool __cdecl QuestJournal::InitializeCaseMapping(void)
{
    LIFT_STUB(0x55d3d0);
}

// 0x55d640
bool __cdecl QuestJournal::IsComplete(unsigned short) const
{
    LIFT_STUB(0x55d640);
}

// 0x55d800
::OpenQuest * __cdecl QuestJournal::GetOpenQuest(unsigned short) const
{
    LIFT_STUB(0x55d800);
}

// 0x55d880
::GameFailReason __cdecl QuestJournal::checkExistEmptySlot(unsigned short, ::QuestJournal::RequestFromType)
{
    LIFT_STUB(0x55d880);
}

// 0x55db10
::GameFailReason __cdecl QuestJournal::acquire(::QuestJournal::QuestRequestInfo const &, ::ScriptEvent const *, ::QuestJournal::RequestFromType, ::QuestRequiredItems const *, bool, bool)
{
    LIFT_STUB(0x55db10);
}

// 0x561f30
bool __cdecl QuestJournal::ConfirmAcquire(__int64, unsigned __int64)
{
    LIFT_STUB(0x561f30);
}

// 0x562240
bool __cdecl QuestJournal::AcquireByDebugCommand(unsigned short)
{
    LIFT_STUB(0x562240);
}

// 0x5622d0
bool __cdecl QuestJournal::AcquireByBuilderCommand(unsigned short)
{
    LIFT_STUB(0x5622d0);
}

// 0x562360
bool __cdecl QuestJournal::AcquireByMentoring(void)
{
    LIFT_STUB(0x562360);
}

// 0x5626e0
::GameFailReason __cdecl QuestJournal::AcquireByContentsReset(unsigned short)
{
    LIFT_STUB(0x5626e0);
}

// 0x5627a0
int __cdecl QuestJournal::Complete(unsigned short, ::QuestJournal::RequestFromType)
{
    LIFT_STUB(0x5627a0);
}

// 0x562970
::GameFailReason __cdecl QuestJournal::dispose(unsigned short, ::QuestJournal::RequestFromType)
{
    LIFT_STUB(0x562970);
}

// 0x562a40
::GameFailReason __cdecl QuestJournal::RefreshSimpleQuestPack(bool, __int64 &)
{
    LIFT_STUB(0x562a40);
}

// 0x562ee0
::GameFailReason __cdecl QuestJournal::FinishTendencyQuestPack(wchar_t const *, int)
{
    LIFT_STUB(0x562ee0);
}

// 0x562f50
::GameFailReason __cdecl QuestJournal::DisposeSimpleQuestPack(char, wchar_t const *, int)
{
    LIFT_STUB(0x562f50);
}

// 0x562fe0
::GameFailReason __cdecl QuestJournal::DisposeTendencyQuestPack(char, wchar_t const *, int)
{
    LIFT_STUB(0x562fe0);
}

// 0x563060
bool __cdecl QuestJournal::addSimpleAndTendencyQuest(bool, int)
{
    LIFT_STUB(0x563060);
}

// 0x563220
bool __cdecl QuestJournal::disposeSimpleQuestPack(unsigned __int64, char)
{
    LIFT_STUB(0x563220);
}

// 0x563470
bool __cdecl QuestJournal::isCompleteSimpleQuestPack(void)
{
    LIFT_STUB(0x563470);
}

// 0x563690
bool __cdecl QuestJournal::completeSimpleQuestPack(int &, short *const)
{
    LIFT_STUB(0x563690);
}

// 0x5639c0
bool __cdecl QuestJournal::acquireSimpleQuestPack(unsigned __int64, bool, short, int, short const *const)
{
    LIFT_STUB(0x5639c0);
}

// 0x564010
::GameFailReason __cdecl QuestJournal::acquireTendencyQuestPack(unsigned __int64, char)
{
    LIFT_STUB(0x564010);
}

// 0x564550
bool __cdecl QuestJournal::disposeTendencyQuestPack(char, ::QuestJournal::RequestFromType)
{
    LIFT_STUB(0x564550);
}

// 0x5648a0
void __cdecl QuestJournal::enterTendencyField(unsigned __int64)
{
    LIFT_STUB(0x5648a0);
}

// 0x5648e0
::GameFailReason __cdecl QuestJournal::enterTendencyFieldSimpleQuest(unsigned __int64)
{
    LIFT_STUB(0x5648e0);
}

// 0x5649a0
::GameFailReason __cdecl QuestJournal::enterTendencyFieldTendencyQuest(unsigned __int64, wchar_t const *, int)
{
    LIFT_STUB(0x5649a0);
}

// 0x564bd0
bool __cdecl QuestJournal::SaveLogoutQuest(void)
{
    LIFT_STUB(0x564bd0);
}

// 0x564d20
::GameFailReason __cdecl QuestJournal::disposeWithOpenQuestIndex(int, ::QuestJournal::RequestFromType, short)
{
    LIFT_STUB(0x564d20);
}

// 0x565ba0
void __cdecl QuestJournal::addQuest(::OpenQuest *, int)
{
    LIFT_STUB(0x565ba0);
}

// 0x565d20
void __cdecl QuestJournal::removeQuest(int)
{
    LIFT_STUB(0x565d20);
}

// 0x565fb0
bool __cdecl QuestJournal::SetRegister(unsigned short, char, __int64, ::QuestJournal::RequestFromType)
{
    LIFT_STUB(0x565fb0);
}

// 0x566050
bool __cdecl QuestJournal::DiffRegister(unsigned short, char, __int64, ::QuestJournal::RequestFromType)
{
    LIFT_STUB(0x566050);
}

// 0x566120
void __cdecl QuestJournal::EnterZone(::EnterReason, unsigned int)
{
    LIFT_STUB(0x566120);
}

// 0x5662f0
void __cdecl QuestJournal::LeaveZone(void)
{
    LIFT_STUB(0x5662f0);
}

// 0x5663b0
bool __cdecl QuestJournal::canMemberBroadcast(::Pc *, ::Pc *)
{
    LIFT_STUB(0x5663b0);
}

// 0x566460
::GameFailReason __cdecl QuestJournal::missionStepFailByPartyBroadcast(unsigned short, char, ::MissionStepFail const *)
{
    LIFT_STUB(0x566460);
}

// 0x566560
int __cdecl QuestJournal::SetDbList(short, char const *, int)
{
    LIFT_STUB(0x566560);
}

// 0x566860
short __cdecl QuestJournal::FetchList(short *, char *, short)
{
    LIFT_STUB(0x566860);
}

// 0x566970
short __cdecl QuestJournal::FetchCompleteList(char *, short)
{
    LIFT_STUB(0x566970);
}

// 0x566a00
void __cdecl QuestJournal::FetchQuestInfoForBuilder(::FragmentPacket &)
{
    LIFT_STUB(0x566a00);
}

// 0x566b60
::GameFailReason __cdecl QuestJournal::GetQuestCase(::Data::QuestForwardingTypeType const &, ::QuestJournal::QuestRequestInfo const &, ::QuestCase *&)
{
    LIFT_STUB(0x566b60);
}

// 0x5670b0
unsigned char __cdecl QuestJournal::GetCompletionCount(unsigned short) const
{
    LIFT_STUB(0x5670b0);
}

// 0x567200
bool __cdecl QuestJournal::HasSimpleTendencyAndFactionQuest(void) const
{
    LIFT_STUB(0x567200);
}

// 0x567350
::GameFailReason __cdecl QuestJournal::findQuestContext(unsigned short, unsigned short, ::QuestJournal::QuestContext &, bool, ::QuestJournal::RequestFromType)
{
    LIFT_STUB(0x567350);
}

// 0x567560
::GameFailReason __cdecl QuestJournal::checkAdvanceMissionStep(::QuestJournal::QuestContext &, char, bool, bool)
{
    LIFT_STUB(0x567560);
}

// 0x5679e0
::GameFailReason __cdecl QuestJournal::ProcessCase(::ScriptEvent const &, char, ::QuestJournal::QuestRequestInfo const &, ::QuestCase::Category, short, ::QuestJournal::RequestFromType, ::QuestRequiredItems const *, bool)
{
    LIFT_STUB(0x5679e0);
}

// 0x568080
bool __cdecl QuestJournal::ProcessCaseWithForwarding(::ScriptEvent const &, short, ::Data::QuestForwarding const &, ::QuestJournal::RequestFromType, bool)
{
    LIFT_STUB(0x568080);
}

// 0x568190
bool __cdecl QuestJournal::processCaseWithForwardingToMembersInternal(::ScriptEvent const &, char, unsigned __int64, char, char, short, ::QuestJournal::RequestFromType, bool)
{
    LIFT_STUB(0x568190);
}

// 0x568430
bool __cdecl QuestJournal::ProcessCaseWithForwardingToMembers(::ScriptEvent const &, short, ::Data::QuestForwarding const &, ::QuestJournal::RequestFromType, bool)
{
    LIFT_STUB(0x568430);
}

// 0x5686e0
bool __cdecl QuestJournal::ProcessCaseWithFactionKilledFowardingToMembers(::ScriptEvent const &)
{
    LIFT_STUB(0x5686e0);
}

// 0x568a70
bool __cdecl QuestJournal::ProcessCaseWithDuel(::ScriptEvent const &)
{
    LIFT_STUB(0x568a70);
}

// 0x568cd0
::GameFailReason __cdecl QuestJournal::checkDistance(::QuestJournal::QuestRequestInfo const &, ::GameObject *, ::GameObject *, int, ::QuestJournal::RequestFromType, bool)
{
    LIFT_STUB(0x568cd0);
}

// 0x568f50
::GameFailReason __cdecl QuestJournal::progressMissionByTalked(::QuestJournal::QuestContext const &, ::QuestJournal::QuestRequestInfo const &, ::QuestCase const &, ::ScriptEvent const &, ::QuestJournal::RequestFromType, ::QuestRequiredItems const *)
{
    LIFT_STUB(0x568f50);
}

// 0x5695f0
::GameFailReason __cdecl QuestJournal::progressMissionByApproached(::QuestJournal::QuestContext const &, ::QuestJournal::QuestRequestInfo const &, ::QuestCase const &, ::ScriptEvent const &, ::QuestJournal::RequestFromType, ::QuestRequiredItems const *)
{
    LIFT_STUB(0x5695f0);
}

// 0x569a70
::GameFailReason __cdecl QuestJournal::progressMissionByTalkToItem(::QuestJournal::QuestContext const &, ::QuestJournal::QuestRequestInfo const &, ::QuestCase const &, ::ScriptEvent const &, ::QuestJournal::RequestFromType, ::QuestRequiredItems const *)
{
    LIFT_STUB(0x569a70);
}

// 0x569e90
::GameFailReason __cdecl QuestJournal::progressMissionByTalkToSelf(::QuestJournal::QuestContext const &, ::QuestJournal::QuestRequestInfo const &, ::QuestCase const &, ::ScriptEvent const &, ::QuestJournal::RequestFromType, ::QuestRequiredItems const *)
{
    LIFT_STUB(0x569e90);
}

// 0x569fe0
::GameFailReason __cdecl QuestJournal::progressMissionByManipulated(::QuestJournal::QuestContext const &, ::QuestJournal::QuestRequestInfo const &, ::QuestCase const &, ::ScriptEvent const &, ::QuestJournal::RequestFromType, ::QuestRequiredItems const *)
{
    LIFT_STUB(0x569fe0);
}

// 0x56a820
::GameFailReason __cdecl QuestJournal::progressMissionByNpcManipulate(::QuestJournal::QuestContext const &, ::QuestJournal::QuestRequestInfo const &, ::QuestCase const &, ::ScriptEvent const &, ::QuestJournal::RequestFromType, ::QuestRequiredItems const *)
{
    LIFT_STUB(0x56a820);
}

// 0x56ae40
::GameFailReason __cdecl QuestJournal::progressMissionBySkillUsed(::QuestJournal::QuestContext const &, ::QuestJournal::QuestRequestInfo const &, ::QuestCase const &, ::ScriptEvent const &, ::QuestJournal::RequestFromType, ::QuestRequiredItems const *)
{
    LIFT_STUB(0x56ae40);
}

// 0x56b160
::GameFailReason __cdecl QuestJournal::progressMissionByLoot(::QuestJournal::QuestContext const &, ::QuestJournal::QuestRequestInfo const &, ::QuestCase const &, ::ScriptEvent const &, ::QuestJournal::RequestFromType, ::QuestRequiredItems const *)
{
    LIFT_STUB(0x56b160);
}

// 0x56b550
bool __cdecl QuestJournal::getVictimInfoFromCase(::Data::QuestCaseKilled const *, ::GameObject *, ::dr_tref &)
{
    LIFT_STUB(0x56b550);
}

// 0x56b680
::GameFailReason __cdecl QuestJournal::progressMissionByKilled(::QuestJournal::QuestContext const &, ::QuestJournal::QuestRequestInfo const &, ::QuestCase const &, ::ScriptEvent const &, ::QuestJournal::RequestFromType, ::QuestRequiredItems const *)
{
    LIFT_STUB(0x56b680);
}

// 0x56bfa0
::GameFailReason __cdecl QuestJournal::progressMissionByFinishBlow(::QuestJournal::QuestContext const &, ::QuestJournal::QuestRequestInfo const &, ::QuestCase const &, ::ScriptEvent const &, ::QuestJournal::RequestFromType, ::QuestRequiredItems const *)
{
    LIFT_STUB(0x56bfa0);
}

// 0x56c190
::GameFailReason __cdecl QuestJournal::progressMissionByEnvEntered(::QuestJournal::QuestContext const &, ::QuestJournal::QuestRequestInfo const &, ::QuestCase const &, ::ScriptEvent const &, ::QuestJournal::RequestFromType, ::QuestRequiredItems const *)
{
    LIFT_STUB(0x56c190);
}

// 0x56c300
::GameFailReason __cdecl QuestJournal::progressMissionByEnterZone(::QuestJournal::QuestContext const &, ::QuestJournal::QuestRequestInfo const &, ::QuestCase const &, ::ScriptEvent const &, ::QuestJournal::RequestFromType, ::QuestRequiredItems const *)
{
    LIFT_STUB(0x56c300);
}

// 0x56c400
::GameFailReason __cdecl QuestJournal::progressMissionByNpcBleedingOccured(::QuestJournal::QuestContext const &, ::QuestJournal::QuestRequestInfo const &, ::QuestCase const &, ::ScriptEvent const &, ::QuestJournal::RequestFromType, ::QuestRequiredItems const *)
{
    LIFT_STUB(0x56c400);
}

// 0x56c590
::GameFailReason __cdecl QuestJournal::progressMissionByEnterPortal(::QuestJournal::QuestContext const &, ::QuestJournal::QuestRequestInfo const &, ::QuestCase const &, ::ScriptEvent const &, ::QuestJournal::RequestFromType, ::QuestRequiredItems const *)
{
    LIFT_STUB(0x56c590);
}

// 0x56ca00
::GameFailReason __cdecl QuestJournal::progressMissionByAcquireSummoned(::QuestJournal::QuestContext const &, ::QuestJournal::QuestRequestInfo const &, ::QuestCase const &, ::ScriptEvent const &, ::QuestJournal::RequestFromType, ::QuestRequiredItems const *)
{
    LIFT_STUB(0x56ca00);
}

// 0x56cc10
::GameFailReason __cdecl QuestJournal::progressMissionByPcSocial(::QuestJournal::QuestContext const &, ::QuestJournal::QuestRequestInfo const &, ::QuestCase const &, ::ScriptEvent const &, ::QuestJournal::RequestFromType, ::QuestRequiredItems const *)
{
    LIFT_STUB(0x56cc10);
}

// 0x56ce80
::GameFailReason __cdecl QuestJournal::progressMissionByJoinFaction(::QuestJournal::QuestContext const &, ::QuestJournal::QuestRequestInfo const &, ::QuestCase const &, ::ScriptEvent const &, ::QuestJournal::RequestFromType, ::QuestRequiredItems const *)
{
    LIFT_STUB(0x56ce80);
}

// 0x56d680
::GameFailReason __cdecl QuestJournal::progressMissionByDuelFinish(::QuestJournal::QuestContext const &, ::QuestJournal::QuestRequestInfo const &, ::QuestCase const &, ::ScriptEvent const &, ::QuestJournal::RequestFromType, ::QuestRequiredItems const *)
{
    LIFT_STUB(0x56d680);
}

// 0x56d960
::GameFailReason __cdecl QuestJournal::progressMissionByPartyBattle(::QuestJournal::QuestContext const &, ::QuestJournal::QuestRequestInfo const &, ::QuestCase const &, ::ScriptEvent const &, ::QuestJournal::RequestFromType, ::QuestRequiredItems const *)
{
    LIFT_STUB(0x56d960);
}

// 0x56db30
::GameFailReason __cdecl QuestJournal::progressMissionByPartyBattleAction(::QuestJournal::QuestContext const &, ::QuestJournal::QuestRequestInfo const &, ::QuestCase const &, ::ScriptEvent const &, ::QuestJournal::RequestFromType, ::QuestRequiredItems const *)
{
    LIFT_STUB(0x56db30);
}

// 0x56dc00
::GameFailReason __cdecl QuestJournal::progressMissionByCompleteQuest(::QuestJournal::QuestContext const &, ::QuestJournal::QuestRequestInfo const &, ::QuestCase const &, ::ScriptEvent const &, ::QuestJournal::RequestFromType, ::QuestRequiredItems const *)
{
    LIFT_STUB(0x56dc00);
}

// 0x56dd40
::GameFailReason __cdecl QuestJournal::progressMissionByBattleRoyal(::QuestJournal::QuestContext const &, ::QuestJournal::QuestRequestInfo const &, ::QuestCase const &, ::ScriptEvent const &, ::QuestJournal::RequestFromType, ::QuestRequiredItems const *)
{
    LIFT_STUB(0x56dd40);
}

// 0x56ddf0
::GameFailReason __cdecl QuestJournal::progressMissionByConvoyArrived(::QuestJournal::QuestContext const &, ::QuestJournal::QuestRequestInfo const &, ::QuestCase const &, ::ScriptEvent const &, ::QuestJournal::RequestFromType, ::QuestRequiredItems const *)
{
    LIFT_STUB(0x56ddf0);
}

// 0x56dec0
::GameFailReason __cdecl QuestJournal::checkProgressConvoy(::QuestJournal::QuestContext const &, ::QuestCase const &, ::Convoy **, ::Npc **const)
{
    LIFT_STUB(0x56dec0);
}

// 0x56e080
::GameFailReason __cdecl QuestJournal::progressMission(::QuestJournal::QuestContext const &, ::QuestJournal::QuestRequestInfo const &, ::QuestCase const &, char, ::QuestJournal::RequestFromType, bool, ::QuestJournal::RequiredItemLoss const *)
{
    LIFT_STUB(0x56e080);
}

// 0x56e870
::GameFailReason __cdecl QuestJournal::progressMissionInternal(::QuestJournal::QuestContext const &, ::QuestJournal::QuestRequestInfo const &, ::QuestCase const &, char, ::QuestJournal::RequestFromType, bool, ::QuestJournal::RequiredItemLoss const *)
{
    LIFT_STUB(0x56e870);
}

// 0x5710d0
::GameFailReason __cdecl QuestJournal::progressMissionByTutorialCase(::QuestJournal::QuestContext const &, ::QuestJournal::QuestRequestInfo const &, ::QuestCase const &, ::ScriptEvent const &, ::QuestJournal::RequestFromType, ::QuestRequiredItems const *)
{
    LIFT_STUB(0x5710d0);
}

// 0x5711c0
bool __cdecl QuestJournal::CanManipulateEnv(::Data::QuestForwarding const &, int, ::ScriptEvent &, ::QuestRequiredItems const *)
{
    LIFT_STUB(0x5711c0);
}

// 0x5718f0
bool __cdecl QuestJournal::CanManipulateNpc(::Data::NpcRecordPtr, int, ::ScriptEvent &, ::QuestRequiredItems const *)
{
    LIFT_STUB(0x5718f0);
}

// 0x571f90
bool __cdecl QuestJournal::CanUseSkill(unsigned __int64, char, char, ::GameObject *, ::ScriptEvent const &)
{
    LIFT_STUB(0x571f90);
}

// 0x572280
bool __cdecl QuestJournal::checkValidZonePhase(char, ::Data::ZoneRecordPtr, unsigned short, char, char)
{
    LIFT_STUB(0x572280);
}

// 0x572310
int __cdecl QuestJournal::SelectTransitDestination(unsigned __int64 const *const, char const *const, int, int, ::Data::ZoneRecordPtr)
{
    LIFT_STUB(0x572310);
}

// 0x5726d0
int __cdecl QuestJournal::SelectTransitDestinationForDungeon(unsigned __int64 const *const, char const *const, int, int, unsigned short, char)
{
    LIFT_STUB(0x5726d0);
}

// 0x572a60
char __cdecl QuestJournal::GetDungeonQuestCurrentMissionStep(unsigned __int64)
{
    LIFT_STUB(0x572a60);
}

// 0x572b30
bool __cdecl QuestJournal::ProgressMissionByPartyDungeonStep(short, char)
{
    LIFT_STUB(0x572b30);
}
