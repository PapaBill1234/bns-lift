# Handoff: lift-gamedaemon-gap-017-e17 (round 1)

Card: Easy leaves (GameDaemon), bns-lift card `lift-gamedaemon-e17`.
The driver builds, gates and compares MATCH counts. This session did not build.

## Lifted

`effect_h` (an earlier part of this round):

- `0x453a20` `Effect::Initialize2`
- `0x453a60` `Effect::Initialize3`
- `0x453aa0` `Effect::Initialize4`
- `0x453ae0` `Effect::Initialize5`
- `0x453b20` `PassiveEffect::GetDbIndex`
- `0x453b30` `PassiveEffect::GetStackCount`
- `0x453b40` `ControlledCreatureEffectSlot::GetEffectSlotList`
- `0x453b60` `EffectContainer::IsBroadcastSlot`

`inventory_cpp_2` (an earlier part of this round):

- `0x507920` `Inventory::CheckTradeSuggestion`

`gamedaemon_h`:

- `0x27f80` `GameDaemon::IsArenaDaemon`
- `0x27fb0` `GameDaemon::IsArenaDungeonDaemon`
- `0x1107f0` `GameDaemon::IsArenaEnabledGameDaemon`
- `0x180e10` `GameDaemon::SetEventReplyCacheHello`
- `0x1ee590` `TimeBasedPlaySeasonSchedule::Rule::Rule`
- `0x1ee6f0` `GameDaemon::ShortName`
- `0x1ee700` `GameDaemon::Name`
- `0x1ee710` `GameDaemon::GetTimerInterval`

## Decisions

- `GameDaemon` gets a partial PDB layout: `replyCacheHelloEvent` (+0x748), `config` (+0xAA8), `arenaAttraction` (+0x1030). Pads fill the other bytes. Size is 0x15378.
- `GameDaemon::GamedInstance` is a static member. `gamedaemon_h.cpp` defines it until `gamedaemon.cpp` is lifted. Move the definition then.
- `gamedaemon.h` includes the BloodLib `Lock.h` for `SystemEvent`.
- `GamedConfig` gets a partial PDB layout: `_arenaEnabled` (+0xED), `_arenaId` (+0xF8). Size is 0x660.
- `TimeBasedPlaySeasonSchedule::Rule` gets its PDB members `minutes` and `rewardList[4]`. The constructor does the same stores as `Rule::Clear`.
- `gamedaemon_h.cpp` has `/INCLUDE` dead-strip pragmas for the 8 lifted bodies. The mangled names come from the MSVC rules, not from a publics dump. If the link fails on one name, fix that name.
- `effect_h.cpp` and `inventory_cpp_2.cpp` have no dead-strip pragmas. Their mangled names have complex parameters. Add them when a publics dump is available, or when a lifted caller keeps them.

## Not done

| RVA | Function | Reason |
| --- | --- | --- |
| `0x971d0` | `GameDaemon::GetRankingResult` | The body has a `Lock.h` guard on a lock member at +0x1630 (null check, line 122) and no acquire call. The lock type and member name need one more look-up. Keep the stub. |
| `0x34f000` | `Inventory::GetEmptyBagSlotCount` | It reads `Pc::Prop.State.inventory_size`. `pc.h` has no PDB layout for `Pc`. `Inventory::_depotList` (+0x8, `Inventory::Depot[13]`) is also not in `inventory.h` yet. |
| `0x504a60` | `Inventory::setUsed` | It calls 3 `Item` virtual functions. `item.h` has no `Item` vtable in PDB slot order. The pseudocode shows the slots as wrong field names. |
| `0x597520` | `Env::SetSession` | `envobj.h` has no `Env` layout and no `GameObject` base. `Data::ZoneEnv2RecordPtr` is an empty placeholder. |
| `0x597560` | `Env::OnTimer` | Same as above. It also calls `InitState` and `SetEnable` by vtable slot. The `Env` virtual order in `envobj.h` is not the PDB slot order. |
| `0x598260` | `Env::IsQuestEnv` | Needs the `Env` layout and the `Data::ZoneEnv2Record` quest arrays (+376, +576). |
| `0x599240` | `Env::GetPos` | Needs the `Env` layout, the `ZoneEnv2PlaceRecord` fields and the PDB vtable order. |
| `0x599280` | `Env::GetActionPoint` | Needs the `Env` layout and the `ZoneEnv2PlaceRecord` fields. |
| `0x5992b0` | `Env::GetManipulationCylinder` | Same as above. |
| `0x599f20` | `Env::IsMoveBlock` | Needs the `Env` layout and `ZoneEnv2Record::subtype`. |
| `0x59a410` | `Env::CheckToLoot` | Needs the `Env` layout and `Pc` (`GameObject::Id`). |
| `0x59add0` | `Refiner::CheckToGiveFactionScore` | `Refiner` has no `Env` base and no members. It also needs `Pc::Prop.State`. |
| `0x59c190` | `ControlPoint::Manipulate` | `ControlPoint` has no `Env` base. It also needs `Zone::_attractionState`. |
| `0x59c310` | `ControlPoint::CancelOccupation` | Same as above. |
| `0x59c430` | `MultipleLoop::Manipulate` | Same as above. |
| `0x59c9e0` | `Portal::GetPos` | `Portal` has no `Env` base. It also needs the record fields and the PDB vtable order. |
| `0x59ca30` | `Portal::GetActionPoint` | Same as above. |
| `0x59ca70` | `Portal::GetActionRadius` | Same as above. |
| `0x59ca90` | `Portal::GetManipulationCylinder` | Same as above. |
| `0x59fcf0` | `OceanicRegion::ApplyEffect` | The pseudocode cache has no body (`None`). The function is 0x200 bytes, so it is not empty. |
| `0x59fef0` | `OceanicRegion::OnTimer` | It needs `GameObject::Id` and `Zone::GeoZoneData`. `OceanicRegion` has no base. |
| `0x5a0020` | `FallDeathRegion::ApplyEffect` | The pseudocode cache has no body (`None`). The function is 0x1D0 bytes, so it is not empty. |
| `0x5a01f0` | `FallDeathRegion::OnTimer` | Same as `OceanicRegion::OnTimer`. |

Advice: an `envobj` layout card must come first. It must add the `GameObject` base, the `Env` members (PDB offsets 0x30 to 0xB0), the PDB virtual slot order, the `Env` base of the derived classes, and the `Data::ZoneEnv2RecordPtr` / `ZoneEnv2PlaceRecordPtr` record pointers.

## Gate and MATCH

The driver runs the gate and the MATCH comparison after this session. This session has no result to record.

## Changed files

- `src/Server/GameDaemon/GameDaemonFwd.h` (earlier part)
- `src/Server/GameDaemon/effect.h` (earlier part)
- `src/Server/GameDaemon/effect_h.cpp` (earlier part)
- `src/Server/GameDaemon/effectproperty.h` (earlier part)
- `src/Server/GameDaemon/inventory.h` (earlier part)
- `src/Server/GameDaemon/inventory_cpp_2.cpp` (earlier part)
- `src/Server/GameDaemon/item.h` (earlier part)
- `src/Server/GameDaemon/gamedaemon.h`
- `src/Server/GameDaemon/gamedaemon_h.cpp`
- `src/Server/GameDaemon/gamedconfig.h`
- `Docs/Plan/handoffs/lift-gamedaemon-gap-017-e17.md`
