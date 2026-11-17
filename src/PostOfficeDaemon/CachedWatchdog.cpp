// CachedWatchdog.obj (PostOfficeDaemon PDB).
#include "CachedWatchdog.h"
#include <new>
#include <windows.h>
#include "Log.h"
#include "AlertSender.h"
#include "Memory.h"
#include "PostOfficeDaemon.h"
#include "WorldConfig.h"

#define CACHED_WATCHDOG_FILE L"CachedWatchdog.cpp"
static wchar_t const* const MODULE_NAME = L"cached watchdog";  // PDB MODULE_NAME

#define CACHED_WATCHDOG_CRASH(line, fmt, ...)                                  \
    do                                                                         \
    {                                                                          \
        Log::Write(Log::LT_ERROR, CACHED_WATCHDOG_FILE, line, fmt, __VA_ARGS__); \
        AlertSender::Write(CACHED_WATCHDOG_FILE, line, fmt, __VA_ARGS__);      \
    } while (0)

static bool isStopState(int state)  // LIFT: inlined switch
{
    return state == Daemon::STATE_STOPPED || state == Daemon::STATE_STOPPING ||
           state == Daemon::STATE_COOLDOWNING || state == Daemon::STATE_COOLDOWNED;
}

// 0x54a70 (folded, ICF)
unsigned int PingGenerator::TimerClass() const
{
    return 1;
}

// 0x5d860 (folded, ICF)
unsigned long long PingGenerator::TimerId() const
{
    return 0;
}

// 0x3d20
CachedWatchdog::CachedWatchdog(unsigned short wid)
    : _wid(wid), _serviceState(SERVICE_STATE_UNAVAILABLE), _pingGenerator(nullptr)
{
    void* const memory = Memory::_Manager[2]->Alloc(sizeof(PingGenerator), CACHED_WATCHDOG_FILE, 26);
    _pingGenerator = memory != nullptr ? ::new (memory) PingGenerator(_wid) : nullptr;
}

// 0x3dc0
bool CachedWatchdog::addTimer(bool const startup)
{
    if (isStopState(Daemon::Instance->State))
        return true;

    long const elapse = startup ? 1000 : 1000 * PostOfficeDaemon::_instance->_config->_pingInterval;
    if (PostOfficeDaemon::_instance->AddTimer(elapse, _pingGenerator))
        return true;

    Log::Write(Log::LT_ERROR, CACHED_WATCHDOG_FILE, 43, L"[%s], %s; failed to add ping generator timer, wid:%u",
               MODULE_NAME, L"CachedWatchdog::addTimer", _wid);
    return false;
}

// 0x3e80
void CachedWatchdog::setServiceState(ServiceState const newState)
{
    long volatile* const state = reinterpret_cast<long volatile*>(&_serviceState);
    if (InterlockedCompareExchange(state, newState == SERVICE_STATE_AVAILABLE, newState != SERVICE_STATE_AVAILABLE) !=
        newState)
    {
        Log::Write(Log::LT_NOTICE, CACHED_WATCHDOG_FILE, 58, L"[%s], %s; [wid:%u] current cached service state:%s",
                   MODULE_NAME, L"CachedWatchdog::setServiceState", _wid,
                   newState == SERVICE_STATE_AVAILABLE ? L"available" : L"unavailable");
    }
}

// 0x3f00
bool CachedWatchdogManager::initWatchdogManager(WorldConfigList const* worldConfigList)
{
    AutoCS lock(&_reloadLock);
    for (WorldConfigList::Container::const_iterator it = worldConfigList->_configList.begin();
         it != worldConfigList->_configList.end(); ++it)
    {
        unsigned short const wid = it->first;
        int const bucketIndex = wid / ARRAY_SIZE;
        int const worldIndex = wid % ARRAY_SIZE;
        if (bucketIndex >= BUCKET_COUNT)
        {
            Log::Write(Log::LT_ERROR, CACHED_WATCHDOG_FILE, 107,
                       L"[%s], %s; wid out of range, wid:%u, bucketIndex:%d, bucketCount:%d", MODULE_NAME,
                       L"CachedWatchdogManager::initWatchdogManager", wid, bucketIndex, BUCKET_COUNT);
            return false;
        }

        if (_containerList[bucketIndex] == nullptr)
            _containerList[bucketIndex] = static_cast<CachedWatchdog**>(
                Memory::_Manager[2]->AllocZero(sizeof(CachedWatchdog*) * ARRAY_SIZE, CACHED_WATCHDOG_FILE, 112));

        if (_containerList[bucketIndex][worldIndex] != nullptr)
        {
            Log::Write(Log::LT_ERROR, CACHED_WATCHDOG_FILE, 122,
                       L"[%s], %s; cached watchdog already exists, wid:%u, bucketIndex:%d, worldIndex:%d",
                       MODULE_NAME, L"CachedWatchdogManager::initWatchdogManager", wid, bucketIndex, worldIndex);
            return false;
        }

        if (!addCachedWatchdog(wid, bucketIndex, worldIndex))
        {
            CACHED_WATCHDOG_CRASH(117,
                                  L"== CRASH == [%s], %s; failed to add cached watchdog, wid:%u, bucketIndex:%d, worldIndex:%d",
                                  MODULE_NAME, L"CachedWatchdogManager::initWatchdogManager", wid, bucketIndex,
                                  worldIndex);
            return false;
        }
    }
    return true;
}

