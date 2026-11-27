// duelbot_h.cpp: duelbot.h (GameDaemon PDB, 2019 + PDB). Wave E: DuelBot getters and setters are lifted.
#include "duelbot.h"
#include "LiftStub.h"

// LIFT: dead-strip keep (no live caller yet) for the lifted virtual functions of DuelBot (0x97270 - 0x974e0).
#pragma comment(linker, "/INCLUDE:?GetLastComboSkill@DuelBot@@UEBAIXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?SetLastComboSkill@DuelBot@@UEAAXI@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetLastComboFireLimitTime@DuelBot@@UEBA_JXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?SetLastComboFireLimitTime@DuelBot@@UEAAX_J@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetLastComboExecFirstLimitTime@DuelBot@@UEBA_JXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?SetLastComboExecFirstLimitTime@DuelBot@@UEAAX_J@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetLastComboExecLastLimitTime@DuelBot@@UEBA_JXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?SetLastComboExecLastLimitTime@DuelBot@@UEAAX_J@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetLastComboExecFirstResult@DuelBot@@UEBA?AW4SkillResult@@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?SetLastComboExecFirstResult@DuelBot@@UEAAXW4SkillResult@@@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetLastComboExecLastResult@DuelBot@@UEBA?AW4SkillResult@@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?SetLastComboExecLastResult@DuelBot@@UEAAXW4SkillResult@@@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetLastAttackLimitTime@DuelBot@@UEBA_JW4SkillResult@@@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?SetLastAttackLimitTime@DuelBot@@UEAAXW4SkillResult@@_J@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetLastAttackedLimitTime@DuelBot@@UEBA_JW4SkillResult@@@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?SetLastAttackedLimitTime@DuelBot@@UEAAXW4SkillResult@@_J@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetAttackHitValueModify@DuelBot@@UEAAFXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetAttackCriticalValueModify@DuelBot@@UEAAFXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetDefendCriticalValueModify@DuelBot@@UEAAFXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetDefendDodgeValueModify@DuelBot@@UEAAFXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetDefendParryValueModify@DuelBot@@UEAAFXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetDefendPhysicalValueModify@DuelBot@@UEAAFXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetDefendForceValueModify@DuelBot@@UEAAFXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetAttackStiffDurationValueModify@DuelBot@@UEAAFXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetDefendStiffDurationValueModify@DuelBot@@UEAAFXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetCastDurationValueModify@DuelBot@@UEAAFXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetAttackCriticalDamageModify@DuelBot@@UEAAFXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetDefendCriticalDamageModify@DuelBot@@UEAAFXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetAttackPierceModify@DuelBot@@UEAAFXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetAttackParryPierceModify@DuelBot@@UEAAFXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetDefendParryReduceModify@DuelBot@@UEAAFXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetAttackPerfectParryDamageModify@DuelBot@@UEAAFXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetDefendPerfectParryReduceModify@DuelBot@@UEAAFXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetAttackCounterDamageModify@DuelBot@@UEAAFXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetDefendCounterReduceModify@DuelBot@@UEAAFXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetHealPowerModify@DuelBot@@UEAAFXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetAOEDefendPowerModify@DuelBot@@UEAAFXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetAbnormalAttackPowerModify@DuelBot@@UEAAFXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetAbnormalDefendPowerModify@DuelBot@@UEAAFXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetHatePowerModify@DuelBot@@UEAAFXZ")  // LIFT: dead-strip keep (no live caller yet)

// 0x97240
void __cdecl DuelBot::ClearLastComboSkillValue(void)
{
    LIFT_STUB(0x97240);
}

// 0x97270
unsigned int __cdecl DuelBot::GetLastComboSkill(void) const
{
    return _skillResultContext._lastComboSkill;
}

// 0x97280
void __cdecl DuelBot::SetLastComboSkill(unsigned int skill)
{
    _skillResultContext._lastComboSkill = skill;
}

// 0x97290
__int64 __cdecl DuelBot::GetLastComboFireLimitTime(void) const
{
    return _skillResultContext._lastComboSkillFireLimitTime;
}

