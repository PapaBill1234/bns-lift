# lift-gamedaemon-45: zlib (upstream): link the upstream source

| Item | Value |
| --- | --- |
| Exe | GD |
| Source build | GameDaemon 2019 + PDB (VS2010 SP1) |
| Exe file | `<work-root>/ida/lift/GameDaemon/GameDaemon.exe` |
| PDB | `<work-root>/ida/lift/GameDaemon/GameDaemon.pdb` |
| Pseudocode | `~/.cache/bns-lift/hr/GameDaemon/<stem>.c` |
| Pseudocode index | `~/.cache/bns-lift/hr/GameDaemon/index.tsv` (stem, rva, name, first, last, status, source file, part) |
| Wave | W2 |
| Model | opus |
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

44 functions, about 5,823 pseudocode lines (about 46,584 tokens). Stems: `adler32`, `compress`, `crc32`, `deflate`, `inffast`, `inflate`, `inftrees`, `trees`, `zutil`.

Do not lift these functions by hand. The pseudocode lines are for reference only. A function that is larger than 2,500 lines is in this card because the upstream source gives it.

| n | Exe | RVA | PDB name | Stem | Lines |
| ---: | --- | --- | --- | --- | ---: |
| 1 | GD | `0x2f10` | `adler32` | adler32 | 209 |
| 2 | GD | `0x3220` | `compress2` | compress | 32 |
| 3 | GD | `0x32c0` | `crc32` | crc32 | 10 |
| 4 | GD | `0x32d0` | `crc32_little` | crc32 | 133 |
| 5 | GD | `0x35f0` | `deflateInit2_` | deflate | 81 |
| 6 | GD | `0x37c0` | `deflateResetKeep` | deflate | 44 |
| 7 | GD | `0x38d0` | `flush_pending` | deflate | 27 |
| 8 | GD | `0x3950` | `deflate` | deflate | 474 |
| 9 | GD | `0x4210` | `deflateEnd` | deflate | 30 |
| 10 | GD | `0x42f0` | `read_buf` | deflate | 41 |
| 11 | GD | `0x43a0` | `lm_init` | deflate | 28 |
| 12 | GD | `0x4460` | `longest_match` | deflate | 96 |
| 13 | GD | `0x4610` | `fill_window` | deflate | 138 |
| 14 | GD | `0x4860` | `deflate_stored` | deflate | 143 |
| 15 | GD | `0x4b10` | `deflate_fast` | deflate | 192 |
| 16 | GD | `0x4f80` | `deflate_slow` | deflate | 218 |
| 17 | GD | `0x54a0` | `deflate_rle` | deflate | 171 |
| 18 | GD | `0x57f0` | `deflate_huff` | deflate | 82 |
| 19 | GD | `0x59b0` | `inflate_fast` | inffast | 340 |
| 20 | GD | `0x5ea0` | `inflateResetKeep` | inflate | 31 |
| 21 | GD | `0x5f20` | `inflateReset2` | inflate | 27 |
| 22 | GD | `0x5fc0` | `inflateInit2_` | inflate | 39 |
| 23 | GD | `0x6080` | `updatewindow` | inflate | 69 |
| 24 | GD | `0x6180` | `inflate` | inflate | 1465 |
| 25 | GD | `0x7850` | `inflateEnd` | inflate | 22 |
| 26 | GD | `0x78b0` | `inflate_table` | inftrees | 303 |
| 27 | GD | `0x7d30` | `init_block` | trees | 36 |
| 28 | GD | `0x7db0` | `pqdownheap` | trees | 59 |
| 29 | GD | `0x7ea0` | `gen_bitlen` | trees | 118 |
| 30 | GD | `0x80c0` | `gen_codes` | trees | 45 |
| 31 | GD | `0x8170` | `build_tree` | trees | 92 |
| 32 | GD | `0x83c0` | `scan_tree` | trees | 84 |
| 33 | GD | `0x84b0` | `send_tree` | trees | 292 |
| 34 | GD | `0x8a20` | `build_bl_tree` | trees | 23 |
| 35 | GD | `0x8aa0` | `send_all_trees` | trees | 126 |
| 36 | GD | `0x8d10` | `_tr_stored_block` | trees | 36 |
| 37 | GD | `0x8da0` | `_tr_flush_block` | trees | 118 |
| 38 | GD | `0x8fd0` | `compress_block` | trees | 212 |
| 39 | GD | `0x9440` | `detect_data_type` | trees | 34 |
| 40 | GD | `0x94c0` | `bi_flush` | trees | 25 |
| 41 | GD | `0x9550` | `bi_windup` | trees | 26 |
| 42 | GD | `0x95b0` | `copy_block` | trees | 38 |
| 43 | GD | `0x96a0` | `zcalloc` | zutil | 7 |
| 44 | GD | `0x96b0` | `zcfree` | zutil | 7 |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Find the exact upstream zlib version. Use the version string in the exe data, the function set and the A5 method (count calls, bisect the commits).
4. Vendor it as `vendor/zlib/` with the same method as `vendor/zstd/` (source in `.gitignore`, `README.md` with the URL, the commit and the copy steps). Add a CMake target and link it into GameDaemon only. Remove the GameDaemon stubs of these functions.
5. If the upstream codegen cannot match a function, write it under "Not done" with the reason. Do not hand-lift upstream code.
6. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `vendor/zlib/README.md`
- `.gitignore`
- `CMakeLists.txt`
- `src/Server/GameDaemon/adler32.cpp`
- `src/Server/GameDaemon/compress.cpp`
- `src/Server/GameDaemon/crc32.cpp`
- `src/Server/GameDaemon/deflate.cpp`
- `src/Server/GameDaemon/inffast.cpp`
- `src/Server/GameDaemon/inflate.cpp`
- `src/Server/GameDaemon/inftrees.cpp`
- `src/Server/GameDaemon/trees.cpp`
- `src/Server/GameDaemon/zutil.cpp`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-45.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
