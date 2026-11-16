# lift-lobbygate-1 handoff

## Done
- Port, Network, Channel, IdleWatcher, PacketUtil, Packet, PacketBuffer::CheckCompose,
  ClientPacketBufferHandler, Security, CrashHandler (13 functions). Session.h: 4 lines added.
- include/pdb/LobbyGate/ types. New .cpp files added to lift_common.

## Not done (Session.cpp not written; all pseudocode is in .scratch/Session.c, Session2.c, facts in .scratch/session-facts.md)
- Session (RVA): EventId 173D0, Session() 173E0, Session(portId,handler) 17480, ~Session 175A0, initialize 177E0,
  clear 179B0, Connect 17A70, Accept 17CE0, tryReconnect 17F60, reconnect 18160, Close 18350, close 183B0,
  Recv 185B0, recv 185F0, HandleEvent 186E0, HandleFailedEvent 18AF0, handlePacket 18C70, SetChannel 18E80,
  Send(fmt) 18ED0, Send(Packet) 18F00, SendV 18F60, SetPacketConcatenater 19110, deallocate_me 19250,
  sendNext 19290, send 19360, allocateCrypt 19460, deallocateCrypt 194C0, SetHandshakeParameter 19530,
  FailHandshake 19790, completeHandshake 197E0.
- ReconnectTimer: TimerClass/TimerId 27FC0, dtor 19890, HandleEvent 198D0.
- Session.h RVAs must change to the LobbyGate values. Connect has 4 params; check Port.cpp MakeNewSession.
- allocateCrypt needs PacketCrypt::InstanceSize 0x4CC60 / Create 0x4CCE0 declarations in PacketBuffer.h.
- BroadcastPacketCrypt bodies 0x4CF60, 0x4DBA0-0x4DF40: no card. Crypto::Create 0x55200, InstanceSize 0x55150: lift-lobbygate-2.

## ❓
- ClientPacketBufferHandler::Initialize: no address. CrashHandler::Initialize LTCG constants.
- TLS +16 ErrCode slot name. Session::initialize sendBuffer size arg is `id` (LTCG).

## BUG marks
- CrashHandler makeDirectory, MakeCrash, handleCrash. To add with Session: 0x19530 log 1381 misses `this`;
  close→tryReconnect arg uninitialized.

## Blocked: none.
## Gate result: `tools/gate.sh` prints gate ok.
- Fix: the gate failed because this handoff file was missing. Wrote this file; the build was already ok.
