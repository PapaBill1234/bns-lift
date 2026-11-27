# lift-gamedaemon-59: DataReader and Property headers: md5, acquiredskill1, creatureproperty, activatedteleport, ...

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
| Depends on | `lift-gamedaemon-e2`, `lift-gamedaemon-e3`, `lift-gamedaemon-e4`, `lift-gamedaemon-e5`, `lift-gamedaemon-e14`, `lift-gamedaemon-35` |
| Pattern | `src/library/FsdReader/FsdDecomposer.cpp` |
| Plan | `Docs/Plan/gamedaemon-lift.md` sections 1, 3, 5 |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Grep `Docs/Parity/lessons.md` for A2 (block order), A6 (per-exe path literals), A12 (PDB member types), A18 (destructors), A21 (PDB facts) and A22 (per-exe source form). Do not read it in full.
- Pattern: `src/library/FsdReader/FsdDecomposer.cpp`. Read it one time. Use its form for the functions of this card.

## Scope

20 functions, about 520 pseudocode lines (about 4,160 tokens). Stems: `md5`, `acquiredskill1`, `creatureproperty`, `activatedteleport`, `clientoption_h`, `clientoption_cpp`, `collectingproperty`, `costumeproperty`, `discoveryarea`, `effectproperty_h`, `effectproperty_cpp`, `extracreatureproperty_h`, `extracreatureproperty_cpp`, `mentoringproperty`, `questlist`, `questproperty`, `randomstore`, `recycletimeproperty`.

The easy functions of this stem are in `lift-gamedaemon-e14`, `lift-gamedaemon-e5`, `lift-gamedaemon-e2`, `lift-gamedaemon-e3`, `lift-gamedaemon-e4`. Do not change them unless a fix needs it.

| n | Exe | RVA | PDB name | Stem | Lines |
| ---: | --- | --- | --- | --- | ---: |
| 1 | GD | `0x6feff0` | `md5_process` | md5 | 193 |
| 2 | GD | `0x6ff880` | `md5_append` | md5 | 50 |
| 3 | GD | `0x6ff980` | `md5_finish` | md5 | 120 |
| 4 | GD | `0x19270` | `AcquiredSkill1::~AcquiredSkill1` | acquiredskill1 | 8 |
| 5 | GD | `0x19340` | `CreatureProperty::~CreatureProperty` | creatureproperty | 8 |
| 6 | GD | `0x193e0` | `ActivatedTeleport::~ActivatedTeleport` | activatedteleport | 8 |
| 7 | GD | `0x19480` | `ClientOption::~ClientOption` | clientoption_h | 8 |
| 8 | GD | `0x19520` | `ClientOption::ClientOption` | clientoption_cpp | 15 |
| 9 | GD | `0x19570` | `CollectingProperty::~CollectingProperty` | collectingproperty | 8 |
| 10 | GD | `0x196a0` | `CostumeProperty::~CostumeProperty` | costumeproperty | 8 |
| 11 | GD | `0x19740` | `DiscoveryArea::~DiscoveryArea` | discoveryarea | 8 |
| 12 | GD | `0x19860` | `EffectProperty::~EffectProperty` | effectproperty_h | 8 |
| 13 | GD | `0x198f0` | `EffectProperty::EffectProperty` | effectproperty_cpp | 15 |
| 14 | GD | `0x19940` | `ExtraCreatureProperty::~ExtraCreatureProperty` | extracreatureproperty_h | 8 |
| 15 | GD | `0x199e0` | `ExtraCreatureProperty::ExtraCreatureProperty` | extracreatureproperty_cpp | 15 |
| 16 | GD | `0x19bd0` | `MentoringProperty::~MentoringProperty` | mentoringproperty | 8 |
| 17 | GD | `0x19c60` | `QuestList::~QuestList` | questlist | 8 |
| 18 | GD | `0x19cf0` | `QuestProperty::~QuestProperty` | questproperty | 8 |
| 19 | GD | `0x19e90` | `RandomStore::~RandomStore` | randomstore | 8 |
| 20 | GD | `0x19f30` | `RecycleTimeProperty::~RecycleTimeProperty` | recycletimeproperty | 8 |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/md5.cpp`
- `src/Server/GameDaemon/md5.h`
- `src/Server/GameDaemon/acquiredskill1.cpp`
- `src/Server/GameDaemon/acquiredskill1.h`
- `src/Server/GameDaemon/creatureproperty.cpp`
- `src/Server/GameDaemon/creatureproperty.h`
- `src/Server/GameDaemon/activatedteleport.cpp`
- `src/Server/GameDaemon/activatedteleport.h`
- `src/Server/GameDaemon/clientoption_h.cpp`
- `src/Server/GameDaemon/clientoption_h.h`
- `src/Server/GameDaemon/clientoption_cpp.cpp`
- `src/Server/GameDaemon/clientoption_cpp.h`
- `src/Server/GameDaemon/collectingproperty.cpp`
- `src/Server/GameDaemon/collectingproperty.h`
- `src/Server/GameDaemon/costumeproperty.cpp`
- `src/Server/GameDaemon/costumeproperty.h`
- `src/Server/GameDaemon/discoveryarea.cpp`
- `src/Server/GameDaemon/discoveryarea.h`
- `src/Server/GameDaemon/effectproperty_h.cpp`
- `src/Server/GameDaemon/effectproperty_h.h`
- `src/Server/GameDaemon/effectproperty_cpp.cpp`
- `src/Server/GameDaemon/effectproperty_cpp.h`
- `src/Server/GameDaemon/extracreatureproperty_h.cpp`
- `src/Server/GameDaemon/extracreatureproperty_h.h`
- `src/Server/GameDaemon/extracreatureproperty_cpp.cpp`
- `src/Server/GameDaemon/extracreatureproperty_cpp.h`
- `src/Server/GameDaemon/mentoringproperty.cpp`
- `src/Server/GameDaemon/mentoringproperty.h`
- `src/Server/GameDaemon/questlist.cpp`
- `src/Server/GameDaemon/questlist.h`
- `src/Server/GameDaemon/questproperty.cpp`
- `src/Server/GameDaemon/questproperty.h`
- `src/Server/GameDaemon/randomstore.cpp`
- `src/Server/GameDaemon/randomstore.h`
- `src/Server/GameDaemon/recycletimeproperty.cpp`
- `src/Server/GameDaemon/recycletimeproperty.h`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-59.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
