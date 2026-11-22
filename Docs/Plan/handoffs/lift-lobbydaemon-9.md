# lift-lobbydaemon-9: GameWorld, Fsd showcase, RuleSet

Source: LobbyDaemon 2019 + PDB, VS2010 SP1. The seven checkpoints cover all 46 card RVAs. No row overlaps another row. The count excludes five compiler-generated deleting destructors. The source covers 34 rows. This count includes three STL rows that the compiler owns. Twelve rows are Not done.

## Lifted

| RVA | Function | Funcdiff score | Status |
| --- | --- | ---: | --- |
| `0x2e0b0` | `DecomposeShowcaseFsd` | 92.2 | DIFF |
| `0x4c810` | `GameWorld::GetWid` | 100.0 | MATCH |
| `0x4c820` | `GameWorld::GameWorld` | 100.0 | MATCH |
| `0x4c880` | `GameWorld::Setup` | 96.3 | DIFF |
| `0x4ca30` | `GameWorld::Update` | 89.7 | DIFF |
| `0x4cc40` | `GameWorld::FetchWorldInfo` | 97.0 | DIFF |
| `0x4ce60` | `GameWorld::FetchWorldInfoForInfoGate` | 91.7 | DIFF |
| `0x4cf40` | `GameWorld::EnterUser` | 96.7 | DIFF |
| `0x4d120` | `GameWorld::PermitCharacterManagement` | 100.0 | MATCH |
| `0x4d390` | `GameWorldCluster::GameWorldCluster` | 100.0 | MATCH |
| `0x4d440` | `GameWorldCluster::~GameWorldCluster` | 100.0 | MATCH |
| `0x4dc70` | `GameWorldCluster::UpdateCounters` | 100.0 | MATCH |
| `0x4e310` | `GameWorldCluster::giveupWait` | 95.2 | DIFF |
| `0x4e4f0` | `GameWorldCluster::addGameWorld` | 94.4 | DIFF |
| `0x4e630` | `GameWorldRegistry::GameWorldRegistry` | 100.0 | MATCH |
| `0x4e6c0` | `GameWorldRegistry::~GameWorldRegistry` | 93.9 | DIFF |
| `0x4e8b0` | `GameWorldRegistry::Get` | 100.0 | MATCH |
| `0x4e900` | `GameWorldRegistry::EnumerateCluster` | 52.4 | DIFF |
| `0x4e9b0` | `GameWorldRegistry::FetchWorldInfoList` | 100.0 | MATCH |
| `0x4ead0` | `GameWorldRegistry::FetchWorldInfoListForInfoGate` | 100.0 | MATCH |
| `0x4ebf0` | `GameWorldRegistry::getGameWorldCluster` | 100.0 | MATCH |
| `0x4ec90` | `GameWorldRegistry::addGameWorldCluster` | 100.0 | MATCH |
| `0x4f940` | `GameWorldReporter::~GameWorldReporter` | 100.0 | MATCH |
| `0x4f9b0` | `GameWorldReporter::Initialize` | 96.3 | DIFF |
| `0x4fa30` | `GameWorldReporter::HandleEvent` | 100.0 | MATCH |
| `0x4fa80` | `GameWorldReporter::WriteReport` | 100.0 | MATCH |
| `0x4fc00` | `GameWorldReport::~GameWorldReport` | 100.0 | MATCH |
| `0x4fc70` | `GameWorldReport::Write` | 89.8 | DIFF |
| `0x4fdc0` | `GameWorldReport::GetPacket` | 100.0 | MATCH |
| `0x500f0` | `std::_Tree<std::_Tmap_traits<short, GameWorldCluster*, std::less<short>, StlAllocator<std::pair<short, GameWorldCluster*>, 2>, 0>>::_Linsert` | — | STL; no pair |
| `0x504d0` | `std::_Tree_val<std::_Tmap_traits<short, GameWorldCluster*, std::less<short>, StlAllocator<std::pair<short, GameWorldCluster*>, 2>, 0>>::_Buynode<std::pair<short, GameWorldCluster*>>` | — | STL; no pair |
| `0x96d20` | `std::map<short, GameWorldCluster*, std::less<short>, StlAllocator<std::pair<short, GameWorldCluster*>, 2>>::~map` | — | STL; no pair |
| `0x59ce0` | `SystemPerfMonitor::~SystemPerfMonitor` | 100.0 | MATCH |
| `0x59d60` | `SystemPerfMonitor::Initialize` | 100.0 | MATCH |

