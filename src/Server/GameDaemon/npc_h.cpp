// npc_h.cpp: npc.h (GameDaemon PDB, 2019 + PDB). Lifted: 30 record getters (card lift-gamedaemon-gap-006-e6).
#include "npc.h"
#include "LiftStub.h"

// LIFT: keep the lifted virtual getters until the callers are lifted (the vftable and the callers are stubs;
// /OPT:REF drops them). Card lift-gamedaemon-gap-006-e6.
#pragma comment(linker, "/INCLUDE:?GetAttackHitValueModify@Npc@@UEAAFXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetAttackCriticalValueModify@Npc@@UEAAFXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetDefendCriticalValueModify@Npc@@UEAAFXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetDefendDodgeValueModify@Npc@@UEAAFXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetDefendParryValueModify@Npc@@UEAAFXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetDefendPhysicalValueModify@Npc@@UEAAFXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetDefendForceValueModify@Npc@@UEAAFXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetAttackStiffDurationValueModify@Npc@@UEAAFXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetDefendStiffDurationValueModify@Npc@@UEAAFXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetCastDurationValueModify@Npc@@UEAAFXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetAttackCriticalDamageModify@Npc@@UEAAFXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetDefendCriticalDamageModify@Npc@@UEAAFXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetAttackPierceModify@Npc@@UEAAFXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetAttackParryPierceModify@Npc@@UEAAFXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetDefendParryReduceModify@Npc@@UEAAFXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetAttackPerfectParryDamageModify@Npc@@UEAAFXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetDefendPerfectParryReduceModify@Npc@@UEAAFXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetAttackCounterDamageModify@Npc@@UEAAFXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetDefendCounterReduceModify@Npc@@UEAAFXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetHealPowerModify@Npc@@UEAAFXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetAOEDefendPowerModify@Npc@@UEAAFXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetAbnormalAttackPowerModify@Npc@@UEAAFXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetAbnormalDefendPowerModify@Npc@@UEAAFXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetHatePowerModify@Npc@@UEAAFXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetAttackAttributeModify@Npc@@UEAAFXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetRAttackAoePierceModify@Npc@@UEAAFXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetRAttackAbnormalHitModify@Npc@@UEAAFXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetRDefendAbnormalDodgeModify@Npc@@UEAAFXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetRSupportPowerModify@Npc@@UEAAFXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetRHypermovePowerModify@Npc@@UEAAFXZ")  // LIFT: dead-strip keep (no live caller yet)

// LIFT: the skeleton Npc has no members. Npc::_data (Data::NpcRecordPtr, PDB +0xC50) holds a DrEl * to the NpcRecord.
// The macro reads one short of the NpcRecord at the PDB offset of the named field.
#define NPC_RECORD_SHORT(self, off) \
    (*reinterpret_cast<short *>(*reinterpret_cast<char **>(reinterpret_cast<char *>(self) + 0xC50) + (off)))

// 0x27380
short __cdecl Npc::GetAttackHitValueModify(void)
{
    return NPC_RECORD_SHORT(this, 0x878);  // attack_hit_value_modify
}

// 0x27390
short __cdecl Npc::GetAttackCriticalValueModify(void)
{
    return NPC_RECORD_SHORT(this, 0x87a);  // attack_critical_value_modify
}

// 0x273a0
short __cdecl Npc::GetDefendCriticalValueModify(void)
{
    return NPC_RECORD_SHORT(this, 0x87c);  // defend_critical_value_modify
}

// 0x273b0
short __cdecl Npc::GetDefendDodgeValueModify(void)
{
    return NPC_RECORD_SHORT(this, 0x87e);  // defend_dodge_value_modify
}

// 0x273c0
short __cdecl Npc::GetDefendParryValueModify(void)
{
    return NPC_RECORD_SHORT(this, 0x880);  // defend_parry_value_modify
}

// 0x273d0
short __cdecl Npc::GetDefendPhysicalValueModify(void)
{
    return NPC_RECORD_SHORT(this, 0x882);  // defend_physical_value_modify
}

// 0x273e0
short __cdecl Npc::GetDefendForceValueModify(void)
{
    return NPC_RECORD_SHORT(this, 0x884);  // defend_force_value_modify
}

// 0x273f0
short __cdecl Npc::GetAttackStiffDurationValueModify(void)
{
    return NPC_RECORD_SHORT(this, 0x886);  // attack_stiff_duration_value_modify
}

