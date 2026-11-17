# PostOfficeDaemon verify (card lift-postofficedaemon-verify)

Status (2026-11-17, done): the lifted exe of bd20e24 crashes (`Network.cpp,175 ASSERT CRASH`). With the fix patch
it runs and is the same as the original for ports, CacheGate peer bytes, client bytes and pkl, also with the Task 4
input streams. The log is the same except timing values (timer ticks, DB loading time).
2026-11-17 (parity-runtime): `.rc` VERSIONINFO added. The compare gives 0 changed lines in all diffs, also the log.

## How to run
| Command | Use |
| --- | --- |
| `POD_CERT=sql tools/verify/run_postofficedaemon.sh lifted\|original [SECONDS] [--pktlog] [--peer] [--client]` | Runs one exe under wine64 (prefix `build/verify/wineprefix`). Output in `build/verify/pod-<kind>/`: `log.txt`, `ports.txt`, `exit.txt`, `peer-cachegate.txt`, `client-{agent,world,manage}.txt`, `pktlog/*.pkl`. |
| `POD_LIFTED_EXE=<exe> POD_CERT=sql tools/verify/compare_postofficedaemon.sh [SECONDS] [--pktlog]` | Runs both, writes `build/verify/pod-compare/*.diff` (log sorted, ports, peer/client bytes, pkl sorted). Exit 0 = same. |

## Run facts (original, version 0.0.348.484)
- Same setup as SmartCouponDaemon: wineconsole on Xvfb `:77`, E: and D: in the run folder.
- Cert file `E:\Service\cert\Postofficed.cfg` = ODBC connection string (`PostOfficeDaemon::initialize` 0x132b0, fread max 1000 B).
  `POD_CERT=sql` uses `Database=PostOfficeDB` in Docker `bns-mssql`. The password is `keyhere` in all docs.
- `--peer` sets `cachegate-ip-address` and gamed `ip-address` to 127.0.0.1. `replay.py listen 20800` is the CacheGate peer.
- The exe connects to CacheGate (20800) and sends a hello (`cachegate-packet-version:4, economy-common-packet-version:10,
  postofficeServiceWid:0`). It does not connect to the GameDaemon (gamed-list = world config list, wid 1, port 20100).
- Listen ports: 30500 (manage, in `initNetwork`), 20500 agent and 20501 world (in `openListenPort`, after the DB load).
- Original, 25 s, `--peer --client --pktlog`: exit 124 (timeout, runs), 102 log lines, `service ready`, ports 20500 20501 30500.

## Checks
Lifted A = gate build of bd20e24. Lifted B = bd20e24 + fix patch (`fixsrc`). Runs: 25 s, `--peer --client --pktlog`, POD_CERT=sql, no input streams.
| # | Check | Original | Lifted A | Lifted B | Result (B) |
| --- | --- | --- | --- | --- | --- |
| 1 | Starts under wine64 | runs to timeout | ASSERT 175, 0xc000ffff | runs to timeout | pass |
| 2 | Listen ports | 20500 20501 30500 | 20500 20501 only | 20500 20501 30500 | pass |
| 3 | Log (sorted, normalized) | 102 lines | 15 lines | 102 lines; 4 diff lines `version:`, 2 lines timer tick | pass (only known diffs) |
| 4 | CacheGate peer bytes | `0a00010004000a000000` (hello) | - | same | pass |
| 5 | Client bytes agent/world/manage (connect, no send) | no reply | - | no reply | pass |
| 6 | pkl (`pkldump --kind pkt,sts,raw,sock`, sorted) | 13 lines | - | same | pass |
| 7 | Self test (original vs original) | - | - | log 0, ports 0, bytes 0; pkl 8 lines before the norm fix | noise: socket handle, listen handle, accept order (masked in compare script) |
| 8 | Input streams (Task 4), `pod_streams.py`, B with the final norm | see below | - | same | pass |
| 8a | CacheGate HelloOk `04000200` | log `HandleCacheGateHelloOk; hello success`; then 48 B to CacheGate `3000 0400 ...` (relay) | - | same bytes | pass |
| 8b | Agent hello `0d0001000f000a000a00010000` | log `sent hello success ack, agentWid:1, connectionType:0`; reply `04000200` | - | same | pass |
| 8c | World hello `1000010010000a0001007f000001844e` | log `sent hello success ack, wid:1`; reply `04000200` | - | same | pass |
| 8d | Manage text `0500` + UTF-16 `Hello` | accept and close log only, no reply | - | same | pass (❓ the stream can be a wrong command format; both exes act the same) |
| 9 | pkl with streams (`listen=` handle masked) | - | - | 0 diff lines | pass |

