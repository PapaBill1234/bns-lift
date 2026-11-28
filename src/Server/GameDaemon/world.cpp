// world.cpp: world.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "world.h"
#include "arenaroommanager.h"
#include "guild.h"
#include "pc.h"
#include "summoned.h"
#include "trade.h"
#include "user.h"
#include "worldserializedobject.h"
#include "zone.h"
#include "zonetimer.h"
#include "Memory.h"
#include "LiftStub.h"

// ❓ The case of the file name (World.cpp) is not proven. The other GameDaemon literals use the class case (Zone.cpp, GeoWorld.cpp).
#define WORLD_FILE L"e:\\dailybuild02\\gamedaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\gamedaemon\\World.cpp"

#pragma comment(linker, "/INCLUDE:??1?$IdManager@_J@@QEAA@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?Initialize@?$IdManager@_J@@QEAAXXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?PushId@?$IdManager@_J@@QEAA_N_J@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?PopId@?$IdManager@_J@@QEAA_JXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?getChannelEnable@World@@AEAA_NPEAUChannelList@1@F@Z")  // LIFT: dead-strip keep (no live caller yet)

// 0x3ebfb0
__cdecl WorldClock::~WorldClock(void)
{
    LIFT_STUB(0x3ebfb0);
}

// 0x3ec040
bool __cdecl WorldClock::HandleEvent(::EventContext *, unsigned long)
{
    LIFT_STUB(0x3ec040);
}

// 0x3ec0a0
bool __cdecl WorldClock::start(char, char)
{
    LIFT_STUB(0x3ec0a0);
}

// 0x3ec140
bool __cdecl WorldClock::reset(char, char)
{
    LIFT_STUB(0x3ec140);
}

// 0x3ec1f0
bool __cdecl ZoneIdManager::IsExist(unsigned __int64)
{
    LIFT_STUB(0x3ec1f0);
}

// 0x3ec290
bool __cdecl PcIdManager::IsExist(unsigned __int64)
{
    LIFT_STUB(0x3ec290);
}

// 0x3ec300
bool __cdecl SummonedIdManager::IsExist(unsigned __int64)
{
    LIFT_STUB(0x3ec300);
}

// 0x3ec370
__cdecl World::World(void)
{
    LIFT_STUB(0x3ec370);
}

// 0x3ec570
__cdecl World::~World(void)
{
    LIFT_STUB(0x3ec570);
}

// 0x3ed0a0
void __cdecl World::PreInitialize(void)
{
    LIFT_STUB(0x3ed0a0);
}

// 0x3ed400
bool __cdecl World::Initialize(void)
{
    LIFT_STUB(0x3ed400);
}

// 0x3ed8a0
void __cdecl World::ChangeZoneBroadcastEncryptParam(int)
{
    LIFT_STUB(0x3ed8a0);
}

// 0x3ed9f0
void __cdecl World::ChangeZoneRecommendPcCount(int *, int *, int)
{
    LIFT_STUB(0x3ed9f0);
}

// 0x3edbb0
void __cdecl World::initZoneManager(void)
{
    LIFT_STUB(0x3edbb0);
}

// 0x3eddc0
void __cdecl World::initPcManager(void)
{
    LIFT_STUB(0x3eddc0);
}

// 0x3edfd0
void __cdecl World::initSummonedManager(void)
{
    LIFT_STUB(0x3edfd0);
}

// 0x3ee0d0
void __cdecl World::initRaidDungeonManager(void)
{
    LIFT_STUB(0x3ee0d0);
}

// 0x3ee190
void __cdecl World::initGuildManager(void)
{
    LIFT_STUB(0x3ee190);
}

// 0x3ee5b0
void __cdecl World::initTradeShelfManager(void)
{
    LIFT_STUB(0x3ee5b0);
}

// 0x3ee670
void __cdecl World::Close(void)
{
    LIFT_STUB(0x3ee670);
}

// 0x3ee940
bool __cdecl World::Start(char, char)
{
    LIFT_STUB(0x3ee940);
}

// 0x3ef870
void __cdecl World::clearTradeShelfManager(void)
{
    LIFT_STUB(0x3ef870);
}

// 0x3ef9b0
void __cdecl World::clearZoneManager(void)
{
    LIFT_STUB(0x3ef9b0);
}

// 0x3efe30
void __cdecl World::clearPcManager(void)
{
    LIFT_STUB(0x3efe30);
}

