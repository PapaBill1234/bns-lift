# lift-gamedaemon-12: BloodLib: source_logarchive, stringbuilder, source_logfile, source_lognetwork

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
| Depends on | `lift-gamedaemon-2`, `lift-gamedaemon-8`, `lift-gamedaemon-11` |
| Pattern | `src/Server/BloodLib/source/LogFile.cpp` |
| Plan | `Docs/Plan/gamedaemon-lift.md` sections 1, 3, 5 |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Grep `Docs/Parity/lessons.md` for A2 (block order), A6 (per-exe path literals), A12 (PDB member types), A18 (destructors), A21 (PDB facts) and A22 (per-exe source form). Do not read it in full.
- Pattern: `src/Server/BloodLib/source/LogFile.cpp`. Read it one time. Use its form for the functions of this card.

## Scope

27 functions, about 1,638 pseudocode lines (about 13,104 tokens). Stems: `source_logarchive`, `stringbuilder`, `source_logfile`, `source_lognetwork`.

| n | Exe | RVA | PDB name | Stem | Lines |
| ---: | --- | --- | --- | --- | ---: |
| 1 | GD | `0x694070` | `LogArchive::LogArchive` | source_logarchive | 105 |
| 2 | GD | `0x6942d0` | `LogArchive::~LogArchive` | source_logarchive | 79 |
| 3 | GD | `0x6944f0` | `LogArchive::Initialize` | source_logarchive | 111 |
| 4 | GD | `0x694730` | `LogArchive::Start` | source_logarchive | 43 |
| 5 | GD | `0x694810` | `LogArchive::Write` | source_logarchive | 57 |
| 6 | GD | `0x694980` | `LogArchive::run` | source_logarchive | 85 |
| 7 | GD | `0x694b90` | `LogArchive::AccessLogServer` | source_logarchive | 156 |
| 8 | GD | `0x695070` | `LogArchive::IsUnsentFileExist` | source_logarchive | 25 |
| 9 | GD | `0x695150` | `LogArchive::ChangeFileMode` | source_logarchive | 32 |
| 10 | GD | `0x6951e0` | `LogArchive::constructEventArray` | source_logarchive | 56 |
| 11 | GD | `0x6952f0` | `LogArchive::processTimeout` | source_logarchive | 29 |
| 12 | GD | `0x6953d0` | `LogArchive::processEventInFileMode` | source_logarchive | 35 |
| 13 | GD | `0x6954a0` | `LogArchive::processEventInNetMode` | source_logarchive | 30 |
| 14 | GD | `0x695530` | `LogArchive::flush` | source_logarchive | 27 |
| 15 | GD | `0x6955b0` | `LogArchive::write` | source_logarchive | 31 |
| 16 | GD | `0x695610` | `LogArchive::pushLogData` | source_logarchive | 76 |
| 17 | GD | `0x695870` | `LogArchive::isPingTimeExpired` | source_logarchive | 15 |
| 18 | GD | `0x6958f0` | `LogArchive::pushPingReqPacket` | source_logarchive | 60 |
| 19 | GD | `0x695aa0` | `LogArchive::startupWinSockLib` | source_logarchive | 14 |
| 20 | GD | `0x69dd00` | `StringBuilderW::~StringBuilderW` | stringbuilder | 8 |
| 21 | GD | `0x69dd40` | `StringBuilderW::AppendFormat` | stringbuilder | 21 |
| 22 | GD | `0x6a0250` | `LogFile::Write` | source_logfile | 21 |
| 23 | GD | `0x6a07c0` | `LogNetwork::Instance` | source_lognetwork | 32 |
| 24 | GD | `0x6a0870` | `LogNetwork::Stop` | source_lognetwork | 71 |
| 25 | GD | `0x6a09d0` | `LogNetwork::AddSession` | source_lognetwork | 150 |
| 26 | GD | `0x6a0c90` | `LogNetwork::RemoveSession` | source_lognetwork | 84 |
| 27 | GD | `0x6a0e30` | `LogNetwork::write` | source_lognetwork | 185 |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/source_logarchive.cpp`
- `src/Server/GameDaemon/source_logarchive.h`
- `src/Server/GameDaemon/stringbuilder.cpp`
- `src/Server/GameDaemon/stringbuilder.h`
- `src/Server/GameDaemon/source_logfile.cpp`
- `src/Server/GameDaemon/source_logfile.h`
- `src/Server/GameDaemon/source_lognetwork.cpp`
- `src/Server/GameDaemon/source_lognetwork.h`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-12.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
