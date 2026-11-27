// skillaction_cpp_1.cpp: skillaction.cpp part 1 (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "skillaction.h"
#include "action.h"
#include "creature.h"
#include "envobj.h"
#include "gameobject.h"
#include "pc.h"
#include "zone.h"
#include "LiftStub.h"

// 0x48d290
void __cdecl TargetSelectorForDamageTransferNpcSquad::AddTarget(unsigned __int64, __int64, ::Creature *, ::Creature *, wchar_t const *)
{
    LIFT_STUB(0x48d290);
}

// 0x48d400
::SkillResult __cdecl SkillAction::GetSkillResultFromData(::Data::SkillSkillResultType)
{
    LIFT_STUB(0x48d400);
}

// 0x48d470
bool __cdecl SkillAction::CheckSkillResult(bool, ::SkillResult, ::Data::SkillSkillResultType)
{
    LIFT_STUB(0x48d470);
}

// 0x48d5a0
bool __cdecl SkillAction::CheckCreatureEffectFlag(::Creature *, short *, short, ::Data::SkillCastCondition3FlagOpType, int &)
{
    LIFT_STUB(0x48d5a0);
}

// 0x48d6d0
bool __cdecl SkillAction::CheckCreatureEffectAttribute(::Creature *, short *, short, ::Data::SkillCastCondition3FlagOpType, int &)
{
    LIFT_STUB(0x48d6d0);
}

// 0x48d7d0
bool __cdecl SkillAction::CheckCreatureFilters(::Creature *, unsigned __int64 const *, short, ::Data::SkillCastCondition3FlagOpType, int &)
{
    LIFT_STUB(0x48d7d0);
}

// 0x48d960
bool __cdecl SkillAction::CheckCreatureStateFilter(::Creature *, unsigned __int64)
{
    LIFT_STUB(0x48d960);
}

// 0x48da60
unsigned __int64 __cdecl SkillAction::GetKey(void) const
{
    LIFT_STUB(0x48da60);
}

// 0x48da80
unsigned int __cdecl SkillAction::GetDataId(void) const
{
    LIFT_STUB(0x48da80);
}

// 0x48daa0
char __cdecl SkillAction::GetSkillVariationId(void) const
{
    LIFT_STUB(0x48daa0);
}

// 0x48dac0
unsigned int __cdecl SkillAction::GetFlowType(void) const
{
    LIFT_STUB(0x48dac0);
}

// 0x48dae0
bool __cdecl SkillAction::IsSimultaneous(void) const
{
    LIFT_STUB(0x48dae0);
}

// 0x48db10
__cdecl SkillAction::SkillAction(void)
{
    LIFT_STUB(0x48db10);
}

// 0x48df30
__cdecl SkillAction::~SkillAction(void)
{
    LIFT_STUB(0x48df30);
}

// 0x48e0e0
void __cdecl SkillAction::sendUseSkillFailToCaster(short, char, unsigned __int64, int, char, __int64)
{
    LIFT_STUB(0x48e0e0);
}

// 0x48e240
bool __cdecl SkillAction::initializeData(char, unsigned __int64)
{
    LIFT_STUB(0x48e240);
}

// 0x48eda0
bool __cdecl SkillAction::initChildSkillData(void)
{
    LIFT_STUB(0x48eda0);
}

// 0x48eef0
bool __cdecl SkillAction::initializeData(void)
{
    LIFT_STUB(0x48eef0);
}

// 0x48fb00
bool __cdecl SkillAction::InitializeToTargetByNpc(::Zone *, ::Creature *, ::SkillAction::SkillReqFrom, unsigned __int64, unsigned __int64, short)
{
    LIFT_STUB(0x48fb00);
}

// 0x48fce0
bool __cdecl SkillAction::InitializeToGroundByNpc(::Zone *, ::Creature *, ::SkillAction::SkillReqFrom, unsigned __int64, ::vector16 const &, short)
{
    LIFT_STUB(0x48fce0);
}

