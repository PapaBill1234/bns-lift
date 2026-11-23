# lift-lobbydaemon-22: LobbyLobbyGatePacketHandler part 2

Source: LobbyDaemon 2019 + PDB (VS2010 SP1). IDA was not opened.
The card has 18 functions (RVA `0xc6e30` to `0xcb330`). 1 is lifted. 17 are Not done.

## Result

| Item | Value |
| --- | --- |
| Lifted | 1 |
| Not done | 17 |
| `tools/gate.sh` (`LIFT_BUILD_DIR=build-ld-22`) | gate ok |
| `tools/parity.sh` (same build) | parity ok |
| LobbyDaemon MATCH, baseline (main aefe11d) | 645 |
| LobbyDaemon MATCH, final | 645 (+0) |
| Card functions at MATCH | 0 of 1 lifted |
| CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon MATCH | 456, 658, 630, 694 (+0 each, no MATCH lost) |
| `changedPaths` (src, include, CMakeLists.txt, cmake, tools, tests) | 1 (the `.cpp`). Docs are not counted. The diff touches 3 paths in total |

LobbyDaemon parity: 645/2204 = 29.3 %. Paired 825, mean score 95.2. No MATCH lost.
CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon: +0 each.
`CliSessionTable::Select` is already MATCH (100.0) on main. The card brings 0 new MATCH.
Baseline files are unchanged. No `--accept` was run.
The branch is rebased onto main aefe11d (only `lessons.md` conflicted: both appends kept). The gain is measured against main.

## Checkpoint check

| Check | Result |
| --- | --- |
| Rows in `checkpoint-1..4.tsv` | 4 + 6 + 3 + 5 = 18 |
| Overlap between checkpoints | none |
| Match with the card index (`index.tsv`, `LobbyLobbyGatePacketHandler`, `0xc6e30` to `0xcb330`) | 18 of 18, same RVA and name, 2,850 lines |
| Checkpoint 4 claim "5 lifted" | Wrong. The 5 handlers do not link. See "Repair" |

## Repair

The checkpoint build lifted 6 handlers, but the build only compiled the clang objects. It did not link the VS2010 exe.
The first `tools/parity.sh` run showed 2 problems.

| Problem | Cause | Action |
| --- | --- | --- |
| 5 exes: `ZSTD_*` unresolved | The new worktree had no ignored `vendor/zstd/src` | Copied it from `lift-lobbydaemon-21`. `rev-parse HEAD` = `bb6eaf64`. Not tracked |
| LobbyDaemon: `ObjPool::Checkout` and 5 `<Job>::_pool` unresolved | `ObjectPool.cpp` is the SmartCouponDaemon form and is not in the LobbyDaemon VS2010 build. No `_pool` has a definition | Put 5 handlers back to `LIFT_STUB`. Reverted 5 job headers, 4 job `.cpp` files and `LobbyJobParams.h` |

The reverted work (PDB layouts of the 5 jobs, 5 parameter structs, 5 handler bodies) is in the ignored file `build-ld-22/full-checkpoint.diff`. Use it when a card defines `ObjPool` for LobbyDaemon.

## Lifted

| RVA | Function | Score | MATCH |
| --- | --- | ---: | --- |
| `0xc8aa0` | `HandleLobbyLobbyGate_GetServiceEntryListReq` | 78.5 | no |

`#pragma comment(linker, "/INCLUDE:...")` keeps it (the PDB public name is present: checked with `grep -a -F`). The caller is not lifted. ❓ The lift has no caller for any `HandleLobbyLobbyGate_` handler yet.
Funcdiff for this function: score 78.5, calls 63, consts 87, refs 86. It is below 85, so no codegen form was tried (see "Not tried").
Repair 2 removed the 2 explicit `fp.packet.Clear()` calls (the original has one Clear per path, from the inlined `~FragmentPacket`). Score 77.9 -> 78.5, calls 61 -> 63.
The cast is now `static_cast<LobbyGateChannel*>` (LobbyGateChannel derives from SharedChannel on main). The /INCLUDE comment gives the RVA of the kept function (0xc8aa0).

