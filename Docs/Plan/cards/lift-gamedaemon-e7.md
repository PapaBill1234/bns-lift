# lift-gamedaemon-e7: Easy leaves (GameDaemon): challengepartyattractionstate_h, duelbotchallengeattractionstate_h, pcattractionstate_h, warfieldattractionstate_h

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
| Pattern | none |
| Plan | `Docs/Plan/gamedaemon-lift.md` sections 1, 3, 5 |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Grep `Docs/Parity/lessons.md` for A2 (block order), A6 (per-exe path literals), A12 (PDB member types), A18 (destructors), A21 (PDB facts) and A22 (per-exe source form). Do not read it in full.
- Pattern: none. No lifted file has the same role.
- Dead-strip: `wmain` and most callers are still `LIFT_STUB` bodies. `/OPT:REF` removes a lifted function that has no live caller, and funcdiff then cannot pair it. For each function in scope with no live caller, add `#pragma comment(linker, "/INCLUDE:<public name>")` in its `.cpp` (public names: `llvm-pdbutil dump -publics`; grep `/INCLUDE` in `Docs/Parity/lessons.md`). Do not add a pragma for a function that a lifted caller keeps.

## Scope

15 functions, about 105 pseudocode lines (about 840 tokens). Stems: `challengepartyattractionstate_h`, `duelbotchallengeattractionstate_h`, `pcattractionstate_h`, `warfieldattractionstate_h`.

Wave E (owner order 2026-11-27: the easiest work first). Each function in this card is a leaf: its body calls no other counted function that needs a lift. Thus a `LIFT_STUB` callee cannot keep it DIFF. Each function has at most 30 pseudocode lines. Ease key: 7.0 cost per function (rule in `Docs/Plan/gamedaemon-lift.md` section 3).

Lift only the functions in the table. The other functions of these stems are in later W cards. Those cards depend on this card.

| n | Exe | RVA | PDB name | Stem | Lines | Form |
| ---: | --- | --- | --- | --- | ---: | --- |
| 1 | GD | `0x35f20` | `AirDashAction::getPriority` | challengepartyattractionstate_h | 7 | getter |
| 2 | GD | `0x35f30` | `ChallengePartyAttractionState::GetTypeName` | challengepartyattractionstate_h | 7 | getter |
| 3 | GD | `0x35f40` | `ChallengePartyAttractionState::SetAttractionOption` | challengepartyattractionstate_h | 7 | setter |
| 4 | GD | `0x97740` | `DuelBotChallengeAttractionState::GetTypeName` | duelbotchallengeattractionstate_h | 7 | getter |
| 5 | GD | `0x180ba0` | `NpcContribution::TotalDamage` | pcattractionstate_h | 7 | getter |
| 6 | GD | `0x180bb0` | `PcPublicRaidState::SetAddScoreCoolTime` | pcattractionstate_h | 7 | setter |
| 7 | GD | `0x180bc0` | `PcPublicRaidState::IsEventAttendee` | pcattractionstate_h | 7 | getter |
| 8 | GD | `0x180bd0` | `PcPublicRaidState::SetEventAttendee` | pcattractionstate_h | 7 | setter |
| 9 | GD | `0x180be0` | `PcPublicRaidState::ResetEventAttendee` | pcattractionstate_h | 7 | setter |
| 10 | GD | `0x180bf0` | `PcPublicRaidState::GetAddScoreCount` | pcattractionstate_h | 7 | getter |
| 11 | GD | `0x180c00` | `PcPublicRaidState::IncrementAddScoreCount` | pcattractionstate_h | 7 | leaf |
| 12 | GD | `0x4535a0` | `DuelBotActionQueue::GetMovement` | pcattractionstate_h | 7 | getter |
| 13 | GD | `0x6fd280` | `DrDataTableImpl::Setup` | pcattractionstate_h | 7 | setter |
| 14 | GD | `0x1ee750` | `WarFieldAttractionState::GetTypeName` | warfieldattractionstate_h | 7 | getter |
| 15 | GD | `0x6f86d0` | `AcquiredSkill1::Version` | warfieldattractionstate_h | 7 | getter |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/challengepartyattractionstate_h.cpp`
- `src/Server/GameDaemon/challengepartyattractionstate_h.h`
- `src/Server/GameDaemon/duelbotchallengeattractionstate_h.cpp`
- `src/Server/GameDaemon/duelbotchallengeattractionstate_h.h`
- `src/Server/GameDaemon/pcattractionstate_h.cpp`
- `src/Server/GameDaemon/pcattractionstate_h.h`
- `src/Server/GameDaemon/warfieldattractionstate_h.cpp`
- `src/Server/GameDaemon/warfieldattractionstate_h.h`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-e7.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
