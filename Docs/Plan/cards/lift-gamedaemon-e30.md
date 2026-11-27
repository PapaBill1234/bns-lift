# lift-gamedaemon-e30: Easy leaves (GameDaemon): pc_cpp_3, pc_cpp_4, user_cpp, npcspawn_h

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
| Pattern | `src/Server/LobbyDaemon/CliSession.cpp` |
| Plan | `Docs/Plan/gamedaemon-lift.md` sections 1, 3, 5 |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Grep `Docs/Parity/lessons.md` for A2 (block order), A6 (per-exe path literals), A12 (PDB member types), A18 (destructors), A21 (PDB facts) and A22 (per-exe source form). Do not read it in full.
- Pattern: `src/Server/LobbyDaemon/CliSession.cpp`. Read it one time. Use its form for the functions of this card.
- Dead-strip: `wmain` and most callers are still `LIFT_STUB` bodies. `/OPT:REF` removes a lifted function that has no live caller, and funcdiff then cannot pair it. For each function in scope with no live caller, add `#pragma comment(linker, "/INCLUDE:<public name>")` in its `.cpp` (public names: `llvm-pdbutil dump -publics`; grep `/INCLUDE` in `Docs/Parity/lessons.md`). Do not add a pragma for a function that a lifted caller keeps.

## Scope

40 functions, about 785 pseudocode lines (about 6,280 tokens). Stems: `pc_cpp_3`, `pc_cpp_4`, `user_cpp`, `npcspawn_h`.

Wave E (owner order 2026-11-27: the easiest work first). Each function in this card is a leaf: its body calls no other counted function that needs a lift. Thus a `LIFT_STUB` callee cannot keep it DIFF. Each function has at most 30 pseudocode lines. Ease key: 19.6 cost per function (rule in `Docs/Plan/gamedaemon-lift.md` section 3).

Lift only the functions in the table. The other functions of these stems are in later W cards. Those cards depend on this card.

