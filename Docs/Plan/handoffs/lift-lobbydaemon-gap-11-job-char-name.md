# Handoff: lift-lobbydaemon-gap-11-job-char-name

Date: 2026-11-25. Branch: `gap-11`. Base: `e68e5d0` (fix7).
Code commit: `ede938a`. This handoff is in the next commit.

## Scope

| Module | Card IDs | NOREF MATCH | NOREF DIFF |
| --- | --- | --- | --- |
| ChangeUserNameJob | 12 | 10 | 2 |
| CreateInitialUserNameJob | 7 | 6 | 1 |
| RenameCharacterJob | 13 | 7 | 6 |
| Total | 32 | 23 | 9 |

All 32 card IDs are lifted. The `*Ok` and `*Fail` handlers, `init` and the helpers are also lifted. They are not card IDs.

Scope additions:

| Item | Reason | NOREF |
| --- | --- | --- |
| `CliSessionJob::CliSessionJob`, `CliSessionJob::~CliSessionJob` | They were LIFT_STUB. A stub callee folds the caller under ICF and /LTCG (gap-06 bodies). | MATCH |
| `TransactionChannel::TRecv`, `Transaction::~Transaction` inline | Same as gap-06. The Ok and Fail handlers need them. | inlined |
| `RuleSet::CheckName` (`RuleSet.h/.cpp`) | `CreateInitialUserNameJob::init` and `ChangeUserNameJob::init` call it. | DIFF |
| `LobbyService.cpp/.h`: `RenameUserService` Start/Finish, `RenameCharacterService` methods, inline `RenameUserService::Setup` | The jobs call them. | inlined or DIFF |
| `NPServiceChannel.h/.cpp`: StsMsg request structs, `SendRequestAuthChangeMyUserNameIncomplete`, `SendRequestFriendSendMessage` | `changeUserNameReq` and `sendFriendMessageToNP` call them. | MATCH / DIFF |
| `CliSession.h` (`Authorize`, `getCharacterInSlot`, `getLobbyService`), `GameWorld.h` (`IsLive`) | Inline accessors that the jobs use (same hunks as clone-12). | inlined |
| `LobbyJobParams.h` | 3 param structs with static_asserts. The PDB gives the layouts. | n/a |

## What changed

- Class layouts come from `tools/pdbcls.py LobbyDaemon <Class>`. Sizes: `RenameCharacterJob` 0x138, `ChangeUserNameJob` 0x110, `CreateInitialUserNameJob` 0x68. Each has static_asserts.
- Bodies come from the 2019 + PDB pseudocode. PDB names and PDB return types only. The server checks stay.
- `_def`: `RenameCharacterJob` {28, 7 states}, `ChangeUserNameJob` {37, 5 states}, `CreateInitialUserNameJob` {31, 2 states}.
- `RenameCharacterJob::init` sends the ChangeCharacterAppearance fail packet when account-inventory is not available. The original does the same. The client sees this packet, so the lift keeps it (LIFT note in the code).
- NP error mapping in `ChangeUserNameJob`: 3003/3042 -> 217, 3041 -> 216, 3336 -> 219, 3743 -> 218, 10/3035 -> 6, 4/48/3000/3002 -> 2, other -> 1.
- NP error mapping in `CreateInitialUserNameJob`: 3003/3042 -> 229, 3041 -> 228, 3336 -> 231, 3743 -> 230. `RuleSet::CheckName` mapping: 6/224/225/227/226, default 1.
- The NP transaction is freed with an explicit destructor call plus `Free` (gap-05 pattern). `delete` would free it twice.
- `SendRequestAuthChangeMyUserNameIncomplete` uses `L"dummy"` as the hash. The original inlines the call with the same arguments (disassembly).

## Checks

