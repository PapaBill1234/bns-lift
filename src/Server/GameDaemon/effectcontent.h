// effectcontent.h: effectcontent.cpp, effectcontent.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class AccumulatedDamageEffect
{
private:
    virtual void __cdecl attachDissolve(::ChangedProperty *, ::DetachReason &);  // 0x5c7420
    virtual void __cdecl attachApply(::ChangedProperty *);  // 0x5d13d0
public:
    virtual bool __cdecl Initialize1(::EffectSource, ::Zone *, unsigned __int64, unsigned __int64, char, unsigned __int64, ::Data::EffectRecord const *);  // 0x5d1c30
private:
    virtual bool __cdecl checkApply(void);  // 0x5d1d00
    virtual void __cdecl preDissolveProc(bool, ::ChangedProperty *);  // 0x5d1d50
public:
    bool __cdecl Explode(::ChangedProperty *, unsigned __int64, char, unsigned __int64, int, ::Data::EffectAccumulatedDamageUseTypeType, short);  // 0x5d1e00
};

class AdditionalHpEffect
{
private:
    virtual bool __cdecl checkApply(void);  // 0x5bf3e0
    virtual void __cdecl attachApply(::ChangedProperty *);  // 0x5c8190
    virtual void __cdecl attachDissolve(::ChangedProperty *, ::DetachReason &);  // 0x5c8340
};

class AirDashEffect
{
public:
    virtual ::Data::EffectRecordSubType __cdecl GetDataSubType(void);  // 0x47a530
    virtual bool __cdecl Initialize5(::EffectSource, ::Zone *, unsigned __int64, unsigned __int64, char, unsigned __int64, long, ::vector16, short, bool, short, int, short, unsigned __int64, unsigned __int64, unsigned __int64, unsigned __int64);  // 0x5cb860
private:
    virtual void __cdecl attachApply(::ChangedProperty *);  // 0x5cb990
    virtual void __cdecl attachDissolve(::ChangedProperty *, ::DetachReason &);  // 0x5cbb50
};

class AirKnockbackEffect
{
private:
    virtual void __cdecl attachDissolve(::ChangedProperty *, ::DetachReason &);  // 0x5cad70
public:
    virtual bool __cdecl Initialize1(::EffectSource, ::Zone *, unsigned __int64, unsigned __int64, char, unsigned __int64, ::Data::EffectRecord const *);  // 0x5cc070
private:
    virtual void __cdecl attachApply(::ChangedProperty *);  // 0x5cc190
};

class AttackEffect
{
public:
    __cdecl AttackEffect(void);  // 0x5b8b10
    virtual bool __cdecl Initialize3(::EffectSource, ::Zone *, unsigned __int64, unsigned __int64, char, unsigned __int64, ::Data::EffectRecord const *, bool, ::SkillResult, ::ApplySkillModifyInfo *, short, ::vector16, short, short);  // 0x5b8bd0
protected:
    void __cdecl calcPower(int &, __int64 &);  // 0x5b8d90
    __int64 __cdecl calcDamage(int, __int64);  // 0x5b9e30
    bool __cdecl applyDamage(__int64, ::ChangedProperty *);  // 0x5bbe80
private:
    virtual void __cdecl apply(void);  // 0x5bc530
};

class AttackGlideEffect
{
private:
    virtual bool __cdecl checkApply(void);  // 0x5d0790
    virtual void __cdecl attachApply(::ChangedProperty *);  // 0x5d0880
    virtual void __cdecl attachDissolve(::ChangedProperty *, ::DetachReason &);  // 0x5d0960
    virtual void __cdecl intervalApply(void);  // 0x5d0a30
};

