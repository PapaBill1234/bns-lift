// DeliveryRelation (MarketDealerDaemon PDB). No code in the PDB. Layout from include/pdb/MarketDealerDaemon/types.h.
// MarketDB::ExpireAuction (0x24490) fills an array of it.
#pragma once
#include <stddef.h>
#include "MarketStatement.h"

class DeliveryRelation
{
public:
    enum Column : int
    {
        COLUMN_DELIVERY_ID = 0x0,
        COLUMN_DELIVERY_REASON = 0x1,
        COLUMN_PAWN_OWNER_SERVICE_ID = 0x2,
        COLUMN_PAWN_OWNER_PCID = 0x3,
        COLUMN_RECIPIENT_PCID = 0x4,
        COLUMN_MARKETSTATEMENT_TITLE = 0x5,
        COLUMN_MARKETSTATEMENT_BODY = 0x6,
        COLUMN_MONEY_AMOUNT = 0x7,
        MAX_COLUMN_COUNT = 0x8,
    };

    long long _deliveryId;
    char _deliveryReason;
    long long _pawnOwnerServiceId;
    long long _pawnOwnerPcId;
    long long _recipientPcId;
    MarketStatement _marketStatement;
    long long _moneyAmount;
};
static_assert(sizeof(DeliveryRelation) == 0x8B8, "sizeof DeliveryRelation");
static_assert(offsetof(DeliveryRelation, _deliveryReason) == 0x8, "DeliveryRelation::_deliveryReason");
static_assert(offsetof(DeliveryRelation, _marketStatement) == 0x28, "DeliveryRelation::_marketStatement");
static_assert(offsetof(DeliveryRelation, _moneyAmount) == 0x8B0, "DeliveryRelation::_moneyAmount");
