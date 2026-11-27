// duelbot.h: duelbot.cpp, duelbot.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class DuelBot
{
public:
    virtual void __cdecl ClearLastComboSkillValue(void);  // 0x97240
    virtual unsigned int __cdecl GetLastComboSkill(void) const;  // 0x97270
    virtual void __cdecl SetLastComboSkill(unsigned int);  // 0x97280
    virtual __int64 __cdecl GetLastComboFireLimitTime(void) const;  // 0x97290
    virtual void __cdecl SetLastComboFireLimitTime(__int64);  // 0x972a0
    virtual __int64 __cdecl GetLastComboExecFirstLimitTime(void) const;  // 0x972b0
    virtual void __cdecl SetLastComboExecFirstLimitTime(__int64);  // 0x972c0
    virtual __int64 __cdecl GetLastComboExecLastLimitTime(void) const;  // 0x972d0
    virtual void __cdecl SetLastComboExecLastLimitTime(__int64);  // 0x972e0
    virtual ::SkillResult __cdecl GetLastComboExecFirstResult(void) const;  // 0x972f0
    virtual void __cdecl SetLastComboExecFirstResult(::SkillResult);  // 0x97300
    virtual ::SkillResult __cdecl GetLastComboExecLastResult(void) const;  // 0x97310
    virtual void __cdecl SetLastComboExecLastResult(::SkillResult);  // 0x97320
    virtual __int64 __cdecl GetLastAttackLimitTime(::SkillResult) const;  // 0x97330
    virtual void __cdecl SetLastAttackLimitTime(::SkillResult, __int64);  // 0x97340
    virtual __int64 __cdecl GetLastAttackedLimitTime(::SkillResult) const;  // 0x97350
    virtual void __cdecl SetLastAttackedLimitTime(::SkillResult, __int64);  // 0x97360
    virtual short __cdecl GetAttackHitValueModify(void);  // 0x97370
    virtual short __cdecl GetAttackCriticalValueModify(void);  // 0x97380
    virtual short __cdecl GetDefendCriticalValueModify(void);  // 0x97390
    virtual short __cdecl GetDefendDodgeValueModify(void);  // 0x973a0
    virtual short __cdecl GetDefendParryValueModify(void);  // 0x973b0
    virtual short __cdecl GetDefendPhysicalValueModify(void);  // 0x973c0
    virtual short __cdecl GetDefendForceValueModify(void);  // 0x973d0
    virtual short __cdecl GetAttackStiffDurationValueModify(void);  // 0x973e0
    virtual short __cdecl GetDefendStiffDurationValueModify(void);  // 0x973f0
    virtual short __cdecl GetCastDurationValueModify(void);  // 0x97400
    virtual short __cdecl GetAttackCriticalDamageModify(void);  // 0x97410
    virtual short __cdecl GetDefendCriticalDamageModify(void);  // 0x97420
    virtual short __cdecl GetAttackPierceModify(void);  // 0x97430
    virtual short __cdecl GetAttackParryPierceModify(void);  // 0x97440
    virtual short __cdecl GetDefendParryReduceModify(void);  // 0x97450
    virtual short __cdecl GetAttackPerfectParryDamageModify(void);  // 0x97460
    virtual short __cdecl GetDefendPerfectParryReduceModify(void);  // 0x97470
    virtual short __cdecl GetAttackCounterDamageModify(void);  // 0x97480
    virtual short __cdecl GetDefendCounterReduceModify(void);  // 0x97490
    virtual short __cdecl GetHealPowerModify(void);  // 0x974a0
    virtual short __cdecl GetAOEDefendPowerModify(void);  // 0x974b0
    virtual short __cdecl GetAbnormalAttackPowerModify(void);  // 0x974c0
    virtual short __cdecl GetAbnormalDefendPowerModify(void);  // 0x974d0
    virtual short __cdecl GetHatePowerModify(void);  // 0x974e0
    virtual short __cdecl GetAttackAttributeModify(void);  // 0x974f0
    virtual short __cdecl GetRAttackAoePierceModify(void);  // 0x97500
    virtual short __cdecl GetRAttackAbnormalHitModify(void);  // 0x97510
    virtual short __cdecl GetRDefendAbnormalDodgeModify(void);  // 0x97520
    virtual short __cdecl GetRSupportPowerModify(void);  // 0x97530
    virtual short __cdecl GetRHypermovePowerModify(void);  // 0x97540
    __cdecl DuelBot(::Data::DuelBotRecordPtr const &, char);  // 0x9ba90
    virtual __cdecl ~DuelBot(void);  // 0x9bc50
    bool __cdecl Initialize(unsigned __int64, ::Zone *, char);  // 0x9bd10
    virtual void __cdecl EnterZone(::EnterReason, bool, unsigned int);  // 0x9bf30
    virtual void __cdecl LeaveZone(::LeaveReason);  // 0x9c000
private:
    void __cdecl loadData(void);  // 0x9c090
    void __cdecl equipItems(void);  // 0x9c7b0
    void __cdecl calcItemAbility(::Data::ItemRecordPtr const &, ::Data::EffectRecordItemAbility &);  // 0x9d0d0
    void __cdecl validateAbility(void);  // 0x9d6a0
    void __cdecl setMaxHp(void);  // 0x9d9e0
    ::Data::DuelBotTrainedSkillRecordPtr __cdecl getTrainedSkillData(char);  // 0x9db20
    void __cdecl invokePassiveEffects(void);  // 0x9dec0
public:
    virtual bool __cdecl SetDead(bool, ::ChangedProperty *, unsigned __int64, unsigned __int64, unsigned __int64, bool, bool);  // 0x9df70
    virtual bool __cdecl HandleStance(char, unsigned __int64 const *, int, ::ChangedProperty *);  // 0x9e030
    unsigned __int64 __cdecl GetEquippedItemKey(short);  // 0x9e0e0
    bool __cdecl CheckUseSkill(unsigned __int64, unsigned int, char);  // 0x9e1c0
    virtual void __cdecl OnKilled(::Zone *, ::GameObject *, unsigned __int64);  // 0x9e220
    virtual void __cdecl OnCombatStart(::Creature *);  // 0x9e4f0
    virtual void __cdecl OnCombatEnd(void);  // 0x9e6b0
    void __cdecl SetActiveDuelBotSummoned(::DuelBotSummoned *);  // 0x9e7c0
    void __cdecl ClearDuelBotSummoned(void);  // 0x5ea260
};

