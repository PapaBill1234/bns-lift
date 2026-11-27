# lift-gamedaemon-gap-008-e8 handoff (round 1)

## Lifted

None. No source file changed.

## Why nothing was lifted

All 40 functions are trivial getters. The blocker is not the body. The blocker is the missing support around the body.

1. The 36 `GetDefinition` bodies return `&<Class>::_def`. The PDB has `_def` as global data of type `GameTranDef` (for example `LeaveWorldTran::_def`, RVA 0xE7FA70). No source file declares or defines any `_def`. A lift needs a `static GameTranDef const _def;` member in each of 33 classes, plus a definition. The real contents (`stateDef`, `fin`, `desc`) need the state tables of each class. Those tables are not in this card. A zero-filled `_def` would be invented data, so I did not add one.
2. The 3 `GetId` bodies read `_worldId` (`GameSideArenaLobbyChannel`, `AccountInventoryChannel`, `GameArenaChannel`: members from the PDB layout). The skeleton headers `src/Server/GameDaemon/<stem>.h` declare these classes with no bases and no members ("Wave 0"). `include/pdb/GameDaemon/types.h` has the full layouts, but no GameDaemon source file includes it yet. The skeleton class declarations would conflict with it (redefinition). Merging the two needs a header decision for all 19 stems. I could not build here to check it.

## Not done

All functions below. Reason: see points 1 and 2 above.

| RVA | Function |
| --- | --- |
| 0x35fe0 | LeaveWorldTran::GetDefinition |
| 0x360f0 | LogoutArenaTran::GetDefinition |
| 0x1397e0 | ReturnToArenaLobbyTran::GetDefinition |
| 0x714c0 | ChangeWeaponAppearanceTran::GetDefinition |
| 0x72590 | CreateCharacterTran::GetDefinition |
| 0x725a0 | ChangeCharacterAppearanceTran::GetDefinition |
| 0x725b0 | ChangeCharacterSexTran::GetDefinition |
| 0x725c0 | ChangeCharacterRaceTran::GetDefinition |
| 0x725d0 | RenameCharacterTran::GetDefinition |
| 0x725e0 | DeleteCharacterTran::GetDefinition |
| 0x725f0 | RestoreCharacterTran::GetDefinition |
| 0x80070 | PutItemIntoClosetTran::GetDefinition |
| 0x80080 | TakeItemFromClosetTran::GetDefinition |
| 0xaca50 | DuelBotTrainingRoomResultTran::GetDefinition |
| 0xaca60 | DuelBotTrainingRoomRewardTran::GetDefinition |
| 0x1105d0 | GameSideArenaLobbyChannel::GetId |
| 0x1107e0 | MileageDepositTran::GetDefinition |
| 0x121950 | NPRegisterServiceTran::GetDefinition |
| 0x121960 | NPValidateGroupTran::GetDefinition |
| 0x121970 | NPGetChannelPropertyTran::GetDefinition |
| 0x121980 | NPGroupInfoTran::GetDefinition |
| 0x13e270 | LobbyTokenAuthTran::GetDefinition |
| 0x156b20 | DepositInGuildBankTran::GetDefinition |
| 0x156b30 | WithdrawFromGuildBankTran::GetDefinition |
| 0x15af00 | RegisterPurchaseTran::GetDefinition |
| 0x15af10 | RegisterBidTran::GetDefinition |
| 0x15af20 | UpdateBidTran::GetDefinition |
| 0x16a300 | ConfirmInvitationMentoringTran::GetDefinition |
| 0x16a310 | LeaveMentoringTran::GetDefinition |
| 0x180c10 | AccountInventoryChannel::GetId |
| 0x180c70 | PartyBattleResultTran::GetDefinition |
| 0x180c80 | DuelResultTran::GetDefinition |
| 0x180c90 | TimeAttackRecordResultTran::GetDefinition |
| 0x1d77b0 | TakeAchievementRewardTran::GetDefinition |
| 0x224250 | TakeTimeBasedPlayRewardTran::GetDefinition |
| 0x6eb460 | GameArenaChannel::GetId |
| 0x65da0 | CreateChallengePartyTran::GetDefinition |
| 0x65db0 | ConfirmInvitationChallengePartyTran::GetDefinition |
| 0x65dc0 | LeaveChallengePartyTran::GetDefinition |

## Suggested next step

Add a prerequisite card that (a) decides how GameDaemon skeleton headers use the PDB layouts in `types.h`, and (b) lifts or declares the `_def` data of each Tran class with its real state tables. After that, these getters are one-line bodies.

## Files changed

Only this handoff file.

Gate and MATCH comparison: not run (no code change; the driver runs them).
