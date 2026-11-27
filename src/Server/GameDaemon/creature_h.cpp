// creature_h.cpp: creature.h (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "creature.h"
#include "LiftStub.h"

// 0x1d240
#pragma comment(linker, "/INCLUDE:?AddChangedPropertyId@Creature@@UEAAXG@Z")  // LIFT: dead-strip keep (no live caller yet)
void __cdecl Creature::AddChangedPropertyId(unsigned short fieldId)
{
    reinterpret_cast< ::CreatureMemberView *>(this)->_changedPropertyIdListSet.insert(fieldId);
}

// 0x1d280
#pragma comment(linker, "/INCLUDE:?AddChangedExtraPropertyId@Creature@@UEAAXG@Z")  // LIFT: dead-strip keep (no live caller yet)
void __cdecl Creature::AddChangedExtraPropertyId(unsigned short fieldId)
{
    reinterpret_cast< ::CreatureMemberView *>(this)->_changedExtraPropertyIdListSet.insert(fieldId);
}

// 0x1edbb0
// LIFT: the object type is the high 16 bits of the id (types 1, 2, 3, 240 and 241 can be in a duel combat).
// ❓ the 2019 body compares combat_side as unsigned (<= 2); the source form of that compare is open.
#pragma comment(linker, "/INCLUDE:?IsCreatureInDuelCombat@Creature@@QEBA_NXZ")  // LIFT: dead-strip keep (no live caller yet)
bool __cdecl Creature::IsCreatureInDuelCombat(void) const
{
    ::CreatureMemberView const *const view = reinterpret_cast< ::CreatureMemberView const *>(this);
    unsigned __int64 const objectType = view->Id >> 48;
    return (objectType == 1 || objectType == 2 || objectType == 3 || objectType == 240 || objectType == 241)
        && static_cast<unsigned char>(view->combat_side) <= 2;
}

// 0x1edbf0
__cdecl CreatureStateKeeper::~CreatureStateKeeper(void)
{
    LIFT_STUB(0x1edbf0);
}

// 0x1edc40
void __cdecl CreatureStateKeeper::SnapshotCreatureState(void)
{
    LIFT_STUB(0x1edc40);
}

// LIFT: the 2019 body evaluates the clamp bounds again in each branch (a min/max macro form).
// The exact source form is still open; this form keeps the logic: value clamped to [min, max] of the limit record.
#define SKILL_MODIFY_RATIO(param, ratio) (static_cast<__int64>(param) * (ratio) / _divideValue)

// 0x453650
#pragma comment(linker, "/INCLUDE:?CalcRecycleDuration@ApplySkillModifyInfo@@QEBA?BJJ@Z")  // LIFT: dead-strip keep (no live caller yet)
long const __cdecl ApplySkillModifyInfo::CalcRecycleDuration(long const param) const
{
    __int64 value = param + SKILL_MODIFY_RATIO(param, _recycleDurationModifyPercent) + _recycleDurationModifyDiff;
    if (_skillModifyLimitData._record != NULL)
    {
        __int64 const minValue = SKILL_MODIFY_RATIO(param, _skillModifyLimitData._record->recycle_duration_min_ratio_percent);
        value = (minValue > value) ? minValue : value;
        __int64 const maxValue = SKILL_MODIFY_RATIO(param, _skillModifyLimitData._record->recycle_duration_max_ratio_percent);
        value = (value < maxValue) ? value : maxValue;
    }
    return static_cast<long>(value);
}

// 0x4536f0
#pragma comment(linker, "/INCLUDE:?CalcSpConsume@ApplySkillModifyInfo@@QEBA?BFF@Z")  // LIFT: dead-strip keep (no live caller yet)
short const __cdecl ApplySkillModifyInfo::CalcSpConsume(short const param) const
{
    __int64 value = static_cast<__int64>(param) + _spConsumeModifyDiff;
    if (_skillModifyLimitData._record != NULL)
    {
        __int64 const minValue = _skillModifyLimitData._record->sp_consume_min_value;
        value = (minValue > value) ? minValue : value;
        __int64 const maxValue = _skillModifyLimitData._record->sp_consume_max_value;
        value = (value < maxValue) ? value : maxValue;
    }
    return static_cast<short>(value);
}

// 0x453740
#pragma comment(linker, "/INCLUDE:?CalcDamagePowerPercent@ApplySkillModifyInfo@@QEBA?BHH@Z")  // LIFT: dead-strip keep (no live caller yet)
int const __cdecl ApplySkillModifyInfo::CalcDamagePowerPercent(int const param) const
{
    __int64 value = param + SKILL_MODIFY_RATIO(param, _damagePowerPercentModifyPercent) + _damagePowerPercentModifyDiff;
    if (_skillModifyLimitData._record != NULL)
    {
        __int64 const minValue = SKILL_MODIFY_RATIO(param, _skillModifyLimitData._record->damage_power_percent_min_ratio_percent);
        value = (minValue > value) ? minValue : value;
        __int64 const maxValue = SKILL_MODIFY_RATIO(param, _skillModifyLimitData._record->damage_power_percent_max_ratio_percent);
        value = (value < maxValue) ? value : maxValue;
    }
    return static_cast<int>(value);
}

// 0x4537e0
#pragma comment(linker, "/INCLUDE:?CalcHealPercent@ApplySkillModifyInfo@@QEBA?BFF@Z")  // LIFT: dead-strip keep (no live caller yet)
short const __cdecl ApplySkillModifyInfo::CalcHealPercent(short const param) const
{
    __int64 value = param + SKILL_MODIFY_RATIO(param, _healPercentModifyPercent) + _healPercentModifyDiff;
    if (_skillModifyLimitData._record != NULL)
    {
        __int64 const minValue = SKILL_MODIFY_RATIO(param, _skillModifyLimitData._record->heal_percent_min_ratio_percent);
        value = (minValue > value) ? minValue : value;
        __int64 const maxValue = SKILL_MODIFY_RATIO(param, _skillModifyLimitData._record->heal_percent_max_ratio_percent);
        value = (value < maxValue) ? value : maxValue;
    }
    return static_cast<short>(value);
}

// 0x453880
#pragma comment(linker, "/INCLUDE:?CalcHpDrainPercent@ApplySkillModifyInfo@@QEBA?BFF@Z")  // LIFT: dead-strip keep (no live caller yet)
short const __cdecl ApplySkillModifyInfo::CalcHpDrainPercent(short const param) const
{
    __int64 value = param + SKILL_MODIFY_RATIO(param, _hpDrainPercentModifyPercent) + _hpDrainPercentModifyDiff;
    if (_skillModifyLimitData._record != NULL)
    {
        __int64 const minValue = SKILL_MODIFY_RATIO(param, _skillModifyLimitData._record->hp_drain_percent_min_ratio_percent);
        value = (minValue > value) ? minValue : value;
        __int64 const maxValue = SKILL_MODIFY_RATIO(param, _skillModifyLimitData._record->hp_drain_percent_max_ratio_percent);
        value = (value < maxValue) ? value : maxValue;
    }
    return static_cast<short>(value);
}

#undef SKILL_MODIFY_RATIO
