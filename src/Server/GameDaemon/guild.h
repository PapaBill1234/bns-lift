// guild.h: guild.cpp, guild.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"
#include "../BloodLib/include/Lock.h"
#include "guildbank.h"
#include "guilduniform.h"

class Guild
{
public:
    struct MeetingPlace {};
    struct RankingRewardInfo {};
    struct Member
    {
        unsigned __int64 pcId;  // +0 (0x0)
        unsigned __int64 pcDbId;  // +8 (0x8)
        wchar_t name[33];  // +16 (0x10)
        short level;  // +82 (0x52)
        char faction2;  // +84 (0x54)
        short masteryLevel;  // +86 (0x56)
        short race;  // +88 (0x58)
        short job;  // +90 (0x5A)
        char grade;  // +92 (0x5C)
        __int64 registrationTime;  // +96 (0x60)
        __int64 logoutTime;  // +104 (0x68)
        short worldId;  // +112 (0x70)
        int geoZone;  // +116 (0x74)
        short x;  // +120 (0x78)
        short y;  // +122 (0x7A)
        short z;  // +124 (0x7C)
        __int64 qqId;  // +128 (0x80)
    };
    struct WaitingMember
    {
        unsigned __int64 pcDbId;  // +0 (0x0)
        wchar_t name[33];  // +8 (0x8)
        short level;  // +74 (0x4A)
        char faction2;  // +76 (0x4C)
        short masteryLevel;  // +78 (0x4E)
        short race;  // +80 (0x50)
        short job;  // +82 (0x52)
        short worldId;  // +84 (0x54)
        wchar_t requestorName[33];  // +86 (0x56)
        __int64 reserveTimestamp;  // +152 (0x98)
        bool confirmReserved;  // +160 (0xA0)
        __int64 qqId;  // +168 (0xA8)
    };
public:
    __cdecl Guild(void);  // 0xe0910
    virtual __cdecl ~Guild(void);  // 0xe0c30
    bool __cdecl Initialize(::LoadGuildInfo const *);  // 0xe0ea0
    bool __cdecl InitializeGuildBankData(void);  // 0xe11b0
    bool __cdecl InitializeGuildUniformList(short, ::GuildUniformInfo *const);  // 0xe1260
    bool __cdecl InitializeGuildCombatRecords(::FragmentPacketConcatenater *);  // 0xe15e0
    bool __cdecl InitializeGuildJoinTicketList(::FragmentPacketConcatenater *);  // 0xe1800
    bool __cdecl SetRenameGuildInProgress(bool);  // 0xe1a50
    void __cdecl GetGuildInfoForGameLog(::GuildInfoForGameLog &);  // 0xe1ac0
    __int64 __cdecl GetGuildRegistrationTime(unsigned __int64);  // 0xe1b40
    bool __cdecl AddGuildMember(unsigned __int64, unsigned __int64, wchar_t const *, short, char, short, short, short, char, __int64, __int64, short, int, short, short, short, __int64);  // 0xe1c40
    bool __cdecl JoinGuildReq(unsigned __int64, unsigned __int64, short &);  // 0xe1ee0
    bool __cdecl JoinGuild(unsigned __int64, char, __int64, __int64);  // 0xe2380
    bool __cdecl EnterWorldGuildMember(unsigned __int64);  // 0xe2ce0
    bool __cdecl LeaveWorldGuildMember(unsigned __int64);  // 0xe3040
    bool __cdecl RetrieveGuildInfo(unsigned __int64);  // 0xe31c0
    bool __cdecl RetrieveGuildMembers(unsigned __int64);  // 0xe3660
    bool __cdecl LevelUpGuildMember(unsigned __int64, char, char, char);  // 0xe38f0
    bool __cdecl UpdateGuildMemberFaction2(unsigned __int64, char);  // 0xe3bc0
    bool __cdecl SetZoneGuildMember(unsigned __int64, ::EnterReason);  // 0xe3cf0
    bool __cdecl UpdateGuildLevelOkFromCache(::UpdateGuildLevelInitParam &);  // 0xe3ff0
    short __cdecl UpdateGuildLevelReq(unsigned __int64, char);  // 0xe4460
    bool __cdecl UpdateGuildLevelDebugReq(unsigned __int64, char);  // 0xe4c40
    bool __cdecl ReserveDistruction(unsigned __int64);  // 0xe5190
    bool __cdecl ReserveDistructionByBuilder(unsigned __int64, wchar_t const *);  // 0xe59b0
    void __cdecl ResetLevelUp(void);  // 0xe5f90
    static __int64 __cdecl GetBanishOpenGuildMemberCountResetTime(__int64, int);  // 0xe5fd0
    bool __cdecl BanishGuildMember(unsigned __int64, char, wchar_t *, short &);  // 0xe6050
    bool __cdecl LeaveGuild(unsigned __int64, wchar_t const *, short &);  // 0xe72a0
    bool __cdecl LeaveGuildOk(unsigned __int64, unsigned __int64, short, ::GuildFlagBearerInfo &, char, __int64);  // 0xe79f0
    bool __cdecl RemoveGuildMember(unsigned __int64, short, ::GuildFlagBearerInfo &, char, __int64);  // 0xe7b40
    bool __cdecl RemoveWaitingMember(unsigned __int64);  // 0xe7f20
    int __cdecl GetMembers(unsigned __int64 *const);  // 0xe7f70
    unsigned __int64 __cdecl GetGuildMemberPcDbId(wchar_t const *);  // 0xe8050
    bool __cdecl IsMemberByPcDbId(unsigned __int64);  // 0xe80e0
    int __cdecl GetGuildJoinRenewalInviteGuildMemberManagers(unsigned __int64 *const);  // 0xe8170
    int __cdecl GetGuildJoinRenewalAcceptGuildMemberManagers(unsigned __int64 *const);  // 0xe8270
    bool __cdecl GetGuildMemberName(int, int, wchar_t *const);  // 0xe8370
    bool __cdecl GetMemberIndexByPcDbId(__int64, int &);  // 0xe8440
    void __cdecl BroadcastPacket(::Packet *);  // 0xe84c0
    bool __cdecl BindingQQGroup(unsigned __int64, __int64, char);  // 0xe8680
    bool __cdecl SetQQGroupMemberInfo(unsigned __int64, __int64, char);  // 0xe8870
    bool __cdecl UnbindingQQGroup(unsigned __int64);  // 0xe8fa0
    bool __cdecl QQGroupMemberChangeStatus(unsigned __int64, __int64, __int64, char);  // 0xe9150
    void __cdecl BroadcastLeaveGuild(char, wchar_t const *, short, ::GuildFlagBearerInfo &, char, __int64);  // 0xe93a0
    bool __cdecl EditNotificationMessageReq(unsigned __int64, wchar_t const *, short &);  // 0xe9650
    bool __cdecl EditNotificationMessageRes(unsigned __int64);  // 0xe9980
    bool __cdecl RetrieveGuildMemberPermission(unsigned __int64, short &);  // 0xe9a80
    bool __cdecl EditGuildMemberPermissionReq(unsigned __int64, unsigned int, unsigned int, unsigned int, unsigned int, short &);  // 0xe9c80
    bool __cdecl EditGuildMemberPermissionRes(unsigned __int64, short &);  // 0xea060
    bool __cdecl JoinGuildFail(unsigned __int64, short);  // 0xea2c0
    bool __cdecl JoinGuildByInvitationFail(unsigned __int64, short);  // 0xea500
    bool __cdecl GetReserveDestruction(void);  // 0xea850
    bool __cdecl TryAcceptGuildApplication(unsigned __int64, short &, short &);  // 0xea940
    bool __cdecl TryJoinGuildRenewal(unsigned __int64, short, __int64);  // 0xeade0
    bool __cdecl FinishJoinGuildRenewal(unsigned __int64, short, __int64, char, __int64);  // 0xeba80
    bool __cdecl CancelJoinGuildRenewal(unsigned __int64, short);  // 0xec670
    void __cdecl UpdateGuildApplicationRefusal(bool);  // 0xecbf0
    unsigned __int64 __cdecl FindByGuildMemberIndex(int);  // 0xecce0
    bool __cdecl InviteGuildRelay(unsigned __int64, wchar_t const *, char, short &);  // 0xecdf0
    bool __cdecl ConfirmInvitation(unsigned __int64, unsigned __int64, short &);  // 0xedda0
    void __cdecl CancelInvitation(unsigned __int64, short);  // 0xee230
    bool __cdecl RejectInvitation(unsigned __int64);  // 0xee410
    bool __cdecl DelegateGuildLeaderRelay(unsigned __int64, char, wchar_t const *, short &);  // 0xeeea0
    bool __cdecl DelegateGuildLeaderConfirm(unsigned __int64, short &);  // 0xef400
    bool __cdecl DelegateGuildLeaderConfirmRes(unsigned __int64, short &);  // 0xef6d0
    bool __cdecl DelegateGuildLeaderForcibly(unsigned __int64, char, wchar_t const *, short &);  // 0xefa00
    bool __cdecl DelegateGuildLeaderByBuilder(unsigned __int64, wchar_t const *);  // 0xf0090
    bool __cdecl RenameGuildMember(unsigned __int64, wchar_t const *);  // 0xf0360
    bool __cdecl SetGuildMeetingPlace(short, unsigned int, ::vector16 &, short);  // 0xf0460
    bool __cdecl GetGuildMeetingPlace(::Guild::MeetingPlace *);  // 0xf05d0
    bool __cdecl RenameGuild(wchar_t const *, __int64);  // 0xf06e0
    bool __cdecl BanishGuildMemberByBuilder(unsigned __int64, wchar_t *, short &);  // 0xf08b0
    bool __cdecl RejectGuildLeader(unsigned __int64, short &);  // 0xf16f0
    void __cdecl ResetDelegate(unsigned __int64, short);  // 0xf18c0
    bool __cdecl ChangeGuildMemberGrade(unsigned __int64, char, wchar_t const *, char, short &);  // 0xf1a30
    bool __cdecl ChangeGuildMemberGradeOk(unsigned __int64, char, short &);  // 0xf1fe0
    void __cdecl ChangeGuildMemberGradeFail(unsigned __int64, short);  // 0xf2190
    void __cdecl BroadcastChangeGuildMemberGrade(char, wchar_t const *, short, short);  // 0xf2260
    void __cdecl BroadcastDelegateGuildLeader(char, wchar_t const *);  // 0xf23b0
    void __cdecl BroadcastRenameGuildMember(char, wchar_t const *);  // 0xf24e0
    void __cdecl BroadcastCallGuildNotify(int);  // 0xf2610
    void __cdecl BroadcastEditGuildNotificationMessage(wchar_t const *);  // 0xf2790
    void __cdecl BroadcastJoinGuild(char, wchar_t const *, short, char, short, short, short, char, __int64, int, short, short, short);  // 0xf28b0
    void __cdecl BroadcastSendGuildApplicationNotify(unsigned __int64, __int64, wchar_t *, short, short, short);  // 0xf2aa0
    void __cdecl BroadcastCancelGuildApplicationNotify(unsigned __int64, short);  // 0xf2bf0
    void __cdecl BroadcastRejectGuildApplicationOk(unsigned __int64, short);  // 0xf2d00
    void __cdecl BroadcastAcceptGuildApplicationOk(unsigned __int64, __int64);  // 0xf2e10
    void __cdecl BroadcastSendGuildInvitationOk(unsigned __int64, __int64, wchar_t *, short, short, short);  // 0xf2f20
    void __cdecl BroadcastCancelGuildInvitationOk(unsigned __int64, short);  // 0xf3070
    void __cdecl BroadcastRejectGuildInvitationNotify(unsigned __int64, short);  // 0xf3180
    void __cdecl BroadcastUpdateGuildApplicationRefusal(wchar_t *, bool);  // 0xf3290
    void __cdecl BroadcastLoginGuildMember(char, wchar_t const *, short, char, short, short, short, char, __int64, int, short, short, short);  // 0xf33a0
    void __cdecl BroadcastEditedGuildMemberPermission(void);  // 0xf35a0
    void __cdecl BroadcastUpdateGuildLevel(char, char, ::GuildBank::GuildBankItem *const);  // 0xf3700
    void __cdecl BroadcastDepositInGuildBank(wchar_t const *, short, ::GuildBank::GuildBankItem const *const);  // 0xf3900
    void __cdecl BroadcastAbandonGuildCraft(unsigned __int64);  // 0xf3ba0
    void __cdecl BroadcastContractGuildUniform(::ContractGuildUniformOkParam const *);  // 0xf3cf0
    void __cdecl BroadcastDonationGuildUniformMaterial(unsigned __int64, wchar_t const *, unsigned int, short, __int64);  // 0xf4210
    void __cdecl BroadcastAbandonGuildUniform(unsigned __int64);  // 0xf43c0
    void __cdecl BroadcastFinishDonationGuildUniform(unsigned __int64);  // 0xf4500
    void __cdecl BroadcastMakeGuildUniform(unsigned __int64, __int64, __int64);  // 0xf4640
    void __cdecl BroadcastFinishMakeGuildUniform(unsigned __int64);  // 0xf47e0
    void __cdecl BroadcastRegisterGuildUniform(unsigned __int64);  // 0xf4950
    void __cdecl BroadcastPutOnGuildUniform(unsigned __int64, __int64);  // 0xf4ac0
    void __cdecl BroadcastRenameGuild(unsigned __int64, wchar_t const *, __int64);  // 0xf4c40
    void __cdecl BroadcastDepositGuildBankByManager(unsigned int, short, __int64);  // 0xf4e90
    void __cdecl BroadcastSubtractGuildBankByManager(unsigned int, short, __int64);  // 0xf4fe0
    void __cdecl BroadcastRenameGuildByManager(wchar_t const *);  // 0xf5130
    void __cdecl BroadcastLogoutGuildmember(char, short, char, short);  // 0xf5270
    void __cdecl BroadcastLevelUpGuildMember(char, short, char, short);  // 0xf5350
    void __cdecl BroadcastTransitZoneGuildMember(char, int, short, short, short);  // 0xf5430
    void __cdecl BroadcastUpdateGuildMemberFaction2(char, char);  // 0xf5520
    bool __cdecl FinishGuildCraftAssentForDebug(unsigned __int64, int);  // 0xf55e0
    short __cdecl EnableDepositGuildBank(unsigned __int64, int, short, __int64);  // 0xf5810
    bool __cdecl EnableContractGuildCraft(unsigned __int64, int, bool, wchar_t const *, bool, bool);  // 0xf5910
    short __cdecl EnableAssentGuildCraft(unsigned __int64, unsigned __int64, char, short, char &);  // 0xf5e80
    short __cdecl EnableMakeGuildCraft(unsigned __int64, unsigned __int64);  // 0xf6100
    short __cdecl EnableDonateGuildCraftNormalMaterial(unsigned __int64, unsigned __int64, int, short, int, short &);  // 0xf65a0
    short __cdecl EnableDonateGuildCraftBrandMaterial(unsigned __int64, unsigned __int64, int, char, int, short &);  // 0xf6960
    short __cdecl EnableTakeGuildCraft(unsigned __int64, unsigned __int64, int, unsigned int &, short &);  // 0xf6d30
    void __cdecl EnableFinishGuildCraft(unsigned __int64);  // 0xf6fa0
    short __cdecl AbandonGuildCraft(unsigned __int64, unsigned __int64, unsigned __int64);  // 0xf70f0
    short __cdecl EnableContractGuildUniform(::Pc const *, unsigned __int64, char const *const, int const *const, char *const, int &, short &, ::GuildUniform::Material *const, short &, ::GuildBank::GuildBankItem *const);  // 0xf71f0
    short __cdecl EnableDonateGuildUniform(::Pc const *, unsigned __int64, unsigned int, short, short, short &);  // 0xf7650
    short __cdecl AbandonGuildUniform(unsigned __int64, unsigned __int64, unsigned __int64);  // 0xf7920
    short __cdecl EnableMakeGuildUniform(::Pc *, unsigned __int64);  // 0xf7a20
    void __cdecl EnableFinishMakeGuildUniform(unsigned __int64);  // 0xf8120
    short __cdecl EnableRegisterGuildUniform(::Pc *, unsigned __int64);  // 0xf8310
    short __cdecl EnableRegisterGuildUniformWithDeletion(::Pc *, unsigned __int64, unsigned __int64);  // 0xf8b40
    short __cdecl EnableIncreaseUniformRegistrationQuota(::Pc const *, char, unsigned int, short, short, short &);  // 0xf9600
    short __cdecl EnablePutOnGuildUniform(::Pc *, unsigned __int64);  // 0xf99f0
private:
    bool __cdecl isFullWaitingGuildMember(void) const;  // 0xfa2d0
    void __cdecl clearWaitingList(void);  // 0xfa350
    bool __cdecl addWaitingGuildMember(unsigned __int64, unsigned __int64, short, wchar_t const *, short, char, short, short, short, wchar_t const *, __int64, bool);  // 0xfa4a0
    bool __cdecl delWaitingGuildMember(unsigned __int64);  // 0xfa670
    int __cdecl findByPcDbId(unsigned __int64);  // 0xfa740
    int __cdecl findByPcName(wchar_t const *);  // 0xfa770
    int __cdecl findByPcDbIdInWaiting(unsigned __int64);  // 0xfa7f0
    bool __cdecl checkPermissionGuild20(int, char);  // 0xfa830
    bool __cdecl isFull(void);  // 0xfa870
public:
    bool __cdecl FetchGuildInfo(::FragmentPacket &);  // 0xfa920
    bool __cdecl FetchGuildMembers(::FragmentPacket &);  // 0xfaa60
    bool __cdecl ComposeGuildSeasonContentsInfo(char const *const, char, ::FragmentPacket &);  // 0xfacc0
    int const __cdecl GetCombatRatingScore(char);  // 0xfaf40
    void __cdecl GetCombatInfo(char, int &, int &);  // 0xfb020
    bool __cdecl DepositInGuildBankOkFromCache(unsigned __int64, wchar_t const *, short, ::GuildBank::GuildBankItem const *const, __int64 *const);  // 0xfb120
    bool __cdecl AbandonGuildCraftOkFromCache(unsigned __int64, unsigned __int64);  // 0xfb250
    __int64 __cdecl EnableDepositCount(int, short);  // 0xfb8a0
private:
    bool __cdecl isFullNormalGuildCraft(char);  // 0xfb9b0
    bool __cdecl contractableGuildUniform(int &);  // 0xfba50
    bool __cdecl registrableGuildUniform(void);  // 0xfbaf0
    bool __cdecl addGuildUniformCost(unsigned int, short, int, short &, ::GuildBank::GuildBankItem *const);  // 0xfbb80
    bool __cdecl addGuildUniformMaterial(unsigned int, short, unsigned int, short &, ::GuildUniform::Material *const);  // 0xfbcc0
    bool __cdecl calculateGuildUniformParam(bool, int, int, int, short &, ::GuildUniform::Material *const, short &, ::GuildBank::GuildBankItem *const);  // 0xfbdd0
    bool __cdecl getCurrentGuildUniform(char *const);  // 0xfc010
    bool __cdecl analyzeGuildUniformParamTypes(bool, unsigned __int64, char const *const, int const *const, char *const, short &, ::GuildUniform::Material *const, short &, ::GuildBank::GuildBankItem *const);  // 0xfc100
    bool __cdecl checkGuildUniformParamTypes(char const *const, int const *const, char const *const);  // 0xfc5a0
public:
    bool __cdecl IsGuildBankItem(unsigned int, short);  // 0xfc980
    bool __cdecl EnableDepositGuildBankByManager(unsigned int, short, __int64, __int64 &);  // 0xfca70
    bool __cdecl EnableWithdrawGuildBankByManager(unsigned int, short, __int64);  // 0xfcca0
    bool __cdecl RenameGuildByManagement(wchar_t const *);  // 0xfce60
    bool __cdecl BanishGuildMemberByManager(unsigned __int64, short &);  // 0xfcfb0
    bool __cdecl DelegateGuildLeaderByManager(unsigned __int64, short &);  // 0xfd180
    bool __cdecl JoinGuildByManager(unsigned __int64, wchar_t *, unsigned __int64, short, short, char, char, short, short, short, short &);  // 0xfd340
private:
    char __cdecl getGuildCraftRecipeUsableCount(char, char);  // 0xfd760
public:
    bool __cdecl CheckPermissionGuild20(unsigned __int64, char);  // 0xfd850
    bool __cdecl ContractGuildCraftOkFromCache(unsigned __int64, ::ContractOkParam *, __int64 *const);  // 0xfda30
    bool __cdecl AssentGuildCraftOkFromCache(unsigned __int64, ::AssentOkParam *);  // 0xfdc20
    bool __cdecl DonateGuildCraftNormalMaterialOkFromCache(unsigned __int64, ::DonateNormalMaterialOkParam *);  // 0xfe0d0
    bool __cdecl DonateGuildCraftBrandMaterialOkFromCache(unsigned __int64, ::DonateBrandMaterialOkParam *);  // 0xfe300
    bool __cdecl MakeGuildCraftOkFromCache(unsigned __int64, ::MakeGuildCraftOkParam *);  // 0xfe540
    bool __cdecl FinishGuildCraftFromSystem(unsigned __int64);  // 0xfea20
    bool __cdecl TakeGuildCraftOkFromCache(unsigned __int64, ::TakeGuildCraftOkParam *);  // 0xfece0
    bool __cdecl ContractGuildUniformOkFromCache(::ContractGuildUniformOkParam const *, __int64 *const);  // 0xff250
    bool __cdecl DonateGuildUniformOkFromCache(::DonateGuildUniformMaterialOkParam const *);  // 0xff440
    bool __cdecl AbandonGuildUniformOkFromCache(unsigned __int64, unsigned __int64);  // 0xff690
    bool __cdecl MakeGuildUniformOkFromCache(::MakeGuildUniformOkParam const *);  // 0xffac0
    bool __cdecl FinishGuildUniformFromSystem(unsigned __int64);  // 0xfff50
    bool __cdecl RegisterGuildUniformOkFromCache(::RegisterGuildUniformOkParam const *);  // 0x100150
    bool __cdecl PutOnGuildUniformOkFromCache(::PutOnGuildUniformOkParam const *);  // 0x1004c0
    bool __cdecl RegisterGuildUniformWithDeletionOkFromCache(::RegisterGuildUniformWithDeletionOkParam const *);  // 0x1007f0
    short __cdecl EnableChangeGuildFlagBearer(::Pc *, char, wchar_t const *);  // 0x100c40
    bool __cdecl TakeRankingRewardOkFromCache(::TakeRankingRewardOkParam const *);  // 0x101120
    bool __cdecl TakeRankingBuffReward(::RankingResultInfo const *);  // 0x101560
    bool __cdecl EnableRetrieveRankingInfo(char, ::LatestRankingInfo &);  // 0x1018d0
    void __cdecl TryUpdateCombatRecord(::TryUpdateCombatRecordParam &);  // 0x101990
    void __cdecl UpdateCombatRecord(char, unsigned __int64, __int64);  // 0x101f00
    void __cdecl ResetCombatRecord(char);  // 0x1022a0
    void __cdecl InitializeCombatRecord(::SeasonContentsGuildCombatRecord const &);  // 0x1023b0
    void __cdecl FetchRankingRewardList(::FragmentPacket &);  // 0x102590
    bool __cdecl UpdateFlagBearerOkFromCache(::UpdateGuildFlagBearerParam const *);  // 0x102720
    void __cdecl BroadcastContractGuildCraft(unsigned __int64, ::ContractOkParam *);  // 0x103040
    void __cdecl BroadcastAssentGuildCraft(unsigned __int64, char, wchar_t *);  // 0x1032e0
    void __cdecl BroadcastDonationGuildCraftNormalMaterial(unsigned __int64, wchar_t const *, unsigned int, short, __int64);  // 0x103460
    void __cdecl BroadcastDonationGuildCraftBrandMaterial(unsigned __int64, wchar_t const *, unsigned int, short, unsigned __int64, char, __int64);  // 0x103620
    void __cdecl BroadcastFinishDonationGuildCraft(unsigned __int64);  // 0x103810
    void __cdecl BroadcastMakeGuildCraft(unsigned __int64, __int64, __int64, int, char, __int64);  // 0x103960
    void __cdecl BroadcastFinishGuildCraft(unsigned __int64);  // 0x103b80
    void __cdecl BroadcastTakeGuildCraft(unsigned __int64, wchar_t *, short);  // 0x103cd0
    void __cdecl BroadcastRegisterGuildUniformWithDeletion(unsigned __int64, unsigned __int64, bool, __int64);  // 0x103e50
    void __cdecl BroadcastIncreaseGuildUniformRegistrationQuota(unsigned __int64, wchar_t const *, short);  // 0x103fe0
    void __cdecl BroadcastTakeRankingRewardForGuildBuff(::Guild::RankingRewardInfo const *);  // 0x104160
    void __cdecl BroadcastTakeRankingRewardForGuildBank(char, int, char, int, char, ::GuildBank::GuildBankItem const *const);  // 0x104700
    void __cdecl BroadcastChangedGuildRankingInfo(char, int);  // 0x104ba0
    void __cdecl BroadcastChangedGuildCombatRecord(::SeasonContentsGuildCombatRecordEntry *, ::Packet *);  // 0x104cb0
    bool __cdecl GetGuildUniformParam(char *const);  // 0x34f3b0
private:
    // PDB layout (size 0x8000). The vfptr is at +0. Only the members that the lifted bodies use are declared.
    char lift_pad_8[0x18];  // ❓ no PDB name: base +8 to +0x17 and _combatRecordContext (+0x18) are not declared yet
    ::Guild::Member _guildMember[100];  // +32 (0x20)
    int _guildMemberCount;  // +13632 (0x3540)
    ::Guild::WaitingMember _waitingGuildMember[100];  // +13640 (0x3548)
    int _waitingGuildMemberCount;  // +31240 (0x7A08)
    char lift_pad_7a0c[0x2C8];  // ❓ no PDB name: members +0x7A0C to +0x7CD3 are not declared yet
    unsigned int _permission[5];  // +31956 (0x7CD4) (❓ PDB type 0xBCBC not looked up; the original reads 32-bit elements, grade 1 to 5)
    char lift_pad_7ce8[0x318];  // ❓ no PDB name: members +0x7CE8 to +0x7FFF are not declared yet
};
static_assert(sizeof(Guild::Member) == 0x88, "sizeof Guild::Member");
static_assert(sizeof(Guild::WaitingMember) == 0xB0, "sizeof Guild::WaitingMember");
static_assert(sizeof(Guild) == 0x8000, "sizeof Guild");

class GuildIdManager
{
public:
    struct GuildIdNode
    {
        unsigned __int64 guildId;  // +0 (0x0)
        ::GuildIdManager::GuildIdNode *prev;  // +8 (0x8)
        ::GuildIdManager::GuildIdNode *next;  // +16 (0x10)
    };
public:
    __cdecl ~GuildIdManager(void);  // 0x104e60
    void __cdecl Initialize(void);  // 0x104f10
    bool __cdecl PushGuildId(unsigned __int64 &);  // 0x104f90
    unsigned __int64 __cdecl PopGuildId(void);  // 0x105030
private:
    // PDB layout (size 0x38).
    ::GuildIdManager::GuildIdNode *head;  // +0 (0x0)
    ::GuildIdManager::GuildIdNode *tail;  // +8 (0x8)
    ::CriticalSection GuildIdMgrCS;  // +16 (0x10)
};
static_assert(sizeof(GuildIdManager) == 0x38, "sizeof GuildIdManager");

struct SeasonContentsRankingLogInfo
{
public:
    static bool __cdecl IsUsePrimaryScoreHighPart(char);  // 0x27610
    void __cdecl Set(char, bool, int, int);  // 0x27720
    void __cdecl Get(int &, char &);  // 0x96d40
};

