// Client.obj (LobbyGate PDB). Source: .scratch/hr/Client.c
// LIFT: LobbyGate, upper case form build path of StlMemory.h (from the HR strings).
#define LIFT_STLMEMORY_FILE \
    L"E:\\DailyBuild02\\LobbyGate-Common-0.0.348\\depot\\Branch\\348NC\\Program\\Server\\BloodLib\\include\\StlMemory.h"
// LIFT: the original Memory.h (line 181) gives its own placement array new and delete. This stops <new> from giving them.
#define __PLACEMENT_VEC_NEW_INLINE
#include "Daemon.h"
#include "Network.h"
#include <new>
#include <vector>
#include <wchar.h>
#include "Client.h"
#include "Session.h"
#include "Connection.h"
#include "Packet.h"
#include "PacketBuffer.h"
#include "Memory.h"
#include "Log.h"
#include "AlertSender.h"
#include "Security.h"
#include "FragmentPacket.h"
#include "LobbyGate.h"
#include "LobbyDChannel.h"
#include "LobbyGatePacketHandler.h"
#include "LobbyGatePredefine.h"

// PDB S_GTHREAD32 (void*, .tls +0x20). The original operator delete[] only keeps the pointer here. ❓ module of the definition.
__declspec(thread) void* __delv_buf__;

// LIFT: inlined in GateKeyManager::Finalize 0x3b10 and ClientManager::Finalize 0x5cf0. No exe imports ??_V@YAXPEAX@Z.
inline void __cdecl operator delete[](void* p)
{
    __delv_buf__ = p;
}

inline void* __cdecl operator new[](size_t, void* buf) throw()
{
    return buf;
}

// 0x37a0
inline void __cdecl operator delete[](void*, void*)
{
    Log::Write(Log::LT_ERROR,
               L"e:\\dailybuild02\\lobbygate-common-0.0.348\\depot\\branch\\348nc\\program\\server\\bloodlib\\include\\Memory.h",
               181, L"== CRASH == [memory], DO NOT USE THIS DEL OPERATOR");
    AlertSender::Write(
        L"e:\\dailybuild02\\lobbygate-common-0.0.348\\depot\\branch\\348nc\\program\\server\\bloodlib\\include\\Memory.h",
        181, L"== CRASH == [memory], DO NOT USE THIS DEL OPERATOR");
}

// LIFT: placement array new on Memory::_Manager[1] (GateKeyManager::Initialize 0x3910, ClientManager::Initialize 0x5b90).
#define liftArrayNew1(T, count, line) \
    (new (Memory::_Manager[1]->Alloc(sizeof(T) * static_cast<long long>(count) + 8, L"Client.cpp", line)) T[count])

namespace
{
wchar_t const* const CLIENT_FILE = L"Client.cpp";
wchar_t const* const SESSION_FILE = L"source\\Session.cpp";
wchar_t const* const CHANNEL_H_FILE =
    L"E:\\DailyBuild02\\LobbyGate-Common-0.0.348\\depot\\Branch\\348NC\\Program\\Server\\BloodLib\\include\\Channel.h";

// PDB S_UDT ClientList (LobbyGate type 0x2A2F, in ClientManager::DisconnectAll).
typedef std::vector<Client*, StlAllocator<Client*, 2> > ClientList;

// LIFT: inlined FragmentPacket free-size check, e.g. LobbyGate 0x482b-0x485c (4000 - CurHeader->size < need, then Packet::Allocate).
static __forceinline void reserveFragment(FragmentPacket& fp, int need)
{
    Packet::Header const* header = fp.packet.CurHeader;
    unsigned short freeSize = header != nullptr ? static_cast<unsigned short>(4000 - header->size) : 0;
    if (freeSize < need)
        fp.packet.Allocate(&fp.composer);
}

// LIFT: Inlined send preamble of the Client::Send* functions.
static __forceinline Session* acquireSendSession(Client* client, short cmd, int invalidLine, int notConnectedLine)
{
    Session* session = const_cast<Session*>(client->GetSession());
    if (session == nullptr)
    {
        Log::Write(Log::LT_ERROR, CLIENT_FILE, invalidLine,
                   L"[channel], 0x%.16I64X, %I64d, invalid session, send fail, cmd:%d", 0ULL, client->GetId(),
                   static_cast<int>(cmd));
        return nullptr;
    }
    session->_lock.Enter();
    bool connected = session->_state == Session::CONNECTED && session->_connection->_socket != INVALID_SOCKET;
    session->_lock.Leave();
    if (!connected)
    {
        Log::Write(Log::LT_ERROR, CLIENT_FILE, notConnectedLine,
                   L"[channel], 0x%.16I64X, %I64d, is not connected session, send fail, cmd:%d", session->_id,
                   client->GetId(), static_cast<int>(cmd));
        session->removeReferenceCount(CHANNEL_H_FILE, 52);
        return nullptr;
    }
    return session;
}

// LIFT: Inlined fail path of the Client::Send* functions.
static __forceinline bool failSend(Client* client, Session* session, FragmentPacket& fp, short cmd, int line, wchar_t const* format)
{
    Log::Write(Log::LT_ERROR, CLIENT_FILE, line, format, session->_id, client->GetId(), static_cast<int>(cmd));
    session->removeReferenceCount(CHANNEL_H_FILE, 52);
    return false;  // LIFT: the FragmentPacket dtor clears the packet (0x4b20)
}

// LIFT: Inlined end of the Client::Send* functions before the send.
static __forceinline void finalizeFragment(FragmentPacket& fp)
{
    fp.composer.PopRepeatCount();
    if (fp.packet.Splitter != nullptr)
        fp.packet.Splitter->Finalize(fp.packet.CurHeader);
}

// LIFT: Inlined ok path of the Client::Send* functions.
static __forceinline bool okSend(Client* client, Session* session, FragmentPacket& fp, short cmd, int line)
{
    Log::Write(Log::LT_DEBUG, CLIENT_FILE, line, L"[channel], 0x%.16I64X, %I64d, send, cmd:%d", session->_id,
               client->GetId(), static_cast<int>(cmd));
    session->removeReferenceCount(CHANNEL_H_FILE, 52);
    return true;  // LIFT: the FragmentPacket dtor clears the packet (0x4b20)
}
}  // namespace

