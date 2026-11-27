# Handoff: lift-gamedaemon-gap-011-e11

## Lifted

All 30 `Summoned::Get*Modify` getters (RVA 0x455210 to 0x4553e0).

Each getter returns one `short` of `Data::SummonedLevelRecord`.
The record pointer is `_levelData._record` at `Summoned` offset 0x19F0 (PDB).
The PDB offsets of the fields are used (0x9A to 0xD8, 0x154 to 0x15C).

## Note

`Summoned` has no lifted layout in `summoned.h` (no base, no members).
Rounds 2 to 4 failed or stayed stubs for that reason.
This round reads `_levelData` through a file-local helper `levelDataShort` with the PDB offset.
`// LIFT:` in the source marks it.
No pad and no invented member is added to the header.
When the `Summoned` layout is lifted, replace the helper with `_levelData._record->field`.

## Not done

`SummonedEntry::SummonedEntry` (RVA 0x96fb0, 0x97010) stay `LIFT_STUB`. They are not in this card.

## Files changed

- `src/Server/GameDaemon/summoned_h.cpp`
- `Docs/Plan/handoffs/lift-gamedaemon-gap-011-e11.md`
