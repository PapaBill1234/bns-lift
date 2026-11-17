// ManagerPacketHandler.obj (MarketDealerDaemon PDB).
#include <winsock2.h>
#include <windows.h>
#include <new>

#include "ManagerPacketHandler.h"
#include "ManagerChannel.h"
#include "ManagementJobContext.h"
#include "MarketDealerDefine.h"
#include "Log.h"
#include "Memory.h"
#include "MemoryManager.h"
#include "Packet.h"
#include "Session.h"

#define MANAGER_PACKET_HANDLER_FILE L"ManagerPacketHandler.cpp"
static wchar_t const* const MODULE_NAME = L"manager packet handler";

// LIFT: No PDB symbol. The binary uses the literals (0x1a940).
static short const MARKETMANAGER_PACKET_VERSION = 4;
static short const ECONOMY_COMMON_PACKET_VERSION = 10;

// 0x1a940
bool HandleMarketManagerHelloReq(Session const* session, Packet const* packet)
{
    wchar_t const* const fn = L"HandleMarketManagerHelloReq";
    Log::Write(Log::LT_DEBUG, MANAGER_PACKET_HANDLER_FILE, 33, L"[%s], %s; <BEGIN PACKET HANDLER>", MODULE_NAME, fn);

    short failReason = MARKETMANAGER_NO_ERROR;
    short cmd = 0;
    short marketmanagerPacketVersion = 0;
    short economyCommonPacketVersion = 0;
    unsigned short managerWid = 0;
    if (packet->Decompose("hhhh", &cmd, &marketmanagerPacketVersion, &economyCommonPacketVersion, &managerWid) == 0)
    {
        Log::Write(Log::LT_ERROR, MANAGER_PACKET_HANDLER_FILE, 47, L"[%s], %s; failed to decompose packet",
                   MODULE_NAME, fn);
        failReason = MARKETMANAGER_SYSTEM_ERROR;
    }
    else
    {
        Log::Write(Log::LT_DEBUG, MANAGER_PACKET_HANDLER_FILE, 52,
                   L"[%s], %s; decomposed packet, marketmanager-packet-version:%d, economy-common-packet-version:%d, "
                   L"managerWid:%u",
                   MODULE_NAME, fn, static_cast<int>(marketmanagerPacketVersion),
                   static_cast<int>(economyCommonPacketVersion), static_cast<unsigned int>(managerWid));
        if (marketmanagerPacketVersion == MARKETMANAGER_PACKET_VERSION &&
            economyCommonPacketVersion == ECONOMY_COMMON_PACKET_VERSION)
        {
            // BUG: 0x1a940 no null check after the ManagerChannel alloc.
            void* const memory =
                Memory::_Manager[2]->Alloc(sizeof(ManagerChannel), MANAGER_PACKET_HANDLER_FILE, 64);
            ManagerChannel* const managerChannel = ::new (memory) ManagerChannel(managerWid);
            managerChannel->SetSession(session);
            managerChannel->removeReferenceCount(MANAGER_PACKET_HANDLER_FILE, 66);
            session->Send("h", MarketManager_HelloOkCmd);
            Log::Write(Log::LT_NOTICE, MANAGER_PACKET_HANDLER_FILE, 69,
                       L"[%s], %s; sent hello success ack, managerWid:%u", MODULE_NAME, fn,
                       static_cast<unsigned int>(managerWid));
            Log::Write(Log::LT_DEBUG, MANAGER_PACKET_HANDLER_FILE, 71, L"[%s], %s; <END PACKET HANDLER>", MODULE_NAME,
                       fn);
            return true;
        }
        Log::Write(Log::LT_ERROR, MANAGER_PACKET_HANDLER_FILE, 57,
                   L"[%s], %s; invalid packet version, my marketmanager-packet-version:%d, client version:%d, my "
                   L"economy-common-packet-version:%d, client version:%d",
                   MODULE_NAME, fn, static_cast<int>(MARKETMANAGER_PACKET_VERSION),
                   static_cast<int>(marketmanagerPacketVersion), static_cast<int>(ECONOMY_COMMON_PACKET_VERSION),
                   static_cast<int>(economyCommonPacketVersion));
        failReason = MARKETMANAGER_HELLOFAIL_INVALID_PACKET_VERSION;
    }

    session->Send("hh", MarketManager_HelloFailCmd, static_cast<int>(failReason));
    Log::Write(Log::LT_NOTICE, MANAGER_PACKET_HANDLER_FILE, 76,
               L"[%s], %s; sent hello failure ack, managerWid:%u, failReason:%d", MODULE_NAME, fn,
               static_cast<unsigned int>(managerWid), static_cast<int>(failReason));
    Log::Write(Log::LT_DEBUG, MANAGER_PACKET_HANDLER_FILE, 81, L"[%s], %s; <END PACKET HANDLER>", MODULE_NAME, fn);
    return false;
}

