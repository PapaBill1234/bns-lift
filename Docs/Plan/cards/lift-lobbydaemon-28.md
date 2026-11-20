# lift-lobbydaemon-28: NPServiceChannel, Transaction

| Item | Value |
| --- | --- |
| Source build | LobbyDaemon 2019 + PDB (VS2010 SP1) |
| Exe | `/home/ubuntu/Documents/Codex/private-project/ida/lift/LobbyDaemon/LobbyDaemon.exe` |
| PDB | `/home/ubuntu/Documents/Codex/private-project/ida/lift/LobbyDaemon/LobbyDaemon.pdb` |
| Pseudocode: NPServiceChannel | `~/.cache/bns-lift/hr/LobbyDaemon/NPServiceChannel.c` |
| Pseudocode: TransactionChannel | `~/.cache/bns-lift/hr/LobbyDaemon/TransactionChannel.c` |
| Wave | 5 |
| Model | sol |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Read A2, A17, A18, A19, A21 and C4 in `Docs/Parity/lessons.md`. This is the current path for `lessons.md`.
- Use `~/.cache/bns-lift/hr/LobbyDaemon/index.tsv` for the function list and pseudocode line spans.
- Read the pattern for NPServiceChannel once: `src/Server/SmartCouponDaemon/NPServiceChannel.cpp`.
- Read the pattern for TransactionChannel once: `src/Server/Economy/PostOfficeDaemon/AgentChannel.cpp`.
- Use `src/Server/LobbyGate/LobbyDChannel.cpp` as the LobbyGate channel reference.

## Modules

Addresses are function entry RVAs. Both ends of each range are in scope. Counts exclude EH funclets and scalar deleting destructors.

| Module | Scope | RVA range | Functions | Pseudocode lines |
| --- | --- | --- | ---: | ---: |
| `NPServiceChannel` | Whole module | `0xcfac0` to `0xd2310` | 40 | 1,817 |
| `TransactionChannel` | Whole module | `0x7b0d0` to `0x7b7e0` | 9 | 331 |
| Total | | | 49 | 2,148 |

## Tasks

1. Use only the exe and PDB in the table. Do not use `LobbyDaemon2019.exe` or a 381 file.
2. Record the MATCH results before edits. Use `tools/gate.sh` and `tools/parity.sh CacheGate LobbyGate SmartCouponDaemon PostOfficeDaemon LobbyDaemon`. Save the before results outside the tracked files.
3. Read only the function spans in scope. Use IDA only if the cache does not give enough data. Close the database when you finish.
4. Replace the stub bodies in the listed `.cpp` files. Use PDB types and names. Check for an existing body before you lift a function.
   Do not reproduce security bugs. Keep any abuse notes out of the public repo.
5. Change `CMakeLists.txt` only if the LobbyDaemon target needs it. Do not add a source file twice.
6. Run `tools/gate.sh` after each module. Run the same parity check after the last edit. Compare the results with the before results. Do not update the parity baselines.

## Files

- `src/Server/LobbyDaemon/NPServiceChannel.cpp`
- `src/Server/LobbyDaemon/TransactionChannel.cpp`
- `CMakeLists.txt`

## Handoff

Write `Docs/Plan/handoffs/lift-lobbydaemon-28.md`. List the functions you lifted. List each function that remains as **Not done**. Give its name, RVA and reason. Record the gate result and the before and after MATCH counts for each exe. Do not write binaries, PDBs, IDA databases, keys or abuse notes to git.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in scope is lifted or is listed as **Not done** in the handoff with its RVA.
- No function that was a MATCH loses that status in CacheGate, LobbyGate, SmartCouponDaemon or PostOfficeDaemon.
- The LobbyDaemon MATCH count does not go down.