| n | Exe | RVA | PDB name | Stem | Lines | Form |
| ---: | --- | --- | --- | --- | ---: | --- |
| 1 | GD | `0x5f7d50` | `Pc::isActivatedGrade` | pc_cpp_3 | 14 | leaf |
| 2 | GD | `0x5f8590` | `Pc::GetRewardContribution` | pc_cpp_3 | 19 | leaf |
| 3 | GD | `0x5fa2a0` | `Pc::AvailableTurnBack` | pc_cpp_3 | 29 | leaf |
| 4 | GD | `0x5fc9f0` | `Pc::BeginArenaLobbyReservation` | pc_cpp_3 | 24 | leaf |
| 5 | GD | `0x5fca90` | `Pc::RollbackArenaLobbyReservation` | pc_cpp_3 | 10 | leaf |
| 6 | GD | `0x5fdc40` | `Pc::LeaveArenaLobbyOk` | pc_cpp_3 | 23 | leaf |
| 7 | GD | `0x600e20` | `Pc::ReturnToGameByEnterFail` | pc_cpp_3 | 15 | leaf |
| 8 | GD | `0x600fe0` | `Pc::GetArenaSessionState` | pc_cpp_3 | 15 | leaf |
| 9 | GD | `0x601020` | `Pc::IsInArenaOrArenaLobby` | pc_cpp_3 | 17 | leaf |
| 10 | GD | `0x604430` | `Pc::checkTeamGuildBattleFieldWithTarget` | pc_cpp_3 | 25 | leaf |
| 11 | GD | `0x6068c0` | `Pc::SetTakingAchievementReward` | pc_cpp_4 | 9 | leaf |
| 12 | GD | `0x606910` | `Pc::IsTakingAchievementReward` | pc_cpp_4 | 15 | leaf |
| 13 | GD | `0x606d10` | `Pc::GetPowerInfoForGameLog` | pc_cpp_4 | 7 | leaf |
| 14 | GD | `0x607550` | `Pc::EnableToRetrieveMyRanking` | pc_cpp_4 | 19 | leaf |
| 15 | GD | `0x608300` | `Pc::HasCraft` | pc_cpp_4 | 29 | leaf |
| 16 | GD | `0x6083a0` | `Pc::IsJoinedCraftUnion` | pc_cpp_4 | 17 | leaf |
| 17 | GD | `0x6084c0` | `Pc::GetCraftUnionExp` | pc_cpp_4 | 16 | leaf |
| 18 | GD | `0x608630` | `Pc::FetchCraftUnionList` | pc_cpp_4 | 29 | leaf |
| 19 | GD | `0x608720` | `Pc::IsRegisteredCraftRecipe` | pc_cpp_4 | 30 | leaf |
| 20 | GD | `0x608950` | `Pc::clearCraftList` | pc_cpp_4 | 29 | leaf |
| 21 | GD | `0x60a3c0` | `Pc::IsUsingJumpingCharacter2Ticket` | pc_cpp_4 | 15 | leaf |
| 22 | GD | `0x60ac30` | `Pc::ClearTransformItemRetry` | pc_cpp_4 | 14 | leaf |
| 23 | GD | `0x60af20` | `Pc::ClearAttractionReward` | pc_cpp_4 | 19 | leaf |
| 24 | GD | `0x60b880` | `Pc::SendInitializeSeasonContentsRecordFail` | pc_cpp_4 | 18 | leaf |
| 25 | GD | `0x60d880` | `Pc::isAccountExpCharged` | pc_cpp_4 | 28 | leaf |
| 26 | GD | `0x3e2040` | `TimeBasedPlayInfoList::~TimeBasedPlayInfoList` | user_cpp | 23 | leaf |
| 27 | GD | `0x3e2260` | `TimeBasedPlayInfoList::SetLastCheckTimeUTC` | user_cpp | 12 | leaf |
| 28 | GD | `0x3e22b0` | `TimeBasedPlayInfoList::GetValidCheckTimeUTC` | user_cpp | 28 | leaf |
| 29 | GD | `0x3e2370` | `TimeBasedPlayInfoList::SetData` | user_cpp | 21 | leaf |
| 30 | GD | `0x3e24a0` | `TimeBasedPlayInfoList::SetDurationForDebug` | user_cpp | 18 | leaf |
| 31 | GD | `0x3e4610` | `User::SetSession` | user_cpp | 15 | leaf |
| 32 | GD | `0x3e4650` | `User::SetPcCafeDebugCode` | user_cpp | 21 | leaf |
| 33 | GD | `0x3e56f0` | `User::resetPc` | user_cpp | 8 | leaf |
| 34 | GD | `0x3e5700` | `User::resetPc` | user_cpp | 27 | leaf |
| 35 | GD | `0x3e5e60` | `User::setExistContentsBan` | user_cpp | 19 | leaf |
| 36 | GD | `0x3e5eb0` | `User::IsBannedContents` | user_cpp | 18 | leaf |
| 37 | GD | `0x3e8440` | `User::ClearBotState` | user_cpp | 27 | leaf |
| 38 | GD | `0x1edf00` | `NpcSpawnInfo::GetAlias` | npcspawn_h | 19 | leaf |
| 39 | GD | `0x34f070` | `NpcSpawnInfo::GetActDetect` | npcspawn_h | 22 | leaf |
| 40 | GD | `0x34f0b0` | `NpcSpawnInfo::GetActSocial` | npcspawn_h | 22 | leaf |

Same name in a lifted exe (a different body is possible): `TimeBasedPlayInfoList::~TimeBasedPlayInfoList` (src/Server/LobbyDaemon/CliSession.cpp).

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/pc_cpp_3.cpp`
- `src/Server/GameDaemon/pc_cpp_3.h`
- `src/Server/GameDaemon/pc_cpp_4.cpp`
- `src/Server/GameDaemon/pc_cpp_4.h`
- `src/Server/GameDaemon/user_cpp.cpp`
- `src/Server/GameDaemon/user_cpp.h`
- `src/Server/GameDaemon/npcspawn_h.cpp`
- `src/Server/GameDaemon/npcspawn_h.h`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-e30.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
