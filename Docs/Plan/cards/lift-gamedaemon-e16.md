# lift-gamedaemon-e16: Easy leaves (GameDaemon): item_h_1, zonetriggerevent_cpp

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
- Dead-strip: `wmain` and most callers are still `LIFT_STUB` bodies. `/OPT:REF` removes a lifted function that has no live caller, and funcdiff then cannot pair it. For each function in scope with no live caller, add `#pragma comment(linker, "/INCLUDE:<public name>")` in its `.cpp` (public names: `llvm-pdbutil dump -publics`; grep `/INCLUDE` in `Docs/Parity/lessons.md`). Do not add a pragma for a function that a lifted caller keeps.

## Scope

40 functions, about 403 pseudocode lines (about 3,224 tokens). Stems: `item_h_1`, `zonetriggerevent_cpp`.

Wave E (owner order 2026-11-27: the easiest work first). Each function in this card is a leaf: its body calls no other counted function that needs a lift. Thus a `LIFT_STUB` callee cannot keep it DIFF. Each function has at most 30 pseudocode lines. Ease key: 10.1 cost per function (rule in `Docs/Plan/gamedaemon-lift.md` section 3).

Lift only the functions in the table. The other functions of these stems are in later W cards. Those cards depend on this card.

| n | Exe | RVA | PDB name | Stem | Lines | Form |
| ---: | --- | --- | --- | --- | ---: | --- |
| 1 | GD | `0x454250` | `GetEconomyCommonItemCategory` | item_h_1 | 21 | leaf |
| 2 | GD | `0x454290` | `Item::~Item` | item_h_1 | 8 | xtor |
| 3 | GD | `0x4542d0` | `WeaponItem::SetCount` | item_h_1 | 25 | leaf |
| 4 | GD | `0x454330` | `AccessoryItem::GetExp` | item_h_1 | 7 | getter |
| 5 | GD | `0x454340` | `WeaponItem::GetMaxDurability` | item_h_1 | 7 | getter |
| 6 | GD | `0x454350` | `WeaponItem::GetDurability` | item_h_1 | 7 | getter |
| 7 | GD | `0x454360` | `AccessoryItem::GetUsed` | item_h_1 | 7 | getter |
| 8 | GD | `0x4543e0` | `WeaponItem::GetAppearanceItemDataId` | item_h_1 | 7 | getter |
| 9 | GD | `0x454420` | `WeaponItem::GetAppearanceItemLevel` | item_h_1 | 7 | getter |
| 10 | GD | `0x454460` | `WeaponItem::IsAppearanceApplied` | item_h_1 | 7 | getter |
| 11 | GD | `0x4544d0` | `WeaponItem::R_GetEnchantConsecutiveTrial` | item_h_1 | 7 | getter |
| 12 | GD | `0x454540` | `WeaponItem::R_GetEnchantCrack` | item_h_1 | 7 | getter |
| 13 | GD | `0x4545b0` | `WeaponItem::R_GetEnchantRestore` | item_h_1 | 7 | getter |
| 14 | GD | `0x4545f0` | `WeaponItem::GetTransformFailureExp` | item_h_1 | 7 | getter |
| 15 | GD | `0x454630` | `CostumeItem::SetCount` | item_h_1 | 25 | leaf |
| 16 | GD | `0x454690` | `CostumeItem::R_GetEnchantPoint` | item_h_1 | 7 | getter |
| 17 | GD | `0x4547c0` | `GroceryItem::HandleExp` | item_h_1 | 16 | leaf |
| 18 | GD | `0x454810` | `GroceryItem::GetCount` | item_h_1 | 7 | getter |
| 19 | GD | `0x4548b0` | `GroceryItem::R_GetEnchantPoint` | item_h_1 | 7 | getter |
| 20 | GD | `0x4548f0` | `GemItem::SetCount` | item_h_1 | 25 | leaf |
| 21 | GD | `0x454950` | `AccessoryItem::Locked` | item_h_1 | 7 | leaf |
| 22 | GD | `0x454960` | `AccessoryItem::GetLockExpirationTime` | item_h_1 | 7 | getter |
| 23 | GD | `0x454970` | `GemItem::R_GetEnchantPoint` | item_h_1 | 7 | getter |
| 24 | GD | `0x4549b0` | `GemItem::R_GetEnchantConsecutiveTrial` | item_h_1 | 7 | getter |
| 25 | GD | `0x454a20` | `GemItem::R_GetEnchantCrack` | item_h_1 | 7 | getter |
| 26 | GD | `0x454a90` | `GemItem::R_GetEnchantRestore` | item_h_1 | 7 | getter |
| 27 | GD | `0x454ad0` | `AccessoryItem::SetCount` | item_h_1 | 25 | leaf |
| 28 | GD | `0x454b30` | `AccessoryItem::GetLevel` | item_h_1 | 7 | getter |
| 29 | GD | `0x454b80` | `AccessoryItem::GetTimeLimitType` | item_h_1 | 7 | getter |
| 30 | GD | `0x454b90` | `AccessoryItem::GetTimeLimitExpirationTime` | item_h_1 | 7 | getter |
| 31 | GD | `0x454bd0` | `AccessoryItem::GetTransformFailureExp` | item_h_1 | 7 | getter |
| 32 | GD | `0x454be0` | `AccessoryItem::R_GetEnchantPoint` | item_h_1 | 7 | getter |
| 33 | GD | `0x454bf0` | `AccessoryItem::R_GetEnchantConsecutiveTrial` | item_h_1 | 7 | getter |
| 34 | GD | `0x454c30` | `AccessoryItem::R_GetEnchantCrack` | item_h_1 | 7 | getter |
| 35 | GD | `0x454c70` | `AccessoryItem::R_GetEnchantRestore` | item_h_1 | 7 | getter |
| 36 | GD | `0x6832d0` | `ZoneTriggerEvent::NextBranch` | zonetriggerevent_cpp | 16 | leaf |
| 37 | GD | `0x6836d0` | `ZoneTriggerNpcKilledEvent::ResetContext` | zonetriggerevent_cpp | 11 | leaf |
| 38 | GD | `0x683780` | `ZoneTriggerNpcKilledEvent2::ResetContext` | zonetriggerevent_cpp | 7 | setter |
| 39 | GD | `0x683bf0` | `ZoneTriggerBossChallengeTimeoutEvent::PostExecute` | zonetriggerevent_cpp | 14 | leaf |
| 40 | GD | `0x683dd0` | `ZoneTriggerBossChallengeRoundScoreEvent::PostExecute` | zonetriggerevent_cpp | 14 | leaf |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/item_h_1.cpp`
- `src/Server/GameDaemon/item_h_1.h`
- `src/Server/GameDaemon/zonetriggerevent_cpp.cpp`
- `src/Server/GameDaemon/zonetriggerevent_cpp.h`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-e16.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
