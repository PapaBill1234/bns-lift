// effectcontent_cpp_1.cpp: effectcontent.cpp part 1 (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "effectcontent.h"
#include "creature.h"
#include "zone.h"
#include "Log.h"
#include "AlertSender.h"
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:?checkApply@HpDamageEffect@@EEAA_NXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?checkApply@InitializeRecycleGroupEffect@@EEAA_NXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?checkApply@AdditionalHpEffect@@EEAA_NXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?checkApply@DesireIncreaseEffect@@EEAA_NXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?checkApply@DifficultyTypeDispelAttributeHpDamageEffect@@EEAA_NXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?checkApply@ReturnSimSkillEffect@@EEAA_NXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?checkApply@ModifyRecycleTimeEffect@@EEAA_NXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?checkApply@SetImmuneBreakerEffect@@EEAA_NXZ")  // LIFT: dead-strip keep (no live caller yet)

// Path literal of EffectContent.cpp in the GameDaemon build (lessons A6).
#define EFFECTCONTENT_FILE L"e:\\dailybuild02\\gamedaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\gamedaemon\\EffectContent.cpp"

namespace
{
// LIFT: views of PDB classes. The effect classes of the skeleton have no Effect base yet. Offsets are from the PDB.

// LIFT: view of GameObject (Id at +0x28). The high 16 bits of Id hold the object type.
struct GameObjectView
{
    char lift_pad_0[0x28];
    unsigned __int64 Id;  // +40 (0x28)
};

// LIFT: view of Effect (target at +0x20, casterId at +0x28).
struct EffectView
{
    char lift_pad_0[0x20];
    GameObjectView *target;     // +32 (0x20)
    unsigned __int64 casterId;  // +40 (0x28)
};

inline EffectView const *liftEffect(void const *effect)  // LIFT: no PDB name (view cast)
{
    return static_cast<EffectView const *>(effect);
}

inline __int64 liftIdType(unsigned __int64 id)  // LIFT: no PDB name (inline HIWORD(Id))
{
    return static_cast<unsigned short>(id >> 48);
}
}  // namespace

// 0x5b4b30
bool __cdecl CommonPassiveEffect::checkApply(void)
{
    LIFT_STUB(0x5b4b30);
}

// 0x5b4c00
void __cdecl CommonPassiveEffect::attachApply(::ChangedProperty *)
{
    LIFT_STUB(0x5b4c00);
}

// 0x5b4c50
void __cdecl CommonPassiveEffect::attachDissolve(::ChangedProperty *, ::DetachReason &)
{
    LIFT_STUB(0x5b4c50);
}

// 0x5b4c60
void __cdecl CommonPassiveEffect::intervalApply(void)
{
    LIFT_STUB(0x5b4c60);
}

// 0x5b4c70
bool __cdecl CommonPassiveEffect::attachApplyData(::ChangedProperty *)
{
    LIFT_STUB(0x5b4c70);
}

// 0x5b5030
bool __cdecl CommonPassiveEffect::attachDissolveData(::ChangedProperty *, ::DetachReason)
{
    LIFT_STUB(0x5b5030);
}

// 0x5b5800
bool __cdecl CommonPassiveEffect::intervalApplyData(void)
{
    LIFT_STUB(0x5b5800);
}

// 0x5b6d80
void __cdecl CommonPassiveEffect::makeAbilityData(unsigned short *const, __int64 *const, short *const, short &, short &)
{
    LIFT_STUB(0x5b6d80);
}

// 0x5b73a0
void __cdecl CommonPassiveEffect::addAbility(unsigned short *const, __int64 *const, short *const, short &, unsigned short, short, short)
{
    LIFT_STUB(0x5b73a0);
}

// 0x5b7440
__cdecl AttackPassiveEffect::AttackPassiveEffect(void)
{
    LIFT_STUB(0x5b7440);
}

// 0x5b7540
bool __cdecl AttackPassiveEffect::Initialize3(::EffectSource, ::Zone *, unsigned __int64, unsigned __int64, char, unsigned __int64, ::Data::EffectRecord const *, bool, ::SkillResult, ::ApplySkillModifyInfo *, short, ::vector16, short, short)
{
    LIFT_STUB(0x5b7540);
}

