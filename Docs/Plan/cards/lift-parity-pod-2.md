# lift-parity-pod-2: PostOfficeDaemon: patterns 47 and 49 again, block order

Repo: bns-lift (PRIVATE). IDA only when the pseudocode and funcdiff are not enough (`<work-root>/ida/lift/PostOfficeDaemon/PostOfficeDaemon.exe`).

## Goal
The exe-only code of PostOfficeDaemon gets the fixes that tool noise stopped in round 1. PostOfficeDaemon gets near 90 % parity.

## Facts
- Read `Docs/Parity/README.md` first. It has the goal, the parity definition, the commands and the rules.
- Read `Docs/Parity/triage.md`, `Docs/Parity/lessons.md` (A9, B, C1) and `Docs/Parity/review-1.md` (section 5).
- Read `Docs/Plan/handoffs/lift-parity-pod-1.md` for the DIFF list of round 1.
- The runner gate runs `tools/gate.sh` and then `tools/parity.sh`. The gate fails if an exe loses a MATCH function.
- Run `tools/gate.sh` and then `tools/parity.sh` yourself before you stop. One parity run takes about 2 to 10 minutes.
- Pseudocode of the original exes: `~/.cache/bns-lift/hr/<EXE>/` for CacheGate, LobbyGate, SmartCouponDaemon and PostOfficeDaemon.
- Scope: the DIFF functions and misses of `PostOfficeDaemon` that are not shared and that the earlier round-2 cards did not fix. The exe-only code is in `src/Server/Economy/PostOfficeDaemon/`.
- Pattern 47 (lessons A9): POD map keys `std::pair<K, V>` as in the PDB. Undone in pod-1 only because of tool noise (lessons C1). lift-parity-tool-2 fixes that noise.
- Pattern 49: remove the `UpdatePostStatus` lift helper (+2 MATCH). Undone for the same reason.
- Block order of the `Get*` functions (lessons A6).
- Fix the shared code only if a cause in this exe is in the shared code. Then check all 4 exes.

## Tasks
1. Run `tools/gate.sh` and `tools/parity.sh`. List the DIFF functions of your scope.
2. Apply pattern 47 and pattern 49 again. Measure.
3. Work on the other groups of functions with the same cause. For each group: run `funcdiff.py --show`, compare with the pseudocode, change the source, build, measure again.
4. Keep a change only if the MATCH count goes up and no exe loses a MATCH function. Undo a change that does not help.
5. Write each fix pattern that worked and each that did not work in `Docs/Parity/lessons.md`.
6. For each DIFF function that you cannot fix, write one line in the handoff: function, signal, cause, why you stopped. Write `Turns: <n>` in the handoff.

## Files
- `src/Server/Economy/PostOfficeDaemon/`
- `src/Server/BloodLib/`
- `src/Server/Shared/`
- `src/Server/Packet/`
- `src/Server/Economy/Shared/`
- `include/`
- `CMakeLists.txt`
- `Docs/Parity/`
- `Docs/Plan/handoffs/lift-parity-pod-2.md`

## Done when
- `PostOfficeDaemon` has 90 % parity or more, or the handoff gives the cause of each DIFF function and each miss that is left.
- `tools/parity.sh` passes.
