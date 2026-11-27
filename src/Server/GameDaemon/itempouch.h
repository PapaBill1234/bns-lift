// itempouch.h: itempouch.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

// LIFT: view of the PDB class Data::RewardRecordPtr (DrRecordPtr: one record pointer, the default constructor sets it to NULL).
class RewardRecordPtrView
{
public:
    RewardRecordPtrView() : _record(NULL) {}
    void *_record;  // +0x0 (PDB: DrRecordPtr::_record, DrEl *)
};

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
private:
    // PDB layout (size 0x1E0).
    int money;  // +0x0
    int itemCount;  // +0x4
    int totalItemCount;  // +0x8
    ::DroppedItem item[16];  // +0x10 (MAX_ITEM_COUNT)
    short pouchId;  // +0x190
    ::GameObject *owner;  // +0x198
    ::RewardRecordPtrView _reward;  // +0x1A0 (PDB type: Data::RewardRecordPtr)
    ::RewardRecordPtrView _eventReward;  // +0x1A8
    ::RewardRecordPtrView _additionalReward;  // +0x1B0
    ::RewardRecordPtrView _additionalReward2;  // +0x1B8
    ::RewardRecordPtrView _additionalReward3;  // +0x1C0
    ::RewardRecordPtrView _additionalReward4;  // +0x1C8
    ::RewardRecordPtrView _additionalReward5;  // +0x1D0
    unsigned char _appearance;  // +0x1D8
    unsigned short _maxAppearancePrioirty;  // +0x1DA
    char _itemPouchAdditionalInfo;  // +0x1DC
    char _diceResult;  // +0x1DD
};
static_assert(sizeof(ItemPouch) == 0x1E0, "sizeof ItemPouch");

