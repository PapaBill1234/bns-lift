// TryEnterGameWorldJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "TryEnterGameWorldJob.h"
#include "LiftStub.h"

// 0x7b840
LobbyJobDef const* TryEnterGameWorldJob::GetDefinition() const
{
    LIFT_STUB(0x7b840);
}

// 0x7b850
void TryEnterGameWorldJob::deallocate_me(void*, wchar_t const*, int)
{
    LIFT_STUB(0x7b850);
}

// 0x7b8a0
void* TryEnterGameWorldJob::_vtbl()
{
    LIFT_STUB(0x7b8a0);
}

// 0x7b920
TryEnterGameWorldJob::TryEnterGameWorldJob(CliSession* owner) : CliSessionJob(owner)  // LIFT: base init only (fix7 layout)
{
    LIFT_STUB(0x7b920);
}

// 0x7b9a0
TryEnterGameWorldJob::~TryEnterGameWorldJob()
{
    LIFT_STUB(0x7b9a0);
}

// 0x7ba40
bool TryEnterGameWorldJob::Initialize(LobbyGateChannel*, id128 const&)
{
    LIFT_STUB(0x7ba40);
}

// 0x7bb70
bool TryEnterGameWorldJob::work(int, void*)
{
    LIFT_STUB(0x7bb70);
}

// 0x7bcf0
bool TryEnterGameWorldJob::init()
{
    LIFT_STUB(0x7bcf0);
}

// 0x7c660
bool TryEnterGameWorldJob::restorePcReq()
{
    LIFT_STUB(0x7c660);
}

// 0x7c820
bool TryEnterGameWorldJob::restorePcOk()
{
    LIFT_STUB(0x7c820);
}

// 0x7cba0
bool TryEnterGameWorldJob::restorePcFail(short*)
{
    LIFT_STUB(0x7cba0);
}

// 0x7cfe0
bool TryEnterGameWorldJob::restorePcExpired()
{
    LIFT_STUB(0x7cfe0);
}

// 0x7d0e0
bool TryEnterGameWorldJob::checkSecondPasswordStatus()
{
    LIFT_STUB(0x7d0e0);
}

// 0x7d400
bool TryEnterGameWorldJob::checkSecondPasswordStatusResponse(void*)
{
    LIFT_STUB(0x7d400);
}

// 0x7d900
bool TryEnterGameWorldJob::checkSecondPasswordStatusExpire()
{
    LIFT_STUB(0x7d900);
}

// 0x7daa0
bool TryEnterGameWorldJob::checkSecondPasswordVerified()
{
    LIFT_STUB(0x7daa0);
}

// 0x7ddc0
bool TryEnterGameWorldJob::checkSecondPasswordVerifiedResponse(void*)
{
    LIFT_STUB(0x7ddc0);
}

// 0x7e0f0
bool TryEnterGameWorldJob::checkSecondPasswordVerifiedExpire()
{
    LIFT_STUB(0x7e0f0);
}

// 0x7e290
bool TryEnterGameWorldJob::requestGetSlot()
{
    LIFT_STUB(0x7e290);
}

// 0x7e570
bool TryEnterGameWorldJob::responseGetSlot(void*)
{
    LIFT_STUB(0x7e570);
}

// 0x7eb60
bool TryEnterGameWorldJob::expireGetSlot()
{
    LIFT_STUB(0x7eb60);
}

// 0x7ecf0
bool TryEnterGameWorldJob::requestChargeGetInfo()
{
    LIFT_STUB(0x7ecf0);
}

// 0x7efd0
bool TryEnterGameWorldJob::responseChargeGetInfo(void*)
{
    LIFT_STUB(0x7efd0);
}

// 0x7fa60
bool TryEnterGameWorldJob::expireChargeGetInfo()
{
    LIFT_STUB(0x7fa60);
}

// 0x7fbf0
bool TryEnterGameWorldJob::tryEnterGameWorld()
{
    LIFT_STUB(0x7fbf0);
}

// 0x7ffe0
bool TryEnterGameWorldJob::issueGameWorldToken()
{
    LIFT_STUB(0x7ffe0);
}
