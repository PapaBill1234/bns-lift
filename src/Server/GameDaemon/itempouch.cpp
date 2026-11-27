// itempouch.cpp: itempouch.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "itempouch.h"
#include "gameobject.h"
#include "pc.h"
#include "zone.h"
#include <string.h>
#include "LiftStub.h"

// 0x40d810
#pragma comment(linker, "/INCLUDE:??0ItemPouch@@QEAA@XZ")  // LIFT: dead-strip keep (no live caller yet)
__cdecl ItemPouch::ItemPouch(void)
    : pouchId(0)
{
    money = 0;
    itemCount = 0;
    totalItemCount = 0;
    owner = NULL;
    _appearance = 0;
    _maxAppearancePrioirty = 0;
    _itemPouchAdditionalInfo = 0;
    _diceResult = -1;
    memset(item, 0, sizeof(item));
}

// 0x40d890
bool __cdecl ItemPouch::Initialize(::GameObject *, unsigned __int64, unsigned __int64, unsigned __int64, unsigned __int64, unsigned __int64, unsigned __int64, unsigned __int64)
{
    LIFT_STUB(0x40d890);
}

// 0x40d9f0
bool __cdecl ItemPouch::Put(unsigned __int64, short, char)
{
    LIFT_STUB(0x40d9f0);
}

// 0x40db10
short __cdecl ItemPouch::Take(char, short, unsigned __int64 *)
{
    LIFT_STUB(0x40db10);
}

// 0x40dbb0
void __cdecl ItemPouch::TakeEffect(::Zone *, ::Pc *)
{
    LIFT_STUB(0x40dbb0);
}

// 0x40dd70
#pragma comment(linker, "/INCLUDE:?Next@ItemPouch@@QEBAPEBUDroppedItem@@PEBU2@@Z")  // LIFT: dead-strip keep (no live caller yet)
::DroppedItem const * __cdecl ItemPouch::Next(::DroppedItem const *i) const
{
    __int64 index = -1;
    if (i != NULL)
    {
        index = i - item;
        if (index < 0)
            return NULL;
    }

    for (++index; index < 16; ++index)  // LIFT: 16 = MAX_ITEM_COUNT
    {
        if (item[index].valid == 1)
            return &item[index];
    }
    return NULL;
}

// 0x40dde0
bool __cdecl ItemPouch::put(unsigned __int64, int, char)
{
    LIFT_STUB(0x40dde0);
}

// 0x40dea0
void __cdecl ItemPouch::Make(int, bool, ::SelectedRewardItemIndexInfo *)
{
    LIFT_STUB(0x40dea0);
}

// 0x40e050
void __cdecl ItemPouch::make(::Data::RewardRecordPtr, int, bool, char, ::SelectedRewardItemIndexInfo *)
{
    LIFT_STUB(0x40e050);
}

// 0x40f0d0
void __cdecl ItemPouch::makeTestServerRareItem(::Data::RewardRecordPtr, int, char)
{
    LIFT_STUB(0x40f0d0);
}

// 0x40f290
bool __cdecl ItemPouch::CheckSelectedReward(::SelectedRewardItemIndexInfo *)
{
    LIFT_STUB(0x40f290);
}
