# lift-gamedaemon-e20: Easy leaves (GameDaemon): arenaroommanager_h, publicraid_h, actsequenceloader_h, bosscombatsequence, ...

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
- Dead-strip: `wmain` and most callers are still `LIFT_STUB` bodies. `/OPT:REF` removes a lifted function that has no live caller, and funcdiff then cannot pair it. For each function in scope with no live caller, add `#pragma comment(linker, "/INCLUDE:<public name>")` in its `.cpp` (public names: `llvm-pdbutil dump -publics`; grep `/INCLUDE` in `Docs/Parity/lessons.md`). Do not add a pragma for a function that a lifted caller keeps.

## Scope

40 functions, about 419 pseudocode lines (about 3,352 tokens). Stems: `arenaroommanager_h`, `publicraid_h`, `actsequenceloader_h`, `bosscombatsequence`, `summoned_cpp`, `bannedwordfiltermemorymanager`, `contribution_h`, `arenalobbycommon`, `brainraidboss_h`, `capturetheflag_cpp`.

Wave E (owner order 2026-11-27: the easiest work first). Each function in this card is a leaf: its body calls no other counted function that needs a lift. Thus a `LIFT_STUB` callee cannot keep it DIFF. Each function has at most 30 pseudocode lines. Ease key: 10.5 cost per function (rule in `Docs/Plan/gamedaemon-lift.md` section 3).

Lift only the functions in the table. The other functions of these stems are in later W cards. Those cards depend on this card.

