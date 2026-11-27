# lift-gamedaemon-e29: Easy leaves (GameDaemon): creaturejob, zonebroadcast_cpp, zonenpcspawnevent

| Item | Value |
| --- | --- |
| Exe | GD |
| Source build | GameDaemon 2019 + PDB (VS2010 SP1) |
| Exe file | `<work-root>/ida/lift/GameDaemon/GameDaemon.exe` |
| PDB | `<work-root>/ida/lift/GameDaemon/GameDaemon.pdb` |
| Pseudocode | `~/.cache/bns-lift/hr/GameDaemon/<stem>.c` |
| Pseudocode index | `~/.cache/bns-lift/hr/GameDaemon/index.tsv` (stem, rva, name, first, last, status, source file, part) |
| Wave | E |
| Model | opus |
| Depends on | `lift-gamedaemon-0e` |
| Pattern | none |
| Plan | `Docs/Plan/gamedaemon-lift.md` sections 1, 3, 5 |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Grep `Docs/Parity/lessons.md` for A2 (block order), A6 (per-exe path literals), A12 (PDB member types), A18 (destructors), A21 (PDB facts) and A22 (per-exe source form). Do not read it in full.
- Pattern: none. No lifted file has the same role.

## Scope

40 functions, about 745 pseudocode lines (about 5,960 tokens). Stems: `creaturejob`, `zonebroadcast_cpp`, `zonenpcspawnevent`.

Wave E (owner order 2026-11-27: the easiest work first). Each function in this card is a leaf: its body calls no other counted function that needs a lift. Thus a `LIFT_STUB` callee cannot keep it DIFF. Each function has at most 30 pseudocode lines. Ease key: 18.6 cost per function (rule in `Docs/Plan/gamedaemon-lift.md` section 3).

Lift only the functions in the table. The other functions of these stems are in later W cards. Those cards depend on this card.

