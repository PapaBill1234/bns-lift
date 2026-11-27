# lift-gamedaemon-e9: Easy leaves (GameDaemon): guildtran_h, posttran_h, instantpaymenttran_h, accountinventorytran_h

| Item | Value |
| --- | --- |
| Exe | GD |
| Source build | GameDaemon 2019 + PDB (VS2010 SP1) |
| Exe file | `<work-root>/ida/lift/GameDaemon/GameDaemon.exe` |
| PDB | `<work-root>/ida/lift/GameDaemon/GameDaemon.pdb` |
| Pseudocode | `~/.cache/bns-lift/hr/GameDaemon/<stem>.c` |
| Pseudocode index | `~/.cache/bns-lift/hr/GameDaemon/index.tsv` (stem, rva, name, first, last, status, source file, part) |
| Wave | E |
| Model | sonnet:high |
| Depends on | `lift-gamedaemon-0e` |
| Pattern | `src/Server/LobbyDaemon/LobbyJob.cpp` |
| Plan | `Docs/Plan/gamedaemon-lift.md` sections 1, 3, 5 |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Grep `Docs/Parity/lessons.md` for A2 (block order), A6 (per-exe path literals), A12 (PDB member types), A18 (destructors), A21 (PDB facts) and A22 (per-exe source form). Do not read it in full.
- Pattern: `src/Server/LobbyDaemon/LobbyJob.cpp`. Read it one time. Use its form for the functions of this card.

## Scope

36 functions, about 268 pseudocode lines (about 2,144 tokens). Stems: `guildtran_h`, `posttran_h`, `instantpaymenttran_h`, `accountinventorytran_h`.

Wave E (owner order 2026-11-27: the easiest work first). Each function in this card is a leaf: its body calls no other counted function that needs a lift. Thus a `LIFT_STUB` callee cannot keep it DIFF. Each function has at most 30 pseudocode lines. Ease key: 7.4 cost per function (rule in `Docs/Plan/gamedaemon-lift.md` section 3).

Lift only the functions in the table. The other functions of these stems are in later W cards. Those cards depend on this card.

