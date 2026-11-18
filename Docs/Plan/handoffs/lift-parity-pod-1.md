# lift-parity-pod-1 handoff

## Done
- POD MATCH 484 -> 509 / 759 (67.1 %). CG 387, LG 487, SCD 461 (no MATCH lost).
- Pattern 46: macro `liftArrayNew` (RelayContext.h) at 9 call sites: +8.
- Pattern 48: `__declspec(noinline)` on 6 exe-only functions (convertFailReason x2, CachedWatchdog ctor,
  AttachedItemContext::operator=, composeRelayHeader(FragmentPacket&), combineFragmentRelayFormat): +17.
- Lessons: Patterns 46 to 49 in `Docs/Parity/lessons.md`.

## Not done (DIFF and misses with cause)
- 90 % is not reachable exe-only: most misses are shared crypto (BigInteger, Rsa, Oaep, Prng) and CRT/STL code.
- `PostOfficeDB::UpdateStatusToDeliverySuccess` 0x17bf0, `UpdateStatusToDeliveryFailure` 0x17e00 (miss): fix is known
  (Pattern 49, +2) but it moves the data layout and loses 5 noise MATCH (refs). Stopped: funcdiff vtable-as-string issue.
- POD map keys non-const (Pattern 47): refs, same layout noise. Stopped for the same reason.
- `CacheEconomyPacketHandler` (13 DIFF, calls): lift helpers `processEconomyResponse`, `notSupported`, `logEnd`
  must be inlined. Not tried (time).
- PostOfficeDB Load* functions (calls/refs): helpers `BindPostColumns`, `MakePostContext` must be inlined. Not tried.
- `PostContextManager::GetContext`, Relay/WorldChannel Get (85.8, refs): orig block order puts addReferenceCount +
  Leave after the error log; a second `L"PostContext.cpp"` ref. Not tried.
- SessionHandler::PacketHandler of Agent, World, CacheGate, Management (calls): Pattern 31 tail call. Not tried.
- `PingRelayContext::GetRequestWid` 0xfb40, `ComposeResponsePacket` 0x34c40, `TimerClass`/`TimerId`: ICF folded,
  the linker keeps a different name. Not fixable in source.
- Scalar deleting dtors and `std::_Tree` map members (misses): compiler-generated, follow the map key and layout.
- Shared `operator delete[]` 0xb040 (miss): orig logs `== CRASH == [memory], DO NOT USE THIS DEL OPERATOR`. Not tried.

## ❓
- Prng::Initialize score changes between builds (88.9 / 72.2): noise?
- Vtable refs read as strings ("PI", "PT") after a layout move: funcdiff artifact or real .rdata change.

## Blocked
- None.

## Gate result
- `.scratch/gate_errors.sh`: gate ok. `tools/parity.sh`: parity ok (POD +25 on baseline, 0 MATCH lost).
