# lift-gamedaemon-2: VC headers and no-file functions and BloodLib and others: nofile, include_property, lock, propertyfield, ...

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
| Depends on | `lift-gamedaemon-e12`, `lift-gamedaemon-e25` |
| Pattern | `src/Server/BloodLib/source/RefCntObject.cpp` |
| Plan | `Docs/Plan/gamedaemon-lift.md` sections 1, 3, 5 |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Grep `Docs/Parity/lessons.md` for A2 (block order), A6 (per-exe path literals), A12 (PDB member types), A18 (destructors), A21 (PDB facts) and A22 (per-exe source form). Do not read it in full.
- Pattern: `src/Server/BloodLib/source/RefCntObject.cpp`. Read it one time. Use its form for the functions of this card.
- Dead-strip: `wmain` and most callers are still `LIFT_STUB` bodies. `/OPT:REF` removes a lifted function that has no live caller, and funcdiff then cannot pair it. For each function in scope with no live caller, add `#pragma comment(linker, "/INCLUDE:<public name>")` in its `.cpp` (public names: `llvm-pdbutil dump -publics`; grep `/INCLUDE` in `Docs/Parity/lessons.md`). Do not add a pragma for a function that a lifted caller keeps.

## Scope

23 functions, about 923 pseudocode lines (about 7,384 tokens). Stems: `nofile`, `include_property`, `lock`, `propertyfield`, `include_refcntobject`.

The easy functions of this stem are in `lift-gamedaemon-e12`, `lift-gamedaemon-e25`. Do not change them unless a fix needs it.

| n | Exe | RVA | PDB name | Stem | Lines |
| ---: | --- | --- | --- | --- | ---: |
| 1 | GD | `0x157c0` | `ZipPackedReaderIO::FileName::~FileName` | nofile | 38 |
| 2 | GD | `0xc0000` | `LogoutOkParam::~LogoutOkParam` | nofile | 31 |
| 3 | GD | `0x13fd20` | `EnterWorldOkParam::~EnterWorldOkParam` | nofile | 48 |
| 4 | GD | `0x681060` | `Json::Reader::~Reader` | nofile | 40 |
| 5 | GD | `0x6a8430` | `Json::LogicError::~LogicError` | nofile | 8 |
| 6 | GD | `0x6a85d0` | `Json::LogicError::LogicError` | nofile | 9 |
| 7 | GD | `0xe230` | `Property::Set` | include_property | 30 |
| 8 | GD | `0x1d120` | `Property::GetFlag` | include_property | 18 |
| 9 | GD | `0x8c2b0` | `Property::Set` | include_property | 73 |
| 10 | GD | `0x1ed800` | `Property::Set` | include_property | 76 |
| 11 | GD | `0x1cbc0` | `AutoCS::~AutoCS` | lock | 8 |
| 12 | GD | `0x68bab0` | `f_ability<char,-128,127>::Set` | propertyfield | 40 |
| 13 | GD | `0x68bb40` | `f_ability<char,-128,127>::Set` | propertyfield | 71 |
| 14 | GD | `0x68bcc0` | `f_ability<short,-32768,32767>::Set` | propertyfield | 40 |
| 15 | GD | `0x68bd50` | `f_ability<short,-32768,32767>::Set` | propertyfield | 71 |
| 16 | GD | `0x68bed0` | `f_ability<int,-2147483648,2147483647>::Set` | propertyfield | 40 |
| 17 | GD | `0x68bf60` | `f_ability<int,-2147483648,2147483647>::Set` | propertyfield | 71 |
| 18 | GD | `0x68c0d0` | `f_ability<__int64,-9223372036854775808,9223372036854775807>::Set` | propertyfield | 85 |
| 19 | GD | `0xa870` | `RefCntObject::addReferenceCount` | include_refcntobject | 50 |
| 20 | GD | `0x8b110` | `Pointer2<ChallengeParty>::operator=` | include_refcntobject | 26 |
| 21 | GD | `0x176380` | `Pointer2<Guild>::Pointer2<Guild>` | include_refcntobject | 13 |
| 22 | GD | `0x3466d0` | `Pointer2<Pc>::operator=` | include_refcntobject | 15 |
| 23 | GD | `0x42e5d0` | `Pointer2<Creature>::operator=` | include_refcntobject | 22 |

### Shared functions

These functions are in shared source. They are not MATCH in each lifted exe that has them.

| PDB name | Shared file | Other exes | Note |
| --- | --- | --- | --- |
| `RefCntObject::addReferenceCount` | `src/Server/BloodLib/source/RefCntObject.cpp` | CacheGate, LobbyDaemon, LobbyGate, PostOfficeDaemon, SmartCouponDaemon | - |

Same name in a lifted exe (a different body is possible): `AutoCS::~AutoCS` (src/Server/Economy/MarketDealerDaemon/JobContext.cpp).

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Shared functions: fix them in the shared file. If GameDaemon needs another form, use a per-exe copy in `lift_common_gd` or a `LIFT_EXE_` wrapper (A22, pattern 35). The 5 other exes must keep each MATCH. A MATCH to DIFF change needs an `allow-worse.txt` row with the counts.
6. An EXCLUDED function has a proof that no honest source fix exists in that exe. Read the proof first. If the same cause applies to GameDaemon, write the function under "Not done" with the proof reference. Do not edit `excluded.tsv`.
7. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/nofile.cpp`
- `src/Server/GameDaemon/nofile.h`
- `src/Server/GameDaemon/include_property.cpp`
- `src/Server/GameDaemon/include_property.h`
- `src/Server/GameDaemon/lock.cpp`
- `src/Server/GameDaemon/lock.h`
- `src/Server/GameDaemon/propertyfield.cpp`
- `src/Server/GameDaemon/propertyfield.h`
- `src/Server/GameDaemon/include_refcntobject.cpp`
- `src/Server/GameDaemon/include_refcntobject.h`
- `src/Server/BloodLib/source/RefCntObject.cpp`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-2.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
