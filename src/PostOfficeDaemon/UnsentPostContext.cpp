// UnsentPostContext.obj (PostOfficeDaemon PDB).
#include "UnsentPostContext.h"
#include <new>
#include <windows.h>
#include "Log.h"
#include "AlertSender.h"
#include "Memory.h"
#include "WorldConfig.h"
#include "PostOfficeDaemon.h"
#include "PostOfficeDB.h"
#include "PostContext.h"
#include "PostDeliveryEvent.h"
#include "CacheGateChannel.h"

#define UNSENT_POST_CONTEXT_FILE L"UnsentPostContext.cpp"
static wchar_t const* const MODULE_NAME = L"unsent post context";  // PDB MODULE_NAME

// The original writes each "== CRASH ==" text to Log (LT_ERROR) and to AlertSender.
#define UNSENT_POST_CONTEXT_CRASH(line, fmt, ...)                                     \
    do                                                                                \
    {                                                                                 \
        Log::Write(Log::LT_ERROR, UNSENT_POST_CONTEXT_FILE, line, fmt, __VA_ARGS__);  \
        AlertSender::Write(UNSENT_POST_CONTEXT_FILE, line, fmt, __VA_ARGS__);         \
    } while (0)

// 0xc3b0
bool UnsentPostContextList::pushUnsentPostContext(long long const postId, bool const hasPostContext)
{
    if (postId == 0)
    {
        UNSENT_POST_CONTEXT_CRASH(52, L"== CRASH == [%s], %s; invalid parameter, postId:0x%I64X",
                                  MODULE_NAME, L"UnsentPostContextList::pushUnsentPostContext", postId);
        return false;
    }
    if (_header == nullptr || _header->_prev == nullptr || _header->_next == nullptr)
    {
        // BUG: 0xc3b0 reads _header->_prev and _header->_next also when _header is null.
        UNSENT_POST_CONTEXT_CRASH(56,
                                  L"== CRASH == [%s], %s; invalid header node, wid:%u, header:0x%p, prev:0x%p, next:0x%p",
                                  MODULE_NAME, L"UnsentPostContextList::pushUnsentPostContext", _wid, _header,
                                  _header->_prev, _header->_next);
        return false;
    }

    void* const memory = Memory::_Manager[2]->Alloc(sizeof(UnsentPostContext), UNSENT_POST_CONTEXT_FILE, 60);  // ❓ line
    // BUG: 0xc3b0 does not stop when Alloc fails. It uses the null node below.
    UnsentPostContext* const unsentPostContext =
        memory != nullptr ? new (memory) UnsentPostContext(postId, hasPostContext) : nullptr;

    _lock.Enter();
    if (_header->_prev == _header)
    {
        _header->_next = unsentPostContext;
        unsentPostContext->_prev = _header;
    }
    else
    {
        _header->_prev->_next = unsentPostContext;
        unsentPostContext->_prev = _header->_prev;
    }
    unsentPostContext->_next = _header;
    _header->_prev = unsentPostContext;
    ++_contextCount;
    _lock.Leave();
    return true;
}

// 0xc5a0
UnsentPostContext* UnsentPostContextList::popUnsentPostContext()
{
    if (_header != nullptr && _header->_prev != nullptr && _header->_next != nullptr)
    {
        UnsentPostContext* next = nullptr;
        _lock.Enter();
        if (_header->_prev != _header)
        {
            next = _header->_next;
            _header->_next = next->_next;
            next->_next->_prev = _header;
            next->_prev = nullptr;
            next->_next = nullptr;
            --_contextCount;
        }
        _lock.Leave();
        return next;
    }

    // BUG: 0xc5a0 reads _header->_prev and _header->_next also when _header is null.
    UNSENT_POST_CONTEXT_CRASH(86,
                              L"== CRASH == [%s], %s; invalid header node, wid:%u, header:0x%p, prev:0x%p, next:0x%p",
                              MODULE_NAME, L"UnsentPostContextList::popUnsentPostContext", _wid, _header,
                              _header->_prev, _header->_next);
    return nullptr;
}