class AttackPassiveEffect
{
public:
    __cdecl AttackPassiveEffect(void);  // 0x5b7440
    virtual bool __cdecl Initialize3(::EffectSource, ::Zone *, unsigned __int64, unsigned __int64, char, unsigned __int64, ::Data::EffectRecord const *, bool, ::SkillResult, ::ApplySkillModifyInfo *, short, ::vector16, short, short);  // 0x5b7540
protected:
    virtual bool __cdecl checkApply(void);  // 0x5b76f0
private:
    virtual void __cdecl attachApply(::ChangedProperty *);  // 0x5b7770
    virtual void __cdecl attachDissolve(::ChangedProperty *, ::DetachReason &);  // 0x5b7870
    short __cdecl getFlag(void);  // 0x5b78f0
    bool __cdecl calcPower(int &, __int64 &);  // 0x5b7960
    __int64 __cdecl calcDamage(int, __int64);  // 0x5b7a10
protected:
    virtual void __cdecl applyDamage(__int64 &, ::ChangedProperty *);  // 0x5b7ae0
private:
    virtual void __cdecl intervalApply(void);  // 0x5b7c50
};

class BindingSkillStepEffect
{
public:
    virtual bool __cdecl Initialize2(::EffectSource, ::Zone *, unsigned __int64, unsigned __int64, char, unsigned __int64, ::Data::EffectRecord const *, long);  // 0x5c8430
private:
    virtual void __cdecl attachApply(::ChangedProperty *);  // 0x5c8510
};

class CastCancelEffect
{
private:
    virtual void __cdecl apply(void);  // 0x5b8ab0
};

class CommonPassiveEffect
{
public:
    __cdecl CommonPassiveEffect(void);  // 0x479cf0
protected:
    virtual bool __cdecl checkApply(void);  // 0x5b4b30
private:
    virtual void __cdecl attachApply(::ChangedProperty *);  // 0x5b4c00
    virtual void __cdecl attachDissolve(::ChangedProperty *, ::DetachReason &);  // 0x5b4c50
    virtual void __cdecl intervalApply(void);  // 0x5b4c60
    bool __cdecl attachApplyData(::ChangedProperty *);  // 0x5b4c70
    bool __cdecl attachDissolveData(::ChangedProperty *, ::DetachReason);  // 0x5b5030
    bool __cdecl intervalApplyData(void);  // 0x5b5800
    void __cdecl makeAbilityData(unsigned short *const, __int64 *const, short *const, short &, short &);  // 0x5b6d80
    void __cdecl addAbility(unsigned short *const, __int64 *const, short *const, short &, unsigned short, short, short);  // 0x5b73a0
};

class DashEffect
{
public:
    virtual ::Data::EffectRecordSubType __cdecl GetDataSubType(void);  // 0x47a4a0
    virtual bool __cdecl Initialize5(::EffectSource, ::Zone *, unsigned __int64, unsigned __int64, char, unsigned __int64, long, ::vector16, short, bool, short, int, short, unsigned __int64, unsigned __int64, unsigned __int64, unsigned __int64);  // 0x5cadf0
private:
    virtual bool __cdecl checkApply(void);  // 0x5caf40
    virtual void __cdecl attachApply(::ChangedProperty *);  // 0x5caf90
    virtual void __cdecl attachDissolve(::ChangedProperty *, ::DetachReason &);  // 0x5cb2e0
};

class DebuffGuildBattleFieldEffect
{
protected:
    virtual void __cdecl attachApply(::ChangedProperty *);  // 0x5c9c20
    virtual void __cdecl intervalApply(void);  // 0x5c9cc0
    virtual bool __cdecl checkApply(void);  // 0x5cbea0
};

class DesireIncreaseEffect
{
private:
    virtual bool __cdecl checkApply(void);  // 0x5bf4d0
    virtual void __cdecl apply(void);  // 0x5bf510
};

class DifficultyTypeDispelAttributeHpDamageEffect
{
private:
    virtual bool __cdecl checkApply(void);  // 0x5bf850
    virtual void __cdecl apply(void);  // 0x5ccab0
};

