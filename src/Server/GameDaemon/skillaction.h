// skillaction.h: skillaction.cpp, skillaction.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"
#include "action.h"

class CasterSkillAction
{
public:
    __cdecl CasterSkillAction(void);  // 0x4ac0c0
    virtual bool __cdecl SucceedTargetInfo(__int64, int, unsigned __int64 &, ::vector16 &, unsigned __int64 *const, char &);  // 0x4ac100
protected:
    virtual void __cdecl modifyTargetPositionByOffset(char);  // 0x4ac160
    virtual void __cdecl stateReturn(void);  // 0x4ac3b0
    virtual void __cdecl gatherTarget(char);  // 0x4ac3c0
    virtual bool __cdecl invokeExecute(char, unsigned short &);  // 0x4ac7e0
};

class ChainSkillAction
{
public:
    __cdecl ChainSkillAction(void);  // 0x4aef80
protected:
    virtual bool __cdecl isCastable(void);  // 0x4af000
    virtual bool __cdecl isFlyable(char);  // 0x4af0b0
    virtual bool __cdecl isExecutable(char);  // 0x4af1d0
public:
    virtual bool __cdecl SucceedTargetInfo(__int64, int, unsigned __int64 &, ::vector16 &, unsigned __int64 *const, char &);  // 0x4af2f0
protected:
    virtual void __cdecl gatherTarget(char);  // 0x4af340
    virtual bool __cdecl getDurationFromSpeed2(short, long &);  // 0x4af430
    virtual bool __cdecl invokeExecute(char, unsigned short &);  // 0x4af4d0
private:
    bool __cdecl getTargetPosition(unsigned __int64, ::vector16 &);  // 0x4af850
    bool __cdecl gatherTargetByChain(void);  // 0x4af990
};

class DuelInterferenceSkillAction
{
protected:
    virtual bool __cdecl isCastable(void);  // 0x4b3490
    virtual bool __cdecl isFlyable(char);  // 0x4b3ac0
    virtual bool __cdecl isExecutable(char);  // 0x4b3da0
    virtual bool __cdecl invokeExecute(char, unsigned short &);  // 0x4b40a0
};

class DuelTagSkillAction
{
protected:
    virtual bool __cdecl isCastable(void);  // 0x4b2710
    virtual bool __cdecl isFlyable(char);  // 0x4b2d40
    virtual bool __cdecl isExecutable(char);  // 0x4b3020
    virtual bool __cdecl invokeExecute(char, unsigned short &);  // 0x4b3310
};

class GroundRadiusSkillAction
{
public:
    __cdecl GroundRadiusSkillAction(void);  // 0x4ad580
protected:
    bool __cdecl calcGroundPos(void);  // 0x4ad5e0
    virtual bool __cdecl prepareAction(void);  // 0x4ad990
public:
    virtual bool __cdecl SucceedTargetInfo(__int64, int, unsigned __int64 &, ::vector16 &, unsigned __int64 *const, char &);  // 0x4adc20
protected:
    virtual void __cdecl gatherTarget(char);  // 0x4adc80
private:
    void __cdecl spawnNpc(char);  // 0x4ae240
protected:
    virtual bool __cdecl invokeExecute(char, unsigned short &);  // 0x4ae500
    virtual bool __cdecl isCastable(void);  // 0x4ae710
    virtual bool __cdecl isFlyable(char);  // 0x4aed50
};

class MakeCampfireSkillAction
{
protected:
    virtual bool __cdecl isCastable(void);  // 0x4b1480
private:
    void __cdecl makeCampfire(void);  // 0x4b15d0
    bool __cdecl canMakeCampfire(void);  // 0x4b1660
protected:
    virtual bool __cdecl invokeExecute(char, unsigned short &);  // 0x4b18f0
};

class NoneTargetSkillAction
{
protected:
    virtual bool __cdecl isCastable(void);  // 0x4aff30
    virtual bool __cdecl isFlyable(char);  // 0x4b0700
    virtual bool __cdecl isExecutable(char);  // 0x4b09d0
public:
    virtual bool __cdecl SucceedTargetInfo(__int64, int, unsigned __int64 &, ::vector16 &, unsigned __int64 *const, char &);  // 0x4b09e0
protected:
    virtual bool __cdecl invokeExecute(char, unsigned short &);  // 0x4b0a00
};

