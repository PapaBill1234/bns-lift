// GameWorld.obj (LobbyDaemon PDB, 2019 + PDB).
#pragma once
#include "Lock.h"
#include "StlMemory.h"
#include "PerfCounterProvider.h"
#include "RefCntObject.h"
#include "TimerQueue.h"
#include "WaitQueue.h"
#include <map>
#include <vector>

class CliSession;
struct EventContext;
class FragmentPacket;
class GameWorld;
class GameWorldCluster;
class GameWorldRegistry;
class GameWorldReporter;
class Packet;
class Session;
struct WaitInfo;

class GameWorld
{
public:
    struct DB
    {
        short wid;
        short clusterId;
        wchar_t name[33];
        int score;
        char worldType;
        char playType;
        bool use;
        bool entrance;
        bool characterCreationLimited;
        bool characterCreationLimitedOnNewAccount;
        bool recommend;
        bool brandnew;
        char crowdness;
    };

    GameWorld();  // 0x4c820
    virtual ~GameWorld() {}
    // LIFT: The original deleting destructor does not free this placement allocation (0x4c870).
    static void operator delete(void*) {}
    bool Setup(DB*, GameWorldCluster*);  // 0x4c880
    bool Update(DB*);  // 0x4ca30
    virtual short GetWid() const;  // 0x4c810
    virtual bool FetchWorldInfo(FragmentPacket*) const;  // 0x4cc40
    virtual bool FetchWorldInfoForInfoGate(FragmentPacket*) const;  // 0x4ce60
    bool EnterUser(CliSession*, bool&, WaitInfo&);  // 0x4cf40
    bool PermitCharacterManagement(CliSession*, bool);  // 0x4d120
    DB const& GetDB() const { return _db; }
    int GetPlayingUserCount() const { return _playingUserCount; }
    int GetQuickpassUserCount() const { return _quickPassPlayingUserCount; }
    // LIFT: access helper. No PDB in the set has friend records. The handlers read and write _live (HelloReq 0x88260, ServiceOpenNotify 0x88cd0).
    friend bool HandleLobbyGame_HelloReq(Session const*, Packet const*);
    friend bool HandleLobbyGame_ServiceOpenNotify(Session const*, Packet const*);
    // LIFT: access helper. No PDB in the set has friend records. GameServiceLocation::OnEnter (0x3b3d0) and OnLeave
    // (0x3b540) change _playingUserCount. Leave (0x3b9a0) reads _cluster. GamedChannelManager::OnClose (0x80790) writes _live.
    friend class GameServiceLocation;
    friend class GamedChannelManager;
private:
    mutable SRWLOCK _infolock;
    DB _db;
    GameWorldCluster* _cluster;
    int _playingUserCount;
    int _quickPassPlayingUserCount;
    bool volatile _live;
};
static_assert(sizeof(GameWorld::DB) == 0x58, "sizeof GameWorld::DB");
static_assert(sizeof(GameWorld) == 0x80, "sizeof GameWorld");

// LIFT: The setters are inlined in GameWorldCluster::UpdateCounters (0x4dc70).
class WorldClusterCounterSet : public CounterSet
{
public:
    bool SetMaxPlayerCount(unsigned __int64 value) { return setU64(2, value); }
    bool SetCurrentPlayerCount(unsigned __int64 value) { return setU64(3, value); }
    bool SetMaxWaitingCount(unsigned __int64 value) { return setU64(4, value); }
    bool SetCurrentWaitingCount(unsigned __int64 value) { return setU64(5, value); }
};

class GameWorldCluster
{
public:
    struct DB
    {
        short clusterId;
        unsigned long pub_IPv4;
        unsigned long internal_IPv4;
        unsigned short pub_port;
        unsigned short mobile_port;
        int maxPlayerCount;
        int maxWaitingCount;
    };
    typedef std::vector<GameWorldCluster*, StlAllocator<GameWorldCluster*, 2> > Vector;