`GameWorld::EnterUser` calls the `enterUser` stub. The STL rows use the registry's standard map. They do not have separate hand-written bodies.

## Not done

| Module | RVA | Function | Reason |
| --- | --- | --- | --- |
| GameWorld | `0x4d510` | `GameWorldCluster::Setup` | Needs the LobbyDaemon singleton and the LobbyConfig performance flag. |
| GameWorld | `0x4d790` | `GameWorldCluster::Update` | Needs the LobbyDaemon session and job members. The end-wait job lacks its pool and base. |
| GameWorld | `0x4dd90` | `GameWorldCluster::enterUser` | Needs `WaitInfo` and the LobbyDaemon priority queue configuration. |
| GameWorld | `0x4e080` | `GameWorldCluster::leaveUser` | Needs the LobbyDaemon session and job members. The end-wait job lacks its pool and base. |
| GameWorld | `0x4e440` | `GameWorldCluster::getWaitInfo` | Needs `WaitInfo` and the grade priority queue configuration. |
| GameWorld | `0x4ed00` | `GameWorldRegistry::Setup` | Needs `GameWorldCluster::Setup` and both LobbyDB world loaders. |
| GameWorld | `0x4f330` | `GameWorldRegistry::Update` | Needs the LobbyDB world loaders and `GameWorldCluster::Setup` and `Update`. |
| GameWorld | `0x500c0` | `swprintf_s<128>` | The GameWorld call site is in the cluster setup stub. The performance monitor emits a matching template body. |
| LobbyPerfMonitor | `0x59e30` | `SystemPerfMonitor::Start` | Original calls `TimerQueue::Add` on `LobbyDaemon::_instance->GlobalTimerQueue` (rva `0x2095D0`). `Daemon::Instance` (rva `0x2095F8`) is another global with another timer queue. Needs the `LobbyDaemon::_instance` layout (ld-15, ld-20). Stub. |
| LobbyPerfMonitor | `0x59ee0` | `SystemPerfMonitor::HandleEvent` | Same reason as `0x59e30`. It also calls the `update` stub. Stub. |
| LobbyPerfMonitor | `0x59f40` | `SystemPerfMonitor::update` | Needs the LobbyDaemon registry and session manager members. The session manager lacks the session count. |
| RuleSet | `0x6bfc0` | `RuleSet::CheckName` | Needs the locale validators, `LobbyLocaleSet`, and `LobbyDaemon::FilterBannedWord`. |

## Codegen trials

| RVA | Trial | Before | Trial score | Result |
| --- | --- | ---: | ---: | --- |
| `0x4c880` | A2/A8: Expand the flag selections and read the log values in the cached order. | 96.3 | 91.7 | Revert. |
| `0x4cc40` | A2/A8: Use the direct capacity test, copy the cluster DB under lock, and use ordered tests for crowdness. | 97.0 | 90.9 | Revert. |
| `0x4e4f0` | A8: Give `push_back` a separate local pointer, as the cached body shows. | 94.4 | 94.4 | Revert. |
| `0x4fa80` | A16: `mem != nullptr ? ::new (mem) T : nullptr`, then the null test. | 90.0 | 90.0 | Same score. |
| `0x4fa80` | A16 + A17: A16 form and both error blocks before the success path. | 90.0 | 100.0 | Keep. MATCH. |
| `0x4cf40` | A8 + A17: error blocks first, two separate `TLobbyError` stores, read `characterCreationLimited` after `Log::Write`. | 88.0 | 96.7 | Keep. |
| `0x4fa30` | Remove the `/INCLUDE` for `GameWorldReporter::HandleEvent`. | 100.0 | 100.0 | Keep the removal. The destructor reaches the vtable. |

