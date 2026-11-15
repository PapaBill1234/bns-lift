# lift-smartcoupondaemon-1 handoff

## Done
- Log.cpp (12), LogBuffer.cpp (13), LogMedia.cpp (4), AlertSender.cpp (10), Timer.cpp (10),
  DelayedRelease.cpp (7), StringUtil.cpp (1), SystemInformation.cpp (2). Total: 59 functions.
  These files are in `lift_common` in `CMakeLists.txt`.
- LogFile.cpp (12) and LogFile.h exist, but `CMakeLists.txt` does not build LogFile.cpp yet.
- Channel.h is new. Log.h, LogBuffer.h, LogMedia.h, Network.h, StringUtil.h, SysInfo.h, TimerQueue.h
  and DelayedRelease.h have more declarations.
- `lift_common` links the Wine import libs odbc32, ws2_32, iphlpapi and ole32.

## Not done
- LogFile.cpp: add it to `lift_common`, then build it. 5 of 17 PDB symbols are not lifted.
- LogBuffer: 3 of 16. AlertSender: 5 of 15. Timer: 9 of 19. Most of these are EH funclets
  (`dtor$N`) and scalar deleting destructors. The next session must check them against the PDB.
- CrashHandler (18): no CrashHandler.cpp. Only the header exists.
- Db (20): no Db.cpp and no Db.h.
- Missing functions in earlier modules: GrowingBuffer::grow 0x195A0, Console::~Console 0x28590,
  PipeConsole::SetDetectFrozenThread 0x25000, swprintf_s<128> 0x25E70, swprintf_s<256> 0x25E40,
  WindowConsoleOnLogoff / WindowConsoleOnShutdown 0x14AA0, Ripemd160::~Ripemd160 0x48730,
  Aes128::~Aes128 0x48A30, Prng::Generate 0x4CBF0 (all SmartCouponDaemon RVAs).

## ❓
- 21 `// ❓`, `// BUG:` or `// TODO` marks in the new .cpp files. Use grep to find them.

## Blocked
- The fix session had no Bash. It could not run `git status` or `tools/gate.sh`.

## Gate result
- First gate: fail, because this handoff file was missing.
- Fix: wrote this handoff. The gate was not run again (no Bash in the fix session).
