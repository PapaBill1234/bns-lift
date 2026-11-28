# lift-gamedaemon-gap-036-e36 (card lift-gamedaemon-e36)

## Lifted

Stem `petitiondaemonchannel`:

- 0x18c8a0 `PetitionSessionHandler::OnAccept`

Stem `mileagedeposittran_cpp`:

- 0x16cf30 `UnsentMileageDepositManager::~UnsentMileageDepositManager` (the PDB members are now in the class)

Stem `chattingserverchannel`:

- 0x77250 `HandleChattingGame_A2G_PROTOCOL_VERSIONNotify` (round 4)

Stem `gamearenachannel_cpp_1`:

- 0xbdb30 `GameArenaSessionHandler::OnAccept`
- 0xbdb70 `GameArenaSessionHandler::OnConnect`

Stem `managementdchannel`:

- 0x156be0 `ManagementdChannel::onCloseAll` (round 4)

Stem `cachedaemonchannel_3`:

- 0x311c10 `HandleCacheGame_InitializeMentoringFail`
- 0x314b00 `HandleCacheGame_PurePropertyTransactionOk`

Stem `gametran_h`:

- 0x27e10 `GameTran::~GameTran`
- 0x27e50 `GameTran::run`
- 0x27ef0 `UserTran::~UserTran`
- 0x110670 `SessionTran::~SessionTran`

Stem `cachedaemonchannel_2`:

- 0x3041c0 `HandleCacheGame_LoadMileageDepositRetryListFail`
- 0x3042c0 `HandleCacheGame_LoadRaidDungeonListFail`
- 0x304520 `HandleCacheGame_BindRaidDungeonFail`
- 0x3046b0 `HandleCacheGame_UpdateRaidDungeonFail`

Stem `cachedaemonchannel_1`:

- 0x2e1380 `HandleCacheGame_HelloFail`
- 0x2e14a0 `HandleCacheGame_InitializeSeasonContentsScheduleFail`
- 0x2e15b0 `HandleCacheGame_InitializeSeasonContentsChallengePartyScheduleFail`
- 0x2e1a80 `HandleCacheGame_LoadGuildCombatRecordFail`
- 0x2e1b00 `HandleCacheGame_RetrieveFactionStatisticsFail`
- 0x2e4010 `HandleCacheGame_DeliverSystemPostOk`
- 0x2e4080 `HandleCacheGame_DeliverSystemPostFail`

Stem `gamedaemon_cpp`:

- 0x339ee0 `GenerateTid`
- 0x33a210 `ManageSessionHandler::OnAccept`
- 0x33a250 `ManageSessionHandler::OnConnect`
- 0x33aaf0 `BuilderSessionHandler::OnAccept`
- 0x33ab30 `BuilderSessionHandler::OnConnect`
- 0x33afc0 `GamedReloadInvalidRestoreTimer::EventId`
- 0x340e70 `GameDaemon::GetRandomStoreServiceState`
- 0x340ea0 `GameDaemon::GetServerIdForDaemon`
- 0x340ee0 `GameDaemon::GetServerIdForNPChat`
- 0x342ae0 `GamedCooldownTimer::EventId`
- 0x343030 `GameDaemon::ServiceName`
- 0x343650 `GameDaemon::NotCheckToPlayInWeek` (the body uses the VS2010 `_Lower_bound` loop. The repo `algorithm` header has no `binary_search`.)
- 0x3438f0 `GameDaemon::WriteDump` (round 4 repair of P5_zero_arg: see Notes)
- 0x343910 `GameDaemon::GetAddressStringWForLogs`

## Not done

| RVA | Function | Reason |
| --- | --- | --- |
| 0x156b80 | `ManagementdChannel::PacketHandler` | The global `GamedManagementdPacketGamedSideHandlerList` (rva 0xE7FAF0) is not in the repo. Its size and entries are not known. One look-up did not give them. A later card that adds the handler list can lift this body. |
| 0x33aed0 | `NPMessageHandleEvent::~NPMessageHandleEvent` | The skeleton class has no base (PDB: DynamicEventObject). The delete form of `_tran` (virtual destructor call, then `Memory::_Manager[2]->Free`) is not clear. |
| 0x315de0 | `CachedChannel::InitChangedCachePacket` | The pseudocode is not clear: it writes a vftable (`AddChangedCachePacketSplitter`) into the first argument, and the `Packet::Compose` arguments do not agree with the format strings. One look-up did not give the form. |

## Notes

- Round 4 rebase: `gametran.h` has no conflict markers. It keeps the main declarations and the PDB layouts of this card. Stem `gametran_h` needed no change in round 4.
- Round 4, 0x3438f0 `GameDaemon::WriteDump`: the body calls `RaiseException(0xC0000005, 1, 0, NULL)` with all 4 arguments. The filter calls `GenerateDump(GetExceptionInformation(), false)`. The body does not read `fullMemory`, so the build does not spill it. Formtest gives SAME for the main body (`xor r9d, r9d` and `xor r8d, r8d` are present). The filter funclet stays DIFF (`GenerateDump` is a stub).
- 0x16cf30: the destructor frees `_mileageList` with `Memory::_Manager[2]->Free` only when `_mileageCount` is not 0. The file literal is the per-exe path of MileageDepositTran.cpp, line 453. It has a dead-strip keep pragma.
- The log bodies use the GameDaemon forms of `Log::Write` (E129). `AlertSender::Write` stays a stub. The card does not lift it.
- The session did not run the gate or funcdiff. The driver builds and records the MATCH comparison.

## Changed files

- `src/Server/GameDaemon/gametran.h`
- `src/Server/GameDaemon/gametran_h.cpp`
- `src/Server/GameDaemon/gamedaemon.h`
- `src/Server/GameDaemon/gamedaemon_cpp.cpp`
- `src/Server/GameDaemon/mileagedeposittran.h`
- `src/Server/GameDaemon/mileagedeposittran_cpp.cpp`
- `src/Server/GameDaemon/petitiondaemonchannel.cpp`
- `src/Server/GameDaemon/gamearenachannel_cpp_1.cpp`
- `src/Server/GameDaemon/cachedaemonchannel_1.cpp`
- `src/Server/GameDaemon/cachedaemonchannel_2.cpp`
- `src/Server/GameDaemon/cachedaemonchannel_3.cpp`
- `src/Server/GameDaemon/chattingserverchannel.cpp`
- `src/Server/GameDaemon/managementdchannel.cpp`
- `Docs/Plan/handoffs/lift-gamedaemon-gap-036-e36.md`
