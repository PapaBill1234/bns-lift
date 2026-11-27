# lift-gamedaemon-41: BloodLib: source_jsoncpp part 1/2

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
| Depends on | `lift-gamedaemon-e25` |
| Pattern | none |
| Plan | `Docs/Plan/gamedaemon-lift.md` sections 1, 3, 5 |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Grep `Docs/Parity/lessons.md` for A2 (block order), A6 (per-exe path literals), A12 (PDB member types), A18 (destructors), A21 (PDB facts) and A22 (per-exe source form). Do not read it in full.
- Pattern: none. No lifted file has the same role.
- Dead-strip: `wmain` and most callers are still `LIFT_STUB` bodies. `/OPT:REF` removes a lifted function that has no live caller, and funcdiff then cannot pair it. For each function in scope with no live caller, add `#pragma comment(linker, "/INCLUDE:<public name>")` in its `.cpp` (public names: `llvm-pdbutil dump -publics`; grep `/INCLUDE` in `Docs/Parity/lessons.md`). Do not add a pragma for a function that a lifted caller keeps.

## Scope

17 functions, about 2,462 pseudocode lines (about 19,696 tokens). Stems: `source_jsoncpp`.

The easy functions of this stem are in `lift-gamedaemon-e25`. Do not change them unless a fix needs it.

This card is part 1/2 of stem `source_jsoncpp`. The other parts are in other cards of this wave. They run one after the other (column "Depends on"). Edit only the functions in this table.

| n | Exe | RVA | PDB name | Stem | Lines |
| ---: | --- | --- | --- | --- | ---: |
| 1 | GD | `0x6a4ca0` | `Json::codePointToUTF8` | source_jsoncpp | 112 |
| 2 | GD | `0x6a4f40` | `Json::Reader::parse` | source_jsoncpp | 82 |
| 3 | GD | `0x6a5120` | `Json::Reader::readValue` | source_jsoncpp | 183 |
| 4 | GD | `0x6a5560` | `Json::Reader::skipCommentTokens` | source_jsoncpp | 197 |
| 5 | GD | `0x6a58f0` | `Json::Reader::readToken` | source_jsoncpp | 186 |
| 6 | GD | `0x6a5c40` | `Json::Reader::readComment` | source_jsoncpp | 114 |
| 7 | GD | `0x6a5da0` | `Json::normalizeEOL` | source_jsoncpp | 127 |
| 8 | GD | `0x6a5f90` | `Json::Reader::addComment` | source_jsoncpp | 37 |
| 9 | GD | `0x6a6040` | `Json::Reader::readNumber` | source_jsoncpp | 62 |
| 10 | GD | `0x6a6120` | `Json::Reader::readObject` | source_jsoncpp | 405 |
| 11 | GD | `0x6a6970` | `Json::Reader::readArray` | source_jsoncpp | 264 |
| 12 | GD | `0x6a6ec0` | `Json::Reader::decodeNumber` | source_jsoncpp | 111 |
| 13 | GD | `0x6a70b0` | `Json::Reader::decodeNumber` | source_jsoncpp | 71 |
| 14 | GD | `0x6a71f0` | `Json::Reader::decodeDouble` | source_jsoncpp | 135 |
| 15 | GD | `0x6a7600` | `Json::Reader::decodeString` | source_jsoncpp | 141 |
| 16 | GD | `0x6a7860` | `Json::Reader::decodeString` | source_jsoncpp | 174 |
| 17 | GD | `0x6a7c00` | `Json::Reader::decodeUnicodeCodePoint` | source_jsoncpp | 61 |

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

Write `Docs/Plan/handoffs/lift-gamedaemon-41.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