// 0x37e0
unsigned long long Client::GetId()
{
    return _cliKey;
}

// 0x44d0
Client::~Client()
{
}

// LIFT: inlined in GateKeyManager::MakeGateKey (0x3ec0)
GateKeyEntry::GateKeyEntry(Session* session)
{
    session->addReferenceCount(false, CLIENT_FILE, 39);
    _session = session;
    _cliKey = 0;
}

// 0x3e80
GateKeyEntry::~GateKeyEntry()
{
    if (_session != nullptr)
    {
        _session->removeReferenceCount(CLIENT_FILE, 57);
        _session = nullptr;
        _cliKey = 0;
    }
}

// 0x3910
// LIFT: noinline. The orig calls it out of line at all call sites (LG 0x3910: one call in LobbyGate.c).
__declspec(noinline) bool GateKeyManager::Initialize(int hashCount)
{
    if (hashCount < 1)
        return false;
    _gkMap = liftArrayNew1(GateKeyManager::GKEMapType, hashCount, 86);
    _gkLock = liftArrayNew1(CriticalSection, hashCount, 87);
    _sgkMap = liftArrayNew1(GateKeyManager::SessionGateKeyMapType, hashCount, 89);
    _sgkLock = liftArrayNew1(CriticalSection, hashCount, 90);
    _hashCount = hashCount;
    _tidSeed = 0;
    return true;
}

// 0x3b10
void GateKeyManager::Finalize()
{
    if (_sgkMap != nullptr)
    {
        for (int i = 0; i < _hashCount; ++i)
            _sgkMap[i].clear();
        delete[] _sgkMap;
        Memory::_Manager[1]->Free(__delv_buf__, L"Client.cpp", 107);
        _sgkMap = nullptr;
    }
    if (_sgkLock != nullptr)
    {
        delete[] _sgkLock;
        Memory::_Manager[1]->Free(__delv_buf__, L"Client.cpp", 111);
        _sgkLock = nullptr;
    }
    if (_gkMap != nullptr)
    {
        for (int i = 0; i < _hashCount; ++i)
        {
            for (GateKeyManager::GKEMapType::iterator it = _gkMap[i].begin(); it != _gkMap[i].end(); ++it)
            {
                if (it->second != nullptr)
                {
                    it->second->~GateKeyEntry();
                    Memory::_Manager[2]->Free(it->second, CLIENT_FILE, 121);
                }
            }
            _gkMap[i].clear();
        }
        delete[] _gkMap;
        Memory::_Manager[1]->Free(__delv_buf__, L"Client.cpp", 125);
        _gkMap = nullptr;
    }
    if (_gkLock != nullptr)
    {
        delete[] _gkLock;
        Memory::_Manager[1]->Free(__delv_buf__, L"Client.cpp", 129);
        _gkLock = nullptr;
    }
    _hashCount = 0;
    _tidSeed = 0;
    Log::Write(Log::LT_DEBUG, CLIENT_FILE, 134, L"[GateKeyManager], finalized,");
}

// 0x3ec0
long long GateKeyManager::MakeGateKey(Session* session)
{
    long long gateKey = InterlockedIncrement64(&_tidSeed);
    int index = static_cast<int>(gateKey % _hashCount);
    int sessionIndex = static_cast<int>(session->_id % static_cast<unsigned long long>(_hashCount));

    // LIFT: placement new with throw(). The orig tests the result of the new expression for null (HR 0x3ec0).
    GateKeyEntry* entry = new (Memory::_Manager[2]->Alloc(sizeof(GateKeyEntry), CLIENT_FILE, 149)) GateKeyEntry(session);
    if (entry == nullptr)
        return 0;

    // Orig inserts non-const std::pair values; the sgk lock stays held in the fail path (HR 0x3ec0).
    _gkLock[index].Enter();
    bool inserted = _gkMap[index].insert(std::pair<long long, GateKeyEntry*>(gateKey, entry)).second;
    _gkLock[index].Leave();
    if (!inserted)
    {
        // LIFT: ~GateKeyEntry written out. The orig inlines it here and calls 0x3e80 in the second fail path.
        if (entry->_session != nullptr)
        {
            entry->_session->removeReferenceCount(CLIENT_FILE, 57);
            entry->_session = nullptr;
            entry->_cliKey = 0;
        }
        Memory::_Manager[2]->Free(entry, CLIENT_FILE, 159);
        return 0;
    }

    _sgkLock[sessionIndex].Enter();
    if (!_sgkMap[sessionIndex]
             .insert(std::pair<long long, long long>(static_cast<long long>(session->_id), gateKey))
             .second)
    {
        // LIFT: the orig puts the fail block first (jne to the success block at the end).
        _gkLock[index].Enter();
        GateKeyManager::GKEMapType::iterator it = _gkMap[index].find(gateKey);
        if (it != _gkMap[index].end())
            _gkMap[index].erase(it);
        _gkLock[index].Leave();
        entry->~GateKeyEntry();
        Memory::_Manager[2]->Free(entry, CLIENT_FILE, 180);
        _sgkLock[sessionIndex].Leave();
        return 0;
    }

    _sgkLock[sessionIndex].Leave();
    return gateKey;
}

