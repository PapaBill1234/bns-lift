# lift-lobbydaemon-20: LobbyDaemon part 2, BLDaemonInfo

| Item | Value |
| --- | --- |
| Source build | LobbyDaemon 2019 + PDB (VS2010 SP1) |
| Exe | `/home/ubuntu/Documents/Codex/private-project/ida/lift/LobbyDaemon/LobbyDaemon.exe` |
| PDB | `/home/ubuntu/Documents/Codex/private-project/ida/lift/LobbyDaemon/LobbyDaemon.pdb` |
| Pseudocode: `LobbyDaemon` | `~/.cache/bns-lift/hr/LobbyDaemon/LobbyDaemon.c` |
| Pseudocode: `BLDaemonInfo` | `~/.cache/bns-lift/hr/LobbyDaemon/BLDaemonInfo.c` |
| Wave | 4 |
| Model | opus |

Use only the exe and PDB in the table. Do not use `LobbyDaemon2019.exe` or a 381 file.

## Read first

- Read `Docs/Plan/plan.md`, “Lift method.”
- Read `Docs/Parity/lessons.md`, sections A2, A8, A17, A21, A29, and C4.
- Pattern for LobbyDaemon: `src/Server/SmartCouponDaemon/SmartCouponDaemon.cpp`.

## Modules

| Module | Scope | RVA range | Functions | Pseudocode lines |
| --- | --- | --- | ---: | ---: |
| `LobbyDaemon` | Part 2 | `0x9d520` to `0x9fd70` | 21 | 2,128 |
| `BLDaemonInfo` | Whole module | `0x403c0` to `0x416f0` | 9 | 1,017 |
| Total | | | 30 | 3,145 |

Counts exclude compiler-generated deleting destructors. Line totals include all exported pseudocode for each whole module.
The RVA limits include both endpoints.

Use `BannedWordFilterLoader` and `PerfCounterProvider` from wave 1. Do not lift them again.

`BLDaemonInfo` has no pattern file. Use its PDB and pseudocode.

## Tasks

1. Record the LobbyDaemon MATCH count before you change code.
2. Use `~/.cache/bns-lift/hr/LobbyDaemon/index.tsv` to find the functions and their pseudocode lines. Read only the entries in scope.
3. Check names, signatures, and types against the PDB. Use IDA only when the PDB and cache do not give the necessary facts. Close the database when you finish.
4. Replace the in-scope stub bodies with C++. Keep all bodies and stubs outside the card scope unchanged. Do not copy keys or unsafe behavior into the public repo.
5. Use the existing `LobbyDaemon` CMake target from the earlier wave. Update its source list only if a listed file is missing from the target.
6. Run `tools/gate.sh` after each module. Run `tools/parity.sh` for the four earlier executables. Do not update the baselines.
7. Build LobbyDaemon with `tools/vs2010/build.sh LobbyDaemon`. Compare its MATCH count with the count before the changes. Use `tools/funcdiff.py` with the same VS2010 build options for both counts.

## Files

- `src/Server/LobbyDaemon/LobbyDaemon.cpp`
- `src/Server/LobbyDaemon/BLDaemonInfo.cpp`
- `CMakeLists.txt`

## Handoff

Write `Docs/Plan/handoffs/lift-lobbydaemon-20.md`. List the modules and functions that you completed. Give each incomplete function name and RVA under **Not done**. Record the gate result and the before and after MATCH counts.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each in-scope function is in C++ or is listed under **Not done** with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, and PostOfficeDaemon lose no MATCH functions.
- The LobbyDaemon MATCH count does not go down.
