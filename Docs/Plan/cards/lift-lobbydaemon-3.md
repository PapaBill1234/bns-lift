# lift-lobbydaemon-3: CliSessionTable part 1 and containers

| Item | Value |
| --- | --- |
| Source build | LobbyDaemon 2019 + PDB (VS2010 SP1) |
| Exe | `/home/ubuntu/Documents/Codex/private-project/ida/lift/LobbyDaemon/LobbyDaemon.exe` |
| PDB | `/home/ubuntu/Documents/Codex/private-project/ida/lift/LobbyDaemon/LobbyDaemon.pdb` |
| Pseudocode | `~/.cache/bns-lift/hr/LobbyDaemon/<Module>.c` |
| Pseudocode index | `~/.cache/bns-lift/hr/LobbyDaemon/index.tsv` |
| Wave | 1 |
| Model | opus |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Read sections A2 (block order), A15 (map allocator types), A18 (compiler-generated destructors), and A21 (PDB facts) in `Docs/Parity/lessons.md`.
- No pattern file is available.

## Modules

37 functions, about 2,367 pseudocode lines.

The ranges give inclusive function start RVAs. Use the module name and the RVA together.
Do not lift compiler-generated deleting destructors as separate functions.

| Module | Scope | RVA range | Functions | Pseudocode lines |
| --- | --- | --- | ---: | ---: |
| `CliSessionTable` | Part 1 | `0x3cfe0` to `0x3ed50` | 21 | 1,749 |
| `WaitQueue` | Whole module | `0xdc540` to `0xdca20` | 8 | 363 |
| `BoundedList` | Whole module | `0x18540` to `0x18790` | 4 | 146 |
| `RefCntList` | Whole module | `0x64c80` to `0x64da0` | 4 | 109 |

## Tasks

1. Use the listed exe and PDB only. Do not use `LobbyDaemon2019.exe` or a 381 file.
2. Use the index to select the functions in this card. Read their pseudocode. Use IDA only if the cached output is not sufficient. Close the database when you finish.
3. Use PDB types and names. Restore STL calls in place of inlined STL code.
4. Replace only the `CliSessionTable` stub bodies in the specified range. Keep the stubs for the other part.
5. Replace the stub bodies in `WaitQueue`, `BoundedList`, and `RefCntList`. Check the container types and layouts against the PDB.
6. Keep each source file in the LobbyDaemon target. Change `CMakeLists.txt` only if the target needs a source entry. Do not add a second entry.
7. Run `tools/gate.sh` after each module.
8. Compare `tools/funcdiff.py` results with the pre-card baseline. Use the same build settings for both runs. Check function identities as well as counts for the four earlier servers.

## Files

- `src/Server/LobbyDaemon/CliSessionTable.cpp`
- `src/Server/LobbyDaemon/WaitQueue.cpp`
- `src/Server/LobbyDaemon/BoundedList.cpp`
- `src/Server/LobbyDaemon/RefCntList.cpp`
- `CMakeLists.txt`

## Handoff

Write `Docs/Plan/handoffs/lift-lobbydaemon-3.md`.
List the modules and functions that you lifted. List each remaining function under "Not done" with its RVA and the reason.
Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, and PostOfficeDaemon lose no MATCH functions.
- The LobbyDaemon MATCH count does not decrease.
