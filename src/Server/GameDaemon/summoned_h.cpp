// summoned_h.cpp: summoned.h (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "summoned.h"
#include "LiftStub.h"

// 0x96fb0
__cdecl SummonedEntry::SummonedEntry(void)
{
    LIFT_STUB(0x96fb0);
}

// 0x97010
__cdecl SummonedEntry::SummonedEntry(char)
{
    LIFT_STUB(0x97010);
}

// 0x455210
short __cdecl Summoned::GetAttackHitValueModify(void)
{
    return _levelData->attack_hit_value_modify;
}

// 0x455220
short __cdecl Summoned::GetAttackCriticalValueModify(void)
{
    return _levelData->attack_critical_value_modify;
}

// 0x455230
short __cdecl Summoned::GetDefendCriticalValueModify(void)
{
    return _levelData->defend_critical_value_modify;
}

// 0x455240
short __cdecl Summoned::GetDefendDodgeValueModify(void)
{
    return _levelData->defend_dodge_value_modify;
}

// 0x455250
short __cdecl Summoned::GetDefendParryValueModify(void)
{
    return _levelData->defend_parry_value_modify;
}

// 0x455260
short __cdecl Summoned::GetDefendPhysicalValueModify(void)
{
    return _levelData->defend_physical_value_modify;
}

// 0x455270
short __cdecl Summoned::GetDefendForceValueModify(void)
{
    return _levelData->defend_force_value_modify;
}

// 0x455280
short __cdecl Summoned::GetAttackStiffDurationValueModify(void)
{
    return _levelData->attack_stiff_duration_value_modify;
}

// 0x455290
short __cdecl Summoned::GetDefendStiffDurationValueModify(void)
{
    return _levelData->defend_stiff_duration_value_modify;
}

// 0x4552a0
short __cdecl Summoned::GetCastDurationValueModify(void)
{
    return _levelData->cast_duration_value_modify;
}

// 0x4552b0
short __cdecl Summoned::GetAttackCriticalDamageModify(void)
{
    return _levelData->attack_critical_damage_modify;
}

// 0x4552c0
short __cdecl Summoned::GetDefendCriticalDamageModify(void)
{
    return _levelData->defend_critical_damage_modify;
}

// 0x4552d0
short __cdecl Summoned::GetAttackPierceModify(void)
{
    return _levelData->attack_pierce_modify;
}

// 0x4552e0
short __cdecl Summoned::GetAttackParryPierceModify(void)
{
    return _levelData->attack_parry_pierce_modify;
}

// 0x4552f0
short __cdecl Summoned::GetDefendParryReduceModify(void)
{
    return _levelData->defend_parry_reduce_modify;
}

// 0x455300
short __cdecl Summoned::GetAttackPerfectParryDamageModify(void)
{
    return _levelData->attack_perfect_parry_damage_modify;
}

// 0x455310
short __cdecl Summoned::GetDefendPerfectParryReduceModify(void)
{
    return _levelData->defend_perfect_parry_reduce_modify;
}

// 0x455320
short __cdecl Summoned::GetAttackCounterDamageModify(void)
{
    return _levelData->attack_counter_damage_modify;
}

// 0x455330
short __cdecl Summoned::GetDefendCounterReduceModify(void)
{
    return _levelData->defend_counter_reduce_modify;
}

// 0x455340
short __cdecl Summoned::GetHealPowerModify(void)
{
    return _levelData->heal_power_modify;
}

// 0x455350
short __cdecl Summoned::GetAOEDefendPowerModify(void)
{
    return _levelData->aoe_defend_power_modify;
}

// 0x455360
short __cdecl Summoned::GetAbnormalAttackPowerModify(void)
{
    return _levelData->abnormal_attack_power_modify;
}

// 0x455370
short __cdecl Summoned::GetAbnormalDefendPowerModify(void)
{
    return _levelData->abnormal_defend_power_modify;
}

// 0x455380
short __cdecl Summoned::GetHatePowerModify(void)
{
    return _levelData->hate_power_modify;
}

// 0x455390
short __cdecl Summoned::GetAttackAttributeModify(void)
{
    return _levelData->attack_attribute_modify;
}

// 0x4553a0
short __cdecl Summoned::GetRAttackAoePierceModify(void)
{
    return _levelData->r_attack_aoe_pierce_modify;
}

// 0x4553b0
short __cdecl Summoned::GetRAttackAbnormalHitModify(void)
{
    return _levelData->r_attack_abnormal_hit_modify;
}

// 0x4553c0
short __cdecl Summoned::GetRDefendAbnormalDodgeModify(void)
{
    return _levelData->r_defend_abnormal_dodge_modify;
}

// 0x4553d0
short __cdecl Summoned::GetRSupportPowerModify(void)
{
    return _levelData->r_support_power_modify;
}

// 0x4553e0
short __cdecl Summoned::GetRHypermovePowerModify(void)
{
    return _levelData->r_hypermove_power_modify;
}