// 0x5b76f0
bool __cdecl AttackPassiveEffect::checkApply(void)
{
    LIFT_STUB(0x5b76f0);
}

// 0x5b7770
void __cdecl AttackPassiveEffect::attachApply(::ChangedProperty *)
{
    LIFT_STUB(0x5b7770);
}

// 0x5b7870
void __cdecl AttackPassiveEffect::attachDissolve(::ChangedProperty *, ::DetachReason &)
{
    LIFT_STUB(0x5b7870);
}

// 0x5b78f0
short __cdecl AttackPassiveEffect::getFlag(void)
{
    LIFT_STUB(0x5b78f0);
}

// 0x5b7960
bool __cdecl AttackPassiveEffect::calcPower(int &, __int64 &)
{
    LIFT_STUB(0x5b7960);
}

// 0x5b7a10
__int64 __cdecl AttackPassiveEffect::calcDamage(int, __int64)
{
    LIFT_STUB(0x5b7a10);
}

// 0x5b7ae0
void __cdecl AttackPassiveEffect::applyDamage(__int64 &, ::ChangedProperty *)
{
    LIFT_STUB(0x5b7ae0);
}

// 0x5b7c50
void __cdecl AttackPassiveEffect::intervalApply(void)
{
    LIFT_STUB(0x5b7c50);
}

// 0x5b7e70
bool __cdecl HpHealEffect::Initialize3(::EffectSource, ::Zone *, unsigned __int64, unsigned __int64, char, unsigned __int64, ::Data::EffectRecord const *, bool, ::SkillResult, ::ApplySkillModifyInfo *, short, ::vector16, short, short)
{
    LIFT_STUB(0x5b7e70);
}

// 0x5b7f30
void __cdecl HpHealEffect::apply(void)
{
    LIFT_STUB(0x5b7f30);
}

// 0x5b8090
void __cdecl HpHealAttackPowerEffect::apply(void)
{
    LIFT_STUB(0x5b8090);
}

// 0x5b8250
bool __cdecl HpDamageEffect::checkApply(void)
{
    __int64 type = liftIdType(liftEffect(this)->target->Id);
    return type == 1 || type == 2 || type == 4 || type == 240 || type == 241 || type == 32;
}

// 0x5b8290
void __cdecl HpDamageEffect::apply(void)
{
    LIFT_STUB(0x5b8290);
}

// 0x5b8590
bool __cdecl GuardGaugeHealEffect::checkApply(void)
{
    LIFT_STUB(0x5b8590);
}

// 0x5b85c0
void __cdecl GuardGaugeHealEffect::apply(void)
{
    LIFT_STUB(0x5b85c0);
}

// 0x5b86f0
bool __cdecl GuardGaugeDamageEffect::checkApply(void)
{
    LIFT_STUB(0x5b86f0);
}

// 0x5b8720
void __cdecl GuardGaugeDamageEffect::apply(void)
{
    LIFT_STUB(0x5b8720);
}

// 0x5b8850
void __cdecl SpHealEffect::apply(void)
{
    LIFT_STUB(0x5b8850);
}

// 0x5b8980
void __cdecl SpDamageEffect::apply(void)
{
    LIFT_STUB(0x5b8980);
}

// 0x5b8ab0
void __cdecl CastCancelEffect::apply(void)
{
    LIFT_STUB(0x5b8ab0);
}

// 0x5b8b10
__cdecl AttackEffect::AttackEffect(void)
{
    LIFT_STUB(0x5b8b10);
}

// 0x5b8bd0
bool __cdecl AttackEffect::Initialize3(::EffectSource, ::Zone *, unsigned __int64, unsigned __int64, char, unsigned __int64, ::Data::EffectRecord const *, bool, ::SkillResult, ::ApplySkillModifyInfo *, short, ::vector16, short, short)
{
    LIFT_STUB(0x5b8bd0);
}

// 0x5b8d90
void __cdecl AttackEffect::calcPower(int &, __int64 &)
{
    LIFT_STUB(0x5b8d90);
}

