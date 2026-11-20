// GameWorld.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once

class CliSession;
struct EventContext;
class FragmentPacket;
class GameWorld;
class GameWorldCluster;
class GameWorldRegistry;
class GameWorldReporter;
class Packet;
struct WaitInfo;

class GameWorld
{
public:
    virtual short GetWid() const;  // 0x4c810
    GameWorld();  // 0x4c820
    virtual bool FetchWorldInfo(FragmentPacket*) const;  // 0x4cc40
    virtual bool FetchWorldInfoForInfoGate(FragmentPacket*) const;  // 0x4ce60
    bool EnterUser(CliSession*, bool&, WaitInfo&);  // 0x4cf40
    bool PermitCharacterManagement(CliSession*, bool);  // 0x4d120
};

class GameWorldCluster
{
public:
    GameWorldCluster();  // 0x4d390
    ~GameWorldCluster();  // 0x4d440
    long long UpdateCounters();  // 0x4dc70
private:
    bool enterUser(GameWorld*, CliSession*, bool&, WaitInfo&);  // 0x4dd90
    bool leaveUser(GameWorld*, CliSession*);  // 0x4e080
    bool addGameWorld(GameWorld*);  // 0x4e4f0
};

class GameWorldRegistry
{
public:
    GameWorldRegistry();  // 0x4e630
    ~GameWorldRegistry();  // 0x4e6c0
    GameWorld* Get(short);  // 0x4e8b0
    bool FetchWorldInfoList(FragmentPacket*);  // 0x4e9b0
    bool FetchWorldInfoListForInfoGate(FragmentPacket*);  // 0x4ead0
    bool Setup(short, short);  // 0x4ed00
    void Update();  // 0x4f330
private:
    GameWorldCluster* getGameWorldCluster(short);  // 0x4ebf0
    bool addGameWorldCluster(GameWorldCluster*);  // 0x4ec90
};

class GameWorldReport
{
public:
    virtual ~GameWorldReport();  // 0x4fc00
    virtual bool Write(GameWorldRegistry*);  // 0x4fc70
    virtual Packet const* GetPacket() const;  // 0x4fdc0
};

class GameWorldReporter
{
public:
    virtual ~GameWorldReporter();  // 0x4f940
    bool Initialize(void (__cdecl*)(GameWorldReporter*), GameWorldRegistry*, long);  // 0x4f9b0
    virtual bool HandleEvent(EventContext*, unsigned long);  // 0x4fa30
    bool WriteReport();  // 0x4fa80
};
