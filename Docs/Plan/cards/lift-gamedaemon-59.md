# lift-gamedaemon-59: Property headers: creatureproperty, activatedteleport, clientoption_h, clientoption_cpp

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

22 functions, about 165 pseudocode lines (about 1,320 tokens). Stems: `creatureproperty`, `activatedteleport`, `clientoption_h`, `clientoption_cpp`.

| n | Exe | RVA | PDB name | Stem | Lines |
| ---: | --- | --- | --- | --- | ---: |
| 1 | GD | `0x19340` | `CreatureProperty::~CreatureProperty` | creatureproperty | 8 |
| 2 | GD | `0x19350` | `CreatureProperty::Version` | creatureproperty | 7 |
| 3 | GD | `0x19360` | `CreatureProperty::Name` | creatureproperty | 7 |
| 4 | GD | `0x19370` | `CreatureProperty::FieldMax` | creatureproperty | 7 |
| 5 | GD | `0x19380` | `CreatureProperty::FieldDefine` | creatureproperty | 7 |
| 6 | GD | `0x19390` | `CreatureProperty::SyncMax` | creatureproperty | 7 |
| 7 | GD | `0x193a0` | `CreatureProperty::SyncDefine` | creatureproperty | 7 |
| 8 | GD | `0x193e0` | `ActivatedTeleport::~ActivatedTeleport` | activatedteleport | 8 |
| 9 | GD | `0x193f0` | `ActivatedTeleport::TypeId` | activatedteleport | 7 |
| 10 | GD | `0x19400` | `ActivatedTeleport::Name` | activatedteleport | 7 |
| 11 | GD | `0x19410` | `ActivatedTeleport::FieldMax` | activatedteleport | 7 |
| 12 | GD | `0x19420` | `ActivatedTeleport::FieldDefine` | activatedteleport | 7 |
| 13 | GD | `0x19430` | `ActivatedTeleport::SyncMax` | activatedteleport | 7 |
| 14 | GD | `0x19440` | `ActivatedTeleport::SyncDefine` | activatedteleport | 7 |
| 15 | GD | `0x19480` | `ClientOption::~ClientOption` | clientoption_h | 8 |
| 16 | GD | `0x19490` | `ClientOption::TypeId` | clientoption_h | 7 |
| 17 | GD | `0x194a0` | `ClientOption::Name` | clientoption_h | 7 |
| 18 | GD | `0x194b0` | `ClientOption::FieldMax` | clientoption_h | 7 |
| 19 | GD | `0x194c0` | `ClientOption::FieldDefine` | clientoption_h | 7 |
| 20 | GD | `0x194d0` | `ClientOption::SyncMax` | clientoption_h | 7 |
| 21 | GD | `0x194e0` | `ClientOption::SyncDefine` | clientoption_h | 7 |
| 22 | GD | `0x19520` | `ClientOption::ClientOption` | clientoption_cpp | 15 |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/creatureproperty.cpp`
- `src/Server/GameDaemon/creatureproperty.h`
- `src/Server/GameDaemon/activatedteleport.cpp`
- `src/Server/GameDaemon/activatedteleport.h`
- `src/Server/GameDaemon/clientoption_h.cpp`
- `src/Server/GameDaemon/clientoption_h.h`
- `src/Server/GameDaemon/clientoption_cpp.cpp`
- `src/Server/GameDaemon/clientoption_cpp.h`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-59.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
