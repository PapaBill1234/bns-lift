// PurchaseContext.obj (MarketDealerDaemon PDB). Not in the pseudocode export: vftable 0x9d6f0 slot 4.
#include "PurchaseContext.h"

// 0x63c60 (ICF fold: mov eax, 1; ret)
int const PurchaseContext::GetDealingType()
{
    return DEALINGTYPE_PURCHASE;
}
