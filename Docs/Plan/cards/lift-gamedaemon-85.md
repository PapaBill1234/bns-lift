# lift-gamedaemon-85: DataManager: datamanager_cpp_2 part 9/10

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
| Depends on | `lift-gamedaemon-84` |
| Pattern | none |
| Plan | `Docs/Plan/gamedaemon-lift.md` sections 1, 3, 5 |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Grep `Docs/Parity/lessons.md` for A2 (block order), A6 (per-exe path literals), A12 (PDB member types), A18 (destructors), A21 (PDB facts) and A22 (per-exe source form). Do not read it in full.
- Pattern: none. Read the functions that `lift-gamedaemon-84` lifted in the same file first. Use their form.

## Scope

6 functions, about 2,387 pseudocode lines (about 19,096 tokens). Stems: `datamanager_cpp_2`.

This card is part 9/10 of stem `datamanager_cpp_2`. The other parts are in other cards of this wave. They run one after the other (column "Depends on"). Edit only the functions in this table.

| n | Exe | RVA | PDB name | Stem | Lines |
| ---: | --- | --- | --- | --- | ---: |
| 1 | GD | `0x645330` | `Data::validateRandomStore` | datamanager_cpp_2 | 478 |
| 2 | GD | `0x645b80` | `Data::validateEffect` | datamanager_cpp_2 | 895 |
| 3 | GD | `0x646bf0` | `Data::validateEnv` | datamanager_cpp_2 | 363 |
| 4 | GD | `0x6472b0` | `Data::isValidArea` | datamanager_cpp_2 | 56 |
| 5 | GD | `0x647410` | `Data::validateZoneNpcSpawn` | datamanager_cpp_2 | 477 |
| 6 | GD | `0x647cb0` | `Data::validateChallengeParty` | datamanager_cpp_2 | 118 |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/datamanager_cpp_2.cpp`
- `src/Server/GameDaemon/datamanager_cpp_2.h`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-85.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
