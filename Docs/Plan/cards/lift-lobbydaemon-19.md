# lift-lobbydaemon-19: LobbyDB part 2

| Item | Value |
| --- | --- |
| Source build | LobbyDaemon 2019 + PDB (VS2010 SP1) |
| Exe | `<work-root>/ida/lift/LobbyDaemon/LobbyDaemon.exe` |
| PDB | `<work-root>/ida/lift/LobbyDaemon/LobbyDaemon.pdb` |
| Pseudocode: `LobbyDB` | `~/.cache/bns-lift/hr/LobbyDaemon/LobbyDB.c` |
| Wave | 4 |
| Model | sol |

Use only the exe and PDB in the table. Do not use `LobbyDaemon2019.exe` or a 381 file.

## Read first

- Read `Docs/Plan/plan.md`, “Lift method.”
- Read `Docs/Parity/lessons.md`, sections A8, A17, A21, A29, C4, and the DB loader notes in `scd-4`.
- Pattern for LobbyDB: `src/Server/SmartCouponDaemon/SmartCouponDB.cpp`.

## Modules

| Module | Scope | RVA range | Functions | Pseudocode lines |
| --- | --- | --- | ---: | ---: |
| `LobbyDB` | Part 2 | `0xa4320` to `0xa8a00` | 26 | 2,822 |

The RVA limits include both endpoints.

Use the SmartCouponDaemon DB file as the pattern. LobbyGate has no DB module in the lift tree.

Keep this card at 26 functions. The 3,500-line limit takes precedence over the 30-function target.

## Tasks

1. Record the LobbyDaemon MATCH count before you change code.
2. Use `~/.cache/bns-lift/hr/LobbyDaemon/index.tsv` to find the functions and their pseudocode lines. Read only the entries in scope.
3. Check names, signatures, and types against the PDB. Use IDA only when the PDB and cache do not give the necessary facts. Close the database when you finish.
4. Replace the in-scope stub bodies with C++. Keep all bodies and stubs outside the card scope unchanged. Do not copy keys or unsafe behavior into the public repo.
5. Use the existing `LobbyDaemon` CMake target from the earlier wave. Update its source list only if a listed file is missing from the target.
6. Run `tools/gate.sh` after each module. Run `tools/parity.sh` for the four earlier executables. Do not update the baselines.
7. Build LobbyDaemon with `tools/vs2010/build.sh LobbyDaemon`. Compare its MATCH count with the count before the changes. Use `tools/funcdiff.py` with the same VS2010 build options for both counts.

## Files

- `src/Server/LobbyDaemon/LobbyDB.cpp`
- `CMakeLists.txt`

## Handoff

Write `Docs/Plan/handoffs/lift-lobbydaemon-19.md`. List the modules and functions that you completed. Give each incomplete function name and RVA under **Not done**. Record the gate result and the before and after MATCH counts.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each in-scope function is in C++ or is listed under **Not done** with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, and PostOfficeDaemon lose no MATCH functions.
- The LobbyDaemon MATCH count does not go down.
