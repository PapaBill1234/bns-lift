// partyauction.cpp: partyauction.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "partyauction.h"
#include "pc.h"
#include "LiftStub.h"

static_assert(sizeof(PartyAuction) == 0x1D8, "sizeof PartyAuction");

#pragma comment(linker, "/INCLUDE:?nextStep@PartyAuction@@AEAA_NXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?checkAuth@PartyAuction@@AEAA_NH@Z")  // LIFT: dead-strip keep (no live caller yet)

// 0x171a20
bool __cdecl PartyAuction::Initialize(::PartyAuction::AuctionItem *const, char, __int64, unsigned __int64, unsigned __int64, __int64, __int64, __int64, ::PartyPickupRule)
{
    LIFT_STUB(0x171a20);
}

// 0x171b70
bool __cdecl PartyAuction::Enter(::Pc **const, char)
{
    LIFT_STUB(0x171b70);
}

// 0x171cd0
bool __cdecl PartyAuction::Join(::PartyAuction::AuctionItem *const, char, ::Pc **const, char)
{
    LIFT_STUB(0x171cd0);
}

// 0x172650
bool __cdecl PartyAuction::Leave(::Pc *, bool, ::TeamPartyProxy *)
{
    LIFT_STUB(0x172650);
}

// 0x172910
void __cdecl PartyAuction::Open(void)
{
    LIFT_STUB(0x172910);
}

// 0x172c60
void __cdecl PartyAuction::Close(::TeamPartyProxy *)
{
    LIFT_STUB(0x172c60);
}

// 0x172d90
bool __cdecl PartyAuction::startAuction(::TeamPartyProxy *)
{
    LIFT_STUB(0x172d90);
}

// 0x173570
bool __cdecl PartyAuction::nextStep(void)
{
    // LIFT: the loop below is PartyAuction::isFinish, inlined in the original.
    bool finish = true;
    for (int i = 0; i < _auctionitemCount; ++i)
    {
        if (!_auctionItems[i].finish)
        {
            finish = false;
            break;
        }
    }
    if (finish)
        return false;

    do
    {
        _currentAuctionIndex = static_cast<char>((_currentAuctionIndex + 1) % _auctionitemCount);
    } while (_auctionItems[_currentAuctionIndex].finish);
    return true;
}

// 0x1735e0
void __cdecl PartyAuction::Clear(void)
{
    LIFT_STUB(0x1735e0);
}

// 0x173640
void __cdecl PartyAuction::sendSelectPacket(void)
{
    LIFT_STUB(0x173640);
}

// 0x1736c0
bool __cdecl PartyAuction::checkAuth(int memberIndex)
{
    if (memberIndex < 0 || memberIndex >= _memberCount)
        return false;
    if (_members[memberIndex].pc == nullptr)
        return false;
    return _auctionItems[_currentAuctionIndex].page >= _members[memberIndex].page;
}

// 0x173710
int __cdecl PartyAuction::getAuthMemberCount(void)
{
    LIFT_STUB(0x173710);
}

// 0x173780
bool __cdecl PartyAuction::FinishAuction(unsigned __int64, char, ::TeamPartyProxy *, bool)
{
    LIFT_STUB(0x173780);
}

// 0x174660
short __cdecl PartyAuction::BidCurrrentItem(::Pc *, __int64, char)
{
    LIFT_STUB(0x174660);
}

// 0x174fc0
bool __cdecl PartyAuction::checkAllPass(::TeamPartyProxy *)
{
    LIFT_STUB(0x174fc0);
}

// 0x175050
short __cdecl PartyAuction::GiveUpCurrrentItem(::Pc *, char)
{
    LIFT_STUB(0x175050);
}

// 0x175430
bool __cdecl PartyAuction::DistributionCurrentItem(unsigned __int64, ::TeamPartyProxy *)
{
    LIFT_STUB(0x175430);
}

// 0x175d90
void __cdecl PassPartyAuctionTask::start(void)
{
    LIFT_STUB(0x175d90);
}

// 0x175e80
void __cdecl FinishPartyAuctionTask::start(void)
{
    LIFT_STUB(0x175e80);
}

// 0x175f70
void __cdecl DistributionCurrentAuctionItemTask::start(void)
{
    LIFT_STUB(0x175f70);
}

// 0x176050
void __cdecl GiveUpCurrentAuctionItemTask::start(void)
{
    LIFT_STUB(0x176050);
}

// 0x176130
void __cdecl BidCurrentAuctionItemTask::start(void)
{
    LIFT_STUB(0x176130);
}
