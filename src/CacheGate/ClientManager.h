// ClientManager.obj (CacheGate PDB). Layout from include/pdb/CacheGate/types.h.
#pragma once
#include <stddef.h>
#include <map>
#include "Lock.h"
#include "StlMemory.h"

class Session;

class ClientManager
{
public:
    typedef std::map<unsigned short, Session*, std::less<unsigned short>,
                     StlAllocator<std::pair<unsigned short const, Session*>, 2> >
        SessionMap;  // PDB nested type (0x29AE)
    typedef std::map<unsigned long long, unsigned short, std::less<unsigned long long>,
                     StlAllocator<std::pair<unsigned long long const, unsigned short>, 2> >
        IndexMap;  // PDB nested type (0x29B1)

    // LIFT: The constructor is inlined in CacheGate::initialize (0x4510).
    ClientManager() : _clientMap(nullptr), _idIndexMap(nullptr) {}
    ~ClientManager();                                                // 0x5D60

    bool Initialize();                                               // 0x5E90
    Session* GetSession(unsigned short wid);                         // 0x6050
    bool AddSession(unsigned short wid, Session const* session);     // 0x6120
    void ReleaseSession(unsigned long long sessionID);               // 0x6250
    void ReleaseAllSession();                                        // 0x6380

    SessionMap* _clientMap;
    IndexMap* _idIndexMap;
    CriticalSection _lock;
};
static_assert(sizeof(ClientManager) == 0x38, "sizeof ClientManager");
static_assert(offsetof(ClientManager, _lock) == 0x10, "ClientManager::_lock");
