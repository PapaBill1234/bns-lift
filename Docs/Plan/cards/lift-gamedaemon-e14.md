# lift-gamedaemon-e14: Easy leaves (DataReader and Data packer): associativetable_cpp, defmemory_cpp, md5, datareaderimpl, ...

| Item | Value |
| --- | --- |
| Exe | GD |
| Source build | GameDaemon 2019 + PDB (VS2010 SP1) |
| Exe file | `<work-root>/ida/lift/GameDaemon/GameDaemon.exe` |
| PDB | `<work-root>/ida/lift/GameDaemon/GameDaemon.pdb` |
| Pseudocode | `~/.cache/bns-lift/hr/GameDaemon/<stem>.c` |
| Pseudocode index | `~/.cache/bns-lift/hr/GameDaemon/index.tsv` (stem, rva, name, first, last, status, source file, part) |
| Wave | E |
| Model | opus |
| Depends on | `lift-gamedaemon-0e` |
| Pattern | `src/library/FsdReader/FsdDecomposer.cpp` |
| Plan | `Docs/Plan/gamedaemon-lift.md` sections 1, 3, 5 |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Grep `Docs/Parity/lessons.md` for A2 (block order), A6 (per-exe path literals), A12 (PDB member types), A18 (destructors), A21 (PDB facts) and A22 (per-exe source form). Do not read it in full.
- Pattern: `src/library/FsdReader/FsdDecomposer.cpp`. Read it one time. Use its form for the functions of this card.
- Dead-strip: `wmain` and most callers are still `LIFT_STUB` bodies. `/OPT:REF` removes a lifted function that has no live caller, and funcdiff then cannot pair it. For each function in scope with no live caller, add `#pragma comment(linker, "/INCLUDE:<public name>")` in its `.cpp` (public names: `llvm-pdbutil dump -publics`; grep `/INCLUDE` in `Docs/Parity/lessons.md`). Do not add a pragma for a function that a lifted caller keeps.

## Scope

40 functions, about 534 pseudocode lines (about 4,272 tokens). Stems: `associativetable_cpp`, `defmemory_cpp`, `md5`, `datareaderimpl`, `questtableimpl_cpp`, `autokeytable_cpp`, `associativetable_h`, `deflog`, `aliasimpl_cpp`, `parallelworker`, `autokeytable_h`, `datapacker`.

Wave E (owner order 2026-11-27: the easiest work first). Each function in this card is a leaf: its body calls no other counted function that needs a lift. Thus a `LIFT_STUB` callee cannot keep it DIFF. Each function has at most 30 pseudocode lines. Ease key: 13.3 cost per function (rule in `Docs/Plan/gamedaemon-lift.md` section 3).

Lift only the functions in the table. The other functions of these stems are in later W cards. Those cards depend on this card.

