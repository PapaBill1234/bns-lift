// WorldListManager.obj (LobbyGate PDB). Layouts from include/pdb/LobbyGate/types.h.
#pragma once
#include <stddef.h>
#include <windows.h>
#include "RefCntObject.h"
#include "FragmentPacket.h"

struct WorldInfo
{
    short worldId;
    short worldClusterId;
    wchar_t worldName[17];
    short worldType;
    short playType;
    unsigned long publicAddress;
    unsigned long internalAddress;
    short publicPort;
    short mobilePort;
    int worldScore;
    char worldLive;
    char entrance;
    char characterCreation;
    char characterCreationLimitedOnNewAccount;
    char recommend;
    char brandnew;
    char crowdness;
};
static_assert(offsetof(WorldInfo, publicAddress) == 0x2C, "WorldInfo::publicAddress");

class WorldList : public DynamicRefCntObj
{
public:
    // LIFT: The constructor is inlined in WorldListManager::SetWorldList (0x16530).
    WorldList() : _worldInfos(nullptr), _worldCount(0), _fp(25, "hiChhsQQihiQQQQQQQ;") {}
    virtual ~WorldList();  // 0x16200

    bool Set(WorldInfo const* infos, int count);  // 0x16280

    WorldInfo const* _worldInfos;
    int _worldCount;
    FragmentPacket _fp;
};
static_assert(sizeof(WorldList) == 288, "sizeof WorldList");
static_assert(offsetof(WorldList, _fp) == 40, "WorldList::_fp");

class WorldListManager
{
public:
    bool SetWorldList(WorldInfo const* worldList, int worldCount);  // 0x16530

    SRWLOCK _srwLock;
    WorldList* _worldList;
};
static_assert(sizeof(WorldListManager) == 0x10, "sizeof WorldListManager");