// 0x48fed0
bool __cdecl SkillAction::InitializeByCounter(::Zone *, ::Creature *, unsigned __int64, unsigned __int64, short)
{
    LIFT_STUB(0x48fed0);
}

// 0x4900c0
bool __cdecl SkillAction::InitializeToTarget(::Zone *const, ::Creature *const, bool, ::SkillAction::SkillReqFrom, unsigned __int64, unsigned __int64, short, short, char, char const *const, char, unsigned __int64 const *const, char, char const *const, char, char const *const, char, __int64)
{
    LIFT_STUB(0x4900c0);
}

// 0x490570
bool __cdecl SkillAction::InitializeToGround(::Zone *const, ::Creature *const, bool, ::SkillAction::SkillReqFrom, unsigned __int64, ::vector16 const &, short, short, char, char const *const, char, unsigned __int64 const *const, char, char const *const, char, char const *const, char, __int64)
{
    LIFT_STUB(0x490570);
}

// 0x490a30
bool __cdecl SkillAction::InitializeToTarget(::Zone *const, char, unsigned __int64, bool, ::SkillAction::SkillReqFrom, unsigned __int64, unsigned __int64, short, short, char, char const *const, char, unsigned __int64 const *const, char, char const *const, char, char const *const, char, __int64)
{
    LIFT_STUB(0x490a30);
}

// 0x490d00
bool __cdecl SkillAction::InitializeToGround(::Zone *const, char, unsigned __int64, bool, ::SkillAction::SkillReqFrom, unsigned __int64, ::vector16 const &, short, short, char, char const *const, char, unsigned __int64 const *const, char, char const *const, char, char const *const, char, __int64)
{
    LIFT_STUB(0x490d00);
}

// 0x490fe0
bool __cdecl SkillAction::InitializeByItemSimSkill(::Zone *const, ::Creature *const, unsigned __int64, ::Data::ItemSkillRecordPtr const &, unsigned __int64, short)
{
    LIFT_STUB(0x490fe0);
}

// 0x491310
bool __cdecl SkillAction::InitializeByGrocery(::Zone *, ::Creature *, short, unsigned __int64, short, unsigned __int64)
{
    LIFT_STUB(0x491310);
}

// 0x4914f0
bool __cdecl SkillAction::InitializeByGrocery(::Zone *, ::Creature *, short, ::vector16, short, unsigned __int64)
{
    LIFT_STUB(0x4914f0);
}

// 0x4916e0
bool __cdecl SkillAction::InitializeByEquipped(::Zone *, ::Creature *, unsigned __int64, short, unsigned __int64, short)
{
    LIFT_STUB(0x4916e0);
}

// 0x4918b0
bool __cdecl SkillAction::InitializeByEquipped(::Zone *, ::Creature *, unsigned __int64, short, ::vector16, short)
{
    LIFT_STUB(0x4918b0);
}

// 0x491aa0
bool __cdecl SkillAction::InitializeByFieldItem(::Zone *, ::Creature *, unsigned __int64, short, char)
{
    LIFT_STUB(0x491aa0);
}

// 0x491c70
bool __cdecl SkillAction::InitializeByFieldItem(::Zone *const, ::Pc *const, ::vector16 const &, short, char)
{
    LIFT_STUB(0x491c70);
}

// 0x491e10
bool __cdecl SkillAction::InitializeByFieldItem(::Zone *, ::Creature *, ::vector16 &, short)
{
    LIFT_STUB(0x491e10);
}

// 0x491ff0
bool __cdecl SkillAction::IsAvailableAction(void)
{
    LIFT_STUB(0x491ff0);
}

// 0x492080
bool __cdecl SkillAction::CheckImmuneSkillResult(::SkillResult)
{
    LIFT_STUB(0x492080);
}

// 0x492180
bool __cdecl SkillAction::ExecuteCounterSkill(unsigned __int64, unsigned __int64)
{
    LIFT_STUB(0x492180);
}

// 0x492570
void __cdecl SkillAction::RequestCancel(::CancelActionReason, unsigned __int64)
{
    LIFT_STUB(0x492570);
}

