# Handoff: lift-lobbydaemon-v2b2-aes (round 2)

## What I lifted

- `aes128TableEncrypt` (CG 0x38790, LG 0x5b4e0): The round 1 state is 64 bits wide. Round 1 used the reference `for (;;)` loop with a break in the middle. That loop did not give the original layout. The original sets a counter to 4 (`mov s6d, 4`), runs two rounds in each pass (`dec`/`jne`), and does round 9 after the loop. Round 2 uses `int r = 4; do { t-round; rk += 8; s-round; } while (--r);`. Then round 9 goes to t, and the final round follows.
- `aes128TableDecrypt` (CG 0x38d10, LG 0x5ba60): Same change as Encrypt.
- `aes128TableSetupEncKey` (CG 0x38370, LG 0x5b0c0): Round 1 used a `for (;;)` loop with `if (++i == 10) return`. That stopped the 5x unroll (lift 68 insns, original 159). Round 2 goes back to the counted `for (i = 0; i < 10; ++i, rk += 4)` loop of the base. The base kept the unroll. The original reads byte 0 of rk[3] from the register (`movzx eax, dl`). It reads bytes 1..3 from memory (`movzx byte ptr [rk + 13..15]`). The lift now does the same. It takes `B0(temp)` from `temp = rk[3]` and reads bytes 1..3 through an `unsigned char const*` to `rk[3]`. The xor order follows the original: (B0 & ff000000), (byte 3 & ff0000), (byte 2 & ff00), (byte 1 & ff), rk[0], Rcon[i].

## Not done

No function has a proof of MATCH yet. The driver measures this round. The forms that failed are:

- Encrypt/Decrypt: rolled loop (base, 70.0); reference `for (;;)` with `r = Nr >> 1` and a break in the middle (round 1, 83.3).
- SetupEncKey: shifts from the register for all bytes (base, 88.9); `for (;;)` with all bytes through a pointer (round 1, 79.8, the unroll stopped).

If Encrypt/Decrypt stay DIFF, look at the final round next. The original computes out[1], out[2] and out[3] first and out[0] last. It stores in the order out[1], out[2], out[0], out[3].

## Changed files

- `src/Security/source/BloodCrypto/crypto/aes128Table.cpp`
- `Docs/Plan/handoffs/lift-lobbydaemon-v2b2-aes.md`
