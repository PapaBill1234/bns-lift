# lift-gamedaemon-e3: Easy leaves (Property headers): duelbottrainingroomscore, extracreatureproperty_h, fishingproperty, gemproperty, ...

| Item | Value |
| --- | --- |
| Exe | GD |
| Source build | GameDaemon 2019 + PDB (VS2010 SP1) |
| Exe file | `<work-root>/ida/lift/GameDaemon/GameDaemon.exe` |
| PDB | `<work-root>/ida/lift/GameDaemon/GameDaemon.pdb` |
| Pseudocode | `~/.cache/bns-lift/hr/GameDaemon/<stem>.c` |
| Pseudocode index | `~/.cache/bns-lift/hr/GameDaemon/index.tsv` (stem, rva, name, first, last, status, source file, part) |
| Wave | E |
| Model | sonnet:high |
| Depends on | `lift-gamedaemon-0e` |
| Pattern | none |
| Plan | `Docs/Plan/gamedaemon-lift.md` sections 1, 3, 5 |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Grep `Docs/Parity/lessons.md` for A2 (block order), A6 (per-exe path literals), A12 (PDB member types), A18 (destructors), A21 (PDB facts) and A22 (per-exe source form). Do not read it in full.
- Pattern: none. No lifted file has the same role.
- Dead-strip: `wmain` and most callers are still `LIFT_STUB` bodies. `/OPT:REF` removes a lifted function that has no live caller, and funcdiff then cannot pair it. For each function in scope with no live caller, add `#pragma comment(linker, "/INCLUDE:<public name>")` in its `.cpp` (public names: `llvm-pdbutil dump -publics`; grep `/INCLUDE` in `Docs/Parity/lessons.md`). Do not add a pragma for a function that a lifted caller keeps.

## Scope

40 functions, about 280 pseudocode lines (about 2,240 tokens). Stems: `duelbottrainingroomscore`, `extracreatureproperty_h`, `fishingproperty`, `gemproperty`, `groceryproperty`, `mentoringproperty`, `questlist`.

Wave E (owner order 2026-11-27: the easiest work first). Each function in this card is a leaf: its body calls no other counted function that needs a lift. Thus a `LIFT_STUB` callee cannot keep it DIFF. Each function has at most 30 pseudocode lines. Ease key: 7.0 cost per function (rule in `Docs/Plan/gamedaemon-lift.md` section 3).

Lift only the functions in the table. The other functions of these stems are in later W cards. Those cards depend on this card.

