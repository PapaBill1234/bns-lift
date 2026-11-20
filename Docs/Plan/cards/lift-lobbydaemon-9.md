# lift-lobbydaemon-9: GameWorld, Fsd showcase, RuleSet

| Item | Value |
| --- | --- |
| Source build | LobbyDaemon 2019 + PDB (VS2010 SP1) |
| Exe | `/home/ubuntu/Documents/Codex/private-project/ida/lift/LobbyDaemon/LobbyDaemon.exe` |
| PDB | `/home/ubuntu/Documents/Codex/private-project/ida/lift/LobbyDaemon/LobbyDaemon.pdb` |
| Pseudocode | `~/.cache/bns-lift/hr/LobbyDaemon/GameWorld.c`<br>`~/.cache/bns-lift/hr/LobbyDaemon/FsdShowcaseRecord.c`<br>`~/.cache/bns-lift/hr/LobbyDaemon/RuleSet.c`<br>`~/.cache/bns-lift/hr/LobbyDaemon/LobbyPerfMonitor.c` |
| Wave | 2 |
| Model | opus |

## Read first

- Read `Docs/Plan/plan.md`, "Lift method".
- Read `Docs/Parity/lessons.md`, sections A2, A21, A12, A17, C4.
- Pattern: none.

## Modules

| Module | Scope | RVA range | Functions | Pseudocode lines |
| --- | --- | --- | ---: | ---: |
| `GameWorld` | Whole module | `0x4c810` to `0x96d20` | 39 | 2,679 |
| `FsdShowcaseRecord` | Whole module | `0x2e0b0` | 1 | 225 |
| `RuleSet` | Whole module | `0x6bfc0` | 1 | 222 |
| `LobbyPerfMonitor` | Whole module | `0x59ce0` to `0x59f40` | 5 | 169 |
| Total | | | 46 | 3,295 |

Use the address range with the module name. The range can contain functions from other modules. The function counts exclude compiler-generated deleting destructors.

- Read the wave 1 common-module handoffs before you start.
- Reuse `FsdDecomposer` in `GameWorld`, `FsdShowcaseRecord`, and `RuleSet`.
- Reuse `BannedWordFilter` in `GameWorld`.
- Reuse `PerfCounterProvider` in `LobbyPerfMonitor`.

## Tasks

1. Record the baseline MATCH counts for CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon, and LobbyDaemon. Use the same comparison settings for the final counts.
2. Read the function list from `~/.cache/bns-lift/hr/LobbyDaemon/index.tsv`. Match the module name and address for each function. Do not lift compiler-generated deleting destructors as separate source functions.
3. Read the listed pseudocode. Use IDA only when the cache does not settle a question. Close the database when you finish with it.
4. Replace the in-scope stub bodies with C++ that uses PDB types and names.
5. Change `CMakeLists.txt` only if the LobbyDaemon target needs it. Do not change the other server targets.
6. Run `tools/gate.sh` after each module. Compare the final MATCH counts with the baseline.

Use only the exe and PDB in the table. Do not use `LobbyDaemon2019.exe` or build 381. The repo is public. Do not add binaries, PDBs, IDA databases, keys, or abuse notes.

## Files

- `src/Server/LobbyDaemon/GameWorld.cpp`
- `src/Server/LobbyDaemon/FsdShowcaseRecord.cpp`
- `src/Server/LobbyDaemon/RuleSet.cpp`
- `src/Server/LobbyDaemon/LobbyPerfMonitor.cpp`
- `CMakeLists.txt`

## Handoff

Write `Docs/Plan/handoffs/lift-lobbydaemon-9.md`. Record the lifted functions, the gate result, and the baseline and final MATCH counts. Under **Not done**, give the module, PDB name, address, and reason for each function that you did not lift.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function on this card is lifted or listed as **Not done** with its address.
- CacheGate, LobbyGate, SmartCouponDaemon, and PostOfficeDaemon lose no MATCH functions.
- The LobbyDaemon MATCH count does not go down.
