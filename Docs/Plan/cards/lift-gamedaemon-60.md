# lift-gamedaemon-60: Property headers: collectingproperty, contentquotaproperty, costumeproperty, discoveryarea

| Item | Value |
| --- | --- |
| Exe | GD |
| Source build | GameDaemon 2019 + PDB (VS2010 SP1) |
| Exe file | `<work-root>/ida/lift/GameDaemon/GameDaemon.exe` |
| PDB | `<work-root>/ida/lift/GameDaemon/GameDaemon.pdb` |
| Pseudocode | `~/.cache/bns-lift/hr/GameDaemon/<stem>.c` |
| Pseudocode index | `~/.cache/bns-lift/hr/GameDaemon/index.tsv` (stem, rva, name, first, last, status, source file, part) |
| Wave | W2 |
| Model | sonnet:high |
| Depends on | `lift-gamedaemon-35`, `lift-gamedaemon-58` |
| Pattern | `src/Server/GameDaemon/challengelistproperty.cpp` |
| Plan | `Docs/Plan/gamedaemon-lift.md` sections 1, 3, 5 |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Grep `Docs/Parity/lessons.md` for A2 (block order), A6 (per-exe path literals), A12 (PDB member types), A18 (destructors), A21 (PDB facts) and A22 (per-exe source form). Do not read it in full.
- Pattern: `src/Server/GameDaemon/challengelistproperty.cpp`. Read it one time. Use its form for the functions of this card.
  The pattern is the output of `lift-gamedaemon-58`. Use the same form for each function: the functions in this group have one layout.

## Scope

26 functions, about 185 pseudocode lines (about 1,480 tokens). Stems: `collectingproperty`, `contentquotaproperty`, `costumeproperty`, `discoveryarea`.

| n | Exe | RVA | PDB name | Stem | Lines |
| ---: | --- | --- | --- | --- | ---: |
| 1 | GD | `0x19570` | `CollectingProperty::~CollectingProperty` | collectingproperty | 8 |
| 2 | GD | `0x19580` | `CollectingProperty::TypeId` | collectingproperty | 7 |
| 3 | GD | `0x195a0` | `CollectingProperty::Name` | collectingproperty | 7 |
| 4 | GD | `0x195b0` | `CollectingProperty::FieldMax` | collectingproperty | 7 |
| 5 | GD | `0x195c0` | `CollectingProperty::FieldDefine` | collectingproperty | 7 |
| 6 | GD | `0x195d0` | `CollectingProperty::SyncMax` | collectingproperty | 7 |
| 7 | GD | `0x195e0` | `CollectingProperty::SyncDefine` | collectingproperty | 7 |
| 8 | GD | `0x19620` | `ContentQuotaProperty::Name` | contentquotaproperty | 7 |
| 9 | GD | `0x19630` | `ContentQuotaProperty::FieldMax` | contentquotaproperty | 7 |
| 10 | GD | `0x19640` | `ContentQuotaProperty::FieldDefine` | contentquotaproperty | 7 |
| 11 | GD | `0x19650` | `ContentQuotaProperty::SyncMax` | contentquotaproperty | 7 |
| 12 | GD | `0x19660` | `ContentQuotaProperty::SyncDefine` | contentquotaproperty | 7 |
| 13 | GD | `0x196a0` | `CostumeProperty::~CostumeProperty` | costumeproperty | 8 |
| 14 | GD | `0x196b0` | `CostumeProperty::Version` | costumeproperty | 7 |
| 15 | GD | `0x196c0` | `CostumeProperty::Name` | costumeproperty | 7 |
| 16 | GD | `0x196d0` | `CostumeProperty::FieldMax` | costumeproperty | 7 |
| 17 | GD | `0x196e0` | `CostumeProperty::FieldDefine` | costumeproperty | 7 |
| 18 | GD | `0x196f0` | `CostumeProperty::SyncMax` | costumeproperty | 7 |
| 19 | GD | `0x19700` | `CostumeProperty::SyncDefine` | costumeproperty | 7 |
| 20 | GD | `0x19740` | `DiscoveryArea::~DiscoveryArea` | discoveryarea | 8 |
| 21 | GD | `0x19750` | `DiscoveryArea::TypeId` | discoveryarea | 7 |
| 22 | GD | `0x19760` | `DiscoveryArea::Name` | discoveryarea | 7 |
| 23 | GD | `0x19770` | `DiscoveryArea::FieldMax` | discoveryarea | 7 |
| 24 | GD | `0x19780` | `DiscoveryArea::FieldDefine` | discoveryarea | 7 |
| 25 | GD | `0x19790` | `DiscoveryArea::SyncMax` | discoveryarea | 7 |
| 26 | GD | `0x197a0` | `DiscoveryArea::SyncDefine` | discoveryarea | 7 |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/collectingproperty.cpp`
- `src/Server/GameDaemon/collectingproperty.h`
- `src/Server/GameDaemon/contentquotaproperty.cpp`
- `src/Server/GameDaemon/contentquotaproperty.h`
- `src/Server/GameDaemon/costumeproperty.cpp`
- `src/Server/GameDaemon/costumeproperty.h`
- `src/Server/GameDaemon/discoveryarea.cpp`
- `src/Server/GameDaemon/discoveryarea.h`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-60.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
