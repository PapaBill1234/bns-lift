# lift-parity-consts-3: constants and refs with no known cause (shared)

Repo: bns-lift (PRIVATE). IDA only when the pseudocode and funcdiff are not enough (`/home/ubuntu/Documents/Codex/private-project/ida/lift/CacheGate/CacheGate.exe`).

## Goal
Find the cause of the shared constant and ref DIFFs. Fix the shared functions first.

## Facts
- Read `Docs/Parity/README.md` first. It has the goal, the parity definition, the commands and the rules.
- Read `Docs/Parity/triage.md`, `Docs/Parity/lessons.md` and `Docs/Parity/review-2.md` (section 5).
- The runner gate runs `tools/gate.sh` and then `tools/parity.sh`. The gate fails if an exe loses a MATCH function.
- Run `tools/gate.sh` and then `tools/parity.sh` yourself before you stop. One parity run takes about 2 to 10 minutes.
- Pseudocode of the original exes: `~/.cache/bns-lift/hr/<EXE>/` for CacheGate, LobbyGate, SmartCouponDaemon and PostOfficeDaemon.
- Entries at review 2: constants only 79 shared + 35 exe-only; refs (+ consts) 37 shared + 25 exe-only.
- Signals: EH state numbers, LTCG constant folding, stack frame size, line numbers in assert or log calls, different data refs.
- Shared functions: `Session::Accept`, `Session::recv`, `Session::HandleFailedEvent`, `Session::Session`, `Session::initialize`, `Daemon::Start`,
  `Daemon::setAddress`, `SysInfo::*`, `Network::Clear`, `Network::Network`, `Network::initWorkerThread`, `Network::GetAddressStringW`,
  `PacketBuffer::Decompose`, `PacketBuffer::CheckCompose`, `TrustedPacketBufferHandler::ToPacket`, `StaticPageMemoryManager::Initialize`,
  `PacketBufferAllocator::initAllocator`, `WindowConsole::Open`, `Port::Initialize` (EH state -2), `FragmentPacketConcatenater::*`,
  `RepeatPacketComposer::PushRepeatCount`.
- Check first: local object order (EH state), member types (stack size), `__LINE__` in macros, `static const` against `#define`.
- Stop list: `.tls` layout, `ThreadManager::Initialize`, `EventNotiJob::finalize`, `JobManager::Execute*`, ICF names.

## Tasks
1. Run `tools/gate.sh`, `tools/parity.sh` and `tools/parity_shared.py --list`. List the DIFF functions of your scope.
2. Work in groups of functions with the same signal. For each group: run `funcdiff.py --show`, compare with the pseudocode, change the source, build, measure again.
3. Keep a change only if the MATCH count goes up and no exe loses a MATCH function. Undo a change that does not help.
4. Write each cause that you found, each fix pattern that worked and each that did not work in `Docs/Parity/lessons.md`.
5. For each DIFF function of your scope that you cannot fix, write one line in the handoff: function, signal, cause, why you stopped. Write `Turns: <n>` in the handoff.

## Files
- `src/Server/BloodLib/`
- `src/Server/Shared/`
- `src/Server/Packet/`
- `include/`
- `CMakeLists.txt`
- `tools/vs2010/build.sh`
- `Docs/Parity/`
- `Docs/Plan/handoffs/lift-parity-consts-3.md`

## Done when
- Each named function is MATCH, or the handoff gives its signal and cause.
- `tools/parity.sh` passes.