class SkillAction
{
public:
    enum SkillLatencyTraceLogState {};
    enum SkillReqFrom {};
    enum StateType {};
protected:
    virtual ::ActionPriorityClass __cdecl getPriority(void) const;  // 0x275e0
    virtual short __cdecl getDashAngle(unsigned __int64);  // 0x27600
protected:
    char lift_pad_8[0xDE];  // ❓ no PDB name: base Action and fields +8 to +0xE5 are not declared yet
    short _dashAngle;       // +230 (0xE6)
public:
    static ::SkillResult __cdecl GetSkillResultFromData(::Data::SkillSkillResultType);  // 0x48d400
    static bool __cdecl CheckSkillResult(bool, ::SkillResult, ::Data::SkillSkillResultType);  // 0x48d470
    static bool __cdecl CheckCreatureEffectFlag(::Creature *, short *, short, ::Data::SkillCastCondition3FlagOpType, int &);  // 0x48d5a0
    static bool __cdecl CheckCreatureEffectAttribute(::Creature *, short *, short, ::Data::SkillCastCondition3FlagOpType, int &);  // 0x48d6d0
    static bool __cdecl CheckCreatureFilters(::Creature *, unsigned __int64 const *, short, ::Data::SkillCastCondition3FlagOpType, int &);  // 0x48d7d0
    static bool __cdecl CheckCreatureStateFilter(::Creature *, unsigned __int64);  // 0x48d960
    unsigned __int64 __cdecl GetKey(void) const;  // 0x48da60
    unsigned int __cdecl GetDataId(void) const;  // 0x48da80
    char __cdecl GetSkillVariationId(void) const;  // 0x48daa0
protected:
    virtual unsigned int __cdecl GetFlowType(void) const;  // 0x48dac0
    virtual bool __cdecl IsSimultaneous(void) const;  // 0x48dae0
public:
    __cdecl SkillAction(void);  // 0x48db10
    virtual __cdecl ~SkillAction(void);  // 0x48df30
    void __cdecl sendUseSkillFailToCaster(short, char, unsigned __int64, int, char, __int64);  // 0x48e0e0
    bool __cdecl initializeData(char, unsigned __int64);  // 0x48e240
protected:
    bool __cdecl initChildSkillData(void);  // 0x48eda0
    bool __cdecl initializeData(void);  // 0x48eef0
public:
    bool __cdecl InitializeToTargetByNpc(::Zone *, ::Creature *, ::SkillAction::SkillReqFrom, unsigned __int64, unsigned __int64, short);  // 0x48fb00
    bool __cdecl InitializeToGroundByNpc(::Zone *, ::Creature *, ::SkillAction::SkillReqFrom, unsigned __int64, ::vector16 const &, short);  // 0x48fce0
    bool __cdecl InitializeByCounter(::Zone *, ::Creature *, unsigned __int64, unsigned __int64, short);  // 0x48fed0
    bool __cdecl InitializeToTarget(::Zone *const, ::Creature *const, bool, ::SkillAction::SkillReqFrom, unsigned __int64, unsigned __int64, short, short, char, char const *const, char, unsigned __int64 const *const, char, char const *const, char, char const *const, char, __int64);  // 0x4900c0
    bool __cdecl InitializeToGround(::Zone *const, ::Creature *const, bool, ::SkillAction::SkillReqFrom, unsigned __int64, ::vector16 const &, short, short, char, char const *const, char, unsigned __int64 const *const, char, char const *const, char, char const *const, char, __int64);  // 0x490570
    bool __cdecl InitializeToTarget(::Zone *const, char, unsigned __int64, bool, ::SkillAction::SkillReqFrom, unsigned __int64, unsigned __int64, short, short, char, char const *const, char, unsigned __int64 const *const, char, char const *const, char, char const *const, char, __int64);  // 0x490a30
    bool __cdecl InitializeToGround(::Zone *const, char, unsigned __int64, bool, ::SkillAction::SkillReqFrom, unsigned __int64, ::vector16 const &, short, short, char, char const *const, char, unsigned __int64 const *const, char, char const *const, char, char const *const, char, __int64);  // 0x490d00
    bool __cdecl InitializeByItemSimSkill(::Zone *const, ::Creature *const, unsigned __int64, ::Data::ItemSkillRecordPtr const &, unsigned __int64, short);  // 0x490fe0
    bool __cdecl InitializeByGrocery(::Zone *, ::Creature *, short, unsigned __int64, short, unsigned __int64);  // 0x491310
    bool __cdecl InitializeByGrocery(::Zone *, ::Creature *, short, ::vector16, short, unsigned __int64);  // 0x4914f0
    bool __cdecl InitializeByEquipped(::Zone *, ::Creature *, unsigned __int64, short, unsigned __int64, short);  // 0x4916e0
    bool __cdecl InitializeByEquipped(::Zone *, ::Creature *, unsigned __int64, short, ::vector16, short);  // 0x4918b0
    bool __cdecl InitializeByFieldItem(::Zone *, ::Creature *, unsigned __int64, short, char);  // 0x491aa0
    bool __cdecl InitializeByFieldItem(::Zone *const, ::Pc *const, ::vector16 const &, short, char);  // 0x491c70
    bool __cdecl InitializeByFieldItem(::Zone *, ::Creature *, ::vector16 &, short);  // 0x491e10
    virtual bool __cdecl IsAvailableAction(void);  // 0x491ff0
    bool __cdecl CheckImmuneSkillResult(::SkillResult);  // 0x492080
    bool __cdecl ExecuteCounterSkill(unsigned __int64, unsigned __int64);  // 0x492180
protected:
    virtual void __cdecl RequestCancel(::CancelActionReason, unsigned __int64);  // 0x492570
public:
    virtual bool __cdecl RequestTrigger(bool);  // 0x492800
    void __cdecl RequestReturn(bool, bool);  // 0x492a00
    bool __cdecl IsMoveBlockCasterFlag(void);  // 0x492bd0
    void __cdecl EnableWriteLatencyTraceLog(void);  // 0x492ca0
    void __cdecl WriteLatencyTraceLog(::SkillAction::SkillLatencyTraceLogState, wchar_t const *, wchar_t const *, wchar_t const *);  // 0x492d10
    void __cdecl AddChildSkillInfo(char, unsigned __int64 *const, ::vector16 *const, unsigned __int64 *const);  // 0x492ef0
protected:
    virtual bool __cdecl prepareAction(void);  // 0x4930b0
    void __cdecl invokeChildSkill(int);  // 0x493910
    virtual void __cdecl startAction(void);  // 0x493cf0
private:
    bool __cdecl applySkillModifyInfoGroupData(::Creature *, char, ::Data::ItemRecordPtr, unsigned __int64);  // 0x493de0
    bool __cdecl getSkillModifyInfoData(::Creature *, ::Data::ItemRecordPtr, int, unsigned __int64, ::Data::SkillModifyInfoRecordPtr *);  // 0x494080
protected:
    void __cdecl calcSkillModifyInfo(void);  // 0x4941a0
    void __cdecl calcDuelBotSkillModifyInfo(void);  // 0x494b20
    bool __cdecl checkItemSkill(void);  // 0x494e00
    void __cdecl invokeItemSkill(::GameObject *const, ::Data::ItemSkillSkillStepType, char, ::SkillResult, bool, bool, bool);  // 0x495a70
    void __cdecl useItemSimSkill(::Pc *const, ::Data::ItemSkillRecordPtr const &);  // 0x495e20
    void __cdecl invokeItemCasterSkill(char, unsigned short);  // 0x495f60
    virtual void __cdecl intervalAction(long);  // 0x496330
    void __cdecl changeState(::SkillAction::StateType, long);  // 0x4964c0
    virtual void __cdecl finishAction(void);  // 0x4965c0
    virtual void __cdecl cancelAction(::Action::CancelReason, wchar_t const *, int);  // 0x496700
private:
    void __cdecl sendUseSkillToNpcEvent(::Creature *);  // 0x496ad0
protected:
    virtual void __cdecl failAction(::Action::FailReason);  // 0x496b90
    virtual void __cdecl stateCast(void);  // 0x496ce0
    virtual void __cdecl stateFly(void);  // 0x499940
    void __cdecl finishActionByFireFail(::Creature *const);  // 0x49b720
    virtual void __cdecl stateExecute(void);  // 0x49b770
    virtual void __cdecl stateExecuteRepeat(void);  // 0x49b9d0
    void __cdecl stateExecutePostProc(void);  // 0x49b9e0
    virtual void __cdecl stateReturn(void);  // 0x49c280
    virtual void __cdecl stateFinish(void);  // 0x49c4c0
    virtual void __cdecl stateDestroy(void);  // 0x49c530
    ::SkillResult __cdecl invokeExecuteToTarget(char, unsigned __int64, ::vector16, bool, bool, ::vector16 &);  // 0x49c540
    ::SkillResult __cdecl invokeExecuteToEnv(char, ::Env *, bool);  // 0x49ceb0
    ::SkillResult __cdecl invokeExecuteToCreature(char, ::Creature *, ::vector16, bool, bool);  // 0x49d040
    bool __cdecl invokeKillEffect(void);  // 0x49d970
    void __cdecl detachBindingEffect(bool);  // 0x49da80
    bool __cdecl isMovable(void) const;  // 0x49db70
    bool __cdecl checkTarget(::vector16, short, unsigned __int64, ::SkillAction::StateType);  // 0x49dbf0
    ::GameFailReason __cdecl checkCreature(::vector16, short, ::SkillAction::StateType, unsigned __int64, short, short, short, short, short);  // 0x49e3b0
    ::GameFailReason __cdecl checkEnvObj(::vector16, short, unsigned __int64, short, short, short, short);  // 0x49e910
    bool __cdecl checkTargetDeadState(::Creature *, ::Data::SkillCastCondition3DeadStateType) const;  // 0x49eb10
    bool __cdecl checkCastSkillAttribute(void);  // 0x49eb90
    bool __cdecl checkCastFilter(::GameFailReason &);  // 0x49ec70
    bool __cdecl checkTarget(::SkillAction::StateType, ::Creature *, ::GameFailReason &) const;  // 0x49f370
    bool __cdecl checkTargetFilter(::SkillAction::StateType, ::Creature *, ::GameFailReason &) const;  // 0x49f6c0
    bool __cdecl getCasterFunctions(char *&, char &);  // 0x49fd20
    bool __cdecl dispelCasterAttribute(void);  // 0x49fe30
    bool __cdecl changeCasterStance(void);  // 0x49feb0
    bool __cdecl attachCasterFunction(wchar_t const *, int);  // 0x49ff80
    bool __cdecl detachCasterFunction(wchar_t const *, int);  // 0x4a01a0
    bool __cdecl invokeCastEffect(void);  // 0x4a03c0
    bool __cdecl invokeSwingEffect(char);  // 0x4a0840
    bool __cdecl invokeExecCasterEffect(char, long, unsigned short);  // 0x4a0af0
    bool __cdecl invokeEffect(char, ::SkillResult, ::GameObject *, bool, bool, bool);  // 0x4a0f70
    bool __cdecl invokeEffectGroup(::GameObject *const, unsigned __int64 const *const, char, char, ::SkillResult, bool, bool, bool);  // 0x4a1310
    long __cdecl getFlyDuration(::SkillFlowCode, char);  // 0x4a1a40
    long __cdecl getSkillStepDuration(::SkillFlowCode, char);  // 0x4a1c50
    virtual void __cdecl broadcastSkill(::SkillFlowCode);  // 0x4a1d20
    void __cdecl broadcastHit(unsigned __int64, ::SkillResult);  // 0x4a2620
    virtual bool __cdecl isCastable(void);  // 0x4a2810
private:
    bool __cdecl checkUseSkillByEquipment(unsigned __int64);  // 0x4a5130
protected:
    bool __cdecl checkUseSkill(void);  // 0x4a51f0
    bool __cdecl checkUseUnnecessaryAcquiredSoulMaskSkill(void);  // 0x4a57d0
    bool __cdecl isInCylinder(__int64, __int64, __int64, __int64, ::vector16 &, ::vector16 &, __int64 &, wchar_t const *);  // 0x4a5880
    bool __cdecl isAvailableDir(::Creature *, ::Data::SkillDirType, ::Data::SkillDirType);  // 0x4a5ad0
    bool __cdecl checkConsumablePoint(::Data::SkillPointTypeType, __int64, ::Data::SkillPointTypeType, __int64, __int64, __int64, __int64);  // 0x4a5bc0
    bool __cdecl isConsumablePoint(void);  // 0x4a5d30
    void __cdecl setRecycleTime2(bool);  // 0x4a5f50
    void __cdecl initializeRecycleTime2(void);  // 0x4a61f0
    void __cdecl initializeGlobalRecycleTime2(void);  // 0x4a6270
    void __cdecl initializeDuelBotGlobalRecycleTime2(void);  // 0x4a62f0
    bool __cdecl checkDuelBotRecycleTime(::Creature *);  // 0x4a6370
    __int64 __cdecl getConsumePoint(::Data::SkillPointTypeType, __int64, __int64, __int64, __int64);  // 0x4a6550
    void __cdecl consumePoint(void);  // 0x4a65f0
    void __cdecl recoverPoint(void);  // 0x4a6930
    void __cdecl executeWeaponGemEffect(::Creature *, ::SkillResult, bool);  // 0x4a6a80
    bool __cdecl calcChangeNpcYaw(short &, char &);  // 0x4a6bb0
    void __cdecl changeNpcYaw(void);  // 0x4a6e90
    void __cdecl onExecute(char, ::SkillResult &, ::Creature *, bool);  // 0x4a6f60
    bool __cdecl checkQuestEvent(::GameObject *);  // 0x4a74d0
    void __cdecl transferQuestEvent(::GameObject *);  // 0x4a7670
    bool __cdecl checkDirection(::Data::SkillDirType, short, ::vector16, ::vector16) const;  // 0x4a7890
    bool __cdecl isValidTarget(::Creature *);  // 0x4a7bc0
    bool __cdecl canExecDash(::vector16);  // 0x4a7c40
    char __cdecl getGatherType(char, bool &);  // 0x4a7d10
    bool __cdecl getCasterEffects(char, unsigned __int64 *&, char &);  // 0x4a7e20
    short __cdecl getTargetAngle(char);  // 0x4a7f80
    bool __cdecl isExistInvokeEffect(char);  // 0x4a7ff0
    void __cdecl calcCheckPosition(::Creature *, ::vector16 &);  // 0x4a80c0
    bool __cdecl calcDashPosition(::Data::SkillDashAttribute3RecordPtr, ::Creature *, ::vector16 &, short &);  // 0x4a8210
    bool __cdecl execDash(::Creature *, ::Creature *, ::vector16, short, long);  // 0x4a87f0
    void __cdecl gatherTargetByPosition(::vector16 &, short, ::Data::SkillDirType, unsigned __int64 *const, char *, bool, int);  // 0x4a8970
    bool __cdecl isLaserScope(::vector16, ::GameObject *, short, short, short, short, short, short, short, bool, bool, __int64 &);  // 0x4a9020
    void __cdecl gatherTargetByLaser(::vector16, short, unsigned __int64 *const, char *, int);  // 0x4a94f0
    void __cdecl gatherTargetByShiftingLaser(::vector16, short, unsigned __int64 *const, char *, int);  // 0x4a9be0
    bool __cdecl calculateRange(short &, short &, ::GameObject *);  // 0x4aa1c0
    bool __cdecl applySkillFormula(void);  // 0x4aa260
    ::Pointer2< ::Creature> __cdecl getCreaturePtr(unsigned __int64);  // 0x4aa360
    void __cdecl execBounce(::Creature *);  // 0x4aa3f0
    void __cdecl execTriggerSkill(void);  // 0x4aa4c0
    bool __cdecl checkSkillResultValue(unsigned short, ::Data::SkillSkillResultType, ::SkillResult *);  // 0x4aa5f0
    bool __cdecl applySkillResultRule(char, ::SkillResult &);  // 0x4aa6a0
    bool __cdecl applySkillAttributeRule(::Creature *, ::SkillResult &, bool);  // 0x4aa930
    bool __cdecl calcFireMiss(void);  // 0x4aaa60
    ::SkillResult __cdecl calcSkillResult(::Creature *, bool);  // 0x4aab00
    long const __cdecl calcCastDuration(long) const;  // 0x4aac80
    short __cdecl calcImmune(::Creature *, bool);  // 0x4aae20
    short __cdecl calcDodge(::Creature *, bool, short &);  // 0x4aaf10
    short __cdecl calcParry(::Creature *, bool, short);  // 0x4ab350
    short __cdecl calcCriticalHit(::Creature *, bool);  // 0x4ab5e0
    virtual bool __cdecl getDurationFromSpeed2(short, long &);  // 0x4aba70
    bool __cdecl getDurationFromSpeed(::vector16, short, long &);  // 0x4abaf0
    void __cdecl setCastingFlag(bool);  // 0x4abe80
    bool __cdecl addGatherTarget(unsigned __int64, unsigned __int64 *const, char *, int);  // 0x4abf30
    void __cdecl resetTimer(void);  // 0x4abf80
    bool __cdecl calcSkillModifyWeight(char, ::ApplySkillModifyInfo *, ::ApplySkillModifyInfo &);  // 0x4abfb0
private:
    unsigned __int64 const __cdecl getSkillInstanceIdForGameLog(void);  // 0x4ac080
};

