// LobbyDB.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "LobbyDB.h"
#include "LiftStub.h"

// 0x9fdb0
AutoDbTran::~AutoDbTran()
{
    LIFT_STUB(0x9fdb0);
}

// 0xa03e0
bool LobbyDB::LoadGameAccountTimeBasedPlayInfo(int&, id128 const&, TimeBasedPlayInfoList&)
{
    LIFT_STUB(0xa03e0);
}

// 0xa0a40
bool LobbyDB::UpdateGameAccountTimeBasedPlayInfo(int&, id128 const&, TimeBasedPlayInfoList const&)
{
    LIFT_STUB(0xa0a40);
}

// 0xa0eb0
bool LobbyDB::RegisterGameAccount(int&, id128 const&, wchar_t const*, int, char, unsigned long)
{
    LIFT_STUB(0xa0eb0);
}

// 0xa12a0
bool LobbyDB::UpdateLastLogin(int&, id128 const&, unsigned long)
{
    LIFT_STUB(0xa12a0);
}

// 0xa1580
bool LobbyDB::UpdateLastLogout(int&, id128 const&, int)
{
    LIFT_STUB(0xa1580);
}

// 0xa37e0
bool LobbyDB::CheckValidityOfCharacterName(int&, wchar_t const*, int)
{
    LIFT_STUB(0xa37e0);
}

// 0xa39b0
bool LobbyDB::TryCharacterCreation(int&, id128 const&, id128 const&, short, wchar_t const*, int, char, unsigned long long*)
{
    LIFT_STUB(0xa39b0);
}

// 0xa3da0
bool LobbyDB::FinishCharacterCreation(int&, unsigned long long, short, short, char, bool, char const*, int)
{
    LIFT_STUB(0xa3da0);
}

// 0xa4150
bool LobbyDB::CancelCharacterCreation(int&, unsigned long long)
{
    LIFT_STUB(0xa4150);
}

// 0xa4320
bool LobbyDB::TryCharacterDeletion(int&, unsigned long long)
{
    LIFT_STUB(0xa4320);
}

// 0xa44f0
bool LobbyDB::FinishCharacterDeletion(int&, unsigned long long, long, long long*)
{
    LIFT_STUB(0xa44f0);
}

// 0xa47c0
bool LobbyDB::CancelCharacterDeletion(int&, unsigned long long)
{
    LIFT_STUB(0xa47c0);
}

// 0xa4990
bool LobbyDB::TryCharacterRestoration(int&, unsigned long long)
{
    LIFT_STUB(0xa4990);
}

// 0xa4b60
bool LobbyDB::FinishCharacterRestoration(int&, unsigned long long)
{
    LIFT_STUB(0xa4b60);
}

// 0xa5220
bool LobbyDB::ExpireCharacterDeletionWaiting(int&, unsigned long long)
{
    LIFT_STUB(0xa5220);
}

// 0xa53f0
bool LobbyDB::UpdateLastPlayStart(int&, unsigned long long, unsigned long)
{
    LIFT_STUB(0xa53f0);
}

// 0xa5690
bool LobbyDB::UpdateLastPlayEnd(int&, unsigned long long)
{
    LIFT_STUB(0xa5690);
}

// 0xa58b0
bool LobbyDB::UpdateCharacterData(int&, unsigned long long, short, short, char*, int)
{
    LIFT_STUB(0xa58b0);
}

// 0xa5ca0
bool LobbyDB::UpdateCharacterLevel(int&, unsigned long long, short)
{
    LIFT_STUB(0xa5ca0);
}

// 0xa5f80
bool LobbyDB::TryGuildRegistration(int&, short, short, char, wchar_t const*, int, unsigned long long*)
{
    LIFT_STUB(0xa5f80);
}

// 0xa6310
bool LobbyDB::FinishGuildRegistration(int&, unsigned long long)
{
    LIFT_STUB(0xa6310);
}

// 0xa64e0
bool LobbyDB::CancelGuildRegistration(int&, unsigned long long)
{
    LIFT_STUB(0xa64e0);
}

