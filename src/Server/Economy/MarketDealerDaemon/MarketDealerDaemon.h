// MarketDealerDaemon.obj (MarketDealerDaemon PDB). Layouts from include/pdb/MarketDealerDaemon/types.h.
// The functions of this module come from a later card. Only the data layout is here now.
#pragma once
#include <stddef.h>
#include "Daemon.h"

class SessionHandler;
class AgentChannelManager;
class SaleContextManager;
class SaleTimeContextManager;
class DeliveryContextManager;
class TaxRateDataManager;
class TimeoutTimer;
class DeliveryTimer;

class MarketDealerConfig
{
public:
    enum DumpType
    {
        DUMP_NONE = 0,
        DUMP_MINIMAL = 1,
        DUMP_FULL = 2,
        DUMP_MAX = 3,
    };

    wchar_t* _rootPath;
    wchar_t* _logPath;
    wchar_t* _dataPath;
    char* _certFile;
    int _workerThreadCount;
    int _maxAgentSessionCount;
    int _dumpType;
    int _timeoutCheckInterval;
    int _deliveryCheckInterval;
    int _agentListenPort;
    int _managerListenPort;
    int _serviceWorldId;
    int _ruleResetTime;
    int _concurrentSaleCount;
    int _accumulatedSaleCount;
    int _concurrentBidCount;
    int _bidPriceUnitRatio;
    int _searchPageSize;
};
static_assert(sizeof(MarketDealerConfig) == 0x58, "sizeof MarketDealerConfig");
static_assert(offsetof(MarketDealerConfig, _bidPriceUnitRatio) == 0x50, "MarketDealerConfig::_bidPriceUnitRatio");

class MarketDealerDaemon : public Daemon
{
public:
    enum DB
    {
        MARKET_DB_ID = 1,
    };
    enum MarketEvent
    {
        MARKETEVENT_INSTANT_SALE_TIMEOUT_EVENT = 0x80,
        MARKETEVENT_AUCTION_TIMEOUT_EVENT = 0x81,
        MARKETEVENT_PACKET_PUMP_EVENT = 0x82,
    };
    enum MarketTimer
    {
        MARKETTIMER_TIMEOUT_TIMER = 1,
        MARKETTIMER_DELIVERY_TIMER = 2,
    };
    enum Port
    {
        AGENT_PORT_ID = 1,
        MANAGER_PORT_ID = 2,
    };

    // TODO(lift-marketdealerdaemon-2): virtual functions of MarketDealerDaemon (later card).

    MarketDealerConfig const* _config;
    SessionHandler* _sessionHandler[25];
    AgentChannelManager* _agentChannelManager;
    SaleContextManager* _saleContextManager;
    SaleTimeContextManager* _saleTimeContextManager;
    DeliveryContextManager* _deliveryContextManager;
    TaxRateDataManager* _taxRateDataManager;
    TimeoutTimer* _timeoutTimer;
    DeliveryTimer* _deliveryTimer;

    static MarketDealerDaemon* _instance;
};
static_assert(sizeof(MarketDealerDaemon) == 0x850, "sizeof MarketDealerDaemon");
static_assert(offsetof(MarketDealerDaemon, _config) == 0x748, "MarketDealerDaemon::_config");
static_assert(offsetof(MarketDealerDaemon, _agentChannelManager) == 0x818, "MarketDealerDaemon::_agentChannelManager");
static_assert(offsetof(MarketDealerDaemon, _deliveryTimer) == 0x848, "MarketDealerDaemon::_deliveryTimer");
