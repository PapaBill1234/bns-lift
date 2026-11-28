# lift-gamedaemon-gap-039-e39 handoff (round 2)

Card: easy leaves (GameDaemon), 16 functions. 15 are lifted. 1 is Not done.

## Round 2 repair

Review round 1 rejected 5 handler bodies. This round fixes all 5. The other accepted bodies did not change.

- `Pc` vtable (`src/Server/GameDaemon/pc.h`): the source header does not declare all PDB virtuals. Thus `Send(char const *, ...)` was at slot 66 (+0x210). The PDB puts the `Send` group at slots 73-75 (+0x258). Nine pure-virtual pad slots (`liftVtablePad0` to `liftVtablePad8`, no PDB names) now come before the `Send` group. This fixes `HandleGame_CreatePartyReq`, `HandleGame_ExtendJumpingCharacterCreationQuotaWithWarehouseItemReq`, `HandleGame_UpgradeJumpingCharacterStateWithCreationQuotaReq` and `HandleGame_CheckRoundTripTimeReq`. Formtest of `HandleGame_CreatePartyReq` gives SAME (`call [r11+0x258]`). No lifted body in `src/Server/GameDaemon` calls a `Pc` virtual that comes after the pads. Later waves must replace the pads with the PDB virtuals in PDB order.
- `HandleGame_CheckRoundTripTimeReq`: the check is now `if (0 >= packet->Decompose(...))`, with the log block first. This gives `xor ecx, ecx; cmp cx, ax; jb`, and the log call uses `ecx` (LT_ERROR = 0) again. Formtest gives SAME.
- `HandleGame_PickGemCardReq`: the original has a /GS cookie (frame 0x48). The handler returns before its old decompose code. The compiler drops that code but keeps the cookie. The body now has a dead `char buf[8]` and a dead `Decompose("b", buf)` after the return. Formtest gives SAME. ❓ The buffer size and format are a code-form guess. The PDB does not give them.

## Lifted

| RVA | Function | Note |
| --- | --- | --- |
| 0x38c070 | `HandleGame_CreatePartyReq` | formtest SAME (round 2). |
| 0x39b970 | `HandleGame_SendPetitionChatNotifyReq` | |
| 0x3bc2e0 | `HandleGame_ExtendJumpingCharacterCreationQuotaWithWarehouseItemReq` | Adds the PDB struct `ExtendJumpingCharacteCreationQuotaWithWarehouseItemReqParam` in the .cpp file. Vtable fix (round 2). |
| 0x3bc3b0 | `HandleGame_UpgradeJumpingCharacterStateWithCreationQuotaReq` | Vtable fix (round 2). |
| 0x3bc9f0 | `HandleGame_SaveVitalityReq` | |
| 0x3bcd00 | `HandleGame_RestoreVitalityReq` | |
| 0x3be660 | `HandleGame_PickGemCardReq` | formtest SAME (round 2). |
| 0x36df20 | `HandleGame_PingReq` | |
| 0x36feb0 | `HandleGame_GodSay` | formtest SAME. |
| 0x384270 | `HandleGame_AcquireRenewalQuestReq` | ❓ The send format is a pooled literal in HR. The code uses "hE". |
| 0x1c00d0 | `HandleSmartCoupon_GameEventByCharacterOk` | |
| 0x1c0140 | `HandleSmartCoupon_GameEventByCharacterFail` | |
| 0x1c01b0 | `HandleSmartCoupon_GameEventByAccountOk` | |
| 0x1c0220 | `HandleSmartCoupon_GameEventByAccountFail` | |
| 0x39c8e0 | `HandleGame_CheckRoundTripTimeReq` | formtest SAME (round 2). |

All lifted bodies have no live caller. Each has an `/INCLUDE` keep pragma.

The `Pc` class in the source has no members yet (`LiftBytes`). The bodies read `GameObject::Id` (+0x28) and `Pc::_pcDbId` (+0x4E10) through PDB offsets. Replace these reads when the `Pc` members are declared.

## Not done

| RVA | Function | Reason |
| --- | --- | --- |
| 0x3d3570 | `HandleGame_SynthesisBadgeRecipeDataReq` | It needs `ContentsRuleConfig::_enableBadge` and `_enableAccountContents`, and `Data::DataManager::_badgeSynthesisResultDataPacket`. The source does not declare these members yet. The fail send format is a pooled literal in HR. |

## Changed files

- `src/Server/GameDaemon/pc.h` (round 2)
- `src/Server/GameDaemon/gamepackethandler_1.cpp`
- `src/Server/GameDaemon/gamepackethandler_2.cpp`
- `src/Server/GameDaemon/gamepackethandler_3.cpp` (round 2)
- `src/Server/GameDaemon/gamepackethandler_4.cpp` (round 2)
- `src/Server/GameDaemon/smartcoupongamepackethandler.cpp`
- `Docs/Plan/handoffs/lift-gamedaemon-gap-039-e39.md`

## Gate and MATCH

The driver builds and compares after this session. This session did not run a build or a gate.
