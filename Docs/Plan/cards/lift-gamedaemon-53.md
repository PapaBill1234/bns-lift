# lift-gamedaemon-53: DataReader: elreaderimpl part 2/2

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
| Depends on | `lift-gamedaemon-e26`, `lift-gamedaemon-40`, `lift-gamedaemon-52`, `lift-gamedaemon-56`, `lift-gamedaemon-51` |
| Pattern | `src/library/FsdReader/FsdDecomposer.cpp` |
| Plan | `Docs/Plan/gamedaemon-lift.md` sections 1, 3, 5 |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Grep `Docs/Parity/lessons.md` for A2 (block order), A6 (per-exe path literals), A12 (PDB member types), A18 (destructors), A21 (PDB facts) and A22 (per-exe source form). Do not read it in full.
- Pattern: `src/library/FsdReader/FsdDecomposer.cpp`. Read it one time. Use its form for the functions of this card.
- Dead-strip: `wmain` and most callers are still `LIFT_STUB` bodies. `/OPT:REF` removes a lifted function that has no live caller, and funcdiff then cannot pair it. For each function in scope with no live caller, add `#pragma comment(linker, "/INCLUDE:<public name>")` in its `.cpp` (public names: `llvm-pdbutil dump -publics`; grep `/INCLUDE` in `Docs/Parity/lessons.md`). Do not add a pragma for a function that a lifted caller keeps.

## Scope

28 functions, about 2,017 pseudocode lines (about 16,136 tokens). Stems: `elreaderimpl`.

The easy functions of this stem are in `lift-gamedaemon-e26`. Do not change them unless a fix needs it.

This card is part 2/2 of stem `elreaderimpl`. The other parts are in other cards of this wave. They run one after the other (column "Depends on"). Edit only the functions in this table.

| n | Exe | RVA | PDB name | Stem | Lines |
| ---: | --- | --- | --- | --- | ---: |
| 1 | GD | `0x6f0500` | `DrElReaderImpl::readTRef` | elreaderimpl | 108 |
| 2 | GD | `0x6f06e0` | `DrElReaderImpl::readScriptObj` | elreaderimpl | 200 |
| 3 | GD | `0x6f0ab0` | `DrElReaderImpl::readIcon` | elreaderimpl | 75 |
| 4 | GD | `0x6f0c30` | `DrElReaderImpl::readDateTime32` | elreaderimpl | 34 |
| 5 | GD | `0x6f0cf0` | `DrElReaderImpl::readDateTime64` | elreaderimpl | 34 |
| 6 | GD | `0x6f0dc0` | `DrElReaderImpl::RelocateMemory` | elreaderimpl | 13 |
| 7 | GD | `0x6f11c0` | `replaceEscaping` | elreaderimpl | 116 |
| 8 | GD | `0x6f1360` | `printSingleNode` | elreaderimpl | 118 |
| 9 | GD | `0x6f15c0` | `printNodeStart` | elreaderimpl | 118 |
| 10 | GD | `0x6f1820` | `printNodeEnd` | elreaderimpl | 33 |
| 11 | GD | `0x6f18c0` | `xmlNodeTraverse` | elreaderimpl | 28 |
| 12 | GD | `0x6f1960` | `printChildNode` | elreaderimpl | 45 |
| 13 | GD | `0x6f1a50` | `DrElReaderImpl::readNative` | elreaderimpl | 54 |
| 14 | GD | `0x6f1b70` | `DrElReaderImpl::__readAttr` | elreaderimpl | 111 |
| 15 | GD | `0x6f1ee0` | `DrElReaderImpl::readAttr` | elreaderimpl | 98 |
| 16 | GD | `0x6f2090` | `DrElReaderImpl::readSetupedAttr` | elreaderimpl | 97 |
| 17 | GD | `0x6f2250` | `DrElReaderImpl::readDefaultAttr` | elreaderimpl | 63 |
| 18 | GD | `0x6f2370` | `DrElReaderImpl::setupDefaultEl` | elreaderimpl | 241 |
| 19 | GD | `0x6f2760` | `DrElReaderImpl::Setup` | elreaderimpl | 17 |
| 20 | GD | `0x6f2790` | `DrElReaderImpl::readAlias` | elreaderimpl | 86 |
| 21 | GD | `0x6f29e0` | `DrElReaderImpl::initEl` | elreaderimpl | 37 |
| 22 | GD | `0x6f2b10` | `DrElReaderImpl::initDefaultEl` | elreaderimpl | 35 |
| 23 | GD | `0x6f2c10` | `DrElReaderImpl::readEl` | elreaderimpl | 56 |
| 24 | GD | `0x6f2d70` | `DrElReaderImpl::readSetupedEl` | elreaderimpl | 56 |
| 25 | GD | `0x6f2ed0` | `DrElReaderImpl::ReadAlias` | elreaderimpl | 31 |
| 26 | GD | `0x6f2f90` | `DrElReaderImpl::ReadHeader` | elreaderimpl | 28 |
| 27 | GD | `0x6f3030` | `DrElReaderImpl::ReadEl` | elreaderimpl | 40 |
| 28 | GD | `0x6f3150` | `DrElReaderImpl::ReadDefaultEl` | elreaderimpl | 45 |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/elreaderimpl.cpp`
- `src/Server/GameDaemon/elreaderimpl.h`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-53.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
