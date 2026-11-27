# lift-gamedaemon-12: BloodLib: source_logarchive, source_lognetwork, source_delayedrelease

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
| Depends on | `lift-gamedaemon-e12`, `lift-gamedaemon-e25`, `lift-gamedaemon-2`, `lift-gamedaemon-4`, `lift-gamedaemon-11` |
| Pattern | `src/Server/BloodLib/source/DelayedRelease.cpp` |
| Plan | `Docs/Plan/gamedaemon-lift.md` sections 1, 3, 5 |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Grep `Docs/Parity/lessons.md` for A2 (block order), A6 (per-exe path literals), A12 (PDB member types), A18 (destructors), A21 (PDB facts) and A22 (per-exe source form). Do not read it in full.
- Pattern: `src/Server/BloodLib/source/DelayedRelease.cpp`. Read it one time. Use its form for the functions of this card.
- Dead-strip: `wmain` and most callers are still `LIFT_STUB` bodies. `/OPT:REF` removes a lifted function that has no live caller, and funcdiff then cannot pair it. For each function in scope with no live caller, add `#pragma comment(linker, "/INCLUDE:<public name>")` in its `.cpp` (public names: `llvm-pdbutil dump -publics`; grep `/INCLUDE` in `Docs/Parity/lessons.md`). Do not add a pragma for a function that a lifted caller keeps.

## Scope

23 functions, about 1,660 pseudocode lines (about 13,280 tokens). Stems: `source_logarchive`, `source_lognetwork`, `source_delayedrelease`.

The easy functions of this stem are in `lift-gamedaemon-e12`, `lift-gamedaemon-e25`. Do not change them unless a fix needs it.

| n | Exe | RVA | PDB name | Stem | Lines |
| ---: | --- | --- | --- | --- | ---: |
| 1 | GD | `0x694070` | `LogArchive::LogArchive` | source_logarchive | 105 |
| 2 | GD | `0x6942d0` | `LogArchive::~LogArchive` | source_logarchive | 79 |
| 3 | GD | `0x6944f0` | `LogArchive::Initialize` | source_logarchive | 111 |
| 4 | GD | `0x694730` | `LogArchive::Start` | source_logarchive | 43 |
| 5 | GD | `0x694810` | `LogArchive::Write` | source_logarchive | 57 |
| 6 | GD | `0x694980` | `LogArchive::run` | source_logarchive | 85 |
| 7 | GD | `0x694b90` | `LogArchive::AccessLogServer` | source_logarchive | 156 |
| 8 | GD | `0x695150` | `LogArchive::ChangeFileMode` | source_logarchive | 32 |
| 9 | GD | `0x6951e0` | `LogArchive::constructEventArray` | source_logarchive | 56 |
| 10 | GD | `0x6952f0` | `LogArchive::processTimeout` | source_logarchive | 29 |
| 11 | GD | `0x6953d0` | `LogArchive::processEventInFileMode` | source_logarchive | 35 |
| 12 | GD | `0x6954a0` | `LogArchive::processEventInNetMode` | source_logarchive | 30 |
| 13 | GD | `0x695530` | `LogArchive::flush` | source_logarchive | 27 |
| 14 | GD | `0x6955b0` | `LogArchive::write` | source_logarchive | 31 |
| 15 | GD | `0x695610` | `LogArchive::pushLogData` | source_logarchive | 76 |
| 16 | GD | `0x6958f0` | `LogArchive::pushPingReqPacket` | source_logarchive | 60 |
| 17 | GD | `0x6a07c0` | `LogNetwork::Instance` | source_lognetwork | 32 |
| 18 | GD | `0x6a0870` | `LogNetwork::Stop` | source_lognetwork | 71 |
| 19 | GD | `0x6a09d0` | `LogNetwork::AddSession` | source_lognetwork | 150 |
| 20 | GD | `0x6a0c90` | `LogNetwork::RemoveSession` | source_lognetwork | 84 |
| 21 | GD | `0x6a0e30` | `LogNetwork::write` | source_lognetwork | 185 |
| 22 | GD | `0x6a16d0` | `DelayedDelete::Add` | source_delayedrelease | 46 |
| 23 | GD | `0x6a17c0` | `DelayedDelete::Delete` | source_delayedrelease | 80 |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/source_logarchive.cpp`
- `src/Server/GameDaemon/source_logarchive.h`
- `src/Server/GameDaemon/source_lognetwork.cpp`
- `src/Server/GameDaemon/source_lognetwork.h`
- `src/Server/GameDaemon/source_delayedrelease.cpp`
- `src/Server/GameDaemon/source_delayedrelease.h`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-12.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