// 0x3efee0
void __cdecl World::clearSummonedManager(void)
{
    LIFT_STUB(0x3efee0);
}

// 0x3f0060
void __cdecl World::clearRaidDungeonManager(void)
{
    LIFT_STUB(0x3f0060);
}

// 0x3f01a0
void __cdecl World::clearGuildManager(void)
{
    LIFT_STUB(0x3f01a0);
}

// 0x3f0380
int __cdecl World::CreatePersistentZone(void)
{
    LIFT_STUB(0x3f0380);
}

// 0x3f0a20
bool __cdecl World::Enter(::Pc *, unsigned __int64, int, int, int, int)
{
    LIFT_STUB(0x3f0a20);
}

// 0x3f0e30
bool __cdecl World::EnterArena(::Pc *)
{
    LIFT_STUB(0x3f0e30);
}

// 0x3f1570
bool __cdecl World::ReturnToGame(::Pc *, unsigned int, ::vector16, bool)
{
    LIFT_STUB(0x3f1570);
}

// 0x3f17a0
void __cdecl World::leave(::Pc *, unsigned __int64, bool &, bool)
{
    LIFT_STUB(0x3f17a0);
}

// 0x3f1af0
int __cdecl World::GetMaxChannelCount(unsigned int)
{
    LIFT_STUB(0x3f1af0);
}

// 0x3f1b30
unsigned __int64 __cdecl World::CreateZone(unsigned int, unsigned __int64, char, bool, bool, bool)
{
    LIFT_STUB(0x3f1b30);
}

// 0x3f1fa0
void __cdecl World::DestroyZone(unsigned __int64)
{
    LIFT_STUB(0x3f1fa0);
}

// 0x3f21b0
void __cdecl World::destroyZone(::RefCntObject *, ::RefCntObject *, ::RefCntObject *)
{
    LIFT_STUB(0x3f21b0);
}

// 0x3f2210
void __cdecl World::destroyZone(unsigned __int64, ::Zone *)
{
    LIFT_STUB(0x3f2210);
}

// 0x3f22c0
void __cdecl World::DestroyExpiredZone(void)
{
    LIFT_STUB(0x3f22c0);
}

// 0x3f2350
::Zone * __cdecl World::AcquireZone(unsigned __int64)
{
    LIFT_STUB(0x3f2350);
}

// 0x3f23f0
::Pointer2< ::Zone> __cdecl World::GetZonePtr(unsigned __int64)
{
    LIFT_STUB(0x3f23f0);
}

// 0x3f24e0
::Zone * __cdecl World::findZone(unsigned int)
{
    LIFT_STUB(0x3f24e0);
}

// 0x3f2540
::Zone * __cdecl World::findPublicRaidZone(::Pc *, ::ArenaRoom *)
{
    LIFT_STUB(0x3f2540);
}

// 0x3f26d0
void __cdecl World::DestroyPc(unsigned __int64, bool)
{
    LIFT_STUB(0x3f26d0);
}

// 0x3f2920
::BuilderChannel * __cdecl World::GetPcBuilderChannel(unsigned __int64)
{
    LIFT_STUB(0x3f2920);
}

// 0x3f2a00
void __cdecl World::SetPcBuilderChannel(::BuilderChannel *)
{
    LIFT_STUB(0x3f2a00);
}

// 0x3f2ac0
void __cdecl World::ResetPcBuilderChannel(unsigned __int64)
{
    LIFT_STUB(0x3f2ac0);
}

// 0x3f2b80
unsigned __int64 __cdecl World::CreatePrePlayPc(::Pc **, char)
{
    LIFT_STUB(0x3f2b80);
}

// 0x3f2d60
bool __cdecl World::RegisterPc(::Pc *, unsigned __int64)
{
    LIFT_STUB(0x3f2d60);
}

// 0x3f30a0
bool __cdecl World::ReplacePc(::User *, ::Pc *, ::FragmentPacketConcatenater *)
{
    LIFT_STUB(0x3f30a0);
}

// 0x3f3ab0
::Pc * __cdecl World::AcquirePc(unsigned __int64)
{
    LIFT_STUB(0x3f3ab0);
}

// 0x3f3b90
::Pointer2< ::Pc> __cdecl World::GetPcPtr(unsigned __int64, short)
{
    LIFT_STUB(0x3f3b90);
}

