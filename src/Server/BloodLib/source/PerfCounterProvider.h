// PerfCounterProvider.obj (LobbyDaemon PDB, 2019 + PDB). Class layout from the PDB (PerfCounterProvider, size 0x70).
// LIFT: the BL_PERF_* structs are in the PDB, but the PDB does not give their header. They are here for now.
#pragma once
#include <windows.h>

// PDB BL_PERF_COUNTER_INFO, size 0x20.
struct BL_PERF_COUNTER_INFO
{
    unsigned long CounterId;
    unsigned long Type;
    unsigned __int64 Attrib;
    unsigned long Size;
    unsigned long DetailLevel;
    long Scale;
    unsigned long Offset;
};

// PDB BL_PERF_COUNTERSET_INFO, size 0x28.
struct BL_PERF_COUNTERSET_INFO
{
    GUID CounterSetGuid;
    GUID ProviderGuid;
    unsigned long NumCounters;
    unsigned long InstanceType;
};

// PDB BL_PERF_COUNTERSET_INFO_LIST, size 0x10.
struct BL_PERF_COUNTERSET_INFO_LIST
{
    BL_PERF_COUNTERSET_INFO* info;
    unsigned long size;
};

// PDB BL_PERF_PROVIDER_CONTEXT, size 0x28.
struct BL_PERF_PROVIDER_CONTEXT
{
    unsigned long ContextSize;
    unsigned long Reserved;
    unsigned long (*ControlCallback)(unsigned long, void*, unsigned long);
    void* (*MemAllocRoutine)(unsigned __int64, void*);
    void (*MemFreeRoutine)(void*, void*);
    void* pMemContext;
};

// PDB BL_PERF_COUNTERSET_INSTANCE, size 0x20.
struct BL_PERF_COUNTERSET_INSTANCE
{
    GUID CounterSetGuid;
    unsigned long dwSize;
    unsigned long InstanceId;
    unsigned long InstanceNameOffset;
    unsigned long InstanceNameSize;
};

class PerfCounterProvider
{
public:
    static bool Initialize(GUID providerGuid, BL_PERF_COUNTERSET_INFO_LIST* perfCounterSetInfoList, int perfCounterSetTotal);
    static void Clenup();  // The PDB name has this spelling.

    // The nested function pointer types of the PDB (advapi32 Perf* functions).
    typedef unsigned long (*StartProvider)(GUID*, BL_PERF_PROVIDER_CONTEXT*, void**);
    typedef unsigned long (*StopProvider)(void*);
    typedef unsigned long (*SetCounterSetInfo)(void*, BL_PERF_COUNTERSET_INFO*, unsigned long);
    typedef unsigned long (*DeleteCounterSet)(void*, BL_PERF_COUNTERSET_INSTANCE*);
    typedef unsigned long (*SetU32Counter)(void*, BL_PERF_COUNTERSET_INSTANCE*, unsigned long, unsigned long);
    typedef unsigned long (*SetU64Counter)(void*, BL_PERF_COUNTERSET_INSTANCE*, unsigned long, unsigned __int64);
    typedef unsigned long (*SetRefCounter)(void*, BL_PERF_COUNTERSET_INSTANCE*, unsigned long, void*);
    typedef unsigned long (*IncU32Counter)(void*, BL_PERF_COUNTERSET_INSTANCE*, unsigned long, unsigned long);
    typedef unsigned long (*IncU64Counter)(void*, BL_PERF_COUNTERSET_INSTANCE*, unsigned long, unsigned __int64);
    typedef unsigned long (*DecU32Counter)(void*, BL_PERF_COUNTERSET_INSTANCE*, unsigned long, unsigned long);
    typedef unsigned long (*DecU64Counter)(void*, BL_PERF_COUNTERSET_INSTANCE*, unsigned long, unsigned __int64);
    typedef BL_PERF_COUNTERSET_INSTANCE* (*CreateCounterSet)(void*, const GUID*, const wchar_t*, unsigned long);

private:
    friend class CounterSet;
    static void* getHandle();

    static PerfCounterProvider Instance;  // rva 0x209a80
    static bool Initialized;              // rva 0x20958a

    PerfCounterProvider();
    ~PerfCounterProvider();

    bool initialize(GUID providerGuid, BL_PERF_COUNTERSET_INFO_LIST* perfCounterSetInfoList, int perfCounterSetTotal);
    void cleanup();
    bool setCounterSetInfo(GUID providerGuid, BL_PERF_COUNTERSET_INFO_LIST* perfCounterSetInfoList, int perfCounterSetTotal);  // 0xe7cd0
    bool loadLibrary();  // 0xe7ae0

    void* _handle;                          // +0x00
    HMODULE _module;                        // +0x08
    StartProvider _startProvider;           // +0x10
    StopProvider _stopProvider;             // +0x18
    SetCounterSetInfo _setCounterSetInfo;   // +0x20
    CreateCounterSet _createCounterSet;     // +0x28
    DeleteCounterSet _deleteCounterSet;     // +0x30
    SetU32Counter _setU32Counter;           // +0x38
    SetU64Counter _setU64Counter;           // +0x40
    SetRefCounter _setRefCounter;           // +0x48
    IncU32Counter _incU32Counter;           // +0x50
    IncU64Counter _incU64Counter;           // +0x58
    DecU32Counter _decU32Counter;           // +0x60
    DecU64Counter _decU64Counter;           // +0x68
};

// LIFT: inlined in GameWorldCluster (0x4d390, 0x4dc70) and SystemPerfMonitor (0x59ce0, 0x59d60).
class CounterSet
{
public:
    bool Destroy()
    {
        if (_instance == nullptr)
            return false;
        if (PerfCounterProvider::Instance._deleteCounterSet(PerfCounterProvider::Instance._handle, _instance) != 0)
            return false;
        _instance = nullptr;
        return true;
    }

protected:
    CounterSet() : _instance(nullptr) {}
    virtual ~CounterSet() { Destroy(); }

    // LIFT: Returns the instance pointer, null on failure. The original tests the stored pointer and has no handle test (0x59d60).
    BL_PERF_COUNTERSET_INSTANCE* create(GUID const* id, wchar_t const* name)
    {
        if (_instance != nullptr)
            return nullptr;
        _instance = PerfCounterProvider::Instance._createCounterSet(PerfCounterProvider::Instance._handle, id, name, 0);
        return _instance;
    }

    bool setU64(unsigned long id, unsigned __int64 value)
    {
        if (_instance == nullptr)
            return false;
        return PerfCounterProvider::Instance._setU64Counter(PerfCounterProvider::Instance._handle, _instance, id, value) == 0;
    }

private:
    BL_PERF_COUNTERSET_INSTANCE* _instance;
};
static_assert(sizeof(CounterSet) == 0x10, "sizeof CounterSet");
