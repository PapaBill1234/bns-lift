// TakeGoodsJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "TakeGoodsJob.h"
#include "LiftStub.h"

// 0x79f00
LobbyJobDef const* TakeGoodsJob::GetDefinition() const
{
    LIFT_STUB(0x79f00);
}

// 0x79f10
void TakeGoodsJob::deallocate_me(void*, wchar_t const*, int)
{
    LIFT_STUB(0x79f10);
}

// 0x79f60
void* TakeGoodsJob::_vtbl()
{
    LIFT_STUB(0x79f60);
}

// 0x79fe0
TakeGoodsJob::TakeGoodsJob(CliSession*, LobbyGateChannel*, unsigned long long)
{
    LIFT_STUB(0x79fe0);
}

// 0x7a080
TakeGoodsJob::~TakeGoodsJob()
{
    LIFT_STUB(0x7a080);
}

// 0x7a0f0
bool TakeGoodsJob::work(int, void*)
{
    LIFT_STUB(0x7a0f0);
}

// 0x7a190
bool TakeGoodsJob::init()
{
    LIFT_STUB(0x7a190);
}

// 0x7a540
bool TakeGoodsJob::takeGoodsReq()
{
    LIFT_STUB(0x7a540);
}

// 0x7a6d0
bool TakeGoodsJob::takeGoodsOk(void*)
{
    LIFT_STUB(0x7a6d0);
}

// 0x7a8d0
bool TakeGoodsJob::takeGoodsFail(void*)
{
    LIFT_STUB(0x7a8d0);
}

// 0x7ab30
bool TakeGoodsJob::takeGoodsTimeout()
{
    LIFT_STUB(0x7ab30);
}
