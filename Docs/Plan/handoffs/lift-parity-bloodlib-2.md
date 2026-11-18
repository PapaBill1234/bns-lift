# lift-parity-bloodlib-2: handoff

## Done
- Shared library 409/490 -> 414/490 (84.5 %). CG 411 -> 418, LG 517 -> 522, SCD 493 -> 498, POD 540 -> 545. MATCH -> DIFF 0.
- `SessionBuffer.cpp` block order (+4 each exe); `Session::handlePacket` 0xf750 order (+1 each exe).
- `Port::Clear` + `Port::clearPool` MATCH in CG (body copy, `pool` local); `PortListener` ctor sets `_tag`, memset.
- `Docs/Parity/lessons.md`: A17 (worked), 2 new lines in B (did not work).

## Not done (shared DIFF, CG addresses where known): function, signal, cause, why stopped
- `Port::Clear`, `Port::clearPool` (LG/SCD/POD): orig refs `L"source\Listener.cpp"`, const -1; ours const 0x30. LTCG inline choice differs per exe; one source cannot match CG and LG. Stopped.
- `Port::Initialize` 0x18b70: const -2 (EH state) missing. Orig has an EH frame; probably a class `operator new(size,file,line)` + matching delete. Not checked.
- `Session::HandleEvent` 0xf1c0: tail merge 780+838 and 785+824 differ. A source goto lowered the score (98.5 -> 97.1). Stopped.
- `Session::~Session` 0xe0a0, `recv` 0xf0d0, `HandleFailedEvent` 0xf5d0, `Accept` 0xe7c0: constants only (LTCG folding). Not tried.
- `Session::Connect`, `Session::Session`, `Session::initialize`, `Session::SendV`: other callee / inline choice. Not tried.
- `SessionSendBuffer::clearPacketBufferList` 0x1a980: orig calls `RefCntHistory::add` out of line; other modules inline it. A global noinline is wrong.
- `Daemon::start`, `Daemon::Start`, `BloodDaemonMain`, `wmain`, `makeConsole`, `InitSymbol`: large; call order and inline choice. Not tried (turns).
- `LogMedia::Write`, `LogFile::writeFile` (stop list B), `IoWorker::run`, `Network::*` (6), `SysInfo::*` (2): not tried.
- `PipeConsole::*` (5), `PipeCommandProcess::processCommand`, `AlertSender::run`: stop list B.
- `ThreadManager::Initialize`, `operator delete`: stop list.
- `aes128Table*` (4), `Blowfish::Setup`: crypto-2 scope; constant tables. Not tried.
- `PacketBuffer::*` (3), `PacketBufferAllocator::initAllocator`, `TrustedPacketBufferHandler::ToPacket`, `FragmentPacketConcatenater::*` (2), `RepeatPacketComposer::PushRepeatCount`, `TFPP_PumpPacket`: not tried (turns).
- `DaemonConfig::*` (2), `BnsCommonConfig::*` (2), `CrashHandler::*` (2), `Daemon::Daemon`, `Daemon::LoadVersion`, `Daemon::setAddress`: not tried.
- `TimerQueue::*` (2), `StaticPageMemoryManager::Initialize`, `String::GetId128FromGuidString`, `WinServiceConsole::UninstallService`, `WindowConsole::Open`, `Channel::MakeSession`: not tried.
- `HandleCacheGate*` (5), `CacheGateSessionHandler::*` (2): server handlers, error block order (see lessons B). Not tried.

## ❓
- None new.

## Blocked
- None.

## Gate result
- `tools/gate.sh`: gate ok. `tools/parity.sh`: parity ok (MATCH -> DIFF 0 in all 4 exes).

Turns: 84
