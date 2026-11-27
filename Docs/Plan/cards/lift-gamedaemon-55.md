# lift-gamedaemon-55: DataReader: binarydatafile, associativetable_cpp, associativetable_h

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
| Depends on | `lift-gamedaemon-e14`, `lift-gamedaemon-52`, `lift-gamedaemon-56` |
| Pattern | `src/library/FsdReader/FsdDecomposer.cpp` |
| Plan | `Docs/Plan/gamedaemon-lift.md` sections 1, 3, 5 |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Grep `Docs/Parity/lessons.md` for A2 (block order), A6 (per-exe path literals), A12 (PDB member types), A18 (destructors), A21 (PDB facts) and A22 (per-exe source form). Do not read it in full.
- Pattern: `src/library/FsdReader/FsdDecomposer.cpp`. Read it one time. Use its form for the functions of this card.

## Scope

26 functions, about 1,749 pseudocode lines (about 13,992 tokens). Stems: `binarydatafile`, `associativetable_cpp`, `associativetable_h`.

The easy functions of this stem are in `lift-gamedaemon-e14`. Do not change them unless a fix needs it.

| n | Exe | RVA | PDB name | Stem | Lines |
| ---: | --- | --- | --- | --- | ---: |
| 1 | GD | `0x6fa370` | `BinaryDataFile::readFromMem` | binarydatafile | 187 |
| 2 | GD | `0x6fa7b0` | `BinaryDataFile::readFromFileStream` | binarydatafile | 190 |
| 3 | GD | `0x6fac30` | `BinaryDataFile::ReadFromMem` | binarydatafile | 40 |
| 4 | GD | `0x6fad10` | `BinaryDataFile::ReadFromFileStream` | binarydatafile | 40 |
| 5 | GD | `0x6fade0` | `BinaryDataFile::ReadFromFile` | binarydatafile | 80 |
| 6 | GD | `0x6faff0` | `BinaryDataFile::ReadFromFileStream` | binarydatafile | 52 |
| 7 | GD | `0x6fb1a0` | `DrMultiKeyTable::LoadAlias` | associativetable_cpp | 47 |
| 8 | GD | `0x6fb280` | `DrMultiKeyTable::GetTableSummary` | associativetable_cpp | 32 |
| 9 | GD | `0x6fb340` | `DrMultiKeyTable::createInnerIter` | associativetable_cpp | 37 |
| 10 | GD | `0x6fb3f0` | `DrMultiKeyTable::removeInnerIter` | associativetable_cpp | 14 |
| 11 | GD | `0x6fb490` | `DrMultiKeyTable::createInnerIter` | associativetable_cpp | 21 |
| 12 | GD | `0x6fb9f0` | `DrMultiKeyTable::setup` | associativetable_cpp | 122 |
| 13 | GD | `0x6fbc00` | `DrMultiKeyTable::LoadTable` | associativetable_cpp | 130 |
| 14 | GD | `0x6fbe40` | `DrMultiKeyTable::LoadTableMT_PreProc` | associativetable_cpp | 107 |
| 15 | GD | `0x6fc060` | `DrMultiKeyTable::LoadTableMT_PostProc` | associativetable_cpp | 59 |
| 16 | GD | `0x6fc130` | `DrMultiKeyElMap::reconstruct` | associativetable_cpp | 94 |
| 17 | GD | `0x6fc2e0` | `DrMultiKeyElMap::destroy` | associativetable_cpp | 23 |
| 18 | GD | `0x6fc370` | `DrMultiKeyTable::clearElMap` | associativetable_cpp | 24 |
| 19 | GD | `0x6fc3f0` | `DrMultiKeyTable::constructExtraBuffer` | associativetable_cpp | 108 |
| 20 | GD | `0x6fc5c0` | `DrMultiKeyTable::FinishLoadTable` | associativetable_cpp | 11 |
| 21 | GD | `0x6fc630` | `DrMultiKeyTable::PrepareLoadTable` | associativetable_cpp | 8 |
| 22 | GD | `0x6fc640` | `DrMultiKeyTable::ReadFromBuffer` | associativetable_cpp | 115 |
| 23 | GD | `0x6fc870` | `DrMultiKeyElMap::~DrMultiKeyElMap` | associativetable_cpp | 28 |
| 24 | GD | `0x6fd210` | `DrMultiKeyTable::DrMultiKeyTable` | associativetable_cpp | 20 |
| 25 | GD | `0x6fcd10` | `DrMultiKeyElMap::get` | associativetable_h | 74 |
| 26 | GD | `0x6fd0f0` | `DrMultiKeyElMap::set` | associativetable_h | 86 |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/binarydatafile.cpp`
- `src/Server/GameDaemon/binarydatafile.h`
- `src/Server/GameDaemon/associativetable_cpp.cpp`
- `src/Server/GameDaemon/associativetable_cpp.h`
- `src/Server/GameDaemon/associativetable_h.cpp`
- `src/Server/GameDaemon/associativetable_h.h`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-55.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
