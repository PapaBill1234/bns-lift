# lift-parity-crypto-4 handoff

Turns: 62

## Done
- MATCH +38, MATCH lost 0. Gate ok, parity ok on commit 99f6223.

| Exe | MATCH | Total | Parity | Gain |
| --- | ---: | ---: | ---: | ---: |
| CacheGate | 448 | 491 | 91.2 % | +0 |
| LobbyGate | 643 | 739 | 87.0 % | +16 |
| SmartCouponDaemon | 593 | 669 | 88.6 % | +11 |
| PostOfficeDaemon | 676 | 759 | 89.1 % | +11 |

- Source forms: see `Docs/Parity/lessons.md` A25 (8 forms) and B "crypto-4" (4 failed forms).
- Files: `crypto/encoder/oaep_encoder.cpp`, `crypto/rsa.cpp`, `crypto/rsa.h`, `hash/ripemd128.h`, `math/bignumber/BigInteger.h`, `NumberTheory.cpp`, `biArithmetic.cpp`, `biMultiplication.cpp`, `BloodLib/source/Session.cpp`.

## Not done (one line per DIFF in scope)

| Function | Signal | Cause | Why stopped |
| --- | --- | --- | --- |
| `BigInteger::Divide` (big), LG/SCD/POD, 76.7 | orig calls `Sub` in loop 1 and `setBit` x2; ours inlines them (`memcpy`, add, `absCompare`, `memset`, sub), extra `digit_bit_r`/`digit_mask` refs | VS2010 inline and block-layout choice | Budget; looked at it, no source try |
| `BigInteger::invMod`, LG/SCD/POD, 83.1 | orig inlines `RightShift(x,1)` and calls `Sub` x6; ours calls `RightShift` and inlines Add/Sub | `RightShift` must stay `noinline` for the `LeftShift` tail-jump MATCH | 2 tries failed (lessons B) |
| `BigInteger::InvMod`, LG/SCD/POD, 89.7 | same as `invMod` | same as `invMod` | 2 tries failed (lessons B) |
| `Rsa::decrypt` LG 0x52de0, LG/SCD/POD, 91.7 | extra `memset` call, extra `digit_mask` ref | VS2010 turns the zero-fill loop into `memset`; orig keeps a byte loop | 3 tries failed |
| `BigInteger::IsPrime`, LG, 82.2 | calls 81, refs/consts differ | ❓ not analysed | Not tried, budget |
| `BigInteger::isPrimeMR`, LG, 88.4 | refs/consts differ | ❓ not analysed | Not tried, budget |
| `Crypto::Create`, LG, 34.0 | calls 29, refs 40 | ❓ factory body differs (lib without debug info) | Not tried, budget |
| `Crypto::InstanceSize`, LG, 44.4 | orig has a `<data>` ref and consts 0x598, 0x7a0, 0x1060, -1; ours only 0x170 | ❓ orig uses a size table per type | Not tried, budget |
| `Dh::Process`, LG, 77.8 | calls/refs differ | ❓ not analysed | Not tried, budget |
| `Dh::getValue`, LG, 98.0 | orig has const 0x7 | ❓ byte-count rounding form | Not tried, budget |
| `Dh::~Dh`, LG, 66.7 | orig refs `??_7Dh@@6B@`, ours `??_7CryptoKey@@6B@` | ❓ our dtor body is empty, so VS2010 drops the `Dh` vtable store | Not tried, budget |
| `BroadcastCrypt::Initialize`, LG, 95.6 | consts: ours +0x4, +0x60, 0x2840 against orig 0x2847 | ❓ size or mask form | Not tried, budget |
| `BroadcastCrypt::clear`, LG, 85.7 | ours has extra consts 0x2, 0x3, 0x4 | ❓ loop unroll or member clear order | Not tried, budget |
| `aes128Table*` x4 | see lessons D | stop list (lessons D) | Not tried |

## ❓
- Causes marked ❓ above are not verified.

## Blocked
- None.

## Gate result
- `tools/gate.sh` ok, `tools/parity.sh` ok on 99f6223. After that run, only docs changed.
