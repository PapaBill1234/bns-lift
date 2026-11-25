# Handoff: lift-lobbydaemon-gap-08-job-session

| Item | Value |
| --- | --- |
| Card | `design/parity-v2/gap-cards/gap-08-job-session.md` (private project) |
| Branch | `gap-08-job-session` (scratch clone only, not pushed) |
| Base | `e68e5d0` (fix7) |
| Code commit | `09dcab1` |
| Source | LobbyDaemon 2019 + PDB (VS2010 SP1), HR pseudocode. IDA was not opened. |
| Author and committer | `Claude <noreply@anthropic.com>` |

## Result

| Check | Result |
| --- | --- |
| Gate `pilot.py gate --rev 09dcab1` | 37 of 38 card IDs have no reason. 0 dropped. 1 `ineligible_unpaired` (`NPDemander::Response`, see below). Before: 0 of 38. Eligible pool: 264 -> 305. |
| Full 5-exe build (`gate_full.sh`, clone of `09dcab1`) | rc 0, "parity ok", 839 s |
| Proof (`proof.py --base e68e5d0 --candidate 09dcab1`, strict rules not changed) | verdict `pass`: 0 lost MATCH, 0 strict regress, 0 reasons, 0 review items, 1 credited |
| Review | Not run. `review.py` refuses a `pass` proof: "only a clean review proof goes to review". There are no items. |
| `integrate.check_proof` (dry) | PASS |

## MATCH per exe

| Exe | Before (`e68e5d0`) | After (`09dcab1`) | Delta | Lost |
| --- | ---: | ---: | ---: | ---: |
| CacheGate | 456 | 456 | 0 | 0 |
| LobbyGate | 658 | 658 | 0 | 0 |
| SmartCouponDaemon | 630 | 630 | 0 | 0 |
| PostOfficeDaemon | 694 | 694 | 0 | 0 |
| LobbyDaemon (REF) | 674 | 675 | +1 | 0 |
| LobbyDaemon NOREF | 973 | 1005 | +32 | 1 (artifact) |

REF: no live code creates the session jobs yet. LTCG drops the job chains. Only `AnonymousLobbyGatePresence` code is in the REF build. The new REF MATCH is `AnonymousLobbyGatePresence::AnonymousLobbyGatePresence`.

### NOREF artifact: `LobbyJobTransaction::Set`

| Item | Value |
| --- | --- |
| Status | MATCH -> DIFF 88.9 (NOREF only; not in the REF build) |
| Cause | `KickJob::worldKickReq` is now the only caller. LTCG puts the constant task 116 (0x74) into `Set`. The original has many callers. |
| Fix | None in this card. The other callers are jobs of other cards. Expect MATCH again when a second caller exists. ❓ not tested |

## Card IDs (NOREF build `noref-build-8TMJwvWy`)

| Status | Count |
| --- | ---: |
| MATCH | 22 |
| DIFF | 15 |
| Unpaired | 1 |
| Paired in REF | 0 |

