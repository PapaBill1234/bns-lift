# lift-parity-noinline-2: noinline on the misses in all 4 exes

Repo: bns-lift (PRIVATE). IDA only when the pseudocode and funcdiff are not enough.

## Goal
Each function that the original calls out of line is a function in our exe too. The misses go away and their callers become MATCH.

## Facts
- Read `Docs/Parity/README.md` first. It has the goal, the parity definition, the commands and the rules.
- Read `Docs/Parity/triage.md`, `Docs/Parity/lessons.md` (pattern A3) and `Docs/Parity/review-1.md` (section 5).
- The runner gate runs `tools/gate.sh` and then `tools/parity.sh`. The gate fails if an exe loses a MATCH function.
- Run `tools/gate.sh` and then `tools/parity.sh` yourself before you stop. One parity run takes about 2 to 10 minutes.
- Pseudocode of the original exes: `~/.cache/bns-lift/hr/<EXE>/` for CacheGate, LobbyGate, SmartCouponDaemon and PostOfficeDaemon.
- Pattern: `__declspec(noinline)` on the function, mark `// LIFT:` with the reason and the address. Use it only when the original never inlines the function (check all callers in all exes).
- Scope (cause classes "Orig calls more" 18 shared + 8 exe-only, and the misses that are not crypto):
  - All exes: `Log::Flush`, `Log::Initialize`, `DelayedRelease::Cleanup`, `Prng::addEntropy`, `Console::Flush`.
  - LG: `ContentsRuleConfig::Dump`, `LobbyGateConfig::Dump`, `ClientManager::Initialize`, `GateKeyManager::Initialize`, `CriticalSection::CriticalSection`, `Session::Send`, `Session::allocateCrypt`, `deallocateCrypt`.
  - SCD: `SetManagerChannel`, `EventNotiJob::eventNotiExpire`, `DbTransaction::BindCol`, `Network::OpenPort`.
  - POD: `Channel::Send`, `GrowingBuffer::Add`, `grow`, `Packet::Decompose`, `parseString`, `DaemonConfig::Dump`, `PostOfficeDB::UpdateStatusToDelivery*`.
- A noinline change can change the inline choice of the callers (lessons A3). Check the callers after each change.
- Do not try again: `TimerQueue::Remove` / `removeShortTermQueue` (POD -2), `noinline` on `_Tree::clear`.

## Tasks
1. Run `tools/gate.sh` and `tools/parity.sh`. List the misses and their callers from `build-vs2010/<EXE>.funcdiff.json`.
2. For each miss: check that the original never inlines it. Add `__declspec(noinline)`, build, measure again.
3. Keep a change only if the MATCH count goes up and no exe loses a MATCH function. Undo a change that does not help.
4. Write each fix and each change that did not work in `Docs/Parity/lessons.md` (A3, B).
5. For each miss that you cannot fix, write one line in the handoff: function, signal, cause, why you stopped. Write `Turns: <n>` in the handoff.

## Files
- `src/Server/`
- `src/Security/`
- `include/`
- `CMakeLists.txt`
- `Docs/Parity/`
- `Docs/Plan/handoffs/lift-parity-noinline-2.md`

## Done when
- Each miss of the scope is a function in our exe, or the handoff gives its cause.
- `tools/parity.sh` passes.
