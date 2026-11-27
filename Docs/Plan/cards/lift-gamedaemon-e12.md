# lift-gamedaemon-e12: Easy leaves (VC headers and no-file functions and Shared gaps and others): stdio, wchar, include_memorymanager, include_refcntobject, ...

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
| Pattern | `src/Server/BloodLib/source/MemoryManager.cpp` |
| Plan | `Docs/Plan/gamedaemon-lift.md` sections 1, 3, 5 |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Grep `Docs/Parity/lessons.md` for A2 (block order), A6 (per-exe path literals), A12 (PDB member types), A18 (destructors), A21 (PDB facts) and A22 (per-exe source form). Do not read it in full.
- Pattern: `src/Server/BloodLib/source/MemoryManager.cpp`. Read it one time. Use its form for the functions of this card.

## Scope

40 functions, about 583 pseudocode lines (about 4,664 tokens). Stems: `stdio`, `wchar`, `include_memorymanager`, `include_refcntobject`, `stringbuilder`, `packetbufferhandler`, `nofile`, `session`, `include_memory`, `xmemory`, `source_logarchive`, `listener`, `include_jsoncpp`, `source_alertsender`, `systemobject`.

Wave E (owner order 2026-11-27: the easiest work first). Each function in this card is a leaf: its body calls no other counted function that needs a lift. Thus a `LIFT_STUB` callee cannot keep it DIFF. Each function has at most 30 pseudocode lines. Ease key: 14.6 cost per function (rule in `Docs/Plan/gamedaemon-lift.md` section 3).

Lift only the functions in the table. The other functions of these stems are in later W cards. Those cards depend on this card.

| n | Exe | RVA | PDB name | Stem | Lines | Form |
| ---: | --- | --- | --- | --- | ---: | --- |
| 1 | GD | `0x10d10` | `swprintf_s<4>` | stdio | 10 | leaf |
| 2 | GD | `0x8b8a0` | `swprintf_s<4000>` | wchar | 10 | leaf |
| 3 | GD | `0x1db350` | `swprintf_s<1025>` | wchar | 10 | leaf |
| 4 | GD | `0x347840` | `swprintf_s<1001>` | wchar | 10 | leaf |
| 5 | GD | `0x347870` | `swprintf_s<1024>` | wchar | 10 | leaf |
| 6 | GD | `0x671140` | `swprintf_s<40>` | wchar | 10 | leaf |
| 7 | GD | `0x6b7c10` | `StaticPageMemoryManager::Initialize` | include_memorymanager | 12 | leaf |
| 8 | GD | `0x6b7c50` | `StaticPageMemoryManager::Clear` | include_memorymanager | 8 | leaf |
| 9 | GD | `0x6b7c90` | `StaticPageMemoryManager::AllocZero` | include_memorymanager | 13 | leaf |
| 10 | GD | `0x6b7cd0` | `StaticPageMemoryManager::Realloc` | include_memorymanager | 13 | leaf |
| 11 | GD | `0x6b7d10` | `StaticPageMemoryManager::ReallocZero` | include_memorymanager | 13 | leaf |
| 12 | GD | `0x105620` | `Pointer2<ChallengeParty>::~Pointer2<ChallengeParty>` | include_refcntobject | 17 | leaf |
| 13 | GD | `0x1daca0` | `Data::ZoneTriggerEventCondRecordPtr::ZoneTriggerEventCondRecordPtr` | include_refcntobject | 9 | xtor |
| 14 | GD | `0x346770` | `Pointer2<CraftInfo>::~Pointer2<CraftInfo>` | include_refcntobject | 14 | xtor |
| 15 | GD | `0x69dd00` | `StringBuilderW::~StringBuilderW` | stringbuilder | 8 | xtor |
| 16 | GD | `0x69dd40` | `StringBuilderW::AppendFormat` | stringbuilder | 21 | leaf |
| 17 | GD | `0x4c380` | `ActSeqState::GetState` | packetbufferhandler | 7 | getter |
| 18 | GD | `0x69ddc0` | `TrustedPacketBufferHandler::Clone` | packetbufferhandler | 23 | leaf |
| 19 | GD | `0x118e0` | `Data::SlateScrollCache::~SlateScrollCache` | nofile | 15 | leaf |
| 20 | GD | `0x14a320` | `TakeTimeBasedPlayRewardResponseParam::~TakeTimeBasedPlayRewardResponseParam` | nofile | 24 | leaf |
| 21 | GD | `0x1b4030` | `RankingSeasonInfo::~RankingSeasonInfo` | nofile | 18 | leaf |
| 22 | GD | `0x1ee8e0` | `ZoneCounterSet::~ZoneCounterSet` | nofile | 15 | leaf |
| 23 | GD | `0x4bfa70` | `InventoryCacheUpdate::~InventoryCacheUpdate` | nofile | 9 | xtor |
| 24 | GD | `0x4bfee0` | `InventoryClientUpdate::~InventoryClientUpdate` | nofile | 7 | xtor |
| 25 | GD | `0x5b3750` | `FallDeathEffect::FallDeathEffect` | nofile | 26 | leaf |
| 26 | GD | `0x6a84d0` | `Json::Exception::Exception` | nofile | 18 | leaf |
| 27 | GD | `0x6eba80` | `LoadTableBinder::~LoadTableBinder` | nofile | 7 | xtor |
| 28 | GD | `0x699170` | `Session::IsConnected` | session | 14 | leaf |
| 29 | GD | `0x699ac0` | `Session::deallocateCrypt` | session | 17 | leaf |
| 30 | GD | `0x1000` | `operator new` | include_memory | 16 | leaf |
| 31 | GD | `0x97e0` | `operator delete` | include_memory | 15 | leaf |
| 32 | GD | `0x6a4c30` | `operator new[]` | include_memory | 16 | leaf |
| 33 | GD | `0x6868c0` | `Json::Reader::ErrorInfo::~ErrorInfo` | xmemory | 17 | leaf |
| 34 | GD | `0x695070` | `LogArchive::IsUnsentFileExist` | source_logarchive | 25 | leaf |
| 35 | GD | `0x695870` | `LogArchive::isPingTimeExpired` | source_logarchive | 15 | leaf |
| 36 | GD | `0x695aa0` | `LogArchive::startupWinSockLib` | source_logarchive | 14 | leaf |
| 37 | GD | `0x6be0b0` | `PortListener::~PortListener` | listener | 18 | leaf |
| 38 | GD | `0x6761e0` | `Json::FastWriter::~FastWriter` | include_jsoncpp | 19 | leaf |
| 39 | GD | `0x686920` | `destroy` | source_alertsender | 19 | leaf |
| 40 | GD | `0x1dc1a0` | `SystemMultiEvent::~SystemMultiEvent` | systemobject | 21 | leaf |

