# lift-gamedaemon-gap-028-e28 handoff

## Round 3 repair (review rejects and log path E16)

Round 3 put these bodies back to the skeleton `LIFT_STUB` body and removed their `/INCLUDE` keep pragmas:

- `Zone::GetTickTime` (0x24ae90): review reject P2_cc. It also calls `Log::Write` (E16).
- `NpcSpawn::GetNpc` (0x429730): review reject P2_cc.
- `NpcSpawn::getNpcPos` (0x429780): review reject P2_cc.
- `Pc::SetIpAddress` (0x5f0f00): review reject (load order of `Id`). It also calls `Log::Write` (E16).
- `DifficultyTypeDispelAttributeHpDamageEffect::checkApply` (0x5bf850): review reject P2_cc, P3_imm, P9_ret_width.
- `ModifyRecycleTimeEffect::checkApply` (0x5c6200): review reject P2_cc, P9_ret_width. It also calls `Log::Write` and `AlertSender::Write` (E16).
- `GuildCraftWSO::writeError` (0x67a7e0): it calls `Log::Write` (E16).
- `Inventory::GetItemClass` (0x4c10d0): it calls `Log::Write` (E16).

The card did not lift `PacketBuffer::deallocate_me`, `PacketBuffer::encrypt` or `Session::send`. Round 3 did not change them. The unused `AlertSender.h` include and the `EFFECTCONTENT_FILE` path macro are removed from `effectcontent_cpp_1.cpp`.

## zone_cpp_2

**Not done:**

- `Zone::GetTickTime` (0x24ae90): review reject P2_cc, and it calls `Log::Write` (E16 is open).

## zonetimer_cpp

Lifted: `ZoneSerializer::preExecute` (0x260170). It has a dead-strip keep pragma.

## worldserializedobject_cpp

**Not done:**

- `GuildCraftWSO::writeError` (0x67a7e0): it calls `Log::Write` (E16 is open).

## npcspawn_cpp

**Not done:**

- `NpcSpawn::GetNpc` (0x429730): review reject P2_cc (signed compare in place of unsigned compare).
- `NpcSpawn::getNpcPos` (0x429780): review reject P2_cc (branch sense).

## inventory_cpp_1

Lifted:

- `InventoryCacheUpdate::AddChange` (0x4bea20)
- `Inventory::IsActivatedGemSlot` (0x4bec40)
- `Inventory::Dispose` (0x4cfcc0)

**Not done:**

- `Inventory::GetItemClass` (0x4c10d0): it calls `Log::Write` (E16 is open).
- `Inventory::GetCacheId` (0x4bed10): it calls the virtual `Item::GetClass` (PDB slot 13). The lifted `Item` class in `item.h` does not declare it, and its slot order is not the PDB order yet.
- `InventoryClientUpdate::InventoryClientUpdate` (0x4be600): it needs the `FragmentPacket` and `RepeatPacketComposer` members of `InventoryClientUpdate`. The skeleton does not declare them.
- `InventoryClientUpdate::Send` (0x4be900): same cause.

## pc_cpp_2

Lifted:

- `Pc::IsSharableCombatModeZone` (0x5e6a90)
- `Pc::GetActiveSummoned` (0x5ea0d0)
- `Pc::Send(char const *, char *)` (0x5eb2e0)
- `Pc::Send(char const *, ...)` (0x5eb350)
- `Pc::Send(Packet const *)` (0x5eb3c0)
- `Pc::Send(PacketList const *)` (0x5eb420)
- `Pc::ReturningToArenaLobby` (0x5ed820)
- `Pc::RollbackReturnToArenaLobby` (0x5ed880)
- `Pc::SetGameGameMode` (0x5edae0)
- `Pc::GetGameGameMode` (0x5edb30)
- `Pc::GetArenaAttraction` (0x5ee6b0)

**Not done:**

- `Pc::SetIpAddress` (0x5f0f00): review reject (the build loads `Id` after the `Network::GetAddressStringW` calls), and it calls `Log::Write` (E16 is open).

The bodies read `Pc` through a local view with PDB offsets. `Pc::_user` is read as `Channel const *` (the PDB base of `User` at +0), and `Channel::GetSession` is the virtual call. `Pc::Send(PacketList const *)` calls the private `Session::send`, so `Session.h` (BloodLib) has a new `friend class Pc;` line. Each lifted body has a dead-strip keep pragma.

Open items for the reviewer:

- The `PacketList::Buffers` element type is not checked in the PDB. The view uses `PacketBuffer const **`, as in the call of the original.
- `Pc::_arenaLock` is a `CriticalSection`. The view uses `CRITICAL_SECTION` at the same offset (the PDB member `CS` is at +0).

## effectcontent_cpp_1

Lifted:

- `HpDamageEffect::checkApply` (0x5b8250)
- `InitializeRecycleGroupEffect::checkApply` (0x5bca00)
- `AdditionalHpEffect::checkApply` (0x5bf3e0)
- `DesireIncreaseEffect::checkApply` (0x5bf4d0)
- `ReturnSimSkillEffect::checkApply` (0x5c5de0)
- `SetImmuneBreakerEffect::checkApply` (0x5c65d0)

The effect classes of the skeleton have no `Effect` base. The bodies read `target` and `casterId` through a local view of `Effect`. Each lifted body has a dead-strip keep pragma.

**Not done:**

- `DifficultyTypeDispelAttributeHpDamageEffect::checkApply` (0x5bf850): review reject P2_cc, P3_imm, P9_ret_width.
- `ModifyRecycleTimeEffect::checkApply` (0x5c6200): review reject P2_cc, P9_ret_width, and it calls `Log::Write` and `AlertSender::Write` (E16 is open).
- `AttackPassiveEffect::checkApply` (0x5b76f0): it reads a 64-bit flag field at Creature+0x1D0. The PDB name of that field is not known. No class in the PDB type header has a Creature member at 0x1D0 (the field is in a nested member).
- `ExtendLinkEffect::checkApply` (0x5be900): same field at Creature+0x1D0.
- `ProvocationEffect::checkApply` (0x5c4bb0): same field at Creature+0x1D0.
- `GuardGaugeHealEffect::checkApply` (0x5b8590): it reads fields of a derived effect record after `Data::EffectRecord`. The record type is not known.
- `GuardGaugeDamageEffect::checkApply` (0x5b86f0): same cause.
- `CastCancelEffect::apply` (0x5b8ab0): it calls a virtual function through a member at Creature+0x8A0. The member and the slot are not known.
- `ReturnSimSkillEffect::apply` (0x5c5e00): same member at Creature+0x8A0, and a derived effect record.
- `TransitEffect::TransitEffect` (0x5c5530): the skeleton has no `InstantEffect` base and no `TransitEffect` members.

## Gate and MATCH

The driver runs the gate, the builds and the MATCH comparison after the session. This session did not run them.

## Changed files

- `src/Server/GameDaemon/effectcontent_cpp_1.cpp`
- `src/Server/GameDaemon/inventory.h`
- `src/Server/GameDaemon/inventory_cpp_1.cpp`
- `src/Server/GameDaemon/worldserializedobject_cpp.cpp`
- `src/Server/GameDaemon/zone_cpp_2.cpp`
- `src/Server/GameDaemon/zonetimer_cpp.cpp`
- `src/Server/GameDaemon/npcspawn_cpp.cpp`
- `src/Server/GameDaemon/pc_cpp_2.cpp`
- `src/Server/BloodLib/include/Session.h`
- `Docs/Plan/handoffs/lift-gamedaemon-gap-028-e28.md`
