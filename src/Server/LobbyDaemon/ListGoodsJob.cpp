// ListGoodsJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "ListGoodsJob.h"
#include "LiftStub.h"

// 0x54ee0
LobbyJobDef const* ListGoodsJob::GetDefinition() const
{
    LIFT_STUB(0x54ee0);
}

// 0x54ef0
void ListGoodsJob::deallocate_me(void*, wchar_t const*, int)
{
    LIFT_STUB(0x54ef0);
}

// 0x54f40
void* ListGoodsJob::_vtbl()
{
    LIFT_STUB(0x54f40);
}

// 0x54fc0
ListGoodsJob::ListGoodsJob(CliSession*, LobbyGateChannel*)
{
    LIFT_STUB(0x54fc0);
}

// 0x55050
ListGoodsJob::~ListGoodsJob()
{
    LIFT_STUB(0x55050);
}

// 0x550c0
bool ListGoodsJob::work(int, void*)
{
    LIFT_STUB(0x550c0);
}

// 0x55160
bool ListGoodsJob::init(void*)
{
    LIFT_STUB(0x55160);
}

// 0x55490
bool ListGoodsJob::listGoodsReq()
{
    LIFT_STUB(0x55490);
}

// 0x55620
bool ListGoodsJob::listGoodsOk(void*)
{
    LIFT_STUB(0x55620);
}

// 0x55820
bool ListGoodsJob::listGoodsFail(void*)
{
    LIFT_STUB(0x55820);
}

// 0x55a20
bool ListGoodsJob::listGoodsTimeout()
{
    LIFT_STUB(0x55a20);
}
