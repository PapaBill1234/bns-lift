// arenaroommanager_cpp.cpp: arenaroommanager.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "arenaroommanager.h"
#include "LiftStub.h"

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
bool __cdecl ArenaDuelRoom::build(char)
{
    LIFT_STUB(0x49c50);
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
    LIFT_STUB(0x4a500);
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
    LIFT_STUB(0x4a900);
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
__cdecl ArenaSessionTimer::ArenaSessionTimer(__int64, __int64, wchar_t const *)
{
    LIFT_STUB(0x4ac20);
}

// 0x4acd0
void __cdecl DisconnectedArenaSessionInfo::Init(::DisconnectedArenaSessionInfo const *)
{
    LIFT_STUB(0x4acd0);
}

// 0x4ad60
bool __cdecl DisconnectedArenaSessionInfo::BuildPacket(::Packet &, ::PacketComposer &)
{
    LIFT_STUB(0x4ad60);
}

// 0x4ae50
bool __cdecl DisconnectedArenaSessionInfo::Decompose(::Packet const *, ::PacketDecomposer &)
{
    LIFT_STUB(0x4ae50);
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
