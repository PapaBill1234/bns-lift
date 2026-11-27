// effectcontent_cpp_2.cpp: effectcontent.cpp part 2 (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "effectcontent.h"
#include "creature.h"
#include "zone.h"
#include "Log.h"
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:?checkApply@EmbersExplosionTimerEffect@@MEAA_NXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?checkApply@DashEffect@@EEAA_NXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?checkApply@DebuffGuildBattleFieldEffect@@MEAA_NXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?checkApply@OceanicEffect@@EEAA_NXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?checkApply@FallDeathEffect@@EEAA_NXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?FindBlankModifyAbility@MasteryStatEquipEffect@@SAHPEBVEffectRecordMasteryStatEquip@Data@@@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?checkApply@SecondGaugePointEffect@@EEAA_NXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?checkApply@IntervalSecondGaugePointEffect@@EEAA_NXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?checkApply@AccumulatedDamageEffect@@EEAA_NXZ")  // LIFT: dead-strip keep (no live caller yet)

#define EFFECTCONTENT_FILE L"e:\\dailybuild02\\gamedaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\gamedaemon\\EffectContent.cpp"

namespace
{
// LIFT: view of GameObject (PDB: Id at +0x28).
struct GameObjectView
{
    char lift_pad_0[0x28];
    unsigned __int64 Id;  // +40 (0x28)
};

// LIFT: view of Effect (PDB: target at +0x20, casterId at +0x28). The skeleton effect classes have no base yet.
struct EffectView
{
    char lift_pad_0[0x20];
    GameObjectView * target;     // +32 (0x20)
    unsigned __int64 casterId;   // +40 (0x28)
};

// LIFT: view of Creature (PDB: Prop at +0x30; CreatureProperty::State at +0xD8, Abnormality at +0x738).
struct CreatureView
{
    char lift_pad_0[0x30 + 0xD8 + 0xD8];
    unsigned __int64 effect_flag_3;  // +0x1E0 (Prop.State.effect_flag_3)
    char lift_pad_1[0x30 + 0xD8 + 0x142 - (0x30 + 0xD8 + 0xD8 + 8)];
    char dead;                       // +0x24A (Prop.State.dead)
    char lift_pad_2[0x30 + 0x738 + 1 - (0x30 + 0xD8 + 0x142 + 1)];
    bool block_move;                 // +0x769 (Prop.Abnormality.block_move)
};

// LIFT: view of Npc (PDB: _flags at +3386).
struct NpcFlagsView
{
    char lift_pad_0[3386];
    unsigned short _flags;  // +3386 (0xD3A)
};

// LIFT: view of Data::EffectRecordMasteryStatEquip (PDB: modify_ability_for_mastery[16] at +0x278).
struct EffectRecordMasteryStatEquipView
{
    char lift_pad_0[0x278];
    short modify_ability_for_mastery[16];  // +0x278
};

// LIFT: object type of a GameObject id (high 16 bits). ❓ PDB names of the inline helpers and type values.
inline unsigned short GetObjectType(unsigned __int64 id)
{
    return static_cast<unsigned short>(id >> 48);
}

inline bool IsCreatureType(unsigned __int64 id)
{
    unsigned short type = GetObjectType(id);
    return type == 1 || type == 2 || type == 4 || type == 240 || type == 241;
}

const unsigned short OBJECT_TYPE_PC = 1;   // LIFT: value 1 (pseudocode); ❓ enumerator name
const unsigned short OBJECT_TYPE_NPC = 4;  // LIFT: value 4 (pseudocode); ❓ enumerator name
const unsigned short NPC_FLAG_SECOND_GAUGE = 0x80;  // LIFT: bit 7 of Npc::_flags (pseudocode); ❓ PDB name
const unsigned __int64 EFFECT_FLAG_3_SECOND_GAUGE_STOPPED = 0x20;  // LIFT: bit of effect_flag_3 (pseudocode, log text); ❓ PDB name
const int MAX_MODIFY_ABILITY_FOR_MASTERY = 16;  // LIFT: array size of modify_ability_for_mastery (PDB)
}

// 0x5c6940
void __cdecl ReplacePositionEffect::apply(void)
{
    LIFT_STUB(0x5c6940);
}

// 0x5c6f90
void __cdecl IntervalRangePhysicalDamageEffect::attachApply(::ChangedProperty *)
{
    LIFT_STUB(0x5c6f90);
}

