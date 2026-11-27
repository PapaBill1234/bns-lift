# lift-gamedaemon-28: Packet game log: gamelog_4 part 1/5

| Item | Value |
| --- | --- |
| Exe | GD |
| Source build | GameDaemon 2019 + PDB (VS2010 SP1) |
| Exe file | `<work-root>/ida/lift/GameDaemon/GameDaemon.exe` |
| PDB | `<work-root>/ida/lift/GameDaemon/GameDaemon.pdb` |
| Pseudocode | `~/.cache/bns-lift/hr/GameDaemon/<stem>.c` |
| Pseudocode index | `~/.cache/bns-lift/hr/GameDaemon/index.tsv` (stem, rva, name, first, last, status, source file, part) |
| Wave | W1 |
| Model | sonnet:high |
| Depends on | `lift-gamedaemon-12`, `lift-gamedaemon-13` |
| Pattern | `src/Server/GameDaemon/gamelog_1.cpp` |
| Plan | `Docs/Plan/gamedaemon-lift.md` sections 1, 3, 5 |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Grep `Docs/Parity/lessons.md` for A2 (block order), A6 (per-exe path literals), A12 (PDB member types), A18 (destructors), A21 (PDB facts) and A22 (per-exe source form). Do not read it in full.
- Pattern: `src/Server/GameDaemon/gamelog_1.cpp`. Read it one time. Use its form for the functions of this card.
  The pattern is the output of `lift-gamedaemon-13`. Use the same form for each function: the functions in this group have one layout.
- Dead-strip: `wmain` and most callers are still `LIFT_STUB` bodies. `/OPT:REF` removes a lifted function that has no live caller, and funcdiff then cannot pair it. For each function in scope with no live caller, add `#pragma comment(linker, "/INCLUDE:<public name>")` in its `.cpp` (public names: `llvm-pdbutil dump -publics`; grep `/INCLUDE` in `Docs/Parity/lessons.md`). Do not add a pragma for a function that a lifted caller keeps.

## Scope

23 functions, about 2,467 pseudocode lines (about 19,736 tokens). Stems: `gamelog_4`.

This card is part 1/5 of stem `gamelog_4`. The other parts are in other cards of this wave. They run one after the other (column "Depends on"). Edit only the functions in this table.

| n | Exe | RVA | PDB name | Stem | Lines |
| ---: | --- | --- | --- | --- | ---: |
| 1 | GD | `0x43cf70` | `GameLog::ConsumeItemByDecompose` | gamelog_4 | 104 |
| 2 | GD | `0x43d330` | `GameLog::ConsumeItemByDischarge` | gamelog_4 | 102 |
| 3 | GD | `0x43d6e0` | `GameLog::GrowUpItem` | gamelog_4 | 111 |
| 4 | GD | `0x43db00` | `GameLog::ConsumeMaterialByGrowth` | gamelog_4 | 109 |
| 5 | GD | `0x43df00` | `GameLog::GetTransformedItem` | gamelog_4 | 105 |
| 6 | GD | `0x43e2f0` | `GameLog::ConsumeItemByTransform` | gamelog_4 | 112 |
| 7 | GD | `0x43e730` | `GameLog::ResultOfTransform` | gamelog_4 | 110 |
| 8 | GD | `0x43eb40` | `GameLog::ItemExceedLimit` | gamelog_4 | 111 |
| 9 | GD | `0x43ef50` | `GameLog::ConsumeMaterialByExceedLimit` | gamelog_4 | 109 |
| 10 | GD | `0x43f350` | `GameLog::DeleteGemSlot` | gamelog_4 | 107 |
| 11 | GD | `0x43f750` | `GameLog::ConsumeItemByDelSlot` | gamelog_4 | 106 |
| 12 | GD | `0x43fb30` | `GameLog::SealItem` | gamelog_4 | 106 |
| 13 | GD | `0x43ff10` | `GameLog::ConsumeItemBySeal` | gamelog_4 | 106 |
| 14 | GD | `0x4402f0` | `GameLog::GetSealedItem` | gamelog_4 | 103 |
| 15 | GD | `0x4406a0` | `GameLog::GetUnsealedItem` | gamelog_4 | 108 |
| 16 | GD | `0x440a90` | `GameLog::ConsumeItemByUnseal` | gamelog_4 | 105 |
| 17 | GD | `0x440e60` | `GameLog::PetDurabilityCharge` | gamelog_4 | 110 |
| 18 | GD | `0x441270` | `GameLog::FeedingResult` | gamelog_4 | 118 |
| 19 | GD | `0x4416e0` | `GameLog::FeedingMaterial` | gamelog_4 | 110 |
| 20 | GD | `0x441b00` | `GameLog::ConsumedByFeeding` | gamelog_4 | 104 |
| 21 | GD | `0x441ed0` | `GameLog::MakeCustomDress` | gamelog_4 | 106 |
| 22 | GD | `0x4422e0` | `GameLog::ConsumeItemByMakeCustomDress` | gamelog_4 | 103 |
| 23 | GD | `0x442690` | `GameLog::ConsumeMoneyByMakeCustomDress` | gamelog_4 | 102 |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/gamelog_4.cpp`
- `src/Server/GameDaemon/gamelog_4.h`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-28.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
