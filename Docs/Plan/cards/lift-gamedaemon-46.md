# lift-gamedaemon-46: minizip (upstream): link the upstream source

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
| Depends on | `lift-gamedaemon-45` |
| Pattern | `vendor/zstd/README.md` |
| Plan | `Docs/Plan/gamedaemon-lift.md` sections 1, 3, 5 |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Grep `Docs/Parity/lessons.md` for A2 (block order), A6 (per-exe path literals), A12 (PDB member types), A18 (destructors), A21 (PDB facts) and A22 (per-exe source form). Do not read it in full.
- Read A5 (third-party code: vendor the exact upstream commit) in `Docs/Parity/lessons.md` and `vendor/zstd/README.md`.
- Pattern: `vendor/zstd/README.md`. Read it one time. Use its form for the functions of this card.

## Scope

20 functions, about 1,663 pseudocode lines (about 13,304 tokens). Stems: `ioapi`, `unzip`.

Do not lift these functions by hand. The pseudocode lines are for reference only. A function that is larger than 2,500 lines is in this card because the upstream source gives it.

| n | Exe | RVA | PDB name | Stem | Lines |
| ---: | --- | --- | --- | --- | ---: |
| 1 | GD | `0x1040` | `fopen64_file_func` | ioapi | 26 |
| 2 | GD | `0x1090` | `fread_file_func` | ioapi | 7 |
| 3 | GD | `0x10b0` | `fwrite_file_func` | ioapi | 7 |
| 4 | GD | `0x10d0` | `ftell64_file_func` | ioapi | 7 |
| 5 | GD | `0x10e0` | `fseek64_file_func` | ioapi | 27 |
| 6 | GD | `0x1140` | `fclose_file_func` | ioapi | 7 |
| 7 | GD | `0x1150` | `ferror_file_func` | ioapi | 7 |
| 8 | GD | `0x1160` | `unz64local_getShort` | unzip | 50 |
| 9 | GD | `0x1210` | `unz64local_getLong` | unzip | 84 |
| 10 | GD | `0x1340` | `unz64local_getLong64` | unzip | 156 |
| 11 | GD | `0x1570` | `unz64local_SearchCentralDir` | unzip | 109 |
| 12 | GD | `0x1730` | `unz64local_SearchCentralDir64` | unzip | 159 |
| 13 | GD | `0x19f0` | `unzOpenInternal` | unzip | 334 |
| 14 | GD | `0x2140` | `unz64local_GetCurrentFileInfoInternal` | unzip | 244 |
| 15 | GD | `0x25f0` | `unzGoToFirstFile` | unzip | 20 |
| 16 | GD | `0x2660` | `unzGoToNextFile` | unzip | 30 |
| 17 | GD | `0x2710` | `unz64local_CheckCurrentFileCoherencyHeader` | unzip | 124 |
| 18 | GD | `0x2960` | `unzOpenCurrentFile3` | unzip | 89 |
| 19 | GD | `0x2b40` | `unzReadCurrentFile` | unzip | 148 |
| 20 | GD | `0x2e50` | `unzCloseCurrentFile` | unzip | 28 |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Find the exact upstream minizip version. Use the version string in the exe data, the function set and the A5 method (count calls, bisect the commits).
4. Vendor it as `vendor/minizip/` with the same method as `vendor/zstd/` (source in `.gitignore`, `README.md` with the URL, the commit and the copy steps). Add a CMake target and link it into GameDaemon only. Remove the GameDaemon stubs of these functions.
5. If the upstream codegen cannot match a function, write it under "Not done" with the reason. Do not hand-lift upstream code.
6. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `vendor/minizip/README.md`
- `.gitignore`
- `CMakeLists.txt`
- `src/Server/GameDaemon/ioapi.cpp`
- `src/Server/GameDaemon/unzip.cpp`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-46.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
