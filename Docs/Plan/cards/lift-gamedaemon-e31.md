# lift-gamedaemon-e31: Easy leaves (GameDaemon): effect_cpp_2, creature_h, zone_cpp_1, skill, ...

| Item | Value |
| --- | --- |
| Exe | GD |
| Source build | GameDaemon 2019 + PDB (VS2010 SP1) |
| Exe file | `<work-root>/ida/lift/GameDaemon/GameDaemon.exe` |
| PDB | `<work-root>/ida/lift/GameDaemon/GameDaemon.pdb` |
| Pseudocode | `~/.cache/bns-lift/hr/GameDaemon/<stem>.c` |
| Pseudocode index | `~/.cache/bns-lift/hr/GameDaemon/index.tsv` (stem, rva, name, first, last, status, source file, part) |
| Wave | E |
| Model | opus |
| Depends on | `lift-gamedaemon-0e` |
| Pattern | none |
| Plan | `Docs/Plan/gamedaemon-lift.md` sections 1, 3, 5 |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Grep `Docs/Parity/lessons.md` for A2 (block order), A6 (per-exe path literals), A12 (PDB member types), A18 (destructors), A21 (PDB facts) and A22 (per-exe source form). Do not read it in full.
- Pattern: none. No lifted file has the same role.
- Dead-strip: `wmain` and most callers are still `LIFT_STUB` bodies. `/OPT:REF` removes a lifted function that has no live caller, and funcdiff then cannot pair it. For each function in scope with no live caller, add `#pragma comment(linker, "/INCLUDE:<public name>")` in its `.cpp` (public names: `llvm-pdbutil dump -publics`; grep `/INCLUDE` in `Docs/Parity/lessons.md`). Do not add a pragma for a function that a lifted caller keeps.

## Scope

35 functions, about 721 pseudocode lines (about 5,768 tokens). Stems: `effect_cpp_2`, `creature_h`, `zone_cpp_1`, `skill`, `itempouch`, `effectcontent_h`.

Wave E (owner order 2026-11-27: the easiest work first). Each function in this card is a leaf: its body calls no other counted function that needs a lift. Thus a `LIFT_STUB` callee cannot keep it DIFF. Each function has at most 30 pseudocode lines. Ease key: 20.6 cost per function (rule in `Docs/Plan/gamedaemon-lift.md` section 3).

Lift only the functions in the table. The other functions of these stems are in later W cards. Those cards depend on this card.