### Shared functions

These functions are in shared source. They are not MATCH in each lifted exe that has them.

| PDB name | Shared file | Other exes | Note |
| --- | --- | --- | --- |
| `StaticPageMemoryManager::Initialize` | `src/Server/BloodLib/source/MemoryManager.cpp` | CacheGate, LobbyDaemon, LobbyGate, PostOfficeDaemon, SmartCouponDaemon | - |
| `StaticPageMemoryManager::Clear` | `src/Server/BloodLib/source/MemoryManager.cpp` | CacheGate, LobbyDaemon, LobbyGate, PostOfficeDaemon, SmartCouponDaemon | - |
| `StaticPageMemoryManager::AllocZero` | `src/Server/BloodLib/source/MemoryManager.cpp` | CacheGate, LobbyDaemon, LobbyGate, PostOfficeDaemon, SmartCouponDaemon | - |
| `StaticPageMemoryManager::Realloc` | `src/Server/BloodLib/source/MemoryManager.cpp` | CacheGate, LobbyDaemon, LobbyGate, PostOfficeDaemon, SmartCouponDaemon | - |
| `StaticPageMemoryManager::ReallocZero` | `src/Server/BloodLib/source/MemoryManager.cpp` | CacheGate, LobbyDaemon, LobbyGate, PostOfficeDaemon, SmartCouponDaemon | - |
| `TrustedPacketBufferHandler::Clone` | `src/Server/BloodLib/source/PacketBufferHandler.cpp` | CacheGate, LobbyDaemon, LobbyGate, PostOfficeDaemon, SmartCouponDaemon | EXCLUDED in LobbyDaemon: read its `excluded.tsv` row first |
| `Session::deallocateCrypt` | `src/Server/BloodLib/source/Security.cpp` | LobbyDaemon, LobbyGate | EXCLUDED in LobbyDaemon: read its `excluded.tsv` row first |
| `operator delete` | `src/Server/BloodLib/source/Memory.cpp` | CacheGate, LobbyDaemon, LobbyGate, PostOfficeDaemon, SmartCouponDaemon | - |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Shared functions: fix them in the shared file. If GameDaemon needs another form, use a per-exe copy in `lift_common_gd` or a `LIFT_EXE_` wrapper (A22, pattern 35). The 5 other exes must keep each MATCH. A MATCH to DIFF change needs an `allow-worse.txt` row with the counts.
6. An EXCLUDED function has a proof that no honest source fix exists in that exe. Read the proof first. If the same cause applies to GameDaemon, write the function under "Not done" with the proof reference. Do not edit `excluded.tsv`.
7. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/stdio.cpp`
- `src/Server/GameDaemon/stdio.h`
- `src/Server/GameDaemon/wchar.cpp`
- `src/Server/GameDaemon/wchar.h`
- `src/Server/BloodLib/source/MemoryManager.cpp`
- `src/Server/GameDaemon/include_refcntobject.cpp`
- `src/Server/GameDaemon/include_refcntobject.h`
- `src/Server/GameDaemon/stringbuilder.cpp`
- `src/Server/GameDaemon/stringbuilder.h`
- `src/Server/GameDaemon/packetbufferhandler.cpp`
- `src/Server/GameDaemon/packetbufferhandler.h`
- `src/Server/BloodLib/source/PacketBufferHandler.cpp`
- `src/Server/GameDaemon/nofile.cpp`
- `src/Server/GameDaemon/nofile.h`
- `src/Server/GameDaemon/session.cpp`
- `src/Server/GameDaemon/session.h`
- `src/Server/BloodLib/source/Security.cpp`
- `src/Server/GameDaemon/include_memory.cpp`
- `src/Server/GameDaemon/include_memory.h`
- `src/Server/BloodLib/source/Memory.cpp`
- `src/Server/GameDaemon/xmemory.cpp`
- `src/Server/GameDaemon/xmemory.h`
- `src/Server/GameDaemon/source_logarchive.cpp`
- `src/Server/GameDaemon/source_logarchive.h`
- `src/Server/GameDaemon/listener.cpp`
- `src/Server/GameDaemon/listener.h`
- `src/Server/GameDaemon/include_jsoncpp.cpp`
- `src/Server/GameDaemon/include_jsoncpp.h`
- `src/Server/GameDaemon/source_alertsender.cpp`
- `src/Server/GameDaemon/source_alertsender.h`
- `src/Server/GameDaemon/systemobject.cpp`
- `src/Server/GameDaemon/systemobject.h`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-e12.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
