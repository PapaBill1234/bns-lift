# lift-lobbydaemon-10: Mileage part 2 and MembershipMileage

## Scope

Source: LobbyDaemon 2019 + PDB. Base: `56270503`. The lift uses the cached pseudocode and the PDB types, publics, and line maps. It does not use the build 381 packets.

## Lifted

| Module | RVA | PDB name | Score |
| --- | --- | --- | ---: |
| Mileage | `0x60660` | `MileageManager::Accept` | 100.0 |
| Mileage | `0x606b0` | `MileageSession::MileageSession` | 86.7 |
| Mileage | `0x608d0` | `MileageSlot::MileageSlot` | 100.0 |
| Mileage | `0x60950` | `MileageSlot::~MileageSlot` | 100.0 |
| Mileage | `0x60a80` | `MileageInterimDepositTimer::MileageInterimDepositTimer` | 100.0 |
| Mileage | `0x60b20` | `MileageInterimDepositTimer::~MileageInterimDepositTimer` | 100.0 |
| Mileage | `0x60d00` | `MileageInterimDepositTimer::Tick` | 80.9 |
| Mileage | `0x614d0` | `swprintf_s<513>` | 100.0 |
| MembershipMileage | `0x5bff0` | `MembershipMileage::Accept` | 100.0 |
| MembershipMileage | `0x5c040` | `MembershipMileage::Initialize` | 0.0 (lifted, not verified: callee `Mileage::Initialize` is a noreturn stub) |
| MembershipMileage | `0x5cca0` | `MembershipMileageSession::start` | 100.0 |
| MembershipMileage | `0x5ce40` | `MembershipMileageSession::update` | 100.0 |
| MembershipMileage | `0x5cfd0` | `MembershipMileageSession::stop` | 100.0 |
| MembershipMileage | `0x5d0d0` | `std::vector<Section<__int64>,StlAllocator<Section<__int64>,2> >::_Reserve` | Excluded |
| MembershipMileage | `0x5d160` | `std::vector<Section<__int64>,StlAllocator<Section<__int64>,2> >::reserve` | Excluded |
| MembershipMileage | `0x5d240` | `Section<__int64>::Intersect<__int64,std::vector,StlAllocator<Section<__int64>,2> >` | 100.0 |
| MembershipMileage | `0x96440` | `std::_Uninit_move<Section<__int64> *,Section<__int64> *,StlAllocator<Section<__int64>,2>,Section<__int64> >` | Excluded |

Total: 17 lifted, including three VS2010 STL bodies. Their decorated names are in the built PDB. The comparison tool excludes `std::` functions. It does not give them MATCH credit.

`MembershipMileage::Initialize` is lifted, not verified: callee `Mileage::Initialize` is a noreturn stub. VS2010 removes the tail of the body. `MileageInterimDepositTimer::Tick` still reaches the stub for `Node::Expire` (`0x60f20`) when a node expires.

The callers of `MileageSession::MileageSession` and the three `MembershipMileageSession` methods are now stubs. Each of these functions has a `/INCLUDE` pragma with a `// LIFT:` reason, so `/OPT:REF` keeps it.

## Not done

`FeverTimeSorter` below is `Mileage::Initialize::FeverTimeSorter`. `SortByStartTime` is `Mileage::FeverTime::Initiaize::SortByStartTime`. The STL methods need the sort calls and local comparators in those original owners. Do not move those types to a different scope or make copies of the STL bodies.

