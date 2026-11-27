# Handoff: lift-gamedaemon-gap-014-e14 (card lift-gamedaemon-e14)

Source: GameDaemon 2019 + PDB. Round 2. The driver does the build, the gate and the MATCH comparison. This session did not run them.

## Lifted (35)

- md5: `md5_init` (0x6ff850).
- deflog: `DrDefLog::Write` (0x6eb380).
- defmemory_cpp: `DrMemoryManager::SetupMemory` (0x6ed5c0), `DrHeapMemory::~DrHeapMemory` (0x6ed5e0), `DrHeapMemory::Alloc` (0x6ed600), `DrHeapMemory::DrHeapMemory` (0x6ed620).
- associativetable_cpp: `DrMultiKeyTable::Find` (0x6fb330), `DrMultiKeyElMap::count` (0x6fb440).
- associativetable_h: `DrMultiKeyInnerIter::Ptr` (0x6fb130), `Next` (0x6fb170), `IsValid` (0x6fb180).
- autokeytable_cpp: `DrAutoKeyTable::FinishLoadAlias` (0x6fd410), `DrAutoKeyTable::Find` (0x6fd790), `DrAutoKeyElMap::destroy` (0x6fda40).
- autokeytable_h: `DrAutoKeyInnerIter::IsValid` (0x6fd300), `Ptr` (0x6fd450), `Next` (0x6fd480).
- questtableimpl_cpp: `QuestTableImpl::GetQuest` (0x6f86a0), `QuestTableImpl::QuestTableImpl` (0x6fa2f0).
- aliasimpl_cpp: `DrAliasMapImpl::WriteToBuffer` (0x6f33a0), `Count` (0x6f3610), `DrAliasMapImpl` (0x6f6450).
- parallelworker: `DrParallelWorkerManager::Init` (0x6fea70), `SetWorkerFunc` (0x6fead0), `SetWorkerInitFunc` (0x6feae0), `Execute` (0x6feaf0), `StartWorkerPool` (0x6fecb0).
- datapacker: `ZipPackedReaderIO::Next` (0x16c40), `Close` (0x16c70).
- datareaderimpl: `DrDataReaderImpl::~DrDataReaderImpl` (0x6eb470), `LoadTableMT_PreProcBinder::Execute` (0x6eba00), `LoadTableMT_PostProcBinder::Execute` (0x6eba40), `loadTableWorker` (0x6ebc90), `DrDataReaderImpl::DrDataReaderImpl` (0x6ebfb0), `LoadTableBinder::Execute` (0x6ec450).

## Not done (3)

- `ZipPackedReaderIO::GetFileSize` (0x16b60). It needs the GameDaemon forms of AlertSender::writev2 / Log::Write (shared card s2). The `LIFT_STUB` stays. The `/INCLUDE` pragma is removed.
- `ZipPackedReaderIO::GetFileName` (0x16bd0). It needs the GameDaemon forms of AlertSender::writev2 / Log::Write (shared card s2). The `LIFT_STUB` stays. The `/INCLUDE` pragma is removed.

- `loadAliasWorker` (0x6eb9a0). The PDB gives no type for the argument block. The pseudocode shows only 2 of the 4 arguments of the `DrTable::LoadAlias` call. One look-up did not give the layout. The `LIFT_STUB` stays.

## Decisions

- `DrTable` (winserviceconsole_gd.h) now has the PDB vtable (19 slots). No lifted class derives from it and nothing constructs it. Thus its non-pure members have no definition.
- `DrDataReaderImpl::LoadFuncBinder` has slot 0 dtor and slot 1 `Execute`. The three binders do not derive from it yet.
- `loadTableWorker` uses a local argument struct. The PDB has no name for it (`// LIFT:` note).
- `ZipPackedReaderIO` does not derive from `XmlReaderIO` yet. The BloodLib `XmlReaderIO` declares `int` returns, not `ErrCode`. The members use the VS2010 `std` containers. They have the same layout as the PDB `StlAllocator<T, 2>` containers.
- `ZipPackedReaderIO::Next` returns the raw values 3 and 0. The PDB has no enumerators for `XmlReaderIO::ErrCode` (`// ❓`).
- `DrParallelWorkerManager::Init` returns true when `CreateIoCompletionPort` fails. This is the original logic (`// BUG:`).
- `DrParallelWorkerManager::Execute` returns `PostQueuedCompletionStatus(...) ? 0 : -1`. This gives the original `setne; lea` form.
- `DrAutoKeyTable::Find` tests `key < elCount` first and returns the element. The null return is last, as in the original block order.
- `DrMultiKeyElMap` declares its virtuals in the PDB slot order: `clearLink` 0, `construct` 1, `set` 2, `get` 3, `count` 4. The exe has no separate body for `clearLink` and `construct`. Thus they have empty inline bodies (`// ❓`). `DrMultiKeyTable::Find` now calls `get` through slot 3.
- `DrAliasStringTable` has its PDB member offsets. The pointer types of `_elArray` and `_stringTable` are placeholders.
- `DrEl` has its 3 PDB members (`type`, `subtype`, `size`; size 0x6).
- `DrDataTableImpl` has its 3 PDB members (`_tabledef` +8, `_uselowmemory` +0x10, `_useLegacyElHeader` +0x11). Its own virtual destructor gives the vfptr at +0. The base `DrDataTable : DrTable` is not declared yet: `DrTable` has no defined members, so a base gives unresolved externals (`// LIFT:` note).
- `DrAutoKeyTable` and `DrMultiKeyTable` derive from `DrDataTableImpl`. The invented `_dataTableImplPad` is removed.
- `DrHeapMemory::Realloc` (0x6b7dc0) uses the same source form as the BloodLib `HeapMemoryManager::Realloc` (`ptr == nullptr` test first). The linker folds the 2 bodies only when the code is the same. The inverted test of round 4 stopped the fold and lost the baseline MATCH.
- Each lifted function with no live caller has a dead-strip `/INCLUDE` pragma with a `// LIFT:` note. A virtual function that a lifted ctor keeps has no pragma.