// 0x5b9e30
__int64 __cdecl AttackEffect::calcDamage(int, __int64)
{
    LIFT_STUB(0x5b9e30);
}

// 0x5bbe80
bool __cdecl AttackEffect::applyDamage(__int64, ::ChangedProperty *)
{
    LIFT_STUB(0x5bbe80);
}

// 0x5bc530
void __cdecl AttackEffect::apply(void)
{
    LIFT_STUB(0x5bc530);
}

// 0x5bc7a0
void __cdecl PartAttackEffect::apply(void)
{
    LIFT_STUB(0x5bc7a0);
}

// 0x5bc9b0
bool __cdecl PartAttackEffect::Initialize4(::EffectSource, ::Zone *, unsigned __int64, unsigned __int64, char, unsigned __int64, ::Data::EffectRecord const *, ::vector16, char, ::TargetPart, unsigned __int64, unsigned __int64)
{
    LIFT_STUB(0x5bc9b0);
}

// 0x5bca00
bool __cdecl InitializeRecycleGroupEffect::checkApply(void)
{
    __int64 type = liftIdType(liftEffect(this)->target->Id);
    return type == 1 || type == 2 || type == 3 || type == 240 || type == 241;
}

// 0x5bca40
void __cdecl StanceEffect::apply(void)
{
    LIFT_STUB(0x5bca40);
}

// 0x5bcb80
bool __cdecl LinkEffect::checkApply(void)
{
    LIFT_STUB(0x5bcb80);
}

// 0x5bccc0
void __cdecl LinkEffect::attachApply(::ChangedProperty *)
{
    LIFT_STUB(0x5bccc0);
}

// 0x5bd8d0
void __cdecl LinkEffect::attachDissolve(::ChangedProperty *, ::DetachReason &)
{
    LIFT_STUB(0x5bd8d0);
}

// 0x5be550
bool __cdecl LinkEffect::invokeEffect(::DetachReason)
{
    LIFT_STUB(0x5be550);
}

// 0x5be650
__int64 __cdecl LinkEffect::calcContribution(__int64, char)
{
    LIFT_STUB(0x5be650);
}

// 0x5be720
int __cdecl LinkEffect::linkContributionPercent(char)
{
    LIFT_STUB(0x5be720);
}

// 0x5be8b0
void __cdecl UnlinkEffect::apply(void)
{
    LIFT_STUB(0x5be8b0);
}

// 0x5be900
bool __cdecl ExtendLinkEffect::checkApply(void)
{
    LIFT_STUB(0x5be900);
}

// 0x5be940
void __cdecl ExtendLinkEffect::apply(void)
{
    LIFT_STUB(0x5be940);
}

// 0x5bf3e0
bool __cdecl AdditionalHpEffect::checkApply(void)
{
    __int64 type = liftIdType(liftEffect(this)->target->Id);
    return type == 1 || type == 2 || type == 4 || type == 240 || type == 241;
}

// 0x5bf420
void __cdecl ExtendEffect::apply(void)
{
    LIFT_STUB(0x5bf420);
}

// 0x5bf4d0
bool __cdecl DesireIncreaseEffect::checkApply(void)
{
    __int64 type = liftIdType(liftEffect(this)->target->Id);
    if (type == 1 || type == 2 || type == 4 || type == 240 || type == 241)
        return type == 4;
    return false;
}

// 0x5bf510
void __cdecl DesireIncreaseEffect::apply(void)
{
    LIFT_STUB(0x5bf510);
}

// 0x5bf670
void __cdecl SetMinHateEffect::apply(void)
{
    LIFT_STUB(0x5bf670);
}

// 0x5bf850
bool __cdecl DifficultyTypeDispelAttributeHpDamageEffect::checkApply(void)
{
    EffectView const *self = liftEffect(this);
    __int64 type = liftIdType(self->target->Id);
    return (type == 1 || type == 2 || type == 4 || type == 240 || type == 241) && liftIdType(self->casterId) == 4;
}

// 0x5bf890
void __cdecl SetMaxHateEffect::apply(void)
{
    LIFT_STUB(0x5bf890);
}

