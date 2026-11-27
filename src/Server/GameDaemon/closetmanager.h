// closetmanager.h: closetmanager.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class ClosetContainer
{
public:
    __cdecl ~ClosetContainer(void);  // 0x7ec10
    bool __cdecl SetDbList(::FragmentPacketConcatenater *);  // 0x7ed00
    ::GameFailReason __cdecl TryToSetClosetUsed(int, int *const);  // 0x7ef80
    void __cdecl FinishSetClosetUsed(int, int *const, bool);  // 0x7f3b0
    bool __cdecl GetUsed(int, bool &);  // 0x7f6a0
    bool __cdecl TryToAddClosetItem(int, bool);  // 0x7f7b0
    void __cdecl FinishAddClosetItem(int);  // 0x7f9f0
    void __cdecl CancelAddClosetItem(int);  // 0x7fb40
    bool __cdecl TryToDeleteClosetItem(int);  // 0x7fcc0
    void __cdecl FinishDeleteClosetItem(int);  // 0x7fda0
    void __cdecl CancelDeleteClosetItem(int);  // 0x7ff20
};