| Check | Result |
| --- | --- |
| `pilot.py gate` (32 card IDs, REF `main-build-l72ddWL0`, NOREF `noref-build-WRTRM74v`, both `ede938a`) | 32 of 32 clear (0 of 32 before); eligible pool 264 -> 304 |
| `gate_fast.sh` (fresh clone of `ede938a`, `/data/parity-v2/gap/full-11`) | rc 0, parity ok, 456 s |
| `strict.py` (5 exes, `cfg` level) | no FAIL; 0 strict regress, 0 cfg regress (LobbyDaemon cfg 594 -> 596, LobbyGate 515 -> 516) |
| `proof.py --base e68e5d0 --candidate ede938a` | verdict `pass`; 0 lost MATCH, 0 strict regress, 0 cfg regress, 0 review items |
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
| LobbyDaemon (NOREF) | 973 (1205 paired) | 998 (1266 paired) | 2 |

REF does not change. No live code creates the name jobs yet (the packet handlers are LIFT_STUB). LTCG drops the unreachable chain.
NOREF: 27 new MATCH, 2 lost (see Open items).

## Card IDs that are DIFF (NOREF)

| Function | Score | Signal | Cause |
| --- | --- | --- | --- |
| `RenameCharacterJob::RenameCharacterJob` | 83.3 | refs 50 | The only caller (`_vtbl`) gives a null owner. LTCG removes the `addReferenceCount` call (same as gap-06 ctors). ❓ |
| `RenameCharacterJob::checkAccountInventoryItem` | 90.3 | calls 88, refs 83 | Callee set differs on the pc path. ❓ |
| `RenameCharacterJob::tryConsumeAccountInventoryItem` | 97.0 | consts 91 | One constant differs. ❓ |
| `RenameCharacterJob::finConsumeAccountInventoryItem` | 97.0 | consts 91 | One constant differs. ❓ |
| `RenameCharacterJob::renameCharacter` | 93.3 | refs 80 | Data references differ. ❓ |
| `RenameCharacterJob::finServiceEntry` | 97.4 | calls 92 | One call differs (inline choice). ❓ |
| `ChangeUserNameJob::consumeLobbyServiceItem` | 96.3 | consts 89 | One constant differs. ❓ |
| `ChangeUserNameJob::finLobbyService` | 89.1 | calls 74, refs 93 | Call order or inline choice around `releaseService`. ❓ |
| `CreateInitialUserNameJob::changeUserNameReq` | 95.1 | calls 96, consts 96, refs 93 | The inlined NP send differs a little. ❓ |

## Open items

| Item | Cause | Owner |
| --- | --- | --- |
| 9 card IDs DIFF (table above) | Codegen gaps. The source shape is not known. ❓ | per-function loop |
| NOREF lost: `LobbyGateChannel::SendChangeCharacterAppearanceWithAccountInventoryItemFail` 100 -> 95.2 (consts 86: ours has 0x7) | `RenameCharacterJob::init` is now its only live caller. It passes the constant reason 7, and LTCG propagates it into the body (funcdiff `--show`). The original has more callers. Expect MATCH when the appearance jobs are lifted. | later cards |
| NOREF lost: `NPLobbyJobTransaction::Set` 100 -> 88.9 (consts 67: ours has 0x47) | `CreateInitialUserNameJob::changeUserNameReq` is now its only live caller with `Set(this, 71)`. LTCG propagates the task 71 (0x47) into the body (funcdiff `--show`). The original has more callers. Expect MATCH when other NP jobs call it. | later cards |
| Not card IDs: `ChangeUserNameJob` init 99.4, changeUserName 91.7, check/consume Ok/Fail 94-98; `RenameCharacterJob` init 96.4, registerServiceEntry 93.2, Ok/Fail 94-97, sendFriendMessageToNP 97.7; `CreateInitialUserNameJob::init` 97.0 | Codegen gaps. ❓ | open |
| `vendor/zstd/src` | It is git-ignored. Scratch clones must copy it in, or the link fails. | build scripts |
