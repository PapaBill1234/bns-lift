// String.obj (CacheGate PDB).  // ❓ file name: "String.h" can hide <string.h> on a case-insensitive file system.
#pragma once

union id128
{
    unsigned char guid[16];  // ❓ PDB type 0x15B9: id128::<unnamed-type-guid>
    unsigned long long id[2];
};
static_assert(sizeof(id128) == 0x10, "sizeof id128");

class String
{
public:
    static bool GetId128FromGuidString(wchar_t const* guidString, id128* id);  // 0x1B360 (SmartCouponDaemon)
};
