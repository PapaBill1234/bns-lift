# lift-parity-scd-2: SmartCouponDaemon: handler inline depth and SmartCouponDB

Repo: bns-lift (PRIVATE). IDA only when the pseudocode and funcdiff are not enough (`/home/ubuntu/Documents/Codex/private-project/ida/lift/SmartCouponDaemon/SmartCouponDaemon.exe`).

## Goal
The exe-only code of SmartCouponDaemon compiles to the same code as the original. SmartCouponDaemon gets near 90 % parity.

## Facts
- Read `Docs/Parity/README.md` first. It has the goal, the parity definition, the commands and the rules.
- Read `Docs/Parity/triage.md`, `Docs/Parity/lessons.md` and `Docs/Parity/review-1.md` (section 5).
- Read `Docs/Plan/handoffs/lift-parity-scd-1.md` for the DIFF list of round 1.
- The runner gate runs `tools/gate.sh` and then `tools/parity.sh`. The gate fails if an exe loses a MATCH function.
- Run `tools/gate.sh` and then `tools/parity.sh` yourself before you stop. One parity run takes about 2 to 10 minutes.
- Pseudocode of the original exes: `~/.cache/bns-lift/hr/<EXE>/` for CacheGate, LobbyGate, SmartCouponDaemon and PostOfficeDaemon.
- Scope: the DIFF functions and misses of `SmartCouponDaemon` that are not shared and that the earlier round-2 cards did not fix. The exe-only code is in `src/Server/SmartCouponDaemon/`.
- Known causes with no fix yet: handler inline depth (the original inlines other callees in the packet handlers); `SmartCouponDB::ProcessCharacterGameEventLog` 0x117c0 inlines only the first `BindCol` (lessons D); `DbTransaction::BindParam` null check in the callers (lessons A3).
- Stop list: `EventNotiJob::finalize` 0x9cc0 constant CSE, `JobManager::Execute` 0x71a0. Do not try them again.
- Fix the shared code only if a cause in this exe is in the shared code. Then check all 4 exes.

## Tasks
1. Run `tools/gate.sh` and `tools/parity.sh`. List the DIFF functions of your scope.
2. Work in groups of functions with the same cause. For each group: run `funcdiff.py --show`, compare with the pseudocode, change the source, build, measure again.
3. Keep a change only if the MATCH count goes up and no exe loses a MATCH function. Undo a change that does not help.
4. Write each fix pattern that worked and each that did not work in `Docs/Parity/lessons.md`.
5. For each DIFF function that you cannot fix, write one line in the handoff: function, signal, cause, why you stopped. Write `Turns: <n>` in the handoff.

## Files
- `src/Server/SmartCouponDaemon/`
- `src/Server/BloodLib/`
- `src/Server/Shared/`
- `src/Server/Packet/`
- `include/`
- `CMakeLists.txt`
- `Docs/Parity/`
- `Docs/Plan/handoffs/lift-parity-scd-2.md`

## Done when
- `SmartCouponDaemon` has 90 % parity or more, or the handoff gives the cause of each DIFF function and each miss that is left.
- `tools/parity.sh` passes.
