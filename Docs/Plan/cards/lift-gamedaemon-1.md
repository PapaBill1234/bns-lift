# lift-gamedaemon-1: zstd (upstream): link the upstream source

| Item | Value |
| --- | --- |
| Exe | GD |
| Source build | GameDaemon 2019 + PDB (VS2010 SP1) |
| Exe file | `<work-root>/ida/lift/GameDaemon/GameDaemon.exe` |
| PDB | `<work-root>/ida/lift/GameDaemon/GameDaemon.pdb` |
| Pseudocode | `~/.cache/bns-lift/hr/GameDaemon/<stem>.c` |
| Pseudocode index | `~/.cache/bns-lift/hr/GameDaemon/index.tsv` (stem, rva, name, first, last, status, source file, part) |
| Wave | W1 |
| Model | sonnet:high |
| Depends on | `lift-gamedaemon-0e` |
| Pattern | `vendor/zstd/README.md` |
| Plan | `Docs/Plan/gamedaemon-lift.md` sections 1, 3, 5 |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Grep `Docs/Parity/lessons.md` for A2 (block order), A6 (per-exe path literals), A12 (PDB member types), A18 (destructors), A21 (PDB facts) and A22 (per-exe source form). Do not read it in full.
- Read A5 (third-party code: vendor the exact upstream commit) in `Docs/Parity/lessons.md` and `vendor/zstd/README.md`.
- Pattern: `vendor/zstd/README.md`. Read it one time. Use its form for the functions of this card.
- Dead-strip: `wmain` and most callers are still `LIFT_STUB` bodies. `/OPT:REF` removes a lifted function that has no live caller, and funcdiff then cannot pair it. For each function in scope with no live caller, add `#pragma comment(linker, "/INCLUDE:<public name>")` in its `.cpp` (public names: `llvm-pdbutil dump -publics`; grep `/INCLUDE` in `Docs/Parity/lessons.md`). Do not add a pragma for a function that a lifted caller keeps.

## Scope

22 functions, about 14,184 pseudocode lines (about 113,472 tokens). Stems: `bitstream`, `entropy_common`, `fse_compress`, `fse_decompress`, `huf_compress`, `xxhash`, `zstd_compress`, `zstd_opt`.

Do not lift these functions by hand. The pseudocode lines are for reference only. A function that is larger than 2,500 lines is in this card because the upstream source gives it.

| n | Exe | RVA | PDB name | Stem | Lines |
| ---: | --- | --- | --- | --- | ---: |
| 1 | GD | `0x6b5b90` | `ZSTD_loadDictionaryContent` | zstd_compress | 47 |
| 2 | GD | `0x6b5cb0` | `ZSTD_loadZstdDictionary` | zstd_compress | 184 |
| 3 | GD | `0x6b6030` | `ZSTD_compressBegin_internal` | zstd_compress | 379 |
| 4 | GD | `0x6b6a20` | `ZSTD_initCDict_internal` | zstd_compress | 125 |
| 5 | GD | `0x6b6d40` | `ZSTD_createCDict_advanced` | zstd_compress | 92 |
| 6 | GD | `0x6b6f00` | `ZSTD_createCDict` | zstd_compress | 30 |
| 7 | GD | `0x6b7230` | `ZSTD_getCParams` | zstd_compress | 89 |
| 8 | GD | `0x6bf2c0` | `ZSTD_updateTree` | zstd_opt | 30 |
| 9 | GD | `0x6bf3d0` | `ZSTD_compressBlock_btopt` | zstd_opt | 2714 |
| 10 | GD | `0x6c1d60` | `ZSTD_compressBlock_btultra` | zstd_opt | 2754 |
| 11 | GD | `0x6c4760` | `ZSTD_compressBlock_btopt_extDict` | zstd_opt | 3162 |
| 12 | GD | `0x6c7aa0` | `ZSTD_compressBlock_btultra_extDict` | zstd_opt | 3199 |
| 13 | GD | `0x6cb0c0` | `FSE_writeNCount_generic` | fse_compress | 139 |
| 14 | GD | `0x6d6670` | `FSE_readNCount` | entropy_common | 207 |
| 15 | GD | `0x6d69f0` | `HUF_readStats` | entropy_common | 122 |
| 16 | GD | `0x6d6bb0` | `XXH64_reset` | xxhash | 27 |
| 17 | GD | `0x6d7360` | `HUF_readCTable` | huf_compress | 128 |
| 18 | GD | `0x6d96d0` | `BIT_initDStream` | bitstream | 89 |
| 19 | GD | `0x6d97f0` | `BIT_reloadDStream` | bitstream | 47 |
| 20 | GD | `0x6d9890` | `FSE_buildDTable` | fse_decompress | 103 |
| 21 | GD | `0x6d9a70` | `FSE_decompress_usingDTable` | fse_decompress | 488 |
| 22 | GD | `0x6da270` | `FSE_decompress_wksp` | fse_decompress | 29 |

### Shared functions

These functions are in shared source. They are not MATCH in each lifted exe that has them.

