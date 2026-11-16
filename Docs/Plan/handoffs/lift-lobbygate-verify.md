# Handoff: lift-lobbygate-verify

## Done
- `tools/verify/run_lobbygate.sh` (modes `original` / `lifted`, options `--peer`, `--client`, `--pktlog`).
- `tools/verify/pkl_stream.py`: LobbyD reply stream (cmd 2 HelloOk + cmd 4, 110 B).
- `tools/verify/compare_lobbygate.sh`: normalizes time, pointers, ports, hosts, worker id, PID, listen socket; diffs log, ports, peer, client and pkl output.
- `tools/verify/fixsrc_lobbygate.sh`: builds the lifted exe with the fix patch in `build/verify/lg-fixsrc`.
- `Docs/Verify/LobbyGate.md`: status PASS WITH THE FIX PATCH, differences 1-6, results table.
- `Docs/Verify/LobbyGate-fixes.patch`: 4 topics, 17 hunks:
  1. CryptoKey::Initialize 0x526E0 call in Network::Initialize 0x200D0.
  2. LobbyD::Hello 0x9BD0: Channel::MakeSession args.
  3. OpenPort purpose check (0x20500).
  4. PushRepeatCount offset in LobbyDPacketHandler (HelloOk 0xAF20, Decompose 0x1BC10).
- Result with the patch: ports, peer-lobbyd, client-client, client-internal and pkl are the same. The log is different only in the version string.

## Not done
- The fix patch is not applied to `src/` (this card may change only `tools/verify/` and `Docs/Verify/`). A follow-up lift card must apply it.
- Hunks 1 and 3 are not checked again with the CacheGate and SmartCouponDaemon verify runs.

## ❓
- MakeSession timeout and reconnect values in LobbyD::Hello 0x9BD0.
- Effect of hunks 1 and 3 on CacheGate and SmartCouponDaemon.
- Port 20900 (internal) does not open within 20 s in either exe.
- Extra log line `Connection.cpp,151 test, reconnect` before fix 4 (Difference 4).

## Blocked
- None. The lifted exe has no VERSIONINFO resource, so the version string is empty (same as SmartCouponDaemon).

## Gate result
- `tools/gate.sh`: gate ok (CacheGate, SmartCouponDaemon, LobbyGate, lift_selftest link).
