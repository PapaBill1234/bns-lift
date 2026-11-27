# lift-gamedaemon-71: DataManager: datamanager_cpp_1 part 5/10

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
| Depends on | `lift-gamedaemon-e26`, `lift-gamedaemon-70` |
| Pattern | none |
| Plan | `Docs/Plan/gamedaemon-lift.md` sections 1, 3, 5 |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Grep `Docs/Parity/lessons.md` for A2 (block order), A6 (per-exe path literals), A12 (PDB member types), A18 (destructors), A21 (PDB facts) and A22 (per-exe source form). Do not read it in full.
- Pattern: none. Read the functions that `lift-gamedaemon-70` lifted in the same file first. Use their form.

## Scope

5 functions, about 1,605 pseudocode lines (about 12,840 tokens). Stems: `datamanager_cpp_1`.

The easy functions of this stem are in `lift-gamedaemon-e26`. Do not change them unless a fix needs it.

This card is part 5/10 of stem `datamanager_cpp_1`. The other parts are in other cards of this wave. They run one after the other (column "Depends on"). Edit only the functions in this table.

| n | Exe | RVA | PDB name | Stem | Lines |
| ---: | --- | --- | --- | --- | ---: |
| 1 | GD | `0x6238f0` | `Data::linkQuestTransitAndZone` | datamanager_cpp_1 | 272 |
| 2 | GD | `0x623d00` | `Data::DataManager::loadHiddenFieldFromZone` | datamanager_cpp_1 | 1078 |
| 3 | GD | `0x624e70` | `Data::DataManager::loadHiddenFieldFromNpcBrainParameters` | datamanager_cpp_1 | 131 |
| 4 | GD | `0x6250c0` | `Data::DataManager::loadHiddenFieldFromFielditem` | datamanager_cpp_1 | 58 |
| 5 | GD | `0x6251b0` | `Data::DataManager::loadHiddenFieldFromFielditemDrop` | datamanager_cpp_1 | 66 |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/datamanager_cpp_1.cpp`
- `src/Server/GameDaemon/datamanager_cpp_1.h`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-71.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