| n | Exe | RVA | PDB name | Stem | Lines | Form |
| ---: | --- | --- | --- | --- | ---: | --- |
| 1 | GD | `0x197e0` | `DuelBotTrainingRoomScore::Name` | duelbottrainingroomscore | 7 | getter |
| 2 | GD | `0x197f0` | `DuelBotTrainingRoomScore::FieldMax` | duelbottrainingroomscore | 7 | getter |
| 3 | GD | `0x19800` | `DuelBotTrainingRoomScore::FieldDefine` | duelbottrainingroomscore | 7 | getter |
| 4 | GD | `0x19810` | `DuelBotTrainingRoomScore::SyncMax` | duelbottrainingroomscore | 7 | getter |
| 5 | GD | `0x19820` | `DuelBotTrainingRoomScore::SyncDefine` | duelbottrainingroomscore | 7 | getter |
| 6 | GD | `0x1a050` | `DuelBotTrainingRoomScore::TypeId` | duelbottrainingroomscore | 7 | getter |
| 7 | GD | `0x19950` | `ExtraCreatureProperty::TypeId` | extracreatureproperty_h | 7 | getter |
| 8 | GD | `0x19960` | `ExtraCreatureProperty::Name` | extracreatureproperty_h | 7 | getter |
| 9 | GD | `0x19970` | `ExtraCreatureProperty::FieldMax` | extracreatureproperty_h | 7 | getter |
| 10 | GD | `0x19980` | `ExtraCreatureProperty::FieldDefine` | extracreatureproperty_h | 7 | getter |
| 11 | GD | `0x19990` | `ExtraCreatureProperty::SyncMax` | extracreatureproperty_h | 7 | getter |
| 12 | GD | `0x199a0` | `ExtraCreatureProperty::SyncDefine` | extracreatureproperty_h | 7 | getter |
| 13 | GD | `0x19a30` | `FishingProperty::TypeId` | fishingproperty | 7 | getter |
| 14 | GD | `0x19a40` | `FishingProperty::Name` | fishingproperty | 7 | getter |
| 15 | GD | `0x19a50` | `FishingProperty::FieldMax` | fishingproperty | 7 | getter |
| 16 | GD | `0x19a60` | `FishingProperty::FieldDefine` | fishingproperty | 7 | getter |
| 17 | GD | `0x19a70` | `FishingProperty::SyncMax` | fishingproperty | 7 | getter |
| 18 | GD | `0x19a80` | `FishingProperty::SyncDefine` | fishingproperty | 7 | getter |
| 19 | GD | `0x19ac0` | `GemProperty::Name` | gemproperty | 7 | getter |
| 20 | GD | `0x19ad0` | `GemProperty::FieldMax` | gemproperty | 7 | getter |
| 21 | GD | `0x19ae0` | `GemProperty::FieldDefine` | gemproperty | 7 | getter |
| 22 | GD | `0x19af0` | `GemProperty::SyncMax` | gemproperty | 7 | getter |
| 23 | GD | `0x19b00` | `GemProperty::SyncDefine` | gemproperty | 7 | getter |
| 24 | GD | `0x19b40` | `GroceryProperty::Version` | groceryproperty | 7 | getter |
| 25 | GD | `0x19b50` | `GroceryProperty::Name` | groceryproperty | 7 | getter |
| 26 | GD | `0x19b60` | `GroceryProperty::FieldMax` | groceryproperty | 7 | getter |
| 27 | GD | `0x19b70` | `GroceryProperty::FieldDefine` | groceryproperty | 7 | getter |
| 28 | GD | `0x19b80` | `GroceryProperty::SyncMax` | groceryproperty | 7 | getter |
| 29 | GD | `0x19b90` | `GroceryProperty::SyncDefine` | groceryproperty | 7 | getter |
| 30 | GD | `0x19be0` | `MentoringProperty::Name` | mentoringproperty | 7 | getter |
| 31 | GD | `0x19bf0` | `MentoringProperty::FieldMax` | mentoringproperty | 7 | getter |
| 32 | GD | `0x19c00` | `MentoringProperty::FieldDefine` | mentoringproperty | 7 | getter |
| 33 | GD | `0x19c10` | `MentoringProperty::SyncMax` | mentoringproperty | 7 | getter |
| 34 | GD | `0x19c20` | `MentoringProperty::SyncDefine` | mentoringproperty | 7 | getter |
| 35 | GD | `0x66ee00` | `ItemBase<AccessoryTrait>::GetFieldCount` | mentoringproperty | 7 | getter |
| 36 | GD | `0x19c70` | `QuestList::Name` | questlist | 7 | getter |
| 37 | GD | `0x19c80` | `QuestList::FieldMax` | questlist | 7 | getter |
| 38 | GD | `0x19c90` | `QuestList::FieldDefine` | questlist | 7 | getter |
| 39 | GD | `0x19ca0` | `QuestList::SyncMax` | questlist | 7 | getter |
| 40 | GD | `0x19cb0` | `QuestList::SyncDefine` | questlist | 7 | getter |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/duelbottrainingroomscore.cpp`
- `src/Server/GameDaemon/duelbottrainingroomscore.h`
- `src/Server/GameDaemon/extracreatureproperty_h.cpp`
- `src/Server/GameDaemon/extracreatureproperty_h.h`
- `src/Server/GameDaemon/fishingproperty.cpp`
- `src/Server/GameDaemon/fishingproperty.h`
- `src/Server/GameDaemon/gemproperty.cpp`
- `src/Server/GameDaemon/gemproperty.h`
- `src/Server/GameDaemon/groceryproperty.cpp`
- `src/Server/GameDaemon/groceryproperty.h`
- `src/Server/GameDaemon/mentoringproperty.cpp`
- `src/Server/GameDaemon/mentoringproperty.h`
- `src/Server/GameDaemon/questlist.cpp`
- `src/Server/GameDaemon/questlist.h`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-e3.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
