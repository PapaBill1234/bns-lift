# lift-gamedaemon-16: Packet game log: gamelog_1 part 4/5

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
| Depends on | `lift-gamedaemon-12`, `lift-gamedaemon-13`, `lift-gamedaemon-15` |
| Pattern | `src/Server/GameDaemon/gamelog_1.cpp` |
| Plan | `Docs/Plan/gamedaemon-lift.md` sections 1, 3, 5 |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Grep `Docs/Parity/lessons.md` for A2 (block order), A6 (per-exe path literals), A12 (PDB member types), A18 (destructors), A21 (PDB facts) and A22 (per-exe source form). Do not read it in full.
- Pattern: `src/Server/GameDaemon/gamelog_1.cpp`. Read it one time. Use its form for the functions of this card.
  The pattern is the output of `lift-gamedaemon-13`. Use the same form for each function: the functions in this group have one layout.
- Dead-strip: `wmain` and most callers are still `LIFT_STUB` bodies. `/OPT:REF` removes a lifted function that has no live caller, and funcdiff then cannot pair it. For each function in scope with no live caller, add `#pragma comment(linker, "/INCLUDE:<public name>")` in its `.cpp` (public names: `llvm-pdbutil dump -publics`; grep `/INCLUDE` in `Docs/Parity/lessons.md`). Do not add a pragma for a function that a lifted caller keeps.

## Scope

14 functions, about 1,351 pseudocode lines (about 10,808 tokens). Stems: `gamelog_1`.

This card is part 4/5 of stem `gamelog_1`. The other parts are in other cards of this wave. They run one after the other (column "Depends on"). Edit only the functions in this table.

| n | Exe | RVA | PDB name | Stem | Lines |
| ---: | --- | --- | --- | --- | ---: |
| 1 | GD | `0x93780` | `GameLog::GuildGetRankingReward` | gamelog_1 | 94 |
| 2 | GD | `0x93ad0` | `GameLog::GuildGetRankingRewardGuildBank` | gamelog_1 | 101 |
| 3 | GD | `0x93e50` | `GameLog::GuildRatingScoreChange` | gamelog_1 | 100 |
| 4 | GD | `0x941d0` | `GameLog::CancelRequestGuildCraft` | gamelog_1 | 104 |
| 5 | GD | `0x945a0` | `GameLog::LoseGuildCraftMaterial` | gamelog_1 | 93 |
| 6 | GD | `0x948f0` | `GameLog::StartGuildCraft` | gamelog_1 | 93 |
| 7 | GD | `0x94c30` | `GameLog::CompleteGuildCraft` | gamelog_1 | 92 |
| 8 | GD | `0x94f70` | `GameLog::TakeGuildCraft` | gamelog_1 | 106 |
| 9 | GD | `0x95350` | `GameLog::AssentGuildCraft` | gamelog_1 | 106 |
| 10 | GD | `0x95730` | `GameLog::CompleteRentGuildCraft` | gamelog_1 | 92 |
| 11 | GD | `0x95a70` | `GameLog::CancelContractGuildUniform` | gamelog_1 | 102 |
| 12 | GD | `0x95e30` | `GameLog::LoseGuildUniformMaterial` | gamelog_1 | 90 |
| 13 | GD | `0x96160` | `GameLog::StartGuildUniform` | gamelog_1 | 90 |
| 14 | GD | `0x964b0` | `GameLog::CompleteGuildUniform` | gamelog_1 | 88 |

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

Write `Docs/Plan/handoffs/lift-gamedaemon-16.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
