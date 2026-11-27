# lift-gamedaemon-61: Property headers: duelbottrainingroomscore, effectproperty_h, effectproperty_cpp, extracreatureproperty_h

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

20 functions, about 150 pseudocode lines (about 1,200 tokens). Stems: `duelbottrainingroomscore`, `effectproperty_h`, `effectproperty_cpp`, `extracreatureproperty_h`.

| n | Exe | RVA | PDB name | Stem | Lines |
| ---: | --- | --- | --- | --- | ---: |
| 1 | GD | `0x197e0` | `DuelBotTrainingRoomScore::Name` | duelbottrainingroomscore | 7 |
| 2 | GD | `0x197f0` | `DuelBotTrainingRoomScore::FieldMax` | duelbottrainingroomscore | 7 |
| 3 | GD | `0x19800` | `DuelBotTrainingRoomScore::FieldDefine` | duelbottrainingroomscore | 7 |
| 4 | GD | `0x19810` | `DuelBotTrainingRoomScore::SyncMax` | duelbottrainingroomscore | 7 |
| 5 | GD | `0x19820` | `DuelBotTrainingRoomScore::SyncDefine` | duelbottrainingroomscore | 7 |
| 6 | GD | `0x1a050` | `DuelBotTrainingRoomScore::TypeId` | duelbottrainingroomscore | 7 |
| 7 | GD | `0x19860` | `EffectProperty::~EffectProperty` | effectproperty_h | 8 |
| 8 | GD | `0x19870` | `EffectProperty::Name` | effectproperty_h | 7 |
| 9 | GD | `0x19880` | `EffectProperty::FieldMax` | effectproperty_h | 7 |
| 10 | GD | `0x19890` | `EffectProperty::FieldDefine` | effectproperty_h | 7 |
| 11 | GD | `0x198a0` | `EffectProperty::SyncMax` | effectproperty_h | 7 |
| 12 | GD | `0x198b0` | `EffectProperty::SyncDefine` | effectproperty_h | 7 |
| 13 | GD | `0x198f0` | `EffectProperty::EffectProperty` | effectproperty_cpp | 15 |
| 14 | GD | `0x19940` | `ExtraCreatureProperty::~ExtraCreatureProperty` | extracreatureproperty_h | 8 |
| 15 | GD | `0x19950` | `ExtraCreatureProperty::TypeId` | extracreatureproperty_h | 7 |
| 16 | GD | `0x19960` | `ExtraCreatureProperty::Name` | extracreatureproperty_h | 7 |
| 17 | GD | `0x19970` | `ExtraCreatureProperty::FieldMax` | extracreatureproperty_h | 7 |
| 18 | GD | `0x19980` | `ExtraCreatureProperty::FieldDefine` | extracreatureproperty_h | 7 |
| 19 | GD | `0x19990` | `ExtraCreatureProperty::SyncMax` | extracreatureproperty_h | 7 |
| 20 | GD | `0x199a0` | `ExtraCreatureProperty::SyncDefine` | extracreatureproperty_h | 7 |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/duelbottrainingroomscore.cpp`
- `src/Server/GameDaemon/duelbottrainingroomscore.h`
- `src/Server/GameDaemon/effectproperty_h.cpp`
- `src/Server/GameDaemon/effectproperty_h.h`
- `src/Server/GameDaemon/effectproperty_cpp.cpp`
- `src/Server/GameDaemon/effectproperty_cpp.h`
- `src/Server/GameDaemon/extracreatureproperty_h.cpp`
- `src/Server/GameDaemon/extracreatureproperty_h.h`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-61.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
