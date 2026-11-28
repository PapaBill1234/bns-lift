// guildjointicket_cpp.cpp: guildjointicket.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "guildjointicket.h"
#include "LiftStub.h"
#include <string.h>

#pragma comment(linker, "/INCLUDE:??0GuildJoinTicket@@IEAA@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:??0GuildJoinTicketListPerGuild@@IEAA@XZ")  // LIFT: dead-strip keep (no live caller yet)

// 0x115dc0
__cdecl GuildJoinTicket::GuildJoinTicket(void)
    : _pcdbid(0)
    , _guildId(0)
    , _ticketType(0)
    , _ticketState(0)
    , _expirationTime(0)
    , _ticketListPerGuild(nullptr)
{
}

// 0x115e30
__cdecl GuildJoinTicket::~GuildJoinTicket(void)
{
    LIFT_STUB(0x115e30);
}

// 0x115f50
bool __cdecl GuildJoinTicket::Initialize(::GuildJoinTicketKey, ::GuildJoinTicketTicketInfo)
{
    LIFT_STUB(0x115f50);
}

// 0x1160c0
unsigned __int64 __cdecl GuildJoinTicket::GetPcdbid(void)
{
    LIFT_STUB(0x1160c0);
}

// 0x1161a0
unsigned __int64 __cdecl GuildJoinTicket::GetGuildId(void)
{
    LIFT_STUB(0x1161a0);
}

// 0x116280
short __cdecl GuildJoinTicket::GetTicketType(void)
{
    LIFT_STUB(0x116280);
}

// 0x116360
short __cdecl GuildJoinTicket::GetTicketState(void)
{
    LIFT_STUB(0x116360);
}

// 0x116440
bool __cdecl GuildJoinTicket::UpdateTicketState(short)
{
    LIFT_STUB(0x116440);
}

// 0x116680
__int64 __cdecl GuildJoinTicket::GetExpirationTime(void)
{
    LIFT_STUB(0x116680);
}

// 0x116760
bool __cdecl GuildJoinTicket::UpdateExpirationTime(__int64)
{
    LIFT_STUB(0x116760);
}

// 0x116860
bool __cdecl GuildJoinTicket::IsReserveDelete(void)
{
    LIFT_STUB(0x116860);
}

// 0x116950
void __cdecl GuildJoinTicket::SetReserveDelete(void)
{
    LIFT_STUB(0x116950);
}

// 0x116a40
::GuildJoinTicketListPerGuild * __cdecl GuildJoinTicket::GetTicketListPerGuild(void)
{
    LIFT_STUB(0x116a40);
}

// 0x116b20
void __cdecl GuildJoinTicket::SetTicketListPerGuild(::GuildJoinTicketListPerGuild *)
{
    LIFT_STUB(0x116b20);
}

// 0x116c60
bool __cdecl GuildJoinTicketListPerPc::Initialize(unsigned __int64, int, int)
{
    LIFT_STUB(0x116c60);
}

// 0x116d90
void __cdecl GuildJoinTicketListPerPc::Clear(void)
{
    LIFT_STUB(0x116d90);
}

// 0x116f60
bool __cdecl GuildJoinTicketListPerPc::IsInProgress(void)
{
    LIFT_STUB(0x116f60);
}

// 0x117050
void __cdecl GuildJoinTicketListPerPc::SetInProgress(bool)
{
    LIFT_STUB(0x117050);
}

// 0x117140
int __cdecl GuildJoinTicketListPerPc::GetGuildApplicationCount(void)
{
    LIFT_STUB(0x117140);
}

// 0x117230
int __cdecl GuildJoinTicketListPerPc::GetGuildInvitationCount(void)
{
    LIFT_STUB(0x117230);
}

// 0x117320
::GuildJoinTicket * __cdecl GuildJoinTicketListPerPc::GetGuildJoinTicket(unsigned __int64)
{
    LIFT_STUB(0x117320);
}

// 0x1174d0
int __cdecl GuildJoinTicketListPerPc::RetrieveGuildJoinTicketList(::Game_GuildJoinTicketInfo *)
{
    LIFT_STUB(0x1174d0);
}

// 0x117680
bool __cdecl GuildJoinTicketListPerPc::HasAcceptedGuildJoinTicket(void)
{
    LIFT_STUB(0x117680);
}

