# Handoff: lift-lobbydaemon-gap-15-clisession

Date: 2026-11-25. Branch: `gap-15-clisession`.
Base: `ad8ae58`. This is fix7 `e68e5d0` plus merge gap-05 `d1a92d7` plus merge gap-04 `f88042e`.
Code commit: `f95b4e4`. This handoff is in the next commit.

## Base merges

| Merge | Why |
| --- | --- |
| gap-05 `d1a92d7` | The card asks for it. |
| gap-04 `f88042e` | `logout`, `cleanupCharge` and `completeRequestChargeStop` call the NP senders of gap-04. gap-04 has an open review reject (`SendRequestPresenceKick`). In this proof the item gets accept. |

## Scope

| Module | Card IDs | NOREF MATCH | NOREF DIFF |
| --- | --- | --- | --- |
| CliSession | 19 | 13 | 6 |
| LobbyMessage | 1 | 1 | 0 |
| LobbyService | 4 | 3 | 1 |
| Total | 24 | 17 | 7 |

All 24 IDs are paired in NOREF. Before this card, 0 were paired.

Scope additions (not card IDs):

- `GameTimeScheduler::Unschedule` 0x4c6a0. `releaseScheduledEndTime` calls it. A stub callee makes the caller noreturn under LTCG.
- `CliSessionStopPcCafeChargeMessage::~CliSessionStopPcCafeChargeMessage` 0x32b60 (empty body).
- `struct UserPromotionReward` layout (size 0x128, static_asserts). Its PDB layout is not in the type dump. ❓
- `StsMsgLib::_StsMsgResponseChargeRequestStop` and `npInitResponse` moved from `NPServiceChannel.cpp` to `NPServiceChannel.h`. `completeRequestChargeStop` builds the ok response inline, as the original does.
- Access helpers (`friend`): GameServiceLocation, GameWorldPresence, GameTimeScheduleNode, GameTimeQueue, MileageSession, MileageManager. No PDB in the set has friend records.

## What changed

- Bodies come from the 2019 + PDB pseudocode. PDB names and PDB return types only. The server checks stay.
- `LobbyService::Fetch` 0x6c330 is lifted first. The 3 service `Fetch` bodies that call it now pair and MATCH.
- `logout` 0x34750 and `cleanupCharge` 0x35fc0 are lifted before `finalize` 0x33cc0 is measured.
- `StsMsgGrade.h` and `NPChannelBase.h` both define the StsMsgLib base types. `NPChannelBase.h` now defines `LIFT_STSMSG_BASE_TYPES`. `StsMsgGrade.h` skips its copy when the macro is set. A TU that includes both headers must include `NPChannelBase.h` (through `NPServiceChannel.h`) first. Layouts and enum values are the same in both headers.
- `TLobbyError` with a DB result uses two stores (`if (dbrtn != 0) ... else ...`), as the original does. A ternary gives one store and a DIFF.
- `ReserveStopPlay` has one `_lock.Leave()` for all paths (`goto done`), as the original does.
- `UpdateTimeBasedPlayReward` shifts by -1 when no rule has the reward, as the original does. The x64 `shl` masks the count to 31, so the byte gets no bit. ❓
- CMakeLists is not changed. No baseline is changed. No new `__declspec(thread)` variable. No new `/INCLUDE` pragma. No inline asm or byte tricks.

## Checks

| Check | Result |
| --- | --- |
| `pilot.py gate` (24 card IDs, REF `main-build-WGL5MAyA`, NOREF `noref-build-oiw22seM`, both `f95b4e4`) | 24 of 24 clear; eligible pool 337 -> 361 |
| `pilot.py gate` at base `ad8ae58` | 0 of 24 clear |
| `gate_full.sh` (fresh clone of `f95b4e4`) | rc 0, gate ok, parity ok, 782 s |
| `proof.py --base ad8ae58 --candidate f95b4e4` (strict for 5 exes, base and candidate) | verdict `review`; 0 lost MATCH, 0 strict regress, 0 cfg regress; 1 credited, 5 review items |
| `review.py run` (fresh ledger) | 3 accept, 2 reject, 0 park |
| `integrate.check_proof` (dry) | Refused: the 2 rejects have no accept receipt |

## Review rejects

| Item | Exact reason |
| --- | --- |
| `CliSession::UpdateCharacterLevel` (not a card ID; precheck P3_imm) | `TLobbyError` TLS offset is 0x8 in the build and 0x60 in the original. The order of the `__declspec(thread)` variables decides the offset. This card adds no thread variable. The same offset gap is in all `TLobbyError` stores. |
| `ExtendJumpingCharacterCreationQuotaService::Fetch` 0x6f000 (card ID) | The original loads `ID128_GUID_ZERO` into xmm6 before the `Packet::Allocate` call. The build loads it after the call. This body is older than this card. It pairs now because `LobbyService::Fetch` is lifted. The source form that gives the early load is not known. ❓ |

## MATCH

| Exe | Before (`ad8ae58`) | After (`f95b4e4`) | Lost |
| --- | --- | --- | --- |
| CacheGate | 456 | 456 | 0 |
| LobbyGate | 658 | 658 | 0 |
| SmartCouponDaemon | 630 | 630 | 0 |
| PostOfficeDaemon | 694 | 694 | 0 |
| LobbyDaemon (REF) | 675 | 680 | 0 |
| LobbyDaemon (NOREF) | 1031 | 1052 | 1 (see below) |

The proof uses the Docs baseline for LobbyDaemon REF (674). The full build of `ad8ae58` gives 675.
gap-04/05 IDs (72): REF MATCH 1 -> 1, so 0 became REF MATCH. NOREF MATCH 52 -> 53.

NOREF lost MATCH (not in the proof; the proof reads the REF full build):
`NPGameServiceChannel::SendResponseChargeRequestStopFail` 0xd1310 goes MATCH -> DIFF 84.1.
Cause: it now has one caller (`completeRequestChargeStop`) with constant arguments. LTCG propagates `L"ErrBadData"` and 4 into the body. The original has a second caller, `Handle_SrvCharge_RequestStop` 0xcd5e0 (NPLobbyMessageHandler). That handler is not in the lift yet. Expect MATCH again when it is lifted. ❓

## Open items

| ID / item | Status | Cause |
| --- | --- | --- |
| `CliSession::finalize` 0x33cc0 | DIFF 33.3 | The original inlines `setPresence(nullptr)`. LTCG does not inline it in our build. ❓ |
| `CliSession::completeRequestChargeStop` 0x35eb0 | DIFF 91.5 | The `SendResponseChargeRequestStopFail` constants move into the callee (see above). |
| `CliSession::HandleGameGetGradeList` 0x36240 | DIFF 89.9 | The original calls `FragmentPacket::FragmentPacket` and `Packet::Allocate` out of line. Ours inlines them. |
| `CliSession::UpdateTimeBasedPlayReward` 0x38670 | DIFF 95.7 | Schedule search loop form (consts 0x6, 0x870 vs 0x138). ❓ |
| `CliSession::UpdateAccountExp` 0x38930 | DIFF 92.3 | `ExpInfo` copy form and `TLobbyError` TLS offset. ❓ |
| `CliSession::ReserveStopPlay` 0x39820 | DIFF 91.7 | Block order of the fail path. ❓ |
| `LobbyService::Fetch` 0x6c330 | DIFF 96.3 | The build has the constant 0x3a (line 58). The original makes it another way. ❓ |
| `CliSession::UpdateAccountRecycleTime` 0x38cc0 | LIFT_STUB | Not a card ID. |
| Branch | Not merged | Landing needs the owner. Nothing pushed. |
