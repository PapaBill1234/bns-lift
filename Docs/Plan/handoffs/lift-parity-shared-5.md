# Handoff: lift-parity-shared-5 (shared crypto, BloodLib, EH state -2, misses)

Branch: `slice/lift-parity-shared-5`. Base: main 8778485. Not merged. Not pushed.

## Result

| Exe | Before (main) | After | Gain |
| --- | --- | --- | --- |
| CacheGate | 456 | 458 | +2 |
| LobbyGate | 658 | 663 | +5 |
| SmartCouponDaemon | 630 | 631 | +1 |
| PostOfficeDaemon | 694 | 696 | +2 |
| LobbyDaemon | 1024 | 1024 | 0 |

Total: +10 MATCH. No MATCH lost. `tools/gate.sh`: gate ok. `tools/parity.sh`: parity ok (last run after e3f19d9).

## Commits

| Commit | Change | Gain |
| --- | --- | --- |
| 3b8b27f | `Dh::~Dh` (no `CryptoKey` dtor), `Dh::Process` switch, `BroadcastCrypt::clear` compare chain | LG +3 |
| 4fb423a | `IdleWatcher::run` uses a local `SystemEvent` | LG +1 |
| a6525a2 | `BaseRefCntObj::operator new(size_t, wchar_t const*, int)`, used in `Port::Initialize` | +1 in each exe (4) |
| e3f19d9 | PDB parameter types: `Packet::Concatenate(char const*, short, ...)`, `Packet::Decompose(unsigned int, int, ...)` | CG +1, POD +1 |

Scope note: a6525a2 changes 2 lines in `src/Server/BloodLib/source/Port.cpp`. That file is not in the card file list.
The miss `RefCntObject::operator delete` has its only call site there (the unwind funclet of `Port::Initialize`).
The change is in its own commit. The integrator can drop it if another card conflicts on `Port.cpp`.

## Lessons

The card says: do not edit `Docs/Parity/lessons.md`. The review merges these tables into A and B.

### Worked

| Function | Before | After | Count |
| --- | --- | --- | --- |
| LG `Dh::~Dh`: remove the declared `virtual ~CryptoKey() {}`. The original stores only `??_7Dh`, no base vtable store at the end. | 66.7 | MATCH | 1 |
| LG `Dh::Process`: `switch (_state)` with case 0, case 1, default `return false`, then `_state = -1` (test plus dec chain, 0x5598d). | 77.8 | MATCH | 1 |
| LG `BroadcastCrypt::clear`: compare chain `type == 0 \|\| (type-1 != 0 && (type-2 == 0 \|\| (unsigned)(type-3) <= 1))`, same form as `Session::deallocateCrypt`. A switch gave a range compare. | 85.7 | MATCH | 1 |
| LG `IdleWatcher::run`: local `SystemEvent event;` before `LogBufferAllocator::Initialize`. Its inline dtor closes the handle. This gives EH state -2 and funclet dtor$0 (0x60430). | 96.3 | MATCH | 1 |
| `RefCntObject::operator delete` (miss, all 4 exes): `BaseRefCntObj` has a PDB `static operator new` (type 0x2FCA). Write `_pool = new (PORT_FILE, 243) SessionPool(_id);`. VS2010 then calls the matching class placement delete in the unwind funclet (CG 0x3a920). | miss | MATCH | 4 |
| CG `Packet::Concatenate` (miss): PDB mangled name has `F` (short), ours had `G` (unsigned short). Signed test `size < 0 \|\| size > 4000` (0x74de: `test si,si; js; cmp 0xfa0; jle`). | miss | MATCH | 1 |
| POD `Packet::Decompose(unsigned int, int, char const*, ...)` (miss): PDB mangled name has `I` (unsigned int) for the first parameter. | miss | MATCH | 1 |

Pattern: for a miss, compare the mangled names first (`Image.mangled` in `tools/funcdiff.py`). A type mismatch in one parameter gives a miss, not a DIFF.

### Failed

| Function | Before | After | Count |
| --- | --- | --- | --- |
| LG `BroadcastCrypt::Initialize`: signed align formula `((cs+15)/16*16 + sizeof(BroadcastPacketCrypt) + 15)/16*16`. VS2010 CSEs `(cs+15)/16`. The original recomputes it with 0x2847. | 95.6 | 94.9 | 0 |
| LG `BroadcastCrypt::clear` as a switch with `case NO_HANDSHAKE_CRYPT: break;` (range compare) and as a per-class dtor switch. | 85.7 | 88.9 / 93.3 | 0 |
| LG `Dh::getValue`: `buffer == 0 \|\|` test, then an inline `generateValue` helper. VS2010 folds the null test of the stack array. 3 tries. | 98.0 | 98.0 | 0 |
| `FragmentPacketConcatenater::Clone`: ctor out of line in FragmentPacket.cpp; inline `PacketConcatenateBuffer()` ctor; `PacketConcatenateBuffer()` defined in PacketUtil.cpp (other TU). No change. 3 tries. | 93.3 | 93.3 | 0 |
| `IoWorker::run` (4 exes): success path first (`if (result) {...} else {...}`) and signed state test `state >= 0 && state <= STATE_STOPPING`. Calls and refs MATCH. Only the `.tls` offset of `ZstdCCtx` is left (orig 0x30, ours 0x18). Reverted: no MATCH gain. Patch kept for a `.tls` card (see below). | 84.9 | 97.4 | 0 |

