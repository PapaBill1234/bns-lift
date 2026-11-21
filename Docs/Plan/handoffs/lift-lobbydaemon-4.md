# lift-lobbydaemon-4 handoff

Card: Character, GradeService and GameTimeSchedule (`Docs/Plan/cards/lift-lobbydaemon-4.md`), 49 functions.
Source: LobbyDaemon.exe and LobbyDaemon.pdb (2019 + PDB, VS2010 SP1). The scalar deleting dtor 0x4c0c0 is not in scope.

## Result

| Check | Result |
| --- | --- |
| `LIFT_BUILD_DIR=build-ld-4 tools/gate.sh` (after Character + GradeService, and at the end) | gate ok |
| VS2010 link of all 5 exes (`tools/vs2010/build.sh`) | ok (LobbyDaemon: 180 sources, 25 per-exe) |
| `LIFT_BUILD_DIR=build-ld-4 tools/parity.sh` (no `--accept`) | parity ok. All 5 exes: +0, no MATCH lost, no MATCH name gone. |
| Lifted functions | 37 (Character 21, GradeService 15, GameTimeSchedule 1) |
| Not done functions | 12 (GradeService 1, GameTimeSchedule 11) |

## MATCH comparison (`tools/parity.sh`, VS2010 /GL /LTCG)

| Exe | Baseline MATCH | Branch MATCH | New MATCH | MATCH -> DIFF | MATCH name gone |
| --- | --- | --- | --- | --- | --- |
| CacheGate | 456 | 456 (92.9 %) | 0 | 0 | 0 |
| LobbyGate | 658 | 658 (89.0 %) | 0 | 0 | 0 |
| SmartCouponDaemon | 630 | 630 (94.2 %) | 0 | 0 | 0 |
| PostOfficeDaemon | 694 | 694 (91.4 %) | 0 | 0 | 0 |
| LobbyDaemon | 49 | 49/2204 (2.2 %; 70 paired, 2134 only in original) | 0 | 0 | 0 |

Why LD gains 0: no live code calls the new functions yet. Their callers are `LIFT_STUB` bodies, so `/OPT:REF`
removes them. The built `LobbyDaemon.pdb` has only the `Character` types. It has no `Character::`, `GradeService::`,
`Grade::FetchGame`, `IDEV612_TimeTable::Initialize` or `_Linsert` function (checked with `grep -a`).
funcdiff cannot pair a function that is not in the exe.

## Lifted

| Module | RVA | PDB name |
| --- | --- | --- |
| Character | 0x30e90 | `Character::DB::Setup` |
| Character | 0x31040 | `Character::IsPlayable` |
| Character | 0x31090 | `Character::GetClientState` |
| Character | 0x310c0 | `Character::FetchCharacterInfo(FragmentPacket*)` |
| Character | 0x31380 | `Character::FetchCharacterInfo(Packet*, PacketComposer*)` |
| Character | 0x31550 | `Character::TryCreation` |
| Character | 0x319b0 | `Character::FinishCreation` |
| Character | 0x31c00 | `Character::CancelCreation` |
| Character | 0x31cf0 | `Character::TryDeletion` |
| Character | 0x31e60 | `Character::FinishDeletion` |
| Character | 0x31fb0 | `Character::CancelDeletion` |
| Character | 0x320a0 | `Character::TryRestore` |
| Character | 0x321e0 | `Character::FinishRestore` |
| Character | 0x322d0 | `Character::EndWaitDeletion` |
| Character | 0x32350 | `Character::UpgradeJumpingCharacterState` |
| Character | 0x32490 | `Character::SetLevel` |
| Character | 0x32510 | `Character::SetShowcase` |
| Character | 0x32630 | `Character::SetName` |
| Character | 0x326c0 | `Character::StartGameWorldPlay` |
| Character | 0x32800 | `Character::EndGameWorldPlay` |
| Character | 0x328f0 | `Character::SetSlotId` |
| GradeService | 0x53370 | `Grade::FetchGame` |
| GradeService | 0x53450 | `GradeService::GradeService()` |
| GradeService | 0x534d0 | `GradeService::GradeService(int)` |
| GradeService | 0x53550 | `GradeService::~GradeService` |
| GradeService | 0x535c0 | `GradeService::clearGradeList` |
| GradeService | 0x53670 | `GradeService::parseGradeChangedReason` |
| GradeService | 0x53750 | `GradeService::SetGradeLevel` |
| GradeService | 0x53800 | `GradeService::SetGradeList` |
| GradeService | 0x541f0 | `GradeService::ApplyChangedGradeLevel` |
| GradeService | 0x542e0 | `GradeService::IsActivated` |
| GradeService | 0x54390 | `GradeService::GetGrade` |
| GradeService | 0x54400 | `GradeService::FetchGradeLevel` |
| GradeService | 0x544d0 | `GradeService::FetchGameGradeList` |
| GradeService | 0x54680 | `std::_Tree<...<int, Grade*>...>::_Linsert` (STL; made by `_gradeList.insert(std::pair<int, Grade*>)` in `SetGradeList`) |
| GradeService | 0x547b0 | `std::_Tree_val<...>::_Buynode<std::pair<int, Grade*>>` (STL; same insert) |
| GameTimeSchedule | 0x4b8e0 | `IDEV612_TimeTable::Initialize` |

