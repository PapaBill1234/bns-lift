# lift-gamedaemon-49: DataReader: tableimpl_cpp, questtableimpl_h, binarydatafile, associativetable_h, ...

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
| Depends on | `lift-gamedaemon-40`, `lift-gamedaemon-47` |
| Pattern | `src/library/FsdReader/FsdDecomposer.cpp` |
| Plan | `Docs/Plan/gamedaemon-lift.md` sections 1, 3, 5 |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Grep `Docs/Parity/lessons.md` for A2 (block order), A6 (per-exe path literals), A12 (PDB member types), A18 (destructors), A21 (PDB facts) and A22 (per-exe source form). Do not read it in full.
- Pattern: `src/library/FsdReader/FsdDecomposer.cpp`. Read it one time. Use its form for the functions of this card.

## Scope

22 functions, about 919 pseudocode lines (about 7,352 tokens). Stems: `tableimpl_cpp`, `questtableimpl_h`, `binarydatafile`, `associativetable_h`, `tableimpl_h`, `autokeytable_h`.

| n | Exe | RVA | PDB name | Stem | Lines |
| ---: | --- | --- | --- | --- | ---: |
| 1 | GD | `0x6f7430` | `DrDataTableImpl::~DrDataTableImpl` | tableimpl_cpp | 7 |
| 2 | GD | `0x6feec0` | `DrDataTableImpl::ReferenceCopiedEl` | tableimpl_cpp | 7 |
| 3 | GD | `0x6feed0` | `DrDataTableImpl::Find` | tableimpl_cpp | 26 |
| 4 | GD | `0x6fefa0` | `DrDataTableImpl::DrDataTableImpl` | tableimpl_cpp | 11 |
| 5 | GD | `0x6f86e0` | `QuestTableImpl::GetMaxQuestId` | questtableimpl_h | 7 |
| 6 | GD | `0x6f86f0` | `QuestTableImpl::GetQuestByIndex` | questtableimpl_h | 7 |
| 7 | GD | `0x6f8700` | `QuestTableImpl::GetMaxQuestNum` | questtableimpl_h | 7 |
| 8 | GD | `0x6fa370` | `BinaryDataFile::readFromMem` | binarydatafile | 187 |
| 9 | GD | `0x6fa7b0` | `BinaryDataFile::readFromFileStream` | binarydatafile | 190 |
| 10 | GD | `0x6fac30` | `BinaryDataFile::ReadFromMem` | binarydatafile | 40 |
| 11 | GD | `0x6fad10` | `BinaryDataFile::ReadFromFileStream` | binarydatafile | 40 |
| 12 | GD | `0x6fade0` | `BinaryDataFile::ReadFromFile` | binarydatafile | 80 |
| 13 | GD | `0x6faff0` | `BinaryDataFile::ReadFromFileStream` | binarydatafile | 52 |
| 14 | GD | `0x6fb130` | `DrMultiKeyInnerIter::Ptr` | associativetable_h | 10 |
| 15 | GD | `0x6fb170` | `DrMultiKeyInnerIter::Next` | associativetable_h | 11 |
| 16 | GD | `0x6fb180` | `DrMultiKeyInnerIter::IsValid` | associativetable_h | 19 |
| 17 | GD | `0x6fcd10` | `DrMultiKeyElMap::get` | associativetable_h | 74 |
| 18 | GD | `0x6fd0f0` | `DrMultiKeyElMap::set` | associativetable_h | 86 |
| 19 | GD | `0x6fd290` | `DrDataTableImpl::UseLegacyElHeader` | tableimpl_h | 7 |
| 20 | GD | `0x6fd300` | `DrAutoKeyInnerIter::IsValid` | autokeytable_h | 19 |
| 21 | GD | `0x6fd450` | `DrAutoKeyInnerIter::Ptr` | autokeytable_h | 10 |
| 22 | GD | `0x6fd480` | `DrAutoKeyInnerIter::Next` | autokeytable_h | 22 |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/tableimpl_cpp.cpp`
- `src/Server/GameDaemon/tableimpl_cpp.h`
- `src/Server/GameDaemon/questtableimpl_h.cpp`
- `src/Server/GameDaemon/questtableimpl_h.h`
- `src/Server/GameDaemon/binarydatafile.cpp`
- `src/Server/GameDaemon/binarydatafile.h`
- `src/Server/GameDaemon/associativetable_h.cpp`
- `src/Server/GameDaemon/associativetable_h.h`
- `src/Server/GameDaemon/tableimpl_h.cpp`
- `src/Server/GameDaemon/tableimpl_h.h`
- `src/Server/GameDaemon/autokeytable_h.cpp`
- `src/Server/GameDaemon/autokeytable_h.h`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-49.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
