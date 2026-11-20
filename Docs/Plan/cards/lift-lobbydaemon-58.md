# lift-lobbydaemon-58: Remove stubs, link exe, startup check

| Item | Value |
| --- | --- |
| Source build | LobbyDaemon 2019 + PDB (VS2010 SP1) |
| Exe | `/home/ubuntu/Documents/Codex/private-project/ida/lift/LobbyDaemon/LobbyDaemon.exe` |
| PDB | `/home/ubuntu/Documents/Codex/private-project/ida/lift/LobbyDaemon/LobbyDaemon.pdb` |
| Pseudocode | `~/.cache/bns-lift/hr/LobbyDaemon/<Module>.c` (only for remaining stub bodies) |
| Wave | 11 |
| Model | opus |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Read A17, A21, and C4 in `Docs/Parity/lessons.md`. This is the current path for `lessons.md`.
- Read `src/Server/LobbyGate/LobbyGate.cpp` for the startup pattern. Read `lift_exe(LobbyGate ...)` in `CMakeLists.txt` for the link pattern.
- Read `Docs/Plan/handoffs/lift-lobbydaemon-0.md` for the stub marker and grep command. Read the later handoffs for open items.

## Modules

| Module scope | Assigned functions | Entry RVA range |
| --- | ---: | --- |
| No new modules. Check the full LobbyDaemon target. | 0 new | Not applicable |

Use `~/.cache/bns-lift/hr/LobbyDaemon/index.tsv` for function RVAs and pseudocode line spans if you find a stub.

## Tasks

1. Use only the exe and PDB in the table as reference. Do not use `LobbyDaemon2019.exe` or a 381 file.
2. Run `tools/parity.sh CacheGate LobbyGate SmartCouponDaemon PostOfficeDaemon LobbyDaemon` before edits. Save the MATCH names and counts outside the tracked files.
3. Use `grep` to find every stub marker in the LobbyDaemon target sources, including shared sources. Replace each marked stub body in the file scope with the verified body. Do not reproduce security bugs. Record any stub outside the file scope as a blocker. Do not remove a marker to hide a stub.
4. Remove the marker macro after the last use is gone. Run the grep check again. The count of references and definitions must be 0.
5. Link the full `LobbyDaemon` exe. Update the source list in `CMakeLists.txt` only if necessary. Do not add stub bodies to make the link pass.
6. Run `tools/gate.sh` and `tools/vs2010/build.sh LobbyDaemon`. Run the same parity check again. Compare the MATCH names and counts with the results before edits. Record the LobbyDaemon MATCH count from `funcdiff`. Do not update the committed parity baselines.
7. Start the lifted exe in an isolated local test environment with a test config. Check that the exe starts and loads the config. Record the log line or other evidence of the load. Stop the test process. Do not use production services or credentials.

## Files

- `src/Server/LobbyDaemon/*.cpp`
- `CMakeLists.txt`

## Handoff

Write `Docs/Plan/handoffs/lift-lobbydaemon-58.md`. Give the grep command and final count. Record the link and gate results, the before and after MATCH counts, and the startup result. List each function in scope that you did not lift as **Not done**. Give its PDB name, entry RVA, and reason. Do not commit binaries, PDBs, IDA databases, keys, or abuse notes.

## Done when

- The stub marker count is 0. The marker macro is removed. The full LobbyDaemon exe links without stub bodies.
- `tools/gate.sh` prints `gate ok`. The VS2010 SP1 build passes. The handoff gives the LobbyDaemon MATCH count from `funcdiff`.
- The lifted exe starts and loads its test config.
- Each function in scope is lifted or listed as **Not done** in the handoff with its entry RVA. A remaining stub blocks completion.
- No function that was a MATCH loses that status in CacheGate, LobbyGate, SmartCouponDaemon, or PostOfficeDaemon.
- The LobbyDaemon MATCH count does not go down.
