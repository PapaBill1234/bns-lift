// guild_cpp_2.cpp: guild.cpp part 2 (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "guild.h"
#include "guildbank.h"
#include "guilduniform.h"
#include "pc.h"
#include "seasonscore.h"
#include <wchar.h>
#include "Memory.h"
#include "MemoryManager.h"
#include "LiftStub.h"

#define GUILD_CPP_FILE L"e:\\dailybuild02\\gamedaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\gamedaemon\\Guild.cpp"

#pragma comment(linker, "/INCLUDE:?findByPcDbId@Guild@@AEAAH_K@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?findByPcName@Guild@@AEAAHPEB_W@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?findByPcDbIdInWaiting@Guild@@AEAAH_K@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?checkPermissionGuild20@Guild@@AEAA_NHD@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?Initialize@GuildIdManager@@QEAAXXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?PushGuildId@GuildIdManager@@QEAA_NAEA_K@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?PopGuildId@GuildIdManager@@QEAA_KXZ")  // LIFT: dead-strip keep (no live caller yet)

// 0xf4c40
void __cdecl Guild::BroadcastRenameGuild(unsigned __int64, wchar_t const *, __int64)
{
    LIFT_STUB(0xf4c40);
}

// 0xf4e90
void __cdecl Guild::BroadcastDepositGuildBankByManager(unsigned int, short, __int64)
{
    LIFT_STUB(0xf4e90);
}

// 0xf4fe0
void __cdecl Guild::BroadcastSubtractGuildBankByManager(unsigned int, short, __int64)
{
    LIFT_STUB(0xf4fe0);
}

// 0xf5130
void __cdecl Guild::BroadcastRenameGuildByManager(wchar_t const *)
{
    LIFT_STUB(0xf5130);
}

// 0xf5270
void __cdecl Guild::BroadcastLogoutGuildmember(char, short, char, short)
{
    LIFT_STUB(0xf5270);
}

// 0xf5350
void __cdecl Guild::BroadcastLevelUpGuildMember(char, short, char, short)
{
    LIFT_STUB(0xf5350);
}

// 0xf5430
void __cdecl Guild::BroadcastTransitZoneGuildMember(char, int, short, short, short)
{
    LIFT_STUB(0xf5430);
}

// 0xf5520
void __cdecl Guild::BroadcastUpdateGuildMemberFaction2(char, char)
{
    LIFT_STUB(0xf5520);
}

// 0xf55e0
bool __cdecl Guild::FinishGuildCraftAssentForDebug(unsigned __int64, int)
{
    LIFT_STUB(0xf55e0);
}

// 0xf5810
short __cdecl Guild::EnableDepositGuildBank(unsigned __int64, int, short, __int64)
{
    LIFT_STUB(0xf5810);
}

// 0xf5910
bool __cdecl Guild::EnableContractGuildCraft(unsigned __int64, int, bool, wchar_t const *, bool, bool)
{
    LIFT_STUB(0xf5910);
}

// 0xf5e80
short __cdecl Guild::EnableAssentGuildCraft(unsigned __int64, unsigned __int64, char, short, char &)
{
    LIFT_STUB(0xf5e80);
}

// 0xf6100
short __cdecl Guild::EnableMakeGuildCraft(unsigned __int64, unsigned __int64)
{
    LIFT_STUB(0xf6100);
}

// 0xf65a0
short __cdecl Guild::EnableDonateGuildCraftNormalMaterial(unsigned __int64, unsigned __int64, int, short, int, short &)
{
    LIFT_STUB(0xf65a0);
}

// 0xf6960
short __cdecl Guild::EnableDonateGuildCraftBrandMaterial(unsigned __int64, unsigned __int64, int, char, int, short &)
{
    LIFT_STUB(0xf6960);
}

// 0xf6d30
short __cdecl Guild::EnableTakeGuildCraft(unsigned __int64, unsigned __int64, int, unsigned int &, short &)
{
    LIFT_STUB(0xf6d30);
}

// 0xf6fa0
void __cdecl Guild::EnableFinishGuildCraft(unsigned __int64)
{
    LIFT_STUB(0xf6fa0);
}

// 0xf70f0
short __cdecl Guild::AbandonGuildCraft(unsigned __int64, unsigned __int64, unsigned __int64)
{
    LIFT_STUB(0xf70f0);
}

