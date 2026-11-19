# Handoff: lift-parity-packet-4 (PacketBuffer, FragmentPacket, ToPacket)

Branch: `slice/lift-parity-packet-4`. Not merged. Not pushed.

## Result

| Exe | Main MATCH | Branch MATCH | Gain | Parity |
| --- | --- | --- | --- | --- |
| CacheGate | 448 | 450 | +2 | 91.6 % |
| LobbyGate | 627 | 633 | +6 | 85.7 % |
| SmartCouponDaemon | 582 | 585 | +3 | 87.4 % |
| PostOfficeDaemon | 665 | 672 | +7 | 88.5 % |
| Total | | | +18 | |

`tools/gate.sh`: gate ok. `tools/parity.sh`: parity ok. No exe lost a MATCH function.

## Commits

| Commit | Function | Gain |
| --- | --- | --- |
| 2dd3328 | `PacketBuffer::Compose` x4 | +4 |
| d04a62e | `PacketBuffer::Decompose` x4 | +4 |
| 37a2f83 | `CheckCompose`, `RepeatPacketComposer::PushRepeatCount` | +4 |
| 53d2b73 | `Packet::Copy` (LG) | +1 |
| 2348094 | `ClientPacketBufferHandler::ToPacket` (LG) | +1 |
| b4dab32 | `RawPacketBufferHandler::Destroy` (SCD), `TextStreamPacketBufferHandler::Destroy` (POD) | +2 |
| 7dcce0e | `TextStreamPacketBufferHandler::ToBuffer` (POD) | +1 |
| 86c1f03 | `PacketBuffer::DecomposeText` (POD) | +1 |

## Not done (function, signal, cause, why stopped)
- LG `FragmentPacket::StartRepeat` 93.3: const 0x8 missing. Cause: the original keeps `this` in rcx and uses `add rcx,8`; ours uses `lea rcx,[rbx+8]` (register allocation). The original also saves rdi and does not use it. Stopped: 3 tries (ternary, local free size with sizeof, local `Packet*`), no gain.
- LG/POD `FragmentPacketConcatenater::Add` 87.4: const 0x4 missing. Cause: the original has a dead `add rax,4` after `mov r9d,[rax+4]` and reads `packet->CurHeader` again in each branch. A single Log::Write exit gives 98.4 but no MATCH, so it is not kept. Stopped: 3 tries, no MATCH.
- LG `PacketConcatenateBuffer::Decompose(VarData*)` 95.2: const 0x2 missing. Cause: the original reads buffer and offset again after `++index` and does `add rax,2`; ours does CSE on the pointer (`lea rax,[r9+2]`). Stopped: 3 tries (pointer from `data->size`, `buffer + offset` two times, original form), same code.
- POD inlined `Packet::Allocate` pool slot (orig 0x28, ours 0x90): no funcdiff signal in this build (no const or call diff). ❓ It is a TLS or pool layout fact. Not tried: no signal to measure.
- LG/POD `FragmentPacketConcatenater::Clone` 93.3: not touched. It belongs to ehstate-4.
- `SessionSendBuffer::clearPacketBufferList` x4 84.9: out of scope. Cause: `RefCntHistory::add` is a call in the original and inline in ours (refcount code, not packet code).

## ❓
- Why does VS2010 do CSE on `&buffer[offset]` across the `index` store in `PacketConcatenateBuffer::Decompose(VarData*)` when the original does not? The source form of the original is not known.

## Blocked
- None.

Turns: 95
