# lift-gamedaemon-66: Property headers and Data packer and others: skillpage, skillskinproperty, summonedproperty, weaponproperty, ...

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
| Depends on | `lift-gamedaemon-e13`, `lift-gamedaemon-e14`, `lift-gamedaemon-e26`, `lift-gamedaemon-2`, `lift-gamedaemon-35`, `lift-gamedaemon-46` |
| Pattern | none |
| Plan | `Docs/Plan/gamedaemon-lift.md` sections 1, 3, 5 |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Grep `Docs/Parity/lessons.md` for A2 (block order), A6 (per-exe path literals), A12 (PDB member types), A18 (destructors), A21 (PDB facts) and A22 (per-exe source form). Do not read it in full.
- Pattern: none. No lifted file has the same role.

## Scope

17 functions, about 1,609 pseudocode lines (about 12,872 tokens). Stems: `skillpage`, `skillskinproperty`, `summonedproperty`, `weaponproperty`, `datapacker`, `datamanager_h`.

The easy functions of this stem are in `lift-gamedaemon-e13`, `lift-gamedaemon-e14`, `lift-gamedaemon-e26`. Do not change them unless a fix needs it.

| n | Exe | RVA | PDB name | Stem | Lines |
| ---: | --- | --- | --- | --- | ---: |
| 1 | GD | `0x1a0e0` | `SkillPage::~SkillPage` | skillpage | 8 |
| 2 | GD | `0x1a180` | `SkillSkinProperty::~SkillSkinProperty` | skillskinproperty | 8 |
| 3 | GD | `0x1a220` | `SummonedProperty::~SummonedProperty` | summonedproperty | 8 |
| 4 | GD | `0x1a2c0` | `WeaponProperty::~WeaponProperty` | weaponproperty | 8 |
| 5 | GD | `0x153d0` | `ZipPackedReaderIO::FileName::FileName` | datapacker | 44 |
| 6 | GD | `0x154f0` | `ZipPackedReaderIO::~ZipPackedReaderIO` | datapacker | 30 |
| 7 | GD | `0x15580` | `ZipPackedReaderIO::OpenZip` | datapacker | 115 |
| 8 | GD | `0x15860` | `ZipPackedReaderIO::Verify` | datapacker | 426 |
| 9 | GD | `0x16290` | `ZipPackedReaderIO::CloseZip` | datapacker | 23 |
| 10 | GD | `0x16330` | `ZipPackedReaderIO::Open` | datapacker | 333 |
| 11 | GD | `0x169a0` | `ZipPackedReaderIO::Read` | datapacker | 98 |
| 12 | GD | `0x16cb0` | `PathUtil::Tokenlize` | datapacker | 41 |
| 13 | GD | `0x16db0` | `PathUtil::MatchPath` | datapacker | 74 |
| 14 | GD | `0x16ec0` | `PathUtil::MatchFile` | datapacker | 105 |
| 15 | GD | `0x1eddc0` | `Data::DataManager::GetNextRandomStoreDrawReward` | datamanager_h | 97 |
| 16 | GD | `0x453bc0` | `Data::AdditionalServiceItems::Add` | datamanager_h | 138 |
| 17 | GD | `0x453e60` | `Data::DataManager::IsRankingPvEStageStartInfo` | datamanager_h | 53 |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/skillpage.cpp`
- `src/Server/GameDaemon/skillpage.h`
- `src/Server/GameDaemon/skillskinproperty.cpp`
- `src/Server/GameDaemon/skillskinproperty.h`
- `src/Server/GameDaemon/summonedproperty.cpp`
- `src/Server/GameDaemon/summonedproperty.h`
- `src/Server/GameDaemon/weaponproperty.cpp`
- `src/Server/GameDaemon/weaponproperty.h`
- `src/Server/GameDaemon/datapacker.cpp`
- `src/Server/GameDaemon/datapacker.h`
- `src/Server/GameDaemon/datamanager_h.cpp`
- `src/Server/GameDaemon/datamanager_h.h`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-66.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
