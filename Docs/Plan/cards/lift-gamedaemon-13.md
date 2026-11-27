# lift-gamedaemon-13: Packet game log: gamelog_1 part 1/5

| Item | Value |
| --- | --- |
| Exe | GD |
| Source build | GameDaemon 2019 + PDB (VS2010 SP1) |
| Exe file | `<work-root>/ida/lift/GameDaemon/GameDaemon.exe` |
| PDB | `<work-root>/ida/lift/GameDaemon/GameDaemon.pdb` |
| Pseudocode | `~/.cache/bns-lift/hr/GameDaemon/<stem>.c` |
| Pseudocode index | `~/.cache/bns-lift/hr/GameDaemon/index.tsv` (stem, rva, name, first, last, status, source file, part) |
| Wave | W1 |
| Model | opus |
| Depends on | `lift-gamedaemon-12` |
| Pattern | none |
| Plan | `Docs/Plan/gamedaemon-lift.md` sections 1, 3, 5 |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Grep `Docs/Parity/lessons.md` for A2 (block order), A6 (per-exe path literals), A12 (PDB member types), A18 (destructors), A21 (PDB facts) and A22 (per-exe source form). Do not read it in full.
- Pattern: none. This card sets the pattern for its group. Write the form so that later cards can copy it. Write the form in the handoff.

## Scope

25 functions, about 2,468 pseudocode lines (about 19,744 tokens). Stems: `gamelog_1`.

This card is part 1/5 of stem `gamelog_1`. The other parts are in other cards of this wave. They run one after the other (column "Depends on"). Edit only the functions in this table.

| n | Exe | RVA | PDB name | Stem | Lines |
| ---: | --- | --- | --- | --- | ---: |
| 1 | GD | `0xacc0` | `GameLog::BoardGachaStart` | gamelog_1 | 85 |
| 2 | GD | `0xafc0` | `GameLog::BoardGachaEnd` | gamelog_1 | 85 |
| 3 | GD | `0xe3e0` | `GameLog::PlayChallenge` | gamelog_1 | 110 |
| 4 | GD | `0x1d2c0` | `GameLog::CreatePc` | gamelog_1 | 90 |
| 5 | GD | `0x1d5f0` | `GameLog::DeletePc` | gamelog_1 | 92 |
| 6 | GD | `0x1d940` | `GameLog::EndCharacterCustomize` | gamelog_1 | 93 |
| 7 | GD | `0x1dc90` | `GameLog::ChangeCharacterRace` | gamelog_1 | 98 |
| 8 | GD | `0x1e010` | `GameLog::ChangeCharacterSex` | gamelog_1 | 96 |
| 9 | GD | `0x1e380` | `GameLog::CutOffAccess` | gamelog_1 | 102 |
| 10 | GD | `0x1e750` | `GameLog::ChangeAchievementStep` | gamelog_1 | 104 |
| 11 | GD | `0x1eb10` | `GameLog::ResetAchievementRegister` | gamelog_1 | 103 |
| 12 | GD | `0x1eed0` | `GameLog::CreateChallengeParty` | gamelog_1 | 102 |
| 13 | GD | `0x1f290` | `GameLog::JoinChallengeParty` | gamelog_1 | 103 |
| 14 | GD | `0x1f660` | `GameLog::DismissChallengeParty` | gamelog_1 | 103 |
| 15 | GD | `0x1fa30` | `GameLog::KickedFromChallengeParty` | gamelog_1 | 106 |
| 16 | GD | `0x1fe60` | `GameLog::PromoteChallengePartyLeader` | gamelog_1 | 106 |
| 17 | GD | `0x20290` | `GameLog::DestroyChallengeParty` | gamelog_1 | 102 |
| 18 | GD | `0x20650` | `GameLog::ChallengeBossCombatStartBoss` | gamelog_1 | 97 |
| 19 | GD | `0x20a90` | `GameLog::ChallengeBossCombatEndBoss` | gamelog_1 | 104 |
| 20 | GD | `0x20f10` | `GameLog::ChallengeBossCombatStartPc` | gamelog_1 | 106 |
| 21 | GD | `0x21300` | `GameLog::ChallengeBossCombatEndPc` | gamelog_1 | 105 |
| 22 | GD | `0x216f0` | `GameLog::ChallengePuzzleStart` | gamelog_1 | 98 |
| 23 | GD | `0x21b40` | `GameLog::ChallengePuzzleEnd` | gamelog_1 | 103 |
| 24 | GD | `0x21fb0` | `GameLog::BattleRoyalFieldStart` | gamelog_1 | 87 |
| 25 | GD | `0x222d0` | `GameLog::BattleRoyalFieldEnd` | gamelog_1 | 88 |

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

Write `Docs/Plan/handoffs/lift-gamedaemon-13.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.
Describe the form that the later cards of this group must copy.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
