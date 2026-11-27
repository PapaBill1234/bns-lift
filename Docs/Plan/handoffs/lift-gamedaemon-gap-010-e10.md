# Handoff: lift-gamedaemon-gap-010-e10 (round 2)

## Lifted

All 40 functions of the card (0x97270 - 0x974e0): 16 combo/attack time accessors and 24 `Modify` getters of `DuelBot`.

## How

- Round 1 stopped because `DuelBot` had no members. Round 2 adds a local PDB layout to `duelbot.h`.
- `DuelBot` gets `_abilityData` (0x1868), `_skillResultContext` (0x1880) and `duelBotSummoned` (0x1930).
  The base chain (`DuelBotCreature`, `Creature`) is not lifted. It is opaque storage up to 0x1868.
- `Data::DuelBotAbilityRecord` has the 24 `*_modify` fields at 0xBE - 0xEC (PDB names). The head is opaque.
- `DuelBotSkillResultContext` copies the PDB `SkillResultContext` (0xB0). Its vptr is a plain slot.
- `Get/SetLastAttack(ed)LimitTime` use `[result - 1]`. The pseudocode reads at 0x28 + 8 * result and the array base is 0x30.
- Each lifted virtual function has a `/INCLUDE` pragma with a `// LIFT:` note (no live caller yet).

## Not done

None. I could not build or diff in this session. The pragma names are hand-made MSVC x64 names.
❓ The return extension (movsx or movzx) of the 24 getters is not checked.

## Files changed

- `src/Server/GameDaemon/duelbot.h`
- `src/Server/GameDaemon/duelbot_h.cpp`
- `Docs/Plan/handoffs/lift-gamedaemon-gap-010-e10.md`
