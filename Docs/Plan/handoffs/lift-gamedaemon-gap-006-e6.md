# Handoff: lift-gamedaemon-gap-006-e6 (round 3)

## Lifted

- 30 `Npc::Get*Modify` getters (RVA 0x27380 to 0x27550). Each reads one `short` of the `NpcRecord` through `Npc::_data` (+0xC50). The record offset comes from the PDB field.
- `User::GetId` (0x3502e0). It reads `PcDbId` (+0xD8).
- `ZoneSerializedObject::TimerExpired(long)` (0x25fbf0). It calls the pure virtual `TimerExpired(unsigned int, long)` with timer id 1.

## Repair in this round

- The skeleton classes have no members. The earlier code used undeclared names. The new code reads the members by PDB offset.
- `zoneserializedobject.h` now declares the pure virtual `TimerExpired(unsigned int, long)` (PDB slot 7).

## Not done

- `GameObject::childRoleAllocator` (worldserializedobject_h, 0x1d070): not lifted in the earlier rounds. It stays a stub.
- `SkillTrainingRoom::GetTypeName` (skilltrainingroom_h, 0x180e40): not lifted. It stays a stub.

## Changed files

- `src/Server/GameDaemon/npc_h.cpp`
- `src/Server/GameDaemon/user_h.cpp`
- `src/Server/GameDaemon/zoneserializedobject.h`
- `Docs/Plan/handoffs/lift-gamedaemon-gap-006-e6.md`