| PDB name | Shared file | Other exes | Note |
| --- | --- | --- | --- |
| `ZSTD_compressBegin_internal` | `?` | LobbyGate | - |
| `ZSTD_compressBlock_btopt` | `?` | CacheGate, LobbyDaemon, LobbyGate, PostOfficeDaemon, SmartCouponDaemon | EXCLUDED in LobbyDaemon: read its `excluded.tsv` row first |
| `ZSTD_compressBlock_btultra` | `?` | CacheGate, LobbyDaemon, LobbyGate, PostOfficeDaemon, SmartCouponDaemon | EXCLUDED in LobbyDaemon: read its `excluded.tsv` row first |
| `ZSTD_compressBlock_btopt_extDict` | `?` | CacheGate, LobbyDaemon, LobbyGate, PostOfficeDaemon, SmartCouponDaemon | EXCLUDED in LobbyDaemon: read its `excluded.tsv` row first |
| `ZSTD_compressBlock_btultra_extDict` | `?` | CacheGate, LobbyDaemon, LobbyGate, PostOfficeDaemon, SmartCouponDaemon | EXCLUDED in LobbyDaemon: read its `excluded.tsv` row first |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. The other 5 exes build zstd from `vendor/zstd/src` (CMake target `lift_zstd`, upstream commit in `vendor/zstd/README.md`). Link `lift_zstd` into the GameDaemon target. Remove the GameDaemon stubs of these functions if the skeleton made them.
4. Compare each function with funcdiff. If a function stays DIFF, find out if the GameDaemon `blood.lib` used other zstd options or another commit. Write the result. Do not hand-edit the upstream source.
5. Shared functions: fix them in the shared file. If GameDaemon needs another form, use a per-exe copy in `lift_common_gd` or a `LIFT_EXE_` wrapper (A22, pattern 35). The 5 other exes must keep each MATCH. A MATCH to DIFF change needs an `allow-worse.txt` row with the counts.
6. An EXCLUDED function has a proof that no honest source fix exists in that exe. Read the proof first. If the same cause applies to GameDaemon, write the function under "Not done" with the proof reference. Do not edit `excluded.tsv`.
7. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `CMakeLists.txt`
- `src/Server/GameDaemon/bitstream.cpp`
- `src/Server/GameDaemon/entropy_common.cpp`
- `src/Server/GameDaemon/fse_compress.cpp`
- `src/Server/GameDaemon/fse_decompress.cpp`
- `src/Server/GameDaemon/huf_compress.cpp`
- `src/Server/GameDaemon/xxhash.cpp`
- `src/Server/GameDaemon/zstd_compress.cpp`
- `src/Server/GameDaemon/zstd_opt.cpp`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-1.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.

## Status: closed (covered by card 0c shared code)

Card 0c links the upstream zstd source for GameDaemon (`lift_common_gd`). No `LIFT_STUB` is left for these rows. State on the first full GameDaemon funcdiff (main `69967df`):

| Function | RVA | GD state |
| --- | --- | --- |
| `ZSTD_loadDictionaryContent` | `0x6b5b90` | unpaired |
| `ZSTD_loadZstdDictionary` | `0x6b5cb0` | unpaired |
| `ZSTD_compressBegin_internal` | `0x6b6030` | unpaired |
| `ZSTD_initCDict_internal` | `0x6b6a20` | unpaired |
| `ZSTD_createCDict_advanced` | `0x6b6d40` | unpaired |
| `ZSTD_createCDict` | `0x6b6f00` | unpaired |
| `ZSTD_getCParams` | `0x6b7230` | unpaired |
| `ZSTD_updateTree` | `0x6bf2c0` | unpaired |
| `ZSTD_compressBlock_btopt` | `0x6bf3d0` | DIFF |
| `ZSTD_compressBlock_btultra` | `0x6c1d60` | DIFF |
| `ZSTD_compressBlock_btopt_extDict` | `0x6c4760` | DIFF |
| `ZSTD_compressBlock_btultra_extDict` | `0x6c7aa0` | DIFF |
| `FSE_writeNCount_generic` | `0x6cb0c0` | unpaired |
| `FSE_readNCount` | `0x6d6670` | MATCH |
| `HUF_readStats` | `0x6d69f0` | MATCH |
| `XXH64_reset` | `0x6d6bb0` | unpaired |
| `HUF_readCTable` | `0x6d7360` | unpaired |
| `BIT_initDStream` | `0x6d96d0` | MATCH |
| `BIT_reloadDStream` | `0x6d97f0` | MATCH |
| `FSE_buildDTable` | `0x6d9890` | MATCH |
| `FSE_decompress_usingDTable` | `0x6d9a70` | MATCH |
| `FSE_decompress_wksp` | `0x6da270` | MATCH |

- MATCH: 7. DIFF: 4. Unpaired: 11 (no live caller yet; they pair when callers land).
- The 4 DIFF functions MATCH in 4 other exes with the same vendor source. Only the calls score is low. Cause (not verified): LTCG call and inline choices depend on the live call graph, and the GameDaemon call graph is mostly stubs now. Recheck after the W waves. Do not edit vendor code.
