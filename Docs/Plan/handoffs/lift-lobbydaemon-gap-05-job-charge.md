# Handoff: lift-lobbydaemon-gap-05-job-charge

Date: 2026-11-25. Branch: `gap-05-job-charge`. Base: `eb68b2a` (head of gap-int-2).
Code commit: `d1a92d7`. This handoff is in the next commit.

## Scope

| Module | Card IDs | NOREF MATCH | NOREF DIFF |
| --- | --- | --- | --- |
| AbandonChargeJob | 6 | 3 | 3 |
| ActivateGradeJob | 11 | 5 | 6 |
| GetChargeInfoJob | 7 | 2 | 5 |
| StartChargeJob | 8 | 5 | 3 |
| StopChargeJob | 8 | 3 | 5 |
| Total | 40 | 18 | 22 |

Scope addition: `CliSessionJob::CliSessionJob` and `CliSessionJob::~CliSessionJob` (both were LIFT_STUB).
The destructor is NOREF MATCH.

## What changed

- Class layouts from `tools/pdbcls.py LobbyDaemon <Class>`: State enums, `_def`, members, static_asserts.
- Bodies from the 2019 + PDB pseudocode. PDB names only. The server checks stay.
- Each job .cpp has its own `JOB_LOG` macro. The macro parameter is `logType`. Do not name it `type`:
  the preprocessor then also replaces `GetDefinition()->type`.
- Do not include `StsMsgGrade.h` together with `NPServiceChannel.h`. `NPServiceChannel.h` gets the StsMsgLib
  base types from `SmartCouponDaemon/NPChannelBase.h`. A second definition gives C2011.
- `_vtbl` uses `::new (buf) X(...)`. The global placement delete then exists. The function gets the EH frame
  of the original (const -2).

## Decisions

| Item | Decision | Reason |
| --- | --- | --- |
| `_pool` | No definition | ObjectPool is not in lift_lobbydaemon (as in CliSession.cpp). |
| `deallocate_me` | Stays LIFT_STUB | The body calls `_pool.Checkin`. Not in the card IDs. |
| `SendRequestChargeStart` 5th parameter | Give 0 | The original caller does not set it. The declaration has it. |
| Transaction free | `~NPLobbyJobTransaction()` then `Memory::_Manager[2]->Free` | The original calls the scalar deleting destructor (flag 1). Its operator delete is empty. |
| `addReferenceCount` | `addReferenceCount(false, file, line)` | The original call is an LTCG copy with rdx=file, r8=line. |
| Abandon response 0x5690, expire 0x5b10 | Stay LIFT_STUB | They need KickJob. Not in the card IDs. |
| GetChargeInfo response 0x50c30 | Stays LIFT_STUB | Not in the card IDs. |

## Checks

| Check | Result |
| --- | --- |
| `pilot.py gate` (40 card IDs, REF main-build of `56d5d9f` = same tree, NOREF `noref-build-X2m27FkU`) | 40 of 40 clear; eligible pool 252 -> 292 |
| `gate_full.sh` (fresh clone of `d1a92d7`) | rc 0, parity ok, 578 s |
| `proof.py --base eb68b2a --candidate d1a92d7` | verdict `review`; 0 lost MATCH, 0 strict regress in 5 exes |
| `review.py run` (fresh ledger, review.py 7ff33683...) | 22 accept, 0 reject, 0 park |
| `integrate.check_proof` (dry) | PASS |

## MATCH

| Exe | Before | After | Lost |
| --- | --- | --- | --- |
| CacheGate | 456 | 456 | 0 |
| LobbyGate | 658 | 658 | 0 |
| SmartCouponDaemon | 630 | 630 | 0 |
| PostOfficeDaemon | 694 | 694 | 0 |
| LobbyDaemon (REF) | 674 | 674 | 0 |
| LobbyDaemon (NOREF) | 973 | 992 | 0 |

REF does not change. No live code creates the charge jobs yet (the packet handlers are LIFT_STUB).
LTCG drops the unreachable chain. The 22 proof review items are gap-int-2 MATCHes against the Docs baseline.

## Open items

| Item | Cause | Owner |
| --- | --- | --- |
| 5 `request*` functions DIFF | NP senders `SendRequestCharge*`, `SendRequestGradeActivateGrade` are LIFT_STUB | gap-04 |
| Start/Stop response, Stop expire/init, Abandon/GetChargeInfo `work` DIFF | `CliSession::onPcCafeChargeStart/Stop`, `completeRequestChargeStop`, response stubs are LIFT_STUB | gap-15 or later |
| 5 `_vtbl` DIFF 77.8 | The original keeps the dead stores of the LobbyJob vptr and pool id 0xa. Ours drops them. ❓ | open |
| `CliSessionJob::CliSessionJob`, `GetChargeInfoJob::GetChargeInfoJob` DIFF | All live callers pass a null owner now. LTCG removes the `addReferenceCount` call. Expect MATCH when real callers exist. ❓ | later cards |
| ActivateGradeJob `initFrom*`, `activateGradeResponse`, `sendFail` DIFF | VS2010 tail-merges the inlined `sendFail` paths. The original does not. ❓ | open |
| `GetChargeInfoJob::init` DIFF 93.3 | Two error paths tail-merge in ours. ❓ | open |
| `AuctionRollbackEscrowJob::AuctionRollbackEscrowJob` unpaired in NOREF | Was DIFF 22.2 at base. Not a lost MATCH. ❓ | open |
