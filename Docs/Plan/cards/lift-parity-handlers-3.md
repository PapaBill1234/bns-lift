# lift-parity-handlers-3: packet handler form in all 4 exes

Repo: bns-lift (PRIVATE). IDA only when the pseudocode and funcdiff are not enough (`/home/ubuntu/Documents/Codex/private-project/ida/lift/CacheGate/CacheGate.exe`).

## Goal
The packet handlers and the send functions get MATCH in each exe.

## Facts
- Read `Docs/Parity/README.md` first. It has the goal, the parity definition, the commands and the rules.
- Read `Docs/Parity/triage.md`, `Docs/Parity/lessons.md` and `Docs/Parity/review-2.md` (section 5).
- The runner gate runs `tools/gate.sh` and then `tools/parity.sh`. The gate fails if an exe loses a MATCH function.
- Run `tools/gate.sh` and then `tools/parity.sh` yourself before you stop. One parity run takes about 2 to 10 minutes.
- Pseudocode of the original exes: `~/.cache/bns-lift/hr/<EXE>/` for CacheGate, LobbyGate, SmartCouponDaemon and PostOfficeDaemon.
- Lessons that apply: A6, A12, A15 and the tail call pattern P31.
- Named functions:
  - LG `HandleLobbyLobbyGate_*` (12), `HandleLobbyGate_*` (5), `Client::Send*Ok` (3).
  - SCD `HandleSmartCoupon*` (6), `ManagerChannel::Send*` (2), `*Event::HandleEvent` (4).
  - POD `*SessionHandler::PacketHandler` (5), `HandlePostOffice*` (8), `HandleCacheGateRelay*` (3).
  - CG `HandleCacheGate*` (3).
- Work in groups by form (tail call, inline depth, local packet object, early return), not by exe.

## Tasks
1. Run `tools/gate.sh`, `tools/parity.sh` and `tools/parity_shared.py --list`. List the DIFF functions of your scope.
2. Work in groups of functions with the same form. For each group: run `funcdiff.py --show`, compare with the pseudocode, change the source, build, measure again.
3. Keep a change only if the MATCH count goes up and no exe loses a MATCH function. Undo a change that does not help.
4. Write each fix pattern that worked and each that did not work in `Docs/Parity/lessons.md`.
5. For each DIFF function of your scope that you cannot fix, write one line in the handoff: function, signal, cause, why you stopped. Write `Turns: <n>` in the handoff.

## Files
- `src/Server/`
- `include/`
- `Docs/Parity/`
- `Docs/Plan/handoffs/lift-parity-handlers-3.md`

## Done when
- Each named function is MATCH, or the handoff gives its cause.
- `tools/parity.sh` passes.
