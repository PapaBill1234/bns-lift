// LobbyDB.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once

#include "Character.h"
#include "CliSession.h"
#include "Db.h"
#include "GameWorld.h"

struct MileageDepositInfo;
struct MileageFeverTimeInfo;
struct MileageInfo;
struct MileageLimitInfo;
struct MileagePolicy;
struct MileagePolicyCondition;
class RandomStoreInitializationSchedule;
class TimeBasedPlayInfoList;
union id128;

// RAII holder of a DbTransaction. The PDB lists 3 constructors and the DbTransaction wrappers (Get, Alloc, Release,
// BindCol, Execute, Prepare, BindParam, BindBinaryParam, Fetch, MoreResults). The compiler inlines all of them.
// LIFT: the PDB members are private. The LobbyDB functions read Tran directly, as in the other servers.
class AutoDbTran
{
public:
    // LIFT: inlined ctor. Db::AllocTransaction ignores the dbId (folded to 1).
    explicit AutoDbTran(unsigned int dbId) : Tran(Db::AllocTransaction(dbId)), TimeoutSec(10) {}
    ~AutoDbTran();  // 0x9fdb0

    DbTransaction* Tran;
    int TimeoutSec;
};
static_assert(sizeof(AutoDbTran) == 0x10, "sizeof AutoDbTran");

