# lift-lobbydaemon-0 handoff

Card: LobbyDaemon skeleton and stubs (wave 0). Source: LobbyDaemon.exe and LobbyDaemon.pdb (2019 + PDB, VS2010 SP1).
Wave 0 lifts no logic. A stub is not a lift.

## Result

| Check | Result |
| --- | --- |
| `LIFT_BUILD_DIR=build-ld-0 tools/gate.sh` | gate ok |
| Clang link of `LobbyDaemon.exe` | ok |
| VS2010 link of `LobbyDaemon.exe` (`tools/vs2010/build.sh LobbyDaemon`) | ok |
| `tools/parity.sh` (no `--accept`) | parity ok. CG, LG, SCD, POD: +0, no MATCH lost. LD: no baseline. |
| Lifted functions | 0 |
| Not done functions | 1921 (1400 with a `LIFT_STUB` body, 521 without a body) |

## MATCH comparison (`tools/parity.sh`, VS2010 /GL /LTCG)

| Exe | Baseline MATCH | Branch MATCH | New MATCH | MATCH -> DIFF | MATCH name gone |
| --- | --- | --- | --- | --- | --- |
| CacheGate | 456 | 456 (92.9 %) | 0 | 0 | 0 |
| LobbyGate | 658 | 658 (89.0 %) | 0 | 0 | 0 |
| SmartCouponDaemon | 630 | 630 (94.2 %) | 0 | 0 | 0 |
| PostOfficeDaemon | 694 | 694 (91.4 %) | 0 | 0 | 0 |
| LobbyDaemon | none | 49/2204 (2.2 %; 70 paired, 2134 only in original) | 49 | - | - |

Initial LobbyDaemon MATCH count: **49**. The MATCH functions are common code only: zstd (31), HeapMemoryManager (6),
AlertSender (5), Thread (3) and CRT startup. No LobbyDaemon module function is a MATCH, because all are stubs.

## Marker

| Item | Value |
| --- | --- |
| Macro | `LIFT_STUB(rva)` |
| Header | `src/Server/BloodLib/include/LiftStub.h` |
| Grep | `grep -rn "LIFT_STUB(" src` |
| Body | `__debugbreak(); ::abort(); __assume(0);` |
| Argument | RVA in LobbyDaemon.exe (2019 + PDB). `0` = no LD RVA (only `ClientSideDaemonChannel::onAccept`). |

The stub never reports success: it stops the process. `__assume(0)` is necessary, because VS2010 `stdlib.h`
does not declare `abort` noreturn. Without it, VS2010 LTCG stops with error C4716 for each stub with a return type.

## Module paths

| Group | Path | Count |
| --- | --- | --- |
| Server modules | `src/Server/LobbyDaemon/<M>.h`, `<M>.cpp` | 96 |
| BannedWordFilter (folder name ❓) | `src/External/BannedWordFilter/{BannedWordFilterLib,BannedWordFilterLoader,ConstFilterChat,ConstFilterName}` | 4 |
| FsdDecomposer | `src/library/FsdReader/FsdDecomposer` | 1 |
| PerfCounterProvider | `src/Server/BloodLib/source/PerfCounterProvider` | 1 |
| Exe resource | `src/Server/LobbyDaemon/LobbyDaemon.rc` (VERSIONINFO copied from the exe) | 1 |
| PDB types | `include/pdb/LobbyDaemon/types.h`, `src/selftest/pdb_types_LobbyDaemon.cpp` | 2 |

The 6 common modules are in `lift_lobbydaemon` only, so that the other exes do not change.
The classes in the module headers have no members and no bases yet. Later waves add the PDB layouts.

## The 18 missing common functions

| Owner file | PDB name | RVA | Result |
| --- | --- | --- | --- |
| `src/Server/Shared/SharedChannel.cpp` | `SharedChannel::Send(char const*, ...)` | 0x4b70 | stub |
| `src/Server/Shared/SharedChannel.cpp` | `SharedChannel::Send(Packet const*)` | 0x4ba0 | stub |
| `src/Server/Shared/SharedChannel.cpp` | `SharedChannel::sendV` | 0x4c50 | stub |
| `src/Server/Shared/SharedChannel.cpp` | `SharedChannelList::~SharedChannelList` | 0x4d20 | stub |
| `src/Server/Shared/SharedChannel.cpp` | `SharedChannelList::Initialize` | 0x4d60 | stub |
| `src/Server/Shared/SharedChannel.cpp` | `SharedChannelList::Set` | 0x4e20 | stub |
| `src/Server/BloodLib/source/Network.cpp` | `Network::GetAddress` | 0xe4900 | stub |
| `src/Server/BloodLib/source/Db.cpp` | `Db::ConvertTimeStamp` | 0xe81f0 | stub |
| `src/Server/Shared/NPChannel2.cpp` | `String::UnicodeToMultibyte` | 0x2700 | stub |
| `src/Server/Shared/NPChannel2.cpp` | `Packet::FreeSize` | 0x29d0 | stub |
| `src/Server/Shared/NPChannel2.cpp` | `NPMsgHelper::LocaleHourToUTCTime` | 0x2be0 | stub |
| `src/Server/Shared/NPChannel2.cpp` | `EventObject::~EventObject` | 0x2a20 | Not done: compiler-generated |
| `src/Server/LobbyGate/ContentsRuleConfigDefinition.cpp` | `ContentsRuleConfigReload::Load` | 0x29730 | stub |
| `src/Server/LobbyGate/ContentsRuleConfigDefinition.cpp` | `ContentsRuleConfig::ReloadContentsRuleConfig` | 0x29980 | stub |
| `src/Server/LobbyGate/ContentsRuleConfigDefinition.cpp` | `ContentsRuleConfig::UpdateReloadedVariable` | 0x2a090 | stub |
| `src/Server/LobbyGate/ContentsRuleConfigDefinition.cpp` | `ContentsRuleConfig::CompareMatch` | 0x2a210 | stub |
| `src/Security/source/BloodCrypto/key/CryptoKey.cpp` | `BigInteger::BigInteger` | 0x10dfb0 | Not done: `__forceinline` body in `BigInteger.h` |
| `src/Security/source/BloodCrypto/key/CryptoKey.cpp` | `BigInteger::~BigInteger` | 0x10dfe0 | Not done: `__forceinline` body in `BigInteger.h` |

LobbyDaemon does not link `NPChannel2.cpp` and `ContentsRuleConfigDefinition.cpp` yet. The other exes do not call
the new functions, so `/OPT:REF` removes them. The parameter names come from the LD PDB.

## Notes for the next waves

| Topic | Note |
| --- | --- |
| `ObjectPool.cpp` | `src/Server/LobbyDaemon/ObjectPool.{h,cpp}` is SCD code and is unchanged. It is not in `lift_lobbydaemon`: it uses `GObjPoolMemAlloc` as `SmartCouponObjPoolMemoryAllocator*`, but the LD PDB gives `LobbyObjPoolMemAllocator*`. The LD ObjectPool module (11 HR functions) is not in this card. A later wave must give LD its own form. |
| `ClientSideDaemonChannel::onAccept` | BloodLib `Channel.cpp` emits the vftable, so the link needs a body. LD has no symbol for it. The LD-only owner is `LobbyDaemon.cpp`, with `LIFT_STUB(0)`. |
| Path literals | `lift_common_ld` uses the plain BloodLib files and their default `__FILE__` paths. A later wave adds the LD wrappers. |
| `tools/pdb2h.py` | New `local_asserts`: types local to a member function (`__l46::SortByStartTime`) get `pdb_local::` in `sizeof`/`offsetof`. The CG, LG, SCD, POD and MDD `types.h` do not change. |
| `tools/funcdiff.py` | `is_tls_index` crashed on `mov [mem], <.tls offset>` in LD. It now returns False for a destination that is not a register. The other exes never reached this case (they did not crash), so their results do not change. |
| `tools/parity_shared.py`, `tools/parity_readme.py` | Unchanged on purpose. They keep 4 exes, because a branch must not change the README table or the shared results. The runner must add LD when it accepts the first LD baseline. |
| `tools/parity.sh --accept` | Not run. LD has no baseline in `Docs/Parity/baseline/`. |
| Generator | The worktree file `.scratch/gen_ld_stubs.py` wrote the module files. It is not committed. Do not run it again over lifted files. |

## Not done

All 1921 in-scope functions are Not done. The full table (module, RVA, PDB name, result, reason) is in
`Docs/Plan/handoffs/lift-lobbydaemon-0-notdone.tsv`.

| Result | Reason | Count |
| --- | --- | --- |
| stub | `LIFT_STUB` body only (1385 generated, incl. `wmain`; 15 common) | 1400 |
| no body | nested type in signature | 166 |
| no body | compiler-generated | 121 |
| no body | template instance | 111 |
| no body | no public symbol (initializer, atexit dtor, or folded) | 96 |
| no body | nested class member | 8 |
| no body | class is in common src (inline header body or owner elsewhere) | 7 |
| no body | operator, needs a hand declaration | 4 |
| no body | class by value in signature | 4 |
| no body | `__forceinline` body in `BigInteger.h` | 2 |
| no body | unparsed signature (`DispatchNPLobbyMessageHandler` 0xcb710) | 1 |
| no body | C linkage name (`tss_load_sdk` 0x7ac30) | 1 |
| **Total** | | **1921** |

### Not done without a body (521 rows)

