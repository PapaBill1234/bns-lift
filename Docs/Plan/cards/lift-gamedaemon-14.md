# lift-gamedaemon-14: Packet game log: gamelog_1 part 2/5

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

24 functions, about 2,493 pseudocode lines (about 19,944 tokens). Stems: `gamelog_1`.

This card is part 2/5 of stem `gamelog_1`. The other parts are in other cards of this wave. They run one after the other (column "Depends on"). Edit only the functions in this table.

| n | Exe | RVA | PDB name | Stem | Lines |
| ---: | --- | --- | --- | --- | ---: |
| 1 | GD | `0x225f0` | `GameLog::BattleRoyalFieldStartPc` | gamelog_1 | 104 |
| 2 | GD | `0x229c0` | `GameLog::BattleRoyalFieldEndPc` | gamelog_1 | 107 |
| 3 | GD | `0x22db0` | `GameLog::LootBattleRoyalFieldDroppedItem` | gamelog_1 | 104 |
| 4 | GD | `0x23180` | `GameLog::BattleRoyalFieldRewardItem` | gamelog_1 | 104 |
| 5 | GD | `0x23560` | `GameLog::BoardGachaLot` | gamelog_1 | 111 |
| 6 | GD | `0x23960` | `GameLog::ChangeWeaponAppearance` | gamelog_1 | 108 |
| 7 | GD | `0x23d40` | `GameLog::ConsumeItemByChangeWeaponAppearance` | gamelog_1 | 109 |
| 8 | GD | `0x24130` | `GameLog::ConsumeMoneyByChangeWeaponAppearance` | gamelog_1 | 106 |
| 9 | GD | `0x24500` | `GameLog::DepositCostume` | gamelog_1 | 105 |
| 10 | GD | `0x248e0` | `GameLog::RetrieveCostume` | gamelog_1 | 105 |
| 11 | GD | `0x24cc0` | `GameLog::DepositGameCash` | gamelog_1 | 102 |
| 12 | GD | `0x25090` | `GameLog::SpawnNPC` | gamelog_1 | 90 |
| 13 | GD | `0x253d0` | `GameLog::DespawnNPC` | gamelog_1 | 88 |
| 14 | GD | `0x25700` | `GameLog::BossCombatStart` | gamelog_1 | 99 |
| 15 | GD | `0x25b60` | `GameLog::BossCombatEnd` | gamelog_1 | 92 |
| 16 | GD | `0x25ea0` | `GameLog::BossCombatMemberStart` | gamelog_1 | 105 |
| 17 | GD | `0x26290` | `GameLog::BossCombatMemberEnd` | gamelog_1 | 105 |
| 18 | GD | `0x26680` | `GameLog::TendencyOccureChannelInfo` | gamelog_1 | 95 |
| 19 | GD | `0x269e0` | `GameLog::CollectMissionReward` | gamelog_1 | 109 |
| 20 | GD | `0x26df0` | `GameLog::CollectMissionRewardItem` | gamelog_1 | 105 |
| 21 | GD | `0x8c630` | `GameLog::DuelBotChallengeStageStart` | gamelog_1 | 113 |
| 22 | GD | `0x8cab0` | `GameLog::DuelBotChallengeStageEnd` | gamelog_1 | 115 |
| 23 | GD | `0x8cf30` | `GameLog::DuelBotChallengeReward` | gamelog_1 | 110 |
| 24 | GD | `0x8d330` | `GameLog::DuelBotChallengeRewardItem` | gamelog_1 | 102 |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/gamelog_1.cpp`
- `src/Server/GameDaemon/gamelog_1.h`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-14.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
