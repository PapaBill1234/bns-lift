# lift-lobbydaemon-24: LobbyGateChannel part 1, PostOffice

Source: LobbyDaemon 2019 + PDB (VS2010 SP1). The lift uses the indexed pseudocode cache, the PDB and disassembly. IDA was not opened.
The index lists 54 functions in the card range. The card counts 53 and excludes the scalar deleting destructor `PostOfficeSessionHandler::~PostOfficeSessionHandler` (`0x64130`, compiler generated).
Base: main 9d0ef81. All counts use its baseline (LobbyDaemon 436 MATCH).

## Result

| Item | Value |
| --- | --- |
| Lifted | 53 (52 with a body, 1 empty folded address, see Notes) |
| Not done | 0 |
| Gate (`tools/gate.sh`, `LIFT_BUILD_DIR=build-ld-24`) | gate ok |
| Parity (`tools/parity.sh`) | parity ok |
| LobbyDaemon MATCH, baseline (main) | 436 |
| LobbyDaemon MATCH, final | 521 (+85) |
| CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon MATCH | 456, 658, 630, 694 (+0 each, no MATCH lost) |

The +85 is 38 card functions and 47 shared functions. The shared functions are BloodLib code that the real link now keeps (`Session::*`, `Channel::*`,
`Connection::*`, `Port::*`, `SessionPool::*`, `PacketFormatIterator::*`, `StaticPageMemoryManager::*` and others). No MATCH turns into DIFF and none disappears.

## Lifted

