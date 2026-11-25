# lift-lobbydaemon-objpool: ObjectPool module and pool statics

| Item | Value |
| --- | --- |
| Source build | LobbyDaemon 2019 + PDB (VS2010 SP1) |
| Exe | `<work-root>/ida/lift/LobbyDaemon/LobbyDaemon.exe` |
| PDB | `<work-root>/ida/lift/LobbyDaemon/LobbyDaemon.pdb` |
| Pseudocode: `ObjectPool` | `~/.cache/bns-lift/hr/LobbyDaemon/ObjectPool.c` |
| Wave | 5 (base card) |
| Model | opus |

Use only the exe and PDB in the table. Do not use `LobbyDaemon2019.exe` or a 381 file.

## Problem

Handlers call `ObjPool::Checkout(&<Job>::_pool)`. This does not link in the VS2010 LobbyDaemon build:

| Cause | Fact |
| --- | --- |
| `src/Server/LobbyDaemon/ObjectPool.cpp` | It is the SmartCouponDaemon form. It is only in `lift_smartcoupondaemon` (CMakeLists.txt, about line 231). |
| `<Job>::_pool` | Job classes declare `static ObjPool _pool;  // LIFT: no definition yet`. No definition exists. |
| `CliSession::_pool` | .data 0x2042b0, id 1, objsize 0x8d0, desc `L"CliSession"`. See the LIFT note in `CliSession.cpp`. |

Card 22 left 17 handlers as **Not done** for this reason. See `Docs/Plan/handoffs/lift-lobbydaemon-22.md`.

## Modules

| Module | Scope | RVA range | Functions |
| --- | --- | --- | ---: |
| `ObjectPool` | Whole module | `0x625d0` to `0x62e00` | 11 |
| Pool statics | `dynamic initializer for '<X>::_pool'` | `0x11d850` to `0x11e660` | 46 |
| Pool statics | `dynamic atexit destructor for '<X>::_pool'` | from `0x11e7c0` | 46 |

Get the list with: `grep -E "dynamic (initializer|atexit destructor) for '.*::_pool'" ~/.cache/bns-lift/hr/LobbyDaemon/index.tsv`.

## Tasks

1. Record the MATCH count of all 5 executables before you change code.
2. Make the ObjectPool module link into `lift_lobbydaemon`. Do not break SmartCouponDaemon parity. Options, in order of preference:
   - Compile the same `ObjectPool.cpp` for both libraries, with a per-exe define for the exe-specific parts (allocator, `LIFT_STLMEMORY_FILE`).
   - Add a LobbyDaemon form of the file. Use this only if the bodies differ.
   Compare the LobbyDaemon bodies (0x625d0–0x62e00) with the SmartCouponDaemon bodies first. Record the differences in the handoff.
3. Define `CliSession::_pool` and each `<Job>::_pool` that the PDB has. Get id, objsize and desc from the dynamic initializer bodies. Declare the job class in its header if it is not declared yet. Put all job pool definitions in one new file `src/Server/LobbyDaemon/JobPools.cpp`. This prevents merge conflicts with other wave 5 cards. Add a `// LIFT:` note with the RVA of each initializer.
4. Remove the `// LIFT: no definition yet` notes that you resolve.
5. Retry the 17 Not-done handlers of card 22 (`LobbyLobbyGatePacketHandler.cpp`) only if time allows. Stay out of the files of cards 25–30.
6. Run `tools/gate.sh`. Run `tools/parity.sh` for the four earlier executables. Do not update the baselines.
7. Build LobbyDaemon with `tools/vs2010/build.sh LobbyDaemon`. Compare its MATCH count with the count before the changes.

## Files

| File | Owner |
| --- | --- |
| `src/Server/LobbyDaemon/ObjectPool.cpp`, `ObjectPool.h` | This card |
| `src/Server/LobbyDaemon/JobPools.cpp` (new) | This card |
| `src/Server/LobbyDaemon/CliSession.cpp` (only the `_pool` definition) | This card |
| Job headers (only the `_pool` line) | This card |
| `CMakeLists.txt` | This card (ObjectPool and JobPools lines only) |

## Handoff

Write `Docs/Plan/handoffs/lift-lobbydaemon-objpool.md`. List the functions and statics that you completed. Give each incomplete item with its RVA under **Not done**. Record the gate result and the before and after MATCH counts.

## Done when

- `tools/gate.sh` prints `gate ok`.
- The VS2010 LobbyDaemon build links with `ObjPool::Checkout` and the pool statics.
- CacheGate, LobbyGate, SmartCouponDaemon, and PostOfficeDaemon lose no MATCH functions.
- The LobbyDaemon MATCH count does not go down.
