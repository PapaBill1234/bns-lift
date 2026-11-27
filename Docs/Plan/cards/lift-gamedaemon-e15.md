# lift-gamedaemon-e15: Easy leaves (GameDaemon): item_h_2, pc_h, envobj_h, npcparty_h, ...

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

40 functions, about 345 pseudocode lines (about 2,760 tokens). Stems: `item_h_2`, `pc_h`, `envobj_h`, `npcparty_h`, `zonetriggerevent_h`, `geoworld_h`.

Wave E (owner order 2026-11-27: the easiest work first). Each function in this card is a leaf: its body calls no other counted function that needs a lift. Thus a `LIFT_STUB` callee cannot keep it DIFF. Each function has at most 30 pseudocode lines. Ease key: 8.6 cost per function (rule in `Docs/Plan/gamedaemon-lift.md` section 3).

Lift only the functions in the table. The other functions of these stems are in later W cards. Those cards depend on this card.

| n | Exe | RVA | PDB name | Stem | Lines | Form |
| ---: | --- | --- | --- | --- | ---: | --- |
| 1 | GD | `0x668830` | `ItemBase<WeaponTrait>::GetFieldCount` | item_h_2 | 7 | getter |
| 2 | GD | `0x668870` | `ItemBase<AccessoryTrait>::GetPos` | item_h_2 | 7 | getter |
| 3 | GD | `0x66ba90` | `ItemBase<GroceryTrait>::GetClass` | item_h_2 | 7 | getter |
| 4 | GD | `0x66baa0` | `ItemBase<AccessoryTrait>::GetDepot` | item_h_2 | 7 | getter |
| 5 | GD | `0x66d510` | `ItemBase<GemTrait>::GetClass` | item_h_2 | 7 | getter |
| 6 | GD | `0x66d520` | `ItemBase<AccessoryTrait>::GetData` | item_h_2 | 10 | leaf |
| 7 | GD | `0x66d530` | `ItemBase<AccessoryTrait>::SetData` | item_h_2 | 13 | leaf |
| 8 | GD | `0x66ede0` | `ItemBase<AccessoryTrait>::GetDataId` | item_h_2 | 7 | getter |
| 9 | GD | `0x66edf0` | `ItemBase<AccessoryTrait>::GetClass` | item_h_2 | 7 | getter |
| 10 | GD | `0x66ee10` | `ItemBase<AccessoryTrait>::GetSequestration` | item_h_2 | 7 | leaf |
| 11 | GD | `0x97130` | `Pc::GetGuildCombatRewardDataId` | pc_h | 28 | leaf |
| 12 | GD | `0x4563d0` | `Pc::IsExceptHate` | pc_h | 7 | getter |
| 13 | GD | `0x4563e0` | `Pc::SetExceptHate` | pc_h | 7 | setter |
| 14 | GD | `0x4563f0` | `Pc::ClearLastComboSkillValue` | pc_h | 11 | leaf |
| 15 | GD | `0x456420` | `Pc::GetLastComboSkill` | pc_h | 7 | getter |
| 16 | GD | `0x456430` | `Pc::SetLastComboSkill` | pc_h | 7 | setter |
| 17 | GD | `0x456440` | `Pc::GetLastComboFireLimitTime` | pc_h | 7 | getter |
| 18 | GD | `0x456450` | `Pc::SetLastComboFireLimitTime` | pc_h | 7 | setter |
| 19 | GD | `0x456460` | `Pc::GetLastComboExecFirstLimitTime` | pc_h | 7 | getter |
| 20 | GD | `0x456470` | `Pc::SetLastComboExecFirstLimitTime` | pc_h | 7 | setter |
| 21 | GD | `0x456480` | `Pc::GetLastComboExecLastLimitTime` | pc_h | 7 | getter |
| 22 | GD | `0x456490` | `Pc::SetLastComboExecLastLimitTime` | pc_h | 7 | setter |
| 23 | GD | `0x4564a0` | `Pc::GetLastComboExecFirstResult` | pc_h | 7 | getter |
| 24 | GD | `0x4564b0` | `Pc::SetLastComboExecFirstResult` | pc_h | 7 | setter |
| 25 | GD | `0x4564c0` | `Pc::GetLastComboExecLastResult` | pc_h | 7 | getter |
| 26 | GD | `0x4564d0` | `Pc::SetLastComboExecLastResult` | pc_h | 7 | setter |
| 27 | GD | `0x4564e0` | `Pc::GetLastAttackLimitTime` | pc_h | 7 | leaf |
| 28 | GD | `0x4564f0` | `Pc::SetLastAttackLimitTime` | pc_h | 7 | leaf |
| 29 | GD | `0x456500` | `Pc::GetLastAttackedLimitTime` | pc_h | 7 | getter |
| 30 | GD | `0x456510` | `Pc::SetLastAttackedLimitTime` | pc_h | 7 | leaf |
| 31 | GD | `0x456520` | `Pc::GetSkillResultContext` | pc_h | 7 | getter |
| 32 | GD | `0x4553f0` | `Env::GetActionRadius` | envobj_h | 7 | getter |
| 33 | GD | `0x455400` | `Env::GetManipulateDuration` | envobj_h | 7 | getter |
| 34 | GD | `0x455410` | `Env::GetOwnerId` | envobj_h | 7 | getter |
| 35 | GD | `0x455430` | `AirDash::CheckToManipulate` | envobj_h | 14 | leaf |
| 36 | GD | `0x34f360` | `NpcPartyTimer::TimerExpired` | npcparty_h | 10 | leaf |
| 37 | GD | `0x6761c0` | `ZoneTriggerBossChallengeBossNpcKilledEvent::GetData` | zonetriggerevent_h | 10 | leaf |
| 38 | GD | `0x6761d0` | `ZoneTriggerNpcKilledEvent2::GetData` | zonetriggerevent_h | 10 | leaf |
| 39 | GD | `0x1d1c0` | `GeoZone::FindCell` | geoworld_h | 13 | leaf |
| 40 | GD | `0x8c440` | `GeoRegion::GetEnv` | geoworld_h | 16 | leaf |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/item_h_2.cpp`
- `src/Server/GameDaemon/item_h_2.h`
- `src/Server/GameDaemon/pc_h.cpp`
- `src/Server/GameDaemon/pc_h.h`
- `src/Server/GameDaemon/envobj_h.cpp`
- `src/Server/GameDaemon/envobj_h.h`
- `src/Server/GameDaemon/npcparty_h.cpp`
- `src/Server/GameDaemon/npcparty_h.h`
- `src/Server/GameDaemon/zonetriggerevent_h.cpp`
- `src/Server/GameDaemon/zonetriggerevent_h.h`
- `src/Server/GameDaemon/geoworld_h.cpp`
- `src/Server/GameDaemon/geoworld_h.h`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-e15.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
