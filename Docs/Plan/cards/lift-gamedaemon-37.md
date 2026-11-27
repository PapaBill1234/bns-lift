# lift-gamedaemon-37: Banned word filter and Shared gaps and others: bannedwordfilterlib, bannedwordfilterloader, constfiltername, table, ...

| Item | Value |
| --- | --- |
| Exe | GD |
| Source build | GameDaemon 2019 + PDB (VS2010 SP1) |
| Exe file | `<work-root>/ida/lift/GameDaemon/GameDaemon.exe` |
| PDB | `<work-root>/ida/lift/GameDaemon/GameDaemon.pdb` |
| Pseudocode | `~/.cache/bns-lift/hr/GameDaemon/<stem>.c` |
| Pseudocode index | `~/.cache/bns-lift/hr/GameDaemon/index.tsv` (stem, rva, name, first, last, status, source file, part) |
| Wave | W1 |
| Model | opus |
| Depends on | `lift-gamedaemon-0e` |
| Pattern | `src/External/BannedWordFilter/BannedWordFilterLoader.cpp` |
| Plan | `Docs/Plan/gamedaemon-lift.md` sections 1, 3, 5 |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Grep `Docs/Parity/lessons.md` for A2 (block order), A6 (per-exe path literals), A12 (PDB member types), A18 (destructors), A21 (PDB facts) and A22 (per-exe source form). Do not read it in full.
- Pattern: `src/External/BannedWordFilter/BannedWordFilterLoader.cpp`. Read it one time. Use its form for the functions of this card.

## Scope

12 functions, about 1,740 pseudocode lines (about 13,920 tokens). Stems: `bannedwordfilterlib`, `bannedwordfilterloader`, `constfiltername`, `table`, `twofish2`.

| n | Exe | RVA | PDB name | Stem | Lines |
| ---: | --- | --- | --- | --- | ---: |
| 1 | GD | `0x6ea100` | `BannedWordFilterLib::LoadNameFilterBuffer` | bannedwordfilterlib | 31 |
| 2 | GD | `0x6ea630` | `BannedWordFilterLoader::~BannedWordFilterLoader` | bannedwordfilterloader | 87 |
| 3 | GD | `0x6ea880` | `BannedWordFilterLoader::LoadNameFilter` | bannedwordfilterloader | 119 |
| 4 | GD | `0x6eaf00` | `ConstFilterName` | constfiltername | 203 |
| 5 | GD | `0x1d050` | `DrElIter::~DrElIter` | table | 8 |
| 6 | GD | `0x39d410` | `ParseHexDword` | twofish2 | 52 |
| 7 | GD | `0x39d4e0` | `RS_MDS_Encode` | twofish2 | 49 |
| 8 | GD | `0x39d680` | `BuildMDS` | twofish2 | 181 |
| 9 | GD | `0x39db80` | `ReverseRoundSubkeys` | twofish2 | 31 |
| 10 | GD | `0x39dbd0` | `Xor256` | twofish2 | 73 |
| 11 | GD | `0x39dee0` | `reKey` | twofish2 | 520 |
| 12 | GD | `0x39ead0` | `blockEncrypt` | twofish2 | 386 |

### Shared functions

These functions are in shared source. They are not MATCH in each lifted exe that has them.

| PDB name | Shared file | Other exes | Note |
| --- | --- | --- | --- |
| `BannedWordFilterLoader::LoadNameFilter` | `src/External/BannedWordFilter/BannedWordFilterLoader.cpp` | LobbyDaemon | EXCLUDED in LobbyDaemon: read its `excluded.tsv` row first |
| `ConstFilterName` | `src/External/BannedWordFilter/ConstFilterName.cpp` | LobbyDaemon | - |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Shared functions: fix them in the shared file. If GameDaemon needs another form, use a per-exe copy in `lift_common_gd` or a `LIFT_EXE_` wrapper (A22, pattern 35). The 5 other exes must keep each MATCH. A MATCH to DIFF change needs an `allow-worse.txt` row with the counts.
6. An EXCLUDED function has a proof that no honest source fix exists in that exe. Read the proof first. If the same cause applies to GameDaemon, write the function under "Not done" with the proof reference. Do not edit `excluded.tsv`.
7. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/bannedwordfilterlib.cpp`
- `src/Server/GameDaemon/bannedwordfilterlib.h`
- `src/Server/GameDaemon/bannedwordfilterloader.cpp`
- `src/Server/GameDaemon/bannedwordfilterloader.h`
- `src/External/BannedWordFilter/BannedWordFilterLoader.cpp`
- `src/External/BannedWordFilter/ConstFilterName.cpp`
- `src/Server/GameDaemon/table.cpp`
- `src/Server/GameDaemon/table.h`
- `src/Server/GameDaemon/twofish2.cpp`
- `src/Server/GameDaemon/twofish2.h`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-37.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
