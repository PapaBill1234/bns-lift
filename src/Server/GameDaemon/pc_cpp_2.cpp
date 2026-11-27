// pc_cpp_2.cpp: pc.cpp part 2 (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "pc.h"
#include "arenaroommanager.h"
#include "convoy.h"
#include "creature.h"
#include "fielditem.h"
#include "gameobject.h"
#include "geoworld.h"
#include "npc.h"
#include "summoned.h"
#include "team.h"
#include "user.h"
#include "zone.h"
#include "Log.h"
#include "../BloodLib/include/Network.h"
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:?IsSharableCombatModeZone@Pc@@QEBA_NXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetActiveSummoned@Pc@@QEAAPEAVSummoned@@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?Send@Pc@@QEAAXPEBDPEAD@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?Send@Pc@@UEAAXPEBDZZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?Send@Pc@@UEAAXPEBVPacket@@@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?Send@Pc@@UEAAXPEBVPacketList@@@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?ReturningToArenaLobby@Pc@@QEAA_NXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?RollbackReturnToArenaLobby@Pc@@QEAAXXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?SetGameGameMode@Pc@@QEAAXD@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetGameGameMode@Pc@@QEBA?BDXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetArenaAttraction@Pc@@QEBADXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?SetIpAddress@Pc@@QEAAXK@Z")  // LIFT: dead-strip keep (no live caller yet)

namespace
{
// LIFT: view of PacketList. The skeleton class is empty. Offsets are from the PDB.
struct PacketListView
{
    char lift_pad_0[0x4];
    int Count;                       // +4 (0x4)
    PacketBuffer const **Buffers;    // +8 (0x8). ❓ PDB element type not checked; the original passes it as PacketBuffer const **
};

// LIFT: views of PDB classes that have no layout in the skeleton yet. Offsets are from the PDB.

// LIFT: view of Data::ZoneRecord (sharable_combatmode at +0xB9).
struct ZoneRecordView
{
    char lift_pad_0[0xB9];
    bool sharable_combatmode;  // +185 (0xB9)
};

// LIFT: view of GeoZone (zoneData at +0, a Data::ZoneRecordPtr with _record at +0).
struct GeoZoneView
{
    ZoneRecordView const *zoneData_record;  // +0 (0x0). LIFT: GeoZone::zoneData._record
};

// LIFT: view of Zone (GeoZoneData at +0x3F60).
struct ZoneGeoView
{
    char lift_pad_0[0x3F60];
    GeoZoneView const *GeoZoneData;  // +16224 (0x3F60)
};

// LIFT: view of Summoned (_summonedState at +0x1A10).
struct SummonedView
{
    char lift_pad_0[0x1A10];
    int _summonedState;  // +6672 (0x1A10). LIFT: PDB type Summoned::SummonedState
};
enum
{
    LIFT_SUMMONED_STATE_SPAWNING = 1,  // LIFT: Summoned::SUMMONED_STATE_SPAWNING
    LIFT_SUMMONED_STATE_SPAWNED = 2,   // LIFT: Summoned::SUMMONED_STATE_SPAWNED
};

// LIFT: view of Pc. The skeleton class declares only part of its PDB members.
struct PcView
{
    char lift_pad_0[0x28];
    unsigned __int64 Id;                 // +40 (0x28). GameObject::Id
    char lift_pad_1[0x8B8 - 0x30];
    ZoneGeoView *zone;                   // +2232 (0x8B8). Creature::zone
    char lift_pad_2[0x4DE0 - 0x8C0];
    ::Channel const *_user;              // +19936 (0x4DE0). LIFT: PDB type User const *, base Channel at +0
    char lift_pad_3[0x4DEC - 0x4DE8];
    unsigned long _ipAddress;            // +19948 (0x4DEC)
    char lift_pad_4[0x8C80 - 0x4DF0];
    SummonedView *_summoned;             // +35968 (0x8C80)
    char lift_pad_5[0x8EC0 - 0x8C88];
    CRITICAL_SECTION _arenaLock;         // +36544 (0x8EC0). LIFT: PDB type CriticalSection (CS at +0, size 0x28)
    char lift_pad_6[0x8F08 - 0x8EE8];
    char _arenaLobbyEnterParam_attraction;  // +36616 (0x8F08). _arenaLobbyEnterParam (+0x8EF0) ._attraction (+0x18)
    char lift_pad_7[0x9054 - 0x8F09];
    bool _isReturningToArenaLobby;       // +36948 (0x9054)
    char _arenaGameGameMode;             // +36949 (0x9055)
};

wchar_t const *const PC_CHANNEL_HEADER_FILE =
    L"E:\\DailyBuild02\\GameDaemon-Common-0.0.348\\depot\\Branch\\348NC\\Program\\Server\\BloodLib\\include\\Channel.h";
}  // namespace

