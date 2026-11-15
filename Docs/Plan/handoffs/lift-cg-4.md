# lift-cg-4: CacheGate crypto

## Done (8 modules, 39 functions)
- Crypto 2, aes128 7 (GetType 0xded0, BlockSize/KeySize 0x35ec0 are folds), aes128Table 7,
  aes128NI 3, blowfish 11, ctr 4, prng 3, ripemd160 2.
- All are in `src/common/` and in the `lift_common` target. Size and offset static_asserts pass.
- zstd is not lifted (by design). `vendor/zstd/README.md` gives the version, the URL and the
  download command. CMake builds `lift_zstd` from `vendor/zstd/src/` only if it exists.

## Not done
- None in scope. zstd modules (zstd_compress, zstd_fast, zstd_double_fast, zstd_lazy, zstd_opt,
  fse_compress) use upstream source.

## BUG marks
- Crypto::Destroy 0x35c1b (vtable slot 8), Ripemd160::Digest 0x3827e ('=' not '^='),
  Prng::Initialize 0x35ce0 (no malloc null check), Prng::addEntropy 0x35e10 (size ignored),
  Ctr::Encrypt 0x36a10 (*encCount not set), Blowfish and Aes128NI Encrypt/Decrypt (partial block).

## ❓
- Member names of the crypto classes, the Aes128 delegator struct and its members.
- Crypto::Type enumerator names (3 = AES128, 4 = BLOWFISH). Destroy types 65 and 81.
- Folded functions 0xded0 and 0x35ec0. The Prng TLS variable name `_Instance`.
- zstd version 1.3.5 is inferred from symbols. The binary has no version string.

## Blocked
- None.

## Toolchain
- `-maes` is set for `src/common/aes128NI.cpp` only. clang-cl needs it for `<wmmintrin.h>`.

## Gate
- `tools/gate.sh`: gate ok.
