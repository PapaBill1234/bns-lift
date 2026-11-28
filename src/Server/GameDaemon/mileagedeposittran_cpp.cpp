// mileagedeposittran_cpp.cpp: mileagedeposittran.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "mileagedeposittran.h"
#include "user.h"
#include "../BloodLib/include/Memory.h"
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:??1UnsentMileageDepositManager@@AEAA@XZ")  // LIFT: dead-strip keep (no live caller yet)

#define MILEAGEDEPOSITTRAN_CPP_FILE L"e:\\dailybuild02\\gamedaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\gamedaemon\\MileageDepositTran.cpp"

// 0x16b9d0
__cdecl MileageDepositTran::MileageDepositTran(::User *)
{
    LIFT_STUB(0x16b9d0);
}

// 0x16bb30
bool __cdecl MileageDepositTran::work(int, void *)
{
    LIFT_STUB(0x16bb30);
}

// 0x16bbe0
bool __cdecl MileageDepositTran::init(int, void *)
{
    LIFT_STUB(0x16bbe0);
}

// 0x16bf00
bool __cdecl MileageDepositTran::mileageDepositTranOk(void *)
{
    LIFT_STUB(0x16bf00);
}

// 0x16ca90
bool __cdecl MileageDepositTran::mileageDepositTranFail(void *)
{
    LIFT_STUB(0x16ca90);
}

// 0x16cf30
__cdecl UnsentMileageDepositManager::~UnsentMileageDepositManager(void)
{
    if (_mileageCount != 0 && _mileageList != nullptr)
        Memory::_Manager[2]->Free(_mileageList, MILEAGEDEPOSITTRAN_CPP_FILE, 453);
}

// 0x16cf70
bool __cdecl UnsentMileageDepositManager::Initialize(::FragmentPacketConcatenater *)
{
    LIFT_STUB(0x16cf70);
}

// 0x16d290
void __cdecl UnsentMileageDepositManager::SendMileageDeposit(void)
{
    LIFT_STUB(0x16d290);
}
