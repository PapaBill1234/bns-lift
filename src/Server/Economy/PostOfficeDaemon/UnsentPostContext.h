// UnsentPostContext.obj (PostOfficeDaemon PDB). Layouts from include/pdb/PostOfficeDaemon/types.h.
#pragma once
#include <stddef.h>
#include <string.h>
#include "Lock.h"

class WorldConfigList;
class CacheGateChannel;

class UnsentPostContext
{
public:
    // PDB constructor, inlined at 0xc3b0 and 0xce80.
    UnsentPostContext(long long const postId, bool const hasPostContext)
        : _postId(postId), _hasPostContext(hasPostContext), _prev(nullptr), _next(nullptr)
    {
    }

    long long const _postId;
    bool const _hasPostContext;
    UnsentPostContext* _prev;
    UnsentPostContext* _next;
};
static_assert(sizeof(UnsentPostContext) == 0x20, "sizeof UnsentPostContext");
static_assert(offsetof(UnsentPostContext, _prev) == 0x10, "UnsentPostContext::_prev");

class UnsentPostContextList
{
public:
    // PDB constructor, inlined at 0xce80. The lock uses InitializeCriticalSectionAndSpinCount(4000).
    explicit UnsentPostContextList(unsigned short const wid) : _wid(wid), _lock(4000), _header(nullptr), _contextCount(0) {}

    bool pushUnsentPostContext(long long const postId, bool const hasPostContext);  // 0xc3b0
    UnsentPostContext* popUnsentPostContext();                                       // 0xc5a0

    unsigned short const _wid;
    CriticalSection _lock;
    UnsentPostContext* _header;  // PDB: UnsentPostContext* const. Set after the ctor in 0xce80.
    int _contextCount;
};
static_assert(sizeof(UnsentPostContextList) == 0x40, "sizeof UnsentPostContextList");
static_assert(offsetof(UnsentPostContextList, _lock) == 0x8, "UnsentPostContextList::_lock");
static_assert(offsetof(UnsentPostContextList, _header) == 0x30, "UnsentPostContextList::_header");
static_assert(offsetof(UnsentPostContextList, _contextCount) == 0x38, "UnsentPostContextList::_contextCount");

class UnsentPostContextManager
{
public:
    // PDB constructor, inlined at 0x13d30: the CriticalSection ctor, then memset of the arrays.
    UnsentPostContextManager()
    {
        memset(_containerList, 0, sizeof(_containerList));
        memset(_arrayBoundary, -1, sizeof(_arrayBoundary));
    }

    bool initContextManager(WorldConfigList const* worldConfigList);                       // 0xc6d0
    bool updateWorldList(WorldConfigList const* worldConfigList);                          // 0xcae0
    bool addUnsentPostContextList(unsigned short wid, int bucketIndex, int worldIndex);    // 0xce80
    UnsentPostContextList* getUnsentPostContextList(unsigned short const wid);             // 0xd070
    bool RegisterUnsentPost(unsigned short wid, long long postId, bool hasPostContext);    // 0xd190
    void CheckUnsentPost();                                                                // 0xd330
    static bool deliverUnsentPost(UnsentPostContext* const unsentPostContext,
                                  CacheGateChannel* const cachegateChannel);               // 0xd510

    CriticalSection _reloadLock;
    static int const BUCKET_COUNT = 33;
    static int const ARRAY_SIZE = 1000;

    UnsentPostContextList** _containerList[BUCKET_COUNT];
    int _arrayBoundary[BUCKET_COUNT][2];
};
static_assert(sizeof(UnsentPostContextManager) == 0x238, "sizeof UnsentPostContextManager");
static_assert(offsetof(UnsentPostContextManager, _containerList) == 0x28, "UnsentPostContextManager::_containerList");
static_assert(offsetof(UnsentPostContextManager, _arrayBoundary) == 0x130, "UnsentPostContextManager::_arrayBoundary");