class DuelBotCreature
{
public:
    virtual __cdecl ~DuelBotCreature(void);  // 0x9b950
    virtual void __cdecl Send(char const *, ...);  // 0x9b970
    virtual void __cdecl Send(::Packet const *);  // 0x9b9d0
    virtual void __cdecl Send(::PacketList const *);  // 0x9ba40
};

class DuelBotSummoned
{
public:
    virtual short __cdecl GetAttackHitValueModify(void);  // 0x97550
    virtual short __cdecl GetAttackCriticalValueModify(void);  // 0x97560
    virtual short __cdecl GetDefendCriticalValueModify(void);  // 0x97570
    virtual short __cdecl GetDefendDodgeValueModify(void);  // 0x97580
    virtual short __cdecl GetDefendParryValueModify(void);  // 0x97590
    virtual short __cdecl GetDefendPhysicalValueModify(void);  // 0x975a0
    virtual short __cdecl GetDefendForceValueModify(void);  // 0x975b0
    virtual short __cdecl GetAttackStiffDurationValueModify(void);  // 0x975c0
    virtual short __cdecl GetDefendStiffDurationValueModify(void);  // 0x975d0
    virtual short __cdecl GetCastDurationValueModify(void);  // 0x975e0
    virtual short __cdecl GetAttackCriticalDamageModify(void);  // 0x975f0
    virtual short __cdecl GetDefendCriticalDamageModify(void);  // 0x97600
    virtual short __cdecl GetAttackPierceModify(void);  // 0x97610
    virtual short __cdecl GetAttackParryPierceModify(void);  // 0x97620
    virtual short __cdecl GetDefendParryReduceModify(void);  // 0x97630
    virtual short __cdecl GetAttackPerfectParryDamageModify(void);  // 0x97640
    virtual short __cdecl GetDefendPerfectParryReduceModify(void);  // 0x97650
    virtual short __cdecl GetAttackCounterDamageModify(void);  // 0x97660
    virtual short __cdecl GetDefendCounterReduceModify(void);  // 0x97670
    virtual short __cdecl GetHealPowerModify(void);  // 0x97680
    virtual short __cdecl GetAOEDefendPowerModify(void);  // 0x97690
    virtual short __cdecl GetAbnormalAttackPowerModify(void);  // 0x976a0
    virtual short __cdecl GetAbnormalDefendPowerModify(void);  // 0x976b0
    virtual short __cdecl GetHatePowerModify(void);  // 0x976c0
    virtual short __cdecl GetAttackAttributeModify(void);  // 0x976d0
    virtual short __cdecl GetRAttackAoePierceModify(void);  // 0x976e0
    virtual short __cdecl GetRAttackAbnormalHitModify(void);  // 0x976f0
    virtual short __cdecl GetRDefendAbnormalDodgeModify(void);  // 0x97700
    virtual short __cdecl GetRSupportPowerModify(void);  // 0x97710
    virtual short __cdecl GetRHypermovePowerModify(void);  // 0x97720
    __cdecl DuelBotSummoned(void);  // 0x9e930
    virtual __cdecl ~DuelBotSummoned(void);  // 0x9ea50
    bool __cdecl Initialize(unsigned __int64, ::DuelBot *, ::SummonedEntry *, ::Data::SummonedRecordPtr, ::Data::SummonedLevelRecordPtr);  // 0x9eae0
    virtual bool __cdecl HandleStance(char, unsigned __int64 const *, int, ::ChangedProperty *);  // 0x9eba0
    virtual void __cdecl EnterZone(::EnterReason, bool, unsigned int);  // 0x9ebd0
    virtual void __cdecl LeaveZone(::LeaveReason);  // 0x9ee60
    virtual void __cdecl GetImmuneEffectAttributeValueFromData(unsigned __int64 &, unsigned __int64 &, unsigned __int64 &);  // 0x9ef30
    virtual void __cdecl OnTimer(::Zone *, unsigned short);  // 0x9efc0
    void __cdecl DespawnDelaying(void);  // 0x9f0e0
    void __cdecl Spawn(::EnterReason);  // 0x9f1a0
    void __cdecl Decompose(void);  // 0x9f310
    void __cdecl SyncMasterState(void);  // 0x9f440
    void __cdecl LoadData(void);  // 0x9f5c0
    bool __cdecl ApplyLevelData(::ChangedProperty *const, char, char);  // 0x9f890
    bool __cdecl ValidateAbility(::ChangedProperty *const, char);  // 0x9f9e0
    bool __cdecl RemasterValidateAbility(::ChangedProperty *const, char);  // 0x9fe50
    bool __cdecl ApplySummonerJobAbility(::ChangedProperty *, ::Data::SummonedLevelRecord const *);  // 0xa03e0
    virtual void __cdecl OnAttacked(::Zone *, ::GameObject *, unsigned __int64, short);  // 0xa1e00
    virtual void __cdecl OnCombatStart(::Creature *, ::ChangedProperty *);  // 0xa1e30
    virtual bool __cdecl SetDead(bool, ::ChangedProperty *, unsigned __int64, unsigned __int64, unsigned __int64, bool, bool);  // 0xa1e50
private:
    void __cdecl handleSpawningStateProperty(bool);  // 0xa1fa0
    void __cdecl finishSpawning(bool);  // 0xa20f0
};

class DuelBotSummonedManager
{
public:
    __cdecl ~DuelBotSummonedManager(void);  // 0xa2270
    bool __cdecl Initialize(::DuelBot *, int);  // 0xa22f0
    void __cdecl CreateSummoned(int);  // 0xa2760
};

class ZoneDuelBotIdManager
{
protected:
    virtual bool __cdecl IsExist(unsigned __int64);  // 0x228450
};