// 0xc6d0
bool UnsentPostContextManager::initContextManager(WorldConfigList const* worldConfigList)
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
            Log::Write(Log::LT_ERROR, UNSENT_POST_CONTEXT_FILE, 159,
                       L"[%s], %s; wid out of range, wid:%u, bucketIndex:%d, bucketCount:%d", MODULE_NAME,
                       L"UnsentPostContextManager::initContextManager", wid, bucketIndex, BUCKET_COUNT);
            lock.Leave();
            return false;
        }
        if (_containerList[bucketIndex] == nullptr)
            _containerList[bucketIndex] = static_cast<UnsentPostContextList**>(Memory::_Manager[2]->AllocZero(
                sizeof(UnsentPostContextList*) * ARRAY_SIZE, UNSENT_POST_CONTEXT_FILE, 164));
        if (_containerList[bucketIndex][worldIndex] != nullptr)
        {
            Log::Write(Log::LT_ERROR, UNSENT_POST_CONTEXT_FILE, 174,
                       L"[%s], %s; unsent post context list already exists, wid:%u, bucketIndex:%d, worldIndex:%d",
                       MODULE_NAME, L"UnsentPostContextManager::initContextManager", wid, bucketIndex,
                       worldIndex);
            lock.Leave();
            return false;
        }
        if (!addUnsentPostContextList(wid, bucketIndex, worldIndex))
        {
            UNSENT_POST_CONTEXT_CRASH(
                169, L"== CRASH == [%s], %s; failed to add unsent post context list, wid:%u, bucketIndex:%d, worldIndex:%d",
                MODULE_NAME, L"UnsentPostContextManager::initContextManager", wid, bucketIndex, worldIndex);
            lock.Leave();
            return false;
        }
    }
    lock.Leave();
    return true;
}

// 0xcae0
bool UnsentPostContextManager::updateWorldList(WorldConfigList const* worldConfigList)
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
            Log::Write(Log::LT_ERROR, UNSENT_POST_CONTEXT_FILE, 198,
                       L"[%s], %s; wid out of range, wid:%u, bucketIndex:%d, bucketCount:%d", MODULE_NAME,
                       L"UnsentPostContextManager::updateWorldList", wid, bucketIndex, BUCKET_COUNT);
            lock.Leave();
            return false;
        }
        if (_containerList[bucketIndex] == nullptr)
            _containerList[bucketIndex] = static_cast<UnsentPostContextList**>(Memory::_Manager[2]->AllocZero(
                sizeof(UnsentPostContextList*) * ARRAY_SIZE, UNSENT_POST_CONTEXT_FILE, 203));
        if (_containerList[bucketIndex][worldIndex] == nullptr && !addUnsentPostContextList(wid, bucketIndex, worldIndex))
        {
            UNSENT_POST_CONTEXT_CRASH(
                208, L"== CRASH == [%s], %s; failed to add unsent post context list, wid:%u, bucketIndex:%d, worldIndex:%d",
                MODULE_NAME, L"UnsentPostContextManager::updateWorldList", wid, bucketIndex, worldIndex);
            lock.Leave();
            return false;
        }
    }
    lock.Leave();
    Log::Write(Log::LT_DEBUG, UNSENT_POST_CONTEXT_FILE, 215,
               L"[%s], %s; succeeded to update world list of unsent post context manager", MODULE_NAME,
               L"UnsentPostContextManager::updateWorldList");
    return true;
}

// 0xce80
bool UnsentPostContextManager::addUnsentPostContextList(unsigned short wid, int bucketIndex, int worldIndex)
{
    if (wid == 0 || bucketIndex >= BUCKET_COUNT || worldIndex >= ARRAY_SIZE)
    {
        UNSENT_POST_CONTEXT_CRASH(223, L"== CRASH == [%s], %s; invalid parameter, wid:%u, bucketIndex:%d, worldIndex:%d",
                                  MODULE_NAME, L"UnsentPostContextManager::addUnsentPostContextList", wid,
                                  bucketIndex, worldIndex);
        return false;
    }

    void* const memory = Memory::_Manager[2]->Alloc(sizeof(UnsentPostContextList), UNSENT_POST_CONTEXT_FILE, 227);
    UnsentPostContextList* unsentPostContextList = nullptr;
    if (memory != nullptr)
    {
        unsentPostContextList = new (memory) UnsentPostContextList(wid);

        void* const headerMemory = Memory::_Manager[2]->Alloc(sizeof(UnsentPostContext), UNSENT_POST_CONTEXT_FILE, 30);
        // BUG: 0xce80 does not stop when Alloc of the header node fails.
        UnsentPostContext* const header = headerMemory != nullptr ? new (headerMemory) UnsentPostContext(0, false) : nullptr;
        header->_prev = header;
        header->_next = header;
        unsentPostContextList->_header = header;
    }

    // BUG: 0xce80 stores a null list when Alloc fails and returns true.
    _containerList[bucketIndex][worldIndex] = unsentPostContextList;
    if (_arrayBoundary[bucketIndex][0] == -1 || worldIndex < _arrayBoundary[bucketIndex][0])
        _arrayBoundary[bucketIndex][0] = worldIndex;
    if (_arrayBoundary[bucketIndex][1] == -1 || worldIndex > _arrayBoundary[bucketIndex][1])
        _arrayBoundary[bucketIndex][1] = worldIndex;

    Log::Write(Log::LT_DEBUG, UNSENT_POST_CONTEXT_FILE, 237,
               L"[%s], %s; succeeded to add unsent post context list, wid:%u, bucketIndex:%d, worldIndex:%d",
               MODULE_NAME, L"UnsentPostContextManager::addUnsentPostContextList", wid, bucketIndex,
               worldIndex);
    return true;
}