| n | Exe | RVA | PDB name | Stem | Lines | Form |
| ---: | --- | --- | --- | --- | ---: | --- |
| 1 | GD | `0x121260` | `TryRegisterGuildTran::GetDefinition` | guildtran_h | 7 | getter |
| 2 | GD | `0x121270` | `RenameGuildTran::GetDefinition` | guildtran_h | 7 | getter |
| 3 | GD | `0x121280` | `DeleteGuildTran::GetDefinition` | guildtran_h | 7 | getter |
| 4 | GD | `0x121290` | `DepositInGuildBankTranEx::GetDefinition` | guildtran_h | 7 | getter |
| 5 | GD | `0x1212a0` | `ContractGuildCraftTran::GetDefinition` | guildtran_h | 7 | getter |
| 6 | GD | `0x1212b0` | `AssentGuildCraftTran::GetDefinition` | guildtran_h | 7 | getter |
| 7 | GD | `0x1212c0` | `MakeGuildCraftTran::GetDefinition` | guildtran_h | 7 | getter |
| 8 | GD | `0x1212d0` | `DonateGuildCraftNormalMaterialTran::GetDefinition` | guildtran_h | 8 | getter |
| 9 | GD | `0x1212e0` | `DonateGuildCraftBrandMaterialTran::GetDefinition` | guildtran_h | 7 | getter |
| 10 | GD | `0x1212f0` | `UpdateGuildLevelTran::GetDefinition` | guildtran_h | 7 | getter |
| 11 | GD | `0x121300` | `ContractGuildUniformTran::GetDefinition` | guildtran_h | 7 | getter |
| 12 | GD | `0x121310` | `DonateGuildUniformTran::GetDefinition` | guildtran_h | 7 | getter |
| 13 | GD | `0x121320` | `MakeGuildUniformTran::GetDefinition` | guildtran_h | 7 | getter |
| 14 | GD | `0x121330` | `RegisterGuildUniformTran::GetDefinition` | guildtran_h | 7 | getter |
| 15 | GD | `0x121340` | `PutOnGuildUniformTran::GetDefinition` | guildtran_h | 7 | getter |
| 16 | GD | `0x121350` | `RegisterGuildUniformWithDeletionTran::GetDefinition` | guildtran_h | 8 | getter |
| 17 | GD | `0x121360` | `IncreaseUniformRegistrationQuotaTran::GetDefinition` | guildtran_h | 8 | getter |
| 18 | GD | `0x1960e0` | `MarkExpressPostTran::GetDefinition` | posttran_h | 7 | getter |
| 19 | GD | `0x1960f0` | `DetachPostAttachmentTran_IndetachFixed::GetDefinition` | posttran_h | 8 | getter |
| 20 | GD | `0x196100` | `DeliverPostTran::GetDefinition` | posttran_h | 7 | getter |
| 21 | GD | `0x1107c0` | `InstantPaymentTran::GetDefinition` | instantpaymenttran_h | 7 | getter |
| 22 | GD | `0x1107d0` | `InstantPaymentJob::DataId` | instantpaymenttran_h | 7 | leaf |
| 23 | GD | `0x1ee480` | `InstantPaymentDrawSlateNewStoneSubJob::DataId` | instantpaymenttran_h | 9 | getter |
| 24 | GD | `0x1c30b0` | `AccountInventoryGetGoodsCountTran::GetDefinition` | accountinventorytran_h | 7 | getter |
| 25 | GD | `0x1c30c0` | `AccountInventoryListGoodsTran::GetDefinition` | accountinventorytran_h | 7 | getter |
| 26 | GD | `0x1c30d0` | `AccountInventoryTakeGoodsTran::GetDefinition` | accountinventorytran_h | 7 | getter |
| 27 | GD | `0x1c30e0` | `AccountInventoryRetrieveWarehouseLobbyServiceItemListTran::GetDefinition` | accountinventorytran_h | 8 | getter |
| 28 | GD | `0x1c30f0` | `AccountInventoryRetrieveWarehouseItemListTran::GetDefinition` | accountinventorytran_h | 8 | getter |
| 29 | GD | `0x1c3100` | `AccountInventoryTakeWarehouseItemTran::GetDefinition` | accountinventorytran_h | 8 | getter |
| 30 | GD | `0x1c3110` | `AccountInventoryJumpingCharacter2TicketTran::GetDefinition` | accountinventorytran_h | 8 | getter |
| 31 | GD | `0x1c3120` | `AccountInventoryBoardGachaParticipationCountPerSeasonTran::GetDefinition` | accountinventorytran_h | 8 | getter |
| 32 | GD | `0x1c3130` | `AccountInventoryBoardGachaParticipationInfoPerPcTran::GetDefinition` | accountinventorytran_h | 8 | getter |
| 33 | GD | `0x1c3140` | `AccountInventoryBoardGachaDrawByItemTran::GetDefinition` | accountinventorytran_h | 8 | getter |
| 34 | GD | `0x1c3150` | `AccountInventoryBoardGachaDrawByInstantPaymentTran::GetDefinition` | accountinventorytran_h | 8 | getter |
| 35 | GD | `0x1c3160` | `AccountInventoryBoardGachaParticipationRewardStateTran::GetDefinition` | accountinventorytran_h | 8 | getter |
| 36 | GD | `0x1c3170` | `AccountInventoryBoardGachaTakeParticipationRewardTran::GetDefinition` | accountinventorytran_h | 8 | getter |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/guildtran_h.cpp`
- `src/Server/GameDaemon/guildtran_h.h`
- `src/Server/GameDaemon/posttran_h.cpp`
- `src/Server/GameDaemon/posttran_h.h`
- `src/Server/GameDaemon/instantpaymenttran_h.cpp`
- `src/Server/GameDaemon/instantpaymenttran_h.h`
- `src/Server/GameDaemon/accountinventorytran_h.cpp`
- `src/Server/GameDaemon/accountinventorytran_h.h`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-e9.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
