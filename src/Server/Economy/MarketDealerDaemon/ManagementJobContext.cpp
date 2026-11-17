// ManagementJobContext.obj (MarketDealerDaemon PDB). Source file name from log strings: "ManagementJobContext.cpp".
// LIFT: The scoped lock of Lock.h is inlined in handleJob. Its null checks (Lock.h:113, Lock.h:122) are not
// in the C++ here: the lock is a member of a context that is not null, so the checks cannot fail.
#include <windows.h>
#include "ManagementJobContext.h"
#include "MarketDealerDefine.h"
#include "MarketDB.h"
#include "MarketDealerDaemon.h"
#include "SaleContext.h"
#include "SaleTimeContext.h"
#include "DeliveryContext.h"
#include "Packet.h"
#include "Session.h"
#include "Log.h"
#include "AlertSender.h"

#define MANAGEMENT_JOB_FILE L"ManagementJobContext.cpp"
static wchar_t const* const MODULE_NAME = L"management job context";

#define MANAGEMENT_JOB_CRASH(line, ...)                                    \
    do                                                                     \
    {                                                                      \
        Log::Write(Log::LT_ERROR, MANAGEMENT_JOB_FILE, line, __VA_ARGS__); \
        AlertSender::Write(MANAGEMENT_JOB_FILE, line, __VA_ARGS__);        \
    } while (0)

#define INVALID_PACKET L"== CRASH == [%s], %s; invalid parameter, packet:0x%p"
#define INVALID_SESSION L"== CRASH == [%s], %s; invalid parameter, session:0x%p"
#define FAIL_DECOMPOSE L"[%s], %s; failed to decompose packet"

// LIFT: The PDB has only the scalar deleting destructors. The destructors have no body.
SuspendSaleManagementJob::~SuspendSaleManagementJob() {}
RetrySingleDeliveryFailureManagementJob::~RetrySingleDeliveryFailureManagementJob() {}
RetryAllDeliveryFailureManagementJob::~RetryAllDeliveryFailureManagementJob() {}
UpdateStatusToReportFailureManagementJob::~UpdateStatusToReportFailureManagementJob() {}

// 0x18980
bool SuspendSaleManagementJob::Initialize(Packet const*& packet)
{
    wchar_t const* const fn = L"SuspendSaleManagementJob::Initialize";
    if (packet == nullptr)
    {
        MANAGEMENT_JOB_CRASH(38, INVALID_PACKET, MODULE_NAME, fn, packet);
        return false;
    }
    short cmd = 0;
    if (packet->Decompose("hqqq", &cmd, &_tid, &_saleId, &_sellerPcId) == 0)
    {
        Log::Write(Log::LT_ERROR, MANAGEMENT_JOB_FILE, 47, FAIL_DECOMPOSE, MODULE_NAME, fn);
        return false;
    }
    Log::Write(Log::LT_DEBUG, MANAGEMENT_JOB_FILE, 50,
               L"[%s], %s; decomposed packet, tid:0x%I64X, saleId:0x%I64X, sellerPcId:0x%I64X", MODULE_NAME, fn, _tid,
               _saleId, _sellerPcId);
    return true;
}

// 0x18ae0
void SuspendSaleManagementJob::ReplyFailure(Session const*& session, short const& failReason) const
{
    wchar_t const* const fn = L"SuspendSaleManagementJob::ReplyFailure";
    if (session == nullptr)
    {
        MANAGEMENT_JOB_CRASH(69, INVALID_SESSION, MODULE_NAME, fn, session);
        return;
    }
    session->Send("hqqE", MarketManager_SuspendSaleFailCmd, _tid, _saleId, static_cast<int>(failReason));
    Log::Write(Log::LT_NOTICE, MANAGEMENT_JOB_FILE, 74,
               L"[%s], %s; sent suspend sale failure ack, tid:0x%I64X, saleId:0x%I64X, sellerPcId:0x%I64X, "
               L"failReason:%d",
               MODULE_NAME, fn, _tid, _saleId, _sellerPcId, static_cast<int>(failReason));
}