// 0xa66b0
bool LobbyDB::DeleteGuild(int&, unsigned long long, long)
{
    LIFT_STUB(0xa66b0);
}

// 0xa68f0
bool LobbyDB::TryRenameGuild(int&, unsigned long long, int, wchar_t const*, int, long, unsigned long long*)
{
    LIFT_STUB(0xa68f0);
}

// 0xa6c60
bool LobbyDB::FinishRenameGuild(int&, unsigned long long, unsigned long long)
{
    LIFT_STUB(0xa6c60);
}

// 0xa6ec0
bool LobbyDB::CancelRenameGuild(int&, unsigned long long)
{
    LIFT_STUB(0xa6ec0);
}

// 0xa7570
bool LobbyDB::BindCharacterSlot(int&, unsigned long long, id128 const&)
{
    LIFT_STUB(0xa7570);
}

// 0xa77e0
bool LobbyDB::UpdateJumpingCharacterStateComplete(int&, unsigned long long, bool)
{
    LIFT_STUB(0xa77e0);
}

// 0xa95f0
bool LobbyDB::LoadRandomStoreInitializationSchedule(int&, RandomStoreInitializationSchedule*)
{
    LIFT_STUB(0xa95f0);
}

// 0xaa1d0
bool LobbyDB::LoadCharacterCosmesisService(int&, unsigned long long, unsigned long long*)
{
    LIFT_STUB(0xaa1d0);
}

// 0xaa670
bool LobbyDB::TryCharacterCosmesisService(int&, id128 const&, unsigned long long, unsigned long long, unsigned int, char*, int, unsigned long long*)
{
    LIFT_STUB(0xaa670);
}

// 0xaadb0
bool LobbyDB::UpdateLobbyServiceStateToItemConsumptionTryState_CharacterCosmesisService(int&, unsigned long long, id128 const&)
{
    LIFT_STUB(0xaadb0);
}

// 0xab070
bool LobbyDB::UpdateLobbyServiceStateToTaskDoneState_CharacterCosmesisService(int&, unsigned long long, id128 const&)
{
    LIFT_STUB(0xab070);
}

// 0xab330
bool LobbyDB::UpdateLobbyServiceStateToItemConsumptionFinishState_CharacterCosmesisService(int&, unsigned long long, id128 const&)
{
    LIFT_STUB(0xab330);
}

// 0xab5f0
bool LobbyDB::FinishCharacterCosmesisService(int&, unsigned long long, id128 const&)
{
    LIFT_STUB(0xab5f0);
}

// 0xab8b0
bool LobbyDB::LoadChangeCharacterSexService(int&, unsigned long long, unsigned long long*)
{
    LIFT_STUB(0xab8b0);
}

// 0xabdc0
bool LobbyDB::TryChangeCharacterSexService(int&, id128 const&, unsigned long long, unsigned long long, unsigned int, char, char*, int, unsigned long long*)
{
    LIFT_STUB(0xabdc0);
}

// 0xac5c0
bool LobbyDB::UpdateLobbyServiceStateToItemConsumptionTryState_ChangeCharacterSexService(int&, unsigned long long, id128 const&)
{
    LIFT_STUB(0xac5c0);
}

// 0xac880
bool LobbyDB::UpdateLobbyServiceStateToTaskDoneState_ChangeCharacterSexService(int&, unsigned long long, id128 const&)
{
    LIFT_STUB(0xac880);
}

// 0xacb40
bool LobbyDB::UpdateLobbyServiceStateToItemConsumptionFinishState_ChangeCharacterSexService(int&, unsigned long long, id128 const&)
{
    LIFT_STUB(0xacb40);
}

// 0xace00
bool LobbyDB::FinishChangeCharacterSexService(int&, unsigned long long, id128 const&)
{
    LIFT_STUB(0xace00);
}

// 0xad0c0
bool LobbyDB::LoadChangeCharacterRaceService(int&, unsigned long long, unsigned long long*)
{
    LIFT_STUB(0xad0c0);
}

