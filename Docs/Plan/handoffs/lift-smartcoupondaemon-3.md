# lift-smartcoupondaemon-3 handoff

## Done
- `src/common/BigInteger.h/.cpp` (7 functions), `biArithmetic.cpp` (11), `biMultiplication.cpp` (2),
  `biSqr.cpp` (1), `biMontgomery.cpp` (2). These are in `lift_common` and compile. 23 functions.
- `src/common/NumberTheory.cpp`: expMod 0x4AE30, invMod 0x49DB0, InvMod 0x48F10 are written.
  The file is NOT in `lift_common` yet. It is not compiled.
- `include/pdb/SmartCouponDaemon/types.h` (from `tools/pdb2h.py`).
- Crypto facts for the next card: `.scratch/facts-scd3.md`.

## Not done
- NumberTheory: other functions (23 in PDB, 3 written). Add the file to CMakeLists.txt.
- ripemd128: Digest 0x50D90 (BUG 0x50F4E), Size 0x48A10, GetType 0x1D7A0 ❓.
- mgf 0x51040; oaep_encoder (9); rsa (18; BUG len cap 0x46B20, BUG dead 512 0x46FE0); CryptoKey Initialize 0x465D0.
- Prng::Generate 0x4CBF0, Reseed ❓. `RSA = 65, // ❓` in Crypto.h.
- Server (all): ObjectPool (36), NPChannel2 (63), NPServiceChannel (20), NPMessageHandler (1).
  Static lib `lift_smartcoupondaemon` is not added.
- Calls into BloodCert, BloodPacketCrypt, zlib, dh, base64, CryptoMode, IdleWatcher are not listed yet
  (example: CertDec::Decrypt 0x42DDD -> BigInteger::Set).

## ❓
- Set(int,uchar const*,int) PDB signature vs 2-arg code. HashFunction base name. CryptoEncoder field names. Oaep+24 byte.
- BUG addresses not verified with dis: 0x4C82B, 0x4C88A, 0x4C4C0, 0x4C330, 0x4F5E0, 0x4F610, 0x4F6A0.

## Blocked
- None.

## Gate result
- `tools/gate.sh`: gate ok.
- Fix: the gate failed because this handoff file was missing. I wrote this file. No code change.
