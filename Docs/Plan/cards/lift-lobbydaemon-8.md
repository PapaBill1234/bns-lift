# lift-lobbydaemon-8: CliSessionTable part 2, LobbyToken

| Item | Value |
| --- | --- |
| Source build | LobbyDaemon 2019 + PDB (VS2010 SP1) |
| Exe | `/home/ubuntu/Documents/Codex/private-project/ida/lift/LobbyDaemon/LobbyDaemon.exe` |
| PDB | `/home/ubuntu/Documents/Codex/private-project/ida/lift/LobbyDaemon/LobbyDaemon.pdb` |
| Pseudocode | `~/.cache/bns-lift/hr/LobbyDaemon/CliSessionTable.c`<br>`~/.cache/bns-lift/hr/LobbyDaemon/LobbyToken.c` |
| Wave | 2 |
| Model | opus |

## Read first

- Read `Docs/Plan/plan.md`, "Lift method".
- Read `Docs/Parity/lessons.md`, sections A2, A21, A12, A17, C4.
- Pattern: none.

## Modules

| Module | Scope | RVA range | Functions | Pseudocode lines |
| --- | --- | --- | ---: | ---: |
| `CliSessionTable` | Part 2 | `0x3eef0` to `0xc2510` | 24 | 1,739 |
| `LobbyToken` | Whole module | `0x96750` to `0x97990` | 10 | 819 |
| Total | | | 34 | 2,558 |

Use the address range with the module name. The range can contain functions from other modules. The function counts exclude compiler-generated deleting destructors.

- Keep token validation and rejection checks. Do not add a bypass, a token generator for tests, or key material. Use synthetic fixtures for tests.

## Tasks

1. Record the baseline MATCH counts for CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon, and LobbyDaemon. Use the same comparison settings for the final counts.
2. Read the function list from `~/.cache/bns-lift/hr/LobbyDaemon/index.tsv`. Match the module name and address for each function. Do not lift compiler-generated deleting destructors as separate source functions.
3. Read the listed pseudocode. Use IDA only when the cache does not settle a question. Close the database when you finish with it.
4. Replace the in-scope stub bodies with C++ that uses PDB types and names. In `CliSessionTable.cpp`, change only the functions in the listed range. Keep the stubs and lifted bodies of the other parts.
5. Change `CMakeLists.txt` only if the LobbyDaemon target needs it. Do not change the other server targets.
6. Run `tools/gate.sh` after each module. Compare the final MATCH counts with the baseline.

Use only the exe and PDB in the table. Do not use `LobbyDaemon2019.exe` or build 381. The repo is public. Do not add binaries, PDBs, IDA databases, keys, or abuse notes.

## Files

- `src/Server/LobbyDaemon/CliSessionTable.cpp`
- `src/Server/LobbyDaemon/LobbyToken.cpp`
- `CMakeLists.txt`

## Handoff

Write `Docs/Plan/handoffs/lift-lobbydaemon-8.md`. Record the lifted functions, the gate result, and the baseline and final MATCH counts. Under **Not done**, give the module, PDB name, address, and reason for each function that you did not lift.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function on this card is lifted or listed as **Not done** with its address.
- CacheGate, LobbyGate, SmartCouponDaemon, and PostOfficeDaemon lose no MATCH functions.
- The LobbyDaemon MATCH count does not go down.
