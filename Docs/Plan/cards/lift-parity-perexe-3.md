# lift-parity-perexe-3: per-exe build define, per-exe inline choice

Repo: bns-lift (PRIVATE). IDA only when the pseudocode and funcdiff are not enough (`/home/ubuntu/Documents/Codex/private-project/ida/lift/CacheGate/CacheGate.exe`).

## Goal
Shared functions that the original compiles in a different form per exe get MATCH in each exe.

## Facts
- Read `Docs/Parity/README.md` first. It has the goal, the parity definition, the commands and the rules.
- Read `Docs/Parity/triage.md`, `Docs/Parity/lessons.md` and `Docs/Parity/review-2.md` (section 5).
- The runner gate runs `tools/gate.sh` and then `tools/parity.sh`. The gate fails if an exe loses a MATCH function.
- Run `tools/gate.sh` and then `tools/parity.sh` yourself before you stop. One parity run takes about 2 to 10 minutes.
- Pseudocode of the original exes: `~/.cache/bns-lift/hr/<EXE>/` for CacheGate, LobbyGate, SmartCouponDaemon and PostOfficeDaemon.
- Parity at review 2: CG 420/491, LG 530/739, SCD 510/669, POD 588/759, shared 421/499.
- Cause: the shared library is built one time per exe, but the original has a different inline choice or code per exe.
  Add a define `-DLIFT_EXE_<X>` (X = CG, LG, SCD, POD) in `tools/vs2010/build.sh` and use it only where the original differs.
- Named functions:
  - `TimerQueue::~TimerQueue` (DIFF in LG, SCD, POD).
  - `Session::Send(Packet const*)` and `Session::deallocateCrypt`: inline in SCD and POD (ONLY-OURS there), a call in CG and LG
    (CG 0x18f00, 0x194c0).
  - `Port::Clear` and `Port::clearPool`.
  - Path literal DIFFs that are left (6 shared, 4 exe-only entries).
- Mark each per-exe block with `// LIFT: per-exe form, <exe> <address>`.

## Tasks
1. Run `tools/gate.sh`, `tools/parity.sh` and `tools/parity_shared.py --list`. List the DIFF functions of your scope.
2. Add the define. For each function: run `funcdiff.py --show`, compare with the pseudocode of each exe, change the source, build, measure again.
3. Keep a change only if the MATCH count goes up and no exe loses a MATCH function. Undo a change that does not help.
4. Write each fix pattern that worked and each that did not work in `Docs/Parity/lessons.md`.
5. For each DIFF function of your scope that you cannot fix, write one line in the handoff: function, signal, cause, why you stopped. Write `Turns: <n>` in the handoff.

## Files
- `tools/vs2010/build.sh`
- `src/Server/`
- `include/`
- `CMakeLists.txt`
- `Docs/Parity/`
- `Docs/Plan/handoffs/lift-parity-perexe-3.md`

## Done when
- Each named function is MATCH in each exe, or the handoff gives its cause.
- `tools/parity.sh` passes.
