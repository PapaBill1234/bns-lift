# lift-gamedaemon-5: BloodLib: logarchivesession, logserver, logagent, logarchivecontext

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
| Depends on | `lift-gamedaemon-e25`, `lift-gamedaemon-e45` |
| Pattern | `src/Server/BloodLib/source/LogFile.cpp` |
| Plan | `Docs/Plan/gamedaemon-lift.md` sections 1, 3, 5 |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Grep `Docs/Parity/lessons.md` for A2 (block order), A6 (per-exe path literals), A12 (PDB member types), A18 (destructors), A21 (PDB facts) and A22 (per-exe source form). Do not read it in full.
- Pattern: `src/Server/BloodLib/source/LogFile.cpp`. Read it one time. Use its form for the functions of this card.
- Dead-strip: `wmain` and most callers are still `LIFT_STUB` bodies. `/OPT:REF` removes a lifted function that has no live caller, and funcdiff then cannot pair it. For each function in scope with no live caller, add `#pragma comment(linker, "/INCLUDE:<public name>")` in its `.cpp` (public names: `llvm-pdbutil dump -publics`; grep `/INCLUDE` in `Docs/Parity/lessons.md`). Do not add a pragma for a function that a lifted caller keeps.

## Scope

25 functions, about 1,402 pseudocode lines (about 11,216 tokens). Stems: `logarchivesession`, `logserver`, `logagent`, `logarchivecontext`.

The easy functions of this stem are in `lift-gamedaemon-e25`, `lift-gamedaemon-e45`. Do not change them unless a fix needs it.

| n | Exe | RVA | PDB name | Stem | Lines |
| ---: | --- | --- | --- | --- | ---: |
| 1 | GD | `0x6b9d60` | `LogArchiveSession::Connect` | logarchivesession | 87 |
| 2 | GD | `0x6b9fd0` | `LogArchiveSession::Send` | logarchivesession | 86 |
| 3 | GD | `0x6ba1f0` | `LogArchiveSession::Recv` | logarchivesession | 40 |
| 4 | GD | `0x6ba300` | `LogArchiveSession::recv` | logarchivesession | 82 |
| 5 | GD | `0x6ba5a0` | `LogServer::~LogServer` | logserver | 44 |
| 6 | GD | `0x6ba6b0` | `LogServer::Initialize` | logserver | 40 |
| 7 | GD | `0x6ba780` | `LogServer::Connect` | logserver | 7 |
| 8 | GD | `0x6ba7a0` | `LogServer::Close` | logserver | 41 |
| 9 | GD | `0x6ba870` | `LogServer::ClearLogData` | logserver | 31 |
| 10 | GD | `0x6ba900` | `LogServer::AsyncSend` | logserver | 102 |
| 11 | GD | `0x6bab30` | `LogServer::SendComplete` | logserver | 93 |
| 12 | GD | `0x6bad70` | `LogServer::RecvComplete` | logserver | 59 |
| 13 | GD | `0x6baf30` | `LogServer::waitComplete` | logserver | 48 |
| 14 | GD | `0x6bb0a0` | `LogServer::HandlePacket` | logserver | 45 |
| 15 | GD | `0x6bb200` | `LogAgent::HandlePacket` | logagent | 34 |
| 16 | GD | `0x6d8560` | `LogArchiveWriteBuffer::LogArchiveWriteBuffer` | logarchivecontext | 48 |
| 17 | GD | `0x6d8650` | `LogArchiveWriteBuffer::PushNetworkData` | logarchivecontext | 101 |
| 18 | GD | `0x6d8860` | `LogArchiveWriteBuffer::PushFileData` | logarchivecontext | 76 |
| 19 | GD | `0x6d89e0` | `LogArchiveWriteBuffer::ClearNetworkBuffer` | logarchivecontext | 42 |
| 20 | GD | `0x6d8aa0` | `LogArchiveWriteBuffer::ClearFileBuffer` | logarchivecontext | 37 |
| 21 | GD | `0x6d8b30` | `LogArchiveWriteBuffer::growBufferChunkSize` | logarchivecontext | 85 |
| 22 | GD | `0x6d8ca0` | `LogArchiveWriteBuffer::growBufferCount` | logarchivecontext | 68 |
| 23 | GD | `0x6d8de0` | `LogArchiveWriteContext::LogArchiveWriteContext` | logarchivecontext | 38 |
| 24 | GD | `0x6d8f20` | `LogArchiveWriteContext::SwitchStatus` | logarchivecontext | 34 |
| 25 | GD | `0x6d8fa0` | `LogArchiveWriteContext::GetWritingBuffer` | logarchivecontext | 34 |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/logarchivesession.cpp`
- `src/Server/GameDaemon/logarchivesession.h`
- `src/Server/GameDaemon/logserver.cpp`
- `src/Server/GameDaemon/logserver.h`
- `src/Server/GameDaemon/logagent.cpp`
- `src/Server/GameDaemon/logagent.h`
- `src/Server/GameDaemon/logarchivecontext.cpp`
- `src/Server/GameDaemon/logarchivecontext.h`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-5.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