// 0x5c70a0
void __cdecl IntervalRangePhysicalDamageEffect::intervalApply(void)
{
    LIFT_STUB(0x5c70a0);
}

// 0x5c72c0
bool __cdecl FoodIntervalHealEffect::Initialize4(::EffectSource, ::Zone *, unsigned __int64, unsigned __int64, char, unsigned __int64, ::Data::EffectRecord const *, ::vector16, char, ::TargetPart, unsigned __int64, unsigned __int64)
{
    LIFT_STUB(0x5c72c0);
}

// 0x5c7310
void __cdecl FoodIntervalHealEffect::attachApply(::ChangedProperty *)
{
    LIFT_STUB(0x5c7310);
}

// 0x5c7420
void __cdecl AccumulatedDamageEffect::attachDissolve(::ChangedProperty *, ::DetachReason &)
{
    LIFT_STUB(0x5c7420);
}

// 0x5c7470
void __cdecl FoodIntervalHealEffect::intervalApply(void)
{
    LIFT_STUB(0x5c7470);
}

// 0x5c7680
void __cdecl IntervalForceDamageEffect::attachApply(::ChangedProperty *)
{
    LIFT_STUB(0x5c7680);
}

// 0x5c77e0
void __cdecl IntervalForceDamageEffect::attachDissolve(::ChangedProperty *, ::DetachReason &)
{
    LIFT_STUB(0x5c77e0);
}

// 0x5c7880
void __cdecl IntervalForceDamageEffect::intervalApply(void)
{
    LIFT_STUB(0x5c7880);
}

// 0x5c7ac0
bool __cdecl TumblingEffect::checkApply(void)
{
    LIFT_STUB(0x5c7ac0);
}

// 0x5c7c30
void __cdecl TumblingEffect::attachApply(::ChangedProperty *)
{
    LIFT_STUB(0x5c7c30);
}

// 0x5c8190
void __cdecl AdditionalHpEffect::attachApply(::ChangedProperty *)
{
    LIFT_STUB(0x5c8190);
}

// 0x5c8340
void __cdecl AdditionalHpEffect::attachDissolve(::ChangedProperty *, ::DetachReason &)
{
    LIFT_STUB(0x5c8340);
}

// 0x5c8430
bool __cdecl BindingSkillStepEffect::Initialize2(::EffectSource, ::Zone *, unsigned __int64, unsigned __int64, char, unsigned __int64, ::Data::EffectRecord const *, long)
{
    LIFT_STUB(0x5c8430);
}

// 0x5c8510
void __cdecl BindingSkillStepEffect::attachApply(::ChangedProperty *)
{
    LIFT_STUB(0x5c8510);
}

// 0x5c8620
bool __cdecl EmbersExplosionTimerEffect::checkApply(void)
{
    EffectView const * self = reinterpret_cast<EffectView const *>(this);
    if (IsCreatureType(self->target->Id) && IsCreatureType(self->casterId))
        return true;
    return false;
}

// 0x5c8690
void __cdecl EmbersExplosionTimerEffect::attachApply(::ChangedProperty *)
{
    LIFT_STUB(0x5c8690);
}

// 0x5c8830
void __cdecl EmbersExplosionTimerEffect::attachDissolve(::ChangedProperty *, ::DetachReason &)
{
    LIFT_STUB(0x5c8830);
}

// 0x5c94b0
void __cdecl SafetyAreaEffect::attachApply(::ChangedProperty *)
{
    LIFT_STUB(0x5c94b0);
}

// 0x5c95f0
void __cdecl SafetyAreaEffect::attachDissolve(::ChangedProperty *, ::DetachReason &)
{
    LIFT_STUB(0x5c95f0);
}

// 0x5c96d0
void __cdecl RechargeGuildBattleFieldEffect::apply(void)
{
    LIFT_STUB(0x5c96d0);
}

// 0x5c9850
bool __cdecl EnableGuildBattleFieldEffect::Initialize2(::EffectSource, ::Zone *, unsigned __int64, unsigned __int64, char, unsigned __int64, ::Data::EffectRecord const *, long)
{
    LIFT_STUB(0x5c9850);
}

// 0x5c9980
void __cdecl EnableGuildBattleFieldEffect::attachApply(::ChangedProperty *)
{
    LIFT_STUB(0x5c9980);
}

// 0x5c9aa0
void __cdecl EnableGuildBattleFieldEffect::attachDissolve(::ChangedProperty *, ::DetachReason &)
{
    LIFT_STUB(0x5c9aa0);
}

