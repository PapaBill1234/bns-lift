# lift-parity-scd-1 handoff

## Done
- Patterns 40-45 in `Docs/Parity/lessons.md`. SCD MATCH 437 -> 461/669 (68.9 %). CG 387, LG 487, POD 484. No MATCH lost.
- Stage 5: kept all 4 Pattern 45 edits (RefCntObject assert path, CouponJob/EventNotiJob init lists, EventNotiJob::init log args).

## Not done (148 DIFF in `build-vs2010/SmartCouponDaemon.funcdiff.json`; grouped by cause)
- Codegen only (constant CSE, LTCG propagation; source cannot control): EventNotiJob::finalize 0x9cc0 (consts),
  JobManager::Execute 0x71a0 / ExecuteW 0x7220 (consts), wmain (const 0xfffffffffffffffe), AddEventLogInfo 0x10a00,
  AddPublicationInfo 0x108e0, NPTransactionRegistry::Register, Log::Write, Packet::Allocate (consts 67).
- SmartCouponDB Load*/Process* 0x117c0, 0x13620 (calls): first-only BindCol inline + extra Fetch/Log::Write. ❓ cause.
- SCD handlers (calls): HandleSmartCoupon_*, HandleSmartCouponManager_*, SendPublicationEvent::HandleEvent,
  ManagerChannel::SendRetry*, SmartCouponDaemon::reload/initialize/loadUnhandledGameEventLog, EventNotiJob::work/
  eventNotiReq/eventNotiRes, DChannelMgr::*, GameEventConfig::*: inline depth of PacketComposer/Log code differs. Stopped: budget.
- Shared BloodLib (Session*, SessionSendBuffer*, Port*, Network*, TimerQueue*, LogFile*, LogMedia*, WindowConsole*,
  PipeConsole*, Console, Channel, SessionHandler, SharedChannel, DynamicRefCntObj dtors, CrashHandler, Daemon*): shared
  code; a change must be checked on all 4 exes. Not in this exe-only scope.
- Crypto (aes128Table*, Blowfish::Setup, Ctr::Encrypt, encrypt/decrypt, Prng*): table refs/consts; shared `src/Security/`.
- ObjPool::ObjPool/Finalize, ObjPoolTimer dtor: source `src/Server/LobbyDaemon/ObjectPool.cpp` is not in card Files.
- `operator delete` (all 0): CRT, not lifted code.
- 60 functions only in original: inline/folded in our build (see `Docs/Parity/triage.md`).
- 90 % = 602 MATCH. Not reachable with exe-only fixes: about 70 % of the DIFF are shared or codegen-only.

## ❓
- GameEventManager::Initialize 0xac90 assert tests `threadManager` (MATCH now).
- SmartCouponDB BindCol/Fetch difference above.

## Blocked
- None.

## Gate result
- `.scratch/gate_errors.sh`: gate ok. `tools/parity.sh`: parity ok (SCD +24 over baseline, MATCH -> DIFF 0 on all exes).
