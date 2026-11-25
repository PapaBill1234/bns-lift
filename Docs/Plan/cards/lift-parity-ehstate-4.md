# lift-parity-ehstate-4: EH state -2 with ::new and the global placement delete

Repo: bns-lift (PUBLIC). Never commit binaries, PDBs, IDA databases or abuse notes. IDA only when the pseudocode and funcdiff are not enough (`<work-root>/ida/lift/PostOfficeDaemon/PostOfficeDaemon.exe`).

## Goal
The functions with the EH state const `0xfffffffffffffffe` DIFF are MATCH, or the handoff gives the cause of each.

## Facts
- Read `Docs/Parity/README.md` first. It has the goal, the parity definition, the commands and the rules.
- Read `Docs/Parity/triage.md`, `Docs/Parity/lessons.md` and `Docs/Parity/review-3.md` (section 5). Read `Docs/Parity/rules-proposal.md` section 5.
- The runner gate runs `tools/gate.sh` and then `tools/parity.sh`. The gate fails if an exe loses a MATCH function.
- Run `tools/gate.sh` and then `tools/parity.sh` yourself before you stop. One parity run takes about 2 to 10 minutes.
- Pseudocode of the original exes: `~/.cache/bns-lift/hr/<EXE>/` for CacheGate, LobbyGate, SmartCouponDaemon and PostOfficeDaemon.
- Parity at review 3: CG 448/491 (91.2 %), LG 627/739 (84.8 %), SCD 582/669 (87.0 %), POD 665/759 (87.6 %), shared 490/549 (89.3 %).
- Before a source change, read the PDB facts of the function (lessons A21). On a `tls:` or vtable-name DIFF, check the tool output first (lessons A1).
- Lessons for this card: A14 (global placement delete, `::new`, construct before assign), A16 (allocation), F "Placement delete and shared functions".
- Estimate (review-3 section 6): CG +1, LG +2, SCD +2, POD +2.
- Named functions (exe, score, signal):
- `wmain` x4: CG 61.9 (`src/Server/Economy/CacheGate/CacheGate.cpp:92`), LG 66.7 (`src/Server/LobbyGate/LobbyGate.cpp:139`),
  SCD 66.7 (`src/Server/SmartCouponDaemon/SmartCouponDaemon.cpp:140`), POD 85.2 (`src/Server/Economy/PostOfficeDaemon/PostOfficeDaemon.cpp:144`).
- `FragmentPacketConcatenater::Clone` (LG, POD 93.3; `src/Server/Packet/FragmentPacket.cpp:328`).
- LG `IdleWatcher::run` (`src/Server/BloodLib/source/IdleWatcher.cpp:111`).
- SCD `NPServiceChannelManager::HandleMessage` (`src/Server/SmartCouponDaemon/NPServiceChannel.cpp:229`).
- POD `operator delete[]` (score 0; compare with `src/crt/new_delete.c` and `include/vs2010/new`).
- Method (A14): write `::new` at each placement new site of the original. Construct a member object before you assign the allocation pointer.
  The global placement `operator delete(void*, void*)` with the crash body is already lifted (beb4669). Do not add a second one.
- Change only the `wmain` body and the named functions. The exe cards (lg-4, scd-4, pod-4, cg-4) come later and touch the other code of these files.
- Stop rule: stop a function after 3 tries with no score gain. Write it in the handoff. Do not try the functions of the stop list (lessons D) without a new idea.

## Tasks
1. Run `tools/gate.sh`, `tools/parity.sh` and `tools/parity_shared.py --list`. List the DIFF functions of your scope.
2. Work in groups of functions with the same form: run `funcdiff.py --show`, compare with the pseudocode, change the source, build, measure again.
3. Keep a change only if the MATCH count goes up and no exe loses a MATCH function. Undo a change that does not help.
4. Write each fix pattern that worked and each that did not work in `Docs/Parity/lessons.md` (sections A and B, with the count).
5. For each DIFF function of your scope that you cannot fix, write one line in the handoff: function, signal, cause, why you stopped. Write `Turns: <n>` in the handoff.

## Files
- `src/Server/Economy/CacheGate/CacheGate.cpp`
- `src/Server/LobbyGate/LobbyGate.cpp`
- `src/Server/SmartCouponDaemon/SmartCouponDaemon.cpp`
- `src/Server/SmartCouponDaemon/NPServiceChannel.cpp`
- `src/Server/Economy/PostOfficeDaemon/PostOfficeDaemon.cpp`
- `src/Server/Packet/FragmentPacket.cpp` (only `Clone`)
- `src/Server/BloodLib/source/IdleWatcher.cpp` (only `IdleWatcher::run`)
- `src/crt/new_delete.c`
- `include/`
- `Docs/Parity/`
- `Docs/Plan/handoffs/lift-parity-ehstate-4.md`

## Done when
- Each named function is MATCH, or the handoff gives its cause.
- No exe loses a MATCH function.
- `tools/parity.sh` passes.
