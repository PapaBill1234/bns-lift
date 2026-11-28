// task_cpp_1.cpp: task.cpp part 1 (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "task.h"
#include "creature.h"
#include "pc.h"
#include "zone.h"
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:?TimerExpired@EnterZoneTask@@EEAAXIJ@Z")  // LIFT: dead-strip keep (no live caller yet)

// 0x2917d0
__cdecl Task::Task(unsigned short)
{
    LIFT_STUB(0x2917d0);
}

// 0x291840
__cdecl Task::~Task(void)
{
    LIFT_STUB(0x291840);
}

// 0x291860
void __cdecl Task::Initialize(::Zone *, ::Creature *)
{
    LIFT_STUB(0x291860);
}

// 0x2918b0
void __cdecl Task::TimerExpired(unsigned int, long)
{
    LIFT_STUB(0x2918b0);
}

// 0x291b50
::Zone * __cdecl Task::getParentZone(void)
{
    LIFT_STUB(0x291b50);
}

// 0x291b70
bool __cdecl AcquireConfirmTask::Initialize(::Zone *, ::Creature *, unsigned __int64, unsigned __int64, unsigned __int64, unsigned __int64, char, char const *, short)
{
    LIFT_STUB(0x291b70);
}

// 0x291cc0
void __cdecl AcquireConfirmTask::TimerExpired(unsigned int, long)
{
    LIFT_STUB(0x291cc0);
}

// 0x291d00
void __cdecl AcquireConfirmTask::start(void)
{
    LIFT_STUB(0x291d00);
}

// 0x291fb0
bool __cdecl AcquireConfirmFailTask::Initialize(::Zone *, ::Creature *, unsigned __int64, unsigned __int64, unsigned __int64, char, short)
{
    LIFT_STUB(0x291fb0);
}

// 0x2920a0
void __cdecl AcquireConfirmFailTask::TimerExpired(unsigned int, long)
{
    LIFT_STUB(0x2920a0);
}

// 0x2920e0
void __cdecl AcquireConfirmFailTask::start(void)
{
    LIFT_STUB(0x2920e0);
}

// 0x292340
bool __cdecl TakeWarehouseItemTask::Initialize(::Zone *, ::Creature *, unsigned __int64, ::PropertyTransactionSyncResult *, char, short, unsigned short)
{
    LIFT_STUB(0x292340);
}

// 0x2924b0
void __cdecl TakeWarehouseItemTask::TimerExpired(unsigned int, long)
{
    LIFT_STUB(0x2924b0);
}

// 0x2924f0
void __cdecl TakeWarehouseItemTask::start(void)
{
    LIFT_STUB(0x2924f0);
}

// 0x2925f0
bool __cdecl LevelUpTask::Initialize(::Zone *, ::Creature *, int, int, int, int, short)
{
    LIFT_STUB(0x2925f0);
}

// 0x2926e0
void __cdecl LevelUpTask::start(void)
{
    LIFT_STUB(0x2926e0);
}

// 0x292b50
bool __cdecl AccountLevelUpTask::Initialize(::Zone *, ::Creature *, int, int, short)
{
    LIFT_STUB(0x292b50);
}

// 0x292c30
void __cdecl AccountLevelUpTask::start(void)
{
    LIFT_STUB(0x292c30);
}

// 0x292cd0
void __cdecl TalkSessionOpenTask::start(void)
{
    LIFT_STUB(0x292cd0);
}

// 0x292dc0
void __cdecl TalkSessionCloseTask::start(void)
{
    LIFT_STUB(0x292dc0);
}

// 0x292e50
bool __cdecl MessageTask::Initialize(::Zone *, ::Creature *, ::MessageRange, int, wchar_t const *, wchar_t const *)
{
    LIFT_STUB(0x292e50);
}

// 0x292f30
void __cdecl MessageTask::start(void)
{
    LIFT_STUB(0x292f30);
}

// 0x293040
bool __cdecl MessageTask::SendMessageInZone(::Zone *, unsigned __int64, short, wchar_t const *, int, wchar_t const *, wchar_t const *)
{
    LIFT_STUB(0x293040);
}

// 0x2931a0
bool __cdecl MessageTask::SendMessageInSight(::Zone *, ::vector16, unsigned __int64, short, wchar_t const *, int, wchar_t const *, wchar_t const *)
{
    LIFT_STUB(0x2931a0);
}

// 0x293310
bool __cdecl MessageByItemTask::Initialize(::Zone *, ::Creature *, wchar_t const *, char, short)
{
    LIFT_STUB(0x293310);
}