    GameWorldCluster();  // 0x4d390
    ~GameWorldCluster();  // 0x4d440
    long long UpdateCounters();  // 0x4dc70
    short GetClusterId() const { return _db.clusterId; }
private:
    friend class GameWorld;
    // LIFT: access helper. No PDB in the set has friend records. GameServiceLocation::Leave (0x3b9a0) calls giveupWait and leaveUser.
    friend class GameServiceLocation;
    bool enterUser(GameWorld*, CliSession*, bool&, WaitInfo&);  // 0x4dd90
    bool leaveUser(GameWorld*, CliSession*);  // 0x4e080
    bool giveupWait(GameWorld*, unsigned long long, WaitQueue::Type const&, short const&);  // 0x4e310
    bool addGameWorld(GameWorld*);  // 0x4e4f0

    CriticalSection _lock;
    mutable SRWLOCK _infoLock;
    DB _db;
    int _currentEntranceCount;
    WaitQueueList _waitQueueList;
    CriticalSection _worldLock;
    std::vector<GameWorld*, StlAllocator<GameWorld*, 2> > _worlds;
    WorldClusterCounterSet _counterSet;
};
static_assert(sizeof(GameWorldCluster::DB) == 0x18, "sizeof GameWorldCluster::DB");
static_assert(sizeof(GameWorldCluster) == 0x1B8, "sizeof GameWorldCluster");

class GameWorldRegistry
{
public:
    GameWorldRegistry();  // 0x4e630
    ~GameWorldRegistry();  // 0x4e6c0
    GameWorld* Get(short);  // 0x4e8b0
    void EnumerateCluster(std::vector<GameWorldCluster*, StlAllocator<GameWorldCluster*, 2> >&);  // 0x4e900
    bool FetchWorldInfoList(FragmentPacket*);  // 0x4e9b0
    bool FetchWorldInfoListForInfoGate(FragmentPacket*);  // 0x4ead0
    bool Setup(short, short);  // 0x4ed00
    void Update();  // 0x4f330
    // LIFT: access helper. ServiceOpenNotify (0x88cd0) has Get (0x4e8b0) inlined and reads _worlds, _min and _size.
    friend bool HandleLobbyGame_ServiceOpenNotify(Session const*, Packet const*);
private:
    GameWorldCluster* getGameWorldCluster(short);  // 0x4ebf0
    bool addGameWorldCluster(GameWorldCluster*);  // 0x4ec90
    typedef std::map<short, GameWorldCluster*, std::less<short>, StlAllocator<std::pair<short, GameWorldCluster*>, 2> > Map;
    CriticalSection _clusterLock;
    Map _clusterList;
    GameWorld** _worlds;
    short _min;
    int _size;
};
static_assert(sizeof(GameWorldRegistry) == 0x58, "sizeof GameWorldRegistry");

class GameWorldReport : public DynamicRefCntObj
{
public:
    // LIFT: Inlined in GameWorldReporter::WriteReport (0x4fa80).
    GameWorldReport() : _fp(nullptr) {}
    virtual ~GameWorldReport();  // 0x4fc00
    virtual bool Write(GameWorldRegistry*);  // 0x4fc70
    virtual Packet const* GetPacket() const;  // 0x4fdc0
private:
    FragmentPacket* _fp;
};
static_assert(sizeof(GameWorldReport) == 0x20, "sizeof GameWorldReport");

class GameWorldReporter : public Timer
{
public:
    // LIFT: No separate constructor body in the PDB.
    GameWorldReporter() : _run(false), _period(0), _registry(nullptr), _report(nullptr), _listener(nullptr) {}
    virtual ~GameWorldReporter();  // 0x4f940
    bool Initialize(void (__cdecl*)(GameWorldReporter*), GameWorldRegistry*, long);  // 0x4f9b0
    virtual unsigned int TimerClass() const { return 0; }  // 0x5a0a0 (folded).
    virtual unsigned long long TimerId() const { return 0; }  // 0x5a0a0 (folded).
    virtual bool HandleEvent(EventContext*, unsigned long);  // 0x4fa30
    bool WriteReport();  // 0x4fa80
    // LIFT: GameWorldReporterListener (0x994b0) has an inlined accessor: it takes _lock and adds a reference to _report.
    friend void GameWorldReporterListener(GameWorldReporter*);
private:
    bool volatile _run;
    long _period;
    GameWorldRegistry* _registry;
    GameWorldReport* _report;
    void (__cdecl* _listener)(GameWorldReporter*);
    CriticalSection _lock;
};
static_assert(sizeof(GameWorldReporter) == 0x80, "sizeof GameWorldReporter");
