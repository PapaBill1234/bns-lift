# Parity triage (lift-parity-0)

Input: `tools/funcdiff.py <EXE> --build build-vs2010 --show .` and `--only`, after the 4 noise fixes in `noise.md`.
Generator: `.scratch/triage.py` (not in git). Each DIFF entry has 1 primary cause class. The column
"Other causes" gives the other classes that the same diff shows. "Source file" is the file that defines the
function in `src/` (`-` = not found).

## Cause classes

| Cause class | Rule (from the diff) | Fix direction |
| --- | --- | --- |
| zstd version | name starts with `ZSTD_`, `FSE_`, `HUF_`, `HIST_`, `BIT_`, `POOL_` | vendor the zstd commit of the original (see "zstd version") |
| wrong callee: memory manager | orig refs `BaseMemoryManager::_Instance` (indirect call); ours calls `HeapAlloc`/`HeapFree` or `*Allocator::initAllocator` | lift `Memory.cpp`/`MemoryManager.h` allocation path as in orig |
| base vtable store (novtable ❓) | ours refs `??_7RefCntObject@@6B@` | ❓ `RefCntObject` is maybe `__declspec(novtable)` in orig |
| `__FILE__` path differs or missing | a ref to a `"*.h"`/`"*.cpp"` string differs | header paths (`e:\dailybuild02\...\RefCntObject.h`) in ours; `L"source\Daemon.cpp"` in orig; `..\..\Shared` against `..\Shared` |
| inlined but should not be | orig calls a named function that ours does not call | stop inlining (move body to `.cpp`, or the function is missing a `__FILE__` macro form) |
| not inlined but should be | ours calls a named function that orig does not call | make it inline (header) or merge |
| wrong callee | each side calls a named function that the other does not | check the callee name and overload |
| STL form differs | callee names differ only in template arguments | use the orig STL type (`pair<K const,V>`, allocator) |
| call order differs | same callees, other order | source statement order |
| call count differs | same named callees, other count | one call more or less in source |
| import or indirect call differs | only `import:*` or `<indirect>` calls differ | API call or virtual call differs |
| string ref differs | a string ref (not a file name) differs | text of a log or format string |
| data ref differs | a global or `<data>` ref differs | global name, static data, vtable |
| constant differs | only constants differ | field offset, size, flag, stack frame size |
| EH state constant (-2) differs | only `0xfffffffffffffffe` differs | an object with a destructor is in scope on one side only |
| ref order differs | score below 100, but the ref sets are equal | order of refs |

Classes for misses (functions only in the original):

| Cause class | Rule |
| --- | --- |
| inlined but should not be | defined in `src/` and a DIFF caller in orig calls it, ours does not |
| inlined but should not be (header inline) | defined in a class body in a header |
| inlined but should not be (CRT template) | `swprintf_s<N>` template: ours calls `import:swprintf_s` direct |
| not referenced in ours (dropped or inlined) | defined in `src/`, no caller in the DIFF lists (mostly `BigInteger`, `Rsa`, `Oaep*`: crypto code that ours does not reach) |
| missing function | not found in `src/` |
| compiler noise (COMDAT fold: PDB name of a folded body) | PDB name is not in the mangled name (identical COMDAT folding). The source cannot change it |
| compiler noise (EH funclet) | `$dtor$` funclet |
| zstd version | zstd name |

## Counts (entries per exe; one entry = one function in one exe)

DIFF entries: 937. Misses (only in original): 342. Only in ours: 175.

### Top 10 causes (DIFF primary class + miss class)

| # | Cause class | Entries |
| --- | --- | --- |
| 1 | __FILE__ path differs or missing | 222 |
| 2 | constant differs | 173 |
| 3 | not referenced in ours (dropped or inlined) | 153 |
| 4 | inlined but should not be | 129 |
| 5 | wrong callee: memory manager | 105 |
| 6 | base vtable store (novtable ❓) | 76 |
| 7 | zstd version | 73 |
| 8 | call order differs | 65 |
| 9 | data ref differs | 56 |
| 10 | not inlined but should be | 33 |

### DIFF functions: primary cause class

| Cause class | Primary | Any (primary + other) |
| --- | --- | --- |
| __FILE__ path differs or missing | 222 | 314 |
| constant differs | 173 | 550 |
| wrong callee: memory manager | 105 | 105 |
| base vtable store (novtable ❓) | 76 | 84 |
| call order differs | 65 | 89 |
| data ref differs | 56 | 335 |
| zstd version | 47 | 47 |
| inlined but should not be | 37 | 91 |
| not inlined but should be | 33 | 61 |
| string ref differs | 31 | 182 |
| import or indirect call differs | 26 | 74 |
| STL form differs | 23 | 30 |
| wrong callee | 22 | 117 |
| call count differs | 13 | 40 |
| ref order differs | 4 | 4 |
| EH state constant (-2) differs | 4 | 10 |

### Misses (only in original)

| Cause class | Entries |
| --- | --- |
| not referenced in ours (dropped or inlined) | 153 |
| inlined but should not be | 92 |
| compiler noise (COMDAT fold: PDB name of a folded body) | 27 |
| zstd version | 26 |
| inlined but should not be (CRT template) | 25 |
| inlined but should not be (header inline) | 12 |
| compiler noise (EH funclet) | 4 |
| missing function | 3 |

### Only in ours

| Cause class | Entries |
| --- | --- |
| zstd version | 119 |
| not inlined but should be, or extra function | 38 |
| lift helper (anonymous namespace) | 14 |
| compiler noise (EH funclet) | 4 |