// 0x492800
bool __cdecl SkillAction::RequestTrigger(bool)
{
    LIFT_STUB(0x492800);
}

// 0x492a00
void __cdecl SkillAction::RequestReturn(bool, bool)
{
    LIFT_STUB(0x492a00);
}

// 0x492bd0
bool __cdecl SkillAction::IsMoveBlockCasterFlag(void)
{
    LIFT_STUB(0x492bd0);
}

// 0x492ca0
void __cdecl SkillAction::EnableWriteLatencyTraceLog(void)
{
    LIFT_STUB(0x492ca0);
}

// 0x492d10
void __cdecl SkillAction::WriteLatencyTraceLog(::SkillAction::SkillLatencyTraceLogState, wchar_t const *, wchar_t const *, wchar_t const *)
{
    LIFT_STUB(0x492d10);
}

// 0x492ef0
void __cdecl SkillAction::AddChildSkillInfo(char, unsigned __int64 *const, ::vector16 *const, unsigned __int64 *const)
{
    LIFT_STUB(0x492ef0);
}

// 0x4930b0
bool __cdecl SkillAction::prepareAction(void)
{
    LIFT_STUB(0x4930b0);
}

// 0x493910
void __cdecl SkillAction::invokeChildSkill(int)
{
    LIFT_STUB(0x493910);
}

// 0x493cf0
void __cdecl SkillAction::startAction(void)
{
    LIFT_STUB(0x493cf0);
}

// 0x493de0
bool __cdecl SkillAction::applySkillModifyInfoGroupData(::Creature *, char, ::Data::ItemRecordPtr, unsigned __int64)
{
    LIFT_STUB(0x493de0);
}

// 0x494080
bool __cdecl SkillAction::getSkillModifyInfoData(::Creature *, ::Data::ItemRecordPtr, int, unsigned __int64, ::Data::SkillModifyInfoRecordPtr *)
{
    LIFT_STUB(0x494080);
}

// 0x4941a0
void __cdecl SkillAction::calcSkillModifyInfo(void)
{
    LIFT_STUB(0x4941a0);
}

// 0x494b20
void __cdecl SkillAction::calcDuelBotSkillModifyInfo(void)
{
    LIFT_STUB(0x494b20);
}

// 0x494cc0
bool __cdecl checkItemSkillData(::Pc const *, ::Data::ItemSkillRecordPtr, int, unsigned int, char)
{
    LIFT_STUB(0x494cc0);
}

// 0x494e00
bool __cdecl SkillAction::checkItemSkill(void)
{
    LIFT_STUB(0x494e00);
}

// 0x495a70
void __cdecl SkillAction::invokeItemSkill(::GameObject *const, ::Data::ItemSkillSkillStepType, char, ::SkillResult, bool, bool, bool)
{
    LIFT_STUB(0x495a70);
}

// 0x495e20
void __cdecl SkillAction::useItemSimSkill(::Pc *const, ::Data::ItemSkillRecordPtr const &)
{
    LIFT_STUB(0x495e20);
}

// 0x495f60
void __cdecl SkillAction::invokeItemCasterSkill(char, unsigned short)
{
    LIFT_STUB(0x495f60);
}

// 0x496330
void __cdecl SkillAction::intervalAction(long)
{
    LIFT_STUB(0x496330);
}

// 0x4964c0
void __cdecl SkillAction::changeState(::SkillAction::StateType, long)
{
    LIFT_STUB(0x4964c0);
}

// 0x4965c0
void __cdecl SkillAction::finishAction(void)
{
    LIFT_STUB(0x4965c0);
}

// 0x496700
void __cdecl SkillAction::cancelAction(::Action::CancelReason, wchar_t const *, int)
{
    LIFT_STUB(0x496700);
}

// 0x496ad0
void __cdecl SkillAction::sendUseSkillToNpcEvent(::Creature *)
{
    LIFT_STUB(0x496ad0);
}

