// LobbyGateChannel.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: LobbyGateChannel has its base and members (ld-24 batch 1). LobbyGateChannelManager has its PDB layout (gap-02).
#pragma once
#include <stddef.h>
#include "Channel.h"
#include "Lock.h"
#include "SharedChannel.h"
#include "Character.h"

class GameAccountExpInfo;
struct Goods;
class GradeService;
class LobbyGateChannel;
struct LobbyServiceItem;
class Packet;
class Session;
struct WaitInfo;
union id128;

class LobbyGateChannel : public SharedChannel
{
public:
    // LIFT: PDB inline method. The body is not in the PDB; it comes from the inlined code at the callers
    // (for example HandleLobbyLobbyGate_GetCharacterInfoListReq, 0xc5360).
    short GetWid() const
    {
        short wid = 0;
        if (_rawChannel != nullptr)
            wid = static_cast<short>(_rawChannel->GetId());
        return wid;
    }
    void SendInitSessionWithNPTokenOk(unsigned long long gatekey, unsigned long long clikey, id128 nptoken, id128 portalAccountId);  // 0xbbe90
    void SendInitSessionWithNPTokenFail(unsigned long long, short);  // 0xbbfb0
    void SendInitSessionWithLobbyTokenOk(unsigned long long, unsigned long long);  // 0xbc080
    void SendInitSessionWithLobbyTokenFail(unsigned long long, short);  // 0xbc150
    void SendStartSessionWithNPTokenOk(unsigned long long, char, id128 const&, unsigned long, unsigned short, bool, GradeService const&, bool, long long, int, GameAccountExpInfo const&);  // 0xbc220
    void SendStartSessionWithNPTokenFail(unsigned long long, short);  // 0xbc540
    void SendStartSessionWithLobbyTokenOk(unsigned long long, bool, GradeService const&, int, GameAccountExpInfo const&);  // 0xbc610
    void SendStartSessionWithLobbyTokenFail(unsigned long long, short);  // 0xbc8f0
    void SendCloseAnonymousSessionNotify(unsigned long long);  // 0xbc9c0
    void SendCloseSessionNotify(unsigned long long);  // 0xbca80
    void SendKickNotify(unsigned long long, char);  // 0xbcb40
    void SendGetCharacterInfoListFail(unsigned long long, short);  // 0xbcc10
    void SendGetCharacterInfoFail(unsigned long long, id128 const&, short);  // 0xbcce0
    void SendCreateCharacterOk(unsigned long long, unsigned long long, id128 const&, short, wchar_t const*, char*, short, long long, char, long long, int);  // 0xbcdd0
    void SendCreateCharacterFail(unsigned long long, id128 const&, short);  // 0xbcf40
    void SendDeleteCharacterOk(unsigned long long, id128 const&, char, long);  // 0xbd030
    void SendDeleteCharacterFail(unsigned long long, id128 const&, Character::ClientState, short);  // 0xbd130
    void SendCancelWaitCharacterDeletionOk(unsigned long long, id128 const&);  // 0xbd250
    void SendCancelWaitCharacterDeletionFail(unsigned long long, id128 const&, Character::ClientState, short);  // 0xbd330
    void SendEndWaitCharacterDeletionNotify(unsigned long long, id128 const&);  // 0xbd450
    void SendGetEnterWorldTokenFail(unsigned long long, short);  // 0xbd530
    void SendGetEnterWorldTokenOk(unsigned long long, unsigned long long, short);  // 0xbd600
    void SendStartWaitNotify(unsigned long long, WaitInfo const&);  // 0xbd6e0
    void SendGetWaitInfoOk(unsigned long long, WaitInfo const&);  // 0xbd9c0
    void SendGetWaitInfoFail(unsigned long long, short);  // 0xbdca0
    void SendGiveupWaitOk(unsigned long long);  // 0xbdd70
    void SendGiveupWaitFail(unsigned long long, short);  // 0xbde30
    void SendEndWaitNotify(unsigned long long, unsigned long long);  // 0xbdf00
    void SendGetChargeInfoOk(unsigned long long, char, char, long, short, char, unsigned int, char, char, char);  // 0xbdfd0
    void SendGetChargeInfoFail(unsigned long long, short);  // 0xbe120
    void SendRecoverCharacterOk(unsigned long long, id128 const&);  // 0xbe1f0
    void SendRecoverCharacterFail(unsigned long long, id128 const&, Character::ClientState, short);  // 0xbe2d0
    void SendBindCharacterSlotFail(unsigned long long, id128 const&, unsigned long long, short);  // 0xbe3f0
    void SendAccountInventoryNotify(unsigned long long, char, unsigned long long);  // 0xbe4f0
    void SendGetGoodsCountOk(unsigned long long, int);  // 0xbe5d0
    void SendGetGoodsCountFail(unsigned long long, short);  // 0xbe6a0
    void SendListGoodsOk(unsigned long long, Goods*, int);  // 0xbe770
    void SendListGoodsFail(unsigned long long, short);  // 0xbe980
    void SendTakeGoodsOk(unsigned long long, unsigned long long, LobbyServiceItem*, int);  // 0xbea50
    void SendTakeGoodsFail(unsigned long long, short);  // 0xbed00
    void SendListLobbyServiceItemInfoOk(unsigned long long, char, int, LobbyServiceItem*, int);  // 0xbedd0
    void SendListLobbyServiceItemInfoFail(unsigned long long, char, short);  // 0xbf080
    void SendGetLobbyServiceItemInfoOk(unsigned long long, LobbyServiceItem const&);  // 0xbf160
    void SendGetLobbyServiceItemInfoFail(unsigned long long, unsigned long long, short);  // 0xbf2e0
    void SendGetServiceEntryListFail(unsigned long long, short);  // 0xbf3c0
    void SendChangeCharacterAppearanceWithAccountInventoryItemOk(unsigned long long, id128 const&, char*, short, unsigned long long, unsigned long long);  // 0xbf490
    void SendChangeCharacterAppearanceWithAccountInventoryItemFail(unsigned long long, id128 const&, unsigned long long, unsigned long long, short);  // 0xbf5a0
    void SendChangeCharacterSexWithAccountInventoryItemOk(unsigned long long, id128 const&, char*, short, unsigned long long, unsigned long long);  // 0xbf6b0
    void SendChangeCharacterSexWithAccountInventoryItemFail(unsigned long long, id128 const&, unsigned long long, unsigned long long, short);  // 0xbf7c0
    void SendChangeCharacterRaceWithAccountInventoryItemOk(unsigned long long, id128 const&, char*, short, unsigned long long, unsigned long long);  // 0xbf8d0
    void SendChangeCharacterRaceWithAccountInventoryItemFail(unsigned long long, id128 const&, unsigned long long, unsigned long long, short);  // 0xbf9e0
    void SendRenameCharacterWithAccountInventoryItemOk(unsigned long long, id128 const&, wchar_t const*, unsigned long long, unsigned long long);  // 0xbfaf0
    void SendRenameCharacterWithAccountInventoryItemFail(unsigned long long, id128 const&, unsigned long long, unsigned long long, short);  // 0xbfc00
    void SendAddSlotWithAccountInventoryItemOk(unsigned long long, unsigned long long, unsigned long long, id128 const&);  // 0xbfd10
    void SendAddSlotWithAccountInventoryItemFail(unsigned long long, unsigned long long, unsigned long long, short);  // 0xbfe10
    void SendChangeUserNameWithAccountInventoryItemOk(unsigned long long, wchar_t const*, unsigned long long, unsigned long long, unsigned int);  // 0xbff00
    void SendChangeUserNameWithAccountInventoryItemFail(unsigned long long, unsigned long long, unsigned long long, short);  // 0xc0050
    void SendExtendJumpingCharacterCreationQuotaWithAccountInventoryItemOk(unsigned long long, unsigned long long, unsigned long long, int);  // 0xc0160
    void SendExtendJumpingCharacterCreationQuotaWithAccountInventoryItemFail(unsigned long long, unsigned long long, unsigned long long, short);  // 0xc0250
    void SendCreateInitialUserNameOk(unsigned long long, wchar_t const*);  // 0xc0340
    void SendCreateInitialUserNameFail(unsigned long long, short);  // 0xc0460
    void SendActivateGradeOk(unsigned long long, int, int, long long, long long);  // 0xc0550
    void SendActivateGradeFail(unsigned long long, int, int, short);  // 0xc0670
    void SendChangedGradeNotify(unsigned long long, int, int, bool, int, long long, long long, wchar_t const*);  // 0xc0790
    void SendChangedGradeLevelNotify(unsigned long long, int, int, int, int, int);  // 0xc0970

