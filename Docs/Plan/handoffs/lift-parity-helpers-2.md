# lift-parity-helpers-2: handoff

Turns: 85 (about; 3 stages of 25 and a short stage 4)

## Done
- LG `Client.cpp`, `LobbyDPacketHandler.cpp`: helpers as `static __forceinline` (LG 528 -> 530).
- POD `CacheEconomyPacketHandler.cpp`: 13 handlers MATCH (helper form, shared `done:` tail, `RelayHeader::GetMemberOffset`).
- POD `RelayContext.h`: `RelayHeader()` ctor and inline `GetMemberOffset()`.
- POD `PostOfficeDB.cpp`: `UpdatePostStatus` `__forceinline`; `ResetAllDeliveryFailurePost`, `UpdateStatusToRetryReady`,
  `UpdateStatusToDeliveryFailure/Success` MATCH.
- `CMakeLists.txt`: `/Zc:threadSafeInit-` for C++ (gate link had no `_Init_thread_*`; see lessons stage 4).
- Patterns (worked and not worked): `Docs/Parity/lessons.md`, "helpers-2" stages 1 to 4.

## Gate result
- `tools/gate.sh` ok. `tools/parity.sh` ok, 0 MATCH lost, baseline not changed (no --accept).
- CG 420 (+0), LG 530 (+2), SCD 504 (+0), POD 570 (+17).

## Not done (one line each: function, signal, cause, why stopped)
- POD `PostOfficeDB::LoadSinglePost` 0x15fa0, `LoadPostList` 0x14e50, `LoadRetryReadyPostList`, `LoadRetryReadySinglePost`: calls/refs.
  Original inlines 17 `SQLBindCol` (ODBC import) and has `memset`/`PostInfo::PostInfo` after the acquire check. Ours calls `DbTransaction::BindCol`.
  No form found that inlines it (positive `BindCol` form lost the BindCol MATCH).
- POD `PostOfficeDB::RegisterPost` (score 84): same inlined BindCol/param block. Not analysed further.
- LG `Client::SendTakeGoodsOk` 0x4ed0, `SendListLobbyServiceItemInfoOk` 0x5320, `SendGetCharacterInfoListOk` ~0x4690: call order.
  Original has `Allocate` before the first `Compose` and the fail block right after it; ours moves `Allocate` after `Packet::Clear`.
  The positive form is worse (98.9 -> 93.8). Cause not found.
- LG `LobbyDPacketHandler`: `HandleLobbyLobbyGate_HelloOk`, `InitSessionWith{Lobby,NP}TokenOk`, `StartSessionWith*TokenOk`,
  `InitSessionWithNPTokenFail`, `LobbyDSessionHandler::OnConnect`: refs less in ours. The 4 helpers gave no score change. Literal `#define`
  and shared tail not tried; stopped for turn budget.
- LG `KickNotify`, `CloseSessionNotify`: `_instance` reload (lessons D). Not tried.
- CG/SCD: `static wchar_t const* const` literal pattern not checked.

## ❓
- `RelayHeader` ctor form (PDB ctor 0x2B5A + `__dflt_ctor_closure`; ours is a plain zero ctor).
- Why ours moves `Packet::Allocate` after `Packet::Clear` in `SendTakeGoodsOk`.

## Blocked
- None.
