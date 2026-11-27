# lift-gamedaemon-e5: Easy leaves (DataReader and Property headers): datareader, questtableimpl_h, tableimpl_h, challengelistproperty, ...

| Item | Value |
| --- | --- |
| Exe | GD |
| Source build | GameDaemon 2019 + PDB (VS2010 SP1) |
| Exe file | `<work-root>/ida/lift/GameDaemon/GameDaemon.exe` |
| PDB | `<work-root>/ida/lift/GameDaemon/GameDaemon.pdb` |
| Pseudocode | `~/.cache/bns-lift/hr/GameDaemon/<stem>.c` |
| Pseudocode index | `~/.cache/bns-lift/hr/GameDaemon/index.tsv` (stem, rva, name, first, last, status, source file, part) |
| Wave | E |
| Model | sonnet:high |
| Depends on | `lift-gamedaemon-0e` |
| Pattern | `src/library/FsdReader/FsdDecomposer.cpp` |
| Plan | `Docs/Plan/gamedaemon-lift.md` sections 1, 3, 5 |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Grep `Docs/Parity/lessons.md` for A2 (block order), A6 (per-exe path literals), A12 (PDB member types), A18 (destructors), A21 (PDB facts) and A22 (per-exe source form). Do not read it in full.
- Pattern: `src/library/FsdReader/FsdDecomposer.cpp`. Read it one time. Use its form for the functions of this card.
- Dead-strip: `wmain` and most callers are still `LIFT_STUB` bodies. `/OPT:REF` removes a lifted function that has no live caller, and funcdiff then cannot pair it. For each function in scope with no live caller, add `#pragma comment(linker, "/INCLUDE:<public name>")` in its `.cpp` (public names: `llvm-pdbutil dump -publics`; grep `/INCLUDE` in `Docs/Parity/lessons.md`). Do not add a pragma for a function that a lifted caller keeps.

## Scope

40 functions, about 284 pseudocode lines (about 2,272 tokens). Stems: `datareader`, `questtableimpl_h`, `tableimpl_h`, `challengelistproperty`, `slateproperty`, `accessoryproperty`, `acquiredskill1`, `creatureproperty`, `tableimpl_cpp`.

Wave E (owner order 2026-11-27: the easiest work first). Each function in this card is a leaf: its body calls no other counted function that needs a lift. Thus a `LIFT_STUB` callee cannot keep it DIFF. Each function has at most 30 pseudocode lines. Ease key: 7.1 cost per function (rule in `Docs/Plan/gamedaemon-lift.md` section 3).

Lift only the functions in the table. The other functions of these stems are in later W cards. Those cards depend on this card.