// 0x972a0
void __cdecl DuelBot::SetLastComboFireLimitTime(__int64 time)
{
    _skillResultContext._lastComboSkillFireLimitTime = time;
}

// 0x972b0
__int64 __cdecl DuelBot::GetLastComboExecFirstLimitTime(void) const
{
    return _skillResultContext._lastComboSkillExecFirstLimitTime;
}

// 0x972c0
void __cdecl DuelBot::SetLastComboExecFirstLimitTime(__int64 time)
{
    _skillResultContext._lastComboSkillExecFirstLimitTime = time;
}

// 0x972d0
__int64 __cdecl DuelBot::GetLastComboExecLastLimitTime(void) const
{
    return _skillResultContext._lastComboSkillExecLastLimitTime;
}

// 0x972e0
void __cdecl DuelBot::SetLastComboExecLastLimitTime(__int64 time)
{
    _skillResultContext._lastComboSkillExecLastLimitTime = time;
}

// 0x972f0
::SkillResult __cdecl DuelBot::GetLastComboExecFirstResult(void) const
{
    return _skillResultContext._lastComboSkillExecFirstResult;
}

// 0x97300
void __cdecl DuelBot::SetLastComboExecFirstResult(::SkillResult result)
{
    _skillResultContext._lastComboSkillExecFirstResult = result;
}

// 0x97310
::SkillResult __cdecl DuelBot::GetLastComboExecLastResult(void) const
{
    return _skillResultContext._lastComboSkillExecLastResult;
}

// 0x97320
void __cdecl DuelBot::SetLastComboExecLastResult(::SkillResult result)
{
    _skillResultContext._lastComboSkillExecLastResult = result;
}

// 0x97330
// LIFT: the index is result - 1 (the pseudocode reads from 0x28 + 8 * result, array base 0x30).
__int64 __cdecl DuelBot::GetLastAttackLimitTime(::SkillResult result) const
{
    return _skillResultContext._lastAttackLimitTime[result - 1];
}

// 0x97340
void __cdecl DuelBot::SetLastAttackLimitTime(::SkillResult result, __int64 time)
{
    _skillResultContext._lastAttackLimitTime[result - 1] = time;
}

// 0x97350
__int64 __cdecl DuelBot::GetLastAttackedLimitTime(::SkillResult result) const
{
    return _skillResultContext._lastAttackedLimitTime[result - 1];
}

// 0x97360
void __cdecl DuelBot::SetLastAttackedLimitTime(::SkillResult result, __int64 time)
{
    _skillResultContext._lastAttackedLimitTime[result - 1] = time;
}

// 0x97370
short __cdecl DuelBot::GetAttackHitValueModify(void)
{
    return _abilityData._record->attack_hit_value_modify;
}

// 0x97380
short __cdecl DuelBot::GetAttackCriticalValueModify(void)
{
    return _abilityData._record->attack_critical_value_modify;
}

// 0x97390
short __cdecl DuelBot::GetDefendCriticalValueModify(void)
{
    return _abilityData._record->defend_critical_value_modify;
}

// 0x973a0
short __cdecl DuelBot::GetDefendDodgeValueModify(void)
{
    return _abilityData._record->defend_dodge_value_modify;
}

// 0x973b0
short __cdecl DuelBot::GetDefendParryValueModify(void)
{
    return _abilityData._record->defend_parry_value_modify;
}

// 0x973c0
short __cdecl DuelBot::GetDefendPhysicalValueModify(void)
{
    return _abilityData._record->defend_physical_value_modify;
}

// 0x973d0
short __cdecl DuelBot::GetDefendForceValueModify(void)
{
    return _abilityData._record->defend_force_value_modify;
}

// 0x973e0
short __cdecl DuelBot::GetAttackStiffDurationValueModify(void)
{
    return _abilityData._record->attack_stiff_duration_value_modify;
}

// 0x973f0
short __cdecl DuelBot::GetDefendStiffDurationValueModify(void)
{
    return _abilityData._record->defend_stiff_duration_value_modify;
}

