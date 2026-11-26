# Handoff: lift-lobbydaemon-gap-12-job-char-sexrace

Date: 2026-11-26. Branch: `gap-12`. Base: `e68e5d0` (fix7).
Code commits: `764129f`, `43ad051`, `76ba1d0`. This handoff is in the next commit.

## Scope

| Module | Card IDs | NOREF MATCH | NOREF DIFF |
| --- | --- | --- | --- |
| ChangeCharacterRaceJob | 13 | 10 | 3 |
| ChangeCharacterSexJob | 13 | 10 | 3 |
| Total | 26 | 20 | 6 |

The card IDs for each job are: `GetDefinition`, ctor, dtor, `work`, `checkAccountInventoryItem`, `checkAccountInventoryItemTimeout`,
`tryConsumeAccountInventoryItem`, `tryConsumeAccountInventoryItemTimeout`, `changeCharacterRace`/`changeCharacterSex`,
`changeCharacter*Timeout`, `finConsumeAccountInventoryItem`, `finConsumeAccountInventoryItemTimeout` and `finServiceEntry`.
`init`, `registerServiceEntry` and the `*Ok` and `*Fail` handlers are also lifted. They are not card IDs.

The Sex job is the Race job with other RVAs, StateDef addresses, line numbers, reasons, tasks and service type.
The Sex job has no `_newRace` member. Its `_def` type is 40 (Race: 41).

Scope additions:

| Item | Reason | NOREF |
| --- | --- | --- |
| `CliSessionJob::CliSessionJob`, `CliSessionJob::~CliSessionJob` | They were LIFT_STUB. A stub callee folds under ICF and /LTCG. | MATCH |
| `TransactionChannel::TRecv` | LTCG inlines it into the Ok and Fail handlers. | inlined |
| `TransactionChannel::Transaction::~Transaction` inline | Without it the link fails (unresolved symbol). | n/a |
| `CliSession::getCharacterInSlot`, `CliSession::getLobbyService`, `Authority::Authorize` (in `CliSession.h`) | The jobs call them. Inline in the original. | inlined |
| `GameWorld::IsLive`, `Character::SetServiceStatus` | The jobs call them. Inline in the original. | inlined |
| `LobbyService::operator delete` (empty) | `registerServiceEntry` runs `delete service`. | inlined |
| Param structs in the job headers | The Ok handlers read them. The PDB gives the layouts. | n/a |
| `releasePcServiceStatus` 0x229a0 | ICF folds it with the Appearance job copy. | n/a |

`_pool` and `deallocate_me` stay LIFT_STUB.

## What changed

- Class layouts come from `tools/pdbcls.py LobbyDaemon <Class>`: State enums, `_def`, members and static_asserts.
- Bodies come from the 2019 + PDB pseudocode. PDB names and PDB return types only. The server checks stay.
- The ctors set `_slotid(ID128_GUID_ZERO)`. `getCharacterInSlot` compares with `ID128_ID_ZERO` (same text as gap-09).
- `init` sends the Fail packet and calls `transit(FIN)` in each failure branch.
- `registerServiceEntry` runs `delete service` in each failure branch and calls Free once.
- `checkAccountInventoryItemOk` keeps the early-return form. The single-transit form made it worse (93.3 -> 91.6).
- The other Ok handlers use one `transit` call.

## Checks

| Check | Result |
| --- | --- |
| `pilot.py gate` (26 card IDs, REF `main-build-vSnHZSDH`, NOREF `noref-build-WKRznEND`, both `76ba1d0`) | 26 of 26 clear (0 of 26 before); eligible pool 264 -> 292 |
| `gate_fast.sh` (fresh clone of `76ba1d0`) | rc 0, parity ok, 953 s |
| `strict.py` (5 exes, `cfg` level) | no FAIL |
| `proof.py --base e68e5d0 --candidate 76ba1d0` | verdict `pass`; 0 lost MATCH, 0 strict regress, 0 cfg regress, 0 credited, 0 review items |
| `integrate.check_proof` (dry) | PASS |

## MATCH

| Exe | Before | After | Lost |
| --- | --- | --- | --- |
| CacheGate | 456 | 456 | 0 |
| LobbyGate | 658 | 658 | 0 |
| SmartCouponDaemon | 630 | 630 | 0 |
| PostOfficeDaemon | 694 | 694 | 0 |
| LobbyDaemon (REF) | 674 | 674 | 0 |
| LobbyDaemon (NOREF) | 973 (1205 paired) | 1004 (1254 paired) | 0 |

REF does not change. No live code creates the jobs yet (the packet handlers are LIFT_STUB).
LTCG drops the unreachable chain.

## Open items

| Item | Cause | Owner |
| --- | --- | --- |
| `tryConsumeAccountInventoryItem` 0x20a10/0x24a10 and `finConsumeAccountInventoryItem` 0x21dc0/0x25db0 DIFF 97.0 | consts 91. HIWORD codegen: ours uses a 64-bit `shr` plus `movzx`, the original a 32-bit `shr`. The inlined `AccountInventoryChannel::SendFinishWarehouseItemConsumptionReq` is DIFF in the base too. ❓ | open |
| `finServiceEntry` 0x225e0/0x265d0 DIFF 91.4 | calls 74. The original duplicates the fail tail and uses another block and register order. ❓ | open |
| `init` 94.9, `registerServiceEntry` 96.5, `checkAccountInventoryItemOk` 93.3 | Branch shape and tail merging differ. Not card IDs. ❓ | open |
| `changeCharacter*Ok` 98.5; `tryConsume*Ok`, `finConsume*Ok` 98.8 (Race), 97.0 (Sex) | Tail merging and constant sharing differ. Not card IDs. ❓ | open |
| `vendor/zstd/src` | It is git-ignored. Scratch clones must copy it in, or the link fails. | build scripts |
