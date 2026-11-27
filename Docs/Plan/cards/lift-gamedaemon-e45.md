# lift-gamedaemon-e45: Easy leaves (BloodLib and Server shared and others): logagent, smartcoupondchannel, npchannel2, source_packet, ...

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
| Pattern | `src/Security/source/BloodCrypto/crypto/Crypto.cpp` |
| Plan | `Docs/Plan/gamedaemon-lift.md` sections 1, 3, 5 |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Grep `Docs/Parity/lessons.md` for A2 (block order), A6 (per-exe path literals), A12 (PDB member types), A18 (destructors), A21 (PDB facts) and A22 (per-exe source form). Do not read it in full.
- Pattern: `src/Security/source/BloodCrypto/crypto/Crypto.cpp`. Read it one time. Use its form for the functions of this card.

## Scope

30 functions, about 706 pseudocode lines (about 5,648 tokens). Stems: `logagent`, `smartcoupondchannel`, `npchannel2`, `source_packet`, `logarchivecontext`, `include_packet`, `source_refcntobject`, `source_pipeconsole`, `logserver`, `source_thread`, `propertysync`, `source_packetutil`, `prng`, `include_stlmemory`, `source_property`, `fragmentpacket_h`, `crypto`, `source_logmedia`.

Wave E (owner order 2026-11-27: the easiest work first). Each function in this card is a leaf: its body calls no other counted function that needs a lift. Thus a `LIFT_STUB` callee cannot keep it DIFF. Each function has at most 30 pseudocode lines. Ease key: 33.5 cost per function (rule in `Docs/Plan/gamedaemon-lift.md` section 3).

Lift only the functions in the table. The other functions of these stems are in later W cards. Those cards depend on this card.

| n | Exe | RVA | PDB name | Stem | Lines | Form |
| ---: | --- | --- | --- | --- | ---: | --- |
| 1 | GD | `0x6bb190` | `LogAgent::~LogAgent` | logagent | 21 | leaf |
| 2 | GD | `0x27fe0` | `GenerateGameEventTid` | smartcoupondchannel | 22 | leaf |
| 3 | GD | `0x28030` | `SmartCouponSessionHandler::OnAccept` | smartcoupondchannel | 16 | leaf |
| 4 | GD | `0x28480` | `SmartCouponSessionHandler::PacketHandler` | smartcoupondchannel | 26 | leaf |
| 5 | GD | `0x1b090` | `NPTransactionRegistry::NPTransactionRegistry` | npchannel2 | 22 | leaf |
| 6 | GD | `0x6912c0` | `Packet::GrowAdd` | source_packet | 28 | leaf |
| 7 | GD | `0x6915e0` | `Packet::Restore` | source_packet | 23 | leaf |
| 8 | GD | `0x692220` | `Packet::setRecvBuffer` | source_packet | 17 | leaf |
| 9 | GD | `0x6d8430` | `LogArchiveReadBuffer::LogArchiveReadBuffer` | logarchivecontext | 28 | leaf |
| 10 | GD | `0x6d84c0` | `LogArchiveReadBuffer::~LogArchiveReadBuffer` | logarchivecontext | 11 | xtor |
| 11 | GD | `0x6d84f0` | `LogArchiveReadBuffer::ClearBuffer` | logarchivecontext | 29 | leaf |
| 12 | GD | `0x6d8e80` | `LogArchiveWriteContext::~LogArchiveWriteContext` | logarchivecontext | 26 | leaf |
| 13 | GD | `0xac70` | `Packet::IncRepeatCount` | include_packet | 25 | leaf |
| 14 | GD | `0x6935c0` | `RelationalRefCntObject::clearRole` | source_refcntobject | 24 | leaf |
| 15 | GD | `0x693a60` | `RelationalRefCntObject::remove_child` | source_refcntobject | 26 | leaf |
| 16 | GD | `0x6b0580` | `PipeConsole::addNode` | source_pipeconsole | 25 | leaf |
| 17 | GD | `0x6bb020` | `LogServer::AsyncRecv` | logserver | 25 | leaf |
| 18 | GD | `0x69daa0` | `ThreadManager::StopThread` | source_thread | 26 | leaf |
| 19 | GD | `0x688890` | `SyncBuffer::setInt` | propertysync | 26 | leaf |
| 20 | GD | `0x688990` | `SyncBuffer::realign` | propertysync | 28 | leaf |
| 21 | GD | `0x693240` | `PacketConcatenateBuffer::DecomposeV` | source_packetutil | 27 | leaf |
| 22 | GD | `0x6e45e0` | `Prng::Initialize` | prng | 27 | leaf |
| 23 | GD | `0x18eb0` | `StlAllocator<ZipPackedReaderIO::FileName,2>::construct` | include_stlmemory | 28 | leaf |
| 24 | GD | `0x68a700` | `Property::Get` | source_property | 27 | leaf |
| 25 | GD | `0x68ba10` | `Property::findMaxId` | source_property | 29 | leaf |
| 26 | GD | `0xb2c0` | `FragmentPacket::StartRepeat` | fragmentpacket_h | 12 | leaf |
| 27 | GD | `0x10d40` | `FragmentPacket::FreeBody` | fragmentpacket_h | 10 | leaf |
| 28 | GD | `0x6df2f0` | `Crypto::Initialize` | crypto | 26 | leaf |
| 29 | GD | `0x6df3a0` | `Crypto::InstanceSize` | crypto | 30 | leaf |
| 30 | GD | `0x69ed10` | `LogMedia::LogMedia` | source_logmedia | 16 | leaf |