| n | Exe | RVA | PDB name | Stem | Lines | Form |
| ---: | --- | --- | --- | --- | ---: | --- |
| 1 | GD | `0x27b20` | `ArenaRoom::GetArenaPortalPublicRaidModeType` | arenaroommanager_h | 7 | getter |
| 2 | GD | `0x27b30` | `ArenaPublicRaidRoom::SetPublicRaidReservePcCount` | arenaroommanager_h | 7 | leaf |
| 3 | GD | `0x27b40` | `ArenaPublicRaidRoom::IsSetPublicRaidReservePcCount` | arenaroommanager_h | 7 | leaf |
| 4 | GD | `0x27b50` | `ArenaPublicRaidRoom::GetPublicRaidReservePcCount` | arenaroommanager_h | 10 | leaf |
| 5 | GD | `0x27b80` | `ArenaPublicRaidRoom::GetPublicRaidKey` | arenaroommanager_h | 12 | leaf |
| 6 | GD | `0x27ba0` | `ArenaPublicRaidRoom::GetArenaPortalPublicRaidModeType` | arenaroommanager_h | 7 | getter |
| 7 | GD | `0x66a1a0` | `ArenaDungeonRoom::GetArenaAttraction` | arenaroommanager_h | 7 | getter |
| 8 | GD | `0x35e90` | `AttractionState::~AttractionState` | publicraid_h | 7 | xtor |
| 9 | GD | `0x180e50` | `PublicRaid::GetTypeName` | publicraid_h | 7 | getter |
| 10 | GD | `0x180e60` | `PublicRaid::GetMaxPcCount` | publicraid_h | 12 | leaf |
| 11 | GD | `0x35f50` | `ActSequenceLoader::GetTableType` | actsequenceloader_h | 7 | getter |
| 12 | GD | `0x3fee30` | `ActSequenceLoader::LoadTableMT_PreProc` | actsequenceloader_h | 12 | leaf |
| 13 | GD | `0x77d70` | `BossCombatSequence::ReserveTransitBerserk` | bosscombatsequence | 10 | leaf |
| 14 | GD | `0x611b20` | `Summoned::Send` | summoned_cpp | 8 | leaf |
| 15 | GD | `0x611b50` | `Summoned::Send` | summoned_cpp | 8 | leaf |
| 16 | GD | `0x611d60` | `Summoned::SetCombatModeByAttack` | summoned_cpp | 8 | leaf |
| 17 | GD | `0x611d90` | `Summoned::SetCombatModeByAttacked` | summoned_cpp | 8 | leaf |
| 18 | GD | `0x611dc0` | `Summoned::SetCombatModeByTargeted` | summoned_cpp | 8 | leaf |
| 19 | GD | `0x611df0` | `Summoned::ResetCombatModeByTargeted` | summoned_cpp | 8 | leaf |
| 20 | GD | `0x611e20` | `Summoned::SetCombatModeByLink` | summoned_cpp | 8 | leaf |
| 21 | GD | `0x611e50` | `Summoned::ResetCombatModeByLink` | summoned_cpp | 8 | leaf |
| 22 | GD | `0x611e80` | `Summoned::ResetCombatMode` | summoned_cpp | 8 | leaf |
| 23 | GD | `0x615250` | `Summoned::OnAttacked` | summoned_cpp | 16 | leaf |
| 24 | GD | `0x615b30` | `SummonedManager::GetPc` | summoned_cpp | 17 | leaf |
| 25 | GD | `0x616c30` | `Summoned::changeMoveState` | summoned_cpp | 28 | leaf |
| 26 | GD | `0x616f10` | `Summoned::StartCombat` | summoned_cpp | 8 | leaf |
| 27 | GD | `0x616f50` | `Summoned::FinishCombat` | summoned_cpp | 7 | setter |
| 28 | GD | `0x33a160` | `BannedWordFilterDynamicMemoryManager::Alloc` | bannedwordfiltermemorymanager | 11 | leaf |
| 29 | GD | `0x33a170` | `BannedWordFilterDynamicMemoryManager::Realloc` | bannedwordfiltermemorymanager | 12 | leaf |
| 30 | GD | `0x616fa0` | `BannedWordFilterDynamicMemoryManager::Free` | bannedwordfiltermemorymanager | 11 | leaf |
| 31 | GD | `0x8c2a0` | `NpcContribution::Reset` | contribution_h | 7 | setter |
| 32 | GD | `0x455480` | `PcContribution::PcContribution` | contribution_h | 12 | xtor |
| 33 | GD | `0x4554a0` | `ContributionPouch::ContributionPouch` | contribution_h | 16 | leaf |
| 34 | GD | `0x49390` | `ArenaLobbyRoomUtil::IsDungeonGameMode` | arenalobbycommon | 7 | getter |
| 35 | GD | `0x493a0` | `ArenaLobbyRoomUtil::IsPartyBattleFieldGameMode` | arenalobbycommon | 7 | getter |
| 36 | GD | `0x493b0` | `ArenaLobbyRoomUtil::IsPublicRaidGameMode` | arenalobbycommon | 7 | leaf |
| 37 | GD | `0x49900` | `ArenaLobbyRoomUtil::IsPreserveSessionInArenaEnable` | arenalobbycommon | 26 | leaf |
| 38 | GD | `0x634a0` | `BrainRaidBoss::GetLastTargetId` | brainraidboss_h | 7 | getter |
| 39 | GD | `0x634b0` | `BrainRaidBoss::GetState` | brainraidboss_h | 19 | leaf |
| 40 | GD | `0x654e0` | `CaptureTheFlag::getRatingRevise` | capturetheflag_cpp | 17 | leaf |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/arenaroommanager_h.cpp`
- `src/Server/GameDaemon/arenaroommanager_h.h`
- `src/Server/GameDaemon/publicraid_h.cpp`
- `src/Server/GameDaemon/publicraid_h.h`
- `src/Server/GameDaemon/actsequenceloader_h.cpp`
- `src/Server/GameDaemon/actsequenceloader_h.h`
- `src/Server/GameDaemon/bosscombatsequence.cpp`
- `src/Server/GameDaemon/bosscombatsequence.h`
- `src/Server/GameDaemon/summoned_cpp.cpp`
- `src/Server/GameDaemon/summoned_cpp.h`
- `src/Server/GameDaemon/bannedwordfiltermemorymanager.cpp`
- `src/Server/GameDaemon/bannedwordfiltermemorymanager.h`
- `src/Server/GameDaemon/contribution_h.cpp`
- `src/Server/GameDaemon/contribution_h.h`
- `src/Server/GameDaemon/arenalobbycommon.cpp`
- `src/Server/GameDaemon/arenalobbycommon.h`
- `src/Server/GameDaemon/brainraidboss_h.cpp`
- `src/Server/GameDaemon/brainraidboss_h.h`
- `src/Server/GameDaemon/capturetheflag_cpp.cpp`
- `src/Server/GameDaemon/capturetheflag_cpp.h`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-e20.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
