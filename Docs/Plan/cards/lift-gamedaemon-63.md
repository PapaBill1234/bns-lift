# lift-gamedaemon-63: Property headers: questlist, questproperty, raiddungeonbindproperty, raiddungeonunbindproperty

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

23 functions, about 163 pseudocode lines (about 1,304 tokens). Stems: `questlist`, `questproperty`, `raiddungeonbindproperty`, `raiddungeonunbindproperty`.

| n | Exe | RVA | PDB name | Stem | Lines |
| ---: | --- | --- | --- | --- | ---: |
| 1 | GD | `0x19c60` | `QuestList::~QuestList` | questlist | 8 |
| 2 | GD | `0x19c70` | `QuestList::Name` | questlist | 7 |
| 3 | GD | `0x19c80` | `QuestList::FieldMax` | questlist | 7 |
| 4 | GD | `0x19c90` | `QuestList::FieldDefine` | questlist | 7 |
| 5 | GD | `0x19ca0` | `QuestList::SyncMax` | questlist | 7 |
| 6 | GD | `0x19cb0` | `QuestList::SyncDefine` | questlist | 7 |
| 7 | GD | `0x19cf0` | `QuestProperty::~QuestProperty` | questproperty | 8 |
| 8 | GD | `0x19d00` | `QuestProperty::Name` | questproperty | 7 |
| 9 | GD | `0x19d10` | `QuestProperty::FieldMax` | questproperty | 7 |
| 10 | GD | `0x19d20` | `QuestProperty::FieldDefine` | questproperty | 7 |
| 11 | GD | `0x19d30` | `QuestProperty::SyncMax` | questproperty | 7 |
| 12 | GD | `0x19d40` | `QuestProperty::SyncDefine` | questproperty | 7 |
| 13 | GD | `0x19d80` | `RaidDungeonBindProperty::Name` | raiddungeonbindproperty | 7 |
| 14 | GD | `0x19d90` | `RaidDungeonBindProperty::FieldMax` | raiddungeonbindproperty | 7 |
| 15 | GD | `0x19da0` | `RaidDungeonBindProperty::FieldDefine` | raiddungeonbindproperty | 7 |
| 16 | GD | `0x19db0` | `RaidDungeonBindProperty::SyncMax` | raiddungeonbindproperty | 7 |
| 17 | GD | `0x19dc0` | `RaidDungeonBindProperty::SyncDefine` | raiddungeonbindproperty | 7 |
| 18 | GD | `0x19e00` | `RaidDungeonUnbindProperty::TypeId` | raiddungeonunbindproperty | 7 |
| 19 | GD | `0x19e10` | `RaidDungeonUnbindProperty::Name` | raiddungeonunbindproperty | 7 |
| 20 | GD | `0x19e20` | `RaidDungeonUnbindProperty::FieldMax` | raiddungeonunbindproperty | 7 |
| 21 | GD | `0x19e30` | `RaidDungeonUnbindProperty::FieldDefine` | raiddungeonunbindproperty | 7 |
| 22 | GD | `0x19e40` | `RaidDungeonUnbindProperty::SyncMax` | raiddungeonunbindproperty | 7 |
| 23 | GD | `0x19e50` | `RaidDungeonUnbindProperty::SyncDefine` | raiddungeonunbindproperty | 7 |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/questlist.cpp`
- `src/Server/GameDaemon/questlist.h`
- `src/Server/GameDaemon/questproperty.cpp`
- `src/Server/GameDaemon/questproperty.h`
- `src/Server/GameDaemon/raiddungeonbindproperty.cpp`
- `src/Server/GameDaemon/raiddungeonbindproperty.h`
- `src/Server/GameDaemon/raiddungeonunbindproperty.cpp`
- `src/Server/GameDaemon/raiddungeonunbindproperty.h`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-63.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
