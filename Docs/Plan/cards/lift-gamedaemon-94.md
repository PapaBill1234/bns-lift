# lift-gamedaemon-94: DataManager: datamanager_cpp_3 part 8/10

| Item | Value |
| --- | --- |
| Exe | GD |
| Source build | GameDaemon 2019 + PDB (VS2010 SP1) |
| Exe file | `<work-root>/ida/lift/GameDaemon/GameDaemon.exe` |
| PDB | `<work-root>/ida/lift/GameDaemon/GameDaemon.pdb` |
| Pseudocode | `~/.cache/bns-lift/hr/GameDaemon/<stem>.c` |
| Pseudocode index | `~/.cache/bns-lift/hr/GameDaemon/index.tsv` (stem, rva, name, first, last, status, source file, part) |
| Wave | W2 |
| Model | opus |
| Depends on | `lift-gamedaemon-e13`, `lift-gamedaemon-67`, `lift-gamedaemon-93` |
| Pattern | none |
| Plan | `Docs/Plan/gamedaemon-lift.md` sections 1, 3, 5 |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Grep `Docs/Parity/lessons.md` for A2 (block order), A6 (per-exe path literals), A12 (PDB member types), A18 (destructors), A21 (PDB facts) and A22 (per-exe source form). Do not read it in full.
- Pattern: none. Read the functions that `lift-gamedaemon-93` lifted in the same file first. Use their form.
- Dead-strip: `wmain` and most callers are still `LIFT_STUB` bodies. `/OPT:REF` removes a lifted function that has no live caller, and funcdiff then cannot pair it. For each function in scope with no live caller, add `#pragma comment(linker, "/INCLUDE:<public name>")` in its `.cpp` (public names: `llvm-pdbutil dump -publics`; grep `/INCLUDE` in `Docs/Parity/lessons.md`). Do not add a pragma for a function that a lifted caller keeps.

## Scope

21 functions, about 2,460 pseudocode lines (about 19,680 tokens). Stems: `datamanager_cpp_3`.

The easy functions of this stem are in `lift-gamedaemon-e13`. Do not change them unless a fix needs it.

This card is part 8/10 of stem `datamanager_cpp_3`. The other parts are in other cards of this wave. They run one after the other (column "Depends on"). Edit only the functions in this table.

| n | Exe | RVA | PDB name | Stem | Lines |
| ---: | --- | --- | --- | --- | ---: |
| 1 | GD | `0x65cd50` | `Data::validateFish` | datamanager_cpp_3 | 116 |
| 2 | GD | `0x65cf80` | `Data::validateFishingField` | datamanager_cpp_3 | 69 |
| 3 | GD | `0x65d1f0` | `Data::validateBadgeSynthesisRecipe` | datamanager_cpp_3 | 80 |
| 4 | GD | `0x65d330` | `Data::validateClosetGroup` | datamanager_cpp_3 | 186 |
| 5 | GD | `0x65d660` | `Data::validateSkillSystematization` | datamanager_cpp_3 | 125 |
| 6 | GD | `0x65d8b0` | `Data::validateJobStyle` | datamanager_cpp_3 | 111 |
| 7 | GD | `0x65daa0` | `Data::validateDifficultyTypeModify` | datamanager_cpp_3 | 88 |
| 8 | GD | `0x65dc50` | `Data::validateBoardGacha` | datamanager_cpp_3 | 52 |
| 9 | GD | `0x65dd70` | `Data::validateBoardGachaReward` | datamanager_cpp_3 | 241 |
| 10 | GD | `0x65e190` | `Data::validateContentsReset` | datamanager_cpp_3 | 119 |
| 11 | GD | `0x65e3d0` | `Data::validateSlateScroll` | datamanager_cpp_3 | 148 |
| 12 | GD | `0x65e6e0` | `Data::validateSlateScrollStone` | datamanager_cpp_3 | 75 |
| 13 | GD | `0x65e8c0` | `Data::validateSlateStone` | datamanager_cpp_3 | 81 |
| 14 | GD | `0x65ea20` | `Data::validateSoulMaskSet` | datamanager_cpp_3 | 108 |
| 15 | GD | `0x65ec60` | `Data::validateItemRandomOption` | datamanager_cpp_3 | 277 |
| 16 | GD | `0x65f0d0` | `Data::validateCostGroup` | datamanager_cpp_3 | 154 |
| 17 | GD | `0x65f360` | `Data::validateZoneAreaGroup` | datamanager_cpp_3 | 95 |
| 18 | GD | `0x65f520` | `Data::validateZoneNpcRandomSpawn` | datamanager_cpp_3 | 76 |
| 19 | GD | `0x65f6a0` | `Data::validateSecondaryStat` | datamanager_cpp_3 | 99 |
| 20 | GD | `0x65f910` | `Data::validateFormulaConstant` | datamanager_cpp_3 | 80 |
| 21 | GD | `0x65fac0` | `Data::validateItemFusion` | datamanager_cpp_3 | 80 |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/datamanager_cpp_3.cpp`
- `src/Server/GameDaemon/datamanager_cpp_3.h`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-94.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
