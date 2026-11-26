# Handoff: lift-lobbydaemon-gap-25-tryentergameworldjob-part-1

Date: 2026-11-26. Branch: `gap-25`. Base: `7b92217` (fix7-stub-headers).
Code commits: `6dc33c5`, `12ff232`, `637c9b2`. This handoff is in the next commit.

## Scope

| Module | Card IDs | REF MATCH | NOREF MATCH | NOREF DIFF |
| --- | --- | --- | --- | --- |
| LobbyLobbyGatePacketHandler (`HandleLobbyLobbyGate_GetEnterWorldTokenReq`, 0xc48b0) | 1 | 0 | 0 | 1 |
| TryEnterGameWorldJob part 1 | 22 | 11 | 13 | 9 |
| Total | 23 | 11 | 13 | 10 |

The TryEnterGameWorldJob card IDs are: ctor, dtor, `_vtbl`, `GetDefinition`, `Initialize`, `deallocate_me`, `init`, `work`,
`checkSecondPasswordStatus`, `checkSecondPasswordStatusResponse`, `checkSecondPasswordStatusExpire`,
`checkSecondPasswordVerified`, `checkSecondPasswordVerifiedResponse`, `checkSecondPasswordVerifiedExpire`,
`requestGetSlot`, `responseGetSlot`, `expireGetSlot`, `restorePcReq`, `restorePcOk`, `restorePcFail`, `restorePcExpired`
and `requestChargeGetInfo`.

Scope additions:

| Item | Reason | REF |
| --- | --- | --- |
| `CliSessionJob::CliSessionJob`, `CliSessionJob::~CliSessionJob` | They were LIFT_STUB. A stub callee folds under ICF and /LTCG. Same code as gap-06. | MATCH |
| `CliSession::getCharacter`, `CliSession::removeCharacter`, inline `getCharacterInSlot` | `restorePc*` and `responseGetSlot` call them. Same code as gap-09. | `getCharacter` MATCH |
| `TransactionChannel::TRecv`, inline `Transaction::~Transaction` | The Response and Expire handlers call them. Same code as gap-06. | inlined |
| `LobbyObjectPool.cpp` (new): `ObjPool` ctor, dtor, `Checkout`, `Checkin` | The handler and `deallocate_me` call them. `Start` is not in it: `GObjPoolTimer` is not defined yet (gap-04 adds it). | Checkout DIFF 67.9, Checkin DIFF 84.4 |
| CMake line `LobbyObjectPool.cpp` after `LobbyMessage.cpp` | Source line only (R3). | n/a |
| Local StsMsgLib param structs in `TryEnterGameWorldJob.cpp` | The Response handlers read them. The PDB gives the layouts. | n/a |

## What changed

- Class layout, State enum, `_def`, `_pool` and the StateDef table come from the PDB (`pdbq`, `tools/pdbcls.py`).
- Bodies come from the 2019 + PDB pseudocode (Hex-Rays cache). PDB names only. The server checks stay.
- The zero id is the global `ID128_ID_ZERO`. The ctor, `Initialize` and the handler load it. The original loads it too.
- The handler uses global placement new: `::new (TryEnterGameWorldJob::_pool.Checkout(L"LobbyLobbyGatePacketHandler.cpp", 558)) TryEnterGameWorldJob(cliSession)`. This gives the EH state of the original.
- The handler puts the `Register` ok block first (log line 575, remove 577/578). The fail block (log 569, remove 570/571) comes second. This is the original block order.
- `responseGetSlot` has an added null check for `pwszSlotType`. This is a LIFT safety check.
- Part 2 stays LIFT_STUB (see **Not done**).

## Not done (part 2, stays LIFT_STUB)

| ID | RVA | Reason |
| --- | --- | --- |
| `TryEnterGameWorldJob::responseChargeGetInfo` | 0x7efd0 | Part 2 card. Not in the gap-25 scope. |
| `TryEnterGameWorldJob::expireChargeGetInfo` | 0x7fa60 | Part 2 card. Not in the gap-25 scope. |
| `TryEnterGameWorldJob::tryEnterGameWorld` | 0x7fbf0 | Part 2 card. Not in the gap-25 scope. |
| `TryEnterGameWorldJob::issueGameWorldToken` | 0x7ffe0 | Part 2 card. Not in the gap-25 scope. |

A LIFT_STUB callee is noreturn (abort). This changes the codegen of `work` (DIFF 93.0). Expect MATCH after part 2. ❓

## Checks

