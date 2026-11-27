# lift-gamedaemon-42: BloodLib: source_jsoncpp part 2/3

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
| Depends on | `lift-gamedaemon-41` |
| Pattern | none |
| Plan | `Docs/Plan/gamedaemon-lift.md` sections 1, 3, 5 |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Grep `Docs/Parity/lessons.md` for A2 (block order), A6 (per-exe path literals), A12 (PDB member types), A18 (destructors), A21 (PDB facts) and A22 (per-exe source form). Do not read it in full.
- Pattern: none. Read the functions that `lift-gamedaemon-41` lifted in the same file first. Use their form.

## Scope

23 functions, about 1,028 pseudocode lines (about 8,224 tokens). Stems: `source_jsoncpp`.

This card is part 2/3 of stem `source_jsoncpp`. The other parts are in other cards of this wave. They run one after the other (column "Depends on"). Edit only the functions in this table.

| n | Exe | RVA | PDB name | Stem | Lines |
| ---: | --- | --- | --- | --- | ---: |
| 1 | GD | `0x6a7db0` | `Json::Reader::decodeUnicodeEscapeSequence` | source_jsoncpp | 77 |
| 2 | GD | `0x6a7f20` | `Json::Reader::addError` | source_jsoncpp | 73 |
| 3 | GD | `0x6a8090` | `Json::Reader::recoverFromError` | source_jsoncpp | 18 |
| 4 | GD | `0x6a8100` | `Json::Reader::currentValue` | source_jsoncpp | 31 |
| 5 | GD | `0x6a81d0` | `Json::duplicateStringValue` | source_jsoncpp | 31 |
| 6 | GD | `0x6a8290` | `Json::duplicateAndPrefixStringValue` | source_jsoncpp | 45 |
| 7 | GD | `0x6a83c0` | `Json::Exception::~Exception` | source_jsoncpp | 17 |
| 8 | GD | `0x6a8420` | `Json::Exception::what` | source_jsoncpp | 13 |
| 9 | GD | `0x6a8440` | `Json::throwRuntimeError` | source_jsoncpp | 22 |
| 10 | GD | `0x6a8540` | `Json::throwLogicError` | source_jsoncpp | 22 |
| 11 | GD | `0x6a8600` | `Json::Value::CommentInfo::~CommentInfo` | source_jsoncpp | 11 |
| 12 | GD | `0x6a8620` | `Json::Value::CommentInfo::setComment` | source_jsoncpp | 36 |
| 13 | GD | `0x6a8720` | `Json::Value::CZString::CZString` | source_jsoncpp | 26 |
| 14 | GD | `0x6a87a0` | `Json::Value::CZString::~CZString` | source_jsoncpp | 11 |
| 15 | GD | `0x6a87d0` | `Json::Value::CZString::operator<` | source_jsoncpp | 28 |
| 16 | GD | `0x6a8850` | `Json::Value::Value` | source_jsoncpp | 86 |
| 17 | GD | `0x6a8a10` | `Json::Value::~Value` | source_jsoncpp | 48 |
| 18 | GD | `0x6a8ae0` | `Json::Value::operator=` | source_jsoncpp | 34 |
| 19 | GD | `0x6a8b80` | `Json::Value::asString` | source_jsoncpp | 82 |
| 20 | GD | `0x6a8d00` | `Json::Value::asInt` | source_jsoncpp | 88 |
| 21 | GD | `0x6a8ea0` | `Json::Value::asInt64` | source_jsoncpp | 85 |
| 22 | GD | `0x6a9010` | `Json::Value::asUInt64` | source_jsoncpp | 88 |
| 23 | GD | `0x6a91a0` | `Json::Value::asDouble` | source_jsoncpp | 56 |

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

Write `Docs/Plan/handoffs/lift-gamedaemon-42.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
