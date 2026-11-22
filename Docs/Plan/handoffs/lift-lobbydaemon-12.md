# lift-lobbydaemon-12: AuctionEscrow, stats, tick, misc

Source: LobbyDaemon 2019 + PDB (VS2010 SP1). The lift uses the indexed pseudocode cache and the PDB types. IDA was not opened.
The card has 26 functions (deleting destructors excluded). 23 are lifted. 3 are Not done.

## Result

| Item | Value |
| --- | --- |
| Lifted | 23 |
| Not done | 3 |
| Gate (`tools/gate.sh`, `LIFT_BUILD_DIR=build-ld-12`) | gate ok |
| Parity (`tools/parity.sh`) | parity ok |
| LobbyDaemon MATCH | 82 -> 108 (+26) |
| CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon MATCH | 456, 658, 630, 694 (+0 each, no MATCH lost) |

The gain is 16 card functions and 10 shared functions that the new code reaches for the first time
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
| LobbyMessage | `0x2fa90` | `CliSessionStopPcCafeChargeMessage::Dispatch` (funcdiff name `CliSessionLeaveWorldMessage::Dispatch`, ICF) | 100.0 | yes |
| LobbyMessage | `0x2fad0` | `CliSessionStartPcCafeChargeMessage::Dispatch` (funcdiff name `CliSessionEnterWorldMessage::Dispatch`, ICF) | 100.0 | yes |
| LobbyStats | `0x5a0b0` | `LobbyStats::Initialize` | 93.3 | no |
| LobbyStats | `0x5a1d0` | `LobbyStats::HandleEvent` | 33.3 | no |
| LobbyStats | `0x5a590` | `swprintf_s<260>` | 100.0 | yes (CRT template, already in the baseline) |
| LobbyStats | `0x5a5c0` | `sprintf_s<1024>` | - | no (CRT template; its only caller `update` is Not done) |
| LobbyTick | `0x5a610` | `LobbyTick::~LobbyTick` | 100.0 | yes |
| LobbyTick | `0x5a6e0` | `LobbyTick::Add` | 100.0 | yes |
| LobbyTick | `0x5a770` | `LobbyTick::Remove` | 100.0 | yes |
| LobbyTick | `0x5a7f0` | `LobbyTick::HandleEvent` | 100.0 | yes |
| LobbyTick | `0x5a830` | `LobbyTick::process` | 100.0 | yes |
| LobbyTick | `0x5a900` | `LobbyTickEvent::LobbyTickEvent` | 100.0 | yes |
| LobbyTick | `0x5a9b0` | `LobbyTickEvent::~LobbyTickEvent` | 100.0 | yes |
| LobbyTick | `0x5aa20` | `LobbyTickEvent::HandleEvent` | 100.0 | yes |
| TencentUIC | `0x7ac30` | `tss_load_sdk` | 100.0 | yes |
| TencentUIC | `0x7ad30` | `TencentUIC::Initialize` | 100.0 | yes |
| TencentUIC | `0x7ae80` | `TencentUIC::CheckNameFilter` | 100.0 | yes |
| TencentUIC | `0x7b0a0` | `_snprintf_s<1024>` | 100.0 | yes |

Other changes:
- `CliSessionStopPcCafeChargeMessage::~CliSessionStopPcCafeChargeMessage` (`0x32b60`, CliSession.cpp) is empty now. The
  `CliSessionMessage` base destructor releases the session reference. It was a `LIFT_STUB` that the LobbyMessage vtable reaches.
- `RefCntList::Popfront` is a PDB inline method in `RefCntList.h`. `LobbyTick::~LobbyTick` uses it.
- `LobbyDB::TryAuctionEscrowRollbackOutParam` is declared in `LobbyDB.h`. `AuctionEscrow.h` defines the PDB layout.
- The functions with no lifted caller have `#pragma comment(linker, "/INCLUDE:...")` with `// LIFT:` (dead-strip rule).

## DIFF reasons

| Function | Score | Reason |
| --- | ---: | --- |
| `AuctionEscrow::GetDeliveryPostMessage` | 82.1 | LTCG folds `bufsizeInWords` to 1025 from the caller (not lifted). The original also duplicates the shared XML tails per event type. Safety guard on `bufsizeInWords`. |
| `AuctionEscrow::GetRollbackEscrowPostMessage` | 94.9 | Same LTCG constant (consts 0x9 vs 0x6/0xc). Safety guard on `buf` and `bufsizeInWords` moves the log block. |
| `LobbyStats::Initialize` | 93.3 | LTCG folds `fname` and `fext` to `L"lobby"` and `L"stats"` from the caller (not lifted). |
| `LobbyStats::HandleEvent` | 33.3 | It calls `LobbyStats::update`, which is still a `LIFT_STUB` (inlined abort). |

## Not done

| Module | RVA | Function | Reason |
| --- | --- | --- | --- |
| LobbyMessage | `0x2fb10` | `CliSessionGradeChangedMessage::Dispatch` | Needs `MembershipMileage::GradeChanged`. lift-lobbydaemon-10 (same wave) owns `MembershipMileage.h`. |
| LobbyMessage | `0x2fb60` | `CliSessionMileageInterimDepositMessage::Dispatch` | Needs `PcCafeMileage::_slotId` and the `MileageSlot` / `MileageSession` layouts. lift-lobbydaemon-10 owns `Mileage.h`; `PcCafeMileage.h` has no layout yet. |
| LobbyStats | `0x5a210` | `LobbyStats::update` | Needs the `LobbyDaemon`, `GameWorldRegistry`, `GameWorldCluster` and `GameWorld` layouts. lift-lobbydaemon-9 owns GameWorld. |

## Safety differences

| Function | Difference |
| --- | --- |
| `AuctionEscrow::GetDeliveryPostMessage` | Also rejects `bufsizeInWords <= 0`. The original checks only `param` and `buf`. Every literal copy keeps the original space check. |
| `AuctionEscrow::GetRollbackEscrowPostMessage` | Also rejects `buf == nullptr` and `bufsizeInWords <= 0`. The original checks only `param`. |
| Both AuctionEscrow functions | Use the real `bufsizeInWords` for the end pointer. The original uses the LTCG constant 1025 from its caller. |

## Bugs kept

- `LobbyStats::Initialize` (`0x5a111`): the original reads `GetLastError` and not the return code from `SHCreateDirectoryExW`. Marked `// BUG:`.
