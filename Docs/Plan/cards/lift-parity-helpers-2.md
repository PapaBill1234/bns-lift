# lift-parity-helpers-2: lift helpers and handler form in LobbyGate and PostOfficeDaemon

Repo: bns-lift (PRIVATE). IDA only when the pseudocode and funcdiff are not enough (`<work-root>/ida/lift/PostOfficeDaemon/PostOfficeDaemon.exe`).

## Goal
The lift helpers that the original inlines are inlined in our exe too. The handlers of LobbyGate and PostOfficeDaemon have the same calls and refs as the original.

## Facts
- Read `Docs/Parity/README.md` first. It has the goal, the parity definition, the commands and the rules.
- Read `Docs/Parity/triage.md`, `Docs/Parity/lessons.md` (patterns A12, A15) and `Docs/Parity/review-1.md` (section 5).
- The runner gate runs `tools/gate.sh` and then `tools/parity.sh`. The gate fails if an exe loses a MATCH function.
- Run `tools/gate.sh` and then `tools/parity.sh` yourself before you stop. One parity run takes about 2 to 10 minutes.
- Pseudocode of the original exes: `~/.cache/bns-lift/hr/<EXE>/` for CacheGate, LobbyGate, SmartCouponDaemon and PostOfficeDaemon.
- Scope (cause classes "Ours calls more" 19 exe-only, part of "Other callee" and "Call order or count"):
  - LG `LobbyDPacketHandler.cpp`: 6 handlers, 23 refs less in ours. LG `Client.cpp`: 7 functions.
  - POD `CacheEconomyPacketHandler.cpp`: 13 handlers, 44 refs less in ours. POD `PostOfficeDB` Load* functions.
- Pattern A15: a helper as `static __forceinline`, crash block last, `ch->GetId()` in each log call. Mark each helper `// LIFT:`.
- Pattern A12: one full error block per failed call, one shared cleanup tail when the original has one.
- Open (lessons D): merged `Log::Write` tails in `Client::Send*Ok`; `_instance` reload in LG `KickNotify`, `CloseSessionNotify`.

## Tasks
1. Run `tools/gate.sh` and `tools/parity.sh`. List the DIFF functions of your scope with `funcdiff.py --show`.
2. Work in groups of functions with the same helper. For each group: inline the helper or change its form, build, measure again.
3. Keep a change only if the MATCH count goes up and no exe loses a MATCH function. Undo a change that does not help.
4. Write each fix pattern that worked in `Docs/Parity/lessons.md`. Also write the patterns that did not work.
5. For each DIFF function of your scope that you cannot fix, write one line in the handoff: function, signal, cause, why you stopped. Write `Turns: <n>` in the handoff.

## Files
- `src/Server/LobbyGate/`
- `src/Server/Economy/PostOfficeDaemon/`
- `src/Server/BloodLib/`
- `src/Server/Shared/`
- `src/Server/Economy/Shared/`
- `include/`
- `CMakeLists.txt`
- `Docs/Parity/`
- `Docs/Plan/handoffs/lift-parity-helpers-2.md`

## Done when
- Each lift helper of the scope is inlined as in the original, or the handoff gives the cause of each DIFF function that is left.
- `tools/parity.sh` passes.
