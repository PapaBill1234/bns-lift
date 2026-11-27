# lift-gamedaemon-23: Packet game log: gamelog_3 part 1/5

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

## Scope

23 functions, about 2,414 pseudocode lines (about 19,312 tokens). Stems: `gamelog_3`.

This card is part 1/5 of stem `gamelog_3`. The other parts are in other cards of this wave. They run one after the other (column "Depends on"). Edit only the functions in this table.

| n | Exe | RVA | PDB name | Stem | Lines |
| ---: | --- | --- | --- | --- | ---: |
| 1 | GD | `0x1e67c0` | `GameLog::SelectEquipBadgePage` | gamelog_3 | 103 |
| 2 | GD | `0x1e6b70` | `GameLog::GetFactionReputation` | gamelog_3 | 105 |
| 3 | GD | `0x1e6f50` | `GameLog::LotRandomStore` | gamelog_3 | 111 |
| 4 | GD | `0x1e7380` | `GameLog::BuyRandomStoreItem` | gamelog_3 | 109 |
| 5 | GD | `0x1e7790` | `GameLog::ExpandRandomStoreSlot` | gamelog_3 | 107 |
| 6 | GD | `0x1e7b70` | `GameLog::UseItemByRandomStorePurchase` | gamelog_3 | 107 |
| 7 | GD | `0x1e7f70` | `GameLog::PutHiddenPower` | gamelog_3 | 105 |
| 8 | GD | `0x1e8340` | `GameLog::PutHiddenPowerItem` | gamelog_3 | 116 |
| 9 | GD | `0x1e87d0` | `GameLog::ApplySlateScroll` | gamelog_3 | 110 |
| 10 | GD | `0x1e8be0` | `GameLog::ApplySlateScrollItem` | gamelog_3 | 103 |
| 11 | GD | `0x1e8fa0` | `GameLog::ConfirmSlateStone` | gamelog_3 | 105 |
| 12 | GD | `0x1e9390` | `GameLog::SelectSlatePage` | gamelog_3 | 99 |
| 13 | GD | `0x1e9720` | `GameLog::SignGatheringFaction` | gamelog_3 | 101 |
| 14 | GD | `0x1e9b50` | `GameLog::LeaveGatheringFaction` | gamelog_3 | 101 |
| 15 | GD | `0x1e9f70` | `GameLog::RequestGatheringItem` | gamelog_3 | 103 |
| 16 | GD | `0x1ea350` | `GameLog::GameMoneyAuctionEscrow` | gamelog_3 | 103 |
| 17 | GD | `0x1ea710` | `GameLog::RewardTimeBase` | gamelog_3 | 106 |
| 18 | GD | `0x1eab00` | `GameLog::RewardRandomStoreBonus` | gamelog_3 | 104 |
| 19 | GD | `0x1eaed0` | `GameLog::FieldPlayPointChange` | gamelog_3 | 106 |
| 20 | GD | `0x1eb2a0` | `GameLog::TendencyOccureWorldInfo` | gamelog_3 | 92 |
| 21 | GD | `0x1eb5f0` | `GameLog::CancelGuildInvite` | gamelog_3 | 107 |
| 22 | GD | `0x1ebab0` | `GameLog::GuildVolunteer` | gamelog_3 | 104 |
| 23 | GD | `0x1ebea0` | `GameLog::RefuseGuildVolunteer` | gamelog_3 | 107 |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/gamelog_3.cpp`
- `src/Server/GameDaemon/gamelog_3.h`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-23.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
