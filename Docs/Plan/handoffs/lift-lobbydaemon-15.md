# lift-lobbydaemon-15: LobbyDaemon part 1

Source: LobbyDaemon 2019 + PDB (VS2010 SP1). IDA was not opened.
The card has 33 functions (RVA `0x991c0` to `0x9b300`). The raw index has 4 more entries. They are compiler-generated
scalar deleting destructors (`0x99310`, `0x99340`, `0x99370`, `0x9a3a0`) and are not on the card.
30 functions are lifted. 3 are Not done.

## Result

| Item | Value |
| --- | --- |
| Lifted | 30 |
| Not done | 3 |
| `tools/gate.sh` (`LIFT_BUILD_DIR=build-ld-15`) | gate ok (after merging main bfb4c98) |
| `tools/parity.sh` (same build) | parity ok |
| LobbyDaemon MATCH | 219 -> 348 (+129) over main bfb4c98 |
| CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon MATCH | 456, 658, 630, 694 (+0 each, no MATCH lost) |

LobbyDaemon parity: 348/2204 = 15.8 %. Paired 464, mean score 95.6.
Baseline: Docs/Parity/baseline/LobbyDaemon.json = 219 MATCH. The baseline files are unchanged.

## Gate

The earlier run stopped at the binary check because main tracked 3 LegacyBin DLLs. Main now allows `tools/LegacyBin/`.
`tools/gate.sh` and `tools/parity.sh` both passed on the merge commit. `tools/gate_extra.sh` is not executable (mode 644). The gate skips it.

## Changes beyond the stub bodies

| File | Change |
| --- | --- |
| `CMakeLists.txt` | `src/Server/Shared/NPChannel2.cpp` added to `lift_lobbydaemon`. `Packet::FreeSize` (`0x29d0`) and `NPMsgHelper::LocaleHourToUTCTime` (`0x2be0`) are lifted in this file. `Compose` and `GetNextResetTimeUTC` call them. Without it the link fails. |
| `src/Server/LobbyDaemon/LobbyDaemon.cpp` | 19 `/INCLUDE` pragmas (dead-strip rule, see below). |
| `LobbyDaemon.h`, `LobbyConfig.h`, `CliSessionManager.h`, `GameWorld.h`, `Lock.h` | PDB layouts for the classes that the card functions use. |

The `/INCLUDE` pragmas show 3 signature errors in the first lift. The linker found them. They are fixed:

| Function | First lift | PDB signature |
| --- | --- | --- |
| `CoolDown::Start` | `static` | member (`QEAA`). IDA shows no `this`. The body reads `GCoolDown`. ❓ whether the source used `this`. |
| `LobbydReloadInvalidRestoreTimer::restoreInvalid` | public | private (`AEAA`) |
| `TimeBasedPlaySeasonSchedule::Data::GetNextResetTimeUTC` | `long long*` out parameters | `long long&` (`AEA_J`) |

## Lifted

Score = funcdiff score of the final build. MATCH = 100.0.

| RVA | Function | Score | MATCH |
| --- | --- | ---: | --- |
| `0x991c0` | `SystemEvent::~SystemEvent` | 100.0 | yes |
| `0x991f0` | `SystemEvent::Make` | 100.0 | yes |
| `0x99220` | `LobbyDaemon::ShortName` | 100.0 | yes |
| `0x99230` | `LobbyDaemon::Name` | 100.0 | yes |
| `0x99240` | `LobbyDaemon::ServiceName` | 100.0 | yes |
| `0x99250` | `LobbyDaemon::Descriptions` | 100.0 | yes |
| `0x99260` | `LobbyObjPoolMemAllocator::Alloc` | 100.0 | yes |
| `0x99380` | `BannedWordFilterMemoryAllocator::Alloc` | 100.0 | yes |
| `0x99390` | `BannedWordFilterMemoryAllocator::Realloc` | 100.0 | yes |
| `0x993b0` | `BannedWordFilterMemoryAllocator::Free` | 100.0 | yes |
| `0x993c0` | `GenerateClikey` | 100.0 | yes |
| `0x99410` | `GenerateJobid` | 100.0 | yes |
| `0x99460` | `GenerateLobbyTokenkey` | 100.0 | yes |
| `0x994b0` | `GameWorldReporterListener` | 86.3 | no |
| `0x995c0` | `CoolDown::HandleEvent` | 94.3 | no |
| `0x99880` | `CoolDown::Start` | 95.0 | no |
| `0x99990` | `LobbydReloadInvalidRestoreTimer::EventId` | 100.0 | yes |
| `0x999a0` | `LobbydReloadInvalidRestoreTimer::HandleEvent` | 100.0 | yes |
| `0x999b0` | `LobbydReloadInvalidRestoreTimer::restoreInvalid` | 93.3 | no |
| `0x99ac0` | `ServiceItems::Add` | 98.7 | no |
| `0x99d20` | `TimeBasedPlaySeasonSchedule::Data::GetNextResetTimeUTC` | 66.7 | no |
| `0x99df0` | `TimeBasedPlaySeasonSchedule::TimeBasedPlaySeasonSchedule` | 100.0 | yes |
| `0x99ef0` | `TimeBasedPlaySeasonSchedule::Compose` | 81.5 | no |
| `0x9a1b0` | `wmain` | 22.2 | no |
| `0x9a230` | `LobbyDaemon::LobbyDaemon` | 100.0 | yes |
| `0x9ae30` | `LobbyDaemon::PrintDependency` | 96.7 | no |
| `0x9af60` | `LobbyDaemon::GetTimerInterval` | 100.0 | yes |
| `0x9af70` | `LobbyDaemon::GetTimerMaxTime` | 100.0 | yes |
| `0x9af80` | `LobbyDaemon::SetTimeZoneBias` | 100.0 | yes |
| `0x9b0c0` | `LobbyDaemon::FailedEventObjectHandler` | 93.3 | no |

