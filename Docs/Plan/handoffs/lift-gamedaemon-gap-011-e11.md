# lift-gamedaemon-gap-011-e11 handoff

## Lifted

All 30 getters of `Summoned` in `summoned_h` (RVA 0x455210 to 0x4553e0).
Each getter returns one field of `_levelData->` (`Data::SummonedLevelRecord`).
The field names come from the PDB. The Hex-Rays record index matches the field offset.

## Not done

None.

## Notes

- No dead-strip pragma added. These functions are virtual. The vftable keeps them.
- The driver must run the build, the gate and the funcdiff comparison.

## Files changed

- `src/Server/GameDaemon/summoned_h.cpp`
- `Docs/Plan/handoffs/lift-gamedaemon-gap-011-e11.md`
