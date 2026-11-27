# lift-gamedaemon-3: BloodLib and Shared gaps: daemon, source_packet, source_packetutil, source_refcntobject

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
| Depends on | `lift-gamedaemon-1`, `lift-gamedaemon-2` |
| Pattern | `src/Server/BloodLib/source/PacketUtil.cpp` |
| Plan | `Docs/Plan/gamedaemon-lift.md` sections 1, 3, 5 |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Grep `Docs/Parity/lessons.md` for A2 (block order), A6 (per-exe path literals), A12 (PDB member types), A18 (destructors), A21 (PDB facts) and A22 (per-exe source form). Do not read it in full.
- Pattern: `src/Server/BloodLib/source/PacketUtil.cpp`. Read it one time. Use its form for the functions of this card.

## Scope

22 functions, about 832 pseudocode lines (about 6,656 tokens). Stems: `daemon`, `source_packet`, `source_packetutil`, `source_refcntobject`.

| n | Exe | RVA | PDB name | Stem | Lines |
| ---: | --- | --- | --- | --- | ---: |
| 1 | GD | `0x68cf50` | `Daemon::AddDelayedRelease` | daemon | 23 |
| 2 | GD | `0x68d9e0` | `Daemon::SetPublicAddressWithSetting` | daemon | 11 |
| 3 | GD | `0x68dba0` | `parseCIDRAddress` | daemon | 25 |
| 4 | GD | `0x68dcc0` | `Daemon::setInternalAddressRange` | daemon | 28 |
| 5 | GD | `0x68dd50` | `Daemon::setPublicAddressRange` | daemon | 28 |
| 6 | GD | `0x68dde0` | `Daemon::allocateZstdDictionary` | daemon | 97 |
| 7 | GD | `0x6910a0` | `Packet::Reserve` | source_packet | 51 |
| 8 | GD | `0x6912c0` | `Packet::GrowAdd` | source_packet | 28 |
| 9 | GD | `0x6915e0` | `Packet::Restore` | source_packet | 23 |
| 10 | GD | `0x691ef0` | `Packet::DecomposeV` | source_packet | 59 |
| 11 | GD | `0x692220` | `Packet::setRecvBuffer` | source_packet | 17 |
| 12 | GD | `0x692840` | `RepeatPacketComposer::PushInnerPacket` | source_packetutil | 33 |
| 13 | GD | `0x692960` | `RepeatPacketComposer::PopInnerPacket` | source_packetutil | 39 |
| 14 | GD | `0x693170` | `PacketConcatenateBuffer::Decompose` | source_packetutil | 32 |
| 15 | GD | `0x693240` | `PacketConcatenateBuffer::DecomposeV` | source_packetutil | 27 |
| 16 | GD | `0x6934a0` | `RelationalRefCntObject::initRole` | source_refcntobject | 64 |
| 17 | GD | `0x6935c0` | `RelationalRefCntObject::clearRole` | source_refcntobject | 24 |
| 18 | GD | `0x693640` | `RelationalRefCntObject::AddChild` | source_refcntobject | 53 |
| 19 | GD | `0x693800` | `RelationalRefCntObject::removeChild` | source_refcntobject | 49 |
| 20 | GD | `0x6939a0` | `RelationalRefCntObject::removeParent` | source_refcntobject | 40 |
| 21 | GD | `0x693a60` | `RelationalRefCntObject::remove_child` | source_refcntobject | 26 |
| 22 | GD | `0x693ae0` | `RelationalRefCntObject::deallocate_object` | source_refcntobject | 55 |

### Shared functions

These functions are in shared source. They are not MATCH in each lifted exe that has them.

| PDB name | Shared file | Other exes | Note |
| --- | --- | --- | --- |
| `PacketConcatenateBuffer::Decompose` | `src/Server/BloodLib/source/PacketUtil.cpp` | LobbyDaemon, LobbyGate, PostOfficeDaemon | - |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Shared functions: fix them in the shared file. If GameDaemon needs another form, use a per-exe copy in `lift_common_gd` or a `LIFT_EXE_` wrapper (A22, pattern 35). The 5 other exes must keep each MATCH. A MATCH to DIFF change needs an `allow-worse.txt` row with the counts.
6. An EXCLUDED function has a proof that no honest source fix exists in that exe. Read the proof first. If the same cause applies to GameDaemon, write the function under "Not done" with the proof reference. Do not edit `excluded.tsv`.
7. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/daemon.cpp`
- `src/Server/GameDaemon/daemon.h`
- `src/Server/GameDaemon/source_packet.cpp`
- `src/Server/GameDaemon/source_packet.h`
- `src/Server/GameDaemon/source_packetutil.cpp`
- `src/Server/GameDaemon/source_packetutil.h`
- `src/Server/BloodLib/source/PacketUtil.cpp`
- `src/Server/GameDaemon/source_refcntobject.cpp`
- `src/Server/GameDaemon/source_refcntobject.h`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-3.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
