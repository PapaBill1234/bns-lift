# lift-lobbydaemon-57: ChangeUserNameJob

| Item | Value |
| --- | --- |
| Source build | LobbyDaemon 2019 + PDB (VS2010 SP1) |
| Exe | `/home/ubuntu/Documents/Codex/private-project/ida/lift/LobbyDaemon/LobbyDaemon.exe` |
| PDB | `/home/ubuntu/Documents/Codex/private-project/ida/lift/LobbyDaemon/LobbyDaemon.pdb` |
| Pseudocode: ChangeUserNameJob | `~/.cache/bns-lift/hr/LobbyDaemon/ChangeUserNameJob.c` |
| Wave | 10 |
| Model | sol |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Read A2, A17, A21, C4 and "Manual parity for logging, timers, and job dispatch" in `Docs/Parity/lessons.md`.
- Use `~/.cache/bns-lift/hr/LobbyDaemon/index.tsv` for the function list and pseudocode line spans.
- Read the pattern once: `src/Server/SmartCouponDaemon/CouponJob.cpp`.

## Modules

Addresses are function entry RVAs. Both ends of each range are in scope. Counts exclude EH funclets and scalar deleting destructors.

| Module | Scope | RVA range | Functions | Pseudocode lines |
| --- | --- | --- | ---: | ---: |
| `ChangeUserNameJob` | Whole module | `0x26990` to `0x11eac0` | 22 | 2,630 |

Keep the scope below 30 functions. The 3,500-line cap takes priority.

## Tasks

1. Use only the exe and PDB in the table. Do not use `LobbyDaemon2019.exe` or a 381 file.
2. Run `tools/gate.sh` before edits. Capture the initial MATCH results with `tools/parity.sh CacheGate LobbyGate SmartCouponDaemon PostOfficeDaemon LobbyDaemon`. Keep those results outside tracked files.
3. Read only the pseudocode spans in scope. Use IDA only if the cache does not give enough data. Close the database when you finish.
4. Replace the stub bodies in the listed `.cpp` files. Use PDB types and names. Check for an existing implementation before you lift a function.
   Do not reproduce security bugs.
5. Change `CMakeLists.txt` only if the LobbyDaemon target needs it. Do not add a source file twice.
6. Run `tools/gate.sh` after each module. Run the same parity check after the last edit. Compare the before and after results. Do not update parity baselines.

## Files

- `src/Server/LobbyDaemon/ChangeUserNameJob.cpp`
- `CMakeLists.txt`

## Handoff

Write `Docs/Plan/handoffs/lift-lobbydaemon-57.md`. List the functions you lifted. List each remaining function as **Not done**. Give its name, RVA and reason. Record the gate result. Record the before and after MATCH counts for each exe. Do not commit binaries, PDBs, IDA databases, keys or abuse notes.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in scope is lifted or is listed as **Not done** with its RVA in the handoff.
- No function that was a MATCH loses that status in CacheGate, LobbyGate, SmartCouponDaemon or PostOfficeDaemon.
- The LobbyDaemon MATCH count does not go down.