// 0xad650
bool LobbyDB::TryChangeCharacterRaceService(int&, id128 const&, unsigned long long, unsigned long long, unsigned int, char, char, char*, int, unsigned long long*)
{
    LIFT_STUB(0xad650);
}

// 0xadf10
bool LobbyDB::UpdateLobbyServiceStateToItemConsumptionTryState_ChangeCharacterRaceService(int&, unsigned long long, id128 const&)
{
    LIFT_STUB(0xadf10);
}

// 0xae1d0
bool LobbyDB::UpdateLobbyServiceStateToTaskDoneState_ChangeCharacterRaceService(int&, unsigned long long, id128 const&)
{
    LIFT_STUB(0xae1d0);
}

// 0xae490
bool LobbyDB::UpdateLobbyServiceStateToItemConsumptionFinishState_ChangeCharacterRaceService(int&, unsigned long long, id128 const&)
{
    LIFT_STUB(0xae490);
}

// 0xae750
bool LobbyDB::FinishChangeCharacterRaceService(int&, unsigned long long, id128 const&)
{
    LIFT_STUB(0xae750);
}

// 0xaea10
bool LobbyDB::LoadRenameCharacterService(int&, unsigned long long, unsigned long long*, wchar_t*, int, wchar_t*, int)
{
    LIFT_STUB(0xaea10);
}

// 0xaee70
bool LobbyDB::TryCharacterRenameService(int&, id128 const&, unsigned long long, unsigned long long, unsigned int, wchar_t*, int, int, unsigned long long*)
{
    LIFT_STUB(0xaee70);
}

// 0xaf630
bool LobbyDB::UpdateLobbyServiceStateToItemConsumptionTryState_CharacterRenameService(int&, unsigned long long, id128 const&)
{
    LIFT_STUB(0xaf630);
}

// 0xafb60
bool LobbyDB::UpdateLobbyServiceStateToTaskDoneState_CharacterRenameService(int&, unsigned long long, id128 const&)
{
    LIFT_STUB(0xafb60);
}

// 0xb0090
bool LobbyDB::UpdateLobbyServiceStateToItemConsumptionFinishState_CharacterRenameService(int&, unsigned long long, id128 const&)
{
    LIFT_STUB(0xb0090);
}

// 0xb05c0
bool LobbyDB::FinishCharacterRenameService(int&, unsigned long long, id128 const&)
{
    LIFT_STUB(0xb05c0);
}

// 0xb0880
bool LobbyDB::LoadSlotAdditionService(int&, unsigned long long, id128*)
{
    LIFT_STUB(0xb0880);
}

// 0xb0c30
bool LobbyDB::TrySlotAdditionService(int&, id128 const&, unsigned long long, unsigned int, unsigned long long*)
{
    LIFT_STUB(0xb0c30);
}

// 0xb11d0
bool LobbyDB::UpdateLobbyServiceStateToItemConsumptionTryState_SlotAdditionService(int&, unsigned long long, id128 const&)
{
    LIFT_STUB(0xb11d0);
}

// 0xb1700
bool LobbyDB::UpdateLobbyServiceStateToTaskDoneState_SlotAdditionService(int&, unsigned long long, id128 const&, id128 const&)
{
    LIFT_STUB(0xb1700);
}

// 0xb1f60
bool LobbyDB::UpdateLobbyServiceStateToItemConsumptionFinishState_SlotAdditionService(int&, unsigned long long, id128 const&)
{
    LIFT_STUB(0xb1f60);
}

// 0xb2490
bool LobbyDB::FinishSlotAdditionService(int&, unsigned long long, id128 const&)
{
    LIFT_STUB(0xb2490);
}

// 0xb2750
bool LobbyDB::WriteUserRenameServiceLog(int&, id128 const&, unsigned long long, unsigned int, wchar_t*, int, wchar_t*, int)
{
    LIFT_STUB(0xb2750);
}

