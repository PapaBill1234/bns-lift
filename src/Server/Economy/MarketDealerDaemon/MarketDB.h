// MarketDB.obj (MarketDealerDaemon PDB). The functions of this module come from a later card.
#pragma once

class SaleIncomeTaxRateTable;
class GrossIncomeTaxRateTable;

class MarketDB
{
public:
    static bool const UpdateStatusToReporting(int& dbRetValue, long long deliveryId);  // 0x24e90. Later card.
    // ❓ Return type: PDB type 0x1626 (taken as bool const, as UpdateStatusToReporting). Later card.
    static bool const SetSaleIncomeTaxRateTable(int& dbRetValue, SaleIncomeTaxRateTable& taxRateTable);
    static bool const SetGrossIncomeTaxRateTable(int& dbRetValue, GrossIncomeTaxRateTable& taxRateTable);
};
