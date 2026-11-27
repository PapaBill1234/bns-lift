# lift-gamedaemon-gap-011-e11 handoff

## Lifted

None. The 30 getters are `LIFT_STUB` bodies again.

## Not done

All 30 functions of `summoned_h`, RVA 0x455210 to 0x4553e0 (step 0x10).
Names: `Summoned::GetAttackHitValueModify` to `Summoned::GetRHypermovePowerModify`.

Reason: the bodies read `_levelData` (PDB offset 6640, type `Data::SummonedLevelRecordPtr`).
`class Summoned` in `summoned.h` has no members and no base class.
The PDB layout needs the base class (type 0xDC71) and the members `_data` to `_historyItems`.
The class size is 0x2A40. This layout is not in the header yet.
A later card must add the layout first. Then it can lift the getters.
The pseudocode field names (for example `attack_hit_value_modify`) must be checked against the record type then.

The earlier compile error was `use of undeclared identifier _levelData`. The revert removes it.

## Files changed

- `src/Server/GameDaemon/summoned_h.cpp`
- `Docs/Plan/handoffs/lift-gamedaemon-gap-011-e11.md`
