// CliSession.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "CliSession.h"
#include "LobbyMessage.h"
#include "LiftStub.h"

// 0x329d0
ServiceLocation::~ServiceLocation()
{
    LIFT_STUB(0x329d0);
}

// 0x329f0
void CliSession::deallocate_me(void*, wchar_t const*, int)
{
    LIFT_STUB(0x329f0);
}

// 0x32a40
CliSession::CliSession()
{
    LIFT_STUB(0x32a40);
}

// 0x32b60
CliSessionStopPcCafeChargeMessage::~CliSessionStopPcCafeChargeMessage()
{
    LIFT_STUB(0x32b60);
}

// 0x32bb0
TimeBasedPlayInfoList::~TimeBasedPlayInfoList()
{
    LIFT_STUB(0x32bb0);
}

// 0x32be0
void TimeBasedPlayInfoList::ValidateDurations()
{
    LIFT_STUB(0x32be0);
}

// 0x32e20
void TimeBasedPlayInfoList::SetPlayInfoFromGame(TimeBasedPlayInfoList const&)
{
    LIFT_STUB(0x32e20);
}

// 0x32ed0
bool TimeBasedPlayInfoList::Compose(FragmentPacket&) const
{
    LIFT_STUB(0x32ed0);
}

// 0x33070
bool TimeBasedPlayInfoList::Compose(RepeatPacketComposer&, Packet&) const
{
    LIFT_STUB(0x33070);
}

// 0x331e0
bool TimeBasedPlayInfoList::Decompose(RepeatPacketDecomposer&, Packet const*)
{
    LIFT_STUB(0x331e0);
}

// 0x33360
GameAccount::GameAccount()
{
    LIFT_STUB(0x33360);
}

// 0x33450
GameAccount::~GameAccount()
{
    LIFT_STUB(0x33450);
}

// 0x33490
CliSession::CliSession(unsigned long long, CliSessionTable*)
{
    LIFT_STUB(0x33490);
}

// 0x336b0
CliSession::~CliSession()
{
    LIFT_STUB(0x336b0);
}

// 0x33cc0
void CliSession::finalize()
{
    LIFT_STUB(0x33cc0);
}

// 0x33d60
bool CliSession::npLogin(id128 const&)
{
    LIFT_STUB(0x33d60);
}

// 0x33f00
bool CliSession::login(id128 const&, wchar_t const*, char, wchar_t const*)
{
    LIFT_STUB(0x33f00);
}

// 0x34750
bool CliSession::logout()
{
    LIFT_STUB(0x34750);
}

// 0x349a0
bool CliSession::loadDB()
{
    LIFT_STUB(0x349a0);
}

// 0x35730
bool CliSession::setPresence(Presence*)
{
    LIFT_STUB(0x35730);
}

// 0x35810
void CliSession::closePresence()
{
    LIFT_STUB(0x35810);
}

// 0x358e0
void CliSession::kickPresence(int)
{
    LIFT_STUB(0x358e0);
}

// 0x359c0
bool CliSession::enter(ServiceLocation*)
{
    LIFT_STUB(0x359c0);
}

// 0x35c10
void CliSession::leave()
{
    LIFT_STUB(0x35c10);
}

// 0x35cf0
Character* CliSession::getCharacter(unsigned long long)
{
    LIFT_STUB(0x35cf0);
}

// 0x35d30
void CliSession::removeCharacter(unsigned long long)
{
    LIFT_STUB(0x35d30);
}

// 0x35d90
Character* CliSession::getPlayingCharacter()
{
    LIFT_STUB(0x35d90);
}

// 0x35e20
void CliSession::setChargeKey(wchar_t const*)
{
    LIFT_STUB(0x35e20);
}

// 0x35eb0
void CliSession::completeRequestChargeStop(bool)
{
    LIFT_STUB(0x35eb0);
}

// 0x35fc0
void CliSession::cleanupCharge()
{
    LIFT_STUB(0x35fc0);
}

