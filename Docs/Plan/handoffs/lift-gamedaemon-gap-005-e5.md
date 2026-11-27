# lift-gamedaemon-gap-005-e5 handoff

## Lifted

- `GetDataReaderInterfaceVersion` (0x6eb2a0), `Logger` (0x6eb320). The static `DrDataReaderImpl::_logger` is new.
- `QuestTableImpl::GetMaxQuestId`, `GetQuestByIndex`, `GetMaxQuestNum`. The class now has 4 PDB members.
- `DrDataTableImpl::UseLegacyElHeader`, `ReferenceCopiedEl`, constructor. The class now has 3 PDB members.
- `ChallengeListProperty`: TypeId (38), FieldMax, FieldDefine, SyncMax, SyncDefine.
- `SlateProperty`: TypeId (39), FieldMax, FieldDefine, SyncMax, SyncDefine.
- `AccessoryProperty`: TypeId (15), Version (20), Name, FieldMax, FieldDefine, SyncMax, SyncDefine.
  RVA 0x191e0 also keeps `GameDaemon::GetTimerMaxTime` (same code, return 20).
- `AcquiredSkill1`: TypeId (21), Name, FieldMax, FieldDefine, SyncMax, SyncDefine.
- Each lifted function has a `/INCLUDE` pragma with a `// LIFT:` note (no live caller yet).
- The `creatureproperty` files have no function in this card. They are unchanged.

## Not done

| RVA | Function | Reason |
| --- | --- | --- |
| 0x96d0 | `ChallengeListProperty::Name` | The pseudocode returns an address inside `zone._publicProp`. The string is not in the cache. |
| 0x9760 | `SlateProperty::Name` | Same reason (`zone._publicProp[3108]`). |
| 0x6f7430 | `DrDataTableImpl::~DrDataTableImpl` | The body sets the vftable of the base `DrTable`. The class has no base layout yet. |

## Count

Lifted: 37. Not done: 3.

## Files changed

`datareader.cpp`, `datareaderimpl.h`, `questtableimpl_h.cpp`, `questtableimpl.h`, `tableimpl_h.cpp`, `tableimpl.h`,
`tableimpl_cpp.cpp`, `challengelistproperty.cpp/.h`, `slateproperty.cpp/.h`, `accessoryproperty.cpp/.h`,
`acquiredskill1.cpp/.h` (all in `src/Server/GameDaemon/`), and this file.

Gate and MATCH counts: the driver records them.
