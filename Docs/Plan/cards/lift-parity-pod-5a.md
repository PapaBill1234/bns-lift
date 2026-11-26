# lift-parity-pod-5a: PostOfficeDaemon: relay, CacheGate channel, DB

Repo: bns-lift (PUBLIC). Never commit binaries, PDBs, IDA databases or abuse notes. IDA only when the pseudocode, the PDB line map and funcdiff are not enough (`<work-root>/ida/lift/PostOfficeDaemon/PostOfficeDaemon.exe`). Close the database when you are done.

## Goal
The POD relay, CacheGate channel and DB DIFF functions are MATCH, or the handoff gives the cause of each. POD moves toward 95 % (722 MATCH).

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
- Lessons for this card: A23 (PacketHandler form), A2 (block order), A17 (error tails, one shared `statmentErrorLog` site), A11 (loop forms, do-while fetch), A26 (reload at each use), A27 (single-expression `::new`), A8, A29, B pod-4 and dbbind-3 rows.
- Estimate (review-4 section 6): POD +8.
- Stop rule: stop a function after 3 tries with no score gain. Write it in the handoff. Do not try the stop list (lessons D) without a new idea.
- Named functions (exe, score, signals c=calls r=refs k=consts):
- `CacheGateChannel.cpp`: `CacheGateChannel::combineFragmentRelayFormat` 53.9 (c57 r55 k50), `SendFragmentRelayRequest` 86.9 (c67), `SendRelayRequest` 94.1 (c82).
- `CacheGatePacketHandler.cpp`: `HandleCacheGateRelayFail` 82.7 and `HandleCacheGateRelayInvalid` 82.7 (c70 r88 k90; the original has 3 `ProcessRelayResponse` calls, not tried),
  `HandleCacheGateRelay` 92.8 (c88 k91), `HandleCacheGateFragmentRelay` 94.7 (c91 k93).
- Relay contexts: `RetrieveCharacterInfoRelayContext::ComposeResponsePacket` 90.5 (k71), `CheckPostCapacityRelayContext::ComposeResponsePacket` 90.5 (k71),
  `DeliverPostRelayContext::processRelayResponse` 96.5 (not examined), `PingRelayContext::processRelayResponse` 97.6 (failure-first failed, B),
  `RelayTimeoutChecker::checkRelayTimeout` 96.3 (k89), `PostDeliveryEvent::deliverPost` 85.4 (c71 r90).
- `PostOfficeDB.cpp`: `PostOfficeDB::RegisterPost` 84.0 (not examined), `LoadSinglePost` 88.4 and `LoadRetryReadySinglePost` 88.8 (one shared
  `statmentErrorLog` site; "Not initialized" log before the binds), `LoadPostList`/`LoadRetryReadyPostList` 99.1 (stop list; try only with a new idea).
- The CG card changes the CacheGate side of the same relay names. Change only the POD files.
- `HandleCacheGateRelay`/`FragmentRelay` exist in CG and POD with other source. Measure each exe.
## Tasks
1. Run `tools/gate.sh` and `tools/parity.sh`. List the DIFF functions of your scope with score and signal.
2. Work in groups of functions with the same form: run `funcdiff.py --show`, read the pseudocode and the PDB line map, change the source, build, measure again.
3. Keep a change only if the MATCH count goes up and no exe loses a MATCH function. Undo a change that does not help.
4. Write each fix pattern that worked and each that did not work in the handoff, section `## Lessons`, with tables "worked" and "failed"
   (function, before, after, count). Do not edit `Docs/Parity/lessons.md`: the round-5 cards run in parallel, and the review merges the handoff lessons into A and B.
5. For each DIFF function of your scope that you cannot fix, write one line in the handoff: function, signal, cause, why you stopped.
   Write the MATCH count per exe before and after, and `Turns: <n>`, in the handoff.

## Files
- `src/Server/Economy/PostOfficeDaemon/CacheGateChannel.cpp`, `CacheGateChannel.h`
- `src/Server/Economy/PostOfficeDaemon/CacheGatePacketHandler.cpp`, `CacheGatePacketHandler.h`, `CacheGateClientSideHandlerList.cpp`
- `src/Server/Economy/PostOfficeDaemon/CheckPostCapacityRelay.cpp`, `DeliverPostRelay.cpp`, `DeliverPostRelay.h`, `PingRelay.cpp`, `PingRelay.h`,
  `RetrieveCharacterInfoRelay.cpp`, `RelayContext.cpp`, `RelayContext.h`, `RelayTimeContext.cpp`, `RelayTimeContext.h`, `RelayTimeoutChecker.cpp`,
  `RelayTimeoutChecker.h`, `RelayTimeoutEvent.cpp`, `RelayTimeoutEvent.h`
- `src/Server/Economy/PostOfficeDaemon/PostDeliveryEvent.cpp`, `PostDeliveryEvent.h`, `PostOfficeDB.cpp`, `PostOfficeDB.h`
- `Docs/Plan/handoffs/lift-parity-pod-5a.md`

## Done when
- Each named function is MATCH, or the handoff gives its cause.
- No exe loses a MATCH function (LobbyDaemon included).
- `tools/gate.sh` and `tools/parity.sh` pass.
