# lift-gamedaemon-44: VC headers and no-file functions: stdio, wchar, xmemory, nofile

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
| Depends on | `lift-gamedaemon-42` |
| Pattern | none |
| Plan | `Docs/Plan/gamedaemon-lift.md` sections 1, 3, 5 |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Grep `Docs/Parity/lessons.md` for A2 (block order), A6 (per-exe path literals), A12 (PDB member types), A18 (destructors), A21 (PDB facts) and A22 (per-exe source form). Do not read it in full.
- Pattern: none. No lifted file has the same role.

## Scope

22 functions, about 390 pseudocode lines (about 3,120 tokens). Stems: `stdio`, `wchar`, `xmemory`, `nofile`.

| n | Exe | RVA | PDB name | Stem | Lines |
| ---: | --- | --- | --- | --- | ---: |
| 1 | GD | `0x10d10` | `swprintf_s<4>` | stdio | 10 |
| 2 | GD | `0x8b8a0` | `swprintf_s<4000>` | wchar | 10 |
| 3 | GD | `0x1db350` | `swprintf_s<1025>` | wchar | 10 |
| 4 | GD | `0x347840` | `swprintf_s<1001>` | wchar | 10 |
| 5 | GD | `0x347870` | `swprintf_s<1024>` | wchar | 10 |
| 6 | GD | `0x671140` | `swprintf_s<40>` | wchar | 10 |
| 7 | GD | `0x6868c0` | `Json::Reader::ErrorInfo::~ErrorInfo` | xmemory | 17 |
| 8 | GD | `0x118e0` | `Data::SlateScrollCache::~SlateScrollCache` | nofile | 15 |
| 9 | GD | `0x157c0` | `ZipPackedReaderIO::FileName::~FileName` | nofile | 38 |
| 10 | GD | `0xc0000` | `LogoutOkParam::~LogoutOkParam` | nofile | 31 |
| 11 | GD | `0x13fd20` | `EnterWorldOkParam::~EnterWorldOkParam` | nofile | 48 |
| 12 | GD | `0x14a320` | `TakeTimeBasedPlayRewardResponseParam::~TakeTimeBasedPlayRewardResponseParam` | nofile | 24 |
| 13 | GD | `0x1b4030` | `RankingSeasonInfo::~RankingSeasonInfo` | nofile | 18 |
| 14 | GD | `0x1ee8e0` | `ZoneCounterSet::~ZoneCounterSet` | nofile | 15 |
| 15 | GD | `0x4bfa70` | `InventoryCacheUpdate::~InventoryCacheUpdate` | nofile | 9 |
| 16 | GD | `0x4bfee0` | `InventoryClientUpdate::~InventoryClientUpdate` | nofile | 7 |
| 17 | GD | `0x5b3750` | `FallDeathEffect::FallDeathEffect` | nofile | 26 |
| 18 | GD | `0x681060` | `Json::Reader::~Reader` | nofile | 40 |
| 19 | GD | `0x6a8430` | `Json::LogicError::~LogicError` | nofile | 8 |
| 20 | GD | `0x6a84d0` | `Json::Exception::Exception` | nofile | 18 |
| 21 | GD | `0x6a85d0` | `Json::LogicError::LogicError` | nofile | 9 |
| 22 | GD | `0x6eba80` | `LoadTableBinder::~LoadTableBinder` | nofile | 7 |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/stdio.cpp`
- `src/Server/GameDaemon/stdio.h`
- `src/Server/GameDaemon/wchar.cpp`
- `src/Server/GameDaemon/wchar.h`
- `src/Server/GameDaemon/xmemory.cpp`
- `src/Server/GameDaemon/xmemory.h`
- `src/Server/GameDaemon/nofile.cpp`
- `src/Server/GameDaemon/nofile.h`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-44.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
