# Handoff: lift-lobbydaemon-v2b-scd-01a (round 1)

The author did not build. The driver builds and runs the proof.

## Changes

1. SCD 0x2c80 `GameEventConfig::SetupGameEventListFromXml`
   - The event loop is now inside `if (root != nullptr)`. The function has one shared `return true`.
   - A new inline helper `findDaemonType` gives the daemon type. It gives 0 for an unknown name. The caller tests only `daemonType != 0`. This removes the extra `cmp 2; jae`.
   - The `_wcsicmp(L"true", enable)` call now comes before the `daemonType` store (orig store order).
   - Not changed: the own `NextElement` call after the 137 log. Lesson scd-4 has 4 failed tries.
2. SCD 0x1180 `ObjPool::ObjPool`
   - `ObjPool::Stack` and `ObjPool::Queue` now have the inline ctors in SCD too (the SCD PDB has `Stack::Stack` and `Queue::Queue`). The members are made in member order: `_pool`, `_lock`, `_wait`, `_waitlock`. The ctor body is empty.
3. SCD 0x1490 `ObjPool::Finalize`
   - The loop is now `for (;;)` with a load, a null test and a `break` (orig has one test and a `jmp` back).
   - The next node is read before `--_pool._size` (orig order).
4. SCD 0x53d0 `NPChannel::SendMsg`
   - The loop calls `Packet::Add` (orig inlines it with the line 287 assert and the `CrashHandler::MakeCrash` call).
   - The loop steps `buffer.pData` and `buffer.nLen` itself (orig reloads `buffer.nLen`).
   - The explicit `p.Clear()` is removed. `~Packet` calls `Clear` once (orig has one call).
5. SCD 0x7dc0 `HandleSmartCoupon_HelloReq`
   - The `DChannel` block reads port and addr first, then sets the id. The null value is set in an own `else` block.
   - Not changed: the orig keeps the constant 1 in a callee-saved register and returns it with `movzx eax, s4b`. The orig does not tail-merge the `Send` of the version-fail path. This is register allocation. No source form is known.
6. SCD 0x1a0d0 `DaemonConfig::Dump` (shared by CG and SCD)
   - Each case reads `base + def.offset` again. The lift had one field pointer before the switch (orig reloads `[s1 - 8]` in each case).
   - The IP case puts the "N/A" path first.

## Not done (left differences)

- 0x1a0d0 `DaemonConfig::Dump`: the jump table ref. The orig has `lea s6, [??_R0?AVNIC@@@8+0x8]` and table offset 0x1a334. The lift has `[_fltused]` and 0x11cd0. Cause: data layout. The nearest data symbol differs because we build with `/GR-` (console-4). No source change can fix it.
- 0x2c80 `SetupGameEventListFromXml`: if the 137 block `NextElement` call stays merged, the cause is the VS2010 tail merge (lesson scd-4, 4 tries).
- 0x7dc0 `HandleSmartCoupon_HelloReq`: if the `movzx eax, s4b` return and the `lea r8d, [s4 + 0x2f]` constants stay, the cause is register allocation (constant 1 in a callee-saved register).

## Risk

- `ObjectPool.h` `Stack` and `Queue` ctors are now in all builds. LD already used them.
- `NPChannel2.cpp` and `DaemonConfig.cpp` are shared files. Check the other exes in the proof.

## Changed files

- `src/Server/LobbyDaemon/ObjectPool.h`
- `src/Server/LobbyDaemon/ObjectPool.cpp`
- `src/Server/Shared/CouponGameEventConfig.cpp`
- `src/Server/Shared/NPChannel2.cpp`
- `src/Server/SmartCouponDaemon/DaemonPacketHandler.cpp`
- `src/Server/BloodLib/source/DaemonConfig.cpp`
- `Docs/Plan/handoffs/lift-lobbydaemon-v2b-scd-01a.md`