// 0x5e5ad0
void __cdecl Pc::CalculateSkillScore(void)
{
    LIFT_STUB(0x5e5ad0);
}

// 0x5e6360
void __cdecl Pc::ModifyEquipBadgeGearScore(int)
{
    LIFT_STUB(0x5e6360);
}

// 0x5e63d0
__int64 __cdecl Pc::CalculateGuildRankingRewardCombatExp(char, __int64)
{
    LIFT_STUB(0x5e63d0);
}

// 0x5e6540
bool __cdecl Pc::GetNearRespawnArea(::vector16, unsigned int &, unsigned __int64 &)
{
    LIFT_STUB(0x5e6540);
}

// 0x5e6a90
bool __cdecl Pc::IsSharableCombatModeZone(void) const
{
    ZoneGeoView const *zone = reinterpret_cast<PcView const *>(this)->zone;
    if (zone != nullptr)
    {
        GeoZoneView const *geoZone = zone->GeoZoneData;
        if (geoZone != nullptr && geoZone->zoneData_record != nullptr)
            return geoZone->zoneData_record->sharable_combatmode;
    }
    return false;
}

// 0x5e6ac0
bool __cdecl Pc::findZoneTeamMemberRemain(unsigned int, int &)
{
    LIFT_STUB(0x5e6ac0);
}

// 0x5e6c20
bool __cdecl Pc::findZonePartyMemberRemain(unsigned int, int &)
{
    LIFT_STUB(0x5e6c20);
}

// 0x5e6cf0
short __cdecl Pc::SelectTransitZone(short, ::LeaveReason, unsigned __int64, unsigned __int64 *, unsigned __int64 *, unsigned __int64 *, unsigned __int64 *, short *, unsigned __int64 *, unsigned int *, unsigned __int64 *, unsigned __int64 *, unsigned __int64 *, unsigned __int64 *, short *, bool, bool, char)
{
    LIFT_STUB(0x5e6cf0);
}

// 0x5e7e50
bool __cdecl Pc::TranslateZoneOnEnterWorld(unsigned __int64 *, unsigned int *, ::vector16 *, short *)
{
    LIFT_STUB(0x5e7e50);
}

// 0x5e81b0
::GameFailReason __cdecl Pc::selectTransitZoneForDungeon(::GeoZone const *, int, bool &, int &)
{
    LIFT_STUB(0x5e81b0);
}

// 0x5e88f0
void __cdecl Pc::CheckConditionAfterSpawn(void)
{
    LIFT_STUB(0x5e88f0);
}

// 0x5e8ef0
void __cdecl Pc::OnTimer(::Zone *, unsigned short)
{
    LIFT_STUB(0x5e8ef0);
}

// 0x5e9190
void __cdecl Pc::OnAttacked(::Zone *, ::GameObject *, unsigned __int64, short)
{
    LIFT_STUB(0x5e9190);
}

// 0x5e91e0
void __cdecl Pc::OnKilled(::Zone *, ::GameObject *, unsigned __int64)
{
    LIFT_STUB(0x5e91e0);
}

// 0x5e93e0
void __cdecl Pc::OnKill(::Zone *, ::Pc *, unsigned __int64, char, char)
{
    LIFT_STUB(0x5e93e0);
}

// 0x5e95c0
void __cdecl Pc::ProcessFactionByKill(::Pc *, unsigned __int64, char, char)
{
    LIFT_STUB(0x5e95c0);
}

// 0x5e9800
void __cdecl Pc::cancelTrade(char, wchar_t const *)
{
    LIFT_STUB(0x5e9800);
}

// 0x5e98b0
void __cdecl Pc::ClearStateOnDead(void)
{
    LIFT_STUB(0x5e98b0);
}

// 0x5e9a70
void __cdecl Pc::SetFieldItem(::FieldItem *)
{
    LIFT_STUB(0x5e9a70);
}

// 0x5e9bf0
void __cdecl Pc::ClearFieldItem(void)
{
    LIFT_STUB(0x5e9bf0);
}

// 0x5e9c50
void __cdecl Pc::ClearFieldItemProperty(void)
{
    LIFT_STUB(0x5e9c50);
}