// 0x5c9c20
void __cdecl DebuffGuildBattleFieldEffect::attachApply(::ChangedProperty *)
{
    LIFT_STUB(0x5c9c20);
}

// 0x5c9cc0
void __cdecl DebuffGuildBattleFieldEffect::intervalApply(void)
{
    LIFT_STUB(0x5c9cc0);
}

// 0x5c9ea0
void __cdecl HelpRestorationEffect::attachApply(::ChangedProperty *)
{
    LIFT_STUB(0x5c9ea0);
}

// 0x5ca0f0
void __cdecl HelpRestorationEffect::attachDissolve(::ChangedProperty *, ::DetachReason &)
{
    LIFT_STUB(0x5ca0f0);
}

// 0x5ca1f0
void __cdecl RecallToCasterEffect::attachApply(::ChangedProperty *)
{
    LIFT_STUB(0x5ca1f0);
}

// 0x5ca830
bool __cdecl RecallToPositionEffect::Initialize4(::EffectSource, ::Zone *, unsigned __int64, unsigned __int64, char, unsigned __int64, ::Data::EffectRecord const *, ::vector16, char, ::TargetPart, unsigned __int64, unsigned __int64)
{
    LIFT_STUB(0x5ca830);
}

// 0x5ca890
void __cdecl RecallToPositionEffect::attachApply(::ChangedProperty *)
{
    LIFT_STUB(0x5ca890);
}

// 0x5cad70
void __cdecl AirKnockbackEffect::attachDissolve(::ChangedProperty *, ::DetachReason &)
{
    LIFT_STUB(0x5cad70);
}

// 0x5cadf0
bool __cdecl DashEffect::Initialize5(::EffectSource, ::Zone *, unsigned __int64, unsigned __int64, char, unsigned __int64, long, ::vector16, short, bool, short, int, short, unsigned __int64, unsigned __int64, unsigned __int64, unsigned __int64)
{
    LIFT_STUB(0x5cadf0);
}

// 0x5caf40
bool __cdecl DashEffect::checkApply(void)
{
    EffectView const * self = reinterpret_cast<EffectView const *>(this);
    GameObjectView * target = self->target;
    if (!IsCreatureType(target->Id))
        return false;
    if (self->casterId == target->Id && reinterpret_cast<CreatureView const *>(target)->block_move)
        return false;
    return true;
}

// 0x5caf90
void __cdecl DashEffect::attachApply(::ChangedProperty *)
{
    LIFT_STUB(0x5caf90);
}

// 0x5cb2e0
void __cdecl DashEffect::attachDissolve(::ChangedProperty *, ::DetachReason &)
{
    LIFT_STUB(0x5cb2e0);
}

// 0x5cb390
bool __cdecl FallDamageEffect::Initialize5(::EffectSource, ::Zone *, unsigned __int64, unsigned __int64, char, unsigned __int64, long, ::vector16, short, bool, short, int, short, unsigned __int64, unsigned __int64, unsigned __int64, unsigned __int64)
{
    LIFT_STUB(0x5cb390);
}

// 0x5cb4b0
void __cdecl FallDamageEffect::apply(void)
{
    LIFT_STUB(0x5cb4b0);
}

// 0x5cb860
bool __cdecl AirDashEffect::Initialize5(::EffectSource, ::Zone *, unsigned __int64, unsigned __int64, char, unsigned __int64, long, ::vector16, short, bool, short, int, short, unsigned __int64, unsigned __int64, unsigned __int64, unsigned __int64)
{
    LIFT_STUB(0x5cb860);
}

// 0x5cb990
void __cdecl AirDashEffect::attachApply(::ChangedProperty *)
{
    LIFT_STUB(0x5cb990);
}

// 0x5cbb50
void __cdecl AirDashEffect::attachDissolve(::ChangedProperty *, ::DetachReason &)
{
    LIFT_STUB(0x5cbb50);
}

// 0x5cbc30
void __cdecl ExhaustionEffect::attachApply(::ChangedProperty *)
{
    LIFT_STUB(0x5cbc30);
}

// 0x5cbcd0
void __cdecl ReviveExceptRuleEffect::attachApply(::ChangedProperty *)
{
    LIFT_STUB(0x5cbcd0);
}

// 0x5cbde0
void __cdecl ReviveExceptRuleEffect::attachDissolve(::ChangedProperty *, ::DetachReason &)
{
    LIFT_STUB(0x5cbde0);
}

