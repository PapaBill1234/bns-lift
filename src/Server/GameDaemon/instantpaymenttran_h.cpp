// instantpaymenttran_h.cpp: instantpaymenttran.h (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
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
    LIFT_STUB(0x1107c0);
}

// 0x1107d0
int __cdecl InstantPaymentJob::DataId(void)
{
    LIFT_STUB(0x1107d0);
}

// 0x1ee480
int __cdecl InstantPaymentDrawSlateNewStoneSubJob::DataId(short)
{
    LIFT_STUB(0x1ee480);
}

// 0x350300
__cdecl InstantPaymentBuyCollectionItemsSubJob::InstantPaymentBuyCollectionItemsSubJob(::InstantPaymentTran *)
{
    LIFT_STUB(0x350300);
}
