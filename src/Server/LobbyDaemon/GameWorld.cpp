// GameWorld.obj (LobbyDaemon PDB, 2019 + PDB).
#include "PlacementNew.h"
#include "GameWorld.h"
#include "Character.h"
#include "CliSession.h"
#include "Daemon.h"
#include "FragmentPacket.h"
#include "LiftStub.h"
#include "Log.h"
#include <string.h>
#include <wchar.h>

#if !defined(__clang__)
#pragma comment(linker, "/INCLUDE:??0GameWorld@@QEAA@XZ")  // LIFT: keep until the caller is lifted (0x4c820).
#pragma comment(linker, "/INCLUDE:?Setup@GameWorld@@QEAA_NPEAUDB@1@PEAVGameWorldCluster@@@Z")  // LIFT: keep until the caller is lifted (0x4c880).
#pragma comment(linker, "/INCLUDE:?Update@GameWorld@@QEAA_NPEAUDB@1@@Z")  // LIFT: keep until the caller is lifted (0x4ca30).
#pragma comment(linker, "/INCLUDE:?EnterUser@GameWorld@@QEAA_NPEAVCliSession@@AEA_NAEAUWaitInfo@@@Z")  // LIFT: keep until the caller is lifted (0x4cf40).
#endif

// 0x4c810
short GameWorld::GetWid() const
{
    return _db.wid;
}

// 0x4c820
GameWorld::GameWorld()
    : _cluster(nullptr), _playingUserCount(0), _quickPassPlayingUserCount(0), _live(false)
{
    memset(&_db, 0, sizeof(_db));
    InitializeSRWLock(&_infolock);
}

// 0x4c880
bool GameWorld::Setup(DB* db, GameWorldCluster* cluster)
{
    if (db != nullptr && cluster != nullptr)
    {
        wchar_t const* brandnew = db->brandnew ? L"yes" : L"no";
        wchar_t const* recommend = db->recommend ? L"yes" : L"no";
        wchar_t const* newLimited = db->characterCreationLimitedOnNewAccount ? L"yes" : L"no";
        wchar_t const* limited = db->characterCreationLimited ? L"yes" : L"no";
        wchar_t const* entrance = db->entrance ? L"yes" : L"no";
        wchar_t const* use = db->use ? L"yes" : L"no";
        Log::Write(Log::LT_DEBUG, L"GameWorld.cpp", 50,
            L"[game-world], setup to, wid:%d, world-cluster-id:%d, name:%s, score:%d, world-type:%d, play-type:%d, use:%s, entrance:%s, pc-creation-limited:%s, pc-creation-limited-on-new-account:%s, recommend:%s, brandnew:%s, crowdness:%d",
            db->wid, db->clusterId, db->name, db->score, db->worldType, db->playType,
            use, entrance, limited, newLimited, recommend, brandnew, db->crowdness);
        memcpy(&_db, db, sizeof(_db));
        _playingUserCount = 0;
        _quickPassPlayingUserCount = 0;
        int wid = _db.wid;
        _cluster = cluster;
        Log::Write(Log::LT_DEBUG, L"GameWorld.cpp", 57, L"[game-world], setup ok, wid:%d", wid);
        return true;
    }
    Log::Write(Log::LT_DEBUG, L"GameWorld.cpp", 46, L"[game-world], setup fail; invalid parameter");
    return false;
}

