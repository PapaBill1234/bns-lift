# lift-parity-console-4 handoff

Turns: 95

## Done
- MATCH over main (95ad5be, after the merge with main): CG 454 -> 456 (+2), LG 653 -> 658 (+5), SCD 628 -> 630 (+2), POD 692 -> 694 (+2).
  Total +11. MATCH lost: 0.
- Parity: CG 92.9 %, LG 89.0 %, SCD 94.2 %, POD 91.4 %.
- New MATCH: `InitSymbol` x4, `WinServiceConsole::UninstallService` x4, LG `PipeConsole::SetRunningInfo`,
  LG `IdleStateTable::scan`, LG `PipeConsole::addNode`.
- Files: `CrashHandler.cpp`, `WinServiceConsole.cpp`, `PipeConsole.cpp`, `IdleWatcher.cpp` (only `IdleStateTable::scan`),
  `SmartCouponDaemon/SmartCouponDaemon.cpp`, `Docs/Parity/lessons.md` (A29, B console-4, D, `## console-4`).

## Not done (function, signal, cause, why stopped)

| Function | Exe | Score | Signal | Cause | Why stopped |
| --- | --- | --- | --- | --- | --- |
| `PipeConsole::run` | CG, LG, SCD, POD | 96.3 | calls 89 | block order (ICF) | stop list |
| `PipeConsole::SetInvalidInfo` | CG, SCD, POD | 96.3 | calls 89 | orig has 2 `addNode` sites; VS2010 merges ours | stop list |
| `WindowConsole::Open` | all 4 | 92.5-95.2 | consts 86 | ICF | stop list |
| `PipeConsole::processCommand` | all 4 | 97.0 | consts 91 | `wcscmp` result in `sbb` form | 3 tries, no gain |
| `PipeCommandProcess::processCommand` | all 4 | 96.3 | consts 89 | `wcscmp` result in `sbb` form | 3 tries, no gain |
| `PipeConsole::checkFrozenThread` | LG | 91.0 | refs 93, consts 80 | orig inlines `SetInvalidInfo` with `addNode` and the match-node search | needs `SetInvalidInfo` change (stop list); inline `addNode` lost score |
| `DaemonConfig::Dump` | CG | 97.9 | refs 94 | RTTI data next to `_Def`; we build with `/GR-` | const pointer form gave 0 |
| `DaemonConfig::Dump` | SCD | 97.9 | refs 94 | data layout of `_Def`; the `LOCALHOST_IP` form gave +1 on eaba76b, 0 on main after pod-4 | win gone after merge; `LOCALHOST_IP` kept as PDB name |
| `CacheDList::LoadCachedListConfigFile` | CG | 98.5 | calls 97, refs 98 | loop form (B) | not tried this card; earlier forms failed |
| `ContentsRuleConfig::CheckMinMaxBoundary` | LG | 93.3 | refs 80 | not examined | time |
| `ContentsRuleConfig::Dump` | LG | 99.2 | refs 98 | not examined | time |
| `ContentsRuleConfig::LoadContentsRuleConfig` | LG | 93.6 | calls 90, refs 91 | 4 path literals (D) | time |
| `ContentsRuleConfig::MakeListPacket` | LG | 86.9 | consts 64 | not examined | time |
| `ContentsRuleConfig::UpdateAllVariable` | LG | 81.8 | refs 73, consts 73 | not examined | time |
| `GameEventConfig::Load` | SCD | 89.2 | calls 88, consts 80 | not examined | time |
| `GameEventConfig::SetupGameEventListFromXml` | SCD | 91.3 | calls 87, consts 88 | not examined | time |
| `WorldConfigManager::loadWorldConfigFile` | POD | 94.3 | calls 84 | success-first form lowered score (B) | time |
| `WorldConfigManager::setupWorldConfigList` | POD | 98.6 | refs 96 | not examined | time |
| `WorldConfigManager::updateWorldList` | POD | 80.2 | calls 69, refs 86 | block layout (D) | time |

## Repair 2 (skeptic findings)
- `PipeConsole::addNode`: one source form in all 4 exes. It copies `valueString`. The per-exe form and the `// BUG:` mark are removed.
  All 4 PDBs give the same lines (841-859) and the same source file. LTCG folds the `L""` argument in CG/SCD/POD (CG 0x15ed0).
- `tools/pdbq.py <EXE> lines <lo> <hi>`: new tracked command for the PDB line map. It replaces the untracked `.scratch/lines.py`.
- `IdleStateTable::scan`: the `// LIFT:` comment names LobbyGate with the address.
- `Docs/Parity/lessons.md` A29 (was A25) and `## console-4`: the constant-folding cause replaces the false "newer source" claim.

## Repair 3 (skeptic findings)
- Merged main (95ad5be: crypto-4, net-4, packet-4, scd-4, pod-4) into the branch. New numbers over main: CG +2, LG +5, SCD +2, POD +2 (+11).
- SCD `DaemonConfig::Dump` is DIFF 97.9 on main after the merge. The MATCH claim is removed. `LOCALHOST_IP` stays as the PDB name form.
- `Docs/Parity/lessons.md`: the console-4 section is A29 (main has A25-A28). The A29 count is 11. The SCD `Dump` bullet moved to B.
- `BnsCommonConfig::LoadBnsCommonConfig` / `ReloadBnsCommonConfig` (SCD, POD) left the "Not done" table: pod-4 matched them with `memcpy` (A28).

## ❓
- None new.

## Blocked
- None.

## Gate result
- Repair 3, after the merge with main (95ad5be): `tools/gate.sh`: gate ok. `tools/parity.sh`: parity ok.
  MATCH -> DIFF 0, MATCH name gone 0 in all 4 exes.