// 0x1ac40
bool HandleMarketManagerSuspendSaleReq(Session const* session, Packet const* packet)
{
    wchar_t const* const fn = L"HandleMarketManagerSuspendSaleReq";
    Log::Write(Log::LT_DEBUG, MANAGER_PACKET_HANDLER_FILE, 87, L"[%s], %s; <BEGIN PACKET HANDLER>", MODULE_NAME, fn);

    short failReason = MARKETMANAGER_UNKNOWN_ERROR;
    SuspendSaleManagementJob jobContext;
    // ❓ The exe only calls ReplyFailure after Initialize. verifyParameter, handleJob and the success reply are
    // not called here (maybe the suspend code is commented out in the source). Kept as in the exe.
    if (jobContext.Initialize(packet))
        jobContext.ReplyFailure(session, failReason);

    Log::Write(Log::LT_DEBUG, MANAGER_PACKET_HANDLER_FILE, 111, L"[%s], %s; <END PACKET HANDLER>", MODULE_NAME, fn);
    return true;
}

// 0x1ad20
bool HandleMarketManagerRetrySingleDeliveryFailureReq(Session const* session, Packet const* packet)
{
    wchar_t const* const fn = L"HandleMarketManagerRetrySingleDeliveryFailureReq";
    Log::Write(Log::LT_DEBUG, MANAGER_PACKET_HANDLER_FILE, 117, L"[%s], %s; <BEGIN PACKET HANDLER>", MODULE_NAME, fn);

    short failReason = MARKETMANAGER_UNKNOWN_ERROR;
    RetrySingleDeliveryFailureManagementJob jobContext;
    if (jobContext.Initialize(packet))
    {
        if (jobContext.verifyParameter(failReason) && jobContext.handleJob(failReason))
            jobContext.ReplySuccess(session);
        else
            jobContext.ReplyFailure(session, failReason);
    }

    Log::Write(Log::LT_DEBUG, MANAGER_PACKET_HANDLER_FILE, 133, L"[%s], %s; <END PACKET HANDLER>", MODULE_NAME, fn);
    return true;
}

// 0x1ae50
bool HandleMarketManagerRetryAllDeliveryFailureReq(Session const* session, Packet const* packet)
{
    wchar_t const* const fn = L"HandleMarketManagerRetryAllDeliveryFailureReq";
    Log::Write(Log::LT_DEBUG, MANAGER_PACKET_HANDLER_FILE, 139, L"[%s], %s; <BEGIN PACKET HANDLER>", MODULE_NAME, fn);

    short failReason = MARKETMANAGER_UNKNOWN_ERROR;
    RetryAllDeliveryFailureManagementJob jobContext;
    if (jobContext.Initialize(packet))
    {
        if (jobContext.verifyParameter(failReason) && jobContext.handleJob(failReason))
            jobContext.ReplySuccess(session);
        else
            jobContext.ReplyFailure(session, failReason);
    }

    Log::Write(Log::LT_DEBUG, MANAGER_PACKET_HANDLER_FILE, 155, L"[%s], %s; <END PACKET HANDLER>", MODULE_NAME, fn);
    return true;
}

// 0x1b040
bool HandleMarketManagerUpdateStatusToReportFailureReq(Session const* session, Packet const* packet)
{
    wchar_t const* const fn = L"HandleMarketManagerUpdateStatusToReportFailureReq";
    Log::Write(Log::LT_DEBUG, MANAGER_PACKET_HANDLER_FILE, 161, L"[%s], %s; <BEGIN PACKET HANDLER>", MODULE_NAME, fn);

    short failReason = MARKETMANAGER_UNKNOWN_ERROR;
    UpdateStatusToReportFailureManagementJob jobContext;
    if (jobContext.Initialize(packet))
    {
        if (jobContext.verifyParameter(failReason) && jobContext.handleJob(failReason))
            jobContext.ReplySuccess(session);
        else
            jobContext.ReplyFailure(session, failReason);
    }

    Log::Write(Log::LT_DEBUG, MANAGER_PACKET_HANDLER_FILE, 177, L"[%s], %s; <END PACKET HANDLER>", MODULE_NAME, fn);
    return true;
}
