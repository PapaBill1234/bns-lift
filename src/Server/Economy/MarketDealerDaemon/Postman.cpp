// Postman.obj (MarketDealerDaemon PDB).
#include "Postman.h"
#include <time.h>
#include "Log.h"
#include "AlertSender.h"
#include "Daemon.h"
#include "FragmentPacket.h"
#include "AgentChannel.h"
#include "DeliveryContext.h"
#include "MarketDB.h"
#include "MarketDealerDaemon.h"

#define POSTMAN_FILE L"Postman.cpp"
static wchar_t const* const MODULE_NAME = L"postman";  // PDB MODULE_NAME

// 0x2aa60
bool Postman::DeliverPost(DeliveryContext* const deliveryContext)
{
    if (deliveryContext == nullptr)
    {
        Log::Write(Log::LT_ERROR, POSTMAN_FILE, 29, L"== CRASH == [%s], %s; invalid parameter, deliveryContext:0x%p",
                   MODULE_NAME, L"Postman::DeliverPost", nullptr);
        AlertSender::Write(POSTMAN_FILE, 29, L"== CRASH == [%s], %s; invalid parameter, deliveryContext:0x%p",
                           MODULE_NAME, L"Postman::DeliverPost", nullptr);
        return false;
    }

    long long const deliveryId = deliveryContext->_deliveryInfo._deliveryId;
    int const state = Daemon::Instance->State;
    if (state == Daemon::STATE_COOLDOWNING || state == Daemon::STATE_COOLDOWNED || state == Daemon::STATE_STOPPING ||
        state == Daemon::STATE_STOPPED)
    {
        Log::Write(Log::LT_DEBUG, POSTMAN_FILE, 36,
                   L"[%s], %s; daemon service state is unavailable; cannot report delivery, deliveryId:0x%I64X",
                   MODULE_NAME, L"Postman::DeliverPost", deliveryId);
        return false;
    }

    AgentChannelManager* const agentChannelManager = MarketDealerDaemon::_instance->_agentChannelManager;
    if (agentChannelManager->_marketAgentChannel == nullptr)
    {
        Log::Write(Log::LT_DEBUG, POSTMAN_FILE, 43,
                   L"[%s], %s; market agent is not connecting; cannot send packet; timer will try to send at next time "
                   L"again, deliveryId:0x%I64X",
                   MODULE_NAME, L"Postman::DeliverPost", deliveryId);
        return false;
    }

    AgentChannel* const marketAgentChannel = agentChannelManager->GetMarketAgentChannel();
    if (marketAgentChannel == nullptr)
    {
        Log::Write(Log::LT_ERROR, POSTMAN_FILE, 49,
                   L"[%s], %s; market agent channel is null; cannot report delivery, deliveryId:0x%I64X, "
                   L"marketAgentChannel:0x%p",
                   MODULE_NAME, L"Postman::DeliverPost", deliveryId, nullptr);
        return false;
    }

    FragmentPacket packet(3076, "hiqccqcqqhqhqsssQQqihqs");
    packet.packet.Allocate(&packet.composer);
    if (!deliveryContext->ComposeReportPacket(packet))
    {
        Log::Write(Log::LT_ERROR, POSTMAN_FILE, 56, L"[%s], %s; failed to compose report packet, deliveryId:0x%I64X",
                   MODULE_NAME, L"Postman::DeliverPost", deliveryId);
        marketAgentChannel->removeReferenceCount(POSTMAN_FILE, 57);
        packet.packet.Clear();
        return false;
    }

    if (packet.packet.Splitter != nullptr)
        packet.packet.Splitter->Finalize(packet.packet.CurHeader);
    marketAgentChannel->Send(&packet.packet);
    Log::Write(Log::LT_NOTICE, POSTMAN_FILE, 63, L"[%s], %s; sent delivery report packet, deliveryId:0x%I64X",
               MODULE_NAME, L"Postman::DeliverPost", deliveryId);
    marketAgentChannel->removeReferenceCount(POSTMAN_FILE, 65);

    deliveryContext->_reportTime = _time64(nullptr);
    char const jobStatus = deliveryContext->_deliveryInfo._jobStatus;
    if (jobStatus == DeliveryInfo::JOBSTATUS_DELIVERY_READY || jobStatus == DeliveryInfo::JOBSTATUS_RETRY_READY)
    {
        deliveryContext->_deliveryInfo._jobStatus = DeliveryInfo::JOBSTATUS_REPORTING;
        int dbRetValue = 0;
        if (MarketDB::UpdateStatusToReporting(dbRetValue, deliveryId))
        {
            Log::Write(Log::LT_DEBUG, POSTMAN_FILE, 77,
                       L"[%s], %s; succeeded to update job status [reporting status], deliveryId:0x%I64X",
                       MODULE_NAME, L"Postman::DeliverPost", deliveryId);
        }
        else
        {
            Log::Write(Log::LT_ERROR, POSTMAN_FILE, 74,
                       L"[%s], %s; failed to update job status [reporting status], dbRetValue:%d, deliveryId:0x%I64X",
                       MODULE_NAME, L"Postman::DeliverPost", dbRetValue, deliveryId);
        }
    }
    packet.packet.Clear();
    return true;
}