| n | Exe | RVA | PDB name | Stem | Lines | Form |
| ---: | --- | --- | --- | --- | ---: | --- |
| 1 | GD | `0x5b03c0` | `EffectContainer::newIndex` | effect_cpp_2 | 29 | leaf |
| 2 | GD | `0x5b37f0` | `EffectFactory::CreateEffect` | effect_cpp_2 | 3 | empty |
| 3 | GD | `0x5b4870` | `EffectList::EffectList` | effect_cpp_2 | 29 | leaf |
| 4 | GD | `0x5b49f0` | `EffectList::Clear` | effect_cpp_2 | 30 | leaf |
| 5 | GD | `0x1d240` | `Creature::AddChangedPropertyId` | creature_h | 22 | leaf |
| 6 | GD | `0x1d280` | `Creature::AddChangedExtraPropertyId` | creature_h | 22 | leaf |
| 7 | GD | `0x1edbb0` | `Creature::IsCreatureInDuelCombat` | creature_h | 11 | leaf |
| 8 | GD | `0x1edbf0` | `CreatureStateKeeper::~CreatureStateKeeper` | creature_h | 19 | leaf |
| 9 | GD | `0x453650` | `ApplySkillModifyInfo::CalcRecycleDuration` | creature_h | 28 | leaf |
| 10 | GD | `0x4536f0` | `ApplySkillModifyInfo::CalcSpConsume` | creature_h | 26 | leaf |
| 11 | GD | `0x453740` | `ApplySkillModifyInfo::CalcDamagePowerPercent` | creature_h | 30 | leaf |
| 12 | GD | `0x4537e0` | `ApplySkillModifyInfo::CalcHealPercent` | creature_h | 26 | leaf |
| 13 | GD | `0x453880` | `ApplySkillModifyInfo::CalcHpDrainPercent` | creature_h | 28 | leaf |
| 14 | GD | `0x22e900` | `Zone::GetEnvWithGeoId` | zone_cpp_1 | 18 | leaf |
| 15 | GD | `0x22e960` | `Zone::GetEnv` | zone_cpp_1 | 18 | leaf |
| 16 | GD | `0x22ec00` | `Zone::GetNpcSquad` | zone_cpp_1 | 24 | leaf |
| 17 | GD | `0x22ec50` | `Zone::GetConvoy` | zone_cpp_1 | 24 | leaf |
| 18 | GD | `0x231510` | `Zone::spawnEnd` | zone_cpp_1 | 26 | leaf |
| 19 | GD | `0x234380` | `Zone::GetFieldItem` | zone_cpp_1 | 25 | leaf |
| 20 | GD | `0x2348d0` | `Zone::SelectFieldItem` | zone_cpp_1 | 30 | leaf |
| 21 | GD | `0x236630` | `Zone::GetCampfire` | zone_cpp_1 | 25 | leaf |
| 22 | GD | `0x58e8f0` | `SkillContainer::FindInPassiveSkills` | skill | 26 | leaf |
| 23 | GD | `0x58ebe0` | `SkillContainer::GetSkillPageEnable` | skill | 21 | leaf |
| 24 | GD | `0x58fc70` | `SkillContainer::GetCurrentSkillPageJobStyle` | skill | 21 | leaf |
| 25 | GD | `0x593020` | `SkillContainer::responseDispose` | skill | 30 | leaf |
| 26 | GD | `0x595430` | `SkillContainer::isCandidateSkill` | skill | 28 | leaf |
| 27 | GD | `0x40d810` | `ItemPouch::ItemPouch` | itempouch | 24 | leaf |
| 28 | GD | `0x40dd70` | `ItemPouch::Next` | itempouch | 29 | leaf |
| 29 | GD | `0x479ee0` | `TransitEffect::GetDataSubType` | effectcontent_h | 7 | getter |
| 30 | GD | `0x47a4a0` | `DashEffect::GetDataSubType` | effectcontent_h | 7 | getter |
| 31 | GD | `0x47a520` | `FallDamageEffect::GetDataSubType` | effectcontent_h | 7 | getter |
| 32 | GD | `0x47a530` | `AirDashEffect::GetDataSubType` | effectcontent_h | 7 | getter |
| 33 | GD | `0x47a770` | `OceanicEffect::GetDataSubType` | effectcontent_h | 7 | getter |
| 34 | GD | `0x47a7f0` | `FallDeathEffect::GetDataSubType` | effectcontent_h | 7 | getter |
| 35 | GD | `0x47a800` | `IncreaseSpecialSkillGaugeEffect::checkApply` | effectcontent_h | 7 | leaf |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/effect_cpp_2.cpp`
- `src/Server/GameDaemon/effect_cpp_2.h`
- `src/Server/GameDaemon/creature_h.cpp`
- `src/Server/GameDaemon/creature_h.h`
- `src/Server/GameDaemon/zone_cpp_1.cpp`
- `src/Server/GameDaemon/zone_cpp_1.h`
- `src/Server/GameDaemon/skill.cpp`
- `src/Server/GameDaemon/skill.h`
- `src/Server/GameDaemon/itempouch.cpp`
- `src/Server/GameDaemon/itempouch.h`
- `src/Server/GameDaemon/effectcontent_h.cpp`
- `src/Server/GameDaemon/effectcontent_h.h`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-e31.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