## Files changed

- `src/Server/GameDaemon/GameDaemonFwd.h`
- `src/Server/GameDaemon/aliasimpl.h`, `aliasimpl_cpp.cpp`
- `src/Server/GameDaemon/associativetable.h`, `associativetable_cpp.cpp`, `associativetable_h.cpp`
- `src/Server/GameDaemon/autokeytable.h`, `autokeytable_cpp.cpp`, `autokeytable_h.cpp`
- `src/Server/GameDaemon/datapacker.h`, `datapacker.cpp`
- `src/Server/GameDaemon/datareaderimpl.h`, `datareaderimpl.cpp`
- `src/Server/GameDaemon/deflog.h`, `deflog.cpp`
- `src/Server/GameDaemon/defmemory.h`, `defmemory_cpp.cpp`
- `src/Server/GameDaemon/md5.h`, `md5.c`
- `src/Server/GameDaemon/parallelworker.h`, `parallelworker.cpp`
- `src/Server/GameDaemon/questtableimpl.h`, `questtableimpl_cpp.cpp`
- `src/Server/GameDaemon/tableimpl.h`
- `src/Server/GameDaemon/winserviceconsole_gd.h`
- `Docs/Plan/handoffs/lift-gamedaemon-gap-014-e14.md`

## Gate and MATCH

Not run in this session. The driver builds REF and NOREF and records the gate result and the MATCH comparison.

Round 3 repair: the round 2 gate build failed. Cause: `datapacker.h` included `<list>`. The VS2010 header set of the repo has no `<list>`. Round 3 removes the include. `ZipPackedReaderIO::FileList` is now a size-only placeholder (0x18). `FileItrArray` holds pointers to the VS2010 list node (`_Next`, `_Prev`, `_Myval`). A release list iterator holds only this pointer, so the code reads the same offsets. No other change.

Round 7 repair: the source guard compared the tree with the old base `ad572b7`. The lead rebased the card onto main `2840a78`. Thus the guard counted main commits (E5, E11 and the parity commits) as card changes: `Docs/Parity/baseline/GameDaemon.json`, `Docs/Parity/progress.tsv`, `README.md` and the `/INCLUDE` pragmas in `accessoryproperty.cpp`, `accountinventorytran_h.cpp` and `acquiredskill1.cpp`. These files are not card changes. The diff from `2840a78` to the card head changes only `src/Server/GameDaemon/**` and this handoff. The driver must use `2840a78` as the base. This card has one `/INCLUDE` pragma: `aliasimpl_cpp.cpp:5` (`DrAliasMapImpl::DrAliasMapImpl`). It has the `// LIFT:` note and goes to review, because no lifted caller keeps this constructor alive. Round 7 changes no code.

Round 8 repair: the guard gave the same result as round 7. The cause is the same: the guard used the old base `ad572b7`, not `2840a78`. The flagged files `Docs/Parity/baseline/GameDaemon.json`, `Docs/Parity/progress.tsv`, `README.md`, `accessoryproperty.cpp`, `accountinventorytran_h.cpp` and `acquiredskill1.cpp` come from main commits. This session cannot fix the issue in the source. A revert of main work would break main. Correction to the round 7 note: this card has 31 `/INCLUDE` pragmas, not one. They are in `aliasimpl_cpp.cpp`, `associativetable_cpp.cpp`, `associativetable_h.cpp`, `autokeytable_cpp.cpp`, `autokeytable_h.cpp`, `datapacker.cpp`, `datareaderimpl.cpp`, `deflog.cpp`, `defmemory_cpp.cpp`, `md5.c`, `parallelworker.cpp` and `questtableimpl_cpp.cpp`. Each pragma has the `// LIFT: dead-strip keep (no live caller yet)` note, so it goes to review. Action for the lead: set the card base to `2840a78` in the driver, then run the guard again. Round 8 changes no code.
