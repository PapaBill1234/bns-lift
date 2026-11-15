# lift-1 handoff: PDB type generator and VS2010 STL subset

## Done
- `include/vs2010/`: xstddef, new, utility, xutility, memory, xstring, string, vector, xtree,
  map, set (also multimap, multiset), deque, algorithm (heap), queue (queue, priority_queue).
  Layouts (x64, from the PDB and IDA): string 0x28 (the card says 0x20; the PDB gives 0x28),
  vector 0x20, map/set 0x20, tree node 0x30, deque 0x30, deque iterator 0x18, priority_queue 0x28.
- `src/selftest/stl_layout.cpp`: static_asserts for container sizes and member offsets.
- `src/selftest/pdb_types.cpp`: compiles `include/pdb/CacheGate/types.h`.
- `CMakeLists.txt`: makes `build/msvcp100.lib` from a .def file (Wine has no libmsvcp100.a).
- `tools/pdb2h.py`: reads the PDB directly (MSF, TPI, DBI), not through llvm-pdbutil.
  Writes enums, structs, bases, virtual methods in vtable order (with `const`), sizeof/offsetof
  asserts, explicit padding, extern globals. Maps std types to include/vs2010.
  Members with a type that it cannot write become `alignas(N) unsigned char[]` with `// ❓`.
  A reference to such a type becomes a pointer (same ABI).
- `include/pdb/CacheGate/types.h`: 241 types, 5 globals. All asserts pass.

## Not done
- `std::list`: not written (CacheGate does not use it).
- 6 types skipped (list at the end of types.h): AsyncConnectContext, AsyncRecvContext,
  AsyncSendContext, EventContext (base `_OVERLAPPED`), OuterWorldDdataHeader (needs pack),
  SCOPE_ID (overlapping members).
- Runtime test (`tools/run_selftest.sh`, expect "lift ok 2 32") not run: Bash denied for wine.

## ❓
- 30 members are opaque byte arrays (Windows/CRT types such as `_RTL_CRITICAL_SECTION`).
- clang-cl can put overloaded virtual methods in a different vtable order than the PDB order
  if the overloads are not adjacent. pdb2h.py does not handle this.
- `__std_terminate` is an inline forwarder in xstddef. crt0 must own it later.

## Blocked
- None.

## Gate result
- `tools/gate.sh`: `gate ok`.
