# lift-gamedaemon-58: Property headers: challengelistproperty, slateproperty, accessoryproperty, acquiredskill1

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
| Depends on | `lift-gamedaemon-35` |
| Pattern | none |
| Plan | `Docs/Plan/gamedaemon-lift.md` sections 1, 3, 5 |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Grep `Docs/Parity/lessons.md` for A2 (block order), A6 (per-exe path literals), A12 (PDB member types), A18 (destructors), A21 (PDB facts) and A22 (per-exe source form). Do not read it in full.
- Pattern: none. This card sets the pattern for its group. Write the form so that later cards can copy it. Write the form in the handoff.

## Scope

26 functions, about 183 pseudocode lines (about 1,464 tokens). Stems: `challengelistproperty`, `slateproperty`, `accessoryproperty`, `acquiredskill1`.

| n | Exe | RVA | PDB name | Stem | Lines |
| ---: | --- | --- | --- | --- | ---: |
| 1 | GD | `0x96c0` | `ChallengeListProperty::TypeId` | challengelistproperty | 7 |
| 2 | GD | `0x96d0` | `ChallengeListProperty::Name` | challengelistproperty | 7 |
| 3 | GD | `0x96e0` | `ChallengeListProperty::FieldMax` | challengelistproperty | 7 |
| 4 | GD | `0x96f0` | `ChallengeListProperty::FieldDefine` | challengelistproperty | 7 |
| 5 | GD | `0x9700` | `ChallengeListProperty::SyncMax` | challengelistproperty | 7 |
| 6 | GD | `0x9710` | `ChallengeListProperty::SyncDefine` | challengelistproperty | 7 |
| 7 | GD | `0x9750` | `SlateProperty::TypeId` | slateproperty | 7 |
| 8 | GD | `0x9760` | `SlateProperty::Name` | slateproperty | 7 |
| 9 | GD | `0x9770` | `SlateProperty::FieldMax` | slateproperty | 7 |
| 10 | GD | `0x9780` | `SlateProperty::FieldDefine` | slateproperty | 7 |
| 11 | GD | `0x9790` | `SlateProperty::SyncMax` | slateproperty | 7 |
| 12 | GD | `0x97a0` | `SlateProperty::SyncDefine` | slateproperty | 7 |
| 13 | GD | `0x191d0` | `AccessoryProperty::TypeId` | accessoryproperty | 7 |
| 14 | GD | `0x191e0` | `AccessoryProperty::Version` | accessoryproperty | 7 |
| 15 | GD | `0x191f0` | `AccessoryProperty::Name` | accessoryproperty | 7 |
| 16 | GD | `0x19200` | `AccessoryProperty::FieldMax` | accessoryproperty | 7 |
| 17 | GD | `0x19210` | `AccessoryProperty::FieldDefine` | accessoryproperty | 7 |
| 18 | GD | `0x19220` | `AccessoryProperty::SyncMax` | accessoryproperty | 7 |
| 19 | GD | `0x19230` | `AccessoryProperty::SyncDefine` | accessoryproperty | 7 |
| 20 | GD | `0x19270` | `AcquiredSkill1::~AcquiredSkill1` | acquiredskill1 | 8 |
| 21 | GD | `0x19280` | `AcquiredSkill1::TypeId` | acquiredskill1 | 7 |
| 22 | GD | `0x19290` | `AcquiredSkill1::Name` | acquiredskill1 | 7 |
| 23 | GD | `0x192a0` | `AcquiredSkill1::FieldMax` | acquiredskill1 | 7 |
| 24 | GD | `0x192b0` | `AcquiredSkill1::FieldDefine` | acquiredskill1 | 7 |
| 25 | GD | `0x192c0` | `AcquiredSkill1::SyncMax` | acquiredskill1 | 7 |
| 26 | GD | `0x192d0` | `AcquiredSkill1::SyncDefine` | acquiredskill1 | 7 |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/challengelistproperty.cpp`
- `src/Server/GameDaemon/challengelistproperty.h`
- `src/Server/GameDaemon/slateproperty.cpp`
- `src/Server/GameDaemon/slateproperty.h`
- `src/Server/GameDaemon/accessoryproperty.cpp`
- `src/Server/GameDaemon/accessoryproperty.h`
- `src/Server/GameDaemon/acquiredskill1.cpp`
- `src/Server/GameDaemon/acquiredskill1.h`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-58.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.
Describe the form that the later cards of this group must copy.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
