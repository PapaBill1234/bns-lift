# lift-gamedaemon-4: BloodLib: source_delayedrelease, httpclient, propertydb, source_timer

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
| Depends on | `lift-gamedaemon-2` |
| Pattern | `src/Server/BloodLib/source/DelayedRelease.cpp` |
| Plan | `Docs/Plan/gamedaemon-lift.md` sections 1, 3, 5 |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Grep `Docs/Parity/lessons.md` for A2 (block order), A6 (per-exe path literals), A12 (PDB member types), A18 (destructors), A21 (PDB facts) and A22 (per-exe source form). Do not read it in full.
- Pattern: `src/Server/BloodLib/source/DelayedRelease.cpp`. Read it one time. Use its form for the functions of this card.

## Scope

22 functions, about 1,474 pseudocode lines (about 11,792 tokens). Stems: `source_delayedrelease`, `httpclient`, `propertydb`, `source_timer`.

| n | Exe | RVA | PDB name | Stem | Lines |
| ---: | --- | --- | --- | --- | ---: |
| 1 | GD | `0x6a11d0` | `DelayedRelease::DelayedRelease` | source_delayedrelease | 14 |
| 2 | GD | `0x6a16d0` | `DelayedDelete::Add` | source_delayedrelease | 46 |
| 3 | GD | `0x6a17c0` | `DelayedDelete::Delete` | source_delayedrelease | 80 |
| 4 | GD | `0x6a1960` | `DelayedDelete::Cleanup` | source_delayedrelease | 22 |
| 5 | GD | `0x6a19d0` | `DelayedDelete::deleteNode` | source_delayedrelease | 21 |
| 6 | GD | `0x6a1a50` | `DeleteEvent::HandleEvent` | source_delayedrelease | 19 |
| 7 | GD | `0x6a1af0` | `HTTPClient::~HTTPClient` | httpclient | 42 |
| 8 | GD | `0x6a1c00` | `HTTPClient::Request` | httpclient | 139 |
| 9 | GD | `0x6a1e80` | `HTTPClient::connect` | httpclient | 69 |
| 10 | GD | `0x6a2080` | `HTTPClient::requestOfURI` | httpclient | 21 |
| 11 | GD | `0x6a20b0` | `HTTPClient::responseOfBytes` | httpclient | 31 |
| 12 | GD | `0x6a2180` | `HTTPClient::queryHttpInfo` | httpclient | 61 |
| 13 | GD | `0x6a2300` | `HTTPClient::queryContentLength` | httpclient | 23 |
| 14 | GD | `0x6a23a0` | `HTTPClient::response` | httpclient | 225 |
| 15 | GD | `0x6a2810` | `HTTPClient::GetHttpResponseUnicodeString` | httpclient | 76 |
| 16 | GD | `0x6a29c0` | `HTTPClient::parseURL` | httpclient | 194 |
| 17 | GD | `0x6a2d30` | `HTTPClient::requestPostBody` | httpclient | 74 |
| 18 | GD | `0x6a2e70` | `WebUtil::ConvertMultiByteToWideChar` | httpclient | 91 |
| 19 | GD | `0x6a30a0` | `WebUtil::ConvertWideCharToMultiByte` | httpclient | 72 |
| 20 | GD | `0x6ae310` | `DbSyncDefine::MakeWhereClause` | propertydb | 30 |
| 21 | GD | `0x6ae400` | `QueryString::Append` | propertydb | 62 |
| 22 | GD | `0x6b0ec0` | `TimerQueue::RemoveAndAdd` | source_timer | 62 |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/source_delayedrelease.cpp`
- `src/Server/GameDaemon/source_delayedrelease.h`
- `src/Server/GameDaemon/httpclient.cpp`
- `src/Server/GameDaemon/httpclient.h`
- `src/Server/GameDaemon/propertydb.cpp`
- `src/Server/GameDaemon/propertydb.h`
- `src/Server/GameDaemon/source_timer.cpp`
- `src/Server/GameDaemon/source_timer.h`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-4.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
