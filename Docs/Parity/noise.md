# funcdiff noise (lift-parity-0)

Status: 4 fixes are in `tools/funcdiff.py`. More candidates are open (see the end).

## Method
- `tools/funcdiff.py <EXE> --build build-vs2010 --show .` for all 4 exes.
- Count each signal line that is only in the original (-) or only in ours (+).
- Prove each candidate with the disassembly of both exes (capstone, same `Image` class as funcdiff).

## Result of the fixes (funcdiff run, not yet the parity gate)
| Exe | MATCH before | MATCH after | Keys gone | MATCH lost |
| --- | --- | --- | --- | --- |
| CacheGate | 216 | 293 | 0 | 0 |
| LobbyGate | 280 | 377 | 0 | 0 |
| SmartCouponDaemon | 225 | 334 | 0 | 0 |
| PostOfficeDaemon | 262 | 375 | 0 | 0 |

## Fix 1: branch targets counted as constants (PROVEN, FIXED)
- `signals()` added each immediate operand to `consts`. A `jcc` to a target inside the function has an immediate operand.
- The filter `0x10000 <= v < img.size` hid these targets only when the code is at RVA 0x10000 or more.
- Proof: CacheGate ours `Aes128NI_Decrypt` (0x63f0): `je 0x64ab`, `jae 0x6499`, `jg 0x6460` gave +0x6440 +0x6460 +0x6499 +0x64ab.
- Fix: skip all `X86_GRP_JUMP` instructions other than `jmp`, and `loop*`.

## Fix 2: jump table bytes decoded as code (PROVEN, FIXED)
- CacheGate orig `Aes128NI_Setup` (0x394c0, size 328): bytes at 0x395e0 decode as `add eax, 0xd000395`, `adc eax, 0x1d000395`. They are a table of 32-bit RVAs (0x395xx).
- Ours reads its table with `mov ecx, [r10 + rax*4 + 0x6270]` (r10 = image base from `lea r10, [rip - 0x6168]`).
- Fix: a memory operand `[base + index*1|4 + disp]` with disp inside the function marks the table start. Decoding stops there.
- After the fix `Aes128NI_Setup` is MATCH.

## Fix 3: calls through a slot with no symbol (PROVEN, FIXED)
- CacheGate `Aes128::Decrypt`: orig `call [rip+..]` → 0x5a398; ours → 0x65d28. Both are `Aes128::_Delegator+0x10`
  (orig `_Delegator` at 0x5a388, ours at 0x65d18). The slot is 0 in the file (set at run time).
- LobbyGate `Client::SendGetServiceEntryListOk`: orig `?62fb8`, ours `?762d8`. Both are `??_7RepeatPacketComposer@@6B@+8`
  (a vtable slot in `.rdata`). PostOfficeDaemon `CacheGateChannel::SendFragmentRelayRequest` orig `?62108` is the same.
- Fix: a call target with no name: (a) in a read-only section, use the function that the pointer holds;
  (b) in a writable section, use `<named global>+0x<off>` (nearest symbol, at most 0x40 bytes below).
- Only calls use this. Data refs still give `<data>` (see open item C).
- After the fix `Aes128::Decrypt` is MATCH. No `?<addr>` call remains in the 4 exes.

## Fix 4: stack frame size given to `__chkstk` (PROVEN, FIXED)
- `mov eax, <frame size>` then `call __chkstk`. The frame size is compiler noise.
- Proof: CacheGate `AlertSender::writev2` orig 0x9585 `mov eax, 0x16e0`; ours 0x9b05 `mov eax, 0x16d0`.
  `CrashHandler::handleCrash` orig 0x8853 `mov eax, 0x12e0`; ours 0xc23b `mov eax, 0x1318`.
- Fix: when a call to `__chkstk` or `_alloca_probe` comes right after `mov eax, imm`, remove that constant.

## Open candidates
- A. TLS offsets (PROVEN noise, NOT FIXED): `mov rax, gs:[0x58]; mov rcx, [rax]; mov edx, 0xfb00; mov rcx, [rdx+rcx]`.
  The immediate is the section-relative offset of a `__declspec(thread)` variable. Seen: SmartCouponDaemon ours
  `Log::WriteV` 0xc838 (0xfb00, 0xfb08); orig `Network::GetAddressStringW` 0x1ad3a/0x1ad42 (0xfa60, 0xfa40).
  Many functions show +0xfb00/+0xfb08 against -0xfa40/-0xfa60. Fix idea: name the value from the PDB
  `S_LTHREAD32`/`S_GTHREAD32` records, or drop an immediate that is used with the TLS array from `gs:[0x58]`.
- B. `??_C@_11LOCGONAA@` (empty wide string, 29/29): same name on both sides. Count per function differs. Real, not noise.
- C. `<data>` refs (141 orig / 244 ours): most are fields of named globals in `.data` (for example
  `AlertSender::_alertSender+0x54`, `Memory::_Manager+0x10`), and the image base (`lea r, [rip-x]` → 0x0).
  Naming them is a tightening, not a noise fix. Not done.
- D. `__FILE__` forms (`..\Shared\` against `..\..\Shared\`, `e:\dailybuild02\...\include\*.h`): real source/build differences.
