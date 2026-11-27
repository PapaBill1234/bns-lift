// brainconst.h: brainconst.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class BrainConst
{
public:
    enum Event {};
    enum State {};
public:
    static wchar_t const * __cdecl GetState(::BrainConst::State);  // 0x402c60
    static wchar_t const * __cdecl GetEvent(::BrainConst::Event);  // 0x402cd0
};

