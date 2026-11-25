# lift-parity-cryptolib-3: lift the callers in the closed crypto libraries

Repo: bns-lift (PRIVATE). IDA: `<work-root>/ida/lift/LobbyGate/LobbyGate.exe` (open only this copy).

## Goal
The crypto functions that the original links from `BloodPacketCrypt64.lib` and `BloodCert64.lib` are in our exes (LG, SCD, POD).

## Facts
- Read `Docs/Parity/README.md` first. It has the goal, the parity definition, the commands and the rules.
- Read `Docs/Parity/triage.md`, `Docs/Parity/lessons.md` and `Docs/Parity/review-2.md` (section 5).
- The runner gate runs `tools/gate.sh` and then `tools/parity.sh`. The gate fails if an exe loses a MATCH function.
- Run `tools/gate.sh` and then `tools/parity.sh` yourself before you stop. One parity run takes about 2 to 10 minutes.
- Pseudocode of the original exes: `~/.cache/bns-lift/hr/<EXE>/` for CacheGate, LobbyGate, SmartCouponDaemon and PostOfficeDaemon.
- Misses (orig-only): LG 72, SCD 47, POD 47. This is 9.7 % of LG. LG cannot get to 90 % without this card.
- Missing functions: `BigInteger::*` (26), `Dh::*` (10), `RsaPrivate::*`, `RsaPublic::*`, `Rsa::*`, `OaepEncoder::*`, `CryptoKey::*`,
  `Crypto::*`, `Prng::*`, `i2os`, `os2i`, `MaskGenerator::generate`, `Ripemd128`, `Ripemd160`, `Aes128::~Aes128`.
- The callers in the closed libraries are not in the PDB source: LG 0x14004cf70, 0x14004c5d0. Lift them from the disassembly.
  Use the PDB names. Mark names that are not in the PDB with `// ❓`.
- Replace the stubs `PacketCrypt::InstanceSize` (LG 0x4CC60) and `PacketCrypt::Create` (LG 0x4CCE0) in
  `src/Server/BloodLib/source/Session.cpp` (about line 941 and 949, `TODO(lift-lobbygate-4)`).
- Ours has LG `BroadcastPacketCrypt::*` (5, ONLY-OURS). The original has them in the closed library. Find the form that the original links.
- Never write keys, passwords or certificates. Write `keyhere`.
- Size is not measured. If the work needs more than 150 turns: finish the callers and `BigInteger`, then write the rest as a new card
  in the handoff (do not write the queue).

## Tasks
1. Run `tools/gate.sh`, `tools/parity.sh` and `tools/parity_shared.py --list`. List the misses of your scope.
2. In IDA, find the callers and the call graph of the missing functions. Decompile many functions in one call to a `.scratch/` file.
3. Lift the code into `src/Security/` (one `.cpp` per PDB module). Build, measure again.
4. Keep a change only if the MATCH count goes up and no exe loses a MATCH function.
5. Write each fix pattern that worked and each that did not work in `Docs/Parity/lessons.md`.
6. For each miss that is left, write one line in the handoff: function, signal, cause, why you stopped. Write `Turns: <n>` in the handoff.

## Files
- `src/Security/`
- `src/Server/BloodLib/`
- `tools/vs2010/build.sh`
- `include/`
- `CMakeLists.txt`
- `Docs/Parity/`
- `Docs/Plan/handoffs/lift-parity-cryptolib-3.md`

## Done when
- The crypto misses are MATCH or DIFF (not orig-only), or the handoff gives the cause of each miss that is left.
- `tools/parity.sh` passes.