| Module | RVA | PDB name | Reason |
| --- | --- | --- | --- |
| Mileage | `0x60770` | `MileageSession::~MileageSession` | Needs `LobbyDaemon::_instance` and `_mileageInterimDepositTimer`. |
| Mileage | `0x60800` | `MileageSession::ReserveInterimDeposit` | Needs `LobbyDaemon::_instance` and `_mileageInterimDepositTimer`. |
| Mileage | `0x60f20` | `MileageInterimDepositTimer::Node::Expire` | Needs the daemon's session table and mileage manager. It also needs the message type with its base and reference-counted payload. |
| Mileage | `0x61060` | `MileageBatchRetryDeposit::Tick` | Needs the daemon's configuration and job manager. It also needs the deposit callback and job pool. |
| Mileage | `0x61500` | `std::_Sort<MileageFeverTimeInfo **,__int64,FeverTimeSorter>` | The `Mileage::Initialize` body is a stub. |
| Mileage | `0x61660` | `std::_Sort<Section<__int64> *,__int64,SortByStartTime>` | The `Mileage::FeverTime::Initiaize` body is not in this card. |
| Mileage | `0x617a0` | `std::_Unguarded_partition<MileageFeverTimeInfo **,FeverTimeSorter>` | The `Mileage::Initialize` body is a stub. |
| Mileage | `0x61990` | `std::_Unguarded_partition<Section<__int64> *,SortByStartTime>` | The `Mileage::FeverTime::Initiaize` body is not in this card. |
| Mileage | `0x61bc0` | `std::_Median<MileageFeverTimeInfo **,FeverTimeSorter>` | The `Mileage::Initialize` body is a stub. |
| Mileage | `0x61de0` | `std::_Make_heap<MileageFeverTimeInfo **,__int64,MileageFeverTimeInfo *,FeverTimeSorter>` | The `Mileage::Initialize` body is a stub. |
| Mileage | `0x61ee0` | `std::_Insertion_sort1<MileageFeverTimeInfo **,FeverTimeSorter,MileageFeverTimeInfo *>` | The `Mileage::Initialize` body is a stub. |
| Mileage | `0x61fc0` | `std::_Median<Section<__int64> *,SortByStartTime>` | The `Mileage::FeverTime::Initiaize` body is not in this card. |
| Mileage | `0x620a0` | `std::_Make_heap<Section<__int64> *,__int64,Section<__int64>,SortByStartTime>` | The `Mileage::FeverTime::Initiaize` body is not in this card. |
| Mileage | `0x62200` | `std::_Sort_heap<Section<__int64> *,SortByStartTime>` | The `Mileage::FeverTime::Initiaize` body is not in this card. |
| Mileage | `0x62350` | `std::_Insertion_sort1<Section<__int64> *,SortByStartTime,Section<__int64>>` | The `Mileage::FeverTime::Initiaize` body is not in this card. |
| Mileage | `0x62410` | `std::_Med3<Section<__int64> *,SortByStartTime>` | The `Mileage::FeverTime::Initiaize` body is not in this card. |
| Mileage | `0x62490` | `std::_Pop_heap_0<MileageFeverTimeInfo **,MileageFeverTimeInfo *,FeverTimeSorter>` | The `Mileage::Initialize` body is a stub. |
| MembershipMileage | `0x5c6c0` | `MembershipMileage::Stop` | Needs `Mileage::settle` (`0x5dd60`). The earlier card did not add a definition for it. |
| MembershipMileage | `0x5c300` | `MembershipMileage::Start` | Blocked. The original flow has no null check after the inline `MembershipMileageSession` construction. The repair removed the added check, but the permission classifier denied that edit. The restore needs explicit user approval. The body is a stub again. |
| MembershipMileage | `0x5ca20` | `MembershipMileage::GradeChanged` | Blocked. Same reason as `Start`: the lift added a null check that the original does not have. The guard removal needs explicit user approval. |
| Mileage | `0x60be0` | `MileageInterimDepositTimer::Register` | Blocked. Same reason: the lift added a null check that the original does not have. The guard removal needs explicit user approval. |
| MembershipMileage | `0x9f540` | `std::vector<Section<__int64>,StlAllocator<Section<__int64>,2> >::vector<Section<__int64>,StlAllocator<Section<__int64>,2> >` | Only the inline `MembershipMileageSession` ctor in `Start` emits it. It comes back when `Start` is lifted. |

Total: 22 not done. The card does not count deleting destructors.

## Header changes

The card overlaps with ld-12 in two shared headers. Each header now has one declaration that matches the ld-12 shape.

| Header | Change | Merge plan |
| --- | --- | --- |
| `src/Server/LobbyDaemon/LobbyTick.h` | `LobbyTick::Listener` uses the ld-12 members (`IsListen`, `SetListen`, pure `Tick`, `volatile bool _listen`). ld-10 adds only the inline ctor `Listener() : _listen(false) {}` (inline at `0x60a80`). The `static_assert(sizeof(LobbyTick::Listener) == 0x38)` is at the end of the file. | Merge ld-12 first. Then keep only the ctor line from ld-10. |
| `src/Server/LobbyDaemon/RefCntList.h` | `RefCntList::Popfront` is the same text as the ld-12 hunk (after `Remove`, `0x64da0`). | The hunks are identical. Git takes one copy. |

## Verification

The VS2010 PDB contains each card `/INCLUDE` name and the three STL decorated names that remain.

The full gate and parity checks ran on the committed source with `LIFT_BUILD_DIR=build-ld-10`. Both exited zero and printed `gate ok` and `parity ok`. There is no MATCH -> DIFF change and no MATCH name is gone.

| Exe | Baseline MATCH | Final MATCH | Gain |
| --- | ---: | ---: | ---: |
| CacheGate | 456 | 456 | 0 |
| LobbyGate | 658 | 658 | 0 |
| SmartCouponDaemon | 630 | 630 | 0 |
| PostOfficeDaemon | 694 | 694 | 0 |
| LobbyDaemon | 82 | 95 | +13 |

The earlier candidate had +17. The repair lost four MATCH entries:

| Function | Cause |
| --- | --- |
| `MembershipMileage::GradeChanged` | Stub again (blocked guard removal). |
| `MileageInterimDepositTimer::Register` | Stub again (blocked guard removal). |
| `GradeService::GetGrade` | Its only lifted caller was `Start`. LTCG removes it now. Its body is in another card's file. |
| `RefCntList::Pushback` | ❓ LTCG probably inlines it into `Tick`, which is now its only caller. |

`vendor/zstd/src` is at `bb6eaf6495a0`. No baseline files changed.

## Codegen trials

`MembershipMileage::Start` (`0x5c300`): the earlier candidate added a null check after the placement new. The original has no such check. This trial does not follow the original flow, so the repair drops it. The original-flow body is not in this commit (see Not done).

No trial changed `MileageSession::MileageSession` (`0x606b0`). It stays at 86.7. No trial changed `Tick` (`0x60d00`) or `Initialize` (`0x5c040`). Their scores are below 85, and their callees still have stubs.
