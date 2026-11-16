# lift-cg-3 handoff: CacheGate network, session, packet

## Done (all in CMake target `lift_common`)
- Connection 0x1AAE0-0x1B030, SessionBuffer 0x1A310-0x1A980, PacketBufferHandler 0x11E00-0x11F50.
- Listener 0x31F60-0x32510, IoWorkerThread 0x199E0-0x19DD0, Channel 0x103C0-0x10B90.
- Network 0xCD70-0xDA30, Port 0x184E0-0x195A0 (SessionPool in Port.h). Session.h, IdleWatcher.h (declarations).
- BUG: 0xCFD0 _workerThreads not freed; Instance/EndEventObject not released, no WSACleanup.
  0xD760 leak when WSAStartup fails. 0x19010 session leaks if out ptr is null.
- Toolchain: Wine headers lack `InterlockedExchange64`; code uses `_InterlockedExchange64` + `<intrin.h>`.

## Not done
- Session (src/common/Session.cpp not written): 0xDE80, 0xDEE0, 0xDF80, 0xE0A0, 0xE2E0, 0xE4B0, 0xE570, 0xE7C0,
  0xEA40, 0xEC40, 0xEE30, 0xEE90, 0xF090, 0xF0D0, 0xF1C0, 0xF5D0, 0xF750, 0xF960, 0xF9B0, 0xFA10, 0xFA40,
  0xFAA0, 0xFC40, 0xFD80, 0xFDC0, 0xFE90; ReconnectTimer 0xFF90, 0xFFD0, 0xFFE0. IdleStateTable::STATE_MASK.
- FragmentPacket 0x1000-0x1290; PacketUtil skipRepeatFormat 0x7700; Packet 0x6FF0, 0x7230, 0x7300, 0x7470.
- PacketBuffer 0x11F70-0x12BC0 (only PacketBuffer.h changed).

## ❓
- LTCG folded constants: Port _nagle, SessionPool readOnly, TimerQueue::Add elapse 5000, SendBuffer freeSize 0x800,
  Connect timeout/nagle/reconnect, StaticPageMemoryManager::Initialize args (0x800, 0x248).
- handlePacket ToPacket size/freeSize args; Send(Packet) and send() count args (1 and 5).
- SessionSendBuffer::Clear order 0x1A750; SessionHandler/IdleWatcher have no PDB module;
  ClientSideDaemonChannel::onAccept 0x40B0 declared only; PacketCrypt::Setup, s_initializedCount external.

## Blocked
- None.

## Gate result
- Gate fix: the gate failed with "missing Docs/Plan/handoffs/lift-cg-3.md". This file now has the current state.
- `tools/gate.sh`: `gate ok` (2026-11-16).
