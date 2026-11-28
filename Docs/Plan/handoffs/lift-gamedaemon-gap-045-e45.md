# Handoff: lift-gamedaemon-gap-045-e45

Round 1. Exe: GameDaemon (2019 + PDB). The driver does the build, the gate and the MATCH count. No build or gate was run in this session.

## Lifted (17 bodies)

| RVA | PDB name | Note |
| --- | --- | --- |
| `0x6bb190` | `LogAgent::~LogAgent` | Layout in `logagent.h`. Keep pragma. |
| `0x27fe0` | `GenerateGameEventTid` | Keep pragma. |
| `0x28030` | `SmartCouponSessionHandler::OnAccept` | Keep pragma. |
| `0x6912c0` | `Packet::GrowAdd` | Keep pragma. |
| `0x6915e0` | `Packet::Restore` | HR subtracts the constant 19. |
| `0x692220` | `Packet::setRecvBuffer` | Keep pragma. |
| `0x6d8430` | `LogArchiveReadBuffer::LogArchiveReadBuffer` | Keep pragma. |
| `0x6d84c0` | `LogArchiveReadBuffer::~LogArchiveReadBuffer` | Keep pragma. |
| `0x6d84f0` | `LogArchiveReadBuffer::ClearBuffer` | Keep pragma. |
| `0x6d8e80` | `LogArchiveWriteContext::~LogArchiveWriteContext` | Keep pragma. |
| `0xac70` | `Packet::IncRepeatCount` | Folded under the Packet name. |
| `0x6bb020` | `LogServer::AsyncRecv` | `LogServerView` (raw offsets `_sock` +0x8, `_readBuffer` +0x30). The log message text is not in HR. `L"WSARecv()"` is assumed (marked with a question mark in the source). |
| `0x693240` | `PacketConcatenateBuffer::DecomposeV` | Same logic as `Decompose(int, ...)` in BloodLib. The crash check is kept. |
| `0x10d40` | `FragmentPacket::FreeBody` | Uses `Packet::GetFreeBody`. |
| `0x693a60` | `RelationalRefCntObject::remove_child` | Views of `ParentRole`, `ChildRole` and the object in the .cpp. The class has no members in the header yet. |
| `0x688990` | `SyncBuffer::realign` | `SyncBufferView`. The overlapping copy uses `memmove`. |
| `0x68ba10` | `Property::findMaxId` (SyncDef) | The id check (crash when id >= 4) is kept. |

## Not done (6)

| RVA | PDB name | Reason |
| --- | --- | --- |
| `0x28480` | `SmartCouponSessionHandler::PacketHandler` | The table `SmartCouponPacketGameSideHandlerList` (data at RVA `0xE98780`) is not in the source. Its size is unknown. A lift without the table does not link. HR has no bounds check on the command index. Add the table in a data card, then lift this function with a bounds check. |
| `0x6935c0` | `RelationalRefCntObject::clearRole` | Needs the base `RefCntObject` layout and the virtual slots 4 and 5 (`parentRoleAllocator`, `childRoleAllocator`). The header has no bases or virtuals. A layout card must come first. |
| `0x688890` | `SyncBuffer::setInt` | HR uses the registers in a non-standard way: rcx is the destination, rdx the source, r8 the type. This does not map to the PDB member signature. No honest source form was found in the read budget. |
| `0x18eb0` | `StlAllocator<ZipPackedReaderIO::FileName,2>::construct` | `ZipPackedReaderIO::FileName` has no layout in GameDaemon yet. The function is a class template member with `basic_string` and `vector` copies. |
| `0x68a700` | `Property::Get(unsigned short, bool *) const` | HR has an extra hidden table argument (FieldDef array, stride 184). The FieldDef layout and the table source are not known. |
| `0x69ed10` | `LogMedia::LogMedia` | EXCLUDED in LobbyDaemon (`Docs/Parity/excluded.tsv`, line 28, precheck P3_imm on the constant `0xffffffff`). The GameDaemon body stores the same `-1`. The constructor is also inline in the shared `LogMedia.h`. |

## Shared functions of the card

I made no change to shared files. These stems have no function in the GameDaemon work order:

- `source_thread`: `ThreadManager::StopThread`
- `prng`: `Prng::Initialize`
- `crypto`: `Crypto::Initialize` and `Crypto::InstanceSize`
- `npchannel2`: `NPTransactionRegistry::NPTransactionRegistry`
- `source_pipeconsole`: `PipeConsole::addNode`

The shared source of these is already lifted for the other exes. The driver checks them with the usual MATCH comparison.

## Files changed in this round

- `src/Server/GameDaemon/include_packet.cpp`
- `src/Server/GameDaemon/logagent.cpp`, `logagent.h`, `logagentpackethandler.h`
- `src/Server/GameDaemon/logarchivecontext.cpp`, `logarchivecontext.h`
- `src/Server/GameDaemon/smartcoupondchannel.cpp`, `smartcoupondchannel.h`
- `src/Server/GameDaemon/source_packet.cpp`
- `src/Server/GameDaemon/logserver.cpp`
- `src/Server/GameDaemon/source_packetutil.cpp`
- `src/Server/GameDaemon/fragmentpacket_h.cpp`
- `src/Server/GameDaemon/source_refcntobject.cpp`
- `src/Server/GameDaemon/propertysync.cpp`
- `src/Server/GameDaemon/source_property.cpp`
- `Docs/Plan/handoffs/lift-gamedaemon-gap-045-e45.md`
