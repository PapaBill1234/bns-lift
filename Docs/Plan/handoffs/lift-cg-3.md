# lift-cg-3 handoff: CacheGate network, session, packet

## Done
- No lifted source. The earlier session decompiled all 13 modules to `.scratch/*.c` (git ignores it)
  and wrote the function list (`.scratch/funcs.txt`, 202 symbols). It did not write `src/common/` files.
- No change to `src/common/`, `CMakeLists.txt` or `include/vs2010/`.

## Not done (all functions; RVA ranges of the PDB symbols, without EH funclets at 0x3A4xx-0x3ACxx)
- FragmentPacket (16): 0x1000-0x1290 (SetFormat 0x1040, Clone 0x1220, ~SendFragmentPacketConcatenater 0x11C0).
- Packet (7): 0x6FE0-0x75B0 (Clear 0x6FF0, Add 0x7230, Concatenate 0x7300/0x7470, Decompose 0x75B0).
- PacketUtil (1): PacketFormatIterator::skipRepeatFormat 0x7700.
- Network (24): 0xCCD0-0xDA30 (Initialize 0xCEA0, Clear 0xCFD0, OpenPort 0xD2C0, initializeSocketInterface 0xDA30).
- Session (42): 0xDE80-0xFFE0 (HandleEvent 0xF1C0, handlePacket 0xF750, Connect 0xE570, Accept 0xE7C0).
- Channel (20): 0x10360-0x10B90 (MakeSession 0x10450, RemoveSession 0x10620, ClientSideDaemonChannel 0x10950).
- PacketBufferHandler (6): 0x11E00-0x11F50, AllocSize 0x35F80.
- PacketBuffer (13): 0x11F70-0x12BC0 (Compose 0x11FB0, Decompose 0x12320, PacketBufferAllocator::allocate 0x12BC0).
- Port (43): 0x18450-0x199B0 (SessionPool 0x184E0-0x18AD0, Port 0x18B70-0x195A0, deque<Session*> 0x19610-0x19880).
- IoWorkerThread (6): 0x199E0-0x19DD0 (IoWorker::run 0x19AC0).
- SessionBuffer (8): 0x1A310-0x1A980.
- Connection (7): 0x1AAE0-0x1B030.
- Listener (9): 0x31F60-0x32510 (PortListener::Initialize 0x31FD0, accept 0x32510).

## ❓
- None recorded.

## Blocked
- None. The earlier session stopped before it wrote source. The card must run again for the lift.

## Gate result
- Gate fix: the gate failed with "missing Docs/Plan/handoffs/lift-cg-3.md". This file is the fix.
- `tools/gate.sh`: `gate ok` (2026-11-15, after the handoff file was added; no source change).
