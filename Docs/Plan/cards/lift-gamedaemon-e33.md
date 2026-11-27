# lift-gamedaemon-e33: Easy leaves (GameDaemon): item_cpp_2, npcparty_cpp, pc_cpp_1, creature_cpp_1, ...

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
| Pattern | none |
| Plan | `Docs/Plan/gamedaemon-lift.md` sections 1, 3, 5 |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Grep `Docs/Parity/lessons.md` for A2 (block order), A6 (per-exe path literals), A12 (PDB member types), A18 (destructors), A21 (PDB facts) and A22 (per-exe source form). Do not read it in full.
- Pattern: none. No lifted file has the same role.

## Scope

39 functions, about 857 pseudocode lines (about 6,856 tokens). Stems: `item_cpp_2`, `npcparty_cpp`, `pc_cpp_1`, `creature_cpp_1`, `npcsquad`.

Wave E (owner order 2026-11-27: the easiest work first). Each function in this card is a leaf: its body calls no other counted function that needs a lift. Thus a `LIFT_STUB` callee cannot keep it DIFF. Each function has at most 30 pseudocode lines. Ease key: 22.0 cost per function (rule in `Docs/Plan/gamedaemon-lift.md` section 3).

Lift only the functions in the table. The other functions of these stems are in later W cards. Those cards depend on this card.

| n | Exe | RVA | PDB name | Stem | Lines | Form |
| ---: | --- | --- | --- | --- | ---: | --- |
| 1 | GD | `0x557fe0` | `AccessoryItem::R_GetRandomEffectId` | item_cpp_2 | 21 | leaf |
| 2 | GD | `0x558090` | `AccessoryItem::R_GetRandomEffectGroupId` | item_cpp_2 | 21 | leaf |
| 3 | GD | `0x558a40` | `GemItem::BroadcastEquip` | item_cpp_2 | 17 | leaf |
| 4 | GD | `0x558a70` | `GemItem::BroadcastUnequip` | item_cpp_2 | 17 | leaf |
| 5 | GD | `0x558aa0` | `GemItem::R_CheckEnchantTargetItem` | item_cpp_2 | 29 | leaf |
| 6 | GD | `0x558b50` | `GemItem::R_GetRandomEffectId` | item_cpp_2 | 21 | leaf |
| 7 | GD | `0x558ba0` | `GemItem::R_GetRandomEffectGroupId` | item_cpp_2 | 21 | leaf |
| 8 | GD | `0x428bc0` | `NpcParty::~NpcParty` | npcparty_cpp | 18 | leaf |
| 9 | GD | `0x428c70` | `NpcParty::Add` | npcparty_cpp | 27 | leaf |
| 10 | GD | `0x428cd0` | `NpcParty::Remove` | npcparty_cpp | 25 | leaf |
| 11 | GD | `0x428d10` | `NpcParty::SetVar` | npcparty_cpp | 15 | leaf |
| 12 | GD | `0x5d4cc0` | `CraftInfo::~CraftInfo` | pc_cpp_1 | 23 | leaf |
| 13 | GD | `0x5d7180` | `Pc::IsTryingInstantPayment` | pc_cpp_1 | 15 | leaf |
| 14 | GD | `0x5d8320` | `Pc::SendRetrieveRankingRewardListFail` | pc_cpp_1 | 19 | leaf |
| 15 | GD | `0x5d8390` | `Pc::SendRetrieveGuildRankingInfoFail` | pc_cpp_1 | 20 | leaf |
| 16 | GD | `0x5d8400` | `Pc::SendRetrieveChallengePartyRankingInfoFail` | pc_cpp_1 | 22 | leaf |
| 17 | GD | `0x5d8490` | `Pc::SendTakeRankingRewardFail` | pc_cpp_1 | 20 | leaf |
| 18 | GD | `0x5d8500` | `Pc::SendRegisterCraftFail` | pc_cpp_1 | 21 | leaf |
| 19 | GD | `0x5d8590` | `Pc::SendTakeCraftFail` | pc_cpp_1 | 21 | leaf |
| 20 | GD | `0x5d8620` | `Pc::SendAbortCraftFail` | pc_cpp_1 | 19 | leaf |
| 21 | GD | `0x5d86a0` | `Pc::SendJoinCraftUnionFail` | pc_cpp_1 | 25 | leaf |
| 22 | GD | `0x5d8730` | `Pc::SendLeaveCraftUnionFail` | pc_cpp_1 | 25 | leaf |
| 23 | GD | `0x5db450` | `Pc::IsInTeamPartyZone` | pc_cpp_1 | 27 | leaf |
| 24 | GD | `0x5db4a0` | `Pc::IsInPartyBattleFieldZone` | pc_cpp_1 | 23 | leaf |
| 25 | GD | `0x5db4e0` | `Pc::IsInPartyZone` | pc_cpp_1 | 24 | leaf |
| 26 | GD | `0x5e1650` | `Pc::GetPcContentsType` | pc_cpp_1 | 28 | leaf |
| 27 | GD | `0x5e2dc0` | `Pc::SetCombatModeByTargeted` | pc_cpp_1 | 7 | leaf |
| 28 | GD | `0x5e51b0` | `Pc::CalculateStyleScoreBonus` | pc_cpp_1 | 29 | leaf |
| 29 | GD | `0x5e5510` | `Pc::DeactivateSkillScore` | pc_cpp_1 | 23 | leaf |
| 30 | GD | `0x261650` | `Creature::GetExtraBroadcastOnChangePropertySize` | creature_cpp_1 | 19 | leaf |
| 31 | GD | `0x261e60` | `Creature::initMoveCtx` | creature_cpp_1 | 26 | leaf |
| 32 | GD | `0x2621b0` | `Creature::IsAttackable` | creature_cpp_1 | 30 | leaf |
| 33 | GD | `0x263a40` | `Creature::CanJoinFaction` | creature_cpp_1 | 22 | leaf |
| 34 | GD | `0x264050` | `Creature::CheckCombatSideEnabled` | creature_cpp_1 | 24 | leaf |
| 35 | GD | `0x264350` | `Creature::IsHostileFaction` | creature_cpp_1 | 14 | leaf |
| 36 | GD | `0x265160` | `Creature::GetAbnormalState` | creature_cpp_1 | 20 | leaf |
| 37 | GD | `0x2672f0` | `Creature::CalcHeal` | creature_cpp_1 | 27 | leaf |
| 38 | GD | `0x42d0a0` | `NpcSquad::EventOccured` | npcsquad | 26 | leaf |
| 39 | GD | `0x42db10` | `NpcSquad::CheckLeaderlessParty` | npcsquad | 26 | leaf |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/item_cpp_2.cpp`
- `src/Server/GameDaemon/item_cpp_2.h`
- `src/Server/GameDaemon/npcparty_cpp.cpp`
- `src/Server/GameDaemon/npcparty_cpp.h`
- `src/Server/GameDaemon/pc_cpp_1.cpp`
- `src/Server/GameDaemon/pc_cpp_1.h`
- `src/Server/GameDaemon/creature_cpp_1.cpp`
- `src/Server/GameDaemon/creature_cpp_1.h`
- `src/Server/GameDaemon/npcsquad.cpp`
- `src/Server/GameDaemon/npcsquad.h`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-e33.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
