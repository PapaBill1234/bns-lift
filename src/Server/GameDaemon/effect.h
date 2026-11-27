// effect.h: effect.cpp, effect.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"
#include "effectproperty.h"

// PDB: CreatureEffectSlot (size 0x8, abstract base of the creature effect slots).
class CreatureEffectSlot
{
public:
    virtual ~CreatureEffectSlot();  // slot 0
    virtual ::EffectSlotList *const GetEffectSlotList(int const) = 0;  // slot 1
};

class BossNpcEffectSlot
{
public:
    __cdecl BossNpcEffectSlot(void);  // 0x5aa970
    virtual ::EffectSlotList *const __cdecl GetEffectSlotList(int);  // 0x5aaae0
};

class ControlledCreatureEffectSlot
{
public:
    virtual ::EffectSlotList *const __cdecl GetEffectSlotList(int);  // 0x453b40
    __cdecl ControlledCreatureEffectSlot(void);  // 0x5aa150
private:
    ::EffectSlotList slotList[19];  // +0x08. LIFT: the other PDB members follow in later waves
};

class DuelBotEffectSlot
{
public:
    __cdecl DuelBotEffectSlot(void);  // 0x5aa500
    virtual ::EffectSlotList *const __cdecl GetEffectSlotList(int);  // 0x5aa760
};

class Effect : public ::DynamicRefCntObj
{
    // PDB data members (size 0x70).
protected:
    ::Zone * zone;                              // +0x18
    ::GameObject * target;                      // +0x20
    unsigned __int64 casterId;                  // +0x28
    char skillInstanceId;                       // +0x30
    unsigned __int64 skillKey;                  // +0x38
    unsigned int groupId;                       // +0x40
    ::Data::EffectRecord const * data;          // +0x48
    ::EffectSlot effectSlot;                    // +0x50
    ::EffectSource source;                      // +0x54
    __int64 damageRate;                         // +0x58
    bool broadcastEnable;                       // +0x60
    int broadcastBitFlag;                       // +0x64
    ::EffectAttachFail _invokeReason;           // +0x68
protected:
    virtual bool __cdecl Initialize2(::EffectSource, ::Zone *, unsigned __int64, unsigned __int64, char, unsigned __int64, ::Data::EffectRecord const *, long);  // 0x453a20
    virtual bool __cdecl Initialize3(::EffectSource, ::Zone *, unsigned __int64, unsigned __int64, char, unsigned __int64, ::Data::EffectRecord const *, bool, ::SkillResult, ::ApplySkillModifyInfo *, short, ::vector16, short, short);  // 0x453a60
    virtual bool __cdecl Initialize4(::EffectSource, ::Zone *, unsigned __int64, unsigned __int64, char, unsigned __int64, ::Data::EffectRecord const *, ::vector16, char, ::TargetPart, unsigned __int64, unsigned __int64);  // 0x453aa0
    virtual bool __cdecl Initialize5(::EffectSource, ::Zone *, unsigned __int64, unsigned __int64, char, unsigned __int64, long, ::vector16, short, bool, short, int, short, unsigned __int64, unsigned __int64, unsigned __int64, unsigned __int64);  // 0x453ae0
public:
    virtual __cdecl ~Effect(void);  // 0x5a2ec0
    virtual ::Data::EffectRecordSubType __cdecl GetDataSubType(void);  // 0x5a2f30
protected:
    virtual bool __cdecl Initialize1(::EffectSource, ::Zone *, unsigned __int64, unsigned __int64, char, unsigned __int64, ::Data::EffectRecord const *);  // 0x5a2f40
public:
    static bool __cdecl GetCreatureFunctionFieldId(::Data::EffectFunctionType, unsigned short &);  // 0x5a3480
    static void __cdecl CalcDamagePowerPercent(int, int, int, int, __int64 &, int &, ::ApplySkillModifyInfo *);  // 0x5a35b0
    static void __cdecl InvokeEffects(::EffectSource, ::Zone *, unsigned __int64, unsigned __int64, unsigned __int64 const *const, char);  // 0x5a3610
    static void __cdecl InvokePassiveEffects(::EffectSource, ::Zone *, unsigned __int64, unsigned __int64, unsigned __int64 const *const, char);  // 0x5a3720
protected:
    bool __cdecl getPosition(::vector16 &);  // 0x5a38d0
    void __cdecl transferEvent(void);  // 0x5a39a0
    void __cdecl broadcastOther(char, char, unsigned int, ::ChangedProperty *, char const *, int, ...);  // 0x5a3ab0
    void __cdecl broadcast(char, unsigned int, ::ChangedProperty *, char const *, int, ...);  // 0x5a3ca0
    void __cdecl createDuelbotEffectAction(char, unsigned int, char const *, int, ...);  // 0x5a3e90
    bool __cdecl checkImmuneDebuff(void);  // 0x5a3fd0
    bool __cdecl checkEffectAttribute(::ChangedProperty *);  // 0x5a4060
    bool __cdecl dropFieldItem(void);  // 0x5a4210
};

