# lift-gamedaemon-43: BloodLib: source_jsoncpp part 3/3

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
| Depends on | `lift-gamedaemon-42` |
| Pattern | none |
| Plan | `Docs/Plan/gamedaemon-lift.md` sections 1, 3, 5 |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Grep `Docs/Parity/lessons.md` for A2 (block order), A6 (per-exe path literals), A12 (PDB member types), A18 (destructors), A21 (PDB facts) and A22 (per-exe source form). Do not read it in full.
- Pattern: none. Read the functions that `lift-gamedaemon-42` lifted in the same file first. Use their form.

## Scope

22 functions, about 1,675 pseudocode lines (about 13,400 tokens). Stems: `source_jsoncpp`.

This card is part 3/3 of stem `source_jsoncpp`. The other parts are in other cards of this wave. They run one after the other (column "Depends on"). Edit only the functions in this table.

| n | Exe | RVA | PDB name | Stem | Lines |
| ---: | --- | --- | --- | --- | ---: |
| 1 | GD | `0x6a9270` | `Json::Value::asFloat` | source_jsoncpp | 56 |
| 2 | GD | `0x6a9340` | `Json::Value::asBool` | source_jsoncpp | 31 |
| 3 | GD | `0x6a9400` | `Json::Value::size` | source_jsoncpp | 51 |
| 4 | GD | `0x6a94b0` | `Json::Value::operator[]` | source_jsoncpp | 153 |
| 5 | GD | `0x6a9780` | `Json::Value::operator[]` | source_jsoncpp | 90 |
| 6 | GD | `0x6a98e0` | `Json::Value::operator[]` | source_jsoncpp | 23 |
| 7 | GD | `0x6a9960` | `Json::Value::resolveReference` | source_jsoncpp | 177 |
| 8 | GD | `0x6a9c80` | `Json::Value::find` | source_jsoncpp | 129 |
| 9 | GD | `0x6a9e50` | `Json::Value::getMemberNames` | source_jsoncpp | 123 |
| 10 | GD | `0x6aa080` | `Json::Value::isInt` | source_jsoncpp | 29 |
| 11 | GD | `0x6aa110` | `Json::Value::isInt64` | source_jsoncpp | 34 |
| 12 | GD | `0x6aa1b0` | `Json::Value::isUInt64` | source_jsoncpp | 26 |
| 13 | GD | `0x6aa230` | `Json::Value::setComment` | source_jsoncpp | 31 |
| 14 | GD | `0x6aa2e0` | `Json::valueToString` | source_jsoncpp | 53 |
| 15 | GD | `0x6aa430` | `Json::valueToString` | source_jsoncpp | 24 |
| 16 | GD | `0x6aa4f0` | `Json::valueToString` | source_jsoncpp | 73 |
| 17 | GD | `0x6aa650` | `Json::valueToString` | source_jsoncpp | 10 |
| 18 | GD | `0x6aa680` | `Json::valueToString` | source_jsoncpp | 18 |
| 19 | GD | `0x6aa6e0` | `Json::valueToQuotedStringN` | source_jsoncpp | 292 |
| 20 | GD | `0x6aad60` | `GameObjectIdManager::~GameObjectIdManager` | source_jsoncpp | 7 |
| 21 | GD | `0x6aad70` | `Json::FastWriter::write` | source_jsoncpp | 22 |
| 22 | GD | `0x6aae10` | `Json::FastWriter::writeValue` | source_jsoncpp | 223 |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/source_jsoncpp.cpp`
- `src/Server/GameDaemon/source_jsoncpp.h`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-43.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
