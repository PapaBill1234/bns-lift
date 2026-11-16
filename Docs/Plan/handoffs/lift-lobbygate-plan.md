# lift-lobbygate-plan handoff

## Done
- Checks: exe and PDB exist. PDB GUID A888A14A-92D2-4FE1-B491-96B539B7DBD2 is the same in the exe (RSDS). PDB age 2, exe age 1 (normal).
  Imports: system DLLs, msvcr100, msvcp100. No ODBC. The exe loads XmlReader_sv64, bsConsole_sv64 and dbghelp at run time (not linked).
- PDB: 1,212 function symbols in 88 modules. Removed: CRT 33, zstd (vendor) 112, lifted names in `src/common/` 319.
- BnsCommonConfigDefinition (10) is already in `src/common/BnsCommonConfig.cpp`. Card 4 only compares the `_Def` tables.
- Cards:
  - `lift-lobbygate-1` (common: Session, PacketUtil, Security, CrashHandler, IdleWatcher, network delta; ~153)
  - `-2` (common: base delta ~88, crypto rsa/dh/NumberTheory/oaep ~106, ContentsRuleConfigDefinition 9; ~203)
  - `-3` (server: ThreadFreePacketPump, FragmentPacket, Client, LobbyDChannel; ~187)
  - `-4` (server: LobbyDPacketHandler, LobbyGate, LobbyGatePacketHandler, small modules; ~195; full exe)
  - `-verify` and `lift-postofficedaemon-plan` (dep `lift-lobbygate-4`)
- Queue: `Docs/Plan/queue/lift-lobbygate-plan.tsv` (6 rows, 9 columns each).

## Not done
- None in scope.

## ❓
- Counts are PDB symbol counts with EH funclets and scalar deleting destructors. The real lift count is lower.
- I matched lifted functions by name after each `// 0x` comment in `src/common/*.cpp`. Overloads can give a wrong match. Each card tells the session to check `src/common/` first.
- `lift-smartcoupondaemon-4` lifted 0 functions. Session, CrashHandler, NumberTheory and rsa are still not lifted. LobbyGate cards 1 and 2 take them.
- ThreadFreePacketPump and FragmentPacket are in the LobbyGate project in the PDB, so card 3 puts them in `src/LobbyGate/`. Later servers can move them to `src/common/`.
- ContentsRuleConfigDefinition goes to `src/common/` (like BnsCommonConfig). Source path not confirmed.

## Blocked
- None.

## Gate result
- `tools/gate.sh`: `gate ok` (2026-11-16). No source change.