class DispelAttributeEffect
{
private:
    virtual void __cdecl apply(void);  // 0x5c3760
};

class DispelBuffEffect
{
private:
    virtual void __cdecl apply(void);  // 0x5c37f0
};

class DispelDebuffEffect
{
private:
    virtual void __cdecl apply(void);  // 0x5c3870
};

class DispelTypeEffect
{
private:
    virtual void __cdecl apply(void);  // 0x5c30f0
};

class DuelFighterChangeEffect
{
public:
    __cdecl DuelFighterChangeEffect(void);  // 0x5ccd90
    virtual bool __cdecl Initialize4(::EffectSource, ::Zone *, unsigned __int64, unsigned __int64, char, unsigned __int64, ::Data::EffectRecord const *, ::vector16, char, ::TargetPart, unsigned __int64, unsigned __int64);  // 0x5cce00
private:
    virtual bool __cdecl checkApply(void);  // 0x5cce50
    virtual void __cdecl apply(void);  // 0x5ccf90
};

class DuelFighterTimeLimitEffect
{
public:
    virtual __cdecl ~DuelFighterTimeLimitEffect(void);  // 0x47a820
private:
    virtual bool __cdecl checkApply(void);  // 0x5cd0c0
    virtual void __cdecl attachApply(::ChangedProperty *);  // 0x5cd210
    virtual void __cdecl attachDissolve(::ChangedProperty *, ::DetachReason &);  // 0x5cd270
};

class DuelInterferenceEffect
{
public:
    virtual __cdecl ~DuelInterferenceEffect(void);  // 0x47a8a0
private:
    virtual bool __cdecl checkApply(void);  // 0x5cd3d0
    virtual void __cdecl attachApply(::ChangedProperty *);  // 0x5cd510
    virtual void __cdecl attachDissolve(::ChangedProperty *, ::DetachReason &);  // 0x5cd660
};

class EmbersExplosionTimerEffect
{
protected:
    virtual bool __cdecl checkApply(void);  // 0x5c8620
    virtual void __cdecl attachApply(::ChangedProperty *);  // 0x5c8690
    virtual void __cdecl attachDissolve(::ChangedProperty *, ::DetachReason &);  // 0x5c8830
};

class EnableGuildBattleFieldEffect
{
public:
    virtual bool __cdecl Initialize2(::EffectSource, ::Zone *, unsigned __int64, unsigned __int64, char, unsigned __int64, ::Data::EffectRecord const *, long);  // 0x5c9850
protected:
    virtual void __cdecl attachApply(::ChangedProperty *);  // 0x5c9980
    virtual void __cdecl attachDissolve(::ChangedProperty *, ::DetachReason &);  // 0x5c9aa0
};

class ExhaustionEffect
{
private:
    virtual void __cdecl attachApply(::ChangedProperty *);  // 0x5cbc30
};

class ExtendEffect
{
private:
    virtual void __cdecl apply(void);  // 0x5bf420
};

class ExtendLinkEffect
{
private:
    virtual bool __cdecl checkApply(void);  // 0x5be900
    virtual void __cdecl apply(void);  // 0x5be940
};

class FallDamageEffect
{
public:
    virtual ::Data::EffectRecordSubType __cdecl GetDataSubType(void);  // 0x47a520
    virtual bool __cdecl Initialize5(::EffectSource, ::Zone *, unsigned __int64, unsigned __int64, char, unsigned __int64, long, ::vector16, short, bool, short, int, short, unsigned __int64, unsigned __int64, unsigned __int64, unsigned __int64);  // 0x5cb390
private:
    virtual void __cdecl apply(void);  // 0x5cb4b0
};