## Not done

| RVA | Function | Reason |
| --- | --- | --- |
| `0xc6e30` | `HandleLobbyLobbyGate_RecoverCharacterReq` | Needs `ObjPool::Checkout(&RecoverPcJob::_pool)`. No `_pool` definition. No `RecoverPcJob` layout |
| `0xc7540` | `HandleLobbyLobbyGate_BindCharacterSlotReq` | Needs `BindCharacterSlotJob::_pool`, its vftable and `LobbyJob::transit`. None lifted |
| `0xc7af0` | `HandleLobbyLobbyGate_GetChargeInfoReq` | Needs `GetChargeInfoJob::_pool` |
| `0xc7df0` | `HandleLobbyLobbyGate_GetGoodsCountReq` | Needs `GetGoodsCountJob::_pool` |
| `0xc8080` | `HandleLobbyLobbyGate_ListGoodsReq` | Needs `ListGoodsJob::_pool`, job layout, `LobbyJob::transit` |
| `0xc83d0` | `HandleLobbyLobbyGate_TakeGoodsReq` | Needs `TakeGoodsJob::_pool` |
| `0xc85e0` | `HandleLobbyLobbyGate_ListLobbyServiceItemInfoReq` | Needs `ListLobbyServiceItemJob::_pool` |
| `0xc8860` | `HandleLobbyLobbyGate_GetLobbyServiceItemInfoReq` | Needs `GetLobbyServiceItemJob::_pool` |
| `0xc8d00` | `HandleLobbyLobbyGate_ChangeCharacterAppearanceWithAccountInventoryItemReq` | Needs `ChangeCharacterAppearanceJob::_pool` |
| `0xc9300` | `HandleLobbyLobbyGate_ChangeCharacterSexWithAccountInventoryItemReq` | Needs `ChangeCharacterSexJob::_pool`, layout, `LobbyJob::transit` |
| `0xc9940` | `HandleLobbyLobbyGate_ChangeCharacterRaceWithAccountInventoryItemReq` | Needs `ChangeCharacterRaceJob::_pool` |
| `0xc9fc0` | `HandleLobbyLobbyGate_RenameCharacterWithAccountInventoryItemReq` | Needs `RenameCharacterJob::_pool` |
| `0xca560` | `HandleLobbyLobbyGate_AddSlotWithAccountInventoryItemReq` | Lifted in the checkpoint. Does not link: `AddSlotJob::_pool` and `ObjPool::Checkout` have no LobbyDaemon definition |
| `0xca8b0` | `HandleLobbyLobbyGate_ChangeUserNameWithAccountInventoryItemReq` | Same: `ChangeUserNameJob::_pool` |
| `0xcac70` | `HandleLobbyLobbyGate_ExtendJumpingCharacterCreationQuotaWithAccountInventoryItemReq` | Same: `ExtendJumpingCharacterCreationQuotaJob::_pool` |
| `0xcafd0` | `HandleLobbyLobbyGate_CreateInitialUserNameReq` | Same: `CreateInitialUserNameJob::_pool` |
| `0xcb330` | `HandleLobbyLobbyGate_ActivateGradeReq` | Same: `ActivateGradeJob::_pool` |

Unblock all 17: a card that lifts the LobbyDaemon `ObjectPool` module (`ObjPool::ObjPool`, `~ObjPool`, `Checkout`) and defines the 17 `<Job>::_pool` statics.

## Safety differences

| Function | Difference |
| --- | --- |
| `GetServiceEntryListReq` | None. The original checks `Decompose`, the session lookup and `FetchServiceEntryList`. We keep all 3 |

## Not tried

| Item | Reason |
| --- | --- |
| Codegen forms for `GetServiceEntryListReq` (78.5) | Below the 85 threshold. The 3 trials were saved for functions above 85. No such function exists on this card |
| Re-lift of the 5 reverted handlers | Cannot link. Waits for the ObjectPool card |
| `ObjPool` definition in this card | Out of scope. The card lists only `LobbyLobbyGatePacketHandler.cpp` and `CMakeLists.txt` |
