// itempouch.cpp: itempouch.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "itempouch.h"
#include "gameobject.h"
#include "pc.h"
#include "zone.h"
#include "LiftStub.h"

// 0x40d810
__cdecl ItemPouch::ItemPouch(void)
{
    LIFT_STUB(0x40d810);
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
::DroppedItem const * __cdecl ItemPouch::Next(::DroppedItem const *) const
{
    LIFT_STUB(0x40dd70);
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
