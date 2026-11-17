// Client.obj (LobbyGate PDB). Layouts from include/pdb/LobbyGate/types.h.
#pragma once
#include <stddef.h>
#include <map>
#include "StlMemory.h"
#include "Channel.h"
#include "Lock.h"
#include "StringUtil.h"
#include "TimerQueue.h"

class Session;
class Packet;
class PacketBuffer;
struct Goods;  // LobbyGatePredefine (later card). sizeof is 0x390.

// ❓ The PDB does not give a module for these structs. Client.obj uses them.
struct CharacterInfo
{
    unsigned long long pcId;
    id128 slotId;
    short worldId;
    wchar_t characterName[33];
    int characterDataSize;
    char* characterData;
    long long lastPlayEndDate;
    char state;
    char jumpingCharacterState;
    int deleteRemainTime;
};
static_assert(sizeof(CharacterInfo) == 0x78, "sizeof CharacterInfo");
static_assert(offsetof(CharacterInfo, characterName) == 0x1A, "CharacterInfo::characterName");
static_assert(offsetof(CharacterInfo, characterData) == 0x60, "CharacterInfo::characterData");
static_assert(offsetof(CharacterInfo, deleteRemainTime) == 0x74, "CharacterInfo::deleteRemainTime");

struct LobbyServiceItem
{
    unsigned long long ownerPcId;
    unsigned long long instanceId;
    unsigned long long labelId;
    unsigned int dataId;
    char state;
};
static_assert(sizeof(LobbyServiceItem) == 0x20, "sizeof LobbyServiceItem");
static_assert(offsetof(LobbyServiceItem, dataId) == 0x18, "LobbyServiceItem::dataId");

struct ServiceEntry
{
    unsigned long long serviceId;
    char serviceKind;
    unsigned long long itemInstanceId;
    id128 targetSlotId;
    short targetWorldId;
    unsigned long long hint1;
};
static_assert(sizeof(ServiceEntry) == 0x38, "sizeof ServiceEntry");
static_assert(offsetof(ServiceEntry, targetSlotId) == 0x18, "ServiceEntry::targetSlotId");
static_assert(offsetof(ServiceEntry, hint1) == 0x30, "ServiceEntry::hint1");

class Client : public Channel
{
public:
    // LIFT: The constructor is inlined in ClientManager::AddClient (0x5f70).
    Client() : _state(0), _broadcast(false), _gateKey(0), _cliKey(0) {}
    virtual ~Client();                                                                     // 0x44d0
    virtual unsigned long long GetId();                                                    // 0x37e0

    bool SendGetCharacterInfoListOk(long long now, short timeZoneBias, CharacterInfo const* characterList,
                                    int characterCount);                                   // 0x4500
    bool SendListGoodsOk(Goods const* goodsList, int goodsCount);                           // 0x4b20
    bool SendTakeGoodsOk(unsigned long long goodsId, LobbyServiceItem const* itemList, int itemCount);  // 0x4ed0
    bool SendListLobbyServiceItemInfoOk(char searchType, unsigned int searchCount, LobbyServiceItem const* itemList,
                                        int itemCount);                                    // 0x5320
    bool SendGetServiceEntryListOk(PacketBuffer* serviceEntryList, int serviceEntryCount);  // 0x5760

    int _state;
    bool _broadcast;
    long long _gateKey;
    long long _cliKey;
};
static_assert(sizeof(Client) == 0x40, "sizeof Client");
static_assert(offsetof(Client, _state) == 0x28, "Client::_state");
static_assert(offsetof(Client, _broadcast) == 0x2C, "Client::_broadcast");
static_assert(offsetof(Client, _gateKey) == 0x30, "Client::_gateKey");
static_assert(offsetof(Client, _cliKey) == 0x38, "Client::_cliKey");

class GateKeyEntry
{
public:
    explicit GateKeyEntry(Session* session);  // LIFT: inlined in GateKeyManager::MakeGateKey (0x3ec0)
    ~GateKeyEntry();                          // 0x3e80

    long long _cliKey;
    Session* _session;
};
static_assert(sizeof(GateKeyEntry) == 0x10, "sizeof GateKeyEntry");

