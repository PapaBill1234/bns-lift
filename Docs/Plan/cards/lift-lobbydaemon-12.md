# lift-lobbydaemon-12: AuctionEscrow, stats, tick, misc

| Item | Value |
| --- | --- |
| Source build | LobbyDaemon 2019 + PDB (VS2010 SP1) |
| Exe | `/home/ubuntu/Documents/Codex/private-project/ida/lift/LobbyDaemon/LobbyDaemon.exe` |
| PDB | `/home/ubuntu/Documents/Codex/private-project/ida/lift/LobbyDaemon/LobbyDaemon.pdb` |
| Pseudocode | `~/.cache/bns-lift/hr/LobbyDaemon/AuctionEscrow.c`<br>`~/.cache/bns-lift/hr/LobbyDaemon/LobbyStats.c`<br>`~/.cache/bns-lift/hr/LobbyDaemon/LobbyTick.c`<br>`~/.cache/bns-lift/hr/LobbyDaemon/TencentUIC.c`<br>`~/.cache/bns-lift/hr/LobbyDaemon/LobbyMessage.c` |
| Wave | 2 |
| Model | opus |

## Read first

- Read `Docs/Plan/plan.md`, "Lift method".
- Read `Docs/Parity/lessons.md`, sections A2, A21, A17, A18, C4.
- Pattern: none.

## Modules

| Module | Scope | RVA range | Functions | Pseudocode lines |
| --- | --- | --- | ---: | ---: |
| `AuctionEscrow` | Whole module | `0x135e0` to `0x14770` | 3 | 989 |
| `LobbyStats` | Whole module | `0x5a0b0` to `0x5a5c0` | 5 | 222 |
| `LobbyTick` | Whole module | `0x5a610` to `0x5aa20` | 8 | 213 |
| `TencentUIC` | Whole module | `0x7ac30` to `0x7b0a0` | 4 | 168 |
| `LobbyMessage` | Whole module | `0x2f9d0` to `0x2fb60` | 6 | 140 |
| Total | | | 26 | 1,732 |

Use the address range with the module name. The range can contain functions from other modules. The function counts exclude compiler-generated deleting destructors.

- These are the last small modules with no pattern file. Keep them on this card even though the total is fewer than 30 functions.

## Tasks

1. Record the baseline MATCH counts for CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon, and LobbyDaemon. Use the same comparison settings for the final counts.
2. Read the function list from `~/.cache/bns-lift/hr/LobbyDaemon/index.tsv`. Match the module name and address for each function. Do not lift compiler-generated deleting destructors as separate source functions.
3. Read the listed pseudocode. Use IDA only when the cache does not settle a question. Close the database when you finish with it.
4. Replace the in-scope stub bodies with C++ that uses PDB types and names.
5. Change `CMakeLists.txt` only if the LobbyDaemon target needs it. Do not change the other server targets.
6. Run `tools/gate.sh` after each module. Compare the final MATCH counts with the baseline.

Use only the exe and PDB in the table. Do not use `LobbyDaemon2019.exe` or build 381. The repo is public. Do not add binaries, PDBs, IDA databases, keys, or abuse notes.

## Files

- `src/Server/LobbyDaemon/AuctionEscrow.cpp`
- `src/Server/LobbyDaemon/LobbyStats.cpp`
- `src/Server/LobbyDaemon/LobbyTick.cpp`
- `src/Server/LobbyDaemon/TencentUIC.cpp`
- `src/Server/LobbyDaemon/LobbyMessage.cpp`
- `CMakeLists.txt`

## Handoff

Write `Docs/Plan/handoffs/lift-lobbydaemon-12.md`. Record the lifted functions, the gate result, and the baseline and final MATCH counts. Under **Not done**, give the module, PDB name, address, and reason for each function that you did not lift.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function on this card is lifted or listed as **Not done** with its address.
- CacheGate, LobbyGate, SmartCouponDaemon, and PostOfficeDaemon lose no MATCH functions.
- The LobbyDaemon MATCH count does not go down.
