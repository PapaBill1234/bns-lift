# LobbyGate verify (lift-lobbygate-verify)

Status: PASS WITH THE FIX PATCH. With `Docs/Verify/LobbyGate-fixes.patch` applied, the lifted exe gives the same ports, packets and packet log as the original. Only the version string in the log is different (Difference 2). Without the patch, the lifted exe crashes during start (Differences 1, 5, 6).

## How to run

| Step | Command |
|---|---|
| Original | `tools/verify/run_lobbygate.sh original 20 --peer --client --pktlog` |
| Lifted | `tools/verify/run_lobbygate.sh lifted 20 --peer --client --pktlog` |
| Output | `build/verify/lg-<kind>/` (log.txt, ports.txt, exit.txt, peer-lobbyd.txt, client-*.txt, pktlog/) |

Original exe: `Service_348_8349/Service/LobbyGate/bin/LobbyGate.exe` (not LobbyGate2019.exe).
Cert file `E:\Service\cert\Lobbygate.cfg`: placeholder text `keyhere`. initialize (0x12E70) only checks fread > 0.

## Reference behaviour (original, 20 s, --peer --client --pktlog)

- Log has 6 lines: Starting (version 0.0.348.527), Network Configuration,
  `Port.cpp,660 [session] created, port-id:2, session-id:200000001`,
  `Session.cpp,431 connect to ... 127.0.0.1, port:21801`,
  `LobbyDChannel.cpp,114 [channel] 0x0000000200000001, connect`,
  `LobbyDChannel.cpp,315 send, cmd:1, gate-wid:1, lobbylobbygatepacket-version:58, internal-port:20900`.
- Peer (LobbyDaemon, port 21801) gets 10 bytes: `0a00010001003a00a451`
  (len 10, cmd 1, wid 1, version 58, port 20900).
- No listen ports in 20 s. Ports 10900 and 20900 open only after a LobbyDaemon reply ❓.
  The clients get "connection refused". Exit code 124 (timeout).

## Differences

| # | Check | Original | Lifted | Function address |
|---|---|---|---|---|
| 1 | Start | Runs, connects to LobbyDaemon | ACCESS_VIOLATION rip=0 about 1 s after start, before the LobbyD connect | Network::Initialize 0x200D0 |
| 2 | Log line "Starting" | version 0.0.348.527 | empty version (no VERSIONINFO resource, same as SmartCouponDaemon) | - |
| 3 | Start after fix 1 | connects to LobbyDaemon | page fault in Channel::MakeSession (wrong args) | LobbyD::Hello 0x9BD0, Channel::MakeSession 0x21300 |
| 4 | Log after fixes 1+3 | 6 lines | 7 lines: extra `Connection.cpp,151 test, reconnect` ❓ | Connection::AsyncConnect 0x26FA0 |

### Difference 1: cause

- Stack (minidump + /MAP relink): `BroadcastPacketCrypt::GenerateKey` 0x4DC20 calls `_crypto->Setup`
  (Aes128::Setup 0x55050) → `Aes128::_Delegator.setup` is null → rip=0.
  Callers: `BroadcastCrypt::Initialize` 0x23000 ← `LobbyGate::initNetwork` ← `Daemon::start`.
- `Aes128::_Delegator` is filled only by `Crypto::Initialize` 0x550A0.
  In the original, `Network::Initialize` 0x200D0 sets `PacketCrypt::_MaxSize = 4000` and then calls
  `CryptoKey::Initialize` 0x526E0 (call at 0x201A5). CryptoKey::Initialize calls srand, Crypto::Initialize, Prng.
- The lifted `src/common/Network.cpp` (CacheGate shape, 0xCEA0) calls the stub `PacketCrypt::Setup(4000)`
  (`TODO(lift-cg-5)`), which does not call `CryptoKey::Initialize`.