| Check | Result |
| --- | --- |
| REF linked build `637c9b2` (`builds-25/main-build-gpEh3jPK`) | 700 MATCH, 881 paired, 0 lost against `builds-06/main-build-ZQfDSNT6` |
| NOREF linked build `637c9b2` (`builds-25/noref-build-Syp8iSFf`) | 989 MATCH, 1234 paired; 1 lost (see Open items) |
| `pilot.py gate` (23 card IDs) | 16 of 23 clear (0 of 23 before); 7 `not_in_ready_pool`; eligible pool 264 -> 283 |
| `gate_fast.sh` (fresh clone of `637c9b2`) | rc 0, gate ok, parity ok, 360 s |
| `strict.py` (5 exes, `cfg` level) | rc 0, no FAIL |
| `proof.py --base 7b92217 --candidate 637c9b2` | verdict `review`; 0 reasons (0 lost MATCH, 0 checker edit, CMake OK, 0 strict regress); 15 review items |
| `review.py run` | not run. The review route decides the 15 items. |

The 7 `not_in_ready_pool` IDs: 0xc48b0, 0x7b850, 0x7bcf0, 0x7c820, 0x7cba0, 0x7d400, 0x7e570.

The 15 review items are all "new MATCH without strict full proof":

| cfg proof | Functions |
| --- | --- |
| yes | `CliSession::getCharacter`, `CliSessionJob::CliSessionJob`, `LobbyJobManager::add`, `LobbyJobTransaction::Expire`, `NPLobbyJobTransaction::Expire`, `TryEnterGameWorldJob::Initialize`, `TryEnterGameWorldJob::TryEnterGameWorldJob`, `restorePcExpired`, `restorePcReq` |
| no | `checkSecondPasswordStatusExpire`, `checkSecondPasswordVerifiedExpire`, `checkSecondPasswordVerifiedResponse`, `expireGetSlot`, `restorePcFail`, `restorePcOk` |

## MATCH

| Exe | Before | After | Lost |
| --- | --- | --- | --- |
| CacheGate | 456 | 456 | 0 |
| LobbyGate | 658 | 658 | 0 |
| SmartCouponDaemon | 630 | 630 | 0 |
| PostOfficeDaemon | 694 | 694 | 0 |
| LobbyDaemon (REF) | 674 (841 paired) | 700 (881 paired) | 0 |
| LobbyDaemon (NOREF) | 973 (1205 paired) | 989 (1234 paired) | 1 |

REF gain: +26 (11 card IDs, 15 other bodies). Planner: +18.4.
The handler 0xc48b0 is now live, so the REF chain links the job and its callees.

New REF MATCH that are not card IDs: `Character::SetShowcase`, `CliSession::getCharacter`,
`CliSessionJob` ctor, dtor and `dispatch_work`, `LobbyJob::dispatch_work`, `resume` and `~LobbyJob`,
`LobbyJobManager::Register`, `ResumeW` and `add`, `LobbyJobTransaction::Expire` and `GetTid`,
`NPLobbyJobTransaction::Expire`, `TransactionChannel::Manager::remove`.

## Open items

| Item | Cause | Owner |
| --- | --- | --- |
| NOREF lost: `LobbyJobTransaction::Set` MATCH -> DIFF 88.9 | `restorePcReq` is the only caller. LTCG puts the constant 113 into `Set`. REF inlines `Set` (no symbol). Same artifact as gap-08. | later cards |
| Handler 0xc48b0 DIFF 97.2 | `cmp s2w,ax` vs `test ax,ax`, and the `GetWid` `movzx` codegen. ❓ | open |
| dtor REF DIFF 71.9 (NOREF MATCH) | LTCG inlines `CliSessionJob::~CliSessionJob` in REF. The original does a `jmp`. | open |
| `deallocate_me` DIFF 66.7, `ObjPool::Checkout` DIFF 67.9, `ObjPool::Checkin` DIFF 84.4 | One live pool. LTCG specializes `Checkin`/`Checkout` (constants propagate, `this` removed). Expect better when more pools are live. ❓ | gap-04 and later |
| `_vtbl` not paired in REF (NOREF MATCH) | ICF / pairing. ❓ | open |
| `init` 99.3 (NOREF 96.6), `checkSecondPasswordStatus` and `checkSecondPasswordVerified` 98.4, `checkSecondPasswordStatusResponse` 96.1, `responseGetSlot` 95.7 | Scheduling and the HIWORD codegen gap from gap-06 (64-bit `shr` vs 32-bit). ❓ | open |
| `requestGetSlot`, `requestChargeGetInfo` DIFF 62.0 | The senders `SendRequestSlotGetSlot` and `SendRequestChargeGetInfo` are LIFT_STUB. | gap-04 |
| `work` DIFF 93.0 | The part-2 stubs are noreturn. | part 2 |
| `ObjPool::Initialize` not lifted | `_alloc` stays null at runtime. | gap-04 |
| Merge overlap with gap-04 | `LobbyObjectPool.cpp` and its CMake line. Keep one copy. | integrator |
| Merge overlap with gap-06 and gap-09 | `CliSessionJob`, `CliSession` and `TransactionChannel` have the same code. | integrator |
| `/INCLUDE` pragmas | Keep them in `LobbyGateChannel.cpp` lines 60-62 and `LobbyDB.cpp:1305`. | integrator |
| `vendor/zstd/src` | It is git-ignored. Scratch clones must copy it in, or the link fails. | build scripts |