class EffectContainer
{
public:
    static bool __cdecl IsBroadcastSlot(::EffectSlot);  // 0x453b60
    __cdecl EffectContainer(void);  // 0x5aab70
    __cdecl ~EffectContainer(void);  // 0x5aac20
    void __cdecl Initialize(::Creature *);  // 0x5aaed0
    bool __cdecl Attach(::PassiveEffect *, ::ChangedProperty *);  // 0x5ab0f0
    bool __cdecl Detach(::PassiveEffect *, ::DetachReason, int);  // 0x5ab430
    bool __cdecl DetachByGroupId(::EffectSlot, unsigned int, ::DetachReason);  // 0x5ab7a0
    bool __cdecl DetachByDataId(::EffectSlot, unsigned int, ::DetachReason);  // 0x5ab910
    bool __cdecl DetachByAttributeValue(::Data::EffectEffectSlotType, unsigned __int64, unsigned __int64, unsigned __int64, char, bool);  // 0x5aba90
    bool __cdecl DetachByType(::Data::EffectRecordSubType, ::DetachReason, short, __int64, bool);  // 0x5abf80
    bool __cdecl DetachAll(::EffectSlot, ::DetachReason, int);  // 0x5ac0a0
    bool __cdecl DetachBindingSkillStep(bool);  // 0x5ac200
    bool __cdecl DetachFactionScore(int);  // 0x5ac380
    bool __cdecl Find(::Data::EffectRecordSubType, ::PassiveEffect **);  // 0x5ac510
    bool __cdecl Find(::EffectSlot, ::Data::EffectRecordSubType, ::PassiveEffect **);  // 0x5ac670
private:
    void __cdecl clearGeoEffects(void);  // 0x5ac7c0
    void __cdecl clearEffectsByLeaveZone(void);  // 0x5acba0
    void __cdecl clearEffects(void);  // 0x5acf80
public:
    void __cdecl DetachAllBuffDebuff(bool, bool);  // 0x5ad2e0
    void __cdecl DetachByDuelBotChallengeAttractionRule(void);  // 0x5ad810
    void __cdecl RemainBySkillTrainingRoomAttractionRule(void);  // 0x5adbf0
    void __cdecl RemainByChallengePartyAttractionRule(void);  // 0x5adfd0
    void __cdecl ClearAllBuffDebuff(void);  // 0x5ae3b0
    void __cdecl EnterZone(::EnterReason);  // 0x5ae810
    void __cdecl LeaveZone(::LeaveReason, bool);  // 0x5ae9a0
    void __cdecl SendUpdateCache(void);  // 0x5aeaf0
private:
    void __cdecl sendDeleteCache(::PassiveEffect *);  // 0x5aed50
    void __cdecl updatePassiveEffects(bool);  // 0x5aedc0
public:
    bool __cdecl OnEvent(unsigned __int64, unsigned __int64, ::Data::EffectRecordSubType);  // 0x5aefa0
    bool __cdecl OnEvent(unsigned __int64, unsigned __int64, ::Data::SkillEventTypeType, ::SkillResult, short);  // 0x5af290
    bool __cdecl OnEventByCasting(bool);  // 0x5af460
private:
    bool __cdecl onEvent(unsigned __int64, unsigned __int64, ::EffectEventType);  // 0x5af510
    void __cdecl postEvent(::EffectEventType, short);  // 0x5af920
public:
    int __cdecl SetDbList(unsigned __int64, short, char const *, int, ::EffectProperty *, short &);  // 0x5afb30
private:
    void __cdecl restore(::EffectProperty const *const, short);  // 0x5afcf0
public:
    short __cdecl FetchList(short *, char *, short, int);  // 0x5b0160
    short __cdecl GetListSize(void);  // 0x5b0320
private:
    short __cdecl newIndex(::EffectSlot);  // 0x5b03c0
public:
    void __cdecl SetSchedule(::PassiveEffect *, long);  // 0x5b0440
    bool __cdecl SetScheduleInterval(long);  // 0x5b0500
    bool __cdecl setScheduleInterval(long);  // 0x5b0600
    void __cdecl OnTimer(long);  // 0x5b0690
private:
    void __cdecl executeSchedule(long);  // 0x5b0790
    void __cdecl releaseDetachedList(void);  // 0x5b0920
    void __cdecl reschedule(__int64, long);  // 0x5b09e0
    // LIFT: PDB members from +0x00 only; the rest of the 0x100 layout comes in a later card.
    ::CreatureEffectSlot* ownerEffectSlot;  // +0x00
};

