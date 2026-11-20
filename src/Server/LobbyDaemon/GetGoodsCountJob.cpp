// GetGoodsCountJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "GetGoodsCountJob.h"
#include "LiftStub.h"

// 0x51460
LobbyJobDef const* GetGoodsCountJob::GetDefinition() const
{
    LIFT_STUB(0x51460);
}

// 0x51470
void GetGoodsCountJob::deallocate_me(void*, wchar_t const*, int)
{
    LIFT_STUB(0x51470);
}

// 0x514c0
void* GetGoodsCountJob::_vtbl()
{
    LIFT_STUB(0x514c0);
}

// 0x51540
GetGoodsCountJob::GetGoodsCountJob(CliSession*, LobbyGateChannel*)
{
    LIFT_STUB(0x51540);
}

// 0x515d0
GetGoodsCountJob::~GetGoodsCountJob()
{
    LIFT_STUB(0x515d0);
}

// 0x51640
bool GetGoodsCountJob::work(int, void*)
{
    LIFT_STUB(0x51640);
}

// 0x516e0
bool GetGoodsCountJob::init()
{
    LIFT_STUB(0x516e0);
}

// 0x51a00
bool GetGoodsCountJob::getGoodsCountReq()
{
    LIFT_STUB(0x51a00);
}

// 0x51b80
bool GetGoodsCountJob::getGoodsCountOk(void*)
{
    LIFT_STUB(0x51b80);
}

// 0x51d60
bool GetGoodsCountJob::getGoodsCountFail(void*)
{
    LIFT_STUB(0x51d60);
}

// 0x51f60
bool GetGoodsCountJob::getGoodsCountTimeout()
{
    LIFT_STUB(0x51f60);
}