// 0x4310
bool CachedWatchdogManager::updateWorldList(WorldConfigList const* worldConfigList)
{
    AutoCS lock(&_reloadLock);
    for (WorldConfigList::Container::const_iterator it = worldConfigList->_configList.begin();
         it != worldConfigList->_configList.end(); ++it)
    {
        unsigned short const wid = it->first;
        int const bucketIndex = wid / ARRAY_SIZE;
        int const worldIndex = wid % ARRAY_SIZE;
        if (bucketIndex >= BUCKET_COUNT)
        {
            Log::Write(Log::LT_ERROR, CACHED_WATCHDOG_FILE, 147,
                       L"[%s], %s; wid out of range, wid:%u, bucketIndex:%d, bucketCount:%d", MODULE_NAME,
                       L"CachedWatchdogManager::updateWorldList", wid, bucketIndex, BUCKET_COUNT);
            return false;
        }

        if (_containerList[bucketIndex] == nullptr)
            _containerList[bucketIndex] = static_cast<CachedWatchdog**>(
                Memory::_Manager[2]->AllocZero(sizeof(CachedWatchdog*) * ARRAY_SIZE, CACHED_WATCHDOG_FILE, 152));

        if (_containerList[bucketIndex][worldIndex] == nullptr && !addCachedWatchdog(wid, bucketIndex, worldIndex))
        {
            CACHED_WATCHDOG_CRASH(157,
                                  L"== CRASH == [%s], %s; failed to add cached watchdog, wid:%u, bucketIndex:%d, worldIndex:%d",
                                  MODULE_NAME, L"CachedWatchdogManager::updateWorldList", wid, bucketIndex,
                                  worldIndex);
            return false;
        }
    }
    lock.Leave();

    Log::Write(Log::LT_DEBUG, CACHED_WATCHDOG_FILE, 164,
               L"[%s], %s; succeeded to update world list of cached watchdog manager", MODULE_NAME,
               L"CachedWatchdogManager::updateWorldList");
    return true;
}

// 0x46b0
bool CachedWatchdogManager::addCachedWatchdog(unsigned short wid, int bucketIndex, int worldIndex)
{
    if (wid == 0 || bucketIndex >= BUCKET_COUNT || worldIndex >= ARRAY_SIZE)
    {
        CACHED_WATCHDOG_CRASH(172, L"== CRASH == [%s], %s; invalid parameter, wid:%u, bucketIndex:%d, worldIndex:%d",
                              MODULE_NAME, L"CachedWatchdogManager::addCachedWatchdog", wid, bucketIndex,
                              worldIndex);
        return false;
    }

    void* const memory = Memory::_Manager[2]->Alloc(sizeof(CachedWatchdog), CACHED_WATCHDOG_FILE, 176);
    CachedWatchdog* const cachedWatchdog = memory != nullptr ? ::new (memory) CachedWatchdog(wid) : nullptr;
    _containerList[bucketIndex][worldIndex] = cachedWatchdog;

    int* const boundary = _arrayBoundary[bucketIndex];
    if (boundary[0] == -1 || boundary[0] > worldIndex)
        boundary[0] = worldIndex;
    if (boundary[1] < worldIndex)
        boundary[1] = worldIndex;

    // BUG: 0x46b0 cachedWatchdog can be null here (Alloc failed); the call does not check it.
    if (!cachedWatchdog->addTimer(true))
    {
        CACHED_WATCHDOG_CRASH(188, L"== CRASH == [%s], %s; failed to add timer, wid:%u", MODULE_NAME,
                              L"CachedWatchdogManager::addCachedWatchdog", wid);
        return false;
    }

    Log::Write(Log::LT_DEBUG, CACHED_WATCHDOG_FILE, 192,
               L"[%s], %s; succeeded to add cached watchdog, wid:%u, bucketIndex:%d, worldIndex:%d", MODULE_NAME,
               L"CachedWatchdogManager::addCachedWatchdog", wid, bucketIndex, worldIndex);
    return true;
}