// 0xb2e40
bool LobbyDB::TryExtendJumpingCharacterCreationQuota(int&, id128 const&, unsigned long long, unsigned int, unsigned long long*)
{
    LIFT_STUB(0xb2e40);
}

// 0xb33e0
bool LobbyDB::UpdateLobbyServiceStateToItemConsumptionTryState_ExtendJumpingCharacterCreationQuota(int&, unsigned long long, id128 const&)
{
    LIFT_STUB(0xb33e0);
}

// 0xb3910
bool LobbyDB::UpdateLobbyServiceStateToTaskDoneState_ExtendJumpingCharacterCreationQuota(int&, unsigned long long, id128 const&)
{
    LIFT_STUB(0xb3910);
}

// 0xb3e40
bool LobbyDB::UpdateLobbyServiceStateToItemConsumptionFinishState_ExtendJumpingCharacterCreationQuota(int&, unsigned long long, id128 const&)
{
    LIFT_STUB(0xb3e40);
}

// 0xb4370
bool LobbyDB::FinishExtendJumpingCharacterCreationQuota(int&, unsigned long long, id128 const&)
{
    LIFT_STUB(0xb4370);
}

// 0xb4630
bool LobbyDB::TryAuctionEscrow(int&, id128 const&, id128 const&, short, unsigned long long, long long, unsigned long long&)
{
    LIFT_STUB(0xb4630);
}

// 0xb4e70
bool LobbyDB::CancelAuctionEscrow(int&, unsigned long long, unsigned long long)
{
    LIFT_STUB(0xb4e70);
}

// 0xb5140
bool LobbyDB::FinishAuctionEscrow(int&, unsigned long long, unsigned long long)
{
    LIFT_STUB(0xb5140);
}

// 0xb5a30
bool LobbyDB::FinishAuctionEscrowRollback(int&, unsigned long long, unsigned long long, unsigned long long)
{
    LIFT_STUB(0xb5a30);
}

// 0xb5d50
bool LobbyDB::TryAuctionResultDelivery(int&, wchar_t const*, int, id128 const&, id128 const&, short, unsigned long long, unsigned long long&, wchar_t*, int, unsigned long long&)
{
    LIFT_STUB(0xb5d50);
}

// 0xb67f0
bool LobbyDB::FinishAuctionResultDelivery(int&, unsigned long long, unsigned long long)
{
    LIFT_STUB(0xb67f0);
}

// 0xb6ad0
bool LobbyDB::LoadMileage(int&, MileageInfo**&, int&)
{
    LIFT_STUB(0xb6ad0);
}

// 0xb77b0
bool LobbyDB::LoadMileagePolicy(int&, int, MileagePolicy&, MileagePolicyCondition**&, int&)
{
    LIFT_STUB(0xb77b0);
}

// 0xb80a0
bool LobbyDB::LoadMileageFeverTime(int&, int, long long, MileageFeverTimeInfo**&, int&)
{
    LIFT_STUB(0xb80a0);
}

// 0xb8db0
bool LobbyDB::LoadMileageAccumulatedTimePerDay(int&, id128 const&, int* const, int, MileageLimitInfo**&, int&)
{
    LIFT_STUB(0xb8db0);
}

// 0xb9630
bool LobbyDB::LoadRetryMileageDeposit(int&, int, unsigned long long, unsigned long long*, unsigned long long*, MileageDepositInfo**&, int&)
{
    LIFT_STUB(0xb9630);
}

// 0xba390
bool LobbyDB::RetrieveMileageDeposit(int&, unsigned long long, MileageDepositInfo&)
{
    LIFT_STUB(0xba390);
}

// 0xbaac0
bool LobbyDB::TryMileageDepost(int&, id128 const&, int, long long, long long, long long, long long*, short*, unsigned long long&)
{
    LIFT_STUB(0xbaac0);
}

// 0xbb3b0
bool LobbyDB::FinishMileageDeposit(int&, unsigned long long, bool)
{
    LIFT_STUB(0xbb3b0);
}
