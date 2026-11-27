// delayedrelease_gd.h: delayedrelease.cpp, delayedrelease.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class DelayedDelete
{
public:
    struct Node {};
public:
    bool __cdecl Add(__int64, bool (__cdecl *)(void *), void (__cdecl *)(void *), void *);  // 0x6a16d0
    void __cdecl Delete(__int64, int, bool, bool);  // 0x6a17c0
    void __cdecl Cleanup(void);  // 0x6a1960
private:
    static void __cdecl deleteNode(::DelayedDelete::Node *);  // 0x6a19d0
};

