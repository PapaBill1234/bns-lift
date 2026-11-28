# lift-gamedaemon-gap-036-e36 (card lift-gamedaemon-e36)

## Lifted

Stem `gametran_h` (the first session lifted it, commit 7f11413):

- 0x27e10 `GameTran::~GameTran`
- 0x27e50 `GameTran::run`
- 0x27ef0 `UserTran::~UserTran`
- 0x110670 `SessionTran::~SessionTran`

Stem `gamedaemon_cpp`:

- 0x33afc0 `GamedReloadInvalidRestoreTimer::EventId`
- 0x340e70 `GameDaemon::GetRandomStoreServiceState`
- 0x340ea0 `GameDaemon::GetServerIdForDaemon`
- 0x340ee0 `GameDaemon::GetServerIdForNPChat`
- 0x342ae0 `GamedCooldownTimer::EventId`
- 0x343030 `GameDaemon::ServiceName`
- 0x343650 `GameDaemon::NotCheckToPlayInWeek` (round 2: the body uses the VS2010 `_Lower_bound` loop. The repo `algorithm` header has no `binary_search`.)
- 0x343910 `GameDaemon::GetAddressStringWForLogs`

Stem `mileagedeposittran_cpp`:

- 0x16cf30 `UnsentMileageDepositManager::~UnsentMileageDepositManager` (the PDB members are now in the class)

## Not done

| RVA | Function | Reason |
| --- | --- | --- |
| 0x3041c0 | `HandleCacheGame_LoadMileageDepositRetryListFail` | log path (E16) |
| 0x3042c0 | `HandleCacheGame_LoadRaidDungeonListFail` | log path (E16) |
| 0x304520 | `HandleCacheGame_BindRaidDungeonFail` | log path (E16) |
| 0x3046b0 | `HandleCacheGame_UpdateRaidDungeonFail` | log path (E16) |
| 0x339ee0 | `GenerateTid` | log path (E16) |
| 0x33a210 | `ManageSessionHandler::OnAccept` | log path (E16) |
| 0x33a250 | `ManageSessionHandler::OnConnect` | log path (E16) |
| 0x33aaf0 | `BuilderSessionHandler::OnAccept` | log path (E16) |
| 0x33ab30 | `BuilderSessionHandler::OnConnect` | log path (E16) |
| 0x33aed0 | `NPMessageHandleEvent::~NPMessageHandleEvent` | The skeleton class has no base (PDB: DynamicEventObject). The delete form of `_tran` (virtual destructor call, then `Memory::_Manager[2]->Free`) is not clear. |
| 0xbdb30 | `GameArenaSessionHandler::OnAccept` | log path (E16) |
| 0xbdb70 | `GameArenaSessionHandler::OnConnect` | log path (E16) |
| 0x18c8a0 | `PetitionSessionHandler::OnAccept` | log path (E16) |
| 0x311c10 | `HandleCacheGame_InitializeMentoringFail` | log path (E16) |
| 0x314b00 | `HandleCacheGame_PurePropertyTransactionOk` | log path (E16) |
| 0x315de0 | `CachedChannel::InitChangedCachePacket` | The pseudocode is not clear: it writes a vftable (`AddChangedCachePacketSplitter`) into the first argument, and the `Packet::Compose` arguments do not agree with the format strings. One look-up did not give the form. |
| 0x2e1380 | `HandleCacheGame_HelloFail` | log path (E16) |
| 0x2e14a0 | `HandleCacheGame_InitializeSeasonContentsScheduleFail` | log path (E16) |
| 0x2e15b0 | `HandleCacheGame_InitializeSeasonContentsChallengePartyScheduleFail` | log path (E16) |
| 0x2e1a80 | `HandleCacheGame_LoadGuildCombatRecordFail` | log path (E16) |
| 0x2e1b00 | `HandleCacheGame_RetrieveFactionStatisticsFail` | log path (E16) |
| 0x2e4010 | `HandleCacheGame_DeliverSystemPostOk` | log path (E16) |
| 0x2e4080 | `HandleCacheGame_DeliverSystemPostFail` | log path (E16) |
| 0x156b80 | `ManagementdChannel::PacketHandler` | log path (E16) |
| 0x156be0 | `ManagementdChannel::onCloseAll` | log path (E16) |
| 0x77250 | `HandleChattingGame_A2G_PROTOCOL_VERSIONNotify` | log path (E16) |
| 0x3438f0 | `GameDaemon::WriteDump` | Review reject (P5_zero_arg, round 3). The body is the skeleton `LIFT_STUB` again. Its keep pragma is removed. |

## Notes

- 0x16cf30: the destructor frees `_mileageList` with `Memory::_Manager[2]->Free` only when `_mileageCount` is not 0. The file literal is the per-exe path of MileageDepositTran.cpp, line 453. It has a dead-strip keep pragma.
- Round 3 repair: the card files have no lifted body that calls `Log::Write`, `Log::WriteV`, `AlertSender`, `LogBuffer`, `LogMedia` or `TencentLog`. The card did not lift `AlertSender::writev2`, `Log::Write`, `LogBuffer::Acquire`, `LogBuffer::deallocate_me`, `LogMedia::Add` or `RefCntHistory::dump`. These rejects are not in the card files, so the session did not change them. Stem `gametran_h` needs no repair change. Its accepted bodies stay as they are.
- The session did not run the gate or funcdiff. The driver builds and records the MATCH comparison.

## Changed files

- `src/Server/GameDaemon/gametran.h`
- `src/Server/GameDaemon/gametran_h.cpp`
- `src/Server/GameDaemon/gamedaemon_cpp.cpp`
- `src/Server/GameDaemon/mileagedeposittran.h`
- `src/Server/GameDaemon/mileagedeposittran_cpp.cpp`
- `Docs/Plan/handoffs/lift-gamedaemon-gap-036-e36.md`
