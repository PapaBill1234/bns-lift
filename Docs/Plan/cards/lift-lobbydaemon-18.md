# lift-lobbydaemon-18: GamedChannel 1, AccountInventory

| Item | Value |
| --- | --- |
| Source build | LobbyDaemon 2019 + PDB (VS2010 SP1) |
| Exe | `<work-root>/ida/lift/LobbyDaemon/LobbyDaemon.exe` |
| PDB | `<work-root>/ida/lift/LobbyDaemon/LobbyDaemon.pdb` |
| Pseudocode index | `~/.cache/bns-lift/hr/LobbyDaemon/index.tsv` |
| Pseudocode: GamedChannel | `~/.cache/bns-lift/hr/LobbyDaemon/GamedChannel.c` |
| Pseudocode: AccountInventoryChannel | `~/.cache/bns-lift/hr/LobbyDaemon/AccountInventoryChannel.c` |
| Wave | 3 |
| Model | sol |

## Read first
- Read “Lift method” in `Docs/Plan/plan.md`.
- Read sections A2, A12, A17, and A19 in `Docs/Parity/lessons.md`.
- Pattern for `GamedChannel`: `src/Server/LobbyGate/LobbyDChannel.cpp`. Read it once.
- Pattern for `AccountInventoryChannel`: `src/Server/Economy/PostOfficeDaemon/AgentChannel.cpp`. Read it once.

## Modules

| Module | Scope | RVA range | Functions | Pseudocode lines |
| --- | --- | --- | ---: | ---: |
| `GamedChannel` | Part 1 | `0x80300` to `0x82950` | 35 | 1,455 |
| `AccountInventoryChannel` | Whole module | `0x64e0` to `0x8790` | 19 | 1,410 |
| Total | | | 54 | 2,865 |

Use the module name and RVA together. The raw index can also contain compiler-generated entries.

## Tasks
1. Record the pre-change MATCH results. Use the same build and comparison settings for the final check.
2. Use `index.tsv` to select the functions and line ranges for this card. Read only those parts of each pseudocode file. Do not use `LobbyDaemon2019.exe` or a 381 file.
3. Replace only the stub bodies in scope. Use the 2019 PDB types and names. Do not copy packet or type definitions from the pattern server.
4. Leave the stubs for part 2 of `GamedChannel` unchanged. The full module has 64 functions. The limit is 60 functions per card.
5. Lift all functions in the `AccountInventoryChannel` module that are in scope.
6. Keep the existing LobbyDaemon source entries in `CMakeLists.txt`. Change the target only if the card needs it. Do not add duplicate entries.
7. Run `tools/gate.sh` after each module. Check the four earlier servers with the parity gate. Also compare the LobbyDaemon MATCH count before and after the lift. Do not update the baselines.

## Files
- `src/Server/LobbyDaemon/GamedChannel.cpp`
- `src/Server/LobbyDaemon/AccountInventoryChannel.cpp`
- `CMakeLists.txt`

## Handoff
Write `Docs/Plan/handoffs/lift-lobbydaemon-18.md`. Record the functions lifted and the check results. List each remaining function as **Not done**. Give its PDB name, RVA, and reason.

## Done when
- `tools/gate.sh` prints `gate ok`.
- Each function in scope is lifted or listed as **Not done** with its address in the handoff.
- CacheGate, LobbyGate, SmartCouponDaemon, and PostOfficeDaemon lose no MATCH functions.
- The LobbyDaemon MATCH count does not go down.
