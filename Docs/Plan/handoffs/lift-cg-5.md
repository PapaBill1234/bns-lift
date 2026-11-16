# lift-cg-5 handoff

## Done
- CacheGate app modules in `src/CacheGate/`: CacheGate, CacheD, CacheDChannel, ClientManager, CacheGateSessionHandler, CacheGateServerSideHandlerList.
- Common: `src/common/Session.cpp` (Session 0xDED0..0xFE90, Timer 0xDE80/0xDE90, ReconnectTimer 0xFF90/0xFFD0/0xFFE0), FragmentPacket.cpp, plus the deltas in Network, Daemon, SystemInformation, Port.h.
- CacheGate.exe links. Link fix: Session.cpp added, import libs advapi32 shell32 version user32 shlwapi, `src/crt/tlssup.c` (TLS directory), `src/crt/new_delete.c` (operator delete alias, the Wine msvcr100 lib has no `??3@YAXPEAX@Z`).

## Not done (stubs with TODO(lift-cg-5))
- PacketCrypt::Setup 0x327E0 (sets _MaxSize, returns SPCE_NO_ERROR).
- ZSTD_freeCDict 0x18380, ZSTD_createCCtx_advanced: `src/crt/zstd_stub.c`. vendor/zstd/src is missing.
- Daemon::cooldown, Daemon::FlushExtraLog (addresses ❓).
- Timer::preprocessExpireEvent, ReconnectTimer::TimerClass.
- Session::allocateCrypt (see LobbyGate 0x19460), returns nullptr.

## ❓
- Allocator Initialize args (2048, 0x248), `_timeout = 0`, recv param, ToPacket freeSize.
- tryReconnect arg 5000 at 0xEE90, crypt release path.
- Place of `s_initializedCount` and `PacketCrypt::_MaxSize`; DynamicEventObject::deallocate_me.

## BUG
- 0xEE90: the POSTPONE_CONNECTING branch is dead; the tryReconnect argument is not set.

## Toolchain (cmake/)
- `cmake/clangcl-wine.cmake`: `/Zc:tlsGuards-` added. Reason: link is /nodefaultlib, no CRT gives `__dyn_tls_on_demand_init` and `__tls_guard`.
- Note: a `build/` with an old CMakeCache keeps the old flags. Remove `build/CMakeCache.txt` once.

## Blocked
- IDA open failed (status 4). Lift used `.scratch/hr/` only.

## Gate result
- `tools/gate.sh`: gate ok.
