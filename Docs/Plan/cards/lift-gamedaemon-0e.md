# lift-gamedaemon-0e: GameDaemon switch-on (tools lane)

| Item | Value |
| --- | --- |
| Base | bns-lift main `81c0fa3` (card 0c part 2, operator land) or later. |
| Lane | tools (card id `tools-gamedaemon-0e`). The lane refuses `src/*`, `CMakeLists.txt`, `cmake/*`, `vendor/*`. It allows 0 new and 0 lost MATCH. |
| Wave | 0 |
| Model | sonnet:high |

## Goal

GameDaemon is in the default exe lists of bns-lift. The gate builds it and reports it. After this card lands, the operator moves GameDaemon from `pending_binaries` to `binaries` in the engine target. Not before.

## Tasks

1. Scratch clone of main:
   ```bash
   git clone --no-hardlinks <lift-root> <work-root>/gap/clone-gd0e
   cd <work-root>/gap/clone-gd0e && git remote set-url --push origin no_push
   git fetch <upstream> main && git checkout -b tools-gamedaemon-0e FETCH_HEAD
   cp -r <lift-root>/vendor/zstd/src vendor/zstd/
   ```
2. `tools/gate.sh`: add `-DLIFT_GAMEDAEMON=ON` to the cmake configure line. The CMake option stays OFF in CMakeLists.txt (no CMake edit in this lane).
3. `tools/vs2010/build.sh` and `tools/parity.sh`: add `GameDaemon` at the end of the default `EXES` list. Remove the "opt-in until card 0e" comments. Keep the clear error of build.sh for a build dir without the GameDaemon target.
4. `tools/parity.sh` with no `Docs/Parity/baseline/GameDaemon.json`: the gate must report GameDaemon and pass. Check this. Do not write the baseline in this card (the lane allows no new MATCH; the lander makes the first baseline).
5. `tools/parity_readme.py`: add GameDaemon after LobbyDaemon (own row, text "Lift in progress"). It must work when `GameDaemon.json` is missing (skip the row then).
6. Build and check (each in `<work-root>/bin/slotrun`, run_in_background, wait for the notification; check `df -h <work-root>` first):
   - `bash tools/gate.sh` (clang, all targets with GameDaemon).
   - `bash tools/vs2010/build.sh` (default list, now 6 exes).
   - `bash tools/parity.sh` (no `--accept`). The 5 old exes: MATCH counts equal to main. GameDaemon: reported, no baseline.
   Write the wall times of the clang build and the VS2010 build (before and after the change) in the report. The engine sets limits from them.
7. Commit (author and committer `Claude <noreply@anthropic.com>`, `git commit --no-verify`, no Co-Authored-By). Copy this card to `Docs/Plan/cards/lift-gamedaemon-0e.md` (private paths → `<work-root>` / `<lift-root>`, no GitHub URL). Do not push. Do not land.

## Rules

- bns-lift is PUBLIC. No binary, PDB, IDA database, pseudocode, key or abuse note. PDB names only. Mention no other repo.
- Change only `tools/*` and `Docs/Plan/*`. Do not edit the engine.
- Do not set `SLOTRUN_PRIO`. Do not open IDA.
- Wait for a long job only with run_in_background and its notification. Never loop on `pgrep -f "<text>"`: the loop matches its own command line and never ends.
- ASD-STE100. Sizes in tokens. Keep context lean.

## Report (final message, at most 250 words)

Commit SHA; changed files; MATCH counts of the 5 exes (main vs card); GameDaemon parity line; build times before and after; problems.