// 0x3f3d60
::Pointer2< ::Pc> __cdecl World::GetPcPtr(wchar_t const *, short)
{
    LIFT_STUB(0x3f3d60);
}

// 0x3f3fb0
::Pointer2< ::Pc> __cdecl World::GetPcPtrWithBuilderId(unsigned __int64, short)
{
    LIFT_STUB(0x3f3fb0);
}

// 0x3f40f0
int __cdecl World::AcquireAllPc(::Pc **const)
{
    LIFT_STUB(0x3f40f0);
}

// 0x3f41a0
void __cdecl World::ReleaseAllPc(::Pc **const, int)
{
    LIFT_STUB(0x3f41a0);
}

// 0x3f42c0
unsigned __int64 __cdecl World::CreateSummoned(::Pc *, ::Summoned **)
{
    LIFT_STUB(0x3f42c0);
}

// 0x3f45f0
void __cdecl World::DestroySummoned(unsigned __int64)
{
    LIFT_STUB(0x3f45f0);
}

// 0x3f46c0
::Pointer2< ::Summoned> __cdecl World::GetSummonedPtr(unsigned __int64)
{
    LIFT_STUB(0x3f46c0);
}

// 0x3f47f0
bool __cdecl World::PushGuildId(unsigned __int64)
{
    LIFT_STUB(0x3f47f0);
}

// 0x3f4880
unsigned __int64 __cdecl World::PopGuildId(void)
{
    LIFT_STUB(0x3f4880);
}

// 0x3f48e0
unsigned __int64 __cdecl World::PopGuildIdForGuildContentsList(void)
{
    LIFT_STUB(0x3f48e0);
}

// 0x3f4940
::Pointer2< ::Guild> __cdecl World::AddGuild(::LoadGuildInfo const *)
{
    LIFT_STUB(0x3f4940);
}

// 0x3f4c60
bool __cdecl World::CreateGuild(unsigned __int64, char, char, wchar_t const *, __int64, ::Pc *)
{
    LIFT_STUB(0x3f4c60);
}

// 0x3f52a0
bool __cdecl World::CreateGuild(unsigned __int64, char, char, wchar_t const *, __int64, wchar_t const *, unsigned __int64, short, __int64)
{
    LIFT_STUB(0x3f52a0);
}

// 0x3f57d0
bool __cdecl World::RenameGuild(unsigned __int64, wchar_t const *, __int64)
{
    LIFT_STUB(0x3f57d0);
}

// 0x3f5c10
void __cdecl World::DestroyGuild(unsigned __int64)
{
    LIFT_STUB(0x3f5c10);
}

// 0x3f5cf0
short __cdecl World::RenameGuildByManagement(unsigned __int64, wchar_t const *)
{
    LIFT_STUB(0x3f5cf0);
}

// 0x3f6130
::Pointer2< ::Guild> __cdecl World::GetGuildPtr(unsigned __int64)
{
    LIFT_STUB(0x3f6130);
}

// 0x3f6210
::Pointer2< ::Guild> __cdecl World::GetGuildPtr(wchar_t const *)
{
    LIFT_STUB(0x3f6210);
}

// 0x3f63b0
bool __cdecl World::JoinChattingChannel(char, ::Pc *, char &)
{
    LIFT_STUB(0x3f63b0);
}

// 0x3f6610
bool __cdecl World::LeaveChattingChannel(char, short, ::Pc *)
{
    LIFT_STUB(0x3f6610);
}

// 0x3f67a0
void __cdecl World::SendMessageInChattingChannel(char, ::Pc *, int, wchar_t const *, wchar_t const *)
{
    LIFT_STUB(0x3f67a0);
}

// 0x3f6900
void __cdecl World::SendPacketToWorldPc(char const *, ...)
{
    LIFT_STUB(0x3f6900);
}

// 0x3f69e0
void __cdecl World::DecreasePublicRaidReserveCount(::Pc *, unsigned __int64)
{
    LIFT_STUB(0x3f69e0);
}

// 0x3f6b70
bool __cdecl World::AvailableChannel(unsigned int, short, bool)
{
    LIFT_STUB(0x3f6b70);
}

// 0x3f6c80
bool __cdecl World::DisableChannel(unsigned int, short, bool)
{
    LIFT_STUB(0x3f6c80);
}

