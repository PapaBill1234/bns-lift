# lift-gamedaemon-18: Packet game log: gamelog_2 part 1/5

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

25 functions, about 2,487 pseudocode lines (about 19,896 tokens). Stems: `gamelog_2`.

This card is part 1/5 of stem `gamelog_2`. The other parts are in other cards of this wave. They run one after the other (column "Depends on"). Edit only the functions in this table.

| n | Exe | RVA | PDB name | Stem | Lines |
| ---: | --- | --- | --- | --- | ---: |
| 1 | GD | `0x10be30` | `GameLog::BidMainAuction` | gamelog_2 | 102 |
| 2 | GD | `0x10c1f0` | `GameLog::RebidMainAuction` | gamelog_2 | 102 |
| 3 | GD | `0x10c5b0` | `GameLog::CancelMainAuction` | gamelog_2 | 100 |
| 4 | GD | `0x10c950` | `GameLog::BuyItemNowMainAuction` | gamelog_2 | 102 |
| 5 | GD | `0x10cd10` | `GameLog::GetBackBidMoneyPass` | gamelog_2 | 100 |
| 6 | GD | `0x10d0b0` | `GameLog::DepositMoneyInGuildBank` | gamelog_2 | 103 |
| 7 | GD | `0x10d470` | `GameLog::DepositItemInGuildBank` | gamelog_2 | 104 |
| 8 | GD | `0x10d830` | `GameLog::AdminChangeGuildBank` | gamelog_2 | 94 |
| 9 | GD | `0x10db70` | `GameLog::GuildRename` | gamelog_2 | 98 |
| 10 | GD | `0x10dfb0` | `GameLog::ContractGuildCraft` | gamelog_2 | 108 |
| 11 | GD | `0x10e3b0` | `GameLog::UseItemByContractGuildCraft` | gamelog_2 | 107 |
| 12 | GD | `0x10e7a0` | `GameLog::DonateToGuildCraft` | gamelog_2 | 105 |
| 13 | GD | `0x10eb70` | `GameLog::RentGuildCraft` | gamelog_2 | 106 |
| 14 | GD | `0x10ef50` | `GameLog::ContractGuildUniform` | gamelog_2 | 106 |
| 15 | GD | `0x10f350` | `GameLog::UseItemByContractGuildUniform` | gamelog_2 | 105 |
| 16 | GD | `0x10f730` | `GameLog::DonateToGuildUniform` | gamelog_2 | 107 |
| 17 | GD | `0x10fb20` | `GameLog::MaterialOfGuildUniform` | gamelog_2 | 92 |
| 18 | GD | `0x10fe80` | `GameLog::AddGuildUniformSlot` | gamelog_2 | 104 |
| 19 | GD | `0x176dc0` | `GameLog::PublicRaidDisconnected` | gamelog_2 | 101 |
| 20 | GD | `0x177160` | `GameLog::OpenPublicRaid` | gamelog_2 | 85 |
| 21 | GD | `0x177470` | `GameLog::ClosePublicRaid` | gamelog_2 | 85 |
| 22 | GD | `0x177780` | `GameLog::PublicRaidStartTeam` | gamelog_2 | 86 |
| 23 | GD | `0x177a90` | `GameLog::PublicRaidFinishTeam` | gamelog_2 | 85 |
| 24 | GD | `0x177da0` | `GameLog::PublicRaidStartPC` | gamelog_2 | 100 |
| 25 | GD | `0x178140` | `GameLog::PublicRaidFinishPC` | gamelog_2 | 100 |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/gamelog_2.cpp`
- `src/Server/GameDaemon/gamelog_2.h`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-18.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
