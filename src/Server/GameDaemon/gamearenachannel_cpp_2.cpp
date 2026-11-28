// gamearenachannel_cpp_2.cpp: gamearenachannel.cpp part 2 (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "gamearenachannel.h"
#include "pc.h"
#include "LiftStub.h"
#include <windows.h>
#include <string.h>

namespace
{
// LIFT: view of GameArenaLobbyManager (PDB size 0xD0). The skeleton class declares no members yet.
struct GameArenaLobbyManagerView
{
    CRITICAL_SECTION _lock;                       // +0 (0x0). LIFT: PDB type CriticalSection (CS at +0, size 0x28)
    short _worldIdCount;                          // +40 (0x28)
    short _worldIds[50];                          // +42 (0x2A)
    bool _connectedWorld[50];                     // +142 (0x8E)
    ::GameSideArenaLobbyChannel **_channels;      // +192 (0xC0)
    unsigned int _connectedArenaLobbyId;          // +200 (0xC8)
    bool _isInitializeGuildInfo;                  // +204 (0xCC)
};
static_assert(sizeof(GameArenaLobbyManagerView) == 0xD0, "sizeof GameArenaLobbyManager");
}  // namespace

// 0xcbfb0
bool __cdecl HandleArenaLobbyGameCancelMatchOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xcbfb0);
}

// 0xcc190
bool __cdecl HandleArenaLobbyGameCancelMatchFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xcc190);
}

// 0xcc3b0
bool __cdecl HandleArenaLobbyGameReadyToGoToArenaOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xcc3b0);
}

// 0xcc590
bool __cdecl HandleArenaLobbyGameReadyToGoToArenaFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xcc590);
}

// 0xcc7b0
bool __cdecl HandleArenaLobbyGameReadyToGoToArenaNotify(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xcc7b0);
}

// 0xccd30
bool __cdecl HandleArenaLobbyGameDecideToGoToArenaOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xccd30);
}

// 0xccf10
bool __cdecl HandleArenaLobbyGameDecideToGoToArenaFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xccf10);
}

// 0xcd150
bool __cdecl HandleArenaLobbyGameDecideToGoToArenaNotify(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xcd150);
}

// 0xcd6d0
bool __cdecl HandleArenaLobbyGameStartWaitingNotify(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xcd6d0);
}

// 0xcdcd0
bool __cdecl HandleArenaLobbyGameRetrieveWaitingNumberOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xcdcd0);
}

// 0xcdee0
bool __cdecl HandleArenaLobbyGameRetrieveWaitingNumberFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xcdee0);
}

// 0xce130
bool __cdecl HandleArenaLobbyGameCancelWaitingOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xce130);
}

// 0xce320
bool __cdecl HandleArenaLobbyGameCancelWaitingFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xce320);
}

// 0xce570
bool __cdecl HandleArenaLobbyGameReserveArenaNotify(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xce570);
}

// 0xcece0
bool __cdecl HandleArenaLobbyGameChattingServerAuthenticateUserReq(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xcece0);
}

// 0xcefd0
bool __cdecl HandleArenaLobbyGamePingOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xcefd0);
}

// 0xcf100
bool __cdecl HandleArenaLobbyGameSpectateGameOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xcf100);
}

// 0xcf7a0
bool __cdecl HandleArenaLobbyGameSpectateGameFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xcf7a0);
}

// 0xcfac0
bool __cdecl HandleArenaLobbyGameListSpectateGameOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xcfac0);
}

// 0xcff80
bool __cdecl HandleArenaLobbyGameListSpectateGameFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xcff80);
}

// 0xd01e0
bool __cdecl HandleArenaLobbyGameMoveToArenaOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xd01e0);
}

// 0xd0410
bool __cdecl HandleArenaLobbyGameMoveToArenaFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xd0410);
}

// 0xd06d0
bool __cdecl HandleArenaLobbyGameFindArenaSessionOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xd06d0);
}

// 0xd0970
bool __cdecl HandleArenaLobbyGameFindArenaSessionFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xd0970);
}

// 0xd0b80
__cdecl GameArenaManager::~GameArenaManager(void)
{
    LIFT_STUB(0xd0b80);
}