// 0x18c00
bool SuspendSaleManagementJob::verifyParameter(short& failReason) const
{
    if (_saleId > 0 && _sellerPcId > 0)
        return true;
    Log::Write(Log::LT_ERROR, MANAGEMENT_JOB_FILE, 81,
               L"[%s], %s; invalid parameter, tid:0x%I64X, saleId:0x%I64X, sellerPcId:0x%I64X", MODULE_NAME,
               L"SuspendSaleManagementJob::verifyParameter", _tid, _saleId, _sellerPcId);
    failReason = MARKETMANAGER_SUSPENDSALEFAIL_INVALID_PARAMETER;
    return false;
}

// 0x18c80
bool SuspendSaleManagementJob::handleJob(short& failReason)
{
    wchar_t const* const fn = L"SuspendSaleManagementJob::handleJob";
    SaleContextManager* const saleContextManager = MarketDealerDaemon::_instance->_saleContextManager;
    SaleContext* const saleContext = saleContextManager->GetContext(_saleId);
    if (saleContext == nullptr)
    {
        Log::Write(Log::LT_ERROR, MANAGEMENT_JOB_FILE, 94,
                   L"[%s], %s; there is no such sale context, tid:0x%I64X, saleId:0x%I64X, sellerPcId:0x%I64X",
                   MODULE_NAME, fn, _tid, _saleId, _sellerPcId);
        failReason = MARKETMANAGER_SUSPENDSALEFAIL_NO_SUCH_SALE;
        return false;
    }

    saleContext->_lock.Enter();
    char const saleStatus = saleContext->_saleInfo._saleStatus;
    if (saleStatus != SaleInfo::SALESTATUS_SELLING)
    {
        Log::Write(Log::LT_ERROR, MANAGEMENT_JOB_FILE, 104,
                   L"[%s], %s; sale status is not selling, tid:0x%I64X, saleId:0x%I64X, sellerPcId:0x%I64X, "
                   L"saleStatus:%d",
                   MODULE_NAME, fn, _tid, _saleId, _sellerPcId, saleStatus);
        failReason = MARKETMANAGER_SUSPENDSALEFAIL_INVALID_SALE_STATUS;
    }
    else if (saleContext->_saleInfo._seller._participantPcId != _sellerPcId)
    {
        Log::Write(Log::LT_ERROR, MANAGEMENT_JOB_FILE, 109,
                   L"[%s], %s; seller pcid is not same, tid:0x%I64X, saleId:0x%I64X, sellerPcId:0x%I64X, "
                   L"contextPcId:0x%I64X",
                   MODULE_NAME, fn, _tid, _saleId, _sellerPcId, saleContext->_saleInfo._seller._participantPcId);
        failReason = MARKETMANAGER_SUSPENDSALEFAIL_PCID_IS_NOT_SAME;
    }
    else
    {
        int dbRetValue = 0;
        if (MarketDB::SuspendSaleByManager(dbRetValue, *this))
        {
            saleContext->_saleInfo._saleStatus = SaleInfo::SALESTATUS_SUSPENSION_OF_SALE;
            saleContext->_lock.Leave();

            if (!MarketDealerDaemon::_instance->_saleTimeContextManager->RemoveContext(
                    _saleId, saleContext->_saleInfo._saleExpirationTime))
            {
                MANAGEMENT_JOB_CRASH(132,
                                     L"== CRASH == [%s], %s; exception occurred; failed to remove saletime context, "
                                     L"saleId:0x%I64X, saleExpirationTime:%I64d",
                                     MODULE_NAME, fn, _saleId, saleContext->_saleInfo._saleExpirationTime);
            }
            if (!saleContextManager->RemoveContext(_saleId))
            {
                MANAGEMENT_JOB_CRASH(137,
                                     L"== CRASH == [%s], %s; exception occurred; failed to remove sale context, "
                                     L"saleId:0x%I64X",
                                     MODULE_NAME, fn, _saleId);
            }
            Log::Write(Log::LT_DEBUG, MANAGEMENT_JOB_FILE, 140,
                       L"[%s], %s; succeeded to suspend sale by manager, tid:0x%I64X, saleId:0x%I64X, "
                       L"sellerPcId:0x%I64X",
                       MODULE_NAME, fn, _tid, _saleId, _sellerPcId);
            saleContext->removeReferenceCount(MANAGEMENT_JOB_FILE, 141);
            return true;
        }
        Log::Write(Log::LT_ERROR, MANAGEMENT_JOB_FILE, 116,
                   L"[%s], %s; failed to suspend sale by manager, dbRetValue:%d, tid:0x%I64X, saleId:0x%I64X, "
                   L"sellerPcId:0x%I64X",
                   MODULE_NAME, fn, dbRetValue, _tid, _saleId, _sellerPcId);
        failReason = MARKETMANAGER_DB_ERROR;
    }
    saleContext->_lock.Leave();
    saleContext->removeReferenceCount(MANAGEMENT_JOB_FILE, 147);
    return false;
}

