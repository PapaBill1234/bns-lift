// arenaroommanager_cpp.cpp: arenaroommanager.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "arenaroommanager.h"
#include <intrin.h>
#include <wchar.h>
#include "Log.h"
#include "Packet.h"
#include "LiftStub.h"

#define ARENAROOMMANAGER_FILE L"e:\\dailybuild02\\gamedaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\gamedaemon\\ArenaRoomManager.cpp"

#pragma comment(linker, "/INCLUDE:?build@ArenaDuelRoom@@MEAA_ND@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetPcContentsType@ArenaPublicRaidRoom@@MEAA?AW4PcContentsTypeType@Data@@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?IssueOtp@ArenaRoomManager@@QEAA_KXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:??0ArenaSessionTimer@@QEAA@_J0PEB_W@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?Init@DisconnectedArenaSessionInfo@@QEAAXPEBV1@@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?Decompose@DisconnectedArenaSessionInfo@@QEAA_NPEBVPacket@@AEAVPacketDecomposer@@@Z")  // LIFT: dead-strip keep (no live caller yet)

// 0x49a20
bool __cdecl ArenaRoom::Build(short, unsigned __int64, unsigned __int64, bool, ::FragmentPacketConcatenater *)
{
    LIFT_STUB(0x49a20);
}

// 0x49b40
__int64 __cdecl ArenaRoom::GetGuildRegistrationTime(unsigned __int64)
{
    LIFT_STUB(0x49b40);
}

// 0x49bc0
int __cdecl ArenaRoom::GetMemberCount(void)
{
    LIFT_STUB(0x49bc0);
}

// 0x49c50
bool __cdecl ArenaDuelRoom::build(char arenaLobbyGameMode)
{
    ::ArenaDuelRoomView *view = reinterpret_cast< ::ArenaDuelRoomView *>(this);
    // ❓ PDB enumerator names of the arena lobby and arena duel game modes are not looked up. The values are those of the original.
    if (arenaLobbyGameMode == 1)
    {
        view->_roomInfo._gameGameMode = 1;
        return true;
    }
    if (arenaLobbyGameMode == 2)
    {
        view->_roomInfo._gameGameMode = 2;
        return true;
    }
    view->_roomInfo._gameGameMode = 0;
    return false;
}

// 0x49c80
bool __cdecl ArenaDuelRoom::getZoneCreationInfo(unsigned int, unsigned int *, ::vector16 *, int *)
{
    LIFT_STUB(0x49c80);
}

// 0x49d90
bool __cdecl ArenaDuelRoom::GetPcSpawnInfo(unsigned int, unsigned __int64, unsigned int *, ::vector16 *, int *)
{
    LIFT_STUB(0x49d90);
}

// 0x49ed0
__cdecl ArenaDungeonRoom::ArenaDungeonRoom(void)
{
    LIFT_STUB(0x49ed0);
}

// 0x49f50
bool __cdecl ArenaDungeonRoom::build(char)
{
    LIFT_STUB(0x49f50);
}

// 0x49ff0
bool __cdecl ArenaDungeonRoom::getZoneCreationInfo(unsigned int, unsigned int *, ::vector16 *, int *)
{
    LIFT_STUB(0x49ff0);
}

// 0x4a090
::Data::PcContentsTypeType __cdecl ArenaDungeonRoom::GetPcContentsType(void)
{
    LIFT_STUB(0x4a090);
}

// 0x4a0e0
bool __cdecl ArenaDungeonRoom::GetPcSpawnInfo(unsigned int, unsigned __int64, unsigned int *, ::vector16 *, int *)
{
    LIFT_STUB(0x4a0e0);
}

// 0x4a350
__cdecl ArenaPublicRaidRoom::ArenaPublicRaidRoom(char)
{
    LIFT_STUB(0x4a350);
}

// 0x4a3e0
bool __cdecl ArenaPublicRaidRoom::build(char)
{
    LIFT_STUB(0x4a3e0);
}

// 0x4a480
bool __cdecl ArenaPublicRaidRoom::getZoneCreationInfo(unsigned int, unsigned int *, ::vector16 *, int *)
{
    LIFT_STUB(0x4a480);
}

// 0x4a500
::Data::PcContentsTypeType __cdecl ArenaPublicRaidRoom::GetPcContentsType(void)
{
    // ❓ PDB enumerator names of the public raid mode are not looked up. Modes 1 to 4 give the battle royal type.
    if (_arenaPortalPublicRaidModeType >= 1 && _arenaPortalPublicRaidModeType <= 4)
        return static_cast< ::Data::PcContentsTypeType>(4);  // PC_CONTENTS_TYPE_BATTLE_ROYAL
    return static_cast< ::Data::PcContentsTypeType>(1);  // PC_CONTENTS_TYPE_NORMAL
}

// 0x4a520
bool __cdecl ArenaPublicRaidRoom::GetPcSpawnInfo(unsigned int, unsigned __int64, unsigned int *, ::vector16 *, int *)
{
    LIFT_STUB(0x4a520);
}

// 0x4a6e0
__cdecl ArenaRoomManager::ArenaRoomManager(void)
{
    LIFT_STUB(0x4a6e0);
}

// 0x4a780
__cdecl ArenaRoomManager::~ArenaRoomManager(void)
{
    LIFT_STUB(0x4a780);
}