// 0x117870
unsigned __int64 __cdecl GuildJoinTicketListPerPc::GetAcceptedGuildApplicationGuildId(void)
{
    LIFT_STUB(0x117870);
}

// 0x117a40
bool __cdecl GuildJoinTicketListPerPc::AddGuildJoinTicket(::GuildJoinTicket *)
{
    LIFT_STUB(0x117a40);
}

// 0x117c70
void __cdecl GuildJoinTicketListPerPc::DeleteGuildJoinTicket(unsigned __int64)
{
    LIFT_STUB(0x117c70);
}

// 0x117e40
void __cdecl GuildJoinTicketListPerPc::DeleteOtherGuildJoinTicket(unsigned __int64)
{
    LIFT_STUB(0x117e40);
}

// 0x118010
void __cdecl GuildJoinTicketListPerPc::DeleteAllGuildJoinTicket(void)
{
    LIFT_STUB(0x118010);
}

// 0x1181c0
void __cdecl GuildJoinTicketListPerPc::ClearExpiredGuildJoinTicket(__int64)
{
    LIFT_STUB(0x1181c0);
}

// 0x118370
__cdecl GuildJoinTicketListPerGuild::GuildJoinTicketListPerGuild(void)
    : _guildId(0)
    , _guildApplicationCount(0)
    , _guildInvitationCount(0)
    , _maxGuildApplicationQuota(0)
    , _maxGuildInvitationQuota(0)
    , _maxGuildJoinTicketQuota(0)
    , _timeStamp(0)
    , _inProgress(false)
{
    memset(_ticketList, 0, sizeof(_ticketList));
}

// 0x118440
bool __cdecl GuildJoinTicketListPerGuild::Initialize(unsigned __int64, int, int)
{
    LIFT_STUB(0x118440);
}

// 0x118570
void __cdecl GuildJoinTicketListPerGuild::Clear(void)
{
    LIFT_STUB(0x118570);
}

// 0x118740
bool __cdecl GuildJoinTicketListPerGuild::IsInProgress(void)
{
    LIFT_STUB(0x118740);
}

// 0x118830
void __cdecl GuildJoinTicketListPerGuild::SetInProgress(bool)
{
    LIFT_STUB(0x118830);
}

// 0x118920
int __cdecl GuildJoinTicketListPerGuild::GetGuildApplicationCount(void)
{
    LIFT_STUB(0x118920);
}

// 0x118a10
int __cdecl GuildJoinTicketListPerGuild::GetGuildInvitationCount(void)
{
    LIFT_STUB(0x118a10);
}

// 0x118b00
__int64 __cdecl GuildJoinTicketListPerGuild::GetTimeStamp(void)
{
    LIFT_STUB(0x118b00);
}

// 0x118bf0
void __cdecl GuildJoinTicketListPerGuild::UpdateTimeStamp(void)
{
    LIFT_STUB(0x118bf0);
}

// 0x118cf0
::GuildJoinTicket * __cdecl GuildJoinTicketListPerGuild::GetGuildJoinTicket(unsigned __int64)
{
    LIFT_STUB(0x118cf0);
}

// 0x118ea0
int __cdecl GuildJoinTicketListPerGuild::RetrieveGuildJoinTicketList(__int64 &, ::Game_GuildJoinTicketInfo *)
{
    LIFT_STUB(0x118ea0);
}

// 0x119070
int __cdecl GuildJoinTicketListPerGuild::GetAcceptedGuildJoinTicketCount(void)
{
    LIFT_STUB(0x119070);
}

// 0x119200
bool __cdecl GuildJoinTicketListPerGuild::AddGuildJoinTicket(::GuildJoinTicket *)
{
    LIFT_STUB(0x119200);
}

// 0x119440
void __cdecl GuildJoinTicketListPerGuild::DeleteGuildJoinTicket(unsigned __int64)
{
    LIFT_STUB(0x119440);
}

// 0x119610
void __cdecl GuildJoinTicketListPerGuild::DeleteAllGuildJoinTicket(void)
{
    LIFT_STUB(0x119610);
}

// 0x1197c0
void __cdecl GuildJoinTicketListPerGuild::ClearExpiredGuildJoinTicket(__int64)
{
    LIFT_STUB(0x1197c0);
}

