# lift-lobbydaemon-20: LobbyDaemon part 2, BLDaemonInfo

Source: LobbyDaemon 2019 + PDB (VS2010 SP1). The lift uses the indexed pseudocode cache and the PDB publics. IDA was not opened.
The index lists 30 functions in scope (21 `LobbyDaemon`, 9 `BLDaemonInfo`), as the card says. 24 are lifted. 6 are Not done.
The build ran in 5 checkpoints (`build-ld-20/checkpoint-1.tsv` to `checkpoint-5.tsv`). The verify step checked that the rows cover all 30 RVAs once.

Base: main 9d0ef81. Baseline: `Docs/Parity/baseline/LobbyDaemon.json` (LobbyDaemon 436 MATCH).

## Result

| Item | Value |
| --- | --- |
| Lifted | 24 |
| Not done | 6 |
| Gate (`tools/gate.sh`, `LIFT_BUILD_DIR=build-ld-20`) | gate ok |
| Parity (`tools/parity.sh`, `VS2010_OUT=build-ld-20/vs2010`) | parity ok |
| LobbyDaemon MATCH | 436 -> 464 (+28) over main 9d0ef81 |
| CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon MATCH | 456, 658, 630, 694 (+0 each, no MATCH lost) |

The gain is 11 card functions and 17 shared functions. No MATCH function turns into DIFF or disappears.

New shared MATCH (17): `BannedWordFilterLib::FilterName`, `StrNormalize`, `FragmentPacketConcatenater::AllocSize`, `Clear`, `Destroy`, `check`,
`~FragmentPacketConcatenater`, `PacketConcatenateBuffer::Add`, `Clear`, `copy`, `~PacketConcatenateBuffer`, `PacketFormatIterator::CurrentFormat`,
`Forward`, `Rewind`, `skipRepeatFormat`, `RepeatPacketDecomposer::Reset`, `Session::SetPacketConcatenater`.
(`ConstFilterName` is now paired too: DIFF 97.4. It belongs to wave 1.)

## Lifted

| Module | RVA | Function | Funcdiff score | MATCH |
| --- | --- | --- | ---: | --- |
| LobbyDaemon | `0x9dc50` | `RawPacketBufferHandler::~RawPacketBufferHandler` | unpaired | no (1) |
| LobbyDaemon | `0x9ef40` | `LobbyDaemon::cooldown` | 100.0 | yes |
| LobbyDaemon | `0x9f240` | `LobbyDaemon::FilterBannedWord` | 100.0 | yes |
| LobbyDaemon | `0x9f340` | `LobbyDaemon::CheckServiceItemDataId` | 100.0 | yes |
| LobbyDaemon | `0x9f3c0` | `LobbyDaemon::GetAddressStringWForLogs` | 100.0 | yes |
| LobbyDaemon | `0x9f3f0` | `ConcatenatePacket` | 100.0 | yes |
| LobbyDaemon | `0x9f560` | `std::vector<unsigned int,StlAllocator<unsigned int,2> >::_Reserve` | skipped (2) | - |
| LobbyDaemon | `0x9f5f0` | `std::vector<unsigned int,StlAllocator<unsigned int,2> >::reserve` | skipped (2) | - |
| LobbyDaemon | `0x9f6e0` | `std::_Sort<unsigned int *,__int64>` | skipped (2) | - |
| LobbyDaemon | `0x9f7f0` | `std::_Unguarded_partition<unsigned int *>` | skipped (2) | - |
| LobbyDaemon | `0x9f980` | `std::_Median<unsigned int *>` | skipped (2) | - |
| LobbyDaemon | `0x9fae0` | `std::_Make_heap<unsigned int *,__int64,unsigned int>` | skipped (2) | - |
| LobbyDaemon | `0x9fbc0` | `std::_Sort_heap<unsigned int *>` | skipped (2) | - |
| LobbyDaemon | `0x9fcb0` | `std::_Insertion_sort1<unsigned int *,unsigned int>` | skipped (2) | - |
| LobbyDaemon | `0x9fd70` | `std::_Uninit_move<unsigned int *,unsigned int *,StlAllocator<unsigned int,2>,unsigned int>` | skipped (2) | - |
| BLDaemonInfo | `0x403c0` | `BLDaemonInfoTable::BLDaemonInfoTable` | 100.0 | yes |
| BLDaemonInfo | `0x40490` | `BLDaemonInfoTable::~BLDaemonInfoTable` | 100.0 | yes |
| BLDaemonInfo | `0x40510` | `BLDaemonInfoTable::load` | 70.6 | no |
| BLDaemonInfo | `0x40e30` | `BLDaemonInfoTable::add` | 100.0 | yes |
| BLDaemonInfo | `0x40f30` | `BLDaemonInfoTable::Load` | 100.0 | yes |
| BLDaemonInfo | `0x41090` | `BLDaemonInfoTable::Update` | 100.0 | yes |
| BLDaemonInfo | `0x41210` | `BLDaemonInfoTable::Find` | 100.0 | yes |
| BLDaemonInfo | `0x412d0` | `BLDaemonInfoTable::Clear` | 57.8 | no |
| BLDaemonInfo | `0x416f0` | `std::_Tree<...BLDaemonID...>::_Linsert` | skipped (2) | - |