| Module | RVA | Function | Funcdiff score | MATCH |
| --- | --- | --- | ---: | --- |
| LobbyGateChannel | `0xbbe90` | `LobbyGateChannel::SendInitSessionWithNPTokenOk` | 100.0 | yes |
| LobbyGateChannel | `0xbbfb0` | `LobbyGateChannel::SendInitSessionWithNPTokenFail` | 100.0 | yes |
| LobbyGateChannel | `0xbc080` | `LobbyGateChannel::SendInitSessionWithLobbyTokenOk` | 100.0 | yes |
| LobbyGateChannel | `0xbc150` | `LobbyGateChannel::SendInitSessionWithLobbyTokenFail` | 100.0 | yes |
| LobbyGateChannel | `0xbc220` | `LobbyGateChannel::SendStartSessionWithNPTokenOk` | 72.0 | no |
| LobbyGateChannel | `0xbc540` | `LobbyGateChannel::SendStartSessionWithNPTokenFail` | 100.0 | yes |
| LobbyGateChannel | `0xbc610` | `LobbyGateChannel::SendStartSessionWithLobbyTokenOk` | 65.1 | no |
| LobbyGateChannel | `0xbc8f0` | `LobbyGateChannel::SendStartSessionWithLobbyTokenFail` | 100.0 | yes |
| LobbyGateChannel | `0xbc9c0` | `LobbyGateChannel::SendCloseAnonymousSessionNotify` | 100.0 | yes |
| LobbyGateChannel | `0xbca80` | `LobbyGateChannel::SendCloseSessionNotify` | 100.0 | yes |
| LobbyGateChannel | `0xbcb40` | `LobbyGateChannel::SendKickNotify` | 100.0 | yes |
| LobbyGateChannel | `0xbcc10` | `LobbyGateChannel::SendGetCharacterInfoListFail` | 100.0 | yes |
| LobbyGateChannel | `0xbcce0` | `LobbyGateChannel::SendGetCharacterInfoFail` | 100.0 | yes |
| LobbyGateChannel | `0xbcdd0` | `LobbyGateChannel::SendCreateCharacterOk` | 100.0 | yes |
| LobbyGateChannel | `0xbcf40` | `LobbyGateChannel::SendCreateCharacterFail` | 100.0 | yes |
| LobbyGateChannel | `0xbd030` | `LobbyGateChannel::SendDeleteCharacterOk` | 100.0 | yes |
| LobbyGateChannel | `0xbd130` | `LobbyGateChannel::SendDeleteCharacterFail` | 100.0 | yes |
| LobbyGateChannel | `0xbd250` | `LobbyGateChannel::SendCancelWaitCharacterDeletionOk` | 100.0 | yes |
| LobbyGateChannel | `0xbd330` | `LobbyGateChannel::SendCancelWaitCharacterDeletionFail` | 100.0 | yes |
| LobbyGateChannel | `0xbd450` | `LobbyGateChannel::SendEndWaitCharacterDeletionNotify` | 100.0 | yes |
| LobbyGateChannel | `0xbd530` | `LobbyGateChannel::SendGetEnterWorldTokenFail` | 100.0 | yes |
| LobbyGateChannel | `0xbd600` | `LobbyGateChannel::SendGetEnterWorldTokenOk` | 100.0 | yes |
| LobbyGateChannel | `0xbd6e0` | `LobbyGateChannel::SendStartWaitNotify` | 84.8 | no |
| LobbyGateChannel | `0xbd9c0` | `LobbyGateChannel::SendGetWaitInfoOk` | 84.8 | no |
| LobbyGateChannel | `0xbdca0` | `LobbyGateChannel::SendGetWaitInfoFail` | 100.0 | yes |
| LobbyGateChannel | `0xbdd70` | `LobbyGateChannel::SendGiveupWaitOk` | 100.0 | yes |
| LobbyGateChannel | `0xbde30` | `LobbyGateChannel::SendGiveupWaitFail` | 100.0 | yes |
| LobbyGateChannel | `0xbdf00` | `LobbyGateChannel::SendEndWaitNotify` | 100.0 | yes |
| LobbyGateChannel | `0xbdfd0` | `LobbyGateChannel::SendGetChargeInfoOk` | 100.0 | yes |
| LobbyGateChannel | `0xbe120` | `LobbyGateChannel::SendGetChargeInfoFail` | 100.0 | yes |
| LobbyGateChannel | `0xbe1f0` | `LobbyGateChannel::SendRecoverCharacterOk` | 100.0 | yes |
| LobbyGateChannel | `0xbe2d0` | `LobbyGateChannel::SendRecoverCharacterFail` | 100.0 | yes |
| LobbyGateChannel | `0xbe3f0` | `LobbyGateChannel::SendBindCharacterSlotFail` | 100.0 | yes |
| LobbyGateChannel | `0xbe4f0` | `LobbyGateChannel::SendAccountInventoryNotify` | 100.0 | yes |
| LobbyGateChannel | `0xbe5d0` | `LobbyGateChannel::SendGetGoodsCountOk` | 100.0 | yes |
| LobbyGateChannel | `0xbe6a0` | `LobbyGateChannel::SendGetGoodsCountFail` | 100.0 | yes |
| LobbyGateChannel | `0xbe770` | `LobbyGateChannel::SendListGoodsOk` | 64.3 | no |
| LobbyGateChannel | `0xbe980` | `LobbyGateChannel::SendListGoodsFail` | 100.0 | yes |
| LobbyGateChannel | `0xbea50` | `LobbyGateChannel::SendTakeGoodsOk` | 81.6 | no |
| LobbyGateChannel | `0xbed00` | `LobbyGateChannel::SendTakeGoodsFail` | 100.0 | yes |
| LobbyGateChannel | `0xbedd0` | `LobbyGateChannel::SendListLobbyServiceItemInfoOk` | 79.0 | no |
| PostOfficeChannel | `0x639f0` | `PostOfficeChannel::Connect` | 97.0 | no |
| PostOfficeChannel | `0x63ba0` | `PostOfficeChannel::SendHelloReq` | 100.0 | yes |
| PostOfficeChannel | `0x63cb0` | `PostOfficeChannel::SendRegisterPostReq` | 80.9 | no |
| PostOfficeChannel | `0x64170` | `PostOfficeSessionHandler::OnAccept` | 100.0 | yes |
| PostOfficeChannel | `0x641d0` | `PostOfficeSessionHandler::OnConnect` | 100.0 | yes |
| PostOfficeChannel | `0x642e0` | `PostOfficeSessionHandler::OnClose` | 97.0 | no |
| PostOfficeChannel | `0x64420` | `PostOfficeSessionHandler::PacketHandler` | 97.6 | no |
| PostOfficeClientSideHandlerList | `0x32b50` | `operator delete (folded with Console::Flush)` | n/a | no |
| PostOfficePacketHandler | `0x646f0` | `HandlePostOfficeHelloOk` | 100.0 | yes |
| PostOfficePacketHandler | `0x64740` | `HandlePostOfficeHelloFail` | 93.3 | no |
| PostOfficePacketHandler | `0x647f0` | `HandlePostOfficeRegisterPostOk` | 38.1 | no |
| PostOfficePacketHandler | `0x64a20` | `HandlePostOfficeRegisterPostFail` | 36.7 | no |

## Not done

None. Two items need a note.

| RVA | Item | Reason |
| --- | --- | --- |
| `0x32b50` | `PostOfficeClientSideHandlerList` operator delete (ICF-folded with `Console::Flush`) | The body is one `ret`. It has no own function in the lift. `Console::Flush` and the empty `operator delete` bodies cover it. No score. |
| `0x64130` | `PostOfficeSessionHandler` scalar deleting destructor | Not in the card (compiler generated). |

## Checks of the saved build

- The 7 checkpoints list 53 rows. They cover the 53 card functions (index.tsv, RVA ranges of the card). No row repeats. No function is missing.
- The saved diff matches the checkpoints. It adds one stub file (see Notes).

## Notes

