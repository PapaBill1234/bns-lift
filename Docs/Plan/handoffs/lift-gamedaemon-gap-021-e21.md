# Handoff: lift-gamedaemon-gap-021-e21 (card lift-gamedaemon-e21)

Exe: GameDaemon (2019 + PDB). Round 1. Two sessions did this round (planned context split).

## Lifted

| RVA | PDB name | Note |
| --- | --- | --- |
| 0x112310 | `GuildBattleFieldManager::OnActivated` | Empty body. |
| 0x35f60 | `BattleRoyalField::GetTypeName` | Returns the literal. |
| 0x633b0 | `ActSeqState::~ActSeqState` | Empty body. The binary folds it with `SpawnState::~SpawnState`. |
| 0x97770 | `DuelBotTrainingRoom::GetTypeName` | Returns the literal. |
| 0x137a30 | `DeleteEvent::EventId` | Returns 7. |
| 0x137a40 | `LeadTheBallManager::Context1` | Returns `_inGameSubStep` (char, +0x30, PartyBattleManager member). |
| 0x1ee470 | `GameTranExpireToken::GetTid` | The skeleton puts `LeadTheBallManager::Context2` at this RVA. The binary folds both bodies (load of +0x38). Context2 returns `_inGameSubStepStartTime` (+0x38). |
| 0x180b90 | `PartyMatchMaker::Name` | Returns the literal. |
| 0x180ed0 | `CaptureTheFlag::Context1` | Getter. |
| 0x180ee0 | `CaptureTheFlag::Context2` | Getter. |
| 0x1edf30 | `TendencyAttractionQuestPack::~TendencyAttractionQuestPack` | Empty body. |
| 0x4307b0 | `LtExpireSO::TimerExpired` | Sets `_enable` to false. |
| 0x666180 | `SerializerTimer::TimerId` | Returns `_serializer->_id`. |
| 0x63700 | `BrainRaidBoss::InitSpecialState` | `memset` of `_specialTargets`, then resets `_specialRotateCount`. |
| 0xaa700 | `DuelBotSpawn::Init` | Two `AllocZero` calls. ❓ The line of the first call is not in the pseudocode (49 is used). |
| 0xaf420 | `DuelBotTrainingRoomScoreContainer::GetRecordEntry` | Keeps the negative index check, the log and the alert. |
| 0xafa40 | `DuelBotTrainingRoomScoreContainer::SetReceiveRewardFlag` | Keeps the reset time check (60000 ms). The owner Id comes from a local GameObject view (+0x28). |
| 0x1bbe50 | `SeasonContentsGuildCombatRecordContainer::GetRecordEntry` | Uses the inline `convertSeasonContentsTypeToEntryIndex`. Only type 8 is known (❓ in the header). |
| 0x664020 | `Serializer::GetNextExpire` | Calls the inline `SerializerTimer::GetNextExpire` (lock, read, unlock). |
| 0x1b2230 | `RankingResult::RankingResult` | The two `std::map` members use their default constructors. Then `InitializeSRWLock`. |

## Not done

None. All 20 bodies are lifted.

## Open items

- Dead-strip: this session added no `/INCLUDE` pragmas. The session could not get the public names with the allowed tools. If funcdiff cannot pair a lifted body, add a pragma with a `// LIFT:` note.
- Layout: `LeadTheBallManager` now has a `LiftBytes<0x30 - 8>` base and two PartyBattleManager members. The full PDB base is not declared yet.

## Gate and MATCH

The driver builds and runs the gate and the MATCH comparison after this session. This session did not build.

## Round 2

- The round 1 gate build failed. The log shows only the wine message "XDG_RUNTIME_DIR is invalid or not set". That message is from the build host, not from the source.
- A source review found one compile error. `SerializerTimer::TimerId` (0x666180) read the private member `Serializer::_id`. The body now calls the public inline accessor `Serializer::Id()`. The generated code is the same load.
- If the build fails again with only the XDG message, examine the build host environment.

## Changed files

- `src/Server/GameDaemon/battleroyalfield_h.cpp`
- `src/Server/GameDaemon/brainraidboss.h`
- `src/Server/GameDaemon/brainraidboss_cpp.cpp`
- `src/Server/GameDaemon/brainstate_h.cpp`
- `src/Server/GameDaemon/capturetheflag.h`
- `src/Server/GameDaemon/capturetheflag_h.cpp`
- `src/Server/GameDaemon/duelbotspawn.cpp`
- `src/Server/GameDaemon/duelbotspawn.h`
- `src/Server/GameDaemon/duelbottrainingroom_h.cpp`
- `src/Server/GameDaemon/duelbottrainingroomscorecontainer.cpp`
- `src/Server/GameDaemon/duelbottrainingroomscorecontainer.h`
- `src/Server/GameDaemon/guildbattlefieldmanager.cpp`
- `src/Server/GameDaemon/leadtheballmanager.h`
- `src/Server/GameDaemon/leadtheballmanager_h.cpp`
- `src/Server/GameDaemon/partymatchmaker_h.cpp`
- `src/Server/GameDaemon/rankingreward.cpp`
- `src/Server/GameDaemon/rankingreward.h`
- `src/Server/GameDaemon/seasonscore.cpp`
- `src/Server/GameDaemon/seasonscore.h`
- `src/Server/GameDaemon/serializedobject.h`
- `src/Server/GameDaemon/serializedobject_h.cpp`
- `src/Server/GameDaemon/serializer.cpp`
- `src/Server/GameDaemon/serializer.h`
- `src/Server/GameDaemon/serializertimer.h`
- `src/Server/GameDaemon/serializertimer_cpp.cpp`
- `src/Server/GameDaemon/tendencymanager_h.cpp`

## Lead repair

| Problem | Repair |
| --- | --- |
| Gate `pdb_layout`: 2 errors. `LeadTheBallManager::_inGameSubStep` (+0x30) and `_inGameSubStepStartTime` (+0x38) are members of the PDB base class `PartyBattleManager`, not of `LeadTheBallManager`. | `leadtheballmanager.h` is back to its base form (no pad, no members). `Context1` and `Context2` read the fields through the view struct `PartyBattleManagerView` in `leadtheballmanager_h.cpp`. The check skips view names. |
| `brainraidboss.h` conflicts with card e20 (same members). | The file is now the same as in e20 (e20 declares all PDB members from +0xC08). |
