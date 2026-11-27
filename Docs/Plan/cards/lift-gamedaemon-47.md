# lift-gamedaemon-47: DataReader: defmemory_cpp, datareader, deflog, defmemory_h, ...

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
| Depends on | `lift-gamedaemon-0e` |
| Pattern | `src/library/FsdReader/FsdDecomposer.cpp` |
| Plan | `Docs/Plan/gamedaemon-lift.md` sections 1, 3, 5 |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Grep `Docs/Parity/lessons.md` for A2 (block order), A6 (per-exe path literals), A12 (PDB member types), A18 (destructors), A21 (PDB facts) and A22 (per-exe source form). Do not read it in full.
- Pattern: `src/library/FsdReader/FsdDecomposer.cpp`. Read it one time. Use its form for the functions of this card.

## Scope

20 functions, about 255 pseudocode lines (about 2,040 tokens). Stems: `defmemory_cpp`, `datareader`, `deflog`, `defmemory_h`, `src_stlmemory`, `aliasimpl_h`.

| n | Exe | RVA | PDB name | Stem | Lines |
| ---: | --- | --- | --- | --- | ---: |
| 1 | GD | `0x6b7dc0` | `DrHeapMemory::Realloc` | defmemory_cpp | 13 |
| 2 | GD | `0x6b7e10` | `DrHeapMemory::Free` | defmemory_cpp | 7 |
| 3 | GD | `0x6ed5c0` | `DrMemoryManager::SetupMemory` | defmemory_cpp | 10 |
| 4 | GD | `0x6ed5e0` | `DrHeapMemory::~DrHeapMemory` | defmemory_cpp | 8 |
| 5 | GD | `0x6ed600` | `DrHeapMemory::Alloc` | defmemory_cpp | 7 |
| 6 | GD | `0x6ed620` | `DrHeapMemory::DrHeapMemory` | defmemory_cpp | 10 |
| 7 | GD | `0x6ed6a0` | `DrMemoryManager::Memory` | defmemory_cpp | 14 |
| 8 | GD | `0x6eb2a0` | `GetDataReaderInterfaceVersion` | datareader | 7 |
| 9 | GD | `0x6eb2b0` | `SetupDataReader` | datareader | 8 |
| 10 | GD | `0x6eb2c0` | `CloseDataReader` | datareader | 8 |
| 11 | GD | `0x6eb2d0` | `CreateDataReader` | datareader | 19 |
| 12 | GD | `0x6eb320` | `Logger` | datareader | 7 |
| 13 | GD | `0x6eb330` | `ReleaseDataReader` | datareader | 14 |
| 14 | GD | `0x6eb380` | `DrDefLog::Write` | deflog | 14 |
| 15 | GD | `0x6ecf90` | `DrBaseStaticMemory::Instance` | defmemory_h | 15 |
| 16 | GD | `0x6ecff0` | `DrBaseDynamicMemory::Instance` | defmemory_h | 15 |
| 17 | GD | `0x6ee800` | `DrStlAllocator<wchar_t,1>::allocate` | src_stlmemory | 14 |
| 18 | GD | `0x6f35d0` | `DrStlAllocator<std::basic_string<wchar_t,std::char_traits<wchar_t>,DrStlAllocator<wchar_t,1> >,1>::deallocate` | src_stlmemory | 17 |
| 19 | GD | `0x6fd420` | `DrStlAllocator<DrEl * __ptr64,0>::deallocate` | src_stlmemory | 17 |
| 20 | GD | `0x6f3310` | `ci_wchar_traits::compare` | aliasimpl_h | 31 |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/defmemory_cpp.cpp`
- `src/Server/GameDaemon/defmemory_cpp.h`
- `src/Server/GameDaemon/datareader.cpp`
- `src/Server/GameDaemon/datareader.h`
- `src/Server/GameDaemon/deflog.cpp`
- `src/Server/GameDaemon/deflog.h`
- `src/Server/GameDaemon/defmemory_h.cpp`
- `src/Server/GameDaemon/defmemory_h.h`
- `src/Server/GameDaemon/src_stlmemory.cpp`
- `src/Server/GameDaemon/src_stlmemory.h`
- `src/Server/GameDaemon/aliasimpl_h.cpp`
- `src/Server/GameDaemon/aliasimpl_h.h`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-47.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
