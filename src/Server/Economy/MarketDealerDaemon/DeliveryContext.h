// DeliveryContext.obj (MarketDealerDaemon PDB). Layouts from include/pdb/MarketDealerDaemon/types.h.
#pragma once
#include <stddef.h>
#include <map>
#include "RefCntObject.h"
#include "Lock.h"
#include "StlMemory.h"
#include "Participant.h"
#include "MarketStatement.h"

class FragmentPacket;
class SaleItemInfo;

class DeliveryInfo
{
public:
    enum Column
    {
        COLUMN_DELIVERY_ID = 0,
        COLUMN_DELIVERY_REASON = 1,
        COLUMN_SALE_ID = 2,
        COLUMN_PAWN_ID = 3,
        COLUMN_PAWN_OWNER_SERVICE_ID = 4,
        COLUMN_PAWN_OWNER_WID = 5,
        COLUMN_PAWN_OWNER_PCID = 6,
        COLUMN_PAWN_OWNER_NAME = 7,
        COLUMN_RECIPIENT_WID = 8,
        COLUMN_RECIPIENT_PCID = 9,
        COLUMN_RECIPIENT_NAME = 10,
        COLUMN_MARKET_STATEMENT_TITLE = 11,
        COLUMN_MARKET_STATEMENT_BODY = 12,
        COLUMN_JOB_STATUS = 13,
        COLUMN_MONEY_AMOUNT = 14,
        MAX_COLUMN_COUNT = 15,
    };
    enum JobStatus
    {
        JOBSTATUS_INVALID_STATUS = 0,
        JOBSTATUS_DELIVERY_READY = 1,
        JOBSTATUS_RETRY_READY = 2,
        JOBSTATUS_REPORTING = 3,
        JOBSTATUS_REPORT_SUCCESS = 4,
        JOBSTATUS_PAWN_REMOVAL_SUCCESS = 5,
        JOBSTATUS_POST_REGISTRATION_SUCCESS = 6,
        JOBSTATUS_REPORT_FAILURE = 7,
        JOBSTATUS_PAWN_REMOVAL_FAILURE = 8,
        JOBSTATUS_POST_REGISTRATION_FAILURE = 9,
        JOBSTATUS_MAX = 10,
    };

    DeliveryInfo();  // 0x7100

    long long _deliveryId;
    char _deliveryReason;
    long long _saleId;
    long long _pawnId;
    long long _pawnServiceId;
    Participant _pawnOwner;
    Participant _recipient;
    MarketStatement _marketStatement;
    char _jobStatus;
};
static_assert(sizeof(DeliveryInfo) == 0xA00, "sizeof DeliveryInfo");
static_assert(offsetof(DeliveryInfo, _pawnOwner) == 0x28, "DeliveryInfo::_pawnOwner");
static_assert(offsetof(DeliveryInfo, _recipient) == 0xD0, "DeliveryInfo::_recipient");
static_assert(offsetof(DeliveryInfo, _marketStatement) == 0x178, "DeliveryInfo::_marketStatement");
static_assert(offsetof(DeliveryInfo, _jobStatus) == 0x9FC, "DeliveryInfo::_jobStatus");

class DeliveryItemInfo
{
public:
    char _itemType;
    char _itemCommonCategory;
    long long _itemInstanceId;
    int _itemDataId;
    short _itemLevel;
    long long _itemAmount;
    wchar_t _itemXmlData[1025];
};
static_assert(sizeof(DeliveryItemInfo) == 0x828, "sizeof DeliveryItemInfo");
static_assert(offsetof(DeliveryItemInfo, _itemXmlData) == 0x20, "DeliveryItemInfo::_itemXmlData");

class DeliveryContext : public DynamicRefCntObj
{
public:
    DeliveryContext(DeliveryInfo const& deliveryInfo, SaleItemInfo const& saleItemInfo);  // 0x72a0
    DeliveryContext(DeliveryInfo const& deliveryInfo, long long moneyAmount);             // 0x7370
    virtual ~DeliveryContext();  // Inlined in the scalar deleting destructor 0x70c0.

    bool ComposeReportPacket(FragmentPacket& packet) const;  // 0x7420

    CriticalSection _lock;
    DeliveryInfo _deliveryInfo;
    DeliveryItemInfo _deliveryItemInfo;
    long long _reportTime;
};
static_assert(sizeof(DeliveryContext) == 0x1270, "sizeof DeliveryContext");
static_assert(offsetof(DeliveryContext, _lock) == 0x18, "DeliveryContext::_lock");
static_assert(offsetof(DeliveryContext, _deliveryInfo) == 0x40, "DeliveryContext::_deliveryInfo");
static_assert(offsetof(DeliveryContext, _deliveryItemInfo) == 0xA40, "DeliveryContext::_deliveryItemInfo");
static_assert(offsetof(DeliveryContext, _reportTime) == 0x1268, "DeliveryContext::_reportTime");

class DeliveryContextManager
{
public:
    // LIFT: no typedef name in the PDB. Member type: std::map<__int64,DeliveryContext *,...,StlAllocator<...,2>>.
    typedef std::map<long long, DeliveryContext*, std::less<long long>,
                     StlAllocator<std::pair<long long const, DeliveryContext*>, 2> > Container;

    bool InitContextManager();                                 // 0x7710
    DeliveryContext* GetContext(long long deliveryId) const;   // 0x78a0. Adds a reference.
    bool AddContext(DeliveryContext* const deliveryContext);   // 0x7b10
    bool RemoveContext(long long deliveryId);                  // 0x7d70

    int const _bucketCount;
    CriticalSection* _lockList;
    Container* _containerList;
    long volatile _contextCount;  // The PDB type is int. The code uses Interlocked calls on it.

    // LIFT: inlined in the MarketDealerDaemon code (later card).
    explicit DeliveryContextManager(int bucketCount)
        : _bucketCount(bucketCount), _lockList(nullptr), _containerList(nullptr), _contextCount(0)
    {
    }
};
static_assert(sizeof(DeliveryContextManager) == 0x20, "sizeof DeliveryContextManager");
static_assert(offsetof(DeliveryContextManager, _lockList) == 0x8, "DeliveryContextManager::_lockList");
static_assert(offsetof(DeliveryContextManager, _containerList) == 0x10, "DeliveryContextManager::_containerList");
static_assert(offsetof(DeliveryContextManager, _contextCount) == 0x18, "DeliveryContextManager::_contextCount");