| n | Exe | RVA | PDB name | Stem | Lines | Form |
| ---: | --- | --- | --- | --- | ---: | --- |
| 1 | GD | `0x99560` | `BladeMasterRule::OnAttackResultEvent` | creaturejob | 22 | leaf |
| 2 | GD | `0x996f0` | `BladeMasterRule::OnPointZero` | creaturejob | 19 | leaf |
| 3 | GD | `0x99730` | `BladeMasterRule::OnCombatModeChanged` | creaturejob | 16 | leaf |
| 4 | GD | `0x99770` | `BladeMasterRule::CheckToChangeStance` | creaturejob | 7 | getter |
| 5 | GD | `0x99790` | `SwordMasterRule::OnAttackResultEvent` | creaturejob | 22 | leaf |
| 6 | GD | `0x99920` | `SwordMasterRule::OnPointZero` | creaturejob | 19 | leaf |
| 7 | GD | `0x99960` | `SwordMasterRule::OnCombatModeChanged` | creaturejob | 16 | leaf |
| 8 | GD | `0x999a0` | `SwordMasterRule::CheckToChangeStance` | creaturejob | 7 | getter |
| 9 | GD | `0x99bb0` | `KungFuFighterRule::OnAttackResultEvent` | creaturejob | 22 | leaf |
| 10 | GD | `0x99c00` | `KungFuFighterRule::OnAttackedResultEvent` | creaturejob | 22 | leaf |
| 11 | GD | `0x99c50` | `KungFuFighterRule::OnCombatModeChanged` | creaturejob | 16 | leaf |
| 12 | GD | `0x99c90` | `ForceMasterRule::OnAttackResultEvent` | creaturejob | 22 | leaf |
| 13 | GD | `0x99ce0` | `ForceMasterRule::OnAttackedResultEvent` | creaturejob | 22 | leaf |
| 14 | GD | `0x99d30` | `ShooterRule::OnAttackResultEvent` | creaturejob | 22 | leaf |
| 15 | GD | `0x99d80` | `ShooterRule::OnAttackedResultEvent` | creaturejob | 22 | leaf |
| 16 | GD | `0x99dd0` | `DestroyerRule::OnAttackResultEvent` | creaturejob | 22 | leaf |
| 17 | GD | `0x9a010` | `DestroyerRule::OnDamaged` | creaturejob | 7 | leaf |
| 18 | GD | `0x9a040` | `DestroyerRule::OnCombatModeChanged` | creaturejob | 16 | leaf |
| 19 | GD | `0x9a1a0` | `SummonerRule::OnAttackedResultEvent` | creaturejob | 22 | leaf |
| 20 | GD | `0x9a2b0` | `AssassinRule::OnAttackResultEvent` | creaturejob | 22 | leaf |
| 21 | GD | `0x9a3d0` | `AssassinRule::OnCombatModeChanged` | creaturejob | 16 | leaf |
| 22 | GD | `0x9a410` | `SoulFighterRule::OnCombatModeChanged` | creaturejob | 14 | leaf |
| 23 | GD | `0x9a450` | `WarriorRule::OnAttackResultEvent` | creaturejob | 22 | leaf |
| 24 | GD | `0x9a4a0` | `WarriorRule::OnAttackedResultEvent` | creaturejob | 22 | leaf |
| 25 | GD | `0x9a4f0` | `WarriorRule::OnCombatModeChanged` | creaturejob | 14 | leaf |
| 26 | GD | `0x9a530` | `ArcherRule::OnAttackResultEvent` | creaturejob | 22 | leaf |
| 27 | GD | `0x9a580` | `ArcherRule::OnAttackedResultEvent` | creaturejob | 22 | leaf |
| 28 | GD | `0x9a600` | `ArcherRule::OnCombatModeChanged` | creaturejob | 14 | leaf |
| 29 | GD | `0x9a670` | `SpearMasterRule::OnAttackResultEvent` | creaturejob | 22 | leaf |
| 30 | GD | `0x9a6c0` | `SpearMasterRule::OnAttackedResultEvent` | creaturejob | 22 | leaf |
| 31 | GD | `0x9a710` | `SpearMasterRule::OnCombatModeChanged` | creaturejob | 14 | leaf |
| 32 | GD | `0x9a750` | `ThundererRule::OnAttackResultEvent` | creaturejob | 22 | leaf |
| 33 | GD | `0x9a7a0` | `ThundererRule::OnAttackedResultEvent` | creaturejob | 22 | leaf |
| 34 | GD | `0x9a7f0` | `ThundererRule::OnCombatModeChanged` | creaturejob | 14 | leaf |
| 35 | GD | `0x25a1e0` | `ZoneFieldItemNode::AddToCube` | zonebroadcast_cpp | 15 | leaf |
| 36 | GD | `0x25a2a0` | `ZoneCampfireNode::AddToCube` | zonebroadcast_cpp | 15 | leaf |
| 37 | GD | `0x25a430` | `ZoneObjectIdList::Clear` | zonebroadcast_cpp | 29 | leaf |
| 38 | GD | `0x25f250` | `ZoneNpcSpawnNpcKilledEvent2::ResetContext` | zonenpcspawnevent | 19 | leaf |
| 39 | GD | `0x25f390` | `ZoneNpcSpawnNpcKilledEvent3::ResetContext` | zonenpcspawnevent | 14 | leaf |
| 40 | GD | `0x25f680` | `ZoneNpcSpawnEventManager::clear` | zonenpcspawnevent | 26 | leaf |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/creaturejob.cpp`
- `src/Server/GameDaemon/creaturejob.h`
- `src/Server/GameDaemon/zonebroadcast_cpp.cpp`
- `src/Server/GameDaemon/zonebroadcast_cpp.h`
- `src/Server/GameDaemon/zonenpcspawnevent.cpp`
- `src/Server/GameDaemon/zonenpcspawnevent.h`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-e29.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
