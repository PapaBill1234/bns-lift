// NPLobbyMessageHandler.obj (LobbyDaemon PDB, 2019 + PDB). Lifted: Handle_SrvCharge_RequestStop. The rest is still stubbed.
#include <wchar.h>
#include "NPLobbyMessageHandler.h"
#include "CliSession.h"
#include "CliSessionManager.h"
#include "LobbyDaemon.h"
#include "NPServiceChannel.h"
#include "Log.h"
#include "LiftStub.h"

extern wchar_t const* LobbyErrorDesc[28];  // LIFT: PDB public LobbyErrorDesc; placeholder definition in LobbyGamePacketHandler.cpp.

namespace StsMsgLib
{
// PDB StsMsgLib::_StsMsgRequestChargeRequestStop (size 0x30).
struct _StsMsgRequestChargeRequestStop : public _StsMsgRequest
{
    _GUID UserId;
    wchar_t* pwszReason;
};
static_assert(sizeof(_StsMsgRequestChargeRequestStop) == 0x30, "sizeof _StsMsgRequestChargeRequestStop");
static_assert(offsetof(_StsMsgRequestChargeRequestStop, UserId) == 0x18, "_StsMsgRequestChargeRequestStop::UserId");
static_assert(offsetof(_StsMsgRequestChargeRequestStop, pwszReason) == 0x28, "_StsMsgRequestChargeRequestStop::pwszReason");
}  // namespace StsMsgLib

namespace
{
// LIFT: inlined in 0xcd5e0. A null or empty reason logs as "unknown".
inline wchar_t const* npReasonText(wchar_t const* reason)
{
    return (reason == nullptr || wcslen(reason) == 0) ? L"unknown" : reason;
}
}  // namespace

// 0xcb710
bool (*DispatchNPLobbyMessageHandler(int))(NPChannel*, StsMsgLib::_StsMsg*, NPTransaction*)
{
    LIFT_STUB(0xcb710);
}

// 0xcd5e0 (command 2904 = COMMAND_SRV_CHARGE_REQUEST_STOP)
#pragma comment(linker, "/INCLUDE:?Handle_SrvCharge_RequestStop@@YA_NPEAVNPChannel@@PEAU_StsMsg@StsMsgLib@@PEAVNPTransaction@@@Z")  // LIFT: keep until the caller is lifted (DispatchNPLobbyMessageHandler 0xcb710).
bool Handle_SrvCharge_RequestStop(NPChannel* channel, StsMsgLib::_StsMsg* msg, NPTransaction* transaction)
{
    if (msg->GetMessageType() != StsMsgLib::MESSAGE_TYPE_REQUEST)
        return false;
    StsMsgLib::_StsMsgRequestChargeRequestStop* req = static_cast<StsMsgLib::_StsMsgRequestChargeRequestStop*>(msg);
    unsigned int txnid = msg->GetTransactionId();
    id128 userId = *reinterpret_cast<id128 const*>(&req->UserId);
    CliSession* cs = LobbyDaemon::_instance->_clisessionMgr->Select_index_account(userId);
    if (cs == nullptr)
    {
        Log::Write(Log::LT_ERROR, L"NPLobbyMessageHandler.cpp", 773,
                   L"[np], handle srv-charge request stop fail; no such cli-session, txn-id:%u, req-reason:%s, "
                   L"user-id:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X",
                   txnid, npReasonText(req->pwszReason), userId.guid.id1, userId.guid.id2, userId.guid.id3,
                   userId.guid.id4[0], userId.guid.id4[1], userId.guid.id4[2], userId.guid.id4[3],
                   userId.guid.id4[4], userId.guid.id4[5], userId.guid.id4[6], userId.guid.id4[7]);
        StsMsgLib::_StsMsgResponseChargeRequestStop res;
        npInitResponse(res, StsMsgLib::COMMAND_SRV_CHARGE_REQUEST_STOP, txnid);
        res.msgInfo.errInfo.nStatusCode = 400;
        res.msgInfo.errInfo.pwszReason = L"ErrUserNotOnline";
        res.msgInfo.errInfo.nErrorCode = 3007;
        channel->SendMsg(&res, false, nullptr);
        return true;
    }
    short stopPlayReason = 0;
    wchar_t const* reason = req->pwszReason;
    if (reason != nullptr && wcslen(reason) != 0)
    {
        if (wcscmp(reason, L"Already Charge") == 0)
            stopPlayReason = 1;
        else if (wcscmp(reason, L"Terminate") == 0)
            stopPlayReason = 2;
        else if (wcscmp(reason, L"Suspend") == 0)
            stopPlayReason = 3;
        else if (wcscmp(reason, L"Abandon") == 0)
            stopPlayReason = 4;
        else if (wcscmp(reason, L"IPKick") == 0)
            stopPlayReason = 5;
    }
    if (!cs->OnChargeStopRequested(txnid))
    {
        LobbyError error = TLobbyError;
        Log::Write(Log::LT_ERROR, L"NPLobbyMessageHandler.cpp", 800,
                   L"[np], handle srv-charge request stop fail; denied by cli-session, error:%s, txn-id:%u, req-reason:%s, "
                   L"user-id:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X",
                   static_cast<unsigned int>(error) >= 28 ? L"LOBERR_UNDEFINED" : LobbyErrorDesc[error], txnid,
                   npReasonText(req->pwszReason), userId.guid.id1, userId.guid.id2, userId.guid.id3,
                   userId.guid.id4[0], userId.guid.id4[1], userId.guid.id4[2], userId.guid.id4[3],
                   userId.guid.id4[4], userId.guid.id4[5], userId.guid.id4[6], userId.guid.id4[7]);
        static_cast<NPGameServiceChannel*>(channel)->SendResponseChargeRequestStopFail(txnid, L"ErrBadData", 4);
        cs->removeReferenceCount(L"NPLobbyMessageHandler.cpp", 802);
        return true;
    }
    cs->ReserveStopPlay(false, stopPlayReason, 9);
    Log::Write(Log::LT_DEBUG, L"NPLobbyMessageHandler.cpp", 813,
               L"[np], handle srv-charge request stop ok, txn-id:%u, req-reason:%s, "
               L"user-id:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X",
               txnid, npReasonText(req->pwszReason), userId.guid.id1, userId.guid.id2, userId.guid.id3,
               userId.guid.id4[0], userId.guid.id4[1], userId.guid.id4[2], userId.guid.id4[3],
               userId.guid.id4[4], userId.guid.id4[5], userId.guid.id4[6], userId.guid.id4[7]);
    cs->removeReferenceCount(L"NPLobbyMessageHandler.cpp", 815);
    return true;
}