// 0x4ca30
bool GameWorld::Update(DB* db)
{
    if (db != nullptr)
    {
        wchar_t const* brandnew = db->brandnew ? L"yes" : L"no";
        wchar_t const* recommend = db->recommend ? L"yes" : L"no";
        wchar_t const* newLimited = db->characterCreationLimitedOnNewAccount ? L"yes" : L"no";
        wchar_t const* limited = db->characterCreationLimited ? L"yes" : L"no";
        wchar_t const* entrance = db->entrance ? L"yes" : L"no";
        wchar_t const* use = db->use ? L"yes" : L"no";
        wchar_t const* name = db->name;
        Log::Write(Log::LT_DEBUG, L"GameWorld.cpp", 68,
            L"[game-world], update to, wid:%d, world-cluster-id:%d, name:%s, score:%d, world-type:%d, play-type:%d, use:%s, entrance:%s, pc-creation-limited:%s, pc-creation-limited-on-new-account:%s, recommend:%s, brandnew:%s, crowdness:%d",
            db->wid, db->clusterId, name, db->score, db->worldType, db->playType,
            use, entrance, limited, newLimited, recommend, brandnew, db->crowdness);
        AcquireSRWLockExclusive(&_infolock);
        wcscpy_s(_db.name, 33, name);
        _db.worldType = db->worldType;
        _db.playType = db->playType;
        _db.score = db->score;
        _db.use = db->use;
        _db.entrance = db->entrance;
        _db.characterCreationLimited = db->characterCreationLimited;
        _db.characterCreationLimitedOnNewAccount = db->characterCreationLimitedOnNewAccount;
        _db.recommend = db->recommend;
        _db.brandnew = db->brandnew;
        _db.crowdness = db->crowdness;
        ReleaseSRWLockExclusive(&_infolock);
        Log::Write(Log::LT_NOTICE, L"GameWorld.cpp", 86, L"[game-world], update ok, wid:%d", _db.wid);
        return true;
    }
    Log::Write(Log::LT_ERROR, L"GameWorld.cpp", 64, L"[game-world], update fail; invalid parameter");
    return false;
}

// 0x4cc40
bool GameWorld::FetchWorldInfo(FragmentPacket* fp) const
{
    if (fp == nullptr)
        return false;
    if (fp->FreeSize() < 0x61)
        fp->packet.Allocate(&fp->composer);
    GameWorldCluster* cluster = _cluster;
    AcquireSRWLockShared(&cluster->_infoLock);
    unsigned long publicIp = cluster->_db.pub_IPv4;
    unsigned long internalIp = cluster->_db.internal_IPv4;
    unsigned short publicPort = cluster->_db.pub_port;
    unsigned short mobilePort = cluster->_db.mobile_port;
    ReleaseSRWLockShared(&cluster->_infoLock);
    AcquireSRWLockShared(&_infolock);
    char crowdness;
    switch (_db.crowdness)
    {
    case 1: crowdness = 0; break;
    case 3: crowdness = 2; break;
    default: crowdness = 1; break;
    }
    bool ok = fp->Compose(17, _db.wid, _db.clusterId, _db.name, _db.worldType,
        _db.playType, publicIp, internalIp, publicPort, mobilePort, _db.score, _live,
        _db.entrance, !_db.characterCreationLimited, _db.characterCreationLimitedOnNewAccount,
        _db.recommend, _db.brandnew, crowdness) != 0;
    ReleaseSRWLockShared(&_infolock);
    return ok;
}

// 0x4ce60
bool GameWorld::FetchWorldInfoForInfoGate(FragmentPacket* fp) const
{
    if (fp == nullptr)
        return false;
    Packet::Header* header = fp->packet.CurHeader;
    if (header == nullptr || static_cast<unsigned short>(4000 - header->size) < 5)
        fp->packet.Allocate(&fp->composer);
    AcquireSRWLockShared(&_infolock);
    bool ok = fp->Compose(3, _db.wid, _db.clusterId, _db.use) != 0;
    Log::Write(Log::LT_NOTICE, L"GameWorld.cpp", 189,
        L"[game-world], fetch world info for infogate ok, wid:%d, clusterId:%d, use:%d",
        _db.wid, _db.clusterId, _db.use);
    ReleaseSRWLockShared(&_infolock);
    return ok;
}

