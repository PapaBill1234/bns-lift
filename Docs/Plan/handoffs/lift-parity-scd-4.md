# Handoff: lift-parity-scd-4

Card: SCD DB loaders, DChannelMgr, EventNotiJob, handlers. Goal: SCD 90 % (603 MATCH). Result: goal met.

## Counts (tools/parity.sh)

| Exe | Baseline | End | Change | MATCH lost |
| --- | ---: | ---: | ---: | ---: |
| CacheGate | 448/491 | 448/491 = 91.2 % | +0 | 0 |
| LobbyGate | 627/739 | 627/739 = 84.8 % | +0 | 0 |
| SmartCouponDaemon | 582/669 | 608/669 = 90.9 % | +26 | 0 |
| PostOfficeDaemon | 665/759 | 665/759 = 87.6 % | +0 | 0 |

## Commits

| Commit | Gain | Change |
| --- | ---: | --- |
| f4ba49f | +6 | DChannelMgr |
| 93296be | +5 | Handlers and contexts |
| 3f572fa | +6 | do-while DB loaders, int params |
| 4a4f013 | +2 | loadUnhandledGameEventLog count local, CouponJob::transit else-if, retry failReason char |
| a7addcc | +2 | GameEventLogEvent::HandleEvent switch + posted info copy; NPTransactionRegistry::Register |
| 9252396 (repair 2) | +5 | EventNotiJob Initialize, eventNotiReq, eventNotiRes; NPServiceChannelCmdDispatcher; GameEventConfig::Load |

## DIFF functions left (SCD, 59)

Tries = tries in this card. "Out of scope" = not in the card list (crypto, BloodLib, shared Network or Session code).

