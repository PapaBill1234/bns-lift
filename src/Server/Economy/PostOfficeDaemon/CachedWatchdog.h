// CachedWatchdog.obj (PostOfficeDaemon PDB). Layouts from include/pdb/PostOfficeDaemon/types.h.
#pragma once
#include <stddef.h>
#include "Lock.h"
#include "PingGenerator.h"

class WorldConfigList;

class CachedWatchdog
{
public:
    enum ServiceState
    {
        SERVICE_STATE_UNAVAILABLE = 0,
        SERVICE_STATE_AVAILABLE = 1,
    };

    explicit CachedWatchdog(unsigned short wid);  // 0x3d20

    bool addTimer(bool const startup);                 // 0x3dc0
    void setServiceState(ServiceState const newState); // 0x3e80

    unsigned short const _wid;
    ServiceState _serviceState;
    PingGenerator* _pingGenerator;
};
static_assert(sizeof(CachedWatchdog) == 0x10, "sizeof CachedWatchdog");
static_assert(offsetof(CachedWatchdog, _serviceState) == 0x4, "CachedWatchdog::_serviceState");
static_assert(offsetof(CachedWatchdog, _pingGenerator) == 0x8, "CachedWatchdog::_pingGenerator");

class CachedWatchdogManager
{
public:
    bool initWatchdogManager(WorldConfigList const* worldConfigList);  // 0x3f00
    bool updateWorldList(WorldConfigList const* worldConfigList);      // 0x4310
    bool addCachedWatchdog(unsigned short wid, int bucketIndex, int worldIndex);  // 0x46b0
    CachedWatchdog* const getCachedWatchdog(unsigned short const wid) const;  // 0x48b0
    void SetServiceState(unsigned short wid, CachedWatchdog::ServiceState const newState);  // 0x49d0
    void SetAllServiceState(CachedWatchdog::ServiceState const newState);           // 0x4a50
    bool AddNextPing(unsigned short wid);                             // 0x4b60
    unsigned long long const GetCurrentPingSeq(unsigned short const wid) const;  // inlined in 0xabd0

    static int const BUCKET_COUNT = 33;
    static int const ARRAY_SIZE = 1000;

    CriticalSection _reloadLock;
    CachedWatchdog** _containerList[BUCKET_COUNT];
    int _arrayBoundary[BUCKET_COUNT][2];

    // PDB constructor, inlined at 0x13d30: the CriticalSection ctor, then memset of the arrays.
    CachedWatchdogManager()
    {
        memset(_containerList, 0, sizeof(_containerList));
        memset(_arrayBoundary, -1, sizeof(_arrayBoundary));
    }
};
static_assert(sizeof(CachedWatchdogManager) == 0x238, "sizeof CachedWatchdogManager");
static_assert(offsetof(CachedWatchdogManager, _containerList) == 0x28, "CachedWatchdogManager::_containerList");
static_assert(offsetof(CachedWatchdogManager, _arrayBoundary) == 0x130, "CachedWatchdogManager::_arrayBoundary");
