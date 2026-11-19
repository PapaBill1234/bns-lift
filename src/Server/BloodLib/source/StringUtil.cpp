// String.obj (SmartCouponDaemon PDB). LIFT: file name, see StringUtil.h.
#include "StringUtil.h"
#include <wchar.h>
#include <windows.h>
#include <objbase.h>

// LIFT: the PDB module of ID128_GUID_ZERO is not known. ❓ String.obj is a guess.
extern id128 const ID128_GUID_ZERO = {0};

// 0x1B360 (SmartCouponDaemon)
bool String::GetId128FromGuidString(wchar_t const* guidString, id128* id)
{
    if (guidString == nullptr)
        return false;
    if (wcslen(guidString) != 36)
        return false;
    wchar_t buffer[40] = L"{";  // LIFT: orig 0xdd90 calls memset for the rest of the array
    wcscat_s(buffer, 39, guidString);
    wcscat_s(buffer, 39, L"}");
    GUID guid;
    if (CLSIDFromString(buffer, &guid) != S_OK)
        return false;
    if (id != nullptr)
        memcpy(id, &guid, sizeof(GUID));
    return true;
}