class FallDeathEffect
{
public:
    virtual ::Data::EffectRecordSubType __cdecl GetDataSubType(void);  // 0x47a7f0
    __cdecl FallDeathEffect(void);  // 0x5b3750
    virtual bool __cdecl Initialize5(::EffectSource, ::Zone *, unsigned __int64, unsigned __int64, char, unsigned __int64, long, ::vector16, short, bool, short, int, short, unsigned __int64, unsigned __int64, unsigned __int64, unsigned __int64);  // 0x5cc4e0
private:
    virtual bool __cdecl checkApply(void);  // 0x5cc5f0
    virtual void __cdecl apply(void);  // 0x5cc630
};

class FoodIntervalHealEffect
{
public:
    virtual bool __cdecl Initialize4(::EffectSource, ::Zone *, unsigned __int64, unsigned __int64, char, unsigned __int64, ::Data::EffectRecord const *, ::vector16, char, ::TargetPart, unsigned __int64, unsigned __int64);  // 0x5c72c0
private:
    virtual void __cdecl attachApply(::ChangedProperty *);  // 0x5c7310
    virtual void __cdecl intervalApply(void);  // 0x5c7470
};

class FrostbiteDrainEffect
{
private:
    virtual void __cdecl apply(void);  // 0x5c38f0
};

class GuardGaugeDamageEffect
{
private:
    virtual bool __cdecl checkApply(void);  // 0x5b86f0
    virtual void __cdecl apply(void);  // 0x5b8720
};

class GuardGaugeHealEffect
{
private:
    virtual bool __cdecl checkApply(void);  // 0x5b8590
    virtual void __cdecl apply(void);  // 0x5b85c0
};

class HelpRestorationEffect
{
protected:
    virtual void __cdecl attachApply(::ChangedProperty *);  // 0x5c9ea0
    virtual void __cdecl attachDissolve(::ChangedProperty *, ::DetachReason &);  // 0x5ca0f0
};

class HpDamageEffect
{
private:
    virtual bool __cdecl checkApply(void);  // 0x5b8250
    virtual void __cdecl apply(void);  // 0x5b8290
};

class HpDrainEffect
{
private:
    virtual void __cdecl apply(void);  // 0x5c2b50
};

class HpHealAttackPowerEffect
{
private:
    virtual void __cdecl apply(void);  // 0x5b8090
};

class HpHealEffect
{
public:
    virtual bool __cdecl Initialize3(::EffectSource, ::Zone *, unsigned __int64, unsigned __int64, char, unsigned __int64, ::Data::EffectRecord const *, bool, ::SkillResult, ::ApplySkillModifyInfo *, short, ::vector16, short, short);  // 0x5b7e70
private:
    virtual void __cdecl apply(void);  // 0x5b7f30
};

class HpTransferEffect
{
private:
    virtual void __cdecl apply(void);  // 0x5c2e80
};

class ImmuneAttributeEffect
{
private:
    virtual void __cdecl attachApply(::ChangedProperty *);  // 0x5c49c0
    virtual void __cdecl attachDissolve(::ChangedProperty *, ::DetachReason &);  // 0x5c4ab0
};

class IncreaseCasterSpecialSkillGaugeEffect
{
private:
    virtual bool __cdecl checkApply(void);  // 0x5cc8e0
    virtual void __cdecl apply(void);  // 0x5cc940
};

class IncreaseSpecialSkillGaugeEffect
{
private:
    virtual bool __cdecl checkApply(void);  // 0x47a800
    virtual void __cdecl apply(void);  // 0x5cc770
};

class InitializeRecycleGroupEffect
{
private:
    virtual bool __cdecl checkApply(void);  // 0x5bca00
    virtual void __cdecl apply(void);  // 0x5c5e70
};

class InstantaneousDeathEffect
{
private:
    virtual bool __cdecl checkApply(void);  // 0x5c4e80
    virtual void __cdecl apply(void);  // 0x5c4f90
};

class IntervalForceDamageEffect
{
private:
    virtual void __cdecl attachApply(::ChangedProperty *);  // 0x5c7680
    virtual void __cdecl attachDissolve(::ChangedProperty *, ::DetachReason &);  // 0x5c77e0
    virtual void __cdecl intervalApply(void);  // 0x5c7880
};

