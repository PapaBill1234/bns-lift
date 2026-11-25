# lift-parity-crypto-4: crypto DIFFs in the lifted crypto library

Repo: bns-lift (PUBLIC). Never commit binaries, PDBs, IDA databases or abuse notes. IDA only when the pseudocode and funcdiff are not enough (`<work-root>/ida/lift/LobbyGate/LobbyGate.exe`).

## Goal
The shared crypto functions and the LG crypto functions are MATCH, or the handoff gives the cause of each.

## Facts
- Read `Docs/Parity/README.md` first. It has the goal, the parity definition, the commands and the rules.
- Read `Docs/Parity/triage.md`, `Docs/Parity/lessons.md` and `Docs/Parity/review-3.md` (section 5). Read `Docs/Parity/rules-proposal.md` section 5.
- The runner gate runs `tools/gate.sh` and then `tools/parity.sh`. The gate fails if an exe loses a MATCH function.
- Run `tools/gate.sh` and then `tools/parity.sh` yourself before you stop. One parity run takes about 2 to 10 minutes.
- Pseudocode of the original exes: `~/.cache/bns-lift/hr/<EXE>/` for CacheGate, LobbyGate, SmartCouponDaemon and PostOfficeDaemon.
- Parity at review 3: CG 448/491 (91.2 %), LG 627/739 (84.8 %), SCD 582/669 (87.0 %), POD 665/759 (87.6 %), shared 490/549 (89.3 %).
- Before a source change, read the PDB facts of the function (lessons A21). On a `tls:` or vtable-name DIFF, check the tool output first (lessons A1).
- Lessons for this card: A3 (closed-lib callers + `/INCLUDE`), A9 (crypto forms), A21 (PDB facts first), A4 (noinline), A20 (`inline_depth(0)`), B (crypto failures), D (`aes128Table` stop), F "Manual parity for arithmetic, startup, and cleanup", F "Public names of folded virtual tables".
- Estimate (review-3 section 6): LG +12, SCD +5, POD +5.
- Named functions (exe, score, signal):
- Shared (LG, SCD, POD): `BigInteger::Mul` (consts 0x1000/0xffffffe0, `_alloca`), `mul` x2, `sub`, `Sqr` (orig calls more), `Divide` 76.7,
  `InvMod`, `invMod` (ours inlines `LeftShift`, `add`, `sub`, `RightShift`), `expMod` (ours calls more), `OaepEncoder::Setup`/`encode`/`decode`,
  `Rsa::decrypt`, `RsaPublic::Setup`, `RsaPublic::~RsaPublic` (orig refs `??_7Ripemd128` and `??_7RsaPublic`; ours `??_7Rsa`).
- LG only: `Crypto::Create` 34.0, `Crypto::InstanceSize` 44.4, `Session::allocateCrypt` 67.4, `Dh::*`, `RsaPrivate::*`, `BigInteger::IsPrime` 82.2,
  `isPrimeMR` 88.4, `Session::completeHandshake` 55.6, `BroadcastCrypt`.
- "Ours inlines" and "orig calls more": try `#pragma inline_depth(0)` in the caller first (A20). Do not put a global `noinline` on a shared callee.
- `RsaPublic::~RsaPublic`: check the vtable public names with fix 10 first (A1, A21). It can be a tool cause.
- Stop list: `aes128Table*` x4 (lessons D).
- Stop rule: stop a function after 3 tries with no score gain. Write it in the handoff. Do not try the functions of the stop list (lessons D) without a new idea.

## Tasks
1. Run `tools/gate.sh`, `tools/parity.sh` and `tools/parity_shared.py --list`. List the DIFF functions of your scope.
2. Work in groups of functions with the same form: run `funcdiff.py --show`, compare with the pseudocode, change the source, build, measure again.
3. Keep a change only if the MATCH count goes up and no exe loses a MATCH function. Undo a change that does not help.
4. Write each fix pattern that worked and each that did not work in `Docs/Parity/lessons.md` (sections A and B, with the count).
5. For each DIFF function of your scope that you cannot fix, write one line in the handoff: function, signal, cause, why you stopped. Write `Turns: <n>` in the handoff.

## Files
- `src/Security/`
- `src/Server/BloodLib/source/Security.cpp`
- `src/Server/BloodLib/source/Session.cpp` (only `allocateCrypt`, `completeHandshake`)
- `tools/vs2010/build.sh`
- `include/`
- `Docs/Parity/`
- `Docs/Plan/handoffs/lift-parity-crypto-4.md`

## Done when
- Each named function is MATCH, or the handoff gives its cause.
- No exe loses a MATCH function.
- `tools/parity.sh` passes.
