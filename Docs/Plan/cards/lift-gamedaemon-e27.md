# lift-gamedaemon-e27: Easy leaves (GameDaemon): item_cpp_1, effectcontent_cpp_2, npc_cpp, effect_cpp_1, ...

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

40 functions, about 649 pseudocode lines (about 5,192 tokens). Stems: `item_cpp_1`, `effectcontent_cpp_2`, `npc_cpp`, `effect_cpp_1`, `creature_cpp_2`.

Wave E (owner order 2026-11-27: the easiest work first). Each function in this card is a leaf: its body calls no other counted function that needs a lift. Thus a `LIFT_STUB` callee cannot keep it DIFF. Each function has at most 30 pseudocode lines. Ease key: 16.2 cost per function (rule in `Docs/Plan/gamedaemon-lift.md` section 3).

Lift only the functions in the table. The other functions of these stems are in later W cards. Those cards depend on this card.

| n | Exe | RVA | PDB name | Stem | Lines | Form |
| ---: | --- | --- | --- | --- | ---: | --- |
| 1 | GD | `0x54f780` | `Item::GetSetItemCount` | item_cpp_1 | 10 | leaf |
| 2 | GD | `0x54fa40` | `Item::CheckRuleDispose` | item_cpp_1 | 13 | leaf |
| 3 | GD | `0x54faa0` | `Item::CheckSell` | item_cpp_1 | 15 | leaf |
| 4 | GD | `0x54fb10` | `Item::CheckOldItemSell` | item_cpp_1 | 18 | leaf |
| 5 | GD | `0x54fbb0` | `Item::CheckMaxDurability` | item_cpp_1 | 10 | leaf |
| 6 | GD | `0x54fbf0` | `Item::CheckWardrobeStoreable` | item_cpp_1 | 18 | leaf |
| 7 | GD | `0x54fc90` | `Item::CheckWarehouseStoreable` | item_cpp_1 | 10 | leaf |
| 8 | GD | `0x54fce0` | `Item::CheckBadgeDepositoryStoreable` | item_cpp_1 | 14 | leaf |
| 9 | GD | `0x54fed0` | `Item::checkEquipLevel` | item_cpp_1 | 24 | leaf |
| 10 | GD | `0x5501f0` | `Item::CheckTimeLimitItem` | item_cpp_1 | 10 | leaf |
| 11 | GD | `0x550230` | `Item::IsExpired` | item_cpp_1 | 7 | getter |
| 12 | GD | `0x550280` | `Item::CalculateRemainingTime` | item_cpp_1 | 14 | leaf |
| 13 | GD | `0x5502d0` | `Item::CheckStackable` | item_cpp_1 | 19 | leaf |
| 14 | GD | `0x5503c0` | `Item::IsEquipJobNone` | item_cpp_1 | 17 | leaf |
| 15 | GD | `0x550430` | `Item::CheckDepositInGuildBank` | item_cpp_1 | 24 | leaf |
| 16 | GD | `0x551380` | `Item::GetUsedGuildIdForGameLog` | item_cpp_1 | 14 | leaf |
| 17 | GD | `0x5535f0` | `WeaponItem::R_GetRandomEffectId` | item_cpp_1 | 21 | leaf |
| 18 | GD | `0x5536a0` | `WeaponItem::R_GetRandomEffectGroupId` | item_cpp_1 | 21 | leaf |
| 19 | GD | `0x5c8620` | `EmbersExplosionTimerEffect::checkApply` | effectcontent_cpp_2 | 19 | leaf |
| 20 | GD | `0x5caf40` | `DashEffect::checkApply` | effectcontent_cpp_2 | 13 | leaf |
| 21 | GD | `0x5cbea0` | `DebuffGuildBattleFieldEffect::checkApply` | effectcontent_cpp_2 | 7 | leaf |
| 22 | GD | `0x5cc380` | `OceanicEffect::checkApply` | effectcontent_cpp_2 | 10 | leaf |
| 23 | GD | `0x5cc5f0` | `FallDeathEffect::checkApply` | effectcontent_cpp_2 | 13 | leaf |
| 24 | GD | `0x5ccd90` | `DuelFighterChangeEffect::DuelFighterChangeEffect` | effectcontent_cpp_2 | 26 | leaf |
| 25 | GD | `0x5cf7c0` | `MasteryStatEquipEffect::FindBlankModifyAbility` | effectcontent_cpp_2 | 19 | leaf |
| 26 | GD | `0x5d10a0` | `SecondGaugePointEffect::checkApply` | effectcontent_cpp_2 | 21 | leaf |
| 27 | GD | `0x5d13a0` | `IntervalSecondGaugePointEffect::checkApply` | effectcontent_cpp_2 | 10 | leaf |
| 28 | GD | `0x5d1d00` | `AccumulatedDamageEffect::checkApply` | effectcontent_cpp_2 | 19 | leaf |
| 29 | GD | `0x4131c0` | `Npc::SetDespawnSocial` | npc_cpp | 11 | leaf |
| 30 | GD | `0x41a220` | `Npc::GetCombatSequence` | npc_cpp | 12 | leaf |
| 31 | GD | `0x41aa60` | `Npc::IsExpiredCombatTimer` | npc_cpp | 28 | leaf |
| 32 | GD | `0x41ba20` | `Npc::calculateAdditionalExpBonusByTestServer` | npc_cpp | 14 | leaf |
| 33 | GD | `0x5a2ec0` | `Effect::~Effect` | effect_cpp_1 | 18 | leaf |
| 34 | GD | `0x5a2f30` | `Effect::GetDataSubType` | effect_cpp_1 | 12 | leaf |
| 35 | GD | `0x5a3fd0` | `Effect::checkImmuneDebuff` | effect_cpp_1 | 29 | leaf |
| 36 | GD | `0x5a62a0` | `PassiveEffect::GetRemainDuration` | effect_cpp_1 | 14 | leaf |
| 37 | GD | `0x26fad0` | `Creature::IsJoinedFaction` | creature_cpp_2 | 29 | leaf |
| 38 | GD | `0x2712e0` | `Creature::CheckToLockMasteryLevel` | creature_cpp_2 | 12 | leaf |
| 39 | GD | `0x2749f0` | `Creature::GetActivatedBadgeEquipSlot` | creature_cpp_2 | 17 | leaf |
| 40 | GD | `0x274a10` | `Creature::IsActivatedBadgeEquipSlot` | creature_cpp_2 | 17 | leaf |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/item_cpp_1.cpp`
- `src/Server/GameDaemon/item_cpp_1.h`
- `src/Server/GameDaemon/effectcontent_cpp_2.cpp`
- `src/Server/GameDaemon/effectcontent_cpp_2.h`
- `src/Server/GameDaemon/npc_cpp.cpp`
- `src/Server/GameDaemon/npc_cpp.h`
- `src/Server/GameDaemon/effect_cpp_1.cpp`
- `src/Server/GameDaemon/effect_cpp_1.h`
- `src/Server/GameDaemon/creature_cpp_2.cpp`
- `src/Server/GameDaemon/creature_cpp_2.h`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-e27.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
