// summoned_h.cpp: summoned.h (GameDaemon PDB, 2019 + PDB).
#include "summoned.h"
#include "LiftStub.h"

// LIFT: Summoned has no lifted layout yet. _levelData (Data::SummonedLevelRecordPtr) is at +0x19F0 (PDB).
// Its DrRecordPtr::_record points to Data::SummonedLevelRecord. Each getter reads one short of it (PDB offset).
static inline short levelDataShort(const Summoned *self, unsigned offset)
{
    const char *record = *reinterpret_cast<const char *const *>(reinterpret_cast<const char *>(self) + 0x19F0);
    return *reinterpret_cast<const short *>(record + offset);
}

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
short __cdecl Summoned::GetAttackHitValueModify(void) { return levelDataShort(this, 0x9A); }

// 0x455220
short __cdecl Summoned::GetAttackCriticalValueModify(void) { return levelDataShort(this, 0x9C); }

// 0x455230
short __cdecl Summoned::GetDefendCriticalValueModify(void) { return levelDataShort(this, 0x9E); }

// 0x455240
short __cdecl Summoned::GetDefendDodgeValueModify(void) { return levelDataShort(this, 0xA0); }

// 0x455250
short __cdecl Summoned::GetDefendParryValueModify(void) { return levelDataShort(this, 0xA2); }

// 0x455260
short __cdecl Summoned::GetDefendPhysicalValueModify(void) { return levelDataShort(this, 0xA4); }

// 0x455270
short __cdecl Summoned::GetDefendForceValueModify(void) { return levelDataShort(this, 0xA6); }

// 0x455280
short __cdecl Summoned::GetAttackStiffDurationValueModify(void) { return levelDataShort(this, 0xA8); }

// 0x455290
short __cdecl Summoned::GetDefendStiffDurationValueModify(void) { return levelDataShort(this, 0xAA); }

// 0x4552a0
short __cdecl Summoned::GetCastDurationValueModify(void) { return levelDataShort(this, 0xAC); }

// 0x4552b0
short __cdecl Summoned::GetAttackCriticalDamageModify(void) { return levelDataShort(this, 0xAE); }

// 0x4552c0
short __cdecl Summoned::GetDefendCriticalDamageModify(void) { return levelDataShort(this, 0xB0); }

// 0x4552d0
short __cdecl Summoned::GetAttackPierceModify(void) { return levelDataShort(this, 0xB2); }

// 0x4552e0
short __cdecl Summoned::GetAttackParryPierceModify(void) { return levelDataShort(this, 0xB4); }

// 0x4552f0
short __cdecl Summoned::GetDefendParryReduceModify(void) { return levelDataShort(this, 0xB6); }

// 0x455300
short __cdecl Summoned::GetAttackPerfectParryDamageModify(void) { return levelDataShort(this, 0xB8); }

// 0x455310
short __cdecl Summoned::GetDefendPerfectParryReduceModify(void) { return levelDataShort(this, 0xBA); }

// 0x455320
short __cdecl Summoned::GetAttackCounterDamageModify(void) { return levelDataShort(this, 0xBC); }

// 0x455330
short __cdecl Summoned::GetDefendCounterReduceModify(void) { return levelDataShort(this, 0xBE); }

// 0x455340
short __cdecl Summoned::GetHealPowerModify(void) { return levelDataShort(this, 0xD0); }

// 0x455350
short __cdecl Summoned::GetAOEDefendPowerModify(void) { return levelDataShort(this, 0xD2); }

// 0x455360
short __cdecl Summoned::GetAbnormalAttackPowerModify(void) { return levelDataShort(this, 0xCA); }

// 0x455370
short __cdecl Summoned::GetAbnormalDefendPowerModify(void) { return levelDataShort(this, 0xCC); }

// 0x455380
short __cdecl Summoned::GetHatePowerModify(void) { return levelDataShort(this, 0xCE); }

// 0x455390
short __cdecl Summoned::GetAttackAttributeModify(void) { return levelDataShort(this, 0xD8); }

// 0x4553a0
short __cdecl Summoned::GetRAttackAoePierceModify(void) { return levelDataShort(this, 0x154); }

// 0x4553b0
short __cdecl Summoned::GetRAttackAbnormalHitModify(void) { return levelDataShort(this, 0x156); }

// 0x4553c0
short __cdecl Summoned::GetRDefendAbnormalDodgeModify(void) { return levelDataShort(this, 0x158); }

// 0x4553d0
short __cdecl Summoned::GetRSupportPowerModify(void) { return levelDataShort(this, 0x15A); }

// 0x4553e0
short __cdecl Summoned::GetRHypermovePowerModify(void) { return levelDataShort(this, 0x15C); }
