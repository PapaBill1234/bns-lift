// GamedChannel.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "GamedChannel.h"
#include "LiftStub.h"

// 0x80300
GamedChannelManager::~GamedChannelManager()
{
    LIFT_STUB(0x80300);
}

// 0x803e0
bool GamedChannelManager::Add(GamedChannel*)
{
    LIFT_STUB(0x803e0);
}

// 0x804a0
void GamedChannelManager::Remove(short)
{
    LIFT_STUB(0x804a0);
}

// 0x805b0
GamedChannel* GamedChannelManager::Acquire(short)
{
    LIFT_STUB(0x805b0);
}

// 0x80680
bool GamedChannelManager::OnAccept(Session const*) const
{
    LIFT_STUB(0x80680);
}

// 0x806e0
bool GamedChannelManager::OnConnect(Session const*, bool) const
{
    LIFT_STUB(0x806e0);
}

// 0x80790
void GamedChannelManager::OnClose(Session const*, bool) const
{
    LIFT_STUB(0x80790);
}

// 0x80980
bool GamedChannelManager::PacketHandler(Session const*, Packet const*) const
{
    LIFT_STUB(0x80980);
}

// 0x80d50
void GamedChannel::SendStopPlayNotify(unsigned long long, short)
{
    LIFT_STUB(0x80d50);
}

// 0x81320
void GamedChannel::SendDeleteCharacterCompleteNotify(unsigned long long)
{
    LIFT_STUB(0x81320);
}

// 0x813e0
void GamedChannel::SendCloseSessionNotify(unsigned long long)
{
    LIFT_STUB(0x813e0);
}

// 0x81620
void GamedChannel::SendEnterWorldFail(unsigned long long, short)
{
    LIFT_STUB(0x81620);
}

// 0x816f0
void GamedChannel::SendLeaveWorldOk(unsigned long long, unsigned long long)
{
    LIFT_STUB(0x816f0);
}

// 0x817c0
void GamedChannel::SendLeaveWorldFail(unsigned long long, short)
{
    LIFT_STUB(0x817c0);
}

// 0x81890
void GamedChannel::SendUpdateCharacterDataOk(unsigned long long)
{
    LIFT_STUB(0x81890);
}

// 0x81950
void GamedChannel::SendUpdateCharacterDataFail(unsigned long long, short)
{
    LIFT_STUB(0x81950);
}

// 0x81a20
void GamedChannel::SendUpdateAccountDataOk(unsigned long long)
{
    LIFT_STUB(0x81a20);
}

// 0x81ae0
void GamedChannel::SendUpdateAccountDataFail(unsigned long long, short)
{
    LIFT_STUB(0x81ae0);
}

// 0x81bb0
void GamedChannel::SendTryRegisterGuildOk(unsigned long long, unsigned long long)
{
    LIFT_STUB(0x81bb0);
}

// 0x81c80
void GamedChannel::SendTryRegisterGuildFail(unsigned long long, short)
{
    LIFT_STUB(0x81c80);
}

// 0x81d50
void GamedChannel::SendTryRenameGuildOk(unsigned long long, unsigned long long, char, unsigned long long)
{
    LIFT_STUB(0x81d50);
}

// 0x81e40
void GamedChannel::SendTryRenameGuildFail(unsigned long long, unsigned long long, char, short)
{
    LIFT_STUB(0x81e40);
}

// 0x81f30
void GamedChannel::SendAccountInventoryNotify(unsigned long long, char, CharacterInventoryItem*, int, char, unsigned long long)
{
    LIFT_STUB(0x81f30);
}

// 0x821f0
void GamedChannel::SendStartChargeOk(unsigned long long, wchar_t*, long, char, unsigned int, short)
{
    LIFT_STUB(0x821f0);
}

// 0x82300
void GamedChannel::SendStartChargeFail(unsigned long long, short)
{
    LIFT_STUB(0x82300);
}

// 0x823d0
void GamedChannel::SendStopChargeOk(unsigned long long)
{
    LIFT_STUB(0x823d0);
}

// 0x82490
void GamedChannel::SendStopChargeFail(unsigned long long, short)
{
    LIFT_STUB(0x82490);
}

// 0x82560
void GamedChannel::SendUpdateChargeRemainTimeNotify(unsigned long long, long, short, unsigned int)
{
    LIFT_STUB(0x82560);
}

// 0x82650
void GamedChannel::SendApplyNewChargeItemNotify(unsigned long long, wchar_t const*, long, unsigned int, short)
{
    LIFT_STUB(0x82650);
}

// 0x82f70
void GamedChannel::SendExtendJumpingCharacterCreationQuotaWithAccountInventoryItemOk(unsigned long long, int)
{
    LIFT_STUB(0x82f70);
}

