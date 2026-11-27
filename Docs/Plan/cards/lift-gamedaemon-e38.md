# lift-gamedaemon-e38: Easy leaves (GameDaemon): marketreaderagentchannel, gamearenachannel_cpp_2, npservicetran_cpp, leaveworldtran_cpp, ...

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
| Pattern | `src/Server/LobbyDaemon/GamedChannel.cpp` |
| Plan | `Docs/Plan/gamedaemon-lift.md` sections 1, 3, 5 |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Grep `Docs/Parity/lessons.md` for A2 (block order), A6 (per-exe path literals), A12 (PDB member types), A18 (destructors), A21 (PDB facts) and A22 (per-exe source form). Do not read it in full.
- Pattern: `src/Server/LobbyDaemon/GamedChannel.cpp`. Read it one time. Use its form for the functions of this card.

## Scope

15 functions, about 362 pseudocode lines (about 2,896 tokens). Stems: `marketreaderagentchannel`, `gamearenachannel_cpp_2`, `npservicetran_cpp`, `leaveworldtran_cpp`, `achievementchannel_cpp`, `rankingchannel`, `charactermanagementtran_cpp`.

Wave E (owner order 2026-11-27: the easiest work first). Each function in this card is a leaf: its body calls no other counted function that needs a lift. Thus a `LIFT_STUB` callee cannot keep it DIFF. Each function has at most 30 pseudocode lines. Ease key: 24.1 cost per function (rule in `Docs/Plan/gamedaemon-lift.md` section 3).

Lift only the functions in the table. The other functions of these stems are in later W cards. Those cards depend on this card.

| n | Exe | RVA | PDB name | Stem | Lines | Form |
| ---: | --- | --- | --- | --- | ---: | --- |
| 1 | GD | `0x1618f0` | `MarketReaderAgentSessionHandler::OnAccept` | marketreaderagentchannel | 18 | leaf |
| 2 | GD | `0x161d40` | `MarketReaderAgentSessionHandler::PacketHandler` | marketreaderagentchannel | 26 | leaf |
| 3 | GD | `0xd26d0` | `GameSideArenaLobbySessionHandler::OnAccept` | gamearenachannel_cpp_2 | 18 | leaf |
| 4 | GD | `0xd3000` | `GameArenaLobbyManager::GameArenaLobbyManager` | gamearenachannel_cpp_2 | 20 | leaf |
| 5 | GD | `0xd3720` | `GameArenaLobbyManager::ResetIsInitializeGuildInfo` | gamearenachannel_cpp_2 | 29 | leaf |
| 6 | GD | `0x16f4e0` | `GetNPCustomProtocolStr` | npservicetran_cpp | 21 | leaf |
| 7 | GD | `0x16f530` | `NPRegisterServiceTran::NPRegisterServiceTran` | npservicetran_cpp | 20 | leaf |
| 8 | GD | `0x170690` | `NPGetChannelPropertyTran::NPGetChannelPropertyTran` | npservicetran_cpp | 29 | leaf |
| 9 | GD | `0x13bdc0` | `ReturnToLobbyTran::failProcess` | leaveworldtran_cpp | 24 | leaf |
| 10 | GD | `0x32f90` | `AchievementDaemonChannel::onConnect` | achievementchannel_cpp | 30 | leaf |
| 11 | GD | `0x33520` | `HandleAchievementGameGameHelloFail` | achievementchannel_cpp | 22 | leaf |
| 12 | GD | `0xa7870` | `AchievementDaemonChannel::Destroy` | achievementchannel_cpp | 22 | leaf |
| 13 | GD | `0x1af180` | `RankingChannel::onConnect` | rankingchannel | 27 | leaf |
| 14 | GD | `0x1af940` | `HandleRankingGame_HelloFail` | rankingchannel | 26 | leaf |
| 15 | GD | `0x760b0` | `DeleteCharacterTran::DeleteCharacterTran` | charactermanagementtran_cpp | 30 | leaf |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/marketreaderagentchannel.cpp`
- `src/Server/GameDaemon/marketreaderagentchannel.h`
- `src/Server/GameDaemon/gamearenachannel_cpp_2.cpp`
- `src/Server/GameDaemon/gamearenachannel_cpp_2.h`
- `src/Server/GameDaemon/npservicetran_cpp.cpp`
- `src/Server/GameDaemon/npservicetran_cpp.h`
- `src/Server/GameDaemon/leaveworldtran_cpp.cpp`
- `src/Server/GameDaemon/leaveworldtran_cpp.h`
- `src/Server/GameDaemon/achievementchannel_cpp.cpp`
- `src/Server/GameDaemon/achievementchannel_cpp.h`
- `src/Server/GameDaemon/rankingchannel.cpp`
- `src/Server/GameDaemon/rankingchannel.h`
- `src/Server/GameDaemon/charactermanagementtran_cpp.cpp`
- `src/Server/GameDaemon/charactermanagementtran_cpp.h`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-e38.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
