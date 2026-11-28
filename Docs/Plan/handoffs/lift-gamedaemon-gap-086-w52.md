# Handoff: lift-gamedaemon-gap-086-w52 (card lift-gamedaemon-52)

## Lifted

- Stem `defmemory_cpp`: `DrMemoryManager::Memory` (0x6ed6a0). Formtest: SAME.
- Stem `aliasimpl_h`: `ci_wchar_traits::compare` (0x6f3310). Formtest: SAME.
- Stem `defmemory_h`: no lifted body. Round 5 put both `Instance` bodies back to `LIFT_STUB` (see "Not done").
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

- `DrBaseStaticMemory::Instance` (0x6ecf90): LTCG + ICF folds the `DrHeapMemory` vftable with the derived vftables (the original keeps a separate derived deleting dtor at 0x6eb430 that calls `~DrHeapMemory` out of line). Needs a later card.
- `DrBaseDynamicMemory::Instance` (0x6ecff0): LTCG + ICF folds the `DrHeapMemory` vftable with the derived vftables (the original keeps a separate derived deleting dtor at 0x6eb430 that calls `~DrHeapMemory` out of line). Needs a later card.
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

## Round 3 fix

- Proof fail: `DrHeapMemory::DrHeapMemory` (0x6ed620) went from 1.0 to 0.9333. The 2 `Instance` bodies are the first callers of the ctor. The original calls the ctor out of line from both `Instance` bodies, then writes the vftable, then calls `atexit`. LTCG probably inlines the ctor into the new callers and changes its emitted form.
- Fix (lessons A4): `defmemory.h` declares the ctor `__declspec(noinline)` with a `// LIFT:` note. The `Instance` bodies stay lifted.
- This session could not run formtest (shell access was denied). The driver build is the proof. If the ctor is still not MATCH, the next round must put `DrBaseStaticMemory::Instance` (0x6ecf90) and `DrBaseDynamicMemory::Instance` (0x6ecff0) back to `LIFT_STUB` and record them as **Not done**.
- Stem `datareader` needs no change in this round.

## Round 4 fix

- Cause: ICF folded the `DrHeapMemory` vftable with the `DrBaseDynamicMemory` vftable. The ctor (0x6ed620) then loaded the wrong vftable. The round 3 `noinline` was not the cause.
- Fix: `defmemory.h` no longer has `__declspec(noinline)` on the `DrHeapMemory` ctor.
- Fix: `DrBaseStaticMemory` and `DrBaseDynamicMemory` declare their PDB virtual dtors. `defmemory_h.cpp` defines them as empty bodies, apart from `~DrHeapMemory`. Their deleting dtor calls `DrHeapMemory::~DrHeapMemory` out of line. The `DrHeapMemory` deleting dtor keeps the inline body. Thus slot 3 differs and the vftables do not fold.
- Formtest (no LTCG): the ctor 0x6ed620 is SAME. `Instance` 0x6ecf90 is FORM, 0x6ecff0 is SAME.
- Known residue: the derived deleting dtor 0x6eb430 shows DIFF 2. The explicit dtor writes the derived vftable before the call; the original does not. 0x6eb430 was not MATCH in the baseline. This residue also stops the fold of the 2 derived vftables with each other.
- If the driver proof still fails on 0x6ed620: put `DrBaseStaticMemory::Instance` (0x6ecf90) and `DrBaseDynamicMemory::Instance` (0x6ecff0) back to `LIFT_STUB` and remove the 2 derived dtors.

## Round 5 fix

- Cause: the round 4 driver build (LTCG) still loads `??_7DrBaseDynamicMemory@@6B@` in the ctor 0x6ed620. LTCG inlines the empty derived dtors and removes the derived vftable store. Then ICF folds the 3 vftables and the 6 deleting dtors. The round 4 formtest ran without LTCG, so it did not show this.
- Fix: `defmemory_h.cpp` has the 2 `Instance` bodies as `LIFT_STUB` again (base form, includes `LiftStub.h`). The keep pragma of `DrBaseDynamicMemory::Instance` is removed.
- Fix: `defmemory.h` no longer declares the 2 derived dtors, and `defmemory_h.cpp` no longer defines them. The 2 classes keep the PDB base `DrHeapMemory`. No code constructs them, so the build emits no derived vftable.
- All other lifted bodies have no change. This session could not run formtest (shell access was denied). The driver build is the proof.

## Round 6 fix

- Review rejected `DrAliasStringTable::Find` (0x6f3430): P2_cc (build `jge`, original `je`, index 2).
- Fix: `Find` is a `LIFT_STUB` again. Its keep pragma is removed.

### Not done

- `DrAliasStringTable::Find` (0x6f3430): P2_cc reject in review. A later card lifts it.

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
