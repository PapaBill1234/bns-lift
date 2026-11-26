# Handoff: lift-lobbydaemon-gap-09-job-char-life

Date: 2026-11-25. Branch: `gap-09`. Base: `e68e5d0` (fix7).
Code commits: `91e6c4e` (lift), `92f7ea1` (repair round). This handoff is in the next commit.

## Scope

| Module | Card IDs | NOREF MATCH | NOREF DIFF |
| --- | --- | --- | --- |
| CancelWaitCharacterDeletionJob | 7 | 4 | 3 |
| CreateCharacterJob | 7 | 4 | 3 |
| DeleteCharacterJob | 15 | 7 | 8 |
| RecoverPcJob | 8 | 6 | 2 |
| Total | 37 | 21 | 16 |

All bodies of the 4 classes are lifted, except `deallocate_me` (4 functions, see Open items).
The class layouts come from `tools/pdbcls.py LobbyDaemon <Class>`: State enums, `_def` and static_asserts.

| Class | `_def` | States |
| --- | --- | --- |
| `CancelWaitCharacterDeletionJob` | `{7, StateDef, 3}` | INIT, RESTORE_LOBBY, RESTORE_GAMEWORLD, FIN |
| `CreateCharacterJob` | `{5, StateDef, 3}` | from the PDB |
| `DeleteCharacterJob` | `{6, StateDef, 7}` | from the PDB |
| `RecoverPcJob` | `{20, StateDef, 2}` | from the PDB |

Scope additions:

| Item | Reason | NOREF |
| --- | --- | --- |
| `CliSessionJob::CliSessionJob`, `~CliSessionJob`, `TransactionChannel::TRecv`, inline `~Transaction` | Same bodies as gap-06 (`4d5bcd8`). A merge with gap-06 is clean. | MATCH / inlined |
| `CliSession::getCharacter` 0x35cf0, `CliSession::removeCharacter` 0x35d30 | They were LIFT_STUB callees. A stub callee makes the caller noreturn under /LTCG. Overlap with the CliSession card (gap-15). | MATCH, MATCH |
| `CliSession::getCharacterInSlot` (inline in `CliSession.h`) | The jobs call it. It compares the slot id with `ID128_ID_ZERO`, as the original does. | inlined |
| `RuleSet::CheckName` 0x6bfc0, `class RuleSet`, `JapaneseSpecialCharRule` | `CreateCharacterJob` calls it. Without it the link fails. | DIFF 91.7 |
| `LobbyJobParams.h`: `CancelWaitCharacterDeletionReqParam`, `CreateCharacterReqParam` (0x160), `DeleteCharacterReqParam` (0x18) | The jobs read them. The PDB gives the layouts. | n/a |

## What changed

- Bodies come from the 2019 + PDB pseudocode. PDB names and PDB return types only. The server checks stay.
- `CreateCharacterJob::init` checks the size of the make data and the name terminator. The Alloc result and the slot type pointer are checked for null.
- `Character` has no destructor declaration. `DeleteCharacterJob::directDelete` and `CreateCharacterJob` free the showcase and the object by hand (`Character.cpp` line 51, as in the scalar deleting destructor 0x33c80).
- Repair round (`92f7ea1`):
  - Slot id zero checks compare with `ID128_ID_ZERO`, not with literal 0.
  - `DeleteCharacterJob::checkSecondPassword*Expire`: the `_owner->_state != 0x20000` branch comes first, as in the original.
  - `CancelWaitCharacterDeletionJob::work`: an if/else-if chain replaces the switch.
  - Result: +4 NOREF MATCH (`CancelWait::work`, both `*Expire`, `RecoverPcJob::Initialize`), 0 lost.

## Checks

| Check | Result |
| --- | --- |
| `pilot.py gate` (37 card IDs, REF `main-build-kykLs0j2`, NOREF `noref-build-WjRmD5Be`, both `92f7ea1`) | 37 of 37 clear; eligible pool 264 -> 303 |
| `pilot.py gate` before (`e68e5d0`, NOREF `noref-build-nKGdiiRj`) | 0 of 37 clear (37 x `ineligible_unpaired` + `ineligible_stub_header`) |
| `gate_fast.sh` (fresh clone of `92f7ea1`) | rc 0, parity ok, 199 s |
| `strict.py` (5 exes, `cfg` level) | no FAIL; 0 strict regress, 0 cfg regress |
| `proof.py --base e68e5d0 --candidate 92f7ea1` | verdict `review`; 0 reasons, 0 lost MATCH, 1 credited, 1 review item |
| `integrate.check_proof` (dry) | REFUSED: the review item has a reject receipt (see below) |

