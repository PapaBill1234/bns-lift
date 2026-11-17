// MarketDB.obj (MarketDealerDaemon PDB). The functions of this module come from a later card.
#pragma once

class MarketDB
{
public:
    static bool const UpdateStatusToReporting(int& dbRetValue, long long deliveryId);  // 0x24e90. Later card.
};
