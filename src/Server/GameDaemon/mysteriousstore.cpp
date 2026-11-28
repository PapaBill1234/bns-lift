// mysteriousstore.cpp: mysteriousstore.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "mysteriousstore.h"
#include "npc.h"
#include "pc.h"
#include "Log.h"
#include "LiftStub.h"

#define MYSTERIOUSSTORE_FILE L"e:\\dailybuild02\\gamedaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\gamedaemon\\MysteriousStore.cpp"

static_assert(sizeof(MysteriousStore) == 0x1C0, "sizeof MysteriousStore");

#pragma comment(linker, "/INCLUDE:?IsAuthorizedMember@MysteriousStore@@QEBA_N_K@Z")  // LIFT: dead-strip keep (no live caller yet)

// 0x16d7a0
__cdecl MysteriousStore::MysteriousStore(::Npc *, ::Data::MysteriousStoreRecordPtr, ::NpcSpawnParam const &)
{
    LIFT_STUB(0x16d7a0);
}

// 0x16d9c0
bool __cdecl MysteriousStore::IsAuthorizedMember(unsigned __int64 pcdbid) const
{
    for (int i = 0; i < 24; ++i)
    {
        if (_authorizedPcdbid[i] == pcdbid)
            return true;
    }
    Log::Write(Log::LT_ERROR, MYSTERIOUSSTORE_FILE, 48, L"[mysterious store], cannot find pc in authorized member, pcdbid:0x%I64X", pcdbid);
    return false;
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
