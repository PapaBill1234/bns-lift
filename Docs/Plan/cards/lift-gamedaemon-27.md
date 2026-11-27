# lift-gamedaemon-27: Packet game log: gamelog_3 part 5/5

| Item | Value |
| --- | --- |
| Exe | GD |
| Source build | GameDaemon 2019 + PDB (VS2010 SP1) |
| Exe file | `<work-root>/ida/lift/GameDaemon/GameDaemon.exe` |
| PDB | `<work-root>/ida/lift/GameDaemon/GameDaemon.pdb` |
| Pseudocode | `~/.cache/bns-lift/hr/GameDaemon/<stem>.c` |
| Pseudocode index | `~/.cache/bns-lift/hr/GameDaemon/index.tsv` (stem, rva, name, first, last, status, source file, part) |
| Wave | W1 |
| Model | sonnet:high |
| Depends on | `lift-gamedaemon-12`, `lift-gamedaemon-13`, `lift-gamedaemon-26` |
| Pattern | `src/Server/GameDaemon/gamelog_1.cpp` |
| Plan | `Docs/Plan/gamedaemon-lift.md` sections 1, 3, 5 |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Grep `Docs/Parity/lessons.md` for A2 (block order), A6 (per-exe path literals), A12 (PDB member types), A18 (destructors), A21 (PDB facts) and A22 (per-exe source form). Do not read it in full.
- Pattern: `src/Server/GameDaemon/gamelog_1.cpp`. Read it one time. Use its form for the functions of this card.
  The pattern is the output of `lift-gamedaemon-13`. Use the same form for each function: the functions in this group have one layout.

## Scope

14 functions, about 1,482 pseudocode lines (about 11,856 tokens). Stems: `gamelog_3`.

This card is part 5/5 of stem `gamelog_3`. The other parts are in other cards of this wave. They run one after the other (column "Depends on"). Edit only the functions in this table.

| n | Exe | RVA | PDB name | Stem | Lines |
| ---: | --- | --- | --- | --- | ---: |
| 1 | GD | `0x4398f0` | `GameLog::RevealItem` | gamelog_3 | 110 |
| 2 | GD | `0x439cf0` | `GameLog::ConsumeGemByReveal` | gamelog_3 | 105 |
| 3 | GD | `0x43a0c0` | `GameLog::ConsumeItemByReveal` | gamelog_3 | 103 |
| 4 | GD | `0x43a480` | `GameLog::DecomposeItem` | gamelog_3 | 116 |
| 5 | GD | `0x43a910` | `GameLog::GetItemByDecomposition` | gamelog_3 | 102 |
| 6 | GD | `0x43acc0` | `GameLog::AttachGemToWeapon` | gamelog_3 | 108 |
| 7 | GD | `0x43b0c0` | `GameLog::DetachGemFromWeapon` | gamelog_3 | 110 |
| 8 | GD | `0x43b4d0` | `GameLog::ExpandWarehouse` | gamelog_3 | 104 |
| 9 | GD | `0x43b890` | `GameLog::RepairItem` | gamelog_3 | 106 |
| 10 | GD | `0x43bc60` | `GameLog::RepairItemSpendMoney` | gamelog_3 | 103 |
| 11 | GD | `0x43c040` | `GameLog::ExpandGemSlot` | gamelog_3 | 108 |
| 12 | GD | `0x43c440` | `GameLog::ConsumeItemByRepair` | gamelog_3 | 103 |
| 13 | GD | `0x43c800` | `GameLog::ConsumeItemByExpSlot` | gamelog_3 | 103 |
| 14 | GD | `0x43cbc0` | `GameLog::DischargeSeal` | gamelog_3 | 101 |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/gamelog_3.cpp`
- `src/Server/GameDaemon/gamelog_3.h`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-27.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
