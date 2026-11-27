# lift-gamedaemon-gap-031-e31 handoff

## Lifted

- `effect_cpp_2`: `EffectContainer::newIndex` (0x5b03c0), `EffectList::EffectList` (0x5b4870), `EffectList::Clear` (0x5b49f0).
- `creature_h`: the five `ApplySkillModifyInfo::Calc*` functions (0x453650, 0x4536f0, 0x453740, 0x4537e0, 0x453880).

## Not done

- `EffectFactory::CreateEffect` (0x5b37f0): the Hex-Rays cache has no pseudocode for this function (the entry is `None`). The body is 0x180 bytes, not empty. The stub stays.

## Changed files

- `src/Server/GameDaemon/GameDaemonFwd.h`
- `src/Server/GameDaemon/campfire.h`
- `src/Server/GameDaemon/creature.h`
- `src/Server/GameDaemon/creature_h.cpp`
- `src/Server/GameDaemon/effect.h`
- `src/Server/GameDaemon/effect_cpp_2.cpp`
- `src/Server/GameDaemon/fielditem.h`
- `src/Server/GameDaemon/zone.h`