// 0x496b90
void __cdecl SkillAction::failAction(::Action::FailReason)
{
    LIFT_STUB(0x496b90);
}

// 0x496ce0
void __cdecl SkillAction::stateCast(void)
{
    LIFT_STUB(0x496ce0);
}

// 0x499940
void __cdecl SkillAction::stateFly(void)
{
    LIFT_STUB(0x499940);
}

// 0x49b720
void __cdecl SkillAction::finishActionByFireFail(::Creature *const)
{
    LIFT_STUB(0x49b720);
}

// 0x49b770
void __cdecl SkillAction::stateExecute(void)
{
    LIFT_STUB(0x49b770);
}

// 0x49b9d0
void __cdecl SkillAction::stateExecuteRepeat(void)
{
    LIFT_STUB(0x49b9d0);
}

// 0x49b9e0
void __cdecl SkillAction::stateExecutePostProc(void)
{
    LIFT_STUB(0x49b9e0);
}

// 0x49c280
void __cdecl SkillAction::stateReturn(void)
{
    LIFT_STUB(0x49c280);
}

// 0x49c4c0
void __cdecl SkillAction::stateFinish(void)
{
    LIFT_STUB(0x49c4c0);
}

// 0x49c530
void __cdecl SkillAction::stateDestroy(void)
{
    LIFT_STUB(0x49c530);
}

// 0x49c540
::SkillResult __cdecl SkillAction::invokeExecuteToTarget(char, unsigned __int64, ::vector16, bool, bool, ::vector16 &)
{
    LIFT_STUB(0x49c540);
}

// 0x49ceb0
::SkillResult __cdecl SkillAction::invokeExecuteToEnv(char, ::Env *, bool)
{
    LIFT_STUB(0x49ceb0);
}

// 0x49d040
::SkillResult __cdecl SkillAction::invokeExecuteToCreature(char, ::Creature *, ::vector16, bool, bool)
{
    LIFT_STUB(0x49d040);
}

// 0x49d970
bool __cdecl SkillAction::invokeKillEffect(void)
{
    LIFT_STUB(0x49d970);
}

// 0x49da80
void __cdecl SkillAction::detachBindingEffect(bool)
{
    LIFT_STUB(0x49da80);
}

// 0x49db70
bool __cdecl SkillAction::isMovable(void) const
{
    LIFT_STUB(0x49db70);
}

// 0x49dbf0
bool __cdecl SkillAction::checkTarget(::vector16, short, unsigned __int64, ::SkillAction::StateType)
{
    LIFT_STUB(0x49dbf0);
}

// 0x49e3b0
::GameFailReason __cdecl SkillAction::checkCreature(::vector16, short, ::SkillAction::StateType, unsigned __int64, short, short, short, short, short)
{
    LIFT_STUB(0x49e3b0);
}

// 0x49e910
::GameFailReason __cdecl SkillAction::checkEnvObj(::vector16, short, unsigned __int64, short, short, short, short)
{
    LIFT_STUB(0x49e910);
}

// 0x49eb10
bool __cdecl SkillAction::checkTargetDeadState(::Creature *, ::Data::SkillCastCondition3DeadStateType) const
{
    LIFT_STUB(0x49eb10);
}

// 0x49eb90
bool __cdecl SkillAction::checkCastSkillAttribute(void)
{
    LIFT_STUB(0x49eb90);
}

// 0x49ec70
bool __cdecl SkillAction::checkCastFilter(::GameFailReason &)
{
    LIFT_STUB(0x49ec70);
}

// 0x49f370
bool __cdecl SkillAction::checkTarget(::SkillAction::StateType, ::Creature *, ::GameFailReason &) const
{
    LIFT_STUB(0x49f370);
}

// 0x49f6c0
bool __cdecl SkillAction::checkTargetFilter(::SkillAction::StateType, ::Creature *, ::GameFailReason &) const
{
    LIFT_STUB(0x49f6c0);
}

// 0x49fd20
bool __cdecl SkillAction::getCasterFunctions(char *&, char &)
{
    LIFT_STUB(0x49fd20);
}

