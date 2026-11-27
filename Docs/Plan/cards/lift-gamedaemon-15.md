# lift-gamedaemon-15: Packet game log: gamelog_1 part 3/5

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
| Depends on | `lift-gamedaemon-12`, `lift-gamedaemon-13`, `lift-gamedaemon-14` |
| Pattern | `src/Server/GameDaemon/gamelog_1.cpp` |
| Plan | `Docs/Plan/gamedaemon-lift.md` sections 1, 3, 5 |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Grep `Docs/Parity/lessons.md` for A2 (block order), A6 (per-exe path literals), A12 (PDB member types), A18 (destructors), A21 (PDB facts) and A22 (per-exe source form). Do not read it in full.
- Pattern: `src/Server/GameDaemon/gamelog_1.cpp`. Read it one time. Use its form for the functions of this card.
  The pattern is the output of `lift-gamedaemon-13`. Use the same form for each function: the functions in this group have one layout.

## Scope

23 functions, about 2,446 pseudocode lines (about 19,568 tokens). Stems: `gamelog_1`.

This card is part 3/5 of stem `gamelog_1`. The other parts are in other cards of this wave. They run one after the other (column "Depends on"). Edit only the functions in this table.

| n | Exe | RVA | PDB name | Stem | Lines |
| ---: | --- | --- | --- | --- | ---: |
| 1 | GD | `0x8d6f0` | `GameLog::DuelBotChallengeScoreChange` | gamelog_1 | 111 |
| 2 | GD | `0x8daf0` | `GameLog::DuelBotTrainingRoomBattleStart` | gamelog_1 | 103 |
| 3 | GD | `0x8def0` | `GameLog::DuelBotTrainingRoomBattleEnd` | gamelog_1 | 107 |
| 4 | GD | `0x8e300` | `GameLog::RecordLifecontentsNote` | gamelog_1 | 100 |
| 5 | GD | `0x8e6b0` | `GameLog::DuelDodgePenalty` | gamelog_1 | 89 |
| 6 | GD | `0x8e9f0` | `GameLog::DuelStartPC` | gamelog_1 | 116 |
| 7 | GD | `0x8ef00` | `GameLog::DuelEndPC` | gamelog_1 | 120 |
| 8 | GD | `0x8f450` | `GameLog::DuelStartTeam` | gamelog_1 | 107 |
| 9 | GD | `0x8f830` | `GameLog::DuelEndTeam` | gamelog_1 | 110 |
| 10 | GD | `0x8fc40` | `GameLog::MoveToArena` | gamelog_1 | 98 |
| 11 | GD | `0x8ffd0` | `GameLog::DisconnectedDuel` | gamelog_1 | 106 |
| 12 | GD | `0x903b0` | `GameLog::BattleSpectate` | gamelog_1 | 111 |
| 13 | GD | `0x908a0` | `GameLog::GetSpecialMaterial` | gamelog_1 | 104 |
| 14 | GD | `0x90c80` | `GameLog::SaveEquipInfo` | gamelog_1 | 119 |
| 15 | GD | `0x91140` | `GameLog::DestoryGuild` | gamelog_1 | 102 |
| 16 | GD | `0x91510` | `GameLog::GuildLevelUp` | gamelog_1 | 106 |
| 17 | GD | `0x91900` | `GameLog::InviteGuild` | gamelog_1 | 108 |
| 18 | GD | `0x91dd0` | `GameLog::JoinGuild` | gamelog_1 | 104 |
| 19 | GD | `0x921a0` | `GameLog::RefuseGuildInvite` | gamelog_1 | 107 |
| 20 | GD | `0x92660` | `GameLog::DismissGuild` | gamelog_1 | 103 |
| 21 | GD | `0x92a30` | `GameLog::KickGuildMember` | gamelog_1 | 107 |
| 22 | GD | `0x92ef0` | `GameLog::UseItemByGuildLevelUp` | gamelog_1 | 103 |
| 23 | GD | `0x932b0` | `GameLog::GuildVanguardChange` | gamelog_1 | 105 |

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

Write `Docs/Plan/handoffs/lift-gamedaemon-15.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
