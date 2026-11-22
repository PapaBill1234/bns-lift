# lift-lobbydaemon-16: LobbyGamePacketHandler part 1

Source: LobbyDaemon 2019 + PDB (VS2010 SP1). IDA was not opened.
The card has 20 functions (RVA `0x88220` to `0x8c250`). The raw index has 1 more entry: `0x88230` (`GamedChannel::`scalar deleting destructor'`, compiler-generated, not on the card).
13 functions are lifted. 7 are Not done.

## Result

| Item | Value |
| --- | --- |
| Lifted | 13 |
| Not done | 7 |
| `tools/gate.sh` (`LIFT_BUILD_DIR=build-ld-16`) | gate ok |
| `tools/parity.sh` (same build) | parity ok |
| LobbyDaemon MATCH | 436 -> 442 (+6) over main 9d0ef81 |
| CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon MATCH | 456, 658, 630, 694 (+0 each, no MATCH lost) |

LobbyDaemon parity: 442/2204 = 20.1 %. Paired 574, mean score 95.0.
Baseline: `Docs/Parity/baseline/LobbyDaemon.json` = 436 MATCH. The baseline files are unchanged.

The +6 MATCH are: `HandleLobbyGame_ServiceOpenNotify`, `HandleLobbyGame_UpdateBotScoreNotify`, `HandleLobbyGame_UpdateCharacterDataReq`
(card functions) and `CliSessionTable::Select_index_pcid`, `Session::Send`, `Session::SendV` (not on the card; they now have a lifted caller).

## Checkpoint review

The four checkpoints (`build-ld-16/checkpoint-1..4.tsv`) were checked against the card index.

| Check | Result |
| --- | --- |
| Rows do not overlap | Yes. 21 distinct RVAs in 4 files. |
| Rows cover the card | No. `0x8be60` (`AbandonChargeNotify`) and `0x8c250` (`UpdateCharacterDataReq`) had no row. |
| Rows `0x8be40`, `0x8be50` | Not functions (no `.pdata`, inside the epilogue of `StopChargeReq`). Not on the card. Dropped. |
| Saved diff | It compiled (`gate ok`) but the exe did not link. See "Link failure". |

This run lifted `AbandonChargeNotify` and `UpdateCharacterDataReq` in addition to the checkpoints.

## Link failure and fix

The first `tools/parity.sh` run failed at the VS2010 link of all 5 exes. Two causes:

1. The worktree had no `vendor/zstd/src` (ignored directory). Fix: copied from the ld-15 worktree, HEAD `bb6eaf64` (checked).
2. The checkpoint bodies needed symbols that no LobbyDaemon source defines:

| Symbol | Needed by | Owner |
| --- | --- | --- |
| `ObjPool::Checkout` | Enter, Leave, Logout, Start, Stop, Abandon | LD ObjectPool module (`0x625d0` and up) |
| `EnterGameWorldJob::_pool`, `LeaveGameWorldJob::_pool`, `LogoutInGameWorldJob::_pool`, `StartChargeJob::_pool`, `StopChargeJob::_pool`, `AbandonChargeJob::_pool` | same | job modules (need the `ObjPool` constructor) |
| `BnsCommonConfig::Config` | `NPPresenceKickReq` | LD `BnsCommonConfigDefinition` module (`0x1890`) |
| `LobbyErrorDesc` | `UpdateBotScoreNotify`, `UpdateCharacterDataReq` | module not found in the PDB module list ❓ |

`ObjectPool.cpp` is the SmartCouponDaemon form and is not in `lift_lobbydaemon` (ld-0 handoff, same block as ld-13 `CliSession::_pool`).
Same rule as ld-2 and ld-13: a function that needs the ObjPool is Not done.
The two data items are not ObjPool-bound. They have placeholders in `LobbyGamePacketHandler.cpp` with `// LIFT:` (see "Placeholders").

## Lifted

| RVA | Function | Score | Status | Note |
| --- | --- | ---: | --- | --- |
| `0x88260` | `HandleLobbyGame_HelloReq` | 18.9 | DIFF | LTCG: `BLDaemonInfoTable::Find` is a stub (noreturn), the rest of the body is removed. |
| `0x88cd0` | `HandleLobbyGame_ServiceOpenNotify` | 100.0 | MATCH | |
| `0x88f30` | `HandleLobbyGame_NPPresenceKickReq` | 65.8 | DIFF | LTCG: `NPGameServiceChannel::SendRequestPresenceKick` is a stub. |
| `0x89d90` | `HandleLobbyGame_UpdateBotScoreNotify` | 100.0 | MATCH | |
| `0x8a400` | `HandleLobbyGame_KickOk` | 51.5 | DIFF | LTCG: `LobbyJobManager::ExecuteW` (and its inlined `find`, `transit`, `remove`) are stubs. |
| `0x8a560` | `HandleLobbyGame_KickFail` | 32.1 | DIFF | same |
| `0x8a7c0` | `HandleLobbyGame_CreateCharacterOk` | 42.7 | DIFF | same |
| `0x8aad0` | `HandleLobbyGame_CreateCharacterFail` | 32.1 | DIFF | same |
| `0x8ad30` | `HandleLobbyGame_DeleteCharacterOk` | 32.1 | DIFF | same |
| `0x8af90` | `HandleLobbyGame_DeleteCharacterFail` | 32.1 | DIFF | same |
| `0x8b1f0` | `HandleLobbyGame_RestoreCharacterOk` | 51.5 | DIFF | same |
| `0x8b350` | `HandleLobbyGame_RestoreCharacterFail` | 32.1 | DIFF | same |
| `0x8c250` | `HandleLobbyGame_UpdateCharacterDataReq` | 100.0 | MATCH | |

Each DIFF function shows `import:abort` in the call list of funcdiff. A stub callee ends in `abort()`. LTCG sees a noreturn call and removes the code after it.
The source form is not the cause. The scores rise when the LobbyJob, BLDaemonInfoTable and NPGameServiceChannel cards land. No re-lift is needed.

Dead-strip: the 13 handlers have no lifted caller (`LobbyGamePacketLobbySideHandlerList` is a null placeholder, ld-18).
Each has `#pragma comment(linker, "/INCLUDE:...")` with `// LIFT:` in `LobbyGamePacketHandler.cpp`. The names come from `llvm-pdbutil dump -publics`.
The verify card removes them when the table is lifted.

## Not done

| RVA | Function | Reason |
| --- | --- | --- |
| `0x88220` | `RepeatPacketDecomposer::Reset` | Body is in the shared `src/Server/BloodLib/source/PacketUtil.cpp:280` (`lift_common_ld`). Not module source. |
| `0x89270` | `HandleLobbyGame_EnterWorldReq` | Needs `ObjPool::Checkout` and `EnterGameWorldJob::_pool`. LD ObjectPool module not lifted. The link would break. |
| `0x899a0` | `HandleLobbyGame_LeaveWorldReq` | Needs `ObjPool::Checkout` and `LeaveGameWorldJob::_pool`. Same. |
| `0x8a060` | `HandleLobbyGame_LogoutNotify` | Needs `ObjPool::Checkout` and `LogoutInGameWorldJob::_pool`. Same. |
| `0x8b5b0` | `HandleLobbyGame_StartChargeReq` | Needs `ObjPool::Checkout` and `StartChargeJob::_pool`. Same. |
| `0x8b9b0` | `HandleLobbyGame_StopChargeReq` | Needs `ObjPool::Checkout` and `StopChargeJob::_pool`. Same. |
| `0x8be60` | `HandleLobbyGame_AbandonChargeNotify` | Needs `ObjPool::Checkout` and `AbandonChargeJob::_pool`. Same. |

The six ObjPool functions were lifted and compiled in the checkpoints. They were reverted to `LIFT_STUB` so that the link works.
The job layouts stay in the headers (`EnterGameWorldJob.h`, `LeaveGameWorldJob.h`, `LogoutInGameWorldJob.h`, `StartChargeJob.h`, `StopChargeJob.h`, `AbandonChargeJob.h`, `LobbyToken.h`, `GameWorld.h`, `LobbyJob.h`, `CliSessionJob.h`). They have static_asserts. The bodies are saved outside the repo in `private-project/ld16-handler-with-objpool-bodies.cpp.txt`.
The LD ObjectPool card can re-add the six bodies and the pool definitions.
`0x88230` (`GamedChannel::`scalar deleting destructor'`) is compiler-generated. It is not on the card and not lifted here.

## Placeholders that later cards must remove

| Item | File | Owner |
| --- | --- | --- |
| `BnsCommonConfig* BnsCommonConfig::Config = nullptr;` | `LobbyGamePacketHandler.cpp` | LD `BnsCommonConfigDefinition` module (`0x1890`). A second definition fails the link. |
| `wchar_t const* LobbyErrorDesc[28]` (strings read from `.data` `0003:2032` of the original, same names as `enum LobbyError`) | `LobbyGamePacketHandler.cpp` | The module that defines it. ❓ The PDB module is not known. |
| 13 `/INCLUDE` pragmas for the handlers | `LobbyGamePacketHandler.cpp` | The verify card (after the handler table lands). |

## Codegen trials

| Item | Result |
| --- | --- |
| DIFF functions above 85 % | None. All 10 DIFF functions are below 66 %. |
| Trials | 0. |
| Not tried | All 10 DIFF functions. The cause is the stub callees (see above). A source form cannot change a `noreturn` stub call. A trial would fit the stubs, not the original. |

## Safety differences

- `NPPresenceKickReq`: the original passes the third argument of `SendRequestPresenceKick` through LTCG. The lift passes `nullptr` (`// LIFT:` in source). Not a guard.
- No guard was added or removed. No session key is logged.

## Gate

`tools/gate.sh` and `tools/parity.sh` both ran on the final tree with `LIFT_BUILD_DIR=build-ld-16` and printed `gate ok` and `parity ok`.
`--accept`, the baselines, `progress.tsv` and the README parity table were not changed.
