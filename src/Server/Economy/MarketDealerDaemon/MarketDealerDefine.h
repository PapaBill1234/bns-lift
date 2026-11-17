// MarketDealerDefine.h (MarketDealerDaemon PDB). No code in the PDB. Values from include/pdb/MarketDealerDaemon/types.h.
// ❓ The PDB gives no header for this enum. Only the values that the lifted code uses are here.
#pragma once

enum MarketDealerFailReason
{
    MARKETDEALER_NO_ERROR = 0,
    MARKETDEALER_UNKNOWN_ERROR = 1,
    MARKETDEALER_SYSTEM_ERROR = 2,
    MARKETDEALER_DB_ERROR = 3,
    MARKETDEALER_HELLOFAIL_INVALID_CONNECTION_TYPE = 4,
    MARKETDEALER_HELLOFAIL_INVALID_PACKET_VERSION = 5,
    MARKETDEALER_RETRIEVESALELISTFAIL_INVALID_PARAMETER = 6,
    MARKETDEALER_RETRIEVEBIDLISTFAIL_INVALID_PARAMETER = 7,
    MARKETDEALER_RETRIEVEBIDRANKSTATUSFAIL_INVALID_PARAMETER = 8,
    MARKETDEALER_RESERVESALEFAIL_INVALID_PARAMETER = 9,
    MARKETDEALER_RESERVESALEFAIL_EXCEEDED_CONCURRENT_SALE_COUNT = 10,
    MARKETDEALER_RESERVESALEFAIL_EXCEEDED_ACCUMULATED_SALE_COUNT = 11,
    MARKETDEALER_CANCELSALERESERVATIONFAIL_INVALID_PARAMETER = 12,
    MARKETDEALER_CANCELSALERESERVATIONFAIL_NO_SUCH_SALE = 13,
    MARKETDEALER_REGISTERSALEFAIL_INVALID_PARAMETER = 14,
    MARKETDEALER_REGISTERSALEFAIL_NO_SUCH_SALE = 15,
    MARKETDEALER_REGISTERSALEFAIL_PCID_IS_NOT_SAME = 16,
    MARKETDEALER_REGISTERSALEFAIL_INVALID_ITEM_DATA = 17,
    MARKETDEALER_REGISTERSALEFAIL_INVALID_MONEY_ITEM_DATA = 18,
    MARKETDEALER_REGISTERSALEFAIL_INVALID_DEFAULT_ITEM_DATA = 19,
    MARKETDEALER_REGISTERSALEFAIL_INVALID_CUSTOM_ITEM_DATA = 20,
    MARKETDEALER_REGISTERSALEFAIL_INVALID_SALE_STATUS = 21,
    MARKETDEALER_UPDATESALEPRICEFAIL_INVALID_PARAMETER = 22,
    MARKETDEALER_UPDATESALEPRICEFAIL_NO_SUCH_SALE = 23,
    MARKETDEALER_UPDATESALEPRICEFAIL_PCID_IS_NOT_SAME = 24,
    MARKETDEALER_UPDATESALEPRICEFAIL_INVALID_SALE_STATUS = 25,
    MARKETDEALER_UPDATESALEPRICEFAIL_EXISTS_BID = 26,
    MARKETDEALER_ABANDONSALEFAIL_INVALID_PARAMETER = 27,
    MARKETDEALER_ABANDONSALEFAIL_NO_SUCH_SALE = 28,
    MARKETDEALER_ABANDONSALEFAIL_PCID_IS_NOT_SAME = 29,
    MARKETDEALER_ABANDONSALEFAIL_INVALID_SALE_STATUS = 30,
    MARKETDEALER_ABANDONSALEFAIL_EXISTS_BID = 31,
    // TODO(lift-marketdealerdaemon-2): the other values (types.h:577).
};

// PDB enum EconomySaleType (types.h:367).
enum EconomySaleType : int
{
    ECONOMY_SALETYPE_INVALID_TYPE = 0x0,
    ECONOMY_SALETYPE_AUCTION = 0x1,
    ECONOMY_SALETYPE_INSTANT_SALE = 0x2,
    ECONOMY_SALETYPE_GLOBAL_MAX = 0x3,
};

// PDB enum MarketDealerPacketCommand (types.h:655). Only the values that the lifted code uses are here.
enum MarketDealerPacketCommand
{
    MarketDealer_RetrieveSaleListReqCmd = 0x4,
    MarketDealer_RetrieveSaleListOkCmd = 0x5,
    MarketDealer_RetrieveSaleListFailCmd = 0x6,
    MarketDealer_RetrieveBidListReqCmd = 0x7,
    MarketDealer_RetrieveBidListOkCmd = 0x8,
    MarketDealer_RetrieveBidListFailCmd = 0x9,
    MarketDealer_RetrieveBidRankStatusReqCmd = 0xA,
    MarketDealer_RetrieveBidRankStatusOkCmd = 0xB,
    MarketDealer_RetrieveBidRankStatusFailCmd = 0xC,
    MarketDealer_ReserveSaleReqCmd = 0xD,
    MarketDealer_ReserveSaleOkCmd = 0xE,
    MarketDealer_ReserveSaleFailCmd = 0xF,
    MarketDealer_CancelSaleReservationReqCmd = 0x10,
    MarketDealer_CancelSaleReservationOkCmd = 0x11,
    MarketDealer_CancelSaleReservationFailCmd = 0x12,
    MarketDealer_RegisterSaleReqCmd = 0x13,
    MarketDealer_RegisterSaleOkCmd = 0x14,
    MarketDealer_RegisterSaleFailCmd = 0x15,
    MarketDealer_UpdateSalePriceReqCmd = 0x16,
    MarketDealer_UpdateSalePriceOkCmd = 0x17,
    MarketDealer_UpdateSalePriceFailCmd = 0x18,
    MarketDealer_AbandonSaleReqCmd = 0x19,
    MarketDealer_AbandonSaleOkCmd = 0x1A,
    MarketDealer_AbandonSaleFailCmd = 0x1B,
};

