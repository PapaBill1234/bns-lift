# lift-parity-noinline-2 handoff

Turns: about 120 (5 stages)

## Done
- `__declspec(noinline)` on the BloodLib and server functions that the original never inlines (`Log::Flush`, `Log::Initialize`, `Log::FlushInline`, `DelayedRelease::Cleanup`, `Prng::addEntropy`, LG `Dump` and `Initialize` functions, SCD and POD functions of the card scope).
- POD: `Packet::Decompose(int,int,char const*,...)` 0x220d0 added. 8 calls in `CacheEconomyPacketHandler.cpp` use it. `Channel::Send` miss gone.
- SCD: `Network::OpenPort` has the 9-argument form only. 3 calls in `SmartCouponDaemon.cpp` changed. Miss gone.
- LG `initialize`: `Dump` calls put back (lessons A3).
- Facts and failed tries are in `Docs/Parity/lessons.md` (A3, B, "noinline-2, stage 5").

## Gate result
- `.scratch/gate_errors.sh`: gate ok.
- `tools/parity.sh`: parity ok. MATCH -> DIFF 0, MATCH name gone 0 in all 4 exes.
  - CG 420/491 (+2), LG 528/739 (+6), SCD 504/669 (+6), POD 553/759 (+8).

## Not done (one line per miss: function, signal, cause, why stopped)
- `Prng::Generate`, `CryptoKey::Initialize`: ONLY-ORIG, crypto code; the original inlines or folds it in a way noinline does not give. Left to the crypto cards.
- `Console::Flush`: the original calls CRT `operator delete`. Ours has no such function. No source fix.
- `RefCntObject::operator delete`: the original shares one body with CRT delete. Cannot be set in source.
- `wmain$dtor$0`: compiler-made unwind funclet. Skipped.
- POD `DaemonConfig::Dump` 0x282d0: dead flow in `initialize` 0x13498 (lessons A3). The original call is not reachable in source.
- `CriticalSection::CriticalSection`: no caller in the original. Nothing to match.
- `Session::Send(Packet const*)`, `Session::deallocateCrypt`: SCD and POD inline them, CG and LG call them (LG 0x18f00, 0x194c0). One setting for all exes is wrong. Needs a wrapper `.cpp` per exe. Stopped: risk of MATCH loss.
- LG `Session::allocateCrypt` 0x19460: ONLY-ORIG. Ours has no symbol although noinline is set. Cause not known.
- `operator delete[]` (orig `??_V@YAXPEAX0@Z`, 59 B): not tried.

## ❓
- Why `Session::allocateCrypt` has no symbol in our exe.
- Array placement new in VS2010.
- Names of 2 LG fields in `LobbyGate::initialize` (`// LIFT:` in LobbyGate.cpp 0x13028-0x13064, 0x13072).

## Blocked
- None.
