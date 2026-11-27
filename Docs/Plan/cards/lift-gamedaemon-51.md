# lift-gamedaemon-51: DataReader: elreaderimpl part 1/2

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
| Depends on | `lift-gamedaemon-e26`, `lift-gamedaemon-40`, `lift-gamedaemon-56` |
| Pattern | `src/library/FsdReader/FsdDecomposer.cpp` |
| Plan | `Docs/Plan/gamedaemon-lift.md` sections 1, 3, 5 |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Grep `Docs/Parity/lessons.md` for A2 (block order), A6 (per-exe path literals), A12 (PDB member types), A18 (destructors), A21 (PDB facts) and A22 (per-exe source form). Do not read it in full.
- Pattern: `src/library/FsdReader/FsdDecomposer.cpp`. Read it one time. Use its form for the functions of this card.
- Dead-strip: `wmain` and most callers are still `LIFT_STUB` bodies. `/OPT:REF` removes a lifted function that has no live caller, and funcdiff then cannot pair it. For each function in scope with no live caller, add `#pragma comment(linker, "/INCLUDE:<public name>")` in its `.cpp` (public names: `llvm-pdbutil dump -publics`; grep `/INCLUDE` in `Docs/Parity/lessons.md`). Do not add a pragma for a function that a lifted caller keeps.

## Scope

28 functions, about 2,257 pseudocode lines (about 18,056 tokens). Stems: `elreaderimpl`.

The easy functions of this stem are in `lift-gamedaemon-e26`. Do not change them unless a fix needs it.

This card is part 1/2 of stem `elreaderimpl`. The other parts are in other cards of this wave. They run one after the other (column "Depends on"). Edit only the functions in this table.

| n | Exe | RVA | PDB name | Stem | Lines |
| ---: | --- | --- | --- | --- | ---: |
| 1 | GD | `0x6ed6e0` | `DrElReaderImpl::GetElAllocedSize` | elreaderimpl | 182 |
| 2 | GD | `0x6ed9b0` | `DrElReaderImpl::DeleteElementExtra` | elreaderimpl | 141 |
| 3 | GD | `0x6edcb0` | `DrElReaderImpl::RelocateAddress` | elreaderimpl | 116 |
| 4 | GD | `0x6edef0` | `DrElReaderImpl::__readBool` | elreaderimpl | 33 |
| 5 | GD | `0x6edfe0` | `DrElReaderImpl::shinkBlank` | elreaderimpl | 75 |
| 6 | GD | `0x6ee0e0` | `DrElReaderImpl::isMultiKey` | elreaderimpl | 35 |
| 7 | GD | `0x6ee160` | `DrElReaderImpl::tokenize` | elreaderimpl | 25 |
| 8 | GD | `0x6ee5c0` | `DrElReaderImpl::readSub` | elreaderimpl | 33 |
| 9 | GD | `0x6ee630` | `DrElReaderImpl::readVersion` | elreaderimpl | 98 |
| 10 | GD | `0x6ee860` | `DrElReaderImpl::AllocedSize` | elreaderimpl | 7 |
| 11 | GD | `0x6ee870` | `DrElReaderImpl::RelocateElMemory` | elreaderimpl | 259 |
| 12 | GD | `0x6eedf0` | `DrElReaderImpl::DeleteElementExtraNativePointer` | elreaderimpl | 174 |
| 13 | GD | `0x6ef1b0` | `DrElReaderImpl::__readStr` | elreaderimpl | 33 |
| 14 | GD | `0x6ef280` | `DrElReaderImpl::__readRef` | elreaderimpl | 114 |
| 15 | GD | `0x6ef5b0` | `DrElReaderImpl::__readDateTime` | elreaderimpl | 84 |
| 16 | GD | `0x6ef7c0` | `DrElReaderImpl::readInt8` | elreaderimpl | 51 |
| 17 | GD | `0x6ef870` | `DrElReaderImpl::readInt16` | elreaderimpl | 51 |
| 18 | GD | `0x6ef920` | `DrElReaderImpl::readInt32` | elreaderimpl | 51 |
| 19 | GD | `0x6ef9d0` | `DrElReaderImpl::readInt64` | elreaderimpl | 51 |
| 20 | GD | `0x6efa80` | `DrElReaderImpl::readFloat32` | elreaderimpl | 50 |
| 21 | GD | `0x6efb40` | `DrElReaderImpl::readVector16` | elreaderimpl | 88 |
| 22 | GD | `0x6efcb0` | `DrElReaderImpl::readVector32` | elreaderimpl | 88 |
| 23 | GD | `0x6efe20` | `DrElReaderImpl::readIColor` | elreaderimpl | 88 |
| 24 | GD | `0x6eff90` | `DrElReaderImpl::readFColor` | elreaderimpl | 99 |
| 25 | GD | `0x6f0140` | `DrElReaderImpl::readBox` | elreaderimpl | 105 |
| 26 | GD | `0x6f0340` | `DrElReaderImpl::readMsec` | elreaderimpl | 55 |
| 27 | GD | `0x6f0400` | `DrElReaderImpl::readAngle` | elreaderimpl | 44 |
| 28 | GD | `0x6f04a0` | `DrElReaderImpl::readStr` | elreaderimpl | 27 |

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

Write `Docs/Plan/handoffs/lift-gamedaemon-51.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