| n | Exe | RVA | PDB name | Stem | Lines | Form |
| ---: | --- | --- | --- | --- | ---: | --- |
| 1 | GD | `0x6fb330` | `DrMultiKeyTable::Find` | associativetable_cpp | 7 | leaf |
| 2 | GD | `0x6fb440` | `DrMultiKeyElMap::count` | associativetable_cpp | 10 | leaf |
| 3 | GD | `0x6b7dc0` | `DrHeapMemory::Realloc` | defmemory_cpp | 13 | leaf |
| 4 | GD | `0x6b7e10` | `DrHeapMemory::Free` | defmemory_cpp | 7 | leaf |
| 5 | GD | `0x6ed5c0` | `DrMemoryManager::SetupMemory` | defmemory_cpp | 10 | leaf |
| 6 | GD | `0x6ed5e0` | `DrHeapMemory::~DrHeapMemory` | defmemory_cpp | 8 | xtor |
| 7 | GD | `0x6ed600` | `DrHeapMemory::Alloc` | defmemory_cpp | 7 | leaf |
| 8 | GD | `0x6ed620` | `DrHeapMemory::DrHeapMemory` | defmemory_cpp | 10 | xtor |
| 9 | GD | `0x6ff850` | `md5_init` | md5 | 11 | leaf |
| 10 | GD | `0x6eb470` | `DrDataReaderImpl::~DrDataReaderImpl` | datareaderimpl | 7 | xtor |
| 11 | GD | `0x6eb9a0` | `loadAliasWorker` | datareaderimpl | 12 | leaf |
| 12 | GD | `0x6eba00` | `LoadTableMT_PreProcBinder::Execute` | datareaderimpl | 13 | leaf |
| 13 | GD | `0x6eba40` | `LoadTableMT_PostProcBinder::Execute` | datareaderimpl | 13 | leaf |
| 14 | GD | `0x6ebc90` | `loadTableWorker` | datareaderimpl | 13 | leaf |
| 15 | GD | `0x6ebfb0` | `DrDataReaderImpl::DrDataReaderImpl` | datareaderimpl | 8 | xtor |
| 16 | GD | `0x6ec450` | `LoadTableBinder::Execute` | datareaderimpl | 16 | leaf |
| 17 | GD | `0x6f86a0` | `QuestTableImpl::GetQuest` | questtableimpl_cpp | 13 | leaf |
| 18 | GD | `0x6fa2f0` | `QuestTableImpl::QuestTableImpl` | questtableimpl_cpp | 12 | xtor |
| 19 | GD | `0x6fd410` | `DrAutoKeyTable::FinishLoadAlias` | autokeytable_cpp | 7 | setter |
| 20 | GD | `0x6fd790` | `DrAutoKeyTable::Find` | autokeytable_cpp | 10 | leaf |
| 21 | GD | `0x6fda40` | `DrAutoKeyElMap::destroy` | autokeytable_cpp | 21 | leaf |
| 22 | GD | `0x6fb130` | `DrMultiKeyInnerIter::Ptr` | associativetable_h | 10 | leaf |
| 23 | GD | `0x6fb170` | `DrMultiKeyInnerIter::Next` | associativetable_h | 11 | leaf |
| 24 | GD | `0x6fb180` | `DrMultiKeyInnerIter::IsValid` | associativetable_h | 19 | leaf |
| 25 | GD | `0x6eb380` | `DrDefLog::Write` | deflog | 14 | leaf |
| 26 | GD | `0x6f33a0` | `DrAliasMapImpl::WriteToBuffer` | aliasimpl_cpp | 10 | getter |
| 27 | GD | `0x6f3610` | `DrAliasMapImpl::Count` | aliasimpl_cpp | 17 | leaf |
| 28 | GD | `0x6f6450` | `DrAliasMapImpl::DrAliasMapImpl` | aliasimpl_cpp | 17 | leaf |
| 29 | GD | `0x6fea70` | `DrParallelWorkerManager::Init` | parallelworker | 23 | leaf |
| 30 | GD | `0x6fead0` | `DrParallelWorkerManager::SetWorkerFunc` | parallelworker | 10 | leaf |
| 31 | GD | `0x6feae0` | `DrParallelWorkerManager::SetWorkerInitFunc` | parallelworker | 8 | leaf |
| 32 | GD | `0x6feaf0` | `DrParallelWorkerManager::Execute` | parallelworker | 7 | leaf |
| 33 | GD | `0x6fecb0` | `DrParallelWorkerManager::StartWorkerPool` | parallelworker | 27 | leaf |
| 34 | GD | `0x6fd300` | `DrAutoKeyInnerIter::IsValid` | autokeytable_h | 19 | leaf |
| 35 | GD | `0x6fd450` | `DrAutoKeyInnerIter::Ptr` | autokeytable_h | 10 | leaf |
| 36 | GD | `0x6fd480` | `DrAutoKeyInnerIter::Next` | autokeytable_h | 22 | leaf |
| 37 | GD | `0x16b60` | `ZipPackedReaderIO::GetFileSize` | datapacker | 24 | leaf |
| 38 | GD | `0x16bd0` | `ZipPackedReaderIO::GetFileName` | datapacker | 30 | leaf |
| 39 | GD | `0x16c40` | `ZipPackedReaderIO::Next` | datapacker | 16 | leaf |
| 40 | GD | `0x16c70` | `ZipPackedReaderIO::Close` | datapacker | 12 | leaf |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/associativetable_cpp.cpp`
- `src/Server/GameDaemon/associativetable_cpp.h`
- `src/Server/GameDaemon/defmemory_cpp.cpp`
- `src/Server/GameDaemon/defmemory_cpp.h`
- `src/Server/GameDaemon/md5.cpp`
- `src/Server/GameDaemon/md5.h`
- `src/Server/GameDaemon/datareaderimpl.cpp`
- `src/Server/GameDaemon/datareaderimpl.h`
- `src/Server/GameDaemon/questtableimpl_cpp.cpp`
- `src/Server/GameDaemon/questtableimpl_cpp.h`
- `src/Server/GameDaemon/autokeytable_cpp.cpp`
- `src/Server/GameDaemon/autokeytable_cpp.h`
- `src/Server/GameDaemon/associativetable_h.cpp`
- `src/Server/GameDaemon/associativetable_h.h`
- `src/Server/GameDaemon/deflog.cpp`
- `src/Server/GameDaemon/deflog.h`
- `src/Server/GameDaemon/aliasimpl_cpp.cpp`
- `src/Server/GameDaemon/aliasimpl_cpp.h`
- `src/Server/GameDaemon/parallelworker.cpp`
- `src/Server/GameDaemon/parallelworker.h`
- `src/Server/GameDaemon/autokeytable_h.cpp`
- `src/Server/GameDaemon/autokeytable_h.h`
- `src/Server/GameDaemon/datapacker.cpp`
- `src/Server/GameDaemon/datapacker.h`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-e14.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