// 0x4cf40
bool GameWorld::EnterUser(CliSession* cs, bool& wait, WaitInfo& waitinfo)
{
    if (cs == nullptr)
    {
        Log::Write(Log::LT_ERROR, L"GameWorld.cpp", 198,
            L"[game-world], enter user fail; null cli-session, wid:%d", _db.wid);
        TLobbyError = LOBERR_INVALID_PARAMETER;
        return false;
    }
    AcquireSRWLockShared(&_infolock);
    if (!_live)
    {
        ReleaseSRWLockShared(&_infolock);
        Log::Write(Log::LT_ERROR, L"GameWorld.cpp", 207,
            L"[game-world], enter user fail; world not alive, wid:%d", _db.wid);
        TLobbyError = LOBERR_GAMEWORLD_NOT_ALIVE;
        return false;
    }
    if (!_db.use)
    {
        ReleaseSRWLockShared(&_infolock);
        Log::Write(Log::LT_ERROR, L"GameWorld.cpp", 214,
            L"[game-world], enter user fail; world not usable, wid:%d", _db.wid);
        TLobbyError = LOBERR_GAMEWORLD_NOT_USABLE;
        return false;
    }
    if (!_db.entrance && !cs->_auth._table.field[Authority::OP_ENTER_GAMEWORLD_ON_ENTRANCE_NOT_ALLOWED])
    {
        ReleaseSRWLockShared(&_infolock);
        Log::Write(Log::LT_ERROR, L"GameWorld.cpp", 221,
            L"[game-world], enter user fail; entrance not allowed, wid:%d", _db.wid);
        if (_db.characterCreationLimited)
            TLobbyError = LOBERR_GAMEWORLD_ENTRANCE_NOT_ALLOWED;
        else
            TLobbyError = LOBERR_GAMEWORLD_PRE_CHARACTER_CREATION_MODE;
        return false;
    }
    ReleaseSRWLockShared(&_infolock);
    return _cluster->enterUser(this, cs, wait, waitinfo);
}

#if !defined(__clang__)
#pragma comment(linker, "/INCLUDE:?PermitCharacterManagement@GameWorld@@QEAA_NPEAVCliSession@@_N@Z")  // LIFT: keep until the caller is lifted (0x4d120).
#endif

// 0x4d120
bool GameWorld::PermitCharacterManagement(CliSession* cs, bool creation)
{
    if (cs == nullptr)
    {
        Log::Write(Log::LT_ERROR, L"GameWorld.cpp", 255, L"[game-world], check character management fail; invalid paramter");
        TLobbyError = LOBERR_INVALID_PARAMETER;
        return false;
    }
    AcquireSRWLockShared(&_infolock);
    if (!_db.use)
    {
        ReleaseSRWLockShared(&_infolock);
        Log::Write(Log::LT_DEBUG, L"GameWorld.cpp", 264,
            L"[game-world], check character management fail; world not usable, cli-key:0x%I64X, cli-state:%d.%d",
            cs->_clikey, HIWORD(cs->_state), LOWORD(cs->_state));
        TLobbyError = LOBERR_GAMEWORLD_NOT_USABLE;
        return false;
    }
    if (_db.characterCreationLimited && !cs->_auth._table.field[Authority::OP_MANAGE_CHARACTER_ON_NOT_ALLOWED])
    {
        ReleaseSRWLockShared(&_infolock);
        Log::Write(Log::LT_DEBUG, L"GameWorld.cpp", 271,
            L"[game-world], check character management fail; not allwed, cli-key:0x%I64X, cli-state:%d.%d",
            cs->_clikey, HIWORD(cs->_state), LOWORD(cs->_state));
        TLobbyError = LOBERR_GAMEWORLD_CHARACTER_MANAGEMENT_NOT_ALLOWED;
        return false;
    }
    if (creation && _db.characterCreationLimitedOnNewAccount &&
        !cs->_auth._table.field[Authority::OP_CREATE_CHARACTER_ON_NEW_ACCOUNT_CREATION_NOT_ALLOWED])
    {
        std::vector<Character*, StlAllocator<Character*, 2> >::const_iterator it = cs->_characters.begin();
        std::vector<Character*, StlAllocator<Character*, 2> >::const_iterator end = cs->_characters.end();
        for (; it != end; ++it)
        {
            if (*it != nullptr && (*it)->_db.belongingWorld == _db.wid)
                break;
        }
        if (it == end)
        {
            ReleaseSRWLockShared(&_infolock);
            Log::Write(Log::LT_DEBUG, L"GameWorld.cpp", 280,
                L"[game-world], check character management fail; new game-account limited, cli-key:0x%I64X, cli-state:%d.%d",
                cs->_clikey, HIWORD(cs->_state), LOWORD(cs->_state));
            TLobbyError = LOBERR_GAMEWORLD_NEW_ACCOUNT_CHARACTER_CREATION_NOT_ALLOWED;
            return false;
        }
    }
    ReleaseSRWLockShared(&_infolock);
    Log::Write(Log::LT_DEBUG, L"GameWorld.cpp", 288,
        L"[game-world], check character management ok, cli-key:0x%I64X, cli-state:%d.%d",
        cs->_clikey, HIWORD(cs->_state), LOWORD(cs->_state));
    return true;
}

