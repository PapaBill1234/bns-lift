# Handoff: lift-lobbydaemon-v2b-lg-01b (round 1)

Exe: LG (LobbyGate). Base: `6824f3d`. The driver builds and runs the proof. This session did no build.

## Lifted (source changes)

1. `LobbyGate::reload` (0x13770)
   - The time string uses the template `swprintf_s<128>` (2-argument form, array destination). The file now includes `crt_cpp_overload.h`.
   - The inlined `SetRunningInfo(L"bns common config reload succeed", nullptr)` uses `wcscmp` against the literal. The original has an inline `repe cmpsw` with count 33. The old lift called `wcsncmp`.
   - Both inlined list searches use the null-tested find form (same form as CacheD::Initialize, CacheGate 0x2430).
2. `LobbyGateReloadInvalidRestoreTimer::restoreInvalid` (0x127a0)
   - The list search uses the null-tested find form. The original tests the found node (`test r10, r10`).
   - The loop end reference (`bypassHandler` in the original, `HEX_PREFIXES` in the lift) is the symbol after `INVALID_REASON_STR`. That is data layout. The source cannot set it.
3. `LobbyGate::AddJobTimer` (0x12bf0)
   - Added the PDB constructor `ClientSessionTimerJob(unsigned long long, TimerReason)`. The old lift set the Timer fields a second time after the constructor.
   - One exit path (`if (_closeTimeout > 0) { ... }`), as in the original.
   - Open risk: the lift loads `LobbyGate::_instance` in the body. LTCG removed `this` because both callers use `_instance`. The original keeps `this` in `rcx`.
4. `ClientSessionTimerJob::HandleEvent` (0x6fa0)
   - Keeps `cliKey` in a local. Reads `LobbyGate::_instance->_clientManager` again for `RemoveClient`, as the original does.
   - Open risk: the original passes `edx = 0` to `Session::Close`. The lift does not (LTCG constant propagation into the shared callee). The original also has extra range compares (`cmp edx, 1` / `cmp edx, 3`). No source form was found for them.
5. `HandleLobbyGate_HelloReq` (0x14470)
   - The reply packet is constructed with separate field stores (no `= {}` memset).
   - Removed the explicit `reply.Clear()` calls. The destructor clears the packet. The original has one `Packet::Clear` call per exit. The old lift had two.

## Not done

- **`LobbyGate::initialize` (0x12e70)**. Cause: missing callee identity.
  - Line map: lobbygate.cpp:285 (0x12EDE-0x12FC3) is one call. The call gets the cert buffer, the fread count, `&dsnSize` (1024) and `&flag`. It returns an error code. Hex-Rays drops this call. `pdbq fn Cert` gives no function. The evidence cuts the call name.
  - Original order after the call: line 287 `memset(certFile, 0, strlen(certFile))` and line 288 `certFile = nullptr` run on every path. Line 290 logs `Cannot execute (%d)` only when the error code is not 0.
  - Line 294-296: when `flag & 1` and `Daemon::Instance+0x2b0 == 0`, it sets `+0x2b0 = +0x2dc` and calls `wcsncpy(Daemon::Instance+0x2b4, Daemon::Instance+0x2e0, 20)`.
  - Line 299-301: when `_config+0x6c == 0`, it sets `Daemon::Instance+0x740 = 0`.
  - Next step: get the callee name at 0x12EDE-0x12FC3 from the disassembly, then lift lines 285-301 in this order.
  - Forms tried: none.

## Files changed

- `src/Server/LobbyGate/LobbyGate.cpp`
- `src/Server/LobbyGate/Client.h`
- `src/Server/LobbyGate/Client.cpp`
- `src/Server/LobbyGate/LobbyGatePacketHandler.cpp`
- `Docs/Plan/handoffs/lift-lobbydaemon-v2b-lg-01b.md`