class EffectFactory
{
public:
    __cdecl ~EffectFactory(void);  // 0x5b0b50
    bool __cdecl Init(void);  // 0x5b0be0
    char __cdecl GetBroadcastType(int) const;  // 0x5b0dc0
private:
    ::Effect * __cdecl CreateEffect(::Data::EffectRecordSubType) const;  // 0x5b0e20
public:
    ::Effect * __cdecl CreateEffect(::EffectSource, ::Zone *, unsigned __int64, unsigned __int64, char, unsigned __int64, ::Data::EffectRecord const *) const;  // 0x5b37f0
private:
    bool __cdecl initEffect(::Effect *, ::EffectSource, ::Zone *, unsigned __int64, unsigned __int64, char, unsigned __int64, ::Data::EffectRecord const *, long, bool, ::SkillResult, ::ApplySkillModifyInfo *, short, ::vector16, short, short, ::vector16, char, ::TargetPart, unsigned __int64, unsigned __int64, bool, short, int, short, unsigned __int64, unsigned __int64, unsigned __int64, unsigned __int64) const;  // 0x5b3970
public:
    ::EffectAttachFail __cdecl InvokeEffect(::EffectSource, ::Zone *, unsigned __int64, unsigned __int64, char, unsigned __int64, ::Data::EffectRecord const *, long, bool, ::SkillResult, ::ApplySkillModifyInfo *, short, ::vector16, short, short, ::vector16, char, ::TargetPart, unsigned __int64, unsigned __int64, bool, short, int, short, unsigned __int64, unsigned __int64, unsigned __int64, unsigned __int64) const;  // 0x5b3d20
    ::EffectAttachFail __cdecl InvokeEffect(::EffectSource, ::Zone *, unsigned __int64, unsigned __int64, char, unsigned __int64, unsigned __int64, short, unsigned int) const;  // 0x5b3ef0
    ::EffectAttachFail __cdecl InvokeEffect(::EffectSource, ::Zone *, unsigned __int64, unsigned __int64, char, unsigned __int64, ::Data::EffectRecord const *, short, unsigned int) const;  // 0x5b3ff0
    ::EffectAttachFail __cdecl InvokeEffect(::EffectSource, ::Zone *, unsigned __int64, unsigned __int64, char, unsigned __int64, unsigned __int64, long) const;  // 0x5b4180
    ::EffectAttachFail __cdecl InvokeEffect(::EffectSource, ::Zone *, unsigned __int64, unsigned __int64, char, unsigned __int64, ::Data::EffectRecord const *, long) const;  // 0x5b4250
    ::EffectAttachFail __cdecl InvokeEffect(::EffectSource, ::Zone *, unsigned __int64, unsigned __int64, char, unsigned __int64, ::Data::EffectRecord const *, bool, ::SkillResult, ::ApplySkillModifyInfo *, short, ::vector16, short, short) const;  // 0x5b4410
    ::EffectAttachFail __cdecl InvokeEffect(::EffectSource, ::Zone *, unsigned __int64, unsigned __int64, char, unsigned __int64, unsigned __int64, ::vector16, char, ::TargetPart, unsigned __int64, unsigned __int64) const;  // 0x5b45d0
    ::EffectAttachFail __cdecl InvokeEffect(::EffectSource, ::Zone *, unsigned __int64, unsigned __int64, char, unsigned __int64, ::Data::EffectRecord const *, ::vector16, char, ::TargetPart, unsigned __int64, unsigned __int64) const;  // 0x5b46d0
};

class EffectList
{
public:
    __cdecl EffectList(void);  // 0x5b4870
    __cdecl ~EffectList(void);  // 0x5b48d0
    void __cdecl Insert(::PassiveEffect *);  // 0x5b4910
    void __cdecl Delete(::EffectNode *);  // 0x5b4990
    void __cdecl Clear(void);  // 0x5b49f0
private:
    ::EffectNode* head;  // +0x00
};

class EffectTimer
{
private:
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x5b4aa0
};

class InstantEffect
{
public:
    virtual ::EffectAttachFail __cdecl Invoke(short, unsigned int);  // 0x5a4260
protected:
    virtual void __cdecl postApply(void);  // 0x5a4430
private:
    void __cdecl addZoneScore(void);  // 0x5a4900
};

class NpcEffectSlot
{
public:
    __cdecl NpcEffectSlot(void);  // 0x5aa810
};

