# Handoff: lift-gamedaemon-gap-011-e11

## Lifted

None. All 30 bodies stay `LIFT_STUB`.

## Why

Each getter reads `this->_levelData._record[N]`.
`Summoned::_levelData` is at offset 0x19F0 (PDB).
`Summoned` has a base class (PDB type 0xDC71) of size 0x19E8.
The base chain is not yet in `src/` as a lifted layout.
The skeleton header `summoned.h` has no bases and no members.
A header with no pads and no invented names needs the full base chain first.
That work is larger than this card.
Round 2 used `_levelData` without a declaration. The build failed.
Round 3 set the bodies back to stubs, so the build is safe. It gives no MATCH.

## Not done

All 30 functions. The reason is the same for each: no base layout for `Summoned`.

| RVA | Function |
| --- | --- |
| 0x455210 | Summoned::GetAttackHitValueModify |
| 0x455220 | Summoned::GetAttackCriticalValueModify |
| 0x455230 | Summoned::GetDefendCriticalValueModify |
| 0x455240 | Summoned::GetDefendDodgeValueModify |
| 0x455250 | Summoned::GetDefendParryValueModify |
| 0x455260 | Summoned::GetDefendPhysicalValueModify |
| 0x455270 | Summoned::GetDefendForceValueModify |
| 0x455280 | Summoned::GetAttackStiffDurationValueModify |
| 0x455290 | Summoned::GetDefendStiffDurationValueModify |
| 0x4552a0 | Summoned::GetCastDurationValueModify |
| 0x4552b0 | Summoned::GetAttackCriticalDamageModify |
| 0x4552c0 | Summoned::GetDefendCriticalDamageModify |
| 0x4552d0 | Summoned::GetAttackPierceModify |
| 0x4552e0 | Summoned::GetAttackParryPierceModify |
| 0x4552f0 | Summoned::GetDefendParryReduceModify |
| 0x455300 | Summoned::GetAttackPerfectParryDamageModify |
| 0x455310 | Summoned::GetDefendPerfectParryReduceModify |
| 0x455320 | Summoned::GetAttackCounterDamageModify |
| 0x455330 | Summoned::GetDefendCounterReduceModify |
| 0x455340 | Summoned::GetHealPowerModify |
| 0x455350 | Summoned::GetAOEDefendPowerModify |
| 0x455360 | Summoned::GetAbnormalAttackPowerModify |
| 0x455370 | Summoned::GetAbnormalDefendPowerModify |
| 0x455380 | Summoned::GetHatePowerModify |
| 0x455390 | Summoned::GetAttackAttributeModify |
| 0x4553a0 | Summoned::GetRAttackAoePierceModify |
| 0x4553b0 | Summoned::GetRAttackAbnormalHitModify |
| 0x4553c0 | Summoned::GetRDefendAbnormalDodgeModify |
| 0x4553d0 | Summoned::GetRSupportPowerModify |
| 0x4553e0 | Summoned::GetRHypermovePowerModify |

## Next step

Lift the layout chain of the `Summoned` base classes first.
Then declare `_data` (0x19E8) and `_levelData` (0x19F0) with PDB types.
Then lift the 30 getters.

## Files changed

- `Docs/Plan/handoffs/lift-gamedaemon-gap-011-e11.md`
