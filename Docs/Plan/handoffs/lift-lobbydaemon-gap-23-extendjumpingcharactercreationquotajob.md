# Handoff: lift-lobbydaemon-gap-23-extendjumpingcharactercreationquotajob

Date: 2026-11-26. Branch: `gap-23`. Base: `7b92217` (contains fix7 `e68e5d0`).
Code commits: `a8562ae`, `1e6d495`. This handoff is in the next commit.

## Scope

| Item | RVA | REF | NOREF |
| --- | --- | --- | --- |
| `ExtendJumpingCharacterCreationQuotaJob` bodies (ctor, dtor, `_vtbl`, `GetDefinition`, `init`, `work`, state handlers) | 0x2a… - 0x2c… | 13 MATCH, 10 DIFF | see gate |
| `LobbyLobbyGatePacketHandler` handler | 0xcac70 | DIFF 92.7 | not paired |
| `deallocate_me` | 0x2a310 | **Not done** (LIFT_STUB) | - |

`deallocate_me` needs `ObjPool::Checkin` 0x629a0. That body is not lifted.

Scope additions (needed for link or to make the chain live):

| Item | Source | Note |
| --- | --- | --- |
| `LobbyObjectPool.cpp` (ObjPool ctor, dtor, `Checkout` 0x628c0) | copy of the gap-26 file | one CMake source line |
| Header params `ExtendJumpingCharacterCreationQuotaWithAccountInventoryItemReqParam` (0x30), `UpgradeJumpingCharacterStateReqParam` (0x20) | gap-26 hunk, verbatim | static_asserts |
| `_pool` tail of the job .cpp | gap-26, verbatim | |
| `CliSessionJob.cpp`, `LobbyService.h`, `TransactionChannel.cpp/.h` | gap-12 patches | `git apply` from clone-12 |
| `CliSession::queryLobbyService(QueryExtendJumpingCharacterCreationQuotaService const&)` | PDB | inline; first entry with `serviceType == 6` |

Merge overlap: gap-26 (pool file, header hunk, `_pool` tail), gap-20 (the same CMake line), gap-12 (support patches). Take one copy of each at merge time.

## Handler 0xcac70

1. memset the param. `Decompose("hqqqi")`; on fail write log line 1754.
2. `Select` the session; on fail write log 1761 and send Fail 4.
3. `param.lgate = gate`. `_pool.Checkout(file, 1768)` and placement new.
4. `Register` fails: log 1771, Fail 2, `removeRef` 1773/1774.
5. Else `jobMgr->Execute(job, 30, &param)`, log 1778, `removeRef` 1780/1781.

## Checks

| Check | Result |
| --- | --- |
| REF linked build `main-build-OqveZqwG` (`1e6d495`) | LobbyDaemon 699 MATCH / 878 paired (base `main-build-qz5iflss`: 674 / 841) |
| NOREF linked build `noref-build-K2k6COTk` (`1e6d495`) | 988 / 1230 (base `g26/builds/noref-build-8ZLbV8tY`: 973 / 1205) |
| `pilot.py gate` (24 card IDs) | 15 clear; 9 not in the ready pool (0xcac70, 0x2a310, 0x2a6a0, 0x2b220, 0x2b640, 0x2bf80, 0x2c220, 0x2c8c0, 0x2cb60); 0 dropped. Out: a local gate file |
| `gate_fast.sh` (fresh clone of `1e6d495`) | rc 0, gate ok, parity ok |
| `strict.py` (5 exes, cfg) | no FAIL. Base: `g24/strict-base` (fix7 `e68e5d0`; same code as `7b92217`) |
| `proof.py --base 7b92217 --candidate 1e6d495` | verdict `review`; 0 reasons, 0 lost, 0 strict regress, 0 cfg regress; 12 auto credited, 13 review items (new MATCH without strict full proof). Out: a local proof file |

## MATCH

| Exe | Before | After | Lost |
| --- | --- | --- | --- |
| CacheGate | 456 | 456 | 0 |
| LobbyGate | 658 | 658 | 0 |
| SmartCouponDaemon | 630 | 630 | 0 |
| PostOfficeDaemon | 694 | 694 | 0 |
| LobbyDaemon (REF) | 674 | 699 (+25) | 0 |
| LobbyDaemon (NOREF) | 973 | 988 (+15) | 0 |

Predicted: REF +21.2, NOREF +19.2. Real: REF +25, NOREF +15.

New REF MATCH (25): CliSessionJob ctor, dtor and `dispatch_work`; 13 job functions; LobbyGateChannel `Send…Ok` and `Send…Fail` (the 2 unlocks); LobbyJob `dispatch_work`, `resume`, `~LobbyJob`; LobbyJobManager `Register`, `ResumeW`, `add`; LobbyJobTransaction `Expire`, `GetTid`; `TransactionChannel::Manager::remove`.

## REF DIFF (open)

| Function | Score | Cause |
| --- | --- | --- |
| `checkAIIOk` | 98.2 | register allocation ❓ |
| `extendJCCQ` | 95.8 | ❓ |
| `finCAII` / `finCAIIOk` | 97.0 / 96.9 | ❓ |
| `finServiceEntry` | 98.8 | ❓ |
| `init` | 88.3 | block order ❓ |
| `registerServiceEntry` | 93.7 | ❓ |
| `tryCAII` / `tryCAIIOk` | 97.0 / 97.1 | HIWORD/LOWORD register scheduling |
| dtor | 71.9 | LTCG inlines the CliSessionJob dtor. The original tail-jumps to `CliSessionJob::~CliSessionJob`. |
| handler 0xcac70 | 92.7 | ❓ |
| `ObjPool::Checkout` | 67.9 | gap-26 body; not this card |

## Fetch 0x6f000 (gap-15 reject)

- `ExtendJumpingCharacterCreationQuotaService::Fetch` is not paired in the base or the candidate (REF and NOREF).
- Its vftable folds (COMDAT) into `??_7LobbyService@@6B@`. The lifted Fetch calls `LobbyService::Fetch` first. That body is still `LIFT_STUB(0x6c330)` (`LobbyService.cpp` line 95). LTCG noreturn and ICF fold the body away.
- This card does not change the Fetch codegen. The xmm6 / frame 0x60 issue cannot be seen in these builds.
- The original loads `ID128_GUID_ZERO` into xmm6 after the null checks and before the FreeSize check.
- Fix: lift `LobbyService::Fetch` 0x6c330 first. Then check the xmm6 order again.

## Rules kept

- Logic from 2019 + PDB. PDB names only. Server checks kept.
- CMakeLists.txt: one source line added. No baseline change. No new `__declspec(thread)`. No inline asm or byte tricks. IDA not opened.

## Rebase on main (2026-11-26)

The lander applied the net diff `7b92217..3dcff2e` 3-way on main. It made 1 squash commit.

| Item | Fix |
| --- | --- |
| `LobbyObjectPool.cpp` and its CMake line (copy of gap-26) | Dropped. Main has one ObjPool module (`ObjectPoolLobbyDaemon.cpp`, gap-17). |
| `CliSessionJob.cpp`, `LobbyService.h`, `TransactionChannel.cpp/.h` (copies of gap-26, gap-20, gap-12) | Already on main. One copy kept. |
| `#include "ObjectPool.h"` | Main form `ObjectPoolLobbyDaemon.h` kept. The `_pool` definitions of main kept (one copy each). |
