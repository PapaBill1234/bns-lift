// task.h: task.cpp, task.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"
#include "duelbottrainingroomscorecontainer.h"
#include "inventory.h"
#include "seasonscore.h"
#include "tendencymanager.h"

class AccountLevelUpTask
{
public:
    __cdecl AccountLevelUpTask(void);  // 0x1edfa0
    bool __cdecl Initialize(::Zone *, ::Creature *, int, int, short);  // 0x292b50
private:
    virtual void __cdecl start(void);  // 0x292c30
};

class AchievementAbilityInstallTask
{
private:
    virtual void __cdecl start(void);  // 0x2a33c0
};

class AchievementPcRelogin
{
private:
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x2a2c00
    virtual void __cdecl start(void);  // 0x2a2c40
};

class AchievementTitleInstallTask
{
private:
    virtual void __cdecl start(void);  // 0x2a31f0
};

class AcquireConfirmFailTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, unsigned __int64, unsigned __int64, unsigned __int64, char, short);  // 0x291fb0
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x2920a0
private:
    virtual void __cdecl start(void);  // 0x2920e0
};

class AcquireConfirmTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, unsigned __int64, unsigned __int64, unsigned __int64, unsigned __int64, char, char const *, short);  // 0x291b70
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x291cc0
private:
    virtual void __cdecl start(void);  // 0x291d00
};

class AcquireMentoringQuestTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, void *);  // 0x2d4700
private:
    virtual void __cdecl start(void);  // 0x2d47f0
public:
    __cdecl AcquireMentoringQuestTask(void);  // 0x350090
};

class ActivateAllGradeTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Pc *, int, ::GradeLevelInfo &, ::GradeInfo *const, short);  // 0x2a2660
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x2a27a0
private:
    virtual void __cdecl start(void);  // 0x2a27e0
public:
    __cdecl ActivateAllGradeTask(void);  // 0x454f50
};

class ActivatedTeleportTask
{
private:
    virtual void __cdecl start(void);  // 0x298820
};

class AddBotScoreStateTask
{
private:
    virtual void __cdecl start(void);  // 0x2c6790
};

class AddDiscoveryAreaTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, short);  // 0x298650
private:
    virtual void __cdecl start(void);  // 0x298760
};

class ApplySkillSkinTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, short);  // 0x2cfaa0
private:
    virtual void __cdecl start(void);  // 0x2cfb40
};

class ArenaEventBattleRoyalScoreTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Pc *);  // 0x2a12b0
private:
    virtual void __cdecl start(void);  // 0x2a1340
};

class ArenaEventInZonePcLocTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Pc *);  // 0x2a1050
private:
    virtual void __cdecl start(void);  // 0x2a10d0
};

class ArenaEventRetreivePcAssetTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Pc *, ::Pc *);  // 0x2a0b10
private:
    virtual void __cdecl start(void);  // 0x2a0bc0
};

class ArenaEventReturnToArenaLobbyAllPcTask
{
private:
    virtual void __cdecl start(void);  // 0x2a0730
};

class ArenaEventReturnToArenaLobbyTask
{
private:
    virtual void __cdecl start(void);  // 0x2a0420
};

class ArenaEventTeleportToTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Pc *, ::Pc *);  // 0x2a0040
private:
    virtual void __cdecl start(void);  // 0x2a00f0
    void __cdecl warp(void);  // 0x2a01f0
    void __cdecl zoneTransition(void);  // 0x2a0310
};

class ArenaEventWarpToDuelRoundStartPcSpawnTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Pc *, char);  // 0x2a0da0
private:
    virtual void __cdecl start(void);  // 0x2a0e40
};

class ArenaGradeParam
{
public:
    __cdecl ArenaGradeParam(void);  // 0x96e50
};

class ArenaSpectateReturnToArenaLobbyTask
{
private:
    virtual void __cdecl start(void);  // 0x29fd50
};

class AuctionEscrowBidTask
{
public:
    __cdecl AuctionEscrowBidTask(void);  // 0x29dbf0
private:
    virtual void __cdecl start(void);  // 0x29dc80
};

class AuctionEscrowTask
{
public:
    virtual void __cdecl ProcessUnexpired(int);  // 0x29d550
    bool __cdecl Initialize(::Zone *, ::Creature *, short, __int64, __int64, __int64);  // 0x29d600
private:
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x29d750
    virtual void __cdecl start(void);  // 0x29d790
public:
    __cdecl AuctionEscrowTask(void);  // 0x454db0
};

class AutoLogoutCheckTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *);  // 0x2a1750
private:
    virtual void __cdecl start(void);  // 0x2a17e0
};

class BanishFromPartyTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, char);  // 0x2b7d30
private:
    virtual void __cdecl start(void);  // 0x2b7e00
};

class BanishFromTeamTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, short, char);  // 0x2b5420
private:
    virtual void __cdecl start(void);  // 0x2b54f0
};

class BindRaidDungeonTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, unsigned __int64, unsigned __int64, char);  // 0x2a3730
private:
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x2a3810
    virtual void __cdecl start(void);  // 0x2a3860
};

class BuyRandomStoreItemTask
{
public:
    struct DisposeOrder {};
public:
    bool __cdecl Initialize(::Zone *const, ::Pc *const, char, char, char, int, ::BuyRandomStoreItemTask::DisposeOrder const *const);  // 0x2aa240
private:
    virtual void __cdecl start(void);  // 0x2aa470
    bool __cdecl checkItemPrice(int, short);  // 0x2ab9a0
public:
    __cdecl BuyRandomStoreItemTask(void);  // 0x34f8a0
};

class CallMentoringMemberTask
{
public:
    static bool __cdecl CheckTeleport(short, ::Pc *, unsigned int &, short &, ::vector16 &);  // 0x2d6100
    static bool __cdecl CheckMentoring(::Pc *, ::Pc *);  // 0x2d64c0
    bool __cdecl Initialize(::Zone *, ::Creature *, unsigned __int64, short);  // 0x2d66e0
private:
    virtual void __cdecl start(void);  // 0x2d67d0
};

class ChallengeListTask
{
private:
    virtual void __cdecl start(void);  // 0x2d92d0
};

class ChangeBadgeEquipPageTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, unsigned char);  // 0x2d9570
private:
    virtual void __cdecl start(void);  // 0x2d9640
};

class ChangeChannelTask
{
private:
    virtual void __cdecl start(void);  // 0x299490
};

class ChangeGradeLevelTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Pc *, int, ::GradeLevelInfo &);  // 0x2a2130
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x2a2210
private:
    virtual void __cdecl start(void);  // 0x2a2250
public:
    __cdecl ChangeGradeLevelTask(void);  // 0x454ed0
};

class ChangeGradeTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Pc *, int, ::GradeInfo &, char);  // 0x2a1c30
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x2a1d20
private:
    virtual void __cdecl start(void);  // 0x2a1d60
public:
    __cdecl ChangeGradeTask(void);  // 0x454e30
};

class ChangeMentoringTypeTask
{
private:
    virtual void __cdecl start(void);  // 0x2d30c0
};

class ChangePartyDifficultyTypeTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, char);  // 0x2b8680
private:
    virtual void __cdecl start(void);  // 0x2b8750
};

class ChangePartyInviteAuthTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, ::PartyInviteAuth);  // 0x2b8220
private:
    virtual void __cdecl start(void);  // 0x2b82f0
};

class ChangePartyOptionTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, ::PartyPickupRule, unsigned __int64, char, __int64);  // 0x2b8050
private:
    virtual void __cdecl start(void);  // 0x2b8140
public:
    __cdecl ChangePartyOptionTask(void);  // 0x34fba0
};

class ChangeSlatePageTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Pc *, char);  // 0x2e00f0
private:
    virtual void __cdecl start(void);  // 0x2e0210
    void __cdecl writeGameLog(char);  // 0x2e0590
};

class ChangeTeamInviteAuthTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, char);  // 0x2b5c70
private:
    virtual void __cdecl start(void);  // 0x2b5d40
};

class ChangeTeamPartyDifficultyTypeTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, char, char);  // 0x2b5e00
private:
    virtual void __cdecl start(void);  // 0x2b5ed0
};

class ChangeToReplayQuestTask
{
private:
    virtual void __cdecl start(void);  // 0x2acaa0
};

class ChangeWarFieldStepTask
{
public:
    __cdecl ChangeWarFieldStepTask(char, char);  // 0x1ee1d0
private:
    virtual void __cdecl start(void);  // 0x2cfd20
};

class ChangeWeaponAppearanceTask
{
public:
    __cdecl ChangeWeaponAppearanceTask(void);  // 0x2bd3f0
    virtual __cdecl ~ChangeWeaponAppearanceTask(void);  // 0x2bd490
    bool __cdecl InitializeForTry(::Zone *, ::Pc *, ::ChangeWeaponAppearanceTaskTryParam const *);  // 0x2bd560
    bool __cdecl InitializeForOk(::Zone *, ::Pc *, ::ChangeWeaponAppearanceTaskOkParam const *);  // 0x2bd6c0
    bool __cdecl InitializeForFail(::Zone *, ::Pc *, ::ChangeWeaponAppearanceTaskFailParam const *);  // 0x2bd860
private:
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x2bda30
    virtual void __cdecl start(void);  // 0x2bda70
    bool __cdecl checkTryParam(::Pc *, ::ChangeWeaponAppearanceTaskTryParam const *);  // 0x2bdc40
    short __cdecl processChangeWeaponAppearanceTry(::Pc *, ::User *);  // 0x2be0f0
    void __cdecl processChangeWeaponAppearanceOk(::Pc *);  // 0x2be660
    void __cdecl processChangeWeaponAppearanceFail(::Pc *);  // 0x2be8b0
    bool __cdecl checkTargetWeapon(::Pc *, unsigned __int64 &, int &, char &, ::Data::ItemRecordWeaponPtr &, ::Data::WeaponAppearanceChangeCostRecordPtr &, ::ChangeWeaponAppearanceTranLogInfo &);  // 0x2bebb0
    bool __cdecl checkApplyingWeapon(::Pc *, int, char, ::Data::ItemRecordWeaponPtr, int &, char &, ::ChangeWeaponAppearanceTranLogInfo &);  // 0x2bf040
    bool __cdecl checkCostItem(::Pc *, ::Data::WeaponAppearanceChangeCostRecordPtr, ::ChangeWeaponAppearanceTranLogInfo &);  // 0x2bf4f0
    bool __cdecl checkCostMoney(::Pc *, ::Data::WeaponAppearanceChangeCostRecordPtr, int &, ::ChangeWeaponAppearanceTranLogInfo &);  // 0x2bf730
    bool __cdecl startTransaction(::Pc *, ::User *, unsigned __int64, int, char, int, ::ChangeWeaponAppearanceTranLogInfo *, ::Item *, unsigned __int64);  // 0x2bf9a0
};

class ChannelListTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, unsigned int);  // 0x299160
private:
    virtual void __cdecl start(void);  // 0x299210
};

class CheckArenaPortalUsableTask
{
public:
    enum CHECK_ARENA_PORTAL_USABLE_REASON {};
private:
    void __cdecl fail(::Pc *, short, wchar_t const *, bool);  // 0x29e410
    virtual void __cdecl start(void);  // 0x29e640
    bool __cdecl usableMoveToArenaLobby(::Pc *, char);  // 0x29e720
    bool __cdecl usableReturnToArenaLobby(::Pc *, char);  // 0x29ec30
    bool __cdecl publishRecruitArenaDungeon(::Pc *, char);  // 0x29ef60
    bool __cdecl cancelRecruitArenaDungeon(::Pc *, char);  // 0x29f290
public:
    __cdecl CheckArenaPortalUsableTask(::Data::ArenaPortalRecordPtr, ::CheckArenaPortalUsableTask::CHECK_ARENA_PORTAL_USABLE_REASON);  // 0x34f6f0
};

class CheckInviteChallengePartyTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, ::CheckInviteChallengePartyTaskParam *);  // 0x2d07b0
private:
    short __cdecl check(::InviteChallengePartyTaskParam const &);  // 0x2d08d0
    short __cdecl checkTarget(::InviteChallengePartyTaskParam const &);  // 0x2d0c30
    virtual void __cdecl start(void);  // 0x2d0ff0
public:
    __cdecl CheckInviteChallengePartyTask(void);  // 0x34fed0
};

class CheckToJoinPartyTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, unsigned __int64, unsigned int, char);  // 0x2b5f80
private:
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x2b6060
    virtual void __cdecl start(void);  // 0x2b60a0
public:
    __cdecl CheckToJoinPartyTask(void);  // 0x34f9d0
};

class CheckToJoinTeamTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, char, unsigned __int64, unsigned __int64);  // 0x2baba0
private:
    virtual void __cdecl start(void);  // 0x2bac80
};

class ClearBuffDebuffTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *);  // 0x298380
private:
    virtual void __cdecl start(void);  // 0x298450
};

class ClearLogoutPartyMemberTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *);  // 0x2b7ee0
private:
    virtual void __cdecl start(void);  // 0x2b7f90
public:
    __cdecl ClearLogoutPartyMemberTask(void);  // 0x34fb40
};

class CollectingListTask
{
private:
    virtual void __cdecl start(void);  // 0x2d7840
};

class CompleteClosetCollectingTask
{
public:
    __cdecl CompleteClosetCollectingTask(void);  // 0x2d7870
    bool __cdecl InitializeForTry(::Zone *, ::Creature *, ::Packet const *);  // 0x2d7920
    bool __cdecl InitializeForOk(::Zone *, ::Creature *, ::CompleteClosetCollectingOkParam &);  // 0x2d7c70
    bool __cdecl InitializeForFail(::Zone *, ::Creature *, ::CompleteClosetCollectingFailParam &);  // 0x2d7e50
private:
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x2d7fb0
public:
    void __cdecl CompleteClosetCollectingReq(void);  // 0x2d7ff0
    void __cdecl CompleteClosetCollectingOk(void);  // 0x2d8100
    void __cdecl CompleteClosetCollectingFail(void);  // 0x2d81d0
private:
    virtual void __cdecl start(void);  // 0x2d8280
};

class ConfirmInvitationChallengePartyFailFromCacheTask
{
public:
    __cdecl ConfirmInvitationChallengePartyFailFromCacheTask(void);  // 0x27a00
    virtual bool __cdecl Initialize(::Zone *, ::Creature *, void *);  // 0x2d1f10
private:
    virtual void __cdecl start(void);  // 0x2d2010
};

class ConfirmInvitationChallengePartyOkFromCacheTask
{
public:
    __cdecl ConfirmInvitationChallengePartyOkFromCacheTask(void);  // 0x27970
    virtual bool __cdecl Initialize(::Zone *, ::Creature *, void *);  // 0x2d1c00
private:
    virtual void __cdecl start(void);  // 0x2d1d40
};

class ConfirmInvitationChallengePartyStartTask
{
public:
    virtual bool __cdecl Initialize(::Zone *, ::Creature *, void *);  // 0x2d1780
private:
    virtual void __cdecl start(void);  // 0x2d1870
};