// 0x4170
GateKeyEntry* GateKeyManager::RemoveGateKey(long long gateKey)
{
    if (gateKey < 1)
        return nullptr;
    int index = static_cast<int>(gateKey % _hashCount);
    GateKeyEntry* entry = nullptr;
    _gkLock[index].Enter();
    GateKeyManager::GKEMapType::iterator it = _gkMap[index].find(gateKey);
    // Orig keeps the gk lock while it erases the sgk entry, with find + erase(it) (HR 0x4170).
    if (it != _gkMap[index].end())
    {
        entry = it->second;
        _gkMap[index].erase(it);
        if (entry != nullptr && entry->_session != nullptr)
        {
            long long sessionId = static_cast<long long>(entry->_session->_id);
            int sessionIndex = static_cast<int>(static_cast<unsigned long long>(sessionId) % static_cast<unsigned long long>(_hashCount));
            _sgkLock[sessionIndex].Enter();
            GateKeyManager::SessionGateKeyMapType::iterator sit = _sgkMap[sessionIndex].find(sessionId);
            if (sit != _sgkMap[sessionIndex].end())
                _sgkMap[sessionIndex].erase(sit);
            _sgkLock[sessionIndex].Leave();
        }
    }
    _gkLock[index].Leave();
    return entry;
}

// 0x4330
GateKeyEntry* GateKeyManager::GetGKEntry(long long gateKey)
{
    int index = static_cast<int>(gateKey % _hashCount);
    GateKeyEntry* entry = nullptr;
    _gkLock[index].Enter();
    GateKeyManager::GKEMapType::iterator it = _gkMap[index].find(gateKey);
    if (it != _gkMap[index].end())
        entry = it->second;
    _gkLock[index].Leave();
    return entry;
}

// 0x4400
long long GateKeyManager::GetGateKey(unsigned long long sessionId)
{
    int index = static_cast<int>(sessionId % static_cast<unsigned long long>(_hashCount));
    long long gateKey = 0;
    _sgkLock[index].Enter();
    GateKeyManager::SessionGateKeyMapType::iterator it = _sgkMap[index].find(static_cast<long long>(sessionId));
    if (it != _sgkMap[index].end())
        gateKey = it->second;
    _sgkLock[index].Leave();
    return gateKey;
}

// 0x4500
bool Client::SendGetCharacterInfoListOk(long long now, short timeZoneBias, CharacterInfo const* characterList,
                                        int characterCount)
{
    short const cmd = 28;
    Session* session = acquireSendSession(this, cmd, 394, 399);
    if (session == nullptr)
        return false;

    FragmentPacket fp(cmd, "hiqhCqohsbqQQi;");
    reserveFragment(fp, 2);
    fp.Compose(2, now, static_cast<int>(timeZoneBias));
    fp.StartRepeat();
    for (int i = 0; i < characterCount; ++i)
    {
        // LIFT: HR 0x4500 leaves the loop at the first failed Compose and runs one fail block after the loop.
        CharacterInfo const& info = characterList[i];
        reserveFragment(fp, 8);
        if (fp.Compose(1, info.pcId) == 0)
            goto composeFail;
        reserveFragment(fp, 16);
        {
            id128 slotId = info.slotId;
            if (fp.Compose(1, &slotId) == 0)
                goto composeFail;
        }
        reserveFragment(fp, 2);
        if (fp.Compose(1, static_cast<int>(info.worldId)) == 0)
            goto composeFail;
        reserveFragment(fp, 0x44);
        if (fp.Compose(1, info.characterName) == 0)
            goto composeFail;
        reserveFragment(fp, info.characterDataSize + 2);
        // 0x4861: r9d = size (+0x5C), r8 = data (+0x60). rdi = info + 0x18.
        if (fp.Compose(1, info.characterData, info.characterDataSize) == 0)
            goto composeFail;
        reserveFragment(fp, 8);
        if (fp.Compose(1, info.lastPlayEndDate) == 0)
            goto composeFail;
        reserveFragment(fp, 1);
        if (fp.Compose(1, static_cast<int>(info.state)) == 0)
            goto composeFail;
        reserveFragment(fp, 1);
        if (fp.Compose(1, static_cast<int>(info.jumpingCharacterState)) == 0)
            goto composeFail;
        reserveFragment(fp, 4);
        if (fp.Compose(1, info.deleteRemainTime) == 0)
            goto composeFail;
        fp.IncRepeatCount();
    }
    goto composeDone;
composeFail:
    return failSend(this, session, fp, cmd, 471, L"[channel], 0x%.16I64X, %I64d, send fail, compose fail, cmd:%d");
composeDone:
    finalizeFragment(fp);
    // Inlined send path A: encrypt the first buffer and send it under the session lock.
    fp.packet.ListHead->encrypt(session->_currentCrypt, session->_security3rd);
    PacketBuffer const* list[1] = {fp.packet.ListHead};
    session->_lock.Enter();
    session->send(list, 1);  // LIFT: LTCG dropped the count. Session::send (0x19360) does not read r8.
    session->_lock.Leave();
    return okSend(this, session, fp, cmd, 464);
}