// 0x2933f0
void __cdecl MessageByItemTask::start(void)
{
    LIFT_STUB(0x2933f0);
}

// 0x293990
bool __cdecl MessageByItemTask::SendMessageInDistrict(short, wchar_t const *)
{
    LIFT_STUB(0x293990);
}

// 0x293ad0
bool __cdecl MessageByItemTask::SendMessageInWorld(short, wchar_t const *)
{
    LIFT_STUB(0x293ad0);
}

// 0x293ba0
bool __cdecl MessageByDiceTask::Initialize(::Zone *, ::Creature *, short, short)
{
    LIFT_STUB(0x293ba0);
}

// 0x293c30
void __cdecl MessageByDiceTask::start(void)
{
    LIFT_STUB(0x293c30);
}

// 0x293d00
bool __cdecl MessageByDiceTask::sendMessageInSight(unsigned __int64, short)
{
    LIFT_STUB(0x293d00);
}

// 0x293e40
bool __cdecl MessageByDiceTask::sendMessageInZone(unsigned __int64, short)
{
    LIFT_STUB(0x293e40);
}

// 0x293f50
void __cdecl SelectTargetTask::start(void)
{
    LIFT_STUB(0x293f50);
}

// 0x293fd0
void __cdecl RequestActionCancel::start(void)
{
    LIFT_STUB(0x293fd0);
}

// 0x294000
void __cdecl RequestSkillTrigger::start(void)
{
    LIFT_STUB(0x294000);
}

// 0x294050
void __cdecl EnterZoneTask::TimerExpired(unsigned int timerId, long elapsed)
{
    // The original ignores both arguments and calls the virtual start().
    start();
}

// 0x294060
void __cdecl EnterZoneTask::start(void)
{
    LIFT_STUB(0x294060);
}

// 0x294290
bool __cdecl RespawnTask::Initialize(::Zone *, ::Creature *, char, bool)
{
    LIFT_STUB(0x294290);
}

// 0x294310
void __cdecl RespawnTask::start(void)
{
    LIFT_STUB(0x294310);
}

// 0x294830
void __cdecl DieInExhaustionTask::start(void)
{
    LIFT_STUB(0x294830);
}

// 0x2948f0
void __cdecl ReturnToBaseCampTask::start(void)
{
    LIFT_STUB(0x2948f0);
}

// 0x294970
void __cdecl TurnTask::start(void)
{
    LIFT_STUB(0x294970);
}

// 0x294bd0
void __cdecl SetPcSocialTask::start(void)
{
    LIFT_STUB(0x294bd0);
}

// 0x294cd0
void __cdecl JoinFactionTask::start(void)
{
    LIFT_STUB(0x294cd0);
}

// 0x295140
void __cdecl LeaveFactionTask::start(void)
{
    LIFT_STUB(0x295140);
}

// 0x295540
void __cdecl TransferFactionTask::start(void)
{
    LIFT_STUB(0x295540);
}

// 0x2961d0
bool __cdecl UseGroceryTask::Initialize(::Zone *, ::Creature *, short, short, short, short, short, __int64)
{
    LIFT_STUB(0x2961d0);
}

// 0x296280
void __cdecl UseGroceryTask::start(void)
{
    LIFT_STUB(0x296280);
}

// 0x2979f0
bool __cdecl UseFieldItemTask::Initialize(::Zone *const, ::Pc *const, unsigned __int64, short, char)
{
    LIFT_STUB(0x2979f0);
}

// 0x297b30
bool __cdecl UseFieldItemTask::Initialize(::Zone *const, ::Pc *const, ::vector16 const &, short, char)
{
    LIFT_STUB(0x297b30);
}

// 0x297c80
void __cdecl UseFieldItemTask::start(void)
{
    LIFT_STUB(0x297c80);
}

// 0x298040
bool __cdecl ThrowFieldItemTask::Initialize(::Zone *, ::Creature *, short, short, short, short)
{
    LIFT_STUB(0x298040);
}

// 0x298130
void __cdecl ThrowFieldItemTask::start(void)
{
    LIFT_STUB(0x298130);
}

// 0x298380
bool __cdecl ClearBuffDebuffTask::Initialize(::Zone *, ::Creature *)
{
    LIFT_STUB(0x298380);
}

// 0x298450
void __cdecl ClearBuffDebuffTask::start(void)
{
    LIFT_STUB(0x298450);
}

// 0x298490
void __cdecl DiscoveryAreaTask::start(void)
{
    LIFT_STUB(0x298490);
}

// 0x298650
bool __cdecl AddDiscoveryAreaTask::Initialize(::Zone *, ::Creature *, short)
{
    LIFT_STUB(0x298650);
}

