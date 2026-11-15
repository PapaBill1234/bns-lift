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
    void Enter() { EnterCriticalSection(&SL); }  // ❓ name not in PDB (inlined)
    void Leave() { LeaveCriticalSection(&SL); }  // ❓ name not in PDB (inlined)

    CRITICAL_SECTION SL;
};
static_assert(sizeof(SpinLock) == 0x28, "sizeof SpinLock");

class CriticalSection
{
public:
    CriticalSection() { InitializeCriticalSection(&CS); }
    ~CriticalSection();
    void Enter() { EnterCriticalSection(&CS); }  // ❓ name not in PDB (inlined)
    void Leave() { LeaveCriticalSection(&CS); }  // ❓ name not in PDB (inlined)

    CRITICAL_SECTION CS;
};
static_assert(sizeof(CriticalSection) == 0x28, "sizeof CriticalSection");

// 0x11f70
inline CriticalSection::~CriticalSection()
{
    DeleteCriticalSection(&CS);
}

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
