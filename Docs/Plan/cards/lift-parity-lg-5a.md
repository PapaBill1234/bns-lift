# lift-parity-lg-5a: LobbyGate: LobbyD channel and packet handlers

Repo: bns-lift (PUBLIC). Never commit binaries, PDBs, IDA databases or abuse notes. IDA only when the pseudocode, the PDB line map and funcdiff are not enough (`<work-root>/ida/lift/LobbyGate/LobbyGate.exe`). Close the database when you are done.

## Goal
The LobbyGate handler and LobbyD channel DIFF functions are MATCH, or the handoff gives the cause of each. LobbyGate moves toward 95 % (703 MATCH).

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
- Lessons for this card: A23 (PacketHandler form), A2 (block order), A17 (error blocks, `AutoCS` scope), A19 (separate stores), A26 (read globals again at each use), A27 (single-expression `::new`), A8 (refs one to one), A29 (PDB line maps), A31 (log-macro arguments). Fold of lift-parity-lg-4 (never built).
- Estimate (review-4 section 6): LG +10.
- Stop rule: stop a function after 3 tries with no score gain. Write it in the handoff. Do not try the stop list (lessons D) without a new idea.
- Named functions (exe, score, signals c=calls r=refs k=consts):
- `LobbyDPacketHandler.cpp`: `HandleLobbyLobbyGate_InitSessionWithLobbyTokenOk` 76.7 (c83 r81 k67), `_InitSessionWithNPTokenOk` 77.4 (c86 r79 k67),
  `_HelloOk` 87.3 (c92 r78 k92), `_InitSessionWithNPTokenFail` 87.8, `_StartSessionWithLobbyTokenOk` 88.7, `_StartSessionWithNPTokenOk` 89.5,
  `_StartSessionWithLobbyTokenFail` 94.3, `_StartSessionWithNPTokenFail` 94.8, `_InitSessionWithLobbyTokenFail` 96.2, `_CloseSessionNotify` 96.8,
  `_GetEnterWorldTokenOk` 98.1, `_KickNotify` 99.4 (`_instance` reload, lessons D).
- `LobbyGatePacketHandler.cpp`: `HandleLobbyGate_GetPcCafeMileageFeverTimeScheduleListReq` 85.8 (c83 r80), `_GetWorldInfoListReq` 92.5 (c83),
  `_HelloReq` 93.3 (c91 k89), `_ContentsRuleListReq` 97.0 (c91), `_BypassPacket` 98.0 (c94).
- `LobbyDChannel.cpp`: `LobbyD::Hello` 93.5 (c95 k86), `LobbyD::hello` 97.0 (r91), `LobbyDSessionHandler::OnConnect` 94.4 (k83), `OnClose` 95.2 (k86).
- Group the 12 `HandleLobbyLobbyGate_*` handlers: Ok handlers, Fail handlers, notify handlers. Apply one form to a group and measure the group.
- The `Ok` handlers with refs 78 to 81 likely have another inline choice of the `Client::Send*` calls or another ref order. Check the PDB line map first.
- `LobbyD::Hello` uses `PipeConsole::addNode` (`noinline` must stay, lessons B console-4).
## Tasks
1. Run `tools/gate.sh` and `tools/parity.sh`. List the DIFF functions of your scope with score and signal.
2. Work in groups of functions with the same form: run `funcdiff.py --show`, read the pseudocode and the PDB line map, change the source, build, measure again.
3. Keep a change only if the MATCH count goes up and no exe loses a MATCH function. Undo a change that does not help.
4. Write each fix pattern that worked and each that did not work in the handoff, section `## Lessons`, with tables "worked" and "failed"
   (function, before, after, count). Do not edit `Docs/Parity/lessons.md`: the round-5 cards run in parallel, and the review merges the handoff lessons into A and B.
5. For each DIFF function of your scope that you cannot fix, write one line in the handoff: function, signal, cause, why you stopped.
   Write the MATCH count per exe before and after, and `Turns: <n>`, in the handoff.

## Files
- `src/Server/LobbyGate/LobbyDPacketHandler.cpp`, `LobbyDPacketHandler.h`
- `src/Server/LobbyGate/LobbyGatePacketHandler.cpp`, `LobbyGatePacketHandler.h`
- `src/Server/LobbyGate/LobbyDChannel.cpp`, `LobbyDChannel.h`
- `Docs/Plan/handoffs/lift-parity-lg-5a.md`

## Done when
- Each named function is MATCH, or the handoff gives its cause.
- No exe loses a MATCH function (LobbyDaemon included).
- `tools/gate.sh` and `tools/parity.sh` pass.
