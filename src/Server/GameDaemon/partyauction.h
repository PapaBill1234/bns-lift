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

class PartyAuction
{
public:
    struct AuctionItem {};
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
};

class PassPartyAuctionTask
{
private:
    virtual void __cdecl start(void);  // 0x175d90
};