// 0x27400
short __cdecl Npc::GetDefendStiffDurationValueModify(void)
{
    return NPC_RECORD_SHORT(this, 0x888);  // defend_stiff_duration_value_modify
}

// 0x27410
short __cdecl Npc::GetCastDurationValueModify(void)
{
    return NPC_RECORD_SHORT(this, 0x88a);  // cast_duration_value_modify
}

// 0x27420
short __cdecl Npc::GetAttackCriticalDamageModify(void)
{
    return NPC_RECORD_SHORT(this, 0x88c);  // attack_critical_damage_modify
}

// 0x27430
short __cdecl Npc::GetDefendCriticalDamageModify(void)
{
    return NPC_RECORD_SHORT(this, 0x88e);  // defend_critical_damage_modify
}

// 0x27440
short __cdecl Npc::GetAttackPierceModify(void)
{
    return NPC_RECORD_SHORT(this, 0x890);  // attack_pierce_modify
}

// 0x27450
short __cdecl Npc::GetAttackParryPierceModify(void)
{
    return NPC_RECORD_SHORT(this, 0x892);  // attack_parry_pierce_modify
}

// 0x27460
short __cdecl Npc::GetDefendParryReduceModify(void)
{
    return NPC_RECORD_SHORT(this, 0x894);  // defend_parry_reduce_modify
}

// 0x27470
short __cdecl Npc::GetAttackPerfectParryDamageModify(void)
{
    return NPC_RECORD_SHORT(this, 0x896);  // attack_perfect_parry_damage_modify
}

// 0x27480
short __cdecl Npc::GetDefendPerfectParryReduceModify(void)
{
    return NPC_RECORD_SHORT(this, 0x898);  // defend_perfect_parry_reduce_modify
}

// 0x27490
short __cdecl Npc::GetAttackCounterDamageModify(void)
{
    return NPC_RECORD_SHORT(this, 0x89a);  // attack_counter_damage_modify
}

// 0x274a0
short __cdecl Npc::GetDefendCounterReduceModify(void)
{
    return NPC_RECORD_SHORT(this, 0x89c);  // defend_counter_reduce_modify
}

// 0x274b0
short __cdecl Npc::GetHealPowerModify(void)
{
    return NPC_RECORD_SHORT(this, 0x874);  // heal_power_modify
}

// 0x274c0
short __cdecl Npc::GetAOEDefendPowerModify(void)
{
    return NPC_RECORD_SHORT(this, 0x876);  // aoe_defend_power_modify
}

// 0x274d0
short __cdecl Npc::GetAbnormalAttackPowerModify(void)
{
    return NPC_RECORD_SHORT(this, 0x86e);  // abnormal_attack_power_modify
}

// 0x274e0
short __cdecl Npc::GetAbnormalDefendPowerModify(void)
{
    return NPC_RECORD_SHORT(this, 0x870);  // abnormal_defend_power_modify
}

// 0x274f0
short __cdecl Npc::GetHatePowerModify(void)
{
    return NPC_RECORD_SHORT(this, 0x872);  // hate_power_modify
}

// 0x27500
short __cdecl Npc::GetAttackAttributeModify(void)
{
    return NPC_RECORD_SHORT(this, 0x8d4);  // attack_attribute_modify
}

// 0x27510
short __cdecl Npc::GetRAttackAoePierceModify(void)
{
    return NPC_RECORD_SHORT(this, 0x90c);  // r_attack_aoe_pierce_modify
}

// 0x27520
short __cdecl Npc::GetRAttackAbnormalHitModify(void)
{
    return NPC_RECORD_SHORT(this, 0x90e);  // r_attack_abnormal_hit_modify
}

// 0x27530
short __cdecl Npc::GetRDefendAbnormalDodgeModify(void)
{
    return NPC_RECORD_SHORT(this, 0x910);  // r_defend_abnormal_dodge_modify
}

// 0x27540
short __cdecl Npc::GetRSupportPowerModify(void)
{
    return NPC_RECORD_SHORT(this, 0x912);  // r_support_power_modify
}

// 0x27550
short __cdecl Npc::GetRHypermovePowerModify(void)
{
    return NPC_RECORD_SHORT(this, 0x914);  // r_hypermove_power_modify
}
