// xigncode3.h: xigncode3.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class XIGNCode3
{
public:
    bool __cdecl Initialize(void);  // 0x2281f0
    void __cdecl AcceptClient(unsigned __int64, unsigned long, wchar_t *);  // 0x228290
    void __cdecl Cleanup(void);  // 0x228360
};

int __cdecl SendProc(unsigned __int64, void *, char const *, unsigned long);  // 0x227fb0
void __cdecl DisconnectProc(unsigned __int64, void *, int, wchar_t const *);  // 0x228110