class IntervalRangePhysicalDamageEffect
{
private:
    virtual void __cdecl attachApply(::ChangedProperty *);  // 0x5c6f90
    virtual void __cdecl intervalApply(void);  // 0x5c70a0
};

class IntervalSecondGaugePointEffect
{
private:
    virtual bool __cdecl checkApply(void);  // 0x5d13a0
    virtual void __cdecl intervalApply(void);  // 0x5d1430
};

class ItemAbilityEffect
{
public:
    virtual bool __cdecl Initialize1(::EffectSource, ::Zone *, unsigned __int64, unsigned __int64, char, unsigned __int64, ::Data::EffectRecord const *);  // 0x5cd7a0
private:
    virtual void __cdecl attachApply(::ChangedProperty *);  // 0x5cd8c0
    virtual void __cdecl attachDissolve(::ChangedProperty *, ::DetachReason &);  // 0x5ce560
};

class KnockBackEffect
{
public:
    __cdecl KnockBackEffect(void);  // 0x5bfa70
    virtual bool __cdecl Initialize3(::EffectSource, ::Zone *, unsigned __int64, unsigned __int64, char, unsigned __int64, ::Data::EffectRecord const *, bool, ::SkillResult, ::ApplySkillModifyInfo *, short, ::vector16, short, short);  // 0x5bfb80
protected:
    virtual bool __cdecl checkApply(void);  // 0x5bfd70
private:
    bool __cdecl calcPower(int &, __int64 &);  // 0x5c00f0
    __int64 __cdecl calcDamage(int, __int64);  // 0x5c0190
protected:
    virtual void __cdecl applyDamage(__int64 &, ::ChangedProperty *);  // 0x5c0260
private:
    virtual void __cdecl attachApply(::ChangedProperty *);  // 0x5c03d0
    virtual void __cdecl attachDissolve(::ChangedProperty *, ::DetachReason &);  // 0x5c0710
    short __cdecl getKnockbackAngle(::vector16 &, ::vector16 &, ::Data::EffectKnockbackDirectionType, short);  // 0x5c07c0
    short __cdecl getKnockbackedYaw(::vector16 &, short, ::Data::EffectKnockbackDirectionType);  // 0x5c0910
    bool __cdecl getKnockBackPos(::vector16 *, long *, ::GeoCell *, __int64 *);  // 0x5c0a50
    bool __cdecl knockBackTarget(::vector16 &, ::GeoCell *, ::ChangedProperty *);  // 0x5c1280
    bool __cdecl dashCaster(::vector16, short, bool);  // 0x5c1520
};

class LinkEffect
{
protected:
    virtual bool __cdecl checkApply(void);  // 0x5bcb80
private:
    virtual void __cdecl attachApply(::ChangedProperty *);  // 0x5bccc0
    virtual void __cdecl attachDissolve(::ChangedProperty *, ::DetachReason &);  // 0x5bd8d0
    bool __cdecl invokeEffect(::DetachReason);  // 0x5be550
    __int64 __cdecl calcContribution(__int64, char);  // 0x5be650
    int __cdecl linkContributionPercent(char);  // 0x5be720
};

class MasteryStatEquipEffect
{
public:
    virtual bool __cdecl Initialize1(::EffectSource, ::Zone *, unsigned __int64, unsigned __int64, char, unsigned __int64, ::Data::EffectRecord const *);  // 0x5cf360
private:
    virtual void __cdecl attachApply(::ChangedProperty *);  // 0x5cf480
    virtual void __cdecl attachDissolve(::ChangedProperty *, ::DetachReason &);  // 0x5cf500
    void __cdecl applyAbilityForMastery(bool, ::ChangedProperty *);  // 0x5cf570
public:
    static bool __cdecl AccumulateModifyAbility(::Data::EffectRecordMasteryStatEquip *, ::Data::EffectRecord const *);  // 0x5cf6d0
    static int __cdecl FindBlankModifyAbility(::Data::EffectRecordMasteryStatEquip const *);  // 0x5cf7c0
};

