# lift-gamedaemon-e28: Easy leaves (GameDaemon): effectcontent_cpp_1, pc_cpp_2, zone_cpp_2, zonetimer_cpp, ...

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

40 functions, about 738 pseudocode lines (about 5,904 tokens). Stems: `effectcontent_cpp_1`, `pc_cpp_2`, `zone_cpp_2`, `zonetimer_cpp`, `inventory_cpp_1`, `worldserializedobject_cpp`, `npcspawn_cpp`.

Wave E (owner order 2026-11-27: the easiest work first). Each function in this card is a leaf: its body calls no other counted function that needs a lift. Thus a `LIFT_STUB` callee cannot keep it DIFF. Each function has at most 30 pseudocode lines. Ease key: 18.4 cost per function (rule in `Docs/Plan/gamedaemon-lift.md` section 3).

Lift only the functions in the table. The other functions of these stems are in later W cards. Those cards depend on this card.

| n | Exe | RVA | PDB name | Stem | Lines | Form |
| ---: | --- | --- | --- | --- | ---: | --- |
| 1 | GD | `0x5b76f0` | `AttackPassiveEffect::checkApply` | effectcontent_cpp_1 | 29 | leaf |
| 2 | GD | `0x5b8250` | `HpDamageEffect::checkApply` | effectcontent_cpp_1 | 10 | leaf |
| 3 | GD | `0x5b8590` | `GuardGaugeHealEffect::checkApply` | effectcontent_cpp_1 | 17 | leaf |
| 4 | GD | `0x5b86f0` | `GuardGaugeDamageEffect::checkApply` | effectcontent_cpp_1 | 17 | leaf |
| 5 | GD | `0x5b8ab0` | `CastCancelEffect::apply` | effectcontent_cpp_1 | 25 | leaf |
| 6 | GD | `0x5bca00` | `InitializeRecycleGroupEffect::checkApply` | effectcontent_cpp_1 | 10 | leaf |
| 7 | GD | `0x5be900` | `ExtendLinkEffect::checkApply` | effectcontent_cpp_1 | 13 | leaf |
| 8 | GD | `0x5bf3e0` | `AdditionalHpEffect::checkApply` | effectcontent_cpp_1 | 10 | leaf |
| 9 | GD | `0x5bf4d0` | `DesireIncreaseEffect::checkApply` | effectcontent_cpp_1 | 20 | leaf |
| 10 | GD | `0x5bf850` | `DifficultyTypeDispelAttributeHpDamageEffect::checkApply` | effectcontent_cpp_1 | 11 | leaf |
| 11 | GD | `0x5c4bb0` | `ProvocationEffect::checkApply` | effectcontent_cpp_1 | 19 | leaf |
| 12 | GD | `0x5c5530` | `TransitEffect::TransitEffect` | effectcontent_cpp_1 | 28 | leaf |
| 13 | GD | `0x5c5de0` | `ReturnSimSkillEffect::checkApply` | effectcontent_cpp_1 | 10 | leaf |
| 14 | GD | `0x5c5e00` | `ReturnSimSkillEffect::apply` | effectcontent_cpp_1 | 28 | leaf |
| 15 | GD | `0x5c6200` | `ModifyRecycleTimeEffect::checkApply` | effectcontent_cpp_1 | 25 | leaf |
| 16 | GD | `0x5c65d0` | `SetImmuneBreakerEffect::checkApply` | effectcontent_cpp_1 | 7 | leaf |
| 17 | GD | `0x5e6a90` | `Pc::IsSharableCombatModeZone` | pc_cpp_2 | 14 | leaf |
| 18 | GD | `0x5ea0d0` | `Pc::GetActiveSummoned` | pc_cpp_2 | 16 | leaf |
| 19 | GD | `0x5eb2e0` | `Pc::Send` | pc_cpp_2 | 24 | leaf |
| 20 | GD | `0x5eb350` | `Pc::Send` | pc_cpp_2 | 26 | leaf |
| 21 | GD | `0x5eb3c0` | `Pc::Send` | pc_cpp_2 | 24 | leaf |
| 22 | GD | `0x5eb420` | `Pc::Send` | pc_cpp_2 | 26 | leaf |
| 23 | GD | `0x5ed820` | `Pc::ReturningToArenaLobby` | pc_cpp_2 | 17 | leaf |
| 24 | GD | `0x5ed880` | `Pc::RollbackReturnToArenaLobby` | pc_cpp_2 | 9 | leaf |
| 25 | GD | `0x5edae0` | `Pc::SetGameGameMode` | pc_cpp_2 | 9 | leaf |
| 26 | GD | `0x5edb30` | `Pc::GetGameGameMode` | pc_cpp_2 | 15 | leaf |
| 27 | GD | `0x5ee6b0` | `Pc::GetArenaAttraction` | pc_cpp_2 | 15 | leaf |
| 28 | GD | `0x5f0f00` | `Pc::SetIpAddress` | pc_cpp_2 | 29 | leaf |
| 29 | GD | `0x24ae90` | `Zone::GetTickTime` | zone_cpp_2 | 19 | leaf |
| 30 | GD | `0x260170` | `ZoneSerializer::preExecute` | zonetimer_cpp | 19 | leaf |
| 31 | GD | `0x4be600` | `InventoryClientUpdate::InventoryClientUpdate` | inventory_cpp_1 | 29 | leaf |
| 32 | GD | `0x4be900` | `InventoryClientUpdate::Send` | inventory_cpp_1 | 20 | leaf |
| 33 | GD | `0x4bea20` | `InventoryCacheUpdate::AddChange` | inventory_cpp_1 | 3 | empty |
| 34 | GD | `0x4bec40` | `Inventory::IsActivatedGemSlot` | inventory_cpp_1 | 18 | leaf |
| 35 | GD | `0x4bed10` | `Inventory::GetCacheId` | inventory_cpp_1 | 24 | leaf |
| 36 | GD | `0x4c10d0` | `Inventory::GetItemClass` | inventory_cpp_1 | 28 | leaf |
| 37 | GD | `0x4cfcc0` | `Inventory::Dispose` | inventory_cpp_1 | 11 | leaf |
| 38 | GD | `0x67a7e0` | `GuildCraftWSO::writeError` | worldserializedobject_cpp | 19 | leaf |
| 39 | GD | `0x429730` | `NpcSpawn::GetNpc` | npcspawn_cpp | 24 | leaf |
| 40 | GD | `0x429780` | `NpcSpawn::getNpcPos` | npcspawn_cpp | 21 | leaf |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/effectcontent_cpp_1.cpp`
- `src/Server/GameDaemon/effectcontent_cpp_1.h`
- `src/Server/GameDaemon/pc_cpp_2.cpp`
- `src/Server/GameDaemon/pc_cpp_2.h`
- `src/Server/GameDaemon/zone_cpp_2.cpp`
- `src/Server/GameDaemon/zone_cpp_2.h`
- `src/Server/GameDaemon/zonetimer_cpp.cpp`
- `src/Server/GameDaemon/zonetimer_cpp.h`
- `src/Server/GameDaemon/inventory_cpp_1.cpp`
- `src/Server/GameDaemon/inventory_cpp_1.h`
- `src/Server/GameDaemon/worldserializedobject_cpp.cpp`
- `src/Server/GameDaemon/worldserializedobject_cpp.h`
- `src/Server/GameDaemon/npcspawn_cpp.cpp`
- `src/Server/GameDaemon/npcspawn_cpp.h`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-e28.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
