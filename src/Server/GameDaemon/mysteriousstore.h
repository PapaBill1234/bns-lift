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
private:
    // PDB layout of MysteriousStore (size 0x1C0).
    ::Npc *_owner;  // +0x0
    unsigned __int64 _authorizedPcdbid[24];  // +0x8
    unsigned __int64 _boughtItemId[24];  // +0xC8
    char _boughtItemIndex[24];  // +0x188
    bool _alreadyBought[24];  // +0x1A0
    void *_itemGroupData;  // +0x1B8 LIFT: Data::MysteriousStoreItemGroupRecordPtr view
};

