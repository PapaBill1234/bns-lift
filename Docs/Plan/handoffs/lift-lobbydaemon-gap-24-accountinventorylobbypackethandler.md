# Handoff: lift-lobbydaemon-gap-24-accountinventorylobbypackethandler

Date: 2026-11-25. Branch: `gap-24`. Base: `7b92217` (origin/main; same code as fix7 `e68e5d0`).
Code commit: `e7f5f36`. This handoff is in the next commit.

## Scope

| Item | Count | REF MATCH | REF DIFF |
| --- | --- | --- | --- |
| Card IDs (`AccountInventoryLobbyPacketHandler` handlers) | 19 | 16 | 3 |
| Fragment handlers, not in the 865-ID manifest (0x8d00, 0x9750, 0x9c60, 0xb510) | 4 | 2 | 2 |
| Helpers that became live | 3 | 3 | 0 |

The fragment handlers are `ListGoodsOk`, `TakeGoodsOk`, `RetrieveLobbyServiceItemListOk` and `GoodsInventoryChangedNotify`.
The helpers are `CliSessionTable::Select_index_account`, `PacketConcatenateBuffer::Decompose(int, ...)` and `RepeatPacketDecomposer::PopRepeatCount`.

## What changed

- New data-only TU `AccountInventoryLobbyPacketLobbySideHandlerList.cpp` (1 CMakeLists.txt source line).
  It fills the 37-entry table. `AccountInventorySessionHandler::PacketHandler` is live and reads the table, so all 23 handlers become live in REF.
- `AccountInventoryLobbyPacketHandlerDef` and the table declaration moved to `AccountInventoryLobbyPacketHandler.h`.
  The null placeholder in `AccountInventoryChannel.cpp` is removed.
- `LobbyGoodsTypes.h`: `GoodsItem` (0x30) and `GoodsInventoryChangedNotifyParam` (0x28).
- `LobbyJobParams.h`: the gap-06 Ok params (`ListGoodsOkParam`, `TakeGoodsOkParam`, `RetrieveLobbyServiceItemListOkParam`).
- `AccountInventoryLobbyPacketHandler.cpp`: 23 bodies from the 2019 + PDB pseudocode. PDB names only. The server checks stay.
  BUG comments mark the "acocunt" log typos, the unchecked `Decompose` calls and the wrong log text at line 849.

## Checks

| Check | Result |
| --- | --- |
| REF card build `main-build-PlDAgJTy` (`e7f5f36`) | 868 paired, 695 MATCH (+21), 0 lost |
| NOREF card build `noref-build-p6TBOKMB` (`e7f5f36`) | 1229 paired, 991 MATCH (+18), 0 lost |
| `pilot.py gate` (19 card IDs) | 19 of 19 clear |
| `gate_fast.sh` (fresh clone of `e7f5f36`) | rc 0, gate ok, parity ok, 341 s |
| `strict.py` (5 exes, `cfg` level, candidate and base) | no FAIL |
| `proof.py --base 7b92217 --candidate e7f5f36` | verdict `review`; 0 lost, 0 strict regress, 0 cfg regress, 0 reasons, 4 credited, 17 review items |
| `review.py run` | 5 accept, 12 reject (10 precheck, 2 model), 0 park; 44,048 tokens |
| `integrate.check_proof` (dry) | REFUSED: 12 items have a reject receipt and no exclude receipt |

## MATCH

| Exe | Before | After | Lost |
| --- | --- | --- | --- |
| CacheGate | 456 | 456 | 0 |
| LobbyGate | 658 | 658 | 0 |
| SmartCouponDaemon | 630 | 630 | 0 |
| PostOfficeDaemon | 694 | 694 | 0 |
| LobbyDaemon (REF) | 674 (841 paired) | 695 (868 paired) | 0 |
| LobbyDaemon (NOREF) | 973 (1205 paired) | 991 (1229 paired) | 0 |

`ActivateGradeJob::ActivateGradeJob` is no longer paired in NOREF. It was DIFF 66.7 in the base, so no MATCH is lost.

## Open items

| Item | Cause | Owner |
| --- | --- | --- |
| 10 review rejects (precheck P3_imm) | The original keeps 0 in `rbx` and compares with `cmp bx,ax`. Ours uses `test ax,ax`, an immediate store or `mov r8d,1`. All checks in the repo use `Decompose(...) == 0`. No known source form gives the original shape. ❓ | open |
| 2 review rejects (`RetrieveLobbyServiceItemListOk`, `TakeGoodsOk`) | `RepeatPacketDecomposer` signatures differ from the PDB. PDB: protected `short PushRepeatCount(char const*, int)`, public `short PushRepeatCount(Packet const*)`, public `short PopRepeatCount()`, public `short DecRepeatCount()`. Ours: public `int` for both. The fix is shared BloodLib code: add `PacketConcatenateBuffer::OpenRepeat`/`CloseRepeat`/`DecRepeatCount`, make the overload protected and return `short`. It touches 26 LobbyGate call sites, so a separate card must do it. | next card |
| Integrate | Each of the 12 rejects needs a fix or an operator exclude receipt. | operator |
| `HelloFail` DIFF 88.9 | Not examined in detail. ❓ | open |
| `GetGoodsCountOk`, `GetGoodsCountFail` DIFF 96.3 | Same `cmp bx,ax` shape as above. ❓ | open |
| `ListGoodsOk` DIFF 98.9 | Codegen detail. ❓ | open |
| `GoodsInventoryChangedNotify` DIFF 69.0 | Callee `CliSession::NotifyGoodsInventoryChangedAlongPresence` (0x392c0) is still LIFT_STUB, so the body ends in abort. The TLobbyError TLS offset also differs. | later card |
| `PacketConcatenateBuffer::Decompose(VarData*)` DIFF 95.2 | Codegen detail. ❓ | open |
| `vendor/zstd/src` | It is git-ignored. Scratch clones must copy it in, or the link fails. | build scripts |

## Rebase on main (2026-11-26)

The lander applied the net diff `7b92217..00fbf38` 3-way on main (after gap-23). It made 1 squash commit.
`LobbyJobParams.h`: the main structs (gap-09, gap-11, gap-14) are kept. The gap-24 structs are added once.
