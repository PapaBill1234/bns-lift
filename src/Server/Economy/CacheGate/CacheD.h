// CacheD.obj (CacheGate PDB). Layouts from include/pdb/CacheGate/types.h.
#pragma once
#include <stddef.h>
#include <map>
#include "Channel.h"
#include "Lock.h"
#include "StlMemory.h"

class Session;

class CacheD : public Channel
{
public:
    // LIFT: The constructor is inlined in CacheDList::addCacheD (0x3700). __forceinline: no out-of-line copy (0x10b0 in ours).
    __forceinline CacheD() :_id(0), _addr(0), _port(0), _status(0)
    {
        _tag = 10;
        _ref = 1;
        _history = nullptr;
    }
    virtual ~CacheD();                                                         // 0x23B0
    virtual unsigned long long GetId();                                        // 0x23A0

    // LIFT: noinline. The orig calls it from addCacheD (0x3700) and inlines it only in MakeSessionAll.
    __declspec(noinline) bool TryConnect();                                    // 0x23E0
    void Initialize(unsigned short id, unsigned long addr, unsigned short port, char status);  // 0x2430
    int Verify(Session const* session);                                        // 0x2530

    unsigned short _id;
    unsigned long _addr;
    unsigned short _port;
    char _status;
    CriticalSection _lock;
    wchar_t _daemonInvalidInfoKey[129];
};
static_assert(sizeof(CacheD) == 0x168, "sizeof CacheD");
static_assert(offsetof(CacheD, _id) == 0x28, "CacheD::_id");
static_assert(offsetof(CacheD, _addr) == 0x2C, "CacheD::_addr");
static_assert(offsetof(CacheD, _port) == 0x30, "CacheD::_port");
static_assert(offsetof(CacheD, _status) == 0x32, "CacheD::_status");
static_assert(offsetof(CacheD, _lock) == 0x38, "CacheD::_lock");
static_assert(offsetof(CacheD, _daemonInvalidInfoKey) == 0x60, "CacheD::_daemonInvalidInfoKey");

class CacheDList
{
public:
    typedef std::map<unsigned short, CacheD*, std::less<unsigned short>,
                     StlAllocator<std::pair<unsigned short, CacheD*>, 2> >
        CacheDMap;  // PDB CacheDList::CacheDMap

    // LIFT: The constructor is inlined in the CacheGate constructor.
    CacheDList() : _capacity(0), _cachedMap(nullptr) {}
    ~CacheDList();                                                             // 0x25C0

    bool Initialize();                                                         // 0x2660
    CacheD* Find(unsigned short id);                                           // 0x2710
    bool MakeSessionAll();                                                     // 0x27D0
    void RemoveSessionAll();                                                   // 0x2940
    bool LoadCachedListConfigFile(wchar_t const* fileName, bool reload);       // 0x2B20
    bool CreateCachedListConfigFile(wchar_t const* const fileName);            // 0x3120

private:
    void writeSampleConfigFormat(void* fileHandle);                            // 0x3230
    bool writeConfigString(void* fileHandle, wchar_t const* configString);     // 0x32C0
    bool add(CacheD* cached);                                                  // 0x3490
    bool del(unsigned short id);                                               // 0x3550
    void clear();                                                              // 0x3640
    bool addCacheD(unsigned short wid, unsigned long addr, unsigned short port, bool connect);  // 0x3700

public:
    CriticalSection _lock;
    int _capacity;
    CacheDMap* _cachedMap;
};
static_assert(sizeof(CacheDList) == 0x38, "sizeof CacheDList");
static_assert(offsetof(CacheDList, _capacity) == 0x28, "CacheDList::_capacity");
static_assert(offsetof(CacheDList, _cachedMap) == 0x30, "CacheDList::_cachedMap");