class LobbyDB
{
public:
    static bool LoadGameAccount(int&, id128 const&, bool&, GameAccount::DB&);  // 0x9fe00
    static bool LoadGameAccountTimeBasedPlayInfo(int&, id128 const&, TimeBasedPlayInfoList&);  // 0xa03e0
    static bool UpdateGameAccountTimeBasedPlayInfo(int&, id128 const&, TimeBasedPlayInfoList const&);  // 0xa0a40
    static bool RegisterGameAccount(int&, id128 const&, wchar_t const*, int, char, unsigned long);  // 0xa0eb0
    static bool UpdateLastLogin(int&, id128 const&, unsigned long);  // 0xa12a0
    static bool UpdateLastLogout(int&, id128 const&, int);  // 0xa1580
    static bool LoadCharacterList(int&, id128 const&, Character::DB**&, int&);  // 0xa17f0
    static bool LoadGameWorldCluster(int&, GameWorldCluster::DB**&, int&);  // 0xa24c0
    static bool LoadGameWorld(int&, GameWorld::DB**&, int&);  // 0xa2dd0
    static bool CheckValidityOfCharacterName(int&, wchar_t const*, int);  // 0xa37e0
    static bool TryCharacterCreation(int&, id128 const&, id128 const&, short, wchar_t const*, int, char, unsigned long long*);  // 0xa39b0
    static bool FinishCharacterCreation(int&, unsigned long long, short, short, char, bool, char const*, int);  // 0xa3da0
    static bool CancelCharacterCreation(int&, unsigned long long);  // 0xa4150
    static bool TryCharacterDeletion(int&, unsigned long long);  // 0xa4320
    static bool FinishCharacterDeletion(int&, unsigned long long, long, long long*);  // 0xa44f0
    static bool CancelCharacterDeletion(int&, unsigned long long);  // 0xa47c0
    static bool TryCharacterRestoration(int&, unsigned long long);  // 0xa4990
    static bool FinishCharacterRestoration(int&, unsigned long long);  // 0xa4b60
    static bool ExpireCharacterDeletionWaiting(int&, unsigned long long);  // 0xa5220
    static bool UpdateLastPlayStart(int&, unsigned long long, unsigned long);  // 0xa53f0
    static bool UpdateLastPlayEnd(int&, unsigned long long);  // 0xa5690
    static bool UpdateCharacterData(int&, unsigned long long, short, short, char*, int);  // 0xa58b0
    static bool UpdateCharacterLevel(int&, unsigned long long, short);  // 0xa5ca0
    static bool TryGuildRegistration(int&, short, short, char, wchar_t const*, int, unsigned long long*);  // 0xa5f80
    static bool FinishGuildRegistration(int&, unsigned long long);  // 0xa6310
    static bool CancelGuildRegistration(int&, unsigned long long);  // 0xa64e0
    static bool DeleteGuild(int&, unsigned long long, long);  // 0xa66b0
    static bool TryRenameGuild(int&, unsigned long long, int, wchar_t const*, int, long, unsigned long long*);  // 0xa68f0
    static bool FinishRenameGuild(int&, unsigned long long, unsigned long long);  // 0xa6c60
    static bool CancelRenameGuild(int&, unsigned long long);  // 0xa6ec0
    static bool BindCharacterSlot(int&, unsigned long long, id128 const&);  // 0xa7570
    static bool UpdateJumpingCharacterStateComplete(int&, unsigned long long, bool);  // 0xa77e0
    static bool LoadRandomStoreInitializationSchedule(int&, RandomStoreInitializationSchedule*);  // 0xa95f0
    static bool LoadCharacterCosmesisService(int&, unsigned long long, unsigned long long*);  // 0xaa1d0
    static bool TryCharacterCosmesisService(int&, id128 const&, unsigned long long, unsigned long long, unsigned int, char*, int, unsigned long long*);  // 0xaa670
    static bool UpdateLobbyServiceStateToItemConsumptionTryState_CharacterCosmesisService(int&, unsigned long long, id128 const&);  // 0xaadb0
    static bool UpdateLobbyServiceStateToTaskDoneState_CharacterCosmesisService(int&, unsigned long long, id128 const&);  // 0xab070
    static bool UpdateLobbyServiceStateToItemConsumptionFinishState_CharacterCosmesisService(int&, unsigned long long, id128 const&);  // 0xab330
    static bool FinishCharacterCosmesisService(int&, unsigned long long, id128 const&);  // 0xab5f0
    static bool LoadChangeCharacterSexService(int&, unsigned long long, unsigned long long*);  // 0xab8b0
    static bool TryChangeCharacterSexService(int&, id128 const&, unsigned long long, unsigned long long, unsigned int, char, char*, int, unsigned long long*);  // 0xabdc0
    static bool UpdateLobbyServiceStateToItemConsumptionTryState_ChangeCharacterSexService(int&, unsigned long long, id128 const&);  // 0xac5c0
    static bool UpdateLobbyServiceStateToTaskDoneState_ChangeCharacterSexService(int&, unsigned long long, id128 const&);  // 0xac880
    static bool UpdateLobbyServiceStateToItemConsumptionFinishState_ChangeCharacterSexService(int&, unsigned long long, id128 const&);  // 0xacb40
    static bool FinishChangeCharacterSexService(int&, unsigned long long, id128 const&);  // 0xace00
    static bool LoadChangeCharacterRaceService(int&, unsigned long long, unsigned long long*);  // 0xad0c0
    static bool TryChangeCharacterRaceService(int&, id128 const&, unsigned long long, unsigned long long, unsigned int, char, char, char*, int, unsigned long long*);  // 0xad650
    static bool UpdateLobbyServiceStateToItemConsumptionTryState_ChangeCharacterRaceService(int&, unsigned long long, id128 const&);  // 0xadf10
    static bool UpdateLobbyServiceStateToTaskDoneState_ChangeCharacterRaceService(int&, unsigned long long, id128 const&);  // 0xae1d0
    static bool UpdateLobbyServiceStateToItemConsumptionFinishState_ChangeCharacterRaceService(int&, unsigned long long, id128 const&);  // 0xae490
    static bool FinishChangeCharacterRaceService(int&, unsigned long long, id128 const&);  // 0xae750
    static bool LoadRenameCharacterService(int&, unsigned long long, unsigned long long*, wchar_t*, int, wchar_t*, int);  // 0xaea10
    static bool TryCharacterRenameService(int&, id128 const&, unsigned long long, unsigned long long, unsigned int, wchar_t*, int, int, unsigned long long*);  // 0xaee70
    static bool UpdateLobbyServiceStateToItemConsumptionTryState_CharacterRenameService(int&, unsigned long long, id128 const&);  // 0xaf630
    static bool UpdateLobbyServiceStateToTaskDoneState_CharacterRenameService(int&, unsigned long long, id128 const&);  // 0xafb60
    static bool UpdateLobbyServiceStateToItemConsumptionFinishState_CharacterRenameService(int&, unsigned long long, id128 const&);  // 0xb0090
    static bool FinishCharacterRenameService(int&, unsigned long long, id128 const&);  // 0xb05c0
    static bool LoadSlotAdditionService(int&, unsigned long long, id128*);  // 0xb0880
    static bool TrySlotAdditionService(int&, id128 const&, unsigned long long, unsigned int, unsigned long long*);  // 0xb0c30
    static bool UpdateLobbyServiceStateToItemConsumptionTryState_SlotAdditionService(int&, unsigned long long, id128 const&);  // 0xb11d0
    static bool UpdateLobbyServiceStateToTaskDoneState_SlotAdditionService(int&, unsigned long long, id128 const&, id128 const&);  // 0xb1700
    static bool UpdateLobbyServiceStateToItemConsumptionFinishState_SlotAdditionService(int&, unsigned long long, id128 const&);  // 0xb1f60
    static bool FinishSlotAdditionService(int&, unsigned long long, id128 const&);  // 0xb2490
    static bool WriteUserRenameServiceLog(int&, id128 const&, unsigned long long, unsigned int, wchar_t*, int, wchar_t*, int);  // 0xb2750
    static bool TryExtendJumpingCharacterCreationQuota(int&, id128 const&, unsigned long long, unsigned int, unsigned long long*);  // 0xb2e40
    static bool UpdateLobbyServiceStateToItemConsumptionTryState_ExtendJumpingCharacterCreationQuota(int&, unsigned long long, id128 const&);  // 0xb33e0
    static bool UpdateLobbyServiceStateToTaskDoneState_ExtendJumpingCharacterCreationQuota(int&, unsigned long long, id128 const&);  // 0xb3910
    static bool UpdateLobbyServiceStateToItemConsumptionFinishState_ExtendJumpingCharacterCreationQuota(int&, unsigned long long, id128 const&);  // 0xb3e40
    static bool FinishExtendJumpingCharacterCreationQuota(int&, unsigned long long, id128 const&);  // 0xb4370
    struct TryAuctionEscrowRollbackOutParam;

