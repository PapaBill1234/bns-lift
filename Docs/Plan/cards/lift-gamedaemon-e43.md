# lift-gamedaemon-e43: Easy leaves (GameDaemon): arenaroommanager_cpp, guild_cpp_2, guildcraft, partyauction, ...

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
| Pattern | `src/Server/LobbyGate/Client.cpp` |
| Plan | `Docs/Plan/gamedaemon-lift.md` sections 1, 3, 5 |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Grep `Docs/Parity/lessons.md` for A2 (block order), A6 (per-exe path literals), A12 (PDB member types), A18 (destructors), A21 (PDB facts) and A22 (per-exe source form). Do not read it in full.
- Pattern: `src/Server/LobbyGate/Client.cpp`. Read it one time. Use its form for the functions of this card.
- Dead-strip: `wmain` and most callers are still `LIFT_STUB` bodies. `/OPT:REF` removes a lifted function that has no live caller, and funcdiff then cannot pair it. For each function in scope with no live caller, add `#pragma comment(linker, "/INCLUDE:<public name>")` in its `.cpp` (public names: `llvm-pdbutil dump -publics`; grep `/INCLUDE` in `Docs/Parity/lessons.md`). Do not add a pragma for a function that a lifted caller keeps.

## Scope

40 functions, about 891 pseudocode lines (about 7,128 tokens). Stems: `arenaroommanager_cpp`, `guild_cpp_2`, `guildcraft`, `partyauction`, `petitionmanager`, `challengeparty`, `clientsessionhandler`, `mysteriousstore`, `challengelistcontainer_cpp`.

Wave E (owner order 2026-11-27: the easiest work first). Each function in this card is a leaf: its body calls no other counted function that needs a lift. Thus a `LIFT_STUB` callee cannot keep it DIFF. Each function has at most 30 pseudocode lines. Ease key: 22.3 cost per function (rule in `Docs/Plan/gamedaemon-lift.md` section 3).

Lift only the functions in the table. The other functions of these stems are in later W cards. Those cards depend on this card.

