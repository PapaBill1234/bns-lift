# lift-lobbygate-4 handoff

## Done
- Modules in src/LobbyGate/: LobbyDPacketHandler, LobbyGate (with wmain), LobbyGatePacketHandler,
  PcCafeMileageFeverTimeScheduleList, WorldListManager, LobbyGatePredefine (Goods, GoodsItem),
  LobbyGateConfig (Dump and _Def table), ContentsRuleConfigDefinition. LinkStubs.cpp is new.
- BroadcastPacketCrypt in src/common/Security.cpp: 0x4CF60, 0x4DBA0, 0x4DBB0, 0x4DC00, 0x4DC20, 0x4DD70,
  0x4DF30, 0x4DF40. Layout with static_asserts in src/common/Security.h.
- CMake exe target `LobbyGate` (lift_exe) links. build/LobbyGate.exe is built.
- BnsCommonConfig _Def compare: the three tables (0x140092640, 0x140092780, 0x1400925f0) match
  src/common/BnsCommonConfig.cpp. No difference. The RVA comments in BnsCommonConfig.h are CacheGate RVAs.

## Not done (stub bodies, TODO(lift-lobbygate-4))
- compress2 ❓ 0x4DFE0 (src/common/Security.cpp): returns -2. zlib is not in the tree.
- ZSTD_compress_usingCDict 0x30AA0 (src/crt/zstd_stub.c): returns (size_t)-1. zstd is not in the tree.
- PacketCrypt::InstanceSize / PacketCrypt::Create (src/common/Session.cpp): PacketCrypt module, other card.
  allocateCrypt 0x19460 uses them.
- ClientSideDaemonChannel::onAccept (src/LobbyGate/LinkStubs.cpp): returns true ❓. No LobbyGate address
  (CacheGate 0x40B0). Channel.cpp emits the vftable, so the link needs a body.

## ❓
- BroadcastPacketCrypt member names and CompressFunc type name (no PDB type record).
- GradeInfo (0x20) and GradeLevelInfo (0x14) in LobbyDPacketHandler.cpp: no PDB module.
- BroadcastCrypt::Initialize args, OpenPort bools, AlertSender::init(...,0,0), SetMaxIdleTime(1,...),
  ClosePort(1), LobbyD::Hello args, TimerClass return 0, PipeConsole file string, addNode L"".
- LobbyGateConfig _Def: a127001 = 3276849, DEFAULT_TRUE (unnamed 0xFF bytes), alert default L"".
- allocateCrypt: real InstanceSize/Create signature.

## Blocked
- None.

## Gate result
- `gate ok`
