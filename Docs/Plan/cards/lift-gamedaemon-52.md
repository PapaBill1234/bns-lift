# lift-gamedaemon-52: DataReader: datareader, defmemory_h, defmemory_cpp, src_stlmemory, ...

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
| Depends on | `lift-gamedaemon-e5`, `lift-gamedaemon-e14` |
| Pattern | `src/library/FsdReader/FsdDecomposer.cpp` |
| Plan | `Docs/Plan/gamedaemon-lift.md` sections 1, 3, 5 |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Grep `Docs/Parity/lessons.md` for A2 (block order), A6 (per-exe path literals), A12 (PDB member types), A18 (destructors), A21 (PDB facts) and A22 (per-exe source form). Do not read it in full.
- Pattern: `src/library/FsdReader/FsdDecomposer.cpp`. Read it one time. Use its form for the functions of this card.

## Scope

30 functions, about 1,716 pseudocode lines (about 13,728 tokens). Stems: `datareader`, `defmemory_h`, `defmemory_cpp`, `src_stlmemory`, `aliasimpl_h`, `aliasimpl_cpp`.

The easy functions of this stem are in `lift-gamedaemon-e5`, `lift-gamedaemon-e14`. Do not change them unless a fix needs it.

| n | Exe | RVA | PDB name | Stem | Lines |
| ---: | --- | --- | --- | --- | ---: |
| 1 | GD | `0x6eb2b0` | `SetupDataReader` | datareader | 8 |
| 2 | GD | `0x6eb2c0` | `CloseDataReader` | datareader | 8 |
| 3 | GD | `0x6eb2d0` | `CreateDataReader` | datareader | 19 |
| 4 | GD | `0x6eb330` | `ReleaseDataReader` | datareader | 14 |
| 5 | GD | `0x6ecf90` | `DrBaseStaticMemory::Instance` | defmemory_h | 15 |
| 6 | GD | `0x6ecff0` | `DrBaseDynamicMemory::Instance` | defmemory_h | 15 |
| 7 | GD | `0x6ed6a0` | `DrMemoryManager::Memory` | defmemory_cpp | 14 |
| 8 | GD | `0x6ee800` | `DrStlAllocator<wchar_t,1>::allocate` | src_stlmemory | 14 |
| 9 | GD | `0x6f35d0` | `DrStlAllocator<std::basic_string<wchar_t,std::char_traits<wchar_t>,DrStlAllocator<wchar_t,1> >,1>::deallocate` | src_stlmemory | 17 |
| 10 | GD | `0x6fd420` | `DrStlAllocator<DrEl * __ptr64,0>::deallocate` | src_stlmemory | 17 |
| 11 | GD | `0x6f3310` | `ci_wchar_traits::compare` | aliasimpl_h | 31 |
| 12 | GD | `0x6f33b0` | `DrAliasStringTable::Clear` | aliasimpl_cpp | 23 |
| 13 | GD | `0x6f3430` | `DrAliasStringTable::Find` | aliasimpl_cpp | 83 |
| 14 | GD | `0x6f3630` | `DrAliasMapImpl::ReplaceIfChanged` | aliasimpl_cpp | 43 |
| 15 | GD | `0x6f36d0` | `DrAliasStringTable::construct` | aliasimpl_cpp | 37 |
| 16 | GD | `0x6f3900` | `DrAliasStringTable::ReadFromBuffer` | aliasimpl_cpp | 60 |
| 17 | GD | `0x6f3a10` | `DrAliasStringTable::Build` | aliasimpl_cpp | 67 |
| 18 | GD | `0x6f3c70` | `DrAliasMapImpl::IsSubsetOf` | aliasimpl_cpp | 88 |
| 19 | GD | `0x6f3df0` | `DrAliasMapImpl::InsertInto` | aliasimpl_cpp | 46 |
| 20 | GD | `0x6f4280` | `DrAliasMapImpl::clearElArray` | aliasimpl_cpp | 46 |
| 21 | GD | `0x6f4490` | `DrAliasMapImpl::allocElArray` | aliasimpl_cpp | 80 |
| 22 | GD | `0x6f4860` | `DrAliasMapImpl::Find` | aliasimpl_cpp | 143 |
| 23 | GD | `0x6f4a90` | `DrAliasMapImpl::rebuildElArray` | aliasimpl_cpp | 126 |
| 24 | GD | `0x6f5780` | `DrAliasMapImpl::clearTableFromAliasMap` | aliasimpl_cpp | 100 |
| 25 | GD | `0x6f5b30` | `DrAliasMapImpl::Reconstruct` | aliasimpl_cpp | 14 |
| 26 | GD | `0x6f5d50` | `DrAliasMapImpl::Insert` | aliasimpl_cpp | 106 |
| 27 | GD | `0x6f5f40` | `DrAliasMapImpl::Clear` | aliasimpl_cpp | 22 |
| 28 | GD | `0x6f5fa0` | `DrAliasMapImpl::ReadFromBuffer` | aliasimpl_cpp | 175 |
| 29 | GD | `0x6f6320` | `DrAliasMapImpl::~DrAliasMapImpl` | aliasimpl_cpp | 41 |
| 30 | GD | `0x6f6490` | `DrAliasMapImpl::ClearTable` | aliasimpl_cpp | 244 |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/datareader.cpp`
- `src/Server/GameDaemon/datareader.h`
- `src/Server/GameDaemon/defmemory_h.cpp`
- `src/Server/GameDaemon/defmemory_h.h`
- `src/Server/GameDaemon/defmemory_cpp.cpp`
- `src/Server/GameDaemon/defmemory_cpp.h`
- `src/Server/GameDaemon/src_stlmemory.cpp`
- `src/Server/GameDaemon/src_stlmemory.h`
- `src/Server/GameDaemon/aliasimpl_h.cpp`
- `src/Server/GameDaemon/aliasimpl_h.h`
- `src/Server/GameDaemon/aliasimpl_cpp.cpp`
- `src/Server/GameDaemon/aliasimpl_cpp.h`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-52.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
