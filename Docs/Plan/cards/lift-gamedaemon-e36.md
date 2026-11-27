# lift-gamedaemon-e36: Easy leaves (GameDaemon): gametran_h, cachedaemonchannel_2, gamedaemon_cpp, gamearenachannel_cpp_1, ...

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
| Pattern | `src/Server/LobbyDaemon/ManageChannel.cpp` |
| Plan | `Docs/Plan/gamedaemon-lift.md` sections 1, 3, 5 |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Grep `Docs/Parity/lessons.md` for A2 (block order), A6 (per-exe path literals), A12 (PDB member types), A18 (destructors), A21 (PDB facts) and A22 (per-exe source form). Do not read it in full.
- Pattern: `src/Server/LobbyDaemon/ManageChannel.cpp`. Read it one time. Use its form for the functions of this card.

## Scope

40 functions, about 647 pseudocode lines (about 5,176 tokens). Stems: `gametran_h`, `cachedaemonchannel_2`, `gamedaemon_cpp`, `gamearenachannel_cpp_1`, `petitiondaemonchannel`, `cachedaemonchannel_3`, `cachedaemonchannel_1`, `mileagedeposittran_cpp`, `managementdchannel`, `chattingserverchannel`.

Wave E (owner order 2026-11-27: the easiest work first). Each function in this card is a leaf: its body calls no other counted function that needs a lift. Thus a `LIFT_STUB` callee cannot keep it DIFF. Each function has at most 30 pseudocode lines. Ease key: 16.2 cost per function (rule in `Docs/Plan/gamedaemon-lift.md` section 3).

Lift only the functions in the table. The other functions of these stems are in later W cards. Those cards depend on this card.

| n | Exe | RVA | PDB name | Stem | Lines | Form |
| ---: | --- | --- | --- | --- | ---: | --- |
| 1 | GD | `0x27e10` | `GameTran::~GameTran` | gametran_h | 13 | xtor |
| 2 | GD | `0x27e50` | `GameTran::run` | gametran_h | 7 | leaf |
| 3 | GD | `0x27ef0` | `UserTran::~UserTran` | gametran_h | 20 | leaf |
| 4 | GD | `0x110670` | `SessionTran::~SessionTran` | gametran_h | 20 | leaf |
| 5 | GD | `0x3041c0` | `HandleCacheGame_LoadMileageDepositRetryListFail` | cachedaemonchannel_2 | 12 | leaf |
| 6 | GD | `0x3042c0` | `HandleCacheGame_LoadRaidDungeonListFail` | cachedaemonchannel_2 | 16 | leaf |
| 7 | GD | `0x304520` | `HandleCacheGame_BindRaidDungeonFail` | cachedaemonchannel_2 | 16 | leaf |
| 8 | GD | `0x3046b0` | `HandleCacheGame_UpdateRaidDungeonFail` | cachedaemonchannel_2 | 16 | leaf |
| 9 | GD | `0x339ee0` | `GenerateTid` | gamedaemon_cpp | 21 | leaf |
| 10 | GD | `0x33a210` | `ManageSessionHandler::OnAccept` | gamedaemon_cpp | 13 | leaf |
| 11 | GD | `0x33a250` | `ManageSessionHandler::OnConnect` | gamedaemon_cpp | 19 | leaf |
| 12 | GD | `0x33aaf0` | `BuilderSessionHandler::OnAccept` | gamedaemon_cpp | 13 | leaf |
| 13 | GD | `0x33ab30` | `BuilderSessionHandler::OnConnect` | gamedaemon_cpp | 19 | leaf |
| 14 | GD | `0x33aed0` | `NPMessageHandleEvent::~NPMessageHandleEvent` | gamedaemon_cpp | 30 | leaf |
| 15 | GD | `0x33afc0` | `GamedReloadInvalidRestoreTimer::EventId` | gamedaemon_cpp | 7 | getter |
| 16 | GD | `0x340e70` | `GameDaemon::GetRandomStoreServiceState` | gamedaemon_cpp | 13 | leaf |
| 17 | GD | `0x340ea0` | `GameDaemon::GetServerIdForDaemon` | gamedaemon_cpp | 14 | leaf |
| 18 | GD | `0x340ee0` | `GameDaemon::GetServerIdForNPChat` | gamedaemon_cpp | 14 | leaf |
| 19 | GD | `0x342ae0` | `GamedCooldownTimer::EventId` | gamedaemon_cpp | 7 | getter |
| 20 | GD | `0x343030` | `GameDaemon::ServiceName` | gamedaemon_cpp | 7 | getter |
| 21 | GD | `0x343650` | `GameDaemon::NotCheckToPlayInWeek` | gamedaemon_cpp | 30 | leaf |
| 22 | GD | `0x3438f0` | `GameDaemon::WriteDump` | gamedaemon_cpp | 7 | leaf |
| 23 | GD | `0x343910` | `GameDaemon::GetAddressStringWForLogs` | gamedaemon_cpp | 15 | leaf |
| 24 | GD | `0xbdb30` | `GameArenaSessionHandler::OnAccept` | gamearenachannel_cpp_1 | 13 | leaf |
| 25 | GD | `0xbdb70` | `GameArenaSessionHandler::OnConnect` | gamearenachannel_cpp_1 | 19 | leaf |
| 26 | GD | `0x18c8a0` | `PetitionSessionHandler::OnAccept` | petitiondaemonchannel | 16 | leaf |
| 27 | GD | `0x311c10` | `HandleCacheGame_InitializeMentoringFail` | cachedaemonchannel_3 | 17 | leaf |
| 28 | GD | `0x314b00` | `HandleCacheGame_PurePropertyTransactionOk` | cachedaemonchannel_3 | 21 | leaf |
| 29 | GD | `0x315de0` | `CachedChannel::InitChangedCachePacket` | cachedaemonchannel_3 | 14 | leaf |
| 30 | GD | `0x2e1380` | `HandleCacheGame_HelloFail` | cachedaemonchannel_1 | 12 | leaf |
| 31 | GD | `0x2e14a0` | `HandleCacheGame_InitializeSeasonContentsScheduleFail` | cachedaemonchannel_1 | 12 | leaf |
| 32 | GD | `0x2e15b0` | `HandleCacheGame_InitializeSeasonContentsChallengePartyScheduleFail` | cachedaemonchannel_1 | 16 | leaf |
| 33 | GD | `0x2e1a80` | `HandleCacheGame_LoadGuildCombatRecordFail` | cachedaemonchannel_1 | 25 | leaf |
| 34 | GD | `0x2e1b00` | `HandleCacheGame_RetrieveFactionStatisticsFail` | cachedaemonchannel_1 | 19 | leaf |
| 35 | GD | `0x2e4010` | `HandleCacheGame_DeliverSystemPostOk` | cachedaemonchannel_1 | 19 | leaf |
| 36 | GD | `0x2e4080` | `HandleCacheGame_DeliverSystemPostFail` | cachedaemonchannel_1 | 21 | leaf |
| 37 | GD | `0x16cf30` | `UnsentMileageDepositManager::~UnsentMileageDepositManager` | mileagedeposittran_cpp | 18 | leaf |
| 38 | GD | `0x156b80` | `ManagementdChannel::PacketHandler` | managementdchannel | 25 | leaf |
| 39 | GD | `0x156be0` | `ManagementdChannel::onCloseAll` | managementdchannel | 12 | leaf |
| 40 | GD | `0x77250` | `HandleChattingGame_A2G_PROTOCOL_VERSIONNotify` | chattingserverchannel | 19 | leaf |

