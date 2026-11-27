# lift-gamedaemon-37: Shared gaps and Common library and others: constfiltername, twofish2, fragmentpacket_h, fragmentpacket_cpp

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
| Depends on | `lift-gamedaemon-e1`, `lift-gamedaemon-e45`, `lift-gamedaemon-3` |
| Pattern | `src/Server/Packet/FragmentPacket.cpp` |
| Plan | `Docs/Plan/gamedaemon-lift.md` sections 1, 3, 5 |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Grep `Docs/Parity/lessons.md` for A2 (block order), A6 (per-exe path literals), A12 (PDB member types), A18 (destructors), A21 (PDB facts) and A22 (per-exe source form). Do not read it in full.
- Pattern: `src/Server/Packet/FragmentPacket.cpp`. Read it one time. Use its form for the functions of this card.

## Scope

14 functions, about 1,847 pseudocode lines (about 14,776 tokens). Stems: `constfiltername`, `twofish2`, `fragmentpacket_h`, `fragmentpacket_cpp`.

The easy functions of this stem are in `lift-gamedaemon-e45`, `lift-gamedaemon-e1`. Do not change them unless a fix needs it.

| n | Exe | RVA | PDB name | Stem | Lines |
| ---: | --- | --- | --- | --- | ---: |
| 1 | GD | `0x6eaf00` | `ConstFilterName` | constfiltername | 203 |
| 2 | GD | `0x39d410` | `ParseHexDword` | twofish2 | 52 |
| 3 | GD | `0x39d4e0` | `RS_MDS_Encode` | twofish2 | 49 |
| 4 | GD | `0x39d680` | `BuildMDS` | twofish2 | 181 |
| 5 | GD | `0x39db80` | `ReverseRoundSubkeys` | twofish2 | 31 |
| 6 | GD | `0x39dbd0` | `Xor256` | twofish2 | 73 |
| 7 | GD | `0x39dee0` | `reKey` | twofish2 | 520 |
| 8 | GD | `0x39ead0` | `blockEncrypt` | twofish2 | 386 |
| 9 | GD | `0x271c0` | `FragmentPacket::StartInnerPacket` | fragmentpacket_h | 12 |
| 10 | GD | `0xdf700` | `SimplePacketSplitter::AddBuffer` | fragmentpacket_cpp | 47 |
| 11 | GD | `0xdf7a0` | `FragmentPacketSplitter::AddBuffer` | fragmentpacket_cpp | 81 |
| 12 | GD | `0xdf8c0` | `FragmentPacketSplitter::Finalize` | fragmentpacket_cpp | 31 |
| 13 | GD | `0xdfaf0` | `FragmentPacketConcatenater::Add` | fragmentpacket_cpp | 138 |
| 14 | GD | `0xdfd90` | `FragmentPacketConcatenater::Clone` | fragmentpacket_cpp | 43 |

### Shared functions

These functions are in shared source. They are not MATCH in each lifted exe that has them.

| PDB name | Shared file | Other exes | Note |
| --- | --- | --- | --- |
| `ConstFilterName` | `src/External/BannedWordFilter/ConstFilterName.cpp` | LobbyDaemon | - |
| `FragmentPacketSplitter::AddBuffer` | `src/Server/Packet/FragmentPacket.cpp` | LobbyDaemon, LobbyGate, PostOfficeDaemon | - |
| `FragmentPacketSplitter::Finalize` | `src/Server/Packet/FragmentPacket.cpp` | LobbyDaemon, LobbyGate, PostOfficeDaemon | - |
| `FragmentPacketConcatenater::Add` | `src/Server/Packet/FragmentPacket.cpp` | LobbyDaemon, LobbyGate, PostOfficeDaemon | - |
| `FragmentPacketConcatenater::Clone` | `src/Server/Packet/FragmentPacket.cpp` | LobbyDaemon, LobbyGate, PostOfficeDaemon | - |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Shared functions: fix them in the shared file. If GameDaemon needs another form, use a per-exe copy in `lift_common_gd` or a `LIFT_EXE_` wrapper (A22, pattern 35). The 5 other exes must keep each MATCH. A MATCH to DIFF change needs an `allow-worse.txt` row with the counts.
6. An EXCLUDED function has a proof that no honest source fix exists in that exe. Read the proof first. If the same cause applies to GameDaemon, write the function under "Not done" with the proof reference. Do not edit `excluded.tsv`.
7. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/External/BannedWordFilter/ConstFilterName.cpp`
- `src/Server/GameDaemon/twofish2.cpp`
- `src/Server/GameDaemon/twofish2.h`
- `src/Server/GameDaemon/fragmentpacket_h.cpp`
- `src/Server/GameDaemon/fragmentpacket_h.h`
- `src/Server/GameDaemon/fragmentpacket_cpp.cpp`
- `src/Server/GameDaemon/fragmentpacket_cpp.h`
- `src/Server/Packet/FragmentPacket.cpp`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-37.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
