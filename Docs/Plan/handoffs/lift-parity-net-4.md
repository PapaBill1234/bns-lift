# lift-parity-net-4 handoff

## Result

| Exe | Main MATCH | Branch MATCH | Gain | Parity |
| --- | --- | --- | --- | --- |
| CacheGate | 448 | 452 | +4 | 92.1 % |
| LobbyGate | 627 | 631 | +4 | 85.4 % |
| SmartCouponDaemon | 582 | 586 | +4 | 87.6 % |
| PostOfficeDaemon | 665 | 668 | +3 | 88.0 % |
| Total | | | +15 | |

- MATCH -> DIFF: 0 in each exe. `gate ok`, `parity ok`.
- Now MATCH: `SessionSendBuffer::clearPacketBufferList` x4, `Session::HandleFailedEvent` x4, `Network::Clear` x4, `Session::Connect` (LG), `Session::SendV` (CG), `Network::OpenPort` (SCD).

## Changes

| File | Change |
| --- | --- |
| `RefCntObject.h` | `friend SessionSendBuffer`. |
| `SessionBuffer.cpp` | `clearPacketBufferList`: `inline_depth(0)` and the `removeReferenceCount` body by hand. |
| `Session.cpp` | `Connect` member reads + `memset`; `HandleFailedEvent` close/`Leave` per case; `SendV` gives `Compose` the header fields. |
| `Network.cpp` | `Clear`: `unsigned int` counter, cached `Port*` only for the null test, reload `_port[i]` for each use. `OpenPort`: `id < 1 \|\| id > 24`, `initialMode` list 0..3. |

## Open DIFF (function, signal, cause, why stopped)

- `IoWorker::run` x4 84.9: calls 69, consts 88. Cause: inlined zstd/TLS paths and a different call set. Stopped: no time left in this card; not tried.
- `Session::HandleEvent` x4 98.5: calls 98, refs 97. Cause: one extra `Log::Write` site; the common log site failed in round 3 (lessons B). Stopped: no new idea.
- `Network::OpenPort` CG/LG 98.9, POD 97.9: refs 97/94. Cause: the original default max-session table (CacheGate .rdata 0x4e408) has no PDB name (`<data>`), ours is `s_defaultMaxSession`; the original tests the id with `test ecx,ecx; jne`, ours with `cmp ecx,1; jae`. Stopped: 3 tries (Port ctor body form, local const array, range check form), no score gain.
- `Session::Connect` SCD 97.8: consts 93. Cause: LTCG propagates the `reconnect` argument as a constant in our build (no `test cl,cl`, `ReconnectTimer` made always); the original keeps the test (0x1bf7d). Caller-set effect, not a body form. Stopped: no source form in this function.
- `Session::Session` x4 95.2: refs 86. Stop list (lessons D). Not tried.
- `Session::allocateCrypt` LG 67.4, `Session::completeHandshake` LG 55.6: out of scope (do not edit).

## Not kept

- `Port` ctor with body assignments (store order of CacheGate 0xd466-0xd480): store order is the same as the original, but 0 MATCH gain. Reverted.
- Local `const` array for the max-session table in `OpenPort`: the table goes on the stack (extra const 0x2710). Reverted.

Turns: 110
