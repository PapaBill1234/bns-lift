// mysteriousstore.h: mysteriousstore.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class MysteriousStore
{
public:
    __cdecl MysteriousStore(::Npc *, ::Data::MysteriousStoreRecordPtr, ::NpcSpawnParam const &);  // 0x16d7a0
    bool __cdecl IsAuthorizedMember(unsigned __int64) const;  // 0x16d9c0
    bool __cdecl Buy(unsigned __int64, char);  // 0x16da10
    bool __cdecl SendItemList(::Pc *) const;  // 0x16dac0
};