// 0x83060
void GamedChannel::SendExtendJumpingCharacterCreationQuotaWithAccountInventoryItemFail(unsigned long long, short)
{
    LIFT_STUB(0x83060);
}

// 0x83150
void GamedChannel::SendUpgradeJumpingCharacterStateWithCreationQuotaOk(unsigned long long, char, int)
{
    LIFT_STUB(0x83150);
}

// 0x83250
void GamedChannel::SendUpgradeJumpingCharacterStateWithCreationQuotaFail(unsigned long long, short)
{
    LIFT_STUB(0x83250);
}

// 0x83340
void GamedChannel::SendUpdateJumpingCharacterStateOk(unsigned long long, char)
{
    LIFT_STUB(0x83340);
}

// 0x83430
void GamedChannel::SendUpdateJumpingCharacterStateFail(unsigned long long, short)
{
    LIFT_STUB(0x83430);
}

// 0x83520
void GamedChannel::SendSecondPasswordGetStatusOk(unsigned long long, unsigned long long, char, int, int, long long, long long, long long)
{
    LIFT_STUB(0x83520);
}

// 0x83670
void GamedChannel::SendSecondPasswordGetStatusFail(unsigned long long, unsigned long long, short)
{
    LIFT_STUB(0x83670);
}

// 0x83770
void GamedChannel::SendSecondPasswordIsVerifiedOk(unsigned long long, unsigned long long)
{
    LIFT_STUB(0x83770);
}

// 0x83860
void GamedChannel::SendSecondPasswordIsVerifiedFail(unsigned long long, unsigned long long, short)
{
    LIFT_STUB(0x83860);
}

// 0x83b00
void GamedChannel::SendGetGradeListFail(unsigned long long, char, unsigned long long, short)
{
    LIFT_STUB(0x83b00);
}

// 0x83c20
void GamedChannel::SendActivateGradeOk(unsigned long long, unsigned long long, int, int, long long, long long)
{
    LIFT_STUB(0x83c20);
}

// 0x83d60
void GamedChannel::SendActivateGradeFail(unsigned long long, unsigned long long, int, int, short)
{
    LIFT_STUB(0x83d60);
}

// 0x83ea0
void GamedChannel::SendChangedGradeNotify(unsigned long long, int, int, int, bool, int, long long, long long, wchar_t const*)
{
    LIFT_STUB(0x83ea0);
}

// 0x84090
void GamedChannel::SendChangedGradeLevelNotify(unsigned long long, int, int, int, int, int, int)
{
    LIFT_STUB(0x84090);
}

// 0x841a0
void GamedChannel::SendDepositGameMileageOk(unsigned long long, char, char, unsigned long long, unsigned long long, unsigned long long, id128 const&, unsigned long long, short, long long, int)
{
    LIFT_STUB(0x841a0);
}

// 0x84310
void GamedChannel::SendDepositGameMileageFail(unsigned long long, char, char, unsigned long long, unsigned long long, unsigned long long, id128 const&, short, int)
{
    LIFT_STUB(0x84310);
}

// 0x84460
void GamedChannel::SendAuctionBidOk(unsigned long long, id128&)
{
    LIFT_STUB(0x84460);
}

// 0x845f0
void GamedChannel::SendAuctionBidFail(unsigned long long, id128&, short)
{
    LIFT_STUB(0x845f0);
}

// 0x84790
void GamedChannel::SendTakeAccountTimeBasedPlayRewardFail(unsigned long long, unsigned long long, int, char, short, long long, short, int)
{
    LIFT_STUB(0x84790);
}

// 0x848f0
void GamedChannel::SendUpdateAccountExpOk(unsigned long long, unsigned long long)
{
    LIFT_STUB(0x848f0);
}

// 0x849c0
void GamedChannel::SendUpdateAccountExpFail(unsigned long long, unsigned long long, short)
{
    LIFT_STUB(0x849c0);
}

// 0x84aa0
void GamedChannel::SendUpdateAccountContentQuotaOk(unsigned long long, unsigned long long)
{
    LIFT_STUB(0x84aa0);
}

// 0x84b70
void GamedChannel::SendUpdateAccountContentQuotaFail(unsigned long long, unsigned long long, short)
{
    LIFT_STUB(0x84b70);
}

// 0x84c50
void GamedChannel::SendUpdateAccountRecycleTimeOk(unsigned long long, unsigned long long)
{
    LIFT_STUB(0x84c50);
}

// 0x84d20
void GamedChannel::SendUpdateAccountRecycleTimeFail(unsigned long long, unsigned long long, short)
{
    LIFT_STUB(0x84d20);
}
