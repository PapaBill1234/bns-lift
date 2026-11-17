// ManagementJobContext.obj (MarketDealerDaemon PDB). Jobs of the manager channel.
// The base class JobContext is in JobContext.h (JobContext.obj, card lift-marketdealerdaemon-8).
#pragma once

#include <stddef.h>
#include "JobContext.h"

class Packet;
class Session;

class SuspendSaleManagementJob : public JobContext
{
public:
    enum Param : int
    {
        PARAM_RETURN_VALUE = 0x0,
        PARAM_SALE_ID = 0x1,
        PARAM_SELLER_PCID = 0x2,
        MAX_PARAM_COUNT = 0x3,
    };
    virtual ~SuspendSaleManagementJob();
    virtual bool verifyParameter(short& failReason) const;                    // 0x18c00
    virtual bool handleJob(short& failReason);                                // 0x18c80
    bool Initialize(Packet const*& packet);                                   // 0x18980
    void ReplyFailure(Session const*& session, short const& failReason) const;  // 0x18ae0

    unsigned long long _tid;
    long long _saleId;
    long long _sellerPcId;
};
static_assert(sizeof(SuspendSaleManagementJob) == 0x20, "sizeof SuspendSaleManagementJob");
static_assert(offsetof(SuspendSaleManagementJob, _sellerPcId) == 0x18, "SuspendSaleManagementJob::_sellerPcId");

class RetrySingleDeliveryFailureManagementJob : public JobContext
{
public:
    enum Param : int
    {
        PARAM_RETURN_VALUE = 0x0,
        PARAM_DELIVERY_ID = 0x1,
        PARAM_SALE_ID = 0x2,
        PARAM_RECIPIENT_PCID = 0x3,
        MAX_PARAM_COUNT = 0x4,
    };
    virtual ~RetrySingleDeliveryFailureManagementJob();
    virtual bool verifyParameter(short& failReason) const;                    // 0x19510
    virtual bool handleJob(short& failReason);                                // 0x195a0
    bool Initialize(Packet const*& packet);                                   // 0x19130
    void ReplySuccess(Session const*& session) const;                         // 0x192a0
    void ReplyFailure(Session const*& session, short const& failReason) const;  // 0x193d0

    unsigned long long _tid;
    long long _deliveryId;
    long long _saleId;
    long long _recipientPcId;
};
static_assert(sizeof(RetrySingleDeliveryFailureManagementJob) == 0x28, "sizeof RetrySingleDeliveryFailureManagementJob");
static_assert(offsetof(RetrySingleDeliveryFailureManagementJob, _recipientPcId) == 0x20,
              "RetrySingleDeliveryFailureManagementJob::_recipientPcId");

class RetryAllDeliveryFailureManagementJob : public JobContext
{
public:
    virtual ~RetryAllDeliveryFailureManagementJob();
    virtual bool verifyParameter(short& failReason) const;  // 0x36600
    virtual bool handleJob(short& failReason);              // 0x199f0
    bool Initialize(Packet const*& packet);                 // 0x197c0
    void ReplySuccess(Session const*& session) const;       // 0x19900

    unsigned long long _tid;
};
static_assert(sizeof(RetryAllDeliveryFailureManagementJob) == 0x10, "sizeof RetryAllDeliveryFailureManagementJob");

class UpdateStatusToReportFailureManagementJob : public JobContext
{
public:
    enum Param : int
    {
        PARAM_RETURN_VALUE = 0x0,
        PARAM_DELIVERY_ID = 0x1,
        MAX_PARAM_COUNT = 0x2,
    };
    virtual ~UpdateStatusToReportFailureManagementJob();
    virtual bool verifyParameter(short& failReason) const;                    // 0x19ef0
    virtual bool handleJob(short& failReason);                                // 0x19f80
    bool Initialize(Packet const*& packet);                                   // 0x19b10
    void ReplySuccess(Session const*& session) const;                         // 0x19c80
    void ReplyFailure(Session const*& session, short const& failReason) const;  // 0x19db0

    unsigned long long _tid;
    long long _deliveryId;
    long long _saleId;
    long long _recipientPcId;
};
static_assert(sizeof(UpdateStatusToReportFailureManagementJob) == 0x28, "sizeof UpdateStatusToReportFailureManagementJob");
static_assert(offsetof(UpdateStatusToReportFailureManagementJob, _recipientPcId) == 0x20,
              "UpdateStatusToReportFailureManagementJob::_recipientPcId");