class SkillActionFactory
{
public:
    ::SkillAction *const __cdecl CreateSkillAction3(unsigned __int64) const;  // 0x4b4220
};

class SuccessionSkillAction
{
protected:
    virtual bool __cdecl prepareAction(void);  // 0x4b1920
    virtual bool __cdecl isCastable(void);  // 0x4b1d10
    virtual bool __cdecl isFlyable(char);  // 0x4b2330
    virtual bool __cdecl isExecutable(char);  // 0x4b24c0
    virtual bool __cdecl invokeExecute(char, unsigned short &);  // 0x4b2570
};

class SummonSkillAction
{
protected:
    virtual bool __cdecl prepareAction(void);  // 0x4b0ad0
    virtual bool __cdecl isCastable(void);  // 0x4b1070
private:
    void __cdecl execSummon(void);  // 0x4b1220
protected:
    virtual bool __cdecl invokeExecute(char, unsigned short &);  // 0x4b1460
};

class TargetSelectorForDamageTransferNpcSquad
{
public:
    virtual __cdecl ~TargetSelectorForDamageTransferNpcSquad(void);  // 0x27560
    void __cdecl AddTarget(unsigned __int64, __int64, ::Creature *, ::Creature *, wchar_t const *);  // 0x48d290
public:
    struct TargetInfo
    {
        __int64 squareDistance;        // +0 (0x0)
        unsigned __int64 creatureId;   // +8 (0x8)
        TargetInfo(__int64 distance, unsigned __int64 id) : squareDistance(distance), creatureId(id) {}
    };
private:
    ::std::map<unsigned __int64, TargetInfo, ::std::less<unsigned __int64>, ::StlAllocator< ::std::pair<unsigned __int64, TargetInfo>, 2> > _list;  // +8 (0x8)
};

class TargetSkillAction
{
public:
    __cdecl TargetSkillAction(void);  // 0x4aca00
protected:
    virtual bool __cdecl isCastable(void);  // 0x4aca40
    virtual bool __cdecl isFlyable(char);  // 0x4acb50
public:
    virtual bool __cdecl SucceedTargetInfo(__int64, int, unsigned __int64 &, ::vector16 &, unsigned __int64 *const, char &);  // 0x4acc40
protected:
    virtual void __cdecl gatherTarget(char);  // 0x4acc90
    virtual bool __cdecl invokeExecute(char, unsigned short &);  // 0x4ad150
    virtual bool __cdecl isExecutable(char);  // 0x4ad470
};

bool __cdecl checkItemSkillData(::Pc const *, ::Data::ItemSkillRecordPtr, int, unsigned int, char);  // 0x494cc0
