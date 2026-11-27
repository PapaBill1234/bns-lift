# lift-gamedaemon-35: BloodLib: source_property

| Item | Value |
| --- | --- |
| Exe | GD |
| Source build | GameDaemon 2019 + PDB (VS2010 SP1) |
| Exe file | `<work-root>/ida/lift/GameDaemon/GameDaemon.exe` |
| PDB | `<work-root>/ida/lift/GameDaemon/GameDaemon.pdb` |
| Pseudocode | `~/.cache/bns-lift/hr/GameDaemon/<stem>.c` |
| Pseudocode index | `~/.cache/bns-lift/hr/GameDaemon/index.tsv` (stem, rva, name, first, last, status, source file, part) |
| Wave | W1 |
| Model | opus |
| Depends on | `lift-gamedaemon-4`, `lift-gamedaemon-34` |
| Pattern | `src/Server/BloodLib/source/Channel.cpp` |
| Plan | `Docs/Plan/gamedaemon-lift.md` sections 1, 3, 5 |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Grep `Docs/Parity/lessons.md` for A2 (block order), A6 (per-exe path literals), A12 (PDB member types), A18 (destructors), A21 (PDB facts) and A22 (per-exe source form). Do not read it in full.
- Pattern: `src/Server/BloodLib/source/Channel.cpp`. Read it one time. Use its form for the functions of this card.

## Scope

27 functions, about 2,336 pseudocode lines (about 18,688 tokens). Stems: `source_property`.

| n | Exe | RVA | PDB name | Stem | Lines |
| ---: | --- | --- | --- | --- | ---: |
| 1 | GD | `0x688a70` | `Property::~Property` | source_property | 40 |
| 2 | GD | `0x688b50` | `Property::self` | source_property | 74 |
| 3 | GD | `0x688ce0` | `Property::init` | source_property | 76 |
| 4 | GD | `0x688ee0` | `Property::SetZero` | source_property | 64 |
| 5 | GD | `0x689080` | `Property::Set` | source_property | 73 |
| 6 | GD | `0x689240` | `Property::Set` | source_property | 53 |
| 7 | GD | `0x689320` | `Property::set` | source_property | 73 |
| 8 | GD | `0x6894e0` | `Property::set` | source_property | 59 |
| 9 | GD | `0x689640` | `Property::set` | source_property | 30 |
| 10 | GD | `0x689740` | `Property::set` | source_property | 92 |
| 11 | GD | `0x689910` | `Property::set` | source_property | 90 |
| 12 | GD | `0x689af0` | `Property::set` | source_property | 76 |
| 13 | GD | `0x689c70` | `Property::set` | source_property | 148 |
| 14 | GD | `0x689f50` | `Property::updateSync` | source_property | 214 |
| 15 | GD | `0x68a2e0` | `Property::updateSync` | source_property | 232 |
| 16 | GD | `0x68a700` | `Property::Get` | source_property | 27 |
| 17 | GD | `0x68a7c0` | `Property::Get` | source_property | 49 |
| 18 | GD | `0x68a880` | `Property::GetPureData` | source_property | 192 |
| 19 | GD | `0x68ac60` | `Property::GetPairData` | source_property | 36 |
| 20 | GD | `0x68ad50` | `Property::get` | source_property | 128 |
| 21 | GD | `0x68af20` | `Property::makeWhere` | source_property | 27 |
| 22 | GD | `0x68afb0` | `Property::initInstance` | source_property | 51 |
| 23 | GD | `0x68b100` | `Property::initFieldDefine` | source_property | 154 |
| 24 | GD | `0x68b510` | `Property::findMaxId` | source_property | 43 |
| 25 | GD | `0x68b610` | `Property::initBitfield` | source_property | 69 |
| 26 | GD | `0x68b770` | `Property::initSyncDefine` | source_property | 137 |
| 27 | GD | `0x68ba10` | `Property::findMaxId` | source_property | 29 |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/source_property.cpp`
- `src/Server/GameDaemon/source_property.h`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-35.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