- Fix (not applied; src/ is not in this card's Files): call `CryptoKey::Initialize()` in the lifted
  Network::Initialize (or in PacketCrypt::Setup) after `_MaxSize` is set.
  The fix is hunk 1 of `Docs/Verify/LobbyGate-fixes.patch`. The original ignores the result.
  CacheGate and SmartCouponDaemon also use this Network::Initialize. The extra call only fills the
  crypto tables (srand, Crypto::Initialize, Prng) ❓ check their runs again after the fix.

### Difference 3: crash in LobbyD::Hello (found after fix 1)

- Stack: rip in `Channel::MakeSession` +0x73 ← `LobbyD::Hello` 0x9BD0. Page fault read FFFFFFFFFFFFFFFF.
- In the LobbyGate exe, LTCG made `Channel::MakeSession` 0x21300 with args (this, ip, portNo).
  Port id 2 is a constant (reads `_port[1]`). The lifted Channel.cpp has the CacheGate shape
  (portId, ip, portNo, timeout, reconnect). Lifted `LobbyD::Hello` called `MakeSession(waitAck, portId, 0, 0, false)`,
  so portId = ip value → `_port[ip-1]` out of range.
- Fix: hunk 2 of the patch, `MakeSession(2, waitAck, portId, 0, false)` (timeout, reconnect ❓).

### Run after both fixes (`tools/verify/fixsrc_lobbygate.sh`, then run_lobbygate.sh lifted 20 --peer --client --pktlog)

- No crash. Exit 124 (timeout), same as the original. No listen ports (same as the original without a LobbyD reply).
- Peer bytes: `0a00010001003a00a451`, same as the original.
- Log: the same 6 lines (version empty, Difference 2) plus 1 extra line
  `Connection.cpp,151 [session], test, reconnect, this:..., addr:(127.0.0.1:<port>)`.
  Connection::AsyncConnect 0x26FA0 and makeConnectSocket 0x27350 have the same logic as the lifted code
  (pseudocode check). Cause of the extra line ❓ (maybe getsockname fails in the original). Log only, no packet change.

### LobbyDaemon reply stream

- The 381 LobbyGate capture `bns-wine/Logs/pktlog/LobbyGate-2272-20261112-234739.pkl` sends the same Hello
  (cmd 1, version 58). The LobbyDaemon replies cmd 2 (61 B, ack) and then cmd 4 (49 B) every 5 s.
  After cmd 2 the 381 gate listens on 10900.
- `tools/verify/pkl_stream.py <pkl> 21801 build/verify/lg-lobbyd.bin --count 2` writes these 2 packets (110 B).
  Use it as `LG_LOBBYD_STREAM`. Not yet run with the original or lifted exe.

## Difference 5: OpenPort purpose check (fix patch hunk 3)

- Original LobbyGate OpenPort 0x20500 accepts the purpose values 0 and 2. The call is at 0x13499 in initNetwork 0x13220.
- The lifted shared `src/common/Network.cpp` OpenPort has the CacheGate shape (it accepts 1 and 2). The lifted LobbyGate asserts at Network.cpp line 175 and port 10900 does not open.
- Fix: accept 0, 1 and 2. Effect on CacheGate and SmartCouponDaemon: not checked yet (❓).

## Difference 6: PushRepeatCount offset (fix patch hunk 4)

- `src/LobbyGate/LobbyDPacketHandler.cpp` calls `PushRepeatCount(pcb->buffer, pcb->size)` (12 calls). The original gives the buffer at the decomposer offset: `PushRepeatCount(&pcb->buffer[pcb->decomposer.offset], pcb->size - pcb->decomposer.offset)`.
- Symptom: HelloOk 0xAF20 → Decompose 0x1BC10 asserts at line 360.
- The same hunk changes the HelloOk log text for enablePcCafeMileage and Deposit to `== 1 ? L"yes" : L"no"`, as in the original.

## Compare results (lifted exe built with the fix patch)

Command: `LG_LIFTED_EXE=$PWD/build/verify/lg-fixsrc/build/LobbyGate.exe tools/verify/compare_lobbygate.sh 20 --pktlog`

| Check | Result |
|---|---|
| Exit code (20 s timeout) | 124 in both |
| Listen ports (ports.diff) | Same: 10900. Port 20900 does not open in 20 s in either exe (❓) |
| peer-lobbyd | Same: `0a00010001003a00a451` |
| client-client | Same: connect, 0 bytes |
| client-internal | Same: connection refused |
| pkl.diff | 0 lines |
| log.diff | Only the version string (`0.0.348.527` vs empty), Daemon.cpp lines 496 and 545. Both logs have 29 lines |

- The `Connection.cpp,151 test, reconnect` line is in both logs. It is not a difference.
- The lifted log shows HelloOk (worldCount:1, no/no) and "ready".
