// MarketManagerServerSideHandlerList (MarketDealerDaemon .data). Data tables only.
#include "ManagerChannel.h"
#include "ManagerPacketHandler.h"

// 0xb5260
wchar_t const* MarketManagerCommandList[16] = {
    nullptr,
    L"Hello",
    L"HelloOk",
    L"Hello-fail",
    L"SuspendSale",
    L"SuspendSaleOk",
    L"SuspendSaleFail",
    L"RetrySingleDeliveryFailure",
    L"RetrySingleDeliveryFailureOk",
    L"RetrySingleDeliveryFailureFail",
    L"RetryAllDeliveryFailure",
    L"RetryAllDeliveryFailureOk",
    L"RetryAllDeliveryFailureFail",
    L"UpdateStatusToReportFailure",
    L"UpdateStatusToReportFailureOk",
    L"UpdateStatusToReportFailureFail",
};

// 0xb52e0
Daemon::PacketHandler MarketManagerPacketServerSideHandlerList[16] = {
    nullptr,
    HandleMarketManagerHelloReq,
    nullptr,
    nullptr,
    HandleMarketManagerSuspendSaleReq,
    nullptr,
    nullptr,
    HandleMarketManagerRetrySingleDeliveryFailureReq,
    nullptr,
    nullptr,
    HandleMarketManagerRetryAllDeliveryFailureReq,
    nullptr,
    nullptr,
    HandleMarketManagerUpdateStatusToReportFailureReq,
    nullptr,
    nullptr,
};

// 0xb6df0 (.bss: all entries are null)
Daemon::PacketHandler MarketManagerPacketServerSideFragmentHandlerList[16] = {};