// 0x4b20
bool Client::SendListGoodsOk(Goods const* goodsList, int goodsCount)
{
    short const cmd = 60;
    Session* session = acquireSendSession(this, cmd, 480, 485);
    if (session == nullptr)
        return false;

    FragmentPacket fp(cmd, "hiCqiQQqqssissbbCiiibb;;");
    reserveFragment(fp, 2);
    fp.StartRepeat();
    if (goodsList != nullptr && goodsCount > 0)
    {
        for (int i = 0; i < goodsCount; ++i)
        {
            if (!const_cast<Goods*>(&goodsList[i])->Fetch(&fp))
                return failSend(this, session, fp, cmd, 501,
                                L"[channel], 0x%.16I64X, %I64d, compose goods fail, send fail, cmd:%d");
            fp.IncRepeatCount();
        }
    }
    finalizeFragment(fp);
    // Inlined send path A: encrypt the first buffer and send it under the session lock.
    fp.packet.ListHead->encrypt(session->_currentCrypt, session->_security3rd);
    PacketBuffer const* list[1] = {fp.packet.ListHead};
    session->_lock.Enter();
    session->send(list, 1);  // LIFT: LTCG dropped the count. Session::send (0x19360) does not read r8.
    session->_lock.Leave();
    return okSend(this, session, fp, cmd, 513);
}

// 0x4ed0
bool Client::SendTakeGoodsOk(unsigned long long goodsId, LobbyServiceItem const* itemList, int itemCount)
{
    short const cmd = 63;
    Session* session = acquireSendSession(this, cmd, 523, 528);
    if (session == nullptr)
        return false;

    FragmentPacket fp(cmd, "hiqCqqqiQ;");
    reserveFragment(fp, 2);
    if (fp.Compose(1, goodsId) == 0)
        return failSend(this, session, fp, cmd, 538, L"[channel], 0x%.16I64X, %I64d, compose goods-id fail, send fail, cmd:%d");
    fp.StartRepeat();
    for (int i = 0; i < itemCount; ++i)
    {
        LobbyServiceItem const& item = itemList[i];
        reserveFragment(fp, 0x1D);
        if (fp.Compose(5, item.ownerPcId, item.instanceId, item.labelId, static_cast<int>(item.dataId),
                       static_cast<int>(item.state)) == 0)
            return failSend(this, session, fp, cmd, 551, L"[channel], 0x%.16I64X, %I64d, compose item fail, send fail, cmd:%d");
        fp.IncRepeatCount();
    }
    finalizeFragment(fp);
    session->Send(&fp.packet);
    return okSend(this, session, fp, cmd, 563);
}

// 0x5320
bool Client::SendListLobbyServiceItemInfoOk(char searchType, unsigned int searchCount, LobbyServiceItem const* itemList,
                                            int itemCount)
{
    short const cmd = 66;
    Session* session = acquireSendSession(this, cmd, 573, 578);
    if (session == nullptr)
        return false;

    FragmentPacket fp(cmd, "hiQiCqqqiQ;");
    reserveFragment(fp, 2);
    if (fp.Compose(2, static_cast<int>(searchType), searchCount) == 0)
        return failSend(this, session, fp, cmd, 587, L"[channel], 0x%.16I64X, %I64d, compose fail, cmd:%d");
    fp.StartRepeat();
    for (int i = 0; i < itemCount; ++i)
    {
        LobbyServiceItem const& item = itemList[i];
        reserveFragment(fp, 0x1D);
        if (fp.Compose(5, item.ownerPcId, item.instanceId, item.labelId, static_cast<int>(item.dataId),
                       static_cast<int>(item.state)) == 0)
            return failSend(this, session, fp, cmd, 600, L"[channel], 0x%.16I64X, %I64d, compose item fail, send fail, cmd:%d");
        fp.IncRepeatCount();
    }
    finalizeFragment(fp);
    session->Send(&fp.packet);
    return okSend(this, session, fp, cmd, 612);
}