class ModifyRecycleTimeEffect
{
private:
    virtual bool __cdecl checkApply(void);  // 0x5c6200
    virtual void __cdecl apply(void);  // 0x5c6280
};

class OceanicEffect
{
public:
    virtual ::Data::EffectRecordSubType __cdecl GetDataSubType(void);  // 0x47a770
    virtual bool __cdecl Initialize5(::EffectSource, ::Zone *, unsigned __int64, unsigned __int64, char, unsigned __int64, long, ::vector16, short, bool, short, int, short, unsigned __int64, unsigned __int64, unsigned __int64, unsigned __int64);  // 0x5cc250
private:
    virtual bool __cdecl checkApply(void);  // 0x5cc380
    virtual void __cdecl attachApply(::ChangedProperty *);  // 0x5cc3a0
    virtual void __cdecl attachDissolve(::ChangedProperty *, ::DetachReason &);  // 0x5cc440
};

class PartAttackEffect
{
private:
    virtual void __cdecl apply(void);  // 0x5bc7a0
public:
    virtual bool __cdecl Initialize4(::EffectSource, ::Zone *, unsigned __int64, unsigned __int64, char, unsigned __int64, ::Data::EffectRecord const *, ::vector16, char, ::TargetPart, unsigned __int64, unsigned __int64);  // 0x5bc9b0
};

class ProvocationEffect
{
protected:
    virtual bool __cdecl checkApply(void);  // 0x5c4bb0
private:
    virtual void __cdecl attachApply(::ChangedProperty *);  // 0x5c4c10
    virtual void __cdecl attachDissolve(::ChangedProperty *, ::DetachReason &);  // 0x5c4d80
};

class RecallToCasterEffect
{
protected:
    virtual bool __cdecl checkApply(void);  // 0x5c6790
    virtual void __cdecl attachApply(::ChangedProperty *);  // 0x5ca1f0
};

class RecallToPositionEffect
{
public:
    virtual bool __cdecl Initialize4(::EffectSource, ::Zone *, unsigned __int64, unsigned __int64, char, unsigned __int64, ::Data::EffectRecord const *, ::vector16, char, ::TargetPart, unsigned __int64, unsigned __int64);  // 0x5ca830
protected:
    virtual void __cdecl attachApply(::ChangedProperty *);  // 0x5ca890
};

class RechargeGuildBattleFieldEffect
{
private:
    virtual void __cdecl apply(void);  // 0x5c96d0
};

class RechargeHeartCountEffect
{
private:
    virtual void __cdecl apply(void);  // 0x5c5110
};

class RecoveryContentQuotaEffect
{
private:
    virtual bool __cdecl checkApply(void);  // 0x5c4460
    virtual void __cdecl apply(void);  // 0x5c4510
};

class ReplacePositionEffect
{
private:
    virtual void __cdecl apply(void);  // 0x5c6940
};

class ResurrectionEffect
{
private:
    virtual bool __cdecl checkApply(void);  // 0x5c19f0
    virtual void __cdecl apply(void);  // 0x5c1b70
};

class ReturnEffect
{
private:
    virtual bool __cdecl checkApply(void);  // 0x5c5860
    virtual void __cdecl apply(void);  // 0x5c5940
};

class ReturnSimSkillEffect
{
private:
    virtual bool __cdecl checkApply(void);  // 0x5c5de0
    virtual void __cdecl apply(void);  // 0x5c5e00
};

class ReturnToBaseCampEffect
{
private:
    virtual void __cdecl apply(void);  // 0x5c5990
};

