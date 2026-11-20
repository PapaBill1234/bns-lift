# lift-lobbydaemon-2 handoff

Card: CliSession part 1 (`Docs/Plan/cards/lift-lobbydaemon-2.md`), RVA 0x329d0 to 0x35eb0, 29 functions.
Source: LobbyDaemon.exe and LobbyDaemon.pdb (2019 + PDB, VS2010 SP1). The 3 compiler-generated scalar deleting dtors are not in scope.

## Result

| Check | Result |
| --- | --- |
| `LIFT_BUILD_DIR=build-ld-2 tools/gate.sh` | gate ok |
| Clang link of `LobbyDaemon.exe` | ok |
| VS2010 link of `LobbyDaemon.exe` (`tools/vs2010/build.sh LobbyDaemon`) | ok (180 sources, 24 per-exe) |
| `tools/parity.sh` (no `--accept`) | parity ok. All 5 exes: +0, no MATCH lost. |
| Lifted functions | 15 |
| Not done functions | 14 |

## MATCH comparison (`tools/parity.sh`, VS2010 /GL /LTCG)

| Exe | Baseline MATCH | Branch MATCH | New MATCH | MATCH -> DIFF | MATCH name gone |
| --- | --- | --- | --- | --- | --- |
| CacheGate | 456 | 456 (92.9 %) | 0 | 0 | 0 |
| LobbyGate | 658 | 658 (89.0 %) | 0 | 0 | 0 |
| SmartCouponDaemon | 630 | 630 (94.2 %) | 0 | 0 | 0 |
| PostOfficeDaemon | 694 | 694 (91.4 %) | 0 | 0 | 0 |
| LobbyDaemon | 49 | 49/2204 (2.2 %; 70 paired, 2134 only in original) | 0 | 0 | 0 |

Why LD gains 0: no live code calls the new functions yet. Their callers are `LIFT_STUB` bodies.
So `/OPT:REF` removes them. The built `LobbyDaemon.pdb` has no `?enter@CliSession`, `??0CliSession`,
`?setPresence@CliSession` or `??1GameAccount` public (checked with `grep -a -F`).
funcdiff cannot pair a function that is not in the exe. The lifts give MATCH when a later wave lifts a caller.

## Lifted

| RVA | PDB name |
| --- | --- |
| 0x329d0 | `ServiceLocation::~ServiceLocation` |
| 0x32a40 | `CliSession::CliSession()` |
| 0x32bb0 | `TimeBasedPlayInfoList::~TimeBasedPlayInfoList` |
| 0x32e20 | `CliSession::SetPlayInfoFromGame` |
| 0x33360 | `GameAccount::GameAccount` |
| 0x33450 | `GameAccount::~GameAccount` |
| 0x33490 | `CliSession::CliSession(unsigned __int64, CliSessionTable*)` |
| 0x33cc0 | `CliSession::finalize` (calls `cleanupCharge` and `logout`, which are still stubs) |
| 0x33d60 | `CliSession::npLogin` |
| 0x35730 | `CliSession::setPresence` |
| 0x35810 | `CliSession::closePresence` |
| 0x358e0 | `CliSession::kickPresence` |
| 0x359c0 | `CliSession::enter` |
| 0x35c10 | `CliSession::leave` |
| 0x35e20 | `CliSession::setChargeKey` |

## Notes for the next waves

| Topic | Note |
| --- | --- |
| `CliSession.h` | Rewritten with the PDB layouts: `CliSession` (0x8D0, offset asserts), `GameAccount` (0x198), `ServiceLocation` (0x10), `TimeBasedPlayInfoList`, `JumpingCharacterCreationQuota`, `Presence` (pure virtual slots 0-8) and the small value structs. |
| Presence classes | `GameServiceLocation`, `GameWorldPresence` and `LobbyGatePresence` have no bases yet. A later wave must add `Presence` / `ServiceLocation` as bases. |
| `operator delete(void*)` 0x32b50 | Empty in the original. ICF folds it with `Console::Flush`. The source pattern is `delete p; Memory::_Manager[2]->Free(p, file, line); p = nullptr;`. Define the empty `operator delete` BEFORE the presence and srvloc classes get bases. If not, `delete` + `Free` frees the memory 2 times. It is not in this card scope. |
| `StlMemory.h` | New `LIFT_EXE_LD` branch (`L"lobbydaemon"`). |
| `GradeService.h` | New `GradeLevel` struct and members (`_gradeList` is `std::map` with `StlAllocator<...,2>`; size 0x40). ld-4 also changes this file. Merge with care. |
| `AuctionDeliverJob.h` | `RefCntPoolObj` now derives from `RefCntObject` (size 0x18, static_assert). |
| `TLobbyError` | `__declspec(thread) LobbyError TLobbyError;` is defined in `CliSession.cpp`. The owner module is ❓. |
| `ID128_ID_ZERO` | Declared in `StringUtil.h`, defined in `StringUtil.cpp`. The owner module is ❓. |
| IDA | Not used. The HR pseudocode (`CliSession.c`) was enough. |

## Not done

| RVA | PDB name | Reason |
| --- | --- | --- |
| 0x329f0 | `CliSession::deallocate_me` | LD has no ObjPool. `ObjectPool.cpp` is SCD code and is linked in SCD only. |
| 0x32b60 | `CliSessionStopPcCafeChargeMessage::~CliSessionStopPcCafeChargeMessage` | `LobbyMessage.h` has no layout. |
| 0x32be0 | `TimeBasedPlayInfoList::ValidateDurations` | Layouts of `LobbyDaemon::_instance`, `TimeBasedPlaySeasonSchedule::Data` and `ContentsRuleConfig` are missing. |
| 0x32ed0 | `TimeBasedPlayInfoList::Compose` | Packet API layouts are missing. |
| 0x33070 | `TimeBasedPlayInfoList::Compose` (2nd overload) | Packet API layouts are missing. |
| 0x331e0 | `TimeBasedPlayInfoList::Decompose` | Packet API layouts are missing. |
| 0x336b0 | `CliSession::~CliSession` | Not lifted in this card (227 HR lines). It inlines the std::map member dtors and calls `TimerQueue::Remove`, `MileageSlot::~MileageSlot` and `LobbyDaemon::_instance`. Those layouts are missing. |
| 0x33f00 | `CliSession::login` | Not lifted in this card (374 HR lines). Not enough time in this card. |
| 0x34750 | `CliSession::logout` | Not lifted in this card (92 HR lines). It needs `LobbyDaemon::_instance`, `LobbyDB`, `GameTimeScheduler`, `AccountInventoryChannel` and `NPGameServiceChannel`. Those layouts are missing. |
| 0x349a0 | `CliSession::loadDB` | Not lifted in this card (730 HR lines). Not enough time in this card. |
| 0x35cf0 | `CliSession::getCharacter` | `Character.h` has no members (needs `_db.pcid`). |
| 0x35d30 | `CliSession::removeCharacter` | `Character.h` has no members (needs `_db.pcid`). |
| 0x35d90 | `CliSession::getPlayingCharacter` | `Character.h` has no members (needs `_db.pcid`). |
| 0x35eb0 | `CliSession::completeRequestChargeStop` | `LobbyDaemon::_npServchmgr` and StsMsg layouts are missing. |
