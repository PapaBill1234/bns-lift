// instantpaymenttran_h.cpp: instantpaymenttran.h (GameDaemon PDB, 2019 + PDB). The getters and DataId leaves are lifted.
// LIFT: the _def data is not lifted yet. The empty GameTranDef of the header stands in for the PDB data.
#include "instantpaymenttran.h"
#include "LiftStub.h"

// 0x110700
__cdecl InstantPaymentTryBuyCollectionItemsParam::InstantPaymentTryBuyCollectionItemsParam(void)
{
    LIFT_STUB(0x110700);
}

// 0x1107c0
::GameTranDef const * __cdecl InstantPaymentTran::GetDefinition(void) const
{
    return &_def;
}

// 0x1107d0
int __cdecl InstantPaymentJob::DataId(void)
{
    return DataId(0);
}

// 0x1ee480
int __cdecl InstantPaymentDrawSlateNewStoneSubJob::DataId(short)
{
    LIFT_STUB(0x1ee480);  // LIFT: returns _cashId; the member needs the InstantPaymentJob base layout
}

// 0x350300
__cdecl InstantPaymentBuyCollectionItemsSubJob::InstantPaymentBuyCollectionItemsSubJob(::InstantPaymentTran *)
{
    LIFT_STUB(0x350300);
}

::GameTranDef InstantPaymentTran::_def;