class ReviveExceptRuleEffect
{
private:
    virtual void __cdecl attachApply(::ChangedProperty *);  // 0x5cbcd0
    virtual void __cdecl attachDissolve(::ChangedProperty *, ::DetachReason &);  // 0x5cbde0
};

class SafetyAreaEffect
{
protected:
    virtual void __cdecl attachApply(::ChangedProperty *);  // 0x5c94b0
    virtual void __cdecl attachDissolve(::ChangedProperty *, ::DetachReason &);  // 0x5c95f0
};

class SecondGaugePointEffect
{
private:
    virtual bool __cdecl checkApply(void);  // 0x5d10a0
    virtual void __cdecl apply(void);  // 0x5d1100
};

class SetImmuneBreakerEffect
{
private:
    virtual bool __cdecl checkApply(void);  // 0x5c65d0
    virtual void __cdecl apply(void);  // 0x5c65f0
};

class SetMaxHateEffect
{
private:
    virtual void __cdecl apply(void);  // 0x5bf890
};

class SetMinHateEffect
{
private:
    virtual void __cdecl apply(void);  // 0x5bf670
};

class SetSecondGaugePointEffect
{
private:
    virtual void __cdecl apply(void);  // 0x5d18a0
};

class ShooterLockOnEffect
{
public:
    virtual bool __cdecl Initialize4(::EffectSource, ::Zone *, unsigned __int64, unsigned __int64, char, unsigned __int64, ::Data::EffectRecord const *, ::vector16, char, ::TargetPart, unsigned __int64, unsigned __int64);  // 0x5cf7f0
private:
    virtual void __cdecl attachApply(::ChangedProperty *);  // 0x5d0010
    virtual void __cdecl intervalApply(void);  // 0x5d0070
};

class SoulMaskEffect
{
public:
    virtual bool __cdecl Initialize1(::EffectSource, ::Zone *, unsigned __int64, unsigned __int64, char, unsigned __int64, ::Data::EffectRecord const *);  // 0x5d21d0
private:
    virtual bool __cdecl checkApply(void);  // 0x5d23d0
    virtual void __cdecl attachApply(::ChangedProperty *);  // 0x5d2540
    virtual void __cdecl attachDissolve(::ChangedProperty *, ::DetachReason &);  // 0x5d2720
};

class SpDamageEffect
{
private:
    virtual void __cdecl apply(void);  // 0x5b8980
};

class SpHealEffect
{
private:
    virtual void __cdecl apply(void);  // 0x5b8850
};

class StanceEffect
{
private:
    virtual void __cdecl apply(void);  // 0x5bca40
};

class StopSecondGaugePointEffect
{
private:
    virtual void __cdecl attachApply(::ChangedProperty *);  // 0x5d16d0
    virtual void __cdecl attachDissolve(::ChangedProperty *, ::DetachReason &);  // 0x5d17b0
};

class TransitEffect
{
public:
    virtual ::Data::EffectRecordSubType __cdecl GetDataSubType(void);  // 0x479ee0
    __cdecl TransitEffect(void);  // 0x5c5530
    virtual bool __cdecl Initialize5(::EffectSource, ::Zone *, unsigned __int64, unsigned __int64, char, unsigned __int64, long, ::vector16, short, bool, short, int, short, unsigned __int64, unsigned __int64, unsigned __int64, unsigned __int64);  // 0x5c55b0
private:
    virtual void __cdecl apply(void);  // 0x5c5710
};

class TumblingEffect
{
private:
    virtual bool __cdecl checkApply(void);  // 0x5c7ac0
    virtual void __cdecl attachApply(::ChangedProperty *);  // 0x5c7c30
};

class UnlinkEffect
{
private:
    virtual void __cdecl apply(void);  // 0x5be8b0
};

class UseHeartCountEffect
{
private:
    virtual void __cdecl attachApply(::ChangedProperty *);  // 0x5cbec0
    virtual void __cdecl attachDissolve(::ChangedProperty *, ::DetachReason &);  // 0x5cbfd0
};

