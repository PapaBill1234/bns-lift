# lift-gamedaemon-33: Shared gaps and BloodLib: source_pipeconsole, windowconsole, ioworkerthread_cpp, connection, ...

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
| Depends on | `lift-gamedaemon-e45`, `lift-gamedaemon-2` |
| Pattern | `src/Server/BloodLib/source/PipeConsole.cpp` |
| Plan | `Docs/Plan/gamedaemon-lift.md` sections 1, 3, 5 |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Grep `Docs/Parity/lessons.md` for A2 (block order), A6 (per-exe path literals), A12 (PDB member types), A18 (destructors), A21 (PDB facts) and A22 (per-exe source form). Do not read it in full.
- Pattern: `src/Server/BloodLib/source/PipeConsole.cpp`. Read it one time. Use its form for the functions of this card.

## Scope

17 functions, about 1,547 pseudocode lines (about 12,376 tokens). Stems: `source_pipeconsole`, `windowconsole`, `ioworkerthread_cpp`, `connection`, `listener`.

The easy functions of this stem are in `lift-gamedaemon-e45`. Do not change them unless a fix needs it.

| n | Exe | RVA | PDB name | Stem | Lines |
| ---: | --- | --- | --- | --- | ---: |
| 1 | GD | `0x6aefc0` | `PipeCommandProcess::processCommand` | source_pipeconsole | 117 |
| 2 | GD | `0x6af430` | `PipeConsole::processCommand` | source_pipeconsole | 203 |
| 3 | GD | `0x6af620` | `PipeConsole::checkFrozenThread` | source_pipeconsole | 170 |
| 4 | GD | `0x6afd40` | `PipeConsole::run` | source_pipeconsole | 143 |
| 5 | GD | `0x6b0450` | `PipeConsole::SetInvalidInfo` | source_pipeconsole | 80 |
| 6 | GD | `0x6b06d0` | `PipeConsole::cleanup` | source_pipeconsole | 97 |
| 7 | GD | `0x6b1520` | `WindowConsole::WindowConsole` | windowconsole | 21 |
| 8 | GD | `0x6b1650` | `WindowConsole::Open` | windowconsole | 109 |
| 9 | GD | `0x6b1920` | `WindowConsole::Close` | windowconsole | 28 |
| 10 | GD | `0x6b7880` | `IoWorker::run` | ioworkerthread_cpp | 145 |
| 11 | GD | `0x6b7ba0` | `IoWorker::handleFailedEvent` | ioworkerthread_cpp | 34 |
| 12 | GD | `0x6bd800` | `Connection::Accept` | connection | 59 |
| 13 | GD | `0x6bd960` | `Connection::Connect` | connection | 67 |
| 14 | GD | `0x6be110` | `PortListener::Initialize` | listener | 90 |
| 15 | GD | `0x6be4a0` | `PortListener::HandleFailedEvent` | listener | 30 |
| 16 | GD | `0x6be530` | `PortListener::asyncAccept` | listener | 42 |
| 17 | GD | `0x6be650` | `PortListener::accept` | listener | 112 |

### Shared functions

These functions are in shared source. They are not MATCH in each lifted exe that has them.

| PDB name | Shared file | Other exes | Note |
| --- | --- | --- | --- |
| `PipeCommandProcess::processCommand` | `src/Server/BloodLib/source/PipeConsole.cpp` | CacheGate, LobbyDaemon, LobbyGate, PostOfficeDaemon, SmartCouponDaemon | - |
| `PipeConsole::processCommand` | `src/Server/BloodLib/source/PipeConsole.cpp` | CacheGate, LobbyDaemon, LobbyGate, PostOfficeDaemon, SmartCouponDaemon | - |
| `PipeConsole::checkFrozenThread` | `src/Server/BloodLib/source/PipeConsole.cpp` | CacheGate, LobbyDaemon, LobbyGate, PostOfficeDaemon, SmartCouponDaemon | - |
| `PipeConsole::run` | `src/Server/BloodLib/source/PipeConsole.cpp` | CacheGate, LobbyDaemon, LobbyGate, PostOfficeDaemon, SmartCouponDaemon | - |
| `PipeConsole::SetInvalidInfo` | `src/Server/BloodLib/source/PipeConsole.cpp` | CacheGate, LobbyDaemon, PostOfficeDaemon, SmartCouponDaemon | - |
| `PipeConsole::cleanup` | `src/Server/BloodLib/source/PipeConsole.cpp` | CacheGate, LobbyDaemon, LobbyGate, PostOfficeDaemon, SmartCouponDaemon | - |
| `WindowConsole::WindowConsole` | `src/Server/BloodLib/source/WindowConsole.cpp` | CacheGate, LobbyDaemon, LobbyGate, PostOfficeDaemon, SmartCouponDaemon | EXCLUDED in LobbyDaemon: read its `excluded.tsv` row first |
| `WindowConsole::Open` | `src/Server/BloodLib/source/WindowConsole.cpp` | CacheGate, LobbyDaemon, LobbyGate, PostOfficeDaemon, SmartCouponDaemon | - |
| `WindowConsole::Close` | `src/Server/BloodLib/source/WindowConsole.cpp` | CacheGate, LobbyDaemon, LobbyGate, PostOfficeDaemon, SmartCouponDaemon | - |
| `IoWorker::run` | `src/Server/BloodLib/source/IoWorkerThread.cpp` | CacheGate, LobbyDaemon, LobbyGate, PostOfficeDaemon, SmartCouponDaemon | - |
| `Connection::Accept` | `src/Server/BloodLib/source/Connection.cpp` | CacheGate, LobbyDaemon, LobbyGate, PostOfficeDaemon, SmartCouponDaemon | EXCLUDED in LobbyDaemon: read its `excluded.tsv` row first |
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

- `src/Server/BloodLib/source/PipeConsole.cpp`
- `src/Server/BloodLib/source/WindowConsole.cpp`
- `src/Server/GameDaemon/ioworkerthread_cpp.cpp`
- `src/Server/GameDaemon/ioworkerthread_cpp.h`
- `src/Server/BloodLib/source/IoWorkerThread.cpp`
- `src/Server/GameDaemon/connection.cpp`
- `src/Server/GameDaemon/connection.h`
- `src/Server/BloodLib/source/Connection.cpp`
- `src/Server/BloodLib/source/Listener.cpp`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-33.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
