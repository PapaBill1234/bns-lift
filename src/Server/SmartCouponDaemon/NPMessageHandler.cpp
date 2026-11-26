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

// ❓ Inlined in NPServiceChannelManager::HandleMessage (0x10700). LIFT: A switch gives the two signed compares at 0x10745. A range test gives lea/ja.
NPServiceMessageHandler DispatchNPMessageHandler(ECommand cmd)
{
    switch (cmd)
    {
    case COMMAND_SRV_REWARDBROKER_EVENT_NOTI:
    case COMMAND_SRV_REWARD_REQUEST_REWARD_FOR_EVENT:
        return NPHandlerEventNoti;
    default:
        Log::Write(Log::LT_ERROR, NPMESSAGEHANDLER_FILE, 36, L"[np], DispatchNPMessageHandler, invalid command, cmd:%d",
                   cmd);
        return nullptr;
    }
}
