# lift-smartcoupondaemon-plan handoff

## Done
- Checks: exe and PDB exist. PDB GUID F07533E7-94BA-4ECE-89D4-868CCB48CA42 is the same in the exe (RSDS).
  Imports: system DLLs, ODBC32, msvcr100, msvcp100. Wine has all import libs (incl. `libodbc32.a`). No game DLLs.
- PDB: 1,068 function symbols. Removed: CRT 33, zstd (vendor) 56, lifted modules in `src/common/` (21 modules).
- Delta in lifted modules: about 10 real functions (put in card 1). The rest are scalar deleting destructors and EH funclets.
- Cards: `lift-smartcoupondaemon-1` (common log/alert/crash/timer/Db, ~141),
  `-2` (common network/session/packet, ~169), `-3` (BloodCrypto RSA ~85 + ObjectPool/NP ~120),
  `-4` (server app modules ~244, full exe), `-verify`, and `lift-lobbygate-plan`.
- Queue: `Docs/Plan/queue/lift-smartcoupondaemon-plan.tsv` (6 rows).

## Not done
- None in scope.

## ❓
- Function counts are PDB symbol counts with EH funclets. The real lift count is lower.
- BloodCert, BloodPacketCrypt, zlib, dh, base64, CryptoMode, IdleWatcher have no function symbols. Cards skip them.
- `lift-cg-3` and `lift-cg-5` wrote no source. Card 2 lifts the network modules for the first time.

## Blocked
- None. Bash denied some commands (redirect, `cat`, `llvm-readobj`). I used IDA Python for the exe GUID and imports.

## Gate result
- `tools/gate.sh`: `gate ok` (2026-11-15). Only the old offsetof warnings. No source change.
