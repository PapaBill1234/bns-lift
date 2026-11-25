# lift-1: PDB type generator and VS2010 STL subset

Repo: bns-lift (PRIVATE). IDA database: `<work-root>/ida/lift/CacheGate/CacheGate.exe` (only for checks of layouts).
PDB: `<work-root>/Service_348_8349/Service/CacheGate/bin/CacheGate.pdb`.

## Goal
1. A generator that writes C++ headers for the types in a server PDB.
2. An STL subset with the VS2010 x64 object layout.

## Tasks
1. `tools/pdb2h.py`: read `llvm-pdbutil dump -types` (and `-symbols` for globals) of a PDB. Write `include/pdb/<Server>/types.h`:
   - structs, classes, unions, enums, with member offsets as `static_assert(offsetof(...) == 0x..)`;
   - virtual methods in vtable order;
   - base classes;
   - skip CRT and STL internals; map `std::` types to `include/vs2010/`.
   Order the types so that each header compiles (forward declarations for pointers).
2. `include/vs2010/`: `xstring` (`std::basic_string` with the 16-byte SSO buffer, size, capacity: 0x20 bytes for `char` on x64), `vector`, `list`, `map`/`set` (red-black tree with `_Myhead`, `_Mysize`), `deque`, `utility`, `memory` (only what the PDB uses). Take the member offsets from the PDB types. Use `msvcp100.dll` exports (`_Xlength_error`, `_Xout_of_range`) through `libmsvcp100.a`.
3. Add a static_assert test for each container size and member offset in `src/selftest/`.
4. Run the generator on CacheGate. The output header must compile with `tools/gate.sh`.

## Files
- `tools/pdb2h.py`
- `include/vs2010/`
- `include/pdb/`
- `src/selftest/`
- `CMakeLists.txt`

## Done when
- `tools/gate.sh` prints `gate ok`.
- `include/pdb/CacheGate/types.h` compiles.
