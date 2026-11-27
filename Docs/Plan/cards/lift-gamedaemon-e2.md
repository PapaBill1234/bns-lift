# lift-gamedaemon-e2: Easy leaves (Property headers): activatedteleport, clientoption_h, collectingproperty, contentquotaproperty, ...

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
| Pattern | none |
| Plan | `Docs/Plan/gamedaemon-lift.md` sections 1, 3, 5 |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Grep `Docs/Parity/lessons.md` for A2 (block order), A6 (per-exe path literals), A12 (PDB member types), A18 (destructors), A21 (PDB facts) and A22 (per-exe source form). Do not read it in full.
- Pattern: none. No lifted file has the same role.
- Dead-strip: `wmain` and most callers are still `LIFT_STUB` bodies. `/OPT:REF` removes a lifted function that has no live caller, and funcdiff then cannot pair it. For each function in scope with no live caller, add `#pragma comment(linker, "/INCLUDE:<public name>")` in its `.cpp` (public names: `llvm-pdbutil dump -publics`; grep `/INCLUDE` in `Docs/Parity/lessons.md`). Do not add a pragma for a function that a lifted caller keeps.

## Scope

40 functions, about 280 pseudocode lines (about 2,240 tokens). Stems: `activatedteleport`, `clientoption_h`, `collectingproperty`, `contentquotaproperty`, `costumeproperty`, `discoveryarea`, `effectproperty_h`.

Wave E (owner order 2026-11-27: the easiest work first). Each function in this card is a leaf: its body calls no other counted function that needs a lift. Thus a `LIFT_STUB` callee cannot keep it DIFF. Each function has at most 30 pseudocode lines. Ease key: 7.0 cost per function (rule in `Docs/Plan/gamedaemon-lift.md` section 3).

Lift only the functions in the table. The other functions of these stems are in later W cards. Those cards depend on this card.

| n | Exe | RVA | PDB name | Stem | Lines | Form |
| ---: | --- | --- | --- | --- | ---: | --- |
| 1 | GD | `0x193f0` | `ActivatedTeleport::TypeId` | activatedteleport | 7 | getter |
| 2 | GD | `0x19400` | `ActivatedTeleport::Name` | activatedteleport | 7 | getter |
| 3 | GD | `0x19410` | `ActivatedTeleport::FieldMax` | activatedteleport | 7 | getter |
| 4 | GD | `0x19420` | `ActivatedTeleport::FieldDefine` | activatedteleport | 7 | getter |
| 5 | GD | `0x19430` | `ActivatedTeleport::SyncMax` | activatedteleport | 7 | getter |
| 6 | GD | `0x19440` | `ActivatedTeleport::SyncDefine` | activatedteleport | 7 | getter |
| 7 | GD | `0x19490` | `ClientOption::TypeId` | clientoption_h | 7 | getter |
| 8 | GD | `0x194a0` | `ClientOption::Name` | clientoption_h | 7 | getter |
| 9 | GD | `0x194b0` | `ClientOption::FieldMax` | clientoption_h | 7 | getter |
| 10 | GD | `0x194c0` | `ClientOption::FieldDefine` | clientoption_h | 7 | getter |
| 11 | GD | `0x194d0` | `ClientOption::SyncMax` | clientoption_h | 7 | getter |
| 12 | GD | `0x194e0` | `ClientOption::SyncDefine` | clientoption_h | 7 | getter |
| 13 | GD | `0x19580` | `CollectingProperty::TypeId` | collectingproperty | 7 | getter |
| 14 | GD | `0x195a0` | `CollectingProperty::Name` | collectingproperty | 7 | getter |
| 15 | GD | `0x195b0` | `CollectingProperty::FieldMax` | collectingproperty | 7 | getter |
| 16 | GD | `0x195c0` | `CollectingProperty::FieldDefine` | collectingproperty | 7 | getter |
| 17 | GD | `0x195d0` | `CollectingProperty::SyncMax` | collectingproperty | 7 | getter |
| 18 | GD | `0x195e0` | `CollectingProperty::SyncDefine` | collectingproperty | 7 | getter |
| 19 | GD | `0x19620` | `ContentQuotaProperty::Name` | contentquotaproperty | 7 | getter |
| 20 | GD | `0x19630` | `ContentQuotaProperty::FieldMax` | contentquotaproperty | 7 | getter |
| 21 | GD | `0x19640` | `ContentQuotaProperty::FieldDefine` | contentquotaproperty | 7 | getter |
| 22 | GD | `0x19650` | `ContentQuotaProperty::SyncMax` | contentquotaproperty | 7 | getter |
| 23 | GD | `0x19660` | `ContentQuotaProperty::SyncDefine` | contentquotaproperty | 7 | getter |
| 24 | GD | `0x196b0` | `CostumeProperty::Version` | costumeproperty | 7 | getter |
| 25 | GD | `0x196c0` | `CostumeProperty::Name` | costumeproperty | 7 | getter |
| 26 | GD | `0x196d0` | `CostumeProperty::FieldMax` | costumeproperty | 7 | getter |
| 27 | GD | `0x196e0` | `CostumeProperty::FieldDefine` | costumeproperty | 7 | getter |
| 28 | GD | `0x196f0` | `CostumeProperty::SyncMax` | costumeproperty | 7 | getter |
| 29 | GD | `0x19700` | `CostumeProperty::SyncDefine` | costumeproperty | 7 | getter |
| 30 | GD | `0x19750` | `DiscoveryArea::TypeId` | discoveryarea | 7 | getter |
| 31 | GD | `0x19760` | `DiscoveryArea::Name` | discoveryarea | 7 | getter |
| 32 | GD | `0x19770` | `DiscoveryArea::FieldMax` | discoveryarea | 7 | getter |
| 33 | GD | `0x19780` | `DiscoveryArea::FieldDefine` | discoveryarea | 7 | getter |
| 34 | GD | `0x19790` | `DiscoveryArea::SyncMax` | discoveryarea | 7 | getter |
| 35 | GD | `0x197a0` | `DiscoveryArea::SyncDefine` | discoveryarea | 7 | getter |
| 36 | GD | `0x19870` | `EffectProperty::Name` | effectproperty_h | 7 | getter |
| 37 | GD | `0x19880` | `EffectProperty::FieldMax` | effectproperty_h | 7 | getter |
| 38 | GD | `0x19890` | `EffectProperty::FieldDefine` | effectproperty_h | 7 | getter |
| 39 | GD | `0x198a0` | `EffectProperty::SyncMax` | effectproperty_h | 7 | getter |
| 40 | GD | `0x198b0` | `EffectProperty::SyncDefine` | effectproperty_h | 7 | getter |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/activatedteleport.cpp`
- `src/Server/GameDaemon/activatedteleport.h`
- `src/Server/GameDaemon/clientoption_h.cpp`
- `src/Server/GameDaemon/clientoption_h.h`
- `src/Server/GameDaemon/collectingproperty.cpp`
- `src/Server/GameDaemon/collectingproperty.h`
- `src/Server/GameDaemon/contentquotaproperty.cpp`
- `src/Server/GameDaemon/contentquotaproperty.h`
- `src/Server/GameDaemon/costumeproperty.cpp`
- `src/Server/GameDaemon/costumeproperty.h`
- `src/Server/GameDaemon/discoveryarea.cpp`
- `src/Server/GameDaemon/discoveryarea.h`
- `src/Server/GameDaemon/effectproperty_h.cpp`
- `src/Server/GameDaemon/effectproperty_h.h`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-e2.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
