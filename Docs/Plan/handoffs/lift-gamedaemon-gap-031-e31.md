# lift-gamedaemon-gap-031-e31 handoff

## Lifted

- `itempouch`: `ItemPouch::ItemPouch` (0x40d810), `ItemPouch::Next` (0x40dd70).
- `effect_cpp_2`: `EffectContainer::newIndex` (0x5b03c0), `EffectList::EffectList` (0x5b4870), `EffectList::Clear` (0x5b49f0).
- `skill`: `SkillContainer::FindInPassiveSkills` (0x58e8f0), `SkillContainer::GetSkillPageEnable` (0x58ebe0), `SkillContainer::GetCurrentSkillPageJobStyle` (0x58fc70), `SkillContainer::isCandidateSkill` (0x595430).
- `zone_cpp_1`: `Zone::GetEnvWithGeoId` (0x22e900), `Zone::GetEnv` (0x22e960), `Zone::GetFieldItem` (0x234380), `Zone::GetCampfire` (0x236630).
- `creature_h`: `Creature::AddChangedPropertyId` (0x1d240), `Creature::AddChangedExtraPropertyId` (0x1d280), `Creature::IsCreatureInDuelCombat` (0x1edbb0), and the five `ApplySkillModifyInfo::Calc*` functions (0x453650, 0x4536f0, 0x453740, 0x4537e0, 0x453880).
- `effectcontent_h`: the six `GetDataSubType` getters (0x479ee0, 0x47a4a0, 0x47a520, 0x47a530, 0x47a770, 0x47a7f0) and `IncreaseSpecialSkillGaugeEffect::checkApply` (0x47a800). The enumerators of `Data::EffectRecordSubType` are not declared, so the getters cast the 2019 values.

## Round 2 repair (pdb_layout)

The round 1 gate failed in `pdb_layout`. The check refuses a member of a PDB class when the PDB has no member with the same name at the same offset. Round 1 put pad blocks and base members (`GameObject::Id`, `Effect::target`) directly into `GameObject`, `Campfire`, `FieldItem`, `Creature`, `Zone` and `IncreaseSpecialSkillGaugeEffect`.

Round 2 removes these members from the PDB classes. The lifted bodies now read the members through view structs. The PDB does not have these structs, so the check does not compare them:

- `GameObjectIdView` (`gameobject.h`): `GameObject::Id` (+0x28). `Zone::GetFieldItem`, `Zone::GetCampfire` and `checkApply` use it.
- `EffectTargetView` (`effectcontent.h`): `Effect::target` (+0x20).
- `ZoneMemberView` (`zone.h`): `_envList` (+0x3FD0), `fieldItemList` (+0x3FE0), `campfireList` (+0x4008).
- `CreatureMemberView` (`creature.h`): `Id`, `Prop.State.combat_side` (+0x235), and the two changed-property sets (+0xC08, +0xC28).

## Gate and MATCH

The driver runs the build, the gate and the MATCH comparison after this session.

## Not done

- `effect_cpp_2` / `EffectFactory::CreateEffect` (0x5b37f0): the Hex-Rays cache has no pseudocode for this function (the entry is `None`). The body is 0x180 bytes, not empty. The stub stays.
- `creature_h` / `CreatureStateKeeper::~CreatureStateKeeper` (0x1edbf0): the body decrements `Creature::_creatureStateKeeperCount` and then runs the `Pointer2<Creature>` destructor (`RefCntObject::removeReferenceCount`). In the lift headers, `Pointer2` is an empty class, `Creature` has no `RefCntObject` base, and `CreatureStateKeeper` has no members. That work is larger than one leaf. The stub stays.
- `zone_cpp_1` / `Zone::GetNpcSquad` (0x22ec00) and `Zone::GetConvoy` (0x22ec50): the body reads `GeoZone::zoneData` (zone id in the record) and `GeoZone::_npcSquadIndexInfo` / `_convoyIndexInfo`. In the lift headers, `GeoZone` is an opaque byte block. The stubs stay.
- `zone_cpp_1` / `Zone::spawnEnd` (0x231510): the body unlinks `PcSpawnAction::_prev` / `_next` and calls `RefCntObject::removeReferenceCount`. In the lift headers, `PcSpawnAction` has no members and no `RefCntObject` base. The stub stays.
- `zone_cpp_1` / `Zone::SelectFieldItem` (0x2348d0): the public name is a non-static member (`QEAA`), but the binary reads the byte array from RDX and returns a qword from RCX (the `this` register). A static form with a loop bound of 3 gives DIFF 18 (register allocation only); a member form gives DIFF 20. The source form is open. The stub stays.
- `skill` / `SkillContainer::responseDispose` (0x593020): the body calls a variadic send virtual of `Creature` (format `"hic"`, packet 1428). The lift headers do not declare the `Creature` virtual table, so the slot and the name are unknown. The stub stays.

## Changed files

- `src/Server/GameDaemon/GameDaemonFwd.h`
- `src/Server/GameDaemon/campfire.h`
- `src/Server/GameDaemon/creature.h`
- `src/Server/GameDaemon/creature_h.cpp`
- `src/Server/GameDaemon/effect.h`
- `src/Server/GameDaemon/effect_cpp_2.cpp`
- `src/Server/GameDaemon/effectcontent.h`
- `src/Server/GameDaemon/effectcontent_h.cpp`
- `src/Server/GameDaemon/fielditem.h`
- `src/Server/GameDaemon/gameobject.h`
- `src/Server/GameDaemon/itempouch.cpp`
- `src/Server/GameDaemon/itempouch.h`
- `src/Server/GameDaemon/skill.cpp`
- `src/Server/GameDaemon/skill.h`
- `src/Server/GameDaemon/zone.h`
- `src/Server/GameDaemon/zone_cpp_1.cpp`