// 0x19130
bool RetrySingleDeliveryFailureManagementJob::Initialize(Packet const*& packet)
{
    wchar_t const* const fn = L"RetrySingleDeliveryFailureManagementJob::Initialize";
    if (packet == nullptr)
    {
        MANAGEMENT_JOB_CRASH(169, INVALID_PACKET, MODULE_NAME, fn, packet);
        return false;
    }
    short cmd = 0;
    if (packet->Decompose("hqqqq", &cmd, &_tid, &_deliveryId, &_saleId, &_recipientPcId) == 0)
    {
        Log::Write(Log::LT_ERROR, MANAGEMENT_JOB_FILE, 179, FAIL_DECOMPOSE, MODULE_NAME, fn);
        return false;
    }
    Log::Write(Log::LT_DEBUG, MANAGEMENT_JOB_FILE, 182,
               L"[%s], %s; decomposed packet, tid:0x%I64X, deliveryId:0x%I64X, saleId:0x%I64X, recipientPcId:0x%I64X",
               MODULE_NAME, fn, _tid, _deliveryId, _saleId, _recipientPcId);
    return true;
}

// 0x192a0
void RetrySingleDeliveryFailureManagementJob::ReplySuccess(Session const*& session) const
{
    wchar_t const* const fn = L"RetrySingleDeliveryFailureManagementJob::ReplySuccess";
    if (session == nullptr)
    {
        MANAGEMENT_JOB_CRASH(190, INVALID_SESSION, MODULE_NAME, fn, session);
        return;
    }
    session->Send("hqqqq", MarketManager_RetrySingleDeliveryFailureOkCmd, _tid, _deliveryId, _saleId, _recipientPcId);
    Log::Write(Log::LT_NOTICE, MANAGEMENT_JOB_FILE, 195,
               L"[%s], %s; sent retry single delivery failure success ack, tid:0x%I64X, deliveryId:0x%I64X, "
               L"saleId:0x%I64X, recipientPcId:0x%I64X",
               MODULE_NAME, fn, _tid, _deliveryId, _saleId, _recipientPcId);
}

// 0x193d0
void RetrySingleDeliveryFailureManagementJob::ReplyFailure(Session const*& session, short const& failReason) const
{
    wchar_t const* const fn = L"RetrySingleDeliveryFailureManagementJob::ReplyFailure";
    if (session == nullptr)
    {
        MANAGEMENT_JOB_CRASH(201, INVALID_SESSION, MODULE_NAME, fn, session);
        return;
    }
    session->Send("hqqqqE", MarketManager_RetrySingleDeliveryFailureFailCmd, _tid, _deliveryId, _saleId,
                  _recipientPcId, static_cast<int>(failReason));
    Log::Write(Log::LT_NOTICE, MANAGEMENT_JOB_FILE, 206,
               L"[%s], %s; sent retry single delivery failure failure ack, tid:0x%I64X, deliveryId:0x%I64X, "
               L"saleId:0x%I64X, recipientPcId:0x%I64X, failReason:%d",
               MODULE_NAME, fn, _tid, _deliveryId, _saleId, _recipientPcId, static_cast<int>(failReason));
}

// 0x19510
bool RetrySingleDeliveryFailureManagementJob::verifyParameter(short& failReason) const
{
    if (_deliveryId > 0 && _saleId > 0 && _recipientPcId > 0)
        return true;
    Log::Write(Log::LT_ERROR, MANAGEMENT_JOB_FILE, 214,
               L"[%s], %s; invalid parameter, tid:0x%I64X, deliveryId:0x%I64X, saleId:0x%I64X, recipientPcId:0x%I64X",
               MODULE_NAME, L"RetrySingleDeliveryFailureManagementJob::verifyParameter", _tid, _deliveryId, _saleId,
               _recipientPcId);
    failReason = MARKETMANAGER_RETRYSINGLEDELIVERYFAILUREFAIL_INVALID_PARAMETER;
    return false;
}

