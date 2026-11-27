# lift-gamedaemon-39: Packet and Server shared and others: gamepackethandlerlist, chattinglog, bnscommonutil, smartcoupondchannel, ...

| Item | Value |
| --- | --- |
| Exe | GD |
| Source build | GameDaemon 2019 + PDB (VS2010 SP1) |
| Exe file | `<work-root>/ida/lift/GameDaemon/GameDaemon.exe` |
| PDB | `<work-root>/ida/lift/GameDaemon/GameDaemon.pdb` |
| Pseudocode | `~/.cache/bns-lift/hr/GameDaemon/<stem>.c` |
| Pseudocode index | `~/.cache/bns-lift/hr/GameDaemon/index.tsv` (stem, rva, name, first, last, status, source file, part) |
| Wave | W1 |
| Model | opus |
| Depends on | `lift-gamedaemon-e45`, `lift-gamedaemon-2`, `lift-gamedaemon-12`, `lift-gamedaemon-9`, `lift-gamedaemon-8` |
| Pattern | `src/Server/Shared/BnsCommonConfigDefinition.cpp` |
| Plan | `Docs/Plan/gamedaemon-lift.md` sections 1, 3, 5 |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Grep `Docs/Parity/lessons.md` for A2 (block order), A6 (per-exe path literals), A12 (PDB member types), A18 (destructors), A21 (PDB facts) and A22 (per-exe source form). Do not read it in full.
- Pattern: `src/Server/Shared/BnsCommonConfigDefinition.cpp`. Read it one time. Use its form for the functions of this card.
- Dead-strip: `wmain` and most callers are still `LIFT_STUB` bodies. `/OPT:REF` removes a lifted function that has no live caller, and funcdiff then cannot pair it. For each function in scope with no live caller, add `#pragma comment(linker, "/INCLUDE:<public name>")` in its `.cpp` (public names: `llvm-pdbutil dump -publics`; grep `/INCLUDE` in `Docs/Parity/lessons.md`). Do not add a pragma for a function that a lifted caller keeps.

## Scope

22 functions, about 2,277 pseudocode lines (about 18,216 tokens). Stems: `gamepackethandlerlist`, `chattinglog`, `bnscommonutil`, `smartcoupondchannel`, `bnscommonconfigdefinition`.

The easy functions of this stem are in `lift-gamedaemon-e45`. Do not change them unless a fix needs it.

| n | Exe | RVA | PDB name | Stem | Lines |
| ---: | --- | --- | --- | --- | ---: |
| 1 | GD | `0xdfe50` | `HandleGame_QQC2CReq` | gamepackethandlerlist | 8 |
| 2 | GD | `0xdfe60` | `GameTestBotQuery` | gamepackethandlerlist | 714 |
| 3 | GD | `0x291490` | `ChattingLog::MessageByItemDistrict` | chattinglog | 57 |
| 4 | GD | `0x291630` | `ChattingLog::MessageByItemWorld` | chattinglog | 57 |
| 5 | GD | `0x5d48a0` | `ChattingLog::Normal` | chattinglog | 55 |
| 6 | GD | `0x5d4a30` | `ChattingLog::Whisper` | chattinglog | 58 |
| 7 | GD | `0xa690` | `BnsCommonUtil::ConvProductTypeStr2ProductTypes` | bnscommonutil | 43 |
| 8 | GD | `0x28070` | `SmartCouponSessionHandler::OnConnect` | smartcoupondchannel | 110 |
| 9 | GD | `0x282a0` | `SmartCouponSessionHandler::OnClose` | smartcoupondchannel | 90 |
| 10 | GD | `0x284e0` | `SmartCoupondChannel::Initialize` | smartcoupondchannel | 58 |
| 11 | GD | `0x28610` | `SmartCoupondChannel::SendHello` | smartcoupondchannel | 44 |
| 12 | GD | `0x28780` | `SmartCoupondChannelManager::Initialize` | smartcoupondchannel | 202 |
| 13 | GD | `0x28ad0` | `SmartCoupondChannelManager::Destroy` | smartcoupondchannel | 65 |
| 14 | GD | `0x28c40` | `SmartCoupondChannelManager::acquire` | smartcoupondchannel | 62 |
| 15 | GD | `0x28d10` | `SmartCoupondChannelManager::Send` | smartcoupondchannel | 63 |
| 16 | GD | `0x28e00` | `SmartCoupondChannelManager::LoadGameEventConfig` | smartcoupondchannel | 40 |
| 17 | GD | `0x28eb0` | `SmartCoupondChannelManager::SendGameEventByCharacterReq` | smartcoupondchannel | 148 |
| 18 | GD | `0x29170` | `SmartCoupondChannelManager::checkGameEventConfig` | smartcoupondchannel | 91 |
| 19 | GD | `0x9820` | `BnsCommonConfigLoad::Load` | bnscommonconfigdefinition | 18 |
| 20 | GD | `0x9960` | `BnsCommonConfig::LoadBnsCommonConfig` | bnscommonconfigdefinition | 80 |
| 21 | GD | `0x9e20` | `BnsCommonConfig::Dump` | bnscommonconfigdefinition | 98 |
| 22 | GD | `0x9fe0` | `BnsCommonConfig::CheckMinMaxBoundary` | bnscommonconfigdefinition | 116 |

### Shared functions

These functions are in shared source. They are not MATCH in each lifted exe that has them.

| PDB name | Shared file | Other exes | Note |
| --- | --- | --- | --- |
| `BnsCommonConfigLoad::Load` | `src/Server/Shared/BnsCommonConfigDefinition.cpp` | CacheGate, LobbyDaemon, LobbyGate, PostOfficeDaemon, SmartCouponDaemon | EXCLUDED in LobbyDaemon: read its `excluded.tsv` row first |
| `BnsCommonConfig::LoadBnsCommonConfig` | `src/Server/Shared/BnsCommonConfigDefinition.cpp` | CacheGate, LobbyDaemon, LobbyGate, PostOfficeDaemon, SmartCouponDaemon | - |
| `BnsCommonConfig::Dump` | `src/Server/Shared/BnsCommonConfigDefinition.cpp` | CacheGate, LobbyDaemon, LobbyGate, PostOfficeDaemon, SmartCouponDaemon | - |
| `BnsCommonConfig::CheckMinMaxBoundary` | `src/Server/Shared/BnsCommonConfigDefinition.cpp` | CacheGate, LobbyDaemon, LobbyGate, PostOfficeDaemon, SmartCouponDaemon | - |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Shared functions: fix them in the shared file. If GameDaemon needs another form, use a per-exe copy in `lift_common_gd` or a `LIFT_EXE_` wrapper (A22, pattern 35). The 5 other exes must keep each MATCH. A MATCH to DIFF change needs an `allow-worse.txt` row with the counts.
6. An EXCLUDED function has a proof that no honest source fix exists in that exe. Read the proof first. If the same cause applies to GameDaemon, write the function under "Not done" with the proof reference. Do not edit `excluded.tsv`.
7. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/gamepackethandlerlist.cpp`
- `src/Server/GameDaemon/gamepackethandlerlist.h`
- `src/Server/GameDaemon/chattinglog.cpp`
- `src/Server/GameDaemon/chattinglog.h`
- `src/Server/GameDaemon/bnscommonutil.cpp`
- `src/Server/GameDaemon/bnscommonutil.h`
- `src/Server/GameDaemon/smartcoupondchannel.cpp`
- `src/Server/GameDaemon/smartcoupondchannel.h`
- `src/Server/Shared/BnsCommonConfigDefinition.cpp`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-39.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
