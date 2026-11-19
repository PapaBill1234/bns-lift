# lift-parity-console-4 handoff

Turns: 95

## Done
- MATCH over main: CG 448 -> 450 (+2), LG 627 -> 632 (+5), SCD 582 -> 585 (+3), POD 665 -> 667 (+2). Total +12. MATCH lost: 0.
- Parity: CG 91.6 %, LG 85.5 %, SCD 87.4 %, POD 87.9 %.
- New MATCH: `InitSymbol` x4, `WinServiceConsole::UninstallService` x4, SCD `DaemonConfig::Dump`, LG `PipeConsole::SetRunningInfo`,
  LG `IdleStateTable::scan`, LG `PipeConsole::addNode`.
- Files: `CrashHandler.cpp`, `WinServiceConsole.cpp`, `PipeConsole.cpp`, `IdleWatcher.cpp` (only `IdleStateTable::scan`),
  `SmartCouponDaemon/SmartCouponDaemon.cpp`, `Docs/Parity/lessons.md` (A25, B console-4, D, `## console-4`).

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
| `BnsCommonConfig::ReloadBnsCommonConfig` | SCD, POD | 98.9 | refs 97 | orig reloads `ID128_GUID_ZERO` per qword; VS2010 merges ours | 3 tries, no gain |
| `BnsCommonConfig::LoadBnsCommonConfig` | SCD, POD | 99.1 | refs 97 | same `ID128_GUID_ZERO` cause | same cause |
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

## ❓
- None new.

## Blocked
- None.

## Gate result
- `tools/gate.sh`: gate ok. `tools/parity.sh`: parity ok, no MATCH lost, on the final source (48df214). Docs only after that run.
