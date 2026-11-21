# lift-lobbydaemon-6: LobbyService part 1 and LobbyEvent

Source: LobbyDaemon 2019 + PDB. The lift uses the indexed pseudocode cache and the PDB types. It covers 11 of 38 functions. It leaves 27 functions Not done. The count excludes four compiler-generated deleting destructors.

## Lifted

| Module | RVA | Function | Funcdiff score | Status |
| --- | --- | --- | ---: | --- |
| LobbyService | `0x6c4a0` | `CharacterCosmesisService::Setup` | 100.0 | MATCH |
| LobbyService | `0x6d180` | `AddSlotService::Setup` | 100.0 | MATCH |
| LobbyService | `0x6d3e0` | `AddSlotService::IsServiceTarget` | 66.7 | DIFF |
| LobbyService | `0x6deb0` | `RenameCharacterService::Setup` | 100.0 | MATCH |
| LobbyService | `0x6ec40` | `RenameUserService::Fetch` | 83.3 | DIFF |
| LobbyEvent | `0xbb7f0` | `SharedChannelPacketHandleEvent::SharedChannelPacketHandleEvent` | 100.0 | MATCH |
| LobbyEvent | `0xbb880` | `SharedChannelPacketHandleEvent::~SharedChannelPacketHandleEvent` | 100.0 | MATCH |
| LobbyEvent | `0xbb900` | `SharedChannelPacketHandleEvent::HandleEvent` | 100.0 | MATCH |
| LobbyEvent | `0xbb950` | `SharedChannelFragmentPacketHandleEvent::SharedChannelFragmentPacketHandleEvent` | 100.0 | MATCH |
| LobbyEvent | `0xbb9e0` | `SharedChannelFragmentPacketHandleEvent::~SharedChannelFragmentPacketHandleEvent` | 100.0 | MATCH |
| LobbyEvent | `0xbba60` | `SharedChannelFragmentPacketHandleEvent::HandleEvent` | 100.0 | MATCH |

The three setup functions reject null input before they change either record. The original wrote the base record before it checked the second input. The slot check rejects the zero ID and compares both parts of the ID. The rename-user fetch always rejects the request. It does not put the session identifier in logs or alerts.

The event constructors take one channel reference if a channel is present. The callbacks run only when the handler, channel, and payload are present. Each handler releases the event reference. Each destructor destroys its payload before it returns the storage to the allocator, then releases its channel reference. The PDB folds both `EventId` functions at `0x5a0a0`; the cached body returns zero.

## Not done

| Module | RVA | Function | Reason |
| --- | --- | --- | --- |
| LobbyService | `0x6c330` | `LobbyService::Fetch` | The caller's packet composer contract still needs verification. |
| LobbyService | `0x6c550` | `CharacterCosmesisService::Fetch` | Needs the base fetch and the character record layout. |
| LobbyService | `0x6c760` | `ChangeCharacterRaceService::IsServiceTarget` | Needs the character record and race-service layouts. |
| LobbyService | `0x6c780` | `CharacterCosmesisService::Start` | Needs the database start operation and session state checks. |
| LobbyService | `0x6c980` | `CharacterCosmesisService::ConsumeItemTried` | Needs the database state transition. |
| LobbyService | `0x6cb80` | `CharacterCosmesisService::TaskDone` | Needs the database state transition. |
| LobbyService | `0x6cd80` | `CharacterCosmesisService::ConsumeItemFinished` | Needs the database state transition. |
| LobbyService | `0x6cf80` | `CharacterCosmesisService::Finish` | Needs the database finish operation. |
| LobbyService | `0x6d240` | `AddSlotService::Fetch` | Needs the base fetch and the caller's packet composer contract. |
| LobbyService | `0x6d420` | `AddSlotService::Start` | Needs the database start operation and session state checks. |
| LobbyService | `0x6d5d0` | `AddSlotService::ConsumeItemTried` | Needs the database state transition. |
| LobbyService | `0x6d7d0` | `AddSlotService::TaskDone` | Needs the database state transition. |
| LobbyService | `0x6dab0` | `AddSlotService::ConsumeItemFinished` | Needs the database state transition. |
| LobbyService | `0x6dcb0` | `AddSlotService::Finish` | Needs the database finish operation. |
| LobbyService | `0x6df60` | `RenameCharacterService::Fetch` | Needs the base fetch and the character record layout. |
| LobbyService | `0x6e170` | `RenameCharacterService::IsServiceTarget` | Needs the character record layout. |
| LobbyService | `0x6e190` | `RenameCharacterService::Start` | Needs the database start operation and session state checks. |
| LobbyService | `0x6e440` | `RenameCharacterService::ConsumeItemTried` | Needs the database state transition. |
| LobbyService | `0x6e640` | `RenameCharacterService::TaskDone` | Needs the database state transition. |
| LobbyService | `0x6e840` | `RenameCharacterService::ConsumeItemFinished` | Needs the database state transition. |
| LobbyService | `0x6ea40` | `RenameCharacterService::Finish` | Needs the database finish operation. |
| LobbyService | `0x6ece0` | `RenameUserService::Start` | The cache does not settle the input checks or the call signature. |
| LobbyEvent | `0xbbad0` | `NPLobbyMessageHandleEvent::~NPLobbyMessageHandleEvent` | The transaction ownership and cleanup are not verified in this target. |
| LobbyEvent | `0xbbb60` | `NPLobbyMessageHandleEvent::HandleEvent` | The target does not have verified support for this channel's message release. |
| LobbyEvent | `0xbbbe0` | `PacketHandleEvent::~PacketHandleEvent` | The caller's allocation and session ownership are not verified. |
| LobbyEvent | `0xbbc60` | `PacketHandleEvent::HandleEvent` | The caller's event initialization and ownership are not verified. |
| LobbyEvent | `0xbbcf0` | `StopPlayTimerEvent::HandleEvent` | Needs the timer layout, session timeout, and kick-job dependencies. |

## Checks

The first parity build did not link. The retry worktree did not have zstd. The local retry uses the pinned `bb6eaf64` library source in an ignored directory. No baseline or progress file changed. No live service tests ran.

`tools/gate.sh` printed `gate ok` after each module. It also passed after the linker retention directives and pinned zstd source were in place.

A local service fixture passed. It checked valid setup, null input, no change on rejection, the zero ID, a mismatch in each ID half, and the rename-user fetch rejection. The fixture used fake log and alert sinks. The event bodies have build and parity checks only.

`tools/parity.sh` printed `parity ok`. The name sets of the four earlier servers did not change. LobbyDaemon lost no MATCH names.

| Server | Baseline MATCH | Retry MATCH | Lost names |
| --- | ---: | ---: | ---: |
| CacheGate | 456 | 456 | 0 |
| LobbyGate | 658 | 658 | 0 |
| SmartCouponDaemon | 630 | 630 | 0 |
| PostOfficeDaemon | 694 | 694 | 0 |
| LobbyDaemon | 49 | 82 | 0 |

Nine of the 33 new MATCH names are card functions. The other 24 do not count as lifted functions for this card. The three setup MATCH scores do not prove exact behavior on rejected inputs. The retry leaves both records unchanged on that path.
