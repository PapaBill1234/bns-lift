# lift-gamedaemon-38: Packet and Shared gaps: fragmentpacket_cpp, gamepackethandlerlist, chattinglog, fragmentpacket_h

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
| Depends on | `lift-gamedaemon-3`, `lift-gamedaemon-12` |
| Pattern | `src/Server/Packet/FragmentPacket.cpp` |
| Plan | `Docs/Plan/gamedaemon-lift.md` sections 1, 3, 5 |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Grep `Docs/Parity/lessons.md` for A2 (block order), A6 (per-exe path literals), A12 (PDB member types), A18 (destructors), A21 (PDB facts) and A22 (per-exe source form). Do not read it in full.
- Pattern: `src/Server/Packet/FragmentPacket.cpp`. Read it one time. Use its form for the functions of this card.

## Scope

15 functions, about 1,330 pseudocode lines (about 10,640 tokens). Stems: `fragmentpacket_cpp`, `gamepackethandlerlist`, `chattinglog`, `fragmentpacket_h`.

| n | Exe | RVA | PDB name | Stem | Lines |
| ---: | --- | --- | --- | --- | ---: |
| 1 | GD | `0xdf700` | `SimplePacketSplitter::AddBuffer` | fragmentpacket_cpp | 47 |
| 2 | GD | `0xdf7a0` | `FragmentPacketSplitter::AddBuffer` | fragmentpacket_cpp | 81 |
| 3 | GD | `0xdf8c0` | `FragmentPacketSplitter::Finalize` | fragmentpacket_cpp | 31 |
| 4 | GD | `0xdfaf0` | `FragmentPacketConcatenater::Add` | fragmentpacket_cpp | 138 |
| 5 | GD | `0xdfd90` | `FragmentPacketConcatenater::Clone` | fragmentpacket_cpp | 43 |
| 6 | GD | `0x5aed40` | `EffectCacheUpdate::~EffectCacheUpdate` | fragmentpacket_cpp | 7 |
| 7 | GD | `0xdfe50` | `HandleGame_QQC2CReq` | gamepackethandlerlist | 8 |
| 8 | GD | `0xdfe60` | `GameTestBotQuery` | gamepackethandlerlist | 714 |
| 9 | GD | `0x291490` | `ChattingLog::MessageByItemDistrict` | chattinglog | 57 |
| 10 | GD | `0x291630` | `ChattingLog::MessageByItemWorld` | chattinglog | 57 |
| 11 | GD | `0x5d48a0` | `ChattingLog::Normal` | chattinglog | 55 |
| 12 | GD | `0x5d4a30` | `ChattingLog::Whisper` | chattinglog | 58 |
| 13 | GD | `0xb2c0` | `FragmentPacket::StartRepeat` | fragmentpacket_h | 12 |
| 14 | GD | `0x10d40` | `FragmentPacket::FreeBody` | fragmentpacket_h | 10 |
| 15 | GD | `0x271c0` | `FragmentPacket::StartInnerPacket` | fragmentpacket_h | 12 |

### Shared functions

These functions are in shared source. They are not MATCH in each lifted exe that has them.

| PDB name | Shared file | Other exes | Note |
| --- | --- | --- | --- |
| `FragmentPacketSplitter::AddBuffer` | `src/Server/Packet/FragmentPacket.cpp` | LobbyDaemon, LobbyGate, PostOfficeDaemon | - |
| `FragmentPacketSplitter::Finalize` | `src/Server/Packet/FragmentPacket.cpp` | LobbyDaemon, LobbyGate, PostOfficeDaemon | - |
| `FragmentPacketConcatenater::Add` | `src/Server/Packet/FragmentPacket.cpp` | LobbyDaemon, LobbyGate, PostOfficeDaemon | - |
| `FragmentPacketConcatenater::Clone` | `src/Server/Packet/FragmentPacket.cpp` | LobbyDaemon, LobbyGate, PostOfficeDaemon | - |
| `FragmentPacket::StartRepeat` | `src/Server/Packet/FragmentPacket.cpp` | LobbyGate | - |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Shared functions: fix them in the shared file. If GameDaemon needs another form, use a per-exe copy in `lift_common_gd` or a `LIFT_EXE_` wrapper (A22, pattern 35). The 5 other exes must keep each MATCH. A MATCH to DIFF change needs an `allow-worse.txt` row with the counts.
6. An EXCLUDED function has a proof that no honest source fix exists in that exe. Read the proof first. If the same cause applies to GameDaemon, write the function under "Not done" with the proof reference. Do not edit `excluded.tsv`.
7. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/fragmentpacket_cpp.cpp`
- `src/Server/GameDaemon/fragmentpacket_cpp.h`
- `src/Server/Packet/FragmentPacket.cpp`
- `src/Server/GameDaemon/gamepackethandlerlist.cpp`
- `src/Server/GameDaemon/gamepackethandlerlist.h`
- `src/Server/GameDaemon/chattinglog.cpp`
- `src/Server/GameDaemon/chattinglog.h`
- `src/Server/GameDaemon/fragmentpacket_h.cpp`
- `src/Server/GameDaemon/fragmentpacket_h.h`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-38.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
