// guildcraft.cpp: guildcraft.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "guildcraft.h"
#include "LiftStub.h"

static_assert(sizeof(GuildCraft) == 0x1848, "sizeof GuildCraft");

#pragma comment(linker, "/INCLUDE:?GetAsseintGuildCraftQuota@GuildCraft@@QEAADD@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?MakeGuildCraft@GuildCraft@@QEAAXHFH_J0@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?EnableDonationGuildCraft@GuildCraft@@QEAA_NXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?IsCompletedGuildCraftDonation@GuildCraft@@QEAA_NXZ")  // LIFT: dead-strip keep (no live caller yet)

// 0x1133d0
__cdecl GuildCraft::GuildCraft(void)
{
    LIFT_STUB(0x1133d0);
}

// 0x1134f0
void __cdecl GuildCraft::Initialize(unsigned __int64, unsigned int, char, char, char, unsigned __int64, wchar_t const *, __int64)
{
    LIFT_STUB(0x1134f0);
}

// 0x113810
bool __cdecl GuildCraft::InitializeFromDBData(::GuildCraftInfo const *)
{
    LIFT_STUB(0x113810);
}

// 0x113f00
bool __cdecl GuildCraft::TakeGuildCraft(short, int &)
{
    LIFT_STUB(0x113f00);
}

// 0x113ff0
bool __cdecl GuildCraft::FetchGuildCraftInfo(::FragmentPacket &)
{
    LIFT_STUB(0x113ff0);
}

// 0x1140e0
bool __cdecl GuildCraft::fetchGuildCraftInfo(::FragmentPacket &)
{
    LIFT_STUB(0x1140e0);
}

// 0x114200
bool __cdecl GuildCraft::fetchGuildCraftAssentients(::FragmentPacket &)
{
    LIFT_STUB(0x114200);
}

// 0x1143f0
bool __cdecl GuildCraft::fetchDonationNormalMaterials(::FragmentPacket &)
{
    LIFT_STUB(0x1143f0);
}

// 0x114580
bool __cdecl GuildCraft::fetchDonationBrandMaterials(::FragmentPacket &)
{
    LIFT_STUB(0x114580);
}

// 0x114710
short __cdecl GuildCraft::EnableAssentGuildCraft(unsigned __int64, char, short)
{
    LIFT_STUB(0x114710);
}

// 0x114960
char __cdecl GuildCraft::GetAsseintGuildCraftQuota(char productionType)
{
    char quota = 0;
    AcquireSRWLockShared(&_srwLock);
    for (int i = 0; i < 7; ++i)
    {
        if (_assentients[i].productionType == productionType)
        {
            quota = _assentients[i].quota;
            break;
        }
    }
    ReleaseSRWLockShared(&_srwLock);
    return quota;
}

// 0x1149f0
void __cdecl GuildCraft::AddAssentient(unsigned __int64, char, wchar_t const *)
{
    LIFT_STUB(0x1149f0);
}

// 0x114ad0
bool __cdecl GuildCraft::EnableMakeGuildCraft(char, ::GuildCraft::Product &)
{
    LIFT_STUB(0x114ad0);
}

// 0x114b90
void __cdecl GuildCraft::MakeGuildCraft(int productDataId, short productLevel, int productTotalAmount, __int64 startTime, __int64 endTime)
{
    AcquireSRWLockExclusive(&_srwLock);
    _state = 3;  // ❓ PDB enumerator name of the craft state is not looked up.
    _startTime = startTime;
    _productDataId = productDataId;
    _productLevel = productLevel;
    _productTotalAmount = productTotalAmount;
    _productRemainAmount = productTotalAmount;
    _endTime = endTime;
    ReleaseSRWLockExclusive(&_srwLock);
}

// 0x114c30
bool __cdecl GuildCraft::EnableDonationGuildCraft(void)
{
    AcquireSRWLockShared(&_srwLock);
    bool enable = _state == 1;  // ❓ PDB enumerator name of the craft state is not looked up.
    ReleaseSRWLockShared(&_srwLock);
    return enable;
}

// 0x114c80
bool __cdecl GuildCraft::EnableDonationItem(unsigned int, short)
{
    LIFT_STUB(0x114c80);
}

// 0x114d20
bool __cdecl GuildCraft::EnableDonationBrandItem(unsigned __int64, char)
{
    LIFT_STUB(0x114d20);
}

// 0x114dc0
short __cdecl GuildCraft::GetDonationItemQuota(unsigned int, short)
{
    LIFT_STUB(0x114dc0);
}

// 0x114e70
short __cdecl GuildCraft::GetDonationBrandItemQuota(unsigned __int64, char)
{
    LIFT_STUB(0x114e70);
}

// 0x114f20
bool __cdecl GuildCraft::EnableDonationNormalMaterial(unsigned int, short, int)
{
    LIFT_STUB(0x114f20);
}

// 0x115020
unsigned __int64 __cdecl GuildCraft::AddDonationNormalMaterial(unsigned int, short, int)
{
    LIFT_STUB(0x115020);
}

// 0x1150d0
unsigned __int64 __cdecl GuildCraft::AddDonationBrandMaterial(unsigned int, char, int)
{
    LIFT_STUB(0x1150d0);
}

// 0x115190
bool __cdecl GuildCraft::IsCompletedGuildCraftDonation(void)
{
    bool completed = false;
    AcquireSRWLockExclusive(&_srwLock);
    if (_assentientsCount == _assentientsCompletedCount && _normalMaterialsCount == _normalMaterialsCompletedCount &&
        _brandMaterialsCount == _brandMaterialsCompletedCount)
    {
        _state = 2;  // ❓ PDB enumerator name of the craft state is not looked up.
        completed = true;
    }
    ReleaseSRWLockExclusive(&_srwLock);
    return completed;
}

// 0x115210
short __cdecl GuildCraft::TryAbandonGuildCraft(unsigned __int64, unsigned __int64, unsigned __int64)
{
    LIFT_STUB(0x115210);
}

// 0x115330
bool __cdecl GuildCraft::EnableDonationBrandMaterial(unsigned __int64, char, int)
{
    LIFT_STUB(0x115330);
}

// 0x115430
__cdecl GuildCraftManager::~GuildCraftManager(void)
{
    LIFT_STUB(0x115430);
}

// 0x115580
bool __cdecl GuildCraftManager::InitializeFromDBData(short, ::GuildCraftInfo const *const)
{
    LIFT_STUB(0x115580);
}

// 0x115720
::Pointer2< ::GuildCraft> __cdecl GuildCraftManager::AcquireGuildCraft(unsigned __int64)
{
    LIFT_STUB(0x115720);
}

// 0x1158d0
::Pointer2< ::GuildCraft> __cdecl GuildCraftManager::AcquireGuildCraft(int)
{
    LIFT_STUB(0x1158d0);
}

// 0x115a80
bool __cdecl GuildCraftManager::AddGuildCraft(::GuildCraft *)
{
    LIFT_STUB(0x115a80);
}

// 0x115b00
bool __cdecl GuildCraftManager::DelGuildCraft(unsigned __int64)
{
    LIFT_STUB(0x115b00);
}

// 0x115bf0
char __cdecl GuildCraftManager::GetGuildCraftCount(char, char)
{
    LIFT_STUB(0x115bf0);
}

// 0x115c70
bool __cdecl GuildCraftManager::FetchGuildCraftList(::FragmentPacket &)
{
    LIFT_STUB(0x115c70);
}
