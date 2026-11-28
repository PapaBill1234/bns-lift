// instantpaymenttran_cpp.cpp: instantpaymenttran.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "instantpaymenttran.h"
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:?tryAbortImpl@InstantPaymentJob@@MEAA_NF@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?DataId@InstantPaymentBuyCollectionItemsSubJob@@UEAAHF@Z")  // LIFT: dead-strip keep (no live caller yet)

// 0x132640
__cdecl InstantPaymentTran::~InstantPaymentTran(void)
{
    LIFT_STUB(0x132640);
}

// 0x1326b0
bool __cdecl InstantPaymentTran::work(int, void *)
{
    LIFT_STUB(0x1326b0);
}

// 0x132850
bool __cdecl InstantPaymentJob::init(int, void *)
{
    LIFT_STUB(0x132850);
}

// 0x1328f0
bool __cdecl InstantPaymentJob::procBeforePurchase(int, void *)
{
    LIFT_STUB(0x1328f0);
}

// 0x132910
bool __cdecl InstantPaymentJob::apply(int, void *)
{
    LIFT_STUB(0x132910);
}

// 0x132930
bool __cdecl InstantPaymentJob::tryInstantPaymentOk(void *)
{
    LIFT_STUB(0x132930);
}

// 0x133070
bool __cdecl InstantPaymentJob::tryInstantPaymentFail(short)
{
    LIFT_STUB(0x133070);
}

// 0x1334b0
bool __cdecl InstantPaymentJob::tryInstantPaymentReq(void *)
{
    LIFT_STUB(0x1334b0);
}

// 0x133900
bool __cdecl InstantPaymentJob::tryAbortImpl(short)
{
    postFailProc();
    return true;
}

// 0x133920
bool __cdecl InstantPaymentJob::finishInstantPaymentReq(void *)
{
    LIFT_STUB(0x133920);
}

// 0x133de0
bool __cdecl InstantPaymentJob::finishInstantPaymentOk(void *)
{
    LIFT_STUB(0x133de0);
}

// 0x134240
bool __cdecl InstantPaymentJob::finishInstantPaymentFail(short)
{
    LIFT_STUB(0x134240);
}

// 0x134390
bool __cdecl InstantPaymentJob::finishAbort(void *)
{
    LIFT_STUB(0x134390);
}

// 0x1343b0
short __cdecl InstantPaymentJob::getGameFailReason(void)
{
    LIFT_STUB(0x1343b0);
}

// 0x1344e0
int __cdecl InstantPaymentRandomStoreDrawSubJob::DataId(short)
{
    LIFT_STUB(0x1344e0);
}

// 0x134590
void __cdecl InstantPaymentRandomStoreDrawSubJob::sendFailPacket(short)
{
    LIFT_STUB(0x134590);
}

// 0x134620
bool __cdecl InstantPaymentRandomStoreDrawSubJob::tryInstantPaymentOkImpl(void *)
{
    LIFT_STUB(0x134620);
}

// 0x134b30
int __cdecl InstantPaymentRandomStoreExpandSubJob::DataId(short)
{
    LIFT_STUB(0x134b30);
}

// 0x134c00
void __cdecl InstantPaymentRandomStoreExpandSubJob::sendFailPacket(short)
{
    LIFT_STUB(0x134c00);
}

// 0x134ca0
bool __cdecl InstantPaymentRandomStoreExpandSubJob::tryInstantPaymentOkImpl(void *)
{
    LIFT_STUB(0x134ca0);
}

// 0x1351e0
void __cdecl InstantPaymentTransformItemSubJob::setExtraParam(void *)
{
    LIFT_STUB(0x1351e0);
}

// 0x135260
void __cdecl InstantPaymentTransformItemSubJob::sendFailPacket(short)
{
    LIFT_STUB(0x135260);
}

// 0x1352a0
bool __cdecl InstantPaymentTransformItemSubJob::tryInstantPaymentOkImpl(void *)
{
    LIFT_STUB(0x1352a0);
}

// 0x135970
bool __cdecl InstantPaymentTransformItemSubJob::tryInstantPaymentFailImpl(void)
{
    LIFT_STUB(0x135970);
}

// 0x135e20
void __cdecl InstantPaymentBuyCollectionItemsSubJob::setExtraParam(void *)
{
    LIFT_STUB(0x135e20);
}

// 0x135e80
void __cdecl InstantPaymentBuyCollectionItemsSubJob::sendFailPacket(short)
{
    LIFT_STUB(0x135e80);
}

// 0x135f00
int __cdecl InstantPaymentBuyCollectionItemsSubJob::DataId(short idx)
{
    return _buyParam.buyItem[idx].chargeItem;
}

// 0x135f10
bool __cdecl InstantPaymentBuyCollectionItemsSubJob::tryInstantPaymentOkImpl(void *)
{
    LIFT_STUB(0x135f10);
}

// 0x136510
bool __cdecl InstantPaymentBuyCollectionItemsSubJob::tryInstantPaymentFailImpl(void)
{
    LIFT_STUB(0x136510);
}

// 0x136950
bool __cdecl InstantPaymentDrawSlateNewStoneSubJob::tryInstantPaymentOkImpl(void *)
{
    LIFT_STUB(0x136950);
}

// 0x137390
void __cdecl InstantPaymentDrawSlateNewStoneSubJob::sendFailPacket(short)
{
    LIFT_STUB(0x137390);
}
