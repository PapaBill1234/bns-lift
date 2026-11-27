# lift-gamedaemon-e1: Easy leaves (BloodLib and Packet and others): include_network, include_logarchive, include_delayedrelease, include_logmedia, ...

| Item | Value |
| --- | --- |
| Exe | GD |
| Source build | GameDaemon 2019 + PDB (VS2010 SP1) |
| Exe file | `<work-root>/ida/lift/GameDaemon/GameDaemon.exe` |
| PDB | `<work-root>/ida/lift/GameDaemon/GameDaemon.pdb` |
| Pseudocode | `~/.cache/bns-lift/hr/GameDaemon/<stem>.c` |
| Pseudocode index | `~/.cache/bns-lift/hr/GameDaemon/index.tsv` (stem, rva, name, first, last, status, source file, part) |
| Wave | E |
| Model | sonnet:high |
| Depends on | `lift-gamedaemon-0e` |
| Pattern | `src/Server/BloodLib/source/Network.cpp` |
| Plan | `Docs/Plan/gamedaemon-lift.md` sections 1, 3, 5 |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Grep `Docs/Parity/lessons.md` for A2 (block order), A6 (per-exe path literals), A12 (PDB member types), A18 (destructors), A21 (PDB facts) and A22 (per-exe source form). Do not read it in full.
- Pattern: `src/Server/BloodLib/source/Network.cpp`. Read it one time. Use its form for the functions of this card.

## Scope

11 functions, about 86 pseudocode lines (about 688 tokens). Stems: `include_network`, `include_logarchive`, `include_delayedrelease`, `include_logmedia`, `logserversessionhandler_h`, `fragmentpacket_cpp`, `table`, `source_network`, `winserviceconsole_h`.

Wave E (owner order 2026-11-27: the easiest work first). Each function in this card is a leaf: its body calls no other counted function that needs a lift. Thus a `LIFT_STUB` callee cannot keep it DIFF. Each function has at most 30 pseudocode lines. Ease key: 7.8 cost per function (rule in `Docs/Plan/gamedaemon-lift.md` section 3).

Lift only the functions in the table. The other functions of these stems are in later W cards. Those cards depend on this card.

| n | Exe | RVA | PDB name | Stem | Lines | Form |
| ---: | --- | --- | --- | --- | ---: | --- |
| 1 | GD | `0x33b980` | `AccountInventorySessionHandler::~AccountInventorySessionHandler` | include_network | 7 | xtor |
| 2 | GD | `0x3feed0` | `CombatSeqState::GetState` | include_logarchive | 7 | getter |
| 3 | GD | `0x694060` | `LogArchive::Name` | include_logarchive | 7 | getter |
| 4 | GD | `0x467720` | `AttachEquipGemPieceAction::getPriority` | include_delayedrelease | 7 | getter |
| 5 | GD | `0x6dcc40` | `AccessoryItem::GetDurability` | include_logmedia | 7 | getter |
| 6 | GD | `0x6ba560` | `LogServerSessionHandler::~LogServerSessionHandler` | logserversessionhandler_h | 7 | xtor |
| 7 | GD | `0x5aed40` | `EffectCacheUpdate::~EffectCacheUpdate` | fragmentpacket_cpp | 7 | xtor |
| 8 | GD | `0x1d050` | `DrElIter::~DrElIter` | table | 8 | xtor |
| 9 | GD | `0x19590` | `AccessoryItem::GetCount` | source_network | 7 | getter |
| 10 | GD | `0x68f080` | `AccessoryItem::R_CheckEnchantTargetItem` | source_network | 11 | getter |
| 11 | GD | `0x455420` | `ActSequenceLoader::ReadFromBuffer` | winserviceconsole_h | 11 | getter |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/include_network.cpp`
- `src/Server/GameDaemon/include_network.h`
- `src/Server/GameDaemon/include_logarchive.cpp`
- `src/Server/GameDaemon/include_logarchive.h`
- `src/Server/GameDaemon/include_delayedrelease.cpp`
- `src/Server/GameDaemon/include_delayedrelease.h`
- `src/Server/GameDaemon/include_logmedia.cpp`
- `src/Server/GameDaemon/include_logmedia.h`
- `src/Server/GameDaemon/logserversessionhandler_h.cpp`
- `src/Server/GameDaemon/logserversessionhandler_h.h`
- `src/Server/GameDaemon/fragmentpacket_cpp.cpp`
- `src/Server/GameDaemon/fragmentpacket_cpp.h`
- `src/Server/GameDaemon/table.cpp`
- `src/Server/GameDaemon/table.h`
- `src/Server/GameDaemon/source_network.cpp`
- `src/Server/GameDaemon/source_network.h`
- `src/Server/GameDaemon/winserviceconsole_h.cpp`
- `src/Server/GameDaemon/winserviceconsole_h.h`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-e1.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
