# Handoff: lift-lobbydaemon-gap-07-job-wnp-a

Date: 2026-11-25. Branch: `gap-07-job-wnp-a`. Base: `e68e5d0` (fix7).
Code commits: `d62e4f7`, `aab86d6`. This handoff is in the next commit.

## Scope

| Module | Card IDs | NOREF MATCH | NOREF DIFF |
| --- | --- | --- | --- |
| InitCliSessionWnpTokenJob (incl. `GetDefinition` 0x3c080 in CliSessionManager) | 3 | 2 | 1 |
| StartCliSessionWnpTokenJob | 18 | 2 | 16 |
| Total | 21 | 4 | 17 |

All 21 card IDs have a real body. No card ID is unpaired.

Scope additions:

| Item | Reason | NOREF |
| --- | --- | --- |
| `CliSessionJob::CliSessionJob`, `CliSessionJob::~CliSessionJob` | Same gap-06 bodies. They were LIFT_STUB in the base. | MATCH |
| `NPServiceChannel::SendRequestSlotListSlots` | `listSlotsReq` calls it. The PDB marks it inline. | inlined |
| `StsMsgLib::_StsMsgRequestSlotListSlots` | The sender builds it. Size 0x28, static_asserts. | n/a |
| `NPLobbyJobTransaction::operator delete` (empty, class scope) | The original does `delete tr;` then `Free(tr, ...)`. The global operator delete is empty. `CliSession.h` has the same pattern. | n/a |

## What changed

- `InitCliSessionWnpTokenJob.h/.cpp`: PDB layout (size 0x58), State `INIT`/`FIN`, `_def`, `_vtbl`, `GetDefinition`, `work`.
- `StartCliSessionWnpTokenJob.h`: full PDB layout (14 members, size 0x1E0), State enum 0-16, static_asserts in a friend struct.
- `StartCliSessionWnpTokenJob.cpp`: StateDef (17 entries), `_def`, `GetDefinition`, ctor, dtor, `work`, `consumeToken`, 6 `*Expire` bodies, `listUserLastPresencesReq`, `listSlotsReq`, `createSlotsReq`, `setSlotDataReq`, `setSlotDataResponse`, `presenceLoginReq`, `getUserProfileReq`.
- Bodies come from the 2019 + PDB pseudocode. PDB names only. The server checks stay.
- The fail path sets `_owner->_state = 0x60000` (PDB `CSS_FIN`). `setSlotDataResponse` checks `0x10002` (PDB `CSS_INIT_verify`).
- The ctor and dtor copy the global `ID128_ID_ZERO` (rva 0x12D870), as the original does.

## Checks

| Check | Result |
| --- | --- |
| `pilot.py gate` (21 card IDs, REF `main-build-poFhGE4D`, NOREF `noref-build-ZiAen4ic`, both `aab86d6`) | 21 of 21 clear (0 of 21 before); eligible pool 264 -> 285 |
| `gate_full.sh` (fresh clone of `aab86d6`) | rc 0, parity ok |
| `strict.py` (5 exes, `cfg` level) | no FAIL |
| `proof.py --base e68e5d0 --candidate aab86d6` | verdict `pass`; 0 lost MATCH, 0 strict regress, 0 cfg regress, 0 review items |
| `review.py run` | not run: the proof has 0 review items |
| `integrate.check_proof` (dry) | PASS |

## MATCH

| Exe | Before | After | Lost |
| --- | --- | --- | --- |
| CacheGate | 456 | 456 | 0 |
| LobbyGate | 658 | 658 | 0 |
| SmartCouponDaemon | 630 | 630 | 0 |
| PostOfficeDaemon | 694 | 694 | 0 |
| LobbyDaemon (REF) | 674 | 674 | 0 |
| LobbyDaemon (NOREF) | 973 (1205 paired) | 979 (1226 paired) | 0 |

REF does not change. No live code creates the WNP-token jobs yet. LTCG drops the chain.

## Card IDs that DIFF (NOREF)

| ID | Function | Score | Cause |
| --- | --- | --- | --- |
| `InitCliSessionWnpTokenJob/0x981a0` | `work` | 66.7 | `init` (0x981c0) is LIFT_STUB. It needs the `AnonymousLobbyGatePresence` ctor 0x3a3f0. |
| `StartCliSessionWnpTokenJob/0xd23a0` | ctor | 81.0 | Ours loads `ID128_ID_ZERO` once and reuses it. The original loads it again before each store. Our global has a constant initializer in a /GL file, so LTCG may treat it as read-only. ❓ |
| `StartCliSessionWnpTokenJob/0xd2530` | `work` | 76.4 | Stub callees: `init`, the `*Response` bodies and part B. |
| `StartCliSessionWnpTokenJob/0xd31e0` | `consumeToken` | 71.2 | Stub sender (gap-04) and `CliSession::finalize` stub (gap-15). |
| 6 `*Expire` (0xd3bc0, 0xd46c0, 0xd5190, 0xd5db0, 0xd66b0, 0xd74a0) | | 84.1 | `CliSession::finalize` 0x33cc0 is LIFT_STUB. The noreturn stub cuts the tail. |
| `0xd3ce0` `listUserLastPresencesReq`, `0xd75c0` `getUserProfileReq` | | 66.8 | Stub senders (gap-04) and `finalize`. |
| `0xd47e0` `listSlotsReq` | | 80.7 | `finalize` stub. The message build order and HIWORD codegen also differ (64-bit `shr` plus `movzx` against a 32-bit `shr`). ❓ |
| `0xd52b0` `createSlotsReq` | | 73.5 | Stub sender and `finalize`. |
| `0xd5ed0` `setSlotDataReq` | | 73.1 | Stub sender and `finalize`. |
| `0xd62b0` `setSlotDataResponse` | | 98.2 | `finalize` stub. |
| `0xd67d0` `presenceLoginReq` | | 60.9 | Stub senders and `finalize`. |

## Not done

| RVA | Function | Reason |
| --- | --- | --- |
| 0x981c0 | `InitCliSessionWnpTokenJob::init` | Needs `AnonymousLobbyGatePresence` ctor 0x3a3f0 (other card). |
| 0x3c090 | `InitCliSessionWnpTokenJob::deallocate_me` | Not a card ID. |
| 0xd2350 | `StartCliSessionWnpTokenJob::deallocate_me` | Not a card ID. |
| `init` and 28 other bodies (`*Response`, `getGameTime*`, `getGradeLevel*`, `listAllGrades*`, `listUserBans*`, `getRMSInquiry*`, `getUserPromotionStatus*`, `loginAccount`, `checkIntialUserName`) | `StartCliSessionWnpTokenJob` | Part B (gap-13). |

## Open items

| Item | Cause | Owner |
| --- | --- | --- |
| 14 DIFF bodies call `CliSession::finalize` | LIFT_STUB callee. Measure again after gap-15. | gap-15 |
| Stub NPGameServiceChannel senders | Measure again after gap-04. | gap-04 |
| Ctor 81.0 | `ID128_ID_ZERO` load is shared by LTCG. The fix is in BloodLib, outside this card. ❓ | open |
| HIWORD codegen in `listSlotsReq` | Same gap-06 open item. ❓ | open |
| `vendor/zstd/src` | It is git-ignored. Scratch clones must copy it in. The linked build scripts print rc 0 on link FAIL: check `run.log`. | build scripts |