| n | Exe | RVA | PDB name | Stem | Lines | Form |
| ---: | --- | --- | --- | --- | ---: | --- |
| 1 | GD | `0x49c50` | `ArenaDuelRoom::build` | arenaroommanager_cpp | 21 | leaf |
| 2 | GD | `0x49ed0` | `ArenaDungeonRoom::ArenaDungeonRoom` | arenaroommanager_cpp | 22 | leaf |
| 3 | GD | `0x4a090` | `ArenaDungeonRoom::GetPcContentsType` | arenaroommanager_cpp | 20 | leaf |
| 4 | GD | `0x4a350` | `ArenaPublicRaidRoom::ArenaPublicRaidRoom` | arenaroommanager_cpp | 27 | leaf |
| 5 | GD | `0x4a500` | `ArenaPublicRaidRoom::GetPcContentsType` | arenaroommanager_cpp | 12 | leaf |
| 6 | GD | `0x4a6e0` | `ArenaRoomManager::ArenaRoomManager` | arenaroommanager_cpp | 20 | leaf |
| 7 | GD | `0x4a900` | `ArenaRoomManager::IssueOtp` | arenaroommanager_cpp | 21 | leaf |
| 8 | GD | `0x4ac20` | `ArenaSessionTimer::ArenaSessionTimer` | arenaroommanager_cpp | 26 | leaf |
| 9 | GD | `0x4acc0` | `DisconnectedArenaSessionInfo::~DisconnectedArenaSessionInfo` | arenaroommanager_cpp | 8 | xtor |
| 10 | GD | `0x4acd0` | `DisconnectedArenaSessionInfo::Init` | arenaroommanager_cpp | 30 | leaf |
| 11 | GD | `0x4ae50` | `DisconnectedArenaSessionInfo::Decompose` | arenaroommanager_cpp | 30 | leaf |
| 12 | GD | `0xfa2d0` | `Guild::isFullWaitingGuildMember` | guild_cpp_2 | 22 | leaf |
| 13 | GD | `0xfa740` | `Guild::findByPcDbId` | guild_cpp_2 | 24 | leaf |
| 14 | GD | `0xfa770` | `Guild::findByPcName` | guild_cpp_2 | 17 | leaf |
| 15 | GD | `0xfa7f0` | `Guild::findByPcDbIdInWaiting` | guild_cpp_2 | 24 | leaf |
| 16 | GD | `0xfa830` | `Guild::checkPermissionGuild20` | guild_cpp_2 | 9 | leaf |
| 17 | GD | `0x1018d0` | `Guild::EnableRetrieveRankingInfo` | guild_cpp_2 | 25 | leaf |
| 18 | GD | `0x104f10` | `GuildIdManager::Initialize` | guild_cpp_2 | 22 | leaf |
| 19 | GD | `0x104f90` | `GuildIdManager::PushGuildId` | guild_cpp_2 | 28 | leaf |
| 20 | GD | `0x105030` | `GuildIdManager::PopGuildId` | guild_cpp_2 | 25 | leaf |
| 21 | GD | `0x114960` | `GuildCraft::GetAsseintGuildCraftQuota` | guildcraft | 28 | leaf |
| 22 | GD | `0x114ad0` | `GuildCraft::EnableMakeGuildCraft` | guildcraft | 30 | leaf |
| 23 | GD | `0x114b90` | `GuildCraft::MakeGuildCraft` | guildcraft | 21 | leaf |
| 24 | GD | `0x114c30` | `GuildCraft::EnableDonationGuildCraft` | guildcraft | 12 | leaf |
| 25 | GD | `0x115190` | `GuildCraft::IsCompletedGuildCraftDonation` | guildcraft | 19 | leaf |
| 26 | GD | `0x173570` | `PartyAuction::nextStep` | partyauction | 28 | leaf |
| 27 | GD | `0x173640` | `PartyAuction::sendSelectPacket` | partyauction | 28 | leaf |
| 28 | GD | `0x1736c0` | `PartyAuction::checkAuth` | partyauction | 10 | leaf |
| 29 | GD | `0x18f8d0` | `Petition::Petition` | petitionmanager | 20 | leaf |
| 30 | GD | `0x18fa50` | `Petition::Accept` | petitionmanager | 24 | leaf |
| 31 | GD | `0x18fb30` | `PetitionManager::PetitionManager` | petitionmanager | 22 | leaf |
| 32 | GD | `0x65f80` | `ChallengeParty::~ChallengeParty` | challengeparty | 24 | leaf |
| 33 | GD | `0x6aed0` | `ChallengePartyManager::Initialize` | challengeparty | 22 | leaf |
| 34 | GD | `0x7d6b0` | `ClientSessionHandler::OnCreated` | clientsessionhandler | 27 | leaf |
| 35 | GD | `0x7d730` | `ClientSessionHandler::OnDestroyed` | clientsessionhandler | 24 | leaf |
| 36 | GD | `0x7d7b0` | `ClientSessionHandler::OnAccept` | clientsessionhandler | 23 | leaf |
| 37 | GD | `0x7d810` | `ClientSessionHandler::OnConnect` | clientsessionhandler | 19 | leaf |
| 38 | GD | `0x16d9c0` | `MysteriousStore::IsAuthorizedMember` | mysteriousstore | 24 | leaf |
| 39 | GD | `0xe920` | `ChallengeListEntry::Initialize` | challengelistcontainer_cpp | 30 | leaf |
| 40 | GD | `0xef90` | `ChallengeListContainer::~ChallengeListContainer` | challengelistcontainer_cpp | 23 | leaf |

Same name in a lifted exe (a different body is possible): `ClientSessionHandler::OnAccept` (src/Server/LobbyGate/Client.cpp), `ClientSessionHandler::OnConnect` (src/Server/LobbyGate/Client.cpp).

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/arenaroommanager_cpp.cpp`
- `src/Server/GameDaemon/arenaroommanager_cpp.h`
- `src/Server/GameDaemon/guild_cpp_2.cpp`
- `src/Server/GameDaemon/guild_cpp_2.h`
- `src/Server/GameDaemon/guildcraft.cpp`
- `src/Server/GameDaemon/guildcraft.h`
- `src/Server/GameDaemon/partyauction.cpp`
- `src/Server/GameDaemon/partyauction.h`
- `src/Server/GameDaemon/petitionmanager.cpp`
- `src/Server/GameDaemon/petitionmanager.h`
- `src/Server/GameDaemon/challengeparty.cpp`
- `src/Server/GameDaemon/challengeparty.h`
- `src/Server/GameDaemon/clientsessionhandler.cpp`
- `src/Server/GameDaemon/clientsessionhandler.h`
- `src/Server/GameDaemon/mysteriousstore.cpp`
- `src/Server/GameDaemon/mysteriousstore.h`
- `src/Server/GameDaemon/challengelistcontainer_cpp.cpp`
- `src/Server/GameDaemon/challengelistcontainer_cpp.h`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-e43.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