// 0xd0c00
bool __cdecl GameArenaManager::Send(unsigned int, unsigned int, ::Packet const *)
{
    LIFT_STUB(0xd0c00);
}

// 0xd0d00
bool __cdecl GameArenaManager::Broadcast(::Packet const *)
{
    LIFT_STUB(0xd0d00);
}

// 0xd0ef0
bool __cdecl GameArenaManager::SendLogoutReq(unsigned int, unsigned __int64, unsigned int, unsigned __int64, short)
{
    LIFT_STUB(0xd0ef0);
}

// 0xd1000
bool __cdecl GameArenaManager::SendLogoutReq(unsigned int, unsigned int, unsigned __int64, unsigned __int64, short)
{
    LIFT_STUB(0xd1000);
}

// 0xd1110
bool __cdecl GameArenaManager::BroadcastLogin(unsigned __int64)
{
    LIFT_STUB(0xd1110);
}

// 0xd11e0
bool __cdecl GameArenaManager::BroadcastRenameGuild(unsigned __int64, wchar_t const *)
{
    LIFT_STUB(0xd11e0);
}

// 0xd1310
bool __cdecl GameArenaManager::BroadcastRenameGuildByManagement(unsigned __int64, wchar_t const *)
{
    LIFT_STUB(0xd1310);
}

// 0xd1410
bool __cdecl GameArenaManager::SendDepositGameMileageOk(unsigned int, unsigned int, unsigned __int64, char, unsigned __int64, unsigned __int64, unsigned __int64, ::id128, __int64, short, __int64, int)
{
    LIFT_STUB(0xd1410);
}

// 0xd1580
bool __cdecl GameArenaManager::SendDepositGameMileageFail(unsigned int, unsigned int, unsigned __int64, char, unsigned __int64, unsigned __int64, unsigned __int64, ::id128, short, int)
{
    LIFT_STUB(0xd1580);
}

// 0xd16d0
::GameArenaChannel * __cdecl GameArenaManager::acquire(unsigned int, unsigned int)
{
    LIFT_STUB(0xd16d0);
}

// 0xd17c0
bool __cdecl GameArenaManager::ReserveConfirm(::GameArenaChannel *)
{
    LIFT_STUB(0xd17c0);
}

// 0xd18b0
void __cdecl GameArenaManager::ClearReserved(short)
{
    LIFT_STUB(0xd18b0);
}

// 0xd1a90
void __cdecl GameArenaManager::ConfirmOk(unsigned int, __int64, unsigned int)
{
    LIFT_STUB(0xd1a90);
}

// 0xd2080
void __cdecl GameArenaManager::ConfirmFail(__int64, unsigned int)
{
    LIFT_STUB(0xd2080);
}

// 0xd21e0
bool __cdecl GameArenaManager::Remove(::GameArenaChannel *)
{
    LIFT_STUB(0xd21e0);
}

// 0xd2320
void __cdecl GameArenaManager::Destroy(void)
{
    LIFT_STUB(0xd2320);
}

// 0xd2460
void __cdecl GameArenaManager::CheckPing(__int64)
{
    LIFT_STUB(0xd2460);
}

// 0xd26d0
bool __cdecl GameSideArenaLobbySessionHandler::OnAccept(::Session const *) const
{
    LIFT_STUB(0xd26d0);
}

// 0xd2710
bool __cdecl GameSideArenaLobbySessionHandler::OnConnect(::Session const *, bool) const
{
    LIFT_STUB(0xd2710);
}

// 0xd2960
void __cdecl GameSideArenaLobbySessionHandler::OnClose(::Session const *, bool) const
{
    LIFT_STUB(0xd2960);
}

// 0xd2be0
bool __cdecl GameSideArenaLobbySessionHandler::PacketHandler(::Session const *, ::Packet const *) const
{
    LIFT_STUB(0xd2be0);
}

// 0xd2d10
void __cdecl GameSideArenaLobbyChannel::Initialize(short)
{
    LIFT_STUB(0xd2d10);
}

// 0xd2e50
bool __cdecl GameSideArenaLobbyChannel::SendPing(void)
{
    LIFT_STUB(0xd2e50);
}

// 0xd2f20
void __cdecl GameSideArenaLobbyChannel::CheckPing(void)
{
    LIFT_STUB(0xd2f20);
}

