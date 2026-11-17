# lift-parity-s2: parity of shared code: network, sessions, packets, buffers

Repo: bns-lift (PRIVATE). IDA only when the pseudocode and funcdiff are not enough (`/home/ubuntu/Documents/Codex/private-project/ida/lift/CacheGate/CacheGate.exe`).

## Goal
The shared network code compiles to the same code as the original in all 4 exes.

## Facts
- Read `Docs/Parity/README.md` first. It has the goal, the parity definition, the commands and the rules.
- Read `Docs/Parity/triage.md` and `Docs/Parity/lessons.md` if they exist.
- The runner gate runs `tools/gate.sh` and then `tools/parity.sh`. The gate fails if an exe loses a MATCH function.
- Run `tools/gate.sh` and then `tools/parity.sh` yourself before you stop. One parity run takes about 2 to 10 minutes.
- Pseudocode of the original exes: `~/.cache/bns-lift/hr/<EXE>/` for CacheGate, LobbyGate, SmartCouponDaemon and PostOfficeDaemon.
- Scope: `Network`, `Session`, `Connection`, `Channel`, `PortListener`, `Packet`, `PacketBuffer`, `SessionSendBuffer`, `FragmentPacketConcatenater`, and the free functions of these modules.
- Shared DIFF counts at the start: Session 20, Network 11, Packet 9, Channel 7, Connection 6, SessionSendBuffer 5, FragmentPacketConcatenater 5, PacketBuffer 4, PortListener 4.
- A fix here changes all 4 exes. Check all 4 in the `tools/parity.sh` output.

## Tasks
1. Run `tools/gate.sh` and `tools/parity.sh`. List the DIFF functions of your scope from `build-vs2010/<EXE>.funcdiff.json` and the miss list in `Docs/Parity/triage.md`.
2. Work in groups of functions with the same cause. For each group: run `funcdiff.py --show`, compare with the pseudocode, change the source, build, measure again.
3. Keep a change only if the MATCH count goes up and no exe loses a MATCH function. Undo a change that does not help.
4. Write each fix pattern that worked in `Docs/Parity/lessons.md`: the cause, the source change, one example function. Also write the patterns that did not work.
5. For each DIFF function that you cannot fix, write one line in the handoff: function, signal (calls, refs or consts), cause, why you stopped.

## Files
- `src/Server/BloodLib/`
- `src/Server/Shared/`
- `src/Server/Packet/`
- `src/Security/`
- `src/Server/Economy/Shared/`
- `include/`
- `CMakeLists.txt`
- `Docs/Parity/`
- `Docs/Plan/handoffs/lift-parity-s2.md`

## Done when
- Each function of the scope is MATCH, or the handoff gives its cause.
- `tools/parity.sh` passes and the MATCH count of each exe went up.
