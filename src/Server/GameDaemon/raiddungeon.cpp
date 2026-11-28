// raiddungeon.cpp: raiddungeon.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
// LIFT: per-exe StlMemory.h path (A6). The inlined std::map head node allocation uses the GameDaemon build path.
#define LIFT_STLMEMORY_FILE \
    L"e:\\dailybuild02\\gamedaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\bloodlib\\include\\StlMemory.h"
#include "raiddungeon.h"
#include "bossnpc.h"
#include "pc.h"
#include "team.h"
#include "LiftStub.h"

// 0x1a6f00
__cdecl RaidDungeon::RaidDungeon(void)
{
    LIFT_STUB(0x1a6f00);
}

// 0x1a6ff0
__cdecl RaidDungeon::~RaidDungeon(void)
{
    LIFT_STUB(0x1a6ff0);
}

// 0x1a70b0
bool __cdecl RaidDungeon::Initialize(unsigned __int64, short)
{
    LIFT_STUB(0x1a70b0);
}

// 0x1a71c0
short __cdecl RaidDungeon::GetMaxUnbindCount(void)
{
    LIFT_STUB(0x1a71c0);
}

// 0x1a7260
bool __cdecl RaidDungeon::Initialize(unsigned __int64, unsigned __int64, short, char, short, __int64)
{
    LIFT_STUB(0x1a7260);
}

// 0x1a7370
bool __cdecl RaidDungeon::LoginCharacter(unsigned __int64, __int64, wchar_t const *, char, char, char)
{
    LIFT_STUB(0x1a7370);
}

// 0x1a76d0
bool __cdecl RaidDungeon::LogoutCharacter(unsigned __int64)
{
    LIFT_STUB(0x1a76d0);
}

// 0x1a78e0
void __cdecl RaidDungeon::SendOnlinePlayerInfo(::Pc *)
{
    LIFT_STUB(0x1a78e0);
}

// 0x1a7b60
::GameFailReason __cdecl RaidDungeon::SetOccupyingObjectId(unsigned __int64, ::Team *)
{
    LIFT_STUB(0x1a7b60);
}

// 0x1a7f60
void __cdecl RaidDungeon::SendInfomationToOccupyingObject(::Team *)
{
    LIFT_STUB(0x1a7f60);
}

// 0x1a8200
void __cdecl RaidDungeon::SendInfomation(::Pc *)
{
    LIFT_STUB(0x1a8200);
}

// 0x1a8360
#pragma comment(linker, "/INCLUDE:?GetOccupyingObjectId@RaidDungeon@@QEAA_KXZ")  // LIFT: dead-strip keep (no live caller yet)
unsigned __int64 __cdecl RaidDungeon::GetOccupyingObjectId(void)
{
    _raidDungeonCS.Enter();
    unsigned __int64 const occupyingObjectId = _occupyingObjectId;
    _raidDungeonCS.Leave();
    return occupyingObjectId;
}

// 0x1a83a0
void __cdecl RaidDungeon::BossCombatStart(::Pc *, ::BossNpc *)
{
    LIFT_STUB(0x1a83a0);
}

// 0x1a8660
void __cdecl RaidDungeon::BossCombatEnd(::BossNpc *)
{
    LIFT_STUB(0x1a8660);
}

// 0x1a87f0
void __cdecl RaidDungeon::LeaveMemberAfterCombatStart(::Pc *)
{
    LIFT_STUB(0x1a87f0);
}

// 0x1a90e0
bool __cdecl RaidDungeon::OnBossNpcKilled(::Data::BossNpcRecordPtr)
{
    LIFT_STUB(0x1a90e0);
}

// 0x1a94a0
#pragma comment(linker, "/INCLUDE:?IsBound@RaidDungeon@@QEAA_NXZ")  // LIFT: dead-strip keep (no live caller yet)
bool __cdecl RaidDungeon::IsBound(void)
{
    _raidDungeonCS.Enter();
    bool const bound = _waitConfirm || _dbId != 0;
    _raidDungeonCS.Leave();
    return bound;
}

// 0x1a94f0
void __cdecl RaidDungeon::broadcastStep(void)
{
    LIFT_STUB(0x1a94f0);
}

// 0x1a9780
void __cdecl RaidDungeon::insertToDB(void)
{
    LIFT_STUB(0x1a9780);
}

// 0x1a9890
void __cdecl RaidDungeon::updateToDB(void)
{
    LIFT_STUB(0x1a9890);
}

// 0x1a9a00
void __cdecl RaidDungeon::PostConfirmTask(__int64)
{
    LIFT_STUB(0x1a9a00);
}

// 0x1a9b90
bool __cdecl RaidDungeon::confirm(unsigned __int64)
{
    LIFT_STUB(0x1a9b90);
}

// 0x1aa220
#pragma comment(linker, "/INCLUDE:??0RaidDungeonManager@@QEAA@XZ")  // LIFT: dead-strip keep (no live caller yet)
__cdecl RaidDungeonManager::RaidDungeonManager(void)
    : _raidDungeonCount(0)
    , _raidDungeonCapacity(0)
    , _raidDungeonList(NULL)
    , _boundRaidDungeonlist()
    , _expirationTime(0)
    , _lock()
    , _lastIssuedId(0)
{
}