    bool _broadcastable;
    bool _isMobileGate;
};
static_assert(sizeof(LobbyGateChannel) == 0x28, "sizeof LobbyGateChannel");
static_assert(offsetof(LobbyGateChannel, _broadcastable) == 0x20, "LobbyGateChannel::_broadcastable");
static_assert(offsetof(LobbyGateChannel, _isMobileGate) == 0x21, "LobbyGateChannel::_isMobileGate");

class LobbyGateChannelManager : public SessionHandler
{
public:
    LobbyGateChannelManager() {}  // LIFT: PDB inline ctor. Inlined in LobbyDaemon::initNetwork (0x9d520).
    virtual ~LobbyGateChannelManager();  // 0xc0aa0
    // LIFT: PDB inline Initialize(short, short). Inlined in LobbyDaemon::initNetwork (0x9d520).
    bool Initialize(short idmin, short idmax);
    bool Add(LobbyGateChannel*);  // 0xc0b80
    void Remove(short);  // 0xc0c40
    LobbyGateChannel* Acquire(short);  // 0xc0d50
    void BroadcastAnnounceNotify(wchar_t const*);  // 0xc0e20
    // LIFT: the PDB also has Broadcast(Packet const*). Its body is folded with InfoGateChannelManager::Broadcast
    // (0x2ef40), so the lift does not declare a second copy. The callers use the InfoGate body (LobbyDaemon.cpp:188).
    virtual bool OnAccept(Session const*) const;  // 0xc0f20
    virtual bool OnConnect(Session const*, bool) const;  // 0xc0f80
    virtual void OnClose(Session const*, bool) const;  // 0xc1030
    virtual bool PacketHandler(Session const*, Packet const*) const;  // 0xc11d0

    SharedChannelList _channels;  // PDB: private
    CriticalSection _lock;  // PDB: private
};
static_assert(sizeof(LobbyGateChannelManager) == 0x48, "sizeof LobbyGateChannelManager");
static_assert(offsetof(LobbyGateChannelManager, _channels) == 0x8, "LobbyGateChannelManager::_channels");
static_assert(offsetof(LobbyGateChannelManager, _lock) == 0x20, "LobbyGateChannelManager::_lock");
