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
| Mileage | `0x60be0` | `MileageInterimDepositTimer::Register` | 100.0 |
| Mileage | `0x60d00` | `MileageInterimDepositTimer::Tick` | 80.9 |
| Mileage | `0x614d0` | `swprintf_s<513>` | 100.0 |
| MembershipMileage | `0x5bff0` | `MembershipMileage::Accept` | 100.0 |
| MembershipMileage | `0x5c040` | `MembershipMileage::Initialize` | 0.0 |
| MembershipMileage | `0x5c300` | `MembershipMileage::Start` | 95.9 |
| MembershipMileage | `0x5ca20` | `MembershipMileage::GradeChanged` | 100.0 |
| MembershipMileage | `0x5cca0` | `MembershipMileageSession::start` | 100.0 |
| MembershipMileage | `0x5ce40` | `MembershipMileageSession::update` | 100.0 |
| MembershipMileage | `0x5cfd0` | `MembershipMileageSession::stop` | 100.0 |
| MembershipMileage | `0x5d0d0` | `std::vector<Section<__int64>,StlAllocator<Section<__int64>,2> >::_Reserve` | Excluded |
| MembershipMileage | `0x5d160` | `std::vector<Section<__int64>,StlAllocator<Section<__int64>,2> >::reserve` | Excluded |
| MembershipMileage | `0x5d240` | `Section<__int64>::Intersect<__int64,std::vector,StlAllocator<Section<__int64>,2> >` | 100.0 |
| MembershipMileage | `0x96440` | `std::_Uninit_move<Section<__int64> *,Section<__int64> *,StlAllocator<Section<__int64>,2>,Section<__int64> >` | Excluded |
| MembershipMileage | `0x9f540` | `std::vector<Section<__int64>,StlAllocator<Section<__int64>,2> >::vector<Section<__int64>,StlAllocator<Section<__int64>,2> >` | Excluded |

Total: 21 lifted, including four VS2010 STL bodies. Their decorated names are in the built PDB. The comparison tool excludes `std::` functions. It does not give them MATCH credit.

`MembershipMileage::Initialize` has a source body. VS2010 removes its tail because the base initializer still stops the process. `MileageInterimDepositTimer::Tick` still reaches the stub for `Node::Expire` when a node expires.

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

Total: 18 not done. The card does not count deleting destructors.

## Verification

The five checkpoints cover the 39 indexed functions with no overlap. They exclude four scalar deleting destructors. Checkpoint 5 did not verify four STL bodies. The VS2010 PDB contains all four original decorated public names. It also contains each card `/INCLUDE` name.

The full gate and parity checks exited zero and printed `gate ok` and `parity ok`. The source patch did not change during the checks.

| Exe | Baseline MATCH | Final MATCH | Gain |
| --- | ---: | ---: | ---: |
| CacheGate | 456 | 456 | 0 |
| LobbyGate | 658 | 658 | 0 |
| SmartCouponDaemon | 630 | 630 | 0 |
| PostOfficeDaemon | 694 | 694 | 0 |
| LobbyDaemon | 82 | 99 | +17 |

`vendor/zstd/src` is at `bb6eaf6495a0`. No baseline files changed.

## Codegen trials

The conditional placement new in `MembershipMileage::Start` (`0x5c300`) kept the null check. Its score stayed at 95.9. The final patch keeps the early return before construction.

No trial changed `MileageSession::MileageSession` (`0x606b0`). The cached body already agrees with the source store order. No trial changed `Tick` (`0x60d00`) or `Initialize` (`0x5c040`). Their scores are below 85, and their callees still have stubs.
