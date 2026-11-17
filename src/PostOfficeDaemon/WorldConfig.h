// WorldConfig.obj (PostOfficeDaemon PDB). Layouts from include/pdb/PostOfficeDaemon/types.h.
// Card lift-postofficedaemon-2 declares only the data layout. A later card lifts the functions.
#pragma once
#include <stddef.h>
#include <map>

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