## Differences
| Item | Original | Lifted | Function |
| --- | --- | --- | --- |
| OpenPort of manage port (purpose 3) | accepts purpose 2 or 3 | lift calls CacheGate `Network::OpenPort` 0xD2C0, accepts 1 or 2 only: ASSERT 175 | `Network::OpenPort` 0x28AB0, `PostOfficeDaemon::initNetwork` |
| OpenPort args | 8 args: portId, portNo, purpose, handler, bufferHandler, maxSession, autoOpen, nagle; always `_enableRecv = true` | 9 args, ports 2/3 get enableRecv false | 0x28AB0 |
| Log tag of CacheGateSessionHandler | `[cachegate channel]` | `[cachegate session handler]` | CacheGateChannel.cpp (OnConnect lines 242, 261) |
| Function name in WorldConfigManager logs | `WorldConfigManager::setupWorldConfigList` (also `loadWorldConfigFile`, `addWorldConfig`) | name without class | WorldConfigManager.cpp lines 150, 283, 352 |
| `version:` | 0.0.348.484 | FIXED: `PostOfficeDaemon.rc` | Daemon.cpp 496/545 |
| Timer tick count of RelayTimeoutChecker | n | n-1 in one run | timing only, not a code difference |
| `database loading time` | 0sec | 1sec in one run | timing only (`loadAllUnsentPostFromDB`, PostOfficeDaemon.cpp 502) |
| Other tags/names (static check: lifted `L"..."` names not in exe strings) | `cachegate channel` for CacheGateChannelManager too; `CacheGateChannel::composeRelayHeader`, `::combineFragmentRelayFormat`; all 12 WorldConfigManager names with `WorldConfigManager::` | short names, tags `cachegate session handler` / `cachegate channel manager` | CacheGateChannel.cpp, WorldConfigManager.cpp |

## Fixes (in `src/`)
- 2026-11-17: the fixes are in `src/`. The patch file and the fixsrc script are removed.
- Adds `Network::OpenPort` 0x28AB0 (8 params) to src/common, and changes the 4 calls in `initNetwork`.
  Table 0x87D68 = {10000, 10000, 16, 16} (= `s_defaultMaxSession`). Call args from the pseudocode: port 1 (true, false),
  ports 2/3 (false, false), port 4 (true, true). `Port::Initialize` 0x361D0 is the same as the lifted one.
- The log text differences above (tags and class prefixes) are fixed in `src/`.
- `Network::OpenPort` in `src/` now has 9 params (nagle last). This replaces the 8-param form of the old patch.

## Input facts for Task 4 (streams: `python3 -I tools/verify/pod_streams.py`, run done)
- Packet = u16 size (includes the size field), u16 cmd, body. CacheGate ids: 1 Hello, 2 HelloOk, 3 HelloFail ("hE").
  HelloOk stream: `04000200`.
- Agent port 20500, cmd 1 `HandlePostOfficeHelloReq` "hhhhhQ": cmd, postofficePacketVersion=15, agentPacketVersion,
  economyCommon=10, agentWid, connectionType (0/1). World port 20501, cmd 1 `HandlePostOfficeServiceHelloReq`
  "hhhhih": cmd, serviceVersion=16, economyCommon>0, wid!=0, ipAddress!=0, portNo.
- Manage port 30500: text packet, `DecomposeText("s")`, UTF-16 words after the u16 size (size counts wchar: `DecomposeText` 0x2FAB0 end = buffer + 2 + 2*size); command "Hello".
