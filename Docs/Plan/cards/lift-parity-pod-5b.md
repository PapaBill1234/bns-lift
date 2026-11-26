# lift-parity-pod-5b: PostOfficeDaemon: daemon, world config, handlers

Repo: bns-lift (PUBLIC). Never commit binaries, PDBs, IDA databases or abuse notes. IDA only when the pseudocode, the PDB line map and funcdiff are not enough (`<work-root>/ida/lift/PostOfficeDaemon/PostOfficeDaemon.exe`). Close the database when you are done.

## Goal
The POD daemon, world config and handler DIFF functions are MATCH, or the handoff gives the cause of each. POD moves toward 95 % (722 MATCH).

## Facts
- Read `Docs/Parity/README.md` first. It has the goal, the parity definition, the commands and the rules.
- Read `Docs/Parity/review-4.md` (sections 5 and 6), `Docs/Parity/lessons.md` (the sections below, and B, C4, D) and `Docs/Parity/triage.md`.
- The runner gate runs `tools/gate.sh` and then `tools/parity.sh`. The gate fails if an exe loses a MATCH function. This includes LobbyDaemon.
- LobbyDaemon is done by another system. Do not change `src/Server/LobbyDaemon/`. Its MATCH count must not drop.
- `Docs/Parity/excluded.tsv`, `Docs/Parity/baseline/` and `Docs/Parity/progress.tsv`: do not change them.
- Run `tools/gate.sh` and then `tools/parity.sh` yourself before you stop. One parity run takes about 2 to 10 minutes.
  For a quick loop, use `tools/parity.sh <EXE>` (about 30 s) and the quick loop of lessons C4.
- Pseudocode of the original exes: `~/.cache/bns-lift/hr/<EXE>/`. PDB line maps: `LIFT_IDA_DIR=<work-root>/ida/lift tools/pdbq.py <EXE> lines <lo> <hi>` (A29).
- Main at review 4: CG 456/491 (92.9 %), LG 658/739 (89.0 %), SCD 630/669 (94.2 %), POD 694/759 (91.4 %). Goal: 95 % per exe
  (CG 467, LG 703, SCD 636, POD 722).
- Before a source change, read the PDB facts and the PDB line map of the function (A21, A29). On a `tls:` or vtable-name DIFF, check the tool output first (A1).
- This card runs in parallel with the other round-5 cards. Change only the files in "Files". Each card touches other files.
- Lessons for this card: A14 (EH state -2 in `wmain`, `::new`), A2 (block order), A17 (error tails, `AutoCS` scope), A23 (PacketHandler form), A26 (reload at each use), A28 (`ID128_GUID_ZERO`), A11 (loop forms), A21 and A29 (PDB facts, line maps), B pod-4 rows. Fold of the POD part of lift-parity-ehstate-4.
- Estimate (review-4 section 6): POD +7.
- Stop rule: stop a function after 3 tries with no score gain. Write it in the handoff. Do not try the stop list (lessons D) without a new idea.
- Named functions (exe, score, signals c=calls r=refs k=consts):
- `PostOfficeDaemon.cpp`: `wmain` 85.2 (c89 k67; EH state -2, A14), `PostOfficeDaemon::initialize` 67.8 (c48 r77 k78).
- `WorldConfigManager.cpp`: `WorldConfigManager::updateWorldList` 80.2 (c69 r86 k86), `loadWorldConfigFile` 94.3 (c84; success-first failed, B),
  `setupWorldConfigList` 98.6 (r96; literal register allocation).
- `UnsentPostContext.cpp`: `UnsentPostContextManager::updateWorldList` 90.5 (c77), `initContextManager` 92.9 (c85) (`goto` and RAII forms failed, B).
- `CachedWatchdog.cpp`: `CachedWatchdogManager::updateWorldList` 95.5 (c94 r93).
- Handlers: `HandlePostOfficeHelloReq` 95.6 (k87), `HandlePostOfficeServiceRegisterPostReq` 95.6 (r91), `HandlePostOfficeRegisterPostReq` 98.0 (B rows),
  `ManagementSessionHandler::PacketHandler` 97.8 (the handler call is at the end in the original), `AgentSessionHandler::OnClose` 97.6 (r93).
- `PostContext.cpp`: `PostInfo::CheckValidityPostData` 90.9 (k73; switch lowering), `parseDecInt` 94.4 (k83), `parseHexInt` 97.4 (k92).
- Miss `wmain$dtor$0` (12 bytes): the original `wmain` has an unwind funclet for the local daemon object; ours has none. Fix it together with `wmain` (A14).
  The other POD misses belong to lift-parity-shared-5. List: `funcdiff.py PostOfficeDaemon --build build-vs2010 --only`.
- Stop list (do not try): `PingGenerator::sendPing`, `PostOfficeDaemon::checkCacheGateServiceState` (LTCG `this` propagation).
- `operator delete[]` belongs to lift-parity-shared-5.
## Tasks
1. Run `tools/gate.sh` and `tools/parity.sh`. List the DIFF functions of your scope with score and signal.
2. Work in groups of functions with the same form: run `funcdiff.py --show`, read the pseudocode and the PDB line map, change the source, build, measure again.
3. Keep a change only if the MATCH count goes up and no exe loses a MATCH function. Undo a change that does not help.
4. Write each fix pattern that worked and each that did not work in the handoff, section `## Lessons`, with tables "worked" and "failed"
   (function, before, after, count). Do not edit `Docs/Parity/lessons.md`: the round-5 cards run in parallel, and the review merges the handoff lessons into A and B.
5. For each DIFF function of your scope that you cannot fix, write one line in the handoff: function, signal, cause, why you stopped.
   Write the MATCH count per exe before and after, and `Turns: <n>`, in the handoff.

## Files
- `src/Server/Economy/PostOfficeDaemon/PostOfficeDaemon.cpp`, `PostOfficeDaemon.h`
- `src/Server/Economy/PostOfficeDaemon/WorldConfigManager.cpp`, `WorldConfig.h`, `UnsentPostContext.cpp`, `UnsentPostContext.h`, `UnsentPostChecker.cpp`, `UnsentPostChecker.h`
- `src/Server/Economy/PostOfficeDaemon/CachedWatchdog.cpp`, `CachedWatchdog.h`, `PingGenerator.cpp`, `PingGenerator.h`, `PostContext.cpp`, `PostContext.h`
- `src/Server/Economy/PostOfficeDaemon/ManagementSessionHandler.cpp`, `ManagementSessionHandler.h`, `ManagementPacketHandler.cpp`, `ManagementPacketHandler.h`
- `src/Server/Economy/PostOfficeDaemon/AgentChannel.cpp`, `AgentChannel.h`, `AgentPacketHandler.cpp`, `AgentPacketHandler.h`, `WorldChannel.cpp`, `WorldChannel.h`,
  `WorldPacketHandler.cpp`, `WorldPacketHandler.h`, `PostOfficePacketServerSideHandlerList.cpp`, `PostOfficeServicePacketServerSideHandlerList.cpp`,
  `PostOfficeManagementPacketHandlerList.cpp`, `CacheEconomyPacketHandler.cpp`, `CacheEconomyPacketHandler.h`, `CacheEconomyClientSideHandlerList.cpp`, `LinkStubs.cpp`
- `Docs/Plan/handoffs/lift-parity-pod-5b.md`

## Done when
- Each named function is MATCH, or the handoff gives its cause.
- No exe loses a MATCH function (LobbyDaemon included).
- `tools/gate.sh` and `tools/parity.sh` pass.