class ConfirmInvitationMentoringFailFromCacheTask
{
public:
    __cdecl ConfirmInvitationMentoringFailFromCacheTask(void);  // 0x110470
    virtual bool __cdecl Initialize(::Zone *, ::Creature *, void *);  // 0x2d5330
private:
    virtual void __cdecl start(void);  // 0x2d5430
};

class ConfirmInvitationMentoringOkFromCacheTask
{
public:
    __cdecl ConfirmInvitationMentoringOkFromCacheTask(void);  // 0x1103f0
    virtual bool __cdecl Initialize(::Zone *, ::Creature *, void *);  // 0x2d5160
private:
    virtual void __cdecl start(void);  // 0x2d52a0
};

class ConfirmInvitationMentoringStartTask
{
public:
    __cdecl ConfirmInvitationMentoringStartTask(void);  // 0x1ee360
    virtual bool __cdecl Initialize(::Zone *, ::Creature *, void *);  // 0x2d4cd0
private:
    virtual void __cdecl start(void);  // 0x2d4dc0
};

class ConfirmPartyMemberTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, unsigned int, char, char);  // 0x2b7040
    virtual void __cdecl ProcessUnexpired(int);  // 0x2b7120
private:
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x2b71b0
    virtual void __cdecl start(void);  // 0x2b71f0
};

class ConfirmTeamMemberPartyChangeTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, unsigned int, char, char, ::LeavePartyMemberResult *);  // 0x2bc2f0
    virtual void __cdecl ProcessUnexpired(int);  // 0x2bc3f0
private:
    virtual void __cdecl start(void);  // 0x2bc480
};

class ConfirmTeamMemberTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, ::TeamInvitationType, char);  // 0x2bbf80
    virtual void __cdecl ProcessUnexpired(int);  // 0x2bc060
private:
    virtual void __cdecl start(void);  // 0x2bc0f0
};

class CreateChallengePartyFailFromCacheTask
{
public:
    __cdecl CreateChallengePartyFailFromCacheTask(void);  // 0x278f0
    virtual bool __cdecl Initialize(::Zone *, ::Creature *, void *);  // 0x2d05d0
private:
    virtual void __cdecl start(void);  // 0x2d06d0
};

class CreateChallengePartyOkFromCacheTask
{
public:
    __cdecl CreateChallengePartyOkFromCacheTask(void);  // 0x27870
    virtual bool __cdecl Initialize(::Zone *, ::Creature *, void *);  // 0x2d02d0
private:
    virtual void __cdecl start(void);  // 0x2d03e0
};

class CreateChallengePartyStartTask
{
public:
    virtual bool __cdecl Initialize(::Zone *, ::Creature *, void *);  // 0x2cfed0
private:
    virtual void __cdecl start(void);  // 0x2cfff0
public:
    __cdecl CreateChallengePartyStartTask(void);  // 0x34fe20
};

class CreatePartyTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, char, bool);  // 0x2b7920
private:
    virtual void __cdecl start(void);  // 0x2b79f0
};

class DelegatePartyLeaderTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, unsigned __int64);  // 0x2b7af0
private:
    virtual void __cdecl start(void);  // 0x2b7bc0
};

class DelegateTeamLeaderTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, unsigned __int64);  // 0x2b5830
private:
    virtual void __cdecl start(void);  // 0x2b5900
};

class DepositMileageTask
{
public:
    __cdecl DepositMileageTask(void);  // 0x2b10d0
    virtual __cdecl ~DepositMileageTask(void);  // 0x2b1170
    bool __cdecl InitializeForTry(::Zone *, ::Creature *, ::DepositMileageTaskTryParam const *);  // 0x2b1240
    bool __cdecl InitializeForOk(::Zone *, ::Creature *, ::DepositMileageTaskOkParam const *);  // 0x2b1530
    bool __cdecl InitializeForFail(::Zone *, ::Creature *, ::DepositMileageTaskFailParam const *);  // 0x2b1760
private:
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x2b19c0
    bool __cdecl checkTryParam(::Pc const *, ::DepositMileageTaskTryParam const *);  // 0x2b1a00
    short __cdecl processDepositMileageTry(::Pc *);  // 0x2b1e00
    void __cdecl processDepositMileageOk(::Pc *);  // 0x2b2980
    void __cdecl processDepositMileageFail(::Pc *);  // 0x2b2a80
    virtual void __cdecl start(void);  // 0x2b2bb0
};

class DetectTeleportSwitchTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, short);  // 0x2989e0
private:
    virtual void __cdecl start(void);  // 0x298af0
};

class DieInExhaustionTask
{
private:
    virtual void __cdecl start(void);  // 0x294830
};

class DiscoveryAreaTask
{
private:
    virtual void __cdecl start(void);  // 0x298490
};

class DismissPartyIfSoloTask
{
public:
    __cdecl DismissPartyIfSoloTask(void);  // 0x1ee150
    bool __cdecl Initialize(::Zone *, ::Creature *);  // 0x2b7380
private:
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x2b7430
    virtual void __cdecl start(void);  // 0x2b7470
};

class DrawSlateNewStoneTask
{
public:
    struct LogForDraw {};
    struct LogForItem {};
public:
    __cdecl DrawSlateNewStoneTask(void);  // 0x2dcf00
    virtual __cdecl ~DrawSlateNewStoneTask(void);  // 0x2dcfe0
    bool __cdecl Initialize(::Zone *, ::Pc *, char, char, ::Inventory::DisposeOrderWithPos &, ::Inventory::DisposeOrderWithPos *, int, int, double);  // 0x2dd050
private:
    virtual void __cdecl start(void);  // 0x2dd2d0
protected:
    bool __cdecl checkCosts(::Data::SlateScrollRecordPtr &, ::DrawSlateNewStoneTask::LogForItem &, ::DrawSlateNewStoneTask::LogForItem *);  // 0x2dd6f0
private:
    bool __cdecl checkScroll(::Item const *, ::Data::ItemRecordPtr const &, ::Data::SlateScrollRecordPtr &);  // 0x2dd950
    bool __cdecl checkOrders(::Data::SlateScrollRecordPtr const &, ::DrawSlateNewStoneTask::LogForItem *);  // 0x2ddad0
    bool __cdecl initCostCollector(::Data::SlateScrollRecordPtr const &);  // 0x2ddec0
    bool __cdecl checkCostCollector(void);  // 0x2ddfb0
    bool __cdecl tryPayment(::Data::SlateScrollRecordPtr const &);  // 0x2de060
protected:
    bool __cdecl disposeCosts(::Data::SlateScrollRecordPtr const &);  // 0x2de4d0
    virtual void __cdecl extractGameLog(::Slate const *, ::Data::SlateScrollRecordPtr const &, ::DrawSlateNewStoneTask::LogForDraw &);  // 0x2de710
    void __cdecl writeGameLog(::DrawSlateNewStoneTask::LogForDraw &, ::DrawSlateNewStoneTask::LogForItem &, ::DrawSlateNewStoneTask::LogForItem *, int);  // 0x2de810
};

class DrawSlateNewStoneCallbackTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Pc *, char, char, ::Inventory::DisposeOrderWithPos &, int, double, __int64, ::InstantPaymentTran *, __int64, __int64);  // 0x2decf0
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x2dee10
    virtual void __cdecl ProcessUnexpired(int);  // 0x2dee50
private:
    virtual void __cdecl start(void);  // 0x2df020
    virtual void __cdecl extractGameLog(::Slate const *, ::Data::SlateScrollRecordPtr const &, ::DrawSlateNewStoneTask::LogForDraw &);  // 0x2df6b0
};

class DuelBotChallengeCombatTask
{
public:
    __cdecl DuelBotChallengeCombatTask(void);  // 0x96f40
    bool __cdecl Initialize(::Zone *, ::Creature *, unsigned __int64);  // 0x2c2e40
private:
    virtual void __cdecl start(void);  // 0x2c2f00
};

