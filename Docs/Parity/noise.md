# funcdiff noise (lift-parity-0)

Fixes 1 to 10 are in `tools/funcdiff.py`. See the open candidates below.

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

## Fixes of lift-parity-tool-2

Counts: `tools/parity.sh` on the same VS2010 objects, before the fixes and after them. No exe loses a MATCH function.

| Exe | MATCH before | After fix 5 to 8 | Change | MATCH lost |
| --- | ---: | ---: | ---: | ---: |
| CacheGate | 387 | 405 | +18 | 0 |
| LobbyGate | 487 | 506 | +19 | 0 |
| SmartCouponDaemon | 461 | 484 | +23 | 0 |
| PostOfficeDaemon | 509 | 529 | +20 | 0 |
| Shared library | 369/489 | 397/489 | +28 | 0 |

Review 1 measured +63 (fix 5 and 6 only). The result is +80. The test copy of review 1 named a TLS offset only after
a `gs:` load. The final fix 6 also finds the offset before the load (see fix 6).

## Fix 5: vtable symbol read as a string (PROVEN, FIXED)
- `Image.string_at()` ran before `target_name()`. Slot 0 of a vtable holds a code address (`0x1400074xx`). Its bytes can
  look like a 2-byte text.
- Proof: SmartCouponDaemon `Console::Console` (orig 0x23170, ours 0x6170). Both have 2 `lea rax, [rip+x]`.
  Orig: `??_7LogMedia@@6B@` (0x78a20) then `??_7Console@@6B@` (0x77060). Ours: the same 2 symbols (0x58700, 0x58730).
  Before: refs orig `??_7Console@@6B@`, `??_7LogMedia@@6B@`; ours `"0a"`, `"0a"` (score 66.7, DIFF).
  After: both sides name the symbol. Score 100, MATCH. The code is equal: same calls, same 2 vtable stores, same size (113 bytes).
- Fix: when a `??_7` symbol is at the exact RVA of the data ref, use that symbol first.
- Effect: all 47 lines of `allow-worse.txt` were for this noise. They are removed (each function is MATCH now).

## Fix 6: `.tls` offsets (PROVEN, FIXED)
- Code: `mov rax, gs:[0x58]; mov rcx, [rax]; mov edx, <off>; mov [rdx+rcx], x`. `<off>` is the offset of a
  `__declspec(thread)` variable in the `.tls` block. The linker puts the variables in another order in each exe.
- Proof: SmartCouponDaemon `LogBuffer::deallocate_me` (orig 0x200b0, ours 0xcac0, 30 bytes each).
  Orig `mov r8d, 0x18`, ours `mov r8d, 0x60`. The PDB (`S_LTHREAD32`) names both: `LogBufferAllocator::_Local`
  (orig .tls offset 0x18, ours 0x60). Same variable, other offset. Before: consts 0x18 against 0x60 (DIFF).
  After: both are the ref `tls:LogBufferAllocator::_Local`. MATCH. `Log::WriteV` (orig 0x19870, ours 0xc600) is the same case.
- Fix: `mov reg, imm` where `imm` is the `.tls` offset of a PDB `S_LTHREAD32` or `S_GTHREAD32` symbol is a ref
  `tls:<name>`, not a constant.
- Guard (`is_tls_index()`): the register must be used as `[reg + reg]` (scale 1) in the next 6 instructions, and there
  must be a `gs:` operand in 6 instructions before or after. The original often puts the `mov` before the `gs:` load
  (`ThreadManager::entry` orig 0x1314e `mov edx, 0x28` then `mov rax, gs:[0x58]`). A version that needed a
  `gs:` load before the `mov` missed these cases. A version with no `[reg+reg]` test named sizes like `mov r8d, 0x40`
  by chance (`Daemon::setAddress`: score 99.3 -> 88.1, `ThreadManager::entry` 66.7 -> 33.3). The final test gives
  no score loss except `IoWorker::run` (85.1 -> 84.9, 0 MATCH lost).

## Fix 7: `<K const ,V>` against `<K const,V>` (PROVEN, FIXED)
- Proof: CacheGate `CacheDList::add` 0x3490. Orig call `..._Buynode<std::pair<unsigned short const ,CacheD * __ptr64> >`,
  ours `..._Buynode<std::pair<unsigned short const,CacheD * __ptr64> >`. Same template, same instance. Only the PDB writer
  differs in the space. Before: calls 83, DIFF 94.4. After: MATCH 100. LobbyGate `ClientManager::AddSession` is the same case.
- Fix: `name_form()` removes the space before a comma in each PDB name (both exes).