// 0x5bfa70
__cdecl KnockBackEffect::KnockBackEffect(void)
{
    LIFT_STUB(0x5bfa70);
}

// 0x5bfb80
bool __cdecl KnockBackEffect::Initialize3(::EffectSource, ::Zone *, unsigned __int64, unsigned __int64, char, unsigned __int64, ::Data::EffectRecord const *, bool, ::SkillResult, ::ApplySkillModifyInfo *, short, ::vector16, short, short)
{
    LIFT_STUB(0x5bfb80);
}

// 0x5bfd70
bool __cdecl KnockBackEffect::checkApply(void)
{
    LIFT_STUB(0x5bfd70);
}

// 0x5c00f0
bool __cdecl KnockBackEffect::calcPower(int &, __int64 &)
{
    LIFT_STUB(0x5c00f0);
}

// 0x5c0190
__int64 __cdecl KnockBackEffect::calcDamage(int, __int64)
{
    LIFT_STUB(0x5c0190);
}

// 0x5c0260
void __cdecl KnockBackEffect::applyDamage(__int64 &, ::ChangedProperty *)
{
    LIFT_STUB(0x5c0260);
}

// 0x5c03d0
void __cdecl KnockBackEffect::attachApply(::ChangedProperty *)
{
    LIFT_STUB(0x5c03d0);
}

// 0x5c0710
void __cdecl KnockBackEffect::attachDissolve(::ChangedProperty *, ::DetachReason &)
{
    LIFT_STUB(0x5c0710);
}

// 0x5c07c0
short __cdecl KnockBackEffect::getKnockbackAngle(::vector16 &, ::vector16 &, ::Data::EffectKnockbackDirectionType, short)
{
    LIFT_STUB(0x5c07c0);
}

// 0x5c0910
short __cdecl KnockBackEffect::getKnockbackedYaw(::vector16 &, short, ::Data::EffectKnockbackDirectionType)
{
    LIFT_STUB(0x5c0910);
}

// 0x5c0a50
bool __cdecl KnockBackEffect::getKnockBackPos(::vector16 *, long *, ::GeoCell *, __int64 *)
{
    LIFT_STUB(0x5c0a50);
}

// 0x5c1280
bool __cdecl KnockBackEffect::knockBackTarget(::vector16 &, ::GeoCell *, ::ChangedProperty *)
{
    LIFT_STUB(0x5c1280);
}

// 0x5c1520
bool __cdecl KnockBackEffect::dashCaster(::vector16, short, bool)
{
    LIFT_STUB(0x5c1520);
}

// 0x5c19f0
bool __cdecl ResurrectionEffect::checkApply(void)
{
    LIFT_STUB(0x5c19f0);
}

// 0x5c1b70
void __cdecl ResurrectionEffect::apply(void)
{
    LIFT_STUB(0x5c1b70);
}

// 0x5c2b50
void __cdecl HpDrainEffect::apply(void)
{
    LIFT_STUB(0x5c2b50);
}

// 0x5c2e80
void __cdecl HpTransferEffect::apply(void)
{
    LIFT_STUB(0x5c2e80);
}

// 0x5c30f0
void __cdecl DispelTypeEffect::apply(void)
{
    LIFT_STUB(0x5c30f0);
}

// 0x5c3760
void __cdecl DispelAttributeEffect::apply(void)
{
    LIFT_STUB(0x5c3760);
}

// 0x5c37f0
void __cdecl DispelBuffEffect::apply(void)
{
    LIFT_STUB(0x5c37f0);
}

// 0x5c3870
void __cdecl DispelDebuffEffect::apply(void)
{
    LIFT_STUB(0x5c3870);
}

// 0x5c38f0
void __cdecl FrostbiteDrainEffect::apply(void)
{
    LIFT_STUB(0x5c38f0);
}

// 0x5c4460
bool __cdecl RecoveryContentQuotaEffect::checkApply(void)
{
    LIFT_STUB(0x5c4460);
}

// 0x5c4510
void __cdecl RecoveryContentQuotaEffect::apply(void)
{
    LIFT_STUB(0x5c4510);
}