// 0x5cbea0
bool __cdecl DebuffGuildBattleFieldEffect::checkApply(void)
{
    return GetObjectType(reinterpret_cast<EffectView const *>(this)->target->Id) == OBJECT_TYPE_PC;
}

// 0x5cbec0
void __cdecl UseHeartCountEffect::attachApply(::ChangedProperty *)
{
    LIFT_STUB(0x5cbec0);
}

// 0x5cbfd0
void __cdecl UseHeartCountEffect::attachDissolve(::ChangedProperty *, ::DetachReason &)
{
    LIFT_STUB(0x5cbfd0);
}

// 0x5cc070
bool __cdecl AirKnockbackEffect::Initialize1(::EffectSource, ::Zone *, unsigned __int64, unsigned __int64, char, unsigned __int64, ::Data::EffectRecord const *)
{
    LIFT_STUB(0x5cc070);
}

// 0x5cc190
void __cdecl AirKnockbackEffect::attachApply(::ChangedProperty *)
{
    LIFT_STUB(0x5cc190);
}

// 0x5cc250
bool __cdecl OceanicEffect::Initialize5(::EffectSource, ::Zone *, unsigned __int64, unsigned __int64, char, unsigned __int64, long, ::vector16, short, bool, short, int, short, unsigned __int64, unsigned __int64, unsigned __int64, unsigned __int64)
{
    LIFT_STUB(0x5cc250);
}

// 0x5cc380
bool __cdecl OceanicEffect::checkApply(void)
{
    unsigned short type = GetObjectType(reinterpret_cast<EffectView const *>(this)->target->Id);
    return type == 1 || type == 2 || type == 3;  // LIFT: type values 1, 2, 3 (pseudocode); ❓ enumerator names
}

// 0x5cc3a0
void __cdecl OceanicEffect::attachApply(::ChangedProperty *)
{
    LIFT_STUB(0x5cc3a0);
}

// 0x5cc440
void __cdecl OceanicEffect::attachDissolve(::ChangedProperty *, ::DetachReason &)
{
    LIFT_STUB(0x5cc440);
}

// 0x5cc4e0
bool __cdecl FallDeathEffect::Initialize5(::EffectSource, ::Zone *, unsigned __int64, unsigned __int64, char, unsigned __int64, long, ::vector16, short, bool, short, int, short, unsigned __int64, unsigned __int64, unsigned __int64, unsigned __int64)
{
    LIFT_STUB(0x5cc4e0);
}

// 0x5cc5f0
bool __cdecl FallDeathEffect::checkApply(void)
{
    GameObjectView * target = reinterpret_cast<EffectView const *>(this)->target;
    if (!IsCreatureType(target->Id))
        return false;
    return reinterpret_cast<CreatureView const *>(target)->dead != 1;
}

// 0x5cc630
void __cdecl FallDeathEffect::apply(void)
{
    LIFT_STUB(0x5cc630);
}

// 0x5cc770
void __cdecl IncreaseSpecialSkillGaugeEffect::apply(void)
{
    LIFT_STUB(0x5cc770);
}

// 0x5cc8e0
bool __cdecl IncreaseCasterSpecialSkillGaugeEffect::checkApply(void)
{
    LIFT_STUB(0x5cc8e0);
}

// 0x5cc940
void __cdecl IncreaseCasterSpecialSkillGaugeEffect::apply(void)
{
    LIFT_STUB(0x5cc940);
}

// 0x5ccab0
void __cdecl DifficultyTypeDispelAttributeHpDamageEffect::apply(void)
{
    LIFT_STUB(0x5ccab0);
}

// 0x5ccd90
__cdecl DuelFighterChangeEffect::DuelFighterChangeEffect(void)
{
    LIFT_STUB(0x5ccd90);
}

// 0x5cce00
bool __cdecl DuelFighterChangeEffect::Initialize4(::EffectSource, ::Zone *, unsigned __int64, unsigned __int64, char, unsigned __int64, ::Data::EffectRecord const *, ::vector16, char, ::TargetPart, unsigned __int64, unsigned __int64)
{
    LIFT_STUB(0x5cce00);
}

// 0x5cce50
bool __cdecl DuelFighterChangeEffect::checkApply(void)
{
    LIFT_STUB(0x5cce50);
}

// 0x5ccf90
void __cdecl DuelFighterChangeEffect::apply(void)
{
    LIFT_STUB(0x5ccf90);
}