// 0x195a0
bool RetrySingleDeliveryFailureManagementJob::handleJob(short& failReason)
{
    wchar_t const* const fn = L"RetrySingleDeliveryFailureManagementJob::handleJob";
    DeliveryContext* const deliveryContext =
        MarketDealerDaemon::_instance->_deliveryContextManager->GetContext(_deliveryId);
    if (deliveryContext != nullptr)
    {
        Log::Write(Log::LT_ERROR, MANAGEMENT_JOB_FILE, 226,
                   L"[%s], %s; delivery context exists on memory, tid:0x%I64X, deliveryId:0x%I64X, saleId:0x%I64X, "
                   L"recipientPcId:0x%I64X",
                   MODULE_NAME, fn, _tid, _deliveryId, _saleId, _recipientPcId);
        failReason = MARKETMANAGER_RETRYSINGLEDELIVERYFAILUREFAIL_ALIVE_CONTEXT;
        deliveryContext->removeReferenceCount(MANAGEMENT_JOB_FILE, 228);
        return false;
    }

    int dbRetValue = 0;
    if (!MarketDB::ResetDeliveryFailureByManager(dbRetValue, *this))
    {
        Log::Write(Log::LT_ERROR, MANAGEMENT_JOB_FILE, 235,
                   L"[%s], %s; failed to reset delivery failure by manager [retry ready status], dbRetValue:%d, "
                   L"tid:0x%I64X, deliveryId:0x%I64X, saleId:0x%I64X, recipientPcId:0x%I64X",
                   MODULE_NAME, fn, dbRetValue, _tid, _deliveryId, _saleId, _recipientPcId);
        failReason = MARKETMANAGER_DB_ERROR;
        return false;
    }
    Log::Write(Log::LT_DEBUG, MANAGEMENT_JOB_FILE, 240,
               L"[%s], %s; succeeded to reset delivery failure by manager [retry ready status], tid:0x%I64X, "
               L"deliveryId:0x%I64X, saleId:0x%I64X, recipientPcId:0x%I64X",
               MODULE_NAME, fn, _tid, _deliveryId, _saleId, _recipientPcId);

    dbRetValue = 0;
    if (!MarketDB::LoadRetryReadySingleDelivery(dbRetValue, _deliveryId))
    {
        Log::Write(Log::LT_ERROR, MANAGEMENT_JOB_FILE, 246,
                   L"[%s], %s; failed to load retry ready single delivery, dbRetValue:%d, tid:0x%I64X, "
                   L"deliveryId:0x%I64X, saleId:0x%I64X, recipientPcId:0x%I64X",
                   MODULE_NAME, fn, dbRetValue, _tid, _deliveryId, _saleId, _recipientPcId);
        failReason = MARKETMANAGER_DB_ERROR;
        return false;
    }
    Log::Write(Log::LT_DEBUG, MANAGEMENT_JOB_FILE, 251,
               L"[%s], %s; succeeded to load retry ready single delivery, tid:0x%I64X, deliveryId:0x%I64X, "
               L"saleId:0x%I64X, recipientPcId:0x%I64X",
               MODULE_NAME, fn, _tid, _deliveryId, _saleId, _recipientPcId);
    return true;
}

// 0x197c0
bool RetryAllDeliveryFailureManagementJob::Initialize(Packet const*& packet)
{
    wchar_t const* const fn = L"RetryAllDeliveryFailureManagementJob::Initialize";
    if (packet == nullptr)
    {
        MANAGEMENT_JOB_CRASH(271, INVALID_PACKET, MODULE_NAME, fn, packet);
        return false;
    }
    short cmd = 0;
    if (packet->Decompose("hq", &cmd, &_tid) == 0)
    {
        Log::Write(Log::LT_ERROR, MANAGEMENT_JOB_FILE, 278, FAIL_DECOMPOSE, MODULE_NAME, fn);
        return false;
    }
    Log::Write(Log::LT_DEBUG, MANAGEMENT_JOB_FILE, 281, L"[%s], %s; decomposed packet, tid:0x%I64X", MODULE_NAME, fn,
               _tid);
    return true;
}

