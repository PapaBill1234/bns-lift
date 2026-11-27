# Handoff: lift-gamedaemon-gap-006-e6

## Lifted (34 bodies)

- `GameObject::childRoleAllocator` (0x1d070): returns `Memory::_Manager[2]`.
- `Npc::Get*Modify` (30 getters, 0x27380 to 0x27550): each returns one `short` field of `_data->` (`Data::NpcRecord`). The Hex-Rays index `_record[N]` with `DrEl` size 6 gives the field offset (for example 361*6+2 = 0x878 = `attack_hit_value_modify`).
- `SkillTrainingRoom::GetTypeName` (0x180e40): returns `L"SkillTraningRoom"` (the original spelling).
- `ZoneSerializedObject::TimerExpired(long)` (0x25fbf0): calls `TimerExpired(1u, elapsed)`.
- `User::GetId` (0x3502e0): returns `PcDbId`.

## Not done

None.

## Notes for the driver

- I could not run a build, a publics dump or a type query for the last steps. The tools were denied late in the session.
- The `/INCLUDE:` names for the virtual getters are hand-built from the x64 name scheme (public virtual: `UEAA`). Check them at link time. If one is wrong, fix the name from the PDB publics.
- `GameObject::childRoleAllocator` has no `/INCLUDE` pragma. I could not confirm its access level (private virtual would be `EEAAPEAVMemoryManager@@XZ`). It may be dead-stripped.
- `worldserializedobject_h.cpp` includes `Memory.h` and `MemoryManager.h` from BloodLib. Check that the include does not clash with the `Memory` class of the PDB `types.h`.

## Changed files

- `src/Server/GameDaemon/npc_h.cpp`
- `src/Server/GameDaemon/user_h.cpp`
- `src/Server/GameDaemon/skilltrainingroom_h.cpp`
- `src/Server/GameDaemon/zoneserializedobject.cpp`
- `src/Server/GameDaemon/worldserializedobject_h.cpp`
- `Docs/Plan/handoffs/lift-gamedaemon-gap-006-e6.md`
