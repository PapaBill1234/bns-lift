# lift-gamedaemon-29: Packet game log: gamelog_4 part 2/5

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
| Depends on | `lift-gamedaemon-12`, `lift-gamedaemon-13`, `lift-gamedaemon-28` |
| Pattern | `src/Server/GameDaemon/gamelog_1.cpp` |
| Plan | `Docs/Plan/gamedaemon-lift.md` sections 1, 3, 5 |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Grep `Docs/Parity/lessons.md` for A2 (block order), A6 (per-exe path literals), A12 (PDB member types), A18 (destructors), A21 (PDB facts) and A22 (per-exe source form). Do not read it in full.
- Pattern: `src/Server/GameDaemon/gamelog_1.cpp`. Read it one time. Use its form for the functions of this card.
  The pattern is the output of `lift-gamedaemon-13`. Use the same form for each function: the functions in this group have one layout.

## Scope

23 functions, about 2,491 pseudocode lines (about 19,928 tokens). Stems: `gamelog_4`.

This card is part 2/5 of stem `gamelog_4`. The other parts are in other cards of this wave. They run one after the other (column "Depends on"). Edit only the functions in this table.

| n | Exe | RVA | PDB name | Stem | Lines |
| ---: | --- | --- | --- | --- | ---: |
| 1 | GD | `0x442a40` | `GameLog::AcquireSkillSkin` | gamelog_4 | 101 |
| 2 | GD | `0x442de0` | `GameLog::SpiritItem` | gamelog_4 | 114 |
| 3 | GD | `0x4431f0` | `GameLog::ConsumeMaterialBySpirit` | gamelog_4 | 108 |
| 4 | GD | `0x4435e0` | `GameLog::ConsumeCatalystBySpirit` | gamelog_4 | 105 |
| 5 | GD | `0x4439b0` | `GameLog::EquipBadge` | gamelog_4 | 111 |
| 6 | GD | `0x443db0` | `GameLog::UnEquipBadge` | gamelog_4 | 111 |
| 7 | GD | `0x4441b0` | `GameLog::ResultOfSynthesisBadge` | gamelog_4 | 108 |
| 8 | GD | `0x4445b0` | `GameLog::GetSynthesisBadge` | gamelog_4 | 108 |
| 9 | GD | `0x4449b0` | `GameLog::SynthesisBadgeCostItem` | gamelog_4 | 108 |
| 10 | GD | `0x444da0` | `GameLog::SynthesisBadgeCostBadge` | gamelog_4 | 112 |
| 11 | GD | `0x4451b0` | `GameLog::BuyItem` | gamelog_4 | 99 |
| 12 | GD | `0x445550` | `GameLog::SellItem` | gamelog_4 | 118 |
| 13 | GD | `0x445a30` | `GameLog::BuyMyItem` | gamelog_4 | 104 |
| 14 | GD | `0x445e10` | `GameLog::GiveItemToNPC` | gamelog_4 | 110 |
| 15 | GD | `0x446260` | `GameLog::GetItemFromNPC` | gamelog_4 | 114 |
| 16 | GD | `0x4466d0` | `GameLog::GivePointToNPC` | gamelog_4 | 105 |
| 17 | GD | `0x446b20` | `GameLog::DepositItem` | gamelog_4 | 103 |
| 18 | GD | `0x446ee0` | `GameLog::RetrieveItem` | gamelog_4 | 103 |
| 19 | GD | `0x4472a0` | `GameLog::ItemExchangeMaterial` | gamelog_4 | 106 |
| 20 | GD | `0x4476a0` | `GameLog::GetItemExchange` | gamelog_4 | 111 |
| 21 | GD | `0x447ac0` | `GameLog::GetItemCrystalization` | gamelog_4 | 111 |
| 22 | GD | `0x447ee0` | `GameLog::BuyItemNowUseSecondaryMoney` | gamelog_4 | 108 |
| 23 | GD | `0x4482c0` | `GameLog::PutMainAuction` | gamelog_4 | 113 |

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

Write `Docs/Plan/handoffs/lift-gamedaemon-29.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
