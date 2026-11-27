# lift-gamedaemon-42: BloodLib: source_jsoncpp part 2/2

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
| Depends on | `lift-gamedaemon-e25`, `lift-gamedaemon-41` |
| Pattern | none |
| Plan | `Docs/Plan/gamedaemon-lift.md` sections 1, 3, 5 |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Grep `Docs/Parity/lessons.md` for A2 (block order), A6 (per-exe path literals), A12 (PDB member types), A18 (destructors), A21 (PDB facts) and A22 (per-exe source form). Do not read it in full.
- Pattern: none. Read the functions that `lift-gamedaemon-41` lifted in the same file first. Use their form.
- Dead-strip: `wmain` and most callers are still `LIFT_STUB` bodies. `/OPT:REF` removes a lifted function that has no live caller, and funcdiff then cannot pair it. For each function in scope with no live caller, add `#pragma comment(linker, "/INCLUDE:<public name>")` in its `.cpp` (public names: `llvm-pdbutil dump -publics`; grep `/INCLUDE` in `Docs/Parity/lessons.md`). Do not add a pragma for a function that a lifted caller keeps.

## Scope

32 functions, about 2,465 pseudocode lines (about 19,720 tokens). Stems: `source_jsoncpp`.

The easy functions of this stem are in `lift-gamedaemon-e25`. Do not change them unless a fix needs it.

This card is part 2/2 of stem `source_jsoncpp`. The other parts are in other cards of this wave. They run one after the other (column "Depends on"). Edit only the functions in this table.

| n | Exe | RVA | PDB name | Stem | Lines |
| ---: | --- | --- | --- | --- | ---: |
| 1 | GD | `0x6a7db0` | `Json::Reader::decodeUnicodeEscapeSequence` | source_jsoncpp | 77 |
| 2 | GD | `0x6a7f20` | `Json::Reader::addError` | source_jsoncpp | 73 |
| 3 | GD | `0x6a8090` | `Json::Reader::recoverFromError` | source_jsoncpp | 18 |
| 4 | GD | `0x6a8100` | `Json::Reader::currentValue` | source_jsoncpp | 31 |
| 5 | GD | `0x6a81d0` | `Json::duplicateStringValue` | source_jsoncpp | 31 |
| 6 | GD | `0x6a8290` | `Json::duplicateAndPrefixStringValue` | source_jsoncpp | 45 |
| 7 | GD | `0x6a8620` | `Json::Value::CommentInfo::setComment` | source_jsoncpp | 36 |
| 8 | GD | `0x6a8720` | `Json::Value::CZString::CZString` | source_jsoncpp | 26 |
| 9 | GD | `0x6a8850` | `Json::Value::Value` | source_jsoncpp | 86 |
| 10 | GD | `0x6a8a10` | `Json::Value::~Value` | source_jsoncpp | 48 |
| 11 | GD | `0x6a8ae0` | `Json::Value::operator=` | source_jsoncpp | 34 |
| 12 | GD | `0x6a8b80` | `Json::Value::asString` | source_jsoncpp | 82 |
| 13 | GD | `0x6a8d00` | `Json::Value::asInt` | source_jsoncpp | 88 |
| 14 | GD | `0x6a8ea0` | `Json::Value::asInt64` | source_jsoncpp | 85 |
| 15 | GD | `0x6a9010` | `Json::Value::asUInt64` | source_jsoncpp | 88 |
| 16 | GD | `0x6a91a0` | `Json::Value::asDouble` | source_jsoncpp | 56 |
| 17 | GD | `0x6a9270` | `Json::Value::asFloat` | source_jsoncpp | 56 |
| 18 | GD | `0x6a9340` | `Json::Value::asBool` | source_jsoncpp | 31 |
| 19 | GD | `0x6a9400` | `Json::Value::size` | source_jsoncpp | 51 |
| 20 | GD | `0x6a94b0` | `Json::Value::operator[]` | source_jsoncpp | 153 |
| 21 | GD | `0x6a9780` | `Json::Value::operator[]` | source_jsoncpp | 90 |
| 22 | GD | `0x6a98e0` | `Json::Value::operator[]` | source_jsoncpp | 23 |
| 23 | GD | `0x6a9960` | `Json::Value::resolveReference` | source_jsoncpp | 177 |
| 24 | GD | `0x6a9c80` | `Json::Value::find` | source_jsoncpp | 129 |
| 25 | GD | `0x6a9e50` | `Json::Value::getMemberNames` | source_jsoncpp | 123 |
| 26 | GD | `0x6aa110` | `Json::Value::isInt64` | source_jsoncpp | 34 |
| 27 | GD | `0x6aa230` | `Json::Value::setComment` | source_jsoncpp | 31 |
| 28 | GD | `0x6aa2e0` | `Json::valueToString` | source_jsoncpp | 53 |
| 29 | GD | `0x6aa4f0` | `Json::valueToString` | source_jsoncpp | 73 |
| 30 | GD | `0x6aa6e0` | `Json::valueToQuotedStringN` | source_jsoncpp | 292 |
| 31 | GD | `0x6aad70` | `Json::FastWriter::write` | source_jsoncpp | 22 |
| 32 | GD | `0x6aae10` | `Json::FastWriter::writeValue` | source_jsoncpp | 223 |

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