| Name | RVA | NOREF | Cause |
| --- | --- | --- | --- |
| `InitCliSessionWlobbyTokenJob::initOk` | 0x54c40 | DIFF 88.0 | `CliSession::finalize` is `LIFT_STUB` (gap-15) |
| `KickJob::work` | 0x86380 | DIFF 78.7 | `CliSession::finalize` is `LIFT_STUB` (gap-15) |
| `NPDemander::Response` | 0x876c0 | unpaired | `NPGatewayChannel::SendResponseGateLogoutUser` is `LIFT_STUB` (gap-04). The body is noreturn and folds. |
| `ManageDemander::Response` | 0x87750 | DIFF 33.3 | `ManageChannel` send functions are `LIFT_STUB` (gap-23) |
| `LogoutInGameWorldJob::logout` | 0x5af30 | DIFF 86.1 | `CliSession::finalize` is `LIFT_STUB` (gap-15) |
| `LogoutJob::LogoutJob` | 0x97af0 | DIFF 66.7 | Only null-owner callers. LTCG drops `addReferenceCount`. ❓ |
| `LogoutJob::logout` | 0x97d30 | DIFF 85.1 | `CliSession::finalize` is `LIFT_STUB` (gap-15); const 0xfffd missing ❓ |
| `StartCliSessionWlobbyTokenJob::Initialize` | 0x76380 | DIFF 88.9 | `addReferenceCount` call order ❓ |
| `StartCliSessionWlobbyTokenJob::work` | 0x76490 | DIFF 73.6 | `CliSession::finalize` is `LIFT_STUB` (gap-15) |
| `StartCliSessionWlobbyTokenJob::getGradeLevelReq` | 0x76720 | DIFF 87.7 | `finalize` stub. The original inlines `NPLobbyJobTransaction::Set` without the null check; ours keeps it. ❓ |
| `StartCliSessionWlobbyTokenJob::getGradeLevelResponse` | 0x76a50 | DIFF 96.7 | `CliSession::finalize` is `LIFT_STUB` (gap-15) |
| `StartCliSessionWlobbyTokenJob::getGradeLevelExpire` | 0x76f30 | DIFF 84.1 | `CliSession::finalize` is `LIFT_STUB` (gap-15) |
| `StartCliSessionWlobbyTokenJob::listAllGradesReq` | 0x77050 | DIFF 53.1 | `NPGameServiceChannel::SendRequestGradeListAllGrades` is `LIFT_STUB` (gap-04) |
| `StartCliSessionWlobbyTokenJob::listAllGradesResponse` | 0x77340 | DIFF 96.7 | `CliSession::finalize` is `LIFT_STUB` (gap-15) |
| `StartCliSessionWlobbyTokenJob::listAllGradesExpire` | 0x777f0 | DIFF 84.1 | `CliSession::finalize` is `LIFT_STUB` (gap-15) |
| `StartCliSessionWlobbyTokenJob::start` | 0x77910 | DIFF 86.2 | `CliSession::finalize` is `LIFT_STUB` (gap-15) |

Lifted bodies that are not card IDs: `KickJob::kick` (DIFF 97.2), `KickJob::worldKickReq` (DIFF 93.0), `KickJob::worldKickOk`, `KickJob::worldKickFail`, `KickJob::KickJob` (MATCH), `KickJob::Demander::~Demander` (MATCH), `GetGameWorldKickReason` (MATCH, see overlaps).

`deallocate_me` x5 stays `LIFT_STUB`: ObjectPool is not lifted.

## Overlaps with other cards

| File | Change | Other card | State |
| --- | --- | --- | --- |
| `CliSession.cpp` | `getCharacter`, `removeCharacter`, `getPlayingCharacter` | gap-15 | Same text as gap-15 `e10d0a5` |
| `CliSession.cpp` | `AnonymousLobbyGatePresence` ctor 0x3a3f0 | gap-15 | New |
| `CliSession.h` | `friend class CliSession` in `GameWorldPresence` | gap-15 | Same text as gap-15 |
| `CliSession.h` | `friend class KickJob` in `GameWorldPresence`; inline `LobbyGatePresence(short)` ctor | gap-15 | New |
| `CliSessionJob.cpp` | ctor/dtor | gap-05 | Same text as gap-05 |
| `StsMsgGrade.h`, `SmartCouponDaemon/NPChannelBase.h` | types | gap-15 | Same text as gap-15 `e10d0a5` |
| `TransactionChannel.h` | inline `TRecv`; inline `~Transaction() {}` (fixes LNK2001 in REF) | - | New |
| `LobbyPredefine.cpp` | `GetGameWorldKickReason` 0x96500 | gap-25-misc | New. Lifted so that `worldKickReq` is not noreturn. |

`git merge-tree 09dcab1 gap-15-clisession` (tip of clone-15 on 2026-11-25) has no conflicts.

## Decisions

- Branch order as in the original (line numbers): fail branch first in both `init` functions and in `initOk`.
- `getGradeLevelReq` keeps the original leak of the transaction on the "no group and no key" path. It is a leak, not a security bug.
- `OnLeave(_owner)` in `worldKickReq`: the original does not set rdx. Ours passes `_owner`.
- Transaction free: `delete p` (empty class operator delete) and then `Memory::_Manager[2]->Free`.
- No new `__declspec(thread)` variables. No inline asm or byte tricks. No new `/INCLUDE` pragmas.

## Next

1. Rebuild after gap-15 (`CliSession::finalize`) and gap-04 (NP senders). Recheck the 15 DIFF and the unpaired ID.
2. Recheck `LobbyJobTransaction::Set` in NOREF when a second caller is lifted.