// 0x5760
bool Client::SendGetServiceEntryListOk(PacketBuffer* serviceEntryList, int serviceEntryCount)
{
    short const cmd = 72;
    Session* session = acquireSendSession(this, cmd, 622, 627);
    if (session == nullptr)
        return false;

    // PDB: the list type is PacketBuffer*. LobbyGate 0x5a2e steps the list by 0x38 (one ServiceEntry record).
    ServiceEntry const* entryList = reinterpret_cast<ServiceEntry const*>(serviceEntryList);
    FragmentPacket fp(cmd, "hiCqQqohq;");
    reserveFragment(fp, 2);
    fp.StartRepeat();
    for (int i = 0; i < serviceEntryCount; ++i)
    {
        ServiceEntry const& entry = entryList[i];
        reserveFragment(fp, 0x2B);
        id128 targetSlotId = entry.targetSlotId;
        if (fp.Compose(6, entry.serviceId, static_cast<int>(entry.serviceKind), entry.itemInstanceId, &targetSlotId,
                       static_cast<int>(entry.targetWorldId), entry.hint1) == 0)
            return failSend(this, session, fp, cmd, 643,
                            L"[channel], 0x%.16I64X, %I64d, compose service-entry-info fail, send fail, cmd:%d");
        fp.IncRepeatCount();
    }
    finalizeFragment(fp);
    // Inlined send path A: encrypt the first buffer and send it under the session lock.
    fp.packet.ListHead->encrypt(session->_currentCrypt, session->_security3rd);
    PacketBuffer const* list[1] = {fp.packet.ListHead};
    session->_lock.Enter();
    session->send(list, 1);  // LIFT: LTCG dropped the count. Session::send (0x19360) does not read r8.
    session->_lock.Leave();
    return okSend(this, session, fp, cmd, 655);
}

// 0x5b90
// LIFT: noinline. The orig calls it out of line at all call sites (LG 0x5b90: one call in LobbyGate.c).
__declspec(noinline) bool ClientManager::Initialize(int hashCount)
{
    if (hashCount < 1)
        return false;
    _cliMap = liftArrayNew1(ClientManager::CliMapType, hashCount, 679);
    _cliLock = liftArrayNew1(CriticalSection, hashCount, 680);
    _hashCount = hashCount;
    return true;
}

// 0x5cf0
void ClientManager::Finalize()
{
    if (_cliMap != nullptr)
    {
        for (int i = 0; i < _hashCount; ++i)
        {
            _cliLock[i].Enter();
            // LIFT: the orig keeps &_cliMap[i] and it->second in registers (HR 0x5cf0 v5, second).
            ClientManager::CliMapType& cliMap = _cliMap[i];
            for (ClientManager::CliMapType::iterator it = cliMap.begin(); it != cliMap.end(); ++it)
            {
                Client* client = it->second;
                if (client != nullptr)
                {
                    // 0x5d84 calls vtable +0x28 (slot 5, Channel::RemoveSession 0x214d0) with edx = 0 and r8d = 0.
                    client->RemoveSession(nullptr, false);
                    client->removeReferenceCount(CLIENT_FILE, 702);
                }
            }
            cliMap.clear();
            _cliLock[i].Leave();
        }
        delete[] _cliMap;
        Memory::_Manager[1]->Free(__delv_buf__, L"Client.cpp", 709);
        _cliMap = nullptr;
    }
    if (_cliLock != nullptr)
    {
        delete[] _cliLock;
        Memory::_Manager[1]->Free(__delv_buf__, L"Client.cpp", 713);
        _cliLock = nullptr;
    }
    _hashCount = 0;
}

// 0x5f70
bool ClientManager::AddClient(Session* session, long long gateKey, long long cliKey)
{
    void* mem = Memory::_Manager[2]->Alloc(sizeof(Client), CLIENT_FILE, 721);
    if (mem == nullptr)
        return false;
    Client* client = new (mem) Client();
    client->_useDelayedRemove = LobbyGate::_instance->_config->_useChannelDelayedRelease;
    client->_state = 0;
    client->_broadcast = false;
    client->_gateKey = gateKey;
    client->_cliKey = cliKey;

    int index = static_cast<int>(cliKey % _hashCount);
    _cliLock[index].Enter();
    // Orig inserts a non-const std::pair (`_Buynode<std::pair<__int64,Client *>>`); fail block first.
    if (!_cliMap[index].insert(std::pair<long long, Client*>(cliKey, client)).second)
    {
        _cliLock[index].Leave();
        client->removeReferenceCount(CLIENT_FILE, 734);
        return false;
    }
    client->SetSession(session);
    _cliLock[index].Leave();
    return true;
}

// 0x60c0
bool ClientManager::RemoveClient(long long cliKey)
{
    if (cliKey < 1)
        return false;
    bool result = false;
    int index = static_cast<int>(cliKey % _hashCount);
    _cliLock[index].Enter();
    ClientManager::CliMapType::iterator it = _cliMap[index].find(cliKey);
    if (it != _cliMap[index].end())
    {
        if (it->second != nullptr)
        {
            it->second->SetSession(nullptr);
            it->second->removeReferenceCount(CLIENT_FILE, 762);
        }
        _cliMap[index].erase(it);
        result = true;
    }
    _cliLock[index].Leave();
    return result;
}