// 0x119980
__cdecl GuildJoinTicketManager::GuildJoinTicketManager(void)
{
    LIFT_STUB(0x119980);
}

// 0x119a40
__cdecl GuildJoinTicketManager::~GuildJoinTicketManager(void)
{
    LIFT_STUB(0x119a40);
}

// 0x119b50
bool __cdecl GuildJoinTicketManager::Initialize(int, int, int, int)
{
    LIFT_STUB(0x119b50);
}

// 0x119c90
int __cdecl GuildJoinTicketManager::RetrieveGuildJoinTicketListPerGuild(unsigned __int64, __int64 &, ::Game_GuildJoinTicketInfo *)
{
    LIFT_STUB(0x119c90);
}

// 0x119db0
int __cdecl GuildJoinTicketManager::RetrieveGuildJoinTicketListPerPc(unsigned __int64, ::Game_GuildJoinTicketInfo *)
{
    LIFT_STUB(0x119db0);
}

// 0x119ea0
unsigned __int64 __cdecl GuildJoinTicketManager::GetGuildApplicationAcceptedGuildId(unsigned __int64)
{
    LIFT_STUB(0x119ea0);
}

// 0x119f40
bool __cdecl GuildJoinTicketManager::AddGuildJoinTicket(::GuildJoinTicketKey, ::GuildJoinTicketTicketInfo, short &)
{
    LIFT_STUB(0x119f40);
}

// 0x11a5b0
bool __cdecl GuildJoinTicketManager::DeleteAllGuildJoinTicketPerPc(unsigned __int64, short &)
{
    LIFT_STUB(0x11a5b0);
}

// 0x11a700
bool __cdecl GuildJoinTicketManager::DeleteAllGuildJoinTicketPerGuild(unsigned __int64, short &)
{
    LIFT_STUB(0x11a700);
}

// 0x11a860
bool __cdecl GuildJoinTicketManager::TrySendGuildApplication(::GuildJoinTicketKey, ::GuildJoinTicketTicketInfo, short &)
{
    LIFT_STUB(0x11a860);
}

// 0x11afa0
bool __cdecl GuildJoinTicketManager::FinishSendGuildApplication(::GuildJoinTicketKey, __int64, short &)
{
    LIFT_STUB(0x11afa0);
}

// 0x11b300
bool __cdecl GuildJoinTicketManager::CancelSendGuildApplication(::GuildJoinTicketKey, short &)
{
    LIFT_STUB(0x11b300);
}

// 0x11b6f0
bool __cdecl GuildJoinTicketManager::TryCancelGuildApplication(::GuildJoinTicketKey, short &)
{
    LIFT_STUB(0x11b6f0);
}

// 0x11ba90
bool __cdecl GuildJoinTicketManager::FinishCancelGuildApplication(::GuildJoinTicketKey, short &)
{
    LIFT_STUB(0x11ba90);
}

// 0x11be80
bool __cdecl GuildJoinTicketManager::CancelCancelGuildApplication(::GuildJoinTicketKey, short &)
{
    LIFT_STUB(0x11be80);
}

// 0x11c1a0
bool __cdecl GuildJoinTicketManager::TryRejectGuildApplication(::GuildJoinTicketKey, short &, short &)
{
    LIFT_STUB(0x11c1a0);
}

// 0x11c5a0
bool __cdecl GuildJoinTicketManager::FinishRejectGuildApplication(::GuildJoinTicketKey, short &)
{
    LIFT_STUB(0x11c5a0);
}

// 0x11c990
bool __cdecl GuildJoinTicketManager::CancelRejectGuildApplication(::GuildJoinTicketKey, short &)
{
    LIFT_STUB(0x11c990);
}

// 0x11cce0
bool __cdecl GuildJoinTicketManager::TryAcceptGuildApplication(::GuildJoinTicketKey, short, short &)
{
    LIFT_STUB(0x11cce0);
}

// 0x11d120
bool __cdecl GuildJoinTicketManager::FinishAcceptGuildApplication(::GuildJoinTicketKey, __int64, short &)
{
    LIFT_STUB(0x11d120);
}

// 0x11d480
bool __cdecl GuildJoinTicketManager::CancelAcceptGuildApplication(::GuildJoinTicketKey, short &)
{
    LIFT_STUB(0x11d480);
}

