# lift-parity-crypto-2 handoff

Turns: 74 (stage 1 = 25, stage 2 = 25, stage 3 = 22, stage 4 = 2).

## Done
- MATCH +5 in each exe, MATCH lost 0: CG 411/491, LG 517/739, SCD 493/669, POD 540/759.
- New MATCH (all 4 exes): `encrypt` 0x35fa0, `Ctr::Encrypt` 0x36a10, `Prng::setSeed` 0x35d60,
  `Prng::addEntropy` 0x35e10, `decrypt` 0x360a0.
- Files: `crypto/blowfish.cpp`, `crypto/mode/ctr.cpp`, `math/prng/prng.cpp`, `math/prng/prng.h`,
  `Docs/Parity/lessons.md` section D (fix patterns and failed tries).

## Task 2 proof (flags)
- No flag difference. The LG PDB `S_COMPILE3` of BloodLib `Port.obj` and of BloodCrypto `rsa.obj`,
  `BigInteger.obj` is the same: `ltcg | security checks | hot patchable`. LTCG objects have no `S_ENVBLOCK`.
- `tools/vs2010/build.sh` is not changed.

## Not done, with cause
- Misses LG 60, SCD 39, POD 39 (`BigInteger::*`, `Rsa::*`, `Oaep*`, DH, ...): the original links
  `Security\lib\BloodPacketCrypt64.lib` and `BloodCert64.lib`. These libs have no debug info (no `S_GPROC32`,
  no pseudocode). They call `Crypto::Create`, `Rsa::Rsa`, `Dh::Dh`, `RsaPrivate::~RsaPrivate`
  (LG 0x14004cf70, 0x14004c5d0). Ours has `PacketCrypt::Create` / `InstanceSize` as stubs. Fix: a new lift card
  for these 2 libs (outside the Files of this card). Review must queue it.
- `Blowfish::Setup` 0x361d0 (98.2): register allocation in the inlined `encrypt` (pbox kept in `rbp`).
  The layout fix (error 5 path last) is kept.
- `aes128TableEncrypt` 0x38790 / `aes128TableDecrypt` 0x38d10: orig uses the fst loop and loads the image
  base 3 times; the fst form gave no MATCH (reverted).
- `aes128TableSetupEncKey` 0x38370: orig unrolls the loop 5 times; ours does not.
- `aes128TableSetupDecKey` 0x385c0: not tried.

## ❓
- Register choice in aes128Table encrypt/decrypt. Rcon neighbour data order.

## Blocked
- None.

## Gate result
- `tools/gate.sh` ok, `tools/parity.sh` ok on the final source (stage 3). No source change after that run.
