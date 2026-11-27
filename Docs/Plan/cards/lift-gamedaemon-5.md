# lift-gamedaemon-5: BloodLib: logarchiveutil, logarchivesession, logserversessionhandler_h, logserver

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
| Depends on | `lift-gamedaemon-0e` |
| Pattern | `src/Server/BloodLib/source/LogFile.cpp` |
| Plan | `Docs/Plan/gamedaemon-lift.md` sections 1, 3, 5 |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Grep `Docs/Parity/lessons.md` for A2 (block order), A6 (per-exe path literals), A12 (PDB member types), A18 (destructors), A21 (PDB facts) and A22 (per-exe source form). Do not read it in full.
- Pattern: `src/Server/BloodLib/source/LogFile.cpp`. Read it one time. Use its form for the functions of this card.

## Scope

24 functions, about 2,060 pseudocode lines (about 16,480 tokens). Stems: `logarchiveutil`, `logarchivesession`, `logserversessionhandler_h`, `logserver`.

| n | Exe | RVA | PDB name | Stem | Lines |
| ---: | --- | --- | --- | --- | ---: |
| 1 | GD | `0x6b8130` | `LogArchiveUtil::GetUtf8StringSizeToTranslate` | logarchiveutil | 37 |
| 2 | GD | `0x6b81e0` | `LogArchiveUtil::UnicodeToMultibyte` | logarchiveutil | 46 |
| 3 | GD | `0x6b82e0` | `LogArchiveUtil::ComposeNetLogData` | logarchiveutil | 418 |
| 4 | GD | `0x6b8cf0` | `LogArchiveUtil::ConvertNetDataToFileData` | logarchiveutil | 577 |
| 5 | GD | `0x6b9af0` | `LogArchiveUtil::ReplaceOriginCharToSpecialChar` | logarchiveutil | 64 |
| 6 | GD | `0x6b9ba0` | `LogArchiveUtil::GetAlphabetCount` | logarchiveutil | 42 |
| 7 | GD | `0x6b9d00` | `LogArchiveSession::~LogArchiveSession` | logarchivesession | 20 |
| 8 | GD | `0x6b9d60` | `LogArchiveSession::Connect` | logarchivesession | 87 |
| 9 | GD | `0x6b9fd0` | `LogArchiveSession::Send` | logarchivesession | 86 |
| 10 | GD | `0x6ba1f0` | `LogArchiveSession::Recv` | logarchivesession | 40 |
| 11 | GD | `0x6ba300` | `LogArchiveSession::recv` | logarchivesession | 82 |
| 12 | GD | `0x6ba510` | `LogArchiveSession::Close` | logarchivesession | 19 |
| 13 | GD | `0x6ba560` | `LogServerSessionHandler::~LogServerSessionHandler` | logserversessionhandler_h | 7 |
| 14 | GD | `0x6ba5a0` | `LogServer::~LogServer` | logserver | 44 |
| 15 | GD | `0x6ba6b0` | `LogServer::Initialize` | logserver | 40 |
| 16 | GD | `0x6ba780` | `LogServer::Connect` | logserver | 7 |
| 17 | GD | `0x6ba7a0` | `LogServer::Close` | logserver | 41 |
| 18 | GD | `0x6ba870` | `LogServer::ClearLogData` | logserver | 31 |
| 19 | GD | `0x6ba900` | `LogServer::AsyncSend` | logserver | 102 |
| 20 | GD | `0x6bab30` | `LogServer::SendComplete` | logserver | 93 |
| 21 | GD | `0x6bad70` | `LogServer::RecvComplete` | logserver | 59 |
| 22 | GD | `0x6baf30` | `LogServer::waitComplete` | logserver | 48 |
| 23 | GD | `0x6bb020` | `LogServer::AsyncRecv` | logserver | 25 |
| 24 | GD | `0x6bb0a0` | `LogServer::HandlePacket` | logserver | 45 |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/logarchiveutil.cpp`
- `src/Server/GameDaemon/logarchiveutil.h`
- `src/Server/GameDaemon/logarchivesession.cpp`
- `src/Server/GameDaemon/logarchivesession.h`
- `src/Server/GameDaemon/logserversessionhandler_h.cpp`
- `src/Server/GameDaemon/logserversessionhandler_h.h`
- `src/Server/GameDaemon/logserver.cpp`
- `src/Server/GameDaemon/logserver.h`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-5.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