// 0x5e9cc0
::GameFailReason const __cdecl Pc::CheckMakeSummoned(__int64)
{
    LIFT_STUB(0x5e9cc0);
}

// 0x5e9e00
void __cdecl Pc::MakeSummoned(__int64, wchar_t const *const)
{
    LIFT_STUB(0x5e9e00);
}

// 0x5ea0d0
::Summoned * __cdecl Pc::GetActiveSummoned(void)
{
    SummonedView *summoned = reinterpret_cast<PcView *>(this)->_summoned;
    if (summoned == nullptr)
        return nullptr;
    int summonedState = summoned->_summonedState;
    if (summonedState != LIFT_SUMMONED_STATE_SPAWNING && summonedState != LIFT_SUMMONED_STATE_SPAWNED)
        return nullptr;
    return reinterpret_cast< ::Summoned *>(summoned);
}

// 0x5ea0f0
void __cdecl Pc::SetActiveSummoned(::Summoned *)
{
    LIFT_STUB(0x5ea0f0);
}

// 0x5ea2d0
::Data::MasteryAbilityRecordPtr const __cdecl Pc::GetMasteryAbilityData(char) const
{
    LIFT_STUB(0x5ea2d0);
}

// 0x5ea390
void __cdecl Pc::LeaveWorld(void)
{
    LIFT_STUB(0x5ea390);
}

// 0x5ea760
void __cdecl Pc::WriteGameLogLeaveWorld(char, char)
{
    LIFT_STUB(0x5ea760);
}

// 0x5eace0
void __cdecl Pc::enterArenaLobby(void)
{
    LIFT_STUB(0x5eace0);
}

// 0x5ead90
void __cdecl Pc::ResetSpecialSkillGauge(void)
{
    LIFT_STUB(0x5ead90);
}

// 0x5eaf10
int __cdecl Pc::GetCurrentSpecialSkillGauge(void)
{
    LIFT_STUB(0x5eaf10);
}

// 0x5eaff0
bool __cdecl Pc::IsSpecialSkillGaugeFull(void)
{
    LIFT_STUB(0x5eaff0);
}

// 0x5eb050
void __cdecl Pc::SetUser(::User const *)
{
    LIFT_STUB(0x5eb050);
}

// 0x5eb130
void __cdecl Pc::SendGameBuilderAuth(void)
{
    LIFT_STUB(0x5eb130);
}

// 0x5eb2e0
void __cdecl Pc::Send(char const *format, char *args)
{
    ::Channel const *user = reinterpret_cast<PcView *>(this)->_user;
    if (user != nullptr)
    {
        Session *session = const_cast<Session *>(user->GetSession());
        if (session != nullptr)
        {
            session->SendV(format, args);
            session->removeReferenceCount(PC_CHANNEL_HEADER_FILE, 52);
        }
    }
}

// 0x5eb350
void __cdecl Pc::Send(char const *format, ...)
{
    va_list args;
    va_start(args, format);
    ::Channel const *user = reinterpret_cast<PcView *>(this)->_user;
    if (user != nullptr)
    {
        Session *session = const_cast<Session *>(user->GetSession());
        if (session != nullptr)
        {
            session->SendV(format, args);
            session->removeReferenceCount(PC_CHANNEL_HEADER_FILE, 52);
        }
    }
    va_end(args);
}

// 0x5eb3c0
void __cdecl Pc::Send(::Packet const *packet)
{
    ::Channel const *user = reinterpret_cast<PcView *>(this)->_user;
    if (user != nullptr)
    {
        Session *session = const_cast<Session *>(user->GetSession());
        if (session != nullptr)
        {
            session->Send(packet);
            session->removeReferenceCount(PC_CHANNEL_HEADER_FILE, 52);
        }
    }
}

// 0x5eb420
void __cdecl Pc::Send(::PacketList const *packetList)
{
    ::Channel const *user = reinterpret_cast<PcView *>(this)->_user;
    if (user != nullptr)
    {
        Session *session = const_cast<Session *>(user->GetSession());
        if (session != nullptr)
        {
            // LIFT: inline Session::Send(PacketList const *)
            session->_lock.Enter();
            PacketListView const *list = reinterpret_cast<PacketListView const *>(packetList);
            session->send(list->Buffers, list->Count);
            session->_lock.Leave();
            session->removeReferenceCount(PC_CHANNEL_HEADER_FILE, 52);
        }
    }
}

// 0x5eb4a0
void __cdecl Pc::SendChangedPrivateProperty(void)
{
    LIFT_STUB(0x5eb4a0);
}

