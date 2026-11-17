// NPMessageHandler.obj of the SmartCouponDaemon PDB.
#include "NPChannel.h"
#include "CouponJob.h"
#include "Log.h"
#include "SmartCouponDaemon.h"

using namespace StsMsgLib;

static wchar_t const NPMESSAGEHANDLER_FILE[] = L"NPMessageHandler.cpp";

// 0xFBC0
bool NPHandlerEventNoti(NPChannel* channel, _StsMsg* msg, NPTransaction* tran)
{
    if (msg == nullptr)
    {
        Log::Write(Log::LT_ERROR, NPMESSAGEHANDLER_FILE, 49, L"[np], handle event-noti fail; msg is null");
        return false;
    }
    if (msg->GetMessageType() != MESSAGE_TYPE_RESPONSE)
        return false;
    _StsMsgResponseRewardBrokerEventNoti* res = static_cast<_StsMsgResponseRewardBrokerEventNoti*>(msg);
    if (tran != nullptr)
    {
        if (tran->GetKind() != 1)
            return false;
        NPJobTransaction* job = static_cast<NPJobTransaction*>(tran);
        if (!SmartCouponDaemon::_instance->_jobMgr->ExecuteW(job->_jobid, 2, msg))
        {
            Log::Write(Log::LT_ERROR, NPMESSAGEHANDLER_FILE, 61,
                       L"[np], handle event-noti fail; execute job fail, np-tid:%u, jobid:0x%I64X",
                       msg->GetTransactionId(), job->_jobid);
            return false;
        }
        Log::Write(Log::LT_DEBUG, NPMESSAGEHANDLER_FILE, 64, L"[np], handle event-noti, np-tid:%u, jobid:0x%I64X",
                   msg->GetTransactionId(), job->_jobid);
        return true;
    }
    wchar_t const* reason = res->msgInfo.errInfo.pwszReason ? res->msgInfo.errInfo.pwszReason : L"null";
    Log::Write(Log::LT_DEBUG, NPMESSAGEHANDLER_FILE, 71,
               L"[np], handle event-noti ok, without transaction, np-tid:%u, cmd:%d, type:%d, status-code:%u, "
               L"reason:%s, error-code:%d",
               msg->GetTransactionId(), msg->GetCommand(), msg->GetMessageType(), res->msgInfo.errInfo.nStatusCode,
               reason, res->msgInfo.errInfo.nErrorCode);
    return true;
}
