# lift-parity-crypto-2: BloodCrypto compile flags, crypto misses and crypto consts

Repo: bns-lift (PRIVATE). IDA only when the pseudocode and funcdiff are not enough (`/home/ubuntu/Documents/Codex/private-project/ida/lift/LobbyGate/LobbyGate.exe`).

## Goal
The crypto code compiles to the same code as the original in each exe. The crypto misses and the crypto const DIFF go away.

## Facts
- Read `Docs/Parity/README.md` first. It has the goal, the parity definition, the commands and the rules.
- Read `Docs/Parity/triage.md`, `Docs/Parity/lessons.md` (section D) and `Docs/Parity/review-1.md` (section 5, "Crypto misses").
- The runner gate runs `tools/gate.sh` and then `tools/parity.sh`. The gate fails if an exe loses a MATCH function.
- Run `tools/gate.sh` and then `tools/parity.sh` yourself before you stop. One parity run takes about 2 to 10 minutes.
- Pseudocode of the original exes: `~/.cache/bns-lift/hr/<EXE>/` for CacheGate, LobbyGate, SmartCouponDaemon and PostOfficeDaemon.
- Misses: LG 60, SCD 39, POD 39: `BigInteger::*`, `Rsa::*`, `Oaep*`, DH, `i2os`, `os2i`, `MaskGenerator::generate`, `Ripemd128::Digest`, `Aes128::~Aes128`.
- The original pseudocode has no caller of `BigInteger::Divide` or `Rsa::*` outside the crypto modules. So the original keeps crypto functions that have no caller.
- Shared crypto DIFF with consts only: `Blowfish::Setup`, `Ctr::Encrypt`, `aes128Table*`, `encrypt`, `decrypt`, `Prng::setSeed`.
- Probable cause: the original BloodCrypto lib had other compile flags (no `/GL`, or no `/Gy`, or no `/OPT:REF` effect) ❓. Our flags are in `tools/vs2010/build.sh` (line 58: `/O2 /GL ...`).
- Find the flags: read the `S_ENVBLOCK` (command line) and `S_COMPILE3` records of the crypto modules in the original PDB (`tools/pdbq.py`). Compare with a module of BloodLib.
- The crypto source is in `src/Security/`.

## Tasks
1. Run `tools/gate.sh` and `tools/parity.sh`. List the crypto DIFF functions and misses from `build-vs2010/<EXE>.funcdiff.json`.
2. Find the compile and link flags of the original crypto modules. Write the proof in the handoff.
3. Give the crypto objects these flags in `tools/vs2010/build.sh` (per-lib flags). Build and measure again.
4. If the flags do not explain the misses: find why the original keeps the functions (references from data, exports, `/OPT:NOREF`). Try one cause at a time.
5. Keep a change only if the MATCH count goes up and no exe loses a MATCH function. Undo a change that does not help.
6. Write each fix pattern and each pattern that did not work in `Docs/Parity/lessons.md`. Write `Turns: <n>` in the handoff.

## Files
- `src/Security/`
- `tools/vs2010/build.sh`
- `CMakeLists.txt`
- `include/`
- `Docs/Parity/`
- `Docs/Plan/handoffs/lift-parity-crypto-2.md`

## Done when
- The crypto misses and crypto DIFF functions are MATCH, or the handoff gives the cause of each that is left.
- `tools/parity.sh` passes.