// 0x19900
void RetryAllDeliveryFailureManagementJob::ReplySuccess(Session const*& session) const
{
    wchar_t const* const fn = L"RetryAllDeliveryFailureManagementJob::ReplySuccess";
    if (session == nullptr)
    {
        MANAGEMENT_JOB_CRASH(289, INVALID_SESSION, MODULE_NAME, fn, session);
        return;
    }
    session->Send("hq", MarketManager_RetryAllDeliveryFailureOkCmd, _tid);
    Log::Write(Log::LT_NOTICE, MANAGEMENT_JOB_FILE, 294,
               L"[%s], %s; sent retry all delivery failure success ack, tid:0x%I64X", MODULE_NAME, fn, _tid);
}

// LIFT: inlined in HandleMarketManagerRetryAllDeliveryFailureReq (0x1ae50). No out-of-line copy in the exe.
void RetryAllDeliveryFailureManagementJob::ReplyFailure(Session const*& session, short const& failReason) const
{
    wchar_t const* const fn = L"RetryAllDeliveryFailureManagementJob::ReplyFailure";
    if (session == nullptr)
    {
        MANAGEMENT_JOB_CRASH(300, INVALID_SESSION, MODULE_NAME, fn, session);
        return;
    }
    session->Send("hqE", MarketManager_RetryAllDeliveryFailureFailCmd, _tid, static_cast<int>(failReason));
    Log::Write(Log::LT_NOTICE, MANAGEMENT_JOB_FILE, 305,
               L"[%s], %s; sent retry all delivery failure failure ack, tid:0x%I64X, failReason:%d", MODULE_NAME, fn,
               _tid, static_cast<int>(failReason));
}

// 0x36600
// LIFT: ICF folds this body with WindowConsole::controlHandler (return true).
bool RetryAllDeliveryFailureManagementJob::verifyParameter(short& /*failReason*/) const
{
    return true;
}

// 0x199f0
bool RetryAllDeliveryFailureManagementJob::handleJob(short& failReason)
{
    wchar_t const* const fn = L"RetryAllDeliveryFailureManagementJob::handleJob";
    int dbRetValue = 0;
    if (!MarketDB::ResetAllDeliveryFailureByManager(dbRetValue))
    {
        Log::Write(Log::LT_ERROR, MANAGEMENT_JOB_FILE, 313,
                   L"[%s], %s; failed to reset all delivery failure by manager [retry ready status], dbRetValue:%d, "
                   L"tid:0x%I64X",
                   MODULE_NAME, fn, dbRetValue, _tid);
        failReason = MARKETMANAGER_DB_ERROR;
        return false;
    }
    Log::Write(Log::LT_DEBUG, MANAGEMENT_JOB_FILE, 317,
               L"[%s], %s; succeeded to reset all delivery failure by manager [retry ready status], tid:0x%I64X",
               MODULE_NAME, fn, _tid);

    dbRetValue = 0;
    if (!MarketDB::LoadRetryReadyDeliveryList(dbRetValue))
    {
        Log::Write(Log::LT_ERROR, MANAGEMENT_JOB_FILE, 323,
                   L"[%s], %s; failed to load retry ready delivery list, dbRetValue:%d, tid:0x%I64X", MODULE_NAME, fn,
                   dbRetValue, _tid);
        failReason = MARKETMANAGER_DB_ERROR;
        return false;
    }
    Log::Write(Log::LT_DEBUG, MANAGEMENT_JOB_FILE, 327,
               L"[%s], %s; succeeded to load retry ready delivery list, tid:0x%I64X", MODULE_NAME, fn, _tid);
    return true;
}

// 0x19b10
bool UpdateStatusToReportFailureManagementJob::Initialize(Packet const*& packet)
{
    wchar_t const* const fn = L"UpdateStatusToReportFailureManagementJob::Initialize";
    if (packet == nullptr)
    {
        MANAGEMENT_JOB_CRASH(350, INVALID_PACKET, MODULE_NAME, fn, packet);
        return false;
    }
    short cmd = 0;
    if (packet->Decompose("hqqqq", &cmd, &_tid, &_deliveryId, &_saleId, &_recipientPcId) == 0)
    {
        Log::Write(Log::LT_ERROR, MANAGEMENT_JOB_FILE, 360, FAIL_DECOMPOSE, MODULE_NAME, fn);
        return false;
    }
    Log::Write(Log::LT_DEBUG, MANAGEMENT_JOB_FILE, 363,
               L"[%s], %s; decomposed packet, tid:0x%I64X, deliveryId:0x%I64X, saleId:0x%I64X, recipientPcId:0x%I64X",
               MODULE_NAME, fn, _tid, _deliveryId, _saleId, _recipientPcId);
    return true;
}

