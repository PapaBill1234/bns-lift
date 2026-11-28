# lift-gamedaemon-gap-133-e133: handoff

## Layout (Part A)

- `Data::DataManager` now holds all PDB data members in `datamanager.h`, with PDB names, types and offsets.
- The file has `static_assert(sizeof(Data::DataManager) == 0xD6E8)` and one `offsetof` assert for each member.
- `DrLoaderDef` has its PDB layout in `GameDaemonFwd.h`. `_loaderDefs[266]` uses it.
- The driver builds the asserts. No build was run in this session.
- `gamedaemon.h` and `gamedaemon_h.cpp` got the PDB globals that the lifted bodies use (`DEBUG_CHECKER_MODE`, `DEBUG_CHECKER_MODE_DATAVALIDATION_CRASH_COUNT`, `DEBUG_CHECKER_MODE_DATAVALIDATION_FAILURE_COUNT`).
- `DataManager::DataManager` (stub) got an initializer for `_badgeSynthesisResultDataPacket`, because `FragmentPacket` has no default constructor.

## Lifted (11 bodies)

Formtest verdict in brackets. The driver build is the proof.

| RVA | Function | Formtest |
| --- | --- | --- |
| 0x453e60 | `IsRankingPvEStageStartInfo` | SAME |
| 0x62aed0 | `addToArenaDungeonZoneIdList` | FORM |
| 0x62afc0 | `addToArenaDuelZoneIdList` | FORM |
| 0x62c300 | `GetGradeBenefitList` | SAME |
| 0x62c370 | `GetWeaponBrandMaxGemSlotCount` | SAME |
| 0x6327a0 | `GetCombatSeasonContentsTypeCount` | FORM |
| 0x632990 | `GetGameModeFromArenaMatchingRuleDetailType` | SAME |
| 0x662a10 | `WriteDataReaderErrorLog` | SAME |
| 0x662a80 | `WriteScriptLoaderErrorLog` | SAME |
| 0x662ab0 | `WriteDataLoadErrorLog` | SAME |
| 0x662ae0 | `WriteDataValidationFailureLog` | SAME |

Each body has a `/INCLUDE` keep pragma, except where a lifted caller keeps it.

Notes:

- `WriteDataReaderErrorLog` leaves the critical section locked when the log file is null in parallel load. This is a bug of the original. The body keeps it for the match. A `// BUG:` note marks it.
- `GetGameModeFromArenaMatchingRuleDetailType` calls `AlertSender::Write`. It does not lift it.

## Not done (14 functions)

Cause for all of them: the body needs a table iterator or a record type that has no layout in the repo. The iterator calls use vtable slots 20 to 25 of the concrete table class (past the 19 slots of the PDB `DrTable`). The rule forbids a partial view of a record type. Each stays `LIFT_STUB`.

| RVA | Function | Cause |
| --- | --- | --- |
| 0x61fe40 | `onConstructData` | `RuleConfig` has no layout (`_zoneBroadcastSocialActionNpc`, `_tendencyFieldEnable`). Table lookup by raw vtable slot. |
| 0x62c210 | `GetQuotaKeyRecord` | `Data::ContentQuotaRecordPtr` is an empty class. The record `subtype` field has no layout. |
| 0x62a2b0 | `loadArenaDuelZoneFromDuel` | Table iterator. Duel record has no layout (field at +64). |
| 0x62aa50 | `loadItemTransformRecipe` | Table iterator. `ItemTransformRecipeRecordPtr` has no layout. |
| 0x628ec0 | `loadHiddenFieldFromAccountPostCharge` | Table iterator. Record has no layout. |
| 0x6250c0 | `loadHiddenFieldFromFielditem` | Table iterator. Record has no layout. |
| 0x632820 | `IsWarFieldMainZone` | Table iterator. Record has no layout (field at +24). |
| 0x6328e0 | `GetBattleRoyalFieldScoreConversion` | Table lookup by key. `BattleRoyalFieldScoreConversionRecord` has no layout. |
| 0x633010 | `ConstructDuelBotTrainingRoomVersion` | Table iterator. Record has no layout (field at +24). |
| 0x6360f0 | `loadHiddenFieldFromDuelBotGroup` | Not read. Same class of loader: table iterator and record. |
| 0x63cdb0 | `loadHiddenFieldFromMentoring` | Not read. Same class of loader. |
| 0x63f770 | `loadHiddenFieldFromNpc` | Not read. Same class of loader. |
| 0x63f8b0 | `loadHiddenFieldFromChallengeList` | Not read. Same class of loader. |
| 0x662210 | `loadHiddenFieldFromBoastEvent` | Not read. Same class of loader. |

## Gate and MATCH

The driver runs the gate and funcdiff. This session ran only formtest.

## Files changed

- `src/Server/GameDaemon/GameDaemonFwd.h`
- `src/Server/GameDaemon/datamanager.h`
- `src/Server/GameDaemon/datamanager_h.cpp`
- `src/Server/GameDaemon/datamanager_cpp_1.cpp`
- `src/Server/GameDaemon/datamanager_cpp_2.cpp`
- `src/Server/GameDaemon/datamanager_cpp_3.cpp`
- `src/Server/GameDaemon/gamedaemon.h`
- `src/Server/GameDaemon/gamedaemon_h.cpp`
- `Docs/Plan/handoffs/lift-gamedaemon-gap-133-e133.md`
