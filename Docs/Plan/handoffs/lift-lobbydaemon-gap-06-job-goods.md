# Handoff: lift-lobbydaemon-gap-06-job-goods

Date: 2026-11-25. Branch: `gap-06-job-goods`. Base: `e68e5d0` (fix7).
Code commits: `b203b37`, `9934bdb`, `4d5bcd8`. This handoff is in the next commit.

## Scope

| Module | Card IDs | NOREF MATCH | NOREF DIFF |
| --- | --- | --- | --- |
| GetGoodsCountJob | 8 | 6 | 2 |
| GetLobbyServiceItemJob | 8 | 6 | 2 |
| ListGoodsJob | 8 | 6 | 2 |
| ListLobbyServiceItemJob | 8 | 6 | 2 |
| TakeGoodsJob | 8 | 6 | 2 |
| Total | 40 | 30 | 10 |

The card IDs for each job are: ctor, dtor, `_vtbl`, `GetDefinition`, `init`, `work`, `*Req` and `*Timeout`.
The `*Ok` and `*Fail` handlers are also lifted. They are not card IDs.

Scope additions:

| Item | Reason | NOREF |
| --- | --- | --- |
| `CliSessionJob::CliSessionJob`, `CliSessionJob::~CliSessionJob` | They were LIFT_STUB. A stub callee folds under ICF and /LTCG. | MATCH |
| `TransactionChannel::TRecv` | LTCG inlines it into the Ok and Fail handlers. | inlined |
| `TransactionChannel::Transaction::~Transaction` inline | Without it the link fails (unresolved symbol). | n/a |
| `ListGoodsOkParam`, `TakeGoodsOkParam`, `RetrieveLobbyServiceItemListOkParam` in `LobbyJobParams.h` | The Ok handlers read them. The PDB gives the layouts. | n/a |

## What changed

- Class layouts come from `tools/pdbcls.py LobbyDaemon <Class>`: State enums, `_def`, members and static_asserts.
- Bodies come from the 2019 + PDB pseudocode. PDB names and PDB return types only. The server checks stay.
- `init` shape: `short reason = 0;`. The checks set `reason` to 5, 6 or 7.
  The success path allocates `_tran` and writes "init ok". The tail sends the Fail packet when `reason != 0`, then calls `transit(next)`.
- The gate world id in `init` is `_lgate != nullptr ? (_lgate->_rawChannel != nullptr ? (short)_lgate->_rawChannel->GetId() : 0) : 0`.
- The Ok and Fail handlers put the null-param branch first, as in the original.
- `TRecv`: if `_mgr == nullptr`, write Log and AlertSender (line 155) and return false. Else return `_mgr->remove(t)`.

## Checks

| Check | Result |
| --- | --- |
| `pilot.py gate` (40 card IDs, REF `main-build-ANFgch5E`, NOREF `noref-build-OXwWr7Zw`, both `4d5bcd8`) | 40 of 40 clear (0 of 40 before); eligible pool 264 -> 306 |
| `gate_full.sh` (fresh clone of `4d5bcd8`) | rc 0, parity ok, 1120 s |
| `strict.py` (5 exes, `cfg` level) | no FAIL |
| `proof.py --base e68e5d0 --candidate 4d5bcd8` | verdict `pass`; 0 lost MATCH, 0 strict regress, 0 cfg regress, 0 review items |
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
| LobbyDaemon (NOREF) | 973 (1205 paired) | 1010 (1259 paired) | 0 |

REF does not change. No live code creates the goods jobs yet (the packet handlers are LIFT_STUB).
LTCG drops the unreachable chain.

## Open items

| Item | Cause | Owner |
| --- | --- | --- |
| 5 ctors DIFF 77.8 (`ListLobbyServiceItemJob` 66.7) | The only caller (`_vtbl`) gives a null owner. LTCG removes the `addReferenceCount` call. Expect MATCH when real callers exist. ❓ | later cards |
| 5 `init` DIFF 97.2 (`TakeGoodsJob` 97.6) | Register allocation and HIWORD codegen differ: ours uses a 64-bit `shr` plus `movzx`, the original a 32-bit `shr`. ❓ | open |
| `getGoodsCountFail`, `listGoodsFail` 96.7; `getLobbyServiceItemFail` 94.4; `takeGoodsFail` 92.6; `getLobbyServiceItemOk` 98.6 | VS2010 tail merging and constant sharing differ. Not card IDs. ❓ | open |
| `vendor/zstd/src` | It is git-ignored. Scratch clones must copy it in, or the link fails (168 of 186 sources). | build scripts |
