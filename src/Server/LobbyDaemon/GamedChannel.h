// GamedChannel.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once

struct CharacterInventoryItem;
class GamedChannel;
class Packet;
class Session;
union id128;

class GamedChannel
{
public:
    void SendStopPlayNotify(unsigned long long, short);  // 0x80d50
    void SendDeleteCharacterCompleteNotify(unsigned long long);  // 0x81320
    void SendCloseSessionNotify(unsigned long long);  // 0x813e0
    void SendEnterWorldFail(unsigned long long, short);  // 0x81620
    void SendLeaveWorldOk(unsigned long long, unsigned long long);  // 0x816f0
    void SendLeaveWorldFail(unsigned long long, short);  // 0x817c0
    void SendUpdateCharacterDataOk(unsigned long long);  // 0x81890
    void SendUpdateCharacterDataFail(unsigned long long, short);  // 0x81950
    void SendUpdateAccountDataOk(unsigned long long);  // 0x81a20
    void SendUpdateAccountDataFail(unsigned long long, short);  // 0x81ae0
    void SendTryRegisterGuildOk(unsigned long long, unsigned long long);  // 0x81bb0
    void SendTryRegisterGuildFail(unsigned long long, short);  // 0x81c80
    void SendTryRenameGuildOk(unsigned long long, unsigned long long, char, unsigned long long);  // 0x81d50
    void SendTryRenameGuildFail(unsigned long long, unsigned long long, char, short);  // 0x81e40
    void SendAccountInventoryNotify(unsigned long long, char, CharacterInventoryItem*, int, char, unsigned long long);  // 0x81f30
    void SendStartChargeOk(unsigned long long, wchar_t*, long, char, unsigned int, short);  // 0x821f0
    void SendStartChargeFail(unsigned long long, short);  // 0x82300
    void SendStopChargeOk(unsigned long long);  // 0x823d0
    void SendStopChargeFail(unsigned long long, short);  // 0x82490
    void SendUpdateChargeRemainTimeNotify(unsigned long long, long, short, unsigned int);  // 0x82560
    void SendApplyNewChargeItemNotify(unsigned long long, wchar_t const*, long, unsigned int, short);  // 0x82650
    void SendExtendJumpingCharacterCreationQuotaWithAccountInventoryItemOk(unsigned long long, int);  // 0x82f70
    void SendExtendJumpingCharacterCreationQuotaWithAccountInventoryItemFail(unsigned long long, short);  // 0x83060
    void SendUpgradeJumpingCharacterStateWithCreationQuotaOk(unsigned long long, char, int);  // 0x83150
    void SendUpgradeJumpingCharacterStateWithCreationQuotaFail(unsigned long long, short);  // 0x83250
    void SendUpdateJumpingCharacterStateOk(unsigned long long, char);  // 0x83340
    void SendUpdateJumpingCharacterStateFail(unsigned long long, short);  // 0x83430
    void SendSecondPasswordGetStatusOk(unsigned long long, unsigned long long, char, int, int, long long, long long, long long);  // 0x83520
    void SendSecondPasswordGetStatusFail(unsigned long long, unsigned long long, short);  // 0x83670
    void SendSecondPasswordIsVerifiedOk(unsigned long long, unsigned long long);  // 0x83770
    void SendSecondPasswordIsVerifiedFail(unsigned long long, unsigned long long, short);  // 0x83860
    void SendGetGradeListFail(unsigned long long, char, unsigned long long, short);  // 0x83b00
    void SendActivateGradeOk(unsigned long long, unsigned long long, int, int, long long, long long);  // 0x83c20
    void SendActivateGradeFail(unsigned long long, unsigned long long, int, int, short);  // 0x83d60
    void SendChangedGradeNotify(unsigned long long, int, int, int, bool, int, long long, long long, wchar_t const*);  // 0x83ea0
    void SendChangedGradeLevelNotify(unsigned long long, int, int, int, int, int, int);  // 0x84090
    void SendDepositGameMileageOk(unsigned long long, char, char, unsigned long long, unsigned long long, unsigned long long, id128 const&, unsigned long long, short, long long, int);  // 0x841a0
    void SendDepositGameMileageFail(unsigned long long, char, char, unsigned long long, unsigned long long, unsigned long long, id128 const&, short, int);  // 0x84310
    void SendAuctionBidOk(unsigned long long, id128&);  // 0x84460
    void SendAuctionBidFail(unsigned long long, id128&, short);  // 0x845f0
    void SendTakeAccountTimeBasedPlayRewardFail(unsigned long long, unsigned long long, int, char, short, long long, short, int);  // 0x84790
    void SendUpdateAccountExpOk(unsigned long long, unsigned long long);  // 0x848f0
    void SendUpdateAccountExpFail(unsigned long long, unsigned long long, short);  // 0x849c0
    void SendUpdateAccountContentQuotaOk(unsigned long long, unsigned long long);  // 0x84aa0
    void SendUpdateAccountContentQuotaFail(unsigned long long, unsigned long long, short);  // 0x84b70
    void SendUpdateAccountRecycleTimeOk(unsigned long long, unsigned long long);  // 0x84c50
    void SendUpdateAccountRecycleTimeFail(unsigned long long, unsigned long long, short);  // 0x84d20
};

class GamedChannelManager
{
public:
    virtual ~GamedChannelManager();  // 0x80300
    bool Add(GamedChannel*);  // 0x803e0
    void Remove(short);  // 0x804a0
    GamedChannel* Acquire(short);  // 0x805b0
    virtual bool OnAccept(Session const*) const;  // 0x80680
    virtual bool OnConnect(Session const*, bool) const;  // 0x806e0
    virtual void OnClose(Session const*, bool) const;  // 0x80790
    virtual bool PacketHandler(Session const*, Packet const*) const;  // 0x80980
};