| Function | Score | Signal | Cause | Why stopped |
| --- | ---: | --- | --- | --- |
| wmain | 66.7 | consts | Not analysed | Card rule: do not change |
| aes128TableDecrypt | 70.0 | refs,consts | Not analysed | Out of scope, 0 tries |
| aes128TableEncrypt | 70.0 | refs,consts | Not analysed | Out of scope, 0 tries |
| BigInteger::Divide | 76.7 | calls,refs,consts | Not analysed | Out of scope, 0 tries |
| RsaPublic::~RsaPublic | 80.0 | refs | Not analysed | Out of scope, 0 tries |
| BigInteger::invMod | 83.1 | calls,consts | Not analysed | Out of scope, 0 tries |
| BigInteger::Mul | 83.3 | consts | Not analysed | Out of scope, 0 tries |
| IoWorker::run | 84.9 | calls,refs,consts | tls: ref differs (lessons D) | Out of scope, 0 tries |
| SessionSendBuffer::clearPacketBufferList | 84.9 | calls,refs,consts | Not analysed | Out of scope, 0 tries |
| OaepEncoder::decode | 87.5 | calls | Not analysed | Out of scope, 0 tries |
| BigInteger::Sqr | 88.0 | calls,consts | Not analysed | Out of scope, 0 tries |
| JobManager::Execute | 88.9 | consts | Not analysed | Card stop list |
| ThreadManager::Initialize | 88.9 | consts | Not analysed | Out of scope, 0 tries |
| aes128TableSetupEncKey | 88.9 | consts | Not analysed | Out of scope, 0 tries |
| BigInteger::InvMod | 89.7 | calls,consts | Not analysed | Out of scope, 0 tries |
| NPChannel::SendMsg | 90.1 | calls,refs,consts | The orig has an inlined Packet assert | 0 tries |
| Network::OpenPort | 90.1 | calls,refs,consts | Not analysed | Out of scope, 0 tries |
| RsaPublic::Setup | 90.2 | consts | Not analysed | Out of scope, 0 tries |
| OaepEncoder::Setup | 90.3 | calls,consts | Not analysed | Out of scope, 0 tries |
| BigInteger::mul (static) | 90.9 | consts | Not analysed | Out of scope, 0 tries |
| Rsa::decrypt | 91.7 | calls,refs | Not analysed | Out of scope, 0 tries |
| aes128TableSetupDecKey | 91.7 | consts | Not analysed | Out of scope, 0 tries |
| NPServiceChannelManager::HandleMessage | 92.3 | consts | Not analysed | Card rule: do not change |
| HandleSmartCoupon_GameEventByAccountReq | 93.0 | calls,refs | The orig puts the decompose-fail Send/Log 327 path at the end and has extra code order that a goto form does not give | 3 tries (93.9, 95.2, 95.2), no MATCH |
| EventNotiJob::finalize | 93.3 | consts | Not analysed | Card stop list |
| JobManager::ExecuteW | 93.3 | consts | Not analysed | Card stop list |
| RawPacketBufferHandler::Destroy | 93.3 | calls | Not analysed | Out of scope, 0 tries |
| SmartCouponDaemon::initialize | 95.1 | calls,refs,consts | The orig exe has a patched-out cert-decode call (NOPs at 0x151D4, 0x15256); dsn[0x400] and the memsets exist only through it | Blocked, 0 tries |
| BigInteger::sub | 95.2 | consts | Not analysed | Out of scope, 0 tries |
| NPServiceChannel::SendRequestEventNoti | 95.2 | calls | `<indirect>` call order before sprintf_s | 0 tries |
| Session::Session | 95.2 | refs | Not analysed | Out of scope, 0 tries |
| WindowConsole::Open | 95.2 | consts | Not analysed | Out of scope, 0 tries |
| OaepEncoder::encode | 96.0 | calls | Not analysed | Out of scope, 0 tries |
| HandleSmartCoupon_HelloReq | 96.1 | calls,refs,consts | Our Send sites are tail-merged; the orig keeps consts in r15/r14 | 1 try, no gain |
| BigInteger::mul (member) | 96.3 | consts | Not analysed | Out of scope, 0 tries |
| Daemon::Start | 96.3 | consts | Not analysed | Out of scope, 0 tries |
| ManagerChannel::SendRetryCouponPublicationOk | 96.3 | consts | Register allocation, const 0x71 | 1 try, no gain |
| PacketBuffer::Compose | 96.3 | calls | Not analysed | Out of scope, 0 tries |
| PipeCommandProcess::processCommand | 96.3 | consts | Not analysed | Out of scope, 0 tries |
| PipeConsole::SetInvalidInfo | 96.3 | calls | Not analysed | Out of scope, 0 tries |
| PipeConsole::run | 96.3 | calls | Not analysed | Out of scope, 0 tries |
| StaticPageMemoryManager::Initialize | 96.3 | refs | Not analysed | Out of scope, 0 tries |
| PipeConsole::processCommand | 97.0 | consts | Not analysed | Out of scope, 0 tries |
| Session::HandleFailedEvent | 97.0 | consts | Not analysed | Out of scope, 0 tries |
| Network::Clear | 97.2 | refs,consts | Not analysed | Out of scope, 0 tries |
| RetryCouponPublicationEvent::HandleEvent | 97.5 | calls,refs | Our fail removeRef(470) is tail-merged; the orig success Log reads ev after the post (BUG, not ported), which keeps r12 live | 2 tries, stopped (needs the bug) |
| Session::Connect | 97.8 | consts | Not analysed | Out of scope, 0 tries |
| DaemonConfig::Dump | 97.9 | refs | Not analysed | Out of scope, 0 tries |
| InitSymbol | 98.0 | calls | Not analysed | Out of scope, 0 tries |
| BigInteger::expMod | 98.2 | calls | Not analysed | Out of scope, 0 tries |
| Session::HandleEvent | 98.5 | calls,refs | Not analysed | Out of scope, 0 tries |
| BnsCommonConfig::ReloadBnsCommonConfig | 98.9 | refs | Not analysed | Out of scope, 0 tries |
| ObjPool::Finalize | 99.0 | refs | Not analysed | Out of scope, 0 tries |
| ObjPool::ObjPool | 99.0 | refs | Not analysed | Out of scope, 0 tries |
| BnsCommonConfig::LoadBnsCommonConfig | 99.1 | refs | Not analysed | Out of scope, 0 tries |
| HandleSmartCoupon_GameEventByCharacterReq | 99.1 | consts | Register allocation (rbx zero, `lea r8d,[rbx+0x7b]`) | 0 tries |
| PacketBuffer::Decompose | 99.2 | consts | Not analysed | Out of scope, 0 tries |
| WinServiceConsole::UninstallService | 99.5 | calls | Not analysed | Out of scope, 0 tries |
| GameEventConfig::SetupGameEventListFromXml | 99.7 | calls | The orig 137 block (0x3144) calls NextElement itself and jumps to the loop test (0x31b2). The other paths share the call at 0x31a9. VS2010 merges our 2 call sites into 1 | 4 tries (block order + inline wcslen 99.x; while loop: unrolled; pointer-step loop 99.7; `continue` in the 137 block 99.7), kept 99.7 |