class DuelBotChallengeStrategicToolTask
{
public:
    enum DuelBotChallengeStrategicToolAction {};
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, ::DuelBotChallengeStrategicToolTask::DuelBotChallengeStrategicToolAction, unsigned __int64, char);  // 0x2c3430
private:
    virtual void __cdecl start(void);  // 0x2c3510
public:
    __cdecl DuelBotChallengeStrategicToolTask(void);  // 0x34fcf0
};

class DuelBotTrainingRoomCombatTask
{
private:
    virtual void __cdecl start(void);  // 0x2c08e0
};

class DuelBotTrainingRoomPickDuelBotTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, int, char);  // 0x2c05a0
private:
    virtual void __cdecl start(void);  // 0x2c06e0
};

class DuelBotTrainingRoomResultTask
{
public:
    __cdecl DuelBotTrainingRoomResultTask(void);  // 0x2c23b0
    bool __cdecl Initialize(::Zone *, ::Pc *, bool, short, ::DuelBotTrainingRoomScoreContainer::DuelBotTrainingRoomScoreValue const *);  // 0x2c2430
private:
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x2c24d0
    virtual void __cdecl start(void);  // 0x2c2510
};

class DuelBotTrainingRoomRewardHandlerTask
{
public:
    __cdecl DuelBotTrainingRoomRewardHandlerTask(void);  // 0x2c2630
    bool __cdecl Initialize(::Zone *, ::Pc *, char, char, char);  // 0x2c26a0
private:
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x2c2760
    virtual void __cdecl start(void);  // 0x2c27a0
};

class DuelBotTrainingRoomRewardTask
{
public:
    __cdecl DuelBotTrainingRoomRewardTask(void);  // 0x2c0e60
    virtual __cdecl ~DuelBotTrainingRoomRewardTask(void);  // 0x2c0f40
    bool __cdecl InitializeForTry(::Zone *, ::Creature *, ::DuelBotTrainingRoomRewardTran *);  // 0x2c0fa0
    bool __cdecl InitializeForOk(::Zone *, ::Creature *, short, char, char, int, short, unsigned __int64 *const, unsigned __int64 *const, ::DuelBotTrainingRoomRewardTran *);  // 0x2c1280
    bool __cdecl InitializeForFail(::Zone *, ::Creature *, short, char, char, int, ::PropertyTransactionFailParam *, ::DuelBotTrainingRoomRewardTran *);  // 0x2c1470
private:
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x2c1690
    virtual void __cdecl start(void);  // 0x2c16d0
};

class DuelChooseDuelOrderTask
{
public:
    bool __cdecl Initialize(::Zone *const, ::Pc *const, char);  // 0x2bc550
private:
    virtual void __cdecl start(void);  // 0x2bc600
};

class DuelResultTask
{
public:
    __cdecl DuelResultTask(void);  // 0x2c4c60
    virtual __cdecl ~DuelResultTask(void);  // 0x2c4d20
    bool __cdecl Initialize(::Zone *, ::Pc *, char, bool, ::SeasonContentsCombatRecordContainer::SeasonContentsCombatRecordValue const *, bool, ::DuelResultTranResultNotifyInfo const *);  // 0x2c4d90
private:
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x2c5030
    virtual void __cdecl start(void);  // 0x2c5070
};

class DuelTask
{
public:
    enum DuelTaskType {};
public:
    bool __cdecl Initialize(::Zone *const, ::Pc *const, ::DuelTask::DuelTaskType);  // 0x2bc850
private:
    virtual void __cdecl start(void);  // 0x2bc8f0
public:
    __cdecl DuelTask(void);  // 0x34fc20
};

class EnterAttractionZoneTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, char, char, short, ::Inventory::DisposeOrderWithPos *const);  // 0x2c3630
private:
    virtual void __cdecl start(void);  // 0x2c37d0
    ::GameFailReason __cdecl checkChallengePartyAttraction(unsigned __int64 &, short &, ::Inventory::DisposeOrderWithPos *const);  // 0x2c3f20
    bool __cdecl chkeckConsumeItems(int, unsigned __int64 const *const, short const *const, short &, ::Inventory::DisposeOrderWithPos *const);  // 0x2c4450
};

class EnterPortalTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *);  // 0x298cb0
private:
    virtual void __cdecl start(void);  // 0x298da0
};

class EnterSkillTrainingRoomTask
{
private:
    virtual void __cdecl start(void);  // 0x2c6f00
};

class EnterZoneTask
{
private:
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x294050
    virtual void __cdecl start(void);  // 0x294060
};

class ExpandRandomStoreSlotTask
{
public:
    struct DisposeOrder {};
    enum Operation {};
public:
    __cdecl ExpandRandomStoreSlotTask(void);  // 0x110330
    bool __cdecl Initialize(::Zone *const, ::Pc *const, char, char, char, int, ::ExpandRandomStoreSlotTask::DisposeOrder const *const);  // 0x2a87d0
    bool __cdecl Initialize(::Zone *const, ::Pc *const, char, char, char, ::ExpandRandomStoreSlotTask::Operation, ::InstantPaymentTran *const, __int64);  // 0x2a8a20
    virtual void __cdecl ProcessUnexpired(int);  // 0x2a8c60
private:
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x2a8cf0
    virtual void __cdecl start(void);  // 0x2a8d30
    short const __cdecl checkInstantPaymentCondition(void);  // 0x2a8d60
    short const __cdecl checkApplyCondition(void);  // 0x2a9350
    void __cdecl tryInstantPayment(void);  // 0x2a9510
    void __cdecl apply(void);  // 0x2a96b0
};

class FeedPetFoodTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, unsigned char, unsigned short, unsigned short, unsigned char);  // 0x2c0300
private:
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x2c03f0
    virtual void __cdecl start(void);  // 0x2c0430
};

class FinishTakeAchievementRewardTask
{
public:
    __cdecl FinishTakeAchievementRewardTask(void);  // 0x180aa0
private:
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x2c8f40
    virtual void __cdecl start(void);  // 0x2c8f80
};

class FishManipulateTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, char, bool);  // 0x2d8f90
private:
    virtual void __cdecl start(void);  // 0x2d90e0
};

class FishingListTask
{
private:
    virtual void __cdecl start(void);  // 0x2d8f60
};

class GiveUpSlateNewStoneTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Pc *, char);  // 0x2dfd20
private:
    virtual void __cdecl start(void);  // 0x2dfe40
};

class GuildBattleFieldZoneCloseTask
{
public:
    bool __cdecl Initialize(::Zone *);  // 0x2a5dc0
private:
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x2a5e50
};

class GuildJoinRenewalTask
{
public:
    void __cdecl Post(void);  // 0x299e40
private:
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x299e70
    virtual void __cdecl start(void);  // 0x299eb0
    void __cdecl sendGuildApplicationReq(void);  // 0x299f70
    void __cdecl cancelGuildApplicationReq(void);  // 0x29a720
    void __cdecl rejectGuildApplicationReq(void);  // 0x29a960
    void __cdecl acceptGuildApplicationReq(void);  // 0x29add0
    void __cdecl sendGuildInvitationReq(void);  // 0x29b0f0
    void __cdecl cancelGuildInvitationReq(void);  // 0x29bbd0
    void __cdecl rejectGuildInvitationReq(void);  // 0x29bf60
    void __cdecl acceptGuildInvitationReq(void);  // 0x29c1a0
public:
    __cdecl GuildJoinRenewalTask(void);  // 0x34f5b0
};

class IPsoTranTask
{
private:
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x2cfe90
};

