// String.obj (CacheGate PDB).  // ❓ file name: "String.h" can hide <string.h> on a case-insensitive file system.
#pragma once

// PDB type id128::<unnamed-type-guid> has id1, id2, id3 and id4[8] (PostOfficeDaemon types.h:1335).
union id128
{
    struct
    {
        unsigned long id1;
        unsigned short id2;
        unsigned short id3;
        unsigned char id4[8];
        // ❓ Not in the PDB. Byte access for the older lifts (guid[i]).
        operator unsigned char*() { return reinterpret_cast<unsigned char*>(this); }
        operator unsigned char const*() const { return reinterpret_cast<unsigned char const*>(this); }
    } guid;
    unsigned long long id[2];
};
static_assert(sizeof(id128) == 0x10, "sizeof id128");

class String
{
public:
    static bool GetId128FromGuidString(wchar_t const* guidString, id128* id);  // 0x1B360 (SmartCouponDaemon)
};