// 0x4a900
unsigned __int64 __cdecl ArenaRoomManager::IssueOtp(void)
{
    unsigned __int64 otp = _InterlockedIncrement64(reinterpret_cast<__int64 volatile *>(&_otpSeed));
    if (otp == 0)  // ArenaRoom::INVALID_OTP
    {
        otp = _InterlockedIncrement64(reinterpret_cast<__int64 volatile *>(&_otpSeed));
        Log::Write(Log::LT_ERROR, ARENAROOMMANAGER_FILE, 796, L"[arena-room-manager], otp overflow");
    }
    return otp;
}

// 0x4a950
unsigned __int64 __cdecl ArenaRoomManager::Add(::ArenaRoom *)
{
    LIFT_STUB(0x4a950);
}

// 0x4aa30
::ArenaRoom * __cdecl ArenaRoomManager::Acquire(unsigned __int64)
{
    LIFT_STUB(0x4aa30);
}

// 0x4aae0
void __cdecl ArenaRoomManager::RemoveTimeout(__int64, __int64)
{
    LIFT_STUB(0x4aae0);
}

// 0x4ac20
__cdecl ArenaSessionTimer::ArenaSessionTimer(__int64 pcDbId, __int64 reserveKey, wchar_t const *name)
    : _touchTime(_time64(nullptr)), _pcDbId(pcDbId), _reserveKey(reserveKey), _state(STATE_DST)
{
    if (name != nullptr)
        wcsncpy(_name, name, 33);
    else
        _name[0] = 0;
}

// 0x4acd0
void __cdecl DisconnectedArenaSessionInfo::Init(::DisconnectedArenaSessionInfo const *sessionInfo)
{
    if (sessionInfo != nullptr)
    {
        _disconnectedTime = sessionInfo->_disconnectedTime;
        _pcDbId = sessionInfo->_pcDbId;
        _teamId = sessionInfo->_teamId;
        _partyId = sessionInfo->_partyId;
        _reserveKey = sessionInfo->_reserveKey;
        _worldId = sessionInfo->_worldId;
        _arenaId = sessionInfo->_arenaId;
        _zoneId = sessionInfo->_zoneId;
        _geoZoneId = sessionInfo->_geoZoneId;
        _moveType = sessionInfo->_moveType;
        _gameMode = sessionInfo->_gameMode;
        wcsncpy(_name, sessionInfo->_name, 33);
    }
}

// 0x4ad60
bool __cdecl DisconnectedArenaSessionInfo::BuildPacket(::Packet &, ::PacketComposer &)
{
    LIFT_STUB(0x4ad60);
}

// 0x4ae50
bool __cdecl DisconnectedArenaSessionInfo::Decompose(::Packet const *packet, ::PacketDecomposer &pdr)
{
    // ❓ The 13th field (arena attraction) goes to a local. The class has no member for it.
    char attraction = 0;
    return packet->Decompose(&pdr, 13, &_disconnectedTime, &_pcDbId, _name, 33, &_teamId, &_partyId, &_reserveKey,
                             &_worldId, &_arenaId, &_zoneId, &_geoZoneId, &_moveType, &_gameMode, &attraction) != 0;
}

// 0x4af50
void __cdecl DisconnectedArenaSessionInfo::SendExpireUpdateArenaSession(char)
{
    LIFT_STUB(0x4af50);
}

// 0x4b030
__cdecl DisconnectedArenaSessionManager::DisconnectedArenaSessionManager(void)
{
    LIFT_STUB(0x4b030);
}

// 0x4b130
__cdecl DisconnectedArenaSessionManager::~DisconnectedArenaSessionManager(void)
{
    LIFT_STUB(0x4b130);
}

// 0x4b420
bool __cdecl DisconnectedArenaSessionManager::CreateTimer(unsigned __int64, __int64, wchar_t const *)
{
    LIFT_STUB(0x4b420);
}

// 0x4b540
void __cdecl DisconnectedArenaSessionManager::RemoveTimeoutTimer(__int64, __int64, __int64)
{
    LIFT_STUB(0x4b540);
}

// 0x4b720
__int64 __cdecl DisconnectedArenaSessionManager::GetTouchTime(unsigned __int64)
{
    LIFT_STUB(0x4b720);
}

// 0x4b7c0
bool __cdecl DisconnectedArenaSessionManager::ClearTimer(unsigned __int64)
{
    LIFT_STUB(0x4b7c0);
}

// 0x4b8b0
bool __cdecl DisconnectedArenaSessionManager::ChangeTimer(unsigned __int64, ::ArenaSessionTimer::STATE)
{
    LIFT_STUB(0x4b8b0);
}

// 0x4b9a0
bool __cdecl DisconnectedArenaSessionManager::IsReturnSession(unsigned __int64)
{
    LIFT_STUB(0x4b9a0);
}

// 0x4ba50
bool __cdecl DisconnectedArenaSessionManager::ExistSession(unsigned __int64, __int64, __int64 &, char &, bool)
{
    LIFT_STUB(0x4ba50);
}

// 0x4bc40
bool __cdecl DisconnectedArenaSessionManager::CreateSession(::DisconnectedArenaSessionInfo const *)
{
    LIFT_STUB(0x4bc40);
}

// 0x4bde0
void __cdecl DisconnectedArenaSessionManager::RemoveTimeoutSession(__int64, __int64)
{
    LIFT_STUB(0x4bde0);
}

// 0x4bfe0
::DisconnectedArenaSessionInfo * __cdecl DisconnectedArenaSessionManager::PopSession(unsigned __int64)
{
    LIFT_STUB(0x4bfe0);
}

// 0x4c0b0
::DisconnectedArenaSessionInfo * __cdecl DisconnectedArenaSessionManager::AcquireSession(unsigned __int64)
{
    LIFT_STUB(0x4c0b0);
}
