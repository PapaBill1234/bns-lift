# lift-parity-pod-5b handoff

## Result
- Status: partial. POD is at 700/759 (92.2 %). The goal is 722 (95 %).
- `tools/gate.sh`: gate ok. `tools/parity.sh`: parity ok. MATCH -> DIFF 0 and MATCH name gone 0 in all 5 exes.
- Branch `slice/lift-parity-pod-5b`. Not merged, not pushed.

| Exe | Main MATCH | Now | Gain | New MATCH |
| --- | --- | --- | --- | --- |
| CacheGate | 456 | 456 (92.9 %) | +0 | none |
| LobbyGate | 658 | 658 (89.0 %) | +0 | none |
| SmartCouponDaemon | 630 | 630 (94.2 %) | +0 | none |
| PostOfficeDaemon | 694 | 700 (92.2 %) | +6 | `ManagementSessionHandler::PacketHandler`, `AgentSessionHandler::OnClose`, `CachedWatchdogManager::updateWorldList`, `UnsentPostContextManager::updateWorldList`, `UnsentPostContextManager::initContextManager`, `PostInfo::CheckValidityPostData` |
| LobbyDaemon | 1024 | 1024 | +0 | none |

Total gain over main: +6.

## Changes
- `ManagementSessionHandler.cpp`: `PacketHandler` (0x10d00) uses the `goto $_ERROR` form. The PDB lines 61-69 and the label `$_ERROR` give this form. The handler call is the last statement.
- `AgentChannel.cpp`: `AgentSessionHandler::OnClose` (0x3820) reads `session->_id` at each use (A26). The order of the `_connectionType` and `_agentWid` reads follows the PDB lines 126-127.
- `CachedWatchdog.cpp`, `UnsentPostContext.cpp`: `updateWorldList` (0x4310, 0xcae0) and `initContextManager` (0xc6d0) use a local `AutoCS autoLock` (PDB name). There is no explicit `Leave`. In `updateWorldList` the lock is in an inner scope, so the success log comes after the leave. The `UNSENT_LOCK_*` macros are gone.
- `UnsentPostContext.cpp`: `initContextManager` tests `== nullptr` first, so line 169 (add failed) comes before line 174 (already exists).
- `WorldConfigManager.cpp`: `updateWorldList` (0xdb30) has no explicit `Leave` (score only, 80.2 -> 85.6). `loadWorldConfigFile` (0xe5f0) has an outer `if (library != nullptr)` with the line-251 block in the `else`. It calls `GetInterfaceVersion` only after the reader check, and the 279 block comes before the 283 block (score only, 94.3 -> 99.5).
- `WorldConfig.h`: `setupWorldConfigList` is a non-static member `(XmlDoc* const doc, WorldConfigList& worldConfigList)`. This follows the PDB type and the mangled name `?setupWorldConfigList@WorldConfigManager@@AEAA_NQEAVXmlDoc@@AEAVWorldConfigList@@@Z`. Score is the same.
- `PostContext.cpp`: `PostInfo::CheckValidityPostData` (0x11290) uses an if chain for the service types 1, 2 and 7, not a `switch`. The original has the consts 0x2 and 0x7.
- `PostOfficeDaemon.h`: the inline ctor sets the 11 manager pointers in the init list. It calls `memset` only for `_sessionHandler` (0x12ca0 stores them one by one). `wmain` 85.2 -> 88.9.
- `WorldPacketHandler.cpp`, `AgentPacketHandler.cpp`: the frees of `attachedItemList` use the `__delv_buf__` form (A16). This affects lines 469/486 and 321/338. Score only (95.6 -> 96.0, 98.0 -> 98.4).

## Unfixed DIFF functions in scope (function, signal, cause, why stopped)
- `PostOfficeDaemon::initialize` 67.8, calls+refs+consts: the original is patched. The jump at 0x133c9 goes from `fclose` to 0x134f0, so the block with `DaemonConfig::Dump`, `LoadBnsCommonConfig`, line 246 and `Sleep(3000)` is dead code in the original. If we lift dead code, we only fool funcdiff. Stopped (same class as SCD `SmartCouponDaemon::initialize`).
- `wmain` 88.9, consts (EH state -2) + miss `wmain$dtor$0`: the original has an unwind state for the daemon object around `BloodDaemonMain`. Ours has none. The cause is ❓ LTCG nothrow inference for the BloodLib `BloodDaemonMain` (`Daemon.h`, not in Files). All 4 `wmain` have the same DIFF. Stopped (out of file scope).
- `WorldConfigManager::updateWorldList` 85.6, calls+refs: ours inlines `Network::GetAddressStringW` at the 2 crash sites (`inet_ntoa`, `strcpy_s`, `MultiByteToWideChar`, `tls:__ip_addr_string_*`). The original calls it. The inline choice is in BloodLib `Network.h/.cpp` (not in Files). Stopped (out of file scope).
- `WorldConfigManager::loadWorldConfigFile` 99.5, refs: the original loads `L"15"` again for the line-263 log. Ours keeps it in `rbx`. One try (2 separate literals) had no change. Register allocation. Stopped.
- `WorldConfigManager::setupWorldConfigList` 98.6, refs: the original loads `L"world config manager"` again at lines 340, 348 and 352. Ours keeps it in `r14`. The member signature had no change. Register allocation. Stopped.
- `HandlePostOfficeServiceRegisterPostReq` 96.0, calls+refs+consts: the original `PushRepeatCount` returns `short` and is protected (`?PushRepeatCount@RepeatPacketDecomposer@@IEAAFPEBDH@Z`). Ours returns `int` (`QEAAH`, shared `PacketUtil.h`, not in Files). So ours compares `r13w`, and the line-355 and line-348 blocks are not cold. Ours also keeps `MODULE_NAME` in a register (14 more refs, const 0x20). Stopped (out of file scope).
- `HandlePostOfficeRegisterPostReq` 98.4, calls+refs+consts: same `PushRepeatCount` cause as above (block order, const 0x20). Stopped (out of file scope).
- `HandlePostOfficeHelloReq` 95.6, consts: the original keeps 15 and 10 in registers (`mov edx,0xf; lea r13d,[rdx-5]`, 95 = `rdx+0x50`). It also stores the `RefCntObject` `_ref` before `_tag` (shared BloodLib ctor). The swap to `connectionType != 1` first gave 97.8 and no MATCH, so it was undone. Register allocation and rematerialization. Stopped.
- `parseDecInt` 94.4 / `parseHexInt` 97.4, consts: these are in `src/Server/BloodLib/source/PacketBuffer.cpp`, not in `PostContext.cpp` as the card says. LTCG removes `if (str >= end) return -1`, and ours does not hoist 0x41/0x46. `__declspec(noinline)` had no change. Stopped (out of file scope).
- Stop list (not tried): `PingGenerator::sendPing` 99.2, `PostOfficeDaemon::checkCacheGateServiceState` 98.4.

