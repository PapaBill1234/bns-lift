# lift-gamedaemon-24: Packet game log: gamelog_3 part 2/5

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
| Depends on | `lift-gamedaemon-12`, `lift-gamedaemon-13`, `lift-gamedaemon-23` |
| Pattern | `src/Server/GameDaemon/gamelog_1.cpp` |
| Plan | `Docs/Plan/gamedaemon-lift.md` sections 1, 3, 5 |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Grep `Docs/Parity/lessons.md` for A2 (block order), A6 (per-exe path literals), A12 (PDB member types), A18 (destructors), A21 (PDB facts) and A22 (per-exe source form). Do not read it in full.
- Pattern: `src/Server/GameDaemon/gamelog_1.cpp`. Read it one time. Use its form for the functions of this card.
  The pattern is the output of `lift-gamedaemon-13`. Use the same form for each function: the functions in this group have one layout.

## Scope

24 functions, about 2,416 pseudocode lines (about 19,328 tokens). Stems: `gamelog_3`.

This card is part 2/5 of stem `gamelog_3`. The other parts are in other cards of this wave. They run one after the other (column "Depends on"). Edit only the functions in this table.

| n | Exe | RVA | PDB name | Stem | Lines |
| ---: | --- | --- | --- | --- | ---: |
| 1 | GD | `0x1ec360` | `GameLog::CancelVolunteer` | gamelog_3 | 103 |
| 2 | GD | `0x1ec740` | `GameLog::AssentGuildVolunteer` | gamelog_3 | 108 |
| 3 | GD | `0x1ecc10` | `GameLog::ServerStart` | gamelog_3 | 81 |
| 4 | GD | `0x1ecf00` | `GameLog::ServerEnd` | gamelog_3 | 81 |
| 5 | GD | `0x1ed1f0` | `GameLog::OpenZone` | gamelog_3 | 86 |
| 6 | GD | `0x1ed500` | `GameLog::CloseZone` | gamelog_3 | 85 |
| 7 | GD | `0x349940` | `GameLog::GetItem` | gamelog_3 | 113 |
| 8 | GD | `0x349da0` | `GameLog::LoseItem` | gamelog_3 | 115 |
| 9 | GD | `0x34a230` | `GameLog::KillNPC` | gamelog_3 | 110 |
| 10 | GD | `0x34a690` | `GameLog::LootMoney` | gamelog_3 | 101 |
| 11 | GD | `0x34aa40` | `GameLog::TradeGiveItem` | gamelog_3 | 104 |
| 12 | GD | `0x34aed0` | `GameLog::TradeGetItem` | gamelog_3 | 104 |
| 13 | GD | `0x34b360` | `GameLog::TradeGiveMoney` | gamelog_3 | 104 |
| 14 | GD | `0x34b7f0` | `GameLog::TradeGetMoney` | gamelog_3 | 104 |
| 15 | GD | `0x34bc80` | `GameLog::RequestTrade` | gamelog_3 | 102 |
| 16 | GD | `0x34c100` | `GameLog::ReplyTrade` | gamelog_3 | 103 |
| 17 | GD | `0x34c580` | `GameLog::TradeGiveOk` | gamelog_3 | 104 |
| 18 | GD | `0x34ca10` | `GameLog::TradeGetOk` | gamelog_3 | 104 |
| 19 | GD | `0x34cea0` | `GameLog::TradeGiveFail` | gamelog_3 | 104 |
| 20 | GD | `0x34d330` | `GameLog::TradeGetFail` | gamelog_3 | 104 |
| 21 | GD | `0x34d7c0` | `GameLog::CancelTrade` | gamelog_3 | 102 |
| 22 | GD | `0x34dc40` | `GameLog::NPCDropItem` | gamelog_3 | 97 |
| 23 | GD | `0x34e060` | `GameLog::GetMainFactionCoinGuild` | gamelog_3 | 91 |
| 24 | GD | `0x34e3d0` | `GameLog::ReportBotSpammer` | gamelog_3 | 106 |

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

Write `Docs/Plan/handoffs/lift-gamedaemon-24.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
