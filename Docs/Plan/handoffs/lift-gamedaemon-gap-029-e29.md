# lift-gamedaemon-gap-029-e29 handoff (card lift-gamedaemon-e29)

Round 1. The driver builds, runs the gate and records the MATCH counts. This session did not build.

## Lifted (25)

### creaturejob (22)

- The caster check (`== CRASH == [creature-job-rule], invalid caster`, Log and AlertSender) in 19 bodies:
  `BladeMasterRule::OnAttackResultEvent` (0x99560), `SwordMasterRule::OnAttackResultEvent` (0x99790),
  `KungFuFighterRule::OnAttackResultEvent` (0x99bb0), `KungFuFighterRule::OnAttackedResultEvent` (0x99c00),
  `ForceMasterRule::OnAttackResultEvent` (0x99c90), `ForceMasterRule::OnAttackedResultEvent` (0x99ce0),
  `ShooterRule::OnAttackResultEvent` (0x99d30), `ShooterRule::OnAttackedResultEvent` (0x99d80),
  `DestroyerRule::OnAttackResultEvent` (0x99dd0), `SummonerRule::OnAttackedResultEvent` (0x9a1a0),
  `AssassinRule::OnAttackResultEvent` (0x9a2b0), `WarriorRule::OnAttackResultEvent` (0x9a450),
  `WarriorRule::OnAttackedResultEvent` (0x9a4a0), `ArcherRule::OnAttackResultEvent` (0x9a530),
  `ArcherRule::OnAttackedResultEvent` (0x9a580), `SpearMasterRule::OnAttackResultEvent` (0x9a670),
  `SpearMasterRule::OnAttackedResultEvent` (0x9a6c0), `ThundererRule::OnAttackResultEvent` (0x9a750),
  `ThundererRule::OnAttackedResultEvent` (0x9a7a0).
- `BladeMasterRule::CheckToChangeStance` (0x99770) and `SwordMasterRule::CheckToChangeStance` (0x999a0).
- `DestroyerRule::OnDamaged` (0x9a010): empty body.

Notes:
- The rule classes have no `CreatureJobRule` base yet. The bodies read `_caster` (+8) through the view
  `CreatureJobRuleView`. The getters read `Creature::Prop.State.sp` (+0x168) through the view `CreatureView`.
- Formtest: the original caster check has a /GS cookie (frame 0x38). The lifted form has no cookie (frame 0x28).
  The rest of the code is the same. ❓ The source of the cookie is not known. These bodies will probably stay DIFF.
- Formtest: the getter had DIFF 3 (`cmp sp, 0` / `jg` against `cmp 0, sp` / `jl`). The source now uses `0 < sp`.
  This form was not tested.
- Each lifted body has a `/INCLUDE` keep pragma with a `// LIFT:` note.

### zonebroadcast_cpp (3)

- `ZoneFieldItemNode::AddToCube` (0x25a1e0), `ZoneCampfireNode::AddToCube` (0x25a2a0), `ZoneObjectIdList::Clear` (0x25a430).
- `zonebroadcast.h` now has the PDB members of `ZoneFieldItemNode`, `ZoneCampfireNode` and `ZoneObjectIdList`.
- The bodies read `ZoneBroadcastCube::FieldItemHead` (+0x90) and `CampfireHead` (+0x98) through the view `ZoneBroadcastCubeView`.
- Each body has a `/INCLUDE` keep pragma with a `// LIFT:` note.

## Not done (15)

| RVA | Function | Reason |
| --- | --- | --- |
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
| 0x25f250 | `ZoneNpcSpawnNpcKilledEvent2::ResetContext` | Needs the `ZoneNpcSpawnEventRecord` field (pseudocode shows `record[13].subtype`), `Zone::_zoneMode` and the event layout (`_data`, `_targetNpcCount`, `_killedCount`). These are not in the repo headers. |
| 0x25f390 | `ZoneNpcSpawnNpcKilledEvent3::ResetContext` | Same as above. |
| 0x25f680 | `ZoneNpcSpawnEventManager::clear` | Needs the `ZoneNpcSpawnEvent` vtable (destructor slot 0), `_next`, `_eventListHead[2]` and the delete form (`Memory::_Manager[2]->Free`, line 425). These are not in the repo headers. |

Advice: a `Creature` layout card (PDB virtual slot order) must come before the 12 `HandleStance` callers.

## Changed files

- `src/Server/GameDaemon/creaturejob.cpp`
- `src/Server/GameDaemon/zonebroadcast.h`
- `src/Server/GameDaemon/zonebroadcast_cpp.cpp`
- `Docs/Plan/handoffs/lift-gamedaemon-gap-029-e29.md`