class InitailizeSeasonContentsInfoTask
{
public:
    __cdecl InitailizeSeasonContentsInfoTask(void);  // 0x2c6020
    bool __cdecl InitializeReq(::Zone *, ::Pc *, char, char const *const);  // 0x2c60f0
    bool __cdecl InitializeOk(::Zone *, ::Pc *, short, ::InitCombatResultList *const, short, ::InitTimeAttackResultList *const);  // 0x2c61c0
private:
    virtual void __cdecl start(void);  // 0x2c62f0
    void __cdecl ok(void);  // 0x2c6360
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x2c6440
};

class InitializeRaidDungeonInfoTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, bool);  // 0x2a5c30
private:
    virtual void __cdecl start(void);  // 0x2a5d00
public:
    __cdecl InitializeRaidDungeonInfoTask(void);  // 0x34f840
};

class InviteChallengePartyTask
{
public:
    __cdecl InviteChallengePartyTask(void);  // 0x1ee260
    bool __cdecl Initialize(::Zone *, ::Creature *, ::InviteChallengePartyTaskParam const *);  // 0x2d1150
private:
    short __cdecl check(void);  // 0x2d1240
    virtual void __cdecl start(void);  // 0x2d1390
};

class InviteMentoringTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, unsigned __int64, unsigned __int64, char);  // 0x2d38d0
private:
    virtual void __cdecl start(void);  // 0x2d39b0
public:
    __cdecl InviteMentoringTask(void);  // 0x350010
};

class InvitePcToPartyTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, unsigned __int64, unsigned __int64, unsigned int, char, char, char, char, char, char);  // 0x2b2fb0
private:
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x2b30e0
    bool __cdecl checkZoneRule(::Pointer2< ::Pc>, ::Pointer2< ::Pc>);  // 0x2b3120
    virtual void __cdecl start(void);  // 0x2b33c0
public:
    __cdecl InvitePcToPartyTask(void);  // 0x34f950
};

class InviteTeamTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, char, unsigned __int64, unsigned __int64, char, char, char, char, char, unsigned __int64);  // 0x2b8f20
private:
    virtual void __cdecl start(void);  // 0x2b9050
};

class JoinCraftUnionTask
{
public:
    __cdecl JoinCraftUnionTask(void);  // 0x2cd0f0
    bool __cdecl InitializeForTry(::Zone *, ::Creature *, char, __int64);  // 0x2cd160
    bool __cdecl InitializeForOk(::Zone *, ::Creature *, char);  // 0x2cd2d0
private:
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x2cd3d0
    virtual void __cdecl start(void);  // 0x2cd410
public:
    void __cdecl JoinCraftUnionReq(void);  // 0x2cd480
    void __cdecl JoinCraftUnionOk(void);  // 0x2cde70
};

class JoinFactionTask
{
private:
    virtual void __cdecl start(void);  // 0x294cd0
};

class KillSummonedTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *);  // 0x2a15f0
private:
    virtual void __cdecl start(void);  // 0x2a1680
};

class LeaveAttractionZoneTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *);  // 0x2c4a40
private:
    virtual void __cdecl start(void);  // 0x2c4af0
public:
    __cdecl LeaveAttractionZoneTask(void);  // 0x34fd60
};

class LeaveChallengePartyOkFromCacheTask
{
public:
    __cdecl LeaveChallengePartyOkFromCacheTask(void);  // 0x27a80
    virtual bool __cdecl Initialize(::Zone *, ::Creature *, void *);  // 0x2d2d60
private:
    virtual void __cdecl start(void);  // 0x2d2ec0
};

class LeaveChallengePartyStartTask
{
public:
    virtual bool __cdecl Initialize(::Zone *, ::Creature *, void *);  // 0x2d25b0
private:
    virtual void __cdecl start(void);  // 0x2d26e0
public:
    __cdecl LeaveChallengePartyStartTask(void);  // 0x34ff80
};

class LeaveCraftUnionTask
{
public:
    __cdecl LeaveCraftUnionTask(void);  // 0x2cdfe0
    bool __cdecl InitializeForTry(::Zone *, ::Creature *, char);  // 0x2ce050
    bool __cdecl InitializeForOk(::Zone *, ::Creature *, char);  // 0x2ce160
private:
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x2ce260
    virtual void __cdecl start(void);  // 0x2ce2a0
public:
    void __cdecl LeaveCraftUnionReq(void);  // 0x2ce310
    void __cdecl LeaveCraftUnionOk(void);  // 0x2ceb60
};

class LeaveFactionTask
{
private:
    virtual void __cdecl start(void);  // 0x295140
};

class LeaveMentoringOkFromCacheTask
{
public:
    __cdecl LeaveMentoringOkFromCacheTask(void);  // 0x110500
    virtual bool __cdecl Initialize(::Zone *, ::Creature *, void *);  // 0x2d5e40
private:
    virtual void __cdecl start(void);  // 0x2d5f80
};

class LeaveMentoringStartTask
{
public:
    virtual bool __cdecl Initialize(::Zone *, ::Creature *, void *);  // 0x2d5a00
private:
    virtual void __cdecl start(void);  // 0x2d5b00
public:
    __cdecl LeaveMentoringStartTask(void);  // 0x3501a0
};

class LeaveTeamMemberTask
{
public:
    __cdecl LeaveTeamMemberTask(void);  // 0x1ee0e0
    bool __cdecl Initialize(::Zone *, ::Creature *, unsigned __int64, ::LeavePartyReason);  // 0x2b4f90
private:
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x2b5060
    virtual void __cdecl start(void);  // 0x2b50a0
};

class LeaveTeamPartyTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, unsigned __int64, ::LeavePartyReason);  // 0x2b51b0
private:
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x2b5270
    virtual void __cdecl start(void);  // 0x2b52b0
};

class LevelUpTask
{
public:
    __cdecl LevelUpTask(void);  // 0x1edf40
    bool __cdecl Initialize(::Zone *, ::Creature *, int, int, int, int, short);  // 0x2925f0
private:
    virtual void __cdecl start(void);  // 0x2926e0
};

class MessageByDiceTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, short, short);  // 0x293ba0
private:
    virtual void __cdecl start(void);  // 0x293c30
    bool __cdecl sendMessageInSight(unsigned __int64, short);  // 0x293d00
    bool __cdecl sendMessageInZone(unsigned __int64, short);  // 0x293e40
};

class MessageByItemTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, wchar_t const *, char, short);  // 0x293310
private:
    virtual void __cdecl start(void);  // 0x2933f0
public:
    bool __cdecl SendMessageInDistrict(short, wchar_t const *);  // 0x293990
    bool __cdecl SendMessageInWorld(short, wchar_t const *);  // 0x293ad0
};

class MessageTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, ::MessageRange, int, wchar_t const *, wchar_t const *);  // 0x292e50
private:
    virtual void __cdecl start(void);  // 0x292f30
public:
    bool __cdecl SendMessageInZone(::Zone *, unsigned __int64, short, wchar_t const *, int, wchar_t const *, wchar_t const *);  // 0x293040
    bool __cdecl SendMessageInSight(::Zone *, ::vector16, unsigned __int64, short, wchar_t const *, int, wchar_t const *, wchar_t const *);  // 0x2931a0
};

class NominatePartyLeaderTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, unsigned __int64);  // 0x2b5a50
private:
    virtual void __cdecl start(void);  // 0x2b5b20
};

class PartyBattleRatingScoreTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Pc *, ::PartyBattleResult, int, int, __int64, ::PartyBattleSideMember const &);  // 0x2bcc70
private:
    virtual void __cdecl start(void);  // 0x2bcda0
public:
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x2bce30
    virtual __cdecl ~PartyBattleRatingScoreTask(void);  // 0x2bce70
    __cdecl PartyBattleRatingScoreTask(void);  // 0x455000
};

