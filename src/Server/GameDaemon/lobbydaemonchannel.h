// lobbydaemonchannel.h: lobbydaemonchannel.cpp, lobbydaemonchannel.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class LobbyDaemonChannel
{
public:
    void __cdecl Initialize(short);  // 0x13e730
    bool __cdecl SendHello(void);  // 0x13e870
    bool __cdecl ProcHello(bool, ::Packet const *);  // 0x13e9e0
};

class LobbyDaemonChannelManager
{
public:
    bool __cdecl Initialize(short, short *const);  // 0x14b220
    void __cdecl Destroy(void);  // 0x14b5c0
private:
    ::LobbyDaemonChannel * __cdecl acquire(unsigned int);  // 0x14b730
public:
    bool __cdecl Send(short, char const *, ...);  // 0x14b850
    bool __cdecl Send(short, ::Packet const *);  // 0x14b940
    bool __cdecl SendCreateCharacterOk(short, __int64, ::FsdShowcaseRecord const &);  // 0x14ba30
    bool __cdecl SendChangeCharacterAppearanceOk(short, __int64, ::FsdShowcaseRecord const &);  // 0x14bbb0
    bool __cdecl SendChangeCharacterSexOk(short, __int64, ::FsdShowcaseRecord const &);  // 0x14bd20
    bool __cdecl SendChangeCharacterRaceOk(short, __int64, ::FsdShowcaseRecord const &);  // 0x14be90
    bool __cdecl SendUpdateCharacterDataReq(short, __int64, unsigned __int64, __int64, ::FsdShowcaseRecord const &);  // 0x14c000
    bool __cdecl SendUpdateAccountDataReq(short, __int64, unsigned __int64, __int64, int, __int64, ::TimeBasedPlayInfoList &, ::AccountExpInfo const *, ::std::vector< ::AccountContentQuota, ::StlAllocator< ::AccountContentQuota, 2> > *, ::std::vector< ::AccountRecycleTime, ::StlAllocator< ::AccountRecycleTime, 2> > *);  // 0x14c190
    bool __cdecl SendUpdateAccountExpReq(short, __int64, unsigned __int64, __int64, ::AccountExpInfo const &);  // 0x14c6b0
    bool __cdecl SendUpdateAccountContentQuotaReq(short, __int64, unsigned __int64, __int64, ::AccountContentQuota const &);  // 0x14c880
    bool __cdecl SendUpdateAccountRecycleTimeReq(short, __int64, unsigned __int64, __int64, ::AccountRecycleTime const &);  // 0x14cb20
    bool __cdecl SendTryRegisterGuildName(short, unsigned __int64, char, wchar_t const *);  // 0x14cda0
    bool __cdecl SendFinishRegisterGuild(short, unsigned __int64, unsigned __int64);  // 0x14cf20
    bool __cdecl SendCancelRegisterGuild(short, unsigned __int64, unsigned __int64);  // 0x14d090
    bool __cdecl SendTryRenameGuild(short, unsigned __int64, unsigned __int64, char, wchar_t const *);  // 0x14d200
    bool __cdecl SendFinishRenameGuildNotify(short, unsigned __int64, unsigned __int64, unsigned __int64);  // 0x14d3d0
    bool __cdecl SendCancelRenameGuildNotify(short, unsigned __int64);  // 0x14d560
    bool __cdecl SendDeleteGuildNotify(short, unsigned __int64, unsigned __int64);  // 0x14d6a0
    bool __cdecl SendSetAppDataNotify(short, unsigned __int64, short, ::KeyValueRecord const *const);  // 0x14d810
    bool __cdecl SendFriendMessage(short, unsigned __int64, wchar_t const *, short, ::KeyValueRecord const *const);  // 0x14dab0
    bool __cdecl SendActivateGrade(short, unsigned __int64, char, int);  // 0x14dd30
    bool __cdecl SendDepositGameMileage(short, ::MileageDepositContext const *, bool);  // 0x14de60
    bool __cdecl SendAuctionBid(short, unsigned __int64, ::id128 &, short, __int64);  // 0x14e210
    bool __cdecl SendServiceOpen(short, short);  // 0x14e400
    bool __cdecl SendBoastEventInWorld(short, short, wchar_t const *, short, __int64, __int64);  // 0x14e530
    bool __cdecl SendBoastEventInWorld(short, short, wchar_t const *, short);  // 0x14e8b0
    bool __cdecl SendUpdateJumpingCharacterState(short, __int64, unsigned __int64, __int64);  // 0x14ea00
    bool __cdecl SendSecondPasswordGetStatus(short, unsigned __int64, unsigned __int64, char);  // 0x14eb20
    bool __cdecl SendSecondPasswordIsVerified(short, unsigned __int64, unsigned __int64, char, char);  // 0x14ec60
};

