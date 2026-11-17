# CacheGate verify (card lift-cg-verify)

Status: PASS. 2026-11-17: the fixes are in `src/`. The patch file and the fixsrc script are removed.
Before the fixes, the exe failed at start (0xc0000417 in `XmlReader_sv64.dll`, 0 log lines, no port).
With the 6 fixes, the lifted exe
starts, listens on 20800, and the packet log, peer bytes and client replies are the same as the original.
Only the version string in the log is different (no VERSIONINFO resource).

## How to run
| Command | Use |
| --- | --- |
| `tools/verify/run_cachegate.sh lifted\|original [SECONDS] [--pktlog] [--peer] [--client]` | Runs one exe under wine64 in its own prefix (`build/verify/wineprefix`). Output in `build/verify/<kind>/`: `log.txt`, `ports.txt`, `exit.txt`, `peer.txt`, `client.txt`, `wine.txt`, `pktlog/*.pkl`. |
| `tools/verify/compare_cachegate.sh [SECONDS] [--pktlog]` | Runs both kinds with `--peer --client`, writes `build/verify/compare/{log,ports,peer,client,pkl}.diff`. Exit 0 = no difference, 3 = no lifted exe. |
| `tools/verify/replay.py connect HOST:PORT\|listen PORT STREAM OUT` | Peer or client. Sends STREAM, records each received packet as `<ms> <len> <id> <hex>`. |

Self test: `CG_LIFTED_EXE=<original exe> tools/verify/compare_cachegate.sh 20 --pktlog` gives 0 changed lines in all 5 diffs.
To find a crash: run with `WINEDEBUG=+seh,+loaddll` and read `build/verify/lifted/wine.txt`.

## Run facts (found with the original exe)
- The exe must have a console window. Without one it starts in service mode and crashes (page fault).
  The script runs it in `wineconsole` on a hidden Xvfb display `:77`. Give the full Windows path of the exe.
