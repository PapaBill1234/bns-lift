// partyauction.h: partyauction.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class BidCurrentAuctionItemTask
{
private:
    virtual void __cdecl start(void);  // 0x176130
};

class DistributionCurrentAuctionItemTask
{
private:
    virtual void __cdecl start(void);  // 0x175f70
};

class FinishPartyAuctionTask
{
private:
    virtual void __cdecl start(void);  // 0x175e80
};

class GiveUpCurrentAuctionItemTask
{
private:
    virtual void __cdecl start(void);  // 0x176050
};

class PartyAuction : public ::RefCntObject
{
public:
    struct AuctionItem
    {
        __int64 dataKey;  // +0
        short count;  // +8
        char additionalInfo;  // +10
        char index;  // +11
        char page;  // +12
        bool finish;  // +13
    };
    struct AuctionMember
    {
        ::Pc *pc;  // +0
        bool pass;  // +8
        char page;  // +9
    };
public:
    virtual ~PartyAuction();  // LIFT: declared for the PDB vtable; the body is in a later card
private:
    virtual void deallocate_me(void *, wchar_t const *, int);  // LIFT: PDB override; the body is in a later card
public:
    bool __cdecl Initialize(::PartyAuction::AuctionItem *const, char, __int64, unsigned __int64, unsigned __int64, __int64, __int64, __int64, ::PartyPickupRule);  // 0x171a20
    bool __cdecl Enter(::Pc **const, char);  // 0x171b70
    bool __cdecl Join(::PartyAuction::AuctionItem *const, char, ::Pc **const, char);  // 0x171cd0
    bool __cdecl Leave(::Pc *, bool, ::TeamPartyProxy *);  // 0x172650
    void __cdecl Open(void);  // 0x172910
    void __cdecl Close(::TeamPartyProxy *);  // 0x172c60
private:
    bool __cdecl startAuction(::TeamPartyProxy *);  // 0x172d90
    bool __cdecl nextStep(void);  // 0x173570
public:
    void __cdecl Clear(void);  // 0x1735e0
private:
    void __cdecl sendSelectPacket(void);  // 0x173640
    bool __cdecl checkAuth(int);  // 0x1736c0
    int __cdecl getAuthMemberCount(void);  // 0x173710
public:
    bool __cdecl FinishAuction(unsigned __int64, char, ::TeamPartyProxy *, bool);  // 0x173780
    short __cdecl BidCurrrentItem(::Pc *, __int64, char);  // 0x174660
private:
    bool __cdecl checkAllPass(::TeamPartyProxy *);  // 0x174fc0
public:
    short __cdecl GiveUpCurrrentItem(::Pc *, char);  // 0x175050
    bool __cdecl DistributionCurrentItem(unsigned __int64, ::TeamPartyProxy *);  // 0x175430
private:
    // PDB layout of PartyAuction (size 0x1D8).
    ::PartyAuction::AuctionItem _auctionItems[16];  // +0x18
    char _auctionitemCount;  // +0x118
    char _currentAuctionIndex;  // +0x119
    bool _currentAuctionFinish;  // +0x11A
    __int64 _currentAuctionLimitTime;  // +0x120
    long _currnetAuctionDuration;  // +0x128
    __int64 _currentItemPrice;  // +0x130
    __int64 _currentItemBiddingMember;  // +0x138
    __int64 _emcee;  // +0x140
    __int64 _partyId;  // +0x148
    __int64 _zoneId;  // +0x150
    __int64 _targetId;  // +0x158
    __int64 _partyOptionStartPrice;  // +0x160
    int _partyOptionPickupRule;  // +0x168 LIFT: PartyPickupRule view
    char _page;  // +0x16C
    ::PartyAuction::AuctionMember _members[6];  // +0x170
    char _memberCount;  // +0x1D0
};

class PassPartyAuctionTask
{
private:
    virtual void __cdecl start(void);  // 0x175d90
};

