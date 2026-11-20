# lift-lobbydaemon-2: CliSession part 1

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
- Read sections A2 (block order), A4 (out-of-line calls), and A21 (PDB facts) in `Docs/Parity/lessons.md`.
- No pattern file is available.

## Modules

29 functions, about 2,518 pseudocode lines. The 3,500-line limit takes priority over the 30-function minimum.

The ranges give inclusive function start RVAs. Use the module name and the RVA together.
Do not lift compiler-generated deleting destructors as separate functions.

| Module | Scope | RVA range | Functions | Pseudocode lines |
| --- | --- | --- | ---: | ---: |
| `CliSession` | Part 1 | `0x329d0` to `0x35eb0` | 29 | 2,518 |

## Tasks

1. Use the listed exe and PDB only. Do not use `LobbyDaemon2019.exe` or a 381 file.
2. Use the index to select the functions in this card. Read their pseudocode. Use IDA only if the cached output is not sufficient. Close the database when you finish.
3. Use PDB types and names. Restore STL calls in place of inlined STL code.
4. Replace only the `CliSession` stub bodies in the specified range. Keep the stubs for all other parts.
5. Keep each source file in the LobbyDaemon target. Change `CMakeLists.txt` only if the target needs a source entry. Do not add a second entry.
6. Run `tools/gate.sh` after each module.
7. Compare `tools/funcdiff.py` results with the pre-card baseline. Use the same build settings for both runs. Check function identities as well as counts for the four earlier servers.

## Files

- `src/Server/LobbyDaemon/CliSession.cpp`
- `CMakeLists.txt`

## Handoff

Write `Docs/Plan/handoffs/lift-lobbydaemon-2.md`.
List the modules and functions that you lifted. List each remaining function under "Not done" with its RVA and the reason.
Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, and PostOfficeDaemon lose no MATCH functions.
- The LobbyDaemon MATCH count does not decrease.
