# lift-gamedaemon-e8: Easy leaves (GameDaemon): leaveworldtran_h, changeweaponappearancetran_h, charactermanagementtran_h, closettran_h, ...

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
| Pattern | `src/Server/LobbyDaemon/AccountInventoryChannel.cpp` |
| Plan | `Docs/Plan/gamedaemon-lift.md` sections 1, 3, 5 |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Grep `Docs/Parity/lessons.md` for A2 (block order), A6 (per-exe path literals), A12 (PDB member types), A18 (destructors), A21 (PDB facts) and A22 (per-exe source form). Do not read it in full.
- Pattern: `src/Server/LobbyDaemon/AccountInventoryChannel.cpp`. Read it one time. Use its form for the functions of this card.
- Dead-strip: `wmain` and most callers are still `LIFT_STUB` bodies. `/OPT:REF` removes a lifted function that has no live caller, and funcdiff then cannot pair it. For each function in scope with no live caller, add `#pragma comment(linker, "/INCLUDE:<public name>")` in its `.cpp` (public names: `llvm-pdbutil dump -publics`; grep `/INCLUDE` in `Docs/Parity/lessons.md`). Do not add a pragma for a function that a lifted caller keeps.

## Scope

40 functions, about 281 pseudocode lines (about 2,248 tokens). Stems: `leaveworldtran_h`, `changeweaponappearancetran_h`, `charactermanagementtran_h`, `closettran_h`, `duelbottrainingroomtran_h`, `lobbydaemonchannel_h`, `mileagedeposittran_h`, `npservicetran_h`, `lobbytokenauthtran_h`, `managementtran_h`, `marketservicetran_h`, `mentoringtran_h`, `accountinventorychannel_h`, `seasoncontentstran_h`, `takeachievementrewardtran_h`, `timebasedplaytran_h`, `arenagamechannel_h`, `gamearenachannel_h`, `challengepartytran_h`.

Wave E (owner order 2026-11-27: the easiest work first). Each function in this card is a leaf: its body calls no other counted function that needs a lift. Thus a `LIFT_STUB` callee cannot keep it DIFF. Each function has at most 30 pseudocode lines. Ease key: 7.0 cost per function (rule in `Docs/Plan/gamedaemon-lift.md` section 3).

Lift only the functions in the table. The other functions of these stems are in later W cards. Those cards depend on this card.

