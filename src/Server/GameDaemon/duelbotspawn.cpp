// duelbotspawn.cpp: duelbotspawn.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "duelbotspawn.h"
#include "duelbot.h"
#include "duelbottask.h"
#include "LiftStub.h"

// 0xaa700
bool __cdecl DuelBotSpawn::Init(void)
{
    LIFT_STUB(0xaa700);
}

// 0xaa790
bool __cdecl DuelBotSpawn::Spawn(unsigned __int64, ::vector16 &, long)
{
    LIFT_STUB(0xaa790);
}

// 0xaab60
void __cdecl DuelBotSpawn::Despawn(::DuelBot *, bool, bool)
{
    LIFT_STUB(0xaab60);
}

// 0xaad70
void __cdecl DuelBotSpawn::Despawn(char, bool, bool)
{
    LIFT_STUB(0xaad70);
}

// 0xaae70
void __cdecl DuelBotSpawn::DespawnAll(bool)
{
    LIFT_STUB(0xaae70);
}

// 0xab050
void __cdecl DuelBotSpawn::Cleanup(void)
{
    LIFT_STUB(0xab050);
}

// 0xab0e0
::DuelBot * __cdecl DuelBotSpawn::CreateDuelBot(unsigned __int64, ::DuelBotSpawnTask *, int)
{
    LIFT_STUB(0xab0e0);
}

// 0xab3e0
void __cdecl DuelBotSpawn::CancelSpawn(::DuelBotSpawnTask *, int)
{
    LIFT_STUB(0xab3e0);
}

// 0xab460
void __cdecl DuelBotSpawn::forceDespawn(::DuelBot *, bool)
{
    LIFT_STUB(0xab460);
}
