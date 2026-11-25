# lift-parity-dbbind-3: DB loaders with inlined SQLBindCol

Repo: bns-lift (PRIVATE). IDA only when the pseudocode and funcdiff are not enough (`<work-root>/ida/lift/PostOfficeDaemon/PostOfficeDaemon.exe`).

## Goal
The DB loader functions of SCD and POD get MATCH.

## Facts
- Read `Docs/Parity/README.md` first. It has the goal, the parity definition, the commands and the rules.
- Read `Docs/Parity/triage.md`, `Docs/Parity/lessons.md` and `Docs/Parity/review-2.md` (section 5).
- The runner gate runs `tools/gate.sh` and then `tools/parity.sh`. The gate fails if an exe loses a MATCH function.
- Run `tools/gate.sh` and then `tools/parity.sh` yourself before you stop. One parity run takes about 2 to 10 minutes.
- Pseudocode of the original exes: `~/.cache/bns-lift/hr/<EXE>/` for CacheGate, LobbyGate, SmartCouponDaemon and PostOfficeDaemon.
- Cause: the original inlines the bind helpers into direct `SQLBindCol` calls (bind macros). Ours calls `DbTransaction::BindCol`.
- Named functions:
  - SCD `SmartCouponDB::Load*` (4), `Process*GameEventLog` (2), `DbTransaction::BindCol`.
  - POD `PostOfficeDB::Load*` (4), `PostOfficeDB::RegisterPost`.
- A half patch is in the pod-2 worktree: `.scratch/postofficedb-bindcol-macros.patch` (not in git). Use it if it exists, else start again.

## Tasks
1. Run `tools/gate.sh`, `tools/parity.sh` and `tools/parity_shared.py --list`. List the DIFF functions of your scope.
2. For each function: run `funcdiff.py --show`, compare with the pseudocode (the order and the arguments of each `SQLBindCol`), change the source, build, measure again.
3. Keep a change only if the MATCH count goes up and no exe loses a MATCH function. Undo a change that does not help.
4. Write each fix pattern that worked and each that did not work in `Docs/Parity/lessons.md`.
5. For each DIFF function of your scope that you cannot fix, write one line in the handoff: function, signal, cause, why you stopped. Write `Turns: <n>` in the handoff.

## Files
- `src/Server/SmartCouponDaemon/`
- `src/Server/Economy/`
- `src/Server/BloodLib/`
- `include/`
- `Docs/Parity/`
- `Docs/Plan/handoffs/lift-parity-dbbind-3.md`

## Done when
- Each named function is MATCH, or the handoff gives its cause.
- `tools/parity.sh` passes.
