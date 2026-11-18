# lift-parity-paths-2: per-exe path literals in all 4 exes

Repo: bns-lift (PRIVATE). IDA only when the pseudocode and funcdiff are not enough.

## Goal
Each `__FILE__`-style literal and each header path literal is equal to the original in each exe. Each exe and the shared library get more MATCH functions.

## Facts
- Read `Docs/Parity/README.md` first. It has the goal, the parity definition, the commands and the rules.
- Read `Docs/Parity/triage.md`, `Docs/Parity/lessons.md` (pattern A5) and `Docs/Parity/review-1.md` (section 5).
- The runner gate runs `tools/gate.sh` and then `tools/parity.sh`. The gate fails if an exe loses a MATCH function.
- Run `tools/gate.sh` and then `tools/parity.sh` yourself before you stop. One parity run takes about 2 to 10 minutes.
- Pseudocode of the original exes: `~/.cache/bns-lift/hr/<EXE>/` for CacheGate, LobbyGate, SmartCouponDaemon and PostOfficeDaemon.
- Scope (cause class "`__FILE__` literal path or count" and "Refs only": 61 shared, 82 exe-only entries; part of 38 + 29 refs only):
  - `PacketUtil.h` has the LobbyGate path in CG and POD (`PacketFormatIterator::SetFormat`).
  - `StlMemory.h` has the CG path in LG (7 functions), SCD (6), POD (6), and CG (3, upper or lower case).
  - `FragmentPacket.cpp` is `..\..\Packet\` in ours, `..\Packet\` in LG (5 functions).
  - POD: ours refs the `Lock.h` path in 7 functions (36 refs), the original in none (`RelayContext::ProcessRelayResponse`, `ProcessRelayTimeout`, `*::updateWorldList`, `UnsentPostContextManager::initContextManager`) ❓.
  - `source\Memory.cpp`: the original has 6 more refs in `BloodDaemonMain` and `Daemon::start` (4 exes) ❓.
- Find the literal of each function with `.scratch/strxref.py`-style string xrefs or `funcdiff.py --show`.
- Keep the object order of CG (`LIFT_COMMON_SOURCES`, `lift_common_cg`). A new object moves the data layout.
- After a header change, `touch` the `.cpp` files that include it, if `tools/vs2010/build.sh` does not track headers yet.

## Tasks
1. Run `tools/gate.sh` and `tools/parity.sh`. List the DIFF functions of your scope with `funcdiff.py --show`.
2. Work in groups of functions with the same literal. For each group: change the source (macro with `#ifndef` default, per-exe wrapper `.cpp`), build, measure again.
3. Keep a change only if the MATCH count goes up and no exe loses a MATCH function. Undo a change that does not help.
4. Write each fix pattern that worked in `Docs/Parity/lessons.md` (A5). Also write the patterns that did not work.
5. For each DIFF function of your scope that you cannot fix, write one line in the handoff: function, signal, cause, why you stopped. Write `Turns: <n>` in the handoff.

## Files
- `src/Server/`
- `src/Security/`
- `include/`
- `CMakeLists.txt`
- `Docs/Parity/`
- `Docs/Plan/handoffs/lift-parity-paths-2.md`

## Done when
- Each path literal of the scope is equal to the original, or the handoff gives the cause of each DIFF function that is left.
- `tools/parity.sh` passes.