// 0xd3000
#pragma comment(linker, "/INCLUDE:??0GameArenaLobbyManager@@QEAA@XZ")  // LIFT: dead-strip keep (no live caller yet)
__cdecl GameArenaLobbyManager::GameArenaLobbyManager(void)
{
    GameArenaLobbyManagerView *self = reinterpret_cast<GameArenaLobbyManagerView *>(this);
    InitializeCriticalSection(&self->_lock);  // CriticalSection::CriticalSection (inlined)
    self->_worldIdCount = 0;
    self->_channels = nullptr;
    self->_connectedArenaLobbyId = 0;
    self->_isInitializeGuildInfo = false;
    memset(self->_worldIds, 0, sizeof(self->_worldIds));
    memset(self->_connectedWorld, 0, sizeof(self->_connectedWorld));
}

// 0xd3080
bool __cdecl GameArenaLobbyManager::Initialize(short, short *const)
{
    LIFT_STUB(0xd3080);
}

// 0xd3460
void __cdecl GameArenaLobbyManager::Destroy(void)
{
    LIFT_STUB(0xd3460);
}

// 0xd35d0
void __cdecl GameArenaLobbyManager::CheckPing(void)
{
    LIFT_STUB(0xd35d0);
}

// 0xd3720
void __cdecl GameArenaLobbyManager::ResetIsInitializeGuildInfo(void)
{
    LIFT_STUB(0xd3720);
}

// 0xd37b0
void __cdecl GameArenaLobbyManager::SetConnectedWorld(short, bool)
{
    LIFT_STUB(0xd37b0);
}

// 0xd3890
bool __cdecl GameArenaLobbyManager::IsCloseAllConnection(void)
{
    LIFT_STUB(0xd3890);
}

// 0xd3960
::GameSideArenaLobbyChannel * __cdecl GameArenaLobbyManager::acquire(unsigned int)
{
    LIFT_STUB(0xd3960);
}

// 0xd3a30
::GameSideArenaLobbyChannel * __cdecl GameArenaLobbyManager::acquireFirstSession(void)
{
    LIFT_STUB(0xd3a30);
}

// 0xd3ab0
bool __cdecl GameArenaLobbyManager::Send(short, char const *, ...)
{
    LIFT_STUB(0xd3ab0);
}

// 0xd3ba0
bool __cdecl GameArenaLobbyManager::Send(short, ::Packet const *)
{
    LIFT_STUB(0xd3ba0);
}

// 0xd3c90
bool __cdecl GameArenaLobbyManager::SendFirstSession(::Packet const *)
{
    LIFT_STUB(0xd3c90);
}

// 0xd3d80
bool __cdecl GameArenaLobbyManager::SendCreateRoom(short, ::Pc **, int, unsigned __int64, char, char, unsigned __int64, char)
{
    LIFT_STUB(0xd3d80);
}

// 0xd3eb0
bool __cdecl GameArenaLobbyManager::SendReserveReturnToArenaLobby(::Pc *, unsigned __int64, unsigned __int64, unsigned int, short)
{
    LIFT_STUB(0xd3eb0);
}

// 0xd3fa0
bool __cdecl GameArenaLobbyManager::SendRelayPacket(short, ::DaemonId, wchar_t const *, wchar_t const *, __int64, ::Packet const *)
{
    LIFT_STUB(0xd3fa0);
}

// 0xd4240
bool __cdecl GameArenaLobbyManager::SendInitializeGuildInfoList(void)
{
    LIFT_STUB(0xd4240);
}

// 0xd4350
bool __cdecl GameArenaLobbyManager::SendInitializeGuildInfoListNolock(void)
{
    LIFT_STUB(0xd4350);
}

// 0xd44c0
bool __cdecl GameArenaLobbyManager::SendUpdateGuildInfo(unsigned __int64, char, int, int, __int64)
{
    LIFT_STUB(0xd44c0);
}

// 0xd47a0
bool __cdecl GameArenaLobbyManager::SendSyncSeasonContentsInfoReq(::Pc const *, unsigned __int64, short, ::SeasonContentsSyncData *const)
{
    LIFT_STUB(0xd47a0);
}
