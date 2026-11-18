# lift-parity-handlers-3

Turns: about 105

## Done
- Gate ok. Parity ok. No MATCH lost in any exe.
- MATCH now: CG 436 (+0), LG 601 (+1), SCD 557 (+1), POD 645 (+8).
- MATCH functions in scope:
  - POD `WorldSessionHandler`, `AgentSessionHandler`, `CacheGateSessionHandler::PacketHandler`.
  - POD `HandlePostOfficeManagement{HelloReq, ResetPostStatusReq, LoadRetryReadySinglePostReq, ResetAllPostStatusReq, LoadRetryReadyPostListReq}`.
  - SCD `ManagerSessionHandler::PacketHandler` 0xe980.
  - LG `ClientSessionHandler::PacketHandler` 0x6b70.
- Fix patterns are in `Docs/Parity/lessons.md` ("Handlers stage 3" and "Handlers stage 4").

## Not done (function, signal, cause, why stopped)
- POD `HandleCacheGateRelay` 0x8070: score 93.3. Orig puts `<indirect>` call after the 3rd `Log::Write`; ours before. One extra const 0x56. Three forms measured, same score. Stopped: no form moves the call.
- POD `HandleCacheGateRelayFail`, `HandleCacheGateRelayInvalid`: score 82.7. Orig has 3 `RelayContext::ProcessRelayResponse` calls. Not tried.
- POD `HandleCacheGateFragmentRelay` 0x82c0, `HandlePostOfficeHelloReq`, `HandleRegisterPostReq`, `HandleServiceRegisterPostReq`: not tried (time).
- LG `HandleLobbyLobbyGate_*` (12), `HandleLobbyGate_*` (5), `Client::Send{GetCharacterInfoList,ListLobbyServiceItemInfo,TakeGoods}Ok`: not tried.
- SCD `HandleSmartCouponManager_HelloReq`, `HandleSmartCoupon_GameEventByAccountReq`, `GameEventLogEvent::HandleEvent`, `RetryCouponPublicationEvent`, `SendPublicationEvent`, `HandleSmartCoupon_HelloReq`, `...RetryCouponPublicationReq`, `ManagerChannel::SendRetryCouponPublication{Ok,Fail}`: not tried. Next idea: failure-first branch order and field-by-field Packet init (worked in POD).
- CG `HandleCacheGateHello` (else-if chain, lessons B), `HelloFail`, `Relay`: not tried.

## ❓
- POD inlined `Packet::Allocate`: pool slot 0x28 in orig, 0x90 in ours.
- Is the iocp test in CG and SCD the same as in POD? Use `Network::iocpHandle()`.
- Does the field-by-field init help SCD and LG local packets? Not measured.

## Blocked
- None.

## Gate result
- `.scratch/gate_errors.sh`: gate ok.
- `tools/parity.sh`: parity ok (CG 436, LG 601, SCD 557, POD 645).

## Gate fix
- Gate failure (many POD functions LOST, e.g. `WindowConsole::*`, `WorldChannel::GetWid`): no source change needed. The failed run was not repeatable. A new `tools/parity.sh` run is ok (CG 436, LG 601, SCD 557, POD 645, MATCH -> DIFF 0).