    static bool TryAuctionEscrow(int&, id128 const&, id128 const&, short, unsigned long long, long long, unsigned long long&);  // 0xb4630
    static bool CancelAuctionEscrow(int&, unsigned long long, unsigned long long);  // 0xb4e70
    static bool FinishAuctionEscrow(int&, unsigned long long, unsigned long long);  // 0xb5140
    static bool FinishAuctionEscrowRollback(int&, unsigned long long, unsigned long long, unsigned long long);  // 0xb5a30
    static bool TryAuctionResultDelivery(int&, wchar_t const*, int, id128 const&, id128 const&, short, unsigned long long, unsigned long long&, wchar_t*, int, unsigned long long&);  // 0xb5d50
    static bool FinishAuctionResultDelivery(int&, unsigned long long, unsigned long long);  // 0xb67f0
    static bool LoadMileage(int&, MileageInfo**&, int&);  // 0xb6ad0
    static bool LoadMileagePolicy(int&, int, MileagePolicy&, MileagePolicyCondition**&, int&);  // 0xb77b0
    static bool LoadMileageFeverTime(int&, int, long long, MileageFeverTimeInfo**&, int&);  // 0xb80a0
    static bool LoadMileageAccumulatedTimePerDay(int&, id128 const&, int* const, int, MileageLimitInfo**&, int&);  // 0xb8db0
    static bool LoadRetryMileageDeposit(int&, int, unsigned long long, unsigned long long*, unsigned long long*, MileageDepositInfo**&, int&);  // 0xb9630
    static bool RetrieveMileageDeposit(int&, unsigned long long, MileageDepositInfo&);  // 0xba390
    static bool TryMileageDepost(int&, id128 const&, int, long long, long long, long long, long long*, short*, unsigned long long&);  // 0xbaac0
    static bool FinishMileageDeposit(int&, unsigned long long, bool);  // 0xbb3b0
};
