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

## Part 2 (this session)

This session did not build. It had no measured insn diff of the part 1 forms. The evidence in the packet is from the base build (rolled form).

### aes128TableSetupEncKey (CG 0x38370, LG 0x5b0c0): changed

- The part 1 form read `rk[3]` as `unsigned int` and took bytes with shifts. MSVC forwards the stored `rk[7]` value, so that form keeps the shifts (`shr rax, 8; movzx`) of the base build.
- The original reads bytes 1..3 with `movzx eax, byte ptr [s0 + 0..2]` (`s0 = rk + 13`). It takes byte 0 from `dl`/`al` of the stored `rk[7]`.
- New form: `unsigned char const* temp = reinterpret_cast<unsigned char const*>(&rk[3]);` and the terms use `temp[0]`, `temp[3]`, `temp[2]`, `temp[1]`. This is the same byte-read idiom as SetupDecKey (MATCH).
- The loop exit is now `if (++i == 10) return;` (reference form).
- The original keeps 6 callee-saved registers (push rdi, r12, r13). The byte reads lower the register pressure. The base lift used 7.

### aes128TableEncrypt and aes128TableDecrypt (CG 0x38790/0x38d10, LG 0x5b4e0/0x5ba60): no change

- The part 1 form (p07 loop, 64-bit state) is not measured yet. This session kept it.
- Logic check against the original: term sets, table offsets, final masks and the `rk` offsets agree.
- Open items for the next round, when a measured diff exists:
  - Loop shape. The original has `do { t-round; s-round; rk += 8; } while (--n)` with n = 4, and one t-round after the loop (`s5 = rk + 4`, `mov s6d, 4`). If the p07 break-in-the-middle loop does not give this shape, try the explicit form: `for (int r = 4; r != 0; --r) { t = ...; s = ...; rk += 8; }`, then the t-round and the final round.
  - Term order. The original emits, for each word, the 3 foreign-state terms in descending state order, then the own-state term, then `rk`. This looks like a compiler order, not a source order.
  - Store order. The original stores `out[1]`, `out[2]`, `out[0]`, `out[3]` after it computes all 4 words.

## Files changed

- `src/Security/source/BloodCrypto/crypto/aes128Table.cpp`
- `Docs/Plan/handoffs/lift-lobbydaemon-v2b2-aes.md`