// 0x19c80
void UpdateStatusToReportFailureManagementJob::ReplySuccess(Session const*& session) const
{
    wchar_t const* const fn = L"UpdateStatusToReportFailureManagementJob::ReplySuccess";
    if (session == nullptr)
    {
        MANAGEMENT_JOB_CRASH(371, INVALID_SESSION, MODULE_NAME, fn, session);
        return;
    }
    session->Send("hqqqq", MarketManager_UpdateStatusToReportFailureOkCmd, _tid, _deliveryId, _saleId,
                  _recipientPcId);
    Log::Write(Log::LT_NOTICE, MANAGEMENT_JOB_FILE, 376,
               L"[%s], %s; sent job status update success ack [report failure status], tid:0x%I64X, "
               L"deliveryId:0x%I64X, saleId:0x%I64X, recipientPcId:0x%I64X",
               MODULE_NAME, fn, _tid, _deliveryId, _saleId, _recipientPcId);
}

// 0x19db0
void UpdateStatusToReportFailureManagementJob::ReplyFailure(Session const*& session, short const& failReason) const
{
    wchar_t const* const fn = L"UpdateStatusToReportFailureManagementJob::ReplyFailure";
    if (session == nullptr)
    {
        MANAGEMENT_JOB_CRASH(382, INVALID_SESSION, MODULE_NAME, fn, session);
        return;
    }
    session->Send("hqqqqE", MarketManager_UpdateStatusToReportFailureFailCmd, _tid, _deliveryId, _saleId,
                  _recipientPcId, static_cast<int>(failReason));
    Log::Write(Log::LT_NOTICE, MANAGEMENT_JOB_FILE, 387,
               L"[%s], %s; sent job status update failure ack [report failure status], tid:0x%I64X, "
               L"deliveryId:0x%I64X, saleId:0x%I64X, recipientPcId:0x%I64X, failReason:%d",
               MODULE_NAME, fn, _tid, _deliveryId, _saleId, _recipientPcId, static_cast<int>(failReason));
}

// 0x19ef0
bool UpdateStatusToReportFailureManagementJob::verifyParameter(short& failReason) const
{
    if (_deliveryId > 0 && _saleId > 0 && _recipientPcId > 0)
        return true;
    Log::Write(Log::LT_ERROR, MANAGEMENT_JOB_FILE, 395,
               L"[%s], %s; invalid parameter, tid:0x%I64X, deliveryId:0x%I64X, saleId:0x%I64X, recipientPcId:0x%I64X",
               MODULE_NAME, L"UpdateStatusToReportFailureManagementJob::verifyParameter", _tid, _deliveryId, _saleId,
               _recipientPcId);
    failReason = MARKETMANAGER_UPDATESTATUSTOREPORTFAILUREFAIL_INVALID_PARAMETER;
    return false;
}