#if !defined(__clang__)
#pragma comment(linker, "/INCLUDE:??0GameWorldCluster@@QEAA@XZ")  // LIFT: keep until the caller is lifted (0x4d390).
#pragma comment(linker, "/INCLUDE:?UpdateCounters@GameWorldCluster@@QEAA_JXZ")  // LIFT: keep until the caller is lifted (0x4dc70).
#endif

// 0x4d390
GameWorldCluster::GameWorldCluster() : _currentEntranceCount(0)
{
    InitializeSRWLock(&_infoLock);
    _db.clusterId = 0;
    _db.pub_IPv4 = 0;
    _db.internal_IPv4 = 0;
    _db.pub_port = 0;
    _db.mobile_port = 0;
    _db.maxPlayerCount = 0;
    _db.maxWaitingCount = 0;
}

// 0x4d440
GameWorldCluster::~GameWorldCluster()
{
}

// 0x4dc70
long long GameWorldCluster::UpdateCounters()
{
    _worldLock.Enter();
    int playing = 0;
    int quickPass = 0;
    for (std::vector<GameWorld*, StlAllocator<GameWorld*, 2> >::const_iterator it = _worlds.begin(), end = _worlds.end(); it != end; ++it)
    {
        GameWorld* world = *it;
        if (world != nullptr)
        {
            playing += world->GetPlayingUserCount();
            quickPass += world->GetQuickpassUserCount();
        }
    }
    _worldLock.Leave();
    long long currentPlayer = playing + quickPass;
    long long currentWaitingPlayer = _waitQueueList.GetAllWaitingPlayer();
    _counterSet.SetMaxPlayerCount(_db.maxPlayerCount);
    _counterSet.SetMaxWaitingCount(_db.maxWaitingCount);
    _counterSet.SetCurrentPlayerCount(currentPlayer);
    _counterSet.SetCurrentWaitingCount(currentWaitingPlayer);
    return currentPlayer + currentWaitingPlayer;
}

// 0x4dd90
bool GameWorldCluster::enterUser(GameWorld*, CliSession*, bool&, WaitInfo&)
{
    LIFT_STUB(0x4dd90);
}

// 0x4e080
bool GameWorldCluster::leaveUser(GameWorld*, CliSession*)
{
    LIFT_STUB(0x4e080);
}

#if !defined(__clang__)
#pragma comment(linker, "/INCLUDE:?giveupWait@GameWorldCluster@@AEAA_NPEAVGameWorld@@_KAEBW4Type@WaitQueue@@AEBF@Z")  // LIFT: keep until the caller is lifted (0x4e310).
#pragma comment(linker, "/INCLUDE:?addGameWorld@GameWorldCluster@@AEAA_NPEAVGameWorld@@@Z")  // LIFT: keep until the caller is lifted (0x4e4f0).
#pragma comment(linker, "/INCLUDE:??0GameWorldRegistry@@QEAA@XZ")  // LIFT: keep until the caller is lifted (0x4e630).
#pragma comment(linker, "/INCLUDE:??1GameWorldRegistry@@QEAA@XZ")  // LIFT: keep until the caller is lifted (0x4e6c0).
#pragma comment(linker, "/INCLUDE:?Get@GameWorldRegistry@@QEAAPEAVGameWorld@@F@Z")  // LIFT: keep until the caller is lifted (0x4e8b0).
#pragma comment(linker, "/INCLUDE:?EnumerateCluster@GameWorldRegistry@@QEAAXAEAV?$vector@PEAVGameWorldCluster@@V?$StlAllocator@PEAVGameWorldCluster@@$01@@@std@@@Z")  // LIFT: keep until the caller is lifted (0x4e900).
#pragma comment(linker, "/INCLUDE:?FetchWorldInfoListForInfoGate@GameWorldRegistry@@QEAA_NPEAVFragmentPacket@@@Z")  // LIFT: keep until the caller is lifted (0x4ead0).
#pragma comment(linker, "/INCLUDE:?getGameWorldCluster@GameWorldRegistry@@AEAAPEAVGameWorldCluster@@F@Z")  // LIFT: keep until the caller is lifted (0x4ebf0).
#pragma comment(linker, "/INCLUDE:?addGameWorldCluster@GameWorldRegistry@@AEAA_NPEAVGameWorldCluster@@@Z")  // LIFT: keep until the caller is lifted (0x4ec90).
#endif