// 0xd070
UnsentPostContextList* UnsentPostContextManager::getUnsentPostContextList(unsigned short const wid)
{
    if (wid == 0)
    {
        Log::Write(Log::LT_ERROR, UNSENT_POST_CONTEXT_FILE, 245, L"[%s], %s; invalid parameter, wid:%u",
                   MODULE_NAME, L"UnsentPostContextManager::getUnsentPostContextList", wid);
        return nullptr;
    }
    int const bucketIndex = wid / ARRAY_SIZE;
    if (bucketIndex >= BUCKET_COUNT)
    {
        Log::Write(Log::LT_ERROR, UNSENT_POST_CONTEXT_FILE, 255,
                   L"[%s], %s; wid out of range, wid:%u, bucketIndex:%d, bucketCount:%d", MODULE_NAME,
                   L"UnsentPostContextManager::getUnsentPostContextList", wid, bucketIndex, BUCKET_COUNT);
        return nullptr;
    }
    if (_containerList[bucketIndex] == nullptr)
    {
        Log::Write(Log::LT_ERROR, UNSENT_POST_CONTEXT_FILE, 260,
                   L"[%s], %s; no such container list, wid:%u, bucketIndex:%d", MODULE_NAME,
                   L"UnsentPostContextManager::getUnsentPostContextList", wid, bucketIndex);
        return nullptr;
    }
    return _containerList[bucketIndex][wid - ARRAY_SIZE * bucketIndex];
}

// 0xd190
bool UnsentPostContextManager::RegisterUnsentPost(unsigned short wid, long long postId, bool hasPostContext)
{
    if (postId == 0)
    {
        UNSENT_POST_CONTEXT_CRASH(270, L"== CRASH == [%s], %s; invalid parameter, postId:0x%I64X",
                                  MODULE_NAME, L"UnsentPostContextManager::RegisterUnsentPost", postId);
        return false;
    }
    UnsentPostContextList* const unsentPostContextList = getUnsentPostContextList(wid);
    if (unsentPostContextList == nullptr)
    {
        Log::Write(Log::LT_ERROR, UNSENT_POST_CONTEXT_FILE, 276,
                   L"[%s], %s; no such unsent post context list, wid:%u, unsentPostContextList:0x%p",
                   MODULE_NAME, L"UnsentPostContextManager::RegisterUnsentPost", wid, unsentPostContextList);
        return false;
    }
    if (!unsentPostContextList->pushUnsentPostContext(postId, hasPostContext))
    {
        UNSENT_POST_CONTEXT_CRASH(281, L"== CRASH == [%s], %s; failed to push unsent post context, wid:%u, postId:0x%I64X",
                                  MODULE_NAME, L"UnsentPostContextManager::RegisterUnsentPost", wid, postId);
        return false;
    }
    Log::Write(Log::LT_DEBUG, UNSENT_POST_CONTEXT_FILE, 285,
               L"[%s], %s; succeeded to register unsent post, wid:%u, postId:0x%I64X", MODULE_NAME,
               L"UnsentPostContextManager::RegisterUnsentPost", wid, postId);
    return true;
}

