# Handoff: lift-gamedaemon-gap-020-e20 (round 1)

Easy leaves (GameDaemon). The driver builds, runs the gate and records the MATCH counts. This session did not build.

## Lifted (36 of 40)

- `arenaroommanager_h`: 0x27b20, 0x27b30, 0x27b40, 0x27b50, 0x27b80, 0x27ba0, 0x66a1a0.
- `publicraid_h`: 0x35e90, 0x180e50, 0x180e60.
- `actsequenceloader_h`: 0x35f50, 0x3fee30.
- `bosscombatsequence`: 0x77d70.
- `bannedwordfiltermemorymanager`: 0x33a160, 0x33a170, 0x616fa0.
- `contribution_h`: 0x8c2a0, 0x455480, 0x4554a0.
- `arenalobbycommon`: 0x49390, 0x493a0, 0x493b0.
- `brainraidboss_h`: 0x634a0, 0x634b0.
- `summoned_cpp`: 0x611b20, 0x611b50, 0x611d60, 0x611d90, 0x611dc0, 0x611df0, 0x611e20, 0x611e50, 0x611e80, 0x615250, 0x616f10, 0x616f50.

## Decisions

- `Summoned` now has a partial PDB layout. A `LiftBytes` private base holds +8 to +0x19FF (base `ControlledCreature` and `_data`, `_levelData`, `_summonedEntry`). The class declares `_master` (+0x1A00) to `_combatStartTime` (+0x1A20). `_history` and `_historyItems` are not declared yet.
- `Summoned::SummonedState` is an empty enum. Its enumerators are not declared yet.
- The `Summoned` forwarders call the `Pc` virtual functions. The skeleton vftable slot order of `Pc` is not the PDB order yet. Thus these bodies can stay DIFF until a later card fixes the `Pc` vftable.
- The new `Summoned` bodies have no live caller. They have `/INCLUDE` dead-strip pragmas with a `// LIFT:` note.

## Not done

- `ArenaLobbyRoomUtil::IsPreserveSessionInArenaEnable` (0x49900): the body reads `GameDaemon::GamedInstance->ruleConfig`. The skeleton has no `GameDaemon` layout and no `RuleConfig` members yet.
- `CaptureTheFlag::getRatingRevise` (0x654e0): the body reads `Data::DataManager::Instance->_loaderDefs[6].table` and calls a table vftable slot. `Data::DataManager` is only a forward declaration in the skeleton.
- `SummonedManager::GetPc` (0x615b30): the body reads `Creature::Id` (+0x28) and `Summoned::_master`. The skeleton `Creature` has no layout and no relation to `Summoned` yet.
- `Summoned::changeMoveState` (0x616c30): the body calls `Log::Write` and reads `Creature::moveCtx` (+0x8C8). The GameDaemon form of `Log::Write` is not available yet (shared card), and `Summoned` does not declare its `Creature` base.

## Files changed

- `src/Server/GameDaemon/actsequenceloader_h.cpp`
- `src/Server/GameDaemon/arenalobbycommon.cpp`
- `src/Server/GameDaemon/arenaroommanager.h`
- `src/Server/GameDaemon/arenaroommanager_h.cpp`
- `src/Server/GameDaemon/bannedwordfiltermemorymanager.cpp`
- `src/Server/GameDaemon/bosscombatsequence.cpp`
- `src/Server/GameDaemon/bosscombatsequence.h`
- `src/Server/GameDaemon/brainconst.h`
- `src/Server/GameDaemon/brainraidboss.h`
- `src/Server/GameDaemon/brainraidboss_h.cpp`
- `src/Server/GameDaemon/contribution.h`
- `src/Server/GameDaemon/contribution_h.cpp`
- `src/Server/GameDaemon/publicraid.h`
- `src/Server/GameDaemon/publicraid_h.cpp`
- `src/Server/GameDaemon/summoned.h`
- `src/Server/GameDaemon/summoned_cpp.cpp`
- `Docs/Plan/handoffs/lift-gamedaemon-gap-020-e20.md`

## Gate and MATCH

The driver runs the gate and the MATCH comparison after this session. This session did not build. It did not run the gate or funcdiff.
