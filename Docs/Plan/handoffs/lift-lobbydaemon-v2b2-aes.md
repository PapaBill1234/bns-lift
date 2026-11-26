# lift-lobbydaemon-v2b2-aes: handoff (round 1 of 2)

## What this session did

This session changed 3 bodies in `aes128Table.cpp`. All 4 exes (CG, LG, SCD, POD) and LobbyDaemon share this code.
The session did not build. The driver measures the result.

### aes128TableEncrypt (CG 0x38790, LG 0x5b4e0) and aes128TableDecrypt (CG 0x38d10, LG 0x5ba60)

- New idea: the state is 64 bits wide (`unsigned long long s0..s3, t0..t3`).
  Evidence: the original xors the table entries as qwords (`xor r11, qword ptr [...]`).
  It reads `rk[]` as zero-extended dwords and xors them into 64-bit registers (`mov eax, [s5]; xor r11, rax`).
  It also needs 8 callee-saved registers (push r14, push r15). The old lift used a 32-bit state.
- The table reads do not cast to `unsigned int`.
- `B3(x)` now masks with `& 0xFF`. The original extracts byte 3 with `shr rax, 0x18; movzx edx, al`. For 32-bit values the mask has no effect.
- The initial state is `(unsigned long long)in[i] ^ rk[i]`. The original does a 64-bit xor there.
- Loop: two rounds per pass (`int r = 10 >> 1; for (;;) { t = ...rk[4..7]; rk += 8; if (--r == 0) break; s = ...rk[0..3]; }`). This is the p07 form.
- Final round: the function calculates all 4 words first and then stores them to `out`. The original loads `rk[4..7]` before the first store.

### aes128TableSetupEncKey (CG 0x38370, LG 0x5b0c0)

- Reference `rijndaelKeySetupEnc` loop: `for (;;) { ...; if (++i == 10) break; rk += 4; }`.
- The expression reads `rk[3]` directly. It does not use a `temp` local.
  Evidence: the original reads bytes 1..3 of `rk[3]` from memory (`movzx eax, byte ptr [s0 + 2]`). It reads byte 0 from the register that holds the previous `rk[7]` (`movzx eax, dl`).
- Term order is the reference order: `rk[0]`, the `0xFF000000` term, `0x00FF0000`, `0x0000FF00`, `0x000000FF`, then `Rcon[i]`. The original emits the terms in this order and then xors `rk[0]` and `Rcon`.

## Not done

There are no Not done functions. The driver has not measured the results yet. If a function stays DIFF, round 2 must examine the new insn diff:

- Encrypt/Decrypt: the xor operand order in the loop. The original emits the terms in the order sbox3, sbox2, sbox1, sbox0, rk for Encrypt. It emits sbox1, sbox2, sbox3, sbox0, rk for Decrypt. The lift keeps the order `rk ^ T0 ^ T1 ^ T2 ^ T3`.
- SetupEncKey: if byte 0 also comes from memory, try `(unsigned char)rk[3]` for byte 0.

## Files changed

- `src/Security/source/BloodCrypto/crypto/aes128Table.cpp`
- `Docs/Plan/handoffs/lift-lobbydaemon-v2b2-aes.md`
