# lift-gamedaemon-e10: Easy leaves (GameDaemon): duelbot_h

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

40 functions, about 280 pseudocode lines (about 2,240 tokens). Stems: `duelbot_h`.

Wave E (owner order 2026-11-27: the easiest work first). Each function in this card is a leaf: its body calls no other counted function that needs a lift. Thus a `LIFT_STUB` callee cannot keep it DIFF. Each function has at most 30 pseudocode lines. Ease key: 7.0 cost per function (rule in `Docs/Plan/gamedaemon-lift.md` section 3).

Lift only the functions in the table. The other functions of these stems are in later W cards. Those cards depend on this card.

| n | Exe | RVA | PDB name | Stem | Lines | Form |
| ---: | --- | --- | --- | --- | ---: | --- |
| 1 | GD | `0x97270` | `DuelBot::GetLastComboSkill` | duelbot_h | 7 | getter |
| 2 | GD | `0x97280` | `DuelBot::SetLastComboSkill` | duelbot_h | 7 | setter |
| 3 | GD | `0x97290` | `DuelBot::GetLastComboFireLimitTime` | duelbot_h | 7 | getter |
| 4 | GD | `0x972a0` | `DuelBot::SetLastComboFireLimitTime` | duelbot_h | 7 | setter |
| 5 | GD | `0x972b0` | `DuelBot::GetLastComboExecFirstLimitTime` | duelbot_h | 7 | getter |
| 6 | GD | `0x972c0` | `DuelBot::SetLastComboExecFirstLimitTime` | duelbot_h | 7 | setter |
| 7 | GD | `0x972d0` | `DuelBot::GetLastComboExecLastLimitTime` | duelbot_h | 7 | getter |
| 8 | GD | `0x972e0` | `DuelBot::SetLastComboExecLastLimitTime` | duelbot_h | 7 | setter |
| 9 | GD | `0x972f0` | `DuelBot::GetLastComboExecFirstResult` | duelbot_h | 7 | getter |
| 10 | GD | `0x97300` | `DuelBot::SetLastComboExecFirstResult` | duelbot_h | 7 | setter |
| 11 | GD | `0x97310` | `DuelBot::GetLastComboExecLastResult` | duelbot_h | 7 | getter |
| 12 | GD | `0x97320` | `DuelBot::SetLastComboExecLastResult` | duelbot_h | 7 | setter |
| 13 | GD | `0x97330` | `DuelBot::GetLastAttackLimitTime` | duelbot_h | 7 | leaf |
| 14 | GD | `0x97340` | `DuelBot::SetLastAttackLimitTime` | duelbot_h | 7 | leaf |
| 15 | GD | `0x97350` | `DuelBot::GetLastAttackedLimitTime` | duelbot_h | 7 | getter |
| 16 | GD | `0x97360` | `DuelBot::SetLastAttackedLimitTime` | duelbot_h | 7 | leaf |
| 17 | GD | `0x97370` | `DuelBot::GetAttackHitValueModify` | duelbot_h | 7 | getter |
| 18 | GD | `0x97380` | `DuelBot::GetAttackCriticalValueModify` | duelbot_h | 7 | getter |
| 19 | GD | `0x97390` | `DuelBot::GetDefendCriticalValueModify` | duelbot_h | 7 | getter |
| 20 | GD | `0x973a0` | `DuelBot::GetDefendDodgeValueModify` | duelbot_h | 7 | getter |
| 21 | GD | `0x973b0` | `DuelBot::GetDefendParryValueModify` | duelbot_h | 7 | getter |
| 22 | GD | `0x973c0` | `DuelBot::GetDefendPhysicalValueModify` | duelbot_h | 7 | getter |
| 23 | GD | `0x973d0` | `DuelBot::GetDefendForceValueModify` | duelbot_h | 7 | getter |
| 24 | GD | `0x973e0` | `DuelBot::GetAttackStiffDurationValueModify` | duelbot_h | 7 | getter |
| 25 | GD | `0x973f0` | `DuelBot::GetDefendStiffDurationValueModify` | duelbot_h | 7 | getter |
| 26 | GD | `0x97400` | `DuelBot::GetCastDurationValueModify` | duelbot_h | 7 | getter |
| 27 | GD | `0x97410` | `DuelBot::GetAttackCriticalDamageModify` | duelbot_h | 7 | getter |
| 28 | GD | `0x97420` | `DuelBot::GetDefendCriticalDamageModify` | duelbot_h | 7 | getter |
| 29 | GD | `0x97430` | `DuelBot::GetAttackPierceModify` | duelbot_h | 7 | getter |
| 30 | GD | `0x97440` | `DuelBot::GetAttackParryPierceModify` | duelbot_h | 7 | getter |
| 31 | GD | `0x97450` | `DuelBot::GetDefendParryReduceModify` | duelbot_h | 7 | getter |
| 32 | GD | `0x97460` | `DuelBot::GetAttackPerfectParryDamageModify` | duelbot_h | 7 | getter |
| 33 | GD | `0x97470` | `DuelBot::GetDefendPerfectParryReduceModify` | duelbot_h | 7 | getter |
| 34 | GD | `0x97480` | `DuelBot::GetAttackCounterDamageModify` | duelbot_h | 7 | getter |
| 35 | GD | `0x97490` | `DuelBot::GetDefendCounterReduceModify` | duelbot_h | 7 | getter |
| 36 | GD | `0x974a0` | `DuelBot::GetHealPowerModify` | duelbot_h | 7 | getter |
| 37 | GD | `0x974b0` | `DuelBot::GetAOEDefendPowerModify` | duelbot_h | 7 | getter |
| 38 | GD | `0x974c0` | `DuelBot::GetAbnormalAttackPowerModify` | duelbot_h | 7 | getter |
| 39 | GD | `0x974d0` | `DuelBot::GetAbnormalDefendPowerModify` | duelbot_h | 7 | getter |
| 40 | GD | `0x974e0` | `DuelBot::GetHatePowerModify` | duelbot_h | 7 | getter |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/duelbot_h.cpp`
- `src/Server/GameDaemon/duelbot_h.h`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-e10.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
