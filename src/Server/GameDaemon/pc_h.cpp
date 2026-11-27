// pc_h.cpp: pc.h (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "pc.h"
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:?IsExceptHate@Pc@@UEAA_NXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?SetExceptHate@Pc@@UEAAX_N@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?ClearLastComboSkillValue@Pc@@UEAAXXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetLastComboSkill@Pc@@UEBAIXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?SetLastComboSkill@Pc@@UEAAXI@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetLastComboFireLimitTime@Pc@@UEBA_JXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?SetLastComboFireLimitTime@Pc@@UEAAX_J@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetLastComboExecFirstLimitTime@Pc@@UEBA_JXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?SetLastComboExecFirstLimitTime@Pc@@UEAAX_J@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetLastComboExecLastLimitTime@Pc@@UEBA_JXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?SetLastComboExecLastLimitTime@Pc@@UEAAX_J@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetLastComboExecFirstResult@Pc@@UEBA?AW4SkillResult@@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?SetLastComboExecFirstResult@Pc@@UEAAXW4SkillResult@@@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetLastComboExecLastResult@Pc@@UEBA?AW4SkillResult@@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?SetLastComboExecLastResult@Pc@@UEAAXW4SkillResult@@@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetLastAttackLimitTime@Pc@@UEBA_JW4SkillResult@@@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?SetLastAttackLimitTime@Pc@@UEAAXW4SkillResult@@_J@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetLastAttackedLimitTime@Pc@@UEBA_JW4SkillResult@@@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?SetLastAttackedLimitTime@Pc@@UEAAXW4SkillResult@@_J@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetSkillResultContext@Pc@@UEAAAEAVSkillResultContext@@XZ")  // LIFT: dead-strip keep (no live caller yet)

// 0xe830
__cdecl PcInfoForGameLog::PcInfoForGameLog(void)
{
    LIFT_STUB(0xe830);
}

// 0x97130
void __cdecl Pc::GetGuildCombatRewardDataId(char, ::Pc::SeasonContentsRewardsOfGuild &)
{
    LIFT_STUB(0x97130);
}

// 0x4554d0
short __cdecl Pc::GetAttackHitValueModify(void)
{
    LIFT_STUB(0x4554d0);
}

// 0x455550
short __cdecl Pc::GetAttackCriticalValueModify(void)
{
    LIFT_STUB(0x455550);
}

// 0x4555d0
short __cdecl Pc::GetDefendCriticalValueModify(void)
{
    LIFT_STUB(0x4555d0);
}

// 0x455650
short __cdecl Pc::GetDefendDodgeValueModify(void)
{
    LIFT_STUB(0x455650);
}

// 0x4556d0
short __cdecl Pc::GetDefendParryValueModify(void)
{
    LIFT_STUB(0x4556d0);
}

// 0x455750
short __cdecl Pc::GetDefendPhysicalValueModify(void)
{
    LIFT_STUB(0x455750);
}

// 0x4557d0
short __cdecl Pc::GetDefendForceValueModify(void)
{
    LIFT_STUB(0x4557d0);
}

// 0x455850
short __cdecl Pc::GetAttackStiffDurationValueModify(void)
{
    LIFT_STUB(0x455850);
}

// 0x4558d0
short __cdecl Pc::GetDefendStiffDurationValueModify(void)
{
    LIFT_STUB(0x4558d0);
}

// 0x455950
short __cdecl Pc::GetCastDurationValueModify(void)
{
    LIFT_STUB(0x455950);
}

// 0x4559d0
short __cdecl Pc::GetAttackCriticalDamageModify(void)
{
    LIFT_STUB(0x4559d0);
}

// 0x455a50
short __cdecl Pc::GetDefendCriticalDamageModify(void)
{
    LIFT_STUB(0x455a50);
}

// 0x455ad0
short __cdecl Pc::GetAttackPierceModify(void)
{
    LIFT_STUB(0x455ad0);
}

// 0x455b50
short __cdecl Pc::GetAttackParryPierceModify(void)
{
    LIFT_STUB(0x455b50);
}

// 0x455bd0
short __cdecl Pc::GetDefendParryReduceModify(void)
{
    LIFT_STUB(0x455bd0);
}

// 0x455c50
short __cdecl Pc::GetAttackPerfectParryDamageModify(void)
{
    LIFT_STUB(0x455c50);
}

// 0x455cd0
short __cdecl Pc::GetDefendPerfectParryReduceModify(void)
{
    LIFT_STUB(0x455cd0);
}

// 0x455d50
short __cdecl Pc::GetAttackCounterDamageModify(void)
{
    LIFT_STUB(0x455d50);
}

// 0x455dd0
short __cdecl Pc::GetDefendCounterReduceModify(void)
{
    LIFT_STUB(0x455dd0);
}

// 0x455e50
short __cdecl Pc::GetHealPowerModify(void)
{
    LIFT_STUB(0x455e50);
}

// 0x455ed0
short __cdecl Pc::GetAOEDefendPowerModify(void)
{
    LIFT_STUB(0x455ed0);
}

// 0x455f50
short __cdecl Pc::GetAbnormalAttackPowerModify(void)
{
    LIFT_STUB(0x455f50);
}

