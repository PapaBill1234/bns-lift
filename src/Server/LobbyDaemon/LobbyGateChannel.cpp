// LobbyGateChannel.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "LobbyGateChannel.h"
#include "LiftStub.h"

// 0xbbfb0
void LobbyGateChannel::SendInitSessionWithNPTokenFail(unsigned long long, short)
{
    LIFT_STUB(0xbbfb0);
}

// 0xbc080
void LobbyGateChannel::SendInitSessionWithLobbyTokenOk(unsigned long long, unsigned long long)
{
    LIFT_STUB(0xbc080);
}

// 0xbc150
void LobbyGateChannel::SendInitSessionWithLobbyTokenFail(unsigned long long, short)
{
    LIFT_STUB(0xbc150);
}

// 0xbc220
void LobbyGateChannel::SendStartSessionWithNPTokenOk(unsigned long long, char, id128 const&, unsigned long, unsigned short, bool, GradeService const&, bool, long long, int, GameAccountExpInfo const&)
{
    LIFT_STUB(0xbc220);
}

// 0xbc540
void LobbyGateChannel::SendStartSessionWithNPTokenFail(unsigned long long, short)
{
    LIFT_STUB(0xbc540);
}

// 0xbc610
void LobbyGateChannel::SendStartSessionWithLobbyTokenOk(unsigned long long, bool, GradeService const&, int, GameAccountExpInfo const&)
{
    LIFT_STUB(0xbc610);
}

// 0xbc8f0
void LobbyGateChannel::SendStartSessionWithLobbyTokenFail(unsigned long long, short)
{
    LIFT_STUB(0xbc8f0);
}

// 0xbc9c0
void LobbyGateChannel::SendCloseAnonymousSessionNotify(unsigned long long)
{
    LIFT_STUB(0xbc9c0);
}

// 0xbca80
void LobbyGateChannel::SendCloseSessionNotify(unsigned long long)
{
    LIFT_STUB(0xbca80);
}

// 0xbcb40
void LobbyGateChannel::SendKickNotify(unsigned long long, char)
{
    LIFT_STUB(0xbcb40);
}

// 0xbcc10
void LobbyGateChannel::SendGetCharacterInfoListFail(unsigned long long, short)
{
    LIFT_STUB(0xbcc10);
}

// 0xbcce0
void LobbyGateChannel::SendGetCharacterInfoFail(unsigned long long, id128 const&, short)
{
    LIFT_STUB(0xbcce0);
}

// 0xbcdd0
void LobbyGateChannel::SendCreateCharacterOk(unsigned long long, unsigned long long, id128 const&, short, wchar_t const*, char*, short, long long, char, long long, int)
{
    LIFT_STUB(0xbcdd0);
}

// 0xbcf40
void LobbyGateChannel::SendCreateCharacterFail(unsigned long long, id128 const&, short)
{
    LIFT_STUB(0xbcf40);
}

// 0xbd030
void LobbyGateChannel::SendDeleteCharacterOk(unsigned long long, id128 const&, char, long)
{
    LIFT_STUB(0xbd030);
}

// 0xbd250
void LobbyGateChannel::SendCancelWaitCharacterDeletionOk(unsigned long long, id128 const&)
{
    LIFT_STUB(0xbd250);
}

// 0xbd450
void LobbyGateChannel::SendEndWaitCharacterDeletionNotify(unsigned long long, id128 const&)
{
    LIFT_STUB(0xbd450);
}

// 0xbd530
void LobbyGateChannel::SendGetEnterWorldTokenFail(unsigned long long, short)
{
    LIFT_STUB(0xbd530);
}

// 0xbd600
void LobbyGateChannel::SendGetEnterWorldTokenOk(unsigned long long, unsigned long long, short)
{
    LIFT_STUB(0xbd600);
}

// 0xbd6e0
void LobbyGateChannel::SendStartWaitNotify(unsigned long long, WaitInfo const&)
{
    LIFT_STUB(0xbd6e0);
}

// 0xbd9c0
void LobbyGateChannel::SendGetWaitInfoOk(unsigned long long, WaitInfo const&)
{
    LIFT_STUB(0xbd9c0);
}

// 0xbdca0
void LobbyGateChannel::SendGetWaitInfoFail(unsigned long long, short)
{
    LIFT_STUB(0xbdca0);
}

// 0xbdd70
void LobbyGateChannel::SendGiveupWaitOk(unsigned long long)
{
    LIFT_STUB(0xbdd70);
}