// 0x4e310
bool GameWorldCluster::giveupWait(GameWorld* world, unsigned long long clikey, WaitQueue::Type const& queueType, short const& waitpos)
{
    _lock.Enter();
    bool removed = _waitQueueList.Remove(queueType, waitpos, clikey);
    _lock.Leave();
    if (removed)
    {
        int wid = world != nullptr ? world->GetWid() : 0;
        Log::Write(Log::LT_DEBUG, L"GameWorld.cpp", 677,
            L"[game-world-cluster], giveup wait ok, cli-key:0x%I64X, world-cluster-id:%d, wid:%d, queueType:%d",
            clikey, _db.clusterId, wid, queueType);
    }
    else
    {
        int wid = world != nullptr ? world->GetWid() : 0;
        Log::Write(Log::LT_ERROR, L"GameWorld.cpp", 681,
            L"[game-world-cluster], giveup wait fail; not in wait queue, cli-key:0x%I64X, world-cluster-id:%d, wid:%d, queueType:%d",
            clikey, _db.clusterId, wid, queueType);
    }
    return removed;
}

// 0x4e4f0
bool GameWorldCluster::addGameWorld(GameWorld* world)
{
    if (world != nullptr)
    {
        _worldLock.Enter();
        _worlds.push_back(world);
        _worldLock.Leave();
        Log::Write(Log::LT_DEBUG, L"GameWorld.cpp", 725,
            L"[game-world-cluster], add game-world ok, wid:%d, world-cluster-id:%d",
            world->GetDB().wid, _db.clusterId);
        return true;
    }
    Log::Write(Log::LT_ERROR, L"GameWorld.cpp", 715,
        L"[game-world-cluster], add game-world fail; null param, world-cluster-id:%d", _db.clusterId);
    return false;
}

// 0x4e630
GameWorldRegistry::GameWorldRegistry() : _worlds(nullptr), _min(0), _size(0)
{
}

// 0x4e6c0
GameWorldRegistry::~GameWorldRegistry()
{
    if (_worlds != nullptr)
    {
        for (GameWorld** it = _worlds; it != _worlds + _size; ++it)
        {
            if (*it != nullptr)
            {
                delete *it;
                Memory::_Manager[2]->Free(*it, L"GameWorld.cpp", 744);
            }
        }
        Memory::_Manager[2]->Free(_worlds, L"GameWorld.cpp", 746);
    }
    for (Map::iterator it = _clusterList.begin(); it != _clusterList.end(); ++it)
    {
        GameWorldCluster* cluster = it->second;
        if (cluster != nullptr)
        {
            cluster->~GameWorldCluster();
            Memory::_Manager[2]->Free(cluster, L"GameWorld.cpp", 752);
        }
    }
    _clusterList.clear();
}

// 0x4e8b0
GameWorld* GameWorldRegistry::Get(short wid)
{
    int index = wid - _min;
    if (index >= 0 && index < _size)
        return _worlds[index];
    Log::Write(Log::LT_ERROR, L"GameWorld.cpp", 761,
        L"[game-world-registry], get fail; wid out of range, wid:%d", wid);
    return nullptr;
}

// 0x4e900
void GameWorldRegistry::EnumerateCluster(GameWorldCluster::Vector& out)
{
    _clusterLock.Enter();
    for (Map::iterator it = _clusterList.begin(); it != _clusterList.end(); ++it)
    {
        if (it->second != nullptr)
            out.push_back(it->second);
    }
    _clusterLock.Leave();
}

