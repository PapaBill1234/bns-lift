# Handoff: lift-lobbydaemon-gap-20 (NPLobbyMessageHandler part 1)

| Item | Value |
| --- | --- |
| Card | gap-20 NPLobbyMessageHandler part 1 (private project) |
| Code | Squash of the gap-20 branch and its repair (37affda), rebased on main on 2026-11-26 |
| Source | LobbyDaemon 2019 + PDB (VS2010 SP1), HR pseudocode. Packets: 381 client. |
| Author and committer | `Claude <noreply@anthropic.com>` |

## Changes

| File | Change |
| --- | --- |
| `src/Server/LobbyDaemon/NPLobbyMessageHandler.cpp` | `DispatchNPLobbyMessageHandler` (0xcb710) and the `Handle_*` handlers. PDB line shape: positive outer type test, `transaction != nullptr && GetKind()` test, `if (!ExecuteW) Log; else return true;`, one trailing `return false`, a `LobbyJobManager* jobMgr` local. |
| `src/Server/LobbyDaemon/NPLobbyMessageHandler.h` | Declarations of all handlers with addresses. |
| `src/Server/SmartCouponDaemon/NPChannelBase.h` | `NPTransaction::GetKind` returns the PDB enum `Kind`. LobbyDaemon names value 1 `KIND_LOBBYJOB`, SmartCouponDaemon `KIND_TRANJOB`. |
| `src/Server/LobbyDaemon/NPServiceChannel.h` | `NPLobbyJobTransaction::GetKind` returns `KIND_LOBBYJOB`. |

## Rebase on main

| Item | Resolution |
| --- | --- |
| `Handle_SrvCharge_RequestStop` | Keep the lift-misc-a copy on main. Its `/INCLUDE` pragma is removed, because the dispatcher now calls it. |
| `_StsMsgRequestChargeRequestStop` | Keep the lift-misc-a copy. |
| `LobbyDaemon.cpp` | Gets `NPChannelBase.h` through `NPServiceChannel.h`, which sets `NPTRANSACTION_KIND_LOBBYJOB` first. |

## Review

Review items that the reviewer rejects are excluded with receipts in `Docs/Parity/excluded.tsv`. The reason column gives the precheck or model reason.
