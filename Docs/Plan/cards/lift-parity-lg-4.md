# lift-parity-lg-4: LobbyGate handlers and LobbyGate modules

Repo: bns-lift (PUBLIC). Never commit binaries, PDBs, IDA databases or abuse notes. IDA only when the pseudocode and funcdiff are not enough (`/home/ubuntu/Documents/Codex/private-project/ida/lift/LobbyGate/LobbyGate.exe`).

## Goal
LobbyGate reaches 90 % (666 MATCH), or the handoff gives the cause of each DIFF function that is left.

## Facts
- Read `Docs/Parity/README.md` first. It has the goal, the parity definition, the commands and the rules.
- Read `Docs/Parity/triage.md`, `Docs/Parity/lessons.md` and `Docs/Parity/review-3.md` (section 5). Read `Docs/Parity/rules-proposal.md` section 5.
- The runner gate runs `tools/gate.sh` and then `tools/parity.sh`. The gate fails if an exe loses a MATCH function.
- Run `tools/gate.sh` and then `tools/parity.sh` yourself before you stop. One parity run takes about 2 to 10 minutes.
- Pseudocode of the original exes: `~/.cache/bns-lift/hr/<EXE>/` for CacheGate, LobbyGate, SmartCouponDaemon and PostOfficeDaemon.
- Parity at review 3: CG 448/491 (91.2 %), LG 627/739 (84.8 %), SCD 582/669 (87.0 %), POD 665/759 (87.6 %), shared 490/549 (89.3 %).
- Before a source change, read the PDB facts of the function (lessons A21). On a `tls:` or vtable-name DIFF, check the tool output first (lessons A1).
- Lessons for this card: A23 (PacketHandler form), A19 (separate stores), A10 (forceinline helpers), A6 (path literal), A17 (error blocks / AutoCS scope), A2 (block/statement order), A14 (`::new`).
- Estimate (review-3 section 6): LG +15.
- Named functions (exe, score, signal):
- `HandleLobbyLobbyGate_*` (about 12), `HandleLobbyGate_*` (5), `Client::Send*Ok` (3; separate stores, A19).
- `ContentsRuleConfig` (4 path literals, A6).
- `LobbyGate::reload`/`initialize`/`AddJobTimer`/`PrintDependency`/`FailedEventObjectHandler` (do not change `wmain`; ehstate-4 owns it).
- `LobbyD::Hello`/`hello`, `LobbyDSessionHandler::OnConnect`/`OnClose`, `ClientSessionHandler::OnClose`, `ClientSessionTimerJob::HandleEvent`.
- `GateKeyManager::MakeGateKey` 94.3 (not tried in round 3), `ClientManager::BroadcastAnnounceNotify` 97.8 (branch swap failed, B),
  `AlertSender::init`, `restoreInvalid`.
- Known fix patterns: apply A23 to each handler as one group. Measure each group.
- Stop rule: stop a function after 3 tries with no score gain. Write it in the handoff. Do not try the functions of the stop list (lessons D) without a new idea.

## Tasks
1. Run `tools/gate.sh`, `tools/parity.sh` and `tools/parity_shared.py --list`. List the DIFF functions of your scope.
2. Work in groups of functions with the same form: run `funcdiff.py --show`, compare with the pseudocode, change the source, build, measure again.
3. Keep a change only if the MATCH count goes up and no exe loses a MATCH function. Undo a change that does not help.
4. Write each fix pattern that worked and each that did not work in `Docs/Parity/lessons.md` (sections A and B, with the count).
5. For each DIFF function of your scope that you cannot fix, write one line in the handoff: function, signal, cause, why you stopped. Write `Turns: <n>` in the handoff.

## Files
- `src/Server/LobbyGate/`
- `Docs/Parity/`
- `Docs/Plan/handoffs/lift-parity-lg-4.md`

## Done when
- Each named function is MATCH, or the handoff gives its cause.
- No exe loses a MATCH function.
- `tools/parity.sh` passes.
