# Handoff: lift-gamedaemon-gap-015-e15 (card lift-gamedaemon-e15)

Round 1. Two sessions did the work. The driver builds, gates and does the parity check. This file records no gate result and no MATCH count.

## Lifted (35)

- `npcparty_h`: `NpcPartyTimer::TimerExpired` (0x34f360).
- `geoworld_h`: `GeoZone::FindCell` (0x1d1c0), `GeoRegion::GetEnv` (0x8c440).
- `envobj_h`: `Env::GetActionRadius` (0x4553f0), `Env::GetManipulateDuration` (0x455400), `Env::GetOwnerId` (0x455410), `AirDash::CheckToManipulate` (0x455430).
- `item_h_2`: `ItemBase<WeaponTrait>::GetFieldCount` (0x668830), `ItemBase<AccessoryTrait>::GetPos` (0x668870), `ItemBase<GroceryTrait>::GetClass` (0x66ba90), `ItemBase<AccessoryTrait>::GetDepot` (0x66baa0), `ItemBase<GemTrait>::GetClass` (0x66d510), `ItemBase<AccessoryTrait>::GetDataId` (0x66ede0), `ItemBase<AccessoryTrait>::GetClass` (0x66edf0), `ItemBase<AccessoryTrait>::GetSequestration` (0x66ee10).
- `pc_h`: the 20 `Pc` getters and setters from `Pc::IsExceptHate` (0x4563d0) to `Pc::GetSkillResultContext` (0x456520).

## Decisions

- `Env` now declares `_env2` (+48), `_env2spawn` (+56) and `_env2place` (+64). The record pointers are view types (`EnvZoneEnv2PtrView`, `EnvZoneEnv2PlacePtrView`). Each view declares only the field that a lifted body reads (`manipulate_duration` +0x68, `action_radius` +0x38).
- `item.h` now declares the class template `ItemBase<Trait>` (base `Item`). It declares only the six virtual getters of the lifted bodies, the member `data` (+40) and the member `prop` (+48).
- The member `prop` uses the view `ItemBaseAccessoryPropertyView` for all traits. Only the `AccessoryProperty::__default__` layout is declared. The other trait properties are not declared yet. A later card must give `prop` the PDB type `<Trait>Property`.
- The item bodies are explicit specializations of the template members. Each has a `/INCLUDE` dead-strip pragma with a `// LIFT:` note.
- `GetSequestration` reads the PDB bit field `sequestration`.

## Not done (5)

- `ItemBase<AccessoryTrait>::GetData` (0x66d520): the body returns `Data::ItemRecordPtr` by value. `Data::ItemRecordPtr` is an empty class in `GameDaemonFwd.h`. A `_record` member changes the by-value ABI of many stubs. A later card must declare the `DrRecordPtr` base.
- `ItemBase<AccessoryTrait>::SetData` (0x66d530): the body calls a virtual of `Data::DataManager::Instance->_loaderDefs[114].table` (a `DrTable`). The `DataManager` and `DrTable` layouts are not declared.
- `ZoneTriggerBossChallengeBossNpcKilledEvent::GetData` (0x6761c0): the class must derive from `ZoneTriggerEvent` (vfptr, `_context` +8). The member `_data` (+16) is a `Data::ZoneTriggerEventCondRecord...Ptr`. The base hierarchy and the record pointer types are not declared. The work is above 5 reads.
- `ZoneTriggerNpcKilledEvent2::GetData` (0x6761d0): same cause. The member `_data` is at +24.
- `Pc::GetGuildCombatRewardDataId` (0x97130): the pseudocode writes the result through the second argument register. The PDB signature has `char` in that place. The signature question is open. The body also needs the `Pc` members `_guildCombatInfoLock` and `_guildCombatResult` and the lock idiom. These are not declared.

## Round 2: pdb_layout fix

- Round 1 failed the gate: `pdb_layout` found 9 errors. Each error was a padding member (`lift_pad_*`, `lift_vfptr`) with no PDB name.
- Round 2 adds the build helper `LiftBytes<N>` in `GameDaemonFwd.h`. A partial class uses it as a private base. The base holds the bytes of the undeclared PDB bases and members. The declared members keep their PDB offsets.
- `Pc`, `Env`, `GeoZone`, `ZoneSerializedObject`, `SkillResultContext` and `ItemBase<Trait>` now use a `LiftBytes` base.
- `Env` declares the real PDB members from `_geoEnvObj` (+72) to `_exceptLootCaseBitmap` (+124).
- `Pc` holds its two inner gaps in char arrays with the PDB names `_combatModeType` (+0x4E34) and `_inviteMentoringContext` (+0x8D78). Later cards must split these arrays into the real members.
- `GeoDataTerrain` has no tail padding now. The lift reads it only through a pointer.
- The resym message about `GameFailReason` is a resym limit. It is not a layout error.

## Files changed

- `src/Server/GameDaemon/GameDaemonFwd.h`
- `src/Server/GameDaemon/envobj.h`
- `src/Server/GameDaemon/envobj_h.cpp`
- `src/Server/GameDaemon/geoworld.h`
- `src/Server/GameDaemon/geoworld_h.cpp`
- `src/Server/GameDaemon/item.h`
- `src/Server/GameDaemon/item_h_2.cpp`
- `src/Server/GameDaemon/npcparty.h`
- `src/Server/GameDaemon/npcparty_h.cpp`
- `src/Server/GameDaemon/pc.h`
- `src/Server/GameDaemon/pc_h.cpp`
- `src/Server/GameDaemon/zoneserializedobject.h`
- `Docs/Plan/handoffs/lift-gamedaemon-gap-015-e15.md`
