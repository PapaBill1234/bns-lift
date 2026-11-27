# lift-gamedaemon-0c: GameDaemon skeleton and stubs

| Item | Value |
| --- | --- |
| Source build | GameDaemon 2019 + PDB (VS2010 SP1) |
| Exe / PDB | `<work-root>/ida/lift/GameDaemon/GameDaemon.exe`, `.pdb` (read only) |
| Pseudocode | `~/.cache/bns-lift/hr/GameDaemon/<stem>.c` |
| Pseudocode index | `~/.cache/bns-lift/hr/GameDaemon/index.tsv` (module, rva, name, first, last, status, source file, part) and `files.tsv` (stem, source file, part, counted, lines, low RVA, high RVA) |
| Base | branch `tools-gamedaemon-0a` of `<scratch>/gap/clone-gd0a` |
| Wave | 0 |
| Model | opus |
| Plan | `Docs/Plan/gamedaemon-lift.md` sections 1, 2, 4, 7 |

`<work-root>` = `<work-root>`.

## Read first

- `Docs/Plan/gamedaemon-lift.md` sections 1 (anti-cheat handling), 2 (unity build, part files), 4.
- `Docs/Plan/cards/lift-lobbydaemon-0.md`: the skeleton pattern. Use the `LobbyDaemon` target and `lift_common_ld` in `CMakeLists.txt` as the build pattern.
- `Docs/Plan/plan.md` "Lift method" and "VS2010 SP1 compiler".
- Grep `Docs/Parity/lessons.md` for A12 (PDB types), A18 (destructors), A22 (per-exe source), C4 (build facts), pattern 35 (per-exe copies). Do not read it in full.
- `include/LiftStub.h` (or where `LIFT_STUB` is defined).

## Tasks

1. Scratch clone on the 0a branch:
   ```bash
   git clone --no-hardlinks <scratch>/gap/clone-gd0a <scratch>/gap/clone-gd0c
   cd <scratch>/gap/clone-gd0c && git remote set-url --push origin no_push
   git checkout -b lift-gamedaemon-0c origin/tools-gamedaemon-0a
   cp -r <lift-root>/vendor/zstd/src vendor/zstd/   # git-ignored
   ```
2. `include/pdb/GameDaemon/types.h` from `python3 -I tools/pdb2h.py <pdb> GameDaemon --out include/pdb`. If the file is very large, split it per area only if the compile time demands it; write the reason.
3. Shared code. Many GameDaemon functions are in shared code that is already lifted (BloodLib, BloodCrypto, `src/Server/Shared`, `src/Server/Packet`, CRT). Link the existing shared sources. Do not make stubs that duplicate a lifted shared function. A shared function that GameDaemon needs in another form goes into `lift_common_gd` (pattern 35 and A22: per-exe copy or `LIFT_EXE_` wrapper), not into the shared file. Do not change any shared source in a way that changes codegen of the 5 other exes.
4. New sources in `src/Server/GameDaemon/`: one `.h` and one `.cpp` per original source file. For a source file that `files.tsv` splits into parts, one `.cpp` per part (`pc_1.cpp`, `pc_2.cpp`, ...) with the same RVA ranges. The `.cpp` stem is the `index.tsv` module column, so a card edits whole files. Each function gets a `LIFT_STUB` body with its RVA comment as in LobbyDaemon. The 19 no-file functions go to `src/Server/GameDaemon/nofile.cpp`.
5. Anti-cheat (plan section 1): vendor libraries (GameGuard server lib, NCGuard server lib, BloodCert): do not lift, do not link. GameDaemon glue (NCGuard, GameGuard, XIGNCode3 classes, timers, handlers) and TencentProtect: "feature off" bodies with a `// LIFT: feature off (owner scope)` note. Do not use `LIFT_STUB` for them. Write no anti-cheat internals into comments.
6. CMake: `add_library(lift_gamedaemon ...)`, `lift_common_gd`, `lift_exe(GameDaemon ...)`. GameDaemon stays opt-in: do not add it to the default exe lists (`tools/vs2010/build.sh` default, `tools/parity.sh`, `tools/parity_readme.py`). That is card 0e. Use a CMake option such as `LIFT_GAMEDAEMON` (default ON for the clang build only if the default build of the other exes does not slow down by more than about 10 %; else OFF; write the reason). The VS2010 build must be able to build GameDaemon by name.
7. Make the `LiftStub.h` comment general: the RVA in a stub is the RVA in the exe of the module (not only LobbyDaemon).
8. Build:
   ```bash
   <scratch>/bin/slotrun bash tools/gate.sh            # clang build; see the script for options
   <scratch>/bin/slotrun bash tools/vs2010/build.sh GameDaemon
   ```
   Check the log for "link FAIL". Measure the cold build time, the link time and the peak RAM of the link (`/usr/bin/time -v` around the link if possible). Write them in your report: card 0d uses them.
9. Other 5 exes: run the gate (`<scratch>/bin/slotrun bash tools/vs2010/build.sh` default list, then `tools/parity.sh` without `--accept`, or `buildonce gate` as AGENT-RULES says). MATCH counts of CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon, LobbyDaemon must not go down. Record the counts before and after.
10. Commit in small steps (types.h, shared wiring, stubs, CMake). Author and committer `Claude <noreply@anthropic.com>`, `git commit --no-verify`, no Co-Authored-By. Copy this card to `Docs/Plan/cards/lift-gamedaemon-0c.md` (private paths → `<work-root>` / `<lift-root>`). Write a handoff `Docs/Plan/handoffs/lift-gamedaemon-0c.md` (pattern: other handoffs in that dir). Do not push. Do not land.

## Rules

- bns-lift is PUBLIC. No binary, PDB, IDA database, pseudocode dump, key, abuse note or anti-cheat internals. PDB names only. Mention no other repo.
- Never fake a MATCH. A stub is a stub.
- Logic 2019 + PDB. Server checks stay. Packets follow 381 (no packet logic in this card).
- Wrap every build in `<scratch>/bin/slotrun`. Do not set `SLOTRUN_PRIO`. Long builds: run_in_background and wait for the notification.
- Check `<scratch>` free space before big builds (`df -h /data`). The build guard stops near 21 GB free. Delete your own large temporary build dirs when you are done; keep `build-vs2010/GameDaemon.exe` and the map for card 0d.
- Do not open IDA. Do not edit the engine.
- Write all text in ASD-STE100. Sizes in tokens. Keep context lean: grep, line ranges, generator scripts.

## Done when

- `slotrun bash tools/vs2010/build.sh GameDaemon` links GameDaemon.exe.
- The other 5 exes lose no MATCH.
- Commits are on branch `lift-gamedaemon-0c`.

## Report (final message, at most 350 words)

Commit SHAs; number of new files; stub count; shared functions linked; off bodies; types.h size (tokens); CMake option decision; cold build time, link time, peak link RAM, object disk; MATCH counts of the 5 exes before and after; GameDaemon MATCH count if `tools/funcdiff.py` runs on it; problems.
