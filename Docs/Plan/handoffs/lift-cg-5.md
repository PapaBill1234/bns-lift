# lift-cg-5 handoff: CacheGate app, full exe

## Done
- Decompile of all six modules to `.scratch/` (git ignores it). All CacheD.c pseudocode is read.
- `src/CacheGate/CacheD.h`: `CacheD::Initialize` has 4th param `char status` (PDB `?Initialize@CacheD@@QEAAXGKGD@Z`).
- Verified facts for the next session are in `lift-cg-5-progress.md`. No `.cpp` is written yet.

## Not done (all functions of the card)
- CacheGate: 0x4050-0x40A0 (names, timer), 0x4180 main, 0x4270/0x4290 dtor, 0x43F0 initLog, 0x4510 initialize,
  0x4770 initNetwork, 0x4930 shutdown, 0x4970 reload, 0x4B40 FailedEventObjectHandler, 0x4B90 PrintDependency.
- CacheD and CacheDList: 0x23A0-0x3B80.
- CacheDChannel: 0x3C40/0x3C70 dtor, 0x3C80 onConnect, 0x3E40 onClose, 0x40B0 onAccept.
- CacheGateSessionHandler: 0x4150 PacketHandler, 0x4C00 Hello, 0x4F20 HelloOk, 0x5040 HelloFail,
  0x51C0 Relay, 0x57A0 RelayFail, 0x5880 FragmentRelay.
- ClientManager: 0x5D60 dtor, 0x5E90 Initialize, 0x6050 GetSession, 0x6120 AddSession,
  0x6250 ReleaseSession, 0x6380 ReleaseAllSession.
- CacheGateServerSideHandlerList: data at 0x592D0. CacheGateConfig::_Def at 0x596C0.
- Wide CRT entry (wmainCRTStartup) in `src/crt/`. CMake target `CacheGate` is not added.

## ❓
- `CacheGate::_instance` (0x5A3E0) is private static: lifted code needs `friend` (not in PDB).
- PacketHandler reads the command at `CurHeader + 2`. Hello error codes (dis 0x4C00) are not read.

## Blocked
- None. The work stopped at the stage limit.

## Gate result
- `tools/gate.sh`: gate ok (only `CacheD.h` changed; the exe target is not in CMake yet).
- Fix: the gate failed because this handoff was the old one from commit 040fe32. It now shows the current state.
