# lift-cg-5 handoff: CacheGate app, full exe

## Done
- Decompile of all six modules to `.scratch/` (CacheGate.c, CacheD.c, CacheDChannel.c,
  CacheGateSessionHandler.c, ClientManager.c, wcrtexe.c). Git ignores `.scratch/`.
- PDB layouts and mangled names of all called library functions are collected. No source is written.
- No change to `src/`, `CMakeLists.txt` or `include/`.

## Not done (all functions of the card)
- CacheGate: 0x4050-0x40A0 (names, timer), 0x4270/0x4290 dtor, 0x43F0 initLog, 0x4510 initialize,
  0x4770 initNetwork, 0x4930 shutdown, 0x4970 reload, 0x4B40 FailedEventObjectHandler, 0x4B90 PrintDependency.
- CacheD and CacheDList: 0x23A0-0x3B80.
- CacheDChannel: 0x3C40/0x3C70 dtor, 0x3C80 onConnect, 0x3E40 onClose.
- CacheGateSessionHandler: 0x4150 PacketHandler, 0x4C00 Hello, 0x4F20 HelloOk, 0x5040 HelloFail,
  0x51C0 Relay, 0x57A0 RelayFail, 0x5880 FragmentRelay.
- ClientManager: 0x5D60 dtor, 0x5E90 Initialize, 0x6050 GetSession, 0x6120 AddSession,
  0x6250 ReleaseSession, 0x6380 ReleaseAllSession.
- CacheGateServerSideHandlerList: data at 0x592D0. CacheGateConfig::_Def at 0x596C0.
- Wide CRT entry (wmainCRTStartup with __wgetmainargs) in `src/crt/`. CMake target `CacheGate`.

## ❓
- None recorded.

## Blocked
- The Bash tool is denied in this session ("don't ask" mode). I cannot run `tools/gate.sh`,
  cmake or the compiler. The card needs a gate run after each module, so I stopped before I wrote code.
- The exe link also needs the lift-cg-3 modules (Session, Channel, Port, Packet, Network), which are
  not lifted. Without them the link needs many stub bodies.

## Gate result
- Not run (Bash denied).
