// guildjointicket.h: guildjointicket.cpp, guildjointicket.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

// PDB: GuildJoinTicket, size 0x68.
class GuildJoinTicket : public DynamicRefCntObj
{
protected:
    __cdecl GuildJoinTicket(void);  // 0x115dc0
    virtual __cdecl ~GuildJoinTicket(void);  // 0x115e30
    bool __cdecl Initialize(::GuildJoinTicketKey, ::GuildJoinTicketTicketInfo);  // 0x115f50
    unsigned __int64 __cdecl GetPcdbid(void);  // 0x1160c0
    unsigned __int64 __cdecl GetGuildId(void);  // 0x1161a0
    short __cdecl GetTicketType(void);  // 0x116280
    short __cdecl GetTicketState(void);  // 0x116360
    bool __cdecl UpdateTicketState(short);  // 0x116440
    __int64 __cdecl GetExpirationTime(void);  // 0x116680
    bool __cdecl UpdateExpirationTime(__int64);  // 0x116760
    bool __cdecl IsReserveDelete(void);  // 0x116860
    void __cdecl SetReserveDelete(void);  // 0x116950
    ::GuildJoinTicketListPerGuild * __cdecl GetTicketListPerGuild(void);  // 0x116a40
    void __cdecl SetTicketListPerGuild(::GuildJoinTicketListPerGuild *);  // 0x116b20
public:
    static short __cdecl GetTicketStateFromInProgressTicketState(short);  // 0x36deb0
private:
    unsigned __int64 _pcdbid;  // +0x18
    unsigned __int64 _guildId;  // +0x20
    short _ticketType;  // +0x28
    short _ticketState;  // +0x2a
    __int64 _expirationTime;  // +0x30
    ::GuildJoinTicketListPerGuild *_ticketListPerGuild;  // +0x38
    CriticalSection _lock;  // +0x40
};
static_assert(sizeof(GuildJoinTicket) == 0x68, "sizeof GuildJoinTicket");

// PDB: GuildJoinTicketListPerGuild, size 0x200.
// LIFT: the PDB virtual destructor has no declared body yet; the implicit destructor stands in for it.
class GuildJoinTicketListPerGuild : public DynamicRefCntObj
{
protected:
    __cdecl GuildJoinTicketListPerGuild(void);  // 0x118370
    bool __cdecl Initialize(unsigned __int64, int, int);  // 0x118440
    void __cdecl Clear(void);  // 0x118570
    bool __cdecl IsInProgress(void);  // 0x118740
    void __cdecl SetInProgress(bool);  // 0x118830
    int __cdecl GetGuildApplicationCount(void);  // 0x118920
    int __cdecl GetGuildInvitationCount(void);  // 0x118a10
    __int64 __cdecl GetTimeStamp(void);  // 0x118b00
    void __cdecl UpdateTimeStamp(void);  // 0x118bf0
    ::GuildJoinTicket * __cdecl GetGuildJoinTicket(unsigned __int64);  // 0x118cf0
    int __cdecl RetrieveGuildJoinTicketList(__int64 &, ::Game_GuildJoinTicketInfo *);  // 0x118ea0
    int __cdecl GetAcceptedGuildJoinTicketCount(void);  // 0x119070
    bool __cdecl AddGuildJoinTicket(::GuildJoinTicket *);  // 0x119200
    void __cdecl DeleteGuildJoinTicket(unsigned __int64);  // 0x119440
    void __cdecl DeleteAllGuildJoinTicket(void);  // 0x119610
    void __cdecl ClearExpiredGuildJoinTicket(__int64);  // 0x1197c0
private:
    unsigned __int64 _guildId;  // +0x18
    ::GuildJoinTicket *_ticketList[50];  // +0x20
    int _guildApplicationCount;  // +0x1b0
    int _guildInvitationCount;  // +0x1b4
    int _maxGuildApplicationQuota;  // +0x1b8
    int _maxGuildInvitationQuota;  // +0x1bc
    int _maxGuildJoinTicketQuota;  // +0x1c0
    __int64 _timeStamp;  // +0x1c8
    bool _inProgress;  // +0x1d0
    CriticalSection _lock;  // +0x1d8
};
static_assert(sizeof(GuildJoinTicketListPerGuild) == 0x200, "sizeof GuildJoinTicketListPerGuild");

class GuildJoinTicketListPerPc
{
protected:
    bool __cdecl Initialize(unsigned __int64, int, int);  // 0x116c60
    void __cdecl Clear(void);  // 0x116d90
    bool __cdecl IsInProgress(void);  // 0x116f60
    void __cdecl SetInProgress(bool);  // 0x117050
    int __cdecl GetGuildApplicationCount(void);  // 0x117140
    int __cdecl GetGuildInvitationCount(void);  // 0x117230
    ::GuildJoinTicket * __cdecl GetGuildJoinTicket(unsigned __int64);  // 0x117320
    int __cdecl RetrieveGuildJoinTicketList(::Game_GuildJoinTicketInfo *);  // 0x1174d0
    bool __cdecl HasAcceptedGuildJoinTicket(void);  // 0x117680
    unsigned __int64 __cdecl GetAcceptedGuildApplicationGuildId(void);  // 0x117870
    bool __cdecl AddGuildJoinTicket(::GuildJoinTicket *);  // 0x117a40
    void __cdecl DeleteGuildJoinTicket(unsigned __int64);  // 0x117c70
    void __cdecl DeleteOtherGuildJoinTicket(unsigned __int64);  // 0x117e40
    void __cdecl DeleteAllGuildJoinTicket(void);  // 0x118010
    void __cdecl ClearExpiredGuildJoinTicket(__int64);  // 0x1181c0
};

