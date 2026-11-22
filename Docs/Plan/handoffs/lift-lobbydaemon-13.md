# lift-lobbydaemon-13: CliSession part 3, CliSessionManager

Source: LobbyDaemon 2019 + PDB (VS2010 SP1). The lift uses the indexed pseudocode cache and the PDB types. IDA was not opened.
The card has 56 functions: CliSession part 3 (49) and CliSessionManager (7). The deleting destructors are excluded.
25 functions are lifted. 31 functions are Not done.
The branch starts at main 75f0769 (ld-12 accepted). All counts are measured against the committed baseline of that commit.

## Result

| Item | Value |
| --- | --- |
| Lifted | 25 |
| Not done | 31 |
| Gate (`tools/gate.sh`, `LIFT_BUILD_DIR=build-ld-13`) | gate ok |
| Parity (`tools/parity.sh`, `VS2010_OUT=build-ld-13/vs2010`) | parity ok |
| LobbyDaemon MATCH | 195 -> 218 (+23) over main 75f0769. Paired 281 -> 305. |
| CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon MATCH | 456, 658, 630, 694 (+0 each, no MATCH lost, no MATCH name gone) |

| Group | New MATCH |
| --- | --- |
| Card, own name (17) | `CliSession::TimeoutStopPlay`, `CliSession::OnChargeStopRequested`, `CliSession::setRole`, `CliSession::setPcCafeCode`, `CliSession::setPcCafe`, `AnonymousLobbyGatePresence::IsEqual`, `AnonymousLobbyGatePresence::Kick`, `AnonymousLobbyGatePresence::GetKind`, `LobbyGatePresence::IsEqual`, `LobbyGatePresence::OnSet`, `LobbyGatePresence::OnUnset`, `GameWorldPresence::IsEqual`, `GameWorldPresence::OnSet`, `GameWorldPresence::OnUnset`, `GameWorldPresence::Kick`, `GameServiceLocation::ReserveStopPlay`, `GameServiceLocation::TimeoutStopPlay` |
| Card, folded name (2) | `LeaveGameWorldToken::GetKind` (`0x99980`, ICF with `LobbyGatePresence::GetKind`), `Aes128::GetType` (`0xe51f0`, ICF with `GameWorldPresence::GetKind`) |
| Shared (4) | New pair: `CliSessionTable::Insert_index_gate`, `CliSessionTable::Delete_index_gate`, `CliSessionTable::Insert_index_pcid`, `CliSessionTable::Delete_index_pcid`. The lifted presence callers keep them in the exe. |

## Lifted

| Module | RVA | Function | Funcdiff score | MATCH |
| --- | --- | --- | ---: | --- |
| CliSession | `0x39a70` | `CliSession::TimeoutStopPlay` | 100.0 | yes |
| CliSession | `0x39be0` | `CliSession::OnChargeStopRequested` | 100.0 | yes |
| CliSession | `0x39f70` | `CliSession::setRole` | 100.0 | yes |
| CliSession | `0x3a000` | `CliSession::setPcCafeCode` | 100.0 | yes |
| CliSession | `0x3a100` | `CliSession::setPcCafe` | 100.0 | yes |
| CliSession | `0x3a4a0` | `AnonymousLobbyGatePresence::IsEqual` | 100.0 | yes |
| CliSession | `0x3a650` | `AnonymousLobbyGatePresence::Close` | 66.7 | no (calls 0: the callee `LobbyGateChannel::SendCloseAnonymousSessionNotify` `0xbc9c0` is a `LIFT_STUB`) |
| CliSession | `0x3a670` | `AnonymousLobbyGatePresence::Kick` | 100.0 | yes |
| CliSession | `0x3a760` | `LobbyGatePresence::IsEqual` | 100.0 | yes |
| CliSession | `0x3a7d0` | `LobbyGatePresence::OnSet` | 100.0 | yes |
| CliSession | `0x3aa30` | `LobbyGatePresence::OnUnset` | 100.0 | yes |
| CliSession | `0x3adf0` | `GameWorldPresence::IsEqual` | 100.0 | yes |
| CliSession | `0x3ae90` | `GameWorldPresence::OnSet` | 100.0 | yes |
| CliSession | `0x3aff0` | `GameWorldPresence::OnUnset` | 100.0 | yes |
| CliSession | `0x3b120` | `GameWorldPresence::Kick` | 100.0 | yes |
| CliSession | `0x3bb60` | `GameServiceLocation::ReserveStopPlay` | 100.0 | yes |
| CliSession | `0x3bc80` | `GameServiceLocation::TimeoutStopPlay` | 100.0 | yes |
| CliSession | `0x5a0a0` | `GameServiceLocation::GetKind` | - | folded (ICF) with many `return 0` functions; funcdiff scores the address under another name that was already paired |
| CliSession | `0x99980` | `LobbyGatePresence::GetKind` | 100.0 | yes (funcdiff name `LeaveGameWorldToken::GetKind`, ICF) |
| CliSession | `0xe3ec0` | `AnonymousLobbyGatePresence::GetKind` | 100.0 | yes |
| CliSession | `0xe51f0` | `GameWorldPresence::GetKind` | 100.0 | yes (funcdiff name `Aes128::GetType`, ICF) |
| CliSession | `0x95fe0` | `std::vector<ContentBan,StlAllocator<ContentBan,2> >::reserve` | - | not scored (`std::`). Template instance from `CliSession::setContentBans`. In the built PDB. |
| CliSession | `0x96100` | `std::vector<ContentBan,StlAllocator<ContentBan,2> >::push_back` | - | not scored (`std::`). In the built PDB. |
| CliSession | `0x962a0` | `std::vector<ContentBan,StlAllocator<ContentBan,2> >::_Reserve` | - | not scored (`std::`). In the built PDB. |
| CliSession | `0x963f0` | `std::_Uninit_move<ContentBan*,ContentBan*,StlAllocator<ContentBan,2>,ContentBan>` | - | not scored (`std::`). In the built PDB. |

