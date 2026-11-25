# lift-parity-arraynew-3: placement array new and eh vector constructor iterator

Repo: bns-lift (PRIVATE). IDA only when the pseudocode and funcdiff are not enough (`<work-root>/ida/lift/LobbyGate/LobbyGate.exe`).

## Goal
The functions that make or delete object arrays get MATCH (pattern of `lift-parity-scd-2`).

## Facts
- Read `Docs/Parity/README.md` first. It has the goal, the parity definition, the commands and the rules.
- Read `Docs/Parity/triage.md`, `Docs/Parity/lessons.md` and `Docs/Parity/review-2.md` (section 5).
- Read `Docs/Plan/handoffs/lift-parity-scd-2.md` for the array new pattern.
- The runner gate runs `tools/gate.sh` and then `tools/parity.sh`. The gate fails if an exe loses a MATCH function.
- Run `tools/gate.sh` and then `tools/parity.sh` yourself before you stop. One parity run takes about 2 to 10 minutes.
- Pseudocode of the original exes: `~/.cache/bns-lift/hr/<EXE>/` for CacheGate, LobbyGate, SmartCouponDaemon and PostOfficeDaemon.
- Named functions:
  - LG `GateKeyManager::Initialize` (score 32.6, calls `eh vector constructor iterator`), `GateKeyManager::Finalize`.
  - LG `ClientManager::Initialize`, `ClientManager::Finalize`, `ClientManager::broadcast`.
  - Orig-only `CriticalSection::CriticalSection` (out of line in the original).
  - `operator delete[]` (LG, POD).
  - Placement `operator delete` (CG, SCD, POD, LG: score 0, crash log at `Memory.h:173`).
- The form: `new (buffer) T[n]` with a user `operator new[]` gives `eh vector constructor iterator`. A class with a non-trivial
  destructor gives `eh vector destructor iterator` and a count cookie.

## Tasks
1. Run `tools/gate.sh`, `tools/parity.sh` and `tools/parity_shared.py --list`. List the DIFF functions of your scope.
2. For each function: run `funcdiff.py --show`, compare with the pseudocode, change the source, build, measure again.
3. Keep a change only if the MATCH count goes up and no exe loses a MATCH function. Undo a change that does not help.
4. Write each fix pattern that worked and each that did not work in `Docs/Parity/lessons.md`.
5. For each DIFF function of your scope that you cannot fix, write one line in the handoff: function, signal, cause, why you stopped. Write `Turns: <n>` in the handoff.

## Files
- `src/Server/LobbyGate/`
- `src/Server/Economy/`
- `src/Server/BloodLib/`
- `src/Server/Shared/`
- `include/`
- `CMakeLists.txt`
- `Docs/Parity/`
- `Docs/Plan/handoffs/lift-parity-arraynew-3.md`

## Done when
- Each named function is MATCH, or the handoff gives its cause.
- `tools/parity.sh` passes.
