# lift-lobbydaemon-48: Goods and service item jobs

| Item | Value |
| --- | --- |
| Source build | LobbyDaemon 2019 + PDB (VS2010 SP1) |
| Exe | `<work-root>/ida/lift/LobbyDaemon/LobbyDaemon.exe` |
| PDB | `<work-root>/ida/lift/LobbyDaemon/LobbyDaemon.pdb` |
| Pseudocode index | `~/.cache/bns-lift/hr/LobbyDaemon/index.tsv` |
| Pseudocode: GetGoodsCountJob | `~/.cache/bns-lift/hr/LobbyDaemon/GetGoodsCountJob.c` |
| Pseudocode: ListGoodsJob | `~/.cache/bns-lift/hr/LobbyDaemon/ListGoodsJob.c` |
| Pseudocode: TakeGoodsJob | `~/.cache/bns-lift/hr/LobbyDaemon/TakeGoodsJob.c` |
| Pseudocode: GetLobbyServiceItemJob | `~/.cache/bns-lift/hr/LobbyDaemon/GetLobbyServiceItemJob.c` |
| Wave | 8 |
| Model | sol |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Read A2, A8, A17, A19, A21, and C4 in `Docs/Parity/lessons.md`. This is the current path for `lessons.md`.
- Read the pattern for the jobs once: `src/Server/SmartCouponDaemon/CouponJob.cpp`.

## Modules

Use the module name and the function entry RVA together. Both ends of each range are in scope. Counts exclude EH funclets and scalar deleting destructors.

| Module | Scope | RVA range | Functions | Pseudocode lines |
| --- | --- | --- | ---: | ---: |
| `GetGoodsCountJob` | Whole module | `0x51460` to `0x11ed40` | 13 | 666 |
| `ListGoodsJob` | Whole module | `0x54ee0` to `0x11ee40` | 13 | 664 |
| `TakeGoodsJob` | Whole module | `0x79f00` to `0x11f140` | 13 | 725 |
| `GetLobbyServiceItemJob` | Whole module | `0x52060` to `0x11ed80` | 13 | 702 |
| Total | | | 52 | 2,757 |

## Tasks

1. Use only the exe and PDB in the table. Do not use `LobbyDaemon2019.exe` or a 381 file.
2. Run `tools/gate.sh` before the edits. Then run `tools/parity.sh CacheGate LobbyGate SmartCouponDaemon PostOfficeDaemon LobbyDaemon`. Save the MATCH counts and function results outside the tracked files.
3. Use `index.tsv` to select the functions and line spans in scope. Read only those spans. Use IDA only if the cache does not give enough data. Close the database when you finish.
4. Replace only the stub bodies in scope. Use names and types from the 2019 PDB. Check for an existing body before you lift a function. Do not reproduce security bugs.
5. Change `CMakeLists.txt` only if the LobbyDaemon target needs it. Do not add a source file twice.
6. Run `tools/gate.sh` after each module. Run the same parity check after the last edit. Compare the results with the saved results. Do not update the parity baselines.

## Files

- `src/Server/LobbyDaemon/GetGoodsCountJob.cpp`
- `src/Server/LobbyDaemon/ListGoodsJob.cpp`
- `src/Server/LobbyDaemon/TakeGoodsJob.cpp`
- `src/Server/LobbyDaemon/GetLobbyServiceItemJob.cpp`
- `CMakeLists.txt`

## Handoff

Write `Docs/Plan/handoffs/lift-lobbydaemon-48.md`. List the functions you lifted. List each function that remains as **Not done**. Give its PDB name, RVA, and reason. Record the gate result and the MATCH counts for each exe before and after the edits. Keep binaries, PDBs, IDA databases, keys, and abuse notes out of git.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in scope is lifted or listed as **Not done** with its RVA in the handoff.
- No function that was a MATCH loses that status in CacheGate, LobbyGate, SmartCouponDaemon, or PostOfficeDaemon.
- The LobbyDaemon MATCH count does not go down.
