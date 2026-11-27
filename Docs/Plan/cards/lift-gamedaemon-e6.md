# lift-gamedaemon-e6: Easy leaves (GameDaemon): worldserializedobject_h, npc_h, skilltrainingroom_h, zoneserializedobject, ...

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

## Scope

34 functions, about 238 pseudocode lines (about 1,904 tokens). Stems: `worldserializedobject_h`, `npc_h`, `skilltrainingroom_h`, `zoneserializedobject`, `user_h`.

Wave E (owner order 2026-11-27: the easiest work first). Each function in this card is a leaf: its body calls no other counted function that needs a lift. Thus a `LIFT_STUB` callee cannot keep it DIFF. Each function has at most 30 pseudocode lines. Ease key: 7.0 cost per function (rule in `Docs/Plan/gamedaemon-lift.md` section 3).

Lift only the functions in the table. The other functions of these stems are in later W cards. Those cards depend on this card.

| n | Exe | RVA | PDB name | Stem | Lines | Form |
| ---: | --- | --- | --- | --- | ---: | --- |
| 1 | GD | `0x1d070` | `GameObject::childRoleAllocator` | worldserializedobject_h | 7 | getter |
| 2 | GD | `0x27380` | `Npc::GetAttackHitValueModify` | npc_h | 7 | getter |
| 3 | GD | `0x27390` | `Npc::GetAttackCriticalValueModify` | npc_h | 7 | getter |
| 4 | GD | `0x273a0` | `Npc::GetDefendCriticalValueModify` | npc_h | 7 | getter |
| 5 | GD | `0x273b0` | `Npc::GetDefendDodgeValueModify` | npc_h | 7 | getter |
| 6 | GD | `0x273c0` | `Npc::GetDefendParryValueModify` | npc_h | 7 | getter |
| 7 | GD | `0x273d0` | `Npc::GetDefendPhysicalValueModify` | npc_h | 7 | getter |
| 8 | GD | `0x273e0` | `Npc::GetDefendForceValueModify` | npc_h | 7 | getter |
| 9 | GD | `0x273f0` | `Npc::GetAttackStiffDurationValueModify` | npc_h | 7 | getter |
| 10 | GD | `0x27400` | `Npc::GetDefendStiffDurationValueModify` | npc_h | 7 | getter |
| 11 | GD | `0x27410` | `Npc::GetCastDurationValueModify` | npc_h | 7 | getter |
| 12 | GD | `0x27420` | `Npc::GetAttackCriticalDamageModify` | npc_h | 7 | getter |
| 13 | GD | `0x27430` | `Npc::GetDefendCriticalDamageModify` | npc_h | 7 | getter |
| 14 | GD | `0x27440` | `Npc::GetAttackPierceModify` | npc_h | 7 | getter |
| 15 | GD | `0x27450` | `Npc::GetAttackParryPierceModify` | npc_h | 7 | getter |
| 16 | GD | `0x27460` | `Npc::GetDefendParryReduceModify` | npc_h | 7 | getter |
| 17 | GD | `0x27470` | `Npc::GetAttackPerfectParryDamageModify` | npc_h | 7 | getter |
| 18 | GD | `0x27480` | `Npc::GetDefendPerfectParryReduceModify` | npc_h | 7 | getter |
| 19 | GD | `0x27490` | `Npc::GetAttackCounterDamageModify` | npc_h | 7 | getter |
| 20 | GD | `0x274a0` | `Npc::GetDefendCounterReduceModify` | npc_h | 7 | getter |
| 21 | GD | `0x274b0` | `Npc::GetHealPowerModify` | npc_h | 7 | getter |
| 22 | GD | `0x274c0` | `Npc::GetAOEDefendPowerModify` | npc_h | 7 | getter |
| 23 | GD | `0x274d0` | `Npc::GetAbnormalAttackPowerModify` | npc_h | 7 | getter |
| 24 | GD | `0x274e0` | `Npc::GetAbnormalDefendPowerModify` | npc_h | 7 | getter |
| 25 | GD | `0x274f0` | `Npc::GetHatePowerModify` | npc_h | 7 | getter |
| 26 | GD | `0x27500` | `Npc::GetAttackAttributeModify` | npc_h | 7 | getter |
| 27 | GD | `0x27510` | `Npc::GetRAttackAoePierceModify` | npc_h | 7 | getter |
| 28 | GD | `0x27520` | `Npc::GetRAttackAbnormalHitModify` | npc_h | 7 | getter |
| 29 | GD | `0x27530` | `Npc::GetRDefendAbnormalDodgeModify` | npc_h | 7 | getter |
| 30 | GD | `0x27540` | `Npc::GetRSupportPowerModify` | npc_h | 7 | getter |
| 31 | GD | `0x27550` | `Npc::GetRHypermovePowerModify` | npc_h | 7 | getter |
| 32 | GD | `0x180e40` | `SkillTrainingRoom::GetTypeName` | skilltrainingroom_h | 7 | getter |
| 33 | GD | `0x25fbf0` | `ZoneSerializedObject::TimerExpired` | zoneserializedobject | 7 | leaf |
| 34 | GD | `0x3502e0` | `User::GetId` | user_h | 7 | getter |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/worldserializedobject_h.cpp`
- `src/Server/GameDaemon/worldserializedobject_h.h`
- `src/Server/GameDaemon/npc_h.cpp`
- `src/Server/GameDaemon/npc_h.h`
- `src/Server/GameDaemon/skilltrainingroom_h.cpp`
- `src/Server/GameDaemon/skilltrainingroom_h.h`
- `src/Server/GameDaemon/zoneserializedobject.cpp`
- `src/Server/GameDaemon/zoneserializedobject.h`
- `src/Server/GameDaemon/user_h.cpp`
- `src/Server/GameDaemon/user_h.h`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-e6.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
