# lift-parity-lg-1: parity of LobbyGate: the exe-only code

Repo: bns-lift (PRIVATE). IDA only when the pseudocode and funcdiff are not enough (`/home/ubuntu/Documents/Codex/private-project/ida/lift/LobbyGate/LobbyGate.exe`).

## Goal
The code of LobbyGate that is not shared compiles to the same code as the original. LobbyGate reaches 90 % parity.

## Facts
- Read `Docs/Parity/README.md` first. It has the goal, the parity definition, the commands and the rules.
- Read `Docs/Parity/triage.md` and `Docs/Parity/lessons.md` if they exist.
- The runner gate runs `tools/gate.sh` and then `tools/parity.sh`. The gate fails if an exe loses a MATCH function.
- Run `tools/gate.sh` and then `tools/parity.sh` yourself before you stop. One parity run takes about 2 to 10 minutes.
- Pseudocode of the original exes: `~/.cache/bns-lift/hr/<EXE>/` for CacheGate, LobbyGate, SmartCouponDaemon and PostOfficeDaemon.
- Scope: the DIFF functions and the misses of `LobbyGate` that are not in the shared code. At the start there were 118 DIFF functions of this kind.
- The exe-only code is in `src/Server/LobbyGate/`.
- Fix the shared code only if a cause in this exe is in the shared code. Then check all 4 exes.

## Tasks
1. Run `tools/gate.sh` and `tools/parity.sh`. List the DIFF functions of your scope from `build-vs2010/<EXE>.funcdiff.json` and the miss list in `Docs/Parity/triage.md`.
2. Work in groups of functions with the same cause. For each group: run `funcdiff.py --show`, compare with the pseudocode, change the source, build, measure again.
3. Keep a change only if the MATCH count goes up and no exe loses a MATCH function. Undo a change that does not help.
4. Write each fix pattern that worked in `Docs/Parity/lessons.md`: the cause, the source change, one example function. Also write the patterns that did not work.
5. For each DIFF function that you cannot fix, write one line in the handoff: function, signal (calls, refs or consts), cause, why you stopped.

## Files
- `src/Server/LobbyGate/`
- `src/Server/BloodLib/`
- `src/Server/Shared/`
- `src/Server/Packet/`
- `src/Security/`
- `src/Server/Economy/Shared/`
- `include/`
- `CMakeLists.txt`
- `Docs/Parity/`
- `Docs/Plan/handoffs/lift-parity-lg-1.md`

## Done when
- `LobbyGate` has 90 % parity or more, or the handoff gives the cause of each DIFF function and each miss that is left.
- `tools/parity.sh` passes.