// 0x5cd0c0
bool __cdecl DuelFighterTimeLimitEffect::checkApply(void)
{
    LIFT_STUB(0x5cd0c0);
}

// 0x5cd210
void __cdecl DuelFighterTimeLimitEffect::attachApply(::ChangedProperty *)
{
    LIFT_STUB(0x5cd210);
}

// 0x5cd270
void __cdecl DuelFighterTimeLimitEffect::attachDissolve(::ChangedProperty *, ::DetachReason &)
{
    LIFT_STUB(0x5cd270);
}

// 0x5cd3d0
bool __cdecl DuelInterferenceEffect::checkApply(void)
{
    LIFT_STUB(0x5cd3d0);
}

// 0x5cd510
void __cdecl DuelInterferenceEffect::attachApply(::ChangedProperty *)
{
    LIFT_STUB(0x5cd510);
}

// 0x5cd660
void __cdecl DuelInterferenceEffect::attachDissolve(::ChangedProperty *, ::DetachReason &)
{
    LIFT_STUB(0x5cd660);
}

// 0x5cd7a0
bool __cdecl ItemAbilityEffect::Initialize1(::EffectSource, ::Zone *, unsigned __int64, unsigned __int64, char, unsigned __int64, ::Data::EffectRecord const *)
{
    LIFT_STUB(0x5cd7a0);
}

// 0x5cd8c0
void __cdecl ItemAbilityEffect::attachApply(::ChangedProperty *)
{
    LIFT_STUB(0x5cd8c0);
}

// 0x5ce560
void __cdecl ItemAbilityEffect::attachDissolve(::ChangedProperty *, ::DetachReason &)
{
    LIFT_STUB(0x5ce560);
}

// 0x5cf360
bool __cdecl MasteryStatEquipEffect::Initialize1(::EffectSource, ::Zone *, unsigned __int64, unsigned __int64, char, unsigned __int64, ::Data::EffectRecord const *)
{
    LIFT_STUB(0x5cf360);
}

// 0x5cf480
void __cdecl MasteryStatEquipEffect::attachApply(::ChangedProperty *)
{
    LIFT_STUB(0x5cf480);
}

// 0x5cf500
void __cdecl MasteryStatEquipEffect::attachDissolve(::ChangedProperty *, ::DetachReason &)
{
    LIFT_STUB(0x5cf500);
}

// 0x5cf570
void __cdecl MasteryStatEquipEffect::applyAbilityForMastery(bool, ::ChangedProperty *)
{
    LIFT_STUB(0x5cf570);
}

// 0x5cf6d0
bool __cdecl MasteryStatEquipEffect::AccumulateModifyAbility(::Data::EffectRecordMasteryStatEquip *, ::Data::EffectRecord const *)
{
    LIFT_STUB(0x5cf6d0);
}

// 0x5cf7c0
int __cdecl MasteryStatEquipEffect::FindBlankModifyAbility(::Data::EffectRecordMasteryStatEquip const * eData)
{
    if (eData == nullptr)
        return -1;
    EffectRecordMasteryStatEquipView const * record = reinterpret_cast<EffectRecordMasteryStatEquipView const *>(eData);
    for (int i = 0; i < MAX_MODIFY_ABILITY_FOR_MASTERY; ++i)
    {
        if (record->modify_ability_for_mastery[i] == 0)
            return i;
    }
    return -1;
}

// 0x5cf7f0
bool __cdecl ShooterLockOnEffect::Initialize4(::EffectSource, ::Zone *, unsigned __int64, unsigned __int64, char, unsigned __int64, ::Data::EffectRecord const *, ::vector16, char, ::TargetPart, unsigned __int64, unsigned __int64)
{
    LIFT_STUB(0x5cf7f0);
}

// 0x5d0010
void __cdecl ShooterLockOnEffect::attachApply(::ChangedProperty *)
{
    LIFT_STUB(0x5d0010);
}

// 0x5d0070
void __cdecl ShooterLockOnEffect::intervalApply(void)
{
    LIFT_STUB(0x5d0070);
}

// 0x5d0790
bool __cdecl AttackGlideEffect::checkApply(void)
{
    LIFT_STUB(0x5d0790);
}

// 0x5d0880
void __cdecl AttackGlideEffect::attachApply(::ChangedProperty *)
{
    LIFT_STUB(0x5d0880);
}

// 0x5d0960
void __cdecl AttackGlideEffect::attachDissolve(::ChangedProperty *, ::DetachReason &)
{
    LIFT_STUB(0x5d0960);
}

