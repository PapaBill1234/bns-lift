# lift-lobbydaemon-3 handoff

Card: CliSessionTable part 1 and containers (`Docs/Plan/cards/lift-lobbydaemon-3.md`), 37 functions.
Source: LobbyDaemon.exe and LobbyDaemon.pdb (2019 + PDB, VS2010 SP1). The compiler-generated scalar deleting dtors
(0x3d020, 0x3d080) are not in scope.

## Result

| Check | Result |
| --- | --- |
| `LIFT_BUILD_DIR=build-ld-3 tools/gate.sh` | gate ok (after each module) |
| VS2010 link of `LobbyDaemon.exe` (`tools/vs2010/build.sh LobbyDaemon`) | ok (180 sources, 24 per-exe) |
| `tools/parity.sh` (no `--accept`) | parity ok. All 5 exes: +0, no MATCH lost. |
| Lifted functions | 37 |
| Not done functions | 0 |

## MATCH comparison (`tools/parity.sh`, VS2010 /GL /LTCG)

| Exe | Baseline MATCH | Branch MATCH | New MATCH | MATCH -> DIFF | MATCH name gone |
| --- | --- | --- | --- | --- | --- |
| CacheGate | 456 | 456 (92.9 %) | 0 | 0 | 0 |
| LobbyGate | 658 | 658 (89.0 %) | 0 | 0 | 0 |
| SmartCouponDaemon | 630 | 630 (94.2 %) | 0 | 0 | 0 |
| PostOfficeDaemon | 694 | 694 (91.4 %) | 0 | 0 | 0 |
| LobbyDaemon | 49 | 49/2204 (2.2 %; 70 paired, 2134 only in original) | 0 | 0 | 0 |

Why LD gains 0: no live code calls the new functions yet. Their callers are `LIFT_STUB` bodies, so `/OPT:REF`
removes them. The built `build-vs2010/LobbyDaemon.pdb` has no `?Insert@CliSessionTable`, `?Initialize@CliSessionTable`,
`??1CliSessionTable`, `?SelectAll@CliSessionTable`, `?Pushback@RefCntList`, `?Add@WaitQueue` or `?Init@BoundedList`
(checked with `grep -a -c -F`). The lifts give MATCH when a later wave lifts a caller.

## Lifted

### CliSessionTable part 1 (`0x3cfe0` to `0x3ed50`, 21 functions)

| RVA | PDB name | Note |
| --- | --- | --- |
| 0x3cfe0 | `operator delete[](void*, void*)` | Memory.h line 181 version, inline in `CliSessionTable.cpp` (see notes) |
| 0x3d0a0 | `CliSessionTable::~CliSessionTable` | also gives `GateNode::~GateNode` (inline in 0x3d020) |
| 0x3d8f0 | `std::map<id128,CliSession*,...>::~map` | STL instantiation from the `AccountIndexMap` typedef |
| 0x3d940 | `CliSessionTable::Initialize` | |
| 0x3de80 | `CliSessionTable::Insert` | |
| 0x3df60 | `CliSessionTable::Insert_index_gate` | |
| 0x3dff0 | `CliSessionTable::Delete` | |
| 0x3e100 | `CliSessionTable::Delete_index_gate` | |
| 0x3e180 | `CliSessionTable::Select` | `// BUG:` no null check before `addReferenceCount` |
| 0x3e270 | `CliSessionTable::Insert_index_gatekey` | |
| 0x3e350 | `CliSessionTable::Delete_index_gatekey` | |
| 0x3e450 | `CliSessionTable::Select_index_gatekey` | |
| 0x3e550 | `CliSessionTable::SelectAll_index_gatekey` | |
| 0x3e670 | `CliSessionTable::Insert_index_account` | account hash from the disasm |
| 0x3e750 | `CliSessionTable::Delete_index_account` | |
| 0x3e870 | `CliSessionTable::Select_index_account` | |
| 0x3e980 | `CliSessionTable::Insert_index_pcid` | |
| 0x3ea50 | `CliSessionTable::Delete_index_pcid` | |
| 0x3eb40 | `CliSessionTable::Select_index_pcid` | |
| 0x3ec40 | `CliSessionTable::SelectAll_index_pcid` | `// LIFT:` LTCG changed the binary signature; source form, will probably not MATCH |
| 0x3ed50 | `CliSessionTable::SelectAll` | |

`CliSessionTable::Select_index_gate` (0x3eef0) is part 2. It stays a `LIFT_STUB`.

### Containers (commit fa85f14 on this branch, 16 functions)

| Module | RVA | PDB name |
| --- | --- | --- |
| BoundedList | 0x18540 | `BoundedList::Init` |
| BoundedList | 0x18650 | `BoundedList::Pushback` |
| BoundedList | 0x186f0 | `BoundedList::Popfront` |
| BoundedList | 0x18790 | `BoundedList::Remove` |
| RefCntList | 0x64c80 | `RefCntList::RefCntList` |
| RefCntList | 0x64c90 | `RefCntList::~RefCntList` |
| RefCntList | 0x64d00 | `RefCntList::Pushback` |
| RefCntList | 0x64da0 | `RefCntList::Remove` |
| WaitQueue | 0xdc540 | `WaitQueue::WaitQueue` |
| WaitQueue | 0xdc590 | `WaitQueue::~WaitQueue` |
| WaitQueue | 0xdc5e0 | `WaitQueue::Add` |
| WaitQueue | 0xdc720 | `WaitQueue::Remove` |
| WaitQueue | 0xdc870 | `WaitQueue::QueryTurn` |
| WaitQueue | 0xdc920 | `WaitQueueList::~WaitQueueList` |
| WaitQueue | 0xdc940 | `WaitQueueList::Init` |
| WaitQueue | 0xdca20 | `WaitQueueList::Pop` |

## Not done

None. Each function of the card is lifted.

## Notes for the next waves

| Topic | Note |
| --- | --- |
| `CliSessionTable.h` | Rewritten with the PDB layout (0x80, offset asserts), `GateNode` (0x38, `_clisession` at 0x30), the 5 map and list typedefs (scope ❓) and all 20 method declarations. |
| `id128` order | `operator<(id128 const&, id128 const&)` is inline in the header (`// LIFT:`). The map find of 0x3e750 compares `id[0]` first, then `id[1]`. |
| Account hash | Not in the PDB. File-static `AccountHash` in the .cpp: the sum of the 4 dwords as 64-bit values, modulo `_accountMod`. |
| Array new | The table arrays use the A16 placement array pattern (same as `CouponJob.cpp`): `new (Alloc(sizeof(T) * n + 8)) T[n]`, then `delete[] x; Free(__delv_buf__); x = nullptr;`. |
| `__delv_buf__` | No other LobbyDaemon file defines it. `CliSessionTable.cpp` defines it with ❓ on the module of the definition. A later card that finds the real owner must move it. |
| StlMemory.h path | This object has the upper case build path. `LIFT_STLMEMORY_FILE` is set before the first include. The Memory.h path is lower case. |
| `Select_index_gate` | Part 2 (0x3eef0). Keep `LIFT_STUB(0x3eef0)` until the part 2 card. |
