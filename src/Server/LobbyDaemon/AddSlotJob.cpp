// AddSlotJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "AddSlotJob.h"
#include "LiftStub.h"

// 0xd1e0
LobbyJobDef const* AddSlotJob::GetDefinition() const
{
    LIFT_STUB(0xd1e0);
}

// 0xd1f0
void AddSlotJob::deallocate_me(void*, wchar_t const*, int)
{
    LIFT_STUB(0xd1f0);
}

// 0xd240
void* AddSlotJob::_vtbl()
{
    LIFT_STUB(0xd240);
}

// 0xd2c0
AddSlotJob::AddSlotJob(CliSession*)
{
    LIFT_STUB(0xd2c0);
}

// 0xd340
AddSlotJob::~AddSlotJob()
{
    LIFT_STUB(0xd340);
}

// 0xd3b0
bool AddSlotJob::work(int, void*)
{
    LIFT_STUB(0xd3b0);
}

// 0xd570
bool AddSlotJob::init(void*)
{
    LIFT_STUB(0xd570);
}

// 0xdc90
bool AddSlotJob::checkAccountInventoryItem()
{
    LIFT_STUB(0xdc90);
}

// 0xde30
bool AddSlotJob::checkAccountInventoryItemOk(void*)
{
    LIFT_STUB(0xde30);
}

// 0xe2a0
bool AddSlotJob::checkAccountInventoryItemFail(void*)
{
    LIFT_STUB(0xe2a0);
}

// 0xe500
bool AddSlotJob::checkAccountInventoryItemTimeout()
{
    LIFT_STUB(0xe500);
}

// 0xe610
bool AddSlotJob::checkSlotCapacity()
{
    LIFT_STUB(0xe610);
}

// 0xe8b0
bool AddSlotJob::checkSlotCapacityAck(void*)
{
    LIFT_STUB(0xe8b0);
}

// 0xedb0
bool AddSlotJob::checkSlotCapacityExpire()
{
    LIFT_STUB(0xedb0);
}

// 0xeec0
bool AddSlotJob::registerServiceEntry()
{
    LIFT_STUB(0xeec0);
}

// 0xf370
bool AddSlotJob::tryConsumeAccountInventoryItem()
{
    LIFT_STUB(0xf370);
}

// 0xf510
bool AddSlotJob::tryConsumeAccountInventoryItemOk(void*)
{
    LIFT_STUB(0xf510);
}

// 0xf7d0
bool AddSlotJob::tryConsumeAccountInventoryItemFail(void*)
{
    LIFT_STUB(0xf7d0);
}

// 0xfa20
bool AddSlotJob::tryConsumeAccountInventoryItemTimeout()
{
    LIFT_STUB(0xfa20);
}

// 0xfb30
bool AddSlotJob::createSlot()
{
    LIFT_STUB(0xfb30);
}

// 0xfe00
bool AddSlotJob::createSlotAck(void*)
{
    LIFT_STUB(0xfe00);
}

// 0x105a0
bool AddSlotJob::createSlotExpire()
{
    LIFT_STUB(0x105a0);
}

// 0x106b0
bool AddSlotJob::finConsumeAccountInventoryItem()
{
    LIFT_STUB(0x106b0);
}

// 0x10850
bool AddSlotJob::finConsumeAccountInventoryItemOk(void*)
{
    LIFT_STUB(0x10850);
}

// 0x10b10
bool AddSlotJob::finConsumeAccountInventoryItemFail(void*)
{
    LIFT_STUB(0x10b10);
}

// 0x10d60
bool AddSlotJob::finConsumeAccountInventoryItemTimeout()
{
    LIFT_STUB(0x10d60);
}

// 0x10e70
bool AddSlotJob::finServiceEntry()
{
    LIFT_STUB(0x10e70);
}