// 0x49fe30
bool __cdecl SkillAction::dispelCasterAttribute(void)
{
    LIFT_STUB(0x49fe30);
}

// 0x49feb0
bool __cdecl SkillAction::changeCasterStance(void)
{
    LIFT_STUB(0x49feb0);
}

// 0x49ff80
bool __cdecl SkillAction::attachCasterFunction(wchar_t const *, int)
{
    LIFT_STUB(0x49ff80);
}

// 0x4a01a0
bool __cdecl SkillAction::detachCasterFunction(wchar_t const *, int)
{
    LIFT_STUB(0x4a01a0);
}

// 0x4a03c0
bool __cdecl SkillAction::invokeCastEffect(void)
{
    LIFT_STUB(0x4a03c0);
}

// 0x4a0840
bool __cdecl SkillAction::invokeSwingEffect(char)
{
    LIFT_STUB(0x4a0840);
}

// 0x4a0af0
bool __cdecl SkillAction::invokeExecCasterEffect(char, long, unsigned short)
{
    LIFT_STUB(0x4a0af0);
}

// 0x4a0f70
bool __cdecl SkillAction::invokeEffect(char, ::SkillResult, ::GameObject *, bool, bool, bool)
{
    LIFT_STUB(0x4a0f70);
}

// 0x4a1310
bool __cdecl SkillAction::invokeEffectGroup(::GameObject *const, unsigned __int64 const *const, char, char, ::SkillResult, bool, bool, bool)
{
    LIFT_STUB(0x4a1310);
}

// 0x4a1a40
long __cdecl SkillAction::getFlyDuration(::SkillFlowCode, char)
{
    LIFT_STUB(0x4a1a40);
}

// 0x4a1c50
long __cdecl SkillAction::getSkillStepDuration(::SkillFlowCode, char)
{
    LIFT_STUB(0x4a1c50);
}

// 0x4a1d20
void __cdecl SkillAction::broadcastSkill(::SkillFlowCode)
{
    LIFT_STUB(0x4a1d20);
}

// 0x4a2620
void __cdecl SkillAction::broadcastHit(unsigned __int64, ::SkillResult)
{
    LIFT_STUB(0x4a2620);
}

// 0x4a2810
bool __cdecl SkillAction::isCastable(void)
{
    LIFT_STUB(0x4a2810);
}

// 0x4a5130
bool __cdecl SkillAction::checkUseSkillByEquipment(unsigned __int64)
{
    LIFT_STUB(0x4a5130);
}

// 0x4a51f0
bool __cdecl SkillAction::checkUseSkill(void)
{
    LIFT_STUB(0x4a51f0);
}

// 0x4a57d0
bool __cdecl SkillAction::checkUseUnnecessaryAcquiredSoulMaskSkill(void)
{
    LIFT_STUB(0x4a57d0);
}

// 0x4a5880
bool __cdecl SkillAction::isInCylinder(__int64, __int64, __int64, __int64, ::vector16 &, ::vector16 &, __int64 &, wchar_t const *)
{
    LIFT_STUB(0x4a5880);
}

// 0x4a5ad0
bool __cdecl SkillAction::isAvailableDir(::Creature *, ::Data::SkillDirType, ::Data::SkillDirType)
{
    LIFT_STUB(0x4a5ad0);
}

// 0x4a5bc0
bool __cdecl SkillAction::checkConsumablePoint(::Data::SkillPointTypeType, __int64, ::Data::SkillPointTypeType, __int64, __int64, __int64, __int64)
{
    LIFT_STUB(0x4a5bc0);
}

// 0x4a5d30
bool __cdecl SkillAction::isConsumablePoint(void)
{
    LIFT_STUB(0x4a5d30);
}

// 0x4a5f50
void __cdecl SkillAction::setRecycleTime2(bool)
{
    LIFT_STUB(0x4a5f50);
}

// 0x4a61f0
void __cdecl SkillAction::initializeRecycleTime2(void)
{
    LIFT_STUB(0x4a61f0);
}