// 0x455fd0
short __cdecl Pc::GetAbnormalDefendPowerModify(void)
{
    LIFT_STUB(0x455fd0);
}

// 0x456050
short __cdecl Pc::GetHatePowerModify(void)
{
    LIFT_STUB(0x456050);
}

// 0x4560d0
short __cdecl Pc::GetAttackAttributeModify(void)
{
    LIFT_STUB(0x4560d0);
}

// 0x456150
short __cdecl Pc::GetRAttackAoePierceModify(void)
{
    LIFT_STUB(0x456150);
}

// 0x4561d0
short __cdecl Pc::GetRAttackAbnormalHitModify(void)
{
    LIFT_STUB(0x4561d0);
}

// 0x456250
short __cdecl Pc::GetRDefendAbnormalDodgeModify(void)
{
    LIFT_STUB(0x456250);
}

// 0x4562d0
short __cdecl Pc::GetRSupportPowerModify(void)
{
    LIFT_STUB(0x4562d0);
}

// 0x456350
short __cdecl Pc::GetRHypermovePowerModify(void)
{
    LIFT_STUB(0x456350);
}

// 0x4563d0
bool __cdecl Pc::IsExceptHate(void)
{
    return _exceptHate;
}

// 0x4563e0
void __cdecl Pc::SetExceptHate(bool except)
{
    _exceptHate = except;
}

// 0x4563f0
void __cdecl Pc::ClearLastComboSkillValue(void)
{
    // LIFT: inline SkillResultContext::ClearLastComboSkillValue (the PDB has no out-of-line body).
    _skillResultContext._lastComboSkill = 0;
    _skillResultContext._lastComboSkillFireLimitTime = 0;
    _skillResultContext._lastComboSkillExecFirstLimitTime = 0;
    _skillResultContext._lastComboSkillExecLastLimitTime = 0;
    _skillResultContext._lastComboSkillExecFirstResult = static_cast< ::SkillResult>(0);
    _skillResultContext._lastComboSkillExecLastResult = static_cast< ::SkillResult>(0);
}

// 0x456420
unsigned int __cdecl Pc::GetLastComboSkill(void) const
{
    return _skillResultContext._lastComboSkill;
}

// 0x456430
void __cdecl Pc::SetLastComboSkill(unsigned int skill)
{
    _skillResultContext._lastComboSkill = skill;
}

// 0x456440
__int64 __cdecl Pc::GetLastComboFireLimitTime(void) const
{
    return _skillResultContext._lastComboSkillFireLimitTime;
}

// 0x456450
void __cdecl Pc::SetLastComboFireLimitTime(__int64 time)
{
    _skillResultContext._lastComboSkillFireLimitTime = time;
}

// 0x456460
__int64 __cdecl Pc::GetLastComboExecFirstLimitTime(void) const
{
    return _skillResultContext._lastComboSkillExecFirstLimitTime;
}

// 0x456470
void __cdecl Pc::SetLastComboExecFirstLimitTime(__int64 time)
{
    _skillResultContext._lastComboSkillExecFirstLimitTime = time;
}

// 0x456480
__int64 __cdecl Pc::GetLastComboExecLastLimitTime(void) const
{
    return _skillResultContext._lastComboSkillExecLastLimitTime;
}

// 0x456490
void __cdecl Pc::SetLastComboExecLastLimitTime(__int64 time)
{
    _skillResultContext._lastComboSkillExecLastLimitTime = time;
}

// 0x4564a0
::SkillResult __cdecl Pc::GetLastComboExecFirstResult(void) const
{
    return _skillResultContext._lastComboSkillExecFirstResult;
}

// 0x4564b0
void __cdecl Pc::SetLastComboExecFirstResult(::SkillResult result)
{
    _skillResultContext._lastComboSkillExecFirstResult = result;
}

// 0x4564c0
::SkillResult __cdecl Pc::GetLastComboExecLastResult(void) const
{
    return _skillResultContext._lastComboSkillExecLastResult;
}

// 0x4564d0
void __cdecl Pc::SetLastComboExecLastResult(::SkillResult result)
{
    _skillResultContext._lastComboSkillExecLastResult = result;
}

// 0x4564e0
__int64 __cdecl Pc::GetLastAttackLimitTime(::SkillResult result) const
{
    return _skillResultContext._lastAttackLimitTime[result - 1];
}

// 0x4564f0
void __cdecl Pc::SetLastAttackLimitTime(::SkillResult result, __int64 time)
{
    _skillResultContext._lastAttackLimitTime[result - 1] = time;
}

// 0x456500
__int64 __cdecl Pc::GetLastAttackedLimitTime(::SkillResult result) const
{
    return _skillResultContext._lastAttackedLimitTime[result - 1];
}

// 0x456510
void __cdecl Pc::SetLastAttackedLimitTime(::SkillResult result, __int64 time)
{
    _skillResultContext._lastAttackedLimitTime[result - 1] = time;
}

// 0x456520
::SkillResultContext & __cdecl Pc::GetSkillResultContext(void)
{
    return _skillResultContext;
}