## Not done

| Module | RVA | PDB name | Reason |
| --- | --- | --- | --- |
| GradeService | 0x539d0 | `GradeService::ApplyChangedGrade` | Needs the `CliSessionGradeChangedMessage` / `LobbyMessage` layouts, `MileageManager` and the `LobbyDaemon::_instance` layout (later cards). |
| GameTimeSchedule | 0x4b9a0 | `GameTimeQueue::GameTimeQueue` | Inlines the `RefCntList` ctor. The `RefCntList` layout belongs to ld-3 (not on main). |
| GameTimeSchedule | 0x4b9e0 | `GameTimeQueue::~GameTimeQueue` | Inlines `RefCntList::Popfront` (ld-3). |
| GameTimeSchedule | 0x4ba80 | `GameTimeQueue::Pushback` | Calls `RefCntList::Pushback`; needs the `GameTimeQueue` layout (size 0x48 needs `RefCntList`, ld-3). |
| GameTimeSchedule | 0x4bb80 | `GameTimeQueue::Block` | Needs the `GameTimeQueue` layout (ld-3), `KickJob`, `LobbyJobManager` and `LobbyDaemon::_instance` (ld-15, ld-20). |
| GameTimeSchedule | 0x4bf90 | `GameTimeQueue::Release` | Reads `_index`, `_block`, `_lock`. Needs the `GameTimeQueue` layout (ld-3). |
| GameTimeSchedule | 0x4c020 | `GameTimeScheduler::GameTimeScheduler` | Needs `GameTimeQueue _queues[168]` (layout, ld-3). |
| GameTimeSchedule | 0x4c0e0 | `GameTimeScheduler::~GameTimeScheduler` | Same as 0x4c020. |
| GameTimeSchedule | 0x4c150 | `GameTimeScheduler::Start` | Calls `TimerQueue::Add` on `LobbyDaemon::_instance->GlobalTimerQueue` (ld-15, ld-20) and needs `_queues` (ld-3). |
| GameTimeSchedule | 0x4c2e0 | `GameTimeScheduler::HandleEvent` | Same as 0x4c150. |
| GameTimeSchedule | 0x4c390 | `GameTimeScheduler::Schedule` | Needs the `GameTimeScheduleNode` layout (`RefCntListNode` base, ld-3) and `CliSession::setScheduledEndTime`. |
| GameTimeSchedule | 0x4c6a0 | `GameTimeScheduler::Unschedule` | Calls `RefCntList::Remove` (ld-3). |

## Notes for the next waves

| Topic | Note |
| --- | --- |
| `Character.h` | PDB layout of `Character` (0xA0) with `DB`, the enums and offset asserts. |
| `GradeService.h` | PDB layout: `_revision`, `GradeLevel _gradeLevel`, `std::map<int, Grade*, std::less<int>, StlAllocator<..., 2>> _gradeList` at 0x18, `_initGradeLevel`, `_initGradeList`. `Grade` layout and `FetchGame`. |
| `CliSession.h` | `_gradeService` is again a `GradeService` member at 0x830. The ctors construct it in the initializer lists (`_gradeService()` in 0x32a40, `_gradeService(1)` in 0x33490). The placement new is gone. |
| `StsMsgGrade.h` (new) | `StsMsgLib` base message types and the 4 grade messages that `GradeService` reads, with size and offset asserts. VS2010 refuses `enum ECommand : int;` (C2059), so the full PDB enum is in the file. A later card can move these types to a shared StsMsgLib header. |
| `TryCreation` 0x31550 | LTCG removed the `char` argument of `LobbyDB::TryCharacterCreation`. The callee binds the constant 1, so the call passes 1 (`// LIFT:` + ❓). |
| `SetGradeList` 0x53800 | `// BUG:` when the key is already in `_gradeList`, the new `Grade` leaks. Kept. |
| GameTimeSchedule | After ld-3 lands, add the `GameTimeQueue` (0x48) and `GameTimeScheduler` (`Timer` base) layouts and lift the 11 stubs. The stub notes give the body outline. |