// PDB enum MarketDealerBidRankStatus (types.h:532).
enum MarketDealerBidRankStatus
{
    MARKETDEALER_BIDRANKSTATUS_INVALID_STATUS = 0x0,
    MARKETDEALER_BIDRANKSTATUS_NO_SUCH_SALE = 0x1,
    MARKETDEALER_BIDRANKSTATUS_TOP_BIDDER = 0x2,
    MARKETDEALER_BIDRANKSTATUS_NO_TOP_BIDDER = 0x3,
};

// PDB enum MarketDealerOrderType (types.h:648).
enum MarketDealerOrderType
{
    MARKETDEALER_ORDERTYPE_INVALID_TYPE = 0x0,
    MARKETDEALER_ORDERTYPE_ASCENDING = 0x1,
    MARKETDEALER_ORDERTYPE_DESCENDING = 0x2,
    MARKETDEALER_ORDERTYPE_MAX_TYPE = 0x3,
};

// PDB enum MarketDealerSearchType (types.h:734). "SERACH" is the PDB spelling.
enum MarketDealerSearchType
{
    MARKETDEALER_SEARCHTYPE_INVALID_TYPE = 0x0,
    MARKETDEALER_SEARCHTYPE_FIRST_SERACH = 0x1,
    MARKETDEALER_SEARCHTYPE_NEXT_SEARCH = 0x2,
    MARKETDEALER_SEARCHTYPE_PREV_SEARCH = 0x3,
    MARKETDEALER_SEARCHTYPE_MAX_TYPE = 0x4,
};

// PDB enum 0x3127 (manager channel packets).
enum MarketManagerPacketCommand
{
    MarketManager_HelloReqCmd = 1,
    MarketManager_HelloOkCmd = 2,
    MarketManager_HelloFailCmd = 3,
    MarketManager_SuspendSaleReqCmd = 4,
    MarketManager_SuspendSaleOkCmd = 5,
    MarketManager_SuspendSaleFailCmd = 6,
    MarketManager_RetrySingleDeliveryFailureReqCmd = 7,
    MarketManager_RetrySingleDeliveryFailureOkCmd = 8,
    MarketManager_RetrySingleDeliveryFailureFailCmd = 9,
    MarketManager_RetryAllDeliveryFailureReqCmd = 10,
    MarketManager_RetryAllDeliveryFailureOkCmd = 11,
    MarketManager_RetryAllDeliveryFailureFailCmd = 12,
    MarketManager_UpdateStatusToReportFailureReqCmd = 13,
    MarketManager_UpdateStatusToReportFailureOkCmd = 14,
    MarketManager_UpdateStatusToReportFailureFailCmd = 15,
    MARKETMANAGER_CMD_MAX = 16,
};

enum MarketManagerFailReason
{
    MARKETMANAGER_NO_ERROR = 0,
    MARKETMANAGER_UNKNOWN_ERROR = 1,
    MARKETMANAGER_SYSTEM_ERROR = 2,
    MARKETMANAGER_DB_ERROR = 3,
    MARKETMANAGER_HELLOFAIL_INVALID_PACKET_VERSION = 4,
    MARKETMANAGER_SUSPENDSALEFAIL_INVALID_PARAMETER = 5,
    MARKETMANAGER_SUSPENDSALEFAIL_NO_SUCH_SALE = 6,
    MARKETMANAGER_SUSPENDSALEFAIL_INVALID_SALE_STATUS = 7,
    MARKETMANAGER_SUSPENDSALEFAIL_PCID_IS_NOT_SAME = 8,
    MARKETMANAGER_RETRYSINGLEDELIVERYFAILUREFAIL_INVALID_PARAMETER = 9,
    MARKETMANAGER_RETRYSINGLEDELIVERYFAILUREFAIL_ALIVE_CONTEXT = 10,
    MARKETMANAGER_UPDATESTATUSTOREPORTFAILUREFAIL_INVALID_PARAMETER = 11,
    MARKETMANAGER_UPDATESTATUSTOREPORTFAILUREFAIL_INVALID_JOB_STATUS = 12,
    MARKETMANAGER_UPDATESTATUSTOREPORTFAILUREFAIL_SALE_ID_IS_NOT_SAME = 13,
    MARKETMANAGER_UPDATESTATUSTOREPORTFAILUREFAIL_RECIPIENT_PCID_IS_NOT_SAME = 14,
    MARKETMANAGER_GLOBAL_MAX = 15,
};
