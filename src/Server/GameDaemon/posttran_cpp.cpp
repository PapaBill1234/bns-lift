// posttran_cpp.cpp: posttran.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "posttran.h"
#include "pc.h"
#include "zone.h"
#include "LiftStub.h"

// 0x197c10
bool __cdecl MarkExpressPostTran::work(int, void *)
{
    LIFT_STUB(0x197c10);
}

// 0x197d50
bool __cdecl MarkExpressPostTran::charge(void)
{
    LIFT_STUB(0x197d50);
}

// 0x197fd0
bool __cdecl MarkExpressPostTran::markReq(void)
{
    LIFT_STUB(0x197fd0);
}

// 0x198060
bool __cdecl MarkExpressPostTran::markOk(void *)
{
    LIFT_STUB(0x198060);
}

// 0x1983a0
bool __cdecl MarkExpressPostTran::markFail(void *)
{
    LIFT_STUB(0x1983a0);
}

// 0x1986e0
bool __cdecl MarkExpressPostTran::abort(short)
{
    LIFT_STUB(0x1986e0);
}

// 0x1987a0
bool __cdecl DetachPostAttachmentTran_IndetachFixed::work(int, void *)
{
    LIFT_STUB(0x1987a0);
}

// 0x1988a0
bool __cdecl DetachPostAttachmentTran_IndetachFixed::detachReq(void)
{
    LIFT_STUB(0x1988a0);
}

// 0x198c50
bool __cdecl DetachPostAttachmentTran_IndetachFixed::reserveBagPosOk(void *)
{
    LIFT_STUB(0x198c50);
}

// 0x198cf0
bool __cdecl DetachPostAttachmentTran_IndetachFixed::detachOk(void *)
{
    LIFT_STUB(0x198cf0);
}

// 0x199130
bool __cdecl DetachPostAttachmentTran_IndetachFixed::detachFail(void *)
{
    LIFT_STUB(0x199130);
}

// 0x199570
bool __cdecl DetachPostAttachmentTran_IndetachFixed::abort(short)
{
    LIFT_STUB(0x199570);
}

// 0x199600
short __cdecl DetachPostAttachmentTran_IndetachFixed::getGameFailReason(short)
{
    LIFT_STUB(0x199600);
}

// 0x1996c0
::DeliverPostTran::CHECK_POST_ZS_RESULT_TYPE __cdecl DeliverPostTran::checkAndPostForExecutingInZS(int, bool *)
{
    LIFT_STUB(0x1996c0);
}

// 0x199b40
bool __cdecl DeliverPostTran::work(int, void *)
{
    LIFT_STUB(0x199b40);
}

// 0x199e40
bool __cdecl DeliverPostTran::init(int, void *)
{
    LIFT_STUB(0x199e40);
}

// 0x19a0c0
bool __cdecl DeliverPostTran::checkPostTitleFromUicReq(void)
{
    LIFT_STUB(0x19a0c0);
}

// 0x19a2c0
bool __cdecl DeliverPostTran::checkPostTitleFromUicOk(void *)
{
    LIFT_STUB(0x19a2c0);
}

// 0x19a3a0
bool __cdecl DeliverPostTran::checkPostTitleFromUicFail(void *)
{
    LIFT_STUB(0x19a3a0);
}

// 0x19a4a0
bool __cdecl DeliverPostTran::checkPostContentFromUicReq(void)
{
    LIFT_STUB(0x19a4a0);
}

// 0x19a6a0
bool __cdecl DeliverPostTran::checkPostContentFromUicOk(void *)
{
    LIFT_STUB(0x19a6a0);
}

// 0x19a780
bool __cdecl DeliverPostTran::checkPostContentFromUicFail(void *)
{
    LIFT_STUB(0x19a780);
}

// 0x19a880
bool __cdecl DeliverPostTran::checkPcInven(void)
{
    LIFT_STUB(0x19a880);
}

// 0x19c650
bool __cdecl DeliverPostTran::retrieveCharacterInfoReq(void)
{
    LIFT_STUB(0x19c650);
}

// 0x19c9e0
bool __cdecl DeliverPostTran::retrieveCharacterInfoOk(void *)
{
    LIFT_STUB(0x19c9e0);
}

// 0x19cac0
bool __cdecl DeliverPostTran::retrieveCharacterInfoFail(void *)
{
    LIFT_STUB(0x19cac0);
}

// 0x19cc50
bool __cdecl DeliverPostTran::checkPostCapacityReq(void)
{
    LIFT_STUB(0x19cc50);
}

// 0x19cf60
bool __cdecl DeliverPostTran::checkPostCapacityOk(void *)
{
    LIFT_STUB(0x19cf60);
}

// 0x19d000
bool __cdecl DeliverPostTran::checkPostCapacityFail(void *)
{
    LIFT_STUB(0x19d000);
}

// 0x19d1b0
bool __cdecl DeliverPostTran::deliverPost(void)
{
    LIFT_STUB(0x19d1b0);
}

// 0x19ed50
bool __cdecl DeliverPostTran::cancel(void)
{
    LIFT_STUB(0x19ed50);
}

// 0x19f160
bool __cdecl DeliverPostTran::expired(void)
{
    LIFT_STUB(0x19f160);
}

// 0x19f1b0
__cdecl DeliverPostWithTranTask::~DeliverPostWithTranTask(void)
{
    LIFT_STUB(0x19f1b0);
}

// 0x19f210
bool __cdecl DeliverPostWithTranTask::Initialize(::Zone *, ::Pc *, ::DeliverPostTran *, int)
{
    LIFT_STUB(0x19f210);
}

// 0x19f360
void __cdecl DeliverPostWithTranTask::TimerExpired(unsigned int, long)
{
    LIFT_STUB(0x19f360);
}

// 0x19f3a0
void __cdecl DeliverPostWithTranTask::start(void)
{
    LIFT_STUB(0x19f3a0);
}

// 0x19f410
bool __cdecl ResumeDeliverPostTranAfterUICTask::Initialize(::Zone *, ::Pc *, unsigned __int64, int, wchar_t const *)
{
    LIFT_STUB(0x19f410);
}

// 0x19f500
void __cdecl ResumeDeliverPostTranAfterUICTask::TimerExpired(unsigned int, long)
{
    LIFT_STUB(0x19f500);
}

// 0x19f540
void __cdecl ResumeDeliverPostTranAfterUICTask::start(void)
{
    LIFT_STUB(0x19f540);
}
