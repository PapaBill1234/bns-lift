// systemobject.cpp: systemobject.h (GameDaemon PDB, 2019 + PDB).
#include "systemobject.h"
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:??1SystemMultiEvent@@QEAA@XZ")  // LIFT: dead-strip keep (no live caller yet)

// 0x8c1b0 SystemEvent::~SystemEvent: LIFT: no body in wave 0 (shared class SystemEvent has another form or the change needs codegen (W1, pattern 35)).

// 0x1dc1a0
// The original inlines SystemMultiEvent::clear here.
__cdecl SystemMultiEvent::~SystemMultiEvent(void)
{
    for (char i = 0; i < Count; ++i)
    {
        if (Event[i] != nullptr)
        {
            CloseHandle(Event[i]);
            Event[i] = nullptr;
        }
    }
    Count = 0;
    SetCount = 0;
    WaitAll = true;
}