// 0x61e0
Client* ClientManager::AcquireClient(long long cliKey)
{
    int index = static_cast<int>(cliKey % _hashCount);
    Client* client = nullptr;
    _cliLock[index].Enter();
    ClientManager::CliMapType::iterator it = _cliMap[index].find(cliKey);
    if (it != _cliMap[index].end())
    {
        client = it->second;
        client->addReferenceCount(false, CLIENT_FILE, 785);
    }
    _cliLock[index].Leave();
    return client;
}

// 0x62c0
__declspec(noinline) void ClientManager::BroadcastAnnounceNotify(wchar_t const* message)
{
    if (wcslen(message) == 0)
    {
        Log::Write(Log::LT_ERROR, CLIENT_FILE, 797,
                   L"[client session handler], broadcast announce notify fail; invalid parameter");
        return;
    }
    // LIFT: inlined Packet constructor (0x62c0): zero fill, then one buffer from the thread pool.
    Packet packet = {nullptr, false};
    packet.ListTail = PacketBufferAllocator::_Local->allocate();
    packet.ListHead = packet.ListTail;
    packet.CurHeader = reinterpret_cast<Packet::Header*>(&packet.ListTail->Buffer[8]);
    packet.CurHeader->size = 2;
    if (packet.Compose("hs", 11, message) == 0)
    {
        Log::Write(Log::LT_ERROR, CLIENT_FILE, 806,
                   L"[client session handler], broadcast announce notify fail; compose fail, message:%s", message);
        return;
    }
    if (!broadcast(&packet))
    {
        Log::Write(Log::LT_ERROR, CLIENT_FILE, 812,
                   L"[client session handler], broadcast announce notify fail; broadcast fail, message:%s", message);
        return;
    }
    Log::Write(Log::LT_DEBUG, CLIENT_FILE, 816, L"[client session handler], broadcast announce notify ok, message:%s",
               message);
}

// 0x6410
bool ClientManager::broadcast(Packet* packet)
{
    if (packet->ListHead != nullptr)
        packet->Encrypt(LobbyGate::_instance->_broadcastCrypt.crypt);

    ClientList clients;
    unsigned long long maxSize = 0;
    for (int i = 0; i < _hashCount; ++i)
    {
        if (_cliMap[i].size() > maxSize)
            maxSize = _cliMap[i].size();
    }
    clients.reserve(maxSize);

    for (int i = 0; i < _hashCount; ++i)
    {
        _cliLock[i].Enter();
        for (ClientManager::CliMapType::iterator it = _cliMap[i].begin(); it != _cliMap[i].end(); ++it)
        {
            Client* client = it->second;
            if (client != nullptr && client->_broadcast)
            {
                clients.push_back(client);
                client->addReferenceCount(false, CLIENT_FILE, 916);
            }
        }
        _cliLock[i].Leave();

        for (ClientList::iterator it = clients.begin(); it != clients.end(); ++it)
        {
            Client* client = *it;
            Session* session = const_cast<Session*>(client->GetSession());
            if (session != nullptr)
            {
                packet->ListHead->encrypt(session->_currentCrypt, session->_security3rd);
                PacketBuffer const* list[1] = {packet->ListHead};
                session->_lock.Enter();
                session->send(list, 1);
                session->_lock.Leave();
                session->removeReferenceCount(CHANNEL_H_FILE, 52);
            }
            client->removeReferenceCount(CLIENT_FILE, 933);
        }
        clients.clear();
    }
    return true;
}

// 0x6820
bool ClientSessionHandler::OnAccept(Session const* session) const
{
    ClientSessionData* data =
        static_cast<ClientSessionData*>(Memory::_Manager[2]->Alloc(sizeof(ClientSessionData), CLIENT_FILE, 945));
    if (data != nullptr)
        data->_lastContentsRuleUpdateTime = 0;
    if (session != nullptr)
        const_cast<Session*>(session)->_extraData = data;
    return true;
}

// 0x6870
bool ClientSessionHandler::OnConnect(Session const* session, bool firstConnected) const
{
    Log::Write(Log::LT_ERROR, CLIENT_FILE, 955, L"== CRASH == [client session handler], OnConnect; called ... wrong");
    AlertSender::Write(CLIENT_FILE, 955, L"== CRASH == [client session handler], OnConnect; called ... wrong");
    return false;
}