Same name in a lifted exe (a different body is possible): `ManageSessionHandler::OnAccept` (src/Server/LobbyDaemon/ManageChannel.cpp), `ManageSessionHandler::OnConnect` (src/Server/LobbyDaemon/ManageChannel.cpp).

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/gametran_h.cpp`
- `src/Server/GameDaemon/gametran_h.h`
- `src/Server/GameDaemon/cachedaemonchannel_2.cpp`
- `src/Server/GameDaemon/cachedaemonchannel_2.h`
- `src/Server/GameDaemon/gamedaemon_cpp.cpp`
- `src/Server/GameDaemon/gamedaemon_cpp.h`
- `src/Server/GameDaemon/gamearenachannel_cpp_1.cpp`
- `src/Server/GameDaemon/gamearenachannel_cpp_1.h`
- `src/Server/GameDaemon/petitiondaemonchannel.cpp`
- `src/Server/GameDaemon/petitiondaemonchannel.h`
- `src/Server/GameDaemon/cachedaemonchannel_3.cpp`
- `src/Server/GameDaemon/cachedaemonchannel_3.h`
- `src/Server/GameDaemon/cachedaemonchannel_1.cpp`
- `src/Server/GameDaemon/cachedaemonchannel_1.h`
- `src/Server/GameDaemon/mileagedeposittran_cpp.cpp`
- `src/Server/GameDaemon/mileagedeposittran_cpp.h`
- `src/Server/GameDaemon/managementdchannel.cpp`
- `src/Server/GameDaemon/managementdchannel.h`
- `src/Server/GameDaemon/chattingserverchannel.cpp`
- `src/Server/GameDaemon/chattingserverchannel.h`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-e36.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
