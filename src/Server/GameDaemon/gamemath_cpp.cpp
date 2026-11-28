// gamemath_cpp.cpp: gamemath.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "gamemath.h"
#include "gamedaemon.h"
#include "gamedconfig.h"
#include "LiftStub.h"
#include <stdlib.h>

#pragma comment(linker, "/INCLUDE:?tryProbability@@YA_NH@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?tryProbability10000@@YA_NH@Z")  // LIFT: dead-strip keep (no live caller yet)

// Partial PDB offset: GamedConfig::_userandomValue2 is at +0x30C.
static bool useRandomValue2()
{
    return *(reinterpret_cast<const bool *>(GameDaemon::GamedInstance->config) + 0x30C);
}

// 0xd5760
int __cdecl randomValue(int)
{
    LIFT_STUB(0xd5760);
}

// 0xd57c0
int __cdecl randomValue(int, int)
{
    LIFT_STUB(0xd57c0);
}

// 0xd5840
bool __cdecl tryProbability(int probability)
{
    if (!useRandomValue2())
        return rand() % 100 < probability;
    unsigned int value;
    do
        value = rand();
    while (value >= 0x7FBC);
    return static_cast<int>(value / 0x147) < probability;
}

// 0xd58d0
bool __cdecl tryProbability10000(int probability)
{
    if (!useRandomValue2())
        return rand() % 10000 < probability;
    unsigned int value;
    do
        value = rand();
    while (value >= 0x7530);
    return static_cast<int>(value / 3) < probability;
}
