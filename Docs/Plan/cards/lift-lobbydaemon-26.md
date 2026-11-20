# lift-lobbydaemon-26: LobbyGamePacketHandler part 3

| Item | Value |
| --- | --- |
| Source build | LobbyDaemon 2019 + PDB (VS2010 SP1) |
| Exe | `/home/ubuntu/Documents/Codex/private-project/ida/lift/LobbyDaemon/LobbyDaemon.exe` |
| PDB | `/home/ubuntu/Documents/Codex/private-project/ida/lift/LobbyDaemon/LobbyDaemon.pdb` |
| Pseudocode: LobbyGamePacketHandler | `~/.cache/bns-lift/hr/LobbyDaemon/LobbyGamePacketHandler.c` |
| Wave | 5 |
| Model | sol |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Read A2, A17, A19, A21, A23 and C4 in `Docs/Parity/lessons.md`. This is the current path for `lessons.md`.
- Use `~/.cache/bns-lift/hr/LobbyDaemon/index.tsv` for the function list and pseudocode line spans.
- Read the pattern for LobbyGamePacketHandler once: `src/Server/Economy/PostOfficeDaemon/AgentPacketHandler.cpp`.
- Use `src/Server/LobbyGate/LobbyGatePacketHandler.cpp` as the LobbyGate handler reference.

## Modules

Addresses are function entry RVAs. Both ends of each range are in scope. Counts exclude EH funclets and scalar deleting destructors.

| Module | Scope | RVA range | Functions | Pseudocode lines |
| --- | --- | --- | ---: | ---: |
| `LobbyGamePacketHandler` | Part 3 | `0x90f70` to `0x96360` | 20 | 3,427 |

Keep the 3,500-line limit. Do not add functions to reach 30.

## Tasks

1. Use only the exe and PDB in the table. Do not use `LobbyDaemon2019.exe` or a 381 file.
2. Record the MATCH results before edits. Use `tools/gate.sh` and `tools/parity.sh CacheGate LobbyGate SmartCouponDaemon PostOfficeDaemon LobbyDaemon`. Save the before results outside the tracked files.
3. Read only the function spans in scope. Use IDA only if the cache does not give enough data. Close the database when you finish.
4. Replace the stub bodies in the listed `.cpp` files. Use PDB types and names. Check for an existing body before you lift a function.
   Do not change the bodies or stubs in the other parts of `LobbyGamePacketHandler.cpp`.
   Do not reproduce security bugs. Keep any abuse notes out of the public repo.
5. Change `CMakeLists.txt` only if the LobbyDaemon target needs it. Do not add a source file twice.
6. Run `tools/gate.sh` after each module. Run the same parity check after the last edit. Compare the results with the before results. Do not update the parity baselines.

## Files

- `src/Server/LobbyDaemon/LobbyGamePacketHandler.cpp`
- `CMakeLists.txt`

## Handoff

Write `Docs/Plan/handoffs/lift-lobbydaemon-26.md`. List the functions you lifted. List each function that remains as **Not done**. Give its name, RVA and reason. Record the gate result and the before and after MATCH counts for each exe. Do not write binaries, PDBs, IDA databases, keys or abuse notes to git.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in scope is lifted or is listed as **Not done** in the handoff with its RVA.
- No function that was a MATCH loses that status in CacheGate, LobbyGate, SmartCouponDaemon or PostOfficeDaemon.
- The LobbyDaemon MATCH count does not go down.
