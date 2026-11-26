# Handoff: lift-lobbydaemon-gap-17-gametimequeue

Date: 2026-11-26. Branch: `gap-17`. Base: `aab86d6` (gap-07 tip; the card named `d62e4f7`, but gap-07 moved).
Code tip: `4536f1f`. This handoff is in the next commit.

## Scope

| Part | Functions | NOREF result |
| --- | --- | --- |
| A: GameTimeSchedule | `GameTimeQueue` ctor, dtor, `Pushback`, `Release`, `Block`; `GameTimeScheduler` ctor, dtor, `Start`, `HandleEvent`, `Schedule`, `Unschedule` | 9 MATCH; `Block` 58.1, `Schedule` 86.1 |
| A: login | `StartCliSessionWnpTokenJob::loginAccount`, `KickJob` ctor | `loginAccount` DIFF; `KickJob` ctor MATCH |
| B: initialize callees | `LobbyConfig::Check`, `GameWorldRegistry::Setup`, `LoadRandomStoreInitializationSchedule`, `GetId128FromGuidString` | MATCH |
| B: initialize callees | `LobbyTokenDesk` ctor 96.3, `MileageManager::Initialize` 12.8, `GameWorldCluster::Setup` 94.4 | DIFF |
| C: initialize | `LobbyDaemon::initialize` | DIFF 67.9 (REF 71.5) |
| C: ObjPool | `ObjPool::Initialize`, `Finalize`, `Checkout`, `Checkin`; `ObjPoolTimer` dtor, `HandleEvent`, `Start`, `Add`, `process`; `LobbyObjPoolMemAllocator::Alloc` | MATCH |
| D: ContentsRuleConfig | `ContentsRuleConfigLoad::Load`, `UpdateAllVariable` MATCH; `LoadContentsRuleConfig` 91.4, `Dump` 99.2, `CheckMinMaxBoundary` 88.9 | mixed |

Scope additions:

| Item | Reason |
| --- | --- |
| `ObjectPoolLobbyDaemon.cpp/.h` (CMake source line) | It includes `ObjectPool.cpp` with the LobbyDaemon defines. |
| 46 `X::_pool` definitions | id 1, PDB objsize, desc from .data. The `AuctionBidJob` desc is "ActivateGradeJob", as in the original. |
| `GObjPoolMemAlloc`, `GObjPoolTimer` | Defined in `LobbyDaemon.cpp`. |
| `LobbyConfigDef.cpp` (CMake source line) | `LobbyConfig::_Def` table. |
| ContentsRuleConfig load path | Without it the link fails. |
| `/INCLUDE` for `GenerateClikey`, `GenerateJobid`, `GenerateLobbyTokenkey` (4536f1f) | `initialize` stores their address. The readers of the stored pointer are still stubs, so LTCG drops them. Without the pragma 3 MATCH are lost. |

All fail checks of the original `initialize` stay. PDB names only.

## Stub cut

`LIFT_STUB` is noreturn. Under /LTCG a stub call cuts all code after it.

