# lift-parity-cgscd-5: CacheGate and SmartCouponDaemon to 95 %

Repo: bns-lift (PUBLIC). Never commit binaries, PDBs, IDA databases or abuse notes. IDA only when the pseudocode, the PDB line map and funcdiff are not enough (`<work-root>/ida/lift/CacheGate/CacheGate.exe` and `<work-root>/ida/lift/SmartCouponDaemon/SmartCouponDaemon.exe`). Close the database when you are done.

## Goal
CacheGate reaches 95 % (467 MATCH) and SmartCouponDaemon reaches 95 % (636 MATCH), or the handoff gives the cause of each DIFF function that is left.

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
- Lessons for this card: A2 (block order), A11 (loop forms), A12 (member types), A14 (EH state -2 in `wmain`, `::new`), A17 (error tails), A18 (compiler dtors), A23 (PacketHandler form), A26, A29, A31, A32, B (`CacheD::Verify`, `LoadCachedListConfigFile`, scd-4 rows), F "Manual server parity checks". Fold of lift-parity-cg-4 and the CG/SCD part of lift-parity-ehstate-4 (never built).
- Estimate (review-4 section 6): CG +8, SCD +5.
- Stop rule: stop a function after 3 tries with no score gain. Write it in the handoff. Do not try the stop list (lessons D) without a new idea.
- Named functions (exe, score, signals c=calls r=refs k=consts):
- CG `CacheD.cpp`: `CacheDList::clear` 61.1 (c67 r50 k67), `CacheDList::RemoveSessionAll` 85.7 (c91 r77), `CacheDList::Initialize` 93.3 (k80; placement new failed, B),
  `CacheDList::MakeSessionAll` 96.3 (c89; merged `Log::Write` tails, D), `CacheDList::LoadCachedListConfigFile` 98.5, `CacheD::Verify` 91.7 (c75; mismatch-first failed, B),
  `CacheD::Initialize` 93.3 (k80).
- CG `CacheDChannel.cpp`: `CacheDChannel::onClose` 97.4 (k92), `ClientSideDaemonChannel::~ClientSideDaemonChannel` 88.8 (A18).
- CG `CacheGateSessionHandler.cpp`: `HandleCacheGateHello` 87.2 (c88 k76; else-if chain failed, B), `HandleCacheGateHelloFail` 97.4, `HandleCacheGateFragmentRelay` 81.4 (c73 r74),
  `HandleCacheGateRelay` 98.4 (k95; 3 forms in round 3, 93.3 then, now 98.4).
- CG `ClientManager.cpp`: `ClientManager::~ClientManager` 88.6 (c80 r86; A18). CG `CacheGate.cpp`: `wmain` 61.9 (r86 k0; EH state -2, A14).
- SCD `SmartCouponDaemon.cpp`: `wmain` 66.7 (k0; EH state -2, A14), `ObjPool::ObjPool` 99.0 and `ObjPool::Finalize` 99.0 (r97).
- SCD `NPServiceChannel.cpp`: `NPServiceChannelManager::HandleMessage` 92.3 (k77; EH state -2), `NPServiceChannel::SendRequestEventNoti` 95.2 (`<indirect>` call order before `sprintf_s`).
- SCD: `NPChannel::SendMsg` 90.1 (the original inlines a `Packet` assert), `HandleSmartCoupon_HelloReq` 96.1, `HandleSmartCoupon_GameEventByCharacterReq` 99.1 (k97),
  `RetryCouponPublicationEvent::HandleEvent` 97.5, `ManagerChannel::SendRetryCouponPublicationOk` 96.3 (register allocation, 1 try).
- Stop list (do not try): CG `DaemonConfig::Dump`, SCD `SmartCouponDaemon::initialize` (patched original), `EventNotiJob::finalize`, `JobManager::Execute`/`ExecuteW`,
  `GameEventConfig::SetupGameEventListFromXml` 99.7 (4 tries), `HandleSmartCoupon_GameEventByAccountReq` (3 tries) unless you have a new idea.
- Miss `wmain$dtor$0` in CG and SCD (12 bytes): the original `wmain` has an unwind funclet for the local daemon object; ours has none.
  Fix it together with `wmain` (A14). The other misses belong to lift-parity-shared-5. List: `funcdiff.py <EXE> --build build-vs2010 --only`.
- The two exes have no common files. Work on CG first (gap 11), then SCD (gap 6).
## Tasks
1. Run `tools/gate.sh` and `tools/parity.sh`. List the DIFF functions of your scope with score and signal.
2. Work in groups of functions with the same form: run `funcdiff.py --show`, read the pseudocode and the PDB line map, change the source, build, measure again.
3. Keep a change only if the MATCH count goes up and no exe loses a MATCH function. Undo a change that does not help.
4. Write each fix pattern that worked and each that did not work in the handoff, section `## Lessons`, with tables "worked" and "failed"
   (function, before, after, count). Do not edit `Docs/Parity/lessons.md`: the round-5 cards run in parallel, and the review merges the handoff lessons into A and B.
5. For each DIFF function of your scope that you cannot fix, write one line in the handoff: function, signal, cause, why you stopped.
   Write the MATCH count per exe before and after, and `Turns: <n>`, in the handoff.

## Files
- `src/Server/Economy/CacheGate/`
- `src/Server/SmartCouponDaemon/`
- `Docs/Plan/handoffs/lift-parity-cgscd-5.md`

## Done when
- Each named function is MATCH, or the handoff gives its cause.
- No exe loses a MATCH function (LobbyDaemon included).
- `tools/gate.sh` and `tools/parity.sh` pass.
