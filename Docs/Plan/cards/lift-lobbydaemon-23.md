# lift-lobbydaemon-23: GamedChannel 2, InfoGate

| Item | Value |
| --- | --- |
| Source build | LobbyDaemon 2019 + PDB (VS2010 SP1) |
| Exe | `/home/ubuntu/Documents/Codex/private-project/ida/lift/LobbyDaemon/LobbyDaemon.exe` |
| PDB | `/home/ubuntu/Documents/Codex/private-project/ida/lift/LobbyDaemon/LobbyDaemon.pdb` |
| Pseudocode: `GamedChannel` | `~/.cache/bns-lift/hr/LobbyDaemon/GamedChannel.c` |
| Pseudocode: `InfoGateChannel` | `~/.cache/bns-lift/hr/LobbyDaemon/InfoGateChannel.c` |
| Pseudocode: `LobbyInfoGatePacketHandler` | `~/.cache/bns-lift/hr/LobbyDaemon/LobbyInfoGatePacketHandler.c` |
| Wave | 4 |
| Model | sol |

Use only the exe and PDB in the table. Do not use `LobbyDaemon2019.exe` or a 381 file.

## Read first

- Read `Docs/Plan/plan.md`, “Lift method.”
- Read `Docs/Parity/lessons.md`, sections A2, A17, A19, A21, A23, A26, and C4.
- Pattern for GamedChannel and InfoGateChannel (LobbyGate pattern): `src/Server/LobbyGate/LobbyDChannel.cpp`.
- Pattern for GamedChannel and InfoGateChannel (module survey pattern): `src/Server/Economy/PostOfficeDaemon/AgentChannel.cpp`.
- Pattern for LobbyInfoGatePacketHandler: `src/Server/Economy/PostOfficeDaemon/AgentPacketHandler.cpp`.

## Modules

| Module | Scope | RVA range | Functions | Pseudocode lines |
| --- | --- | --- | ---: | ---: |
| `GamedChannel` | Part 2 | `0x82b70` to `0x84d20` | 29 | 1,318 |
| `InfoGateChannel` | Whole module | `0x2e6d0` to `0x2f300` | 13 | 848 |
| `LobbyInfoGatePacketHandler` | Whole module | `0x56d40` to `0x57880` | 3 | 549 |
| Total | | | 45 | 2,715 |

Counts exclude compiler-generated deleting destructors. Line totals include all exported pseudocode for each whole module.
The RVA limits include both endpoints.

## Tasks

1. Record the LobbyDaemon MATCH count before you change code.
2. Use `~/.cache/bns-lift/hr/LobbyDaemon/index.tsv` to find the functions and their pseudocode lines. Read only the entries in scope.
3. Check names, signatures, and types against the PDB. Use IDA only when the PDB and cache do not give the necessary facts. Close the database when you finish.
4. Replace the in-scope stub bodies with C++. Keep all bodies and stubs outside the card scope unchanged. Do not copy keys or unsafe behavior into the public repo.
5. Use the existing `LobbyDaemon` CMake target from the earlier wave. Update its source list only if a listed file is missing from the target.
6. Run `tools/gate.sh` after each module. Run `tools/parity.sh` for the four earlier executables. Do not update the baselines.
7. Build LobbyDaemon with `tools/vs2010/build.sh LobbyDaemon`. Compare its MATCH count with the count before the changes. Use `tools/funcdiff.py` with the same VS2010 build options for both counts.

## Files

- `src/Server/LobbyDaemon/GamedChannel.cpp`
- `src/Server/LobbyDaemon/InfoGateChannel.cpp`
- `src/Server/LobbyDaemon/LobbyInfoGatePacketHandler.cpp`
- `CMakeLists.txt`

## Handoff

Write `Docs/Plan/handoffs/lift-lobbydaemon-23.md`. List the modules and functions that you completed. Give each incomplete function name and RVA under **Not done**. Record the gate result and the before and after MATCH counts.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each in-scope function is in C++ or is listed under **Not done** with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, and PostOfficeDaemon lose no MATCH functions.
- The LobbyDaemon MATCH count does not go down.