// 0xf71f0
short __cdecl Guild::EnableContractGuildUniform(::Pc const *, unsigned __int64, char const *const, int const *const, char *const, int &, short &, ::GuildUniform::Material *const, short &, ::GuildBank::GuildBankItem *const)
{
    LIFT_STUB(0xf71f0);
}

// 0xf7650
short __cdecl Guild::EnableDonateGuildUniform(::Pc const *, unsigned __int64, unsigned int, short, short, short &)
{
    LIFT_STUB(0xf7650);
}

// 0xf7920
short __cdecl Guild::AbandonGuildUniform(unsigned __int64, unsigned __int64, unsigned __int64)
{
    LIFT_STUB(0xf7920);
}

// 0xf7a20
short __cdecl Guild::EnableMakeGuildUniform(::Pc *, unsigned __int64)
{
    LIFT_STUB(0xf7a20);
}

// 0xf8120
void __cdecl Guild::EnableFinishMakeGuildUniform(unsigned __int64)
{
    LIFT_STUB(0xf8120);
}

// 0xf8310
short __cdecl Guild::EnableRegisterGuildUniform(::Pc *, unsigned __int64)
{
    LIFT_STUB(0xf8310);
}

// 0xf8b40
short __cdecl Guild::EnableRegisterGuildUniformWithDeletion(::Pc *, unsigned __int64, unsigned __int64)
{
    LIFT_STUB(0xf8b40);
}

// 0xf9600
short __cdecl Guild::EnableIncreaseUniformRegistrationQuota(::Pc const *, char, unsigned int, short, short, short &)
{
    LIFT_STUB(0xf9600);
}

// 0xf99f0
short __cdecl Guild::EnablePutOnGuildUniform(::Pc *, unsigned __int64)
{
    LIFT_STUB(0xf99f0);
}

// 0xfa2d0
bool __cdecl Guild::isFullWaitingGuildMember(void) const
{
    LIFT_STUB(0xfa2d0);
}

// 0xfa350
void __cdecl Guild::clearWaitingList(void)
{
    LIFT_STUB(0xfa350);
}

// 0xfa4a0
bool __cdecl Guild::addWaitingGuildMember(unsigned __int64, unsigned __int64, short, wchar_t const *, short, char, short, short, short, wchar_t const *, __int64, bool)
{
    LIFT_STUB(0xfa4a0);
}

// 0xfa670
bool __cdecl Guild::delWaitingGuildMember(unsigned __int64)
{
    LIFT_STUB(0xfa670);
}

// 0xfa740
int __cdecl Guild::findByPcDbId(unsigned __int64 pcDbId)
{
    if (_guildMemberCount <= 0)
        return -1;
    for (int i = 0; i < 100; ++i)  // ❓ PDB constant name of the member array size not looked up
    {
        if (pcDbId == _guildMember[i].pcDbId)
            return i;
    }
    return -1;
}

// 0xfa770
int __cdecl Guild::findByPcName(wchar_t const *pcName)
{
    if (_guildMemberCount <= 0)
        return -1;
    for (int i = 0; i < 100; ++i)
    {
        if (_wcsicmp(_guildMember[i].name, pcName) == 0)
            return i;
    }
    return -1;
}

// 0xfa7f0
int __cdecl Guild::findByPcDbIdInWaiting(unsigned __int64 pcDbId)
{
    if (_waitingGuildMemberCount <= 0)
        return -1;
    for (int i = 0; i < 100; ++i)
    {
        if (pcDbId == _waitingGuildMember[i].pcDbId)
            return i;
    }
    return -1;
}

// 0xfa830
bool __cdecl Guild::checkPermissionGuild20(int grade, char permission)
{
    // ❓ PDB enumerator names of the grade (1 to 5) and the permission (1 to 17) are not looked up.
    if (grade < 1 || grade > 5)
        return false;
    if (permission < 1 || permission > 17)
        return false;
    return (reinterpret_cast< ::GuildView *>(this)->_permission[grade - 1] & (1 << (permission - 1))) != 0;
}

// 0xfa870
bool __cdecl Guild::isFull(void)
{
    LIFT_STUB(0xfa870);
}

// 0xfa920
bool __cdecl Guild::FetchGuildInfo(::FragmentPacket &)
{
    LIFT_STUB(0xfa920);
}

// 0xfaa60
bool __cdecl Guild::FetchGuildMembers(::FragmentPacket &)
{
    LIFT_STUB(0xfaa60);
}

// 0xfacc0
bool __cdecl Guild::ComposeGuildSeasonContentsInfo(char const *const, char, ::FragmentPacket &)
{
    LIFT_STUB(0xfacc0);
}

