# lift-lobbydaemon-plan: plan the lift of LobbyDaemon

Repo: bns-lift (public). This card is the record of the LobbyDaemon planner. The planner did not lift code. It wrote cards 0 to 58, the verify card and the queue file.

| Item | Value |
| --- | --- |
| Server | LobbyDaemon |
| Slug | lobbydaemon |
| Source build | LobbyDaemon 2019 + PDB (VS2010 SP1) |
| Exe | `/home/ubuntu/Documents/Codex/private-project/ida/lift/LobbyDaemon/LobbyDaemon.exe` |
| PDB | `/home/ubuntu/Documents/Codex/private-project/ida/lift/LobbyDaemon/LobbyDaemon.pdb` |
| Pseudocode index | `~/.cache/bns-lift/hr/LobbyDaemon/index.tsv` |
| Dep of the first card | `-` (no earlier LobbyDaemon card) |
| Lift cards | 59 (`lift-lobbydaemon-0` to `lift-lobbydaemon-58`) |
| Verify card | `lift-lobbydaemon-verify` |
| Queue file | `Docs/Plan/queue/lift-lobbydaemon-plan.tsv` |

Do not use `LobbyDaemon2019.exe` or a 381 file as the source. The exe in `Service_348_8349/Service/LobbyDaemon/bin/` has the same SHA-256 as the source exe.

## What the planner did
1. It listed the PDB modules and their functions with `tools/hr_export.py` and `llvm-pdbutil dump -modules`.
2. It removed the CRT modules, the vendor modules (zstd and the related modules) and the compiler-made code. The name filter is the same as in `tools/coverage.py`.
3. It compared each remaining function with the objects of the current lift build (`llvm-nm` and `llvm-undname`). A module with all functions in the lift build is skipped.
4. It kept 108 modules:

| Kind | Modules | Functions | Card |
| --- | --- | --- | --- |
| new-server (`LobbyDaemon/service`) | 96 | 1,769 | 2 to 57 |
| new-common | 6 | 28 | 1 |
| missing-common (only the missing functions) | 6 | 18 | 1 |
| **Total** | **108** | **1,815** | |

The new-common modules are BannedWordFilterLib, BannedWordFilterLoader, ConstFilterChat, ConstFilterName, FsdDecomposer and PerfCounterProvider. The missing-common functions are in ContentsRuleConfigDefinition (4), CryptoKey (2), Db (1), NPChannel2 (4), Network (1) and SharedChannel (6).

5. It grouped the modules into cards. A large module is split over cards. Each part has an RVA range. The ranges of one module do not overlap.
6. It put the cards into waves. Cards of one wave do not share a source file. A card needs only headers from card 0 or from an earlier wave.
7. It checked the cards: each kept module is in one card, or in parts with ranges that do not overlap. The counts and the line values agree with the index.

## Count rules
- The function count of a module excludes the deleting destructors only. The index has 2,592 rows. 151 of them are deleting destructors.
- The pseudocode lines of a whole module are the largest `end_line` of the module in the index.
- The pseudocode lines of a part are the sum of the function spans (`end_line - start_line + 1`) in the RVA range.
- The template limit is 2,500 lines per card. The LobbyDaemon cards have 3,500 lines or fewer. The largest card (`lift-lobbydaemon-51`) has 3,483 lines. A smaller limit gives more than 59 cards and more waves.

## Waves
The values are the sums of the card tables. The 18 missing functions of card 1 have 585 lines.


| Wave | Cards | Model | Functions | Pseudocode lines | Scope |
| --- | --- | --- | --- | --- | --- |
| 0 | 0 | opus | - | - | Headers from the PDB, stubs, CMake target `LobbyDaemon` |
| 1 | 1-6 | opus | 211 + 18 missing | 16,040 + 585 | Common modules, CliSession 1, CliSessionTable 1, Character, Mileage 1, LobbyService 1 |
| 2 | 7-12 | opus | 210 | 16,355 | CliSession 2, CliSessionTable 2, GameWorld, Mileage 2, LobbyService 2, AuctionEscrow |
| 3 | 13 opus, 14-18 sol | mixed | 194 | 17,427 | CliSession 3, LobbyDB 1, LobbyDaemon 1, packet handlers 1, GamedChannel 1 |
| 4 | 19, 21-24 sol, 20 opus | mixed | 192 | 17,022 | LobbyDB 2, LobbyDaemon 2, packet handlers 2, channels |
| 5 | 25-30 | sol | 222 | 17,122 | LobbyDB 3, LobbyGamePacketHandler 3, channels, NPLobbyMessageHandler |
| 6 | 31-36 | sol | 168 | 19,482 | LobbyDB 4, jobs part 1 |
| 7 | 37-42 | sol | 186 | 19,550 | LobbyDB 5, jobs part 2 |
| 8 | 43-48 | sol | 158 | 17,913 | LobbyDB 6, jobs |
| 9 | 49-54 | sol | 191 | 18,483 | Jobs, LobbyJob base |
| 10 | 55-57 | sol | 65 | 8,670 | StartCliSessionWnpTokenJob 3, CreateCharacterJob, ChangeUserNameJob |
| 11 | 58 | opus | - | - | Remove the stubs, link the exe, startup check |
| **Total** | **59** | | **1,797 + 18 missing** | **168,064 + 585** | |

```
wave 0 -> wave 1 -> wave 2 -> ... -> wave 10 -> wave 11 -> verify
```

## Queue file format
One row per line. 9 columns, separated by one TAB. No header.

| Column | Value |
| --- | --- |
| id | `lift-lobbydaemon-N` or `lift-lobbydaemon-verify` |
| kind | `lift` |
| model | The `Model` value of the card (`opus` or `sol`). Verify: `opus`. |
| crate | `-` |
| paths | Comma list of the card "Files" (no spaces). Card 0 and card 58 use the folders. |
| deps | Card 0: `-`. A card of wave N: all cards of wave N-1. Verify: `lift-lobbydaemon-58`. |
| turns | `150` |
| status | `ready` |
| title | `Lift LobbyDaemon: <card title>` (no TAB) |

The rows are in card order. The verify row is the last row. There is no next-planner row. LobbyDaemon was planned out of the server order in `Docs/Plan/plan.md`.

## CMake
Each card has `CMakeLists.txt` in "Files". Card 0 adds all source files to the target. A card changes `CMakeLists.txt` only if the target does not have a source file of the card. Then two cards of one wave can change the same file. Keep each change to one line, and merge one card at a time.

## Files
- `Docs/Plan/cards/`
- `Docs/Plan/queue/`

## Blocked
`Docs/Plan/plan.md` (parity phase) says: no new daemon work starts before CacheGate, LobbyGate, SmartCouponDaemon and PostOfficeDaemon reach 90 % parity. The queue rows have the status `ready`. Do not start them before that checkpoint, or before the operator starts them.

## Done when
- The cards 0 to 58, the verify card and the queue file exist.
- `tools/gate.sh` prints `gate ok`.