// 0x5eb4f0
void __cdecl Pc::SendActionPrivatePacket(void)
{
    LIFT_STUB(0x5eb4f0);
}

// 0x5eb540
void __cdecl Pc::SendEnterWorldOk(void)
{
    LIFT_STUB(0x5eb540);
}

// 0x5ec3e0
void __cdecl Pc::writeGameLogEnterWorld(char, char)
{
    LIFT_STUB(0x5ec3e0);
}

// 0x5ec8a0
void __cdecl Pc::SendSummonedEnterWorldOk(void)
{
    LIFT_STUB(0x5ec8a0);
}

// 0x5ecb90
void __cdecl Pc::ChangeEnterArenaParam(unsigned __int64, __int64, unsigned __int64, __int64)
{
    LIFT_STUB(0x5ecb90);
}

// 0x5ecce0
void __cdecl Pc::SendEnterArenaOk(void)
{
    LIFT_STUB(0x5ecce0);
}

// 0x5ed820
bool __cdecl Pc::ReturningToArenaLobby(void)
{
    PcView *self = reinterpret_cast<PcView *>(this);
    bool result = false;
    EnterCriticalSection(&self->_arenaLock);
    if (!self->_isReturningToArenaLobby)
    {
        self->_isReturningToArenaLobby = true;
        result = true;
    }
    LeaveCriticalSection(&self->_arenaLock);
    return result;
}

// 0x5ed880
void __cdecl Pc::RollbackReturnToArenaLobby(void)
{
    PcView *self = reinterpret_cast<PcView *>(this);
    EnterCriticalSection(&self->_arenaLock);
    self->_isReturningToArenaLobby = false;
    LeaveCriticalSection(&self->_arenaLock);
}

// 0x5ed8c0
void __cdecl Pc::SendUpdateDodgeInfo(void)
{
    LIFT_STUB(0x5ed8c0);
}

// 0x5ed9c0
void __cdecl Pc::SetArenaRoom(::ArenaRoom *, __int64)
{
    LIFT_STUB(0x5ed9c0);
}

// 0x5edae0
void __cdecl Pc::SetGameGameMode(char gameGameMode)
{
    PcView *self = reinterpret_cast<PcView *>(this);
    EnterCriticalSection(&self->_arenaLock);
    self->_arenaGameGameMode = gameGameMode;
    LeaveCriticalSection(&self->_arenaLock);
}

// 0x5edb30
char const __cdecl Pc::GetGameGameMode(void) const
{
    PcView *self = const_cast<PcView *>(reinterpret_cast<PcView const *>(this));
    EnterCriticalSection(&self->_arenaLock);
    char gameGameMode = self->_arenaGameGameMode;
    LeaveCriticalSection(&self->_arenaLock);
    return gameGameMode;
}

// 0x5edb70
bool __cdecl Pc::SendReturnToGameOk(char)
{
    LIFT_STUB(0x5edb70);
}

// 0x5ee6b0
char __cdecl Pc::GetArenaAttraction(void) const
{
    PcView *self = const_cast<PcView *>(reinterpret_cast<PcView const *>(this));
    EnterCriticalSection(&self->_arenaLock);
    char attraction = self->_arenaLobbyEnterParam_attraction;
    LeaveCriticalSection(&self->_arenaLock);
    return attraction;
}

// 0x5ee6f0
void __cdecl Pc::SendCurrentUTCTimeOk(void)
{
    LIFT_STUB(0x5ee6f0);
}

// 0x5ee830
void __cdecl Pc::SendChatMessage(char, wchar_t const *, int, wchar_t const *, wchar_t const *)
{
    LIFT_STUB(0x5ee830);
}

// 0x5ef4b0
void __cdecl Pc::SendChatMessageByItem(wchar_t const *, char, short)
{
    LIFT_STUB(0x5ef4b0);
}

// 0x5ef760
void __cdecl Pc::SendChatMessageByDice(short, short)
{
    LIFT_STUB(0x5ef760);
}

// 0x5ef9a0
void __cdecl Pc::SendPcDbIdOk(void)
{
    LIFT_STUB(0x5ef9a0);
}

// 0x5efb50
void __cdecl Pc::SendQuestCompleteListOk(void)
{
    LIFT_STUB(0x5efb50);
}

// 0x5efd00
void __cdecl Pc::SendMentoringPropertySync(void)
{
    LIFT_STUB(0x5efd00);
}