// 0xfaf40
int const __cdecl Guild::GetCombatRatingScore(char)
{
    LIFT_STUB(0xfaf40);
}

// 0xfb020
void __cdecl Guild::GetCombatInfo(char, int &, int &)
{
    LIFT_STUB(0xfb020);
}

// 0xfb120
bool __cdecl Guild::DepositInGuildBankOkFromCache(unsigned __int64, wchar_t const *, short, ::GuildBank::GuildBankItem const *const, __int64 *const)
{
    LIFT_STUB(0xfb120);
}

// 0xfb250
bool __cdecl Guild::AbandonGuildCraftOkFromCache(unsigned __int64, unsigned __int64)
{
    LIFT_STUB(0xfb250);
}

// 0xfb8a0
__int64 __cdecl Guild::EnableDepositCount(int, short)
{
    LIFT_STUB(0xfb8a0);
}

// 0xfb9b0
bool __cdecl Guild::isFullNormalGuildCraft(char)
{
    LIFT_STUB(0xfb9b0);
}

// 0xfba50
bool __cdecl Guild::contractableGuildUniform(int &)
{
    LIFT_STUB(0xfba50);
}

// 0xfbaf0
bool __cdecl Guild::registrableGuildUniform(void)
{
    LIFT_STUB(0xfbaf0);
}

// 0xfbb80
bool __cdecl Guild::addGuildUniformCost(unsigned int, short, int, short &, ::GuildBank::GuildBankItem *const)
{
    LIFT_STUB(0xfbb80);
}

// 0xfbcc0
bool __cdecl Guild::addGuildUniformMaterial(unsigned int, short, unsigned int, short &, ::GuildUniform::Material *const)
{
    LIFT_STUB(0xfbcc0);
}

// 0xfbdd0
bool __cdecl Guild::calculateGuildUniformParam(bool, int, int, int, short &, ::GuildUniform::Material *const, short &, ::GuildBank::GuildBankItem *const)
{
    LIFT_STUB(0xfbdd0);
}

// 0xfc010
bool __cdecl Guild::getCurrentGuildUniform(char *const)
{
    LIFT_STUB(0xfc010);
}

// 0xfc100
bool __cdecl Guild::analyzeGuildUniformParamTypes(bool, unsigned __int64, char const *const, int const *const, char *const, short &, ::GuildUniform::Material *const, short &, ::GuildBank::GuildBankItem *const)
{
    LIFT_STUB(0xfc100);
}

// 0xfc5a0
bool __cdecl Guild::checkGuildUniformParamTypes(char const *const, int const *const, char const *const)
{
    LIFT_STUB(0xfc5a0);
}

// 0xfc980
bool __cdecl Guild::IsGuildBankItem(unsigned int, short)
{
    LIFT_STUB(0xfc980);
}

// 0xfca70
bool __cdecl Guild::EnableDepositGuildBankByManager(unsigned int, short, __int64, __int64 &)
{
    LIFT_STUB(0xfca70);
}

// 0xfcca0
bool __cdecl Guild::EnableWithdrawGuildBankByManager(unsigned int, short, __int64)
{
    LIFT_STUB(0xfcca0);
}

// 0xfce60
bool __cdecl Guild::RenameGuildByManagement(wchar_t const *)
{
    LIFT_STUB(0xfce60);
}

// 0xfcfb0
bool __cdecl Guild::BanishGuildMemberByManager(unsigned __int64, short &)
{
    LIFT_STUB(0xfcfb0);
}

// 0xfd180
bool __cdecl Guild::DelegateGuildLeaderByManager(unsigned __int64, short &)
{
    LIFT_STUB(0xfd180);
}

// 0xfd340
bool __cdecl Guild::JoinGuildByManager(unsigned __int64, wchar_t *, unsigned __int64, short, short, char, char, short, short, short, short &)
{
    LIFT_STUB(0xfd340);
}

// 0xfd760
char __cdecl Guild::getGuildCraftRecipeUsableCount(char, char)
{
    LIFT_STUB(0xfd760);
}

// 0xfd850
bool __cdecl Guild::CheckPermissionGuild20(unsigned __int64, char)
{
    LIFT_STUB(0xfd850);
}

// 0xfda30
bool __cdecl Guild::ContractGuildCraftOkFromCache(unsigned __int64, ::ContractOkParam *, __int64 *const)
{
    LIFT_STUB(0xfda30);
}

