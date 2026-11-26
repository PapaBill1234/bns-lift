# Handoff: lift-lobbydaemon-v2b-pod-01 (round 1)

Exe: PostOfficeDaemon (POD). Source: 2019 + PDB. The driver builds and measures. This session recorded no scores.

## Lifted (source changes in this round)

| # | RVA | Function | Change |
| --- | --- | --- | --- |
| 2 | `0x1a6f0` | `HandlePostOfficeHelloReq` | Decompose test is `!(0 < Decompose(...))` (zero register form). The connection type test is `!= 1`, so the line 65 block falls through and the line 80 block is the jump target. |
| 12 | `0x9570` | `CheckPostCapacityRelayContext::ComposeResponsePacket` | Read the result state once. Success first, then the signed range test `1 < state && state <= 4`, crash in the else branch. The switch is removed. |
| 15 | `0x1e230` | `RetrieveCharacterInfoRelayContext::ComposeResponsePacket` | The same form as #12. |
| 20 | `0x12ca0` | `wmain` | `wmain` is not `extern "C"` (as LobbyGate). VS2010 then gives the EH state `-2` and the funclet `wmain$dtor$0`. The name stays unmangled. |
| 19 | `0xb040` | `operator delete[](void*, void*)` | New header `PlacementVecNew.h` defines `__PLACEMENT_VEC_NEW_INLINE`, an inline placement `operator new[]` and declares the placement `operator delete[]`. The body (Memory.h line 181 crash Log + Alert, lower-case POD path) is in `RelayTimeContext.cpp`, the PDB owner module. All 5 POD modules that use `liftArrayNew` include the header first. Form from lessons A16 (SCD, LG). |

The `wmain$dtor$0` miss must close with #20. The `Console::Flush` miss (ICF name of `operator delete`, 3 bytes) is not examined.

## Not done

| # | RVA | Function | Reason |
| --- | --- | --- | --- |
| 1 | `0xabd0` | `PingRelayContext::processRelayResponse` | Tail merge: VS2010 cross-jumps the two "failed to add next ping" crash blocks (lines 64 and 86) into one `AlertSender::Write` site. The original keeps two sites. Lessons: failure-first form gave 97.6 -> 95.1. No new source form found. |
| 3 | `0x71e0` | `CacheGateChannel::SendFragmentRelayRequest` | The original calls `Packet::Allocate(PacketComposer*)` out of line. The lift inlines it (`PacketBufferPool::allocate`). `noinline` on the BloodLib function changes all 5 exes (lessons: `GamedChannel::SendAccountInventoryNotify`, same cause). Not tried. |
| 4 | `0x4ed0` | `PingGenerator::sendPing` | Stop list (lessons D): LTCG `this` propagation of `PostOfficeDaemon::_instance`. No new idea. |
| 5 | `0x14930` | `PostOfficeDaemon::checkCacheGateServiceState` | Stop list (lessons D): LTCG `this` propagation. The original reads `[rcx+0x840]`; the lift reads `_instance`. No new idea. |
| 6 | `0xe5f0` | `WorldConfigManager::loadWorldConfigFile` | Shared exit path. Lessons: success-first gave a lower score. Not tried again. |
| 7 | `0x132b0` | `PostOfficeDaemon::initialize` | The PDB locals are `wdsn` (wchar_t[1024], rsp+2128), `dsn` (char[1024], rsp+96), `dsnSize` (int = 1024, rsp+80) and `flag` (unsigned char = 0, rsp+64). The `_time64` result stays in a callee-saved register. PDB line 225 is one 191-byte statement (an inlined helper that reads the cert file), and lines 236-252 hold about 72 instructions that the lift does not have. The Hex-Rays text does not show them, so the use of `dsnSize`, `flag` and the time value is unknown. No source change. |
| 8 | `0xdb30` | `WorldConfigManager::updateWorldList` | The lift inlines `Network::GetAddressStringW` (`inet_ntoa`, `MultiByteToWideChar`); the original calls it. Lessons: block layout did not move (goto and RAII forms). The function is in BloodLib (5 exes). Not tried. |
| 9 | `0x1aaa0` | `HandlePostOfficeRegisterPostReq` | Lessons B: goto form and single-expression `::new` gave no change. |
| 10 | `0x20720` | `HandlePostOfficeServiceRegisterPostReq` | Block layout. Not examined in this round. |
| 11 | `0x190f0` | `PostOfficeDB::LoadRetryReadyPostList` | Stop list: rotated fetch loop header (99.1). No new idea. |
| 13 | `0x16f20` | `PostOfficeDB::RegisterPost` | Not examined (695 instructions; the session budget went to the other items). |
| 14 | `0x14e50` | `PostOfficeDB::LoadPostList` | Stop list: rotated fetch loop header (99.1). No new idea. |
| 16 | `0xe8c0` | `WorldConfigManager::setupWorldConfigList` | Tail merge. Not examined in this round. |
| 17 | `0x2f940` | `parseDecInt` | BloodLib `PacketBuffer.cpp` (shared by all exes). The original has an early `begin < end` test that returns -1. A change can break the other exes. Not tried. |
| 18 | `0x2f850` | `parseHexInt` | The same file and cause as #17. The original also keeps 0x41 and 0x46 in registers. |
| - | `0x282d0` | `DaemonConfig::Dump` (4 arguments, XmlCfgDef) | Miss. The caller is not found in this round. |

## Changed files

- `src/Server/Economy/PostOfficeDaemon/AgentPacketHandler.cpp`
- `src/Server/Economy/PostOfficeDaemon/CheckPostCapacityRelay.cpp`
- `src/Server/Economy/PostOfficeDaemon/RetrieveCharacterInfoRelay.cpp`
- `src/Server/Economy/PostOfficeDaemon/PostOfficeDaemon.cpp`
- `src/Server/Economy/PostOfficeDaemon/PlacementVecNew.h` (new)
- `src/Server/Economy/PostOfficeDaemon/RelayTimeContext.cpp`
- `src/Server/Economy/PostOfficeDaemon/RelayContext.cpp`
- `src/Server/Economy/PostOfficeDaemon/PostContext.cpp`
- `src/Server/Economy/PostOfficeDaemon/WorldChannel.cpp`
- `src/Server/Economy/PostOfficeDaemon/WorldPacketHandler.cpp`
- `Docs/Plan/handoffs/lift-lobbydaemon-v2b-pod-01.md`
