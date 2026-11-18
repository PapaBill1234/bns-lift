# lift-parity-order-3 handoff

Turns: 133

## Done
- MATCH now (7 functions): `BloodDaemonMain` 0xa690, `makeConsole` 0xa540, `LogFile::writeFile` 0x11600, `Daemon::start` 0xb140,
  `DaemonConfig::Load` 0xc600, `BnsCommonConfig::LoadBnsCommonConfig` 0x13e0, SCD `GameEventManager::PostGameEventLogList` 0xb140.
- Result (baseline -> now): CG 424 -> 430, LG 583 -> 588, SCD 543 -> 550, POD 626 -> 631. MATCH lost: 0.
- Gate ok. `tools/parity.sh` ok. Patterns are in `Docs/Parity/lessons.md`.

## Not fixed (function, signal, cause, why stopped)
- `PipeConsole::run` 0x157b0 (shared): call order 96.3. Extra Log before GetLastError, `disconnectAndReconnect` too early. 3 tries, no gain.
- `Channel::MakeSession` 0x10450 (SCD): Log::Write order, consts 0x17 0x24. Port-first form lost MATCH in CG, LG, POD. Undone.
- `DChannelMgr::SetupDaemonList` 0xd270 (SCD): 96.3. Ref order (vtable before file string), const 0x178. 2 tries.
- `UnsentPostContextManager::initContextManager` 0xc6d0 and `updateWorldList` 0xcae0 (POD): success Leave tail must be the last block.
  `goto` form and RAII (`AutoCS`) give the same layout or add a call. Compiler layout cause.
- `UnsentPostContextManager::addUnsentPostContextList` 0xce80 (POD): only const -2 (EH state). Toolchain cause.
- `UnsentPostContextManager::deliverUnsentPost` 0xd510 (POD): `removeReferenceCount` order. Not looked at (turn limit).
- LG `IdleStateTable::scan`, `PipeConsole::SetRunningInfo`: not looked at (turn limit).
- SCD `GameEventLogEvent::HandleEvent` 0xb6e0: 92.7, call order, const 0x2. Not in the card list.
- Stop list: POD `DaemonConfig::Dump`, `TimerQueue::clearShortTermQueueSlot`.
- Shared entries with a shared cause, not in scope: `Daemon::setState`, `CryptoMode::~CryptoMode`, `BloodCert::IsValid`,
  `Console::Flush`, `RefCntObject::operator delete`, `wmain$dtor$0`.

## ❓
- `DaemonConfig::Load` body is not indented after the `if (module != nullptr)` change (marked LIFT). Cosmetic.

## Blocked
- None.
