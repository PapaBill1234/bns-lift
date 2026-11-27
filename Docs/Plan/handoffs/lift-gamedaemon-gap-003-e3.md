# Handoff: lift-gamedaemon-gap-003-e3

## Lifted (39 bodies)

All bodies are getters of Property classes. Each one returns a constant or a static data member.

- `DuelBotTrainingRoomScore`: Name, FieldMax, FieldDefine, SyncMax, SyncDefine, TypeId (33).
- `ExtraCreatureProperty`: TypeId (17), Name, FieldMax, FieldDefine, SyncMax, SyncDefine.
- `FishingProperty`: TypeId (37), Name, FieldMax, FieldDefine, SyncMax, SyncDefine.
- `GemProperty`: Name, FieldMax, FieldDefine, SyncMax, SyncDefine.
- `GroceryProperty`: Version (18), Name, FieldMax, FieldDefine, SyncMax, SyncDefine.
- `MentoringProperty`: Name, FieldMax, FieldDefine, SyncMax, SyncDefine.
- `QuestList`: Name, FieldMax, FieldDefine, SyncMax, SyncDefine.

Each class gets four protected static members (`fieldMax`, `fieldDefine`, `syncMax`, `syncDefine`). The form is the same as the pilot in `creatureproperty`. No `/INCLUDE` pragma is used (the source guard forbids it). `/OPT:REF` can remove a lifted function that has no live caller. The driver must handle this in the build.

## Not done

- `0x66ee00` `ItemBase<AccessoryTrait>::GetFieldCount` (stem `mentoringproperty`). It is a member of a class template. Wave 0 made no declaration for it. The body returns 35. A later card must add the `ItemBase<AccessoryTrait>` layout first.

## Files changed

- `src/Server/GameDaemon/duelbottrainingroomscore.cpp`, `.h`
- `src/Server/GameDaemon/extracreatureproperty_h.cpp`, `extracreatureproperty.h`
- `src/Server/GameDaemon/fishingproperty.cpp`, `.h`
- `src/Server/GameDaemon/gemproperty.cpp`, `.h`
- `src/Server/GameDaemon/groceryproperty.cpp`, `.h`
- `src/Server/GameDaemon/mentoringproperty.cpp`, `.h`
- `src/Server/GameDaemon/questlist.cpp`, `.h`
- `Docs/Plan/handoffs/lift-gamedaemon-gap-003-e3.md`

The driver runs the gate and the MATCH comparison. This author session did not run them.