// 0x5efec0
void __cdecl Pc::SendActivatedTeleportListOk(void)
{
    LIFT_STUB(0x5efec0);
}

// 0x5f0070
void __cdecl Pc::ChangeTeamPartyProperty(unsigned short)
{
    LIFT_STUB(0x5f0070);
}

// 0x5f00d0
bool __cdecl Pc::FetchTeamPartyProperty(::Packet *, ::Packet *, ::Packet *, ::Packet *)
{
    LIFT_STUB(0x5f00d0);
}

// 0x5f04e0
void __cdecl Pc::BroadcastTeamPartyProperty(void)
{
    LIFT_STUB(0x5f04e0);
}

// 0x5f0970
int __cdecl Pc::GetTeamMembers(unsigned __int64 *const)
{
    LIFT_STUB(0x5f0970);
}

// 0x5f0a90
unsigned short __cdecl Pc::FetchPartyProperty(char *, unsigned short)
{
    LIFT_STUB(0x5f0a90);
}

// 0x5f0bd0
unsigned short __cdecl Pc::FetchTeamProperty(char *, unsigned short)
{
    LIFT_STUB(0x5f0bd0);
}

// 0x5f0d10
::Pointer2< ::User> __cdecl Pc::GetUserPtr(void)
{
    LIFT_STUB(0x5f0d10);
}

// 0x5f0d70
__int64 __cdecl Pc::GetSessionId(void)
{
    LIFT_STUB(0x5f0d70);
}

// 0x5f0df0
void __cdecl Pc::GetGameAccountId(int, wchar_t *const)
{
    LIFT_STUB(0x5f0df0);
}

// 0x5f0f00
void __cdecl Pc::SetIpAddress(unsigned long ip)
{
    PcView *self = reinterpret_cast<PcView *>(this);
    if (self->_ipAddress != 0)
    {
        Log::Write(Log::LT_ERROR,
                   L"e:\\dailybuild02\\gamedaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\gamedaemon\\Pc.cpp",
                   10589, L"[pc], %s; ip address already set. pc:%I64x, ip:%s, new ip:%s", L"Pc::SetIpAddress", self->Id,
                   Network::GetAddressStringW(self->_ipAddress), Network::GetAddressStringW(ip));
        return;
    }
    self->_ipAddress = ip;
}

// 0x5f0f90
wchar_t const * __cdecl Pc::GetUserExternalAccountKeyString(void)
{
    LIFT_STUB(0x5f0f90);
}

// 0x5f0fe0
unsigned int __cdecl Pc::GetUserGamePlayRestrictLevel(void)
{
    LIFT_STUB(0x5f0fe0);
}

// 0x5f1030
int __cdecl Pc::GetUserGamePlayRestrictLevelRatio(void)
{
    LIFT_STUB(0x5f1030);
}

// 0x5f1080
void __cdecl Pc::UpdatePartyDifficultyType(bool, unsigned __int64, unsigned __int64, char)
{
    LIFT_STUB(0x5f1080);
}

// 0x5f1110
int __cdecl Pc::GetPartyMembers(unsigned __int64 *const)
{
    LIFT_STUB(0x5f1110);
}

// 0x5f1250
void __cdecl Pc::SetTeamInfo(unsigned __int64, unsigned __int64, char, ::Team *)
{
    LIFT_STUB(0x5f1250);
}

// 0x5f12d0
void __cdecl Pc::ClearTeamInfo(::LeavePartyReason, bool, ::TeamPartyProxy *)
{
    LIFT_STUB(0x5f12d0);
}

// 0x5f1460
bool __cdecl Pc::AssignChasePosition(::vector16 const &, int, int *)
{
    LIFT_STUB(0x5f1460);
}

// 0x5f1610
bool __cdecl Pc::ChaseTicketToPos(int, int, ::vector16 *)
{
    LIFT_STUB(0x5f1610);
}

// 0x5f17f0
void __cdecl Pc::ClearChasePosition(int)
{
    LIFT_STUB(0x5f17f0);
}

// 0x5f18b0
bool __cdecl Pc::takeFactionScore(::Pc *)
{
    LIFT_STUB(0x5f18b0);
}

// 0x5f1a20
int __cdecl Pc::DistributeFactionScoreToPc(int, unsigned __int64, char)
{
    LIFT_STUB(0x5f1a20);
}

// 0x5f2680
void __cdecl Pc::DistributeFactionScore(int, ::Creature *)
{
    LIFT_STUB(0x5f2680);
}