class GuildJoinTicketManager
{
public:
    __cdecl GuildJoinTicketManager(void);  // 0x119980
    __cdecl ~GuildJoinTicketManager(void);  // 0x119a40
    bool __cdecl Initialize(int, int, int, int);  // 0x119b50
    int __cdecl RetrieveGuildJoinTicketListPerGuild(unsigned __int64, __int64 &, ::Game_GuildJoinTicketInfo *);  // 0x119c90
    int __cdecl RetrieveGuildJoinTicketListPerPc(unsigned __int64, ::Game_GuildJoinTicketInfo *);  // 0x119db0
    unsigned __int64 __cdecl GetGuildApplicationAcceptedGuildId(unsigned __int64);  // 0x119ea0
    bool __cdecl AddGuildJoinTicket(::GuildJoinTicketKey, ::GuildJoinTicketTicketInfo, short &);  // 0x119f40
    bool __cdecl DeleteAllGuildJoinTicketPerPc(unsigned __int64, short &);  // 0x11a5b0
    bool __cdecl DeleteAllGuildJoinTicketPerGuild(unsigned __int64, short &);  // 0x11a700
    bool __cdecl TrySendGuildApplication(::GuildJoinTicketKey, ::GuildJoinTicketTicketInfo, short &);  // 0x11a860
    bool __cdecl FinishSendGuildApplication(::GuildJoinTicketKey, __int64, short &);  // 0x11afa0
    bool __cdecl CancelSendGuildApplication(::GuildJoinTicketKey, short &);  // 0x11b300
    bool __cdecl TryCancelGuildApplication(::GuildJoinTicketKey, short &);  // 0x11b6f0
    bool __cdecl FinishCancelGuildApplication(::GuildJoinTicketKey, short &);  // 0x11ba90
    bool __cdecl CancelCancelGuildApplication(::GuildJoinTicketKey, short &);  // 0x11be80
    bool __cdecl TryRejectGuildApplication(::GuildJoinTicketKey, short &, short &);  // 0x11c1a0
    bool __cdecl FinishRejectGuildApplication(::GuildJoinTicketKey, short &);  // 0x11c5a0
    bool __cdecl CancelRejectGuildApplication(::GuildJoinTicketKey, short &);  // 0x11c990
    bool __cdecl TryAcceptGuildApplication(::GuildJoinTicketKey, short, short &);  // 0x11cce0
    bool __cdecl FinishAcceptGuildApplication(::GuildJoinTicketKey, __int64, short &);  // 0x11d120
    bool __cdecl CancelAcceptGuildApplication(::GuildJoinTicketKey, short &);  // 0x11d480
    bool __cdecl TrySendGuildInvitation(::GuildJoinTicketKey, ::GuildJoinTicketTicketInfo, short &);  // 0x11d7a0
    bool __cdecl FinishSendGuildInvitation(::GuildJoinTicketKey, __int64, short &);  // 0x11dee0
    bool __cdecl CancelSendGuildInvitation(::GuildJoinTicketKey, short &);  // 0x11e200
    bool __cdecl TryCancelGuildInvitation(::GuildJoinTicketKey, short &);  // 0x11e620
    bool __cdecl FinishCancelGuildInvitation(::GuildJoinTicketKey, short &);  // 0x11e980
    bool __cdecl CancelCancelGuildInvitation(::GuildJoinTicketKey, short &);  // 0x11eda0
    bool __cdecl TryRejectGuildInvitation(::GuildJoinTicketKey, short &);  // 0x11f080
    bool __cdecl FinishRejectGuildInvitation(::GuildJoinTicketKey, short &);  // 0x11f430
    bool __cdecl CancelRejectGuildInvitation(::GuildJoinTicketKey, short &);  // 0x11f850
    bool __cdecl TryJoinGuildRenewalByAcceptedGuildApplication(::GuildJoinTicketKey, short &);  // 0x11fb30
    bool __cdecl FinishJoinGuildRenewalByAcceptedGuildApplication(::GuildJoinTicketKey, short &);  // 0x11fe30
    bool __cdecl CancelJoinGuildRenewalByAcceptedGuildApplication(::GuildJoinTicketKey, short &);  // 0x1201f0
    bool __cdecl TryJoinGuildRenewalByAcceptingGuildInvitation(::GuildJoinTicketKey, short, short &);  // 0x1204b0
    bool __cdecl FinishJoinGuildRenewalByAcceptingGuildInvitation(::GuildJoinTicketKey, short &);  // 0x1208b0
    bool __cdecl CancelJoinGuildRenewalByAcceptingGuildInvitation(::GuildJoinTicketKey, short &);  // 0x120c70
private:
    ::GuildJoinTicketListPerPc * __cdecl createTicketListPerPc(unsigned __int64, ::std::map<unsigned __int64, ::GuildJoinTicketListPerPc *, ::std::less<unsigned __int64>, ::StlAllocator< ::std::pair<unsigned __int64, ::GuildJoinTicketListPerPc *>, 2> >::iterator &);  // 0x120f50
    ::GuildJoinTicketListPerGuild * __cdecl createTicketListPerGuild(unsigned __int64, ::std::map<unsigned __int64, ::GuildJoinTicketListPerGuild *, ::std::less<unsigned __int64>, ::StlAllocator< ::std::pair<unsigned __int64, ::GuildJoinTicketListPerGuild *>, 2> >::iterator &);  // 0x121100
};