// 0x1aa2d0
// LIFT: the member destructors do the work (_lock: DeleteCriticalSection, then _boundRaidDungeonlist).
#pragma comment(linker, "/INCLUDE:??1RaidDungeonManager@@UEAA@XZ")  // LIFT: dead-strip keep (no live caller yet)
__cdecl RaidDungeonManager::~RaidDungeonManager(void)
{
}

// 0x1aa340
__int64 __cdecl RaidDungeonManager::makeId(void)
{
    LIFT_STUB(0x1aa340);
}

// 0x1aa3e0
bool __cdecl RaidDungeonManager::Initialize(int, int, int)
{
    LIFT_STUB(0x1aa3e0);
}

// 0x1aa5b0
bool __cdecl RaidDungeonManager::SetRaidDungeonExpirationTime(int, int)
{
    LIFT_STUB(0x1aa5b0);
}

// 0x1aa6f0
__int64 __cdecl RaidDungeonManager::GetRaidDungeonExpirationTime(void)
{
    LIFT_STUB(0x1aa6f0);
}

// 0x1aa740
bool __cdecl RaidDungeonManager::SetRaidDungeonFromDBData(::FragmentPacketConcatenater *)
{
    LIFT_STUB(0x1aa740);
}

// 0x1aaa30
::Pointer2< ::RaidDungeon> __cdecl RaidDungeonManager::Confirm(unsigned __int64, __int64)
{
    LIFT_STUB(0x1aaa30);
}

// 0x1aabb0
::Pointer2< ::RaidDungeon> __cdecl RaidDungeonManager::CreateRaidDungeon(int)
{
    LIFT_STUB(0x1aabb0);
}

// 0x1aadf0
::Pointer2< ::RaidDungeon> __cdecl RaidDungeonManager::DestroyRaidDungeon(unsigned __int64)
{
    LIFT_STUB(0x1aadf0);
}

// 0x1aaf70
::Pointer2< ::RaidDungeon> __cdecl RaidDungeonManager::GetRaidDungeonPtrById(unsigned __int64)
{
    LIFT_STUB(0x1aaf70);
}

// 0x1aaff0
::Pointer2< ::RaidDungeon> __cdecl RaidDungeonManager::GetRaidDungeonPtrByDbId(unsigned __int64)
{
    LIFT_STUB(0x1aaff0);
}

// 0x1ab0e0
__cdecl RaidDungeonBindPropertyEntry::RaidDungeonBindPropertyEntry(void)
{
    LIFT_STUB(0x1ab0e0);
}

// 0x1ab130
__cdecl RaidDungeonUnbindPropertyEntry::RaidDungeonUnbindPropertyEntry(void)
{
    LIFT_STUB(0x1ab130);
}

// 0x1ab180
void __cdecl RaidDungeonUnbindPropertyEntry::Initialize(int, ::Pc *)
{
    LIFT_STUB(0x1ab180);
}

// 0x1ab250
short __cdecl RaidDungeonUnbindPropertyEntry::FetchBroadcast(char *, short)
{
    LIFT_STUB(0x1ab250);
}

// 0x1ab2e0
#pragma comment(linker, "/INCLUDE:??0RaidDungeonPropertyContainer@@QEAA@XZ")  // LIFT: dead-strip keep (no live caller yet)
__cdecl RaidDungeonPropertyContainer::RaidDungeonPropertyContainer(void)
    : _bindList()
    , _unbindList()
    , _owner(NULL)
{
}

// 0x1ab3b0
__cdecl RaidDungeonPropertyContainer::~RaidDungeonPropertyContainer(void)
{
    LIFT_STUB(0x1ab3b0);
}

// 0x1ab5a0
int __cdecl RaidDungeonPropertyContainer::SetBindDbData(short, char const *, int)
{
    LIFT_STUB(0x1ab5a0);
}

// 0x1ab7f0
bool __cdecl RaidDungeonPropertyContainer::ConfirmAcquireBindData(__int64)
{
    LIFT_STUB(0x1ab7f0);
}

// 0x1ab8c0
bool __cdecl RaidDungeonPropertyContainer::BindRaidDungeonByDbId(__int64)
{
    LIFT_STUB(0x1ab8c0);
}

// 0x1aba20
int __cdecl RaidDungeonPropertyContainer::SetUnbindDbData(short, char const *, int)
{
    LIFT_STUB(0x1aba20);
}

// 0x1abca0
bool __cdecl RaidDungeonPropertyContainer::ConfirmAcquireUnbindData(int)
{
    LIFT_STUB(0x1abca0);
}

// 0x1abd50
short __cdecl RaidDungeonPropertyContainer::FetchUnbindList(short *, char *, short)
{
    LIFT_STUB(0x1abd50);
}

// 0x1abe30
bool __cdecl RaidDungeonPropertyContainer::UnbindRaidDungeon(int, __int64, bool)
{
    LIFT_STUB(0x1abe30);
}

// 0x1ac3c0
bool __cdecl RaidDungeonPropertyContainer::CheckExpiredRaidDungeon(bool)
{
    LIFT_STUB(0x1ac3c0);
}

// 0x1ac690
bool __cdecl RaidDungeonPropertyContainer::DisposeAll(void)
{
    LIFT_STUB(0x1ac690);
}