// 0x36240
void CliSession::HandleGameGetGradeList(GamedChannel*, unsigned long long, char, unsigned long long, int) const
{
    LIFT_STUB(0x36240);
}

// 0x36df0
bool CliSession::fetchContentBans(FragmentPacket*)
{
    LIFT_STUB(0x36df0);
}

// 0x36fa0
bool CliSession::fetchAccountContentQuotaList(FragmentPacket*)
{
    LIFT_STUB(0x36fa0);
}

// 0x371b0
bool CliSession::fetchAccountRecycleTimeList(FragmentPacket*)
{
    LIFT_STUB(0x371b0);
}

// 0x373a0
bool CliSession::addLobbyService(LobbyService*)
{
    LIFT_STUB(0x373a0);
}

// 0x37530
void CliSession::removeLobbyService(unsigned long long)
{
    LIFT_STUB(0x37530);
}

// 0x37670
LobbyService* CliSession::getLobbyServiceByType(unsigned long long, int)
{
    LIFT_STUB(0x37670);
}

// 0x376b0
LobbyService* CliSession::queryLobbyService(Character*)
{
    LIFT_STUB(0x376b0);
}

// 0x37790
bool CliSession::addRenameUserService(RenameUserService*)
{
    LIFT_STUB(0x37790);
}

// 0x37890
void CliSession::setScheduledEndTime(GameTimeScheduleNode*)
{
    LIFT_STUB(0x37890);
}

// 0x37950
void CliSession::releaseScheduledEndTime()
{
    LIFT_STUB(0x37950);
}

// 0x37af0
bool CliSession::FetchCharacterInfo(id128 const&, Packet*, PacketComposer*) const
{
    LIFT_STUB(0x37af0);
}

// 0x37c70
bool CliSession::FetchServiceEntryList(FragmentPacket*) const
{
    LIFT_STUB(0x37c70);
}

// 0x37de0
bool CliSession::UpdateBotScore(unsigned long long, int)
{
    LIFT_STUB(0x37de0);
}

// 0x37eb0
bool CliSession::BindCharacterSlot(unsigned long long, id128 const&)
{
    LIFT_STUB(0x37eb0);
}

// 0x381c0
bool CliSession::UpdateCharacterData(unsigned long long, short, char*, short)
{
    LIFT_STUB(0x381c0);
}

// 0x38380
bool CliSession::UpdateCharacterLevel(unsigned long long, short)
{
    LIFT_STUB(0x38380);
}

// 0x38500
bool CliSession::UpdateAccountData(unsigned long long, int, TimeBasedPlayInfoList&)
{
    LIFT_STUB(0x38500);
}

// 0x38670
bool CliSession::UpdateTimeBasedPlayReward(unsigned long long, int, char, short, UserPromotionReward&, long long)
{
    LIFT_STUB(0x38670);
}

// 0x392c0
bool CliSession::NotifyGoodsInventoryChangedAlongPresence(GoodsInventoryChangedNotifyParam&)
{
    LIFT_STUB(0x392c0);
}

// 0x39820
bool CliSession::ReserveStopPlay(bool, int, int)
{
    LIFT_STUB(0x39820);
}

// 0x39a70
bool CliSession::TimeoutStopPlay(StopPlayTimerEvent*)
{
    LIFT_STUB(0x39a70);
}

// 0x39be0
bool CliSession::OnChargeStopRequested(unsigned int)
{
    LIFT_STUB(0x39be0);
}

// 0x39cc0
bool CliSession::ApplyNewChargeItem(wchar_t const*, long, unsigned int, short)
{
    LIFT_STUB(0x39cc0);
}

// 0x39e50
bool CliSession::NotifyChargeRemainTime(long, short, unsigned int)
{
    LIFT_STUB(0x39e50);
}

// 0x39f70
bool CliSession::setRole(unsigned int const* const, int)
{
    LIFT_STUB(0x39f70);
}

// 0x3a000
bool CliSession::setPcCafeCode(wchar_t const*)
{
    LIFT_STUB(0x3a000);
}

