# lift-parity-bloodlib-2: shared BloodLib DIFF functions that are left

Repo: bns-lift (PRIVATE). IDA only when the pseudocode and funcdiff are not enough (`/home/ubuntu/Documents/Codex/private-project/ida/lift/CacheGate/CacheGate.exe`).

## Goal
The shared library (BloodLib, Shared, Packet) gets near 99 % parity (`tools/parity_shared.py`).

## Facts
- Read `Docs/Parity/README.md` first. It has the goal, the parity definition, the commands and the rules.
- Read `Docs/Parity/triage.md`, `Docs/Parity/lessons.md` and `Docs/Parity/review-1.md` (section 5).
- The runner gate runs `tools/gate.sh` and then `tools/parity.sh`. The gate fails if an exe loses a MATCH function.
- Run `tools/gate.sh` and then `tools/parity.sh` yourself before you stop. One parity run takes about 2 to 10 minutes.
- Pseudocode of the original exes: `~/.cache/bns-lift/hr/<EXE>/` for CacheGate, LobbyGate, SmartCouponDaemon and PostOfficeDaemon.
- Scope: the shared DIFF functions from `tools/parity_shared.py --list` that the cards tool-2, paths-2 and crypto-2 did not fix. At review 1 the shared library had 369/489 (Fix V + T: 394/489).
- Main classes left (shared entries at review 1): call order or count (34: merged tails, block order), other callee (32), orig calls more (18), constants only (LTCG folding, stack).
- Named functions: `Session::HandleEvent` 0xf1c0, `Session::handlePacket` 0xf750, `Session::Connect`, `Port`, `SessionSendBuffer`, `Daemon::start`, `BloodDaemonMain`, `Log::Flush`, `Log::Initialize`, `DelayedRelease::Cleanup`, `Prng::addEntropy`, `Console::Flush` (CG addresses).
- Stop list (do not try again): `.tls` order, `ThreadManager::Initialize` constant propagation, `EventNotiJob::finalize` constant CSE, `JobManager::Execute*`, ICF names, `wmain$dtor$0`, `operator delete`.

## Tasks
1. Run `tools/gate.sh`, `tools/parity.sh` and `tools/parity_shared.py --list`. List the shared DIFF functions of your scope.
2. Work in groups of functions with the same cause. For each group: run `funcdiff.py --show`, compare with the pseudocode, change the source, build, measure again.
3. Keep a change only if the MATCH count goes up and no exe loses a MATCH function. Undo a change that does not help.
4. Write each fix pattern that worked in `Docs/Parity/lessons.md`: the cause, the source change, one example function. Also write the patterns that did not work.
5. For each shared DIFF function that you cannot fix, write one line in the handoff: function, signal, cause, why you stopped. Write `Turns: <n>` in the handoff.

## Files
- `src/Server/BloodLib/`
- `src/Server/Shared/`
- `src/Server/Packet/`
- `include/`
- `CMakeLists.txt`
- `Docs/Parity/`
- `Docs/Plan/handoffs/lift-parity-bloodlib-2.md`

## Done when
- The shared library has 99 % parity, or the handoff gives the cause of each shared DIFF function that is left.
- `tools/parity.sh` passes.