## MATCH

| Exe | Before | After | Lost |
| --- | --- | --- | --- |
| CacheGate | 456 | 456 | 0 |
| LobbyGate | 658 | 658 | 0 |
| SmartCouponDaemon | 630 | 630 | 0 |
| PostOfficeDaemon | 694 | 694 | 0 |
| LobbyDaemon (REF) | 674 | 676 | 0 |
| LobbyDaemon (NOREF) | 973 (1205 paired) | 999 (1267 paired) | 0 |

REF LobbyDaemon pairs no card function. No live code creates these jobs yet (the packet handlers are LIFT_STUB). LTCG drops the unreachable chain.

## Review item

| Item | Result |
| --- | --- |
| `Character::FetchCharacterInfo(FragmentPacket*)` 0x310c0, REF DIFF -> MATCH | `review.py` precheck reject (P2_cc: `je` in the original, `jne` in the build at insn 6). Not a card ID. This card does not change `Character.cpp`. The new LTCG callers change its code. |
| Effect | `integrate.check_proof` refuses the proof. The lander needs an operator exclude receipt for this item, or a fix in a later card. |

`Character::SetShowcase` is the credited new REF MATCH.

## Card IDs with DIFF (NOREF)

| Function | Score | Cause |
| --- | --- | --- |
| 4 ctors (`CancelWait` 0x18970, `Create` 0x418a0, `Delete` 0x45120, `RecoverPc` 0x64f30) | 83.3 | The only caller (`_vtbl`) gives a null owner. LTCG removes the `addReferenceCount` call. Same cause as gap-06. ❓ |
| `CreateCharacterJob::reqGetSlot` 0x43260 | 49.2 | The callee `NPGameServiceChannel::SendRequestSlotGetSlot` 0xd03d0 is LIFT_STUB (gap-04 scope). |
| `RecoverPcJob::restoreGameWorldPcExpired` 0x664f0 | 65.4 | The source follows the pseudocode. LTCG inlines `SendRecoverCharacterFail` in our build (EH frame and /GS cookie). Inlining decision. ❓ |
| `CreateCharacterJob::createCharacterExpire` 0x44d40 | 80.4 | The original calls `Character`'s scalar deleting destructor 0x33c80 and then checks `_jumpingCharacter` and the quota config bytes. Our helper frees by hand in a different order. |
| `DeleteCharacterJob::directDelete` 0x493a0 | 88.0 | Same cause: hand-written `Character` free instead of the scalar deleting destructor. |
| `DeleteCharacterJob::scheduleDelete` 0x49770 | 94.2 | Register allocation and HIWORD codegen. ❓ |
| `CancelWait::restore` 0x196f0, `CancelWait::restoreCharacterExpire` 0x1a860, `Delete::getCharacterGoodsCountExpire` 0x47fa0, `Delete::deleteExpire` 0x49090 | 95.2-95.8 | Same instruction count. HIWORD codegen (64-bit `shr` plus `movzx` against a 32-bit `shr`) and register allocation, as in gap-06 `init`. ❓ |
| `DeleteCharacterJob::getCharacterGoodsReq` 0x47710 | 97.0 | Register allocation. ❓ |
| `DeleteCharacterJob::checkSecondPasswordStatus` 0x46440, `checkSecondPasswordVerified` 0x46ed0 | 98.4 | Load order of `_owner` and register allocation. ❓ |

## Open items

| Item | Cause | Owner |
| --- | --- | --- |
| `deallocate_me` x4 | ObjPool release path is not lifted. Not done. | later card |
| `reqGetSlot` | Needs `NPGameServiceChannel::SendRequestSlotGetSlot` 0xd03d0. | gap-04 |
| `CliSession::getCharacter`, `removeCharacter` | Also in the CliSession card scope. Keep one copy at merge. | gap-15 lander |
| `Character` destructor | Declare `~Character` in `Character.h` and use it. Expect gains in `createCharacterExpire` and `directDelete`. ❓ | Character card |
| `LobbyDB.cpp` /INCLUDE notes | Not changed. | n/a |
| `vendor/zstd/src` | It is git-ignored. Scratch clones must copy it in. | build scripts |