class PartyBattleResultTask
{
public:
    __cdecl PartyBattleResultTask(void);  // 0x2c5450
    virtual __cdecl ~PartyBattleResultTask(void);  // 0x2c5510
    bool __cdecl Initialize(::Zone *, ::Pc *, char, bool, ::SeasonContentsCombatRecordContainer::SeasonContentsCombatRecordValue const *, bool, ::PartyBattleResultTranResultNotifyInfo const *);  // 0x2c5580
private:
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x2c5800
    virtual void __cdecl start(void);  // 0x2c5840
};

class PartyBattleTask
{
public:
    enum PartyBattleTaskType {};
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, ::PartyBattleTask::PartyBattleTaskType);  // 0x2bcee0
private:
    virtual void __cdecl start(void);  // 0x2bcfb0
public:
    __cdecl PartyBattleTask(void);  // 0x34fc90
};

class PartyBattleVoteCastTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, unsigned __int64);  // 0x2bd1b0
private:
    virtual void __cdecl start(void);  // 0x2bd280
};

class PartyMatchNotifyTask
{
public:
    __cdecl PartyMatchNotifyTask(void);  // 0x180a30
    bool __cdecl Initialize(::Zone *, ::Creature *, unsigned __int64, unsigned int, bool, short);  // 0x299bb0
private:
    virtual void __cdecl start(void);  // 0x299c80
};

class PartyVoteCastTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, char, char);  // 0x2b8b50
private:
    virtual void __cdecl start(void);  // 0x2b8c20
};

class PublicRaidEventAddScoreTask
{
private:
    virtual void __cdecl start(void);  // 0x2cf5a0
};

class PutItemIntoClosetTask
{
public:
    __cdecl PutItemIntoClosetTask(void);  // 0x2acb60
    bool __cdecl InitializeForTry(::Zone *, ::Creature *, short);  // 0x2acbf0
    bool __cdecl InitializeForOk(::Zone *, ::Creature *, int, char, short);  // 0x2accf0
    bool __cdecl InitializeForFail(::Zone *, ::Creature *, short, unsigned __int64, char, int);  // 0x2acdd0
private:
    bool __cdecl rollbackItem(char);  // 0x2aceb0
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x2acef0
    virtual void __cdecl start(void);  // 0x2acf30
    bool __cdecl checkItem(void);  // 0x2ad2f0
    bool __cdecl makeTransaction(::Pc *);  // 0x2ad8d0
};

class RandomStoreDrawTask
{
public:
    struct ConsumeOrder {};
    enum Operation {};
public:
    __cdecl RandomStoreDrawTask(void);  // 0x110250
    virtual __cdecl ~RandomStoreDrawTask(void);  // 0x2a62f0
    bool __cdecl Initialize(::Zone *const, ::Pc *const, char, char, char, int, ::RandomStoreDrawTask::ConsumeOrder const *const);  // 0x2a6350
    bool __cdecl Initialize(::Zone *const, ::Pc *const, char, char, char, ::RandomStoreDrawTask::Operation, ::InstantPaymentTran *const, __int64);  // 0x2a6620
    virtual void __cdecl ProcessUnexpired(int);  // 0x2a6830
private:
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x2a68b0
    virtual void __cdecl start(void);  // 0x2a68f0
    short const __cdecl checkInstantPaymentCondition(void);  // 0x2a6920
    short const __cdecl checkApplyCondition(void);  // 0x2a6b80
    void __cdecl tryInstantPayment(void);  // 0x2a7460
    void __cdecl apply(void);  // 0x2a75f0
};

class RandomStoreInfoTask
{
private:
    virtual void __cdecl start(void);  // 0x2a62c0
};

class RechargeVitalityTask
{
private:
    virtual void __cdecl start(void);  // 0x2a1b10
};

class RefreshSimpleQuestPackTask
{
private:
    virtual void __cdecl start(void);  // 0x2c6860
};

class RegisterCraftTask
{
public:
    __cdecl RegisterCraftTask(void);  // 0x2c9550
    bool __cdecl InitializeForTry(::Zone *, ::Creature *, ::Packet const *);  // 0x2c9650
    bool __cdecl InitializeForOk(::Zone *, ::Creature *, ::RegisterCraftOkParam &);  // 0x2c99e0
    bool __cdecl InitializeForFail(::Zone *, ::Creature *, ::FragmentPacketConcatenater *);  // 0x2c9c70
private:
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x2c9f30
    bool __cdecl makeConsumptionParam(::PropertyTransactionSyncFetchEx &, int, short, ::CraftOutput *const);  // 0x2c9f70
public:
    void __cdecl RegisterCraftReq(void);  // 0x2ca720
    void __cdecl RegisterCraftOk(void);  // 0x2caa20
    void __cdecl RegisterCraftFail(void);  // 0x2cac60
private:
    virtual void __cdecl start(void);  // 0x2cb1b0
    short __cdecl checkRecipe(void);  // 0x2cb230
    short __cdecl checkMaterial(void);  // 0x2cb4b0
    short __cdecl checkMaterialItem(::Data::ItemRecordPtr &, short, short &);  // 0x2cb600
    short __cdecl checkMaterialItemBrand(::Data::ItemBrandRecordPtr &, char, short &);  // 0x2cb950
    bool __cdecl simulation(short &, ::CraftOutput *const);  // 0x2cbc80
};

class RejectInvitationChallengePartyTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, __int64, char);  // 0x2d20b0
private:
    virtual void __cdecl start(void);  // 0x2d21a0
};

class RejectInvitationMentoringTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, __int64, __int64, char);  // 0x2d54d0
private:
    virtual void __cdecl start(void);  // 0x2d55c0
};

class RejectTeamInvitationTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, ::TeamInvitationType, unsigned __int64, char, char);  // 0x2b4790
private:
    virtual void __cdecl start(void);  // 0x2b4870
public:
    __cdecl RejectTeamInvitationTask(void);  // 0x34fa40
};

class RequestActionCancel
{
public:
    __cdecl RequestActionCancel(void);  // 0x96ee0
private:
    virtual void __cdecl start(void);  // 0x293fd0
};

class RequestSkillTrigger
{
private:
    virtual void __cdecl start(void);  // 0x294000
};

class ReserveArenaLobbyPartyAgreementTask
{
private:
    virtual void __cdecl start(void);  // 0x29dea0
};

class ReserveArenaLobbyPartyFinalDecisionTask
{
private:
    virtual void __cdecl start(void);  // 0x29e1b0
};

class ReservePartyMemberTask
{
public:
    __cdecl ReservePartyMemberTask(void);  // 0x1ee060
    bool __cdecl Initialize(::Zone *, ::Creature *, unsigned __int64, unsigned __int64, unsigned int, char);  // 0x2b6b20
private:
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x2b6c00
    virtual void __cdecl start(void);  // 0x2b6c40
};

class ReserveTeamMemberTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, char, unsigned __int64, unsigned __int64);  // 0x2bbba0
private:
    virtual void __cdecl start(void);  // 0x2bbc80
};

class ResetChallengePartyEnvOperationTask
{
private:
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x2d2fc0
};

class ResetCombatModeTask
{
private:
    virtual void __cdecl start(void);  // 0x2cf180
};

class RespawnTask
{
public:
    __cdecl RespawnTask(void);  // 0x1ee000
    bool __cdecl Initialize(::Zone *, ::Creature *, char, bool);  // 0x294290
private:
    virtual void __cdecl start(void);  // 0x294310
};

class RetrieveBoundRaidDungeonInfoTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, unsigned __int64);  // 0x2a5630
private:
    virtual void __cdecl start(void);  // 0x2a5700
};

