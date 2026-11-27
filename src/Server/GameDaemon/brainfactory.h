// brainfactory.h: brainfactory.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class BrainFactory
{
protected:
    static ::BrainBase * __cdecl CreateBrain(::Npc &, ::Data::NpcBrainType, bool);  // 0x402e00
};