// 0x4e9b0
bool GameWorldRegistry::FetchWorldInfoList(FragmentPacket* fp)
{
    if (fp == nullptr)
    {
        Log::Write(Log::LT_ERROR, L"GameWorld.cpp", 789,
            L"[game-world-registry], fetch world info list fail; invalid parameter");
        return false;
    }
    GameWorld** it = _worlds;
    GameWorld** end = it + _size;
    Packet::Header* header = fp->packet.CurHeader;
    if (header == nullptr || static_cast<unsigned short>(4000 - header->size) < 2)
        fp->packet.Allocate(&fp->composer);
    fp->composer.PushRepeatCount(&fp->packet);
    for (; it != end; ++it)
    {
        GameWorld* world = *it;
        if (world != nullptr && world->GetDB().use)
        {
            if (!world->FetchWorldInfo(fp))
            {
                Log::Write(Log::LT_ERROR, L"GameWorld.cpp", 804,
                    L"[game-world-registry], fetch world info list fail; fetch fail, wid:%d", world->GetWid());
                return false;
            }
            fp->IncRepeatCount();
        }
    }
    fp->composer.PopRepeatCount();
    return true;
}

// 0x4ead0
bool GameWorldRegistry::FetchWorldInfoListForInfoGate(FragmentPacket* fp)
{
    GameWorld** it = _worlds;
    GameWorld** end = it + _size;
    Packet::Header* header = fp->packet.CurHeader;
    if (header == nullptr || static_cast<unsigned short>(4000 - header->size) < 2)
        fp->packet.Allocate(&fp->composer);
    fp->composer.PushRepeatCount(&fp->packet);
    for (; it != end; ++it)
    {
        GameWorld* world = *it;
        if (world == nullptr)
            continue;
        if (!world->FetchWorldInfoForInfoGate(fp))
        {
            Log::Write(Log::LT_ERROR, L"GameWorld.cpp", 833,
                L"[game-world-registry], fetch world info list for infogate fail; fetch fail, wid:%d", world->GetWid());
            return false;
        }
        fp->IncRepeatCount();
    }
    fp->composer.PopRepeatCount();
    return true;
}

// 0x4ebf0
GameWorldCluster* GameWorldRegistry::getGameWorldCluster(short clusterId)
{
    GameWorldCluster* cluster = nullptr;
    _clusterLock.Enter();
    Map::iterator it = _clusterList.find(clusterId);
    if (it != _clusterList.end())
        cluster = it->second;
    _clusterLock.Leave();
    return cluster;
}

// 0x4ec90
bool GameWorldRegistry::addGameWorldCluster(GameWorldCluster* cluster)
{
    if (cluster == nullptr)
        return false;
    _clusterLock.Enter();
    bool inserted = _clusterList.insert(std::pair<short, GameWorldCluster*>(cluster->GetClusterId(), cluster)).second;
    _clusterLock.Leave();
    return inserted;
}

// 0x4ed00
bool GameWorldRegistry::Setup(short, short)
{
    LIFT_STUB(0x4ed00);
}

// 0x4f330
void GameWorldRegistry::Update()
{
    LIFT_STUB(0x4f330);
}

#if !defined(__clang__)
#pragma comment(linker, "/INCLUDE:??1GameWorldReporter@@UEAA@XZ")  // LIFT: keep until the caller is lifted (0x4f940).
#pragma comment(linker, "/INCLUDE:?Initialize@GameWorldReporter@@QEAA_NP6AXPEAV1@@ZPEAVGameWorldRegistry@@J@Z")  // LIFT: keep until the caller is lifted (0x4f9b0).
#endif

// 0x4f940
GameWorldReporter::~GameWorldReporter()
{
    if (_report != nullptr)
        _report->removeReferenceCount(L"GameWorld.cpp", 1147);
}

