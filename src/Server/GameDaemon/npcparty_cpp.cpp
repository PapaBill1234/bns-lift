// npcparty_cpp.cpp: npcparty.cpp (GameDaemon PDB, 2019 + PDB).
#include "npcparty.h"
#include "npc.h"
#include "LiftStub.h"

#define NPCPARTY_FILE L"e:\\dailybuild02\\gamedaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\gamedaemon\\NpcParty.cpp"

// 0x428bc0
#pragma comment(linker, "/INCLUDE:??1NpcParty@@MEAA@XZ")  // LIFT: dead-strip keep (no live caller yet)
__cdecl NpcParty::~NpcParty(void)
{
    if (_timer != nullptr)
    {
        // LIFT: NpcPartyTimer derives from RefCntObject in the PDB. The skeleton base has no RefCntObject yet.
        reinterpret_cast<::RefCntObject *>(_timer)->removeReferenceCount(NPCPARTY_FILE, 30);
        _timer = nullptr;
    }
}

// 0x428c00
bool __cdecl NpcParty::initializeTimer(void)
{
    LIFT_STUB(0x428c00);
}

// 0x428c70
bool __cdecl NpcParty::Add(::Npc *)
{
    LIFT_STUB(0x428c70);
}

// 0x428cd0
#pragma comment(linker, "/INCLUDE:?Remove@NpcParty@@UEAA_NPEAVNpc@@@Z")  // LIFT: dead-strip keep (no live caller yet)
bool __cdecl NpcParty::Remove(::Npc *npc)
{
    if (npc == nullptr)
        return false;
    for (int i = 0; i < _maxNpc; ++i)
    {
        if (_npc[i] == npc)
        {
            _npc[i] = nullptr;
            return true;
        }
    }
    return false;
}

// 0x428d10
void __cdecl NpcParty::SetVar(int, __int64)
{
    LIFT_STUB(0x428d10);
}

// 0x428d50
void __cdecl NpcPartyTimer::SetTimer(long)
{
    LIFT_STUB(0x428d50);
}
