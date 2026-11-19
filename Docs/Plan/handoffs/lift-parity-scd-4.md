# Handoff: lift-parity-scd-4

Card: SCD DB loaders, DChannelMgr, EventNotiJob, handlers. Goal: SCD 90 % (603 MATCH). Result: goal met.

## Counts (tools/parity.sh)

| Exe | Baseline | End | Change | MATCH lost |
| --- | ---: | ---: | ---: | ---: |
| CacheGate | 448/491 | 448/491 = 91.2 % | +0 | 0 |
| LobbyGate | 627/739 | 627/739 = 84.8 % | +0 | 0 |
| SmartCouponDaemon | 582/669 | 603/669 = 90.1 % | +21 | 0 |
| PostOfficeDaemon | 665/759 | 665/759 = 87.6 % | +0 | 0 |

## Commits

| Commit | Gain | Change |
| --- | ---: | --- |
| f4ba49f | +6 | DChannelMgr |
| 93296be | +5 | Handlers and contexts |
| 3f572fa | +6 | do-while DB loaders, int params |
| 4a4f013 | +2 | loadUnhandledGameEventLog count local, CouponJob::transit else-if, retry failReason char |
| a7addcc | +2 | GameEventLogEvent::HandleEvent switch + posted info copy; NPTransactionRegistry::Register |

## DIFF functions left (SCD, 64)

Tries = tries in this card. "Out of scope" = not in the card list (crypto, BloodLib, shared Network or Session code).

| Function | Score | Signal | Cause | Why stopped |
| --- | ---: | --- | --- | --- |
| wmain | 66.7 | consts | Not analysed | Card rule: do not change |
| aes128TableDecrypt | 70.0 | refs,consts | Not analysed | Out of scope, 0 tries |
| aes128TableEncrypt | 70.0 | refs,consts | Not analysed | Out of scope, 0 tries |
| BigInteger::Divide | 76.7 | calls,refs,consts | Not analysed | Out of scope, 0 tries |
| EventNotiJob::Initialize | 77.8 | refs,consts | Not analysed | Goal met first, 0 tries |
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
| EventNotiJob::eventNotiRes | 89.0 | calls,consts | Not analysed | Goal met first, 0 tries |
| GameEventConfig::Load | 89.2 | calls,consts | Not analysed | Goal met first, 0 tries |
| BigInteger::InvMod | 89.7 | calls,consts | Not analysed | Out of scope, 0 tries |
| NPChannel::SendMsg | 90.1 | calls,refs,consts | The orig has an inlined Packet assert | 0 tries |
| Network::OpenPort | 90.1 | calls,refs,consts | Not analysed | Out of scope, 0 tries |
| RsaPublic::Setup | 90.2 | consts | Not analysed | Out of scope, 0 tries |
| OaepEncoder::Setup | 90.3 | calls,consts | Not analysed | Out of scope, 0 tries |
| BigInteger::mul (static) | 90.9 | consts | Not analysed | Out of scope, 0 tries |
| GameEventConfig::SetupGameEventListFromXml | 91.3 | calls,refs,consts | Not analysed | Goal met first, 0 tries |
| Rsa::decrypt | 91.7 | calls,refs | Not analysed | Out of scope, 0 tries |
| aes128TableSetupDecKey | 91.7 | consts | Not analysed | Out of scope, 0 tries |
| NPServiceChannelManager::HandleMessage | 92.3 | consts | Not analysed | Card rule: do not change |
| EventNotiJob::eventNotiReq | 92.8 | calls,consts | Not analysed | Goal met first, 0 tries |
| HandleSmartCoupon_GameEventByAccountReq | 93.0 | calls,refs | The orig puts the decompose-fail Send/Log 327 path at the end and has extra code order that a goto form does not give | 3 tries (93.9, 95.2, 95.2), no MATCH |
| EventNotiJob::finalize | 93.3 | consts | Not analysed | Card stop list |
| JobManager::ExecuteW | 93.3 | consts | Not analysed | Card stop list |
| RawPacketBufferHandler::Destroy | 93.3 | calls | Not analysed | Out of scope, 0 tries |
| NPServiceChannelCmdDispatcher | 94.3 | calls,refs | Not analysed | 0 tries |
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

## Gate result

`tools/gate.sh`: gate ok. `tools/parity.sh`: parity ok, MATCH -> DIFF 0 in all 4 exes.
Baselines, progress.tsv and the README table are not changed. Not merged. Not pushed.

Turns: 295
