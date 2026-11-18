# lift-parity-scd-2 handoff

## Done
- SmartCouponDaemon MATCH 504 -> 510 of 669 (76.2 %). CG 420, LG 530, POD 588: no change, 0 MATCH lost.
- New MATCH: 6 (incl. `SmartCouponDB::UpdateStatusToPublicationSuccess` 0x129c0). Handlers 0x8360 (98.1) and 0x8e80 (91.9) better.
- Files: `SmartCouponDaemon/CouponJob.cpp`, `GameEventWorker.cpp`, `SmartCouponDB.cpp`, `DaemonPacketHandler.cpp`
  (`DaemonPacketHandlerSend` forceinline send), `BloodLib/include/Session.h` (one `friend` line, access only), `Docs/Parity/lessons.md`.
- Fix patterns that worked and did not work: `Docs/Parity/lessons.md`, sections "scd-2, stage 1" to "stage 4".

## Not done (function, signal, cause, why stopped)
- 0x8e80 `HandleSmartCoupon_GameEventByAccountReq`: calls 82, refs 94. Block layout (fail tail, invalid-param Log at end). Source order did not move it.
- 0x8360 `HandleSmartCoupon_GameEventByCharacterReq`: 2nd `ID128_GUID_ZERO` ref, extra const 0x7b. Orig asm not checked. Turn budget.
- 0xeb80/0xed20 `ManagerChannel::SendRetryCouponPublication{Ok,Fail}`: Compose-fail block before `encrypt` (lessons A6). Not tried.
- `HandleSmartCouponManager_RetryCouponPublicationReq`, `GameEventManager::PostGameEventLogList`, `EventNotiJob::Initialize`: `ID128_GUID_ZERO` refs (A11).
- `SmartCouponDaemon::loadUnhandledGameEventLog`, `HandleSmartCouponManager_LoadRetryReadyGameEventLogListReq`: inline depth of `PostGameEventLogList`.
- `SmartCouponDB::Process*GameEventLog`, `Load*`: orig inlines only the first `BindCol`, no `DbTransaction::Fetch` call (lessons D). No fix known.
- Block order: `ManagerSessionHandler::PacketHandler`, `HandleSmartCouponManager_HelloReq`, `SmartCouponDaemon::initialize`,
  `SendPublicationEvent::HandleEvent`, `RetryCouponPublicationEvent::HandleEvent`. Not tried.
- 0x6990 `CouponJob::transit` (94.8): orig tail-merges the Alert. Not tried.
- Stop list kept: `EventNotiJob::finalize` 0x9cc0, `JobManager::Execute` 0x71a0.
- Shared DIFFs (`ObjPool`, `RawPacketBufferHandler::Destroy`, NP channel code): out of scope.

## ❓ / Blocked
- ❓ Module of `__delv_buf__` (shared TLS layout differs in all exes); scalar placement `operator delete` 0x1b90 (shared). Blocked: none.

## Gate result
- `tools/gate.sh`: gate ok. `tools/parity.sh` (all 4 exes): parity ok. The runner must `--accept` the new SCD baseline (510).

Turns: 79
