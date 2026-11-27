# Handoff: lift-gamedaemon-gap-004-e4

## Lifted (38 functions)

- QuestProperty: Name, FieldMax, FieldDefine, SyncMax, SyncDefine.
- RaidDungeonBindProperty: Name, FieldMax, FieldDefine, SyncMax, SyncDefine.
- RaidDungeonUnbindProperty: TypeId (30), Name, FieldMax, FieldDefine, SyncMax, SyncDefine.
- RandomStore: TypeId (28), Name, FieldMax, FieldDefine, SyncMax, SyncDefine.
- RecycleTimeProperty: Name, FieldMax, FieldDefine, SyncMax, SyncDefine.
- SeasonContentsCombatRecord: TypeId (32), Name, FieldMax, FieldDefine, SyncMax, SyncDefine.
- SeasonContentsTimeAttackRecord: Name, FieldMax, FieldDefine, SyncMax, SyncDefine.

Form follows the pilot of card lift-gamedaemon-0d. Each class has four protected static data members
(`fieldMax`, `fieldDefine`, `syncMax`, `syncDefine`). Each getter returns its member. Each lifted function has a
`/INCLUDE` keep pragma with a `// LIFT:` note, because no live caller exists yet.

## Not done

None. The destructors of QuestProperty, RandomStore and RecycleTimeProperty are not in scope. They stay `LIFT_STUB`.

## Open

- The static members use plain pointer types, as in the pilot. The PDB mangles them as const. Not checked by a build.
- The driver did the build and the proof. No gate or MATCH result is recorded here.

## Files changed

- `src/Server/GameDaemon/{questproperty,raiddungeonbindproperty,raiddungeonunbindproperty,randomstore,recycletimeproperty,seasoncontentscombatrecord,seasoncontentstimeattackrecord}.{cpp,h}`
- `Docs/Plan/handoffs/lift-gamedaemon-gap-004-e4.md`