class PassiveEffect : public ::Effect
{
public:
    enum ReturnStackable {};
public:
    virtual short __cdecl GetDbIndex(void) const;  // 0x453b20
    virtual char __cdecl GetStackCount(void) const;  // 0x453b30
    __cdecl PassiveEffect(void);  // 0x5a49b0
    // PDB data members (size 0x100).
private:
    short _slotIndex;                           // +0x70
    long _scheduleTime;                         // +0x74
    __int64 _updateTime;                        // +0x78
    bool _validateAction;                       // +0x80
    bool _immuned;                              // +0x81
    bool _detach;                               // +0x82
    bool _appliedMaxStackFlag;                  // +0x83
    __int64 _attachedTime;                      // +0x88
    __int64 _passiveDuration;                   // +0x90
    __int64 _lastUpdateScheduleTime;            // +0x98
    long _passiveInterval;                      // +0xA0
    long _accumulateDiffTime;                   // +0xA4
protected:
    ::Data::EffectAccumulateDamageSlotType _accumulateDamageSlotType;  // +0xA8
    int _accumulatedDamageType;                 // +0xAC. LIFT: the PDB type is Data::EffectAccumulatedDamageTypeType (enum, not declared yet)
    __int64 _maxAccumulateDamage;               // +0xB0
    ::EffectProperty _prop;                     // +0xB8
protected:
    virtual bool __cdecl Initialize1(::EffectSource, ::Zone *, unsigned __int64, unsigned __int64, char, unsigned __int64, ::Data::EffectRecord const *);  // 0x5a4b80
public:
    short __cdecl FetchBroadcast(char *, short) const;  // 0x5a4d90
    short __cdecl FetchDb(char *, short) const;  // 0x5a4e20
    void __cdecl SetProperty(::EffectProperty const *);  // 0x5a4ea0
    virtual ::EffectAttachFail __cdecl Invoke(short, unsigned int);  // 0x5a4fb0
protected:
    void __cdecl setDuration(long);  // 0x5a52c0
public:
    short __cdecl GetSlotIndex(void);  // 0x5a5320
private:
    void __cdecl attached(short, ::ChangedProperty *);  // 0x5a5430
    void __cdecl detached(::DetachReason, bool, bool);  // 0x5a56a0
    bool __cdecl invokeDetachEffect(::DetachReason);  // 0x5a5ae0
    void __cdecl intervalExpired(long, __int64);  // 0x5a5cf0
public:
    bool __cdecl ResetDuration(long);  // 0x5a60b0
    void __cdecl CalcRemained(void);  // 0x5a61f0
    long __cdecl GetRemainDuration(wchar_t *);  // 0x5a62a0
    void __cdecl CalcScheduleTime(__int64, long);  // 0x5a6300
    void __cdecl UpdateScheduleTime(__int64, bool);  // 0x5a63d0
private:
    void __cdecl broadcastPassiveFullSync(bool);  // 0x5a64b0
    void __cdecl broadcastPassiveDetachCountSync(void);  // 0x5a65d0
    void __cdecl broadcastPassiveDetach(void);  // 0x5a6760
    bool __cdecl checkApplyPassive(void);  // 0x5a6850
protected:
    ::Data::EffectTransitionType __cdecl getTransitionLinkState(void);  // 0x5a68f0
private:
    bool __cdecl dispelLink(void);  // 0x5a69a0
    bool __cdecl applyDurationFormula(long &);  // 0x5a79b0
    bool __cdecl checkStackable(::PassiveEffect::ReturnStackable &);  // 0x5a7d00
    long __cdecl getExpirationRemainDuration(void);  // 0x5a7dc0
    ::PassiveEffect::ReturnStackable __cdecl checkStackPriority(::PassiveEffect *);  // 0x5a7e70
    ::EffectEventType __cdecl getEventType(::Data::EffectDetachSlotType);  // 0x5a9040
    void __cdecl execChangeDefaultStanceByFlag(::ChangedProperty *);  // 0x5a9130
    void __cdecl reApplyAbility(char, ::ChangedProperty *);  // 0x5a9210
    void __cdecl applyAbility(bool, ::ChangedProperty *);  // 0x5a9340
    void __cdecl applyFunctionFlag(bool, ::ChangedProperty *);  // 0x5a94a0
    void __cdecl applyEffectAttribute(bool, ::ChangedProperty *);  // 0x5a95c0
    void __cdecl applyEffectFlag(bool, ::ChangedProperty *);  // 0x5a9930
    void __cdecl applyMaxStackEffectFlag(bool, ::ChangedProperty *);  // 0x5a99b0
protected:
    bool __cdecl onEvent(unsigned __int64, unsigned __int64, ::EffectEventType);  // 0x5a9a30
    bool __cdecl invokeEventEffect(unsigned __int64, unsigned __int64, ::EffectEventType);  // 0x5a9dc0
    bool __cdecl invokeTransformEffect(void);  // 0x5aa0a0
};