## DIFF functions not fixed

| Function | Signal | Cause | Why I stopped |
| --- | --- | --- | --- |
| LG `Crypto::Create` 34.0 | c29 r40 k33 | Ours is constant-propagated to type 2: all callers pass 2. The original keeps the full switch (byte table over types 0..81). The original PacketCrypt was likely a closed non-/GL lib object. | Needs a per-file no-/GL option in `tools/vs2010/build.sh` (tool card). |
| LG `Crypto::InstanceSize` 44.4 | r0 k33 | Same as `Crypto::Create`. The table also suggests case labels 0,1,4,5,14,32,33,34,65,81 that return -1 ❓. | Same. |
| LG/POD `FragmentPacketConcatenater::Clone` 93.3 | k80 (-2 missing) | Orig has funclet `dtor$0` that calls the global placement delete (0x1000). Our ctor has only stores, so VS2010 drops the new-expression cleanup. Likely the Packet lib was a non-/GL object ❓. | 3 tries, no change. |
| `IoWorker::run` x4 84.9 | c69 r97 k88 | Layout of the loop (fixed by the saved patch to 97.4) and the `.tls` order: orig `WorkerId` 0x10, `LogBufferAllocator::_Local` 0x18, `PacketBufferAllocator::_Local` 0x20, `Thread::Current` 0x28, `ZstdCCtx` 0x30 (CG). Ours puts `ZstdCCtx` at 0x18. | `.tls` order is set by the definitions in other files (LogBuffer.cpp, Thread.cpp, Network.cpp). Out of scope. |
| LG `AlertSender::init` 99.1 | r97 | The original `ThreadManager::StartThread` writes `*threadId = threadAddr` (LG 0x276be). Ours never writes it, so LTCG drops `&_threadId` (no `lea r8`). | The fix is in `Thread.cpp` (not in the card files). The `// BUG:` comment at 0x12e40 is wrong for LG. |
| SCD `Session::Connect` 98.0 | k94 (0x3e8 missing) | The original multiplies the timeout: `now + timeout * 1000` (SCD 0x1c0bb `imul ebx, ebx, 0x3e8`). The timeout is in seconds. | LG `LobbyGate.cpp:396` passes 5000. It must pass 5 with this fix. That is an exe file. |
| POD `Channel::Send` 97.0 | c91 | Orig is an LTCG clone: the caller passes the session in r8 and the `GetSession` virtual call is gone. | Caller-side (exe file). |
| POD `operator delete[]` 0.0 | c0 r0 k0 | The original is `operator delete[](void*, void*)` with the Memory.h:181 crash body in `RelayTimeContext.obj` (lesson A16 form). | `RelayTimeContext.cpp` is an exe file. |
| CG/SCD `DaemonConfig::Dump` 97.9 | r94 | See console-4 stop notes. | Not tried (stop notes). |
| POD `DaemonConfig::Dump` (miss) | miss | Orig `PostOfficeDaemon::initialize` calls `DaemonConfig::Dump` (POD 0x13498). Our POD source has no call, so `/OPT:REF` removes it. | Exe file. |
| LG `operator delete` / POD `??3@YAXPEAX@Z` (miss) | miss | The original has an empty 3-byte `??3@YAXPEAX@Z` in `FragmentPacket.obj`, folded with `Console::Flush`. Ours maps the global delete to `free` (`src/crt/new_delete.c`). | An empty global delete changes run-time behavior. Owner decision. |
| LG `BroadcastCrypt::Initialize` 95.2 | k86 | Orig recomputes the align with 0x2847; VS2010 CSEs our form. | 1 try (worse). |
| LG `Dh::getValue` 98.0 | k94 | Orig keeps `lea rax,[rsp+0x240]; test rax,rax` and `add eax,eax`. | 3 tries. |
| `BigInteger::invMod` LG/SCD/POD 83.1 | c59 k90 | Order of the inlined Add/Sub/compare blocks. 2 tries in crypto-4. | Not tried here (time). |
| `BigInteger::InvMod` LG/SCD/POD 89.7 | c85 k84 | Same family as invMod. | Not tried here (time). |
| `BigInteger::Divide` SCD/POD and LG overload 76.7 | c75 r67 k89 | Ours inlines `Set` and `setBit` in other places; extra `memcpy`, `0x208`. | Not tried here (time). |
| LG `BigInteger::IsPrime` 82.2, `isPrimeMR` 88.4 | r80 k67 / c81 k84 | Not studied. | Not tried here (time). |

### Saved patch for IoWorker::run

Apply it together with a `.tls` order fix. Then `IoWorker::run` should MATCH in 4 exes.

- `handleFailedEvent`: `int state = Daemon::Instance->State; if (state >= Daemon::STATE_UNKNOWN && state <= Daemon::STATE_STOPPING) return;`
- Loop body: `if (result) { end-event test; HandleEvent path } else { failed path }`, without `continue`.

## Turns

Turns: 140 (estimate, 2 context windows).
