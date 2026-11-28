# Handoff: lift-gamedaemon-gap-086-w52 (card lift-gamedaemon-52)

## Lifted

- Stem `defmemory_cpp`: `DrMemoryManager::Memory` (0x6ed6a0). Formtest: SAME.
- Stem `aliasimpl_h`: `ci_wchar_traits::compare` (0x6f3310). Formtest: SAME.
- Stem `defmemory_h`: `DrBaseStaticMemory::Instance` (0x6ecf90, FORM), `DrBaseDynamicMemory::Instance` (0x6ecff0, SAME). This session added the keep pragma for `DrBaseDynamicMemory::Instance` (no lifted caller).
- Stem `src_stlmemory`: the 3 `DrStlAllocator` members (0x6ee800, 0x6f35d0, 0x6fd420). The template is in `drstlmemory.h`. The `.cpp` file instantiates the members. Formtest for 0x6ee800: SAME.
- Stem `datareader`: `SetupDataReader` (0x6eb2b0), `CloseDataReader` (0x6eb2c0), `CreateDataReader` (0x6eb2d0), `ReleaseDataReader` (0x6eb330). Formtest: SAME for all 4.
- Stem `aliasimpl_cpp`:
  - SAME: `DrAliasStringTable::Clear` (0x6f33b0), `DrAliasStringTable::construct` (0x6f36d0), `DrAliasMapImpl::InsertInto` (0x6f3df0), `DrAliasMapImpl::clearElArray` (0x6f4280), `DrAliasMapImpl::allocElArray` (0x6f4490), `DrAliasMapImpl::Clear` (0x6f5f40), `DrAliasMapImpl::~DrAliasMapImpl` (0x6f6320).
  - DIFF, logic is the same: `DrAliasStringTable::Find` (0x6f3430). The 2019 build keeps a null test of the stack buffer. The lift helper does not give it. `DrAliasStringTable::Build` (0x6f3a10): only the order of instructions differs.
  - DIFF by intent: `DrAliasStringTable::ReadFromBuffer` (0x6f3900). The 2019 build reads the buffer before it checks the size. The lift checks the size first (`// BUG:`). `DrAliasMapImpl::IsSubsetOf` (0x6f3c70). The 2019 build reads a null `tablename`. The lift returns false (`// BUG:`).
  - `DrAliasMapImpl::Reconstruct` (0x6f5b30): lifted. It calls the stub `rebuildElArray`, so formtest shows DIFF until that stub is lifted.

## Header changes

- `GameDaemonFwd.h`: `DrAliasMap` is now the PDB interface (13 pure virtual functions in slot order).
- `aliasimpl.h`: PDB types. `ci_wchar_traits` derives from `std::char_traits<wchar_t>`. `_aliasmap` has the PDB map type (ci string key, `DrStlAllocator`). `AliasArrayElement` and `DrAliasStringTable::ArrayElement` have the PDB members. `_stringTableSize` is `int` (PDB).
- `defmemory.h`: `DrNewArray<T>` is the inlined array helper of DefMemory.h (line 193). It has no PDB name (`// LIFT:`).

## Not done

- `DrAliasMapImpl::ReplaceIfChanged` (0x6f3630): it passes `*this` as `DrAliasMap const &`. That needs the `DrAliasMap` base class. The base needs bodies for `WriteSize` and `Print`. They are not in the index (folded), so their bodies are not known.
- `DrAliasMapImpl::Find` (0x6f4860): not done in this session (context limit).
- `DrAliasMapImpl::rebuildElArray` (0x6f4a90): not done in this session (context limit).
- `DrAliasMapImpl::clearTableFromAliasMap` (0x6f5780): not done in this session (context limit).
- `DrAliasMapImpl::Insert` (0x6f5d50): not done in this session (context limit).
- `DrAliasMapImpl::ReadFromBuffer` (0x6f5fa0): not done in this session (context limit).
- `DrAliasMapImpl::ClearTable` (0x6f6490): not done in this session (context limit).

## Round 2 fix

- The gate build failed: the include path has no `<cstddef>`. `drstlmemory.h` now includes `<stddef.h>`.
- `aliasimpl.h`, `aliasimpl_h.cpp` and `aliasimpl_cpp.cpp` used `<cwctype>`, `<cstring>` and `<cwchar>`. No other file in the tree uses these headers. They now include `<wctype.h>`, `<string.h>` and `<wchar.h>`. The code does not use `std::` names from these headers.
- Stem `datareader` needs no change in this round. Round 1 lifted its 4 functions.

## Open items

- `DrAliasMapImpl::DrAliasMapImpl` (0x6f6450) stays DIFF (it was DIFF in the baseline). The class has no `DrAliasMap` base, so the vtable differs.
- The driver runs the gate and the MATCH comparison.

## Files changed

- `src/Server/GameDaemon/GameDaemonFwd.h`
- `src/Server/GameDaemon/aliasimpl.h`
- `src/Server/GameDaemon/aliasimpl_cpp.cpp`
- `src/Server/GameDaemon/aliasimpl_h.cpp`
- `src/Server/GameDaemon/datareader.cpp`
- `src/Server/GameDaemon/defmemory.h`
- `src/Server/GameDaemon/defmemory_cpp.cpp`
- `src/Server/GameDaemon/defmemory_h.cpp`
- `src/Server/GameDaemon/drstlmemory.h`
- `src/Server/GameDaemon/src_stlmemory.cpp`
- `src/Server/GameDaemon/stlmemory.h`
