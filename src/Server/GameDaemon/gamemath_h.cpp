// gamemath_h.cpp: gamemath.h (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "gamemath.h"
#include "LiftStub.h"
#include <math.h>
#include <stdlib.h>

#pragma comment(linker, "/INCLUDE:?getAngle@@YAFAEBUvector16@@0@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?randomValue2Amount100@@YAHXZ")  // LIFT: dead-strip keep (no live caller yet)

namespace
{
// LIFT: view of the PDB struct vector16 (x, y, z). The skeleton vector16 has no members yet.
struct Vector16View
{
    short x;  // +0
    short y;  // +2
    short z;  // +4
};

// LIFT: inline vector16 subtraction (PDB: vector16::operator-, inlined).
inline Vector16View operator-(Vector16View const &a, Vector16View const &b)
{
    Vector16View r;
    r.x = a.x - b.x;
    r.y = a.y - b.y;
    r.z = a.z - b.z;
    return r;
}
}

// 0x10db0
int __cdecl randomValue2(int)
{
    LIFT_STUB(0x10db0);
}

// 0x27280
short __cdecl getAngle(::vector16 const & from, ::vector16 const & to)
{
    Vector16View d = reinterpret_cast<Vector16View const &>(to) - reinterpret_cast<Vector16View const &>(from);
    short angle = static_cast<short>(atan2(static_cast<double>(d.y), static_cast<double>(d.x)) * 180.0 / 3.14);
    if (angle < 0)
        angle += 360;
    return angle;
}

// 0x272e0
short __cdecl getNormalizedAngle(::vector16 const &)
{
    LIFT_STUB(0x272e0);
}

// 0x96bb0
int __cdecl randomValue2(int, int)
{
    LIFT_STUB(0x96bb0);
}

// 0x96c30
bool __cdecl randomId64Pickup2(unsigned __int64 *const, unsigned __int64 *const, int, int)
{
    LIFT_STUB(0x96c30);
}

// 0x1808e0
int __cdecl randomValue2Amount100(void)
{
    unsigned int value;
    do
    {
        value = rand();
    } while (value >= 32700);  // LIFT: 32700 = 100 * 327 (uniform 0..99)
    return value / 327;
}

// 0x453920
bool __cdecl randomInt8Pickup2(char *const, char *const, int, int)
{
    LIFT_STUB(0x453920);
}
