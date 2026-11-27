# lift-gamedaemon-64: Property headers: randomstore, recycletimeproperty, seasoncontentscombatrecord, seasoncontentstimeattackrecord

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

24 functions, about 170 pseudocode lines (about 1,360 tokens). Stems: `randomstore`, `recycletimeproperty`, `seasoncontentscombatrecord`, `seasoncontentstimeattackrecord`.

| n | Exe | RVA | PDB name | Stem | Lines |
| ---: | --- | --- | --- | --- | ---: |
| 1 | GD | `0x19e90` | `RandomStore::~RandomStore` | randomstore | 8 |
| 2 | GD | `0x19ea0` | `RandomStore::TypeId` | randomstore | 7 |
| 3 | GD | `0x19eb0` | `RandomStore::Name` | randomstore | 7 |
| 4 | GD | `0x19ec0` | `RandomStore::FieldMax` | randomstore | 7 |
| 5 | GD | `0x19ed0` | `RandomStore::FieldDefine` | randomstore | 7 |
| 6 | GD | `0x19ee0` | `RandomStore::SyncMax` | randomstore | 7 |
| 7 | GD | `0x19ef0` | `RandomStore::SyncDefine` | randomstore | 7 |
| 8 | GD | `0x19f30` | `RecycleTimeProperty::~RecycleTimeProperty` | recycletimeproperty | 8 |
| 9 | GD | `0x19f40` | `RecycleTimeProperty::Name` | recycletimeproperty | 7 |
| 10 | GD | `0x19f50` | `RecycleTimeProperty::FieldMax` | recycletimeproperty | 7 |
| 11 | GD | `0x19f60` | `RecycleTimeProperty::FieldDefine` | recycletimeproperty | 7 |
| 12 | GD | `0x19f70` | `RecycleTimeProperty::SyncMax` | recycletimeproperty | 7 |
| 13 | GD | `0x19f80` | `RecycleTimeProperty::SyncDefine` | recycletimeproperty | 7 |
| 14 | GD | `0x19fc0` | `SeasonContentsCombatRecord::TypeId` | seasoncontentscombatrecord | 7 |
| 15 | GD | `0x19fd0` | `SeasonContentsCombatRecord::Name` | seasoncontentscombatrecord | 7 |
| 16 | GD | `0x19fe0` | `SeasonContentsCombatRecord::FieldMax` | seasoncontentscombatrecord | 7 |
| 17 | GD | `0x19ff0` | `SeasonContentsCombatRecord::FieldDefine` | seasoncontentscombatrecord | 7 |
| 18 | GD | `0x1a000` | `SeasonContentsCombatRecord::SyncMax` | seasoncontentscombatrecord | 7 |
| 19 | GD | `0x1a010` | `SeasonContentsCombatRecord::SyncDefine` | seasoncontentscombatrecord | 7 |
| 20 | GD | `0x1a060` | `SeasonContentsTimeAttackRecord::Name` | seasoncontentstimeattackrecord | 7 |
| 21 | GD | `0x1a070` | `SeasonContentsTimeAttackRecord::FieldMax` | seasoncontentstimeattackrecord | 7 |
| 22 | GD | `0x1a080` | `SeasonContentsTimeAttackRecord::FieldDefine` | seasoncontentstimeattackrecord | 7 |
| 23 | GD | `0x1a090` | `SeasonContentsTimeAttackRecord::SyncMax` | seasoncontentstimeattackrecord | 7 |
| 24 | GD | `0x1a0a0` | `SeasonContentsTimeAttackRecord::SyncDefine` | seasoncontentstimeattackrecord | 7 |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/randomstore.cpp`
- `src/Server/GameDaemon/randomstore.h`
- `src/Server/GameDaemon/recycletimeproperty.cpp`
- `src/Server/GameDaemon/recycletimeproperty.h`
- `src/Server/GameDaemon/seasoncontentscombatrecord.cpp`
- `src/Server/GameDaemon/seasoncontentscombatrecord.h`
- `src/Server/GameDaemon/seasoncontentstimeattackrecord.cpp`
- `src/Server/GameDaemon/seasoncontentstimeattackrecord.h`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-64.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