// 0x5c49c0
void __cdecl ImmuneAttributeEffect::attachApply(::ChangedProperty *)
{
    LIFT_STUB(0x5c49c0);
}

// 0x5c4ab0
void __cdecl ImmuneAttributeEffect::attachDissolve(::ChangedProperty *, ::DetachReason &)
{
    LIFT_STUB(0x5c4ab0);
}

// 0x5c4bb0
bool __cdecl ProvocationEffect::checkApply(void)
{
    LIFT_STUB(0x5c4bb0);
}

// 0x5c4c10
void __cdecl ProvocationEffect::attachApply(::ChangedProperty *)
{
    LIFT_STUB(0x5c4c10);
}

// 0x5c4d80
void __cdecl ProvocationEffect::attachDissolve(::ChangedProperty *, ::DetachReason &)
{
    LIFT_STUB(0x5c4d80);
}

// 0x5c4e80
bool __cdecl InstantaneousDeathEffect::checkApply(void)
{
    LIFT_STUB(0x5c4e80);
}

// 0x5c4f90
void __cdecl InstantaneousDeathEffect::apply(void)
{
    LIFT_STUB(0x5c4f90);
}

// 0x5c5110
void __cdecl RechargeHeartCountEffect::apply(void)
{
    LIFT_STUB(0x5c5110);
}

// 0x5c5530
__cdecl TransitEffect::TransitEffect(void)
{
    LIFT_STUB(0x5c5530);
}

// 0x5c55b0
bool __cdecl TransitEffect::Initialize5(::EffectSource, ::Zone *, unsigned __int64, unsigned __int64, char, unsigned __int64, long, ::vector16, short, bool, short, int, short, unsigned __int64, unsigned __int64, unsigned __int64, unsigned __int64)
{
    LIFT_STUB(0x5c55b0);
}

// 0x5c5710
void __cdecl TransitEffect::apply(void)
{
    LIFT_STUB(0x5c5710);
}

// 0x5c5860
bool __cdecl ReturnEffect::checkApply(void)
{
    LIFT_STUB(0x5c5860);
}

// 0x5c5940
void __cdecl ReturnEffect::apply(void)
{
    LIFT_STUB(0x5c5940);
}

// 0x5c5990
void __cdecl ReturnToBaseCampEffect::apply(void)
{
    LIFT_STUB(0x5c5990);
}

// 0x5c5de0
bool __cdecl ReturnSimSkillEffect::checkApply(void)
{
    __int64 type = liftIdType(liftEffect(this)->target->Id);
    return type == 1 || type == 240;
}

// 0x5c5e00
void __cdecl ReturnSimSkillEffect::apply(void)
{
    LIFT_STUB(0x5c5e00);
}

// 0x5c5e70
void __cdecl InitializeRecycleGroupEffect::apply(void)
{
    LIFT_STUB(0x5c5e70);
}

// 0x5c6200
bool __cdecl ModifyRecycleTimeEffect::checkApply(void)
{
    GameObjectView const *target = liftEffect(this)->target;
    if (target == nullptr)
    {
        Log::Write(Log::LT_ERROR, EFFECTCONTENT_FILE, 5495, L"== CRASH == [effect], ModifyRecycleTimeEffect::checkApply; target is null");
        AlertSender::Write(EFFECTCONTENT_FILE, 5495, L"== CRASH == [effect], ModifyRecycleTimeEffect::checkApply; target is null");
        return false;
    }
    __int64 type = liftIdType(target->Id);
    return type == 1 || type == 2 || type == 3 || type == 240 || type == 241;
}

// 0x5c6280
void __cdecl ModifyRecycleTimeEffect::apply(void)
{
    LIFT_STUB(0x5c6280);
}

// 0x5c65d0
bool __cdecl SetImmuneBreakerEffect::checkApply(void)
{
    return liftIdType(liftEffect(this)->target->Id) == 4;
}

// 0x5c65f0
void __cdecl SetImmuneBreakerEffect::apply(void)
{
    LIFT_STUB(0x5c65f0);
}

// 0x5c6790
bool __cdecl RecallToCasterEffect::checkApply(void)
{
    LIFT_STUB(0x5c6790);
}
