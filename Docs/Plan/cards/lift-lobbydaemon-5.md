# lift-lobbydaemon-5: Mileage part 1 and PcCafe

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
- Read sections A2 (block order), A8 (references and reads), and A21 (PDB facts) in `Docs/Parity/lessons.md`.
- No pattern file is available.

## Modules

30 functions, about 3,205 pseudocode lines.

The ranges give inclusive function start RVAs. Use the module name and the RVA together.
Do not lift compiler-generated deleting destructors as separate functions.

| Module | Scope | RVA range | Functions | Pseudocode lines |
| --- | --- | --- | ---: | ---: |
| `Mileage` | Part 1 | `0x5d370` to `0x5fc30` | 23 | 2,505 |
| `PcCafe` | Whole module | `0x62e90` to `0x63350` | 2 | 334 |
| `PcCafeMileage` | Whole module | `0x633b0` to `0x636b0` | 3 | 291 |
| `MileageDailyLimit` | Whole module | `0x62560` | 1 | 22 |
| `LobbyJSON` | Whole module | `0x2f830` | 1 | 53 |

## Tasks

1. Use the listed exe and PDB only. Do not use `LobbyDaemon2019.exe` or a 381 file.
2. Use the index to select the functions in this card. Read their pseudocode. Use IDA only if the cached output is not sufficient. Close the database when you finish.
3. Use PDB types and names. Restore STL calls in place of inlined STL code.
4. Replace only the `Mileage` stub bodies in the specified range. Keep the stubs for the other part.
5. Replace the stub bodies in `PcCafe`, `PcCafeMileage`, `MileageDailyLimit`, and `LobbyJSON`.
6. Keep each source file in the LobbyDaemon target. Change `CMakeLists.txt` only if the target needs a source entry. Do not add a second entry.
7. Run `tools/gate.sh` after each module.
8. Compare `tools/funcdiff.py` results with the pre-card baseline. Use the same build settings for both runs. Check function identities as well as counts for the four earlier servers.

## Files

- `src/Server/LobbyDaemon/Mileage.cpp`
- `src/Server/LobbyDaemon/PcCafe.cpp`
- `src/Server/LobbyDaemon/PcCafeMileage.cpp`
- `src/Server/LobbyDaemon/MileageDailyLimit.cpp`
- `src/Server/LobbyDaemon/LobbyJSON.cpp`
- `CMakeLists.txt`

## Handoff

Write `Docs/Plan/handoffs/lift-lobbydaemon-5.md`.
List the modules and functions that you lifted. List each remaining function under "Not done" with its RVA and the reason.
Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, and PostOfficeDaemon lose no MATCH functions.
- The LobbyDaemon MATCH count does not decrease.