// 0xd330
void UnsentPostContextManager::CheckUnsentPost()
{
    bool delivered;
    do
    {
        delivered = false;
        for (int bucketIndex = 0; bucketIndex < BUCKET_COUNT; ++bucketIndex)
        {
            int const minIndex = _arrayBoundary[bucketIndex][0];
            if (minIndex == -1)
                continue;
            for (int worldIndex = minIndex; worldIndex <= _arrayBoundary[bucketIndex][1]; ++worldIndex)
            {
                UnsentPostContextList* const unsentPostContextList = _containerList[bucketIndex][worldIndex];
                if (unsentPostContextList == nullptr || unsentPostContextList->_contextCount <= 0)
                    continue;
                unsigned short const wid = unsentPostContextList->_wid;
                CacheGateChannel* const cachegateChannel = PostOfficeDaemon::checkDestinationServiceState(wid);
                if (cachegateChannel == nullptr)
                    continue;
                UnsentPostContext* const unsentPostContext = unsentPostContextList->popUnsentPostContext();
                if (unsentPostContext == nullptr)
                {
                    UNSENT_POST_CONTEXT_CRASH(315, L"== CRASH == [%s], %s; unsent post context is null, wid:%u",
                                              MODULE_NAME, L"UnsentPostContextManager::CheckUnsentPost", wid);
                    cachegateChannel->removeReferenceCount(UNSENT_POST_CONTEXT_FILE, 316);
                }
                else if (!deliverUnsentPost(unsentPostContext, cachegateChannel))
                {
                    Memory::_Manager[2]->Free(unsentPostContext, UNSENT_POST_CONTEXT_FILE, 322);
                    cachegateChannel->removeReferenceCount(UNSENT_POST_CONTEXT_FILE, 323);
                }
                else
                {
                    Memory::_Manager[2]->Free(unsentPostContext, UNSENT_POST_CONTEXT_FILE, 327);
                    cachegateChannel->removeReferenceCount(UNSENT_POST_CONTEXT_FILE, 328);
                    delivered = true;
                }
            }
        }
    } while (delivered);
}

// 0xd510 ❓ The caller passes no this pointer. The lift makes it static.
bool UnsentPostContextManager::deliverUnsentPost(UnsentPostContext* const unsentPostContext,
                                                 CacheGateChannel* const cachegateChannel)
{
    if (unsentPostContext == nullptr || cachegateChannel == nullptr)
    {
        UNSENT_POST_CONTEXT_CRASH(340,
                                  L"== CRASH == [%s], %s; invalid parameter, unsentPostContext:0x%p, cachegateChannel:0x%p",
                                  MODULE_NAME, L"UnsentPostContextManager::deliverUnsentPost",
                                  unsentPostContext, cachegateChannel);
        return false;
    }

    long long const postId = unsentPostContext->_postId;
    if (!unsentPostContext->_hasPostContext)
    {
        int dbRetValue = 0;
        if (!PostOfficeDB::LoadSinglePost(&dbRetValue, postId))
        {
            Log::Write(Log::LT_ERROR, UNSENT_POST_CONTEXT_FILE, 349,
                       L"[%s], %s; exception occurred; failed to load single post, dbRetValue:%d, postId:0x%I64X",
                       MODULE_NAME, L"UnsentPostContextManager::deliverUnsentPost", dbRetValue, postId);
            return false;
        }
    }

    PostContext* const postContext = PostOfficeDaemon::_instance->_postContextManager->GetContext(postId);
    if (postContext == nullptr)
    {
        Log::Write(Log::LT_ERROR, UNSENT_POST_CONTEXT_FILE, 356, L"[%s], %s; no such post context, postId:0x%I64X",
                   MODULE_NAME, L"UnsentPostContextManager::deliverUnsentPost", postId);
        return false;
    }

    if (PostDeliveryEvent::OccurEvent(postContext, cachegateChannel))
    {
        postContext->removeReferenceCount(UNSENT_POST_CONTEXT_FILE, 371);
        return true;
    }

    Log::Write(Log::LT_ERROR, UNSENT_POST_CONTEXT_FILE, 361,
               L"[%s], %s; exception occurred; failed to occur post delivery event, postId:0x%I64X",
               MODULE_NAME, L"UnsentPostContextManager::deliverUnsentPost", postId);
    if (!PostOfficeDaemon::_instance->_postContextManager->RemoveContext(postId))
        UNSENT_POST_CONTEXT_CRASH(364, L"== CRASH == [%s], %s; exception occurred; failed to remove post context, postId:0x%I64X",
                                  MODULE_NAME, L"UnsentPostContextManager::deliverUnsentPost", postId);
    postContext->removeReferenceCount(UNSENT_POST_CONTEXT_FILE, 367);
    return false;
}
