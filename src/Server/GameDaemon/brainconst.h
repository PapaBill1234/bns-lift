// brainconst.h: brainconst.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class BrainConst
{
public:
    enum Event {};
    // PDB enumerators of BrainConst::State.
    enum State
    {
        STATE_INVALID = 0,
        STATE_SPAWN = 1,
        STATE_ACT_SEQ = 2,
        STATE_FOLLOW = 3,
        STATE_TALK = 4,
        STATE_COMBAT_SEQ = 5,
        STATE_RETURN = 6,
        STATE_COUNT = 7,
    };
public:
    static wchar_t const * __cdecl GetState(::BrainConst::State);  // 0x402c60
    static wchar_t const * __cdecl GetEvent(::BrainConst::Event);  // 0x402cd0
};