| n | Exe | RVA | PDB name | Stem | Lines | Form |
| ---: | --- | --- | --- | --- | ---: | --- |
| 1 | GD | `0x35fe0` | `LeaveWorldTran::GetDefinition` | leaveworldtran_h | 7 | getter |
| 2 | GD | `0x360f0` | `LogoutArenaTran::GetDefinition` | leaveworldtran_h | 7 | getter |
| 3 | GD | `0x1397e0` | `ReturnToArenaLobbyTran::GetDefinition` | leaveworldtran_h | 7 | getter |
| 4 | GD | `0x714c0` | `ChangeWeaponAppearanceTran::GetDefinition` | changeweaponappearancetran_h | 7 | getter |
| 5 | GD | `0x72590` | `CreateCharacterTran::GetDefinition` | charactermanagementtran_h | 7 | getter |
| 6 | GD | `0x725a0` | `ChangeCharacterAppearanceTran::GetDefinition` | charactermanagementtran_h | 7 | getter |
| 7 | GD | `0x725b0` | `ChangeCharacterSexTran::GetDefinition` | charactermanagementtran_h | 7 | getter |
| 8 | GD | `0x725c0` | `ChangeCharacterRaceTran::GetDefinition` | charactermanagementtran_h | 7 | getter |
| 9 | GD | `0x725d0` | `RenameCharacterTran::GetDefinition` | charactermanagementtran_h | 7 | getter |
| 10 | GD | `0x725e0` | `DeleteCharacterTran::GetDefinition` | charactermanagementtran_h | 7 | getter |
| 11 | GD | `0x725f0` | `RestoreCharacterTran::GetDefinition` | charactermanagementtran_h | 7 | getter |
| 12 | GD | `0x80070` | `PutItemIntoClosetTran::GetDefinition` | closettran_h | 7 | getter |
| 13 | GD | `0x80080` | `TakeItemFromClosetTran::GetDefinition` | closettran_h | 7 | getter |
| 14 | GD | `0xaca50` | `DuelBotTrainingRoomResultTran::GetDefinition` | duelbottrainingroomtran_h | 7 | getter |
| 15 | GD | `0xaca60` | `DuelBotTrainingRoomRewardTran::GetDefinition` | duelbottrainingroomtran_h | 7 | getter |
| 16 | GD | `0x1105d0` | `GameSideArenaLobbyChannel::GetId` | lobbydaemonchannel_h | 7 | getter |
| 17 | GD | `0x1107e0` | `MileageDepositTran::GetDefinition` | mileagedeposittran_h | 7 | getter |
| 18 | GD | `0x121950` | `NPRegisterServiceTran::GetDefinition` | npservicetran_h | 7 | getter |
| 19 | GD | `0x121960` | `NPValidateGroupTran::GetDefinition` | npservicetran_h | 7 | getter |
| 20 | GD | `0x121970` | `NPGetChannelPropertyTran::GetDefinition` | npservicetran_h | 7 | getter |
| 21 | GD | `0x121980` | `NPGroupInfoTran::GetDefinition` | npservicetran_h | 7 | getter |
| 22 | GD | `0x13e270` | `LobbyTokenAuthTran::GetDefinition` | lobbytokenauthtran_h | 7 | getter |
| 23 | GD | `0x156b20` | `DepositInGuildBankTran::GetDefinition` | managementtran_h | 7 | getter |
| 24 | GD | `0x156b30` | `WithdrawFromGuildBankTran::GetDefinition` | managementtran_h | 7 | getter |
| 25 | GD | `0x15af00` | `RegisterPurchaseTran::GetDefinition` | marketservicetran_h | 7 | getter |
| 26 | GD | `0x15af10` | `RegisterBidTran::GetDefinition` | marketservicetran_h | 7 | getter |
| 27 | GD | `0x15af20` | `UpdateBidTran::GetDefinition` | marketservicetran_h | 7 | getter |
| 28 | GD | `0x16a300` | `ConfirmInvitationMentoringTran::GetDefinition` | mentoringtran_h | 7 | getter |
| 29 | GD | `0x16a310` | `LeaveMentoringTran::GetDefinition` | mentoringtran_h | 7 | getter |
| 30 | GD | `0x180c10` | `AccountInventoryChannel::GetId` | accountinventorychannel_h | 7 | getter |
| 31 | GD | `0x180c70` | `PartyBattleResultTran::GetDefinition` | seasoncontentstran_h | 7 | getter |
| 32 | GD | `0x180c80` | `DuelResultTran::GetDefinition` | seasoncontentstran_h | 7 | getter |
| 33 | GD | `0x180c90` | `TimeAttackRecordResultTran::GetDefinition` | seasoncontentstran_h | 7 | getter |
| 34 | GD | `0x1d77b0` | `TakeAchievementRewardTran::GetDefinition` | takeachievementrewardtran_h | 7 | getter |
| 35 | GD | `0x224250` | `TakeTimeBasedPlayRewardTran::GetDefinition` | timebasedplaytran_h | 7 | getter |
| 36 | GD | `0x3502a0` | `ArenaGameChannel::GetId` | arenagamechannel_h | 7 | getter |
| 37 | GD | `0x6eb460` | `GameArenaChannel::GetId` | gamearenachannel_h | 7 | getter |
| 38 | GD | `0x65da0` | `CreateChallengePartyTran::GetDefinition` | challengepartytran_h | 7 | getter |
| 39 | GD | `0x65db0` | `ConfirmInvitationChallengePartyTran::GetDefinition` | challengepartytran_h | 8 | getter |
| 40 | GD | `0x65dc0` | `LeaveChallengePartyTran::GetDefinition` | challengepartytran_h | 7 | getter |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/leaveworldtran_h.cpp`
- `src/Server/GameDaemon/leaveworldtran_h.h`
- `src/Server/GameDaemon/changeweaponappearancetran_h.cpp`
- `src/Server/GameDaemon/changeweaponappearancetran_h.h`
- `src/Server/GameDaemon/charactermanagementtran_h.cpp`
- `src/Server/GameDaemon/charactermanagementtran_h.h`
- `src/Server/GameDaemon/closettran_h.cpp`
- `src/Server/GameDaemon/closettran_h.h`
- `src/Server/GameDaemon/duelbottrainingroomtran_h.cpp`
- `src/Server/GameDaemon/duelbottrainingroomtran_h.h`
- `src/Server/GameDaemon/lobbydaemonchannel_h.cpp`
- `src/Server/GameDaemon/lobbydaemonchannel_h.h`
- `src/Server/GameDaemon/mileagedeposittran_h.cpp`
- `src/Server/GameDaemon/mileagedeposittran_h.h`
- `src/Server/GameDaemon/npservicetran_h.cpp`
- `src/Server/GameDaemon/npservicetran_h.h`
- `src/Server/GameDaemon/lobbytokenauthtran_h.cpp`
- `src/Server/GameDaemon/lobbytokenauthtran_h.h`
- `src/Server/GameDaemon/managementtran_h.cpp`
- `src/Server/GameDaemon/managementtran_h.h`
- `src/Server/GameDaemon/marketservicetran_h.cpp`
- `src/Server/GameDaemon/marketservicetran_h.h`
- `src/Server/GameDaemon/mentoringtran_h.cpp`
- `src/Server/GameDaemon/mentoringtran_h.h`
- `src/Server/GameDaemon/accountinventorychannel_h.cpp`
- `src/Server/GameDaemon/accountinventorychannel_h.h`
- `src/Server/GameDaemon/seasoncontentstran_h.cpp`
- `src/Server/GameDaemon/seasoncontentstran_h.h`
- `src/Server/GameDaemon/takeachievementrewardtran_h.cpp`
- `src/Server/GameDaemon/takeachievementrewardtran_h.h`
- `src/Server/GameDaemon/timebasedplaytran_h.cpp`
- `src/Server/GameDaemon/timebasedplaytran_h.h`
- `src/Server/GameDaemon/arenagamechannel_h.cpp`
- `src/Server/GameDaemon/arenagamechannel_h.h`
- `src/Server/GameDaemon/gamearenachannel_h.cpp`
- `src/Server/GameDaemon/gamearenachannel_h.h`
- `src/Server/GameDaemon/challengepartytran_h.cpp`
- `src/Server/GameDaemon/challengepartytran_h.h`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-e8.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