// 0x3a100
void CliSession::setPcCafe(PcCafe*)
{
    LIFT_STUB(0x3a100);
}

// 0x3a190
void CliSession::onPcCafeChargeStart()
{
    LIFT_STUB(0x3a190);
}

// 0x3a2c0
void CliSession::onPcCafeChargeStop()
{
    LIFT_STUB(0x3a2c0);
}

// 0x3a3f0
AnonymousLobbyGatePresence::AnonymousLobbyGatePresence(LobbyGateChannel*, unsigned long long)
{
    LIFT_STUB(0x3a3f0);
}

// 0x3a4a0
bool AnonymousLobbyGatePresence::IsEqual(Presence const*) const
{
    LIFT_STUB(0x3a4a0);
}

// 0x3a530
bool AnonymousLobbyGatePresence::OnSet(CliSessionTable*, CliSession*)
{
    LIFT_STUB(0x3a530);
}

// 0x3a600
void AnonymousLobbyGatePresence::OnUnset(CliSessionTable*, CliSession*)
{
    LIFT_STUB(0x3a600);
}

// 0x3a650
void AnonymousLobbyGatePresence::Close(CliSession*)
{
    LIFT_STUB(0x3a650);
}

// 0x3a670
void AnonymousLobbyGatePresence::Kick(CliSession*, int)
{
    LIFT_STUB(0x3a670);
}

// 0x3a760
bool LobbyGatePresence::IsEqual(Presence const*) const
{
    LIFT_STUB(0x3a760);
}

// 0x3a7d0
bool LobbyGatePresence::OnSet(CliSessionTable*, CliSession*)
{
    LIFT_STUB(0x3a7d0);
}

// 0x3aa30
void LobbyGatePresence::OnUnset(CliSessionTable*, CliSession*)
{
    LIFT_STUB(0x3aa30);
}

// 0x3abc0
void LobbyGatePresence::Close(CliSession*)
{
    LIFT_STUB(0x3abc0);
}

// 0x3ac20
void LobbyGatePresence::Kick(CliSession*, int)
{
    LIFT_STUB(0x3ac20);
}

// 0x3adf0
bool GameWorldPresence::IsEqual(Presence const*) const
{
    LIFT_STUB(0x3adf0);
}

// 0x3ae90
bool GameWorldPresence::OnSet(CliSessionTable*, CliSession*)
{
    LIFT_STUB(0x3ae90);
}

// 0x3aff0
void GameWorldPresence::OnUnset(CliSessionTable*, CliSession*)
{
    LIFT_STUB(0x3aff0);
}

// 0x3b0c0
void GameWorldPresence::Close(CliSession*)
{
    LIFT_STUB(0x3b0c0);
}

// 0x3b120
void GameWorldPresence::Kick(CliSession*, int)
{
    LIFT_STUB(0x3b120);
}

// 0x3b360
GameServiceLocation::~GameServiceLocation()
{
    LIFT_STUB(0x3b360);
}

// 0x3b3d0
void GameServiceLocation::OnEnter(CliSession*)
{
    LIFT_STUB(0x3b3d0);
}

// 0x3b540
void GameServiceLocation::OnLeave(CliSession*)
{
    LIFT_STUB(0x3b540);
}

// 0x3b6f0
bool GameServiceLocation::Enter(CliSession*)
{
    LIFT_STUB(0x3b6f0);
}

// 0x3b9a0
bool GameServiceLocation::Leave(CliSession*)
{
    LIFT_STUB(0x3b9a0);
}

// 0x3bb60
bool GameServiceLocation::ReserveStopPlay(CliSession*, StopPlayTimerEvent*)
{
    LIFT_STUB(0x3bb60);
}

// 0x3bc80
bool GameServiceLocation::TimeoutStopPlay(CliSession*, StopPlayTimerEvent*)
{
    LIFT_STUB(0x3bc80);
}

// 0x3bda0
void GameServiceLocation::NotifyStopPlay(CliSession*, int)
{
    LIFT_STUB(0x3bda0);
}