class RetrieveMysteriousStoreTask
{
private:
    virtual void __cdecl start(void);  // 0x2b2ce0
};

class ReturnToArenaLobbyFromDuelTask
{
private:
    virtual void __cdecl start(void);  // 0x29f520
};

class ReturnToArenaLobbyFromDungeonTask
{
private:
    void __cdecl movePc(::Pc *, char);  // 0x29f810
    virtual void __cdecl start(void);  // 0x29f9d0
public:
    __cdecl ReturnToArenaLobbyFromDungeonTask(::Data::ArenaPortalRecordPtr, bool);  // 0x34f780
};

class ReturnToBaseCampTask
{
private:
    virtual void __cdecl start(void);  // 0x2948f0
};

class ReviveByAttractionRuleTask
{
private:
    virtual void __cdecl start(void);  // 0x2c35e0
};

class SeasonContentsInfoTask
{
private:
    virtual void __cdecl start(void);  // 0x2c6480
};

class SelectTargetTask
{
private:
    virtual void __cdecl start(void);  // 0x293f50
};

class SetClosetItemUsedTask
{
public:
    __cdecl SetClosetItemUsedTask(void);  // 0x2d8310
    bool __cdecl InitializeForTry(::Zone *, ::Creature *, ::Packet const *);  // 0x2d83c0
    bool __cdecl InitializeForOk(::Zone *, ::Creature *, int, int *const);  // 0x2d8670
    bool __cdecl InitializeForFail(::Zone *, ::Creature *, int, int *const);  // 0x2d8880
private:
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x2d8a90
public:
    void __cdecl SetUsedReq(void);  // 0x2d8ad0
private:
    void __cdecl sendOk(void);  // 0x2d8bb0
    virtual void __cdecl start(void);  // 0x2d8dc0
};

class SetGuildIdTask
{
private:
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x299d10
    virtual void __cdecl start(void);  // 0x299d50
};

class SetPcSocialTask
{
private:
    virtual void __cdecl start(void);  // 0x294bd0
};

class SetPvPModeTask
{
private:
    virtual void __cdecl start(void);  // 0x2d9300
};

class SetSlateAmpSlotTask
{
public:
    struct LogForItem {};
    struct LogForSlot {};
public:
    __cdecl SetSlateAmpSlotTask(void);  // 0x2dbdd0
    bool __cdecl Initialize(::Zone *, ::Pc *, char, char, ::Inventory::DisposeOrderWithPos &);  // 0x2dbe50
private:
    virtual void __cdecl start(void);  // 0x2dc030
    bool __cdecl checkItem(int &, char &, ::SetSlateAmpSlotTask::LogForItem &);  // 0x2dc4d0
    void __cdecl extractGameLog(::Item const *, ::Data::ItemRecordPtr const &, ::SetSlateAmpSlotTask::LogForItem &);  // 0x2dc8d0
    void __cdecl writeGameLog(::SetSlateAmpSlotTask::LogForSlot &, ::SetSlateAmpSlotTask::LogForItem &);  // 0x2dcaf0
};

class SetSlateNewStoneTask
{
public:
    struct LogForSet {};
public:
    bool __cdecl Initialize(::Zone *, ::Pc *, char);  // 0x2df6f0
private:
    virtual void __cdecl start(void);  // 0x2df810
    void __cdecl writeGameLog(::SetSlateNewStoneTask::LogForSet &);  // 0x2dfab0
};

class SkillScoreNotifyTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *);  // 0x2a1540
private:
    virtual void __cdecl start(void);  // 0x2a15d0
};

class SkillSkinAcquiredListTask
{
private:
    virtual void __cdecl start(void);  // 0x2cf8e0
};

class SkillTrainingRoomCombatRestartTask
{
private:
    virtual void __cdecl start(void);  // 0x2c6d80
};

class SkillTrainingRoomCombatStartTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, unsigned __int64, char);  // 0x2c6a30
private:
    virtual void __cdecl start(void);  // 0x2c6b10
};

class SkillTrainingRoomCombatStopTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, char);  // 0x2c6be0
private:
    virtual void __cdecl start(void);  // 0x2c6cb0
};

class SkillTrainingRoomInitCreatureStateTask
{
private:
    virtual void __cdecl start(void);  // 0x2c6e40
};

class SpecialSkillGaugeTask
{
private:
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x2c9350
    virtual void __cdecl start(void);  // 0x2c9390
};

class StopCinematicTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, unsigned int);  // 0x2b83b0
private:
    virtual void __cdecl start(void);  // 0x2b8480
};

class SuggestPartyTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, unsigned __int64, char, char, char, char, char, char);  // 0x2b75b0
private:
    virtual void __cdecl start(void);  // 0x2b76c0
public:
    __cdecl SuggestPartyTask(void);  // 0x34fac0
};

class SurveyTask
{
public:
    __cdecl SurveyTask(void);  // 0x29c9e0
    bool __cdecl Initialize(::Zone *, ::Creature *, char *const, short);  // 0x29ca80
    bool __cdecl Initialize(::Zone *, ::Creature *, char, char, wchar_t *);  // 0x29cb50
private:
    virtual void __cdecl start(void);  // 0x29cc30
};

class TakeAchievementRewardTask
{
public:
    __cdecl TakeAchievementRewardTask(void);  // 0x2c75d0
private:
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x2c76e0
    virtual void __cdecl start(void);  // 0x2c7720
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, __int64, short, short);  // 0x2c7760
private:
    void __cdecl processTry(void);  // 0x2c7830
public:
    bool __cdecl InitializeForOk(::Zone *, ::Creature *, ::TakeAchievementRewardTranOkParam *);  // 0x2c7f30
private:
    void __cdecl processOk(void);  // 0x2c8090
public:
    bool __cdecl InitializeForFail(::Zone *, ::Creature *, short, ::TakeAchievementRewardTranFailParam *);  // 0x2c8980
private:
    void __cdecl processFail(void);  // 0x2c8ae0
};

class TakeAttractionRewardTask
{
private:
    virtual void __cdecl start(void);  // 0x2c3590
};

class TakeCraftTask
{
public:
    __cdecl TakeCraftTask(void);  // 0x2cbe80
    bool __cdecl InitializeForTry(::Zone *, ::Creature *, unsigned __int64);  // 0x2cbf20
    bool __cdecl InitializeForOk(::Zone *, ::Creature *, ::TakeCraftOkParam &);  // 0x2cc040
    bool __cdecl InitializeForFail(::Zone *, ::Creature *, ::TakeCraftFailParam &);  // 0x2cc200
private:
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x2cc300
    virtual void __cdecl start(void);  // 0x2cc340
public:
    void __cdecl TakeCraftReq(void);  // 0x2cc3c0
    void __cdecl TakeCraftOk(void);  // 0x2cc900
    void __cdecl TakeCraftFail(void);  // 0x2ccc90
};

class TakeItemFromClosetTask
{
public:
    __cdecl TakeItemFromClosetTask(void);  // 0x2ae100
    bool __cdecl InitializeForReqRetrieve(::Zone *, ::Creature *, int, short);  // 0x2ae1b0
    bool __cdecl InitializeForFailRetrieve(::Zone *, ::Creature *, int, short);  // 0x2ae2f0
    bool __cdecl InitializeForTry(::Zone *, ::Creature *, int, short, unsigned __int64, unsigned int, bool, bool, __int64, char, __int64, char *const);  // 0x2ae400
    bool __cdecl InitializeForOk(::Zone *, ::Creature *, int, short, unsigned __int64);  // 0x2ae540
    bool __cdecl InitializeForFail(::Zone *, ::Creature *, int, short, unsigned __int64, char);  // 0x2ae620
private:
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x2ae700
    virtual void __cdecl start(void);  // 0x2ae740
    bool __cdecl makeTransaction(::Pc *, ::Item *);  // 0x2aef70
};

