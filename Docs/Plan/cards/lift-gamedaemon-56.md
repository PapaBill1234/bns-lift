# lift-gamedaemon-56: DataReader: autokeytable_cpp, parallelworker, util, tableimpl_cpp

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
| Depends on | `lift-gamedaemon-e5`, `lift-gamedaemon-e14`, `lift-gamedaemon-e26`, `lift-gamedaemon-40`, `lift-gamedaemon-52`, `lift-gamedaemon-59` |
| Pattern | `src/library/FsdReader/FsdDecomposer.cpp` |
| Plan | `Docs/Plan/gamedaemon-lift.md` sections 1, 3, 5 |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Grep `Docs/Parity/lessons.md` for A2 (block order), A6 (per-exe path literals), A12 (PDB member types), A18 (destructors), A21 (PDB facts) and A22 (per-exe source form). Do not read it in full.
- Pattern: `src/library/FsdReader/FsdDecomposer.cpp`. Read it one time. Use its form for the functions of this card.
- Dead-strip: `wmain` and most callers are still `LIFT_STUB` bodies. `/OPT:REF` removes a lifted function that has no live caller, and funcdiff then cannot pair it. For each function in scope with no live caller, add `#pragma comment(linker, "/INCLUDE:<public name>")` in its `.cpp` (public names: `llvm-pdbutil dump -publics`; grep `/INCLUDE` in `Docs/Parity/lessons.md`). Do not add a pragma for a function that a lifted caller keeps.

## Scope

24 functions, about 1,128 pseudocode lines (about 9,024 tokens). Stems: `autokeytable_cpp`, `parallelworker`, `util`, `tableimpl_cpp`.

The easy functions of this stem are in `lift-gamedaemon-e14`, `lift-gamedaemon-e26`, `lift-gamedaemon-e5`. Do not change them unless a fix needs it.

| n | Exe | RVA | PDB name | Stem | Lines |
| ---: | --- | --- | --- | --- | ---: |
| 1 | GD | `0x6fd320` | `DrAutoKeyTable::LoadAlias` | autokeytable_cpp | 48 |
| 2 | GD | `0x6fd4c0` | `DrAutoKeyTable::constructExtraBuffer` | autokeytable_cpp | 72 |
| 3 | GD | `0x6fd620` | `DrAutoKeyTable::FinishLoadTable` | autokeytable_cpp | 10 |
| 4 | GD | `0x6fd630` | `DrAutoKeyTable::LoadTableMT_PostProc` | autokeytable_cpp | 45 |
| 5 | GD | `0x6fd6c0` | `DrAutoKeyTable::GetTableSummary` | autokeytable_cpp | 48 |
| 6 | GD | `0x6fd7b0` | `DrAutoKeyTable::createInnerIter` | autokeytable_cpp | 69 |
| 7 | GD | `0x6fd8d0` | `DrAutoKeyTable::removeInnerIter` | autokeytable_cpp | 14 |
| 8 | GD | `0x6fd920` | `DrAutoKeyTable::createInnerIter` | autokeytable_cpp | 36 |
| 9 | GD | `0x6fdab0` | `DrAutoKeyTable::clearElMap` | autokeytable_cpp | 24 |
| 10 | GD | `0x6fdb30` | `DrAutoKeyElMap::~DrAutoKeyElMap` | autokeytable_cpp | 23 |
| 11 | GD | `0x6fdf80` | `DrAutoKeyTable::PrepareLoadTable` | autokeytable_cpp | 8 |
| 12 | GD | `0x6fe030` | `DrAutoKeyTable::DrAutoKeyTable` | autokeytable_cpp | 20 |
| 13 | GD | `0x6fe090` | `DrAutoKeyTable::~DrAutoKeyTable` | autokeytable_cpp | 28 |
| 14 | GD | `0x6fe150` | `DrAutoKeyElMap::construct` | autokeytable_cpp | 53 |
| 15 | GD | `0x6fe220` | `DrAutoKeyTable::setup` | autokeytable_cpp | 101 |
| 16 | GD | `0x6fe3d0` | `DrAutoKeyTable::LoadTable` | autokeytable_cpp | 133 |
| 17 | GD | `0x6fe600` | `DrAutoKeyTable::LoadTableMT_PreProc` | autokeytable_cpp | 125 |
| 18 | GD | `0x6fe7f0` | `DrAutoKeyTable::ReadFromBuffer` | autokeytable_cpp | 129 |
| 19 | GD | `0x6feb20` | `DrParallelWorkerManager::StopWorkerPool` | parallelworker | 42 |
| 20 | GD | `0x6febc0` | `DrParallelWorkerManager::workerFrame` | parallelworker | 37 |
| 21 | GD | `0x6fec80` | `DrParallelWorkerManager::~DrParallelWorkerManager` | parallelworker | 9 |
| 22 | GD | `0x6fed30` | `DrUtil::GenerateMD5Checksum` | util | 21 |
| 23 | GD | `0x6fee40` | `DrUtil::Copy` | util | 7 |
| 24 | GD | `0x6feed0` | `DrDataTableImpl::Find` | tableimpl_cpp | 26 |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/autokeytable_cpp.cpp`
- `src/Server/GameDaemon/autokeytable_cpp.h`
- `src/Server/GameDaemon/parallelworker.cpp`
- `src/Server/GameDaemon/parallelworker.h`
- `src/Server/GameDaemon/util.cpp`
- `src/Server/GameDaemon/util.h`
- `src/Server/GameDaemon/tableimpl_cpp.cpp`
- `src/Server/GameDaemon/tableimpl_cpp.h`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-56.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
