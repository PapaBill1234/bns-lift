# lift-parity-inline-3: orig calls more, ours calls more

Repo: bns-lift (PRIVATE). IDA only when the pseudocode and funcdiff are not enough (`/home/ubuntu/Documents/Codex/private-project/ida/lift/CacheGate/CacheGate.exe`).

## Goal
The functions where the original and ours do not inline the same callees get MATCH.

## Facts
- Read `Docs/Parity/README.md` first. It has the goal, the parity definition, the commands and the rules.
- Read `Docs/Parity/triage.md`, `Docs/Parity/lessons.md` and `Docs/Parity/review-2.md` (section 5).
- The runner gate runs `tools/gate.sh` and then `tools/parity.sh`. The gate fails if an exe loses a MATCH function.
- Run `tools/gate.sh` and then `tools/parity.sh` yourself before you stop. One parity run takes about 2 to 10 minutes.
- Pseudocode of the original exes: `~/.cache/bns-lift/hr/<EXE>/` for CacheGate, LobbyGate, SmartCouponDaemon and PostOfficeDaemon.
- Entries at review 2: orig calls more 29 shared + 15 exe-only; ours calls more 13 shared + 24 exe-only.
- Shared functions first: `Log::Initialize`, `Session::~Session`, `String::GetId128FromGuidString`, `WinServiceConsole::UninstallService`,
  `PipeConsole::SetInvalidInfo`, `Network::OpenPort` (2 overloads), `PacketBuffer::Compose`, `CrashHandler::handleCrash`, `Session::HandleEvent`.
- Exe-only: LG `LobbyD::Send*` (6, extra `Packet::Clear`), LG `LobbyDSessionHandler::*`, POD `RelayContext::Process*` (3),
  POD `*PacketBufferHandler::Destroy` (2).
- Fix forms: `__declspec(noinline)` on the callee, `__forceinline`, remove an explicit `Clear` that the original does not call,
  move the body into or out of the header. Lessons A1 to A17 have the forms that worked.
- Do not touch the per-exe functions of `lift-parity-perexe-3` and the handlers of `lift-parity-handlers-3`.

## Tasks
1. Run `tools/gate.sh`, `tools/parity.sh` and `tools/parity_shared.py --list`. List the DIFF functions of your scope.
2. Work in groups of functions with the same callee. For each group: run `funcdiff.py --show`, compare with the pseudocode, change the source, build, measure again.
3. Keep a change only if the MATCH count goes up and no exe loses a MATCH function. Undo a change that does not help.
4. Write each fix pattern that worked and each that did not work in `Docs/Parity/lessons.md`.
5. For each DIFF function of your scope that you cannot fix, write one line in the handoff: function, signal, cause, why you stopped. Write `Turns: <n>` in the handoff.

## Files
- `src/Server/`
- `src/Security/`
- `include/`
- `CMakeLists.txt`
- `Docs/Parity/`
- `Docs/Plan/handoffs/lift-parity-inline-3.md`

## Done when
- Each named function is MATCH, or the handoff gives its cause.
- `tools/parity.sh` passes.
