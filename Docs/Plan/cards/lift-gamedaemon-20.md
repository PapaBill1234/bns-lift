# lift-gamedaemon-20: Packet game log: gamelog_2 part 3/5

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
| Depends on | `lift-gamedaemon-12`, `lift-gamedaemon-13`, `lift-gamedaemon-19` |
| Pattern | `src/Server/GameDaemon/gamelog_1.cpp` |
| Plan | `Docs/Plan/gamedaemon-lift.md` sections 1, 3, 5 |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Grep `Docs/Parity/lessons.md` for A2 (block order), A6 (per-exe path literals), A12 (PDB member types), A18 (destructors), A21 (PDB facts) and A22 (per-exe source form). Do not read it in full.
- Pattern: `src/Server/GameDaemon/gamelog_1.cpp`. Read it one time. Use its form for the functions of this card.
  The pattern is the output of `lift-gamedaemon-13`. Use the same form for each function: the functions in this group have one layout.

## Scope

23 functions, about 2,412 pseudocode lines (about 19,296 tokens). Stems: `gamelog_2`.

This card is part 3/5 of stem `gamelog_2`. The other parts are in other cards of this wave. They run one after the other (column "Depends on"). Edit only the functions in this table.

| n | Exe | RVA | PDB name | Stem | Lines |
| ---: | --- | --- | --- | --- | ---: |
| 1 | GD | `0x17e100` | `GameLog::GetItemPost` | gamelog_2 | 110 |
| 2 | GD | `0x17e550` | `GameLog::GetMoneyPost` | gamelog_2 | 108 |
| 3 | GD | `0x17e990` | `GameLog::LotRandomStoreResult` | gamelog_2 | 109 |
| 4 | GD | `0x17edb0` | `GameLog::ReceiveEventItemComplete` | gamelog_2 | 102 |
| 5 | GD | `0x17f160` | `GameLog::SummonedSpawn` | gamelog_2 | 102 |
| 6 | GD | `0x17f590` | `GameLog::EndSummonedCustomize` | gamelog_2 | 105 |
| 7 | GD | `0x17f9d0` | `GameLog::ChangeSummonedName` | gamelog_2 | 106 |
| 8 | GD | `0x17fe40` | `GameLog::StartHongmoonTraining` | gamelog_2 | 106 |
| 9 | GD | `0x180210` | `GameLog::EndHongmoonTraining` | gamelog_2 | 107 |
| 10 | GD | `0x1805f0` | `GameLog::ServerRaidDungeonAffiliationReset` | gamelog_2 | 81 |
| 11 | GD | `0x1dc310` | `GameLog::AutoLogoutCheck` | gamelog_2 | 99 |
| 12 | GD | `0x1dc690` | `GameLog::GetExperience` | gamelog_2 | 113 |
| 13 | GD | `0x1dcb00` | `GameLog::GetMoney` | gamelog_2 | 104 |
| 14 | GD | `0x1dcec0` | `GameLog::SpendMoney` | gamelog_2 | 106 |
| 15 | GD | `0x1dd290` | `GameLog::GetExceededMoney` | gamelog_2 | 102 |
| 16 | GD | `0x1dd640` | `GameLog::GetBuildupPoint` | gamelog_2 | 108 |
| 17 | GD | `0x1dda40` | `GameLog::ExhaustVitality` | gamelog_2 | 101 |
| 18 | GD | `0x1ddde0` | `GameLog::RewardAchievement` | gamelog_2 | 104 |
| 19 | GD | `0x1de1b0` | `GameLog::InviteParty` | gamelog_2 | 109 |
| 20 | GD | `0x1de5f0` | `GameLog::JoinParty` | gamelog_2 | 110 |
| 21 | GD | `0x1de9d0` | `GameLog::RefuseParty` | gamelog_2 | 105 |
| 22 | GD | `0x1dedf0` | `GameLog::DismissParty` | gamelog_2 | 106 |
| 23 | GD | `0x1df1c0` | `GameLog::KickPartyMember` | gamelog_2 | 109 |

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

Write `Docs/Plan/handoffs/lift-gamedaemon-20.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
