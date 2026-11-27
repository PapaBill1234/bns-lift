# lift-gamedaemon-57: DataReader: datareaderimpl

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
| Depends on | `lift-gamedaemon-e14`, `lift-gamedaemon-56`, `lift-gamedaemon-55`, `lift-gamedaemon-53` |
| Pattern | `src/library/FsdReader/FsdDecomposer.cpp` |
| Plan | `Docs/Plan/gamedaemon-lift.md` sections 1, 3, 5 |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Grep `Docs/Parity/lessons.md` for A2 (block order), A6 (per-exe path literals), A12 (PDB member types), A18 (destructors), A21 (PDB facts) and A22 (per-exe source form). Do not read it in full.
- Pattern: `src/library/FsdReader/FsdDecomposer.cpp`. Read it one time. Use its form for the functions of this card.
- Dead-strip: `wmain` and most callers are still `LIFT_STUB` bodies. `/OPT:REF` removes a lifted function that has no live caller, and funcdiff then cannot pair it. For each function in scope with no live caller, add `#pragma comment(linker, "/INCLUDE:<public name>")` in its `.cpp` (public names: `llvm-pdbutil dump -publics`; grep `/INCLUDE` in `Docs/Parity/lessons.md`). Do not add a pragma for a function that a lifted caller keeps.

## Scope

28 functions, about 1,413 pseudocode lines (about 11,304 tokens). Stems: `datareaderimpl`.

The easy functions of this stem are in `lift-gamedaemon-e14`. Do not change them unless a fix needs it.

| n | Exe | RVA | PDB name | Stem | Lines |
| ---: | --- | --- | --- | --- | ---: |
| 1 | GD | `0x6eb480` | `DrDataReaderImpl::Close` | datareaderimpl | 9 |
| 2 | GD | `0x6eb4b0` | `DrDataReaderImpl::CreateElReader` | datareaderimpl | 19 |
| 3 | GD | `0x6eb500` | `DrDataReaderImpl::CreateAliasMap` | datareaderimpl | 19 |
| 4 | GD | `0x6eb550` | `DrDataReaderImpl::CreateAliasMapMT` | datareaderimpl | 19 |
| 5 | GD | `0x6eb5b0` | `DrDataReaderImpl::ReleaseAliasMapMT` | datareaderimpl | 17 |
| 6 | GD | `0x6eb610` | `DrDataReaderImpl::CreateQuestTable` | datareaderimpl | 19 |
| 7 | GD | `0x6eb660` | `DrDataReaderImpl::ReleaseTable` | datareaderimpl | 15 |
| 8 | GD | `0x6eb6b0` | `DrDataReaderImpl::loadAlias` | datareaderimpl | 66 |
| 9 | GD | `0x6eb860` | `XmlPieceAliasReader::Read` | datareaderimpl | 37 |
| 10 | GD | `0x6ebac0` | `DrDataReaderImpl::ReadBinaryDataFile` | datareaderimpl | 25 |
| 11 | GD | `0x6ebb80` | `DrDataReaderImpl::ReadBinaryDataFileStream` | datareaderimpl | 33 |
| 12 | GD | `0x6ebc40` | `DrDataReaderImpl::ReadBinaryDataFileFromMem` | datareaderimpl | 25 |
| 13 | GD | `0x6ebcd0` | `DrDataReaderImpl::clearDocument` | datareaderimpl | 29 |
| 14 | GD | `0x6ebd70` | `DrDataReaderImpl::createTable` | datareaderimpl | 50 |
| 15 | GD | `0x6ebe70` | `XmlPieceTableReader::Read` | datareaderimpl | 37 |
| 16 | GD | `0x6ebfc0` | `DrDataReaderImpl::ReleaseElReader` | datareaderimpl | 17 |
| 17 | GD | `0x6ec010` | `DrDataReaderImpl::ReleaseAliasMap` | datareaderimpl | 17 |
| 18 | GD | `0x6ec060` | `DrDataReaderImpl::LoadAlias` | datareaderimpl | 32 |
| 19 | GD | `0x6ec0d0` | `DrDataReaderImpl::LoadAliasMT` | datareaderimpl | 149 |
| 20 | GD | `0x6ec4c0` | `DrDataReaderImpl::loadTable` | datareaderimpl | 44 |
| 21 | GD | `0x6ec590` | `DrDataReaderImpl::loadTableMT` | datareaderimpl | 163 |
| 22 | GD | `0x6ec920` | `DrDataReaderImpl::loadTablePieceByPiece` | datareaderimpl | 100 |
| 23 | GD | `0x6ecb60` | `DrDataReaderImpl::LoadDocument` | datareaderimpl | 204 |
| 24 | GD | `0x6ed050` | `DrDataReaderImpl::Setup` | datareaderimpl | 29 |
| 25 | GD | `0x6ed0f0` | `DrDataReaderImpl::LoadAliasPieceByPiece` | datareaderimpl | 129 |
| 26 | GD | `0x6ed400` | `DrDataReaderImpl::LoadTable` | datareaderimpl | 19 |
| 27 | GD | `0x6ed450` | `DrDataReaderImpl::LoadTableMT` | datareaderimpl | 30 |
| 28 | GD | `0x6ed4c0` | `DrDataReaderImpl::LoadTablePieceByPiece` | datareaderimpl | 61 |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/datareaderimpl.cpp`
- `src/Server/GameDaemon/datareaderimpl.h`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-57.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
