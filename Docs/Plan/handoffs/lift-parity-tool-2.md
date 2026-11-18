# Handoff: lift-parity-tool-2

## Done
- `tools/funcdiff.py`: fix 5 (vtable symbol before `string_at`), fix 6 (`.tls` offset as ref `tls:<name>`, with the
  `[reg + reg]` guard), fix 7 (`<K const ,V>`), fix 8 (`?Setup@PacketCrypt@@...` demangled). Proof in `Docs/Parity/noise.md`.
- `tools/vs2010/build.sh`: `/showIncludes` writes `build-vs2010/obj/<src>.dep`. A newer repo header builds the object again.
  Test: no change = 0 objects built; `touch Log.h` = 31 CacheGate objects built.
- `Docs/Parity/allow-worse.txt`: all 47 lines removed (each function is MATCH now). `tool-2-fix.patch` deleted.
- `lessons.md` C1, C2, C3, C4 updated. No change in `src/`.

## Counts (tools/parity.sh, same objects)
| Exe | Start | End | Change | MATCH lost |
| --- | ---: | ---: | ---: | ---: |
| CacheGate | 387/491 | 405/491 = 82.5 % | +18 | 0 |
| LobbyGate | 487/739 | 506/739 = 68.5 % | +19 | 0 |
| SmartCouponDaemon | 461/669 | 484/669 = 72.3 % | +23 | 0 |
| PostOfficeDaemon | 509/759 | 529/759 = 69.7 % | +20 | 0 |
| Shared library | 369/489 = 75.5 % | 397/489 = 81.2 % | +28 | 0 |
Review 1 expected +63 (shared 394). Result: +80 (shared 397). Fix 6 also finds the `mov` that comes before the `gs:` load.
`tools/parity_shared.py build-vs2010 --list`: 92 shared DIFF functions left.

## Not done
- Nothing from the task list. The baseline (`Docs/Parity/baseline/`) is not changed: the runner accepts it.

## ❓
- The first `build-vs2010` after this card builds all objects once (no `.dep` files yet).
- `IoWorker::run` score 85.1 -> 84.9 in 3 exes (a `tls:` ref differs). Not MATCH before or after.

## Blocked
- None.

## Gate result
`tools/gate.sh`: gate ok. `tools/parity.sh`: parity ok, MATCH -> DIFF 0 in all 4 exes.
Setup note: the worktree needed `vendor/zstd/src` at bb6eaf64 and `LIFT_IDA_DIR` (see memory parity-worktree-setup).
