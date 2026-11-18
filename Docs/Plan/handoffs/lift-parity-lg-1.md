# lift-parity-lg-1 handoff
## Done
- LG MATCH 462 -> 486 (65.8 %). CG 385 -> 386, SCD 429 -> 437, POD 474 -> 479. Exe-only DIFF 118 -> 72.
- Patterns 34-39 are in `Docs/Parity/lessons.md`: handler prologue, per-exe RefCntObject/MemoryManager, shared cleanup
  tail + `__try/__finally`, inlined Packet ctor, non-const map pair key, Clone branch order, empty member dtor.
- Files: `src/Server/LobbyGate/{Client.h,Client.cpp,LobbyDPacketHandler.cpp}`, `src/Server/Packet/FragmentPacket.cpp`,
  `src/Server/BloodLib/source/{PacketBufferHandler,RefCntObject*,MemoryManager*}.cpp`, `CMakeLists.txt`, `Docs/Parity/`.
- Tool fact: `tools/vs2010/build.sh` ignores header changes. Touch the `.cpp` files after a header edit.
## Not done (72 exe-only DIFF; signal, cause, why stopped)
- Token Ok/Fail handlers 0xbe90, 0xca10, 0xcd00, 0xe810, 0xeb30, 0xef10, 0xf230, 0xffc0, HelloOk 0xaf20 (77-96): calls
  + refs. Block order and merged log/cleanup tails. Not tried in this card (pattern 36 is the probable fix).
- KickNotify 0x10660, CloseSessionNotify, GetEnterWorldTokenOk (97-99): refs. Orig loads `LobbyGate::_instance` 2 times;
  ours 1. CloseSessionNotify: orig calls `removeReferenceCount` before `AddJobTimer`. Cause unknown.
- `LobbyD::Send*Req` x6, `LobbyD::hello/Hello` (92-98): calls. Packet compose inline form. Not analysed.
- `Client::Send*Ok` x5 (84-85), `ClientManager::broadcast/BroadcastAnnounceNotify/DisconnectAll`: calls + refs. Orig
  merges the LT_ERROR `Log::Write` calls and has one `Packet::Clear`. No source form found.
- `GateKeyManager::Finalize`, `ClientManager::Finalize` (72): map clear loop inline form. `MakeGateKey` (94): orig calls
  the `GateKeyEntry` scalar deleting dtor in the fail path. Not finished.
- `ContentsRuleConfig::*` x6, `LobbyGate::initialize/reload/initNetwork/PrintDependency`, `PcCafe...::Set`: consts +
  calls. Noinline candidates (0x3910, 0x13e20, 0x8600, 0x5b90) and UTF-8 BOM (pattern 13). Not tried.
- `FragmentPacket*`, `Packet::Copy`, `ClientPacketBufferHandler::ToPacket`, `Session::*Handshake*`, `BroadcastCrypt::*`,
  `zstd*`, `AlertSender::init`, `PipeConsole::SetRunningInfo`, `Network::SetMaxIdleTime`, `IdleWatcher/IdleStateTable`,
  `ClientSessionHandler::*`, `LobbyDSessionHandler::*`, timers: per-exe copies of shared code or LTCG inline choices.
  Not analysed in this card. `operator delete` (0): ICF name only.
## ❓
- funcdiff `string_at` noise moves 2-8 MATCH per layout change (AlertSender/CrashHandler ctors). Needs a tooling card.
- 90 % (665) is not reachable in this card.
## Blocked
- None.
## Gate result
- `tools/gate.sh`: gate ok. `tools/parity.sh`: parity ok, no MATCH lost against the baseline.
