# lift-gamedaemon-36: BloodLib and Shared gaps: include_memory, include_packet, include_property, include_stlmemory, ...

| Item | Value |
| --- | --- |
| Exe | GD |
| Source build | GameDaemon 2019 + PDB (VS2010 SP1) |
| Exe file | `<work-root>/ida/lift/GameDaemon/GameDaemon.exe` |
| PDB | `<work-root>/ida/lift/GameDaemon/GameDaemon.pdb` |
| Pseudocode | `~/.cache/bns-lift/hr/GameDaemon/<stem>.c` |
| Pseudocode index | `~/.cache/bns-lift/hr/GameDaemon/index.tsv` (stem, rva, name, first, last, status, source file, part) |
| Wave | W1 |
| Model | opus |
| Depends on | `lift-gamedaemon-34` |
| Pattern | `src/Server/BloodLib/source/Memory.cpp` |
| Plan | `Docs/Plan/gamedaemon-lift.md` sections 1, 3, 5 |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Grep `Docs/Parity/lessons.md` for A2 (block order), A6 (per-exe path literals), A12 (PDB member types), A18 (destructors), A21 (PDB facts) and A22 (per-exe source form). Do not read it in full.
- Pattern: `src/Server/BloodLib/source/Memory.cpp`. Read it one time. Use its form for the functions of this card.

## Scope

20 functions, about 447 pseudocode lines (about 3,576 tokens). Stems: `include_memory`, `include_packet`, `include_property`, `include_stlmemory`, `lock`, `systemobject`, `include_network`, `include_logarchive`, `include_delayedrelease`, `include_jsoncpp`.

| n | Exe | RVA | PDB name | Stem | Lines |
| ---: | --- | --- | --- | --- | ---: |
| 1 | GD | `0x1000` | `operator new` | include_memory | 16 |
| 2 | GD | `0x97e0` | `operator delete` | include_memory | 15 |
| 3 | GD | `0x6a4c30` | `operator new[]` | include_memory | 16 |
| 4 | GD | `0xac70` | `Packet::IncRepeatCount` | include_packet | 25 |
| 5 | GD | `0xe230` | `Property::Set` | include_property | 30 |
| 6 | GD | `0x1d120` | `Property::GetFlag` | include_property | 18 |
| 7 | GD | `0x8c2b0` | `Property::Set` | include_property | 73 |
| 8 | GD | `0x1ed800` | `Property::Set` | include_property | 76 |
| 9 | GD | `0x18eb0` | `StlAllocator<ZipPackedReaderIO::FileName,2>::construct` | include_stlmemory | 28 |
| 10 | GD | `0x1cbc0` | `AutoCS::~AutoCS` | lock | 8 |
| 11 | GD | `0x1cbd0` | `AutoCS::Enter` | lock | 25 |
| 12 | GD | `0x1cc50` | `AutoCS::Leave` | lock | 25 |
| 13 | GD | `0x18d060` | `AccountInventoryChannelManager::~AccountInventoryChannelManager` | lock | 8 |
| 14 | GD | `0x1dc200` | `AutoSRW::~AutoSRW` | lock | 16 |
| 15 | GD | `0x1dc1a0` | `SystemMultiEvent::~SystemMultiEvent` | systemobject | 21 |
| 16 | GD | `0x33b980` | `AccountInventorySessionHandler::~AccountInventorySessionHandler` | include_network | 7 |
| 17 | GD | `0x3feed0` | `CombatSeqState::GetState` | include_logarchive | 7 |
| 18 | GD | `0x694060` | `LogArchive::Name` | include_logarchive | 7 |
| 19 | GD | `0x467720` | `AttachEquipGemPieceAction::getPriority` | include_delayedrelease | 7 |
| 20 | GD | `0x6761e0` | `Json::FastWriter::~FastWriter` | include_jsoncpp | 19 |

### Shared functions

These functions are in shared source. They are not MATCH in each lifted exe that has them.

| PDB name | Shared file | Other exes | Note |
| --- | --- | --- | --- |
| `operator delete` | `src/Server/BloodLib/source/Memory.cpp` | CacheGate, LobbyDaemon, LobbyGate, PostOfficeDaemon, SmartCouponDaemon | - |

Same name in a lifted exe (a different body is possible): `AutoCS::~AutoCS` (src/Server/Economy/MarketDealerDaemon/JobContext.cpp), `AutoCS::Leave` (src/Server/Economy/MarketDealerDaemon/JobContext.cpp).

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Shared functions: fix them in the shared file. If GameDaemon needs another form, use a per-exe copy in `lift_common_gd` or a `LIFT_EXE_` wrapper (A22, pattern 35). The 5 other exes must keep each MATCH. A MATCH to DIFF change needs an `allow-worse.txt` row with the counts.
6. An EXCLUDED function has a proof that no honest source fix exists in that exe. Read the proof first. If the same cause applies to GameDaemon, write the function under "Not done" with the proof reference. Do not edit `excluded.tsv`.
7. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/include_memory.cpp`
- `src/Server/GameDaemon/include_memory.h`
- `src/Server/BloodLib/source/Memory.cpp`
- `src/Server/GameDaemon/include_packet.cpp`
- `src/Server/GameDaemon/include_packet.h`
- `src/Server/GameDaemon/include_property.cpp`
- `src/Server/GameDaemon/include_property.h`
- `src/Server/GameDaemon/include_stlmemory.cpp`
- `src/Server/GameDaemon/include_stlmemory.h`
- `src/Server/GameDaemon/lock.cpp`
- `src/Server/GameDaemon/lock.h`
- `src/Server/GameDaemon/systemobject.cpp`
- `src/Server/GameDaemon/systemobject.h`
- `src/Server/GameDaemon/include_network.cpp`
- `src/Server/GameDaemon/include_network.h`
- `src/Server/GameDaemon/include_logarchive.cpp`
- `src/Server/GameDaemon/include_logarchive.h`
- `src/Server/GameDaemon/include_delayedrelease.cpp`
- `src/Server/GameDaemon/include_delayedrelease.h`
- `src/Server/GameDaemon/include_jsoncpp.cpp`
- `src/Server/GameDaemon/include_jsoncpp.h`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-36.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
