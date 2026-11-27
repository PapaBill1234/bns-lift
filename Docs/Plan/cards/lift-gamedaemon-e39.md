# lift-gamedaemon-e39: Easy leaves (GameDaemon): gamepackethandler_2, gamepackethandler_4, gamepackethandler_1, smartcoupongamepackethandler, ...

| Item | Value |
| --- | --- |
| Exe | GD |
| Source build | GameDaemon 2019 + PDB (VS2010 SP1) |
| Exe file | `<work-root>/ida/lift/GameDaemon/GameDaemon.exe` |
| PDB | `<work-root>/ida/lift/GameDaemon/GameDaemon.pdb` |
| Pseudocode | `~/.cache/bns-lift/hr/GameDaemon/<stem>.c` |
| Pseudocode index | `~/.cache/bns-lift/hr/GameDaemon/index.tsv` (stem, rva, name, first, last, status, source file, part) |
| Wave | E |
| Model | opus |
| Depends on | `lift-gamedaemon-0e` |
| Pattern | `src/Server/LobbyDaemon/LobbyGamePacketHandler.cpp` |
| Plan | `Docs/Plan/gamedaemon-lift.md` sections 1, 3, 5 |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Grep `Docs/Parity/lessons.md` for A2 (block order), A6 (per-exe path literals), A12 (PDB member types), A18 (destructors), A21 (PDB facts) and A22 (per-exe source form). Do not read it in full.
- Pattern: `src/Server/LobbyDaemon/LobbyGamePacketHandler.cpp`. Read it one time. Use its form for the functions of this card.
- Dead-strip: `wmain` and most callers are still `LIFT_STUB` bodies. `/OPT:REF` removes a lifted function that has no live caller, and funcdiff then cannot pair it. For each function in scope with no live caller, add `#pragma comment(linker, "/INCLUDE:<public name>")` in its `.cpp` (public names: `llvm-pdbutil dump -publics`; grep `/INCLUDE` in `Docs/Parity/lessons.md`). Do not add a pragma for a function that a lifted caller keeps.

## Scope

16 functions, about 279 pseudocode lines (about 2,232 tokens). Stems: `gamepackethandler_2`, `gamepackethandler_4`, `gamepackethandler_1`, `smartcoupongamepackethandler`, `gamepackethandler_3`.

Wave E (owner order 2026-11-27: the easiest work first). Each function in this card is a leaf: its body calls no other counted function that needs a lift. Thus a `LIFT_STUB` callee cannot keep it DIFF. Each function has at most 30 pseudocode lines. Ease key: 17.4 cost per function (rule in `Docs/Plan/gamedaemon-lift.md` section 3).

Lift only the functions in the table. The other functions of these stems are in later W cards. Those cards depend on this card.

| n | Exe | RVA | PDB name | Stem | Lines | Form |
| ---: | --- | --- | --- | --- | ---: | --- |
| 1 | GD | `0x38c070` | `HandleGame_CreatePartyReq` | gamepackethandler_2 | 15 | leaf |
| 2 | GD | `0x39b970` | `HandleGame_SendPetitionChatNotifyReq` | gamepackethandler_2 | 12 | leaf |
| 3 | GD | `0x3bc2e0` | `HandleGame_ExtendJumpingCharacterCreationQuotaWithWarehouseItemReq` | gamepackethandler_4 | 19 | leaf |
| 4 | GD | `0x3bc3b0` | `HandleGame_UpgradeJumpingCharacterStateWithCreationQuotaReq` | gamepackethandler_4 | 15 | leaf |
| 5 | GD | `0x3bc9f0` | `HandleGame_SaveVitalityReq` | gamepackethandler_4 | 13 | leaf |
| 6 | GD | `0x3bcd00` | `HandleGame_RestoreVitalityReq` | gamepackethandler_4 | 13 | leaf |
| 7 | GD | `0x3be660` | `HandleGame_PickGemCardReq` | gamepackethandler_4 | 13 | leaf |
| 8 | GD | `0x3d3570` | `HandleGame_SynthesisBadgeRecipeDataReq` | gamepackethandler_4 | 22 | leaf |
| 9 | GD | `0x36df20` | `HandleGame_PingReq` | gamepackethandler_1 | 13 | leaf |
| 10 | GD | `0x36feb0` | `HandleGame_GodSay` | gamepackethandler_1 | 30 | leaf |
| 11 | GD | `0x384270` | `HandleGame_AcquireRenewalQuestReq` | gamepackethandler_1 | 14 | leaf |
| 12 | GD | `0x1c00d0` | `HandleSmartCoupon_GameEventByCharacterOk` | smartcoupongamepackethandler | 19 | leaf |
| 13 | GD | `0x1c0140` | `HandleSmartCoupon_GameEventByCharacterFail` | smartcoupongamepackethandler | 21 | leaf |
| 14 | GD | `0x1c01b0` | `HandleSmartCoupon_GameEventByAccountOk` | smartcoupongamepackethandler | 19 | leaf |
| 15 | GD | `0x1c0220` | `HandleSmartCoupon_GameEventByAccountFail` | smartcoupongamepackethandler | 21 | leaf |
| 16 | GD | `0x39c8e0` | `HandleGame_CheckRoundTripTimeReq` | gamepackethandler_3 | 20 | leaf |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/gamepackethandler_2.cpp`
- `src/Server/GameDaemon/gamepackethandler_2.h`
- `src/Server/GameDaemon/gamepackethandler_4.cpp`
- `src/Server/GameDaemon/gamepackethandler_4.h`
- `src/Server/GameDaemon/gamepackethandler_1.cpp`
- `src/Server/GameDaemon/gamepackethandler_1.h`
- `src/Server/GameDaemon/smartcoupongamepackethandler.cpp`
- `src/Server/GameDaemon/smartcoupongamepackethandler.h`
- `src/Server/GameDaemon/gamepackethandler_3.cpp`
- `src/Server/GameDaemon/gamepackethandler_3.h`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-e39.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