// 0x3f6e00
bool __cdecl World::getChannelEnable(::World::ChannelList *channel, short channelIndex)
{
    // LIFT: formtest DIFF 6. The original does not use `this` (channel is in rcx, likely an LTCG register change). Same logic.
    if (channel != nullptr && channelIndex >= 1 && channelIndex <= channel->maxChannelCount)
        return (channel->enable[(channelIndex - 1) / 8] >> ((channelIndex - 1) % 8)) & 1;
    return false;
}

// 0x3f6e50
::Guild * __cdecl World::findGuild(unsigned __int64)
{
    LIFT_STUB(0x3f6e50);
}

// 0x3f6ec0
void __cdecl World::removeGuildList(unsigned __int64)
{
    LIFT_STUB(0x3f6ec0);
}

// 0x3f6f40
void __cdecl World::removeGuildName(wchar_t const *)
{
    LIFT_STUB(0x3f6f40);
}

// 0x3f70d0
void __cdecl World::KeepSerializer(::ZoneSerializer *, unsigned __int64)
{
    LIFT_STUB(0x3f70d0);
}

// 0x3f71c0
bool __cdecl World::checkSerializer(void *)
{
    LIFT_STUB(0x3f71c0);
}

// 0x3f7210
void __cdecl World::deleteSerializer(void *)
{
    LIFT_STUB(0x3f7210);
}

// 0x3f72a0
bool __cdecl World::PostWSO(::WorldSerializedObject *, long)
{
    LIFT_STUB(0x3f72a0);
}

// 0x3f72e0
bool __cdecl World::PostWSOFromExternal(::WorldSerializedObject *)
{
    LIFT_STUB(0x3f72e0);
}

// 0x3f7340
bool __cdecl World::PostTSO(::WorldSerializedObject *, long)
{
    LIFT_STUB(0x3f7340);
}

// 0x3f7380
void __cdecl World::AddArenaGuildName(unsigned __int64, char, wchar_t const *, bool, char *const)
{
    LIFT_STUB(0x3f7380);
}

// 0x3f75d0
bool __cdecl World::GetArenaGuildName(unsigned __int64, char, wchar_t *, int, bool &, char *const)
{
    LIFT_STUB(0x3f75d0);
}

// 0x3f76e0
void __cdecl World::RenameArenaGuild(unsigned __int64, wchar_t const *)
{
    LIFT_STUB(0x3f76e0);
}

// 0x3f77e0
bool __cdecl World::GetGuildName(unsigned __int64, wchar_t *, int)
{
    LIFT_STUB(0x3f77e0);
}

// 0x3f7900
bool __cdecl World::ReserveZone(::Zone *, ::Pc *)
{
    LIFT_STUB(0x3f7900);
}

// 0x3f7970
bool __cdecl World::getGeoZoneByDeprecatedZone(unsigned int *, ::Pc *, unsigned __int64 *, int *)
{
    LIFT_STUB(0x3f7970);
}

// 0x3f7ab0
unsigned __int64 __cdecl World::GetReentrancePcSpawnKey(unsigned int, ::Pc *)
{
    LIFT_STUB(0x3f7ab0);
}

// 0x3f7c00
unsigned __int64 __cdecl World::getZoneToEnter2(unsigned int *, ::Pc *, unsigned __int64 *, bool, char, bool)
{
    LIFT_STUB(0x3f7c00);
}

// 0x3f86a0
unsigned __int64 __cdecl World::getZoneToEnter2(unsigned int, ::Pc *, short)
{
    LIFT_STUB(0x3f86a0);
}

// 0x3f88e0
unsigned __int64 __cdecl World::getZoneInChannel2(unsigned int, ::Pc *, unsigned __int64)
{
    LIFT_STUB(0x3f88e0);
}

// 0x3f9040
unsigned __int64 __cdecl World::getZoneInChannel2EventStageParty(unsigned int, ::Pc *, char, char, bool)
{
    LIFT_STUB(0x3f9040);
}

// 0x3f9460
unsigned __int64 __cdecl World::getZoneInChannel2EventStageSolo(unsigned int, ::Pc *, char, char, bool)
{
    LIFT_STUB(0x3f9460);
}

// 0x3f9880
unsigned __int64 __cdecl World::getZoneInChannel2EventStage(unsigned int, ::Pc *, char, char, bool)
{
    LIFT_STUB(0x3f9880);
}