// 0x97400
short __cdecl DuelBot::GetCastDurationValueModify(void)
{
    return _abilityData._record->cast_duration_value_modify;
}

// 0x97410
short __cdecl DuelBot::GetAttackCriticalDamageModify(void)
{
    return _abilityData._record->attack_critical_damage_modify;
}

// 0x97420
short __cdecl DuelBot::GetDefendCriticalDamageModify(void)
{
    return _abilityData._record->defend_critical_damage_modify;
}

// 0x97430
short __cdecl DuelBot::GetAttackPierceModify(void)
{
    return _abilityData._record->attack_pierce_modify;
}

// 0x97440
short __cdecl DuelBot::GetAttackParryPierceModify(void)
{
    return _abilityData._record->attack_parry_pierce_modify;
}

// 0x97450
short __cdecl DuelBot::GetDefendParryReduceModify(void)
{
    return _abilityData._record->defend_parry_reduce_modify;
}

// 0x97460
short __cdecl DuelBot::GetAttackPerfectParryDamageModify(void)
{
    return _abilityData._record->attack_perfect_parry_damage_modify;
}

// 0x97470
short __cdecl DuelBot::GetDefendPerfectParryReduceModify(void)
{
    return _abilityData._record->defend_perfect_parry_reduce_modify;
}

// 0x97480
short __cdecl DuelBot::GetAttackCounterDamageModify(void)
{
    return _abilityData._record->attack_counter_damage_modify;
}

// 0x97490
short __cdecl DuelBot::GetDefendCounterReduceModify(void)
{
    return _abilityData._record->defend_counter_reduce_modify;
}

// 0x974a0
short __cdecl DuelBot::GetHealPowerModify(void)
{
    return _abilityData._record->heal_power_modify;
}

// 0x974b0
short __cdecl DuelBot::GetAOEDefendPowerModify(void)
{
    return _abilityData._record->aoe_defend_power_modify;
}

// 0x974c0
short __cdecl DuelBot::GetAbnormalAttackPowerModify(void)
{
    return _abilityData._record->abnormal_attack_power_modify;
}

// 0x974d0
short __cdecl DuelBot::GetAbnormalDefendPowerModify(void)
{
    return _abilityData._record->abnormal_defend_power_modify;
}

// 0x974e0
short __cdecl DuelBot::GetHatePowerModify(void)
{
    return _abilityData._record->hate_power_modify;
}

// 0x974f0
short __cdecl DuelBot::GetAttackAttributeModify(void)
{
    LIFT_STUB(0x974f0);
}

// 0x97500
short __cdecl DuelBot::GetRAttackAoePierceModify(void)
{
    LIFT_STUB(0x97500);
}

// 0x97510
short __cdecl DuelBot::GetRAttackAbnormalHitModify(void)
{
    LIFT_STUB(0x97510);
}

// 0x97520
short __cdecl DuelBot::GetRDefendAbnormalDodgeModify(void)
{
    LIFT_STUB(0x97520);
}

// 0x97530
short __cdecl DuelBot::GetRSupportPowerModify(void)
{
    LIFT_STUB(0x97530);
}

// 0x97540
short __cdecl DuelBot::GetRHypermovePowerModify(void)
{
    LIFT_STUB(0x97540);
}

// 0x97550
short __cdecl DuelBotSummoned::GetAttackHitValueModify(void)
{
    LIFT_STUB(0x97550);
}

// 0x97560
short __cdecl DuelBotSummoned::GetAttackCriticalValueModify(void)
{
    LIFT_STUB(0x97560);
}

// 0x97570
short __cdecl DuelBotSummoned::GetDefendCriticalValueModify(void)
{
    LIFT_STUB(0x97570);
}

// 0x97580
short __cdecl DuelBotSummoned::GetDefendDodgeValueModify(void)
{
    LIFT_STUB(0x97580);
}

// 0x97590
short __cdecl DuelBotSummoned::GetDefendParryValueModify(void)
{
    LIFT_STUB(0x97590);
}

