// itempouch.h: itempouch.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class ItemPouch
{
public:
    __cdecl ItemPouch(void);  // 0x40d810
    bool __cdecl Initialize(::GameObject *, unsigned __int64, unsigned __int64, unsigned __int64, unsigned __int64, unsigned __int64, unsigned __int64, unsigned __int64);  // 0x40d890
protected:
    bool __cdecl Put(unsigned __int64, short, char);  // 0x40d9f0
public:
    short __cdecl Take(char, short, unsigned __int64 *);  // 0x40db10
    void __cdecl TakeEffect(::Zone *, ::Pc *);  // 0x40dbb0
    ::DroppedItem const * __cdecl Next(::DroppedItem const *) const;  // 0x40dd70
private:
    bool __cdecl put(unsigned __int64, int, char);  // 0x40dde0
public:
    void __cdecl Make(int, bool, ::SelectedRewardItemIndexInfo *);  // 0x40dea0
protected:
    void __cdecl make(::Data::RewardRecordPtr, int, bool, char, ::SelectedRewardItemIndexInfo *);  // 0x40e050
    void __cdecl makeTestServerRareItem(::Data::RewardRecordPtr, int, char);  // 0x40f0d0
public:
    bool __cdecl CheckSelectedReward(::SelectedRewardItemIndexInfo *);  // 0x40f290
};

