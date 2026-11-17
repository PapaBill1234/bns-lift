// Lock classes of BloodLib (CacheGate PDB). Layouts from include/pdb/CacheGate/types.h.
// The PDB has no separate module for these classes. The bodies are inline in the original.
#pragma once
#include <windows.h>
#include <stddef.h>

// The spin count that the SpinLock constructor gives (0x3AB30: 0xFA0).
class SpinLock
{
public:
    SpinLock() { InitializeCriticalSectionAndSpinCount(&SL, 4000); }
    ~SpinLock() { DeleteCriticalSection(&SL); }
    void Enter() { EnterCriticalSection(&SL); }  // LIFT: name not in PDB (inlined)
    void Leave() { LeaveCriticalSection(&SL); }  // LIFT: name not in PDB (inlined)

    CRITICAL_SECTION SL;
};
static_assert(sizeof(SpinLock) == 0x28, "sizeof SpinLock");

class CriticalSection
{
public:
    CriticalSection() { InitializeCriticalSection(&CS); }
    // LIFT: Not in PDB. Inlined at PostOfficeDaemon 0xce80 (InitializeCriticalSectionAndSpinCount).
    explicit CriticalSection(unsigned long spinCount) { InitializeCriticalSectionAndSpinCount(&CS, spinCount); }
    ~CriticalSection();
    void Enter() { EnterCriticalSection(&CS); }  // LIFT: name not in PDB (inlined)
    void Leave() { LeaveCriticalSection(&CS); }  // LIFT: name not in PDB (inlined)

    CRITICAL_SECTION CS;
};
static_assert(sizeof(CriticalSection) == 0x28, "sizeof CriticalSection");

// 0x11f70
inline CriticalSection::~CriticalSection()
{
    DeleteCriticalSection(&CS);
}

// PDB: AutoCS (PostOfficeDaemon). The ctor is inline. Leave (0x3c90) and the dtor (0x3c80)
// have their bodies in src/PostOfficeDaemon/CachedWatchdog.cpp (PDB: COMDAT in CachedWatchdog.obj, Mod 0010).
class AutoCS
{
public:
    explicit AutoCS(CriticalSection* cs);  // LIFT: inlined; asserts at Lock.h line 113
    ~AutoCS();                             // 0x3c80
    void Leave();                          // 0x3c90

    CriticalSection* CS;
    unsigned int EnterCount;
};
static_assert(sizeof(AutoCS) == 0x10, "sizeof AutoCS");

class SystemEvent
{
public:
    SystemEvent() : Event(nullptr) {}
    ~SystemEvent();

    void* Event;
};
static_assert(sizeof(SystemEvent) == 0x8, "sizeof SystemEvent");

// 0x9d60
inline SystemEvent::~SystemEvent()
{
    if (Event != nullptr)
    {
        CloseHandle(Event);
        Event = nullptr;
    }
}
