# lift-cg-2 handoff: CacheGate console, daemon, config

## Done
- `src/common/` modules (`// 0x<rva>` marks): Console (2), PipeConsole (23), WindowConsole (14),
  WinServiceConsole (13), TextConsole (9), Daemon (15), DaemonConfig (3 + inline FreeConfig),
  BnsCommonConfigDefinition (10 functions + 4 data tables, from IDA). About 89 functions.
- An IDA check found that all named functions of these classes have a mark, except the 2 below.
- New headers: Console, PipeConsole, WindowConsole, WinServiceConsole, TextConsole, CrashHandler, LogBuffer,
  LogMedia, DaemonConfig, DelayedRelease, Network, SysInfo, TimerQueue, BnsCommonConfig ❓ (file name),
  StringUtil ❓ (String class, id128).
- `CMakeLists.txt`: all new `.cpp` files are in `lift_common`.

## Not done (compiler-generated or no IDA symbol)
- 0xac80 Daemon vector deleting destructor; 0x17600 WinServiceConsole vector deleting destructor.
- 0xc5d0, 0xcca0, 0x3a4a0, 0x3aa50: compiler-generated helpers.
- Daemon::cooldown and FlushExtraLog have no IDA symbols (LTCG inlined them).
- TODO declarations for later cards: String::GetId128FromGuidString 0xdd90, Network::GetAddressStringW 0xd6d0.

## ❓
- BnsCommonConfig UpdateAllVariable 0x1c10, Copy 0x1d50, CompareMatch 0x1fc0: LTCG put the globals
  Config / ConfigNoReload in place of this and the arguments. The lift uses this and the arguments
  (the only callers give the same values).
- MIN/MAX/DEFAULT_NP_PROGRAM_ID (0x467b4, 0x465bc, 0x4638c) are file-static in the lift.
- Open: StateString text, Log::Flush semantics, makeConsole line 119, CreateManager option values,
  arguments that LTCG removed. Daemon::Reload is static in the code, not in the PDB.

## BUG marks
- 0x13e0 (old Config leaks), 0x1600 (reload struct leaks, 2 paths), and the console marks in the source.

## Blocked
- None. Bash denied some combined commands; single commands worked.

## Gate result
- `tools/gate.sh`: `gate ok` (2026-11-15, after BnsCommonConfigDefinition). No new warnings in BnsCommonConfig.cpp.
