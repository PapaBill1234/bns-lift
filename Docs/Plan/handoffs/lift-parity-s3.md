# lift-parity-s3 handoff

## Done
- Gate ok. `tools/parity.sh` PARITY 0. MATCH s2 end -> now: CG 345 -> 374, LG 425 -> 462, SCD 388 -> 429, POD 423 -> 474. No exe lost a MATCH function.
- zstd: `vendor/zstd/src` is now upstream zstd `dev` commit bb6eaf64 (source: github.com/facebook/zstd). The old v1.3.5 is in `.scratch/zstd-1.3.5`. `vendor/zstd/README.md` has the version.
- Fixed groups: AlertSender, LogMedia, LogFile, LogBuffer, Db / DbTransaction (inline `Db::~Db`), BnsCommonConfig, StringUtil, zstd functions.
- Per-exe file path literal: new wrapper files `src/Server/Shared/BnsCommonConfigDefinitionShortPath.cpp` (LG, SCD) and `src/Server/Economy/Shared/ThreadFreePacketPumpShortPath.cpp` (POD, MDD). `CMakeLists.txt` moves both sources out of `lift_common`.
- `Docs/Parity/lessons.md`: lessons 18-30 (fixes that worked and fixes that did not work).
- `Docs/Parity/allow-worse.txt`: LG `Memory::CreateManager` (string_at noise, lesson 2).

## Not done (function, signal, cause, why stopped)
- `AlertSender::AlertSender` LG/SCD, `Channel::~Channel` SCD/POD, `Memory::CreateManager`: refs; a vtable read as a 2-byte string (lesson 2). Tool noise, no source cause.
- `Log::Write`, `Log::WriteV`: consts (0x20 vs 0x88); `.tls` variable order. Also `LogBuffer::deallocate_me`, `LogBufferAllocator::Initialize`. Linker order, no source fix found.
- `LogMedia::Write` 46.8: calls; LTCG inlines `removeReferenceCount`. Inline choice of the linker.
- `LogFile::writeFile` 93.9: layout of the alert block. Not found after 2 tries.
- `AlertSender::run` 97.8: original inlines the 44-byte zero; VS2010 cl emits a `memset` call. Each try lost a MATCH; undone.
- `AlertSender::init` LG 0x19da0 90.5: consts; LTCG folds L"LOBBYGATE", worldId 0, 1000. Cause is the virtual `ShortName()` call in `src/Server/LobbyGate/LobbyGate.cpp:407`. Out of card files.
- LG `ZSTD_compressBegin_internal` 98.8: calls; LTCG inline choice.
- `BnsCommonConfig::LoadBnsCommonConfig` CG 97.0, LG 97.0, SCD 96.1, POD 96.1: calls/refs; `Log::Write` call order and one extra Config ref. Not found.
- `BnsCommonConfig::ReloadBnsCommonConfig` SCD/POD 98.9: refs; original loads `ID128_GUID_ZERO` two times.
- `ThreadFreePacketPump::~ThreadFreePacketPump`, `ThreadFreePacketPumpEvent::~ThreadFreePacketPumpEvent` LG/POD: not looked at (no turns left).

## ❓
- None new.

## Blocked
- IDA open of `CacheGate.exe.i64` fails (idalib status 4). Used capstone (`.scratch/dis_any.py`) and `tools/funcdiff.py --show`.

## Gate result
- `tools/gate.sh`: ok. `tools/parity.sh`: PARITY 0, all 4 exes up.
