// gamemath.h: gamemath.cpp, gamemath.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

int __cdecl randomValue2(int);  // 0x10db0
short __cdecl getAngle(::vector16 const &, ::vector16 const &);  // 0x27280
short __cdecl getNormalizedAngle(::vector16 const &);  // 0x272e0
int __cdecl randomValue2(int, int);  // 0x96bb0
bool __cdecl randomId64Pickup2(unsigned __int64 *const, unsigned __int64 *const, int, int);  // 0x96c30
int __cdecl randomValue(int);  // 0xd5760
int __cdecl randomValue(int, int);  // 0xd57c0
bool __cdecl tryProbability(int);  // 0xd5840
bool __cdecl tryProbability10000(int);  // 0xd58d0
int __cdecl randomValue2Amount100(void);  // 0x1808e0
bool __cdecl randomInt8Pickup2(char *const, char *const, int, int);  // 0x453920
