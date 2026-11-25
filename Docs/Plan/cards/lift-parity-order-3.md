# lift-parity-order-3: block order and call order

Repo: bns-lift (PRIVATE). IDA only when the pseudocode and funcdiff are not enough (`<work-root>/ida/lift/CacheGate/CacheGate.exe`).

## Goal
The functions with a different block order or call order (not packet handlers) get MATCH.

## Facts
- Read `Docs/Parity/README.md` first. It has the goal, the parity definition, the commands and the rules.
- Read `Docs/Parity/triage.md`, `Docs/Parity/lessons.md` and `Docs/Parity/review-2.md` (section 5).
- The runner gate runs `tools/gate.sh` and then `tools/parity.sh`. The gate fails if an exe loses a MATCH function.
- Run `tools/gate.sh` and then `tools/parity.sh` yourself before you stop. One parity run takes about 2 to 10 minutes.
- Pseudocode of the original exes: `~/.cache/bns-lift/hr/<EXE>/` for CacheGate, LobbyGate, SmartCouponDaemon and PostOfficeDaemon.
- Entries at review 2: call order 29 shared + 27 exe-only; call count 2 shared + 3 exe-only.
- Shared functions first: `BloodDaemonMain`, `Daemon::start`, `makeConsole`, `BnsCommonConfig::LoadBnsCommonConfig`, `DaemonConfig::Load`,
  `LogFile::writeFile`, `PipeConsole::run`.
- Exe-only: SCD `DChannelMgr::SetupDaemonList`, `Channel::MakeSession`, `GameEventManager::PostGameEventLogList`;
  POD `UnsentPostContextManager::*` (3); LG `IdleStateTable::scan`, `PipeConsole::SetRunningInfo`.
- Fix forms that worked (lessons): `if` / `else` order, early `return` against nested `if`, `goto` to a shared tail, loop form
  (`for` against `while`), order of the error checks.
- Stop list: `POD DaemonConfig::Dump` (dead flow), `TimerQueue::clearShortTermQueueSlot`.

## Tasks
1. Run `tools/gate.sh`, `tools/parity.sh` and `tools/parity_shared.py --list`. List the DIFF functions of your scope.
2. For each function: run `funcdiff.py --show`, compare with the pseudocode, change the source, build, measure again.
   Stop a function after 3 tries with no gain.
3. Keep a change only if the MATCH count goes up and no exe loses a MATCH function. Undo a change that does not help.
4. Write each fix pattern that worked and each that did not work in `Docs/Parity/lessons.md`.
5. For each DIFF function of your scope that you cannot fix, write one line in the handoff: function, signal, cause, why you stopped. Write `Turns: <n>` in the handoff.

## Files
- `src/Server/`
- `include/`
- `Docs/Parity/`
- `Docs/Plan/handoffs/lift-parity-order-3.md`

## Done when
- Each named function is MATCH, or the handoff gives its cause.
- `tools/parity.sh` passes.
