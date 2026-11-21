// PerfCounterProvider.obj (LobbyDaemon PDB, 2019 + PDB): lines from the PDB line map (perfcounterprovider.cpp).
// LTCG removed "this" from loadLibrary and setCounterSetInfo: the code uses PerfCounterProvider::Instance directly.
#include "PerfCounterProvider.h"

// rva 0x20958a. A zero initial value. The constructor sets it again (dynamic initializer 0x11e700).
bool PerfCounterProvider::Initialized;

// rva 0x209a80. Dynamic initializer 0x11e700 (line 29), atexit destructor 0x11f3a0.
PerfCounterProvider PerfCounterProvider::Instance;

// LIFT: inlined in the dynamic initializer 0x11e700. The only store is "Initialized = false".
PerfCounterProvider::PerfCounterProvider()
{
    Initialized = false;
}

// LIFT: inlined in the atexit destructor 0x11f3a0.
// ❓ The destructor can also call Clenup(). The code is the same.
PerfCounterProvider::~PerfCounterProvider()
{
    if (Initialized)
        cleanup();
}

// LIFT: inlined in the caller in lobbydaemon.cpp (0x9be21, line 1445). No separate copy in the exe.
bool PerfCounterProvider::Initialize(GUID providerGuid, BL_PERF_COUNTERSET_INFO_LIST* perfCounterSetInfoList, int perfCounterSetTotal)
{
    if (Initialized)
        return true;
    if (!Instance.initialize(providerGuid, perfCounterSetInfoList, perfCounterSetTotal))
        return false;
    Initialized = true;
    return true;
}

// LIFT: no copy and no call site in the exe. ❓ The body is not verified.
void PerfCounterProvider::Clenup()
{
    if (Initialized)
        Instance.cleanup();
}

// LIFT: no copy and no call site in the exe. ❓ The body is not verified.
void* PerfCounterProvider::getHandle()
{
    return Instance._handle;
}

// LIFT: inlined in the caller (0x9be31: loadLibrary, then setCounterSetInfo).
bool PerfCounterProvider::initialize(GUID providerGuid, BL_PERF_COUNTERSET_INFO_LIST* perfCounterSetInfoList, int perfCounterSetTotal)
{
    if (!loadLibrary())
        return false;
    return setCounterSetInfo(providerGuid, perfCounterSetInfoList, perfCounterSetTotal);
}

// LIFT: inlined in setCounterSetInfo 0xe7cd0 (lines 123, 129) and in the atexit destructor 0x11f3a0.
void PerfCounterProvider::cleanup()
{
    if (_handle != NULL)
    {
        _stopProvider(_handle);
        _handle = NULL;
    }
    if (_module != NULL)
    {
        FreeLibrary(_module);
        _module = NULL;
    }
    Initialized = false;
}

// 0xe7cd0
bool PerfCounterProvider::setCounterSetInfo(GUID providerGuid, BL_PERF_COUNTERSET_INFO_LIST* perfCounterSetInfoList, int perfCounterSetTotal)
{
    BL_PERF_PROVIDER_CONTEXT context;
    memset(&context, 0, sizeof(context));
    context.ContextSize = sizeof(context);

    if (_startProvider(&providerGuid, &context, &_handle) != ERROR_SUCCESS)
    {
        _handle = NULL;
        cleanup();
        return false;
    }

    // LTCG made perfCounterSetTotal a constant: the loop stops at LobbyDaemonPerfCounterSetInfoListPtr (list + 2).
    for (int i = 0; i < perfCounterSetTotal; ++i)
    {
        if (_setCounterSetInfo(_handle, perfCounterSetInfoList[i].info, perfCounterSetInfoList[i].size) != ERROR_SUCCESS)
        {
            cleanup();
            return false;
        }
    }

    return true;
}

// LIFT: lines 87-98 have one lookup per line and one shared fail block (tail merge at line 98).
// ❓ The original form of these lines (macro or plain statements) is not known.
#define LIFT_PCP_LOAD_PROC(member, type, name)                  \
    member = reinterpret_cast<type>(GetProcAddress(_module, name)); \
    if (member == NULL)                                          \
    {                                                            \
        if (_module != NULL)                                     \
        {                                                        \
            FreeLibrary(_module);                                \
            _module = NULL;                                      \
        }                                                        \
        return false;                                            \
    }

// 0xe7ae0
bool PerfCounterProvider::loadLibrary()
{
    _module = LoadLibraryW(L"advapi32.dll");
    if (_module == NULL)
        return false;

    LIFT_PCP_LOAD_PROC(_startProvider, StartProvider, "PerfStartProviderEx");
    LIFT_PCP_LOAD_PROC(_stopProvider, StopProvider, "PerfStopProvider");
    LIFT_PCP_LOAD_PROC(_setCounterSetInfo, SetCounterSetInfo, "PerfSetCounterSetInfo");
    LIFT_PCP_LOAD_PROC(_createCounterSet, CreateCounterSet, "PerfCreateInstance");
    LIFT_PCP_LOAD_PROC(_deleteCounterSet, DeleteCounterSet, "PerfDeleteInstance");
    LIFT_PCP_LOAD_PROC(_setU32Counter, SetU32Counter, "PerfSetULongCounterValue");
    LIFT_PCP_LOAD_PROC(_setU64Counter, SetU64Counter, "PerfSetULongLongCounterValue");
    LIFT_PCP_LOAD_PROC(_setRefCounter, SetRefCounter, "PerfSetCounterRefValue");
    LIFT_PCP_LOAD_PROC(_incU32Counter, IncU32Counter, "PerfIncrementULongCounterValue");
    LIFT_PCP_LOAD_PROC(_incU64Counter, IncU64Counter, "PerfIncrementULongLongCounterValue");
    LIFT_PCP_LOAD_PROC(_decU32Counter, DecU32Counter, "PerfDecrementULongCounterValue");
    LIFT_PCP_LOAD_PROC(_decU64Counter, DecU64Counter, "PerfDecrementULongLongCounterValue");

    return true;
}

#undef LIFT_PCP_LOAD_PROC
