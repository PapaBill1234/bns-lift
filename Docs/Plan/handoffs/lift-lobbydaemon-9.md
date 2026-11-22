# lift-lobbydaemon-9: GameWorld, Fsd showcase, RuleSet

Source: LobbyDaemon 2019 + PDB, VS2010 SP1. The seven checkpoints cover all 46 card RVAs. No row overlaps another row. The count excludes five compiler-generated deleting destructors. The source covers 36 rows. This count includes three STL rows that the compiler owns. Ten rows are Not done.

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
| `0x4cf40` | `GameWorld::EnterUser` | 88.0 | DIFF |
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
| `0x4fa80` | `GameWorldReporter::WriteReport` | 90.0 | DIFF |
| `0x4fc00` | `GameWorldReport::~GameWorldReport` | 100.0 | MATCH |
| `0x4fc70` | `GameWorldReport::Write` | 89.8 | DIFF |
| `0x4fdc0` | `GameWorldReport::GetPacket` | 100.0 | MATCH |
| `0x500f0` | `std::_Tree<std::_Tmap_traits<short, GameWorldCluster*, std::less<short>, StlAllocator<std::pair<short, GameWorldCluster*>, 2>, 0>>::_Linsert` | — | STL; no pair |
| `0x504d0` | `std::_Tree_val<std::_Tmap_traits<short, GameWorldCluster*, std::less<short>, StlAllocator<std::pair<short, GameWorldCluster*>, 2>, 0>>::_Buynode<std::pair<short, GameWorldCluster*>>` | — | STL; no pair |
| `0x96d20` | `std::map<short, GameWorldCluster*, std::less<short>, StlAllocator<std::pair<short, GameWorldCluster*>, 2>>::~map` | — | STL; no pair |
| `0x59ce0` | `SystemPerfMonitor::~SystemPerfMonitor` | 100.0 | MATCH |
| `0x59d60` | `SystemPerfMonitor::Initialize` | 100.0 | MATCH |
| `0x59e30` | `SystemPerfMonitor::Start` | 94.4 | DIFF |
| `0x59ee0` | `SystemPerfMonitor::HandleEvent` | 0.0 | DIFF |

`GameWorld::EnterUser` calls the `enterUser` stub. `SystemPerfMonitor::HandleEvent` calls the `update` stub. The STL rows use the registry's standard map. They do not have separate hand-written bodies.

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
| LobbyPerfMonitor | `0x59f40` | `SystemPerfMonitor::update` | Needs the LobbyDaemon registry and session manager members. The session manager lacks the session count. |
| RuleSet | `0x6bfc0` | `RuleSet::CheckName` | Needs the locale validators, `LobbyLocaleSet`, and `LobbyDaemon::FilterBannedWord`. |

## Codegen trials

| RVA | Trial | Before | Trial score | Result |
| --- | --- | ---: | ---: | --- |
| `0x4c880` | A2/A8: Expand the flag selections and read the log values in the cached order. | 96.3 | 91.7 | Revert. |
| `0x4cc40` | A2/A8: Use the direct capacity test, copy the cluster DB under lock, and use ordered tests for crowdness. | 97.0 | 90.9 | Revert. |
| `0x4e4f0` | A8: Give `push_back` a separate local pointer, as the cached body shows. | 94.4 | 94.4 | Revert. |

The `/INCLUDE` rule pairs `GameWorld::EnterUser` at 88.0. It does not change the function body. The final PDB contains all 23 names kept by the card. No other codegen trial ran. The reporter setup keeps its PDB callback parameter. The Fsd and wait queue code keeps its input checks. The other DIFF rows did not get a trial after the trial limit.

## Checks

The full gate and parity runs on the final source exited zero. They printed `gate ok` and `parity ok`. No baseline MATCH was lost. The baseline comes from `main` at `562705035d7c9bb04be7992457dc78fde0e0a4f8`. The vendor zstd checkout remains at `bb6eaf64`. No live service test ran.

| Exe | Baseline MATCH | Final MATCH | Gain | Parity |
| --- | ---: | ---: | ---: | ---: |
| CacheGate | 456/491 | 456/491 | 0 | 92.9% |
| LobbyGate | 658/739 | 658/739 | 0 | 89.0% |
| SmartCouponDaemon | 630/669 | 630/669 | 0 | 94.2% |
| PostOfficeDaemon | 694/759 | 694/759 | 0 | 91.4% |
| LobbyDaemon | 82/2204 | 141/2204 | +59 | 6.4% |