// 0x298760
void __cdecl AddDiscoveryAreaTask::start(void)
{
    LIFT_STUB(0x298760);
}

// 0x298820
void __cdecl ActivatedTeleportTask::start(void)
{
    LIFT_STUB(0x298820);
}

// 0x2989e0
bool __cdecl DetectTeleportSwitchTask::Initialize(::Zone *, ::Creature *, short)
{
    LIFT_STUB(0x2989e0);
}

// 0x298af0
void __cdecl DetectTeleportSwitchTask::start(void)
{
    LIFT_STUB(0x298af0);
}

// 0x298cb0
bool __cdecl EnterPortalTask::Initialize(::Zone *, ::Creature *)
{
    LIFT_STUB(0x298cb0);
}

// 0x298da0
void __cdecl EnterPortalTask::start(void)
{
    LIFT_STUB(0x298da0);
}

// 0x299160
bool __cdecl ChannelListTask::Initialize(::Zone *, ::Creature *, unsigned int)
{
    LIFT_STUB(0x299160);
}

// 0x299210
void __cdecl ChannelListTask::start(void)
{
    LIFT_STUB(0x299210);
}

// 0x299490
void __cdecl ChangeChannelTask::start(void)
{
    LIFT_STUB(0x299490);
}

// 0x299bb0
bool __cdecl PartyMatchNotifyTask::Initialize(::Zone *, ::Creature *, unsigned __int64, unsigned int, bool, short)
{
    LIFT_STUB(0x299bb0);
}

// 0x299c80
void __cdecl PartyMatchNotifyTask::start(void)
{
    LIFT_STUB(0x299c80);
}

// 0x299d10
void __cdecl SetGuildIdTask::TimerExpired(unsigned int, long)
{
    LIFT_STUB(0x299d10);
}

// 0x299d50
void __cdecl SetGuildIdTask::start(void)
{
    LIFT_STUB(0x299d50);
}

// 0x299e40
void __cdecl GuildJoinRenewalTask::Post(void)
{
    LIFT_STUB(0x299e40);
}

// 0x299e70
void __cdecl GuildJoinRenewalTask::TimerExpired(unsigned int, long)
{
    LIFT_STUB(0x299e70);
}

// 0x299eb0
void __cdecl GuildJoinRenewalTask::start(void)
{
    LIFT_STUB(0x299eb0);
}

// 0x299f70
void __cdecl GuildJoinRenewalTask::sendGuildApplicationReq(void)
{
    LIFT_STUB(0x299f70);
}

// 0x29a720
void __cdecl GuildJoinRenewalTask::cancelGuildApplicationReq(void)
{
    LIFT_STUB(0x29a720);
}

// 0x29a960
void __cdecl GuildJoinRenewalTask::rejectGuildApplicationReq(void)
{
    LIFT_STUB(0x29a960);
}

// 0x29add0
void __cdecl GuildJoinRenewalTask::acceptGuildApplicationReq(void)
{
    LIFT_STUB(0x29add0);
}

// 0x29b0f0
void __cdecl GuildJoinRenewalTask::sendGuildInvitationReq(void)
{
    LIFT_STUB(0x29b0f0);
}

// 0x29bbd0
void __cdecl GuildJoinRenewalTask::cancelGuildInvitationReq(void)
{
    LIFT_STUB(0x29bbd0);
}

// 0x29bf60
void __cdecl GuildJoinRenewalTask::rejectGuildInvitationReq(void)
{
    LIFT_STUB(0x29bf60);
}

// 0x29c1a0
void __cdecl GuildJoinRenewalTask::acceptGuildInvitationReq(void)
{
    LIFT_STUB(0x29c1a0);
}

// 0x29c450
bool __cdecl UpdateGuildApplicationRefusalTask::Initialize(::Zone *, ::Creature *, unsigned __int64, unsigned __int64, wchar_t *, char)
{
    LIFT_STUB(0x29c450);
}

// 0x29c530
void __cdecl UpdateGuildApplicationRefusalTask::TimerExpired(unsigned int, long)
{
    LIFT_STUB(0x29c530);
}

// 0x29c570
void __cdecl UpdateGuildApplicationRefusalTask::start(void)
{
    LIFT_STUB(0x29c570);
}

// 0x29c7c0
bool __cdecl UpdateGuildInvitationRefusalTask::Initialize(::Zone *, ::Creature *, unsigned __int64, char)
{
    LIFT_STUB(0x29c7c0);
}

// 0x29c870
void __cdecl UpdateGuildInvitationRefusalTask::TimerExpired(unsigned int, long)
{
    LIFT_STUB(0x29c870);
}