// 0xbde30
void LobbyGateChannel::SendGiveupWaitFail(unsigned long long, short)
{
    LIFT_STUB(0xbde30);
}

// 0xbdf00
void LobbyGateChannel::SendEndWaitNotify(unsigned long long, unsigned long long)
{
    LIFT_STUB(0xbdf00);
}

// 0xbdfd0
void LobbyGateChannel::SendGetChargeInfoOk(unsigned long long, char, char, long, short, char, unsigned int, char, char, char)
{
    LIFT_STUB(0xbdfd0);
}

// 0xbe120
void LobbyGateChannel::SendGetChargeInfoFail(unsigned long long, short)
{
    LIFT_STUB(0xbe120);
}

// 0xbe1f0
void LobbyGateChannel::SendRecoverCharacterOk(unsigned long long, id128 const&)
{
    LIFT_STUB(0xbe1f0);
}

// 0xbe3f0
void LobbyGateChannel::SendBindCharacterSlotFail(unsigned long long, id128 const&, unsigned long long, short)
{
    LIFT_STUB(0xbe3f0);
}

// 0xbe4f0
void LobbyGateChannel::SendAccountInventoryNotify(unsigned long long, char, unsigned long long)
{
    LIFT_STUB(0xbe4f0);
}

// 0xbe5d0
void LobbyGateChannel::SendGetGoodsCountOk(unsigned long long, int)
{
    LIFT_STUB(0xbe5d0);
}

// 0xbe6a0
void LobbyGateChannel::SendGetGoodsCountFail(unsigned long long, short)
{
    LIFT_STUB(0xbe6a0);
}

// 0xbe770
void LobbyGateChannel::SendListGoodsOk(unsigned long long, Goods*, int)
{
    LIFT_STUB(0xbe770);
}

// 0xbe980
void LobbyGateChannel::SendListGoodsFail(unsigned long long, short)
{
    LIFT_STUB(0xbe980);
}

// 0xbea50
void LobbyGateChannel::SendTakeGoodsOk(unsigned long long, unsigned long long, LobbyServiceItem*, int)
{
    LIFT_STUB(0xbea50);
}

// 0xbed00
void LobbyGateChannel::SendTakeGoodsFail(unsigned long long, short)
{
    LIFT_STUB(0xbed00);
}

// 0xbedd0
void LobbyGateChannel::SendListLobbyServiceItemInfoOk(unsigned long long, char, int, LobbyServiceItem*, int)
{
    LIFT_STUB(0xbedd0);
}

// 0xbf080
void LobbyGateChannel::SendListLobbyServiceItemInfoFail(unsigned long long, char, short)
{
    LIFT_STUB(0xbf080);
}

// 0xbf160
void LobbyGateChannel::SendGetLobbyServiceItemInfoOk(unsigned long long, LobbyServiceItem const&)
{
    LIFT_STUB(0xbf160);
}

// 0xbf2e0
void LobbyGateChannel::SendGetLobbyServiceItemInfoFail(unsigned long long, unsigned long long, short)
{
    LIFT_STUB(0xbf2e0);
}

// 0xbf3c0
void LobbyGateChannel::SendGetServiceEntryListFail(unsigned long long, short)
{
    LIFT_STUB(0xbf3c0);
}

// 0xbf490
void LobbyGateChannel::SendChangeCharacterAppearanceWithAccountInventoryItemOk(unsigned long long, id128 const&, char*, short, unsigned long long, unsigned long long)
{
    LIFT_STUB(0xbf490);
}

// 0xbf5a0
void LobbyGateChannel::SendChangeCharacterAppearanceWithAccountInventoryItemFail(unsigned long long, id128 const&, unsigned long long, unsigned long long, short)
{
    LIFT_STUB(0xbf5a0);
}

// 0xbf6b0
void LobbyGateChannel::SendChangeCharacterSexWithAccountInventoryItemOk(unsigned long long, id128 const&, char*, short, unsigned long long, unsigned long long)
{
    LIFT_STUB(0xbf6b0);
}

// 0xbf7c0
void LobbyGateChannel::SendChangeCharacterSexWithAccountInventoryItemFail(unsigned long long, id128 const&, unsigned long long, unsigned long long, short)
{
    LIFT_STUB(0xbf7c0);
}

// 0xbf8d0
void LobbyGateChannel::SendChangeCharacterRaceWithAccountInventoryItemOk(unsigned long long, id128 const&, char*, short, unsigned long long, unsigned long long)
{
    LIFT_STUB(0xbf8d0);
}