// 0x3f9a00
unsigned __int64 __cdecl World::getZoneInChannel2FactionBattleField(unsigned int, ::Pc *)
{
    LIFT_STUB(0x3f9a00);
}

// 0x3f9f90
unsigned __int64 __cdecl World::getZoneInChannel2TendencyFactionBattleField(unsigned int, ::Pc *)
{
    LIFT_STUB(0x3f9f90);
}

// 0x3fa670
unsigned __int64 __cdecl World::getZoneInChannel2GuildBattleField(unsigned int, ::Pc *)
{
    LIFT_STUB(0x3fa670);
}

// 0x3fa8f0
unsigned __int64 __cdecl World::getZoneInChannel2WarField(unsigned int, ::Pc *)
{
    LIFT_STUB(0x3fa8f0);
}

// 0x3fab80
unsigned __int64 __cdecl World::createZone2(unsigned int, bool, unsigned __int64, char, ::Pc *, short, ::ArenaRoom *, char)
{
    LIFT_STUB(0x3fab80);
}

// 0x3fb150
__int64 __cdecl World::AddTradeShelf(::TradeShelf2 *)
{
    LIFT_STUB(0x3fb150);
}

// 0x3fb220
::Pointer2< ::TradeShelf2> __cdecl World::RemoveTradeShelf(__int64)
{
    LIFT_STUB(0x3fb220);
}

// 0x3fb340
bool __cdecl World::AddGuildPriorityQueueJob(::GuildPriorityQueueJob *)
{
    LIFT_STUB(0x3fb340);
}

// 0x3fb450
void __cdecl World::processPQGuildCraftTimerJob(void)
{
    LIFT_STUB(0x3fb450);
}

// 0x3fb800
bool __cdecl GuildTimerJobPriorityQueue::Push(::GuildPriorityQueueJob *)
{
    LIFT_STUB(0x3fb800);
}

// 0x3fb930
void __cdecl GuildTimerJobPriorityQueue::Clear(void)
{
    LIFT_STUB(0x3fb930);
}

// 0x3fb9c0
bool __cdecl World::ComposeGuildInfoList(::FragmentPacket &)
{
    LIFT_STUB(0x3fb9c0);
}

// 0x42eed0
template <typename T>
__cdecl IdManager<T>::~IdManager(void)
{
    IdNode *node = _head->_next;
    while (node != _tail)
    {
        IdNode *del = node;
        node = node->_next;
        Memory::_Manager[2]->Free(del, WORLD_FILE, 6808);
    }
    Memory::_Manager[2]->Free(_head, WORLD_FILE, 6811);
    Memory::_Manager[2]->Free(_tail, WORLD_FILE, 6812);
}

// 0x42ef80
template <typename T>
void __cdecl IdManager<T>::Initialize(void)
{
    _head = static_cast<IdNode *>(Memory::_Manager[2]->Alloc(sizeof(IdNode), WORLD_FILE, 6818));
    _tail = static_cast<IdNode *>(Memory::_Manager[2]->Alloc(sizeof(IdNode), WORLD_FILE, 6819));
    _head->_prev = _head;
    _head->_next = _tail;
    _tail->_prev = _head;
    _tail->_next = _tail;
}

// 0x42f000
template <typename T>
bool __cdecl IdManager<T>::PushId(T const id)
{
    bool result = false;
    _idMgrCS.Enter();
    IdNode *node = static_cast<IdNode *>(Memory::_Manager[2]->Alloc(sizeof(IdNode), WORLD_FILE, 6832));
    if (node != nullptr)
    {
        node->_id = id;
        result = true;
        _tail->_prev->_next = node;
        node->_prev = _tail->_prev;
        _tail->_prev = node;
        node->_next = _tail;
    }
    _idMgrCS.Leave();
    return result;
}

// 0x42f0a0
template <typename T>
T __cdecl IdManager<T>::PopId(void)
{
    T id = 0;
    _idMgrCS.Enter();
    IdNode *node = _head->_next;
    if (node != _tail)
    {
        id = node->_id;
        _head->_next = node->_next;
        node->_next->_prev = _head;
        Memory::_Manager[2]->Free(node, WORLD_FILE, 6871);
    }
    _idMgrCS.Leave();
    return id;
}

template class IdManager<__int64>;  // LIFT: explicit instantiation emits the 4 bodies above