The lifted functions have no lifted caller yet. Each has a `#pragma comment(linker, "/INCLUDE:...")` with its PDB public name in
`CliSession.cpp` (21 pragmas, `// LIFT: keep until the caller is lifted`). The verify card removes them when the callers are lifted.

New PDB layouts in this card: `Role` enum, `Role::Set`, `Role::Reset`, `Authority::Merge` (inlined, `// LIFT:`), `GRoleAuthorityTable`
(.data `0x201d70`), `PcCafe` (abstract base), `AnonymousLobbyGatePresence` (0x18), `LobbyGatePresence` (0x18), `GameWorldPresence` (0x20),
`GameServiceLocation` (0x30), the inlined `GateNode` ctor, and the declaration of `CliSession::_pool`.

## Not done

| RVA | Function | Reason |
| --- | --- | --- |
| `0x39820` | `CliSession::ReserveStopPlay` | Needs `LobbyDaemon::_instance->GlobalTimerQueue` and `_config`. `LobbyDaemon.h` has no PDB layout (ld-15, ld-20). |
| `0x39cc0` | `CliSession::ApplyNewChargeItem` | Needs `LobbyDaemon::_instance->_gamedchmgr` (ld-15, ld-20). |
| `0x39e50` | `CliSession::NotifyChargeRemainTime` | Needs `LobbyDaemon::_instance->_gamedchmgr` (ld-15, ld-20). |
| `0x3a190` | `CliSession::onPcCafeChargeStart` | Needs `LobbyDaemon::_instance->_mileageManager` (ld-15, ld-20). |
| `0x3a2c0` | `CliSession::onPcCafeChargeStop` | Needs `LobbyDaemon::_instance->_mileageManager` (ld-15, ld-20). |
| `0x5a060` | `std::vector<LobbyService::DB*,StlAllocator<LobbyService::DB*,2> >::~vector` | Compiler-generated STL instance. No lifted caller makes it yet (the `LobbyService` users are stubs). Not in the built PDB. |
| `0x61490` | `std::vector<CliSession*,StlAllocator<CliSession*,2> >::~vector` | Compiler-generated STL instance. No lifted caller makes it yet (the `CliSessionTable` dtor is a stub). Not in the built PDB. |
| `0x3a3f0` | `AnonymousLobbyGatePresence::AnonymousLobbyGatePresence` | Calls `_lgate->addReferenceCount`. `LobbyGateChannel.h` has no `RefCntObject` base yet (other card). |
| `0x3a530` | `AnonymousLobbyGatePresence::OnSet` | Needs `LobbyGateChannel::_rawChannel`. `LobbyGateChannel.h` has no PDB base yet. |
| `0x3a600` | `AnonymousLobbyGatePresence::OnUnset` | Same as `0x3a530` (`_rawChannel->GetId`). |
| `0x3abc0` | `LobbyGatePresence::Close` | Needs `LobbyDaemon::_instance->_lgatechmgr` and the `RefCntObject` base of `LobbyGateChannel`. |
| `0x3ac20` | `LobbyGatePresence::Kick` | Same as `0x3abc0`. |
| `0x3aca0` | `LobbyGatePresence::NotifyChangedGrade` | Same as `0x3abc0`. |
| `0x3ad60` | `LobbyGatePresence::NotifyChangedGradeLevel` | Same as `0x3abc0`. |
| `0x3b0c0` | `GameWorldPresence::Close` | Needs `LobbyDaemon::_instance->_gamedchmgr`. `LobbyDaemon.h` has no PDB layout. |
| `0x3b1c0` | `GameWorldPresence::NotifyChangedGrade` | Needs `LobbyDaemon::_instance->_gamedchmgr`. |
| `0x3b290` | `GameWorldPresence::NotifyChangedGradeLevel` | Needs `LobbyDaemon::_instance->_gamedchmgr`. |
| `0x3b360` | `GameServiceLocation::~GameServiceLocation` | Needs `LobbyDaemon::_instance->GlobalTimerQueue`. |
| `0x3b3d0` | `GameServiceLocation::OnEnter` | Needs `LobbyDaemon::_instance->_gameWorldRegistry` and `_mileageManager`. |
| `0x3b540` | `GameServiceLocation::OnLeave` | Needs `LobbyDaemon::_instance->_gameWorldRegistry`, `GlobalTimerQueue` and `_mileageManager`. |
| `0x3b6f0` | `GameServiceLocation::Enter` | Needs `LobbyDaemon::_instance->_gameWorldRegistry`. |
| `0x3b9a0` | `GameServiceLocation::Leave` | Needs `LobbyDaemon::_instance->_gameWorldRegistry`. |
| `0x3bda0` | `GameServiceLocation::NotifyStopPlay` | Needs `LobbyDaemon::_instance->_gamedchmgr`. `LobbyDaemon.h` has no PDB layout. |
| `0x11dd50` | `dynamic initializer for 'CliSession::_pool'` | Needs a definition of `CliSession::_pool`. The LobbyDaemon ObjectPool module (`0x625d0` and up) is not lifted. `ObjectPool.cpp` is the SmartCouponDaemon form and is not in `lift_lobbydaemon` (ld-0 handoff). Original data: id 1, objsize `0x8d0`, desc `L"CliSession"` (.data `0x2042b0`). |
| `0x11ebc0` | `dynamic atexit destructor for 'CliSession::_pool'` | Same as `0x11dd50`. The build checkpoint defined the pool. The clang gate linked (CliSession.obj was not pulled from the static lib), but the VS2010 link failed: `ObjPool::ObjPool` and `ObjPool::~ObjPool` are unresolved. The definition is removed. |
| `0x3c080` | `InitCliSessionWnpTokenJob::GetDefinition` | Needs `InitCliSessionWnpTokenJob::_def` and the `LobbyJobDef` layout (InitCliSessionWnpTokenJob and LobbyJob modules are stubs). |
| `0x3c090` | `InitCliSessionWnpTokenJob::deallocate_me` | Needs the `CliSessionJob` and `RefCntObject` bases, the virtual dtor and the job `_pool`. The job hierarchy has no layout. |
| `0x3c140` | `CliSessionManager::InitSessionWnpToken` | Needs `LobbyJob` `_lock`, `_state`, `transit`, the `CliSessionJob` ctor, `InitSessionWnpTokenTaskParam` and the job `_pool`. Not declared in the header. |
| `0x3c780` | `CliSessionManager::StartSessionWnpToken` | Needs the `StartCliSessionWnpTokenJob` layout and `_pool`, `LobbyJob` `_state`/`transit` and `LobbyJobManager::remove`. Not declared in the header. |
| `0x3cbd0` | `CliSessionManager::OnCloseLobbyGateChannel` | Needs the `LogoutJob` layout, `_pool`, vftable and the `CliSessionJob` ctor. `CliSessionManager` has no `CliSessionTable` base yet. |
| `0x3cdd0` | `CliSessionManager::OnCloseGamedChannel` | Needs the `LogoutInGameWorldJob` layout, `_pool`, `_wid` and the `CliSessionJob` ctor. No `CliSessionTable` base. |

