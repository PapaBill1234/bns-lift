# lift-gamedaemon-e24: Easy leaves (GameDaemon): tlog, gamedebugcommand_cpp_2, gamebuilderpackethandler, gamedebugcommand_cpp_1

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

40 functions, about 449 pseudocode lines (about 3,592 tokens). Stems: `tlog`, `gamedebugcommand_cpp_2`, `gamebuilderpackethandler`, `gamedebugcommand_cpp_1`.

Wave E (owner order 2026-11-27: the easiest work first). Each function in this card is a leaf: its body calls no other counted function that needs a lift. Thus a `LIFT_STUB` callee cannot keep it DIFF. Each function has at most 30 pseudocode lines. Ease key: 11.2 cost per function (rule in `Docs/Plan/gamedaemon-lift.md` section 3).

Lift only the functions in the table. The other functions of these stems are in later W cards. Those cards depend on this card.

| n | Exe | RVA | PDB name | Stem | Lines | Form |
| ---: | --- | --- | --- | --- | ---: | --- |
| 1 | GD | `0x1397f0` | `TencentLog::Offline` | tlog | 8 | leaf |
| 2 | GD | `0x139d10` | `TencentLog::PartyAuctionFail` | tlog | 27 | leaf |
| 3 | GD | `0x191ac0` | `TencentLog::SendMail` | tlog | 12 | leaf |
| 4 | GD | `0x191cb0` | `TencentLog::RcvMail` | tlog | 8 | leaf |
| 5 | GD | `0x1ee920` | `TencentLog::JoinTeam` | tlog | 8 | leaf |
| 6 | GD | `0x3d7930` | `TencentLog::P2P` | tlog | 12 | leaf |
| 7 | GD | `0x3d7c20` | `TencentLog::KillMon` | tlog | 8 | leaf |
| 8 | GD | `0x3d7e70` | `TencentLog::MonsterKilled` | tlog | 8 | leaf |
| 9 | GD | `0x3d7fb0` | `TencentLog::PickupItem` | tlog | 12 | leaf |
| 10 | GD | `0x46f430` | `TencentLog::RoleLogin` | tlog | 8 | leaf |
| 11 | GD | `0x46f550` | `TencentLog::RoleLogout` | tlog | 12 | leaf |
| 12 | GD | `0x46f6e0` | `TencentLog::RoleLevelUp` | tlog | 12 | leaf |
| 13 | GD | `0x46f850` | `TencentLog::MonsterKill` | tlog | 12 | leaf |
| 14 | GD | `0x46f9c0` | `TencentLog::PlayerKill` | tlog | 12 | leaf |
| 15 | GD | `0x46fba0` | `TencentLog::TaskStart` | tlog | 8 | leaf |
| 16 | GD | `0x46fde0` | `TencentLog::ProgressMission` | tlog | 12 | leaf |
| 17 | GD | `0x470050` | `TencentLog::TaskFinished` | tlog | 8 | leaf |
| 18 | GD | `0x470240` | `TencentLog::CompleteMissionStep` | tlog | 12 | leaf |
| 19 | GD | `0x470440` | `TencentLog::CancelTask` | tlog | 8 | leaf |
| 20 | GD | `0x470650` | `TencentLog::FailMissionStep` | tlog | 12 | leaf |
| 21 | GD | `0x470850` | `TencentLog::CallBack` | tlog | 8 | leaf |
| 22 | GD | `0x470a20` | `TencentLog::NpcTrade` | tlog | 8 | leaf |
| 23 | GD | `0x470c00` | `TencentLog::Store` | tlog | 8 | leaf |
| 24 | GD | `0x470db0` | `TencentLog::TakeOut` | tlog | 8 | leaf |
| 25 | GD | `0x470f60` | `TencentLog::LearnSkill` | tlog | 12 | leaf |
| 26 | GD | `0x471570` | `TencentLog::UseItem` | tlog | 8 | leaf |
| 27 | GD | `0x471700` | `TencentLog::DestroyItem` | tlog | 12 | leaf |
| 28 | GD | `0x471890` | `TencentLog::CompoundItem` | tlog | 12 | leaf |
| 29 | GD | `0x471b00` | `TencentLog::EnchaseEquip` | tlog | 12 | leaf |
| 30 | GD | `0x471ce0` | `TencentLog::RepairEquip` | tlog | 12 | leaf |
| 31 | GD | `0x471ef0` | `TencentLog::EquipItem` | tlog | 8 | leaf |
| 32 | GD | `0x472090` | `TencentLog::UnEquipItem` | tlog | 12 | leaf |
| 33 | GD | `0x28a090` | `IgnoreRecycleTimeTask::start` | gamedebugcommand_cpp_2 | 12 | leaf |
| 34 | GD | `0x28a0d0` | `IgnoreSkillConsumePointTask::start` | gamedebugcommand_cpp_2 | 12 | leaf |
| 35 | GD | `0x28a110` | `IgnoreMoveChannelCooltimeTask::start` | gamedebugcommand_cpp_2 | 12 | leaf |
| 36 | GD | `0x28b080` | `SetDuelTeamDebugTask::start` | gamedebugcommand_cpp_2 | 11 | leaf |
| 37 | GD | `0x28dd30` | `UsePerfMonTask::start` | gamedebugcommand_cpp_2 | 16 | leaf |
| 38 | GD | `0x32c2b0` | `HandleGameBuilder_PingReq` | gamebuilderpackethandler | 8 | leaf |
| 39 | GD | `0x336340` | `HandleGameBuilder_SetAbilityReq` | gamebuilderpackethandler | 19 | leaf |
| 40 | GD | `0x2849c0` | `GameDebugTask::isHex` | gamedebugcommand_cpp_1 | 20 | leaf |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/tlog.cpp`
- `src/Server/GameDaemon/tlog.h`
- `src/Server/GameDaemon/gamedebugcommand_cpp_2.cpp`
- `src/Server/GameDaemon/gamedebugcommand_cpp_2.h`
- `src/Server/GameDaemon/gamebuilderpackethandler.cpp`
- `src/Server/GameDaemon/gamebuilderpackethandler.h`
- `src/Server/GameDaemon/gamedebugcommand_cpp_1.cpp`
- `src/Server/GameDaemon/gamedebugcommand_cpp_1.h`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-e24.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
