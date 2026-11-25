# lift-parity-packet-4: PacketBuffer, FragmentPacket and ToPacket

Repo: bns-lift (PUBLIC). Never commit binaries, PDBs, IDA databases or abuse notes. IDA only when the pseudocode and funcdiff are not enough (`<work-root>/ida/lift/LobbyGate/LobbyGate.exe`).

## Goal
The DIFF functions of the packet files are MATCH, or the handoff gives the cause of each.

## Facts
- Read `Docs/Parity/README.md` first. It has the goal, the parity definition, the commands and the rules.
- Read `Docs/Parity/triage.md`, `Docs/Parity/lessons.md` and `Docs/Parity/review-3.md` (section 5). Read `Docs/Parity/rules-proposal.md` section 5.
- The runner gate runs `tools/gate.sh` and then `tools/parity.sh`. The gate fails if an exe loses a MATCH function.
- Run `tools/gate.sh` and then `tools/parity.sh` yourself before you stop. One parity run takes about 2 to 10 minutes.
- Pseudocode of the original exes: `~/.cache/bns-lift/hr/<EXE>/` for CacheGate, LobbyGate, SmartCouponDaemon and PostOfficeDaemon.
- Parity at review 3: CG 448/491 (91.2 %), LG 627/739 (84.8 %), SCD 582/669 (87.0 %), POD 665/759 (87.6 %), shared 490/549 (89.3 %).
- Before a source change, read the PDB facts of the function (lessons A21). On a `tls:` or vtable-name DIFF, check the tool output first (lessons A1).
- Lessons for this card: A10 (forceinline helpers), A11 (loop forms), A16 (allocation), A23 (PacketHandler form), A2 (block/statement order), B (`Compose` case P).
- Estimate (review-3 section 6): CG +2, LG +4, SCD +2, POD +2.
- Named functions (exe, score, signal):
- `PacketBuffer::Compose` x4 (case P: `memcpy` tail merge, 96.3 -> 93.0 failed), `PacketBuffer::Decompose` x4, `CheckCompose` (LG, POD).
- `RepeatPacketComposer::PushRepeatCount` (LG, POD), `FragmentPacketConcatenater::Add` (LG, POD).
- LG: `Packet::Copy`, `PacketConcatenateBuffer::Decompose` 95.2, `ClientPacketBufferHandler::ToPacket` 85.2, `FragmentPacket::StartRepeat`.
- POD: the pool index in the inlined `Packet::Allocate` (orig 0x28, ours 0x90).
- `FragmentPacketConcatenater::Clone` belongs to ehstate-4. Do not change it.
- Stop rule: stop a function after 3 tries with no score gain. Write it in the handoff. Do not try the functions of the stop list (lessons D) without a new idea.

## Tasks
1. Run `tools/gate.sh`, `tools/parity.sh` and `tools/parity_shared.py --list`. List the DIFF functions of your scope.
2. Work in groups of functions with the same form: run `funcdiff.py --show`, compare with the pseudocode, change the source, build, measure again.
3. Keep a change only if the MATCH count goes up and no exe loses a MATCH function. Undo a change that does not help.
4. Write each fix pattern that worked and each that did not work in `Docs/Parity/lessons.md` (sections A and B, with the count).
5. For each DIFF function of your scope that you cannot fix, write one line in the handoff: function, signal, cause, why you stopped. Write `Turns: <n>` in the handoff.

## Files
- `src/Server/BloodLib/source/PacketBuffer.cpp`
- `src/Server/BloodLib/source/Packet.cpp`
- `src/Server/BloodLib/source/PacketBufferHandler.cpp`
- `src/Server/BloodLib/source/PacketUtil.cpp`
- `src/Server/Packet/`
- `src/Server/BloodLib/include/`
- `Docs/Parity/`
- `Docs/Plan/handoffs/lift-parity-packet-4.md`

## Done when
- Each named function is MATCH, or the handoff gives its cause.
- No exe loses a MATCH function.
- `tools/parity.sh` passes.
