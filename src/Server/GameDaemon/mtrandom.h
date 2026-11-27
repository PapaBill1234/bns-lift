// mtrandom.h: mtrandom.cpp, mtrandom.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class MTRandom
{
public:
    __cdecl MTRandom(void);  // 0x16d470
    unsigned int __cdecl RandInt(void);  // 0x16d500
    unsigned int __cdecl RandInt(unsigned int);  // 0x16d550
private:
    void __cdecl reload(void);  // 0x16d5e0
};

class MTRandomAllocator
{
public:
    static unsigned int __cdecl RandInt(unsigned int);  // 0x10d60
    static unsigned int __cdecl RandInt(unsigned int, unsigned int);  // 0x96b40
private:
    static void __cdecl initialize(void);  // 0x16d6a0
};

