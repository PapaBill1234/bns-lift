# Handoff: lift-lobbydaemon-gap-14-job-slot-add

Date: 2026-11-26. Branch: `gap-14`. Base: `e68e5d0` (fix7).
Code commits: `e9614ff`, `4f3ffb0`, `1372721`, `f08578f`. This handoff is in the next commit.

## Scope

| Module | Card IDs | NOREF MATCH | NOREF DIFF |
| --- | --- | --- | --- |
| AddSlotJob | 18 | 12 | 6 |
| BindCharacterSlotJob | 6 | 5 | 1 |
| Total | 24 | 17 | 7 |

Card IDs that MATCH:
- AddSlotJob: ctor, dtor, `GetDefinition`, `work`, `checkAccountInventoryItem`, `checkAccountInventoryItemTimeout`, `checkSlotCapacityAck`, `checkSlotCapacityExpire`, `createSlotExpire`, `tryConsumeAccountInventoryItemTimeout`, `finConsumeAccountInventoryItemTimeout`, `finServiceEntry`.
- BindCharacterSlotJob: `_vtbl`, `GetDefinition`, `work`, `expireGetSlot`, `bindCharacterSlot`.

Scope additions:

| Item | Reason | NOREF |
| --- | --- | --- |
| AddSlotService steps in `LobbyService.cpp` | AddSlotJob starts the service. | DIFF 40-63 (LobbyDB SlotAddition callees are LIFT_STUB) |
| `CliSession::getCharacter` | The bind and add steps call it. | MATCH |
| `CliSessionJob::CliSessionJob`, `~CliSessionJob` | A stub callee folds under ICF and /LTCG. | MATCH |
| `TransactionChannel::TRecv` | LTCG inlines it into the Ok and Fail handlers. | inlined |
| `LobbyJobParams.h` slot params with static_asserts | The Ok handlers read them. The PDB gives the layouts. | n/a |

## What changed

- Class layouts come from the PDB: State enums, `_def`, members and static_asserts.
- Bodies come from the 2019 + PDB pseudocode. PDB names only. The server checks stay (slot count limit, item checks).
- `AddSlotJob.cpp` includes `crt_cpp_overload.h` under clang-cl. Without it, `swprintf_s` with an array argument does not compile (gate FAIL).
- The ctor copies the 2 qwords of `ID128_GUID_ZERO` into `_slotId`, as the original does (0xd2fb).
- `checkSlotCapacityAck` tests the overflow first and has separate returns (0xecc5).
- `bindCharacterSlot` puts the fail path before the ok path (0x182ea).

## Checks

| Check | Result |
| --- | --- |
| `pilot.py gate` (24 card IDs, REF `main-build-bFgcQmD4`, NOREF `noref-build-ABAmQpID`, both `f08578f`) | 24 of 24 clear (0 of 24 before); eligible pool 264 -> 294 |
| `gate_fast.sh` (scratch clone at `f08578f`) | rc 0, parity ok |
| `strict.py` (5 exes, `cfg` level) | no FAIL |
| `proof.py --base e68e5d0 --candidate f08578f` | verdict `pass`; 0 lost MATCH, 0 strict regress, 0 cfg regress, 0 review items; 1 credited (`Character::SetShowcase`) |
| `review.py run` | not run: the proof has 0 review items |
| `integrate.check_proof` (dry) | PASS |

## MATCH

| Exe | Before | After | Lost |
| --- | --- | --- | --- |
| CacheGate | 456 | 456 | 0 |
| LobbyGate | 658 | 658 | 0 |
| SmartCouponDaemon | 630 | 630 | 0 |
| PostOfficeDaemon | 694 | 694 | 0 |
| LobbyDaemon (REF) | 674 (841 paired) | 675 (842 paired) | 0 |
| LobbyDaemon (NOREF) | 973 (1205 paired) | 999 (1246 paired) | 0 |

The new REF MATCH is `Character::SetShowcase`. `CliSession::UpdateCharacterData` went from 55.0 to 81.2.

## Open items

| Item | Cause | Owner |
| --- | --- | --- |
| `AddSlotJob::_vtbl` DIFF 22.2 | With the `ID128_GUID_ZERO` copy the ctor is not inlined into `_vtbl`. With zero stores `_vtbl` MATCH and the ctor DIFF 83.3. Both give 17 of 24. ❓ | open |
| `checkSlotCapacity`, `createSlot` 98.4; `tryConsumeAccountInventoryItem`, `finConsumeAccountInventoryItem` 97.0 | Scheduling of `&_owner->_acb._id`: ours `add rax,0x30`, the original `lea rax,[rdx+0x30]`. ❓ | open |
| `registerServiceEntry` 92.7 | Order and layout of the indirect and Log calls differ. ❓ | open |
| `BindCharacterSlotJob::reqGetSlot` 49.2 | Callee `NPGameServiceChannel::SendRequestSlotGetSlot` (0xd03d0) is LIFT_STUB. | gap-04 |
| AddSlotService steps DIFF 40-63 | LobbyDB SlotAddition callees (0xb0c30, 0xb11d0, 0xb1700, 0xb1f60, 0xb2490) are LIFT_STUB. | later cards |
| `deallocate_me` x2 | They depend on ObjPool. | later cards |
| `vendor/zstd/src` | It is git-ignored. Scratch clones must copy it in. | build scripts |