// 0xfdc20
bool __cdecl Guild::AssentGuildCraftOkFromCache(unsigned __int64, ::AssentOkParam *)
{
    LIFT_STUB(0xfdc20);
}

// 0xfe0d0
bool __cdecl Guild::DonateGuildCraftNormalMaterialOkFromCache(unsigned __int64, ::DonateNormalMaterialOkParam *)
{
    LIFT_STUB(0xfe0d0);
}

// 0xfe300
bool __cdecl Guild::DonateGuildCraftBrandMaterialOkFromCache(unsigned __int64, ::DonateBrandMaterialOkParam *)
{
    LIFT_STUB(0xfe300);
}

// 0xfe540
bool __cdecl Guild::MakeGuildCraftOkFromCache(unsigned __int64, ::MakeGuildCraftOkParam *)
{
    LIFT_STUB(0xfe540);
}

// 0xfea20
bool __cdecl Guild::FinishGuildCraftFromSystem(unsigned __int64)
{
    LIFT_STUB(0xfea20);
}

// 0xfece0
bool __cdecl Guild::TakeGuildCraftOkFromCache(unsigned __int64, ::TakeGuildCraftOkParam *)
{
    LIFT_STUB(0xfece0);
}

// 0xff250
bool __cdecl Guild::ContractGuildUniformOkFromCache(::ContractGuildUniformOkParam const *, __int64 *const)
{
    LIFT_STUB(0xff250);
}

// 0xff440
bool __cdecl Guild::DonateGuildUniformOkFromCache(::DonateGuildUniformMaterialOkParam const *)
{
    LIFT_STUB(0xff440);
}

// 0xff690
bool __cdecl Guild::AbandonGuildUniformOkFromCache(unsigned __int64, unsigned __int64)
{
    LIFT_STUB(0xff690);
}

// 0xffac0
bool __cdecl Guild::MakeGuildUniformOkFromCache(::MakeGuildUniformOkParam const *)
{
    LIFT_STUB(0xffac0);
}

// 0xfff50
bool __cdecl Guild::FinishGuildUniformFromSystem(unsigned __int64)
{
    LIFT_STUB(0xfff50);
}

// 0x100150
bool __cdecl Guild::RegisterGuildUniformOkFromCache(::RegisterGuildUniformOkParam const *)
{
    LIFT_STUB(0x100150);
}

// 0x1004c0
bool __cdecl Guild::PutOnGuildUniformOkFromCache(::PutOnGuildUniformOkParam const *)
{
    LIFT_STUB(0x1004c0);
}

// 0x1007f0
bool __cdecl Guild::RegisterGuildUniformWithDeletionOkFromCache(::RegisterGuildUniformWithDeletionOkParam const *)
{
    LIFT_STUB(0x1007f0);
}

// 0x100c40
short __cdecl Guild::EnableChangeGuildFlagBearer(::Pc *, char, wchar_t const *)
{
    LIFT_STUB(0x100c40);
}

// 0x101120
bool __cdecl Guild::TakeRankingRewardOkFromCache(::TakeRankingRewardOkParam const *)
{
    LIFT_STUB(0x101120);
}

// 0x101560
bool __cdecl Guild::TakeRankingBuffReward(::RankingResultInfo const *)
{
    LIFT_STUB(0x101560);
}

// 0x1018d0
bool __cdecl Guild::EnableRetrieveRankingInfo(char, ::LatestRankingInfo &)
{
    LIFT_STUB(0x1018d0);
}

// 0x101990
void __cdecl Guild::TryUpdateCombatRecord(::TryUpdateCombatRecordParam &)
{
    LIFT_STUB(0x101990);
}

// 0x101f00
void __cdecl Guild::UpdateCombatRecord(char, unsigned __int64, __int64)
{
    LIFT_STUB(0x101f00);
}

// 0x1022a0
void __cdecl Guild::ResetCombatRecord(char)
{
    LIFT_STUB(0x1022a0);
}

// 0x1023b0
void __cdecl Guild::InitializeCombatRecord(::SeasonContentsGuildCombatRecord const &)
{
    LIFT_STUB(0x1023b0);
}

// 0x102590
void __cdecl Guild::FetchRankingRewardList(::FragmentPacket &)
{
    LIFT_STUB(0x102590);
}

// 0x102720
bool __cdecl Guild::UpdateFlagBearerOkFromCache(::UpdateGuildFlagBearerParam const *)
{
    LIFT_STUB(0x102720);
}

