# lift-gamedaemon-62: Property headers: extracreatureproperty_cpp, fishingproperty, gemproperty, groceryproperty, ...

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

25 functions, about 184 pseudocode lines (about 1,472 tokens). Stems: `extracreatureproperty_cpp`, `fishingproperty`, `gemproperty`, `groceryproperty`, `mentoringproperty`.

| n | Exe | RVA | PDB name | Stem | Lines |
| ---: | --- | --- | --- | --- | ---: |
| 1 | GD | `0x199e0` | `ExtraCreatureProperty::ExtraCreatureProperty` | extracreatureproperty_cpp | 15 |
| 2 | GD | `0x19a30` | `FishingProperty::TypeId` | fishingproperty | 7 |
| 3 | GD | `0x19a40` | `FishingProperty::Name` | fishingproperty | 7 |
| 4 | GD | `0x19a50` | `FishingProperty::FieldMax` | fishingproperty | 7 |
| 5 | GD | `0x19a60` | `FishingProperty::FieldDefine` | fishingproperty | 7 |
| 6 | GD | `0x19a70` | `FishingProperty::SyncMax` | fishingproperty | 7 |
| 7 | GD | `0x19a80` | `FishingProperty::SyncDefine` | fishingproperty | 7 |
| 8 | GD | `0x19ac0` | `GemProperty::Name` | gemproperty | 7 |
| 9 | GD | `0x19ad0` | `GemProperty::FieldMax` | gemproperty | 7 |
| 10 | GD | `0x19ae0` | `GemProperty::FieldDefine` | gemproperty | 7 |
| 11 | GD | `0x19af0` | `GemProperty::SyncMax` | gemproperty | 7 |
| 12 | GD | `0x19b00` | `GemProperty::SyncDefine` | gemproperty | 7 |
| 13 | GD | `0x19b40` | `GroceryProperty::Version` | groceryproperty | 7 |
| 14 | GD | `0x19b50` | `GroceryProperty::Name` | groceryproperty | 7 |
| 15 | GD | `0x19b60` | `GroceryProperty::FieldMax` | groceryproperty | 7 |
| 16 | GD | `0x19b70` | `GroceryProperty::FieldDefine` | groceryproperty | 7 |
| 17 | GD | `0x19b80` | `GroceryProperty::SyncMax` | groceryproperty | 7 |
| 18 | GD | `0x19b90` | `GroceryProperty::SyncDefine` | groceryproperty | 7 |
| 19 | GD | `0x19bd0` | `MentoringProperty::~MentoringProperty` | mentoringproperty | 8 |
| 20 | GD | `0x19be0` | `MentoringProperty::Name` | mentoringproperty | 7 |
| 21 | GD | `0x19bf0` | `MentoringProperty::FieldMax` | mentoringproperty | 7 |
| 22 | GD | `0x19c00` | `MentoringProperty::FieldDefine` | mentoringproperty | 7 |
| 23 | GD | `0x19c10` | `MentoringProperty::SyncMax` | mentoringproperty | 7 |
| 24 | GD | `0x19c20` | `MentoringProperty::SyncDefine` | mentoringproperty | 7 |
| 25 | GD | `0x66ee00` | `ItemBase<AccessoryTrait>::GetFieldCount` | mentoringproperty | 7 |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/extracreatureproperty_cpp.cpp`
- `src/Server/GameDaemon/extracreatureproperty_cpp.h`
- `src/Server/GameDaemon/fishingproperty.cpp`
- `src/Server/GameDaemon/fishingproperty.h`
- `src/Server/GameDaemon/gemproperty.cpp`
- `src/Server/GameDaemon/gemproperty.h`
- `src/Server/GameDaemon/groceryproperty.cpp`
- `src/Server/GameDaemon/groceryproperty.h`
- `src/Server/GameDaemon/mentoringproperty.cpp`
- `src/Server/GameDaemon/mentoringproperty.h`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-62.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
