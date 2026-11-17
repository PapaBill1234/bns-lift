// ClientManager.obj (CacheGate PDB).
#include "ClientManager.h"

#include <winsock2.h>
#include <windows.h>
#include <new>

#include "AlertSender.h"
#include "Log.h"
#include "Memory.h"
#include "MemoryManager.h"
#include "Session.h"

static wchar_t const CLIENT_MANAGER_FILE[] = L"ClientManager.cpp";

// 0x5d60
ClientManager::~ClientManager()
{
    if (_clientMap != nullptr)
    {
        ReleaseAllSession();
        _clientMap->~ClientMap();
        Memory::_Manager[2]->Free(_clientMap, CLIENT_MANAGER_FILE, 19);
    }
    if (_idIndexMap != nullptr)
    {
        _idIndexMap->~IdIndexMap();
        Memory::_Manager[2]->Free(_idIndexMap, CLIENT_MANAGER_FILE, 23);
    }
}

// 0x5e90
bool ClientManager::Initialize()
{
    if (_clientMap != nullptr || _idIndexMap != nullptr)
    {
        Log::Write(Log::LT_ERROR, CLIENT_MANAGER_FILE, 29,
                   L"== CRASH == [client session manager], Initialize;session map already exist.");
        AlertSender::Write(CLIENT_MANAGER_FILE, 29,
                           L"== CRASH == [client session manager], Initialize;session map already exist.");
        return false;
    }

    void* buffer = Memory::_Manager[2]->Alloc(sizeof(IdIndexMap), CLIENT_MANAGER_FILE, 33);
    _idIndexMap = buffer != nullptr ? new (buffer) IdIndexMap() : nullptr;
    if (_idIndexMap == nullptr)
        return false;

    buffer = Memory::_Manager[2]->Alloc(sizeof(ClientMap), CLIENT_MANAGER_FILE, 37);
    _clientMap = buffer != nullptr ? new (buffer) ClientMap() : nullptr;
    if (_clientMap != nullptr)
        return true;

    if (_idIndexMap != nullptr)
        _idIndexMap->~IdIndexMap();
    // BUG: 0x5e90 _idIndexMap is not set to null after Free. The destructor frees it again.
    Memory::_Manager[2]->Free(_idIndexMap, CLIENT_MANAGER_FILE, 39);
    return false;
}

// 0x6050
Session* ClientManager::GetSession(unsigned short wid)
{
    if (_clientMap == nullptr)
        return nullptr;
    _lock.Enter();
    ClientMap::iterator it = _clientMap->find(wid);
    Session* session = nullptr;
    if (it != _clientMap->end())
        session = it->second;
    _lock.Leave();
    return session;
}

// 0x6120
bool ClientManager::AddSession(unsigned short wid, Session const* session)
{
    if (session == nullptr || _clientMap == nullptr)
        return false;
    _lock.Enter();
    Session* target = const_cast<Session*>(session);
    target->addReferenceCount(CLIENT_MANAGER_FILE, 77);
    if (!_clientMap->insert(ClientMap::value_type(wid, target)).second)
    {
        target->removeReferenceCount(CLIENT_MANAGER_FILE, 80);
        _lock.Leave();
        return false;
    }
    bool result = _idIndexMap->insert(IdIndexMap::value_type(session->_id, wid)).second;
    if (!result)
    {
        _clientMap->erase(wid);
        target->removeReferenceCount(CLIENT_MANAGER_FILE, 89);
    }
    _lock.Leave();
    return result;
}

// 0x6250
void ClientManager::ReleaseSession(unsigned long long sessionID)
{
    // BUG: 0x6250 No null check of _idIndexMap and _clientMap (the other functions check).
    _lock.Enter();
    IdIndexMap::iterator idIt = _idIndexMap->find(sessionID);
    if (idIt != _idIndexMap->end())
    {
        unsigned short wid = idIt->second;
        ClientMap::iterator it = _clientMap->find(wid);
        if (it != _clientMap->end())
        {
            if (it->second != nullptr)
                it->second->removeReferenceCount(CLIENT_MANAGER_FILE, 114);
            _clientMap->erase(wid);
            _idIndexMap->erase(sessionID);
        }
    }
    _lock.Leave();
}

// 0x6380
void ClientManager::ReleaseAllSession()
{
    if (_clientMap == nullptr)
        return;
    _lock.Enter();
    for (ClientMap::iterator it = _clientMap->begin(); it != _clientMap->end(); ++it)
    {
        if (it->second != nullptr)
            it->second->removeReferenceCount(CLIENT_MANAGER_FILE, 134);
    }
    _clientMap->clear();
    _idIndexMap->clear();
    _lock.Leave();
}
