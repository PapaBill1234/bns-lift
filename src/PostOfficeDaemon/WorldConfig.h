// WorldConfig.obj (PostOfficeDaemon PDB). Layouts from include/pdb/PostOfficeDaemon/types.h.
// Card lift-postofficedaemon-2 declares only the data layout. A later card lifts the functions.
#pragma once
#include <stddef.h>
#include <map>
#include "Lock.h"

class WorldConfig
{
public:
    unsigned short _wid;
    unsigned long _ipAddress;
    unsigned short _port;
};
static_assert(sizeof(WorldConfig) == 0xC, "sizeof WorldConfig");
static_assert(offsetof(WorldConfig, _ipAddress) == 0x4, "WorldConfig::_ipAddress");
static_assert(offsetof(WorldConfig, _port) == 0x8, "WorldConfig::_port");

class WorldConfigList
{
public:
    std::map<unsigned short, WorldConfig*> _configList;
};
static_assert(sizeof(WorldConfigList) == 0x20, "sizeof WorldConfigList");

class WorldConfigManager
{
public:
    bool CheckWorldConfig(unsigned short wid, unsigned long ipAddr, unsigned short const port);  // 0xe430 (later card)

    CriticalSection _reloadLock;
    WorldConfig** _containerList[33];
    int _arrayBoundary[33][2];
    wchar_t _filePath[260];

private:
    WorldConfigManager();  // later card (PostOfficeDaemon)
};
static_assert(sizeof(WorldConfigManager) == 0x440, "sizeof WorldConfigManager");
static_assert(offsetof(WorldConfigManager, _containerList) == 0x28, "WorldConfigManager::_containerList");
static_assert(offsetof(WorldConfigManager, _arrayBoundary) == 0x130, "WorldConfigManager::_arrayBoundary");
static_assert(offsetof(WorldConfigManager, _filePath) == 0x238, "WorldConfigManager::_filePath");
