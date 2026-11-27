# lift-gamedaemon-gap-008-e8 handoff (round 2)

## Lifted (37 bodies)

All `GetDefinition` getters of the card. Each body is `return &<Class>::_def;`.

- Each class header got `static ::GameTranDef _def;` after the `GetDefinition` declaration.
- Each `_h.cpp` file defines `_def` as a placeholder (`GameTranDef` is an empty struct in `GameDaemonFwd.h`). The real data (RVA of `_def` in the PDB, for example 0xE7FA70 for `LeaveWorldTran`) needs the state tables of the class. A later card must lift them.
- Each getter has a `/INCLUDE` pragma with a `// LIFT:` note. No live caller exists yet.

Files: `leaveworldtran`, `changeweaponappearancetran`, `charactermanagementtran`, `closettran`, `duelbottrainingroomtran`, `mileagedeposittran`, `npservicetran`, `lobbytokenauthtran`, `managementtran`, `marketservicetran`, `mentoringtran`, `seasoncontentstran`, `takeachievementrewardtran`, `timebasedplaytran`, `challengepartytran` (each `.h` and `_h.cpp`).

## Not done (3 bodies)

| RVA | Function | Reason |
| --- | --- | --- |
| 0x1105d0 | GameSideArenaLobbyChannel::GetId | Reads `_worldId` at offset 0x30. The skeleton class has no base and no members. The offset needs the `Channel` base layout. |
| 0x180c10 | AccountInventoryChannel::GetId | Reads `_worldId` at offset 0x28. Same reason. |
| 0x6eb460 | GameArenaChannel::GetId | The body is folded (ICF) with `DataId` of `instantpaymenttran.h` (same RVA). The class has no layout in the skeleton. |

## Files changed

The `.h` and `_h.cpp` files listed above, and this handoff file.

Gate and MATCH comparison: not run (the driver runs them).