// 0x5d0a30
void __cdecl AttackGlideEffect::intervalApply(void)
{
    LIFT_STUB(0x5d0a30);
}

// 0x5d10a0
bool __cdecl SecondGaugePointEffect::checkApply(void)
{
    GameObjectView * target = reinterpret_cast<EffectView const *>(this)->target;
    if (GetObjectType(target->Id) != OBJECT_TYPE_NPC
        || (reinterpret_cast<NpcFlagsView const *>(target)->_flags & NPC_FLAG_SECOND_GAUGE) == 0)
        return false;
    if ((reinterpret_cast<CreatureView const *>(target)->effect_flag_3 & EFFECT_FLAG_3_SECOND_GAUGE_STOPPED) != 0)
    {
        Log::Write(Log::LT_DEBUG, EFFECTCONTENT_FILE, 8388,
                   L"[effect], SecondGaugePointEffect::checkApply; SecondGaugeStopped flag is true. no apply.");
        return false;
    }
    return true;
}

// 0x5d1100
void __cdecl SecondGaugePointEffect::apply(void)
{
    LIFT_STUB(0x5d1100);
}

// 0x5d13a0
bool __cdecl IntervalSecondGaugePointEffect::checkApply(void)
{
    GameObjectView * target = reinterpret_cast<EffectView const *>(this)->target;
    return GetObjectType(target->Id) == OBJECT_TYPE_NPC
        && (reinterpret_cast<NpcFlagsView const *>(target)->_flags & NPC_FLAG_SECOND_GAUGE) != 0;
}

// 0x5d13d0
void __cdecl AccumulatedDamageEffect::attachApply(::ChangedProperty *)
{
    LIFT_STUB(0x5d13d0);
}

// 0x5d1430
void __cdecl IntervalSecondGaugePointEffect::intervalApply(void)
{
    LIFT_STUB(0x5d1430);
}

// 0x5d16d0
void __cdecl StopSecondGaugePointEffect::attachApply(::ChangedProperty *)
{
    LIFT_STUB(0x5d16d0);
}

// 0x5d17b0
void __cdecl StopSecondGaugePointEffect::attachDissolve(::ChangedProperty *, ::DetachReason &)
{
    LIFT_STUB(0x5d17b0);
}

// 0x5d18a0
void __cdecl SetSecondGaugePointEffect::apply(void)
{
    LIFT_STUB(0x5d18a0);
}

// 0x5d1c30
bool __cdecl AccumulatedDamageEffect::Initialize1(::EffectSource, ::Zone *, unsigned __int64, unsigned __int64, char, unsigned __int64, ::Data::EffectRecord const *)
{
    LIFT_STUB(0x5d1c30);
}

// 0x5d1d00
bool __cdecl AccumulatedDamageEffect::checkApply(void)
{
    EffectView const * self = reinterpret_cast<EffectView const *>(this);
    unsigned short casterType = GetObjectType(self->casterId);
    if ((casterType == 1 || casterType == 240) && IsCreatureType(self->target->Id))  // LIFT: type values 1, 240 (pseudocode); ❓ enumerator names
        return true;
    return false;
}

// 0x5d1d50
void __cdecl AccumulatedDamageEffect::preDissolveProc(bool, ::ChangedProperty *)
{
    LIFT_STUB(0x5d1d50);
}

// 0x5d1e00
bool __cdecl AccumulatedDamageEffect::Explode(::ChangedProperty *, unsigned __int64, char, unsigned __int64, int, ::Data::EffectAccumulatedDamageUseTypeType, short)
{
    LIFT_STUB(0x5d1e00);
}

// 0x5d21d0
bool __cdecl SoulMaskEffect::Initialize1(::EffectSource, ::Zone *, unsigned __int64, unsigned __int64, char, unsigned __int64, ::Data::EffectRecord const *)
{
    LIFT_STUB(0x5d21d0);
}

// 0x5d23d0
bool __cdecl SoulMaskEffect::checkApply(void)
{
    LIFT_STUB(0x5d23d0);
}

// 0x5d2540
void __cdecl SoulMaskEffect::attachApply(::ChangedProperty *)
{
    LIFT_STUB(0x5d2540);
}

// 0x5d2720
void __cdecl SoulMaskEffect::attachDissolve(::ChangedProperty *, ::DetachReason &)
{
    LIFT_STUB(0x5d2720);
}