// 0x11d7a0
bool __cdecl GuildJoinTicketManager::TrySendGuildInvitation(::GuildJoinTicketKey, ::GuildJoinTicketTicketInfo, short &)
{
    LIFT_STUB(0x11d7a0);
}

// 0x11dee0
bool __cdecl GuildJoinTicketManager::FinishSendGuildInvitation(::GuildJoinTicketKey, __int64, short &)
{
    LIFT_STUB(0x11dee0);
}

// 0x11e200
bool __cdecl GuildJoinTicketManager::CancelSendGuildInvitation(::GuildJoinTicketKey, short &)
{
    LIFT_STUB(0x11e200);
}

// 0x11e620
bool __cdecl GuildJoinTicketManager::TryCancelGuildInvitation(::GuildJoinTicketKey, short &)
{
    LIFT_STUB(0x11e620);
}

// 0x11e980
bool __cdecl GuildJoinTicketManager::FinishCancelGuildInvitation(::GuildJoinTicketKey, short &)
{
    LIFT_STUB(0x11e980);
}

// 0x11eda0
bool __cdecl GuildJoinTicketManager::CancelCancelGuildInvitation(::GuildJoinTicketKey, short &)
{
    LIFT_STUB(0x11eda0);
}

// 0x11f080
bool __cdecl GuildJoinTicketManager::TryRejectGuildInvitation(::GuildJoinTicketKey, short &)
{
    LIFT_STUB(0x11f080);
}

// 0x11f430
bool __cdecl GuildJoinTicketManager::FinishRejectGuildInvitation(::GuildJoinTicketKey, short &)
{
    LIFT_STUB(0x11f430);
}

// 0x11f850
bool __cdecl GuildJoinTicketManager::CancelRejectGuildInvitation(::GuildJoinTicketKey, short &)
{
    LIFT_STUB(0x11f850);
}

// 0x11fb30
bool __cdecl GuildJoinTicketManager::TryJoinGuildRenewalByAcceptedGuildApplication(::GuildJoinTicketKey, short &)
{
    LIFT_STUB(0x11fb30);
}

// 0x11fe30
bool __cdecl GuildJoinTicketManager::FinishJoinGuildRenewalByAcceptedGuildApplication(::GuildJoinTicketKey, short &)
{
    LIFT_STUB(0x11fe30);
}

// 0x1201f0
bool __cdecl GuildJoinTicketManager::CancelJoinGuildRenewalByAcceptedGuildApplication(::GuildJoinTicketKey, short &)
{
    LIFT_STUB(0x1201f0);
}

// 0x1204b0
bool __cdecl GuildJoinTicketManager::TryJoinGuildRenewalByAcceptingGuildInvitation(::GuildJoinTicketKey, short, short &)
{
    LIFT_STUB(0x1204b0);
}

// 0x1208b0
bool __cdecl GuildJoinTicketManager::FinishJoinGuildRenewalByAcceptingGuildInvitation(::GuildJoinTicketKey, short &)
{
    LIFT_STUB(0x1208b0);
}

// 0x120c70
bool __cdecl GuildJoinTicketManager::CancelJoinGuildRenewalByAcceptingGuildInvitation(::GuildJoinTicketKey, short &)
{
    LIFT_STUB(0x120c70);
}

// 0x120f50
::GuildJoinTicketListPerPc * __cdecl GuildJoinTicketManager::createTicketListPerPc(unsigned __int64, ::std::map<unsigned __int64, ::GuildJoinTicketListPerPc *, ::std::less<unsigned __int64>, ::StlAllocator< ::std::pair<unsigned __int64, ::GuildJoinTicketListPerPc *>, 2> >::iterator &)
{
    LIFT_STUB(0x120f50);
}

// 0x121100
::GuildJoinTicketListPerGuild * __cdecl GuildJoinTicketManager::createTicketListPerGuild(unsigned __int64, ::std::map<unsigned __int64, ::GuildJoinTicketListPerGuild *, ::std::less<unsigned __int64>, ::StlAllocator< ::std::pair<unsigned __int64, ::GuildJoinTicketListPerGuild *>, 2> >::iterator &)
{
    LIFT_STUB(0x121100);
}
