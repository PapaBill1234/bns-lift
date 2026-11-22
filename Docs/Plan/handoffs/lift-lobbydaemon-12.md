# lift-lobbydaemon-12: AuctionEscrow, stats, tick, misc

Source: LobbyDaemon 2019 + PDB (VS2010 SP1). The lift uses the indexed pseudocode cache and the PDB types. IDA was not opened.
The card has 26 functions (deleting destructors excluded). 23 are lifted. 3 are Not done.
The branch is rebased on main 94b02f6 (ld-8 and ld-10 are on main).

## Result

| Item | Value |
| --- | --- |
| Lifted | 23 |
| Not done | 3 |
| Gate (`tools/gate.sh`, `LIFT_BUILD_DIR=build-ld-12`) | gate ok |
| Parity (`tools/parity.sh`) | parity ok |
| LobbyDaemon MATCH | 97 -> 122 (+25) over main |
| CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon MATCH | 456, 658, 630, 694 (+0 each, no MATCH lost) |

The gain is 15 card functions and 10 shared functions that the new code reaches for the first time
(`RefCntList::Pushback`, `RefCntList::Remove`, `TimerQueue::Add`, `TimerQueue::addLongTermQueue`, `Timer::~Timer`, `Timer::EventId`,
`CriticalSection::~CriticalSection`, `CrashHandler::MakeCrash`, `Network::iocpHandle`, `Log::Write` (the error-code overload)).
New DIFF that is not on this card: `RefCntList::~RefCntList` 30.3 (lift-lobbydaemon-3), `Log::WriteV` 95.2, `operator delete` 83.3.

## Lifted

| Module | RVA | Function | Funcdiff score | MATCH |
| --- | --- | --- | ---: | --- |
| AuctionEscrow | `0x135e0` | `__printXml` | - | not scored (funcdiff `SKIP_NAME` skips `__` names; the function is in the built PDB) |
| AuctionEscrow | `0x13630` | `AuctionEscrow::GetDeliveryPostMessage` | 82.1 | no |
| AuctionEscrow | `0x14770` | `AuctionEscrow::GetRollbackEscrowPostMessage` | 94.9 | no |
| LobbyMessage | `0x2f9d0` | `LobbyMessage::~LobbyMessage` | 100.0 | yes |
| LobbyMessage | `0x2f9e0` | `LobbyMessage::Dispatch` | 100.0 | yes |
| LobbyMessage | `0x2fb60` | `CliSessionMileageInterimDepositMessage::Dispatch` | Needs the `PcCafeMileage` layout (`_slotId`, `Mileage` base). lift-lobbydaemon-5 owns `PcCafeMileage.h`; main has no layout yet. |
| LobbyStats | `0x5a5c0` | `sprintf_s<1024>` | CRT template. Only `LobbyStats::update` instantiates it, and `update` is Not done. It is not in the built PDB. |
| LobbyStats | `0x5a210` | `LobbyStats::update` | Needs the `LobbyDaemon`, `GameWorldRegistry`, `GameWorldCluster` and `GameWorld` layouts. lift-lobbydaemon-9 owns GameWorld. |

## Safety differences

| Function | Difference |
| --- | --- |
| `AuctionEscrow::GetDeliveryPostMessage` | Also rejects `bufsizeInWords <= 0` and `param->pDeliveryItem == nullptr`. The original checks only `param`, `buf` and `nDeliveryItemCount <= 0`, then reads `pDeliveryItem`. Every literal copy keeps the original space check. |
| `AuctionEscrow::GetRollbackEscrowPostMessage` | Also rejects `buf == nullptr` and `bufsizeInWords <= 0`. The original checks only `param`. |
| `TencentUIC::CheckNameFilter` | Also sets `user_message.callback_data` and `user_message.game_data` to `nullptr` (safety initialization). The original sets only the two length fields (`0x7ae80`). Funcdiff drops the constants, so MATCH 100 does not show this. |
| Both AuctionEscrow functions | Use the real `bufsizeInWords` for the end pointer. The original uses the LTCG constant 1025 from its caller. |

## Bugs kept

- `LobbyStats::Initialize` (`0x5a111`): the original reads `GetLastError` and not the return code from `SHCreateDirectoryExW`. Marked `// BUG:`.

## Follow-up for other cards

| Item | Owner | Note |
| --- | --- | --- |
| `CliSessionStopPcCafeChargeMessage::~CliSessionStopPcCafeChargeMessage` (`0x32b60`, `CliSession.cpp`) | ld-7 or the integration step | The body is empty in the HR. Replace the `LIFT_STUB` with an empty body. The `CliSessionMessage` base destructor releases the session reference. This card does not edit `CliSession.cpp`. |
| `CliSessionMileageInterimDepositMessage::Dispatch` (`0x2fb60`) | after ld-5 | Lift it when the `PcCafeMileage` layout is on main. |