// 0x29c8b0
void __cdecl UpdateGuildInvitationRefusalTask::start(void)
{
    LIFT_STUB(0x29c8b0);
}

// 0x29c9e0
__cdecl SurveyTask::SurveyTask(void)
{
    LIFT_STUB(0x29c9e0);
}

// 0x29ca80
bool __cdecl SurveyTask::Initialize(::Zone *, ::Creature *, char *const, short)
{
    LIFT_STUB(0x29ca80);
}

// 0x29cb50
bool __cdecl SurveyTask::Initialize(::Zone *, ::Creature *, char, char, wchar_t *)
{
    LIFT_STUB(0x29cb50);
}

// 0x29cc30
void __cdecl SurveyTask::start(void)
{
    LIFT_STUB(0x29cc30);
}

// 0x29d550
void __cdecl AuctionEscrowTask::ProcessUnexpired(int)
{
    LIFT_STUB(0x29d550);
}

// 0x29d600
bool __cdecl AuctionEscrowTask::Initialize(::Zone *, ::Creature *, short, __int64, __int64, __int64)
{
    LIFT_STUB(0x29d600);
}

// 0x29d750
void __cdecl AuctionEscrowTask::TimerExpired(unsigned int, long)
{
    LIFT_STUB(0x29d750);
}

// 0x29d790
void __cdecl AuctionEscrowTask::start(void)
{
    LIFT_STUB(0x29d790);
}

// 0x29dbf0
__cdecl AuctionEscrowBidTask::AuctionEscrowBidTask(void)
{
    LIFT_STUB(0x29dbf0);
}

// 0x29dc80
void __cdecl AuctionEscrowBidTask::start(void)
{
    LIFT_STUB(0x29dc80);
}

// 0x29dea0
void __cdecl ReserveArenaLobbyPartyAgreementTask::start(void)
{
    LIFT_STUB(0x29dea0);
}

// 0x29e1b0
void __cdecl ReserveArenaLobbyPartyFinalDecisionTask::start(void)
{
    LIFT_STUB(0x29e1b0);
}

// 0x29e410
void __cdecl CheckArenaPortalUsableTask::fail(::Pc *, short, wchar_t const *, bool)
{
    LIFT_STUB(0x29e410);
}

// 0x29e640
void __cdecl CheckArenaPortalUsableTask::start(void)
{
    LIFT_STUB(0x29e640);
}

// 0x29e720
bool __cdecl CheckArenaPortalUsableTask::usableMoveToArenaLobby(::Pc *, char)
{
    LIFT_STUB(0x29e720);
}

// 0x29ec30
bool __cdecl CheckArenaPortalUsableTask::usableReturnToArenaLobby(::Pc *, char)
{
    LIFT_STUB(0x29ec30);
}

// 0x29ef60
bool __cdecl CheckArenaPortalUsableTask::publishRecruitArenaDungeon(::Pc *, char)
{
    LIFT_STUB(0x29ef60);
}

// 0x29f290
bool __cdecl CheckArenaPortalUsableTask::cancelRecruitArenaDungeon(::Pc *, char)
{
    LIFT_STUB(0x29f290);
}

// 0x29f520
void __cdecl ReturnToArenaLobbyFromDuelTask::start(void)
{
    LIFT_STUB(0x29f520);
}

// 0x29f810
void __cdecl ReturnToArenaLobbyFromDungeonTask::movePc(::Pc *, char)
{
    LIFT_STUB(0x29f810);
}

// 0x29f9d0
void __cdecl ReturnToArenaLobbyFromDungeonTask::start(void)
{
    LIFT_STUB(0x29f9d0);
}

// 0x29fd50
void __cdecl ArenaSpectateReturnToArenaLobbyTask::start(void)
{
    LIFT_STUB(0x29fd50);
}

// 0x2a0040
bool __cdecl ArenaEventTeleportToTask::Initialize(::Zone *, ::Pc *, ::Pc *)
{
    LIFT_STUB(0x2a0040);
}

// 0x2a00f0
void __cdecl ArenaEventTeleportToTask::start(void)
{
    LIFT_STUB(0x2a00f0);
}

// 0x2a01f0
void __cdecl ArenaEventTeleportToTask::warp(void)
{
    LIFT_STUB(0x2a01f0);
}

// 0x2a0310
void __cdecl ArenaEventTeleportToTask::zoneTransition(void)
{
    LIFT_STUB(0x2a0310);
}

// 0x2a0420
void __cdecl ArenaEventReturnToArenaLobbyTask::start(void)
{
    LIFT_STUB(0x2a0420);
}
