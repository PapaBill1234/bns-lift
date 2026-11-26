// ExtendJumpingCharacterCreationQuotaJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "ExtendJumpingCharacterCreationQuotaJob.h"
#include "LiftStub.h"
#include "ObjectPoolLobbyDaemon.h"

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
ExtendJumpingCharacterCreationQuotaJob::ExtendJumpingCharacterCreationQuotaJob(CliSession* owner)
    : CliSessionJob(owner), _tran(nullptr), _lgate(nullptr), _gamed(nullptr), _gamedTid(0), _acciv(nullptr), _labelId(0),
      _itemInstanceId(0), _itemDataId(0), _serviceId(0)
{
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
UpgradeJumpingCharacterStateJob::UpgradeJumpingCharacterStateJob(CliSession* owner)
    : CliSessionJob(owner), _gamed(nullptr), _gamedTid(0), _wid(0), _pcId(0), _jumpingCharacterState(0), _consumeCreationQuota(false)
{
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

// LIFT: ExtendJumpingCharacterCreationQuotaJob::_pool (.data RVA 0x2040a0). Dynamic initializer 0x11dc60, atexit destructor 0x11eb00. The original static data
// holds id 1, objsize sizeof(ExtendJumpingCharacterCreationQuotaJob) and desc L"ExtendJumpingCharacterCreationQuotaJob".
ObjPool ExtendJumpingCharacterCreationQuotaJob::_pool(1, sizeof(ExtendJumpingCharacterCreationQuotaJob), L"ExtendJumpingCharacterCreationQuotaJob");

// LIFT: UpgradeJumpingCharacterStateJob::_pool (.data RVA 0x204150). Dynamic initializer 0x11dcb0, atexit destructor 0x11eb40. The original static data
// holds id 1, objsize sizeof(UpgradeJumpingCharacterStateJob) and desc L"UpgradeJumpingCharacterStateJob".
ObjPool UpgradeJumpingCharacterStateJob::_pool(1, sizeof(UpgradeJumpingCharacterStateJob), L"UpgradeJumpingCharacterStateJob");