class TakeRandomStoreDrawRewardTask
{
public:
    bool __cdecl Initialize(::Zone *const, ::Pc *const, char, char);  // 0x2abd80
private:
    virtual void __cdecl start(void);  // 0x2abed0
    void __cdecl writeGameLogGetRandomStoreDrawReward(::Pc *const, int, ::Data::RandomStoreDrawRewardRecordPtr, char, ::Inventory::AcquireOrder const *const);  // 0x2ac870
};

class TakeRankingRewardTask
{
public:
    __cdecl TakeRankingRewardTask(void);  // 0x2af430
    bool __cdecl InitializeForTry(::Zone *, ::Creature *, char, int, char, short, int, bool, int, int, bool);  // 0x2af520
    bool __cdecl InitializeForOk(::Zone *, ::Creature *, char, int, char, char, int, int, int, int, short, unsigned __int64 *const, unsigned __int64 *const);  // 0x2af7f0
    bool __cdecl InitializeForFail(::Zone *, ::Creature *, char, int, char, char, int, int, int, int, ::PropertyTransactionFailParam *);  // 0x2afb20
private:
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x2afcc0
    virtual void __cdecl start(void);  // 0x2afd00
};

class TakeWarehouseItemTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, unsigned __int64, ::PropertyTransactionSyncResult *, char, short, unsigned short);  // 0x292340
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x2924b0
private:
    virtual void __cdecl start(void);  // 0x2924f0
};

class TalkSessionCloseTask
{
private:
    virtual void __cdecl start(void);  // 0x292dc0
};

class TalkSessionOpenTask
{
private:
    virtual void __cdecl start(void);  // 0x292cd0
};

class Task
{
public:
    __cdecl Task(unsigned short);  // 0x2917d0
    virtual __cdecl ~Task(void);  // 0x291840
    void __cdecl Initialize(::Zone *, ::Creature *);  // 0x291860
private:
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x2918b0
protected:
    virtual ::Zone * __cdecl getParentZone(void);  // 0x291b50
};

class TeamMemberPartyChangeTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, short, char, __int64, short, char, __int64);  // 0x2b55d0
private:
    virtual void __cdecl start(void);  // 0x2b56d0
};

class TeamPsoTask
{
private:
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x2b8ee0
};

class TendencyEventTask
{
public:
    __cdecl TendencyEventTask(void);  // 0x2a5ed0
    bool __cdecl Initialize(::Zone *, ::TendencyField::EventData const &);  // 0x2a5f70
    bool __cdecl Initialize(::Zone *, int, unsigned __int64, int, __int64, __int64, char);  // 0x2a6010
private:
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x2a6110
};

class ThrowFieldItemTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, short, short, short, short);  // 0x298040
private:
    virtual void __cdecl start(void);  // 0x298130
};

class TimeAttackRecordResultTask
{
public:
    __cdecl TimeAttackRecordResultTask(void);  // 0x2c5ac0
    virtual __cdecl ~TimeAttackRecordResultTask(void);  // 0x2c5b70
    bool __cdecl Initialize(::Zone *, ::Pc *, char, bool, ::SeasonContentsTimeAttackRecordContainer::SeasonContentsTimeAttackRecordValue const *, bool, ::TimeAttackRecordResultTranResultNotifyInfo const *);  // 0x2c5be0
private:
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x2c5e40
    virtual void __cdecl start(void);  // 0x2c5e80
};

class TransferFactionTask
{
private:
    virtual void __cdecl start(void);  // 0x295540
};

class TurnTask
{
private:
    virtual void __cdecl start(void);  // 0x294970
};

class UnbindRaidDungeonTask
{
public:
    __cdecl UnbindRaidDungeonTask(void);  // 0x2a3c80
    bool __cdecl Initialize(::Zone *, ::Creature *, unsigned __int64, int, ::Inventory::DisposeOrderWithPos *const);  // 0x2a3d30
private:
    virtual void __cdecl start(void);  // 0x2a3e20
};

class UpdateAchievementListTask
{
public:
    virtual __cdecl ~UpdateAchievementListTask(void);  // 0x2a2f90
    bool __cdecl Initialize(::Zone *, ::Pc *, ::AchievementData *);  // 0x2a3010
private:
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x2a30e0
    virtual void __cdecl start(void);  // 0x2a3120
};

class UpdateGuildApplicationRefusalTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, unsigned __int64, unsigned __int64, wchar_t *, char);  // 0x29c450
private:
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x29c530
    virtual void __cdecl start(void);  // 0x29c570
public:
    __cdecl UpdateGuildApplicationRefusalTask(void);  // 0x34f630
};

class UpdateGuildInvitationRefusalTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, unsigned __int64, char);  // 0x29c7c0
private:
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x29c870
    virtual void __cdecl start(void);  // 0x29c8b0
};

class UpdatePcTeamInfoTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, unsigned __int64, unsigned __int64);  // 0x2b8810
private:
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x2b88e0
    virtual void __cdecl start(void);  // 0x2b8920
};

class UseEquippedTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, short, short, short, short, short);  // 0x2cecd0
private:
    virtual void __cdecl start(void);  // 0x2ced70
public:
    __cdecl UseEquippedTask(void);  // 0x34fdc0
};

class UseFieldItemTask
{
public:
    bool __cdecl Initialize(::Zone *const, ::Pc *const, unsigned __int64, short, char);  // 0x2979f0
    bool __cdecl Initialize(::Zone *const, ::Pc *const, ::vector16 const &, short, char);  // 0x297b30
private:
    virtual void __cdecl start(void);  // 0x297c80
public:
    __cdecl UseFieldItemTask(bool);  // 0x34f520
};

class UseGroceryTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, short, short, short, short, short, __int64);  // 0x2961d0
private:
    virtual void __cdecl start(void);  // 0x296280
public:
    __cdecl UseGroceryTask(void);  // 0x34f4c0
};

class UseJumpingCharacterTicketAbortTask
{
private:
    virtual void __cdecl start(void);  // 0x2db7c0
};

class UseJumpingCharacterTicketChangeJumpingStateTask
{
private:
    virtual void __cdecl start(void);  // 0x2db6a0
};

class UseJumpingCharacterTicketFinishTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, unsigned __int64);  // 0x2dba40
private:
    virtual void __cdecl start(void);  // 0x2dbb80
};

class UseJumpingCharacterTicketStartTask
{
private:
    virtual void __cdecl failProcess(short);  // 0x2d9bd0
    virtual void __cdecl start(void);  // 0x2d9c60
};

class UseJumpingCharacterTicketTakeRewardOkTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Pc *, ::AccountInventoryJumpingCharacter2TicketTran *, ::TryTakeJumpingCharacter2RewardOkParam &);  // 0x2dad60
private:
    virtual void __cdecl start(void);  // 0x2dae40
};

class UseJumpingCharacterTicketTask
{
public:
    __cdecl UseJumpingCharacterTicketTask(void);  // 0x180b20
    virtual __cdecl ~UseJumpingCharacterTicketTask(void);  // 0x2d9980
    bool __cdecl Initialize(::Zone *, ::Pc *, ::AccountInventoryJumpingCharacter2TicketTran *);  // 0x2d99e0
private:
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x2d9b30
protected:
    virtual void __cdecl failProcess(short);  // 0x2d9b70
};

class UseJumpingCharacterTicketTryConsumeTicketOkTask
{
private:
    virtual void __cdecl start(void);  // 0x2da3c0
};

class WarpToMentoringMemberTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, unsigned __int64, short);  // 0x2d6e40
private:
    virtual void __cdecl start(void);  // 0x2d6f30
};