| Build | First stub on the `initialize` path |
| --- | --- |
| Card alone | `LogoutJob::_vtbl` (0x97a70, pool #4) |
| Stack (gap-04/05/06/08) | `CreateCharacterJob` ctor and `_vtbl` (pool #6) |

Other stub callees on live paths:

| Function | Stub callees |
| --- | --- |
| `initialize` | about 30 job `_vtbl`, `DepositMileageJob` ctor, `MileageInterimDepositTimer` ctor 0x60a80, `MileageManager` dtor |
| `loginAccount` | `CliSession::login` 0x33f00, `loadDB` 0x349a0, `checkIntialUserName` 0xdc310 |
| `GameTimeQueue::Block` | `CliSession::ReserveStopPlay` 0x39820 |
| `GameTimeScheduler::Schedule` | `CliSession::setScheduledEndTime` 0x37890 |
| `MileageManager::Initialize` | `LobbyDB::LoadMileage`, `LoadMileagePolicy`, `LoadMileageFeverTime`, `Mileage::Initialize` |

## Checks

| Check | Result |
| --- | --- |
| `pilot.py gate` (8 IDs, REF a local REF build, NOREF a local NOREF build, `4536f1f`) | 5 of 8 clear; 3 `not_in_ready_pool` (`initialize`, `loginAccount`, `Block`); eligible pool 285 -> 293 |
| `buildonce gate` (fresh clone of `4536f1f`) | rc 0, parity ok |
| `strict.py` (5 exes, `cfg` level) | no FAIL |
| `proof.py --base aab86d6 --candidate 4536f1f` | verdict `review`: 0 reasons, 0 lost MATCH, 41 new MATCH, 23 credited, 18 review items (16 with cfg) |
| `proof.py` at `5a2684d` | `fail`: 3 `lost_match` (Generate*). Fixed in `4536f1f`. |

## MATCH

| Exe | Before (`aab86d6`) | After (`4536f1f`) | Stack before | Stack after |
| --- | --- | --- | --- | --- |
| CacheGate | 456 | 456 | 456 | 456 |
| LobbyGate | 658 | 658 | 658 | 658 |
| SmartCouponDaemon | 630 | 630 | 630 | 630 |
| PostOfficeDaemon | 694 | 694 | 694 | 694 |
| LobbyDaemon REF | 674 (841 paired) | 715 (914 paired) | 688 (862 paired) | 793 (975 paired) |
| LobbyDaemon NOREF | 979 (1226 paired) | 1007 (1256 paired) | not built | not built |

The stack changes only LobbyDaemon sources. The other exes are the same as the base gate.

## Stack branch (throwaway)

Local branch `stack-17`, tip `38544ad` (not pushed).
It merges gap-05 `d1a92d7`, gap-06 `4d5bcd8`, gap-08 `09dcab1`, gap-04 `96eca3f` and gap-17.

| Conflict | Fix in the stack |
| --- | --- |
| Union merge gives duplicate declarations (C2535) in job files | Job files taken from the stack base, then the gap-17 `_pool` definitions added (`e8f0b84`). |
| `GObjPoolTimer` defined twice (C2374) | One definition (`305824f`). |
| LNK2005 `ObjPoolTimer::Start` | gap-04 `LobbyObjectPool.cpp` dropped. |

When gap-04 lands, gap-17 needs the same two fixes: one `GObjPoolTimer` and no `LobbyObjectPool.cpp`.

## Open items

| Item | Note |
| --- | --- |
| Cert `jmp` patch at 0x9b454 in `initialize` | Not lifted as a patch. ❓ |
| Empty-string defaults in `LobbyConfig::_Def` | Taken from .data. ❓ |
| `LobbyErrorDesc` placeholder | ❓ |
| Login right = 1 in `loginAccount` | ❓ |
| Null check in `GameTimeScheduler::Schedule` | ❓ |
| TLS buffers in `GameWorldCluster::Setup` | No new `__declspec(thread)`. DIFF 94.4. ❓ |
| Reload flag rows in the config tables | ❓ |
| `vendor/zstd/src` | Git-ignored. Scratch clones must copy it in. |
| Merge | See "Rebase on main". |

## Rebase on main (2026-11-26)

The lander applied the net diff `aab86d6..4536f1f` 3-way on main `1262ef7`. It made 1 squash commit.

| Conflict | Fix |
| --- | --- |
| Job .h/.cpp: main already has the class body, `_def` and some `_pool` | Main side kept. The gap-17 `_pool` definition and include are added only where main has none. |
| `ExtendJumpingCharacterCreationQuotaJob.cpp`: 2 `_pool` twice | Main copy kept (gap-25). |
| `_vtbl()` in 6 jobs | gap-17 bodies added. Main ctors kept. The gap-17 `DepositMileageJob` stub ctor dropped. |
| `KickJob` ctor twice, `KickJob.h` | Main form kept (full `Demander` class). |
| `LobbyObjectPool.cpp` (gap-04) | Removed with its CMake line. `ObjectPoolLobbyDaemon.cpp` has all ObjPool bodies, also `ObjPoolTimer::Start`. |
| `GObjPoolTimer` twice | One definition in `LobbyDaemon.cpp`. |
| `#include "ObjectPool.h"` in 11 LobbyDaemon files | Now `ObjectPoolLobbyDaemon.h`. |
| `GameTimeSchedule.cpp` | gap-17 bodies kept (main had only `Unschedule`). |
| `Mileage.h` `_mileages` | PDB type `std::vector<Mileage*, StlAllocator<Mileage*, 2> >`. `CliSession.cpp` iterators follow. |
| Stale "`_pool` has no definition" comments (29) | Removed. |
