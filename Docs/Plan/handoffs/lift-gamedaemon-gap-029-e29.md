# lift-gamedaemon-gap-029-e29 handoff (card lift-gamedaemon-e29)

Round 2 (repair of review rejects). The driver builds, runs the gate and records the MATCH counts. This session did not build.

## Repair actions

- The review rejected 4 bodies. Each one is now its skeleton `LIFT_STUB` body again, and its `/INCLUDE` keep pragma is gone.
- The caster check in creaturejob calls `Log::Write` and `AlertSender::Write`. All 19 caster-check bodies are now `LIFT_STUB` again (log path, E16). Their pragmas are gone.
- The caster-check macro, the `CreatureJobRuleView` and `CreatureView` views and the `Log.h` / `AlertSender.h` includes are gone from `creaturejob.cpp`.
- The accepted bodies did not change.

## Lifted (4)

### creaturejob (1)

- `DestroyerRule::OnDamaged` (0x9a010): empty body. It has a `/INCLUDE` keep pragma with a `// LIFT:` note.

### zonebroadcast_cpp (3)

- `ZoneFieldItemNode::AddToCube` (0x25a1e0), `ZoneCampfireNode::AddToCube` (0x25a2a0), `ZoneObjectIdList::Clear` (0x25a430).
- `zonebroadcast.h` has the PDB members of `ZoneFieldItemNode`, `ZoneCampfireNode` and `ZoneObjectIdList`.
- Each body has a `/INCLUDE` keep pragma with a `// LIFT:` note.

## Not done (36)

| RVA | Function | Reason |
| --- | --- | --- |
| 0x99560 | `BladeMasterRule::OnAttackResultEvent` | Review reject (P1_calls, P3_imm). Also log path (E16). |
| 0x99790 | `SwordMasterRule::OnAttackResultEvent` | Review reject (P1_calls, P3_imm). Also log path (E16). |
| 0x99770 | `BladeMasterRule::CheckToChangeStance` | Review reject (P2_cc, P9_ret_width). |
| 0x999a0 | `SwordMasterRule::CheckToChangeStance` | Review reject (P2_cc, P9_ret_width). |
| 0x99bb0 | `KungFuFighterRule::OnAttackResultEvent` | log path (E16) |
| 0x99c00 | `KungFuFighterRule::OnAttackedResultEvent` | log path (E16) |
| 0x99c90 | `ForceMasterRule::OnAttackResultEvent` | log path (E16) |
| 0x99ce0 | `ForceMasterRule::OnAttackedResultEvent` | log path (E16) |
| 0x99d30 | `ShooterRule::OnAttackResultEvent` | log path (E16) |
| 0x99d80 | `ShooterRule::OnAttackedResultEvent` | log path (E16) |
| 0x99dd0 | `DestroyerRule::OnAttackResultEvent` | log path (E16) |
| 0x9a1a0 | `SummonerRule::OnAttackedResultEvent` | log path (E16) |
| 0x9a2b0 | `AssassinRule::OnAttackResultEvent` | log path (E16) |
| 0x9a450 | `WarriorRule::OnAttackResultEvent` | log path (E16) |
| 0x9a4a0 | `WarriorRule::OnAttackedResultEvent` | log path (E16) |
| 0x9a530 | `ArcherRule::OnAttackResultEvent` | log path (E16) |
| 0x9a580 | `ArcherRule::OnAttackedResultEvent` | log path (E16) |
| 0x9a670 | `SpearMasterRule::OnAttackResultEvent` | log path (E16) |
| 0x9a6c0 | `SpearMasterRule::OnAttackedResultEvent` | log path (E16) |
| 0x9a750 | `ThundererRule::OnAttackResultEvent` | log path (E16) |
| 0x9a7a0 | `ThundererRule::OnAttackedResultEvent` | log path (E16) |
| 0x996f0 | `BladeMasterRule::OnPointZero` | Calls the virtual `Creature::HandleStance` (PDB slot 68). `creature.h` does not declare the virtual functions in PDB slot order. |
| 0x99730 | `BladeMasterRule::OnCombatModeChanged` | Same as above (`HandleStance`, slot 68). |
| 0x99920 | `SwordMasterRule::OnPointZero` | Same as above. |
| 0x99960 | `SwordMasterRule::OnCombatModeChanged` | Same as above. |
| 0x99c50 | `KungFuFighterRule::OnCombatModeChanged` | Same as above. |
| 0x9a040 | `DestroyerRule::OnCombatModeChanged` | Same as above. |
| 0x9a3d0 | `AssassinRule::OnCombatModeChanged` | Same as above. |
| 0x9a410 | `SoulFighterRule::OnCombatModeChanged` | Same as above. |
| 0x9a4f0 | `WarriorRule::OnCombatModeChanged` | Same as above. |
| 0x9a600 | `ArcherRule::OnCombatModeChanged` | Same as above. |
| 0x9a710 | `SpearMasterRule::OnCombatModeChanged` | Same as above. |
| 0x9a7f0 | `ThundererRule::OnCombatModeChanged` | Same as above. |
| 0x25f250 | `ZoneNpcSpawnNpcKilledEvent2::ResetContext` | Needs the `ZoneNpcSpawnEventRecord` field, `Zone::_zoneMode` and the event layout (`_data`, `_targetNpcCount`, `_killedCount`). These are not in the repo headers. |
| 0x25f390 | `ZoneNpcSpawnNpcKilledEvent3::ResetContext` | Same as above. |
| 0x25f680 | `ZoneNpcSpawnEventManager::clear` | Needs the `ZoneNpcSpawnEvent` vtable (destructor slot 0), `_next`, `_eventListHead[2]` and the delete form. These are not in the repo headers. |

Advice: a `Creature` layout card (PDB virtual slot order) must come before the 12 `HandleStance` callers. The caster-check bodies must wait until E16 is closed.

## Changed files

- `src/Server/GameDaemon/creaturejob.cpp`
- `src/Server/GameDaemon/zonebroadcast.h`
- `src/Server/GameDaemon/zonebroadcast_cpp.cpp`
- `Docs/Plan/handoffs/lift-gamedaemon-gap-029-e29.md`