- Paths from the config: `E:\Service\CacheGate\{bin,config}`, `E:\log\CacheGate\`. pktlog writes to
  `D:\Logs\pktlog\`. The script points E: and D: into `build/verify/<kind>/`.
- The exe stops at start if `config\cached-list.config.xml` is missing. With `--peer` the script sets its
  `ip-address` to 127.0.0.1, and `replay.py listen` is the CacheD peer on the economy port (20202).
- `exit.txt` = 124 is correct: the script stops the exe with SIGINT after SECONDS.

## Reference behaviour (original, 2019 + PDB, version 0.0.348.524)
- Listen port: 20800 (`public-port`). No other listen port.
- Log: 36 lines. Config dump, bns-common-config, CacheD session 200000001 connect,
  `[cg], cached connect, hello send, wid:1`, `network initialize ok.`, `start`.
- To CacheD (economy port) it sends one 10-byte hello: `0a 00 01 00 04 00 0a 00 01 00`.
- Client connect with no data: accept (session 100000001), `recv zero`, `on close, portid : 1`, remove. No bytes sent to the client.

## Noise (removed by compare_cachegate.sh)
- Time stamps, pointers, socket handles, local ports, the host name and addresses.
- `[worker], event object handle failed, id: N`: N changes from run to run.
- The order of `Cached channel connected` and the connect lines changes (threads). The log diff ignores line order.

## Checks (run 2026-11-16, `compare_cachegate.sh 20 --pktlog`)
| # | Check | Original | Lifted | Result |
| --- | --- | --- | --- | --- |
| 1 | Exe starts under wine64 | yes | crash 0xc0000417 in XmlReader_sv64.dll | FAIL |
| 2 | Startup log lines | 36 lines | 0 lines (log.diff 36) | FAIL |
| 3 | Listen ports | 20800 | none (ports.diff 1) | FAIL |
| 4 | Bytes to CacheD peer | 10 B hello | no connect (peer.diff 2) | FAIL |
| 5 | Client on 20800, no data | accept, recv zero, close | ConnectionRefused (client.diff 1) | FAIL |
| 6 | Packet log (`pkldump.py`) | 7 records | 0 records (pkl.diff 7) | FAIL |
| 7 | 381 CacheDaemon accepts the 2019 hello ❓ | not run | not run | open |

Checks with the fixed copy (`CG_LIFTED_EXE=$PWD/build/verify/fixsrc/build/CacheGate.exe`, run 2026-11-16):
| # | Check | Original | Lifted (fixed) | Result |
| --- | --- | --- | --- | --- |
| 1 | Exe starts under wine64 | yes | yes (exit 124 = stopped by script) | PASS |
| 2 | Startup log lines | 36 lines | 36 lines, log.diff 4 (version only) | PASS except version |
| 3 | Listen ports | 20800 | 20800 (ports.diff 0) | PASS |
| 4 | Bytes to CacheD peer | 10 B hello | same (peer.diff 0) | PASS |
| 5 | Client on 20800, no data | accept, recv zero, close | same (client.diff 0) | PASS |
| 6 | Packet log (`pkldump.py`) | 7 records | same (pkl.diff 0) | PASS |

## Differences
| Packet | Field | Original value | Lifted value | Function address |
| --- | --- | --- | --- | --- |
| - (config) | `CacheGateConfig::_Def` rows 2, 7, 10 (section headers): label is in `desc`, `name` = nullptr | `{-1, nullptr, 0, 0, nullptr, L"system configuration"}` (same for network, economy service) | label in `name`, `desc` = nullptr | data RVA 0x596c0; used by `CacheGate::initLog` 0x43f0 → `DaemonConfig::Load` 0xc600. Source: `src/CacheGate/CacheGate.cpp:39,48,51` |

| - (config) | `XmlConfigReader` vtable: `Initialize(XmlCfgDef const*, ...)` is slot 1 | `call [vtbl+8]` | `call [vtbl+0]` (slot 0, the `XmlCfgDef2` overload) → `_wcsicmp(NULL, "root-path")` crash in XmlReader | `DaemonConfig::Load` 0xc600. Source: `src/common/DaemonConfig.h:53-54`. Cause: the MSVC ABI puts overloads of a virtual function in reverse declaration order. Fix: declare the `XmlCfgDef` overload first. |
| - (cached list) | `_wtoi` argument after `wcsncmp(name, L"cached", 7)` | value of the attribute (original log: `CacheD.cpp,169 [cached list], connect, wid:1, ipAddress:127.0.0.1`) | NULL → `_wtoi(NULL)` → 0xc0000417 | lifted call ret 0x14000262b; source `src/CacheGate/CacheD.cpp:239,243` (`element->Attribute(L"wid")`, `L"economy-port"`); original pseudocode `.scratch/hr/CacheD.c:741,753`. Cause not found yet ❓ |
| - (cached list) | cause of the `_wtoi(NULL)` row above: `XmlElement::Attribute(wchar_t const*)` must be slot 8 (`call [vtbl+64]`, CacheD.c:758) | slot 8 | slot 6 (MSVC reverses overload groups) | `src/common/XmlReader.h`: declare each overload group in reverse (Attribute, ToXmlNode, ToXmlElement, ToXmlTextNode, XmlReader::Read, IsBinary). FIXED in test copy |
| - (client close) | `Session::EventId` return value | 3 (bytes `b8 03 00 00 00 c3` at 0xded0) | 0 → `[cg], unknown event object id, id: 0` (CacheGate.cpp 267), no `on close`, no session remove | `Session::EventId` 0xded0, `src/common/Session.cpp`. FIXED in test copy |
| - (refcount) | `RefCntObject` constructor | inlined `_ref = 1; _tag = 10; _history = nullptr` (Session::Session 0xdee0) | no constructor; `_ref` 0, then -1 after the decrement in `Session::Session` → `== CRASH == [ref obj] ... ref:-1, tag:0x0000070a` | `src/common/RefCntObject.h`. FIXED in test copy |
| - (log) | config dump tag | `[cachegate config]` | `[cacheGate]` | caller `CacheGate.cpp:171` must pass `L"cachegate config"` (LTCG constant in `DaemonConfig::Dump` 0xca10). FIXED in test copy |
| - (log) | version | `0.0.348.524` | empty | `Daemon::LoadVersion` reads the exe VERSIONINFO resource. The lifted exe has no `.rc`. OPEN |
| - (log) | extra line `[crash-mail], PrintMailInfo` | none | seen in an earlier run | Not seen in the last runs (log.diff 4). Closed ❓ |

All 6 fixes are in `src/` now.
All other `_Def` rows agree with the original table.

## Next steps
1. DONE: all 6 fixes are in `src/` (the `_Def` section rows are in `src/Server/Economy/CacheGate/CacheGate.cpp`).
2. Add a VERSIONINFO resource (FileVersion 0.0.348.524) to the CacheGate target.
3. Look for the same patterns in the other servers: overloaded virtuals declared in PDB order,
   `EventId` stubs that return 0 ❓, and classes with inlined base constructors.
4. Check 7 needs the 381 CacheDaemon (`bns-wine/`). Not run.