// 0x103040
void __cdecl Guild::BroadcastContractGuildCraft(unsigned __int64, ::ContractOkParam *)
{
    LIFT_STUB(0x103040);
}

// 0x1032e0
void __cdecl Guild::BroadcastAssentGuildCraft(unsigned __int64, char, wchar_t *)
{
    LIFT_STUB(0x1032e0);
}

// 0x103460
void __cdecl Guild::BroadcastDonationGuildCraftNormalMaterial(unsigned __int64, wchar_t const *, unsigned int, short, __int64)
{
    LIFT_STUB(0x103460);
}

// 0x103620
void __cdecl Guild::BroadcastDonationGuildCraftBrandMaterial(unsigned __int64, wchar_t const *, unsigned int, short, unsigned __int64, char, __int64)
{
    LIFT_STUB(0x103620);
}

// 0x103810
void __cdecl Guild::BroadcastFinishDonationGuildCraft(unsigned __int64)
{
    LIFT_STUB(0x103810);
}

// 0x103960
void __cdecl Guild::BroadcastMakeGuildCraft(unsigned __int64, __int64, __int64, int, char, __int64)
{
    LIFT_STUB(0x103960);
}

// 0x103b80
void __cdecl Guild::BroadcastFinishGuildCraft(unsigned __int64)
{
    LIFT_STUB(0x103b80);
}

// 0x103cd0
void __cdecl Guild::BroadcastTakeGuildCraft(unsigned __int64, wchar_t *, short)
{
    LIFT_STUB(0x103cd0);
}

// 0x103e50
void __cdecl Guild::BroadcastRegisterGuildUniformWithDeletion(unsigned __int64, unsigned __int64, bool, __int64)
{
    LIFT_STUB(0x103e50);
}

// 0x103fe0
void __cdecl Guild::BroadcastIncreaseGuildUniformRegistrationQuota(unsigned __int64, wchar_t const *, short)
{
    LIFT_STUB(0x103fe0);
}

// 0x104160
void __cdecl Guild::BroadcastTakeRankingRewardForGuildBuff(::Guild::RankingRewardInfo const *)
{
    LIFT_STUB(0x104160);
}

// 0x104700
void __cdecl Guild::BroadcastTakeRankingRewardForGuildBank(char, int, char, int, char, ::GuildBank::GuildBankItem const *const)
{
    LIFT_STUB(0x104700);
}

// 0x104ba0
void __cdecl Guild::BroadcastChangedGuildRankingInfo(char, int)
{
    LIFT_STUB(0x104ba0);
}

// 0x104cb0
void __cdecl Guild::BroadcastChangedGuildCombatRecord(::SeasonContentsGuildCombatRecordEntry *, ::Packet *)
{
    LIFT_STUB(0x104cb0);
}

// 0x104e60
__cdecl GuildIdManager::~GuildIdManager(void)
{
    LIFT_STUB(0x104e60);
}

// 0x104f10
void __cdecl GuildIdManager::Initialize(void)
{
    head = static_cast<GuildIdNode *>(Memory::_Manager[2]->Alloc(sizeof(GuildIdNode), GUILD_CPP_FILE, 10385));
    tail = static_cast<GuildIdNode *>(Memory::_Manager[2]->Alloc(sizeof(GuildIdNode), GUILD_CPP_FILE, 10386));
    head->prev = head;
    head->next = tail;
    tail->prev = head;
    tail->next = tail;
}

// 0x104f90
bool __cdecl GuildIdManager::PushGuildId(unsigned __int64 &guildId)
{
    bool result = false;
    GuildIdMgrCS.Enter();
    GuildIdNode *node = static_cast<GuildIdNode *>(Memory::_Manager[2]->Alloc(sizeof(GuildIdNode), GUILD_CPP_FILE, 10398));
    if (node != nullptr)
    {
        result = true;
        node->guildId = guildId;
        tail->prev->next = node;
        node->prev = tail->prev;
        tail->prev = node;
        node->next = tail;
    }
    GuildIdMgrCS.Leave();
    return result;
}

// 0x105030
unsigned __int64 __cdecl GuildIdManager::PopGuildId(void)
{
    unsigned __int64 guildId = 0;
    GuildIdMgrCS.Enter();
    GuildIdNode *node = head->next;
    if (node != tail)
    {
        guildId = node->guildId;
        head->next = node->next;
        node->next->prev = head;
        Memory::_Manager[2]->Free(node, GUILD_CPP_FILE, 10436);
    }
    GuildIdMgrCS.Leave();
    return guildId;
}