## Codegen trials

| Function | Score before | Try | Score after | Kept |
| --- | ---: | --- | ---: | --- |
| `CliSession::setRole` (`0x39f70`) | 93.3 | A19: `Authority::Merge` as four separate `|=` stores in place of the `for` loop | 93.3 | no (reverted; same code) |
| `CliSession::setRole` (`0x39f70`) | 93.3 | A8: read `roles[i]` once into `int const role` | 88.9 | no (reverted) |
| `CliSession::setRole` (`0x39f70`) | 93.3 | A8 + A11: `int const role` and a `long long` loop index | 88.9 | no (reverted) |
| `CliSession::setRole` (`0x39f70`) | 93.3 | A11 only: `long long i` loop index, `roles[i]` as before | 100.0 | yes (MATCH) |

Not tried:
- `AnonymousLobbyGatePresence::Close` (`0x3a650`, 66.7): the only gap is the stub callee `LobbyGateChannel::SendCloseAnonymousSessionNotify`
  (`0xbc9c0`, other card). No source form can fix it (ld-11 lesson).
- No other card function is DIFF besides `AnonymousLobbyGatePresence::Close`.
- The 31 Not done functions need layouts of other cards. They were not tried.

## Safety differences

This card adds no guard and removes no guard. The table lists the checked items.

