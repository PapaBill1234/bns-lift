// zonescore.h: zonescore.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class ZoneScore
{
public:
    void __cdecl AddScore(char, short);  // 0x25f710
    bool __cdecl FetchPartyBattleScore(::FragmentPacket &, char);  // 0x25f7a0
    bool __cdecl FetchScoreTypeHistory(::FragmentPacket &);  // 0x25f870
};