(1) Compiler-generated destructor (A18). Nothing in the build uses `RawPacketBufferHandler` yet, so the linker drops the whole class.
An `/INCLUDE` cannot keep an implicit inline destructor. It pairs when its user (`initNetwork`, Not done) is lifted.

(2) VS2010 STL template instances. `funcdiff.py` skips `std::` names (`SKIP_NAME`). They come from `ServiceItems::Add` (`std::sort`,
`push_back`) and `BLDaemonInfoTable::add` (`_daemons.insert`).

## Codegen trials (3 functions, 1 trial each)

| Function | Before | Form | After |
| --- | ---: | --- | ---: |
| `BLDaemonInfoTable::add` | 95.2 | A15: insert `std::pair<BLDaemonID, BLDaemonInfo*>(id, daemon)`, not `value_type` | 100.0 |
| `LobbyDaemon::cooldown` | 97.8 | A27: `GCoolDown = ::new (Alloc(...)) CoolDown();` | 100.0 |
| `LobbyDaemon::CheckServiceItemDataId` | 83.3 | `(unsigned)type > SERVICEITEMTYPE_RENAME_CHARACTER_BY_SYSTEM` (form of `ServiceItems::Add`) | 100.0 |

The `add` trial also repaired a regression: the `value_type` insert made `CliSessionTable::Insert_index_pcid` DIFF (100 -> 93.3) through
`/OPT:ICF`. After the trial it is MATCH again.

Not tried (trial limit, and both are below 85):

| Function | Score | Cause |
| --- | ---: | --- |
| `BLDaemonInfoTable::load` (`0x40510`) | 70.6 | The original interleaves the 5 inlined element blocks (`_wcsicmp`, alloc, 3 `Attribute` calls, log). Ours groups the `_wcsicmp` tests first. A next try: write the 5 element blocks out in place (no `ReadDaemonElement` helper, A2), or `static __forceinline` (A10). |
| `BLDaemonInfoTable::Clear` (`0x412d0`) | 57.8 | The original calls `_Tree::clear` out of line. Ours inlines `clear` into `_Erase`. The STL header form decides this. |

## Dead-strip pragmas

The callers of these functions are still `LIFT_STUB` bodies. Each has `#pragma comment(linker, "/INCLUDE:...")` with a `// LIFT:` comment.
The verify card removes them when the callers are lifted.

