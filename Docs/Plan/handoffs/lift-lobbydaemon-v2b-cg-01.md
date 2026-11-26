# Handoff: lift-lobbydaemon-v2b-cg-01 (round 1)

Exe: CacheGate (CG). Base: bns-lift `6824f3d` (main).

## Lifted (source changes)

### CG 0x27d0 `CacheDList::MakeSessionAll`

- The original has one `Log::Write` call for the connect and the try-connect-fail messages.
  Each branch calls `Network::GetAddressStringW` and sets the format and the line (169 or 171).
- The original reads `_addr` and `_id` after `LeaveCriticalSection`, before the branch.
- The new form reads `addr` and `id` into locals after `Leave`. Each branch sets `ipString`, `format` and `line`.
  One `Log::Write` call follows the branch.
- Lessons D lists this function as a merged `Log::Write` tail. The source now has the merged form explicitly.

### CG 0x2660 `CacheDList::Initialize`

- The original has one placement-new expression: `::new (Memory::_Manager[2]->Alloc(...)) CacheDMap()`.
  The `throw()` placement `operator new` makes VS2010 add the null test and the `nullptr` branch.
- Evidence: the original stores the allocation pointer 2 times on the stack (EH placement-delete arguments).
  The original has a separate `xor` in the null branch. The old lift form (`buffer != nullptr ? new (buffer) ... : nullptr`) shared one zero register.
- Lessons B lists "placement new" as a failed form. That form used a separate `buffer` local and the explicit null test.
  This form has no explicit test. If the proof shows no gain, revert to the base form.

## Not done

| RVA | Function | Reason |
| --- | --- | --- |
| 0x10950 | `ClientSideDaemonChannel::~ClientSideDaemonChannel` | The original calls `RefCntHistory::add` out of line. The lift inlines it. Lessons B: a global `noinline` on `RefCntHistory::add` lost MATCH in other functions. No per-function form is allowed. Cause: inlining decision. |
| 0x5880 | `HandleCacheGateFragmentRelay` | Per-exe LTCG split. The same object is MATCH in POD. CG inlines `Session::Send` (`PacketBuffer::encrypt`, `EnterCriticalSection`, `Session::send`, `LeaveCriticalSection`), POD calls it. A body change changes POD too. |
| 0x2b20 | `CacheDList::LoadCachedListConfigFile` | 98.5. The evidence has no instruction lines (81 hunks). Lessons D: loop forms were tried (96.3 best before). Note for the next round: the original stores a 16-bit zero at `ipText+30` before `WideCharToMultiByte`; the lift has no such store. Not tried. |
| 0x51c0 | `HandleCacheGateRelay` | Per-exe LTCG split. Same object is MATCH in POD. CG inlines `Session::Send`. Lessons D: 3 forms tried. |
| 0xca10 | `DaemonConfig::Dump` | The original refers to RTTI data (`??_R0?AVCrypto@@@8`) next to `CacheGateConfig::_Def`. The lift builds with `/GR-` (console-4). Cause: data layout, not source. |
| 0x5040 | `HandleCacheGateHelloFail` | Per-exe register allocation. The original keeps 0 in `rdi` (a callee-saved register) for the `Decompose` test, the word store and the `cmp byte`. The same object is MATCH in POD. A body change changes POD. |
| 0x4180 | `wmain` (+ miss `wmain$dtor$0`) | The original has an unwind funclet for `daemonInstance` around `BloodDaemonMain` (EH state -2, `nop` after the call, frame 0x1800 = lift 0x17f0 + EH slot). The inlined `CacheGate` ctor has no allocation, so the A14 `::new` form does not apply. The lift also stores the `DaemonChannel` vftable; the original does not. LG has an out-of-line ctor and is MATCH. No source form found in one look-up. |
| 0x4c00 | `HandleCacheGateHello` | Per-exe LTCG split. The same object is MATCH in POD. Lessons B: else-if chain and nested version ifs failed. |

## Changed files

- `src/Server/Economy/CacheGate/CacheD.cpp`
- `Docs/Plan/handoffs/lift-lobbydaemon-v2b-cg-01.md`
