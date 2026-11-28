# lift-gamedaemon-gap-127-e127: handoff

Card: keep pragmas for the E21 bodies on main (GameDaemon). This card lifts no new body.

## Done

These bodies from card E21 now have an `/INCLUDE` keep pragma in the `.cpp` file that defines them (16 bodies, 16 pragma lines):

| RVA | Function | File |
| --- | --- | --- |
| 0x112310 | `GuildBattleFieldManager::OnActivated` | `guildbattlefieldmanager.cpp` |
| 0x35f60 | `BattleRoyalField::GetTypeName` | `battleroyalfield_h.cpp` |
| 0x633b0 | `ActSeqState::~ActSeqState` | `brainstate_h.cpp` |
| 0x97770 | `DuelBotTrainingRoom::GetTypeName` | `duelbottrainingroom_h.cpp` |
| 0x137a30 | `DeleteEvent::EventId` | `leadtheballmanager_h.cpp` |
| 0x137a40 | `LeadTheBallManager::Context1` | `leadtheballmanager_h.cpp` |
| 0x1ee470 | `LeadTheBallManager::Context2` (the binary folds it with `GameTranExpireToken::GetTid`) | `leadtheballmanager_h.cpp` |
| 0x180b90 | `PartyMatchMaker::Name` | `partymatchmaker_h.cpp` |
| 0x180ed0 | `CaptureTheFlag::Context1` | `capturetheflag_h.cpp` |
| 0x180ee0 | `CaptureTheFlag::Context2` | `capturetheflag_h.cpp` |
| 0x1edf30 | `TendencyAttractionQuestPack::~TendencyAttractionQuestPack` | `tendencymanager_h.cpp` |
| 0x4307b0 | `LtExpireSO::TimerExpired` | `serializedobject_h.cpp` |
| 0x666180 | `SerializerTimer::TimerId` | `serializertimer_cpp.cpp` |
| 0x63700 | `BrainRaidBoss::InitSpecialState` | `brainraidboss_cpp.cpp` |
| 0xaa700 | `DuelBotSpawn::Init` | `duelbotspawn.cpp` |
| 0x1b2230 | `RankingResult::RankingResult` | `rankingreward.cpp` |

## Not done

These bodies are back to `LIFT_STUB`. They have no pragma.

| RVA | Function | Reason |
| --- | --- | --- |
| 0xafa40 | `DuelBotTrainingRoomScoreContainer::SetReceiveRewardFlag` | Review rejected it. It also calls `Log::Write`: log path (E16). |
| 0xaf420 | `DuelBotTrainingRoomScoreContainer::GetRecordEntry` | log path (E16). The body calls `Log::Write` and `AlertSender::Write`. |
| 0x1bbe50 | `SeasonContentsGuildCombatRecordContainer::GetRecordEntry` | log path (E16). The body calls `Log::Write` and `AlertSender::Write`. |
| 0x664020 | `Serializer::GetNextExpire` | log path (E16). The body calls `Log::Write`. |

## Changed files

All files are in `src/Server/GameDaemon/`:

- `battleroyalfield_h.cpp`
- `brainraidboss_cpp.cpp`
- `brainstate_h.cpp`
- `capturetheflag_h.cpp`
- `duelbotspawn.cpp`
- `duelbottrainingroom_h.cpp`
- `duelbottrainingroomscorecontainer.cpp`
- `guildbattlefieldmanager.cpp`
- `leadtheballmanager_h.cpp`
- `partymatchmaker_h.cpp`
- `rankingreward.cpp`
- `seasonscore.cpp`
- `serializedobject_h.cpp`
- `serializer.cpp`
- `serializertimer_cpp.cpp`
- `tendencymanager_h.cpp`