The `/INCLUDE` rule pairs `GameWorld::EnterUser`. The `/INCLUDE` lines for `SystemPerfMonitor::Start` and `GameWorldReporter::HandleEvent` are removed. `SystemPerfMonitor::Start` is a stub. `GameWorldReporter::HandleEvent` is reached through the kept destructor. No other codegen trial ran. The reporter setup keeps its PDB callback parameter. The Fsd and wait queue code keeps its input checks. The other DIFF rows did not get a trial after the trial limit.

## Safety differences

These guards are deliberate. Each guard can cause a missing MATCH or a branch difference. Keep each guard. Do not remove a guard to get a MATCH.

| RVA | Function | Original behaviour | Lift guard |
| --- | --- | --- | --- |
| `0x11a040` | `FsdDecomposer::GetString` | Calls `wcslen` on the data before it checks the data size. A string without a terminator reads past the buffer. | Searches for the terminator only inside the remaining data. Returns -1 if no terminator is found. |
| `0x2e0b0` | `FsdPointer::Initialize` (inline in `DecomposeShowcaseFsd`) | Compares the frame size as unsigned. A negative size passes. A negative format size is not rejected. | Rejects a negative frame size and a negative format size. |
| `0x4e310` | `WaitQueueList::Remove` (inline in `GameWorldCluster::giveupWait`) | Indexes the wait queue array with the queue type. It does not check the range. | Returns false if the type is not less than `MAX_WAIT_QUEUE_TYPE`. |
| `0x4fa80` | `GameWorldReporter::WriteReport` | Calls `GameWorldReport::Write` on the allocation also when the allocation fails. | Returns false if the allocation fails. |
| `0x4fc70` | `GameWorldReport::Write` | Constructs the `FragmentPacket` in the allocation without a null test. | Returns false if the allocation fails. |

Each guard has a `// BUG:` note at its source line. No lifted function logs a session key or another secret. The appearance index check in `DecomposeShowcaseFsd` is not a safety difference. The original has the same check.

The review asked to remove input guards. The repair did not remove them, because the safety rule keeps them.

## Review repair 2

| Finding | Action |
| --- | --- |
| `SystemPerfMonitor::Start` and `HandleEvent` used `Daemon::Instance`. The original uses `LobbyDaemon::_instance->GlobalTimerQueue`. | Both functions are LIFT_STUB again. They are in Not done. The `/INCLUDE` for `Start` is removed. |
| `GameWorldReporter::WriteReport` had no trial for A16. | A16 alone: 90.0. A16 with error blocks first: 100.0 MATCH. The allocation guard stays. |
| The `/INCLUDE` for `GameWorldReporter::HandleEvent` was not needed. | Removed. The function stays MATCH. |
| `GameWorld::EnterUser` read `characterCreationLimited` under the lock. | Read after `Log::Write`. Error blocks first. Score 88.0 to 96.7. |

The stub change drops `SystemPerfMonitor::Start` and `wmain` from the paired list, because the compiler folds identical stub bodies. This is not a MATCH loss.

## Checks

The full gate and parity runs on the final source exited zero. They printed `gate ok` and `parity ok`. No baseline MATCH was lost. The baseline comes from `main` at `562705035d7c9bb04be7992457dc78fde0e0a4f8`. The vendor zstd checkout remains at `bb6eaf64`. No live service test ran.

| Exe | Baseline MATCH | Final MATCH | Gain | Parity |
| --- | ---: | ---: | ---: | ---: |
| CacheGate | 456/491 | 456/491 | 0 | 92.9% |
| LobbyGate | 658/739 | 658/739 | 0 | 89.0% |
| SmartCouponDaemon | 630/669 | 630/669 | 0 | 94.2% |
| PostOfficeDaemon | 694/759 | 694/759 | 0 | 91.4% |
| LobbyDaemon | 82/2204 | 142/2204 | +60 | 6.4% |