// 0x68b0
#pragma inline_depth(0)
void ClientSessionHandler::OnClose(Session const* session, bool tryReconnect) const
{
    Session* s = const_cast<Session*>(session);
    if (s != nullptr)
    {
        void* extraData = s->_extraData;
        s->_extraData = nullptr;
        if (extraData != nullptr)
            Memory::_Manager[2]->Free(extraData, CLIENT_FILE, 966);
    }

    // BUG: 0x68b0 reads session->_channel with no null check of session.
    Client* client = nullptr;
    if (s->_channel != nullptr && !s->_waitForRelease)
    {
        s->_channel->addReferenceCount(false, SESSION_FILE, 1051);
        client = static_cast<Client*>(s->_channel);
    }

    if (client != nullptr)
    {
        LobbyGate* lobbyGate = LobbyGate::_instance;
        if (!lobbyGate->_lobbyD->SendLostConnectionNotify(client->GetId()))
            Log::Write(Log::LT_ERROR, CLIENT_FILE, 974,
                       L"[client session handler], OnClose; sendLostConnectionNotify fail, session:0x%I64X, "
                       L"gateKey:0x%I64X, cliKey:0x%I64X",
                       s->_id, client->_gateKey, client->GetId());
        Log::Write(Log::LT_DEBUG, CLIENT_FILE, 977,
                   L"[client session handler], OnClose; authed session:0x%I64X, gateKey:0x%I64X, cliKey:0x%I64X",
                   s->_id, client->_gateKey, client->GetId());
        long long gateKey = client->_gateKey;
        LobbyGate::_instance->_clientManager->RemoveClient(client->GetId());
        GateKeyEntry* entry = LobbyGate::_instance->_gatekeyManager->RemoveGateKey(gateKey);
        if (entry != nullptr)
        {
            // LIFT: ~GateKeyEntry written out; the orig inlines it at 0x68b0 here and calls 0x3e80 in the anonymous branch.
            if (entry->_session != nullptr)
            {
                entry->_session->removeReferenceCount(CLIENT_FILE, 57);
                entry->_session = nullptr;
                entry->_cliKey = 0;
            }
            Memory::_Manager[2]->Free(entry, CLIENT_FILE, 983);
        }
        client->removeReferenceCount(SESSION_FILE, 1059);
    }
    else
    {
        long long gateKey = LobbyGate::_instance->_gatekeyManager->GetGateKey(s->_id);
        if (gateKey > 0)
        {
            if (!LobbyGate::_instance->_lobbyD->SendLostAnonymousConnectionNotify(gateKey))
                Log::Write(Log::LT_ERROR, CLIENT_FILE, 994,
                           L"[client session handler], OnClose; sendLostAnonymousConnectionNotify fail, "
                           L"session:0x%I64X, gateKey:0x%I64X",
                           s->_id, gateKey);
            GateKeyEntry* entry = LobbyGate::_instance->_gatekeyManager->RemoveGateKey(gateKey);
            if (entry != nullptr)
            {
                entry->~GateKeyEntry();
                Memory::_Manager[2]->Free(entry, CLIENT_FILE, 999);
            }
        }
        Log::Write(Log::LT_DEBUG, CLIENT_FILE, 1002,
                   L"[client session handler], OnClose; not authed session:0x%I64X, gateKey:0x%I64X", s->_id,
                   gateKey);
    }
}
#pragma inline_depth()

// 0x6b70
bool ClientSessionHandler::PacketHandler(Session const* session, Packet const* packet) const
{
    // The command is the short after the packet header.
    short const* const pCmd = &packet->CurHeader[1].size;
    if (*pCmd >= 0 && *pCmd < 0x6E)
    {
        Daemon::PacketHandler handler =
            reinterpret_cast<Daemon::PacketHandler>(AnyAuthedLobbyGatePacketHandlerList[*pCmd]);
        if (handler != nullptr)
            return handler(session, packet);
    }

    // LIFT: Inlined Session::GetChannel with the add-ref (Session.cpp line 1051).
    if (session->_channel != nullptr && !session->_waitForRelease)
    {
        session->_channel->addReferenceCount(false, SESSION_FILE, 1051);
        Client* client = static_cast<Client*>(session->_channel);
        // BUG: 0x6b70 no release of the channel reference when Client::_state is not 1.
        if (client != nullptr && client->_state == 1)
        {
            if (*pCmd == 9)
            {
                Log::Write(Log::LT_DEBUG, L"LobbyGatePacketHandler.cpp", 31,
                           L"[lobbygate], ping recv ok, SessionId:0x%I64X", session->_id);
                client->removeReferenceCount(SESSION_FILE, 1059);
                return true;
            }
            // BUG: 0x6b70 index 0x6E is out of bounds for the 110 entries of AuthedLobbyGatePacketHandlerList.
            if (*pCmd >= 0 && *pCmd <= 0x6E && AuthedLobbyGatePacketHandlerList[*pCmd] != nullptr)
            {
                bool result;
                if (*pCmd == 24)
                    result = HandleLobbyGate_GetWorldInfoListReq(client, packet);
                else if (*pCmd == 103)
                    result = HandleLobbyGate_GetPcCafeMileageFeverTimeScheduleListReq(client, packet);
                else
                    result = HandleLobbyGate_BypassPacket(client, packet);
                client->removeReferenceCount(SESSION_FILE, 1059);
                return result;
            }
            Log::Write(Log::LT_ERROR, CLIENT_FILE, 1034, L"%I64X[%I64X], Unknown packet command %d", session->_id,
                       client->GetId(), static_cast<int>(*pCmd));
            client->removeReferenceCount(SESSION_FILE, 1059);
            return false;
        }
    }

    // BUG: 0x6b70 index 0x6E is out of bounds for the 110 entries of NotAuthedLobbyGatePacketHandlerList.
    if (*pCmd >= 0 && *pCmd <= 0x6E)
    {
        Daemon::PacketHandler handler =
            reinterpret_cast<Daemon::PacketHandler>(NotAuthedLobbyGatePacketHandlerList[*pCmd]);
        if (handler != nullptr)
            return handler(session, packet);
    }
    Log::Write(Log::LT_ERROR, CLIENT_FILE, 1066, L"%I64X[N/A], Unknown packet command %d", session->_id,
               static_cast<int>(*pCmd));
    return false;
}