## Fix 8: function name not demangled in the original PDB (PROVEN, FIXED)
- Proof: CacheGate `Network::Initialize`. Orig call `?Setup@PacketCrypt@@SA?AW4ErrCode@1@H@Z`, ours `PacketCrypt::Setup`.
  The original PDB has only the public (mangled) name at this address. The mangled name is the name of
  `PacketCrypt::Setup` (class `PacketCrypt`, function `Setup`, static, returns `ErrCode`). Before: calls 91, DIFF 97.0.
  After: MATCH 100.
- Fix: `simple_demangle()` gives `Scope::name` for a plain mangled name (`?name@Scope@@...`). It does not change
  operators, ctors or templates (`??`, `?$`). Used for the names of functions and for a call target that has only a public name.

## Fix 9. TLS offset definitions outside the local instruction window

- In CacheGate `Network::initWorkerThread`, the original puts 0x30 in
  `r14d` at 0xd94f. At 0xd9c9 it stores zero to `[r14+rcx]`.
  The instruction at 0xd9c1 loads the TLS block pointer into `rcx`.
  The build uses 0x18. Both PDBs identify the variable as
  `IoWorker::ZstdCCtx`. The earlier instruction window missed both
  definitions. The comparison now uses `tls:IoWorker::ZstdCCtx`.
- CacheGate `Network::GetAddressStringW` at 0xd6d0 forms two addresses
  by adding 0x40 and 0x60 to the TLS block pointer. It writes a byte
  to the first address and a wide character to the second. It passes
  the first address to `strcpy_s` with size 32. The PDB gives the
  second address the name `__ip_addr_string_w__`. The build uses
  offsets 0x20 and 0x40 for these buffers and names both in its PDB.
  LobbyGate and PostOfficeDaemon use the same original offsets as
  CacheGate. SmartCouponDaemon uses 0xfa40 and 0xfa60.
- Recover the narrow buffer name only when the function has two
  verified TLS offsets 32 bytes apart and the PDB names the higher
  offset as the wide buffer. Keep any existing PDB name for the
  lower offset. This also corrects the inlined references in
  `Daemon::setAddress`.
- In the additional check, follow each path to the definition.
  Check that the register is used only to form the TLS address.
  Keep an immediate value as a constant if the code also reads it
  as data or passes it to a function.
- In the same VS2010 binaries, this adds three matches in CacheGate,
  five in LobbyGate, four in SmartCouponDaemon, and three in
  PostOfficeDaemon. Shared matches increase from 483 to 486 of 549.
  Every previous match holds.

## Fix 10. Public names of folded virtual tables

- In CacheGate `Session::initialize`, the instruction at 0xe343
  loads the table at 0x52780. The original PDB names this table
  `SessionRecvBuffer`. In the build, the instruction at 0x19fc0
  loads the table at 0x4c228. The build PDB gives two public names
  at section 2 offset 70184. They are `SessionRecvBuffer` and
  `CrashHandler`. The old comparison selected `CrashHandler`.
- In SmartCouponDaemon `Network::Network`, the original PDB gives
  the `NetworkEndEvent` and `GameEventEndEvent` tables the same
  address, section 2 offset 90096. The reference in the build has
  the `NetworkEndEvent` name.
- In PostOfficeDaemon `CrashHandler::CrashHandler`, the build PDB
  gives the `CrashHandler`, `SessionRecvBuffer`, and
  `CheckPostCapacityRelayRequest` tables the same address,
  section 2 offset 167328. The original PDB gives the reference
  the `CrashHandler` name.
- Use every public table name at the referenced address. Pair
  references when they share a name. Count each reference once.
  These checks preserve differences in table names and counts.
- The same binaries gained five matches. CacheGate, LobbyGate, and
  SmartCouponDaemon gain `Session::initialize`. SmartCouponDaemon
  also gains `Network::Network`. PostOfficeDaemon gains
  `CrashHandler::CrashHandler`. Shared matches increase from 487
  to 490 of 549. All previous matches hold.

## Open candidates
- A. TLS offsets: see fixes 6 and 9.
- B. `??_C@_11LOCGONAA@` (empty wide string, 29/29): same name on both sides. Count per function differs. Real, not noise.
- C. `<data>` refs (141 orig / 244 ours): most are fields of named globals in `.data` (for example
  `AlertSender::_alertSender+0x54`, `Memory::_Manager+0x10`), and the image base (`lea r, [rip-x]` → 0x0).
  Naming them is a tightening, not a noise fix. Not done.
- D. `__FILE__` forms (`..\Shared\` against `..\..\Shared\`, `e:\dailybuild02\...\include\*.h`): real source/build differences.
