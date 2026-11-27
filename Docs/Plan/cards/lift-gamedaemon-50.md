# lift-gamedaemon-50: DataReader: parallelworker, util, md5

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
| Depends on | `lift-gamedaemon-40` |
| Pattern | `src/library/FsdReader/FsdDecomposer.cpp` |
| Plan | `Docs/Plan/gamedaemon-lift.md` sections 1, 3, 5 |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Grep `Docs/Parity/lessons.md` for A2 (block order), A6 (per-exe path literals), A12 (PDB member types), A18 (destructors), A21 (PDB facts) and A22 (per-exe source form). Do not read it in full.
- Pattern: `src/library/FsdReader/FsdDecomposer.cpp`. Read it one time. Use its form for the functions of this card.

## Scope

15 functions, about 595 pseudocode lines (about 4,760 tokens). Stems: `parallelworker`, `util`, `md5`.

| n | Exe | RVA | PDB name | Stem | Lines |
| ---: | --- | --- | --- | --- | ---: |
| 1 | GD | `0x6fea70` | `DrParallelWorkerManager::Init` | parallelworker | 23 |
| 2 | GD | `0x6fead0` | `DrParallelWorkerManager::SetWorkerFunc` | parallelworker | 10 |
| 3 | GD | `0x6feae0` | `DrParallelWorkerManager::SetWorkerInitFunc` | parallelworker | 8 |
| 4 | GD | `0x6feaf0` | `DrParallelWorkerManager::Execute` | parallelworker | 7 |
| 5 | GD | `0x6feb20` | `DrParallelWorkerManager::StopWorkerPool` | parallelworker | 42 |
| 6 | GD | `0x6febc0` | `DrParallelWorkerManager::workerFrame` | parallelworker | 37 |
| 7 | GD | `0x6fec80` | `DrParallelWorkerManager::~DrParallelWorkerManager` | parallelworker | 9 |
| 8 | GD | `0x6fecb0` | `DrParallelWorkerManager::StartWorkerPool` | parallelworker | 27 |
| 9 | GD | `0x6fed30` | `DrUtil::GenerateMD5Checksum` | util | 21 |
| 10 | GD | `0x6fee40` | `DrUtil::Copy` | util | 7 |
| 11 | GD | `0x6fee60` | `DrUtil::Length` | util | 30 |
| 12 | GD | `0x6feff0` | `md5_process` | md5 | 193 |
| 13 | GD | `0x6ff850` | `md5_init` | md5 | 11 |
| 14 | GD | `0x6ff880` | `md5_append` | md5 | 50 |
| 15 | GD | `0x6ff980` | `md5_finish` | md5 | 120 |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/parallelworker.cpp`
- `src/Server/GameDaemon/parallelworker.h`
- `src/Server/GameDaemon/util.cpp`
- `src/Server/GameDaemon/util.h`
- `src/Server/GameDaemon/md5.cpp`
- `src/Server/GameDaemon/md5.h`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-50.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
