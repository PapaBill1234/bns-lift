// mysteriousstore.cpp: mysteriousstore.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "mysteriousstore.h"
#include "npc.h"
#include "pc.h"
#include "LiftStub.h"

// 0x16d7a0
__cdecl MysteriousStore::MysteriousStore(::Npc *, ::Data::MysteriousStoreRecordPtr, ::NpcSpawnParam const &)
{
    LIFT_STUB(0x16d7a0);
}

// 0x16d9c0
bool __cdecl MysteriousStore::IsAuthorizedMember(unsigned __int64) const
{
    LIFT_STUB(0x16d9c0);
}

// 0x16da10
bool __cdecl MysteriousStore::Buy(unsigned __int64, char)
{
    LIFT_STUB(0x16da10);
}

// 0x16dac0
bool __cdecl MysteriousStore::SendItemList(::Pc *) const
{
    LIFT_STUB(0x16dac0);
}