// 0xbf9e0
void LobbyGateChannel::SendChangeCharacterRaceWithAccountInventoryItemFail(unsigned long long, id128 const&, unsigned long long, unsigned long long, short)
{
    LIFT_STUB(0xbf9e0);
}

// 0xbfaf0
void LobbyGateChannel::SendRenameCharacterWithAccountInventoryItemOk(unsigned long long, id128 const&, wchar_t const*, unsigned long long, unsigned long long)
{
    LIFT_STUB(0xbfaf0);
}

// 0xbfc00
void LobbyGateChannel::SendRenameCharacterWithAccountInventoryItemFail(unsigned long long, id128 const&, unsigned long long, unsigned long long, short)
{
    LIFT_STUB(0xbfc00);
}

// 0xbfd10
void LobbyGateChannel::SendAddSlotWithAccountInventoryItemOk(unsigned long long, unsigned long long, unsigned long long, id128 const&)
{
    LIFT_STUB(0xbfd10);
}

// 0xbfe10
void LobbyGateChannel::SendAddSlotWithAccountInventoryItemFail(unsigned long long, unsigned long long, unsigned long long, short)
{
    LIFT_STUB(0xbfe10);
}

// 0xbff00
void LobbyGateChannel::SendChangeUserNameWithAccountInventoryItemOk(unsigned long long, wchar_t const*, unsigned long long, unsigned long long, unsigned int)
{
    LIFT_STUB(0xbff00);
}

// 0xc0050
void LobbyGateChannel::SendChangeUserNameWithAccountInventoryItemFail(unsigned long long, unsigned long long, unsigned long long, short)
{
    LIFT_STUB(0xc0050);
}

// 0xc0160
void LobbyGateChannel::SendExtendJumpingCharacterCreationQuotaWithAccountInventoryItemOk(unsigned long long, unsigned long long, unsigned long long, int)
{
    LIFT_STUB(0xc0160);
}

// 0xc0250
void LobbyGateChannel::SendExtendJumpingCharacterCreationQuotaWithAccountInventoryItemFail(unsigned long long, unsigned long long, unsigned long long, short)
{
    LIFT_STUB(0xc0250);
}

// 0xc0340
void LobbyGateChannel::SendCreateInitialUserNameOk(unsigned long long, wchar_t const*)
{
    LIFT_STUB(0xc0340);
}

// 0xc0460
void LobbyGateChannel::SendCreateInitialUserNameFail(unsigned long long, short)
{
    LIFT_STUB(0xc0460);
}

// 0xc0550
void LobbyGateChannel::SendActivateGradeOk(unsigned long long, int, int, long long, long long)
{
    LIFT_STUB(0xc0550);
}

// 0xc0670
void LobbyGateChannel::SendActivateGradeFail(unsigned long long, int, int, short)
{
    LIFT_STUB(0xc0670);
}

// 0xc0790
void LobbyGateChannel::SendChangedGradeNotify(unsigned long long, int, int, bool, int, long long, long long, wchar_t const*)
{
    LIFT_STUB(0xc0790);
}

// 0xc0970
void LobbyGateChannel::SendChangedGradeLevelNotify(unsigned long long, int, int, int, int, int)
{
    LIFT_STUB(0xc0970);
}

// 0xc0aa0
LobbyGateChannelManager::~LobbyGateChannelManager()
{
    LIFT_STUB(0xc0aa0);
}

// 0xc0b80
bool LobbyGateChannelManager::Add(LobbyGateChannel*)
{
    LIFT_STUB(0xc0b80);
}

// 0xc0c40
void LobbyGateChannelManager::Remove(short)
{
    LIFT_STUB(0xc0c40);
}

// 0xc0d50
LobbyGateChannel* LobbyGateChannelManager::Acquire(short)
{
    LIFT_STUB(0xc0d50);
}

// 0xc0e20
void LobbyGateChannelManager::BroadcastAnnounceNotify(wchar_t const*)
{
    LIFT_STUB(0xc0e20);
}

// 0xc0f20
bool LobbyGateChannelManager::OnAccept(Session const*) const
{
    LIFT_STUB(0xc0f20);
}

// 0xc0f80
bool LobbyGateChannelManager::OnConnect(Session const*, bool) const
{
    LIFT_STUB(0xc0f80);
}

// 0xc1030
void LobbyGateChannelManager::OnClose(Session const*, bool) const
{
    LIFT_STUB(0xc1030);
}

// 0xc11d0
bool LobbyGateChannelManager::PacketHandler(Session const*, Packet const*) const
{
    LIFT_STUB(0xc11d0);
}