21 of the 30 card functions are MATCH. The other 109 new MATCH are shared BloodLib code and inline members that are paired for the first time (the 19 `/INCLUDE` functions pull their callees into the exe).

## Not done

| RVA | Function | Reason |
| --- | --- | --- |
| `0x9a3c0` | `LobbyDaemon::~LobbyDaemon` | Needs 46 job `ObjPool` statics (`X::_pool`). They belong to the job modules and have no definition yet. The link would break. |
| `0x9b1b0` | `LobbyDaemon::initLog` | Needs `LobbyConfig::_Def` (167 XML entries, LobbyConfig module card). No definition yet. The link would break. |
| `0x9b300` | `LobbyDaemon::initialize` | About 1720 pseudocode lines (index 1547 to 3265). Needs the same 46 job `ObjPool` statics (`CliSession::_pool`, `LogoutJob::_pool` and others). |

`wmain` is lifted but scores 22.2. It calls the `~LobbyDaemon` stub (`abort`), and our `LobbyDaemon` vftable ref is not in the original. It rises when `~LobbyDaemon` is lifted.

## Dead-strip

19 lifted functions have only `LIFT_STUB` callers. Each has `#pragma comment(linker, "/INCLUDE:<name>")` with a `// LIFT: keep until the caller is lifted (<rva>)` comment in `LobbyDaemon.cpp`.
The names are from the original PDB publics. All 19 are now in the built PDB.
The verify card removes them when the callers are lifted.

`SystemEvent::Make`, `LobbyObjPoolMemAllocator::Alloc`, `BannedWordFilterMemoryAllocator::{Alloc,Realloc,Free}`, `GenerateClikey`, `GenerateJobid`, `GenerateLobbyTokenkey`, `GameWorldReporterListener`, `CoolDown::{HandleEvent,Start}`, `LobbydReloadInvalidRestoreTimer::{EventId,HandleEvent,restoreInvalid}`, `ServiceItems::Add`, `TimeBasedPlaySeasonSchedule::Data::GetNextResetTimeUTC`, `TimeBasedPlaySeasonSchedule::Compose`, `LobbyDaemon::SetTimeZoneBias`, `LobbyDaemon::FailedEventObjectHandler`.

## Codegen trials

Rule: max 3 functions, 1 trial each. Only functions above 85 %.

| Function | Trial | Before | After |
| --- | --- | ---: | ---: |
| `ServiceItems::Add` | `delimiter[0] = L';'; delimiter[1] = 0;` instead of `wcscpy(delimiter, L";")` | 94.1 | 98.7 (kept) |
| `LobbyDaemon::FailedEventObjectHandler` | 3 separate `Log::Write` calls with lines 1140, 1148, 1153 instead of one shared tail | 91.7 | 93.3 (kept) |
| `CoolDown::HandleEvent`, `CoolDown::Start` | `GlobalTimerQueue->Add(...)` instead of `Daemon::AddTimer` | 94.3, 95.0 | no result. `TimerQueue::Add` is protected. Reverted. |

Not tried (for a later card):

| Function | Score | Idea |
| --- | ---: | --- |
| `FailedEventObjectHandler` | 93.3 | The original calls `GetLastError` before `EventId` in each branch. Use locals in this order inside the 3 branches. |
| `GetNextResetTimeUTC` | 66.7 | Ours has the const `-86400` (`0xfffffffffffeae80`). The original has none. Try `reset - 86400` as one `sub`, or a local. |
| `PrintDependency` | 96.7 | Ours has the consts 65 and 72. The original has none. The second `%d` has no argument (BUG). Check the register use in the disassembly. |
| `restoreInvalid` | 93.3 | The original loop end is `&CONFIG_FILENAME` (data order). Ours is `TextConsole::COLOR_TABLE`. Data layout, not source form. The original also has `if (next != nullptr)` before the unlink. |
| `GameWorldReporterListener` | 86.3 | The original calls `InfoGateChannelManager::Broadcast` (not lifted) and a second `Log::Write`. Retry after that module. |
| `Compose` | 81.5 | The original calls `Packet::Compose` (variadic). `Packet.h` has only `ComposeV`. |
| `ServiceItems::Add` (rest) | 98.7 | The original calls `std::_Sort` (`0x9f6e0`). The VS2010 headers here have no `std::sort`. Heap sort stands in. |

## Safety differences

- `LobbyObjPoolMemAllocator::Alloc`: the original does not check the `VirtualAlloc` result and leaks the old block (marked `// BUG:`). The lift keeps this logic. No guard was added.
- No session key or secret is logged.

## ❓ items

- `GenerateClikey`, `GenerateJobid`: the initial value of the seed is 0 (not verified).
- `LobbydReloadInvalidRestoreTimer::INVALID_REASON_STR`: the order of the 5 pointers is not checked in the binary.
- `TimeBasedPlaySeasonSchedule::Compose`: the argument order comes from the stack args only.
- `LobbyDaemon::setArgument`, `Free`: no LD RVA in the index (folded).
- `CoolDown::Start`: whether the source used `this` (see above).

## Build notes

- `vendor/zstd/src` was missing in this worktree. It was copied from the worktree `lift-lobbydaemon-12` (`bb6eaf64`, checked). The directory is git-ignored.
- Final run: `tools/parity.sh` output is in `build-ld-15/parity_final.log` (ignored directory).
