# lift-gamedaemon-gap-039-e39 handoff (round 1)

Card: easy leaves (GameDaemon), 16 functions. 15 are lifted. 1 is Not done.

## Lifted

| RVA | Function | Note |
| --- | --- | --- |
| 0x38c070 | `HandleGame_CreatePartyReq` | |
| 0x39b970 | `HandleGame_SendPetitionChatNotifyReq` | |
| 0x3bc2e0 | `HandleGame_ExtendJumpingCharacterCreationQuotaWithWarehouseItemReq` | Adds the PDB struct `ExtendJumpingCharacteCreationQuotaWithWarehouseItemReqParam` in the .cpp file. |
| 0x3bc3b0 | `HandleGame_UpgradeJumpingCharacterStateWithCreationQuotaReq` | |
| 0x3bc9f0 | `HandleGame_SaveVitalityReq` | |
| 0x3bcd00 | `HandleGame_RestoreVitalityReq` | |
| 0x3be660 | `HandleGame_PickGemCardReq` | |
| 0x36df20 | `HandleGame_PingReq` | |
| 0x36feb0 | `HandleGame_GodSay` | formtest SAME. |
| 0x384270 | `HandleGame_AcquireRenewalQuestReq` | ❓ The send format is a pooled literal in HR. The code uses "hE". |
| 0x1c00d0 | `HandleSmartCoupon_GameEventByCharacterOk` | |
| 0x1c0140 | `HandleSmartCoupon_GameEventByCharacterFail` | |
| 0x1c01b0 | `HandleSmartCoupon_GameEventByAccountOk` | |
| 0x1c0220 | `HandleSmartCoupon_GameEventByAccountFail` | |
| 0x39c8e0 | `HandleGame_CheckRoundTripTimeReq` | formtest DIFF 5. The original tests the Decompose result with `xor ecx, ecx; cmp cx, ax; jb`. The lift gives `test ax, ax; jne`. `== 0`, `<= 0`, `> 0` and both block orders do not change it. The vtable slot is also different, but funcdiff ignores the displacement. |

All lifted bodies have no live caller. Each has an `/INCLUDE` keep pragma.

The `Pc` class in the source has no members yet (`LiftBytes`). The bodies read `GameObject::Id` (+0x28) and `Pc::_pcDbId` (+0x4E10) through PDB offsets. Replace these reads when the `Pc` members are declared.

## Not done

| RVA | Function | Reason |
| --- | --- | --- |
| 0x3d3570 | `HandleGame_SynthesisBadgeRecipeDataReq` | It needs `ContentsRuleConfig::_enableBadge` and `_enableAccountContents`, and `Data::DataManager::_badgeSynthesisResultDataPacket`. The source does not declare these members yet. The fail send format is a pooled literal in HR. |

## Changed files

- `src/Server/GameDaemon/gamepackethandler_1.cpp`
- `src/Server/GameDaemon/gamepackethandler_2.cpp`
- `src/Server/GameDaemon/gamepackethandler_3.cpp`
- `src/Server/GameDaemon/gamepackethandler_4.cpp`
- `src/Server/GameDaemon/smartcoupongamepackethandler.cpp`
- `Docs/Plan/handoffs/lift-gamedaemon-gap-039-e39.md`

## Gate and MATCH

The driver builds and compares after this session. This session did not run a build or a gate.