| RVA | Decorated name | File |
| --- | --- | --- |
| `0x403c0` | `??0BLDaemonInfoTable@@QEAA@XZ` | `BLDaemonInfo.cpp` |
| `0x40490` | `??1BLDaemonInfoTable@@QEAA@XZ` | `BLDaemonInfo.cpp` |
| `0x40f30` | `?Load@BLDaemonInfoTable@@QEAA_NPEB_W@Z` | `BLDaemonInfo.cpp` |
| `0x41090` | `?Update@BLDaemonInfoTable@@QEAAXPEB_W@Z` | `BLDaemonInfo.cpp` |
| `0x41210` | `?Find@BLDaemonInfoTable@@QEBAPEBUBLDaemonInfo@@AEBUBLDaemonID@@@Z` | `BLDaemonInfo.cpp` |
| `0x412d0` | `?Clear@BLDaemonInfoTable@@QEAAXXZ` | `BLDaemonInfo.cpp` |
| `0x9f240` | `?FilterBannedWord@LobbyDaemon@@QEAA?AW4BannedWordFilterResult@1@PEB_W@Z` | `LobbyDaemon.cpp` |
| `0x9f340` | `?CheckServiceItemDataId@LobbyDaemon@@QEAA_NW4ServiceItemType@1@I@Z` | `LobbyDaemon.cpp` |
| `0x9f3c0` | `?GetAddressStringWForLogs@LobbyDaemon@@SAPEB_WK@Z` | `LobbyDaemon.cpp` (the lifted caller in `Character.cpp` is dead-stripped too) |

`load` and `add` need no pragma: `Load` and `Update` reach them.

## Not done

| RVA | Function | Reason |
| --- | --- | --- |
| `0x9d520` | `LobbyDaemon::initNetwork` | Needs PDB layouts that main does not have: `AccountInventorySessionHandler`, `PostOfficeSessionHandler` (`SessionHandler` base, 0x30), `ManageSessionHandler` (0x8), `LobbyGateChannelManager`/`InfoGateChannelManager::Initialize` (0x48), `GamedChannelManager` constructor and `Initialize`. |
| `0x9dca0` | `LobbyDaemon::onStart` | Needs the `PostOfficeChannel` layout (`TransactionChannel` base, 0x140), the `MileageBatchRetryDeposit` layout (0x58), and the inline `Start` of `LobbyTick`, `GameWorldReporter` and `LobbyStats`. |
| `0x9e2f0` | `LobbyDaemon::shutdown` | `LobbyDaemon.cpp` sees the SmartCouponDaemon `NPServiceChannelManager` (`NPChannel.h`, `_npServChannel`, no `Finalize`). The LD PDB class has `_gameServChannel` and `Finalize`. Also needs the inline `Stop` helpers and `TencentUIC::CleanUp`. |
| `0x9e5b0` | `LobbyDaemon::reload` | Calls `ContentsRuleConfig::ReloadContentsRuleConfig` and `BnsCommonConfig::ReloadBnsCommonConfig`. The LD target links no owner for them (`ContentsRuleConfigDefinition.cpp`: a later wave adds it). |
| `0x9f010` | `LobbyDaemon::startNPChannel` | `NPServiceChannelManager` has no PDB layout, base or inline constructor in `NPServiceChannel.h` (owner module). |
| `0x9f130` | `LobbyDaemon::setupNpScheduleInfo` | `SetupNpScheduleInfoJob` has no `LobbyJob` base, `_pool` or layout in `SetupNpScheduleInfoJob.h` (owner module). |

## Safety differences

None. The lift adds no guard and logs no key. The original has no null test after these allocations. The lift keeps the original
behaviour and marks each one `// BUG:`:

| Function (RVA) | Original behaviour |
| --- | --- |
| `LobbyDaemon::cooldown` (`0x9ef40`) | A failed `Alloc` leaves `GCoolDown` null. `CoolDown::Start` then reads it. |
| `BLDaemonInfoTable::load` (`0x40510`) | No test of the `AllocZero` result of the array or of each entry. No test of the `Realloc` result. |
| `BLDaemonInfoTable::Update` (`0x41090`) | Leaks the loaded entry when it exists already or when `add` fails. |

## Build notes

- The worktree had no `vendor/zstd/src`. It was copied from `lift-lobbydaemon-15` (`bb6eaf64`, checked). The directory is git-ignored.
- All build and parity output is in the ignored `build-ld-20/` (`gate-final.log`, `parity-final.log`, `vs2010/`).

## Merge note

Rebase on main before the merge. Run `tools/parity.sh` again after the merge. The runner accepts the baseline. This branch does not change it.