typedef std::map<long long, GateKeyEntry*, std::less<long long>,
                 StlAllocator<std::pair<long long const, GateKeyEntry*>, 2> > GateKeyMap;  // ❓ typedef name
typedef std::map<long long, long long, std::less<long long>,
                 StlAllocator<std::pair<long long const, long long>, 2> > SessionGateKeyMap;  // ❓ typedef name
typedef std::map<long long, Client*, std::less<long long>,
                 StlAllocator<std::pair<long long const, Client*>, 2> > ClientMap;  // ❓ typedef name

class GateKeyManager
{
public:
    bool Initialize(int hashCount);                            // 0x3910
    void Finalize();                                           // 0x3b10
    long long MakeGateKey(Session* session);                   // 0x3ec0
    GateKeyEntry* RemoveGateKey(long long gateKey);            // 0x4170
    GateKeyEntry* GetGKEntry(long long gateKey);               // 0x4330
    long long GetGateKey(unsigned long long sessionId);        // 0x4400

    GateKeyMap* _gkMap;
    CriticalSection* _gkLock;
    SessionGateKeyMap* _sgkMap;
    CriticalSection* _sgkLock;
    long long volatile _tidSeed;
    int _hashCount;
};
static_assert(sizeof(GateKeyManager) == 0x30, "sizeof GateKeyManager");
static_assert(offsetof(GateKeyManager, _tidSeed) == 0x20, "GateKeyManager::_tidSeed");
static_assert(offsetof(GateKeyManager, _hashCount) == 0x28, "GateKeyManager::_hashCount");

class ClientManager
{
public:
    bool Initialize(int hashCount);                                          // 0x5b90
    void Finalize();                                                         // 0x5cf0
    bool AddClient(Session* session, long long gateKey, long long cliKey);   // 0x5f70
    bool RemoveClient(long long cliKey);                                     // 0x60c0
    Client* AcquireClient(long long cliKey);                                 // 0x61e0
    void BroadcastAnnounceNotify(wchar_t const* message);                    // 0x62c0
    int DisconnectAll();                                                     // 0x7180

private:
    bool broadcast(Packet* packet);                                          // 0x6410

public:
    ClientMap* _cliMap;
    CriticalSection* _cliLock;
    int _hashCount;
};
static_assert(sizeof(ClientManager) == 0x18, "sizeof ClientManager");

struct ClientSessionData
{
    long long _lastContentsRuleUpdateTime;
};
static_assert(sizeof(ClientSessionData) == 0x8, "sizeof ClientSessionData");

class ClientSessionHandler : public SessionHandler
{
public:
    virtual bool OnAccept(Session const* session) const;                          // 0x6820
    virtual bool OnConnect(Session const* session, bool firstConnected) const;    // 0x6870
    virtual void OnClose(Session const* session, bool tryReconnect) const;        // 0x68b0
    virtual bool PacketHandler(Session const* session, Packet const* packet) const;  // 0x6b70
    virtual ~ClientSessionHandler();                                              // 0x126e0 (LobbyGate.obj, later card)

    static short SwitchCmdLobbyGateToLobbyDaemon(short lobbyGateCmd);             // 0x6da0
};
static_assert(sizeof(ClientSessionHandler) == 0x8, "sizeof ClientSessionHandler");

class ClientSessionTimerJob : public Timer
{
public:
    // PDB ClientSessionTimerJob::TimerReason (LobbyGate type 0x276C).
    enum TimerReason
    {
        TR_NONE = 0,
        TR_KICK = 1,
        TR_CLOSE_ANONYMOUS = 2,
        TR_CLOSE = 3,
        TR_MAX = 4,
    };

    virtual ~ClientSessionTimerJob();                                    // later card
    virtual unsigned int TimerClass() const;                             // later card
    virtual unsigned long long TimerId() const;                          // 0x27fc0 (LobbyGate.obj, later card)
    virtual bool HandleEvent(EventContext* context, unsigned long numOfBytes);  // 0x6fa0

    unsigned long long _key;
    TimerReason _timerReason;
};
static_assert(sizeof(ClientSessionTimerJob) == 0x48, "sizeof ClientSessionTimerJob");
static_assert(offsetof(ClientSessionTimerJob, _key) == 0x38, "ClientSessionTimerJob::_key");
