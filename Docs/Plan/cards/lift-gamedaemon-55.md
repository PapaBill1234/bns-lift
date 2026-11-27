# lift-gamedaemon-55: DataReader: associativetable_cpp

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
| Depends on | `lift-gamedaemon-47`, `lift-gamedaemon-50` |
| Pattern | `src/library/FsdReader/FsdDecomposer.cpp` |
| Plan | `Docs/Plan/gamedaemon-lift.md` sections 1, 3, 5 |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Grep `Docs/Parity/lessons.md` for A2 (block order), A6 (per-exe path literals), A12 (PDB member types), A18 (destructors), A21 (PDB facts) and A22 (per-exe source form). Do not read it in full.
- Pattern: `src/library/FsdReader/FsdDecomposer.cpp`. Read it one time. Use its form for the functions of this card.

## Scope

20 functions, about 1,017 pseudocode lines (about 8,136 tokens). Stems: `associativetable_cpp`.

| n | Exe | RVA | PDB name | Stem | Lines |
| ---: | --- | --- | --- | --- | ---: |
| 1 | GD | `0x6fb1a0` | `DrMultiKeyTable::LoadAlias` | associativetable_cpp | 47 |
| 2 | GD | `0x6fb280` | `DrMultiKeyTable::GetTableSummary` | associativetable_cpp | 32 |
| 3 | GD | `0x6fb330` | `DrMultiKeyTable::Find` | associativetable_cpp | 7 |
| 4 | GD | `0x6fb340` | `DrMultiKeyTable::createInnerIter` | associativetable_cpp | 37 |
| 5 | GD | `0x6fb3f0` | `DrMultiKeyTable::removeInnerIter` | associativetable_cpp | 14 |
| 6 | GD | `0x6fb440` | `DrMultiKeyElMap::count` | associativetable_cpp | 10 |
| 7 | GD | `0x6fb490` | `DrMultiKeyTable::createInnerIter` | associativetable_cpp | 21 |
| 8 | GD | `0x6fb9f0` | `DrMultiKeyTable::setup` | associativetable_cpp | 122 |
| 9 | GD | `0x6fbc00` | `DrMultiKeyTable::LoadTable` | associativetable_cpp | 130 |
| 10 | GD | `0x6fbe40` | `DrMultiKeyTable::LoadTableMT_PreProc` | associativetable_cpp | 107 |
| 11 | GD | `0x6fc060` | `DrMultiKeyTable::LoadTableMT_PostProc` | associativetable_cpp | 59 |
| 12 | GD | `0x6fc130` | `DrMultiKeyElMap::reconstruct` | associativetable_cpp | 94 |
| 13 | GD | `0x6fc2e0` | `DrMultiKeyElMap::destroy` | associativetable_cpp | 23 |
| 14 | GD | `0x6fc370` | `DrMultiKeyTable::clearElMap` | associativetable_cpp | 24 |
| 15 | GD | `0x6fc3f0` | `DrMultiKeyTable::constructExtraBuffer` | associativetable_cpp | 108 |
| 16 | GD | `0x6fc5c0` | `DrMultiKeyTable::FinishLoadTable` | associativetable_cpp | 11 |
| 17 | GD | `0x6fc630` | `DrMultiKeyTable::PrepareLoadTable` | associativetable_cpp | 8 |
| 18 | GD | `0x6fc640` | `DrMultiKeyTable::ReadFromBuffer` | associativetable_cpp | 115 |
| 19 | GD | `0x6fc870` | `DrMultiKeyElMap::~DrMultiKeyElMap` | associativetable_cpp | 28 |
| 20 | GD | `0x6fd210` | `DrMultiKeyTable::DrMultiKeyTable` | associativetable_cpp | 20 |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/associativetable_cpp.cpp`
- `src/Server/GameDaemon/associativetable_cpp.h`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-55.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
