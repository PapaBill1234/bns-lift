# lift-gamedaemon-e23: Easy leaves (GameDaemon): publisherlibsfunctions

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

40 functions, about 448 pseudocode lines (about 3,584 tokens). Stems: `publisherlibsfunctions`.

Wave E (owner order 2026-11-27: the easiest work first). Each function in this card is a leaf: its body calls no other counted function that needs a lift. Thus a `LIFT_STUB` callee cannot keep it DIFF. Each function has at most 30 pseudocode lines. Ease key: 11.2 cost per function (rule in `Docs/Plan/gamedaemon-lift.md` section 3).

Lift only the functions in the table. The other functions of these stems are in later W cards. Those cards depend on this card.

| n | Exe | RVA | PDB name | Stem | Lines | Form |
| ---: | --- | --- | --- | --- | ---: | --- |
| 1 | GD | `0x1a4350` | `packetBufferAlloc` | publisherlibsfunctions | 8 | leaf |
| 2 | GD | `0x1a4360` | `getPacketCommand` | publisherlibsfunctions | 7 | leaf |
| 3 | GD | `0x1a4540` | `deletePacketComposer` | publisherlibsfunctions | 13 | leaf |
| 4 | GD | `0x1a4570` | `deletePacketDecomposer` | publisherlibsfunctions | 13 | leaf |
| 5 | GD | `0x1a45a0` | `deletePacket` | publisherlibsfunctions | 15 | leaf |
| 6 | GD | `0x1a46e0` | `composeV` | publisherlibsfunctions | 27 | leaf |
| 7 | GD | `0x1a4800` | `startRepeat` | publisherlibsfunctions | 8 | leaf |
| 8 | GD | `0x1a4820` | `endRepeat` | publisherlibsfunctions | 8 | leaf |
| 9 | GD | `0x1a4840` | `incRepeat` | publisherlibsfunctions | 26 | leaf |
| 10 | GD | `0x1a4890` | `openRepeat` | publisherlibsfunctions | 7 | leaf |
| 11 | GD | `0x1a48b0` | `closeRepeat` | publisherlibsfunctions | 7 | getter |
| 12 | GD | `0x1a48d0` | `decRepeat` | publisherlibsfunctions | 11 | leaf |
| 13 | GD | `0x1a4900` | `freeSize` | publisherlibsfunctions | 13 | leaf |
| 14 | GD | `0x1a4920` | `allocate` | publisherlibsfunctions | 8 | getter |
| 15 | GD | `0x1a4930` | `copyPacket` | publisherlibsfunctions | 8 | leaf |
| 16 | GD | `0x1a4b50` | `fpCreatePacket` | publisherlibsfunctions | 19 | leaf |
| 17 | GD | `0x1a4bd0` | `fpDeletePacket` | publisherlibsfunctions | 15 | leaf |
| 18 | GD | `0x1a4c10` | `fpCompose` | publisherlibsfunctions | 13 | leaf |
| 19 | GD | `0x1a4c60` | `fpComposeV` | publisherlibsfunctions | 10 | leaf |
| 20 | GD | `0x1a4cb0` | `fpStartRepeat` | publisherlibsfunctions | 13 | leaf |
| 21 | GD | `0x1a4d00` | `fpEndRepeat` | publisherlibsfunctions | 8 | leaf |
| 22 | GD | `0x1a4d20` | `fpIncRepeat` | publisherlibsfunctions | 8 | leaf |
| 23 | GD | `0x1a4df0` | `fpInitDecomposer` | publisherlibsfunctions | 12 | leaf |
| 24 | GD | `0x1a4e20` | `fpOpenRepeat` | publisherlibsfunctions | 11 | leaf |
| 25 | GD | `0x1a4e50` | `fpCloseRepeat` | publisherlibsfunctions | 7 | leaf |
| 26 | GD | `0x1a4e70` | `fpDecRepeat` | publisherlibsfunctions | 11 | leaf |
| 27 | GD | `0x1a4ed0` | `fpClearConcatenater` | publisherlibsfunctions | 8 | leaf |
| 28 | GD | `0x1a4ee0` | `fpDeleteConcatenater` | publisherlibsfunctions | 17 | leaf |
| 29 | GD | `0x1a4f20` | `fpFinalize` | publisherlibsfunctions | 12 | leaf |
| 30 | GD | `0x1a4f50` | `fpGetPacket` | publisherlibsfunctions | 8 | leaf |
| 31 | GD | `0x1a4f60` | `fpClear` | publisherlibsfunctions | 11 | leaf |
| 32 | GD | `0x1a4fb0` | `fpFreeSize` | publisherlibsfunctions | 13 | leaf |
| 33 | GD | `0x1a4fd0` | `fpAllocate` | publisherlibsfunctions | 7 | leaf |
| 34 | GD | `0x1a4fe0` | `getInternalAddress` | publisherlibsfunctions | 7 | getter |
| 35 | GD | `0x1a4ff0` | `getPublicAddress` | publisherlibsfunctions | 7 | getter |
| 36 | GD | `0x1a5000` | `logBufferAlloc` | publisherlibsfunctions | 8 | leaf |
| 37 | GD | `0x1a5010` | `errorWrite` | publisherlibsfunctions | 11 | leaf |
| 38 | GD | `0x1a5040` | `noticeWrite` | publisherlibsfunctions | 11 | leaf |
| 39 | GD | `0x1a5080` | `debugWrite` | publisherlibsfunctions | 11 | leaf |
| 40 | GD | `0x1a50c0` | `traceWrite` | publisherlibsfunctions | 11 | leaf |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/publisherlibsfunctions.cpp`
- `src/Server/GameDaemon/publisherlibsfunctions.h`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-e23.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