## zstd version
- Vendored: upstream tag v1.3.5 (`vendor/zstd/src`, `git describe` = v1.3.5).
- Original (CacheGate PDB): a zstd `dev` branch snapshot between 2018-05-23 and 2018-05-30. Its headers still say 1.3.4.
  - It has `ZSTD_compressBlock_fast_dictMatchState`. dev got it with merge `08c5be5d` (PR #1117, 2018-05-23).
  - It has no `ZSTD_compressBlock_doubleFast_dictMatchState`. dev got it with merge `7c33b482` (PR #1151, 2018-05-31).
  - It has `ZSTD_BtFindBestMatch_selectMLS_extDict` (renamed by PR #1169, 2018-06-13), `FSE_count_simple` (moved to `hist.c` by PR #1189, 2018-06-14), `ZSTD_cpuid`.
  - Last dev merge with these facts: `ac4f7ead` (PR #1154, 2018-05-30). Range: `08c5be5d`..`ac4f7ead`.
  - The original PDB has no `zstd_decompress.obj` and no `hist.obj`. Ours links `HUF_decompress*`, `FSE_decompress*`, `HIST_*`.
- Result: version differs. All zstd DIFF and miss entries have the cause class "zstd version".
- Fix proposal (later card): vendor commit `ac4f7ead` of facebook/zstd, and build only `lib/common` + `lib/compress` (+ `fse_decompress.c`, which the original has).

## Shared code (DIFF in 2 or more exes): 169 functions

| Function | Exes | Signal | Cause class | Other causes | Source file |
| --- | --- | --- | --- | --- | --- |
| AlertSender::AlertSender | LG,SCD,POD | refs | string ref differs | data ref differs | BloodLib/source/AlertSender.cpp |
| AlertSender::run | CG,LG,SCD,POD | calls/consts | wrong callee | constant differs | BloodLib/source/AlertSender.cpp |
| AlertSender::sendRemain | CG,LG,SCD,POD | calls | call order differs | - | BloodLib/source/AlertSender.cpp |
| AlertSender::writev2 | CG,LG,SCD,POD | calls/consts | inlined but should not be | constant differs | BloodLib/source/AlertSender.cpp |
| BaseRefCntObj::deallocate_me | CG,LG,SCD,POD | calls/refs | wrong callee: memory manager | import or indirect call differs; data ref differs | BloodLib/source/RefCntObject.cpp |
| BloodDaemonMain | CG,LG,SCD,POD | calls/refs/consts | wrong callee: memory manager | __FILE__ path differs or missing; inlined but should not be; string ref differs; data ref differs; constant differs | BloodLib/source/Daemon.cpp |
| Blowfish::Setup | CG,LG,SCD,POD | consts | constant differs | - | Security/source/BloodCrypto/crypto/blowfish.cpp |
| BnsCommonConfig::CheckMinMaxBoundary | CG,LG,SCD,POD | refs/consts | constant differs | __FILE__ path differs or missing | Shared/BnsCommonConfigDefinition.cpp |
| BnsCommonConfig::Dump | CG,LG,SCD,POD | refs | data ref differs | __FILE__ path differs or missing | Shared/BnsCommonConfigDefinition.cpp |
| BnsCommonConfig::LoadBnsCommonConfig | CG,LG,SCD,POD | calls/refs | __FILE__ path differs or missing | not inlined but should be; data ref differs | Shared/BnsCommonConfigDefinition.cpp |
| BnsCommonConfig::ReloadBnsCommonConfig | CG,LG,SCD,POD | calls/refs | call order differs | data ref differs; __FILE__ path differs or missing | Shared/BnsCommonConfigDefinition.cpp |
| BnsCommonConfig::UpdateAllVariable | CG,LG,SCD,POD | refs | data ref differs | - | Shared/BnsCommonConfigDefinition.cpp |
| BnsCommonConfig::UpdateReloadedVariable | CG,LG,SCD,POD | refs | data ref differs | - | Shared/BnsCommonConfigDefinition.cpp |
| Channel::Close | SCD,POD | refs | __FILE__ path differs or missing | - | BloodLib/source/Channel.cpp |
| Channel::~Channel | SCD,POD | refs | string ref differs | data ref differs | BloodLib/source/Channel.cpp |
| CrashHandler::CrashHandler | SCD,POD | refs | string ref differs | data ref differs | BloodLib/source/CrashHandler.cpp |
| CrashHandler::MakeCrash | CG,LG,SCD,POD | consts | constant differs | - | BloodLib/source/CrashHandler.cpp |
| CrashHandler::handleCrash | CG,LG,SCD,POD | calls/refs/consts | inlined but should not be | string ref differs; data ref differs; constant differs | BloodLib/source/CrashHandler.cpp |
| Ctr::Encrypt | CG,LG,SCD,POD | consts | constant differs | - | Security/source/BloodCrypto/crypto/mode/ctr.cpp |
| Daemon::Cooldown | CG,LG,SCD,POD | consts | constant differs | - | BloodLib/source/Daemon.cpp |
| Daemon::Reload | CG,LG,SCD,POD | consts | constant differs | - | BloodLib/source/Daemon.cpp |
| Daemon::Start | CG,LG,SCD,POD | calls/refs/consts | wrong callee: memory manager | __FILE__ path differs or missing; inlined but should not be; data ref differs; constant differs | BloodLib/source/Daemon.cpp |
| Daemon::setAddress | CG,LG,SCD,POD | consts | constant differs | - | BloodLib/source/Daemon.cpp |
| Daemon::start | CG,LG,SCD,POD | calls/refs/consts | wrong callee: memory manager | __FILE__ path differs or missing; wrong callee; string ref differs; data ref differs; constant differs | BloodLib/source/Daemon.cpp |
| Daemon::timerMain | CG,LG,SCD,POD | calls | call order differs | - | BloodLib/source/Daemon.cpp |
| DaemonConfig::Dump | CG,SCD | refs | __FILE__ path differs or missing | data ref differs | BloodLib/source/DaemonConfig.cpp |
| DaemonConfig::Load | CG,LG,SCD,POD | calls/consts | inlined but should not be | constant differs | BloodLib/source/DaemonConfig.cpp |
| Db::AllocTransaction | SCD,POD | calls | call order differs | - | BloodLib/source/Db.cpp |
| Db::Clear | SCD,POD | calls/refs/consts | wrong callee: memory manager | __FILE__ path differs or missing; import or indirect call differs; data ref differs; EH state constant (-2) differs | BloodLib/source/Db.cpp |
| Db::Initialize | SCD,POD | calls/refs | wrong callee: memory manager | __FILE__ path differs or missing; import or indirect call differs; data ref differs | BloodLib/source/Db.cpp |
| Db::Log | SCD,POD | consts | constant differs | - | BloodLib/source/Db.cpp |
| Db::clearList | SCD,POD | calls/consts | inlined but should not be | constant differs | BloodLib/source/Db.cpp |
| Db::initEnv | SCD,POD | consts | constant differs | - | BloodLib/source/Db.cpp |
| DbTransaction::BindCol | SCD,POD | calls/refs/consts | __FILE__ path differs or missing | inlined but should not be; string ref differs; constant differs | BloodLib/source/Db.cpp |
| DbTransaction::BindParam | SCD,POD | refs/consts | string ref differs | constant differs | BloodLib/source/Db.cpp |
| DbTransaction::Execute | SCD,POD | consts | constant differs | - | BloodLib/source/Db.cpp |
| DbTransaction::Fetch | SCD,POD | calls/refs/consts | not inlined but should be | string ref differs; constant differs | BloodLib/source/Db.cpp |
| DbTransaction::Prepare | SCD,POD | calls/refs/consts | __FILE__ path differs or missing | not inlined but should be; constant differs | BloodLib/source/Db.cpp |
| DbTransaction::connect | SCD,POD | consts | constant differs | - | BloodLib/source/Db.cpp |
| DbTransaction::initStatement | SCD,POD | consts | constant differs | - | BloodLib/source/Db.cpp |
| DbTransaction::initialize | SCD,POD | consts | constant differs | - | BloodLib/source/Db.cpp |
| DelayedRelease::Release | CG,LG,SCD,POD | refs | base vtable store (novtable ❓) | - | BloodLib/source/DelayedRelease.cpp |
| DelayedRelease::releaseNode | CG,LG,SCD,POD | calls/refs | __FILE__ path differs or missing | call order differs | BloodLib/source/DelayedRelease.cpp |
| DynamicEventObject::~DynamicEventObject | CG,LG,SCD,POD | refs | data ref differs | - | BloodLib/source/Network.cpp |
| DynamicRefCntObj::~DynamicRefCntObj | SCD,POD | refs | string ref differs | data ref differs | BloodLib/source/RefCntObject.cpp |
| FragmentPacketConcatenater::Add | LG,POD | calls/refs/consts | __FILE__ path differs or missing | call count differs; constant differs | Packet/FragmentPacket.cpp |
| FragmentPacketConcatenater::Clone | LG,POD | refs/consts | __FILE__ path differs or missing | EH state constant (-2) differs | Packet/FragmentPacket.cpp |
| HandleCacheGateFragmentRelay | CG,POD | calls/refs/consts | __FILE__ path differs or missing | wrong callee; string ref differs; data ref differs; constant differs; import or indirect call differs | Economy/CacheGate/CacheGateSessionHandler.cpp |
| HandleCacheGateRelay | CG,POD | calls/refs/consts | data ref differs | constant differs; call order differs | Economy/CacheGate/CacheGateSessionHandler.cpp |
| HeapMemoryManager::Realloc | CG,LG,SCD,POD | calls | call order differs | - | BloodLib/source/MemoryManager.cpp |
| HeapMemoryManager::ReallocZero | CG,LG,SCD,POD | calls | call order differs | - | BloodLib/source/MemoryManager.cpp |
| InitSymbol | CG,LG,SCD,POD | calls/refs | import or indirect call differs | string ref differs | BloodLib/source/CrashHandler.cpp |
| IoWorker::run | CG,LG,SCD,POD | calls/refs/consts | wrong callee: memory manager | __FILE__ path differs or missing; wrong callee; data ref differs; constant differs | BloodLib/source/IoWorkerThread.cpp |
| Log::Add | CG,LG,SCD,POD | calls/refs | __FILE__ path differs or missing | wrong callee | BloodLib/source/Log.cpp |
| Log::Write [?Write@Log@@SAXW4Type@1@PEB_WH1ZZ] | CG,LG,SCD,POD | consts | constant differs | - | BloodLib/source/Log.cpp |
| Log::WriteV | CG,LG,SCD,POD | consts | constant differs | - | BloodLib/source/Log.cpp |
| Log::run | CG,LG,SCD,POD | calls/refs/consts | wrong callee: memory manager | wrong callee; data ref differs; constant differs | BloodLib/source/Log.cpp |
| LogBuffer::GetLog | CG,LG,SCD,POD | refs | data ref differs | - | BloodLib/source/LogBuffer.cpp |
| LogBuffer::deallocate_me | CG,LG,SCD,POD | consts | constant differs | - | BloodLib/source/LogBuffer.cpp |
| LogBufferAllocator::allocate | CG,LG,SCD,POD | refs/consts | base vtable store (novtable ❓) | constant differs | BloodLib/source/LogBuffer.cpp |
| LogBufferAllocator::initAllocator | CG,LG,SCD,POD | calls/refs/consts | wrong callee: memory manager | __FILE__ path differs or missing; import or indirect call differs; data ref differs; constant differs | BloodLib/source/LogBuffer.cpp |
| LogBufferPool::allocate | CG,LG,SCD,POD | refs/consts | base vtable store (novtable ❓) | data ref differs; constant differs | BloodLib/source/LogBuffer.cpp |
| LogFile::makeDirectory | CG,LG,SCD,POD | calls/consts | call order differs | constant differs | BloodLib/source/LogFile.cpp |
| LogFile::writeFile | CG,LG,SCD,POD | calls | call count differs | - | BloodLib/source/LogFile.cpp |
| LogMedia::Write | CG,LG,SCD,POD | calls/refs/consts | __FILE__ path differs or missing | wrong callee; string ref differs; data ref differs; constant differs | BloodLib/source/LogMedia.cpp |
| Network::Clear | CG,LG,SCD,POD | calls/refs/consts | wrong callee: memory manager | __FILE__ path differs or missing; import or indirect call differs; data ref differs; constant differs | BloodLib/source/Network.cpp |
| Network::GetAddressStringW | CG,LG,SCD,POD | consts | constant differs | - | BloodLib/source/Network.cpp |
| Network::Initialize | CG,LG,SCD,POD | calls/refs/consts | wrong callee | not inlined but should be; data ref differs; constant differs | BloodLib/source/Network.cpp |
| Network::Network | CG,LG,SCD,POD | refs/consts | base vtable store (novtable ❓) | data ref differs; constant differs; string ref differs | BloodLib/source/Network.cpp |
| Network::OpenPort | CG,LG | calls/refs/consts | wrong callee: memory manager | __FILE__ path differs or missing; inlined but should not be; string ref differs; data ref differs; constant differs | BloodLib/source/Network.cpp |
| Network::initInstance | CG,LG,SCD,POD | calls/refs/consts | wrong callee: memory manager | __FILE__ path differs or missing; import or indirect call differs; data ref differs; constant differs | BloodLib/source/Network.cpp |
| Network::initWorkerThread | CG,LG,SCD,POD | calls/refs/consts | wrong callee: memory manager | __FILE__ path differs or missing; import or indirect call differs; data ref differs; constant differs; string ref differs | BloodLib/source/Network.cpp |
| Network::initializeSocketInterface | CG,LG,SCD,POD | calls | import or indirect call differs | - | BloodLib/source/Network.cpp |
| Packet::Allocate | CG,SCD | consts | constant differs | - | BloodLib/source/Packet.cpp |
| Packet::Allocate [?Allocate@Packet@@QEAAPEBDXZ] | LG,POD | consts | constant differs | - | BloodLib/source/Packet.cpp |
| Packet::Clear | CG,LG,SCD,POD | calls/refs | __FILE__ path differs or missing | call order differs | BloodLib/source/Packet.cpp |
| PacketBuffer::CheckCompose | LG,POD | consts | constant differs | - | BloodLib/source/PacketBuffer.cpp |
| PacketBuffer::Compose | CG,LG,SCD,POD | calls/refs/consts | inlined but should not be | __FILE__ path differs or missing; wrong callee; data ref differs; constant differs | BloodLib/source/PacketBuffer.cpp |
| PacketBuffer::Decompose | CG,LG,SCD,POD | consts | constant differs | - | BloodLib/source/PacketBuffer.cpp |
| PacketBuffer::deallocate_me | CG,LG,SCD,POD | consts | constant differs | - | BloodLib/source/PacketBuffer.cpp |
| PacketBufferAllocator::allocate | CG,LG,SCD,POD | refs/consts | base vtable store (novtable ❓) | constant differs | BloodLib/source/PacketBuffer.cpp |
| PacketBufferAllocator::initAllocator | CG,LG,SCD,POD | calls/refs/consts | wrong callee: memory manager | __FILE__ path differs or missing; import or indirect call differs; data ref differs; constant differs | BloodLib/source/PacketBuffer.cpp |
| PacketBufferPool::allocate | CG,LG,SCD,POD | refs/consts | base vtable store (novtable ❓) | data ref differs; constant differs | BloodLib/source/PacketBuffer.cpp |
| PacketFormatIterator::SetFormat | CG,POD | refs | __FILE__ path differs or missing | - | BloodLib/source/PacketUtil.cpp |
| PipeCommandProcess::processCommand | CG,LG,SCD,POD | consts | constant differs | - | BloodLib/source/PipeConsole.cpp |
| PipeCommandProcess::run | CG,LG,SCD,POD | calls/refs/consts | wrong callee: memory manager | wrong callee; data ref differs; constant differs | BloodLib/source/PipeConsole.cpp |
| PipeConsole::SetInvalidInfo | CG,SCD,POD | calls/refs/consts | __FILE__ path differs or missing | inlined but should not be; data ref differs; constant differs | BloodLib/source/PipeConsole.cpp |
| PipeConsole::checkFrozenThread | CG,LG,SCD,POD | calls/refs/consts | inlined but should not be | constant differs; __FILE__ path differs or missing; data ref differs | BloodLib/source/PipeConsole.cpp |
| PipeConsole::initPipe | CG,LG,SCD,POD | calls/refs/consts | __FILE__ path differs or missing | wrong callee; string ref differs; constant differs | BloodLib/source/PipeConsole.cpp |
| PipeConsole::processCommand | CG,LG,SCD,POD | consts | constant differs | - | BloodLib/source/PipeConsole.cpp |
| PipeConsole::run | CG,LG,SCD,POD | calls/refs/consts | wrong callee: memory manager | __FILE__ path differs or missing; wrong callee; string ref differs; data ref differs; constant differs | BloodLib/source/PipeConsole.cpp |
| Port::Clear | CG,LG,SCD,POD | calls/refs/consts | wrong callee: memory manager | __FILE__ path differs or missing; import or indirect call differs; data ref differs; constant differs | BloodLib/source/Port.cpp |
| Port::Initialize | CG,LG,SCD,POD | calls/refs/consts | wrong callee: memory manager | base vtable store (novtable ❓); __FILE__ path differs or missing; inlined but should not be; data ref differs; constant differs | BloodLib/source/Port.cpp |
| Port::clearPool | CG,LG,SCD,POD | consts | constant differs | - | BloodLib/source/Port.cpp |
| PortListener::Initialize | CG,LG,SCD,POD | calls/refs/consts | __FILE__ path differs or missing | wrong callee; constant differs | BloodLib/source/Listener.cpp |
| Prng::Initialize | CG,LG,SCD,POD | consts | constant differs | - | Security/source/BloodCrypto/math/prng/prng.cpp |
| Prng::setSeed | CG,LG,SCD,POD | calls/consts | wrong callee | constant differs | Security/source/BloodCrypto/math/prng/prng.cpp |
| RefCntHistory::dump | CG,LG,SCD,POD | consts | constant differs | - | BloodLib/source/RefCntObject.cpp |
| RefCntObject::addReferenceCount | CG,LG,SCD,POD | calls/refs | __FILE__ path differs or missing | call order differs | BloodLib/source/RefCntObject.cpp |
| RefCntObject::removeReferenceCount | CG,LG,SCD,POD | calls/refs | __FILE__ path differs or missing | call order differs | BloodLib/source/RefCntObject.cpp |
| RefCntObject::~RefCntObject | LG,SCD,POD | refs | __FILE__ path differs or missing | base vtable store (novtable ❓); string ref differs | BloodLib/source/RefCntObject.cpp |
| RepeatPacketComposer::PushRepeatCount | LG,POD | consts | constant differs | - | BloodLib/source/PacketUtil.cpp |
| Session::Accept | CG,LG,SCD,POD | consts | constant differs | - | BloodLib/source/Session.cpp |
| Session::Connect | CG,LG,SCD,POD | calls/refs/consts | base vtable store (novtable ❓) | call order differs; constant differs | BloodLib/source/Session.cpp |
| Session::HandleEvent | CG,LG,SCD,POD | calls/refs | __FILE__ path differs or missing | wrong callee | BloodLib/source/Session.cpp |
| Session::HandleFailedEvent | CG,LG,SCD,POD | consts | constant differs | - | BloodLib/source/Session.cpp |
| Session::SendV | CG,LG,SCD,POD | calls/consts | not inlined but should be | constant differs | BloodLib/source/Session.cpp |
| Session::Session [??0Session@@IEAA@IPEBVPacketBufferHandler@@@Z] | CG,LG,SCD,POD | refs | wrong callee: memory manager | base vtable store (novtable ❓) | BloodLib/source/Session.cpp |
| Session::Session [??0Session@@IEAA@XZ] | CG,LG,SCD,POD | refs | base vtable store (novtable ❓) | - | BloodLib/source/Session.cpp |
| Session::handlePacket | CG,LG,SCD,POD | calls | not inlined but should be | - | BloodLib/source/Session.cpp |
| Session::initialize | CG,LG,SCD | refs | data ref differs | string ref differs | BloodLib/source/Session.cpp |
| Session::recv | CG,LG,SCD,POD | consts | constant differs | - | BloodLib/source/Session.cpp |
| Session::sendNext | CG,LG,SCD,POD | calls | import or indirect call differs | - | BloodLib/source/Session.cpp |
| Session::~Session | CG,LG,SCD,POD | refs/consts | data ref differs | constant differs | BloodLib/source/Session.cpp |
| SessionPool::SessionPool | CG,LG,SCD,POD | refs | base vtable store (novtable ❓) | __FILE__ path differs or missing | BloodLib/source/Port.cpp |
| SessionPool::~SessionPool | LG,SCD,POD | refs | __FILE__ path differs or missing | - | BloodLib/source/Port.cpp |
| SessionSendBuffer::Add | CG,LG,SCD,POD | calls/consts | call order differs | constant differs | BloodLib/source/SessionBuffer.cpp |
| SessionSendBuffer::Clear | CG,LG,SCD,POD | calls/refs/consts | wrong callee: memory manager | __FILE__ path differs or missing; wrong callee; data ref differs; constant differs | BloodLib/source/SessionBuffer.cpp |
| SessionSendBuffer::Initialize | CG,LG,SCD,POD | consts | constant differs | - | BloodLib/source/SessionBuffer.cpp |
| SessionSendBuffer::RemoveSentBuffer | CG,LG,SCD,POD | calls | call order differs | - | BloodLib/source/SessionBuffer.cpp |
| SessionSendBuffer::increaseBuffer | CG,LG,SCD,POD | calls/refs/consts | wrong callee: memory manager | __FILE__ path differs or missing; import or indirect call differs; data ref differs; constant differs | BloodLib/source/SessionBuffer.cpp |
| StaticPageMemoryManager::AllocZero | LG,SCD,POD | refs | __FILE__ path differs or missing | - | BloodLib/source/MemoryManager.cpp |
| StaticPageMemoryManager::Clear | LG,SCD,POD | refs | __FILE__ path differs or missing | - | BloodLib/source/MemoryManager.cpp |
| StaticPageMemoryManager::Initialize [?Initialize@StaticPageMemoryManager@@QEAA_NPEAX_K1PEBVMemoryManager@@@Z] | CG,LG,SCD,POD | refs | ref order differs | - | BloodLib/source/MemoryManager.cpp |
| StaticPageMemoryManager::Initialize [?Initialize@StaticPageMemoryManager@@UEAA_NPEBX_K@Z] | LG,SCD,POD | refs | __FILE__ path differs or missing | - | BloodLib/source/MemoryManager.cpp |
| StaticPageMemoryManager::Realloc | LG,SCD,POD | refs | __FILE__ path differs or missing | - | BloodLib/source/MemoryManager.cpp |
| StaticPageMemoryManager::ReallocZero | LG,SCD,POD | refs | __FILE__ path differs or missing | - | BloodLib/source/MemoryManager.cpp |
| String::GetId128FromGuidString | CG,LG,SCD,POD | calls | inlined but should not be | - | BloodLib/source/StringUtil.cpp |
| SysInfo::Hostname | CG,LG,SCD,POD | consts | constant differs | - | BloodLib/source/SystemInformation.cpp |
| SysInfo::IpAddress | CG,LG,SCD,POD | calls/consts | import or indirect call differs | constant differs | BloodLib/source/SystemInformation.cpp |
| ThreadFreeFragmentPacketPump::~ThreadFreeFragmentPacketPump | LG,POD | refs | data ref differs | __FILE__ path differs or missing; string ref differs | Economy/Shared/ThreadFreePacketPump.cpp |
| ThreadFreePacketPump::~ThreadFreePacketPump | LG,POD | refs | data ref differs | __FILE__ path differs or missing; string ref differs | Economy/Shared/ThreadFreePacketPump.cpp |
| ThreadFreePacketPumpEvent::~ThreadFreePacketPumpEvent | LG,POD | refs | data ref differs | __FILE__ path differs or missing; string ref differs | Economy/Shared/ThreadFreePacketPump.cpp |
| ThreadManager::entry | CG,LG,SCD,POD | consts | constant differs | - | BloodLib/source/Thread.cpp |
| TimerQueue::Add | CG,LG,SCD,POD | calls | call order differs | - | BloodLib/source/Timer.cpp |
| TimerQueue::Remove | CG,LG,SCD,POD | calls/refs/consts | __FILE__ path differs or missing | wrong callee; constant differs | BloodLib/source/Timer.cpp |
| TimerQueue::clearShortTermQueueSlot | CG,LG,SCD,POD | calls/refs/consts | __FILE__ path differs or missing | not inlined but should be; string ref differs; data ref differs; constant differs | BloodLib/source/Timer.cpp |
| TimerQueue::~TimerQueue | LG,SCD,POD | refs | __FILE__ path differs or missing | string ref differs; data ref differs | BloodLib/source/Timer.cpp |
| TrustedPacketBufferHandler::Clone | CG,LG,SCD,POD | consts | constant differs | - | BloodLib/source/PacketBufferHandler.cpp |
| TrustedPacketBufferHandler::ToPacket | CG,LG,SCD,POD | consts | constant differs | - | BloodLib/source/PacketBufferHandler.cpp |
| WinMsgHandler::run | CG,LG,SCD,POD | calls/refs/consts | wrong callee: memory manager | wrong callee; data ref differs; constant differs | BloodLib/source/WindowConsole.cpp |
| WinMsgHandler::~WinMsgHandler | CG,LG,SCD,POD | calls/refs/consts | wrong callee: memory manager | __FILE__ path differs or missing; import or indirect call differs; data ref differs; constant differs; string ref differs | BloodLib/source/WindowConsole.cpp |
| WinServiceConsole::InstallService | CG,LG,SCD,POD | calls/refs | call order differs | data ref differs | BloodLib/source/WinServiceConsole.cpp |
| WinServiceConsole::ServiceMain | CG,LG,SCD,POD | calls/consts | inlined but should not be | constant differs | BloodLib/source/WinServiceConsole.cpp |
| WinServiceConsole::UninstallService | CG,LG,SCD,POD | calls | call count differs | - | BloodLib/source/WinServiceConsole.cpp |
| WinServiceConsole::controlHandler | CG,LG,SCD,POD | calls/refs/consts | wrong callee | string ref differs; constant differs | BloodLib/source/WinServiceConsole.cpp |
| WindowConsole::Open | CG,LG,SCD,POD | calls/refs/consts | wrong callee: memory manager | __FILE__ path differs or missing; inlined but should not be; data ref differs; constant differs | BloodLib/source/WindowConsole.cpp |
| WindowConsole::Write | CG,LG,SCD,POD | consts | constant differs | - | BloodLib/source/WindowConsole.cpp |
| WindowConsole::~WindowConsole | CG,LG,SCD,POD | calls/refs/consts | wrong callee: memory manager | __FILE__ path differs or missing; import or indirect call differs; data ref differs; constant differs | BloodLib/source/WindowConsole.cpp |
| ZSTD_BtFindBestMatch_selectMLS | CG,LG,SCD,POD | calls/consts | zstd version | - | vendor/zstd |
| ZSTD_DUBT_findBestMatch | CG,LG,SCD,POD | calls/consts | zstd version | - | vendor/zstd |
| ZSTD_HcFindBestMatch_selectMLS | CG,LG,SCD,POD | consts | zstd version | - | vendor/zstd |
| ZSTD_compressBlock_btlazy2_extDict | CG,LG,SCD,POD | calls | zstd version | - | vendor/zstd |
| ZSTD_compressBlock_btopt | CG,LG,SCD,POD | calls/refs/consts | zstd version | - | vendor/zstd |
| ZSTD_compressBlock_btopt_extDict | CG,LG,SCD,POD | calls/refs/consts | zstd version | - | vendor/zstd |
| ZSTD_compressBlock_btultra | CG,LG,SCD,POD | calls/consts | zstd version | - | vendor/zstd |
| ZSTD_compressBlock_btultra_extDict | CG,LG,SCD,POD | calls/consts | zstd version | - | vendor/zstd |
| ZSTD_compressBlock_doubleFast | CG,LG,SCD,POD | calls | zstd version | - | vendor/zstd |
| ZSTD_rescaleFreqs | CG,LG,SCD,POD | calls | zstd version | - | vendor/zstd |
| aes128TableDecrypt | CG,LG,SCD,POD | refs/consts | data ref differs | constant differs | Security/source/BloodCrypto/crypto/aes128Table.cpp |
| aes128TableEncrypt | CG,LG,SCD,POD | refs/consts | data ref differs | constant differs | Security/source/BloodCrypto/crypto/aes128Table.cpp |
| aes128TableSetupDecKey | CG,LG,SCD,POD | consts | constant differs | - | Security/source/BloodCrypto/crypto/aes128Table.cpp |
| aes128TableSetupEncKey | CG,LG,SCD,POD | refs/consts | constant differs | __FILE__ path differs or missing; data ref differs | Security/source/BloodCrypto/crypto/aes128Table.cpp |
| decrypt | CG,LG,SCD,POD | consts | constant differs | - | Security/source/BloodCrypto/crypto/blowfish.cpp |
| encrypt | CG,LG,SCD,POD | consts | constant differs | - | Security/source/BloodCrypto/crypto/blowfish.cpp |
| makeConsole | CG,LG,SCD,POD | calls/refs/consts | wrong callee: memory manager | __FILE__ path differs or missing; call count differs; data ref differs; constant differs | BloodLib/source/Daemon.cpp |
| makeDirectory | CG,LG,SCD,POD | calls | call order differs | - | BloodLib/source/CrashHandler.cpp |
| operator delete | CG,SCD,POD | calls/refs/consts | __FILE__ path differs or missing | inlined but should not be; string ref differs; constant differs | BloodLib/include/RefCntObject.h |
| wmain | CG,LG,SCD,POD | calls/refs/consts | EH state constant (-2) differs | string ref differs; data ref differs; not inlined but should be | Economy/CacheGate/CacheGate.cpp |

### Shared misses (only in original, 2 or more exes): 81 functions

| Function | Exes | Size | Cause class | Source file |
| --- | --- | --- | --- | --- |
| Aes128::~Aes128 [??1Aes128@@QEAA@XZ] | LG,SCD,POD | 61 | compiler noise (COMDAT fold: PDB name of a folded body) | Security/source/BloodCrypto/crypto/aes128.h |
| AlertSender::createSocket [?createSocket@AlertSender@@AEAA_NXZ] | CG,SCD,POD | 138 | inlined but should not be | BloodLib/source/AlertSender.cpp |
| BigInteger::Add [?Add@BigInteger@@QEAAXPEBV1@0@Z] | LG,SCD,POD | 303 | not referenced in ours (dropped or inlined) | Security/source/BloodCrypto/math/bignumber/biArithmetic.cpp |
| BigInteger::BigInteger [??0BigInteger@@QEAA@XZ] | LG,SCD,POD | 48 | inlined but should not be (header inline) | Security/source/BloodCrypto/math/bignumber/BigInteger.h |
| BigInteger::Divide [?Divide@BigInteger@@SAXPEBV1@0PEAV1@1@Z] | LG,SCD,POD | 2698 | not referenced in ours (dropped or inlined) | Security/source/BloodCrypto/math/bignumber/biArithmetic.cpp |
| BigInteger::InvMod [?InvMod@BigInteger@@QEAA_NPEBV1@0@Z] | LG,SCD,POD | 3739 | not referenced in ours (dropped or inlined) | Security/source/BloodCrypto/math/bignumber/NumberTheory.cpp |
| BigInteger::LeftShift [?LeftShift@BigInteger@@QEAAXPEBV1@H@Z] | LG,SCD,POD | 356 | not referenced in ours (dropped or inlined) | Security/source/BloodCrypto/math/bignumber/biArithmetic.cpp |
| BigInteger::Mul [?Mul@BigInteger@@QEAAXPEBV1@0@Z] | LG,SCD,POD | 407 | not referenced in ours (dropped or inlined) | Security/source/BloodCrypto/math/bignumber/biArithmetic.cpp |
| BigInteger::Pow2 [?Pow2@BigInteger@@QEAAXH@Z] | LG,SCD,POD | 122 | not referenced in ours (dropped or inlined) | Security/source/BloodCrypto/math/bignumber/biArithmetic.cpp |
| BigInteger::RightShift [?RightShift@BigInteger@@QEAAXPEBV1@H@Z] | LG,SCD,POD | 490 | not referenced in ours (dropped or inlined) | Security/source/BloodCrypto/math/bignumber/biArithmetic.cpp |
| BigInteger::Set [?Set@BigInteger@@QEAAXPEBV1@H@Z] | LG,SCD,POD | 60 | not referenced in ours (dropped or inlined) | Security/source/BloodCrypto/math/bignumber/BigInteger.cpp |
| BigInteger::Set [?Set@BigInteger@@QEAAX_J@Z] | LG,SCD,POD | 209 | not referenced in ours (dropped or inlined) | Security/source/BloodCrypto/math/bignumber/BigInteger.cpp |
| BigInteger::Set [?Set@BigInteger@@QEAA_NHPEBEH@Z] | LG,SCD,POD | 146 | not referenced in ours (dropped or inlined) | Security/source/BloodCrypto/math/bignumber/BigInteger.cpp |
| BigInteger::Sqr [?Sqr@BigInteger@@QEAAXPEBV1@@Z] | LG,SCD,POD | 347 | not referenced in ours (dropped or inlined) | Security/source/BloodCrypto/math/bignumber/biArithmetic.cpp |
| BigInteger::Sub [?Sub@BigInteger@@QEAAXPEBV1@0@Z] | LG,SCD,POD | 313 | not referenced in ours (dropped or inlined) | Security/source/BloodCrypto/math/bignumber/biArithmetic.cpp |
| BigInteger::absCompare [?absCompare@BigInteger@@CAHPEBV1@0@Z] | LG,SCD,POD | 87 | not referenced in ours (dropped or inlined) | Security/source/BloodCrypto/math/bignumber/BigInteger.cpp |
| BigInteger::add [?add@BigInteger@@AEAAXPEBV1@0H@Z] | LG,SCD,POD | 334 | not referenced in ours (dropped or inlined) | Security/source/BloodCrypto/math/bignumber/biArithmetic.cpp |
| BigInteger::expMod [?expMod@BigInteger@@AEAAXPEBV1@00@Z] | LG,SCD,POD | 1439 | not referenced in ours (dropped or inlined) | Security/source/BloodCrypto/math/bignumber/NumberTheory.cpp |
| BigInteger::invMod [?invMod@BigInteger@@AEAA_NPEBV1@0@Z] | LG,SCD,POD | 4223 | not referenced in ours (dropped or inlined) | Security/source/BloodCrypto/math/bignumber/NumberTheory.cpp |
| BigInteger::leftShiftDigit [?leftShiftDigit@BigInteger@@AEAAXPEBV1@H_N@Z] | LG,SCD,POD | 169 | not referenced in ours (dropped or inlined) | Security/source/BloodCrypto/math/bignumber/biArithmetic.cpp |
| BigInteger::montgomeryNormalize [?montgomeryNormalize@BigInteger@@AEAAXPEBV1@@Z] | LG,SCD,POD | 362 | not referenced in ours (dropped or inlined) | Security/source/BloodCrypto/math/bignumber/biMontgomery.cpp |
| BigInteger::montgomeryReduce [?montgomeryReduce@BigInteger@@AEAAXPEBV1@I@Z] | LG,SCD,POD | 510 | not referenced in ours (dropped or inlined) | Security/source/BloodCrypto/math/bignumber/biMontgomery.cpp |
| BigInteger::mul [?mul@BigInteger@@AEAAXI@Z] | LG,SCD,POD | 216 | not referenced in ours (dropped or inlined) | Security/source/BloodCrypto/math/bignumber/biMultiplication.cpp |
| BigInteger::mul [?mul@BigInteger@@CAXPEBV1@0PEAV1@@Z] | LG,SCD,POD | 604 | not referenced in ours (dropped or inlined) | Security/source/BloodCrypto/math/bignumber/biMultiplication.cpp |
| BigInteger::setBit [?setBit@BigInteger@@AEAAXH@Z] | LG,SCD,POD | 123 | not referenced in ours (dropped or inlined) | Security/source/BloodCrypto/math/bignumber/BigInteger.cpp |
| BigInteger::sqr [?sqr@BigInteger@@CAXPEBV1@PEAV1@@Z] | LG,SCD,POD | 722 | not referenced in ours (dropped or inlined) | Security/source/BloodCrypto/math/bignumber/biSqr.cpp |
| BigInteger::sub [?sub@BigInteger@@AEAAXPEBV1@0H@Z] | LG,SCD,POD | 373 | not referenced in ours (dropped or inlined) | Security/source/BloodCrypto/math/bignumber/biArithmetic.cpp |
| BigInteger::~BigInteger [??1BigInteger@@QEAA@XZ] | LG,SCD,POD | 17 | compiler noise (COMDAT fold: PDB name of a folded body) | Security/source/BloodCrypto/math/bignumber/BigInteger.h |
| Console::Flush [??3@YAXPEAX@Z] | CG,SCD,POD | 3 | compiler noise (COMDAT fold: PDB name of a folded body) | BloodLib/source/Console.cpp |
| CriticalSection::CriticalSection [??0CriticalSection@@QEAA@XZ] | LG,SCD,POD | 24 | inlined but should not be (header inline) | BloodLib/include/Lock.h |
| CryptoKey::Initialize [?Initialize@CryptoKey@@SA_NXZ] | LG,SCD,POD | 108 | inlined but should not be | Security/source/BloodCrypto/key/CryptoKey.cpp |
| DelayedRelease::Cleanup [?Cleanup@DelayedRelease@@QEAAXXZ] | CG,LG,SCD,POD | 63 | inlined but should not be | BloodLib/source/DelayedRelease.cpp |
| FSE_count_simple | CG,LG,SCD,POD | 209 | zstd version | vendor/zstd |
| Log::Flush [?Flush@Log@@SAXXZ] | CG,LG,SCD,POD | 46 | inlined but should not be | BloodLib/source/Log.cpp |
| Log::Initialize [?Initialize@Log@@SA_NXZ] | CG,LG,SCD,POD | 255 | inlined but should not be | BloodLib/source/Log.cpp |
| LogBufferAllocator::Initialize [?Initialize@LogBufferAllocator@@SAXXZ] | CG,LG,SCD,POD | 107 | inlined but should not be | BloodLib/source/LogBuffer.cpp |
| LogMedia::Add [?Add@LogMedia@@IEAAHPEAVLogBuffer@@@Z] | CG,LG,SCD,POD | 149 | inlined but should not be | BloodLib/source/LogMedia.cpp |
| MaskGenerator::generate [?generate@MaskGenerator@@AEAA_NPEBEHPEAEH@Z] | LG,SCD,POD | 350 | not referenced in ours (dropped or inlined) | Security/source/BloodCrypto/crypto/encoder/mgf.cpp |
| Memory::CreateManager [?CreateManager@Memory@@SAPEBVMemoryManager@@W4MgrType@1@PEBX_K_N@Z] | CG,LG,SCD,POD | 116 | inlined but should not be | BloodLib/source/Memory.cpp |
| OaepEncoder::Decode [?Decode@OaepEncoder@@UEBA_NPEBEHPEAEPEAH@Z] | LG,SCD,POD | 24 | not referenced in ours (dropped or inlined) | Security/source/BloodCrypto/crypto/encoder/oaep_encoder.cpp |
| OaepEncoder::Encode [?Encode@OaepEncoder@@UEBA_NPEBEHPEAEPEAHPEAXH@Z] | LG,SCD,POD | 45 | not referenced in ours (dropped or inlined) | Security/source/BloodCrypto/crypto/encoder/oaep_encoder.cpp |
| OaepEncoder::Setup [?Setup@OaepEncoder@@UEAA_NH@Z] | LG,SCD,POD | 158 | not referenced in ours (dropped or inlined) | Security/source/BloodCrypto/crypto/encoder/oaep_encoder.cpp |
| OaepEncoder::decode [?decode@OaepEncoder@@AEAA_NPEBEHPEAEPEAH@Z] | LG,SCD,POD | 525 | not referenced in ours (dropped or inlined) | Security/source/BloodCrypto/crypto/encoder/oaep_encoder.cpp |
| OaepEncoder::encode [?encode@OaepEncoder@@AEAA_NPEBEHPEAEPEAHPEAXH@Z] | LG,SCD,POD | 623 | not referenced in ours (dropped or inlined) | Security/source/BloodCrypto/crypto/encoder/oaep_encoder.cpp |
| PacketBufferAllocator::Initialize [?Initialize@PacketBufferAllocator@@SAXXZ] | CG,LG,SCD,POD | 107 | inlined but should not be | BloodLib/source/PacketBuffer.cpp |
| PortListener::Clear [?Clear@PortListener@@QEAAXXZ] | CG,LG,SCD,POD | 64 | inlined but should not be | BloodLib/source/Listener.cpp |
| Prng::Generate [?Generate@Prng@@SA_NPEAEH@Z] | LG,SCD,POD | 150 | not referenced in ours (dropped or inlined) | Security/source/BloodCrypto/math/prng/prng.cpp |
| Prng::addEntropy [?addEntropy@Prng@@AEAA_NPEBEH@Z] | CG,LG,SCD,POD | 173 | inlined but should not be | Security/source/BloodCrypto/math/prng/prng.cpp |
| RefCntObject::operator delete [??3RefCntObject@@SAXPEAXPEB_WH@Z] | CG,LG,SCD,POD | 93 | compiler noise (COMDAT fold: PDB name of a folded body) | BloodLib/source/RefCntObject.cpp |
| Ripemd128::Digest [?Digest@Ripemd128@@UEBA_NPEBEHPEAEPEAH@Z] | LG,SCD,POD | 675 | not referenced in ours (dropped or inlined) | Security/source/BloodCrypto/hash/ripemd128.cpp |
| Ripemd160::~Ripemd160 [??1Ripemd160@@QEAA@XZ] | LG,SCD,POD | 11 | compiler noise (COMDAT fold: PDB name of a folded body) | Security/source/BloodCrypto/hash/ripemd160.cpp |
| Rsa::Rsa [??0Rsa@@QEAA@XZ] | LG,SCD,POD | 328 | inlined but should not be (header inline) | Security/source/BloodCrypto/crypto/rsa.h |
| Rsa::decrypt [?decrypt@Rsa@@IEBA_NPEBVBigInteger@@PEBEHPEAEPEAH@Z] | LG,SCD,POD | 850 | not referenced in ours (dropped or inlined) | Security/source/BloodCrypto/crypto/rsa.cpp |
| Rsa::encrypt [?encrypt@Rsa@@IEBA_NPEBVBigInteger@@PEBEHPEAEPEAH@Z] | LG,SCD,POD | 882 | not referenced in ours (dropped or inlined) | Security/source/BloodCrypto/crypto/rsa.cpp |
| RsaPublic::Decrypt [?Decrypt@RsaPublic@@UEBA_NPEBEHPEAEPEAH@Z] | LG,SCD,POD | 94 | not referenced in ours (dropped or inlined) | Security/source/BloodCrypto/crypto/rsa.cpp |
| RsaPublic::Encrypt [?Encrypt@RsaPublic@@UEBA_NPEBEHPEAEPEAH@Z] | LG,SCD,POD | 94 | not referenced in ours (dropped or inlined) | Security/source/BloodCrypto/crypto/rsa.cpp |
| RsaPublic::GetType [?GetType@RsaPublic@@UEBA?AW4Type@Crypto@@XZ] | LG,SCD,POD | 6 | not referenced in ours (dropped or inlined) | Security/source/BloodCrypto/crypto/rsa.cpp |
| RsaPublic::Setup [?Setup@RsaPublic@@UEAA_NPEBEHH@Z] | LG,SCD,POD | 202 | not referenced in ours (dropped or inlined) | Security/source/BloodCrypto/crypto/rsa.cpp |
| RsaPublic::~RsaPublic [??1RsaPublic@@UEAA@XZ] | LG,SCD,POD | 163 | compiler noise (COMDAT fold: PDB name of a folded body) | Security/source/BloodCrypto/crypto/rsa.cpp |
| Session::Recv [?Recv@Session@@AEAA_NXZ] | CG,LG,SCD,POD | 60 | inlined but should not be | BloodLib/source/Session.cpp |
| SessionSendBuffer::clearPacketBufferList [?clearPacketBufferList@SessionSendBuffer@@AEAAXPEAUSendBufferList@@@Z] | CG,LG,SCD,POD | 342 | inlined but should not be | BloodLib/source/SessionBuffer.cpp |
| ThreadManager::Initialize [?Initialize@ThreadManager@@QEAA_NI@Z] | CG,LG,SCD,POD | 112 | inlined but should not be | BloodLib/source/Thread.cpp |
| ThreadManager::~ThreadManager [??1ThreadManager@@QEAA@XZ] | CG,LG,SCD,POD | 119 | compiler noise (COMDAT fold: PDB name of a folded body) | BloodLib/source/Thread.cpp |
| TimerQueue::removeShortTermQueue [?removeShortTermQueue@TimerQueue@@AEAAXPEAUSlot@1@PEAVTimer@@@Z] | CG,LG,SCD,POD | 103 | inlined but should not be | BloodLib/source/Timer.cpp |
| WinMsgHandler::WaitInit [?WaitInit@WinMsgHandler@@QEAAXXZ] | CG,LG,SCD,POD | 123 | inlined but should not be | BloodLib/source/WindowConsole.cpp |
| WinServiceConsole::reportStatusToSCManager [?reportStatusToSCManager@WinServiceConsole@@IEAA_NKKK@Z] | CG,LG,SCD,POD | 119 | inlined but should not be | BloodLib/source/WinServiceConsole.cpp |
| ZSTD_BtFindBestMatch | CG,LG,SCD,POD | 132 | zstd version | vendor/zstd |
| ZSTD_BtFindBestMatch_extDict | CG,LG,SCD,POD | 132 | zstd version | vendor/zstd |
| ZSTD_BtFindBestMatch_selectMLS_extDict | CG,LG,SCD,POD | 99 | zstd version | vendor/zstd |
| ZSTD_cpuid | CG,LG,SCD,POD | 165 | zstd version | vendor/zstd |
| ZSTD_createCCtx_advanced | CG,LG,SCD,POD | 192 | zstd version | vendor/zstd |
| i2os [?i2os@@YAXPEBEHPEAEH@Z] | LG,SCD,POD | 212 | not referenced in ours (dropped or inlined) | Security/source/BloodCrypto/crypto/encoder/oaep_encoder.cpp |
| operator delete[] [??_V@YAXPEAX0@Z] | LG,SCD,POD | 59 | missing function | - |
| os2i [?os2i@@YAXPEBEHPEAEH@Z] | LG,SCD,POD | 227 | not referenced in ours (dropped or inlined) | Security/source/BloodCrypto/crypto/encoder/oaep_encoder.cpp |
| swprintf_s<128> [??$swprintf_s@$0IA@@@YAHAEAY0IA@_WPEB_WZZ] | CG,LG,SCD,POD | 43 | inlined but should not be (CRT template) | - |
| swprintf_s<256> [??$swprintf_s@$0BAA@@@YAHAEAY0BAA@_WPEB_WZZ] | CG,LG,SCD,POD | 43 | inlined but should not be (CRT template) | - |
| swprintf_s<260> [??$swprintf_s@$0BAE@@@YAHAEAY0BAE@_WPEB_WZZ] | CG,LG,SCD,POD | 43 | inlined but should not be (CRT template) | - |
| swprintf_s<520> [??$swprintf_s@$0CAI@@@YAHAEAY0CAI@_WPEB_WZZ] | CG,LG,SCD,POD | 43 | inlined but should not be (CRT template) | - |
| swprintf_s<64> [??$swprintf_s@$0EA@@@YAHAEAY0EA@_WPEB_WZZ] | CG,LG,SCD,POD | 43 | inlined but should not be (CRT template) | - |
| swprintf_s<780> [??$swprintf_s@$0DAM@@@YAHAEAY0DAM@_WPEB_WZZ] | CG,LG,SCD,POD | 43 | inlined but should not be (CRT template) | - |
| wmain$dtor$0 | CG,LG,SCD,POD | 12 | compiler noise (EH funclet) | Economy/CacheGate/CacheGate.cpp |

### Shared, only in ours (2 or more exes): 35 functions

| Function | Exes | Size | Cause class | Source file |
| --- | --- | --- | --- | --- |
| ?dtor$0@?0???__F?_alertSender@AlertSender@@0V1@A@@YAXXZ@4HA | CG,LG,SCD,POD | 12 | compiler noise (EH funclet) | - |
| ?initMemorySection@?A0x98b17629@@YAXHPEBX@Z | CG,LG,SCD,POD | 203 | lift helper (anonymous namespace) | - |
| BIT_initDStream | CG,LG,SCD,POD | 288 | zstd version | vendor/zstd |
| BIT_reloadDStream | CG,LG,SCD,POD | 149 | zstd version | vendor/zstd |
| CryptoMode::~CryptoMode [??1CryptoMode@@UEAA@XZ] | CG,LG,SCD,POD | 11 | not inlined but should be, or extra function | Security/source/BloodCrypto/crypto/mode/ctr.h |
| Daemon::setState [?setState@Daemon@@IEAAXH@Z] | CG,LG,SCD,POD | 87 | not inlined but should be, or extra function | BloodLib/source/Daemon.cpp |
| FSE_buildDTable | CG,LG,SCD,POD | 467 | zstd version | vendor/zstd |
| FSE_decompress_usingDTable | CG,LG,SCD,POD | 2045 | zstd version | vendor/zstd |
| FSE_decompress_wksp | CG,LG,SCD,POD | 184 | zstd version | vendor/zstd |
| FSE_readNCount | CG,LG,SCD,POD | 841 | zstd version | vendor/zstd |
| HIST_count_simple | CG,LG,SCD,POD | 209 | zstd version | vendor/zstd |
| HUF_decompress4X1 | CG,LG,SCD,POD | 186 | zstd version | vendor/zstd |
| HUF_decompress4X1_usingDTable_internal | CG,LG,SCD,POD | 3088 | zstd version | vendor/zstd |
| HUF_decompress4X2 | CG,LG,SCD,POD | 186 | zstd version | vendor/zstd |
| HUF_decompress4X2_usingDTable_internal | CG,LG,SCD,POD | 4609 | zstd version | vendor/zstd |
| HUF_fillDTableX2 | CG,LG,SCD,POD | 508 | zstd version | vendor/zstd |
| HUF_fillDTableX2Level2 | CG,LG,SCD,POD | 326 | zstd version | vendor/zstd |
| HUF_readDTableX1_wksp | CG,LG,SCD,POD | 382 | zstd version | vendor/zstd |
| HUF_readDTableX2_wksp | CG,LG,SCD,POD | 646 | zstd version | vendor/zstd |
| HUF_readStats | CG,LG,SCD,POD | 437 | zstd version | vendor/zstd |
| Log::Log [??0Log@@AEAA@XZ] | CG,LG,SCD,POD | 135 | not inlined but should be, or extra function | BloodLib/include/Log.h |
| PacketCrypt::Setup [?Setup@PacketCrypt@@SA?AW4ErrCode@1@H@Z] | CG,LG,SCD,POD | 126 | not inlined but should be, or extra function | BloodLib/source/Network.cpp |
| Port::Port [??0Port@@QEAA@XZ] | CG,LG,SCD,POD | 91 | not inlined but should be, or extra function | BloodLib/include/Port.h |
| ZSTD_BtFindBestMatch_dictMatchState_selectMLS | CG,LG,SCD,POD | 554 | zstd version | vendor/zstd |
| ZSTD_BtFindBestMatch_extDict_selectMLS | CG,LG,SCD,POD | 554 | zstd version | vendor/zstd |
| ZSTD_DUBT_findBetterDictMatch | CG,LG,SCD,POD | 745 | zstd version | vendor/zstd |
| ZSTD_HcFindBestMatch_dictMatchState_selectMLS | CG,LG,SCD,POD | 2320 | zstd version | vendor/zstd |
| ZSTD_compressBlock_btlazy2_dictMatchState | CG,LG,SCD,POD | 1952 | zstd version | vendor/zstd |
| ZSTD_compressBlock_btopt_dictMatchState | CG,LG,SCD,POD | 16440 | zstd version | vendor/zstd |
| ZSTD_compressBlock_btultra_dictMatchState | CG,LG,SCD,POD | 16553 | zstd version | vendor/zstd |
| ZSTD_compressBlock_doubleFast_dictMatchState | CG,LG,SCD,POD | 8391 | zstd version | vendor/zstd |
| ZSTD_compressBlock_greedy_dictMatchState | CG,LG,SCD,POD | 1164 | zstd version | vendor/zstd |
| ZSTD_compressBlock_lazy2_dictMatchState | CG,LG,SCD,POD | 1952 | zstd version | vendor/zstd |
| ZSTD_compressBlock_lazy_dictMatchState | CG,LG,SCD,POD | 1572 | zstd version | vendor/zstd |
| ZSTD_initCCtx | CG,LG,SCD,POD | 204 | zstd version | vendor/zstd |

## CacheGate: 29 DIFF functions only in this exe (shared ones are above)

| Function | Signal | Cause class | Other causes | Source file |
| --- | --- | --- | --- | --- |
| CacheD::Initialize | calls/consts | inlined but should not be | constant differs | Economy/CacheGate/CacheD.cpp |
| CacheD::Verify | calls | call order differs | - | Economy/CacheGate/CacheD.cpp |
| CacheDChannel::PacketHandler | calls | import or indirect call differs | - | Economy/CacheGate/CacheDChannel.cpp |
| CacheDChannel::onClose | consts | constant differs | - | Economy/CacheGate/CacheDChannel.cpp |
| CacheDChannel::onConnect | calls/consts | call order differs | constant differs | Economy/CacheGate/CacheDChannel.cpp |
| CacheDChannel::~CacheDChannel | refs | string ref differs | - | Economy/CacheGate/CacheDChannel.cpp |
| CacheDList::Initialize | consts | constant differs | - | Economy/CacheGate/CacheD.cpp |
| CacheDList::LoadCachedListConfigFile | calls/refs | __FILE__ path differs or missing | inlined but should not be | Economy/CacheGate/CacheD.cpp |
| CacheDList::MakeSessionAll | calls | wrong callee | - | Economy/CacheGate/CacheD.cpp |
| CacheDList::RemoveSessionAll | calls/refs/consts | __FILE__ path differs or missing | wrong callee; data ref differs; constant differs | Economy/CacheGate/CacheD.cpp |
| CacheDList::add | calls | STL form differs | - | Economy/CacheGate/CacheD.cpp |
| CacheDList::addCacheD | calls/refs/consts | wrong callee | data ref differs; constant differs | Economy/CacheGate/CacheD.cpp |
| CacheDList::clear | calls/refs/consts | __FILE__ path differs or missing | wrong callee; data ref differs; constant differs | Economy/CacheGate/CacheD.cpp |
| CacheDList::del | calls | STL form differs | - | Economy/CacheGate/CacheD.cpp |
| CacheDList::~CacheDList | calls | STL form differs | - | Economy/CacheGate/CacheD.cpp |
| CacheGate::initNetwork | refs | string ref differs | data ref differs | Economy/CacheGate/CacheGate.cpp |
| CacheGate::~CacheGate | refs | string ref differs | data ref differs | Economy/CacheGate/CacheGate.cpp |
| ClientManager::AddSession | calls | STL form differs | - | Economy/CacheGate/ClientManager.cpp |
| ClientManager::GetSession | calls | import or indirect call differs | - | Economy/CacheGate/ClientManager.cpp |
| ClientManager::Initialize | calls | STL form differs | - | Economy/CacheGate/ClientManager.cpp |
| ClientManager::ReleaseAllSession | calls | STL form differs | - | Economy/CacheGate/ClientManager.cpp |
| ClientManager::ReleaseSession | calls | STL form differs | - | Economy/CacheGate/ClientManager.cpp |
| ClientManager::~ClientManager | calls/refs | __FILE__ path differs or missing | wrong callee; data ref differs | Economy/CacheGate/ClientManager.cpp |
| ClientSideDaemonChannel::getSession | consts | constant differs | - | BloodLib/source/Channel.cpp |
| ClientSideDaemonChannel::~ClientSideDaemonChannel | calls/refs/consts | inlined but should not be | string ref differs; data ref differs; constant differs | BloodLib/source/Channel.cpp |
| DaemonChannel::~DaemonChannel | refs | string ref differs | data ref differs | BloodLib/source/Channel.cpp |
| HandleCacheGateHello | calls/refs/consts | __FILE__ path differs or missing | call count differs; data ref differs; constant differs | Economy/CacheGate/CacheGateSessionHandler.cpp |
| HandleCacheGateHelloFail | consts | constant differs | - | Economy/CacheGate/CacheGateSessionHandler.cpp |
| Packet::Concatenate [?Concatenate@Packet@@QEAAXPEBV1@PEBVPacketConcatenateHandler@@@Z] | consts | constant differs | - | BloodLib/source/Packet.cpp |

### CacheGate: misses only in this exe: 3

| Function | RVA | Size | Cause class | Source file |
| --- | --- | --- | --- | --- |
| CacheD::TryConnect [?TryConnect@CacheD@@QEAA_NXZ] | 0x23e0 | 68 | inlined but should not be | Economy/CacheGate/CacheD.cpp |
| Packet::Concatenate [?Concatenate@Packet@@QEAAXPEBDFPEBVPacketConcatenateHandler@@@Z] | 0x7470 | 310 | not referenced in ours (dropped or inlined) | BloodLib/source/Packet.cpp |
| swprintf_s<129> [??$swprintf_s@$0IB@@@YAHAEAY0IB@_WPEB_WZZ] | 0x3b80 | 43 | inlined but should not be (CRT template) | - |

### CacheGate: only in ours, only in this exe: 2

| Function | RVA | Size | Cause class | Source file |
| --- | --- | --- | --- | --- |
| CacheD::CacheD [??0CacheD@@QEAA@XZ] | 0x10b0 | 118 | not inlined but should be, or extra function | Economy/CacheGate/CacheD.h |
| Packet::Concatenate [?Concatenate@Packet@@QEAAXPEBDGPEBVPacketConcatenateHandler@@@Z] | 0x14320 | 300 | not inlined but should be, or extra function | BloodLib/source/Packet.cpp |

## LobbyGate: 102 DIFF functions only in this exe (shared ones are above)

| Function | Signal | Cause class | Other causes | Source file |
| --- | --- | --- | --- | --- |
| AlertSender::init | refs/consts | string ref differs | data ref differs; constant differs | BloodLib/source/AlertSender.cpp |
| BroadcastCrypt::Initialize | calls/refs/consts | wrong callee: memory manager | __FILE__ path differs or missing; inlined but should not be; data ref differs; constant differs | BloodLib/source/Security.cpp |
| BroadcastCrypt::clear | calls/refs/consts | wrong callee: memory manager | __FILE__ path differs or missing; import or indirect call differs; data ref differs; constant differs | BloodLib/source/Security.cpp |
| Client::SendGetCharacterInfoListOk | calls/refs/consts | __FILE__ path differs or missing | not inlined but should be; string ref differs; data ref differs; constant differs | LobbyGate/Client.cpp |
| Client::SendGetServiceEntryListOk | calls/refs/consts | __FILE__ path differs or missing | not inlined but should be; string ref differs; data ref differs; constant differs | LobbyGate/Client.cpp |
| Client::SendListGoodsOk | calls/refs/consts | __FILE__ path differs or missing | not inlined but should be; string ref differs; data ref differs; constant differs | LobbyGate/Client.cpp |
| Client::SendListLobbyServiceItemInfoOk | calls/refs/consts | __FILE__ path differs or missing | wrong callee; string ref differs; data ref differs; constant differs | LobbyGate/Client.cpp |
| Client::SendTakeGoodsOk | calls/refs/consts | __FILE__ path differs or missing | wrong callee; string ref differs; data ref differs; constant differs | LobbyGate/Client.cpp |
| ClientManager::AddClient | calls/refs | base vtable store (novtable ❓) | STL form differs | LobbyGate/Client.cpp |
| ClientManager::BroadcastAnnounceNotify | calls/refs/consts | __FILE__ path differs or missing | wrong callee; string ref differs; constant differs | LobbyGate/Client.cpp |
| ClientManager::DisconnectAll | calls/refs | __FILE__ path differs or missing | STL form differs | LobbyGate/Client.cpp |
| ClientManager::Finalize | calls/refs/consts | __FILE__ path differs or missing | wrong callee; data ref differs; constant differs | LobbyGate/Client.cpp |
| ClientManager::RemoveClient | calls | STL form differs | - | LobbyGate/Client.cpp |
| ClientManager::broadcast | calls/refs/consts | __FILE__ path differs or missing | wrong callee; string ref differs; constant differs | LobbyGate/Client.cpp |
| ClientPacketBufferHandler::Clone | consts | constant differs | - | BloodLib/source/PacketBufferHandler.cpp |
| ClientPacketBufferHandler::ToPacket | calls/consts | inlined but should not be | constant differs | BloodLib/source/PacketBufferHandler.cpp |
| ClientSessionHandler::OnClose | calls/refs | __FILE__ path differs or missing | wrong callee | LobbyGate/Client.cpp |
| ClientSessionHandler::PacketHandler | consts | constant differs | - | LobbyGate/Client.cpp |
| ClientSessionTimerJob::HandleEvent | refs/consts | data ref differs | constant differs | LobbyGate/Client.cpp |
| ContentsRuleConfig::CheckMinMaxBoundary | refs | data ref differs | - | LobbyGate/ContentsRuleConfigDefinition.cpp |
| ContentsRuleConfig::ConvPacketElement | consts | constant differs | - | LobbyGate/ContentsRuleConfigDefinition.cpp |
| ContentsRuleConfig::LoadContentsRuleConfig | calls/refs | __FILE__ path differs or missing | not inlined but should be; data ref differs | LobbyGate/ContentsRuleConfigDefinition.cpp |
| ContentsRuleConfig::MakeListPacket | calls/refs/consts | inlined but should not be | data ref differs; constant differs | LobbyGate/ContentsRuleConfigDefinition.cpp |
| ContentsRuleConfig::UpdateAllVariable | refs/consts | data ref differs | constant differs | LobbyGate/ContentsRuleConfigDefinition.cpp |
| Daemon::Daemon | consts | constant differs | - | BloodLib/source/Daemon.cpp |
| Daemon::LoadVersion | consts | constant differs | - | BloodLib/source/Daemon.cpp |
| FragmentPacket::FragmentPacket | refs | string ref differs | data ref differs | Packet/FragmentPacket.cpp |
| FragmentPacket::StartRepeat | consts | constant differs | - | Packet/FragmentPacket.cpp |
| FragmentPacket::~FragmentPacket | calls/consts | not inlined but should be | constant differs | Packet/FragmentPacket.cpp |
| FragmentPacketConcatenater::Copy | refs | __FILE__ path differs or missing | - | Packet/FragmentPacket.cpp |
| FragmentPacketSplitter::AddBuffer | refs | __FILE__ path differs or missing | - | Packet/FragmentPacket.cpp |
| FragmentPacketSplitter::Finalize | refs | __FILE__ path differs or missing | - | Packet/FragmentPacket.cpp |
| GateKeyManager::Finalize | calls/refs/consts | __FILE__ path differs or missing | wrong callee; data ref differs; constant differs | LobbyGate/Client.cpp |
| GateKeyManager::MakeGateKey | calls/refs | wrong callee | data ref differs | LobbyGate/Client.cpp |
| GateKeyManager::RemoveGateKey | calls | STL form differs | - | LobbyGate/Client.cpp |
| HUF_compress_internal | calls/consts | zstd version | - | vendor/zstd |
| HandleLobbyGate_BypassPacket | calls | not inlined but should be | - | LobbyGate/LobbyGatePacketHandler.cpp |
| HandleLobbyGate_ContentsRuleListReq | calls | not inlined but should be | - | LobbyGate/LobbyGatePacketHandler.cpp |
| HandleLobbyGate_GetPcCafeMileageFeverTimeScheduleListReq | calls/refs/consts | call order differs | string ref differs; constant differs | LobbyGate/LobbyGatePacketHandler.cpp |
| HandleLobbyGate_GetWorldInfoListReq | calls/consts | call order differs | constant differs | LobbyGate/LobbyGatePacketHandler.cpp |
| HandleLobbyGate_HelloReq | calls/consts | not inlined but should be | constant differs | LobbyGate/LobbyGatePacketHandler.cpp |
| HandleLobbyLobbyGate_AnnounceNotify | calls/refs/consts | __FILE__ path differs or missing | call count differs; string ref differs; constant differs | LobbyGate/LobbyDPacketHandler.cpp |
| HandleLobbyLobbyGate_BypassPacket | calls/refs/consts | __FILE__ path differs or missing | not inlined but should be; string ref differs; constant differs | LobbyGate/LobbyDPacketHandler.cpp |
| HandleLobbyLobbyGate_CloseAnonymousSessionNotify | calls/refs/consts | __FILE__ path differs or missing | call count differs; string ref differs; constant differs | LobbyGate/LobbyDPacketHandler.cpp |
| HandleLobbyLobbyGate_CloseSessionNotify | calls/refs/consts | __FILE__ path differs or missing | call count differs; string ref differs; data ref differs; constant differs | LobbyGate/LobbyDPacketHandler.cpp |
| HandleLobbyLobbyGate_GetCharacterInfoListOk | calls/refs/consts | __FILE__ path differs or missing | call count differs; string ref differs; constant differs | LobbyGate/LobbyDPacketHandler.cpp |
| HandleLobbyLobbyGate_GetEnterWorldTokenOk | calls/refs/consts | __FILE__ path differs or missing | inlined but should not be; string ref differs; constant differs | LobbyGate/LobbyDPacketHandler.cpp |
| HandleLobbyLobbyGate_GetServiceEntryListOk | calls/refs/consts | __FILE__ path differs or missing | call count differs; string ref differs; constant differs | LobbyGate/LobbyDPacketHandler.cpp |
| HandleLobbyLobbyGate_HelloFail | calls/refs/consts | __FILE__ path differs or missing | wrong callee; string ref differs; constant differs | LobbyGate/LobbyDPacketHandler.cpp |
| HandleLobbyLobbyGate_HelloOk | calls/refs/consts | __FILE__ path differs or missing | wrong callee; string ref differs; data ref differs; constant differs | LobbyGate/LobbyDPacketHandler.cpp |
| HandleLobbyLobbyGate_InitSessionWithLobbyTokenFail | calls/refs/consts | __FILE__ path differs or missing | wrong callee; string ref differs; constant differs | LobbyGate/LobbyDPacketHandler.cpp |
| HandleLobbyLobbyGate_InitSessionWithLobbyTokenOk | calls/refs/consts | __FILE__ path differs or missing | inlined but should not be; string ref differs; data ref differs; constant differs | LobbyGate/LobbyDPacketHandler.cpp |
| HandleLobbyLobbyGate_InitSessionWithNPTokenFail | calls/refs/consts | __FILE__ path differs or missing | wrong callee; string ref differs; constant differs | LobbyGate/LobbyDPacketHandler.cpp |
| HandleLobbyLobbyGate_InitSessionWithNPTokenOk | calls/refs/consts | __FILE__ path differs or missing | inlined but should not be; string ref differs; data ref differs; constant differs | LobbyGate/LobbyDPacketHandler.cpp |
| HandleLobbyLobbyGate_KickNotify | calls/refs/consts | __FILE__ path differs or missing | call count differs; string ref differs; data ref differs; constant differs | LobbyGate/LobbyDPacketHandler.cpp |
| HandleLobbyLobbyGate_ListGoodsOk | calls/refs/consts | __FILE__ path differs or missing | call count differs; string ref differs; constant differs | LobbyGate/LobbyDPacketHandler.cpp |
| HandleLobbyLobbyGate_ListLobbyServiceItemInfoOk | calls/refs/consts | __FILE__ path differs or missing | call count differs; string ref differs; constant differs | LobbyGate/LobbyDPacketHandler.cpp |
| HandleLobbyLobbyGate_StartSessionWithLobbyTokenFail | calls/refs/consts | __FILE__ path differs or missing | wrong callee; string ref differs; data ref differs; constant differs | LobbyGate/LobbyDPacketHandler.cpp |
| HandleLobbyLobbyGate_StartSessionWithLobbyTokenOk | calls/refs/consts | __FILE__ path differs or missing | wrong callee; string ref differs; data ref differs; constant differs | LobbyGate/LobbyDPacketHandler.cpp |
| HandleLobbyLobbyGate_StartSessionWithNPTokenFail | calls/refs/consts | __FILE__ path differs or missing | wrong callee; string ref differs; data ref differs; constant differs | LobbyGate/LobbyDPacketHandler.cpp |
| HandleLobbyLobbyGate_StartSessionWithNPTokenOk | calls/refs/consts | __FILE__ path differs or missing | wrong callee; string ref differs; data ref differs; constant differs | LobbyGate/LobbyDPacketHandler.cpp |
| HandleLobbyLobbyGate_TakeGoodsOk | calls/refs/consts | __FILE__ path differs or missing | call count differs; string ref differs; constant differs | LobbyGate/LobbyDPacketHandler.cpp |
| HandleLobbyLobbyGate_UpdateWorldInfoListNotify | calls/refs/consts | __FILE__ path differs or missing | call count differs; string ref differs; constant differs | LobbyGate/LobbyDPacketHandler.cpp |
| IdleStateTable::Create | calls/refs | wrong callee: memory manager | __FILE__ path differs or missing; import or indirect call differs; data ref differs | BloodLib/source/IdleWatcher.cpp |
| IdleStateTable::scan | calls | call order differs | - | BloodLib/source/IdleWatcher.cpp |
| IdleWatcher::run | calls/refs/consts | wrong callee: memory manager | wrong callee; data ref differs; constant differs | BloodLib/source/IdleWatcher.cpp |
| LobbyD::Hello | calls/refs/consts | import or indirect call differs | data ref differs; constant differs | LobbyGate/LobbyDChannel.cpp |
| LobbyD::SendInitSessionWithLobbyTokenReq | calls | not inlined but should be | - | LobbyGate/LobbyDChannel.cpp |
| LobbyD::SendInitSessionWithNPTokenReq | calls | not inlined but should be | - | LobbyGate/LobbyDChannel.cpp |
| LobbyD::SendLostAnonymousConnectionNotify | calls | not inlined but should be | - | LobbyGate/LobbyDChannel.cpp |
| LobbyD::SendLostConnectionNotify | calls | not inlined but should be | - | LobbyGate/LobbyDChannel.cpp |
| LobbyD::SendStartSessionWithLobbyTokenReq | calls | not inlined but should be | - | LobbyGate/LobbyDChannel.cpp |
| LobbyD::SendStartSessionWithNPTokenReq | calls | not inlined but should be | - | LobbyGate/LobbyDChannel.cpp |
| LobbyD::hello | refs | data ref differs | - | LobbyGate/LobbyDChannel.cpp |
| LobbyDSessionHandler::OnClose | calls/refs/consts | import or indirect call differs | data ref differs; constant differs | LobbyGate/LobbyDChannel.cpp |
| LobbyDSessionHandler::OnConnect | calls/refs/consts | __FILE__ path differs or missing | call count differs; string ref differs; data ref differs; constant differs | LobbyGate/LobbyDChannel.cpp |
| LobbyGate::AddJobTimer | refs | base vtable store (novtable ❓) | data ref differs | LobbyGate/LobbyGate.cpp |
| LobbyGate::FailedEventObjectHandler | calls | import or indirect call differs | - | LobbyGate/LobbyGate.cpp |
| LobbyGate::PrintDependency | consts | constant differs | - | LobbyGate/LobbyGate.cpp |
| LobbyGate::cooldown | refs | base vtable store (novtable ❓) | - | LobbyGate/LobbyGate.cpp |
| LobbyGate::initNetwork | calls/refs | base vtable store (novtable ❓) | import or indirect call differs | LobbyGate/LobbyGate.cpp |
| LobbyGate::initialize | calls/refs/consts | inlined but should not be | data ref differs; constant differs | LobbyGate/LobbyGate.cpp |
| LobbyGate::reload | calls/refs/consts | base vtable store (novtable ❓) | __FILE__ path differs or missing; inlined but should not be; data ref differs; constant differs | LobbyGate/LobbyGate.cpp |
| LobbyGateCooldownTimer::HandleEvent | consts | constant differs | - | LobbyGate/LobbyGate.cpp |
| LobbyGateReloadInvalidRestoreTimer::restoreInvalid | refs | data ref differs | - | LobbyGate/LobbyGate.cpp |
| Network::SetMaxIdleTime | calls/refs/consts | wrong callee: memory manager | __FILE__ path differs or missing; import or indirect call differs; data ref differs; constant differs | BloodLib/source/Network.cpp |
| Packet::Copy | calls/consts | inlined but should not be | constant differs | BloodLib/source/Packet.cpp |
| PcCafeMileageFeverTimeScheduleList::Set | consts | constant differs | - | LobbyGate/PcCafeMileageFeverTimeScheduleList.cpp |
| PcCafeMileageFeverTimeScheduleListManager::SetPcCafeMileageFeverTimeScheduleList | refs | base vtable store (novtable ❓) | - | LobbyGate/PcCafeMileageFeverTimeScheduleList.cpp |
| PipeConsole::SetRunningInfo | calls/consts | call order differs | constant differs | BloodLib/source/PipeConsole.cpp |
| PipeConsole::addNode | refs | data ref differs | - | BloodLib/source/PipeConsole.cpp |
| Session::SetHandshakeParameter | calls/refs/consts | __FILE__ path differs or missing | inlined but should not be; string ref differs; constant differs | BloodLib/source/Session.cpp |
| Session::completeHandshake | consts | constant differs | - | BloodLib/source/Session.cpp |
| WorldListManager::SetWorldList | refs | base vtable store (novtable ❓) | - | LobbyGate/WorldListManager.cpp |
| ZSTD_compressBegin_internal | calls/consts | zstd version | - | vendor/zstd |
| ZSTD_compressSequences_internal | calls/consts | zstd version | - | vendor/zstd |
| ZSTD_ldm_adjustParameters | consts | zstd version | - | vendor/zstd |
| ZSTD_resetCCtx_internal | calls/consts | zstd version | - | vendor/zstd |
| ZSTD_resetCCtx_usingCDict | consts | zstd version | - | vendor/zstd |
| ZSTD_selectEncodingType | consts | zstd version | - | vendor/zstd |
| operator delete [??3@YAXPEAX0@Z] | calls/refs/consts | __FILE__ path differs or missing | inlined but should not be; string ref differs; constant differs | BloodLib/include/RefCntObject.h |
| zstdPacketCompress | consts | constant differs | - | BloodLib/source/Security.cpp |

### LobbyGate: misses only in this exe: 37

| Function | RVA | Size | Cause class | Source file |
| --- | --- | --- | --- | --- |
| BigInteger::Divide [?Divide@BigInteger@@SAXPEBV1@IPEAV1@PEAI@Z] | 0x59ab0 | 240 | not referenced in ours (dropped or inlined) | Security/source/BloodCrypto/math/bignumber/biArithmetic.cpp |
| BigInteger::ExpMod [?ExpMod@BigInteger@@QEAAXPEBV1@00@Z] | 0x570d0 | 187 | not referenced in ours (dropped or inlined) | Security/source/BloodCrypto/math/bignumber/NumberTheory.cpp |
| BigInteger::IsPrime [?IsPrime@BigInteger@@QEBA_NXZ] | 0x561a0 | 133 | not referenced in ours (dropped or inlined) | Security/source/BloodCrypto/math/bignumber/NumberTheory.cpp |
| BigInteger::isPrimeMR [?isPrimeMR@BigInteger@@CA_NPEBV1@_K@Z] | 0x57190 | 1119 | not referenced in ours (dropped or inlined) | Security/source/BloodCrypto/math/bignumber/NumberTheory.cpp |
| ClientManager::Initialize [?Initialize@ClientManager@@QEAA_NH@Z] | 0x5b90 | 270 | inlined but should not be | Economy/CacheGate/ClientManager.cpp |
| ContentsRuleConfig::Dump [?Dump@ContentsRuleConfig@@SAXXZ] | 0x8600 | 501 | inlined but should not be | LobbyGate/ContentsRuleConfigDefinition.cpp |
| Crypto::Create [?Create@Crypto@@SAPEAV1@W4Type@1@PEAXH@Z] | 0x55200 | 502 | inlined but should not be | Security/source/BloodCrypto/crypto/Crypto.cpp |
| Crypto::InstanceSize [?InstanceSize@Crypto@@SAHW4Type@1@@Z] | 0x55150 | 166 | inlined but should not be | Security/source/BloodCrypto/crypto/Crypto.cpp |
| CryptoKey::generateBigNumber [?generateBigNumber@CryptoKey@@CA_NHPEAEPEAH@Z] | 0x52750 | 205 | not referenced in ours (dropped or inlined) | Security/source/BloodCrypto/key/CryptoKey.cpp |
| CryptoKey::generatePrimeNumber [?generatePrimeNumber@CryptoKey@@CA_NHPEAEPEAH@Z] | 0x52820 | 194 | not referenced in ours (dropped or inlined) | Security/source/BloodCrypto/key/CryptoKey.cpp |
| Dh::Cleanup [?Cleanup@Dh@@UEAAXXZ] | 0x55630 | 5 | not referenced in ours (dropped or inlined) | Security/source/BloodCrypto/key/CryptoKey.cpp |
| Dh::Dh [??0Dh@@QEAA@XZ] | 0x554c0 | 191 | not referenced in ours (dropped or inlined) | Security/source/BloodCrypto/key/CryptoKey.cpp |
| Dh::GetKey [?GetKey@Dh@@UEBA_NPEAEPEAH@Z] | 0x55a00 | 432 | not referenced in ours (dropped or inlined) | Security/source/BloodCrypto/key/CryptoKey.cpp |
| Dh::Process [?Process@Dh@@UEAA_NPEBEHPEAEPEAH@Z] | 0x55980 | 118 | not referenced in ours (dropped or inlined) | Security/source/BloodCrypto/key/CryptoKey.cpp |
| Dh::Setup [?Setup@Dh@@UEAA_NH@Z] | 0x55610 | 26 | not referenced in ours (dropped or inlined) | Security/source/BloodCrypto/key/CryptoKey.cpp |
| Dh::Start [?Start@Dh@@UEAA_NPEBEHPEAEPEAH@Z] | 0x556f0 | 646 | not referenced in ours (dropped or inlined) | Security/source/BloodCrypto/key/CryptoKey.cpp |
| Dh::clear [?clear@Dh@@AEAAXXZ] | 0x55640 | 171 | not referenced in ours (dropped or inlined) | Security/source/BloodCrypto/key/CryptoKey.cpp |
| Dh::getValue [?getValue@Dh@@AEAA_NPEAEPEAH@Z] | 0x55d80 | 383 | not referenced in ours (dropped or inlined) | Security/source/BloodCrypto/key/CryptoKey.cpp |
| Dh::setupFactors [?setupFactors@Dh@@AEAA_NPEBEH@Z] | 0x55bb0 | 457 | not referenced in ours (dropped or inlined) | Security/source/BloodCrypto/key/CryptoKey.cpp |
| Dh::~Dh [??1Dh@@UEAA@XZ] | 0x555a0 | 106 | compiler noise (COMDAT fold: PDB name of a folded body) | Security/source/BloodCrypto/key/CryptoKey.cpp |
| FSE_count_parallel_wksp | 0x3eb10 | 627 | zstd version | vendor/zstd |
| FragmentPacket::FreeSize [?FreeSize@FragmentPacket@@QEAAGXZ] | 0x38a0 | 22 | inlined but should not be | Packet/FragmentPacket.cpp |
| GateKeyManager::Initialize [?Initialize@GateKeyManager@@QEAA_NH@Z] | 0x3910 | 498 | inlined but should not be | LobbyGate/Client.cpp |
| LobbyGateConfig::Dump [?Dump@LobbyGateConfig@@QEBAXXZ] | 0x13e20 | 1118 | inlined but should not be | LobbyGate/LobbyGateConfig.cpp |
| PacketConcatenateBuffer::Decompose [?Decompose@PacketConcatenateBuffer@@QEAAGPEAUVarData@1@@Z] | 0x1bce0 | 313 | not referenced in ours (dropped or inlined) | BloodLib/source/PacketUtil.cpp |
| Prng::GeneratePrime [?GeneratePrime@Prng@@SA_NHPEAVBigInteger@@@Z] | 0x5a5c0 | 451 | not referenced in ours (dropped or inlined) | Security/source/BloodCrypto/math/prng/prng.cpp |
| RsaPrivate::Decrypt [?Decrypt@RsaPrivate@@UEBA_NPEBEHPEAEPEAH@Z] | 0x536c0 | 94 | not referenced in ours (dropped or inlined) | Security/source/BloodCrypto/crypto/rsa.cpp |
| RsaPrivate::Encrypt [?Encrypt@RsaPrivate@@UEBA_NPEBEHPEAEPEAH@Z] | 0x53660 | 94 | not referenced in ours (dropped or inlined) | Security/source/BloodCrypto/crypto/rsa.cpp |
| RsaPrivate::GetType [?GetType@RsaPrivate@@UEBA?AW4Type@Crypto@@XZ] | 0x52a50 | 6 | not referenced in ours (dropped or inlined) | Security/source/BloodCrypto/crypto/rsa.cpp |
| RsaPrivate::RsaPrivate [??0RsaPrivate@@QEAA@XZ] | 0x53430 | 73 | inlined but should not be (header inline) | Security/source/BloodCrypto/crypto/rsa.h |
| RsaPrivate::Setup [?Setup@RsaPrivate@@UEAA_NPEBEHH@Z] | 0x53560 | 255 | not referenced in ours (dropped or inlined) | Security/source/BloodCrypto/crypto/rsa.cpp |
| RsaPrivate::~RsaPrivate [??1RsaPrivate@@UEAA@XZ] | 0x534a0 | 183 | compiler noise (COMDAT fold: PDB name of a folded body) | Security/source/BloodCrypto/crypto/rsa.h |
| Session::Send [?Send@Session@@QEBAXPEBVPacket@@@Z] | 0x18f00 | 92 | inlined but should not be | BloodLib/source/Session.cpp |
| Session::allocateCrypt [?allocateCrypt@Session@@AEBAPEAXW4Type@PacketCrypt@@W4Algorithm@3@@Z] | 0x19460 | 94 | inlined but should not be | BloodLib/source/Session.cpp |
| Session::deallocateCrypt [?deallocateCrypt@Session@@AEBAXPEAX@Z] | 0x194c0 | 101 | inlined but should not be | BloodLib/source/Session.cpp |
| ZSTD_sizeof_matchState | 0x2cc30 | 104 | zstd version | vendor/zstd |
| operator delete [??3@YAXPEAX@Z] | 0x126f0 | 3 | inlined but should not be (header inline) | BloodLib/include/RefCntObject.h |

### LobbyGate: only in ours, only in this exe: 21

| Function | RVA | Size | Cause class | Source file |
| --- | --- | --- | --- | --- |
| ?ReserveVar@?A0x347a5fcb@@YAXPEAVFragmentPacket@@_K@Z | 0x5da60 | 53 | lift helper (anonymous namespace) | - |
| ?acquireSendSession@?A0x2a352fe5@@YAPEAVSession@@PEAVClient@@FHH@Z | 0x4dd10 | 266 | lift helper (anonymous namespace) | - |
| ?clearDisconnectedInfo@?A0xbc9d2969@@YAXXZ | 0x534a0 | 134 | lift helper (anonymous namespace) | - |
| ?findDisconnectedNode@?A0xbc9d2969@@YAPEAUItemNode@PipeConsole@@PEAV3@@Z | 0x53440 | 94 | lift helper (anonymous namespace) | - |
| BroadcastPacketCrypt::Decrypt [?Decrypt@BroadcastPacketCrypt@@UEAA?AW4ErrCode@PacketCrypt@@PEAEHPEAHPEA_N@Z] | 0x16890 | 6 | not inlined but should be, or extra function | BloodLib/source/Security.cpp |
| BroadcastPacketCrypt::Encrypt [?Encrypt@BroadcastPacketCrypt@@UEAA?AW4ErrCode@PacketCrypt@@PEAEPEAHH_N@Z] | 0x166e0 | 425 | not inlined but should be, or extra function | BloodLib/source/Security.cpp |
| BroadcastPacketCrypt::GenerateKey [?GenerateKey@BroadcastPacketCrypt@@UEAA?AW4ErrCode@PacketCrypt@@PEAEPEAH01@Z] | 0x165a0 | 315 | not inlined but should be, or extra function | BloodLib/source/Security.cpp |
| BroadcastPacketCrypt::SetEncryptParam [?SetEncryptParam@BroadcastPacketCrypt@@UEAA?AW4ErrCode@PacketCrypt@@W4Param@3@@Z] | 0x16580 | 27 | not inlined but should be, or extra function | BloodLib/source/Security.cpp |
| BroadcastPacketCrypt::SetExternalCompressFunc [?SetExternalCompressFunc@BroadcastPacketCrypt@@UEAA?AW4ErrCode@PacketCrypt@@P6AHPEAEPEAHPEBEH2H@Z2H@Z] | 0x168a0 | 150 | not inlined but should be, or extra function | BloodLib/source/Security.cpp |
| HIST_count_parallel_wksp | 0x208e0 | 627 | zstd version | vendor/zstd |
| HIST_count_wksp | 0x20b60 | 95 | zstd version | vendor/zstd |
| HUF_readCTable | 0x20f50 | 509 | zstd version | vendor/zstd |
| LobbyDHandlerChannel | 0x55100 | 187 | not inlined but should be, or extra function | LobbyGate/LobbyDPacketHandler.cpp |
| PacketConcatenateBuffer::Decompose [?Decompose@PacketConcatenateBuffer@@QEAAHPEAUVarData@1@@Z] | 0x12420 | 298 | not inlined but should be, or extra function | BloodLib/source/PacketUtil.cpp |
| PacketCrypt::~PacketCrypt [??1PacketCrypt@@UEAA@XZ] | 0x16110 | 11 | not inlined but should be, or extra function | BloodLib/include/PacketBuffer.h |
| PipeConsole::SetInvalidInfo [?SetInvalidInfo@PipeConsole@@QEAAXPEB_W_N@Z] | 0x13ce0 | 366 | not inlined but should be, or extra function | BloodLib/source/PipeConsole.cpp |
| WorldList::~WorldList [??1WorldList@@UEAA@XZ] | 0x5e8b0 | 142 | not inlined but should be, or extra function | LobbyGate/WorldListManager.cpp |
| ZSTD_compress_insertDictionary | 0x259a0 | 186 | zstd version | vendor/zstd |
| ZSTD_loadDictionaryContent | 0x25520 | 260 | zstd version | vendor/zstd |
| ZSTD_loadZstdDictionary | 0x25630 | 869 | zstd version | vendor/zstd |
| ZSTD_updateTree | 0x36e50 | 136 | zstd version | vendor/zstd |

## SmartCouponDaemon: 93 DIFF functions only in this exe (shared ones are above)

| Function | Signal | Cause class | Other causes | Source file |
| --- | --- | --- | --- | --- |
| Channel::MakeSession | calls/consts | call order differs | constant differs | BloodLib/source/Channel.cpp |
| CouponJob::transit | calls/refs | __FILE__ path differs or missing | inlined but should not be; string ref differs | SmartCouponDaemon/CouponJob.cpp |
| Crypto::Destroy | refs | string ref differs | data ref differs | Security/source/BloodCrypto/crypto/Crypto.cpp |
| DChannelMgr::AddDaemon | calls | wrong callee | - | SmartCouponDaemon/DaemonChannel.cpp |
| DChannelMgr::CreateDaemonListXml | calls | import or indirect call differs | - | SmartCouponDaemon/DaemonChannel.cpp |
| DChannelMgr::DChannelMgr | refs | __FILE__ path differs or missing | - | SmartCouponDaemon/DaemonChannel.cpp |
| DChannelMgr::FindDaemon | calls | inlined but should not be | - | SmartCouponDaemon/DaemonChannel.cpp |
| DChannelMgr::PacketHandler | calls/consts | not inlined but should be | constant differs | SmartCouponDaemon/DaemonChannel.cpp |
| DChannelMgr::ReplaceDaemon | calls | wrong callee | - | SmartCouponDaemon/DaemonChannel.cpp |
| DChannelMgr::SetupDaemonList | calls/refs/consts | base vtable store (novtable ❓) | __FILE__ path differs or missing; call order differs; string ref differs; data ref differs; constant differs | SmartCouponDaemon/DaemonChannel.cpp |
| DChannelMgr::SetupDaemonListFromXml | calls/refs/consts | __FILE__ path differs or missing | call count differs; string ref differs; data ref differs; constant differs | SmartCouponDaemon/DaemonChannel.cpp |
| DChannelMgr::writeFileUtf8 | calls/consts | not inlined but should be | constant differs | SmartCouponDaemon/DaemonChannel.cpp |
| DChannelMgr::~DChannelMgr | calls/refs | __FILE__ path differs or missing | wrong callee; string ref differs | SmartCouponDaemon/DaemonChannel.cpp |
| EventNotiJob::EventNotiJob | refs | base vtable store (novtable ❓) | data ref differs | SmartCouponDaemon/EventNotiJob.cpp |
| EventNotiJob::Initialize | refs/consts | data ref differs | constant differs | SmartCouponDaemon/EventNotiJob.cpp |
| EventNotiJob::eventNotiReq | calls/consts | call order differs | constant differs | SmartCouponDaemon/EventNotiJob.cpp |
| EventNotiJob::eventNotiRes | calls/consts | call count differs | constant differs | SmartCouponDaemon/EventNotiJob.cpp |
| EventNotiJob::finalize | refs/consts | base vtable store (novtable ❓) | constant differs | SmartCouponDaemon/EventNotiJob.cpp |
| EventNotiJob::init | consts | constant differs | - | SmartCouponDaemon/EventNotiJob.cpp |
| EventNotiJob::work | calls/refs/consts | __FILE__ path differs or missing | wrong callee; string ref differs; constant differs | SmartCouponDaemon/EventNotiJob.cpp |
| GameEventConfig::GameEventConfig | refs | __FILE__ path differs or missing | - | Shared/CouponGameEventConfig.cpp |
| GameEventConfig::Load | calls/consts | import or indirect call differs | constant differs | Shared/CouponGameEventConfig.cpp |
| GameEventConfig::SetupGameEventListFromXml | calls/refs/consts | call count differs | data ref differs; constant differs | Shared/CouponGameEventConfig.cpp |
| GameEventConfig::addGameEventInfo | calls | STL form differs | - | Shared/CouponGameEventConfig.cpp |
| GameEventConfig::~GameEventConfig | calls/refs | __FILE__ path differs or missing | STL form differs | Shared/CouponGameEventConfig.cpp |
| GameEventLogEvent::HandleEvent | calls/refs/consts | base vtable store (novtable ❓) | call order differs; data ref differs; constant differs | SmartCouponDaemon/GameEventWorker.cpp |
| GameEventManager::GameEventManager | refs/consts | base vtable store (novtable ❓) | data ref differs; constant differs | SmartCouponDaemon/GameEventWorker.cpp |
| GameEventManager::Initialize | refs | data ref differs | - | SmartCouponDaemon/GameEventWorker.cpp |
| GameEventManager::PostGameEventLogList | calls/refs | base vtable store (novtable ❓) | call order differs; data ref differs | SmartCouponDaemon/GameEventWorker.cpp |
| GameEventWorker::run | calls/refs/consts | wrong callee: memory manager | wrong callee; data ref differs; constant differs | SmartCouponDaemon/GameEventWorker.cpp |
| HandleSmartCouponManager_HelloReq | calls/refs/consts | base vtable store (novtable ❓) | inlined but should not be; data ref differs; constant differs | SmartCouponDaemon/ManagerPacketHandler.cpp |
| HandleSmartCouponManager_LoadRetryReadyGameEventLogListReq | calls/refs/consts | __FILE__ path differs or missing | not inlined but should be; string ref differs; data ref differs; constant differs | SmartCouponDaemon/ManagerPacketHandler.cpp |
| HandleSmartCouponManager_RetryCouponPublicationReq | refs/consts | base vtable store (novtable ❓) | data ref differs; constant differs | SmartCouponDaemon/ManagerPacketHandler.cpp |
| HandleSmartCoupon_GameEventByAccountReq | calls/refs | base vtable store (novtable ❓) | __FILE__ path differs or missing; not inlined but should be; data ref differs | SmartCouponDaemon/DaemonPacketHandler.cpp |
| HandleSmartCoupon_GameEventByCharacterReq | calls/refs/consts | base vtable store (novtable ❓) | not inlined but should be; data ref differs; constant differs | SmartCouponDaemon/DaemonPacketHandler.cpp |
| HandleSmartCoupon_HelloReq | calls/refs/consts | base vtable store (novtable ❓) | inlined but should not be; string ref differs; data ref differs; constant differs | SmartCouponDaemon/DaemonPacketHandler.cpp |
| JobManager::Clear | calls/refs | __FILE__ path differs or missing | STL form differs | SmartCouponDaemon/CouponJob.cpp |
| JobManager::Execute | consts | constant differs | - | SmartCouponDaemon/CouponJob.cpp |
| JobManager::ExecuteW | consts | constant differs | - | SmartCouponDaemon/CouponJob.cpp |
| JobManager::Initialize | calls/refs/consts | __FILE__ path differs or missing | inlined but should not be; data ref differs; constant differs | SmartCouponDaemon/CouponJob.cpp |
| JobManager::add | calls | STL form differs | - | SmartCouponDaemon/CouponJob.cpp |
| JobManager::remove | calls | STL form differs | - | SmartCouponDaemon/CouponJob.cpp |
| JobManager::~JobManager | calls/refs/consts | __FILE__ path differs or missing | wrong callee; data ref differs; constant differs | SmartCouponDaemon/CouponJob.cpp |
| ManagerChannel::SendRetryCouponPublicationFail | calls/consts | call order differs | constant differs | SmartCouponDaemon/ManagerChannel.cpp |
| ManagerChannel::SendRetryCouponPublicationOk | calls/consts | call order differs | constant differs | SmartCouponDaemon/ManagerChannel.cpp |
| ManagerSessionHandler::PacketHandler | calls/consts | call order differs | constant differs | Economy/MarketDealerDaemon/ManagerChannel.cpp |
| NPChannel::Initialize | refs | base vtable store (novtable ❓) | - | Shared/NPChannel2.cpp |
| NPChannel::SendMsg | calls/refs/consts | __FILE__ path differs or missing | wrong callee; string ref differs; data ref differs; constant differs | Shared/NPChannel2.cpp |
| NPChannel::Setup | refs | string ref differs | data ref differs | Shared/NPChannel2.cpp |
| NPChannel::handlePacket | consts | constant differs | - | Shared/NPChannel2.cpp |
| NPChannel::sendInitialConnectMessage | refs/consts | string ref differs | data ref differs; constant differs | Shared/NPChannel2.cpp |
| NPChannel::~NPChannel | calls/refs | __FILE__ path differs or missing | STL form differs; string ref differs; data ref differs | Shared/NPChannel2.cpp |
| NPMsgHandleEvent::~NPMsgHandleEvent | refs | data ref differs | - | SmartCouponDaemon/NPServiceChannel.cpp |
| NPPing::HandleEvent | refs | string ref differs | data ref differs | Shared/NPChannel2.cpp |
| NPServiceChannel::SendRequestEventNoti | calls/refs | call order differs | string ref differs; data ref differs | SmartCouponDaemon/NPServiceChannel.cpp |
| NPServiceChannelCmdDispatcher | calls/refs | __FILE__ path differs or missing | inlined but should not be | SmartCouponDaemon/NPServiceChannel.cpp |
| NPServiceChannelManager::HandleMessage | refs/consts | base vtable store (novtable ❓) | constant differs | SmartCouponDaemon/NPServiceChannel.cpp |
| NPServiceChannelManager::Initialize | refs | base vtable store (novtable ❓) | - | SmartCouponDaemon/NPServiceChannel.cpp |
| NPServiceChannelManager::OnClose | calls/refs/consts | __FILE__ path differs or missing | inlined but should not be; string ref differs; constant differs | SmartCouponDaemon/NPServiceChannel.cpp |
| NPTransactionRegistry::NPTransactionRegistry | refs | __FILE__ path differs or missing | - | Shared/NPChannel2.cpp |
| NPTransactionRegistry::Register | calls/consts | STL form differs | constant differs | Shared/NPChannel2.cpp |
| NPTransactionRegistry::Release | calls | STL form differs | - | Shared/NPChannel2.cpp |
| NPTransactionRegistry::ReleaseAll | calls/refs | __FILE__ path differs or missing | STL form differs | Shared/NPChannel2.cpp |
| ObjPool::Finalize | refs | data ref differs | - | LobbyDaemon/ObjectPool.cpp |
| ObjPool::ObjPool | refs | data ref differs | - | LobbyDaemon/ObjectPool.cpp |
| ObjPoolTimer::~ObjPoolTimer | refs | __FILE__ path differs or missing | data ref differs | LobbyDaemon/ObjectPool.cpp |
| RawPacketBufferHandler::Destroy | calls | import or indirect call differs | - | BloodLib/source/PacketBufferHandler.cpp |
| RetrieveEventLogContext::AddEventLogInfo | consts | constant differs | - | SmartCouponDaemon/SmartCouponDB.cpp |
| RetrievePublicationContext::AddPublicationInfo | consts | constant differs | - | SmartCouponDaemon/SmartCouponDB.cpp |
| RetryCouponPublicationEvent::HandleEvent | calls/refs/consts | base vtable store (novtable ❓) | __FILE__ path differs or missing; inlined but should not be; constant differs | SmartCouponDaemon/GameEventWorker.cpp |
| SendPublicationEvent::HandleEvent | calls/refs | base vtable store (novtable ❓) | call order differs | SmartCouponDaemon/GameEventWorker.cpp |
| SendRetryCouponPublicationFailEvent::HandleEvent | refs/consts | data ref differs | constant differs | SmartCouponDaemon/GameEventWorker.cpp |
| SendRetryCouponPublicationOkEvent::HandleEvent | refs/consts | data ref differs | constant differs | SmartCouponDaemon/GameEventWorker.cpp |
| SessionHandler::~SessionHandler | refs | string ref differs | - | BloodLib/include/Channel.h |
| SharedChannel::Accept | refs | base vtable store (novtable ❓) | - | Shared/SharedChannel.cpp |
| SharedChannel::Connect | refs | base vtable store (novtable ❓) | - | Shared/SharedChannel.cpp |
| SharedChannel::~SharedChannel | refs | string ref differs | data ref differs | Shared/SharedChannel.cpp |
| SmartCouponDB::LoadCouponPublicationList | calls/refs/consts | __FILE__ path differs or missing | not inlined but should be; string ref differs; data ref differs; constant differs | SmartCouponDaemon/SmartCouponDB.cpp |
| SmartCouponDB::LoadGameEventLogList | calls/refs/consts | __FILE__ path differs or missing | not inlined but should be; string ref differs; data ref differs; constant differs | SmartCouponDaemon/SmartCouponDB.cpp |
| SmartCouponDB::LoadRetryReadyGameEventLogList | calls/refs/consts | __FILE__ path differs or missing | not inlined but should be; string ref differs; data ref differs; constant differs | SmartCouponDaemon/SmartCouponDB.cpp |
| SmartCouponDB::LoadSingleCouponPublication | calls/refs/consts | __FILE__ path differs or missing | not inlined but should be; string ref differs; constant differs | SmartCouponDaemon/SmartCouponDB.cpp |
| SmartCouponDB::ProcessAccountGameEventLog | calls/refs/consts | __FILE__ path differs or missing | wrong callee; string ref differs; data ref differs; constant differs | SmartCouponDaemon/SmartCouponDB.cpp |
| SmartCouponDB::ProcessCharacterGameEventLog | calls/refs/consts | __FILE__ path differs or missing | wrong callee; string ref differs; data ref differs; constant differs | SmartCouponDaemon/SmartCouponDB.cpp |
| SmartCouponDB::RegisterGameEventLog | calls/refs/consts | __FILE__ path differs or missing | wrong callee; string ref differs; data ref differs; constant differs | SmartCouponDaemon/SmartCouponDB.cpp |
| SmartCouponDB::UpdateStatusToProcessFailure | calls/refs/consts | __FILE__ path differs or missing | wrong callee; string ref differs; data ref differs; constant differs | SmartCouponDaemon/SmartCouponDB.cpp |
| SmartCouponDB::UpdateStatusToPublicationFailure | calls/refs/consts | __FILE__ path differs or missing | wrong callee; string ref differs; data ref differs; constant differs | SmartCouponDaemon/SmartCouponDB.cpp |
| SmartCouponDB::UpdateStatusToPublicationSuccess | calls/refs/consts | __FILE__ path differs or missing | wrong callee; string ref differs; data ref differs; constant differs | SmartCouponDaemon/SmartCouponDB.cpp |
| SmartCouponDaemon::initNetwork | refs | string ref differs | - | SmartCouponDaemon/SmartCouponDaemon.cpp |
| SmartCouponDaemon::initialize | calls/refs/consts | base vtable store (novtable ❓) | call order differs; data ref differs; constant differs | SmartCouponDaemon/SmartCouponDaemon.cpp |
| SmartCouponDaemon::loadUnhandledCouponPublication | refs | base vtable store (novtable ❓) | - | SmartCouponDaemon/SmartCouponDaemon.cpp |
| SmartCouponDaemon::loadUnhandledGameEventLog | calls/refs/consts | __FILE__ path differs or missing | not inlined but should be; string ref differs; data ref differs; constant differs | SmartCouponDaemon/SmartCouponDaemon.cpp |
| SmartCouponDaemon::reload | calls | call count differs | - | SmartCouponDaemon/SmartCouponDaemon.cpp |
| Timer::~Timer | refs | data ref differs | - | BloodLib/source/Session.cpp |

### SmartCouponDaemon: misses only in this exe: 4

| Function | RVA | Size | Cause class | Source file |
| --- | --- | --- | --- | --- |
| EventNotiJob::eventNotiExpire [?eventNotiExpire@EventNotiJob@@AEAA_NXZ] | 0xa9d0 | 126 | inlined but should not be | SmartCouponDaemon/EventNotiJob.cpp |
| Network::OpenPort [?OpenPort@Network@@SA_NIGHPEBVSessionHandler@@PEBVPacketBufferHandler@@I_N22@Z] | 0x1a8b0 | 617 | not referenced in ours (dropped or inlined) | BloodLib/source/Network.cpp |
| PipeConsole::addNode [?addNode@PipeConsole@@CA_NAEAUItemList@1@PEB_W1@Z] | 0x25b00 | 183 | inlined but should not be | BloodLib/source/PipeConsole.cpp |
| SmartCouponDaemon::SetManagerChannel [?SetManagerChannel@SmartCouponDaemon@@SAXPEAVManagerChannel@@@Z] | 0x14df0 | 62 | inlined but should not be | SmartCouponDaemon/SmartCouponDaemon.cpp |

### SmartCouponDaemon: only in ours, only in this exe: 1

| Function | RVA | Size | Cause class | Source file |
| --- | --- | --- | --- | --- |
| Network::OpenPort [?OpenPort@Network@@SA_NIGPEBVSessionHandler@@PEBVPacketBufferHandler@@I@Z] | 0xf2f0 | 450 | not inlined but should be, or extra function | BloodLib/source/Network.cpp |

## PostOfficeDaemon: 113 DIFF functions only in this exe (shared ones are above)

| Function | Signal | Cause class | Other causes | Source file |
| --- | --- | --- | --- | --- |
| AgentSessionHandler::OnClose | refs | string ref differs | - | Economy/MarketDealerDaemon/AgentChannel.cpp |
| AgentSessionHandler::PacketHandler | calls/consts | call order differs | constant differs | Economy/MarketDealerDaemon/AgentChannel.cpp |
| CacheGateChannel::SendFragmentRelayRequest | calls/refs/consts | __FILE__ path differs or missing | wrong callee; string ref differs; data ref differs; constant differs | Economy/PostOfficeDaemon/CacheGateChannel.cpp |
| CacheGateChannel::SendRelayRequest | calls/consts | not inlined but should be | constant differs | Economy/PostOfficeDaemon/CacheGateChannel.cpp |
| CacheGateSessionHandler::OnClose | calls/refs/consts | wrong callee | string ref differs; data ref differs; constant differs | Economy/CacheGate/CacheGateSessionHandler.cpp |
| CacheGateSessionHandler::OnConnect | refs | data ref differs | - | Economy/CacheGate/CacheGateSessionHandler.cpp |
| CacheGateSessionHandler::PacketHandler | consts | constant differs | - | Economy/CacheGate/CacheGateSessionHandler.cpp |
| CachedWatchdogManager::addCachedWatchdog | calls/refs/consts | base vtable store (novtable ❓) | __FILE__ path differs or missing; inlined but should not be; string ref differs; data ref differs; constant differs | Economy/PostOfficeDaemon/CachedWatchdog.cpp |
| CachedWatchdogManager::updateWorldList | calls/refs | __FILE__ path differs or missing | not inlined but should be; string ref differs; data ref differs | Economy/PostOfficeDaemon/CachedWatchdog.cpp |
| CheckPostCapacityRelayContext::ComposeResponsePacket | calls/consts | inlined but should not be | constant differs | Economy/PostOfficeDaemon/CheckPostCapacityRelay.cpp |
| DeliverPostRelayContext::DeliverPostRelayContext | refs | base vtable store (novtable ❓) | - | Economy/PostOfficeDaemon/DeliverPostRelay.cpp |
| DeliverPostRelayContext::initResponse | consts | constant differs | - | Economy/PostOfficeDaemon/DeliverPostRelay.cpp |
| DeliverPostRelayContext::processRelayResponse | calls/refs/consts | __FILE__ path differs or missing | wrong callee; string ref differs; data ref differs; constant differs | Economy/PostOfficeDaemon/DeliverPostRelay.cpp |
| DeliverPostRelayContext::~DeliverPostRelayContext | refs | string ref differs | data ref differs | Economy/PostOfficeDaemon/DeliverPostRelay.cpp |
| HandleCacheEconomyCheckPostCapacityFail | calls/refs/consts | __FILE__ path differs or missing | call count differs; string ref differs; data ref differs; constant differs | Economy/PostOfficeDaemon/CacheEconomyPacketHandler.cpp |
| HandleCacheEconomyCheckPostCapacityOk | calls/refs/consts | __FILE__ path differs or missing | call count differs; string ref differs; data ref differs; constant differs | Economy/PostOfficeDaemon/CacheEconomyPacketHandler.cpp |
| HandleCacheEconomyDeliverPostFail | calls/refs/consts | __FILE__ path differs or missing | call count differs; string ref differs; data ref differs; constant differs | Economy/PostOfficeDaemon/CacheEconomyPacketHandler.cpp |
| HandleCacheEconomyDeliverPostOk | calls/refs/consts | __FILE__ path differs or missing | call count differs; string ref differs; data ref differs; constant differs | Economy/PostOfficeDaemon/CacheEconomyPacketHandler.cpp |
| HandleCacheEconomyFail | refs/consts | __FILE__ path differs or missing | string ref differs; constant differs | Economy/PostOfficeDaemon/CacheEconomyPacketHandler.cpp |
| HandleCacheEconomyHelloFail | refs/consts | __FILE__ path differs or missing | string ref differs; constant differs | Economy/PostOfficeDaemon/CacheEconomyPacketHandler.cpp |
| HandleCacheEconomyHelloOk | refs/consts | __FILE__ path differs or missing | string ref differs; constant differs | Economy/PostOfficeDaemon/CacheEconomyPacketHandler.cpp |
| HandleCacheEconomyPingFail | calls/refs/consts | __FILE__ path differs or missing | call count differs; string ref differs; data ref differs; constant differs | Economy/PostOfficeDaemon/CacheEconomyPacketHandler.cpp |
| HandleCacheEconomyPingOk | calls/refs/consts | __FILE__ path differs or missing | call count differs; string ref differs; data ref differs; constant differs | Economy/PostOfficeDaemon/CacheEconomyPacketHandler.cpp |
| HandleCacheEconomyRemovePawnFail | refs/consts | __FILE__ path differs or missing | string ref differs; constant differs | Economy/PostOfficeDaemon/CacheEconomyPacketHandler.cpp |
| HandleCacheEconomyRemovePawnOk | refs/consts | __FILE__ path differs or missing | string ref differs; constant differs | Economy/PostOfficeDaemon/CacheEconomyPacketHandler.cpp |
| HandleCacheEconomyRetrieveCharacterInfoFail | calls/refs/consts | __FILE__ path differs or missing | call count differs; string ref differs; data ref differs; constant differs | Economy/PostOfficeDaemon/CacheEconomyPacketHandler.cpp |
| HandleCacheEconomyRetrieveCharacterInfoOk | calls/refs/consts | __FILE__ path differs or missing | call count differs; string ref differs; data ref differs; constant differs | Economy/PostOfficeDaemon/CacheEconomyPacketHandler.cpp |
| HandleCacheGateRelayFail | calls/refs/consts | __FILE__ path differs or missing | wrong callee; string ref differs; data ref differs; constant differs | Economy/CacheGate/CacheGateSessionHandler.cpp |
| HandleCacheGateRelayInvalid | calls/refs/consts | __FILE__ path differs or missing | wrong callee; string ref differs; data ref differs; constant differs | Economy/PostOfficeDaemon/CacheGatePacketHandler.cpp |
| HandlePostOfficeHelloReq | refs/consts | base vtable store (novtable ❓) | constant differs | Economy/PostOfficeDaemon/AgentPacketHandler.cpp |
| HandlePostOfficeManagementHelloReq | calls/consts | not inlined but should be | constant differs | Economy/PostOfficeDaemon/ManagementPacketHandler.cpp |
| HandlePostOfficeManagementLoadRetryReadyPostListReq | calls/consts | not inlined but should be | constant differs | Economy/PostOfficeDaemon/ManagementPacketHandler.cpp |
| HandlePostOfficeManagementLoadRetryReadySinglePostReq | calls/consts | not inlined but should be | constant differs | Economy/PostOfficeDaemon/ManagementPacketHandler.cpp |
| HandlePostOfficeManagementResetAllPostStatusReq | calls/consts | not inlined but should be | constant differs | Economy/PostOfficeDaemon/ManagementPacketHandler.cpp |
| HandlePostOfficeManagementResetPostStatusReq | calls/consts | not inlined but should be | constant differs | Economy/PostOfficeDaemon/ManagementPacketHandler.cpp |
| HandlePostOfficeRegisterPostReq | calls/refs/consts | call order differs | string ref differs; constant differs | Economy/PostOfficeDaemon/AgentPacketHandler.cpp |
| HandlePostOfficeServiceCheckPostCapacityReq | refs | base vtable store (novtable ❓) | string ref differs | Economy/PostOfficeDaemon/WorldPacketHandler.cpp |
| HandlePostOfficeServiceHelloReq | refs | base vtable store (novtable ❓) | - | Economy/PostOfficeDaemon/WorldPacketHandler.cpp |
| HandlePostOfficeServiceRegisterPostReq | calls/refs/consts | __FILE__ path differs or missing | call order differs; string ref differs; data ref differs; constant differs | Economy/PostOfficeDaemon/WorldPacketHandler.cpp |
| HandlePostOfficeServiceRetrieveCharacterInfoReq | calls | inlined but should not be | - | Economy/PostOfficeDaemon/WorldPacketHandler.cpp |
| ManagementSessionHandler::PacketHandler | calls/consts | not inlined but should be | constant differs | Economy/PostOfficeDaemon/ManagementSessionHandler.cpp |
| Network::OpenPort [?OpenPort@Network@@SA_NIGHPEBVSessionHandler@@PEBVPacketBufferHandler@@I_N22@Z] | calls/refs/consts | wrong callee: memory manager | __FILE__ path differs or missing; inlined but should not be; string ref differs; data ref differs; constant differs | BloodLib/source/Network.cpp |
| PacketBuffer::DecomposeText | calls/refs/consts | __FILE__ path differs or missing | inlined but should not be; string ref differs; constant differs | BloodLib/source/PacketBuffer.cpp |
| PingGenerator::sendPing | refs/consts | base vtable store (novtable ❓) | string ref differs; data ref differs; EH state constant (-2) differs | Economy/PostOfficeDaemon/PingGenerator.cpp |
| PingRelayContext::processRelayResponse | calls/refs | __FILE__ path differs or missing | inlined but should not be; string ref differs | Economy/PostOfficeDaemon/PingRelay.cpp |
| PipeCommandProcess::~PipeCommandProcess | refs | string ref differs | data ref differs | BloodLib/source/PipeConsole.cpp |
| PipeConsole::~PipeConsole | refs | string ref differs | data ref differs | BloodLib/source/PipeConsole.cpp |
| PostContext::PostContext | refs | base vtable store (novtable ❓) | - | Economy/PostOfficeDaemon/PostContext.cpp |
| PostContext::~PostContext | refs/consts | string ref differs | data ref differs; constant differs | Economy/PostOfficeDaemon/PostContext.cpp |
| PostContextManager::AddContext | calls | STL form differs | - | Economy/PostOfficeDaemon/PostContext.cpp |
| PostContextManager::GetContext | calls/refs | __FILE__ path differs or missing | inlined but should not be | Economy/PostOfficeDaemon/PostContext.cpp |
| PostContextManager::RemoveContext | calls | STL form differs | - | Economy/PostOfficeDaemon/PostContext.cpp |
| PostContextManager::initContextManager | calls/refs/consts | __FILE__ path differs or missing | inlined but should not be; data ref differs; constant differs | Economy/PostOfficeDaemon/PostContext.cpp |
| PostDeliveryEvent::PostDeliveryEvent | refs | base vtable store (novtable ❓) | - | Economy/PostOfficeDaemon/PostDeliveryEvent.cpp |
| PostDeliveryEvent::deliverPost | calls/refs/consts | __FILE__ path differs or missing | inlined but should not be; string ref differs; data ref differs; constant differs | Economy/PostOfficeDaemon/PostDeliveryEvent.cpp |
| PostDeliveryEvent::~PostDeliveryEvent | refs | data ref differs | - | Economy/PostOfficeDaemon/PostDeliveryEvent.cpp |
| PostInfo::CheckValidityPostData | refs/consts | data ref differs | constant differs | Economy/PostOfficeDaemon/PostContext.cpp |
| PostInfo::PostInfo | refs | data ref differs | - | Economy/PostOfficeDaemon/PostContext.cpp |
| PostOfficeDB::LoadPostList | calls/refs/consts | __FILE__ path differs or missing | wrong callee; string ref differs; data ref differs; constant differs | Economy/PostOfficeDaemon/PostOfficeDB.cpp |
| PostOfficeDB::LoadRetryReadyPostList | calls/refs/consts | __FILE__ path differs or missing | wrong callee; string ref differs; data ref differs; constant differs | Economy/PostOfficeDaemon/PostOfficeDB.cpp |
| PostOfficeDB::LoadRetryReadySinglePost | calls/refs/consts | __FILE__ path differs or missing | wrong callee; string ref differs; data ref differs; constant differs | Economy/PostOfficeDaemon/PostOfficeDB.cpp |
| PostOfficeDB::LoadSinglePost | calls/refs/consts | __FILE__ path differs or missing | wrong callee; string ref differs; data ref differs; constant differs | Economy/PostOfficeDaemon/PostOfficeDB.cpp |
| PostOfficeDB::RegisterPost | calls/refs/consts | __FILE__ path differs or missing | inlined but should not be; string ref differs; data ref differs; constant differs | Economy/PostOfficeDaemon/PostOfficeDB.cpp |
| PostOfficeDB::ResetAllDeliveryFailurePost | calls | inlined but should not be | - | Economy/PostOfficeDaemon/PostOfficeDB.cpp |
| PostOfficeDB::UpdateStatusToRetryReady | consts | constant differs | - | Economy/PostOfficeDaemon/PostOfficeDB.cpp |
| PostOfficeDaemon::checkCacheGateServiceState | refs | data ref differs | - | Economy/PostOfficeDaemon/PostOfficeDaemon.cpp |
| PostOfficeDaemon::initNetwork | refs | base vtable store (novtable ❓) | - | Economy/PostOfficeDaemon/PostOfficeDaemon.cpp |
| PostOfficeDaemon::initWorldConfigDependencyManager | refs | __FILE__ path differs or missing | - | Economy/PostOfficeDaemon/PostOfficeDaemon.cpp |
| PostOfficeDaemon::initialize | calls/refs/consts | __FILE__ path differs or missing | inlined but should not be; string ref differs; data ref differs; constant differs | Economy/PostOfficeDaemon/PostOfficeDaemon.cpp |
| PostOfficeDaemon::reload | refs | __FILE__ path differs or missing | - | Economy/PostOfficeDaemon/PostOfficeDaemon.cpp |
| PostOfficeDaemon::startTimer | refs | base vtable store (novtable ❓) | - | Economy/PostOfficeDaemon/PostOfficeDaemon.cpp |
| RelayContext::ProcessRelayRequest | calls/refs | not inlined but should be | data ref differs | Economy/PostOfficeDaemon/RelayContext.cpp |
| RelayContext::ProcessRelayResponse | calls/refs/consts | __FILE__ path differs or missing | not inlined but should be; string ref differs; data ref differs; constant differs | Economy/PostOfficeDaemon/RelayContext.cpp |
| RelayContext::ProcessRelayTimeout | calls/refs | __FILE__ path differs or missing | not inlined but should be; string ref differs; data ref differs | Economy/PostOfficeDaemon/RelayContext.cpp |
| RelayContext::~RelayContext | refs | string ref differs | data ref differs | Economy/PostOfficeDaemon/RelayContext.h |
| RelayContextManager::AddContext | calls | STL form differs | - | Economy/PostOfficeDaemon/RelayContext.cpp |
| RelayContextManager::GetContext | calls/refs | __FILE__ path differs or missing | inlined but should not be | Economy/PostOfficeDaemon/RelayContext.cpp |
| RelayContextManager::RemoveContext | calls | STL form differs | - | Economy/PostOfficeDaemon/RelayContext.cpp |
| RelayContextManager::initContextManager | calls/refs/consts | __FILE__ path differs or missing | inlined but should not be; data ref differs; constant differs | Economy/PostOfficeDaemon/RelayContext.cpp |
| RelayTimeContextManager::AddContext | calls | STL form differs | - | Economy/PostOfficeDaemon/RelayTimeContext.cpp |
| RelayTimeContextManager::RemoveContext | calls | STL form differs | - | Economy/PostOfficeDaemon/RelayTimeContext.cpp |
| RelayTimeContextManager::initContextManager | calls/refs/consts | __FILE__ path differs or missing | inlined but should not be; data ref differs; constant differs | Economy/PostOfficeDaemon/RelayTimeContext.cpp |
| RelayTimeoutChecker::checkRelayTimeout | consts | constant differs | - | Economy/PostOfficeDaemon/RelayTimeoutChecker.cpp |
| RelayTimeoutChecker::occurTimeoutEvent | refs | base vtable store (novtable ❓) | - | Economy/PostOfficeDaemon/RelayTimeoutChecker.cpp |
| RetrieveCharacterInfoRelayContext::ComposeResponsePacket | calls/consts | wrong callee | constant differs | Economy/PostOfficeDaemon/RetrieveCharacterInfoRelay.cpp |
| RetrieveCharacterInfoRelayContext::RetrieveCharacterInfoRelayContext | refs | base vtable store (novtable ❓) | - | Economy/PostOfficeDaemon/WorldPacketHandler.cpp |
| RetrieveCharacterInfoRelayContext::initResponse | consts | constant differs | - | Economy/PostOfficeDaemon/WorldPacketHandler.cpp |
| TFPP_PumpPacket | refs/consts | __FILE__ path differs or missing | constant differs | Economy/Shared/ThreadFreePacketPump.cpp |
| TextStreamPacketBufferHandler::Destroy | calls | import or indirect call differs | - | BloodLib/source/PacketBufferHandler.cpp |
| TextStreamPacketBufferHandler::ToBuffer | consts | constant differs | - | BloodLib/source/PacketBufferHandler.cpp |
| TextStreamPacketBufferHandler::ToPacket | calls/refs/consts | __FILE__ path differs or missing | wrong callee; string ref differs; data ref differs; constant differs | BloodLib/source/PacketBufferHandler.cpp |
| Thread::~Thread | refs | string ref differs | data ref differs | BloodLib/source/Thread.cpp |
| ThreadFreeFragmentPacketPump::HandleEvent | refs | __FILE__ path differs or missing | - | Economy/Shared/ThreadFreePacketPump.cpp |
| ThreadFreeFragmentPacketPump::Initialize | refs | __FILE__ path differs or missing | - | Economy/Shared/ThreadFreePacketPump.cpp |
| ThreadFreePacketPump::HandleEvent | refs | __FILE__ path differs or missing | - | Economy/Shared/ThreadFreePacketPump.cpp |
| ThreadFreePacketPump::Initialize | refs | __FILE__ path differs or missing | - | Economy/Shared/ThreadFreePacketPump.cpp |
| ThreadFreePacketPumpEvent::initialize | refs | __FILE__ path differs or missing | - | Economy/Shared/ThreadFreePacketPump.cpp |
| UnsentPostContextManager::addUnsentPostContextList | consts | EH state constant (-2) differs | - | Economy/PostOfficeDaemon/UnsentPostContext.cpp |
| UnsentPostContextManager::deliverUnsentPost | calls | call order differs | - | Economy/PostOfficeDaemon/UnsentPostContext.cpp |
| UnsentPostContextManager::initContextManager | calls/refs | __FILE__ path differs or missing | not inlined but should be; string ref differs; data ref differs | Economy/PostOfficeDaemon/UnsentPostContext.cpp |
| UnsentPostContextManager::updateWorldList | calls/refs | __FILE__ path differs or missing | not inlined but should be; string ref differs; data ref differs | Economy/PostOfficeDaemon/UnsentPostContext.cpp |
| WorldChannel::SendRelayResponse | calls/consts | not inlined but should be | constant differs | Economy/PostOfficeDaemon/WorldChannel.cpp |
| WorldChannelManager::AddWorldChannel | calls | STL form differs | - | Economy/PostOfficeDaemon/WorldChannel.cpp |
| WorldChannelManager::GetWorldChannel | calls/consts | call count differs | constant differs | Economy/PostOfficeDaemon/WorldChannel.cpp |
| WorldChannelManager::RemoveWorldChannel | calls | STL form differs | - | Economy/PostOfficeDaemon/WorldChannel.cpp |
| WorldChannelManager::initChannelManager | calls/refs/consts | __FILE__ path differs or missing | inlined but should not be; data ref differs; constant differs | Economy/PostOfficeDaemon/WorldChannel.cpp |
| WorldConfigList::~WorldConfigList | calls/refs | __FILE__ path differs or missing | STL form differs | Economy/PostOfficeDaemon/WorldConfigManager.cpp |
| WorldConfigManager::loadWorldConfigFile | calls | call count differs | - | Economy/PostOfficeDaemon/WorldConfigManager.cpp |
| WorldConfigManager::setupWorldConfigList | calls/refs | STL form differs | string ref differs | Economy/PostOfficeDaemon/WorldConfigManager.cpp |
| WorldConfigManager::updateWorldList | calls/refs/consts | __FILE__ path differs or missing | wrong callee; string ref differs; data ref differs; constant differs | Economy/PostOfficeDaemon/WorldConfigManager.cpp |
| WorldSessionHandler::PacketHandler | calls/consts | call order differs | constant differs | Economy/PostOfficeDaemon/WorldChannel.cpp |
| parseDecInt | consts | constant differs | - | BloodLib/source/PacketBuffer.cpp |
| parseHexInt | consts | constant differs | - | BloodLib/source/PacketBuffer.cpp |

### PostOfficeDaemon: misses only in this exe: 25

| Function | RVA | Size | Cause class | Source file |
| --- | --- | --- | --- | --- |
| AttachedItemContext::operator= [??4AttachedItemContext@@QEAAAEAV0@AEBVAttachedItemInfo@@@Z] | 0x110e0 | 87 | compiler noise (COMDAT fold: PDB name of a folded body) | Economy/PostOfficeDaemon/PostContext.cpp |
| CacheGateChannel::combineFragmentRelayFormat [?combineFragmentRelayFormat@CacheGateChannel@@AEAA_NQEAD_KQEBD@Z] | 0x7410 | 398 | inlined but should not be | Economy/PostOfficeDaemon/CacheGateChannel.cpp |
| CacheGateChannel::composeRelayHeader [?composeRelayHeader@CacheGateChannel@@AEAA_NAEAVFragmentPacket@@AEBVRelayHeader@@@Z] | 0x7670 | 195 | inlined but should not be | Economy/PostOfficeDaemon/CacheGateChannel.cpp |
| CachedWatchdog::CachedWatchdog [??0CachedWatchdog@@AEAA@G@Z] | 0x3d20 | 154 | inlined but should not be | Economy/PostOfficeDaemon/CachedWatchdog.cpp |
| Channel::Send [?Send@Channel@@QEAA_NPEBVPacket@@@Z] | 0x2c160 | 115 | inlined but should not be | BloodLib/source/Channel.cpp |
| CheckPostCapacityRelayContext::convertFailReason [?convertFailReason@CheckPostCapacityRelayContext@@AEBA?BFW4ResultState@RelayResponse@@F@Z] | 0x9740 | 139 | inlined but should not be | Economy/PostOfficeDaemon/CheckPostCapacityRelay.cpp |
| DaemonConfig::Dump [?Dump@DaemonConfig@@SAXPEB_WPEBXPEBUXmlCfgDef@@H@Z] | 0x282d0 | 644 | inlined but should not be | BloodLib/source/DaemonConfig.cpp |
| FragmentPacket::~FragmentPacket [??1FragmentPacket@@QEAA@XZ] | 0x1370 | 9 | compiler noise (COMDAT fold: PDB name of a folded body) | Packet/FragmentPacket.cpp |
| FragmentPacketSplitter::AddBuffer [?AddBuffer@FragmentPacketSplitter@@MEAA_NPEBUHeader@Packet@@PEAU23@@Z] | 0x11d0 | 278 | not referenced in ours (dropped or inlined) | Packet/FragmentPacket.cpp |
| FragmentPacketSplitter::Clear [?Clear@FragmentPacketSplitter@@MEAAXXZ] | 0x1360 | 11 | not referenced in ours (dropped or inlined) | Packet/FragmentPacket.cpp |
| FragmentPacketSplitter::Finalize [?Finalize@FragmentPacketSplitter@@MEAA_NPEBUHeader@Packet@@@Z] | 0x12f0 | 112 | not referenced in ours (dropped or inlined) | Packet/FragmentPacket.cpp |
| GrowingBuffer::Add [?Add@GrowingBuffer@@QEAAX_K@Z] | 0x29750 | 134 | inlined but should not be | BloodLib/source/Memory.cpp |
| GrowingBuffer::grow [?grow@GrowingBuffer@@AEAAX_K@Z] | 0x297e0 | 121 | inlined but should not be | BloodLib/source/Memory.cpp |
| Packet::Decompose [?Decompose@Packet@@QEBAGIHPEBDZZ] | 0x220d0 | 173 | not referenced in ours (dropped or inlined) | BloodLib/source/Packet.cpp |
| Packet::GetFreeBody [?GetFreeBody@Packet@@QEAAPEBDXZ] | 0x21720 | 22 | inlined but should not be (header inline) | BloodLib/include/Packet.h |
| PostOfficeDB::UpdateStatusToDeliveryFailure [?UpdateStatusToDeliveryFailure@PostOfficeDB@@SA?B_NAEAH_J@Z] | 0x17e00 | 522 | inlined but should not be | Economy/PostOfficeDaemon/PostOfficeDB.cpp |
| PostOfficeDB::UpdateStatusToDeliverySuccess [?UpdateStatusToDeliverySuccess@PostOfficeDB@@SA?B_NAEAH_J@Z] | 0x17bf0 | 522 | inlined but should not be | Economy/PostOfficeDaemon/PostOfficeDB.cpp |
| RepeatPacketComposer::Allocated [?Allocated@RepeatPacketComposer@@UEAAXPEAVPacket@@PEBD@Z] | 0x22900 | 129 | not referenced in ours (dropped or inlined) | BloodLib/source/PacketUtil.cpp |
| RepeatPacketComposer::CurrentFormat [?CurrentFormat@RepeatPacketComposer@@UEBAPEBDXZ] | 0x22860 | 148 | not referenced in ours (dropped or inlined) | BloodLib/source/PacketUtil.cpp |
| RepeatPacketComposer::Forward [?Forward@RepeatPacketComposer@@UEAAXH@Z] | 0x1190 | 24 | not referenced in ours (dropped or inlined) | BloodLib/source/PacketUtil.cpp |
| RepeatPacketComposer::Reset [?Reset@RepeatPacketComposer@@UEAAXXZ] | 0x1170 | 25 | not referenced in ours (dropped or inlined) | BloodLib/source/PacketUtil.cpp |
| RepeatPacketComposer::Rewind [?Rewind@RepeatPacketComposer@@UEAAXH@Z] | 0x11b0 | 24 | not referenced in ours (dropped or inlined) | BloodLib/source/PacketUtil.cpp |
| RepeatPacketComposer::skipRepeatFormat [?skipRepeatFormat@RepeatPacketComposer@@MEAAXXZ] | 0x22990 | 318 | not referenced in ours (dropped or inlined) | BloodLib/source/PacketUtil.cpp |
| RetrieveCharacterInfoRelayContext::convertFailReason [?convertFailReason@RetrieveCharacterInfoRelayContext@@AEBA?BFW4ResultState@RelayResponse@@F@Z] | 0x1e410 | 124 | inlined but should not be | Economy/PostOfficeDaemon/RetrieveCharacterInfoRelay.cpp |
| parseString [?parseString@@YAHPEB_W0PEA_WF@Z] | 0x2fa20 | 131 | inlined but should not be | BloodLib/source/PacketBuffer.cpp |

### PostOfficeDaemon: only in ours, only in this exe: 11

| Function | RVA | Size | Cause class | Source file |
| --- | --- | --- | --- | --- |
| ?BindPostColumns@?A0xb052ce63@@YA_NPEAVDbTransaction@@AEAVPostInfo@@PEAVAttachedItemInfo@@PEA_KPEAY06_K@Z | 0x50480 | 1194 | lift helper (anonymous namespace) | - |
| ?MakePostContext@?A0xb052ce63@@YAPEAVPostContext@@AEBVPostInfo@@PEAVAttachedItemInfo@@PEAY06_KHH@Z | 0x50930 | 397 | lift helper (anonymous namespace) | - |
| ?UpdatePostStatus@?A0xb052ce63@@YA_NPEAH_JPEB_W2HHHH@Z | 0x520a0 | 509 | lift helper (anonymous namespace) | - |
| ?logEnd@?A0x705eab38@@YAXPEB_WH@Z | 0x46e60 | 53 | lift helper (anonymous namespace) | - |
| ?notSupported@?A0x705eab38@@YA_NPEB_WH@Z | 0x47070 | 155 | lift helper (anonymous namespace) | - |
| ?processEconomyResponse@?A0x705eab38@@YA_NPEB_WAEBVEconomyHeader@@QEAVRelayResponse@@0AEBUResponseLines@1@@Z | 0x46ea0 | 453 | lift helper (anonymous namespace) | - |
| liftArrayNew<AttachedItemContext> [??$liftArrayNew@VAttachedItemContext@@@@YAPEAVAttachedItemContext@@HPEB_WH@Z] | 0x5f590 | 134 | not inlined but should be, or extra function | Economy/PostOfficeDaemon/RelayContext.h |
| liftArrayNew<std::map<CompoundKey,RelayTimeContext * __ptr64,std::less<CompoundKey>,StlAllocator<std::pair<CompoundKey const,RelayTimeContext * __ptr64>,2> > > [??$liftArrayNew@V?$map@VCompoundKey@@PEAVRelayTimeContext@@U?$less@VCompoundKey@@@std@@V?$StlAllocator@U?$pair@$$CBVCompoundKey@@PEAVRelayTimeContext@@@std@@$01@@@std@@@@YAPEAV?$map@VCompoundKey@@PEAVRelayTimeContext@@U?$less@VCompoundKey@@@std@@V?$StlAllocator@U?$pair@$$CBVCompoundKey@@PEAVRelayTimeContext@@@std@@$01@@@std@@HPEB_WH@Z] | 0x57a10 | 223 | not inlined but should be, or extra function | Economy/PostOfficeDaemon/RelayContext.h |
| liftArrayNew<std::map<__int64,PostContext * __ptr64,std::less<__int64>,StlAllocator<std::pair<__int64 const,PostContext * __ptr64>,2> > > [??$liftArrayNew@V?$map@_JPEAVPostContext@@U?$less@_J@std@@V?$StlAllocator@U?$pair@$$CB_JPEAVPostContext@@@std@@$01@@@std@@@@YAPEAV?$map@_JPEAVPostContext@@U?$less@_J@std@@V?$StlAllocator@U?$pair@$$CB_JPEAVPostContext@@@std@@$01@@@std@@HPEB_WH@Z] | 0x4fb60 | 223 | not inlined but should be, or extra function | Economy/PostOfficeDaemon/RelayContext.h |
| liftArrayNew<std::map<unsigned __int64,RelayContext * __ptr64,std::less<unsigned __int64>,StlAllocator<std::pair<unsigned __int64 const,RelayContext * __ptr64>,2> > > [??$liftArrayNew@V?$map@_KPEAVRelayContext@@U?$less@_K@std@@V?$StlAllocator@U?$pair@$$CB_KPEAVRelayContext@@@std@@$01@@@std@@@@YAPEAV?$map@_KPEAVRelayContext@@U?$less@_K@std@@V?$StlAllocator@U?$pair@$$CB_KPEAVRelayContext@@@std@@$01@@@std@@HPEB_WH@Z] | 0x56c00 | 223 | not inlined but should be, or extra function | Economy/PostOfficeDaemon/RelayContext.h |
| liftArrayNew<std::map<unsigned short,WorldChannel * __ptr64,std::less<unsigned short>,StlAllocator<std::pair<unsigned short const,WorldChannel * __ptr64>,2> > > [??$liftArrayNew@V?$map@GPEAVWorldChannel@@U?$less@G@std@@V?$StlAllocator@U?$pair@$$CBGPEAVWorldChannel@@@std@@$01@@@std@@@@YAPEAV?$map@GPEAVWorldChannel@@U?$less@G@std@@V?$StlAllocator@U?$pair@$$CBGPEAVWorldChannel@@@std@@$01@@@std@@HPEB_WH@Z] | 0x5b3f0 | 223 | not inlined but should be, or extra function | Economy/PostOfficeDaemon/RelayContext.h |
