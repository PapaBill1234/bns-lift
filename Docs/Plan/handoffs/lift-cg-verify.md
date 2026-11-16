# lift-cg-verify handoff

## Done
- `tools/verify/run_cachegate.sh`, `compare_cachegate.sh`, `replay.py`. Self test with the original exe: 0 diffs.
- Checks 1-6 run. Results and each difference are in `Docs/Verify/CacheGate.md`.
- `src/` as committed: all checks FAIL. The lifted exe stops at start with 0xc0000417.
- 6 fixes found and tested in `build/verify/fixsrc/` (scratch copy). The diff is in `Docs/Verify/CacheGate-fixes.patch` (`git apply --check` passes):
  1. `CacheGateConfig::_Def` section rows: label in `desc` (`src/CacheGate/CacheGate.cpp:39,48,51`).
  2. `XmlConfigReader::Initialize` overload order (`src/common/DaemonConfig.h:53-54`).
  3. `XmlReader.h` overload groups in reverse order (`XmlElement::Attribute` must be vtable slot 8).
  4. `Session::EventId` 0xded0 returns 3 (`src/common/Session.cpp`).
  5. `RefCntObject` constructor: `_ref 1`, `_tag 10`, `_history nullptr` (`src/common/RefCntObject.h`).
  6. `DaemonConfig::Dump` caller passes `L"cachegate config"` (`src/CacheGate/CacheGate.cpp:171`).
- With the patched exe: checks 1, 3, 4, 5, 6 PASS. It listens on the same ports as the original. Check 2 PASS, but the version line is different (log.diff 4 lines).

## Not done
- The patch is not applied to `src/`. `src/` is outside the Files of this card. A follow-up card must apply it.
- VERSIONINFO 0.0.348.524 is missing in the lifted exe (`Daemon::LoadVersion`, log at `src/common/Daemon.cpp:496,545`).
- Check 7 (381 CacheDaemon accepts the 2019 hello) is not run. It needs `bns-wine/`.
- After the patch is in `src/`, run `compare_cachegate.sh 20 --pktlog` again.
- Follow-up: look for the same faults in the other servers (overload order, `EventId` stubs, inlined base constructors).

## ❓
- `[crash-mail], PrintMailInfo` line: seen one time only. Closed.

## Blocked
- IDA failed to open (error 4). All facts came from `.scratch/hr/` and the exe bytes.

## Gate result
- `tools/gate.sh`: `gate ok`.