- The table `PostOfficePacketClientSideHandlerList` (data, `0x203770`, 7 entries) is the only data of the module `PostOfficeClientSideHandlerList`. The checkpoint missed it, and the VS2010 link failed
  (`LNK2001`). It is now defined in `PostOfficeClientSideHandlerList.cpp`: entries 2 to 6 = `HandlePostOfficeHelloOk`, `HandlePostOfficeHelloFail`, null, `HandlePostOfficeRegisterPostOk`, `HandlePostOfficeRegisterPostFail`.
  The type is `Daemon::PacketHandler[7]` (public name `?PostOfficePacketClientSideHandlerList@@3PAP6A_NPEBVSession@@PEBVPacket@@@ZA`).
- `Goods::Fetch` (`0x6010`, module `AccountInventory`) has no owner card and no skeleton file. `SendListGoodsOk` calls it, so the link failed. New file `src/Server/LobbyDaemon/AccountInventory.cpp`
  holds a `LIFT_STUB(0x6010)` body and is in `CMakeLists.txt`. The card that lifts the module `AccountInventory` (also `GoodsItem::Fetch` `0x5e60`) replaces the body and keeps the file.
- Dead-strip: 11 more functions got `#pragma comment(linker, "/INCLUDE:...")` (5 in `LobbyGateChannel.cpp`, 6 in `PostOfficeChannel.cpp`). The checkpoints had already added 36 in `LobbyGateChannel.cpp` and 1 in `PostOfficeChannel.cpp`.
  They were unpaired before. The verify card removes them when the callers are lifted.
- The worktree lacked the ignored `vendor/zstd/src`. All 5 VS2010 links failed on `ZSTD_*`. It was copied from the main checkout (`git rev-parse HEAD` = bb6eaf64). The first gate run had no zstd and still passed.
- `HandlePostOfficeRegisterPostOk` (38.1) and `HandlePostOfficeRegisterPostFail` (36.7): the original inlines `LobbyJobManager::find` and the job call. `LobbyJob` has no PDB layout in the repo yet, so
  the lift calls `LobbyJobManager::ExecuteW`. The behaviour is the same, the code is not. The verify card can revisit it when `LobbyJob` has its layout.
- `SendStartSessionWithNPTokenOk` (72.0) and `SendStartSessionWithLobbyTokenOk` (65.1) build a `FragmentPacket`. `SendListGoodsOk` (64.3), `SendTakeGoodsOk` (81.6), `SendListLobbyServiceItemInfoOk` (79.0),
  `SendStartWaitNotify` and `SendGetWaitInfoOk` (84.8) and `SendRegisterPostReq` (80.9, the original calls `Packet::Allocate`, ours `PacketBufferPool::allocate`) are all below 85. No codegen trial.

## Codegen trials (max 3, one each)

| Function | Score before | Form | Score after | Kept |
| --- | ---: | --- | ---: | --- |
| `PostOfficeChannel::Connect` and `PostOfficeSessionHandler::OnClose` (one macro) | 90.3 and 93.3 | Locals `lockPtr` and `invalidList` in `POST_OFFICE_SET_INVALID_INFO` (the original takes `&pipeConsole->_invalid` once before the loop, as in the pseudocode) | 97.0 and 97.0 | yes |
| `HandlePostOfficeHelloFail` | 93.3 | Decomposer fields in the pseudocode order, `reason = 0` in between | 93.3 | no |
| `PostOfficeSessionHandler::PacketHandler` | 97.6 | The invalid parameter block after the main path (the original has it last) | 97.6 | no |

Not tried:
- `HandlePostOfficeHelloFail`: second form (zero in a callee-saved register, as ld-18). One try only.
- `PostOfficeSessionHandler::PacketHandler`: the `Log::Write` order in the original follows a different block order. Other layout forms (A17, A20).
- `Connect` and `OnClose`: the last difference is a `L""` reference (`valueString`). Lessons section B says LTCG folds it. No change possible.
- All functions below 85 (see Notes).

## Safety differences

- No guard was removed or added. `PostOfficeSessionHandler::PacketHandler` keeps the null checks of the original.
- Card 24 adds the `PacketHandleEvent` constructor to `LobbyEvent.cpp` (card 6 module). It has a null check on `session` before `addReferenceCount`. The original inlines the constructor in 0x64420 after its own null check, so behaviour is the same (`// LIFT:` tag in the code).
- `HandlePostOfficeRegisterPostFail` (0x64a20): `param` is zero-initialised. The original leaves it uninitialised, and its decompose-fail log then prints uninitialised stack memory. The lift fixes this bug on purpose (`// LIFT:` tag in the code).
- `// BUG:` in `PostOfficeSessionHandler::PacketHandler`: the original does not check the packet copy for `nullptr` after a failed allocation. The lift keeps this (marked).