## Lessons
### worked

| Function | Before | After | Count | Pattern |
| --- | --- | --- | --- | --- |
| `UnsentPostContextManager::updateWorldList`, `CachedWatchdogManager::updateWorldList` | 90.5, 95.5 | 100, 100 | 2 | Local `AutoCS autoLock` in an inner scope with no explicit `Leave`. One Lock.h line-122 assert per exit and EH state -2. An explicit `Leave` before the dtor adds a second assert block per exit. |
| `UnsentPostContextManager::initContextManager` | 92.9 | 100 | 1 | Same `AutoCS` form, and the PDB line order (169 before 174) gives `if (x == nullptr) { add } else { error }`. |
| `PostInfo::CheckValidityPostData` | 90.9 | 100 | 1 | A `switch` over 1, 2, 7 lowers to `dec`/`cmp 5`. An if chain gives the original consts 0x2 and 0x7. |
| `ManagementSessionHandler::PacketHandler` | 97.8 | 100 | 1 | `goto $_ERROR` form from the PDB label and lines 61-69. The handler call is at the end (A23). |
| `AgentSessionHandler::OnClose` | 97.6 | 100 | 1 | Read `session->_id` at each use. Field reads follow the PDB line order (A26). |
| `wmain` | 85.2 | 88.9 | 1 | The inline ctor sets each pointer member in the init list, not with one `memset`. |
| `WorldConfigManager::loadWorldConfigFile` | 94.3 | 99.5 | 1 | Outer `if (library != nullptr) {...} else { log 251 }`. The cold block comes after `FreeLibrary` (A2). |
| `WorldConfigManager::updateWorldList` | 80.2 | 85.6 | 1 | Remove the explicit `Leave` calls before `return`. |
| `HandlePostOfficeServiceRegisterPostReq`, `HandlePostOfficeRegisterPostReq` | 95.6, 98.0 | 96.0, 98.4 | 2 | `__delv_buf__ = p; Free(__delv_buf__, ...)` for the inlined `delete[]` (A16). |

### failed

| Function | Before | After | Count | Pattern |
| --- | --- | --- | --- | --- |
| `HandlePostOfficeHelloReq` | 95.6 | 97.8 (no MATCH, undone) | 1 | Swap the `connectionType` branches. The cause is register allocation. |
| `parseHexInt` / `parseDecInt` | 97.4 / 94.4 | same (undone) | 1 | `__declspec(noinline)` (out of file scope anyway). |
| `WorldConfigManager::loadWorldConfigFile` | 99.5 | 99.5 (undone) | 1 | Separate `L"15"` literals for the compare and the log. The compiler still uses one register. |
| `WorldConfigManager::setupWorldConfigList` | 98.6 | 98.6 (kept for the PDB signature) | 1 | Non-static member with a reference parameter. No codegen change. |

## pod-5b (lessons for the review)
The harness asked for a `## pod-5b` section in `Docs/Parity/lessons.md`. The card says not to edit `lessons.md`, because the round-5 cards run in parallel and the review merges the handoff lessons. So the section is here.
- A17 addition: a PDB local `AutoCS autoLock` with no explicit `Leave` gives EH state -2 and one Lock.h line-122 assert per exit. If the success path logs after the leave, put the lock in an inner scope. Do not use hand-inlined `Enter`/`Leave` macros, and do not use `Leave()` followed by the dtor.
- A switch over sparse small values (1, 2, 7) lowers to `dec`/`cmp`. An if chain keeps the compare consts.
- `PushRepeatCount` in the original returns `short` and is protected (`IEAAF`). The shared header has `int` and public. This is a candidate for lift-parity-shared (it touches LobbyDaemon users).
- `Network::GetAddressStringW` is inlined by LTCG in POD `WorldConfigManager::updateWorldList`. The original calls it. This is a shared BloodLib inline decision.
- POD `PostOfficeDaemon::initialize` is a patched original (jump at 0x133c9). Add it to the stop list.

Turns: 110