// 0x4f9b0
bool GameWorldReporter::Initialize(void (__cdecl* listener)(GameWorldReporter*), GameWorldRegistry* registry, long period)
{
    if (registry != nullptr && period > 0)
    {
        if (_registry != nullptr)
        {
            Log::Write(Log::LT_ERROR, L"GameWorld.cpp", 1158, L"[world-reporter], initialize fail; already initialized");
            return false;
        }
        _registry = registry;
        _period = period;
        _listener = listener;
        return true;
    }
    Log::Write(Log::LT_ERROR, L"GameWorld.cpp", 1153,
        L"[world-reporter], initialize fail; invalid parameter, registry:%p, period:%d(msec)", registry, static_cast<int>(period));
    return false;
}

// 0x4fa30
bool GameWorldReporter::HandleEvent(EventContext*, unsigned long)
{
    if (_run)
    {
        if (WriteReport())
        {
            if (_listener != nullptr)
                _listener(this);
        }
        Daemon::Instance->AddTimer(_period, this);
    }
    return true;
}

// 0x4fa80
bool GameWorldReporter::WriteReport()
{
    if (_registry == nullptr)
    {
        Log::Write(Log::LT_ERROR, L"GameWorld.cpp", 1206,
            L"[world-reporter], write report fail; invalid parameter, registry:%p", static_cast<void*>(nullptr));
        return false;
    }
    void* mem = Memory::_Manager[2]->Alloc(sizeof(GameWorldReport), L"GameWorld.cpp", 1210);
    GameWorldReport* next = mem != nullptr ? ::new (mem) GameWorldReport : nullptr;
    // BUG: The original calls Write even if the allocation fails (0x4fa80).
    if (next == nullptr)
        return false;
    if (!next->Write(_registry))
    {
        Log::Write(Log::LT_ERROR, L"GameWorld.cpp", 1212, L"[world-reporter], write report fail; writing fail");
        next->removeReferenceCount(L"GameWorld.cpp", 1213);
        return false;
    }
    _lock.Enter();
    if (_report != nullptr)
        _report->removeReferenceCount(L"GameWorld.cpp", 1228);
    _report = next;
    next->addReferenceCount(L"GameWorld.cpp", 1233);
    _lock.Leave();
    next->removeReferenceCount(L"GameWorld.cpp", 1219);
    return true;
}

// 0x4fc00
GameWorldReport::~GameWorldReport()
{
    if (_fp != nullptr)
    {
        _fp->~FragmentPacket();
        Memory::_Manager[2]->Free(_fp, L"GameWorld.cpp", 1266);
        _fp = nullptr;
    }
}

// 0x4fc70
bool GameWorldReport::Write(GameWorldRegistry* registry)
{
    if (registry != nullptr)
    {
        if (_fp != nullptr)
        {
            Log::Write(Log::LT_ERROR, L"GameWorld.cpp", 1277, L"[game-world-report], write fail; already written");
            return false;
        }
        void* mem = Memory::_Manager[2]->Alloc(sizeof(FragmentPacket), L"GameWorld.cpp", 1281);
        // BUG: The original dereferences the allocation without a null test (0x4fc70).
        if (mem == nullptr)
            return false;
        _fp = ::new (mem) FragmentPacket(4, "hiChhsQQiihhiQQQQQQQ;");
        _fp->packet.Allocate(&_fp->composer);
        if (registry->FetchWorldInfoList(_fp))
        {
            PacketSplitter* splitter = _fp->packet.Splitter;
            if (splitter != nullptr)
                splitter->Finalize(_fp->packet.CurHeader);
            return true;
        }
        Log::Write(Log::LT_ERROR, L"GameWorld.cpp", 1284, L"[game-world-reporter], write fail; fetch world-info-list fail");
        _fp->~FragmentPacket();
        Memory::_Manager[2]->Free(_fp, L"GameWorld.cpp", 1285);
        _fp = nullptr;
        return false;
    }
    Log::Write(Log::LT_ERROR, L"GameWorld.cpp", 1272,
        L"[game-world-reporter], write fail; invalid parameter, registry:%p", static_cast<void*>(nullptr));
    return false;
}

// 0x4fdc0
Packet const* GameWorldReport::GetPacket() const
{
    if (_fp != nullptr)
        return &_fp->packet;
    return nullptr;
}
