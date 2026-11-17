// String.obj (CacheGate PDB). LIFT: file name. "String.h" can hide <string.h> on a case-insensitive file system.
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
        // LIFT: Not in the PDB. Byte access for the older lifts (guid[i]).
        operator unsigned char*() { return reinterpret_cast<unsigned char*>(this); }
        operator unsigned char const*() const { return reinterpret_cast<unsigned char const*>(this); }
    } guid;
    unsigned long long id[2];
};
static_assert(sizeof(id128) == 0x10, "sizeof id128");

// PDB global (types.h: `id128 ID128_GUID_ZERO`). CacheGate 0x46be8 is in read-only data, and the inline
// BnsCommonConfig constructor copies it (two qword loads in 0x13e0 and 0x1600).
extern id128 ID128_GUID_ZERO;

class String
{
public:
    static bool GetId128FromGuidString(wchar_t const* guidString, id128* id);  // 0x1B360 (SmartCouponDaemon)
};
