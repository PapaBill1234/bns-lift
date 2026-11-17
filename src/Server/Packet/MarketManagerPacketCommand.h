// LIFT: file. The PDB has no source path for this enum. Name and values are from include/pdb/MarketDealerDaemon/types.h
// (MarketDealerDaemon PDB, enum 0x3127). The command names are in MarketManagerCommandList (0xb5260).
// Use these names in Send and Decompose calls. Do not write bare command numbers.
#pragma once

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
