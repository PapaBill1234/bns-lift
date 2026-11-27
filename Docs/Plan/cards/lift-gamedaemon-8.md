# lift-gamedaemon-8: BloodLib and Shared gaps: logserversessionhandler_cpp, logagentpackethandler, source_alertsender, daemonconfig, ...

| Item | Value |
| --- | --- |
| Exe | GD |
| Source build | GameDaemon 2019 + PDB (VS2010 SP1) |
| Exe file | `<work-root>/ida/lift/GameDaemon/GameDaemon.exe` |
| PDB | `<work-root>/ida/lift/GameDaemon/GameDaemon.pdb` |
| Pseudocode | `~/.cache/bns-lift/hr/GameDaemon/<stem>.c` |
| Pseudocode index | `~/.cache/bns-lift/hr/GameDaemon/index.tsv` (stem, rva, name, first, last, status, source file, part) |
| Wave | W1 |
| Model | opus |
| Depends on | `lift-gamedaemon-e12`, `lift-gamedaemon-12`, `lift-gamedaemon-33`, `lift-gamedaemon-9` |
| Pattern | `src/Server/BloodLib/source/Session.cpp` |
| Plan | `Docs/Plan/gamedaemon-lift.md` sections 1, 3, 5 |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Grep `Docs/Parity/lessons.md` for A2 (block order), A6 (per-exe path literals), A12 (PDB member types), A18 (destructors), A21 (PDB facts) and A22 (per-exe source form). Do not read it in full.
- Pattern: `src/Server/BloodLib/source/Session.cpp`. Read it one time. Use its form for the functions of this card.
- Dead-strip: `wmain` and most callers are still `LIFT_STUB` bodies. `/OPT:REF` removes a lifted function that has no live caller, and funcdiff then cannot pair it. For each function in scope with no live caller, add `#pragma comment(linker, "/INCLUDE:<public name>")` in its `.cpp` (public names: `llvm-pdbutil dump -publics`; grep `/INCLUDE` in `Docs/Parity/lessons.md`). Do not add a pragma for a function that a lifted caller keeps.

## Scope

22 functions, about 1,847 pseudocode lines (about 14,776 tokens). Stems: `logserversessionhandler_cpp`, `logagentpackethandler`, `source_alertsender`, `daemonconfig`, `source_network`, `stringutil`, `source_crashhandler`, `session`.

The easy functions of this stem are in `lift-gamedaemon-e12`. Do not change them unless a fix needs it.

| n | Exe | RVA | PDB name | Stem | Lines |
| ---: | --- | --- | --- | --- | ---: |
| 1 | GD | `0x6d9010` | `LogServerSessionHandler::HandleVersionNotifyPacket` | logserversessionhandler_cpp | 92 |
| 2 | GD | `0x6d91f0` | `LogServerSessionHandler::HandleInitAckPacket` | logserversessionhandler_cpp | 78 |
| 3 | GD | `0x6d9370` | `LogServerSessionHandler::HandlePingAckPacket` | logserversessionhandler_cpp | 32 |
| 4 | GD | `0x6d93f0` | `LogServerSessionHandler::HandleControlRequeryNotifyPacket` | logserversessionhandler_cpp | 55 |
| 5 | GD | `0x6d94e0` | `LogAgentPacketHandler::HandleLogdAckPacket` | logagentpackethandler | 111 |
| 6 | GD | `0x686a90` | `AlertSender::init` | source_alertsender | 72 |
| 7 | GD | `0x686c20` | `AlertSender::fini` | source_alertsender | 42 |
| 8 | GD | `0x68e9a0` | `DaemonConfig::Load` | daemonconfig | 159 |
| 9 | GD | `0x68edb0` | `DaemonConfig::Dump` | daemonconfig | 118 |
| 10 | GD | `0x68f1a0` | `Network::Initialize` | source_network | 50 |
| 11 | GD | `0x68f5d0` | `Network::OpenPort` | source_network | 130 |
| 12 | GD | `0x68f8e0` | `Network::OpenPort` | source_network | 32 |
| 13 | GD | `0x68ff90` | `Network::initWorkerThread` | source_network | 63 |
| 14 | GD | `0x6905a0` | `String::GetId128FromGuidString` | stringutil | 35 |
| 15 | GD | `0x696750` | `CrashHandler::Initialize` | source_crashhandler | 25 |
| 16 | GD | `0x6968d0` | `CrashHandler::SetLogPath` | source_crashhandler | 79 |
| 17 | GD | `0x697720` | `Session::~Session` | session | 102 |
| 18 | GD | `0x697b80` | `Session::Connect` | session | 178 |
| 19 | GD | `0x697f20` | `Session::Accept` | session | 118 |
| 20 | GD | `0x698920` | `Session::HandleEvent` | session | 178 |
| 21 | GD | `0x6992c0` | `Session::SendText` | session | 10 |
| 22 | GD | `0x6994a0` | `Session::SendTextV` | session | 88 |

