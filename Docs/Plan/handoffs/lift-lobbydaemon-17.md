# lift-lobbydaemon-17: LobbyLobbyGatePacketHandler part 1

Source: LobbyDaemon 2019 + PDB (VS2010 SP1). Pseudocode: the indexed cache (`LobbyLobbyGatePacketHandler.c`). IDA was not opened.
The card has 17 functions (`0xc25c0` to `0xc67e0`). 1 is lifted. 16 are Not done.

## Result

| Item | Value |
| --- | --- |
| Lifted | 1 |
| Not done | 16 |
| Gate (`tools/gate.sh`, `LIFT_BUILD_DIR=build-ld-17`) | gate ok |
| Parity (`tools/parity.sh`) | parity ok |
| LobbyDaemon MATCH (baseline = main 75f0769) | 195 -> 196 (+1) |
| CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon MATCH | 456, 658, 630, 694 (+0 each, no MATCH lost) |
| LobbyDaemon paired / only in original | 281 -> 282 / 1923 -> 1922 |

## Lifted

| RVA | Function | Funcdiff score | MATCH |
| --- | --- | ---: | --- |
| `0xc5ae0` | `HandleLobbyLobbyGate_CheckCharacterNameReq` | 100.0 | yes |

The function logs an error (`Log::Write(Log::LT_ERROR, ..., 807, ...)`) and returns true. No layout is needed.
Its only caller is the handler table (a stub body). Without a reference, /OPT:REF removes it.
`#pragma comment(linker, "/INCLUDE:...")` keeps it (`// LIFT:` comment in the source). The verify card removes the pragma.

## Not done

Common blocker: `LobbyDaemon.h` has no members (card ld-15 owns the layout). `LobbyGateChannel` has no base and no members (no `_rawChannel`).
The functions use `LobbyDaemon::_instance->_clisessionMgr`, `_jobMgr`, `_config` and similar. A lift now would not compile, or would need invented layouts.
All stubs stay unchanged. Each stub keeps `LIFT_STUB(<rva>)`.

| RVA | Function | Reason (beyond the common blocker) |
| --- | --- | --- |
| `0xc25c0` | `HandleLobbyLobbyGate_HelloReq` | Also needs `_daemonInfoTable`, `_gameWorldRegistry`, `_mileageManager`, `_lgatechmgr`, `BLDaemonInfo`, `GameWorldRegistry`, `MileageManager`, `LobbyGateChannelManager`. The chunk at `0xc2990` is part of this function. |
| `0xc2d90` | `HandleLobbyLobbyGate_InitSessionWithNPTokenReq` | `LobbyGateChannel`, `CliSessionManager`, `LobbyConfig`, `CliSession` layouts (not in checkpoints; checked in the pseudocode, lines 305-542). |
| `0xc3380` | `HandleLobbyLobbyGate_StartSessionWithNPTokenReq` | `CliSessionManager::StartSessionWnpToken` is not declared. `CSMResultDesc` is not in src (link error). |
| `0xc3890` | `HandleLobbyLobbyGate_InitSessionWithLobbyTokenReq` | `_tokenDesk`, `_jobMgr`, `_config`, `LobbyJobManager`, `LobbyTokenDesk`. |
| `0xc3e70` | `HandleLobbyLobbyGate_StartSessionWithLobbyTokenReq` | `_clisessionMgr`, `_jobMgr`, `CliSessionTable`, `LobbyJobManager`. |
| `0xc4180` | `HandleLobbyLobbyGate_LostAnonymousConnectionNotify` | `_clisessionMgr`, `_jobMgr`, `CliSessionTable`, `LogoutJob`. |
| `0xc43f0` | `HandleLobbyLobbyGate_LostConnectionNotify` | Same as `0xc4180`. |
| `0xc4650` | `HandleLobbyLobbyGate_LogoutNotify` | Same as `0xc4180`. |
| `0xc48b0` | `HandleLobbyLobbyGate_GetEnterWorldTokenReq` | `TryEnterGameWorldJob`, `LobbyJobManager`, `CliSessionTable::Select`. |
| `0xc4df0` | `HandleLobbyLobbyGate_GetWaitInfoReq` | `WaitInfo`, `CliSession::GetGameWorldWaitInfo`. |
| `0xc5040` | `HandleLobbyLobbyGate_GiveupWaitReq` | `GiveupWaitGameWorldJob` (ObjPool, vtable), `CliSessionJob`, `LobbyJobManager`. Not in the checkpoints; checked in the pseudocode (lines 1728-1865). |
| `0xc5360` | `HandleLobbyLobbyGate_GetCharacterInfoListReq` | `CliSession` and the character list types. |
| `0xc5630` | `HandleLobbyLobbyGate_GetCharacterInfoReq` | `CliSession` and `Character` layouts. |
| `0xc5b10` | `HandleLobbyLobbyGate_CreateCharacterReq` | `CreateCharacterJob` layout and vtable, `CliSession`, `LobbyJobManager`. |
| `0xc6190` | `HandleLobbyLobbyGate_DeleteCharacterReq` | Same as `0xc5b10`, plus `DeleteCharacterJob`. |
| `0xc67e0` | `HandleLobbyLobbyGate_CancelWaitCharacterDeletionReq` | `CancelWaitCharacterDeletionJob`, `CancelWaitCharacterDeletionReqParam`, `LobbyJobManager`, `CliSessionTable`. Not in the checkpoints (a checkpoint row wrongly put it outside the card); checked in the pseudocode (lines 2661-2903). |

## Checkpoint review

| Checkpoint | Result |
| --- | --- |
| 1 to 4 | Rows cover 14 of 17 functions. They do not overlap. |
| Missing rows | `0xc2d90`, `0xc5040`, `0xc67e0`. Added above. |
| Rows that are not functions | `0xc2990`, `0xc5058`, `0xc6960` (inside other functions). Ignored. |
| Saved diff | Only `CheckCharacterNameReq` (and the `Log.h` include) changed. The text matches the pseudocode (lines 2157-2164). |

## Codegen trials

| Item | Result |
| --- | --- |
| Trials | 0. The only lifted function is MATCH 100.0 at the first build. |
| Not tried | The 16 Not done functions. They need the layouts first (ld-15 and the job and channel cards). |

## Safety differences

None. The lifted function has no input and no guard.

## Build notes

- The worktree had no `vendor/zstd/src`. The VS2010 link of all 5 exes failed (unresolved `ZSTD_*`).
  The source was copied from another worktree (HEAD bb6eaf64 verified). `vendor/zstd/src` is ignored by git and not committed.
- Final run: `tools/gate.sh` printed `gate ok`. `tools/parity.sh` printed `parity ok`. Baselines are unchanged.
