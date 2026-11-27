# lift-gamedaemon-e17: Easy leaves (GameDaemon): gamedaemon_h, effect_h, envobj_cpp, inventory_h, ...

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

40 functions, about 564 pseudocode lines (about 4,512 tokens). Stems: `gamedaemon_h`, `effect_h`, `envobj_cpp`, `inventory_h`, `inventory_cpp_2`.

Wave E (owner order 2026-11-27: the easiest work first). Each function in this card is a leaf: its body calls no other counted function that needs a lift. Thus a `LIFT_STUB` callee cannot keep it DIFF. Each function has at most 30 pseudocode lines. Ease key: 14.1 cost per function (rule in `Docs/Plan/gamedaemon-lift.md` section 3).

Lift only the functions in the table. The other functions of these stems are in later W cards. Those cards depend on this card.

| n | Exe | RVA | PDB name | Stem | Lines | Form |
| ---: | --- | --- | --- | --- | ---: | --- |
| 1 | GD | `0x27f80` | `GameDaemon::IsArenaDaemon` | gamedaemon_h | 10 | leaf |
| 2 | GD | `0x27fb0` | `GameDaemon::IsArenaDungeonDaemon` | gamedaemon_h | 10 | leaf |
| 3 | GD | `0x971d0` | `GameDaemon::GetRankingResult` | gamedaemon_h | 26 | leaf |
| 4 | GD | `0x1107f0` | `GameDaemon::IsArenaEnabledGameDaemon` | gamedaemon_h | 10 | leaf |
| 5 | GD | `0x180e10` | `GameDaemon::SetEventReplyCacheHello` | gamedaemon_h | 10 | leaf |
| 6 | GD | `0x1ee590` | `TimeBasedPlaySeasonSchedule::Rule::Rule` | gamedaemon_h | 11 | xtor |
| 7 | GD | `0x1ee6f0` | `GameDaemon::ShortName` | gamedaemon_h | 7 | getter |
| 8 | GD | `0x1ee700` | `GameDaemon::Name` | gamedaemon_h | 7 | getter |
| 9 | GD | `0x1ee710` | `GameDaemon::GetTimerInterval` | gamedaemon_h | 7 | getter |
| 10 | GD | `0x453a20` | `Effect::Initialize2` | effect_h | 16 | leaf |
| 11 | GD | `0x453a60` | `Effect::Initialize3` | effect_h | 16 | leaf |
| 12 | GD | `0x453aa0` | `Effect::Initialize4` | effect_h | 16 | leaf |
| 13 | GD | `0x453ae0` | `Effect::Initialize5` | effect_h | 16 | leaf |
| 14 | GD | `0x453b20` | `PassiveEffect::GetDbIndex` | effect_h | 7 | getter |
| 15 | GD | `0x453b30` | `PassiveEffect::GetStackCount` | effect_h | 7 | getter |
| 16 | GD | `0x453b40` | `ControlledCreatureEffectSlot::GetEffectSlotList` | effect_h | 12 | leaf |
| 17 | GD | `0x453b60` | `EffectContainer::IsBroadcastSlot` | effect_h | 21 | leaf |
| 18 | GD | `0x597520` | `Env::SetSession` | envobj_cpp | 16 | leaf |
| 19 | GD | `0x597560` | `Env::OnTimer` | envobj_cpp | 14 | leaf |
| 20 | GD | `0x598260` | `Env::IsQuestEnv` | envobj_cpp | 26 | leaf |
| 21 | GD | `0x599240` | `Env::GetPos` | envobj_cpp | 15 | leaf |
| 22 | GD | `0x599280` | `Env::GetActionPoint` | envobj_cpp | 8 | leaf |
| 23 | GD | `0x5992b0` | `Env::GetManipulationCylinder` | envobj_cpp | 11 | leaf |
| 24 | GD | `0x599f20` | `Env::IsMoveBlock` | envobj_cpp | 7 | leaf |
| 25 | GD | `0x59a410` | `Env::CheckToLoot` | envobj_cpp | 7 | getter |
| 26 | GD | `0x59add0` | `Refiner::CheckToGiveFactionScore` | envobj_cpp | 15 | leaf |
| 27 | GD | `0x59c190` | `ControlPoint::Manipulate` | envobj_cpp | 29 | leaf |
| 28 | GD | `0x59c310` | `ControlPoint::CancelOccupation` | envobj_cpp | 20 | leaf |
| 29 | GD | `0x59c430` | `MultipleLoop::Manipulate` | envobj_cpp | 27 | leaf |
| 30 | GD | `0x59c9e0` | `Portal::GetPos` | envobj_cpp | 17 | leaf |
| 31 | GD | `0x59ca30` | `Portal::GetActionPoint` | envobj_cpp | 10 | leaf |
| 32 | GD | `0x59ca70` | `Portal::GetActionRadius` | envobj_cpp | 10 | leaf |
| 33 | GD | `0x59ca90` | `Portal::GetManipulationCylinder` | envobj_cpp | 13 | leaf |
| 34 | GD | `0x59fcf0` | `OceanicRegion::ApplyEffect` | envobj_cpp | 3 | empty |
| 35 | GD | `0x59fef0` | `OceanicRegion::OnTimer` | envobj_cpp | 26 | leaf |
| 36 | GD | `0x5a0020` | `FallDeathRegion::ApplyEffect` | envobj_cpp | 3 | empty |
| 37 | GD | `0x5a01f0` | `FallDeathRegion::OnTimer` | envobj_cpp | 26 | leaf |
| 38 | GD | `0x34f000` | `Inventory::GetEmptyBagSlotCount` | inventory_h | 16 | leaf |
| 39 | GD | `0x504a60` | `Inventory::setUsed` | inventory_cpp_2 | 20 | leaf |
| 40 | GD | `0x507920` | `Inventory::CheckTradeSuggestion` | inventory_cpp_2 | 16 | leaf |

Same name in a lifted exe (a different body is possible): `TimeBasedPlaySeasonSchedule::Rule::Rule` (LobbyDaemon).

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/gamedaemon_h.cpp`
- `src/Server/GameDaemon/gamedaemon_h.h`
- `src/Server/GameDaemon/effect_h.cpp`
- `src/Server/GameDaemon/effect_h.h`
- `src/Server/GameDaemon/envobj_cpp.cpp`
- `src/Server/GameDaemon/envobj_cpp.h`
- `src/Server/GameDaemon/inventory_h.cpp`
- `src/Server/GameDaemon/inventory_h.h`
- `src/Server/GameDaemon/inventory_cpp_2.cpp`
- `src/Server/GameDaemon/inventory_cpp_2.h`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-e17.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
