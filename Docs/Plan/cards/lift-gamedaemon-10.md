# lift-gamedaemon-10: BloodLib and Shared gaps: logagent, listener, logarchivecontext, logserversessionhandler_cpp

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
| Depends on | `lift-gamedaemon-2`, `lift-gamedaemon-8` |
| Pattern | `src/Server/BloodLib/source/Listener.cpp` |
| Plan | `Docs/Plan/gamedaemon-lift.md` sections 1, 3, 5 |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Grep `Docs/Parity/lessons.md` for A2 (block order), A6 (per-exe path literals), A12 (PDB member types), A18 (destructors), A21 (PDB facts) and A22 (per-exe source form). Do not read it in full.
- Pattern: `src/Server/BloodLib/source/Listener.cpp`. Read it one time. Use its form for the functions of this card.

## Scope

25 functions, about 1,261 pseudocode lines (about 10,088 tokens). Stems: `logagent`, `listener`, `logarchivecontext`, `logserversessionhandler_cpp`.

| n | Exe | RVA | PDB name | Stem | Lines |
| ---: | --- | --- | --- | --- | ---: |
| 1 | GD | `0x6bb190` | `LogAgent::~LogAgent` | logagent | 21 |
| 2 | GD | `0x6bb200` | `LogAgent::HandlePacket` | logagent | 34 |
| 3 | GD | `0x6be0b0` | `PortListener::~PortListener` | listener | 18 |
| 4 | GD | `0x6be110` | `PortListener::Initialize` | listener | 90 |
| 5 | GD | `0x6be4a0` | `PortListener::HandleFailedEvent` | listener | 30 |
| 6 | GD | `0x6be530` | `PortListener::asyncAccept` | listener | 42 |
| 7 | GD | `0x6be650` | `PortListener::accept` | listener | 112 |
| 8 | GD | `0x6d8430` | `LogArchiveReadBuffer::LogArchiveReadBuffer` | logarchivecontext | 28 |
| 9 | GD | `0x6d84c0` | `LogArchiveReadBuffer::~LogArchiveReadBuffer` | logarchivecontext | 11 |
| 10 | GD | `0x6d84f0` | `LogArchiveReadBuffer::ClearBuffer` | logarchivecontext | 29 |
| 11 | GD | `0x6d8560` | `LogArchiveWriteBuffer::LogArchiveWriteBuffer` | logarchivecontext | 48 |
| 12 | GD | `0x6d8650` | `LogArchiveWriteBuffer::PushNetworkData` | logarchivecontext | 101 |
| 13 | GD | `0x6d8860` | `LogArchiveWriteBuffer::PushFileData` | logarchivecontext | 76 |
| 14 | GD | `0x6d89e0` | `LogArchiveWriteBuffer::ClearNetworkBuffer` | logarchivecontext | 42 |
| 15 | GD | `0x6d8aa0` | `LogArchiveWriteBuffer::ClearFileBuffer` | logarchivecontext | 37 |
| 16 | GD | `0x6d8b30` | `LogArchiveWriteBuffer::growBufferChunkSize` | logarchivecontext | 85 |
| 17 | GD | `0x6d8ca0` | `LogArchiveWriteBuffer::growBufferCount` | logarchivecontext | 68 |
| 18 | GD | `0x6d8de0` | `LogArchiveWriteContext::LogArchiveWriteContext` | logarchivecontext | 38 |
| 19 | GD | `0x6d8e80` | `LogArchiveWriteContext::~LogArchiveWriteContext` | logarchivecontext | 26 |
| 20 | GD | `0x6d8f20` | `LogArchiveWriteContext::SwitchStatus` | logarchivecontext | 34 |
| 21 | GD | `0x6d8fa0` | `LogArchiveWriteContext::GetWritingBuffer` | logarchivecontext | 34 |
| 22 | GD | `0x6d9010` | `LogServerSessionHandler::HandleVersionNotifyPacket` | logserversessionhandler_cpp | 92 |
| 23 | GD | `0x6d91f0` | `LogServerSessionHandler::HandleInitAckPacket` | logserversessionhandler_cpp | 78 |
| 24 | GD | `0x6d9370` | `LogServerSessionHandler::HandlePingAckPacket` | logserversessionhandler_cpp | 32 |
| 25 | GD | `0x6d93f0` | `LogServerSessionHandler::HandleControlRequeryNotifyPacket` | logserversessionhandler_cpp | 55 |

### Shared functions

These functions are in shared source. They are not MATCH in each lifted exe that has them.

| PDB name | Shared file | Other exes | Note |
| --- | --- | --- | --- |
| `PortListener::Initialize` | `src/Server/BloodLib/source/Listener.cpp` | CacheGate, LobbyDaemon, LobbyGate, PostOfficeDaemon, SmartCouponDaemon | EXCLUDED in LobbyDaemon: read its `excluded.tsv` row first |
| `PortListener::HandleFailedEvent` | `src/Server/BloodLib/source/Listener.cpp` | CacheGate, LobbyDaemon, LobbyGate, PostOfficeDaemon, SmartCouponDaemon | EXCLUDED in LobbyDaemon: read its `excluded.tsv` row first |
| `PortListener::asyncAccept` | `src/Server/BloodLib/source/Listener.cpp` | CacheGate, LobbyDaemon, LobbyGate, PostOfficeDaemon, SmartCouponDaemon | EXCLUDED in LobbyDaemon: read its `excluded.tsv` row first |
| `PortListener::accept` | `src/Server/BloodLib/source/Listener.cpp` | CacheGate, LobbyDaemon, LobbyGate, PostOfficeDaemon, SmartCouponDaemon | - |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Shared functions: fix them in the shared file. If GameDaemon needs another form, use a per-exe copy in `lift_common_gd` or a `LIFT_EXE_` wrapper (A22, pattern 35). The 5 other exes must keep each MATCH. A MATCH to DIFF change needs an `allow-worse.txt` row with the counts.
6. An EXCLUDED function has a proof that no honest source fix exists in that exe. Read the proof first. If the same cause applies to GameDaemon, write the function under "Not done" with the proof reference. Do not edit `excluded.tsv`.
7. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/logagent.cpp`
- `src/Server/GameDaemon/logagent.h`
- `src/Server/GameDaemon/listener.cpp`
- `src/Server/GameDaemon/listener.h`
- `src/Server/BloodLib/source/Listener.cpp`
- `src/Server/GameDaemon/logarchivecontext.cpp`
- `src/Server/GameDaemon/logarchivecontext.h`
- `src/Server/GameDaemon/logserversessionhandler_cpp.cpp`
- `src/Server/GameDaemon/logserversessionhandler_cpp.h`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-10.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