| Function | Item | Result |
| --- | --- | --- |
| `CliSession::setPcCafeCode` (`0x3a000`) | No allocation-failure test after `AllocZero` | Original form. The original has no test. The other `AllocZero` callers in the lift have no test either. MATCH. |
| `LobbyGatePresence::OnSet` (`0x3a7d0`) | No allocation-failure test after `Alloc` | Original form. MATCH. |
| `CliSession::setRole` (`0x39f70`) | Bounds checks on `roles[i]` | Both checks are in the original (`role - 1 <= 6` in `Role::Set`, `role < 8` before the `GRoleAuthorityTable` read). Kept. |
| All lifted logs | Secrets in logs | No log prints a session key, a charge key or a secret. `cli-key` is the session lookup id. The original log text prints it, and main prints it in 38 other places. |

## Review notes

- The six build checkpoints cover the 56 card functions once each, with no overlap (checked against `index.tsv`).
- Checkpoint 5 marked `0x11ebc0` as lifted. The VS2010 link proved that wrong. It is Not done now (see the table).
- The worktree had no `vendor/zstd/src`. The VS2010 link of all five exes failed on `ZSTD_*` until it was copied from the main checkout
  (commit `bb6eaf64`). `vendor/zstd/src` is ignored by git.
- `PcCafe` has an empty class `operator delete` (`// LIFT:`). The original global `operator delete` (`0x32b50`) is empty, and
  `CliSession::setPcCafe` frees the memory with `Memory::_Manager[2]->Free` after `delete`.
- `friend class CliSession;` in `PcCafe` is a `// LIFT:` with `// ❓`: the PDB has no friend record.

## Verify (retry after the 429 stop)

| Check | Candidate | Result |
| --- | --- | --- |
| `tools/gate.sh` (`LIFT_BUILD_DIR=build-ld-13`) | repair 2 source (`CliSession.cpp`, `PcCafe.h`) | exit 0, `gate ok` |
| `tools/parity.sh` (`VS2010_OUT=build-ld-13/vs2010`, clean VS2010 dir) | repair 2 source | exit 0, `parity ok`. LobbyDaemon 195 -> 218 (+23), MATCH -> DIFF 0, name gone 0. Other exes +0. |

- No code finding. The verify commit changes only this handoff.
- `vendor/zstd` is not changed by the branch.

## Repair 2 (skeptic findings)

| Finding | Fix |
| --- | --- |
| `setRole` 93.3 DIFF | Loop index is `long long` (A11). Score 100.0, MATCH. Two A8 forms with a local lowered the score and were reverted. |
| Two STL dtors listed as Lifted | Moved to Not done (25 lifted, 31 Not done). The built PDB has no instance of them. |
| `PcCafe::GetType` | Now `virtual Type GetType() const = 0;` as in the PDB. |
| `changedPaths` | The claim counts `src include CMakeLists.txt cmake tools tests` only (docs not counted). |

Verify of the repair candidate: `tools/gate.sh` gate ok, `tools/parity.sh` parity ok on the committed source. LobbyDaemon MATCH 218/2204 (9.9 %).
