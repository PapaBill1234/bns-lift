# lift-gamedaemon-e21: Easy leaves (GameDaemon): guildbattlefieldmanager, battleroyalfield_h, brainstate_h, duelbottrainingroom_h, ...

| Item | Value |
| --- | --- |
| Exe | GD |
| Source build | GameDaemon 2019 + PDB (VS2010 SP1) |
| Exe file | `<work-root>/ida/lift/GameDaemon/GameDaemon.exe` |
| PDB | `<work-root>/ida/lift/GameDaemon/GameDaemon.pdb` |
| Pseudocode | `~/.cache/bns-lift/hr/GameDaemon/<stem>.c` |
| Pseudocode index | `~/.cache/bns-lift/hr/GameDaemon/index.tsv` (stem, rva, name, first, last, status, source file, part) |
| Wave | E |
| Model | opus |
| Depends on | `lift-gamedaemon-0e` |
| Pattern | none |
| Plan | `Docs/Plan/gamedaemon-lift.md` sections 1, 3, 5 |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Grep `Docs/Parity/lessons.md` for A2 (block order), A6 (per-exe path literals), A12 (PDB member types), A18 (destructors), A21 (PDB facts) and A22 (per-exe source form). Do not read it in full.
- Pattern: none. No lifted file has the same role.

## Scope

20 functions, about 270 pseudocode lines (about 2,160 tokens). Stems: `guildbattlefieldmanager`, `battleroyalfield_h`, `brainstate_h`, `duelbottrainingroom_h`, `leadtheballmanager_h`, `partymatchmaker_h`, `capturetheflag_h`, `tendencymanager_h`, `serializedobject_h`, `serializertimer_cpp`, `brainraidboss_cpp`, `duelbotspawn`, `duelbottrainingroomscorecontainer`, `seasonscore`, `serializer`, `rankingreward`.

Wave E (owner order 2026-11-27: the easiest work first). Each function in this card is a leaf: its body calls no other counted function that needs a lift. Thus a `LIFT_STUB` callee cannot keep it DIFF. Each function has at most 30 pseudocode lines. Ease key: 13.5 cost per function (rule in `Docs/Plan/gamedaemon-lift.md` section 3).

Lift only the functions in the table. The other functions of these stems are in later W cards. Those cards depend on this card.

| n | Exe | RVA | PDB name | Stem | Lines | Form |
| ---: | --- | --- | --- | --- | ---: | --- |
| 1 | GD | `0x112310` | `GuildBattleFieldManager::OnActivated` | guildbattlefieldmanager | 3 | empty |
| 2 | GD | `0x35f60` | `BattleRoyalField::GetTypeName` | battleroyalfield_h | 7 | getter |
| 3 | GD | `0x633b0` | `ActSeqState::~ActSeqState` | brainstate_h | 7 | xtor |
| 4 | GD | `0x97770` | `DuelBotTrainingRoom::GetTypeName` | duelbottrainingroom_h | 7 | getter |
| 5 | GD | `0x137a30` | `DeleteEvent::EventId` | leadtheballmanager_h | 7 | getter |
| 6 | GD | `0x137a40` | `LeadTheBallManager::Context1` | leadtheballmanager_h | 7 | getter |
| 7 | GD | `0x1ee470` | `GameTranExpireToken::GetTid` | leadtheballmanager_h | 7 | getter |
| 8 | GD | `0x180b90` | `PartyMatchMaker::Name` | partymatchmaker_h | 7 | getter |
| 9 | GD | `0x180ed0` | `CaptureTheFlag::Context1` | capturetheflag_h | 7 | getter |
| 10 | GD | `0x180ee0` | `CaptureTheFlag::Context2` | capturetheflag_h | 7 | getter |
| 11 | GD | `0x1edf30` | `TendencyAttractionQuestPack::~TendencyAttractionQuestPack` | tendencymanager_h | 7 | xtor |
| 12 | GD | `0x4307b0` | `LtExpireSO::TimerExpired` | serializedobject_h | 7 | setter |
| 13 | GD | `0x666180` | `SerializerTimer::TimerId` | serializertimer_cpp | 7 | getter |
| 14 | GD | `0x63700` | `BrainRaidBoss::InitSpecialState` | brainraidboss_cpp | 8 | leaf |
| 15 | GD | `0xaa700` | `DuelBotSpawn::Init` | duelbotspawn | 29 | leaf |
| 16 | GD | `0xaf420` | `DuelBotTrainingRoomScoreContainer::GetRecordEntry` | duelbottrainingroomscorecontainer | 29 | leaf |
| 17 | GD | `0xafa40` | `DuelBotTrainingRoomScoreContainer::SetReceiveRewardFlag` | duelbottrainingroomscorecontainer | 29 | leaf |
| 18 | GD | `0x1bbe50` | `SeasonContentsGuildCombatRecordContainer::GetRecordEntry` | seasonscore | 29 | leaf |
| 19 | GD | `0x664020` | `Serializer::GetNextExpire` | serializer | 29 | leaf |
| 20 | GD | `0x1b2230` | `RankingResult::RankingResult` | rankingreward | 30 | leaf |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/guildbattlefieldmanager.cpp`
- `src/Server/GameDaemon/guildbattlefieldmanager.h`
- `src/Server/GameDaemon/battleroyalfield_h.cpp`
- `src/Server/GameDaemon/battleroyalfield_h.h`
- `src/Server/GameDaemon/brainstate_h.cpp`
- `src/Server/GameDaemon/brainstate_h.h`
- `src/Server/GameDaemon/duelbottrainingroom_h.cpp`
- `src/Server/GameDaemon/duelbottrainingroom_h.h`
- `src/Server/GameDaemon/leadtheballmanager_h.cpp`
- `src/Server/GameDaemon/leadtheballmanager_h.h`
- `src/Server/GameDaemon/partymatchmaker_h.cpp`
- `src/Server/GameDaemon/partymatchmaker_h.h`
- `src/Server/GameDaemon/capturetheflag_h.cpp`
- `src/Server/GameDaemon/capturetheflag_h.h`
- `src/Server/GameDaemon/tendencymanager_h.cpp`
- `src/Server/GameDaemon/tendencymanager_h.h`
- `src/Server/GameDaemon/serializedobject_h.cpp`
- `src/Server/GameDaemon/serializedobject_h.h`
- `src/Server/GameDaemon/serializertimer_cpp.cpp`
- `src/Server/GameDaemon/serializertimer_cpp.h`
- `src/Server/GameDaemon/brainraidboss_cpp.cpp`
- `src/Server/GameDaemon/brainraidboss_cpp.h`
- `src/Server/GameDaemon/duelbotspawn.cpp`
- `src/Server/GameDaemon/duelbotspawn.h`
- `src/Server/GameDaemon/duelbottrainingroomscorecontainer.cpp`
- `src/Server/GameDaemon/duelbottrainingroomscorecontainer.h`
- `src/Server/GameDaemon/seasonscore.cpp`
- `src/Server/GameDaemon/seasonscore.h`
- `src/Server/GameDaemon/serializer.cpp`
- `src/Server/GameDaemon/serializer.h`
- `src/Server/GameDaemon/rankingreward.cpp`
- `src/Server/GameDaemon/rankingreward.h`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-e21.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