### Shared functions

These functions are in shared source. They are not MATCH in each lifted exe that has them.

| PDB name | Shared file | Other exes | Note |
| --- | --- | --- | --- |
| `AlertSender::init` | `src/Server/BloodLib/source/AlertSender.cpp` | LobbyGate | - |
| `AlertSender::fini` | `src/Server/BloodLib/source/AlertSender.cpp` | CacheGate, LobbyDaemon, LobbyGate, PostOfficeDaemon, SmartCouponDaemon | - |
| `DaemonConfig::Load` | `src/Server/BloodLib/source/DaemonConfig.cpp` | CacheGate, LobbyDaemon, LobbyGate, PostOfficeDaemon, SmartCouponDaemon | EXCLUDED in LobbyDaemon: read its `excluded.tsv` row first |
| `DaemonConfig::Dump` | `src/Server/BloodLib/source/DaemonConfig.cpp` | CacheGate, LobbyDaemon, SmartCouponDaemon | - |
| `Network::Initialize` | `src/Server/BloodLib/source/Network.cpp` | CacheGate, LobbyDaemon, LobbyGate, PostOfficeDaemon, SmartCouponDaemon | - |
| `Network::OpenPort` | `src/Server/BloodLib/source/Network.cpp` | CacheGate, LobbyDaemon, LobbyGate, PostOfficeDaemon, SmartCouponDaemon | - |
| `Network::OpenPort` | `src/Server/BloodLib/source/Network.cpp` | CacheGate, LobbyDaemon, LobbyGate, PostOfficeDaemon, SmartCouponDaemon | - |
| `Network::initWorkerThread` | `src/Server/BloodLib/source/Network.cpp` | CacheGate, LobbyDaemon, LobbyGate, PostOfficeDaemon, SmartCouponDaemon | EXCLUDED in LobbyDaemon: read its `excluded.tsv` row first |
| `String::GetId128FromGuidString` | `src/Server/BloodLib/source/StringUtil.cpp` | CacheGate, LobbyDaemon, LobbyGate, PostOfficeDaemon, SmartCouponDaemon | EXCLUDED in LobbyDaemon: read its `excluded.tsv` row first |
| `CrashHandler::Initialize` | `src/Server/BloodLib/source/CrashHandler.cpp` | CacheGate, LobbyDaemon, LobbyGate, PostOfficeDaemon, SmartCouponDaemon | - |
| `CrashHandler::SetLogPath` | `src/Server/BloodLib/source/CrashHandler.cpp` | CacheGate, LobbyDaemon, LobbyGate, PostOfficeDaemon, SmartCouponDaemon | - |
| `Session::~Session` | `src/Server/BloodLib/source/Session.cpp` | CacheGate, LobbyDaemon, LobbyGate, PostOfficeDaemon, SmartCouponDaemon | EXCLUDED in LobbyDaemon: read its `excluded.tsv` row first |
| `Session::Connect` | `src/Server/BloodLib/source/Session.cpp` | CacheGate, LobbyDaemon, LobbyGate, PostOfficeDaemon, SmartCouponDaemon | - |
| `Session::Accept` | `src/Server/BloodLib/source/Session.cpp` | CacheGate, LobbyDaemon, LobbyGate, PostOfficeDaemon, SmartCouponDaemon | EXCLUDED in LobbyDaemon: read its `excluded.tsv` row first |
| `Session::HandleEvent` | `src/Server/BloodLib/source/Session.cpp` | CacheGate, LobbyDaemon, LobbyGate, PostOfficeDaemon, SmartCouponDaemon | - |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Shared functions: fix them in the shared file. If GameDaemon needs another form, use a per-exe copy in `lift_common_gd` or a `LIFT_EXE_` wrapper (A22, pattern 35). The 5 other exes must keep each MATCH. A MATCH to DIFF change needs an `allow-worse.txt` row with the counts.
6. An EXCLUDED function has a proof that no honest source fix exists in that exe. Read the proof first. If the same cause applies to GameDaemon, write the function under "Not done" with the proof reference. Do not edit `excluded.tsv`.
7. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/logserversessionhandler_cpp.cpp`
- `src/Server/GameDaemon/logserversessionhandler_cpp.h`
- `src/Server/GameDaemon/logagentpackethandler.cpp`
- `src/Server/GameDaemon/logagentpackethandler.h`
- `src/Server/BloodLib/source/AlertSender.cpp`
- `src/Server/BloodLib/source/DaemonConfig.cpp`
- `src/Server/BloodLib/source/Network.cpp`
- `src/Server/BloodLib/source/StringUtil.cpp`
- `src/Server/BloodLib/source/CrashHandler.cpp`
- `src/Server/GameDaemon/session.cpp`
- `src/Server/GameDaemon/session.h`
- `src/Server/BloodLib/source/Session.cpp`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-8.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
