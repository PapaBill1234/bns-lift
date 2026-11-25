# lift-lobbydaemon-39: Appearance job 2, RecoverPcJob

| Item | Value |
| --- | --- |
| Source build | LobbyDaemon 2019 + PDB (VS2010 SP1) |
| Exe | `<work-root>/ida/lift/LobbyDaemon/LobbyDaemon.exe` |
| PDB | `<work-root>/ida/lift/LobbyDaemon/LobbyDaemon.pdb` |
| Pseudocode: ChangeCharacterAppearanceJob | `~/.cache/bns-lift/hr/LobbyDaemon/ChangeCharacterAppearanceJob.c` |
| Pseudocode: RecoverPcJob | `~/.cache/bns-lift/hr/LobbyDaemon/RecoverPcJob.c` |
| Wave | 7 |
| Model | sol |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Read A2, A17, A18, A19, A21 and C4 and the applicable examples in `scd-4` in `Docs/Parity/lessons.md`.
- Use `~/.cache/bns-lift/hr/LobbyDaemon/index.tsv` for the function list and line ranges.
- Read `src/Server/SmartCouponDaemon/CouponJob.cpp` once as the pattern.

## Modules

Use function entry RVAs. Include both ends of each range. Count only functions from the listed module. Do not count EH funclets or scalar deleting destructors.

| Module | Scope | RVA range | Functions | Pseudocode lines |
| --- | --- | --- | ---: | ---: |
| `ChangeCharacterAppearanceJob` | Part 2 | `0x1cf70` to `0x11ea00` | 14 | 1,663 |
| `RecoverPcJob` | Whole module | `0x64e50` to `0x11ef00` | 15 | 1,650 |
| Total | | | 29 | 3,313 |

Keep the 3,500-line limit. Do not add functions to reach 30.

## Tasks

1. Use only the exe and PDB in the table. Do not use `LobbyDaemon2019.exe` or a 381 file.
2. Run `tools/gate.sh` before edits. Run `tools/parity.sh CacheGate LobbyGate SmartCouponDaemon PostOfficeDaemon LobbyDaemon`. Save the MATCH counts and function results outside the tracked files.
3. Read only the indexed functions in scope. Use IDA only if the cache does not give enough data. Close the database when you finish.
4. Replace the stub bodies in the listed `.cpp` files. Use PDB types and names. Check for an existing body before you lift a function.
   Do not change any body or stub outside the given range in `ChangeCharacterAppearanceJob.cpp`.
   Do not reproduce security bugs. Keep abuse notes out of the public repo.
5. Change `CMakeLists.txt` only if the LobbyDaemon target needs it. Do not add a source file twice.
6. Run `tools/gate.sh` after each module. Run the same parity check after the last edit. Compare function status and MATCH counts with the saved results. Do not update the parity baselines.

## Files

- `src/Server/LobbyDaemon/ChangeCharacterAppearanceJob.cpp`
- `src/Server/LobbyDaemon/RecoverPcJob.cpp`
- `CMakeLists.txt`

## Handoff

Write `Docs/Plan/handoffs/lift-lobbydaemon-39.md`. List the functions you lifted. List each function that remains as **Not done**. Give its name, RVA and reason. Record the gate result and the before and after MATCH counts for each exe. Report any parity check that did not run as blocked. Do not put binaries, PDBs, IDA databases, keys or abuse notes in git.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in scope is lifted or is listed as **Not done** in the handoff with its RVA.
- Every function that was a MATCH stays a MATCH in CacheGate, LobbyGate, SmartCouponDaemon and PostOfficeDaemon.
- The LobbyDaemon MATCH count does not go down.
