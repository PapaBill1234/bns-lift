# lift-gamedaemon-e25: Easy leaves (BloodLib): lock, source_jsoncpp, channel, source_delayedrelease, ...

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

40 functions, about 755 pseudocode lines (about 6,040 tokens). Stems: `lock`, `source_jsoncpp`, `channel`, `source_delayedrelease`, `logarchivesession`, `daemon`, `source_logfile`.

Wave E (owner order 2026-11-27: the easiest work first). Each function in this card is a leaf: its body calls no other counted function that needs a lift. Thus a `LIFT_STUB` callee cannot keep it DIFF. Each function has at most 30 pseudocode lines. Ease key: 18.9 cost per function (rule in `Docs/Plan/gamedaemon-lift.md` section 3).

Lift only the functions in the table. The other functions of these stems are in later W cards. Those cards depend on this card.

| n | Exe | RVA | PDB name | Stem | Lines | Form |
| ---: | --- | --- | --- | --- | ---: | --- |
| 1 | GD | `0x1cbd0` | `AutoCS::Enter` | lock | 25 | leaf |
| 2 | GD | `0x1cc50` | `AutoCS::Leave` | lock | 25 | leaf |
| 3 | GD | `0x18d060` | `AccountInventoryChannelManager::~AccountInventoryChannelManager` | lock | 8 | xtor |
| 4 | GD | `0x1dc200` | `AutoSRW::~AutoSRW` | lock | 16 | leaf |
| 5 | GD | `0x6a4eb0` | `Json::Reader::Reader` | source_jsoncpp | 23 | leaf |
| 6 | GD | `0x6a83c0` | `Json::Exception::~Exception` | source_jsoncpp | 17 | leaf |
| 7 | GD | `0x6a8420` | `Json::Exception::what` | source_jsoncpp | 13 | leaf |
| 8 | GD | `0x6a8440` | `Json::throwRuntimeError` | source_jsoncpp | 22 | leaf |
| 9 | GD | `0x6a8540` | `Json::throwLogicError` | source_jsoncpp | 22 | leaf |
| 10 | GD | `0x6a8600` | `Json::Value::CommentInfo::~CommentInfo` | source_jsoncpp | 11 | xtor |
| 11 | GD | `0x6a87a0` | `Json::Value::CZString::~CZString` | source_jsoncpp | 11 | xtor |
| 12 | GD | `0x6a87d0` | `Json::Value::CZString::operator<` | source_jsoncpp | 28 | leaf |
| 13 | GD | `0x6aa080` | `Json::Value::isInt` | source_jsoncpp | 29 | leaf |
| 14 | GD | `0x6aa1b0` | `Json::Value::isUInt64` | source_jsoncpp | 26 | leaf |
| 15 | GD | `0x6aa430` | `Json::valueToString` | source_jsoncpp | 24 | leaf |
| 16 | GD | `0x6aa650` | `Json::valueToString` | source_jsoncpp | 10 | leaf |
| 17 | GD | `0x6aa680` | `Json::valueToString` | source_jsoncpp | 18 | leaf |
| 18 | GD | `0x6aad60` | `GameObjectIdManager::~GameObjectIdManager` | source_jsoncpp | 7 | xtor |
| 19 | GD | `0x69a3e0` | `DaemonChannel::Send` | channel | 20 | leaf |
| 20 | GD | `0x69a440` | `DaemonChannel::Send` | channel | 15 | leaf |
| 21 | GD | `0x69a4c0` | `DaemonChannel::Send` | channel | 20 | leaf |
| 22 | GD | `0x69a540` | `ClientSideHashedDaemonChannel::OnAccept` | channel | 15 | leaf |
| 23 | GD | `0x69a570` | `ClientSideHashedDaemonChannel::OnConnect` | channel | 18 | leaf |
| 24 | GD | `0x69a740` | `ClientSideDaemonChannel::initialize` | channel | 22 | leaf |
| 25 | GD | `0x69abf0` | `ClientSideHashedDaemonChannel::Send` | channel | 24 | leaf |
| 26 | GD | `0x69ac40` | `ClientSideHashedDaemonChannel::Send` | channel | 21 | leaf |
| 27 | GD | `0x69aca0` | `ClientSideHashedDaemonChannel::OnClose` | channel | 12 | leaf |
| 28 | GD | `0x69acc0` | `ClientSideHashedDaemonChannel::initialize` | channel | 22 | leaf |
| 29 | GD | `0x69afb0` | `ClientSideHashedDaemonChannel::releaseSession` | channel | 8 | leaf |
| 30 | GD | `0x69b0a0` | `ServerSideDaemonChannel::Initialize` | channel | 28 | leaf |
| 31 | GD | `0x6a11d0` | `DelayedRelease::DelayedRelease` | source_delayedrelease | 14 | leaf |
| 32 | GD | `0x6a1960` | `DelayedDelete::Cleanup` | source_delayedrelease | 22 | leaf |
| 33 | GD | `0x6a19d0` | `DelayedDelete::deleteNode` | source_delayedrelease | 21 | leaf |
| 34 | GD | `0x6a1a50` | `DeleteEvent::HandleEvent` | source_delayedrelease | 19 | leaf |
| 35 | GD | `0x6b9d00` | `LogArchiveSession::~LogArchiveSession` | logarchivesession | 20 | leaf |
| 36 | GD | `0x6ba510` | `LogArchiveSession::Close` | logarchivesession | 19 | leaf |
| 37 | GD | `0x68cf50` | `Daemon::AddDelayedRelease` | daemon | 23 | leaf |
| 38 | GD | `0x68d9e0` | `Daemon::SetPublicAddressWithSetting` | daemon | 11 | leaf |
| 39 | GD | `0x68dba0` | `parseCIDRAddress` | daemon | 25 | leaf |
| 40 | GD | `0x6a0250` | `LogFile::Write` | source_logfile | 21 | leaf |

Same name in a lifted exe (a different body is possible): `AutoCS::Leave` (src/Server/Economy/MarketDealerDaemon/JobContext.cpp).

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/lock.cpp`
- `src/Server/GameDaemon/lock.h`
- `src/Server/GameDaemon/source_jsoncpp.cpp`
- `src/Server/GameDaemon/source_jsoncpp.h`
- `src/Server/GameDaemon/channel.cpp`
- `src/Server/GameDaemon/channel.h`
- `src/Server/GameDaemon/source_delayedrelease.cpp`
- `src/Server/GameDaemon/source_delayedrelease.h`
- `src/Server/GameDaemon/logarchivesession.cpp`
- `src/Server/GameDaemon/logarchivesession.h`
- `src/Server/GameDaemon/daemon.cpp`
- `src/Server/GameDaemon/daemon.h`
- `src/Server/GameDaemon/source_logfile.cpp`
- `src/Server/GameDaemon/source_logfile.h`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-e25.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
