# lift-gamedaemon-0d: unity pilot and build measurement

| Item | Value |
| --- | --- |
| Source build | GameDaemon 2019 + PDB (VS2010 SP1) |
| Base | branch `lift-gamedaemon-0c` of `<work-root>/gap/clone-gd0c` (tip `c48fb3d`) |
| Wave | 0 |
| Model | sonnet:high |
| Plan | `Docs/Plan/gamedaemon-lift.md` sections 2 (unity build), 7 (build and disk), 9 (risks) |

## Goal

1. Decide if per-file TUs give the same codegen as a unity TU for GameDaemon.
2. Measure build cost. The operator sets the engine limits (ENGINE-ISSUES E7) from your numbers.

## Facts from card 0c (read first)

| Fact | Effect on this card |
| --- | --- |
| `wmain` is a stub. `/OPT:REF` drops nearly all code. funcdiff pairs only 77 functions (55 MATCH, all common code). | A lifted leaf is unpaired unless something keeps it. Add `#pragma comment(linker, "/INCLUDE:<public name>")` for each pilot function with no live caller (lessons.md: grep `/INCLUDE`; public names from `llvm-pdbutil dump -publics`). Write the pragma count in the report. |
| The 0c link (39 s, 0.92 GB peak) measures a nearly empty exe. | Measure the link a second time with all code kept: add `/OPT:NOREF` (keep `/LTCG`) in a local test only, not in a commit. Report both. Also give a scaled estimate for the full lift from the LobbyDaemon ratio (plan section 7) and say which number E7 must use. |
| `LIFT_GAMEDAEMON` is OFF by default. | Configure the clang build with `-DLIFT_GAMEDAEMON=ON` before `tools/vs2010/build.sh GameDaemon`. |
| `tools/gate.sh` needs `LIFT_IDA_DIR` for pdb_layout. | Set `LIFT_IDA_DIR=<lift-root>/ida/lift`. |
| `include/pdb/GameDaemon/types.h` does not compile (120 clang-cl errors, incomplete `Field::Def`, `SyncBuffer::Def`). No source includes it. | Do not include it in the pilot. Write any compile-time problem of the headers that you see. |

## Tasks

1. Scratch clone on the 0c branch:
   ```bash
   git clone --no-hardlinks <work-root>/gap/clone-gd0c <work-root>/gap/clone-gd0d
   cd <work-root>/gap/clone-gd0d && git remote set-url --push origin no_push
   git checkout -b lift-gamedaemon-0d origin/lift-gamedaemon-0c
   cp -r <lift-root>/vendor/zstd/src vendor/zstd/
   ```
2. Unity pilot. Pick 2 small source files of one original unity module that have real MATCH-able code now. The skeleton has only stubs, so lift 10 to 20 short leaf functions (getters, ctors, small helpers) of these 2 files from the pseudocode cache first (`<hr-cache>/GameDaemon/<stem>.c`, grep `// 0x<rva>`). Then build two forms:
   - A: per-file TUs (the skeleton layout).
   - B: one unity TU (`unity_pilot.cpp` that `#include`s the 2 `.cpp` files in the original order; the 2 files leave the CMake source list).
   Run `tools/funcdiff.py` on GameDaemon for both builds. Compare the MATCH sets of the functions of the 2 files. Equal counts and equal sets = per-file TUs are safe. If they differ, list each function, its state in A and B, and the cause from the insn diff.
3. Measure (both on this host, inside slotrun):
   | Item | How |
   | --- | --- |
   | Cold VS2010 build of GameDaemon | empty `build-vs2010` obj dir, `JOBS` default; wall time |
   | Warm build after a change of 1 `.cpp` | touch one stub file; wall time |
   | LTCG link time | the link step alone |
   | Peak RAM of the link | `/usr/bin/time -v` max RSS (Wine `link.exe` and its children); also watch with `ps` if `time` does not see the child |
   | Peak RAM of one cl job | same |
   | Disk | `du -s` of objects, exe, pdb, map; full card dir size |
   | funcdiff time | `tools/funcdiff.py` wall time on GameDaemon |
   Run each heavy step once only.
   Remote (operator note 2026-11-27, owner order "use also remote builds when possible"): measure one GameDaemon build on build3 too, next to the local one. This needs the engine items E2 (wine.tar path) and E8 (toolchain cache). Read `<work-root>/s4/OPERATOR-NOTES.md` first. If E8 is not merged: do the local numbers now, write the build3 row as "waits for E8", and say so in the report. If a remote job fails for GameDaemon, write it in `<work-root>/s4/ENGINE-ISSUES.md`. Run the builds with run_in_background and wait for the notification.
4. Write the numbers into `Docs/Plan/gamedaemon-lift.md` section 7 (replace the ❓ estimates; keep the LobbyDaemon column). Write the unity decision in section 2 ("Rule for GameDaemon"), with the evidence.
5. Write the same numbers in `<work-root>/s4/ENGINE-ISSUES.md` under "E7 data (card 0d)" with a proposal for `disk_guard --peak`, the bwrap `/tmp` size and `slot_peak_mb` (with margin). Say if GameDaemon builds must run one at a time.
6. Do not keep the pilot lift code if it is not a clean lift; the decision and numbers are the deliverable. If the 10 to 20 lifted leaves are honest MATCH lifts in form A, keep them in form A (per-file) in a separate commit. Never fake a MATCH.
7. Commit (author and committer `Claude <noreply@anthropic.com>`, `git commit --no-verify`, no Co-Authored-By). Copy this card to `Docs/Plan/cards/lift-gamedaemon-0d.md` (private paths → `<work-root>` / `<lift-root>`). Do not push. Do not land.

## Rules

- bns-lift is PUBLIC. No binary, PDB, IDA database, pseudocode dump, key or abuse note. PDB names only. Mention no other repo.
- Wrap every build and funcdiff in `<work-root>/bin/slotrun`. Do not set `SLOTRUN_PRIO`.
- Check `df -h /data` before each build. The build guard stops near 21 GB free. Delete your temporary build dirs after the measurement.
- Do not open IDA. Do not edit the engine.
- ASD-STE100. Sizes in tokens. Keep context lean.

## Done when

- Section 7 has measured numbers. Section 2 has the unity decision. ENGINE-ISSUES has the E7 data.

## Report (final message, at most 300 words)

Commit SHA; unity result (functions, A vs B MATCH sets); the measured table; E7 proposal; problems.