class LobbyDaemonSessionHandler
{
public:
    virtual bool __cdecl OnAccept(::Session const *) const;  // 0x13e280
    virtual bool __cdecl OnConnect(::Session const *, bool) const;  // 0x13e2c0
    virtual void __cdecl OnClose(::Session const *, bool) const;  // 0x13e4f0
    virtual bool __cdecl PacketHandler(::Session const *, ::Packet const *) const;  // 0x13e6d0
};

bool __cdecl HandleLobbyGame_HelloOk(::Session const *, ::Packet const *);  // 0x13ec00
bool __cdecl HandleLobbyGame_HelloFail(::Session const *, ::Packet const *);  // 0x13ed30
bool __cdecl HandleLobbyGame_NPPresenceKickNotify(::Session const *, ::Packet const *);  // 0x13ee50
bool __cdecl HandleLobbyGame_EnterWorldOk(::Session const *, ::Packet const *);  // 0x13efc0
bool __cdecl HandleLobbyGame_EnterWorldFail(::Session const *, ::Packet const *);  // 0x13fe30
bool __cdecl HandleLobbyGame_LeaveWorldOk(::Session const *, ::Packet const *);  // 0x13ff90
bool __cdecl HandleLobbyGame_LeaveWorldFail(::Session const *, ::Packet const *);  // 0x1400f0
bool __cdecl HandleLobbyGame_CloseSessionNotify(::Session const *, ::Packet const *);  // 0x140250
bool __cdecl HandleLobbyGame_KickReq(::Session const *, ::Packet const *);  // 0x1402a0
bool __cdecl HandleLobbyGame_StopPlayNotify(::Session const *, ::Packet const *);  // 0x140610
bool __cdecl HandleLobbyGame_CreateCharacterReq(::Session const *, ::Packet const *);  // 0x140730
bool __cdecl HandleLobbyGame_DeleteCharacterReq(::Session const *, ::Packet const *);  // 0x141130
bool __cdecl HandleLobbyGame_RestoreCharacterReq(::Session const *, ::Packet const *);  // 0x141460
bool __cdecl HandleLobbyGame_DeleteCharacterCompleteNotify(::Session const *, ::Packet const *);  // 0x1417c0
bool __cdecl HandleLobbyGame_StartChargeOk(::Session const *, ::Packet const *);  // 0x141880
bool __cdecl HandleLobbyGame_StartChargeFail(::Session const *, ::Packet const *);  // 0x141ab0
bool __cdecl HandleLobbyGame_StopChargeOk(::Session const *, ::Packet const *);  // 0x141c40
bool __cdecl HandleLobbyGame_StopChargeFail(::Session const *, ::Packet const *);  // 0x141ce0
bool __cdecl HandleLobbyGame_ApplyNewChargeItemNotify(::Session const *, ::Packet const *);  // 0x141e70
bool __cdecl HandleLobbyGame_UpdateChargeRemainTimeNotify(::Session const *, ::Packet const *);  // 0x142070
bool __cdecl HandleLobbyGame_UpdateCharacterDataOk(::Session const *, ::Packet const *);  // 0x142190
bool __cdecl HandleLobbyGame_UpdateCharacterDataFail(::Session const *, ::Packet const *);  // 0x142200
bool __cdecl HandleLobbyGame_UpdateAccountDataOk(::Session const *, ::Packet const *);  // 0x142360
bool __cdecl HandleLobbyGame_UpdateAccountDataFail(::Session const *, ::Packet const *);  // 0x1423e0
bool __cdecl HandleLobbyGame_TryRegisterGuildOk(::Session const *, ::Packet const *);  // 0x142540
bool __cdecl HandleLobbyGame_TryRegisterGuildFail(::Session const *, ::Packet const *);  // 0x142720
bool __cdecl HandleLobbyGame_TryRenameGuildOk(::Session const *, ::Packet const *);  // 0x142920
bool __cdecl HandleLobbyGame_TryRenameGuildFail(::Session const *, ::Packet const *);  // 0x142b60
bool __cdecl HandleLobbyGame_AccountInventoryNotify(::Session const *, ::Packet const *);  // 0x142da0
bool __cdecl HandleLobbyGame_ChangeCharacterAppearanceReq(::Session const *, ::Packet const *);  // 0x143270
bool __cdecl HandleLobbyGame_ChangeCharacterSexReq(::Session const *, ::Packet const *);  // 0x143cc0
bool __cdecl HandleLobbyGame_ChangeCharacterRaceReq(::Session const *, ::Packet const *);  // 0x1447b0
bool __cdecl HandleLobbyGame_RenameCharacterReq(::Session const *, ::Packet const *);  // 0x1452e0
bool __cdecl HandleLobbyGame_ExtendJumpingCharacterCreationQuotaWithAccountInventoryItemOk(::Session const *, ::Packet const *);  // 0x145690
bool __cdecl HandleLobbyGame_ExtendJumpingCharacterCreationQuotaWithAccountInventoryItemFail(::Session const *, ::Packet const *);  // 0x145860
bool __cdecl HandleLobbyGame_UpgradeJumpingCharacterStateWithCreationQuotaOk(::Session const *, ::Packet const *);  // 0x145a20
bool __cdecl HandleLobbyGame_UpgradeJumpingCharacterStateWithCreationQuotaFail(::Session const *, ::Packet const *);  // 0x145c00
bool __cdecl HandleLobbyGame_UpdateJumpingCharacterStateOk(::Session const *, ::Packet const *);  // 0x145dc0
bool __cdecl HandleLobbyGame_UpdateJumpingCharacterStateFail(::Session const *, ::Packet const *);  // 0x145f80
bool __cdecl HandleLobbyGame_SecondPasswordGetStatusOk(::Session const *, ::Packet const *);  // 0x146150
bool __cdecl HandleLobbyGame_SecondPasswordGetStatusFail(::Session const *, ::Packet const *);  // 0x146740
bool __cdecl HandleLobbyGame_SecondPasswordIsVerifiedOk(::Session const *, ::Packet const *);  // 0x146cd0
bool __cdecl HandleLobbyGame_SecondPasswordIsVerifiedFail(::Session const *, ::Packet const *);  // 0x147240
bool __cdecl HandleLobbyGame_AuctionEscrowReq(::Session const *, ::Packet const *);  // 0x1477d0
bool __cdecl HandleLobbyGame_AuctionBidOk(::Session const *, ::Packet const *);  // 0x147e30
bool __cdecl HandleLobbyGame_AuctionBidFail(::Session const *, ::Packet const *);  // 0x148100
bool __cdecl HandleLobbyGame_ActivateGradeOk(::Session const *, ::Packet const *);  // 0x148510
bool __cdecl HandleLobbyGame_ActivateGradeFail(::Session const *, ::Packet const *);  // 0x148680
bool __cdecl HandleLobbyGame_DepositGameMileageOk(::Session const *, ::Packet const *);  // 0x148820
bool __cdecl HandleLobbyGame_DepositGameMileageFail(::Session const *, ::Packet const *);  // 0x149480
bool __cdecl HandleLobbyGame_TakeAccountTimeBasedPlayRewardOk(::Session const *, ::Packet const *);  // 0x149ec0
bool __cdecl HandleLobbyGame_TakeAccountTimeBasedPlayRewardFail(::Session const *, ::Packet const *);  // 0x14a390
bool __cdecl HandleLobbyGame_GetGradeListOk(::Session const *, ::Packet const *);  // 0x14a630
bool __cdecl HandleLobbyGame_GetGradeListFail(::Session const *, ::Packet const *);  // 0x14aa80
bool __cdecl HandleLobbyGame_ChangedGradeNotify(::Session const *, ::Packet const *);  // 0x14ac80
bool __cdecl HandleLobbyGame_ChangedGradeLevelNotify(::Session const *, ::Packet const *);  // 0x14ae80
bool __cdecl HandleLobbyGame_UpdateAccountExpFail(::Session const *, ::Packet const *);  // 0x14b060
bool __cdecl HandleLobbyGame_UpdateAccountContentQuotaOk(::Session const *, ::Packet const *);  // 0x14b0e0
bool __cdecl HandleLobbyGame_UpdateAccountContentQuotaFail(::Session const *, ::Packet const *);  // 0x14b120
bool __cdecl HandleLobbyGame_UpdateAccountRecycleTimeFail(::Session const *, ::Packet const *);  // 0x14b1a0