### Shared functions

These functions are in shared source. They are not MATCH in each lifted exe that has them.

| PDB name | Shared file | Other exes | Note |
| --- | --- | --- | --- |
| `NPTransactionRegistry::NPTransactionRegistry` | `src/Server/Shared/NPChannel2.cpp` | LobbyDaemon, SmartCouponDaemon | - |
| `PipeConsole::addNode` | `src/Server/BloodLib/source/PipeConsole.cpp` | CacheGate, LobbyDaemon, LobbyGate, PostOfficeDaemon, SmartCouponDaemon | - |
| `ThreadManager::StopThread` | `src/Server/BloodLib/source/Thread.cpp` | CacheGate, LobbyDaemon, LobbyGate, PostOfficeDaemon, SmartCouponDaemon | - |
| `Prng::Initialize` | `src/Security/source/BloodCrypto/math/prng/prng.cpp` | CacheGate, LobbyDaemon, LobbyGate, PostOfficeDaemon, SmartCouponDaemon | EXCLUDED in LobbyDaemon: read its `excluded.tsv` row first |
| `FragmentPacket::StartRepeat` | `src/Server/Packet/FragmentPacket.cpp` | LobbyGate | - |
| `Crypto::Initialize` | `src/Security/source/BloodCrypto/crypto/Crypto.cpp` | CacheGate, LobbyDaemon, LobbyGate, PostOfficeDaemon, SmartCouponDaemon | EXCLUDED in LobbyDaemon: read its `excluded.tsv` row first |
| `Crypto::InstanceSize` | `src/Security/source/BloodCrypto/crypto/Crypto.cpp` | LobbyGate | - |
| `LogMedia::LogMedia` | `src/Server/BloodLib/source/LogMedia.cpp` | LobbyDaemon | EXCLUDED in LobbyDaemon: read its `excluded.tsv` row first |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Shared functions: fix them in the shared file. If GameDaemon needs another form, use a per-exe copy in `lift_common_gd` or a `LIFT_EXE_` wrapper (A22, pattern 35). The 5 other exes must keep each MATCH. A MATCH to DIFF change needs an `allow-worse.txt` row with the counts.
6. An EXCLUDED function has a proof that no honest source fix exists in that exe. Read the proof first. If the same cause applies to GameDaemon, write the function under "Not done" with the proof reference. Do not edit `excluded.tsv`.
7. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/logagent.cpp`
- `src/Server/GameDaemon/logagent.h`
- `src/Server/GameDaemon/smartcoupondchannel.cpp`
- `src/Server/GameDaemon/smartcoupondchannel.h`
- `src/Server/Shared/NPChannel2.cpp`
- `src/Server/GameDaemon/source_packet.cpp`
- `src/Server/GameDaemon/source_packet.h`
- `src/Server/GameDaemon/logarchivecontext.cpp`
- `src/Server/GameDaemon/logarchivecontext.h`
- `src/Server/GameDaemon/include_packet.cpp`
- `src/Server/GameDaemon/include_packet.h`
- `src/Server/GameDaemon/source_refcntobject.cpp`
- `src/Server/GameDaemon/source_refcntobject.h`
- `src/Server/BloodLib/source/PipeConsole.cpp`
- `src/Server/GameDaemon/logserver.cpp`
- `src/Server/GameDaemon/logserver.h`
- `src/Server/BloodLib/source/Thread.cpp`
- `src/Server/GameDaemon/propertysync.cpp`
- `src/Server/GameDaemon/propertysync.h`
- `src/Server/GameDaemon/source_packetutil.cpp`
- `src/Server/GameDaemon/source_packetutil.h`
- `src/Security/source/BloodCrypto/math/prng/prng.cpp`
- `src/Server/GameDaemon/include_stlmemory.cpp`
- `src/Server/GameDaemon/include_stlmemory.h`
- `src/Server/GameDaemon/source_property.cpp`
- `src/Server/GameDaemon/source_property.h`
- `src/Server/GameDaemon/fragmentpacket_h.cpp`
- `src/Server/GameDaemon/fragmentpacket_h.h`
- `src/Server/Packet/FragmentPacket.cpp`
- `src/Security/source/BloodCrypto/crypto/Crypto.cpp`
- `src/Server/BloodLib/source/LogMedia.cpp`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-e45.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
