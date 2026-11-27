# lift-gamedaemon-34: BloodLib and Shared gaps: source_network, packetbufferhandler, winserviceconsole_h, source_alertsender, ...

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
| Depends on | `lift-gamedaemon-8`, `lift-gamedaemon-33` |
| Pattern | `src/Server/BloodLib/source/Network.cpp` |
| Plan | `Docs/Plan/gamedaemon-lift.md` sections 1, 3, 5 |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Grep `Docs/Parity/lessons.md` for A2 (block order), A6 (per-exe path literals), A12 (PDB member types), A18 (destructors), A21 (PDB facts) and A22 (per-exe source form). Do not read it in full.
- Pattern: `src/Server/BloodLib/source/Network.cpp`. Read it one time. Use its form for the functions of this card.

## Scope

24 functions, about 1,278 pseudocode lines (about 10,224 tokens). Stems: `source_network`, `packetbufferhandler`, `winserviceconsole_h`, `source_alertsender`, `propertysync`.

| n | Exe | RVA | PDB name | Stem | Lines |
| ---: | --- | --- | --- | --- | ---: |
| 1 | GD | `0x19590` | `AccessoryItem::GetCount` | source_network | 7 |
| 2 | GD | `0x68f080` | `AccessoryItem::R_CheckEnchantTargetItem` | source_network | 11 |
| 3 | GD | `0x68f1a0` | `Network::Initialize` | source_network | 50 |
| 4 | GD | `0x68f5d0` | `Network::OpenPort` | source_network | 130 |
| 5 | GD | `0x68f8e0` | `Network::OpenPort` | source_network | 32 |
| 6 | GD | `0x68ff90` | `Network::initWorkerThread` | source_network | 63 |
| 7 | GD | `0x4c380` | `ActSeqState::GetState` | packetbufferhandler | 7 |
| 8 | GD | `0x69ddc0` | `TrustedPacketBufferHandler::Clone` | packetbufferhandler | 23 |
| 9 | GD | `0x69de40` | `TrustedPacketBufferHandler::ToPacket` | packetbufferhandler | 46 |
| 10 | GD | `0x69e780` | `RawPacketBufferHandler::Clone` | packetbufferhandler | 42 |
| 11 | GD | `0x455420` | `ActSequenceLoader::ReadFromBuffer` | winserviceconsole_h | 11 |
| 12 | GD | `0x686920` | `destroy` | source_alertsender | 19 |
| 13 | GD | `0x686a90` | `AlertSender::init` | source_alertsender | 72 |
| 14 | GD | `0x686c20` | `AlertSender::fini` | source_alertsender | 42 |
| 15 | GD | `0x687ce0` | `SyncBuffer::~SyncBuffer` | propertysync | 48 |
| 16 | GD | `0x687df0` | `SyncBuffer::Initialize` | propertysync | 81 |
| 17 | GD | `0x687fc0` | `SyncBuffer::Initialize` | propertysync | 40 |
| 18 | GD | `0x6880c0` | `SyncBuffer::Clear` | propertysync | 36 |
| 19 | GD | `0x688130` | `SyncBuffer::Copy` | propertysync | 32 |
| 20 | GD | `0x6881b0` | `SyncBuffer::Set` | propertysync | 193 |
| 21 | GD | `0x688560` | `SyncBuffer::set` | propertysync | 188 |
| 22 | GD | `0x688890` | `SyncBuffer::setInt` | propertysync | 26 |
| 23 | GD | `0x6888d0` | `SyncBuffer::setString` | propertysync | 51 |
| 24 | GD | `0x688990` | `SyncBuffer::realign` | propertysync | 28 |

### Shared functions

These functions are in shared source. They are not MATCH in each lifted exe that has them.

| PDB name | Shared file | Other exes | Note |
| --- | --- | --- | --- |
| `Network::Initialize` | `src/Server/BloodLib/source/Network.cpp` | CacheGate, LobbyDaemon, LobbyGate, PostOfficeDaemon, SmartCouponDaemon | - |
| `Network::OpenPort` | `src/Server/BloodLib/source/Network.cpp` | CacheGate, LobbyDaemon, LobbyGate, PostOfficeDaemon, SmartCouponDaemon | - |
| `Network::OpenPort` | `src/Server/BloodLib/source/Network.cpp` | CacheGate, LobbyDaemon, LobbyGate, PostOfficeDaemon, SmartCouponDaemon | - |
| `Network::initWorkerThread` | `src/Server/BloodLib/source/Network.cpp` | CacheGate, LobbyDaemon, LobbyGate, PostOfficeDaemon, SmartCouponDaemon | EXCLUDED in LobbyDaemon: read its `excluded.tsv` row first |
| `TrustedPacketBufferHandler::Clone` | `src/Server/BloodLib/source/PacketBufferHandler.cpp` | CacheGate, LobbyDaemon, LobbyGate, PostOfficeDaemon, SmartCouponDaemon | EXCLUDED in LobbyDaemon: read its `excluded.tsv` row first |
| `TrustedPacketBufferHandler::ToPacket` | `src/Server/BloodLib/source/PacketBufferHandler.cpp` | CacheGate, LobbyDaemon, LobbyGate, PostOfficeDaemon, SmartCouponDaemon | EXCLUDED in LobbyDaemon: read its `excluded.tsv` row first |
| `RawPacketBufferHandler::Clone` | `src/Server/BloodLib/source/PacketBufferHandler.cpp` | LobbyDaemon, SmartCouponDaemon | EXCLUDED in LobbyDaemon: read its `excluded.tsv` row first |
| `AlertSender::init` | `src/Server/BloodLib/source/AlertSender.cpp` | LobbyGate | - |
| `AlertSender::fini` | `src/Server/BloodLib/source/AlertSender.cpp` | CacheGate, LobbyDaemon, LobbyGate, PostOfficeDaemon, SmartCouponDaemon | - |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Shared functions: fix them in the shared file. If GameDaemon needs another form, use a per-exe copy in `lift_common_gd` or a `LIFT_EXE_` wrapper (A22, pattern 35). The 5 other exes must keep each MATCH. A MATCH to DIFF change needs an `allow-worse.txt` row with the counts.
6. An EXCLUDED function has a proof that no honest source fix exists in that exe. Read the proof first. If the same cause applies to GameDaemon, write the function under "Not done" with the proof reference. Do not edit `excluded.tsv`.
7. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/source_network.cpp`
- `src/Server/GameDaemon/source_network.h`
- `src/Server/BloodLib/source/Network.cpp`
- `src/Server/GameDaemon/packetbufferhandler.cpp`
- `src/Server/GameDaemon/packetbufferhandler.h`
- `src/Server/BloodLib/source/PacketBufferHandler.cpp`
- `src/Server/GameDaemon/winserviceconsole_h.cpp`
- `src/Server/GameDaemon/winserviceconsole_h.h`
- `src/Server/GameDaemon/source_alertsender.cpp`
- `src/Server/GameDaemon/source_alertsender.h`
- `src/Server/BloodLib/source/AlertSender.cpp`
- `src/Server/GameDaemon/propertysync.cpp`
- `src/Server/GameDaemon/propertysync.h`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-34.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