## Fixed in repair 2 (were "Not analysed")

| Function | Before | After | Cause and fix |
| --- | ---: | --- | --- |
| EventNotiJob::Initialize | 77.8 | MATCH | Orig 0x9AE0 compares the GUID with the ID128_GUID_ZERO global and tests the job pointer for the log args (log macro form) |
| EventNotiJob::eventNotiReq | 92.8 | MATCH | Orig 0xA0E0 puts the unsent block (178) before the ok block (182); job pointer test in the log args |
| EventNotiJob::eventNotiRes | 89.0 | MATCH | Orig 0xA310 tests err as a switch, calls GetCommand again for the 270 log and puts the 270 block first |
| NPServiceChannelCmdDispatcher | 94.3 | MATCH | Orig 0xFD80 puts the not-found block (34) before the cmd store. 2 tries: nested ifs (80.3, reverted), inverted Find test (MATCH) |
| GameEventConfig::Load | 89.2 | MATCH | Orig 0x3430: `wchar_t file[260] = {0}` (memset 0x206) and the fail block before `return true` (no shared console tail) |

## Shared files changed (not in the card Files list)

Each change was checked with tools/parity.sh on all 4 exes: CG 448 -> 448, LG 627 -> 627, POD 665 -> 665, MATCH -> DIFF 0 in each exe.

| File | Change | Reason | Source |
| --- | --- | --- | --- |
| src/Server/BloodLib/include/Db.h, source/Db.cpp | DbTransaction::BindCol takes `int index` and `int varType` (was unsigned int) | The PDB symbol has int. VS2010 then forms the index from varType (`lea edx,[r9+0xd]`) as the orig does. Callers in SCD DB loaders MATCH | SCD PDB S_REGREL32; SCD 0x13c19; 2019 + PDB |
| src/Server/Shared/NPChannel2.cpp | NPTransactionRegistry::Register: Alloc line 134 -> 131; `for (;;)` seed loop; `if (id != nullptr)` before the store; one `return inserted;` | Line 131 is the orig value. The loop and the single return give the orig register use (result in bl, `add rbx,0x10`). The null test of id is in the orig | SCD 0x1400046f2 `mov r9d,0x83` in Register 0x4690; HR NPChannel2.c; 2019 + PDB |
| src/Server/Shared/CouponGameEventConfig.cpp | Load: `= {0}` and fail block order. SetupGameEventListFromXml: inline wcslen, block order (64, 137, 178, 186 blocks last), pointer-step daemon-type loop | Source form for the orig codegen. The behaviour does not change: same tests, same logs, same return values | SCD 0x3430, 0x2c80; 2019 + PDB |
| src/Server/SmartCouponDaemon/GameEventWorker.cpp (card file) | `// LIFT: 0xb6e0` comment on `PublicationInfo const posted = *info;` | The copy is a source-form change for the const 0x16. It does not change the behaviour. The `// BUG: 0xbc19` note stays | SCD 0xb6e0 |

Docs/Parity/lessons.md: the posted-copy row now says "codegen only; main already logged from info, not from ev".

## Fixed in repair 3 (skeptic findings)

| Finding | Fix | Source |
| --- | --- | --- |
| lessons.md said 582 -> 603 (+21) | Now 582 -> 608 (+26) | tools/parity.sh |
| LIFT address 0x10a97 in AddPublicationInfo | Now 0x10971. 0x10a97 stays only in AddEventLogInfo | SCD exe, capstone (skeptic) |
| LIFT Fetch address 0x13cb5 in 5 other loaders | ProcessCharacterGameEventLog 0x11da7, ProcessAccountGameEventLog 0x12677, LoadGameEventLogList 0x138fd, LoadSingleCouponPublication 0x14225, LoadRetryReadyGameEventLogList 0x148cd | SCD exe, capstone (skeptic) |
| SetupGameEventListFromXml row out of score order | Moved after UninstallService (99.5) | handoff table |

## Gate result

`tools/gate.sh`: gate ok. `tools/parity.sh`: parity ok, MATCH -> DIFF 0 in all 4 exes.
Baselines, progress.tsv and the README table are not changed. Not merged. Not pushed.

Turns: 395
