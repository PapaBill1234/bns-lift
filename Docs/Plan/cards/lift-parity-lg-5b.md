# lift-parity-lg-5b: LobbyGate: daemon, Client, config modules

Repo: bns-lift (PUBLIC). Never commit binaries, PDBs, IDA databases or abuse notes. IDA only when the pseudocode, the PDB line map and funcdiff are not enough (`<work-root>/ida/lift/LobbyGate/LobbyGate.exe`). Close the database when you are done.

## Goal
The LobbyGate daemon, Client and config DIFF functions are MATCH, or the handoff gives the cause of each. LobbyGate moves toward 95 % (703 MATCH).

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
- Lessons for this card: A14 (EH state -2 in `wmain`, `::new`), A2 (block order), A4 (`noinline`), A6 (path literal), A10 (forceinline helpers), A17 (error tails), A19 (separate stores), A21 and A29 (PDB facts, line maps), A22 (per-exe form). Fold of lift-parity-lg-4 and the LG part of lift-parity-ehstate-4 (never built).
- Estimate (review-4 section 6): LG +10.
- Stop rule: stop a function after 3 tries with no score gain. Write it in the handoff. Do not try the stop list (lessons D) without a new idea.
- Named functions (exe, score, signals c=calls r=refs k=consts):
- `LobbyGate.cpp`: `wmain` 66.7 (k0; EH state -2, A14), `LobbyGate::reload` 87.1 (c73), `LobbyGate::initialize` 91.5 (c89 r94 k91),
  `LobbyGate::PrintDependency` 91.7 (k75), `LobbyGate::FailedEventObjectHandler` 93.3 (c80), `LobbyGate::AddJobTimer` 96.3 (r89),
  `LobbyGateReloadInvalidRestoreTimer::restoreInvalid` 93.3 (r80), `ClientSessionTimerJob::HandleEvent` 96.8, `GateKeyManager::MakeGateKey` 94.3 (c89 r94; not tried).
- `Client.cpp`: `Client::SendGetCharacterInfoListOk` 98.3, `SendListLobbyServiceItemInfoOk` 98.9, `SendTakeGoodsOk` 98.9 (A19; positive form failed, B),
  `ClientManager::BroadcastAnnounceNotify` 97.8 (c93; branch swap failed, B), `ClientManager::Finalize` 95.2 (k86), `ClientSessionHandler::OnClose` 97.7.
- `ContentsRuleConfigDefinition.cpp`: `ContentsRuleConfig::UpdateAllVariable` 81.8 (r73 k73), `MakeListPacket` 86.9 (k64), `CheckMinMaxBoundary` 93.3 (r80),
  `LoadContentsRuleConfig` 93.6 (c90 r91), `Dump` 99.2 (r98). Check the path literals (A6) first.
- `PcCafeMileageFeverTimeScheduleList.cpp`: `PcCafeMileageFeverTimeScheduleList::Set` 98.2 (k95).
- Miss `wmain$dtor$0` (12 bytes): the original `wmain` has an unwind funclet for the local daemon object; ours has none. Fix it together with `wmain` (A14).
  The other LG misses belong to lift-parity-shared-5. List: `funcdiff.py LobbyGate --build build-vs2010 --only`.
- `ContentsRuleConfigDefinition` has a copy in `src/Server/LobbyDaemon/`. Do not change that copy.
## Tasks
1. Run `tools/gate.sh` and `tools/parity.sh`. List the DIFF functions of your scope with score and signal.
2. Work in groups of functions with the same form: run `funcdiff.py --show`, read the pseudocode and the PDB line map, change the source, build, measure again.
3. Keep a change only if the MATCH count goes up and no exe loses a MATCH function. Undo a change that does not help.
4. Write each fix pattern that worked and each that did not work in the handoff, section `## Lessons`, with tables "worked" and "failed"
   (function, before, after, count). Do not edit `Docs/Parity/lessons.md`: the round-5 cards run in parallel, and the review merges the handoff lessons into A and B.
5. For each DIFF function of your scope that you cannot fix, write one line in the handoff: function, signal, cause, why you stopped.
   Write the MATCH count per exe before and after, and `Turns: <n>`, in the handoff.

## Files
- `src/Server/LobbyGate/LobbyGate.cpp`, `LobbyGate.h`
- `src/Server/LobbyGate/Client.cpp`, `Client.h`
- `src/Server/LobbyGate/ContentsRuleConfigDefinition.cpp`, `ContentsRuleConfigDefinition.h`
- `src/Server/LobbyGate/PcCafeMileageFeverTimeScheduleList.cpp`, `.h`
- `src/Server/LobbyGate/LobbyGateConfig.cpp`, `LobbyGatePredefine.cpp`, `LobbyGatePredefine.h`, `WorldListManager.cpp`, `WorldListManager.h`, `LinkStubs.cpp`
- `Docs/Plan/handoffs/lift-parity-lg-5b.md`

## Done when
- Each named function is MATCH, or the handoff gives its cause.
- No exe loses a MATCH function (LobbyDaemon included).
- `tools/gate.sh` and `tools/parity.sh` pass.