// 0x5f4160
::GameFailReason __cdecl Pc::TalkStart(::Npc *)
{
    LIFT_STUB(0x5f4160);
}

// 0x5f42a0
bool __cdecl Pc::TalkStop(::Npc *)
{
    LIFT_STUB(0x5f42a0);
}

// 0x5f4320
bool __cdecl Pc::TalkInterrupted(::Npc *, bool, wchar_t const *)
{
    LIFT_STUB(0x5f4320);
}

// 0x5f43d0
bool __cdecl Pc::AddConvoy(::Convoy *)
{
    LIFT_STUB(0x5f43d0);
}

// 0x5f44a0
void __cdecl Pc::RemoveConvoy(void)
{
    LIFT_STUB(0x5f44a0);
}

// 0x5f4530
int __cdecl Pc::SetDbClientOptionData(short, char const *, int)
{
    LIFT_STUB(0x5f4530);
}

// 0x5f46a0
short __cdecl Pc::FetchDiscoveryArea(char *, short)
{
    LIFT_STUB(0x5f46a0);
}

// 0x5f4730
short __cdecl Pc::FetchActivatedTeleport(char *, short)
{
    LIFT_STUB(0x5f4730);
}

// 0x5f47c0
short __cdecl Pc::FetchSkillSkinAcquired(char *, short)
{
    LIFT_STUB(0x5f47c0);
}

// 0x5f4850
short __cdecl Pc::FetchMentoringProperty(char *, short)
{
    LIFT_STUB(0x5f4850);
}

// 0x5f48e0
bool __cdecl Pc::CheckActivatedTeleport(short)
{
    LIFT_STUB(0x5f48e0);
}

// 0x5f49f0
bool __cdecl Pc::CheckSkillSkinProperty(short)
{
    LIFT_STUB(0x5f49f0);
}

// 0x5f4b30
bool __cdecl Pc::SetDiscoveryAreaBit(short)
{
    LIFT_STUB(0x5f4b30);
}

// 0x5f4cd0
bool __cdecl Pc::SetActivatedTeleportBit(short, unsigned char, bool)
{
    LIFT_STUB(0x5f4cd0);
}

// 0x5f4ec0
void __cdecl Pc::SetActivatedTeleport(unsigned char)
{
    LIFT_STUB(0x5f4ec0);
}

// 0x5f5250
bool __cdecl Pc::SetSkillSkinAcquiredBit(short, bool)
{
    LIFT_STUB(0x5f5250);
}

// 0x5f5440
bool __cdecl Pc::SetMentoringType(char, short)
{
    LIFT_STUB(0x5f5440);
}

// 0x5f56e0
bool __cdecl Pc::IncreaseMentoringFinishCount(::Pc *)
{
    LIFT_STUB(0x5f56e0);
}

// 0x5f5ac0
bool __cdecl Pc::SetMentoringFinishCount(char)
{
    LIFT_STUB(0x5f5ac0);
}

// 0x5f5b90
int __cdecl Pc::GetPartyMembersForDistribute(::Pc **, ::vector16 const &, int, bool, bool)
{
    LIFT_STUB(0x5f5b90);
}

// 0x5f5dc0
void __cdecl Pc::ReleaseMembersForDistribute(::Pc **, int)
{
    LIFT_STUB(0x5f5dc0);
}

// 0x5f5ee0
int __cdecl Pc::GetTeamMembersForDistribute(::Pc **, ::vector16 const &, int, bool)
{
    LIFT_STUB(0x5f5ee0);
}

// 0x5f60a0
bool __cdecl Pc::UpdateLogoutTime(void)
{
    LIFT_STUB(0x5f60a0);
}

// 0x5f60e0
void __cdecl Pc::StartCombat(void)
{
    LIFT_STUB(0x5f60e0);
}

// 0x5f6620
void __cdecl Pc::FinishCombat(void)
{
    LIFT_STUB(0x5f6620);
}

// 0x5f6ba0
void __cdecl Pc::ChangeGradeExpirationTimeForDebug(int, __int64)
{
    LIFT_STUB(0x5f6ba0);
}

// 0x5f6c80
bool __cdecl Pc::AddAndActivateGrade(::GradeInfo &)
{
    LIFT_STUB(0x5f6c80);
}

// 0x5f6e80
bool __cdecl Pc::DeleteGrade(int)
{
    LIFT_STUB(0x5f6e80);
}

// 0x5f7000
void __cdecl Pc::ActivateAllGradeBenefits(void)
{
    LIFT_STUB(0x5f7000);
}
