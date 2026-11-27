// closetmanager.cpp: closetmanager.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "closetmanager.h"
#include "LiftStub.h"

// 0x7ec10
__cdecl ClosetContainer::~ClosetContainer(void)
{
    LIFT_STUB(0x7ec10);
}

// 0x7ed00
bool __cdecl ClosetContainer::SetDbList(::FragmentPacketConcatenater *)
{
    LIFT_STUB(0x7ed00);
}

// 0x7ef80
::GameFailReason __cdecl ClosetContainer::TryToSetClosetUsed(int, int *const)
{
    LIFT_STUB(0x7ef80);
}

// 0x7f3b0
void __cdecl ClosetContainer::FinishSetClosetUsed(int, int *const, bool)
{
    LIFT_STUB(0x7f3b0);
}

// 0x7f6a0
bool __cdecl ClosetContainer::GetUsed(int, bool &)
{
    LIFT_STUB(0x7f6a0);
}

// 0x7f7b0
bool __cdecl ClosetContainer::TryToAddClosetItem(int, bool)
{
    LIFT_STUB(0x7f7b0);
}

// 0x7f9f0
void __cdecl ClosetContainer::FinishAddClosetItem(int)
{
    LIFT_STUB(0x7f9f0);
}

// 0x7fb40
void __cdecl ClosetContainer::CancelAddClosetItem(int)
{
    LIFT_STUB(0x7fb40);
}

// 0x7fcc0
bool __cdecl ClosetContainer::TryToDeleteClosetItem(int)
{
    LIFT_STUB(0x7fcc0);
}

// 0x7fda0
void __cdecl ClosetContainer::FinishDeleteClosetItem(int)
{
    LIFT_STUB(0x7fda0);
}

// 0x7ff20
void __cdecl ClosetContainer::CancelDeleteClosetItem(int)
{
    LIFT_STUB(0x7ff20);
}
