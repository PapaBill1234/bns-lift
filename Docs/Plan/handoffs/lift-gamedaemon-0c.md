# lift-gamedaemon-0c handoff

Stamp: 2026-11-27 03:01Z. Card: GameDaemon skeleton and stubs (S4, wave 0). Source: GameDaemon.exe and
GameDaemon.pdb (2019 + PDB, VS2010 SP1). Wave 0 lifts no logic. A stub is not a lift.

## Result

| Check | Result |
| --- | --- |
| `tools/gate.sh` (build dir configured with `-DLIFT_GAMEDAEMON=ON`) | gate ok; pdb_layout 3211 classes, 0 errors |
| Clang link of `GameDaemon.exe` | ok |
| VS2010 link (`tools/vs2010/build.sh GameDaemon`) | ok, `build-vs2010/GameDaemon.exe` and `GameDaemon.map` |
| `tools/parity.sh` (no `--accept`) | parity ok. CG, LG, SCD, POD, LD: +0, no MATCH lost |
| `tools/funcdiff.py GameDaemon` | 55 MATCH, 77 paired, 12,774 only in original |
| Lifted functions | 0 |

## MATCH comparison (VS2010 /GL /LTCG)

| Exe | Baseline MATCH | Branch MATCH |
| --- | --- | --- |
| CacheGate | 475 | 475 |
| LobbyGate | 701 | 701 |
| SmartCouponDaemon | 649 | 649 |
| PostOfficeDaemon | 733 | 733 |
| LobbyDaemon | 1038 | 1038 |
| GameDaemon | none | 55 (common code only: zstd, HeapMemoryManager, AlertSender, Thread, DrHeapMemory) |

## Build measurements (for card 0d)

| Item | Value |
| --- | --- |
| VS2010 cold build of GameDaemon (563 sources, 8 jobs, shared host) | 8 min 51 s compile and first link try; plus the link |
| VS2010 link only (`link /LTCG /OPT:REF /OPT:ICF /MAP`) | 39 s |
| Peak RAM of the link (`/usr/bin/time -v`, link.exe under Wine) | 0.92 GB |
| VS2010 objects of GameDaemon | 542 MB |
| Clang build of `lift_gamedaemon` only | 1 min 45 s |
| Clang base build of the default exes (no GameDaemon) | 49 s |

The link is small and fast because `wmain` is a stub: `/OPT:REF` drops nearly all code. The values are not
representative for a GameDaemon with real logic.

## Function split (12,851 counted functions)

| Result | Count | Where |
| --- | --- | --- |
| `LIFT_STUB` body | 11,923 | `src/Server/GameDaemon/<module>.cpp` (`.c` for zlib) |
| Feature off (`// LIFT: feature off (owner scope)`) | 35 | anti-cheat glue (33) and TencentProtect (2) |
| No body: template instance | 134 | comment line with the RVA |
| No body: shared class, other form | 70 | comment line; W1 (pattern 35: `lift_common_gd` copy or `LIFT_EXE_GD`) |
| No body: funclet (`wmain$dtor$0`) | 1 | comment line |
| Linked from existing shared sources (`lift_common_gd`) | 527 | BloodLib, BloodCrypto, Shared, Packet, BannedWordFilter, FsdDecomposer |
| zstd (vendor/zstd) | 118 | `lift_zstd` |
| CRT | 32 | VS2010 CRT |
| Vendor anti-cheat server lib | 11 | not lifted, not linked |

Full list (module, RVA, result, PDB name) of the 12,163 Not done rows: `lift-gamedaemon-0c-notdone.tsv`.

## Layout

| Item | Value |
| --- | --- |
| Modules | 476 sources: one per `index.tsv` module (part files `<stem>_1.cpp`, ...), `nofile.cpp` for 19 functions |
| Headers | one per original source basename. A name that clashes with a repo or SDK header gets `_gd.h` (14 headers) |
| `GameDaemonFwd.h` | LIFT: build helper. Forward declarations and empty types that have no owner module yet |
| `LinkStubs.cpp` | hand-written. `ClientSideDaemonChannel::onAccept` (folded at 0x455420) and `SmartCouponDaemonTypeDesc` (0xe8ec38) |
| `CMakeLists.txt` | inline module list of `lift_gamedaemon` (one line per module; no `*.cmake` file, because the proof pins `*.cmake`) |
| Classes | no members and no bases yet. Later waves add the PDB layouts |
| Shared headers | 27 GameDaemon-only member declarations and 1 empty nested enum (`XmlReaderIO::ErrCode`). No codegen change for the other exes (parity +0) |

## CMake

| Item | Decision | Reason |
| --- | --- | --- |
| `LIFT_GAMEDAEMON` | default OFF | 476 modules and the `lift_common_gd` copy add more than 100 % to the 49 s default clang build. The card limit is 10 % |
| `lift_common_gd` | full copy of the common sources without BloodCert, plus MemoryManager, RefCntObject, PerfCounterProvider, BannedWordFilter, FsdDecomposer, Shared | It does not link `lift_common`, so BloodCert stays out and the other exes keep their objects and order |
| `tools/vs2010/build.sh` | tag `GD`, `/MAP` for GameDaemon only, clear error when the clang build has no GameDaemon target | default exe list unchanged (card 0e) |
| `tools/pdb_layout.py` | GameDaemon targets map to the GameDaemon PDB | |

To build: `cmake -S . -B build ... -DLIFT_GAMEDAEMON=ON`, then `tools/gate.sh` (the cache keeps the option),
then `tools/vs2010/build.sh GameDaemon`. `tools/gate.sh` needs `LIFT_IDA_DIR` for pdb_layout.

## Open items

| Item | Note |
| --- | --- |
| `include/pdb/GameDaemon/types.h` | 6.2 MB, about 1.6 M tokens ❓ (4 bytes per token). No source includes it. clang-cl gives 120 errors (incomplete `Field::Def` and `SyncBuffer::Def` in class `Property`). A test compile takes about 1.5 s, so no split. Fix pdb2h (nested type order) before a selftest TU includes it |
| Path literals | `lift_common_gd` uses the plain BloodLib files with the CacheGate default `__FILE__` paths (A5). W1 adds the GameDaemon wrappers |
| `SmartCouponDaemonTypeDesc` | GameDaemon module of the definition not known ❓ |
| Shared-form functions | 70 (list: `result` = `shared-form` in the TSV). W1 |
| Generator | Not committed (it reads private dumps). Do not run it again over lifted files. It deletes and writes `src/Server/GameDaemon/`: keep `LinkStubs.cpp` |
| `parity_readme.py`, `parity.sh` default lists | unchanged on purpose (card 0e) |