// 0x19f80
bool UpdateStatusToReportFailureManagementJob::handleJob(short& failReason)
{
    wchar_t const* const fn = L"UpdateStatusToReportFailureManagementJob::handleJob";
    DeliveryContextManager* const deliveryContextManager = MarketDealerDaemon::_instance->_deliveryContextManager;
    DeliveryContext* const deliveryContext = deliveryContextManager->GetContext(_deliveryId);
    if (deliveryContext == nullptr)
    {
        // The delivery is not in memory: update the DB only.
        int dbRetValue = 0;
        if (!MarketDB::UpdateStatusToReportFailure(dbRetValue, *this))
        {
            Log::Write(Log::LT_ERROR, MANAGEMENT_JOB_FILE, 448,
                       L"[%s], %s; failed to update job status [report failure status], dbRetValue:%d, tid:0x%I64X, "
                       L"deliveryId:0x%I64X, saleId:0x%I64X, recipientPcId:0x%I64X",
                       MODULE_NAME, fn, dbRetValue, _tid, _deliveryId, _saleId, _recipientPcId);
            failReason = MARKETMANAGER_DB_ERROR;
            return false;
        }
    }
    else
    {
        deliveryContext->_lock.Enter();
        char const jobStatus = deliveryContext->_deliveryInfo._jobStatus;
        bool ok = false;
        if (jobStatus != DeliveryInfo::JOBSTATUS_REPORTING)
        {
            Log::Write(Log::LT_ERROR, MANAGEMENT_JOB_FILE, 412,
                       L"[%s], %s; invalid job status, tid:0x%I64X, deliveryId:0x%I64X, saleId:0x%I64X, "
                       L"recipientPcId:0x%I64X, jobStatus:%d",
                       MODULE_NAME, fn, _tid, _deliveryId, _saleId, _recipientPcId, jobStatus);
            failReason = MARKETMANAGER_UPDATESTATUSTOREPORTFAILUREFAIL_INVALID_JOB_STATUS;
        }
        else if (deliveryContext->_deliveryInfo._saleId != _saleId)
        {
            Log::Write(Log::LT_ERROR, MANAGEMENT_JOB_FILE, 418,
                       L"[%s], %s; sale id is not same, tid:0x%I64X, deliveryId:0x%I64X, saleId:0x%I64X, "
                       L"recipientPcId:0x%I64X, contextSaleId:0x%I64X",
                       MODULE_NAME, fn, _tid, _deliveryId, _saleId, _recipientPcId,
                       deliveryContext->_deliveryInfo._saleId);
            failReason = MARKETMANAGER_UPDATESTATUSTOREPORTFAILUREFAIL_SALE_ID_IS_NOT_SAME;
        }
        else if (deliveryContext->_deliveryInfo._recipient._participantPcId != _recipientPcId)
        {
            Log::Write(Log::LT_ERROR, MANAGEMENT_JOB_FILE, 424,
                       L"[%s], %s; recipient pcid is not same, tid:0x%I64X, deliveryId:0x%I64X, saleId:0x%I64X, "
                       L"recipientPcId:0x%I64X, contextPcId:0x%I64X",
                       MODULE_NAME, fn, _tid, _deliveryId, _saleId, _recipientPcId,
                       deliveryContext->_deliveryInfo._recipient._participantPcId);
            failReason = MARKETMANAGER_UPDATESTATUSTOREPORTFAILUREFAIL_RECIPIENT_PCID_IS_NOT_SAME;
        }
        else
        {
            int dbRetValue = 0;
            if (!MarketDB::UpdateStatusToReportFailure(dbRetValue, *this))
            {
                Log::Write(Log::LT_ERROR, MANAGEMENT_JOB_FILE, 435,
                           L"[%s], %s; failed to update job status [report failure status], dbRetValue:%d, "
                           L"tid:0x%I64X, deliveryId:0x%I64X, saleId:0x%I64X, recipientPcId:0x%I64X",
                           MODULE_NAME, fn, dbRetValue, _tid, _deliveryId, _saleId, _recipientPcId);
                failReason = MARKETMANAGER_DB_ERROR;
            }
            else
            {
                deliveryContext->_deliveryInfo._jobStatus = DeliveryInfo::JOBSTATUS_REPORT_FAILURE;
                ok = true;
            }
        }
        deliveryContext->_lock.Leave();
        if (!ok)
        {
            deliveryContext->removeReferenceCount(MANAGEMENT_JOB_FILE, 468);
            return false;
        }
        if (!deliveryContextManager->RemoveContext(_deliveryId))
        {
            MANAGEMENT_JOB_CRASH(457,
                                 L"== CRASH == [%s], %s; exception occurred; failed to remove delivery context, "
                                 L"tid:0x%I64X, deliveryId:0x%I64X, saleId:0x%I64X, recipientPcId:0x%I64X",
                                 MODULE_NAME, fn, _tid, _deliveryId, _saleId, _recipientPcId);
        }
        deliveryContext->removeReferenceCount(MANAGEMENT_JOB_FILE, 459);
    }
    Log::Write(Log::LT_DEBUG, MANAGEMENT_JOB_FILE, 462,
               L"[%s], %s; succeeded to update job status [report failure status], tid:0x%I64X, deliveryId:0x%I64X, "
               L"saleId:0x%I64X, recipientPcId:0x%I64X",
               MODULE_NAME, fn, _tid, _deliveryId, _saleId, _recipientPcId);
    return true;
}