// 0x6da0
short ClientSessionHandler::SwitchCmdLobbyGateToLobbyDaemon(short lobbyGateCmd)
{
    switch (lobbyGateCmd)
    {
    case 12: return 23;
    case 13: return 24;
    case 17: return 28;
    case 20: return 31;
    case 27: return 35;
    case 30: return 38;
    case 36: return 44;
    case 39: return 47;
    case 41: return 41;
    case 43: return 51;
    case 46: return 54;
    case 49: return 57;
    case 52: return 60;
    case 56: return 64;
    case 59: return 67;
    case 62: return 70;
    case 65: return 73;
    case 68: return 76;
    case 71: return 79;
    case 74: return 82;
    case 77: return 85;
    case 80: return 88;
    case 83: return 91;
    case 86: return 94;
    case 89: return 97;
    case 92: return 100;
    case 95: return 103;
    case 98: return 106;
    default: return 0;
    }
}

// 0x6fa0
bool ClientSessionTimerJob::HandleEvent(EventContext* context, unsigned long numOfBytes)
{
    // LIFT: 0x6fca (client.cpp:1145) the original has a second range test after the first one (1136).
    // BUG: 0x6fa0 the second test can never be true (`&&` where `||` is meant). It has no effect; the first test holds.
    if (_key != 0 && _timerReason > TR_NONE && _timerReason < TR_MAX &&
        !(_timerReason < TR_KICK && _timerReason > TR_CLOSE))
    {
        GateKeyManager* gatekeyManager = LobbyGate::_instance->_gatekeyManager;
        if (gatekeyManager == nullptr)
        {
            // BUG: 0x6fa0 the arguments (key, reason) do not agree with the format (one %d).
            Log::Write(Log::LT_ERROR, CLIENT_FILE, 1151, L"[TimerJob], timer expired, invalid gatekeyManger, timerReason:%d",
                       _key, _timerReason);
        }
        else
        {
            GateKeyEntry* entry = gatekeyManager->RemoveGateKey(static_cast<long long>(_key));
            if (entry == nullptr)
            {
                Log::Write(Log::LT_ERROR, CLIENT_FILE, 1158,
                           L"[TimerJob], timer expired, invalid gatekeyManger, key:0x%I64X, timerReason:%d", _key,
                           _timerReason);
            }
            else if (entry->_cliKey != 0)
            {
                // LIFT: 0x6fa0 keeps cliKey in a register and reads _instance->_clientManager again for RemoveClient.
                long long const cliKey = entry->_cliKey;
                ClientManager* const clientManager = LobbyGate::_instance->_clientManager;
                Client* client = clientManager->AcquireClient(cliKey);
                if (client != nullptr)
                {
                    Session* session = const_cast<Session*>(client->GetSession());
                    if (session != nullptr)
                    {
                        LobbyGate::_instance->_clientManager->RemoveClient(cliKey);
                        session->Close(false);
                        session->removeReferenceCount(CLIENT_FILE, 1179);
                    }
                    client->removeReferenceCount(CLIENT_FILE, 1181);
                }
                entry->~GateKeyEntry();
                Memory::_Manager[2]->Free(entry, CLIENT_FILE, 1183);
            }
            else
            {
                if (entry->_session != nullptr)
                    entry->_session->Close(false);
                entry->~GateKeyEntry();
                Memory::_Manager[2]->Free(entry, CLIENT_FILE, 1194);
            }
        }
    }
    removeReferenceCount(CLIENT_FILE, 1199);
    return true;
}

// 0x7180
int ClientManager::DisconnectAll()
{
    int count = 0;
    ClientList clients;
    unsigned long long maxSize = 0;
    for (int i = 0; i < _hashCount; ++i)
    {
        if (_cliMap[i].size() > maxSize)
            maxSize = _cliMap[i].size();
    }
    clients.reserve(maxSize);

    for (int i = 0; i < _hashCount; ++i)
    {
        _cliLock[i].Enter();
        for (ClientManager::CliMapType::iterator it = _cliMap[i].begin(); it != _cliMap[i].end(); ++it)
        {
            if (it->second != nullptr)
            {
                clients.push_back(it->second);
                it->second->addReferenceCount(false, CLIENT_FILE, 1229);
            }
        }
        _cliLock[i].Leave();

        for (ClientList::iterator it = clients.begin(); it != clients.end(); ++it)
        {
            Client* client = *it;
            Session* session = const_cast<Session*>(client->GetSession());
            if (session != nullptr)
            {
                unsigned long long sessionId = session->_id;
                session->removeReferenceCount(CHANNEL_H_FILE, 52);
                if (sessionId != 0)
                {
                    Log::Write(Log::LT_DEBUG, CLIENT_FILE, 1252,
                               L"[lobbygate], disconnect session, gateKey:0x%I64x, cliKey:0x%I64x, sessionId:0x%I64x",
                               client->_gateKey, client->GetId(), sessionId);
                    Network::CloseSession(sessionId, false);
                }
            }
            client->removeReferenceCount(CLIENT_FILE, 1256);
        }
        count += static_cast<unsigned int>(clients.size());
        clients.clear();
    }
    return count;
}