// 0x975a0
short __cdecl DuelBotSummoned::GetDefendPhysicalValueModify(void)
{
    LIFT_STUB(0x975a0);
}

// 0x975b0
short __cdecl DuelBotSummoned::GetDefendForceValueModify(void)
{
    LIFT_STUB(0x975b0);
}

// 0x975c0
short __cdecl DuelBotSummoned::GetAttackStiffDurationValueModify(void)
{
    LIFT_STUB(0x975c0);
}

// 0x975d0
short __cdecl DuelBotSummoned::GetDefendStiffDurationValueModify(void)
{
    LIFT_STUB(0x975d0);
}

// 0x975e0
short __cdecl DuelBotSummoned::GetCastDurationValueModify(void)
{
    LIFT_STUB(0x975e0);
}

// 0x975f0
short __cdecl DuelBotSummoned::GetAttackCriticalDamageModify(void)
{
    LIFT_STUB(0x975f0);
}

// 0x97600
short __cdecl DuelBotSummoned::GetDefendCriticalDamageModify(void)
{
    LIFT_STUB(0x97600);
}

// 0x97610
short __cdecl DuelBotSummoned::GetAttackPierceModify(void)
{
    LIFT_STUB(0x97610);
}

// 0x97620
short __cdecl DuelBotSummoned::GetAttackParryPierceModify(void)
{
    LIFT_STUB(0x97620);
}

// 0x97630
short __cdecl DuelBotSummoned::GetDefendParryReduceModify(void)
{
    LIFT_STUB(0x97630);
}

// 0x97640
short __cdecl DuelBotSummoned::GetAttackPerfectParryDamageModify(void)
{
    LIFT_STUB(0x97640);
}

// 0x97650
short __cdecl DuelBotSummoned::GetDefendPerfectParryReduceModify(void)
{
    LIFT_STUB(0x97650);
}

// 0x97660
short __cdecl DuelBotSummoned::GetAttackCounterDamageModify(void)
{
    LIFT_STUB(0x97660);
}

// 0x97670
short __cdecl DuelBotSummoned::GetDefendCounterReduceModify(void)
{
    LIFT_STUB(0x97670);
}

// 0x97680
short __cdecl DuelBotSummoned::GetHealPowerModify(void)
{
    LIFT_STUB(0x97680);
}

// 0x97690
short __cdecl DuelBotSummoned::GetAOEDefendPowerModify(void)
{
    LIFT_STUB(0x97690);
}

// 0x976a0
short __cdecl DuelBotSummoned::GetAbnormalAttackPowerModify(void)
{
    LIFT_STUB(0x976a0);
}

// 0x976b0
short __cdecl DuelBotSummoned::GetAbnormalDefendPowerModify(void)
{
    LIFT_STUB(0x976b0);
}

// 0x976c0
short __cdecl DuelBotSummoned::GetHatePowerModify(void)
{
    LIFT_STUB(0x976c0);
}

// 0x976d0
short __cdecl DuelBotSummoned::GetAttackAttributeModify(void)
{
    LIFT_STUB(0x976d0);
}

// 0x976e0
short __cdecl DuelBotSummoned::GetRAttackAoePierceModify(void)
{
    LIFT_STUB(0x976e0);
}

// 0x976f0
short __cdecl DuelBotSummoned::GetRAttackAbnormalHitModify(void)
{
    LIFT_STUB(0x976f0);
}

// 0x97700
short __cdecl DuelBotSummoned::GetRDefendAbnormalDodgeModify(void)
{
    LIFT_STUB(0x97700);
}

// 0x97710
short __cdecl DuelBotSummoned::GetRSupportPowerModify(void)
{
    LIFT_STUB(0x97710);
}

// 0x97720
short __cdecl DuelBotSummoned::GetRHypermovePowerModify(void)
{
    LIFT_STUB(0x97720);
}

// 0x228450
bool __cdecl ZoneDuelBotIdManager::IsExist(unsigned __int64)
{
    LIFT_STUB(0x228450);
}
