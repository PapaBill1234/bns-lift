// ExtendJumpingCharacterCreationQuotaJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "ExtendJumpingCharacterCreationQuotaJob.h"
#include "LiftStub.h"

// 0x2a300
LobbyJobDef const* ExtendJumpingCharacterCreationQuotaJob::GetDefinition() const
{
    LIFT_STUB(0x2a300);
}

// 0x2a310
void ExtendJumpingCharacterCreationQuotaJob::deallocate_me(void*, wchar_t const*, int)
{
    LIFT_STUB(0x2a310);
}

// 0x2a360
LobbyJobDef const* UpgradeJumpingCharacterStateJob::GetDefinition() const
{
    LIFT_STUB(0x2a360);
}

// 0x2a370
void UpgradeJumpingCharacterStateJob::deallocate_me(void*, wchar_t const*, int)
{
    LIFT_STUB(0x2a370);
}

// 0x2a3c0
void* ExtendJumpingCharacterCreationQuotaJob::_vtbl()
{
    LIFT_STUB(0x2a3c0);
}

// 0x2a440
ExtendJumpingCharacterCreationQuotaJob::ExtendJumpingCharacterCreationQuotaJob(CliSession* owner) : CliSessionJob(owner)  // LIFT: base init only (fix7 layout)
{
    LIFT_STUB(0x2a440);
}

// 0x2a4c0
ExtendJumpingCharacterCreationQuotaJob::~ExtendJumpingCharacterCreationQuotaJob()
{
    LIFT_STUB(0x2a4c0);
}

// 0x2a540
bool ExtendJumpingCharacterCreationQuotaJob::work(int, void*)
{
    LIFT_STUB(0x2a540);
}

// 0x2a6a0
bool ExtendJumpingCharacterCreationQuotaJob::init(void*)
{
    LIFT_STUB(0x2a6a0);
}

// 0x2b0a0
bool ExtendJumpingCharacterCreationQuotaJob::checkAccountInventoryItem()
{
    LIFT_STUB(0x2b0a0);
}

// 0x2b220
bool ExtendJumpingCharacterCreationQuotaJob::checkAccountInventoryItemOk(void*)
{
    LIFT_STUB(0x2b220);
}

// 0x2b640
bool ExtendJumpingCharacterCreationQuotaJob::checkAccountInventoryItemFail(void*)
{
    LIFT_STUB(0x2b640);
}

// 0x2b890
bool ExtendJumpingCharacterCreationQuotaJob::checkAccountInventoryItemTimeout()
{
    LIFT_STUB(0x2b890);
}

// 0x2b990
bool ExtendJumpingCharacterCreationQuotaJob::registerServiceEntry()
{
    LIFT_STUB(0x2b990);
}

// 0x2bdf0
bool ExtendJumpingCharacterCreationQuotaJob::tryConsumeAccountInventoryItem()
{
    LIFT_STUB(0x2bdf0);
}

// 0x2bf80
bool ExtendJumpingCharacterCreationQuotaJob::tryConsumeAccountInventoryItemOk(void*)
{
    LIFT_STUB(0x2bf80);
}

// 0x2c220
bool ExtendJumpingCharacterCreationQuotaJob::tryConsumeAccountInventoryItemFail(void*)
{
    LIFT_STUB(0x2c220);
}

// 0x2c450
bool ExtendJumpingCharacterCreationQuotaJob::tryConsumeAccountInventoryItemTimeout()
{
    LIFT_STUB(0x2c450);
}

// 0x2c550
bool ExtendJumpingCharacterCreationQuotaJob::extendJumpingCharacterCreationQuota()
{
    LIFT_STUB(0x2c550);
}

// 0x2c730
bool ExtendJumpingCharacterCreationQuotaJob::finConsumeAccountInventoryItem()
{
    LIFT_STUB(0x2c730);
}

// 0x2c8c0
bool ExtendJumpingCharacterCreationQuotaJob::finConsumeAccountInventoryItemOk(void*)
{
    LIFT_STUB(0x2c8c0);
}

// 0x2cb60
bool ExtendJumpingCharacterCreationQuotaJob::finConsumeAccountInventoryItemFail(void*)
{
    LIFT_STUB(0x2cb60);
}

// 0x2cd90
bool ExtendJumpingCharacterCreationQuotaJob::finConsumeAccountInventoryItemTimeout()
{
    LIFT_STUB(0x2cd90);
}

// 0x2ce90
bool ExtendJumpingCharacterCreationQuotaJob::finServiceEntry()
{
    LIFT_STUB(0x2ce90);
}

// 0x2d140
void ExtendJumpingCharacterCreationQuotaJob::sendFailReason(short)
{
    LIFT_STUB(0x2d140);
}

// 0x2d440
void* UpgradeJumpingCharacterStateJob::_vtbl()
{
    LIFT_STUB(0x2d440);
}

// 0x2d4c0
UpgradeJumpingCharacterStateJob::UpgradeJumpingCharacterStateJob(CliSession* owner) : CliSessionJob(owner)  // LIFT: base init only (fix7 layout)
{
    LIFT_STUB(0x2d4c0);
}

// 0x2d550
bool UpgradeJumpingCharacterStateJob::work(int, void*)
{
    LIFT_STUB(0x2d550);
}

// 0x2d580
bool UpgradeJumpingCharacterStateJob::init(int, void*)
{
    LIFT_STUB(0x2d580);
}

// 0x2d9c0
bool UpgradeJumpingCharacterStateJob::upgradeJumpingCharacterState()
{
    LIFT_STUB(0x2d9c0);
}
