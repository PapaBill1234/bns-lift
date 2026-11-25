# lift-smartcoupondaemon-3: SmartCouponDaemon lift: RSA crypto (common), NP channel, object pool

Repo: bns-lift (PRIVATE). IDA database: `<work-root>/ida/lift/SmartCouponDaemon/SmartCouponDaemon.exe`. PDB: `<work-root>/Service_348_8349/Service/SmartCouponDaemon/bin/SmartCouponDaemon.pdb`.
Read `Docs/Plan/plan.md` "Lift method" first. Read the handoffs of the earlier lift cards for the state of `src/common/`.

## Modules (one `.cpp` + `.h` per PDB module)
Function counts are PDB symbol counts. They include EH funclets and scalar deleting destructors.
- BloodCrypto, in `src/common/` (lift these first):
  CryptoKey (3), rsa (18), BigInteger (5), NumberTheory (23), biArithmetic (17), biMontgomery (2),
  biSqr (1), biMultiplication (2), oaep_encoder (9), mgf (1), ripemd128 (4) (85)
- Server, in `src/SmartCouponDaemon/`:
  ObjectPool (36), NPChannel2 (63), NPServiceChannel (20), NPMessageHandler (1) (120)
- About 205 functions.

## Notes
- The PDB has no function symbols for BloodCert, BloodPacketCrypt, zlib (deflate, trees, adler32, crc32, zutil), dh, base64, CryptoMode and IdleWatcher. Do not lift them. If a call needs one of them, write it in the handoff with the address.
- `include/pdb/` has only `CacheGate/types.h`. Generate `include/pdb/SmartCouponDaemon/types.h` with `tools/pdb2h.py` (see the `lift-1` handoff) before the server modules.
- Write the SmartCouponDaemon RVA as `// 0x<rva>`.

## Tasks
1. List the functions of each module from the PDB (`llvm-pdbutil dump -symbols`, section of the module) or from IDA.
2. Decompile them in batches to `.scratch/`. Lift them to C++ with the PDB types.
3. Add the crypto files to `lift_common`. Add a static library `lift_smartcoupondaemon` for the server files (the exe target comes in card 4).
4. Run `tools/gate.sh` after each module.

## Files
- `src/common/`
- `src/SmartCouponDaemon/`
- `include/pdb/`
- `include/vs2010/`
- `CMakeLists.txt`

## Done when
- All functions of the modules are in C++, or listed in the handoff as Not done with the address.
- `tools/gate.sh` prints `gate ok`.