| n | Exe | RVA | PDB name | Stem | Lines | Form |
| ---: | --- | --- | --- | --- | ---: | --- |
| 1 | GD | `0x6eb2a0` | `GetDataReaderInterfaceVersion` | datareader | 7 | getter |
| 2 | GD | `0x6eb320` | `Logger` | datareader | 7 | getter |
| 3 | GD | `0x6f86e0` | `QuestTableImpl::GetMaxQuestId` | questtableimpl_h | 7 | getter |
| 4 | GD | `0x6f86f0` | `QuestTableImpl::GetQuestByIndex` | questtableimpl_h | 7 | getter |
| 5 | GD | `0x6f8700` | `QuestTableImpl::GetMaxQuestNum` | questtableimpl_h | 7 | getter |
| 6 | GD | `0x6fd290` | `DrDataTableImpl::UseLegacyElHeader` | tableimpl_h | 7 | setter |
| 7 | GD | `0x96c0` | `ChallengeListProperty::TypeId` | challengelistproperty | 7 | getter |
| 8 | GD | `0x96d0` | `ChallengeListProperty::Name` | challengelistproperty | 7 | getter |
| 9 | GD | `0x96e0` | `ChallengeListProperty::FieldMax` | challengelistproperty | 7 | getter |
| 10 | GD | `0x96f0` | `ChallengeListProperty::FieldDefine` | challengelistproperty | 7 | getter |
| 11 | GD | `0x9700` | `ChallengeListProperty::SyncMax` | challengelistproperty | 7 | getter |
| 12 | GD | `0x9710` | `ChallengeListProperty::SyncDefine` | challengelistproperty | 7 | getter |
| 13 | GD | `0x9750` | `SlateProperty::TypeId` | slateproperty | 7 | getter |
| 14 | GD | `0x9760` | `SlateProperty::Name` | slateproperty | 7 | getter |
| 15 | GD | `0x9770` | `SlateProperty::FieldMax` | slateproperty | 7 | getter |
| 16 | GD | `0x9780` | `SlateProperty::FieldDefine` | slateproperty | 7 | getter |
| 17 | GD | `0x9790` | `SlateProperty::SyncMax` | slateproperty | 7 | getter |
| 18 | GD | `0x97a0` | `SlateProperty::SyncDefine` | slateproperty | 7 | getter |
| 19 | GD | `0x191d0` | `AccessoryProperty::TypeId` | accessoryproperty | 7 | getter |
| 20 | GD | `0x191e0` | `AccessoryProperty::Version` | accessoryproperty | 7 | getter |
| 21 | GD | `0x191f0` | `AccessoryProperty::Name` | accessoryproperty | 7 | getter |
| 22 | GD | `0x19200` | `AccessoryProperty::FieldMax` | accessoryproperty | 7 | getter |
| 23 | GD | `0x19210` | `AccessoryProperty::FieldDefine` | accessoryproperty | 7 | getter |
| 24 | GD | `0x19220` | `AccessoryProperty::SyncMax` | accessoryproperty | 7 | getter |
| 25 | GD | `0x19230` | `AccessoryProperty::SyncDefine` | accessoryproperty | 7 | getter |
| 26 | GD | `0x19280` | `AcquiredSkill1::TypeId` | acquiredskill1 | 7 | getter |
| 27 | GD | `0x19290` | `AcquiredSkill1::Name` | acquiredskill1 | 7 | getter |
| 28 | GD | `0x192a0` | `AcquiredSkill1::FieldMax` | acquiredskill1 | 7 | getter |
| 29 | GD | `0x192b0` | `AcquiredSkill1::FieldDefine` | acquiredskill1 | 7 | getter |
| 30 | GD | `0x192c0` | `AcquiredSkill1::SyncMax` | acquiredskill1 | 7 | getter |
| 31 | GD | `0x192d0` | `AcquiredSkill1::SyncDefine` | acquiredskill1 | 7 | getter |
| 32 | GD | `0x19350` | `CreatureProperty::Version` | creatureproperty | 7 | getter |
| 33 | GD | `0x19360` | `CreatureProperty::Name` | creatureproperty | 7 | getter |
| 34 | GD | `0x19370` | `CreatureProperty::FieldMax` | creatureproperty | 7 | getter |
| 35 | GD | `0x19380` | `CreatureProperty::FieldDefine` | creatureproperty | 7 | getter |
| 36 | GD | `0x19390` | `CreatureProperty::SyncMax` | creatureproperty | 7 | getter |
| 37 | GD | `0x193a0` | `CreatureProperty::SyncDefine` | creatureproperty | 7 | getter |
| 38 | GD | `0x6f7430` | `DrDataTableImpl::~DrDataTableImpl` | tableimpl_cpp | 7 | xtor |
| 39 | GD | `0x6feec0` | `DrDataTableImpl::ReferenceCopiedEl` | tableimpl_cpp | 7 | getter |
| 40 | GD | `0x6fefa0` | `DrDataTableImpl::DrDataTableImpl` | tableimpl_cpp | 11 | xtor |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/datareader.cpp`
- `src/Server/GameDaemon/datareader.h`
- `src/Server/GameDaemon/questtableimpl_h.cpp`
- `src/Server/GameDaemon/questtableimpl_h.h`
- `src/Server/GameDaemon/tableimpl_h.cpp`
- `src/Server/GameDaemon/tableimpl_h.h`
- `src/Server/GameDaemon/challengelistproperty.cpp`
- `src/Server/GameDaemon/challengelistproperty.h`
- `src/Server/GameDaemon/slateproperty.cpp`
- `src/Server/GameDaemon/slateproperty.h`
- `src/Server/GameDaemon/accessoryproperty.cpp`
- `src/Server/GameDaemon/accessoryproperty.h`
- `src/Server/GameDaemon/acquiredskill1.cpp`
- `src/Server/GameDaemon/acquiredskill1.h`
- `src/Server/GameDaemon/creatureproperty.cpp`
- `src/Server/GameDaemon/creatureproperty.h`
- `src/Server/GameDaemon/tableimpl_cpp.cpp`
- `src/Server/GameDaemon/tableimpl_cpp.h`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-e5.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