// 0x48b0
CachedWatchdog* const CachedWatchdogManager::getCachedWatchdog(unsigned short const wid) const
{
    if (wid == 0)
    {
        Log::Write(Log::LT_ERROR, CACHED_WATCHDOG_FILE, 200, L"[%s], %s; invalid parameter, wid:%u", MODULE_NAME,
                   L"CachedWatchdogManager::getCachedWatchdog", 0);
        return nullptr;
    }

    int const bucketIndex = wid / ARRAY_SIZE;
    if (bucketIndex >= BUCKET_COUNT)
    {
        Log::Write(Log::LT_ERROR, CACHED_WATCHDOG_FILE, 210,
                   L"[%s], %s; wid out of range, wid:%u, bucketIndex:%d, bucketCount:%d", MODULE_NAME,
                   L"CachedWatchdogManager::getCachedWatchdog", wid, bucketIndex, BUCKET_COUNT);
        return nullptr;
    }

    if (_containerList[bucketIndex] == nullptr)
    {
        Log::Write(Log::LT_ERROR, CACHED_WATCHDOG_FILE, 215, L"[%s], %s; no such container list, wid:%u, bucketIndex:%d",
                   MODULE_NAME, L"CachedWatchdogManager::getCachedWatchdog", wid, bucketIndex);
        return nullptr;
    }

    return _containerList[bucketIndex][wid - ARRAY_SIZE * bucketIndex];
}

// 0x49d0
void CachedWatchdogManager::SetServiceState(unsigned short wid, CachedWatchdog::ServiceState const newState)
{
    CachedWatchdog* const cachedWatchdog = getCachedWatchdog(wid);
    if (cachedWatchdog == nullptr)
    {
        Log::Write(Log::LT_ERROR, CACHED_WATCHDOG_FILE, 237, L"[%s], %s; no such cached watchdog, wid:%u, cachedWatchdog:0x%p",
                   MODULE_NAME, L"CachedWatchdogManager::SetServiceState", wid, static_cast<CachedWatchdog*>(nullptr));
        return;
    }
    cachedWatchdog->setServiceState(newState);
}

// 0x4a50
void CachedWatchdogManager::SetAllServiceState(CachedWatchdog::ServiceState const newState)
{
    for (int bucketIndex = 0; bucketIndex < BUCKET_COUNT; ++bucketIndex)
    {
        for (int worldIndex = _arrayBoundary[bucketIndex][0];
             worldIndex != -1 && worldIndex <= _arrayBoundary[bucketIndex][1]; ++worldIndex)
        {
            CachedWatchdog* const cachedWatchdog = _containerList[bucketIndex][worldIndex];
            if (cachedWatchdog != nullptr)
                cachedWatchdog->setServiceState(newState);  // ❓ the binary has UNAVAILABLE as a constant here
        }
    }

    Log::Write(Log::LT_NOTICE, CACHED_WATCHDOG_FILE, 256, L"[%s], %s; [all] current cached service state:%s",
               MODULE_NAME, L"CachedWatchdogManager::SetAllServiceState",
               newState == CachedWatchdog::SERVICE_STATE_AVAILABLE ? L"available" : L"unavailable");  // ❓ the binary has "unavailable"
}

// 0x4b60
bool CachedWatchdogManager::AddNextPing(unsigned short wid)
{
    CachedWatchdog* const cachedWatchdog = getCachedWatchdog(wid);
    if (cachedWatchdog == nullptr)
    {
        Log::Write(Log::LT_ERROR, CACHED_WATCHDOG_FILE, 263, L"[%s], %s; no such cached watchdog, wid:%u, cachedWatchdog:0x%p",
                   MODULE_NAME, L"CachedWatchdogManager::AddNextPing", wid, static_cast<CachedWatchdog*>(nullptr));
        return false;
    }
    return cachedWatchdog->addTimer(false);
}

// LIFT: inlined in PingRelayContext::processRelayResponse (0xabd0). The name comes from the log text.
unsigned long long const CachedWatchdogManager::GetCurrentPingSeq(unsigned short const wid) const
{
    CachedWatchdog* const cachedWatchdog = getCachedWatchdog(wid);
    if (cachedWatchdog == nullptr)
    {
        Log::Write(Log::LT_ERROR, CACHED_WATCHDOG_FILE, 274, L"[%s], %s; no such cached watchdog, wid:%u, cachedWatchdog:0x%p",
                   MODULE_NAME, L"CachedWatchdogManager::GetCurrentPingSeq", wid, static_cast<CachedWatchdog*>(nullptr));
        return 0;
    }
    return cachedWatchdog->_pingGenerator->_pingSeq;
}
