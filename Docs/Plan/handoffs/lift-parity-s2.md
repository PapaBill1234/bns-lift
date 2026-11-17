# lift-parity-s2 handoff

## Done
- Parity ok in all 4 exes. MATCH baseline -> now: CG 331 -> 345, LG 400 -> 425, SCD 367 -> 388, POD 407 -> 423. MATCH -> DIFF 0.
- Files: `Session.cpp`, `Listener.cpp`, `Network.cpp`, `PacketBuffer.cpp`, `LogBuffer.cpp` (BOM), `SessionBuffer.cpp`,
  `PacketBuffer.h`, `RefCntObject.h` (`_ref` plain `long`). Patterns 11, 13-17 in `Docs/Parity/lessons.md`.
- Now MATCH: `PortListener::Initialize`, `Session::Connect` (CG, POD), `Network::initializeSocketInterface`, `Session::sendNext`,
  `Connection::AsyncSend`, `PacketBufferPool::allocate`, `PacketBufferAllocator::allocate`, `SessionSendBuffer::Clear`, others.

## Not done (function: signal, cause, why stopped)
- `Packet::Allocate`, `Packet::Concatenate`, `PacketBuffer::deallocate_me`, `PacketBufferAllocator::Initialize/initAllocator`, `Session::SendV`: const 0x20 vs 0x88, TLS offset of `_Local`; link order, not source.
- `Session::Session(uint, ...)` 0xdf80, `StaticPageMemoryManager::Initialize`: ref/const, our LTCG folds `&BaseMemoryManager::_Instance`; source form unknown.
- `Network::OpenPort` 0xd2c0: const 0xaa, orig keeps the `portId == 0` assert; our IPA drops it. Source form unknown.
- `Network::Initialize`: callee name `?Setup@PacketCrypt@@...` not demangled in the orig PDB (tooling).
- `Network::Network/Clear/GetAddressStringW/initWorkerThread/SetMaxIdleTime`: refs, `??_7RefCntObject` and inline order; not reached.
- `Session::HandleEvent` 0xf1c0: calls, orig merges 2 `Log::Write` tails; cause unknown (2 forms tried).
- `Session::handlePacket` 0xf750: calls, one extra `Packet::Clear` tail; source form unknown.
- `Session::Connect` (LG, SCD): const 0x1388, timeout folding differs by LTCG; not fixable in source.
- `Session::initialize`: ref `??_7CrashHandler` vs `??_7SessionRecvBuffer`, likely ICF noise.
- `Session::~Session`, `Session::Accept`, `HandleFailedEvent`, `recv`, `SetHandshakeParameter`, `completeHandshake`: not reached.
- `SessionSendBuffer::Add` 0x1a350, `RemoveSentBuffer` 0x1a4f0, `increaseBuffer` 0x1a810, `Initialize`, `clearPacketBufferList`: not reached.
- `Channel::Close`, `Channel::~Channel`, `Channel::MakeSession`, `DaemonChannel::~DaemonChannel`, `ClientSideDaemonChannel::~ClientSideDaemonChannel`: not reached.
- `FragmentPacketConcatenater::Add/Clone/Copy`, `Packet::Clear`, `Packet::Copy`, `PacketBuffer::Compose/Decompose/CheckCompose/DecomposeText`: not reached.

## ❓
- `src/Server/LobbyGate/ContentsRuleConfigDefinition.cpp` needs a UTF-8 BOM (not in the file list).
- `RefCntHistory::_dumped/_historyPos` volatile not checked against the PDB.

## Blocked
- None.

## Gate result
- `tools/gate.sh`: gate ok. `tools/parity.sh`: parity ok (all 4 exes up, MATCH -> DIFF 0).