| Module | RVA | PDB name | Reason |
| --- | --- | --- | --- |
| AbandonChargeJob | 0x4f30 | `RefCntPoolObj::operator delete` | operator, needs a hand declaration |
| AbandonChargeJob | 0x4fd0 | `` `vector constructor iterator' `` | compiler-generated |
| AbandonChargeJob | 0x50a0 | `` AbandonChargeJob::`scalar deleting destructor' `` | compiler-generated |
| AbandonChargeJob | 0x11d850 | `` `dynamic initializer for 'AbandonChargeJob::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| AbandonChargeJob | 0x11e7c0 | `` `dynamic atexit destructor for 'AbandonChargeJob::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| AccountInventoryChannel | 0x64e0 | `Network::iocpHandle` | class is in common src (inline header body or owner elsewhere) |
| AccountInventoryChannel | 0x6990 | `AccountInventoryChannel::SendGetGoodsCountReq` | nested type in signature |
| AccountInventoryChannel | 0x6bd0 | `AccountInventoryChannel::SendListGoodsReq` | nested type in signature |
| AccountInventoryChannel | 0x6e30 | `AccountInventoryChannel::SendTakeGoodsReq` | nested type in signature |
| AccountInventoryChannel | 0x7090 | `AccountInventoryChannel::SendRetrieveLobbyServiceItemListReq` | nested type in signature |
| AccountInventoryChannel | 0x72f0 | `AccountInventoryChannel::SendRetrieveSingleWarehouseItemReq` | nested type in signature |
| AccountInventoryChannel | 0x7590 | `AccountInventoryChannel::SendTryWarehouseItemConsumptionReq` | nested type in signature |
| AccountInventoryChannel | 0x7810 | `AccountInventoryChannel::SendFinishWarehouseItemConsumptionReq` | nested type in signature |
| AccountInventoryChannel | 0x7ab0 | `AccountInventoryChannel::SendConsumeWarehouseItemReq` | nested type in signature |
| AccountInventoryChannel | 0x7d30 | `AccountInventoryChannel::SendRetrieveCharacterGoodsCountReq` | nested type in signature |
| AccountInventoryChannel | 0x7fe0 | `` AccountInventorySessionHandler::`scalar deleting destructor' `` | compiler-generated |
| AccountInventoryChannel | 0x8790 | `swprintf_s<129>` | template instance |
| AccountInventoryLobbyPacketHandler | 0x87c0 | `PacketDecomposer::Reset` | class is in common src (inline header body or owner elsewhere) |
| ActivateGradeJob | 0xb9e0 | `RefCntObject::addReferenceCount` | class is in common src (inline header body or owner elsewhere) |
| ActivateGradeJob | 0xbbe0 | `` ActivateGradeJob::`scalar deleting destructor' `` | compiler-generated |
| ActivateGradeJob | 0x11d8a0 | `` `dynamic initializer for 'ActivateGradeJob::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| ActivateGradeJob | 0x11e800 | `` `dynamic atexit destructor for 'ActivateGradeJob::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| AddSlotJob | 0xd320 | `` AddSlotJob::`scalar deleting destructor' `` | compiler-generated |
| AddSlotJob | 0x11d8f0 | `` `dynamic initializer for 'AddSlotJob::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| AddSlotJob | 0x11e840 | `` `dynamic atexit destructor for 'AddSlotJob::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| AuctionBidJob | 0x111c0 | `` AuctionBidJob::`scalar deleting destructor' `` | compiler-generated |
| AuctionBidJob | 0x11d940 | `` `dynamic initializer for 'AuctionBidJob::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| AuctionBidJob | 0x11e880 | `` `dynamic atexit destructor for 'AuctionBidJob::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| AuctionDeliverJob | 0x12240 | `` RefCntPoolObj::`scalar deleting destructor' `` | compiler-generated |
| AuctionDeliverJob | 0x122c0 | `` LobbyJob::`scalar deleting destructor' `` | compiler-generated |
| AuctionDeliverJob | 0x123d0 | `` AuctionDeliverJob::`scalar deleting destructor' `` | compiler-generated |
| AuctionDeliverJob | 0x11d990 | `` `dynamic initializer for 'AuctionDeliverJob::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| AuctionDeliverJob | 0x11e8c0 | `` `dynamic atexit destructor for 'AuctionDeliverJob::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| AuctionEscrow | 0x13630 | `AuctionEscrow::GetDeliveryPostMessage` | nested type in signature |
| AuctionEscrow | 0x14770 | `AuctionEscrow::GetRollbackEscrowPostMessage` | nested type in signature |
| AuctionEscrowJob | 0x14d90 | `` AuctionEscrowJob::`scalar deleting destructor' `` | compiler-generated |
| AuctionEscrowJob | 0x11d9e0 | `` `dynamic initializer for 'AuctionEscrowJob::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| AuctionEscrowJob | 0x11e900 | `` `dynamic atexit destructor for 'AuctionEscrowJob::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| AuctionRollbackEscrowJob | 0x16070 | `` AuctionRollbackEscrowJob::`scalar deleting destructor' `` | compiler-generated |
| AuctionRollbackEscrowJob | 0x11da30 | `` `dynamic initializer for 'AuctionRollbackEscrowJob::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| AuctionRollbackEscrowJob | 0x11e940 | `` `dynamic atexit destructor for 'AuctionRollbackEscrowJob::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| BLDaemonInfo | 0x416f0 | `std::_Tree<std::_Tmap_traits<BLDaemonID,BLDaemonInfo * __ptr64,std::less<BLDaemonID>,StlAllocator<std::pair<BLDaemonID,BLDaemonInfo * __ptr64>,2>,0> >::_Linsert` | template instance |
| BannedWordFilterLib | 0x118b40 | `std::basic_string<wchar_t,std::char_traits<wchar_t>,BannedWordFilterAllocator<wchar_t> >::~basic_string<wchar_t,std::char_traits<wchar_t>,BannedWordFilterAllocator<wchar_t> >` | template instance |
| BannedWordFilterLib | 0x118b90 | `std::basic_string<wchar_t,std::char_traits<wchar_t>,BannedWordFilterAllocator<wchar_t> >::assign` | template instance |
| BannedWordFilterLib | 0x118c80 | `std::basic_string<wchar_t,std::char_traits<wchar_t>,BannedWordFilterAllocator<wchar_t> >::assign` | template instance |
| BannedWordFilterLib | 0x118d60 | `std::basic_string<wchar_t,std::char_traits<wchar_t>,BannedWordFilterAllocator<wchar_t> >::_Grow` | template instance |
| BannedWordFilterLib | 0x118de0 | `std::basic_string<wchar_t,std::char_traits<wchar_t>,BannedWordFilterAllocator<wchar_t> >::erase` | template instance |
| BannedWordFilterLib | 0x118e80 | `std::basic_string<wchar_t,std::char_traits<wchar_t>,BannedWordFilterAllocator<wchar_t> >::_Copy` | template instance |
| BannedWordFilterLoader | 0x119500 | `std::vector<FilterRec,BannedWordFilterAllocator<FilterRec> >::~vector<FilterRec,BannedWordFilterAllocator<FilterRec> >` | template instance |
| BannedWordFilterLoader | 0x119540 | `std::vector<FilterRec,BannedWordFilterAllocator<FilterRec> >::_Reserve` | template instance |
| BannedWordFilterLoader | 0x119600 | `std::vector<FilterRec,BannedWordFilterAllocator<FilterRec> >::reserve` | template instance |
| BannedWordFilterLoader | 0x119720 | `std::_Uninit_move<FilterRec * __ptr64,FilterRec * __ptr64,BannedWordFilterAllocator<FilterRec>,FilterRec>` | template instance |
| BindCharacterSlotJob | 0x16f70 | `` BindCharacterSlotJob::`scalar deleting destructor' `` | compiler-generated |
| BindCharacterSlotJob | 0x11da80 | `` `dynamic initializer for 'BindCharacterSlotJob::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| BindCharacterSlotJob | 0x11e980 | `` `dynamic atexit destructor for 'BindCharacterSlotJob::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| CancelWaitCharacterDeletionJob | 0x189c0 | `` CancelWaitCharacterDeletionJob::`scalar deleting destructor' `` | compiler-generated |
| CancelWaitCharacterDeletionJob | 0x11dad0 | `` `dynamic initializer for 'CancelWaitCharacterDeletionJob::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| CancelWaitCharacterDeletionJob | 0x11e9c0 | `` `dynamic atexit destructor for 'CancelWaitCharacterDeletionJob::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| ChangeCharacterAppearanceJob | 0x1ac30 | `` ChangeCharacterAppearanceJob::`scalar deleting destructor' `` | compiler-generated |
| ChangeCharacterAppearanceJob | 0x11db20 | `` `dynamic initializer for 'ChangeCharacterAppearanceJob::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| ChangeCharacterAppearanceJob | 0x11ea00 | `` `dynamic atexit destructor for 'ChangeCharacterAppearanceJob::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| ChangeCharacterRaceJob | 0x1eb20 | `` ChangeCharacterRaceJob::`scalar deleting destructor' `` | compiler-generated |
| ChangeCharacterRaceJob | 0x11db70 | `` `dynamic initializer for 'ChangeCharacterRaceJob::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| ChangeCharacterRaceJob | 0x11ea40 | `` `dynamic atexit destructor for 'ChangeCharacterRaceJob::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| ChangeCharacterSexJob | 0x22b40 | `` ChangeCharacterSexJob::`scalar deleting destructor' `` | compiler-generated |
| ChangeCharacterSexJob | 0x11dbc0 | `` `dynamic initializer for 'ChangeCharacterSexJob::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| ChangeCharacterSexJob | 0x11ea80 | `` `dynamic atexit destructor for 'ChangeCharacterSexJob::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| ChangeUserNameJob | 0x26ac0 | `` ChangeUserNameJob::`scalar deleting destructor' `` | compiler-generated |
| ChangeUserNameJob | 0x11dc10 | `` `dynamic initializer for 'ChangeUserNameJob::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| ChangeUserNameJob | 0x11eac0 | `` `dynamic atexit destructor for 'ChangeUserNameJob::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| Character | 0x30e90 | `Character::DB::Setup` | nested type in signature |
| Character | 0x31040 | `Character::IsPlayable` | nested type in signature |
| Character | 0x31090 | `Character::GetClientState` | nested type in signature |
| Character | 0x31550 | `Character::TryCreation` | nested type in signature |
| Character | 0x319b0 | `Character::FinishCreation` | nested type in signature |
| Character | 0x31c00 | `Character::CancelCreation` | nested type in signature |
| Character | 0x31cf0 | `Character::TryDeletion` | nested type in signature |
| Character | 0x31e60 | `Character::FinishDeletion` | nested type in signature |
| Character | 0x31fb0 | `Character::CancelDeletion` | nested type in signature |
| Character | 0x320a0 | `Character::TryRestore` | nested type in signature |
| Character | 0x321e0 | `Character::FinishRestore` | nested type in signature |
| Character | 0x322d0 | `Character::EndWaitDeletion` | nested type in signature |
| Character | 0x32350 | `Character::UpgradeJumpingCharacterState` | nested type in signature |
| CliSession | 0x329e0 | `` GameWorldPresence::`scalar deleting destructor' `` | compiler-generated |
| CliSession | 0x32b30 | `` CliSession::`scalar deleting destructor' `` | compiler-generated |
| CliSession | 0x33c80 | `` Character::`scalar deleting destructor' `` | compiler-generated |
| CliSession | 0x360a0 | `CliSession::NotifyChangedGrade` | nested type in signature |
| CliSession | 0x36170 | `CliSession::NotifyChangedGradeLevel` | nested type in signature |
| CliSession | 0x366e0 | `CliSession::setContentBans` | nested type in signature |
| CliSession | 0x36960 | `CliSession::setRMSInquiryResult` | nested type in signature |
| CliSession | 0x36a50 | `CliSession::setUserPromotionStatus` | nested type in signature |
| CliSession | 0x379b0 | `CliSession::FetchCharacterInfoList` | nested type in signature |
| CliSession | 0x38930 | `CliSession::UpdateAccountExp` | nested type in signature |
| CliSession | 0x38b50 | `CliSession::UpdateAccountContentQuota` | template instance |
| CliSession | 0x38cc0 | `CliSession::UpdateAccountRecycleTime` | template instance |
| CliSession | 0x38e30 | `CliSession::GetGameWorldWaitInfo` | nested type in signature |
| CliSession | 0x38f60 | `CliSession::EndWaitCharacterDeletion` | nested type in signature |
| CliSession | 0x3a450 | `` AnonymousLobbyGatePresence::`scalar deleting destructor' `` | compiler-generated |
| CliSession | 0x3a710 | `` LobbyGatePresence::`scalar deleting destructor' `` | compiler-generated |
| CliSession | 0x3aca0 | `LobbyGatePresence::NotifyChangedGrade` | nested type in signature |
| CliSession | 0x3ad60 | `LobbyGatePresence::NotifyChangedGradeLevel` | nested type in signature |
| CliSession | 0x3b1c0 | `GameWorldPresence::NotifyChangedGrade` | nested type in signature |
| CliSession | 0x3b290 | `GameWorldPresence::NotifyChangedGradeLevel` | nested type in signature |
| CliSession | 0x3b340 | `` GameServiceLocation::`scalar deleting destructor' `` | compiler-generated |
| CliSession | 0x5a060 | `std::vector<LobbyService::DB * __ptr64,StlAllocator<LobbyService::DB * __ptr64,2> >::~vector<LobbyService::DB * __ptr64,StlAllocator<LobbyService::DB * __ptr64,2> >` | template instance |
| CliSession | 0x5a0a0 | `GameServiceLocation::GetKind` | nested type in signature |
| CliSession | 0x95fe0 | `std::vector<ContentBan,StlAllocator<ContentBan,2> >::reserve` | template instance |
| CliSession | 0x96100 | `std::vector<ContentBan,StlAllocator<ContentBan,2> >::push_back` | template instance |
| CliSession | 0x962a0 | `std::vector<ContentBan,StlAllocator<ContentBan,2> >::_Reserve` | template instance |
| CliSession | 0x963f0 | `std::_Uninit_move<ContentBan * __ptr64,ContentBan * __ptr64,StlAllocator<ContentBan,2>,ContentBan>` | template instance |
| CliSession | 0x99980 | `LobbyGatePresence::GetKind` | nested type in signature |
| CliSession | 0xe3ec0 | `AnonymousLobbyGatePresence::GetKind` | nested type in signature |
| CliSession | 0xe51f0 | `GameWorldPresence::GetKind` | nested type in signature |
| CliSession | 0x11dd50 | `` `dynamic initializer for 'CliSession::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| CliSession | 0x11ebc0 | `` `dynamic atexit destructor for 'CliSession::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| CliSessionJob | 0x3bf80 | `` CliSessionJob::`scalar deleting destructor' `` | compiler-generated |
| CliSessionManager | 0x3c0e0 | `` InitCliSessionWnpTokenJob::`scalar deleting destructor' `` | compiler-generated |
| CliSessionManager | 0x3c110 | `` CliSessionManager::`scalar deleting destructor' `` | compiler-generated |
| CliSessionManager | 0x3c140 | `CliSessionManager::InitSessionWnpToken` | class by value in signature |
| CliSessionManager | 0x3c780 | `CliSessionManager::StartSessionWnpToken` | class by value in signature |
| CliSessionManager | 0x61490 | `std::vector<CliSession * __ptr64,StlAllocator<CliSession * __ptr64,2> >::~vector<CliSession * __ptr64,StlAllocator<CliSession * __ptr64,2> >` | template instance |
| CliSessionTable | 0x3cfe0 | `operator delete[]` | operator, needs a hand declaration |
| CliSessionTable | 0x3d020 | `` GateNode::`scalar deleting destructor' `` | compiler-generated |
| CliSessionTable | 0x3d080 | `` CliSessionTable::`scalar deleting destructor' `` | compiler-generated |
| CliSessionTable | 0x3d8f0 | `std::map<id128,CliSession * __ptr64,std::less<id128>,StlAllocator<std::pair<id128,CliSession * __ptr64>,2> >::~map<id128,CliSession * __ptr64,std::less<id128>,StlAllocator<std::pair<id128,CliSession * __ptr64>,2> >` | template instance |
| CliSessionTable | 0x3e550 | `CliSessionTable::SelectAll_index_gatekey` | template instance |
| CliSessionTable | 0x3ec40 | `CliSessionTable::SelectAll_index_pcid` | template instance |
| CliSessionTable | 0x3ed50 | `CliSessionTable::SelectAll` | template instance |
| CliSessionTable | 0x3eef0 | `CliSessionTable::Select_index_gate` | template instance |
| CliSessionTable | 0x3f090 | `std::map<unsigned __int64,CliSession * __ptr64,std::less<unsigned __int64>,StlAllocator<std::pair<unsigned __int64,CliSession * __ptr64>,2> >::map<unsigned __int64,CliSession * __ptr64,std::less<unsigned __int64>,StlAllocator<std::pair<unsigned __int64,CliSession * __ptr64>,2> >` | template instance |
| CliSessionTable | 0x3f0f0 | `std::_Tree<std::_Tmap_traits<unsigned __int64,CliSession * __ptr64,std::less<unsigned __int64>,StlAllocator<std::pair<unsigned __int64,CliSession * __ptr64>,2>,0> >::clear` | template instance |
| CliSessionTable | 0x3f180 | `std::map<id128,CliSession * __ptr64,std::less<id128>,StlAllocator<std::pair<id128,CliSession * __ptr64>,2> >::map<id128,CliSession * __ptr64,std::less<id128>,StlAllocator<std::pair<id128,CliSession * __ptr64>,2> >` | template instance |
| CliSessionTable | 0x3f1e0 | `std::_Tree<std::_Tmap_traits<id128,CliSession * __ptr64,std::less<id128>,StlAllocator<std::pair<id128,CliSession * __ptr64>,2>,0> >::erase` | template instance |
| CliSessionTable | 0x3f550 | `std::_Tree<std::_Tmap_traits<id128,CliSession * __ptr64,std::less<id128>,StlAllocator<std::pair<id128,CliSession * __ptr64>,2>,0> >::clear` | template instance |
| CliSessionTable | 0x3f5e0 | `std::vector<CliSession * __ptr64,StlAllocator<CliSession * __ptr64,2> >::push_back` | template instance |
| CliSessionTable | 0x3f670 | `std::_Tree<std::_Tmap_traits<unsigned __int64,CliSession * __ptr64,std::less<unsigned __int64>,StlAllocator<std::pair<unsigned __int64,CliSession * __ptr64>,2>,0> >::_Erase` | template instance |
| CliSessionTable | 0x3f6e0 | `std::_Tree<std::_Tmap_traits<id128,CliSession * __ptr64,std::less<id128>,StlAllocator<std::pair<id128,CliSession * __ptr64>,2>,0> >::_Erase` | template instance |
| CliSessionTable | 0x3f750 | `std::_Tree<std::_Tmap_traits<id128,CliSession * __ptr64,std::less<id128>,StlAllocator<std::pair<id128,CliSession * __ptr64>,2>,0> >::_Lrotate` | template instance |
| CliSessionTable | 0x3f7b0 | `std::_Tree<std::_Tmap_traits<id128,CliSession * __ptr64,std::less<id128>,StlAllocator<std::pair<id128,CliSession * __ptr64>,2>,0> >::_Rrotate` | template instance |
| CliSessionTable | 0x3f810 | `std::vector<CliSession * __ptr64,StlAllocator<CliSession * __ptr64,2> >::_Reserve` | template instance |
| CliSessionTable | 0x3f8a0 | `std::_Tree<std::_Tmap_traits<unsigned __int64,CliSession * __ptr64,std::less<unsigned __int64>,StlAllocator<std::pair<unsigned __int64,CliSession * __ptr64>,2>,0> >::erase` | template instance |
| CliSessionTable | 0x3f980 | `std::_Tree<std::_Tmap_traits<id128,CliSession * __ptr64,std::less<id128>,StlAllocator<std::pair<id128,CliSession * __ptr64>,2>,0> >::erase` | template instance |
| CliSessionTable | 0x3fa60 | `std::vector<CliSession * __ptr64,StlAllocator<CliSession * __ptr64,2> >::reserve` | template instance |
| CliSessionTable | 0x3fb50 | `std::_Tree<std::_Tmap_traits<unsigned __int64,CliSession * __ptr64,std::less<unsigned __int64>,StlAllocator<std::pair<unsigned __int64,CliSession * __ptr64>,2>,0> >::_Linsert` | template instance |
| CliSessionTable | 0x3fc80 | `std::_Tree<std::_Tmap_traits<id128,CliSession * __ptr64,std::less<id128>,StlAllocator<std::pair<id128,CliSession * __ptr64>,2>,0> >::_Linsert` | template instance |
| CliSessionTable | 0x3fdd0 | `std::_Tree<std::_Tmap_traits<unsigned __int64,CliSession * __ptr64,std::less<unsigned __int64>,StlAllocator<std::pair<unsigned __int64,CliSession * __ptr64>,2>,0> >::_Insert` | template instance |
| CliSessionTable | 0x40080 | `std::_Tree<std::_Tmap_traits<id128,CliSession * __ptr64,std::less<id128>,StlAllocator<std::pair<id128,CliSession * __ptr64>,2>,0> >::_Insert` | template instance |
| CliSessionTable | 0x40330 | `std::_Tree_val<std::_Tmap_traits<id128,CliSession * __ptr64,std::less<id128>,StlAllocator<std::pair<id128,CliSession * __ptr64>,2>,0> >::_Buynode<std::pair<id128,CliSession * __ptr64> >` | template instance |
| CliSessionTable | 0x40440 | `std::map<unsigned __int64,CliSession * __ptr64,std::less<unsigned __int64>,StlAllocator<std::pair<unsigned __int64,CliSession * __ptr64>,2> >::~map<unsigned __int64,CliSession * __ptr64,std::less<unsigned __int64>,StlAllocator<std::pair<unsigned __int64,CliSession * __ptr64>,2> >` | template instance |
| CliSessionTable | 0x41380 | `std::_Tree<std::_Tmap_traits<unsigned __int64,CliSession * __ptr64,std::less<unsigned __int64>,StlAllocator<std::pair<unsigned __int64,CliSession * __ptr64>,2>,0> >::erase` | template instance |
| CliSessionTable | 0x54660 | `std::_Tree_val<std::_Tmap_traits<id128,CliSession * __ptr64,std::less<id128>,StlAllocator<std::pair<id128,CliSession * __ptr64>,2>,0> >::~_Tree_val<std::_Tmap_traits<id128,CliSession * __ptr64,std::less<id128>,StlAllocator<std::pair<id128,CliSession * __ptr64>,2>,0> >` | template instance |
| CliSessionTable | 0xc2510 | `std::_Tree_val<std::_Tmap_traits<unsigned __int64,CliSession * __ptr64,std::less<unsigned __int64>,StlAllocator<std::pair<unsigned __int64,CliSession * __ptr64>,2>,0> >::_Buynode<std::pair<unsigned __int64,CliSession * __ptr64> >` | template instance |
| ConstFilterChat | 0x119760 | `std::basic_string<wchar_t,std::char_traits<wchar_t>,BannedWordFilterAllocator<wchar_t> >::operator[]` | template instance |
| ConstFilterName | 0x119770 | `StrNormalize` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| ConstFilterName | 0x119870 | `ConstFilterName` | template instance |
| CreateCharacterJob | 0x41920 | `` CreateCharacterJob::`scalar deleting destructor' `` | compiler-generated |
| CreateCharacterJob | 0x11dda0 | `` `dynamic initializer for 'CreateCharacterJob::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| CreateCharacterJob | 0x11ec00 | `` `dynamic atexit destructor for 'CreateCharacterJob::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| CreateInitialUserNameJob | 0x2fd00 | `` CreateInitialUserNameJob::`scalar deleting destructor' `` | compiler-generated |
| CreateInitialUserNameJob | 0x11dd00 | `` `dynamic initializer for 'CreateInitialUserNameJob::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| CreateInitialUserNameJob | 0x11eb80 | `` `dynamic atexit destructor for 'CreateInitialUserNameJob::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| CryptoKey | 0x10dfb0 | `BigInteger::BigInteger` | __forceinline body in BigInteger.h; the compiler emits it |
| CryptoKey | 0x10dfe0 | `BigInteger::~BigInteger` | __forceinline body in BigInteger.h; the compiler emits it |
| DeleteCharacterJob | 0x45180 | `` DeleteCharacterJob::`scalar deleting destructor' `` | compiler-generated |
| DeleteCharacterJob | 0x11ddf0 | `` `dynamic initializer for 'DeleteCharacterJob::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| DeleteCharacterJob | 0x11ec40 | `` `dynamic atexit destructor for 'DeleteCharacterJob::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| DepositMileageJob | 0x49ba0 | `DepositMileageJob::DepositMileageJob` | nested type in signature |
| DepositMileageJob | 0x49c70 | `` DepositMileageJob::`scalar deleting destructor' `` | compiler-generated |
| DepositMileageJob | 0x11de40 | `` `dynamic initializer for 'DepositMileageJob::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| DepositMileageJob | 0x11ec80 | `` `dynamic atexit destructor for 'DepositMileageJob::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| EndWaitGameWorldJob | 0x4b0c0 | `` EndWaitGameWorldJob::`scalar deleting destructor' `` | compiler-generated |
| EndWaitGameWorldJob | 0x11de90 | `` `dynamic initializer for 'EndWaitGameWorldJob::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| EndWaitGameWorldJob | 0x11ecc0 | `` `dynamic atexit destructor for 'EndWaitGameWorldJob::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| EnterGameWorldJob | 0x84ee0 | `` EnterGameWorldJob::`scalar deleting destructor' `` | compiler-generated |
| EnterGameWorldJob | 0x11e4d0 | `` `dynamic initializer for 'EnterGameWorldJob::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| EnterGameWorldJob | 0x11f1c0 | `` `dynamic atexit destructor for 'EnterGameWorldJob::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| ExtendJumpingCharacterCreationQuotaJob | 0x2a4a0 | `` ExtendJumpingCharacterCreationQuotaJob::`scalar deleting destructor' `` | compiler-generated |
| ExtendJumpingCharacterCreationQuotaJob | 0x2d500 | `` UpgradeJumpingCharacterStateJob::`scalar deleting destructor' `` | compiler-generated |
| ExtendJumpingCharacterCreationQuotaJob | 0x11dc60 | `` `dynamic initializer for 'ExtendJumpingCharacterCreationQuotaJob::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| ExtendJumpingCharacterCreationQuotaJob | 0x11dcb0 | `` `dynamic initializer for 'UpgradeJumpingCharacterStateJob::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| ExtendJumpingCharacterCreationQuotaJob | 0x11eb00 | `` `dynamic atexit destructor for 'ExtendJumpingCharacterCreationQuotaJob::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| ExtendJumpingCharacterCreationQuotaJob | 0x11eb40 | `` `dynamic atexit destructor for 'UpgradeJumpingCharacterStateJob::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| GameTimeSchedule | 0x4c0c0 | `` GameTimeScheduler::`scalar deleting destructor' `` | compiler-generated |
| GameWorld | 0x4c870 | `` GameWorld::`scalar deleting destructor' `` | compiler-generated |
| GameWorld | 0x4c880 | `GameWorld::Setup` | nested type in signature |
| GameWorld | 0x4ca30 | `GameWorld::Update` | nested type in signature |
| GameWorld | 0x4d510 | `GameWorldCluster::Setup` | nested type in signature |
| GameWorld | 0x4d790 | `GameWorldCluster::Update` | nested type in signature |
| GameWorld | 0x4e310 | `GameWorldCluster::giveupWait` | nested type in signature |
| GameWorld | 0x4e440 | `GameWorldCluster::getWaitInfo` | nested type in signature |
| GameWorld | 0x4e900 | `GameWorldRegistry::EnumerateCluster` | template instance |
| GameWorld | 0x4f920 | `` GameWorldReporter::`scalar deleting destructor' `` | compiler-generated |
| GameWorld | 0x4fbe0 | `` GameWorldReport::`scalar deleting destructor' `` | compiler-generated |
| GameWorld | 0x500c0 | `swprintf_s<128>` | template instance |
| GameWorld | 0x500f0 | `std::_Tree<std::_Tmap_traits<short,GameWorldCluster * __ptr64,std::less<short>,StlAllocator<std::pair<short,GameWorldCluster * __ptr64>,2>,0> >::_Linsert` | template instance |
| GameWorld | 0x504d0 | `std::_Tree_val<std::_Tmap_traits<short,GameWorldCluster * __ptr64,std::less<short>,StlAllocator<std::pair<short,GameWorldCluster * __ptr64>,2>,0> >::_Buynode<std::pair<short,GameWorldCluster * __ptr64> >` | template instance |
| GameWorld | 0x59c70 | `` WorldClusterCounterSet::`scalar deleting destructor' `` | compiler-generated |
| GameWorld | 0x96d20 | `std::map<short,GameWorldCluster * __ptr64,std::less<short>,StlAllocator<std::pair<short,GameWorldCluster * __ptr64>,2> >::~map<short,GameWorldCluster * __ptr64,std::less<short>,StlAllocator<std::pair<short,GameWorldCluster * __ptr64>,2> >` | template instance |
| GamedChannel | 0x802e0 | `` GamedChannelManager::`scalar deleting destructor' `` | compiler-generated |
| GamedChannel | 0x80e20 | `GamedChannel::SendCreateCharacterReq` | nested type in signature |
| GamedChannel | 0x81040 | `GamedChannel::SendDeleteCharacterReq` | nested type in signature |
| GamedChannel | 0x811c0 | `GamedChannel::SendRestoreCharacterReq` | nested type in signature |
| GamedChannel | 0x814a0 | `GamedChannel::SendKickReq` | nested type in signature |
| GamedChannel | 0x82750 | `GamedChannel::SendChangeCharacterAppearanceReq` | nested type in signature |
| GamedChannel | 0x82950 | `GamedChannel::SendChangeCharacterSexReq` | nested type in signature |
| GamedChannel | 0x82b70 | `GamedChannel::SendChangeCharacterRaceReq` | nested type in signature |
| GamedChannel | 0x82db0 | `GamedChannel::SendRenameCharacterReq` | nested type in signature |
| GamedChannel | 0x83960 | `GamedChannel::SendAuctionEscrowReq` | nested type in signature |
| GetChargeInfoJob | 0x50690 | `` GetChargeInfoJob::`scalar deleting destructor' `` | compiler-generated |
| GetChargeInfoJob | 0x11dee0 | `` `dynamic initializer for 'GetChargeInfoJob::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| GetChargeInfoJob | 0x11ed00 | `` `dynamic atexit destructor for 'GetChargeInfoJob::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| GetGoodsCountJob | 0x515b0 | `` GetGoodsCountJob::`scalar deleting destructor' `` | compiler-generated |
| GetGoodsCountJob | 0x11df30 | `` `dynamic initializer for 'GetGoodsCountJob::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| GetGoodsCountJob | 0x11ed40 | `` `dynamic atexit destructor for 'GetGoodsCountJob::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| GetLobbyServiceItemJob | 0x521c0 | `` GetLobbyServiceItemJob::`scalar deleting destructor' `` | compiler-generated |
| GetLobbyServiceItemJob | 0x11df80 | `` `dynamic initializer for 'GetLobbyServiceItemJob::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| GetLobbyServiceItemJob | 0x11ed80 | `` `dynamic atexit destructor for 'GetLobbyServiceItemJob::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| GiveupWaitGameWorldJob | 0x52dd0 | `` GiveupWaitGameWorldJob::`scalar deleting destructor' `` | compiler-generated |
| GiveupWaitGameWorldJob | 0x11dfd0 | `` `dynamic initializer for 'GiveupWaitGameWorldJob::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| GiveupWaitGameWorldJob | 0x11edc0 | `` `dynamic atexit destructor for 'GiveupWaitGameWorldJob::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| GradeService | 0x53670 | `GradeService::parseGradeChangedReason` | nested type in signature |
| GradeService | 0x53750 | `GradeService::SetGradeLevel` | nested type in signature |
| GradeService | 0x53800 | `GradeService::SetGradeList` | nested type in signature |
| GradeService | 0x539d0 | `GradeService::ApplyChangedGrade` | nested type in signature |
| GradeService | 0x541f0 | `GradeService::ApplyChangedGradeLevel` | nested type in signature |
| GradeService | 0x54680 | `std::_Tree<std::_Tmap_traits<int,Grade * __ptr64,std::less<int>,StlAllocator<std::pair<int,Grade * __ptr64>,2>,0> >::_Linsert` | template instance |
| GradeService | 0x547b0 | `std::_Tree_val<std::_Tmap_traits<int,Grade * __ptr64,std::less<int>,StlAllocator<std::pair<int,Grade * __ptr64>,2>,0> >::_Buynode<std::pair<int,Grade * __ptr64> >` | template instance |
| InfoGateChannel | 0x2ea50 | `` InfoGateChannelManager::`scalar deleting destructor' `` | compiler-generated |
| InitCliSessionWlobbyTokenJob | 0x54910 | `` InitCliSessionWlobbyTokenJob::`scalar deleting destructor' `` | compiler-generated |
| InitCliSessionWlobbyTokenJob | 0x11e020 | `` `dynamic initializer for 'InitCliSessionWlobbyTokenJob::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| InitCliSessionWlobbyTokenJob | 0x11ee00 | `` `dynamic atexit destructor for 'InitCliSessionWlobbyTokenJob::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| InitCliSessionWnpTokenJob | 0x11e610 | `` `dynamic initializer for 'InitCliSessionWnpTokenJob::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| InitCliSessionWnpTokenJob | 0x11f2c0 | `` `dynamic atexit destructor for 'InitCliSessionWnpTokenJob::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| KickJob | 0x86280 | `KickJob::KickJob` | nested type in signature |
| KickJob | 0x862d0 | `` KickJob::`scalar deleting destructor' `` | compiler-generated |
| KickJob | 0x87670 | `` NPDemander::`scalar deleting destructor' `` | compiler-generated |
| KickJob | 0x87700 | `` ManageDemander::`scalar deleting destructor' `` | compiler-generated |
| KickJob | 0x11e520 | `` `dynamic initializer for 'KickJob::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| KickJob | 0x11f200 | `` `dynamic atexit destructor for 'KickJob::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| LeaveGameWorldJob | 0x87890 | `` LeaveGameWorldJob::`scalar deleting destructor' `` | compiler-generated |
| LeaveGameWorldJob | 0x11e570 | `` `dynamic initializer for 'LeaveGameWorldJob::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| LeaveGameWorldJob | 0x11f240 | `` `dynamic atexit destructor for 'LeaveGameWorldJob::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| ListGoodsJob | 0x55030 | `` ListGoodsJob::`scalar deleting destructor' `` | compiler-generated |
| ListGoodsJob | 0x11e070 | `` `dynamic initializer for 'ListGoodsJob::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| ListGoodsJob | 0x11ee40 | `` `dynamic atexit destructor for 'ListGoodsJob::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| ListLobbyServiceItemJob | 0x55c90 | `` ListLobbyServiceItemJob::`scalar deleting destructor' `` | compiler-generated |
| ListLobbyServiceItemJob | 0x11e0c0 | `` `dynamic initializer for 'ListLobbyServiceItemJob::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| ListLobbyServiceItemJob | 0x11ee80 | `` `dynamic atexit destructor for 'ListLobbyServiceItemJob::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| LobbyCharacterDeletionScheduler | 0x56ce0 | `std::vector<LobbyDB::EndWaitDeletionInfo * __ptr64,StlAllocator<LobbyDB::EndWaitDeletionInfo * __ptr64,2> >::clear` | template instance |
| LobbyDB | 0x9fe00 | `LobbyDB::LoadGameAccount` | nested type in signature |
| LobbyDB | 0xa17f0 | `LobbyDB::LoadCharacterList` | nested type in signature |
| LobbyDB | 0xa24c0 | `LobbyDB::LoadGameWorldCluster` | nested type in signature |
| LobbyDB | 0xa2dd0 | `LobbyDB::LoadGameWorld` | nested type in signature |
| LobbyDB | 0xa4d30 | `LobbyDB::RetrieveExpiredDeletionWaitingList` | template instance |
| LobbyDB | 0xa70b0 | `LobbyDB::LoadJumpingCharacterCreationQuota` | nested type in signature |
| LobbyDB | 0xa79f0 | `LobbyDB::LoadGameAccounExpInfo` | nested type in signature |
| LobbyDB | 0xa7e90 | `LobbyDB::RegisterGameAccountExpInfo` | nested type in signature |
| LobbyDB | 0xa81e0 | `LobbyDB::UpdateGameAccountExpInfo` | nested type in signature |
| LobbyDB | 0xa84f0 | `LobbyDB::LoadGameAccountContentQuotaList` | template instance |
| LobbyDB | 0xa8a00 | `LobbyDB::UpdateGameAccountContentQuota` | template instance |
| LobbyDB | 0xa8e00 | `LobbyDB::LoadGameAccountRecycleTimeList` | template instance |
| LobbyDB | 0xa92a0 | `LobbyDB::UpdateGameAccountRecycleTime` | template instance |
| LobbyDB | 0xa9880 | `LobbyDB::LoadIncompleteLobbyService` | template instance |
| LobbyDB | 0xb5410 | `LobbyDB::TryAuctionEscrowRollback` | nested type in signature |
| LobbyDaemon | 0x991c0 | `SystemEvent::~SystemEvent` | class is in common src (inline header body or owner elsewhere) |
| LobbyDaemon | 0x991f0 | `SystemEvent::Make` | class is in common src (inline header body or owner elsewhere) |
| LobbyDaemon | 0x99310 | `` AccountInventoryChannel::`scalar deleting destructor' `` | compiler-generated |
| LobbyDaemon | 0x99340 | `` PostOfficeChannel::`scalar deleting destructor' `` | compiler-generated |
| LobbyDaemon | 0x99370 | `` TencentUIC::`scalar deleting destructor' `` | compiler-generated |
| LobbyDaemon | 0x99ac0 | `ServiceItems::Add` | nested type in signature |
| LobbyDaemon | 0x99d20 | `TimeBasedPlaySeasonSchedule::Data::GetNextResetTimeUTC` | nested class member |
| LobbyDaemon | 0x9a3a0 | `` LobbyDaemon::`scalar deleting destructor' `` | compiler-generated |
| LobbyDaemon | 0x9dc50 | `RawPacketBufferHandler::~RawPacketBufferHandler` | class is in common src (inline header body or owner elsewhere) |
| LobbyDaemon | 0x9f240 | `LobbyDaemon::FilterBannedWord` | nested type in signature |
| LobbyDaemon | 0x9f340 | `LobbyDaemon::CheckServiceItemDataId` | nested type in signature |
| LobbyDaemon | 0x9f560 | `std::vector<unsigned int,StlAllocator<unsigned int,2> >::_Reserve` | template instance |
| LobbyDaemon | 0x9f5f0 | `std::vector<unsigned int,StlAllocator<unsigned int,2> >::reserve` | template instance |
| LobbyDaemon | 0x9f6e0 | `std::_Sort<unsigned int * __ptr64,__int64>` | template instance |
| LobbyDaemon | 0x9f7f0 | `std::_Unguarded_partition<unsigned int * __ptr64>` | template instance |
| LobbyDaemon | 0x9f980 | `std::_Median<unsigned int * __ptr64>` | template instance |
| LobbyDaemon | 0x9fae0 | `std::_Make_heap<unsigned int * __ptr64,__int64,unsigned int>` | template instance |
| LobbyDaemon | 0x9fbc0 | `std::_Sort_heap<unsigned int * __ptr64>` | template instance |
| LobbyDaemon | 0x9fcb0 | `std::_Insertion_sort1<unsigned int * __ptr64,unsigned int>` | template instance |
| LobbyDaemon | 0x9fd70 | `std::_Uninit_move<unsigned int * __ptr64,unsigned int * __ptr64,StlAllocator<unsigned int,2>,unsigned int>` | template instance |
| LobbyEvent | 0xbb860 | `` SharedChannelPacketHandleEvent::`scalar deleting destructor' `` | compiler-generated |
| LobbyEvent | 0xbb9c0 | `` SharedChannelFragmentPacketHandleEvent::`scalar deleting destructor' `` | compiler-generated |
| LobbyEvent | 0xbbab0 | `` NPLobbyMessageHandleEvent::`scalar deleting destructor' `` | compiler-generated |
| LobbyEvent | 0xbbbc0 | `` PacketHandleEvent::`scalar deleting destructor' `` | compiler-generated |
| LobbyGamePacketHandler | 0x88220 | `RepeatPacketDecomposer::Reset` | class is in common src (inline header body or owner elsewhere) |
| LobbyGamePacketHandler | 0x88230 | `` GamedChannel::`scalar deleting destructor' `` | compiler-generated |
| LobbyGamePacketHandler | 0x93360 | `DepositGameMileageCallback::OnError` | nested type in signature |
| LobbyGamePacketHandler | 0x933c0 | `DepositGameMileageCallback::OnSuccess` | nested type in signature |
| LobbyGamePacketHandler | 0x93430 | `DepositGameMileageCallback::OnFail` | nested type in signature |
| LobbyGamePacketHandler | 0x93490 | `DepositGameMileageCallback::OnTimeout` | nested type in signature |
| LobbyGamePacketHandler | 0x934f0 | `` DepositGameMileageCallback::`scalar deleting destructor' `` | compiler-generated |
| LobbyGamePacketHandler | 0x961c0 | `std::vector<AccountRecycleTime,StlAllocator<AccountRecycleTime,2> >::reserve` | template instance |
| LobbyGamePacketHandler | 0x96360 | `std::vector<AccountRecycleTime,StlAllocator<AccountRecycleTime,2> >::_Reserve` | template instance |
| LobbyGateChannel | 0xbbe90 | `LobbyGateChannel::SendInitSessionWithNPTokenOk` | class by value in signature |
| LobbyGateChannel | 0xbd130 | `LobbyGateChannel::SendDeleteCharacterFail` | nested type in signature |
| LobbyGateChannel | 0xbd330 | `LobbyGateChannel::SendCancelWaitCharacterDeletionFail` | nested type in signature |
| LobbyGateChannel | 0xbe2d0 | `LobbyGateChannel::SendRecoverCharacterFail` | nested type in signature |
| LobbyGateChannel | 0xc0a80 | `` LobbyGateChannelManager::`scalar deleting destructor' `` | compiler-generated |
| LobbyInfoGatePacketHandler | 0xc2590 | `` InfoGateChannel::`scalar deleting destructor' `` | compiler-generated |
| LobbyJob | 0xc16f0 | `` LobbyJobTaskEvent::`scalar deleting destructor' `` | compiler-generated |
| LobbyJob | 0xc18d0 | `LobbyJob::execute` | nested type in signature |
| LobbyJob | 0xc1990 | `LobbyJob::resume` | nested type in signature |
| LobbyLocale | 0x58120 | `LobbyLocale::GetNextThaiCell` | nested type in signature |
| LobbyLocale | 0x58260 | `LobbyLocale::GetVietVowelType` | nested type in signature |
| LobbyLocale | 0x58460 | `LobbyLocale::GetVietToneMarkType` | nested type in signature |
| LobbyManagePacketHandler | 0x58780 | `` ManageChannel::`scalar deleting destructor' `` | compiler-generated |
| LobbyManagePacketHandler | 0x587b0 | `DepositMileageJob::Callback::~Callback` | nested class member |
| LobbyManagePacketHandler | 0x587c0 | `` DepositMileageJob::Callback::`scalar deleting destructor' `` | compiler-generated |
| LobbyManagePacketHandler | 0x596c0 | `DepositPcCafeMileageJobManageCallback::OnError` | nested type in signature |
| LobbyManagePacketHandler | 0x596f0 | `DepositPcCafeMileageJobManageCallback::OnSuccess` | nested type in signature |
| LobbyManagePacketHandler | 0x59710 | `DepositPcCafeMileageJobManageCallback::OnFail` | nested type in signature |
| LobbyManagePacketHandler | 0x59790 | `DepositPcCafeMileageJobManageCallback::OnTimeout` | nested type in signature |
| LobbyManagePacketHandler | 0x597c0 | `` DepositPcCafeMileageJobManageCallback::`scalar deleting destructor' `` | compiler-generated |
| LobbyMessage | 0x2fa30 | `` LobbyMessage::`scalar deleting destructor' `` | compiler-generated |
| LobbyMessage | 0x2fa40 | `` CliSessionMessage::`scalar deleting destructor' `` | compiler-generated |
| LobbyPerfMonitor | 0x59cc0 | `` SystemPerfMonitor::`scalar deleting destructor' `` | compiler-generated |
| LobbyService | 0x6c4a0 | `CharacterCosmesisService::Setup` | nested type in signature |
| LobbyService | 0x6d180 | `AddSlotService::Setup` | nested type in signature |
| LobbyService | 0x6deb0 | `RenameCharacterService::Setup` | nested type in signature |
| LobbyService | 0x6ef90 | `ExtendJumpingCharacterCreationQuotaService::Setup` | nested type in signature |
| LobbyService | 0x6fb60 | `ChangeCharacterSexService::Setup` | nested type in signature |
| LobbyService | 0x70840 | `` ChangeCharacterRaceService::`scalar deleting destructor' `` | compiler-generated |
| LobbyService | 0x70850 | `ChangeCharacterRaceService::Setup` | nested type in signature |
| LobbyStats | 0x5a590 | `swprintf_s<260>` | template instance |
| LobbyStats | 0x5a5c0 | `sprintf_s<1024>` | template instance |
| LobbyTick | 0x5a5f0 | `` LobbyTick::`scalar deleting destructor' `` | compiler-generated |
| LobbyTick | 0x5a6e0 | `LobbyTick::Add` | nested type in signature |
| LobbyTick | 0x5a770 | `LobbyTick::Remove` | nested type in signature |
| LobbyTick | 0x5a900 | `LobbyTickEvent::LobbyTickEvent` | nested type in signature |
| LobbyTick | 0x5a990 | `` LobbyTickEvent::`scalar deleting destructor' `` | compiler-generated |
| LobbyToken | 0x967d0 | `` LobbyToken::`scalar deleting destructor' `` | compiler-generated |
| LobbyToken | 0x96d00 | `` LobbyTokenDesk::`scalar deleting destructor' `` | compiler-generated |
| LobbyToken | 0x97860 | `std::_Tree<std::_Tmap_traits<unsigned __int64,LobbyToken * __ptr64,std::less<unsigned __int64>,StlAllocator<std::pair<unsigned __int64,LobbyToken * __ptr64>,2>,0> >::_Linsert` | template instance |
| LobbyToken | 0x97990 | `std::_Tree_val<std::_Tmap_traits<unsigned __int64,LobbyToken * __ptr64,std::less<unsigned __int64>,StlAllocator<std::pair<unsigned __int64,LobbyToken * __ptr64>,2>,0> >::_Buynode<std::pair<unsigned __int64,LobbyToken * __ptr64> >` | template instance |
| LogoutInGameWorldJob | 0x5ab60 | `` LogoutInGameWorldJob::`scalar deleting destructor' `` | compiler-generated |
| LogoutInGameWorldJob | 0x11e110 | `` `dynamic initializer for 'LogoutInGameWorldJob::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| LogoutInGameWorldJob | 0x11eec0 | `` `dynamic atexit destructor for 'LogoutInGameWorldJob::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| LogoutJob | 0x97b60 | `` LogoutJob::`scalar deleting destructor' `` | compiler-generated |
| LogoutJob | 0x11e5c0 | `` `dynamic initializer for 'LogoutJob::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| LogoutJob | 0x11f280 | `` `dynamic atexit destructor for 'LogoutJob::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| MembershipMileage | 0x5c010 | `` MembershipMileage::`scalar deleting destructor' `` | compiler-generated |
| MembershipMileage | 0x5ca20 | `MembershipMileage::GradeChanged` | nested type in signature |
| MembershipMileage | 0x5cc50 | `` MembershipMileageSession::`scalar deleting destructor' `` | compiler-generated |
| MembershipMileage | 0x5cca0 | `MembershipMileageSession::start` | nested type in signature |
| MembershipMileage | 0x5ce40 | `MembershipMileageSession::update` | nested type in signature |
| MembershipMileage | 0x5cfd0 | `MembershipMileageSession::stop` | nested type in signature |
| MembershipMileage | 0x5d0d0 | `std::vector<Section<__int64>,StlAllocator<Section<__int64>,2> >::_Reserve` | template instance |
| MembershipMileage | 0x5d160 | `std::vector<Section<__int64>,StlAllocator<Section<__int64>,2> >::reserve` | template instance |
| MembershipMileage | 0x5d240 | `Section<__int64>::Intersect<__int64,std::vector,StlAllocator<Section<__int64>,2> >` | template instance |
| MembershipMileage | 0x96440 | `std::_Uninit_move<Section<__int64> * __ptr64,Section<__int64> * __ptr64,StlAllocator<Section<__int64>,2>,Section<__int64> >` | template instance |
| MembershipMileage | 0x9f540 | `std::vector<Section<__int64>,StlAllocator<Section<__int64>,2> >::vector<Section<__int64>,StlAllocator<Section<__int64>,2> >` | template instance |
| Mileage | 0x5d380 | `` LobbyMessageAcceptor::`scalar deleting destructor' `` | compiler-generated |
| Mileage | 0x5d5a0 | `MileageConfig::operator=` | operator, needs a hand declaration |
| Mileage | 0x5d880 | `` Mileage::`scalar deleting destructor' `` | compiler-generated |
| Mileage | 0x5dd60 | `Mileage::settle` | template instance |
| Mileage | 0x5df70 | `DepositMileageCallback::OnError` | nested type in signature |
| Mileage | 0x5e050 | `DepositMileageCallback::OnSuccess` | nested type in signature |
| Mileage | 0x5e0f0 | `DepositMileageCallback::OnFail` | nested type in signature |
| Mileage | 0x5e170 | `DepositMileageCallback::OnTimeout` | nested type in signature |
| Mileage | 0x5e660 | `Mileage::FeverTime::FeverTime` | nested class member |
| Mileage | 0x5e680 | `Mileage::FeverTime::~FeverTime` | nested class member |
| Mileage | 0x5e6c0 | `Mileage::FeverTime::Initiaize` | nested class member |
| Mileage | 0x5f170 | `Mileage::FeverTime::makeRepeatSection` | template instance |
| Mileage | 0x5f2c0 | `MileageLimit::Fillin` | template instance |
| Mileage | 0x5f460 | `` MileageManager::`scalar deleting destructor' `` | compiler-generated |
| Mileage | 0x60750 | `` MileageSession::`scalar deleting destructor' `` | compiler-generated |
| Mileage | 0x60b00 | `` MileageInterimDepositTimer::`scalar deleting destructor' `` | compiler-generated |
| Mileage | 0x60be0 | `MileageInterimDepositTimer::Register` | nested type in signature |
| Mileage | 0x60f20 | `MileageInterimDepositTimer::Node::Expire` | nested class member |
| Mileage | 0x614d0 | `swprintf_s<513>` | template instance |
| Mileage | 0x61500 | `` std::_Sort<MileageFeverTimeInfo * __ptr64 * __ptr64,__int64,`Mileage::Initialize'::`11'::FeverTimeSorter> `` | compiler-generated |
| Mileage | 0x61660 | `` std::_Sort<Section<__int64> * __ptr64,__int64,`Mileage::FeverTime::Initiaize'::`46'::SortByStartTime> `` | compiler-generated |
| Mileage | 0x617a0 | `` std::_Unguarded_partition<MileageFeverTimeInfo * __ptr64 * __ptr64,`Mileage::Initialize'::`11'::FeverTimeSorter> `` | compiler-generated |
| Mileage | 0x61990 | `` std::_Unguarded_partition<Section<__int64> * __ptr64,`Mileage::FeverTime::Initiaize'::`46'::SortByStartTime> `` | compiler-generated |
| Mileage | 0x61bc0 | `` std::_Median<MileageFeverTimeInfo * __ptr64 * __ptr64,`Mileage::Initialize'::`11'::FeverTimeSorter> `` | compiler-generated |
| Mileage | 0x61de0 | `` std::_Make_heap<MileageFeverTimeInfo * __ptr64 * __ptr64,__int64,MileageFeverTimeInfo * __ptr64,`Mileage::Initialize'::`11'::FeverTimeSorter> `` | compiler-generated |
| Mileage | 0x61ee0 | `` std::_Insertion_sort1<MileageFeverTimeInfo * __ptr64 * __ptr64,`Mileage::Initialize'::`11'::FeverTimeSorter,MileageFeverTimeInfo * __ptr64> `` | compiler-generated |
| Mileage | 0x61fc0 | `` std::_Median<Section<__int64> * __ptr64,`Mileage::FeverTime::Initiaize'::`46'::SortByStartTime> `` | compiler-generated |
| Mileage | 0x620a0 | `` std::_Make_heap<Section<__int64> * __ptr64,__int64,Section<__int64>,`Mileage::FeverTime::Initiaize'::`46'::SortByStartTime> `` | compiler-generated |
| Mileage | 0x62200 | `` std::_Sort_heap<Section<__int64> * __ptr64,`Mileage::FeverTime::Initiaize'::`46'::SortByStartTime> `` | compiler-generated |
| Mileage | 0x62350 | `` std::_Insertion_sort1<Section<__int64> * __ptr64,`Mileage::FeverTime::Initiaize'::`46'::SortByStartTime,Section<__int64> > `` | compiler-generated |
| Mileage | 0x62410 | `` std::_Med3<Section<__int64> * __ptr64,`Mileage::FeverTime::Initiaize'::`46'::SortByStartTime> `` | compiler-generated |
| Mileage | 0x62490 | `` std::_Pop_heap_0<MileageFeverTimeInfo * __ptr64 * __ptr64,MileageFeverTimeInfo * __ptr64,`Mileage::Initialize'::`11'::FeverTimeSorter> `` | compiler-generated |
| Mileage | 0x62550 | `` MileageLimit::`scalar deleting destructor' `` | compiler-generated |
| NPChannel2 | 0x2a20 | `EventObject::~EventObject` | compiler-generated |
| NPLobbyMessageHandler | 0xcb710 | `DispatchNPLobbyMessageHandler` | unparsed signature |
| NPLobbyMessageHandler | 0xcbcb0 | `Handle_SrvGate_RegisterService` | nested type in signature |
| NPLobbyMessageHandler | 0xcbe00 | `Handle_SrvProfile_GetUserProfile` | nested type in signature |
| NPLobbyMessageHandler | 0xcbea0 | `Handle_SrvGameTime_GetGameTime` | nested type in signature |
| NPLobbyMessageHandler | 0xcbf40 | `Handle_SrvAuth_ConsumeGameToken` | nested type in signature |
| NPLobbyMessageHandler | 0xcbfe0 | `Handle_SrvAuth_IsUserNameChangeableIncomplete` | nested type in signature |
| NPLobbyMessageHandler | 0xcc110 | `Handle_SrvAuth_GetUserNameChangeableIncomplete` | nested type in signature |
| NPLobbyMessageHandler | 0xcc240 | `Handle_SrvAuth_ChangeMyUserNameIncomplete` | nested type in signature |
| NPLobbyMessageHandler | 0xcc370 | `Handle_SrvPres_LogoutUser` | nested type in signature |
| NPLobbyMessageHandler | 0xcc900 | `Handle_SrvPres_SetAppData` | nested type in signature |
| NPLobbyMessageHandler | 0xcca30 | `Handle_CommonSlot_GetSlot` | nested type in signature |
| NPLobbyMessageHandler | 0xccad0 | `Handle_CommonSlot_ListSlots` | nested type in signature |
| NPLobbyMessageHandler | 0xccb70 | `Handle_SrvSlot_CreateSlots` | nested type in signature |
| NPLobbyMessageHandler | 0xccc10 | `Handle_SrvSlot_SetData` | nested type in signature |
| NPLobbyMessageHandler | 0xcccb0 | `Handle_SrvPres_Login` | nested type in signature |
| NPLobbyMessageHandler | 0xccd50 | `Handle_SrvPres_Logout` | nested type in signature |
| NPLobbyMessageHandler | 0xcce80 | `Handle_SrvPres_GetUserInfo` | nested type in signature |
| NPLobbyMessageHandler | 0xccf10 | `Handle_CommonPres_UserInfo` | nested type in signature |
| NPLobbyMessageHandler | 0xcd070 | `Handle_SrvPres_Message` | nested type in signature |
| NPLobbyMessageHandler | 0xcd1a0 | `Handle_SrvPres_Kick` | nested type in signature |
| NPLobbyMessageHandler | 0xcd2d0 | `Handle_SrvCharge_GetInfo` | nested type in signature |
| NPLobbyMessageHandler | 0xcd370 | `Handle_SrvCharge_Start` | nested type in signature |
| NPLobbyMessageHandler | 0xcd410 | `Handle_SrvCharge_Stop` | nested type in signature |
| NPLobbyMessageHandler | 0xcd540 | `Handle_SrvCharge_Abandon` | nested type in signature |
| NPLobbyMessageHandler | 0xcd5e0 | `Handle_SrvCharge_RequestStop` | nested type in signature |
| NPLobbyMessageHandler | 0xcdaa0 | `Handle_SrvCharge_NotifyApplyNewChargeItem` | nested type in signature |
| NPLobbyMessageHandler | 0xcdda0 | `Handle_SrvCharge_NotifyRemainTime` | nested type in signature |
| NPLobbyMessageHandler | 0xce140 | `Handle_SrvFriend_SendMessage` | nested type in signature |
| NPLobbyMessageHandler | 0xce280 | `Handle_CommonSecondPassword_GetStatus` | nested type in signature |
| NPLobbyMessageHandler | 0xce3c0 | `Handle_SrvSecondPassword_IsVerified` | nested type in signature |
| NPLobbyMessageHandler | 0xce500 | `Handle_SrvGameAccount_ListUserLastPresences` | nested type in signature |
| NPLobbyMessageHandler | 0xce5a0 | `Handle_CommonGrade_ListGrades` | nested type in signature |
| NPLobbyMessageHandler | 0xce640 | `Handle_CommonGrade_ListAllGrades` | nested type in signature |
| NPLobbyMessageHandler | 0xce6e0 | `Handle_CommonGrade_GetLevel` | nested type in signature |
| NPLobbyMessageHandler | 0xce780 | `Handle_SrvGrade_ActivateGrade` | nested type in signature |
| NPLobbyMessageHandler | 0xce820 | `Handle_SrvGrade_NotifyGradeChanged` | nested type in signature |
| NPLobbyMessageHandler | 0xced00 | `Handle_SrvGrade_NotifyScoreChanged` | nested type in signature |
| NPLobbyMessageHandler | 0xcf0b0 | `Handle_SrvAuction_Escrow` | nested type in signature |
| NPLobbyMessageHandler | 0xcf270 | `Handle_SrvAuction_RollbackEscrow` | nested type in signature |
| NPLobbyMessageHandler | 0xcf440 | `Handle_SrvAuction_Deliver` | nested type in signature |
| NPLobbyMessageHandler | 0xcf570 | `Handle_SrvAuction_Bid` | nested type in signature |
| NPLobbyMessageHandler | 0xcf620 | `Handle_SrvContentBan_ListUserBans` | nested type in signature |
| NPLobbyMessageHandler | 0xcf6c0 | `Handle_SrvRMS_Inquiry` | nested type in signature |
| NPLobbyMessageHandler | 0xcf760 | `Handle_SrvVirtualCurrency_Deposit` | nested type in signature |
| NPLobbyMessageHandler | 0xcf800 | `Handle_SrvPromotionStamp_ListCurrentPromotions` | nested type in signature |
| NPLobbyMessageHandler | 0xcf8a0 | `Handle_SrvPromotionStamp_GetPromotionPolicy` | nested type in signature |
| NPLobbyMessageHandler | 0xcf940 | `Handle_SrvPromotionStamp_GetUserPromotionStatus` | nested type in signature |
| NPLobbyMessageHandler | 0xcf9e0 | `Handle_SrvPromotionStamp_AttendPromotionSecured` | nested type in signature |
| NPServiceChannel | 0xcfa90 | `` NPGameServiceChannel::`scalar deleting destructor' `` | compiler-generated |
| NPServiceChannel | 0xcfac0 | `NPGameServiceChannelCmdDispatcher` | nested type in signature |
| NPServiceChannel | 0xd0100 | `NPServiceChannelManager::HandleMessage` | nested type in signature |
| NPServiceChannel | 0xd0a00 | `NPGameServiceChannel::SendRequestFriendSendMessage` | nested type in signature |
| NPServiceChannel | 0xd2240 | `` NPLobbyJobTransaction::`scalar deleting destructor' `` | compiler-generated |
| NPServiceChannel | 0xd2310 | `swprintf_s<33>` | template instance |
| PcCafe | 0x63340 | `` TencentNetBar::`scalar deleting destructor' `` | compiler-generated |
| PcCafeMileage | 0x633d0 | `` PcCafeMileage::`scalar deleting destructor' `` | compiler-generated |
| PerfCounterProvider | 0xe7cd0 | `PerfCounterProvider::setCounterSetInfo` | class by value in signature |
| PerfCounterProvider | 0x11e700 | `` `dynamic initializer for 'PerfCounterProvider::Instance'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| PerfCounterProvider | 0x11f3a0 | `` `dynamic atexit destructor for 'PerfCounterProvider::Instance'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| PostOfficeChannel | 0x63cb0 | `PostOfficeChannel::SendRegisterPostReq` | nested type in signature |
| PostOfficeChannel | 0x64130 | `` PostOfficeSessionHandler::`scalar deleting destructor' `` | compiler-generated |
| PostOfficeClientSideHandlerList | 0x32b50 | `operator delete` | operator, needs a hand declaration |
| RecoverPcJob | 0x64f80 | `` RecoverPcJob::`scalar deleting destructor' `` | compiler-generated |
| RecoverPcJob | 0x11e160 | `` `dynamic initializer for 'RecoverPcJob::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| RecoverPcJob | 0x11ef00 | `` `dynamic atexit destructor for 'RecoverPcJob::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| RenameCharacterJob | 0x66c30 | `` RenameCharacterJob::`scalar deleting destructor' `` | compiler-generated |
| RenameCharacterJob | 0x11e1b0 | `` `dynamic initializer for 'RenameCharacterJob::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| RenameCharacterJob | 0x11ef40 | `` `dynamic atexit destructor for 'RenameCharacterJob::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| RuleSet | 0x6bfc0 | `RuleSet::CheckName` | nested type in signature |
| SecondPasswordGetStatusJob | 0x71630 | `` SecondPasswordGetStatusJob::`scalar deleting destructor' `` | compiler-generated |
| SecondPasswordGetStatusJob | 0x11e200 | `` `dynamic initializer for 'SecondPasswordGetStatusJob::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| SecondPasswordGetStatusJob | 0x11ef80 | `` `dynamic atexit destructor for 'SecondPasswordGetStatusJob::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| SecondPasswordIsVerifiedJob | 0x721f0 | `` SecondPasswordIsVerifiedJob::`scalar deleting destructor' `` | compiler-generated |
| SecondPasswordIsVerifiedJob | 0x11e250 | `` `dynamic initializer for 'SecondPasswordIsVerifiedJob::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| SecondPasswordIsVerifiedJob | 0x11efc0 | `` `dynamic atexit destructor for 'SecondPasswordIsVerifiedJob::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| SetupNpScheduleInfoJob | 0x72d50 | `TimeBasedPlaySeasonSchedule::Rule::Rule` | nested class member |
| SetupNpScheduleInfoJob | 0x72d80 | `TimeBasedPlaySeasonSchedule::Rule::compare` | nested type in signature |
| SetupNpScheduleInfoJob | 0x72e20 | `` SetupNpScheduleInfoJob::`scalar deleting destructor' `` | compiler-generated |
| SetupNpScheduleInfoJob | 0x742c0 | `std::deque<int,StlAllocator<int,2> >::deque<int,StlAllocator<int,2> >` | template instance |
| SetupNpScheduleInfoJob | 0x74330 | `std::deque<int,StlAllocator<int,2> >::~deque<int,StlAllocator<int,2> >` | template instance |
| SetupNpScheduleInfoJob | 0x74380 | `std::deque<int,StlAllocator<int,2> >::begin` | template instance |
| SetupNpScheduleInfoJob | 0x743a0 | `std::deque<int,StlAllocator<int,2> >::push_back` | template instance |
| SetupNpScheduleInfoJob | 0x74460 | `std::deque<int,StlAllocator<int,2> >::_Growmap` | template instance |
| SetupNpScheduleInfoJob | 0x745a0 | `std::deque<int,StlAllocator<int,2> >::_Tidy` | template instance |
| SetupNpScheduleInfoJob | 0x74650 | `std::vector<TimeBasedPlaySeasonSchedule::Rule,StlAllocator<TimeBasedPlaySeasonSchedule::Rule,2> >::_Reserve` | template instance |
| SetupNpScheduleInfoJob | 0x74710 | `std::vector<TimeBasedPlaySeasonSchedule::Rule,StlAllocator<TimeBasedPlaySeasonSchedule::Rule,2> >::reserve` | template instance |
| SetupNpScheduleInfoJob | 0x74830 | `std::_Sort<TimeBasedPlaySeasonSchedule::Rule * __ptr64,__int64,bool (__cdecl*)(TimeBasedPlaySeasonSchedule::Rule const & __ptr64,TimeBasedPlaySeasonSchedule::Rule const & __ptr64)>` | template instance |
| SetupNpScheduleInfoJob | 0x749d0 | `std::_Unguarded_partition<TimeBasedPlaySeasonSchedule::Rule * __ptr64,bool (__cdecl*)(TimeBasedPlaySeasonSchedule::Rule const & __ptr64,TimeBasedPlaySeasonSchedule::Rule const & __ptr64)>` | template instance |
| SetupNpScheduleInfoJob | 0x74d40 | `std::_Uninit_def_fill_n<int * __ptr64 * __ptr64,unsigned __int64,int * __ptr64,StlAllocator<int * __ptr64,2>,int * __ptr64>` | template instance |
| SetupNpScheduleInfoJob | 0x74d70 | `std::_Uninit_move<TimeBasedPlaySeasonSchedule::Rule * __ptr64,TimeBasedPlaySeasonSchedule::Rule * __ptr64,StlAllocator<TimeBasedPlaySeasonSchedule::Rule,2>,TimeBasedPlaySeasonSchedule::Rule>` | template instance |
| SetupNpScheduleInfoJob | 0x74dd0 | `std::_Median<TimeBasedPlaySeasonSchedule::Rule * __ptr64,bool (__cdecl*)(TimeBasedPlaySeasonSchedule::Rule const & __ptr64,TimeBasedPlaySeasonSchedule::Rule const & __ptr64)>` | template instance |
| SetupNpScheduleInfoJob | 0x74ec0 | `std::_Make_heap<TimeBasedPlaySeasonSchedule::Rule * __ptr64,__int64,TimeBasedPlaySeasonSchedule::Rule,bool (__cdecl*)(TimeBasedPlaySeasonSchedule::Rule const & __ptr64,TimeBasedPlaySeasonSchedule::Rule const & __ptr64)>` | template instance |
| SetupNpScheduleInfoJob | 0x750a0 | `std::_Sort_heap<TimeBasedPlaySeasonSchedule::Rule * __ptr64,bool (__cdecl*)(TimeBasedPlaySeasonSchedule::Rule const & __ptr64,TimeBasedPlaySeasonSchedule::Rule const & __ptr64)>` | template instance |
| SetupNpScheduleInfoJob | 0x75150 | `std::_Insertion_sort1<TimeBasedPlaySeasonSchedule::Rule * __ptr64,bool (__cdecl*)(TimeBasedPlaySeasonSchedule::Rule const & __ptr64,TimeBasedPlaySeasonSchedule::Rule const & __ptr64),TimeBasedPlaySeasonSchedule::Rule>` | template instance |
| SetupNpScheduleInfoJob | 0x75280 | `std::_Med3<TimeBasedPlaySeasonSchedule::Rule * __ptr64,bool (__cdecl*)(TimeBasedPlaySeasonSchedule::Rule const & __ptr64,TimeBasedPlaySeasonSchedule::Rule const & __ptr64)>` | template instance |
| SetupNpScheduleInfoJob | 0x75390 | `std::_Adjust_heap<TimeBasedPlaySeasonSchedule::Rule * __ptr64,__int64,TimeBasedPlaySeasonSchedule::Rule,bool (__cdecl*)(TimeBasedPlaySeasonSchedule::Rule const & __ptr64,TimeBasedPlaySeasonSchedule::Rule const & __ptr64)>` | template instance |
| SetupNpScheduleInfoJob | 0x754d0 | `std::_Pop_heap_0<TimeBasedPlaySeasonSchedule::Rule * __ptr64,TimeBasedPlaySeasonSchedule::Rule,bool (__cdecl*)(TimeBasedPlaySeasonSchedule::Rule const & __ptr64,TimeBasedPlaySeasonSchedule::Rule const & __ptr64)>` | template instance |
| SetupNpScheduleInfoJob | 0xefaf0 | `swprintf` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| SetupNpScheduleInfoJob | 0xf1e70 | `std::_Deque_val<int,StlAllocator<int,2> >::~_Deque_val<int,StlAllocator<int,2> >` | template instance |
| SetupNpScheduleInfoJob | 0x11e2a0 | `` `dynamic initializer for 'SetupNpScheduleInfoJob::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| SetupNpScheduleInfoJob | 0x11f000 | `` `dynamic atexit destructor for 'SetupNpScheduleInfoJob::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| StartChargeJob | 0x75650 | `` StartChargeJob::`scalar deleting destructor' `` | compiler-generated |
| StartChargeJob | 0x11e2f0 | `` `dynamic initializer for 'StartChargeJob::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| StartChargeJob | 0x11f040 | `` `dynamic atexit destructor for 'StartChargeJob::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| StartCliSessionWlobbyTokenJob | 0x76330 | `` StartCliSessionWlobbyTokenJob::`scalar deleting destructor' `` | compiler-generated |
| StartCliSessionWlobbyTokenJob | 0x11e340 | `` `dynamic initializer for 'StartCliSessionWlobbyTokenJob::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| StartCliSessionWlobbyTokenJob | 0x11f080 | `` `dynamic atexit destructor for 'StartCliSessionWlobbyTokenJob::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| StartCliSessionWnpTokenJob | 0xd2480 | `` StartCliSessionWnpTokenJob::`scalar deleting destructor' `` | compiler-generated |
| StartCliSessionWnpTokenJob | 0xdc500 | `swprintf_s<65>` | template instance |
| StartCliSessionWnpTokenJob | 0x11e660 | `` `dynamic initializer for 'StartCliSessionWnpTokenJob::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| StartCliSessionWnpTokenJob | 0x11f300 | `` `dynamic atexit destructor for 'StartCliSessionWnpTokenJob::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| StopChargeJob | 0x77d70 | `` StopChargeJob::`scalar deleting destructor' `` | compiler-generated |
| StopChargeJob | 0x11e390 | `` `dynamic initializer for 'StopChargeJob::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| StopChargeJob | 0x11f0c0 | `` `dynamic atexit destructor for 'StopChargeJob::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| TakeAccountTimeBasedPlayRewardJob | 0x78980 | `` TakeAccountTimeBasedPlayRewardJob::`scalar deleting destructor' `` | compiler-generated |
| TakeAccountTimeBasedPlayRewardJob | 0x11e3e0 | `` `dynamic initializer for 'TakeAccountTimeBasedPlayRewardJob::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| TakeAccountTimeBasedPlayRewardJob | 0x11f100 | `` `dynamic atexit destructor for 'TakeAccountTimeBasedPlayRewardJob::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| TakeGoodsJob | 0x7a060 | `` TakeGoodsJob::`scalar deleting destructor' `` | compiler-generated |
| TakeGoodsJob | 0x11e430 | `` `dynamic initializer for 'TakeGoodsJob::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| TakeGoodsJob | 0x11f140 | `` `dynamic atexit destructor for 'TakeGoodsJob::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| TencentUIC | 0x7ac30 | `tss_load_sdk` | C linkage name; the public gives no signature |
| TencentUIC | 0x7b0a0 | `_snprintf_s<1024>` | template instance |
| TransactionChannel | 0x7b0e0 | `` TransactionChannel::`scalar deleting destructor' `` | compiler-generated |
| TransactionChannel | 0x7b2b0 | `TransactionChannel::TSend` | nested type in signature |
| TransactionChannel | 0x7b3f0 | `` TransactionChannel::Manager::`scalar deleting destructor' `` | compiler-generated |
| TransactionChannel | 0x7b440 | `TransactionChannel::Manager::add` | nested type in signature |
| TransactionChannel | 0x7b4c0 | `TransactionChannel::Manager::remove` | nested type in signature |
| TransactionChannel | 0x7b540 | `TransactionChannel::Manager::Tick` | nested class member |
| TransactionChannel | 0x7b7e0 | `LobbyJobTransaction::Set` | nested type in signature |
| TryEnterGameWorldJob | 0x7b980 | `` TryEnterGameWorldJob::`scalar deleting destructor' `` | compiler-generated |
| TryEnterGameWorldJob | 0x11e480 | `` `dynamic initializer for 'TryEnterGameWorldJob::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
| TryEnterGameWorldJob | 0x11f180 | `` `dynamic atexit destructor for 'TryEnterGameWorldJob::_pool'' `` | no public symbol (compiler-generated initializer or atexit dtor, or folded) |
