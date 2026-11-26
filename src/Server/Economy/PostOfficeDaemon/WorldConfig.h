// WorldConfig.obj / WorldConfigManager.obj (PostOfficeDaemon PDB). Layouts from include/pdb/PostOfficeDaemon/types.h.
#pragma once
#include <stddef.h>
#include <string.h>
#include <map>
#include "Lock.h"
#include "StlMemory.h"

class XmlDoc;

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
    typedef std::map<unsigned short, WorldConfig*, std::less<unsigned short>,
                     StlAllocator<std::pair<unsigned short, WorldConfig*>, 2> > Container;

    ~WorldConfigList();  // 0xd910

    Container _configList;
};
static_assert(sizeof(WorldConfigList) == 0x20, "sizeof WorldConfigList");

class WorldConfigManager
{
public:
    // PDB constructor, inlined at 0x13d30: the CriticalSection ctor, then memset of the arrays.
    WorldConfigManager()
    {
        memset(_containerList, 0, sizeof(_containerList));
        memset(_arrayBoundary, -1, sizeof(_arrayBoundary));
        memset(_filePath, 0, sizeof(_filePath));
    }

    bool initConfigManager();                                                       // 0xda70
    bool updateWorldList(WorldConfigList const* worldConfigList);                   // 0xdb30
    bool addWorldConfig(unsigned short wid, int bucketIndex, int worldIndex,
                        WorldConfig const* const worldConfig);                      // 0xdfd0
    bool updateWorldConfig(unsigned short wid, int bucketIndex, int worldIndex,
                           WorldConfig const* const worldConfig);                   // 0xe190
    WorldConfig* getWorldConfig(unsigned short const wid);                          // 0xe310
    bool CheckWorldConfig(unsigned short wid, unsigned long ipAddr, unsigned short const port);  // 0xe430
    bool setWorldConfigFilePath();                                                  // 0xe560
    bool loadWorldConfigFile(WorldConfigList* worldConfigList);                     // 0xe5f0
    bool setupWorldConfigList(XmlDoc* const doc, WorldConfigList& worldConfigList);  // 0xe8c0 (PDB: member, not static)
    static bool createWorldConfigFile(wchar_t const* const worldConfigFilePath);     // 0xede0
    static void writeSampleConfigFormat(void* fileHandle);                          // 0xef40
    static bool writeConfigString(void* fileHandle, wchar_t const* const configString);  // 0xeff0

    CriticalSection _reloadLock;
    static int const BUCKET_COUNT = 33;
    static int const ARRAY_SIZE = 1000;

    WorldConfig** _containerList[BUCKET_COUNT];
    int _arrayBoundary[BUCKET_COUNT][2];
    wchar_t _filePath[260];
};
static_assert(sizeof(WorldConfigManager) == 0x440, "sizeof WorldConfigManager");
static_assert(offsetof(WorldConfigManager, _containerList) == 0x28, "WorldConfigManager::_containerList");
static_assert(offsetof(WorldConfigManager, _arrayBoundary) == 0x130, "WorldConfigManager::_arrayBoundary");
static_assert(offsetof(WorldConfigManager, _filePath) == 0x238, "WorldConfigManager::_filePath");
